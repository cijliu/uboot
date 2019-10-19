
#include <config.h>
#include <common.h>
#include <malloc.h>
#include <asm/dma-mapping.h>
#include "ufs.h"
#include "scsi.h"

#include "scsi.c"
#define IF_FPGA() (0)

/* should use multithread */
struct dwc_ufs_hba g_dwc_host[MAX_DEVICE];
struct ufs_descriptor ufs_desc;

static uint32_t uic_cmd_read(uint32_t command, uint32_t arg1);
unsigned int *ufs_pack_cid(void);

uint8_t g_h8_cnt[MAX_DEVICE];
uint8_t g_tx_lane_num[MAX_DEVICE] = {0};
uint8_t g_rx_lane_num[MAX_DEVICE] = {0};
int wlun = 0;

#if defined(COMBO_PHY_V120)
struct pllChkInfo HsDefault[] = {
    {ATTR_MCB(RG_PLL_PRE_DIV), 0x0F, 0x0, "RG_PLL_PRE_DIV"},
    {ATTR_MCB(RG_PLL_SWC_EN), 0x01, 0x0, "RG_PLL_SWC_EN"},
    {ATTR_MCB(RG_PLL_FBK_S), 0x0F, 0x01, "RG_PLL_FBK_S"},
    {ATTR_MCB(RG_PLL_FBK_P), 0xFF, HS_R_B_FBK_P, "RG_PLL_FBK_P"},
    {ATTR_MCB(RG_PLL_TXHSGR), 0x03, HS_G_1_TXRXHSGR, "RG_PLL_TXHSGR"},
    {ATTR_MCB(RG_PLL_RXHSGR), 0x03, HS_G_1_TXRXHSGR, "RG_PLL_RXHSGR"},
};
#endif

static int ufs_read_string_index(char * dest, uint8_t desc_index)
{
    struct desc_params params;
    struct dwc_ufs_query_upiu *req_upiu = NULL;
    void *resp_upiu = NULL;
    int ret;
    u8 *p;
    char *str_buf = NULL;
    int i;
    int lenth = 0;
    int ret_desc_idn;
    GET_LOCAL_DWC_HOST();

    /*1.    get req resp upiu use slot 0 default,fill the pacake */
    req_upiu = (struct dwc_ufs_query_upiu *)(dwc_host->lrb[0].cmd_upiu);
    resp_upiu = dwc_host->lrb[0].resp_upiu;
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = STRING_DESC;
    params.desc_index = desc_index;
    params.length = STRING_DESC_LENGTH;
    modify_desc_upiu(&params);

    /*2.    start to read */
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_SUCCESS) {
        PRINT_ERROR("%s: read_descriptor fail. ret = %d\n", __func__, ret);
        return UFS_ERROR;
    }

    /*3.    show info*/
    p = ((u8 *)resp_upiu + QUERY_RESPONSE_HEAD_OFFSET);
    /*3.1   check idn*/
    ret_desc_idn = p[1];
    if(ret_desc_idn != STRING_DESC) {
        PRINT_ERROR("%s: ind error,send is 0x%08x,return is 0x%08x,\n", __func__, STRING_DESC, ret_desc_idn);
        return UFS_ERROR;
    }
    lenth = p[0];
    str_buf = (char *)malloc(lenth / 2 + 1);
    str_buf[lenth / 2] = '\0';
    for(i = QUERY_RESPONSE_DATA_OFFSET; i <= lenth; i++) {
        if(i % 2) {
            str_buf[i / 2 - 1] = p[i];
        }
    }
    (void)memcpy((void *)dest, (void *)str_buf, lenth / 2);

    if (str_buf) {
        free((void *)str_buf);
    }
    str_buf = NULL;

    return UFS_OK;
}

static int ufs_read_string_descriptor(void)
{
    int ret = UFS_ERROR;
    /*1.    get manufacturer name*/
    ret = ufs_read_string_index(ufs_desc.str_desc.manufacturer_name, ufs_desc.dev_desc.iManufacturerName);
    if(ret != UFS_OK) {
        UFS_PRINT("Get  MANUFACTURER_NAME name fail.\n");
        return UFS_ERROR;
    }

    /*2.    get product name*/
    ret = ufs_read_string_index(ufs_desc.str_desc.product_name, ufs_desc.dev_desc.iProductName);
    if(ret != UFS_OK) {
        UFS_PRINT("Get  PRODUCT_NAME name fail.\n");
        return UFS_ERROR;
    }

    return UFS_OK;
}

static int ufs_read_unit_descriptor(void)
{
    int ret;
    struct desc_params params;
    struct dwc_ufs_query_upiu *req_upiu = NULL;
    void *resp_upiu = NULL;
    uint8_t i;

    for( i = 0; i < UNIT_DESC_MAX; i++) {
        /* Unit Descriptor */
        params.req_upiu = req_upiu;
        params.part_desc = NULL;
        params.opcode = READ_DESC_OPCODE;
        params.desc_idn = UNIT_DESC;
        params.desc_index = i;
        params.length = UNIT_DESC_LENGTH;
        modify_desc_upiu(&params);
        ret = read_descriptor(req_upiu, &resp_upiu);
        if (ret != UFS_OK) {
            UFS_PRINT("READ UNIT_DESC error num is %x\n", ret);
            FUNC_EXIT();
            return ret;
        }
        memcpy((void *)(&ufs_desc.unit_desc.unit_index_desc[i]), (void *)((u8 *)resp_upiu + 32), UNIT_DESC_LENGTH);
    }

    /* RPMB Descriptor */
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = UNIT_DESC;
    params.desc_index = 0xc4;
    params.length = UNIT_DESC_LENGTH;
    modify_desc_upiu(&params);
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_OK) {
        UFS_PRINT("READ RPMB UNIT_DESC error num %x\n", ret);
        FUNC_EXIT();
        return ret;
    }
    memcpy((void *)(&ufs_desc.unit_desc.unit_RPMB_desc), (void *)((u8 *)resp_upiu + 32), UNIT_DESC_LENGTH);
    return UFS_OK;
}
static int ufs_read_conf_descriptor(void)
{
    int ret;
    struct desc_params params;
    struct dwc_ufs_query_upiu *req_upiu = NULL;
    void *resp_upiu = NULL;

    /* RPMB Descriptor */
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = CONFIGURATION_DESC;
    params.desc_index = 0;
    params.length = CONFIGURATION_DESC_LENGTH;
    modify_desc_upiu(&params);
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_OK) {
        UFS_PRINT("READ RPMB UNIT_DESC error num %x\n", ret);
        FUNC_EXIT();
        return ret;
    }
    memcpy((void *)(&ufs_desc.conf_desc), (void *)((u8 *)resp_upiu + 32), CONFIGURATION_DESC_LENGTH);

    return UFS_OK;
}
static int ufs_read_health_descriptor(void)
{
    int ret;
    struct desc_params params;
    struct dwc_ufs_query_upiu *req_upiu = NULL;
    void *resp_upiu = NULL;

    /* Health Descriptor */
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = HEALTH_DESC;
    params.desc_index = 0;
    params.length = HEALTH_DESC_LENGTH;
    modify_desc_upiu(&params);
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_OK) {
        UFS_PRINT("READ HEALTH error num %x\n", ret);
        FUNC_EXIT();
        return ret;
    }
    memcpy((void *)(&ufs_desc.heal_desc), (void *)((u8 *)resp_upiu + 32), HEALTH_DESC_LENGTH);

    return UFS_OK;
}
static void ufs_info_show_portion(void)
{
    enum POWER_MODE mode = DEFAULT_POWER_MODE;
    int hs_gear = DEFAULT_GEAR;
    int rate = DEFAULT_RATE;
    int lane = DEFAULT_LANE;

    UFS_PRINT("Manufacturer Name :%s\n", ufs_desc.str_desc.manufacturer_name);
    UFS_PRINT("Product Name :%s \n", ufs_desc.str_desc.product_name);
    UFS_PRINT("qTotalRawDeviceCapacity :0x%llx B\n", cpu_to_be64(ufs_desc.geo_desc.qTotalRawDeviceCapacity));
    UFS_PRINT("UFS %s Gear-%d Rate-%c Lanes-%d\n", ((mode == SLOW_MODE) ? "Slow" :
              ((mode == SLOWAUTO_MODE) ? "SlowAuto" :
               ((mode == FAST_MODE) ? "Fast" : "FastAuto"))),
              hs_gear, (rate == 1) ? 'A' : 'B', lane);
    UFS_PRINT("UFSHCI Version 0x%x \n", dwc_ufs_read_reg(UFS_VER_OFF));
    UFS_PRINT("UFS wSpecVersion 0x%x \n", to_bigendian16(ufs_desc.dev_desc.wSpecVersion));
}
static void ufs_info_show_dev_desc(void)
{
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("---UFS Device Descriptor-----\n");
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("bLength: 0x%x\n", ufs_desc.dev_desc.bLength);
    UFS_PRINT("bDescriptorType: 0x%x\n", ufs_desc.dev_desc.bDescriptorType);
    UFS_PRINT("bDevice: 0x%x\n", ufs_desc.dev_desc.bDevice);
    UFS_PRINT("bDeviceClass: 0x%x\n", ufs_desc.dev_desc.bDeviceClass);
    UFS_PRINT("bDeviceSubClass: 0x%x\n", ufs_desc.dev_desc.bDeviceSubClass);
    UFS_PRINT("bProtocol: 0x%x\n", ufs_desc.dev_desc.bProtocol);
    UFS_PRINT("bNumberLU: 0x%x\n", ufs_desc.dev_desc.bNumberLU);
    UFS_PRINT("bNumberWLU: 0x%x\n", ufs_desc.dev_desc.bNumberWLU);
    UFS_PRINT("bBootEnable: 0x%x\n", ufs_desc.dev_desc.bBootEnable);
    UFS_PRINT("bDescrAccessEn: 0x%x\n", ufs_desc.dev_desc.bDescrAccessEn);
    UFS_PRINT("bInitPowerMode: 0x%x\n", ufs_desc.dev_desc.bInitPowerMode);
    UFS_PRINT("bHighPriorityLUN: 0x%x\n", ufs_desc.dev_desc.bHighPriorityLUN);
    UFS_PRINT("bSecureRemovalType: 0x%x\n", ufs_desc.dev_desc.bSecureRemovalType);
    UFS_PRINT("bSecurityLU: 0x%x\n", ufs_desc.dev_desc.bSecurityLU);
    UFS_PRINT("bBackgroundOpsTermLat: 0x%x\n", ufs_desc.dev_desc.bBackgroundOpsTermLat);
    UFS_PRINT("bInitActiveICCLevel: 0x%x\n", ufs_desc.dev_desc.bInitActiveICCLevel);
    UFS_PRINT("wSpecVersion: 0x%04x\n", to_bigendian16(ufs_desc.dev_desc.wSpecVersion));
    UFS_PRINT("wManufactureDate: 0x%04x\n", to_bigendian16(ufs_desc.dev_desc.wManufactureDate));
    UFS_PRINT("iManufacturerName: 0x%x\n", ufs_desc.dev_desc.iManufacturerName);
    UFS_PRINT("iProductName: 0x%x\n", ufs_desc.dev_desc.iProductName);
    UFS_PRINT("iSerialNumber: 0x%x\n", ufs_desc.dev_desc.iSerialNumber);
    UFS_PRINT("iOemID: 0x%x\n", ufs_desc.dev_desc.iOemID);
    UFS_PRINT("wManufacturerID: 0x%04x\n", to_bigendian16(ufs_desc.dev_desc.wManufacturerID));
    UFS_PRINT("bUD0BaseOffset: 0x%x\n", ufs_desc.dev_desc.bUD0BaseOffset);
    UFS_PRINT("bUDConfigPLength: 0x%x\n", ufs_desc.dev_desc.bUDConfigPLength);
    UFS_PRINT("bDeviceRTTCap: 0x%x\n", ufs_desc.dev_desc.bDeviceRTTCap);
    UFS_PRINT("wPeriodicRTCUpdate: 0x%04x\n", to_bigendian16(ufs_desc.dev_desc.wPeriodicRTCUpdate));
    UFS_PRINT("bUFSFeatureSupport: 0x%x\n", ufs_desc.dev_desc.bUFSFeatureSupport);
    UFS_PRINT("bFFUTimeout: 0x%x\n", ufs_desc.dev_desc.bFFUTimeout);
    UFS_PRINT("bQueueDepth: 0x%x\n", ufs_desc.dev_desc.bQueueDepth);
    UFS_PRINT("wDeviceVersion: 0x%x\n", to_bigendian16(ufs_desc.dev_desc.wDeviceVersion));
    UFS_PRINT("bNumSecureWPArea: 0x%x\n", ufs_desc.dev_desc.bNumSecureWPArea);
    UFS_PRINT("dPSAMaxDataSize: 0x%x\n", to_bigendian32(ufs_desc.dev_desc.dPSAMaxDataSize));
    UFS_PRINT("bPSAStateTimeout: 0x%x\n", ufs_desc.dev_desc.bPSAStateTimeout);
    UFS_PRINT("iProductRevisionLevel: 0x%x\n", ufs_desc.dev_desc.iProductRevisionLevel);
}
static void ufs_info_show_geo_desc(void)
{
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("---UFS Geometry Descriptor--\n");
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("bLength: 0x%x\n", ufs_desc.geo_desc.bLength);
    UFS_PRINT("bDescriptorType: 0x%x\n", ufs_desc.geo_desc.bDescriptorType);
    UFS_PRINT("bMediaTechnology: 0x%x\n", ufs_desc.geo_desc.bMediaTechnology);
    UFS_PRINT("Reserved: 0x%x\n", ufs_desc.geo_desc.Reserved);
    UFS_PRINT("qTotalRawDeviceCapacity: 0x%llx\n", cpu_to_be64(ufs_desc.geo_desc.qTotalRawDeviceCapacity));
    UFS_PRINT("bMaxNumberLU: 0x%x\n", ufs_desc.geo_desc.bMaxNumberLU);
    UFS_PRINT("dSegmentSize: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dSegmentSize));
    UFS_PRINT("bAllocationUnitSize: 0x%x\n", ufs_desc.geo_desc.bAllocationUnitSize);
    UFS_PRINT("bMinAddrBlockSize: 0x%x\n", ufs_desc.geo_desc.bMinAddrBlockSize);
    UFS_PRINT("bOptimalReadBlockSize: 0x%x\n", ufs_desc.geo_desc.bOptimalReadBlockSize);
    UFS_PRINT("bOptimalWriteBlockSize: 0x%x\n", ufs_desc.geo_desc.bOptimalWriteBlockSize);
    UFS_PRINT("bMaxInBufferSize: 0x%x\n", ufs_desc.geo_desc.bMaxInBufferSize);
    UFS_PRINT("bMaxOutBufferSize: 0x%x\n", ufs_desc.geo_desc.bMaxOutBufferSize);
    UFS_PRINT("bRPMB_ReadWriteSize: 0x%x\n", ufs_desc.geo_desc.bRPMB_ReadWriteSize);
    UFS_PRINT("bDynamicCapacityResourcePolicy: 0x%x\n", ufs_desc.geo_desc.bDynamicCapacityResourcePolicy);
    UFS_PRINT("bDataOrdering: 0x%x\n", ufs_desc.geo_desc.bDataOrdering);
    UFS_PRINT("bMaxContexIDNumber: 0x%x\n", ufs_desc.geo_desc.bMaxContexIDNumber);
    UFS_PRINT("bSysDataTagUnitSize: 0x%x\n", ufs_desc.geo_desc.bSysDataTagUnitSize);
    UFS_PRINT("bSysDataTagResSize: 0x%x\n", ufs_desc.geo_desc.bSysDataTagResSize);
    UFS_PRINT("bSupportedSecRTypes: 0x%x\n", ufs_desc.geo_desc.bSupportedSecRTypes);
    UFS_PRINT("wSupportedMemoryTypes: 0x%x\n", to_bigendian16(ufs_desc.geo_desc.wSupportedMemoryTypes));
    UFS_PRINT("dSystemCodeMaxNAllocU: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dSystemCodeMaxNAllocU));
    UFS_PRINT("wSystemCodeCapAdjFac: 0x%x\n", to_bigendian16(ufs_desc.geo_desc.wSystemCodeCapAdjFac));
    UFS_PRINT("dNonPersistMaxNAllocU: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dNonPersistMaxNAllocU));
    UFS_PRINT("wNonPersistCapAdjFac: 0x%x\n", to_bigendian16(ufs_desc.geo_desc.wNonPersistCapAdjFac));
    UFS_PRINT("dEnhanced1MaxNAllocU: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dEnhanced1MaxNAllocU));
    UFS_PRINT("wEnhanced1CapAdjFac: 0x%x\n", to_bigendian16(ufs_desc.geo_desc.wEnhanced1CapAdjFac));
    UFS_PRINT("dEnhanced2MaxNAllocU: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dEnhanced2MaxNAllocU));
    UFS_PRINT("wEnhanced2CapAdjFac: 0x%x\n", to_bigendian16(ufs_desc.geo_desc.wEnhanced2CapAdjFac));
    UFS_PRINT("dEnhanced3MaxNAllocU: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dEnhanced3MaxNAllocU));
    UFS_PRINT("wEnhanced3CapAdjFac: 0x%x\n", to_bigendian16(ufs_desc.geo_desc.wEnhanced3CapAdjFac));
    UFS_PRINT("dEnhanced4MaxNAllocU: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dEnhanced4MaxNAllocU));
    UFS_PRINT("wEnhanced4CapAdjFac: 0x%x\n", to_bigendian16(ufs_desc.geo_desc.wEnhanced4CapAdjFac));
    UFS_PRINT("dOptimalLogicalBlockSize: 0x%x\n", to_bigendian32(ufs_desc.geo_desc.dOptimalLogicalBlockSize));
}
static void ufs_info_show_heal_desc(void)
{
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("---UFS Health Descriptor--\n");
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("bLength: 0x%x\n", ufs_desc.heal_desc.bLength);
    UFS_PRINT("bDescriptorIDN: 0x%x\n", ufs_desc.heal_desc.bDescriptorIDN);
    UFS_PRINT("bPreEOLInfo: 0x%x\n", ufs_desc.heal_desc.bPreEOLInfo);
    UFS_PRINT("bDeviceLifeTimeEstA: 0x%x\n", ufs_desc.heal_desc.bDeviceLifeTimeEstA);
    UFS_PRINT("bDeviceLifeTimeEstB: 0x%x\n", ufs_desc.heal_desc.bDeviceLifeTimeEstB);
}
static void ufs_info_show_unit_desc(void)
{
    int i = 0;

    for(i = 0; i < UNIT_DESC_MAX; i++) {
        UFS_PRINT("--------------------------\n");
        UFS_PRINT("---UFS Unit %d Descriptor----\n", i);
        UFS_PRINT("--------------------------\n");
        UFS_PRINT("bLength:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bLength);
        UFS_PRINT("bDescriptorType:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bDescriptorType);
        UFS_PRINT("bUnitIndex:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bUnitIndex);
        UFS_PRINT("bLUEnable:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bLUEnable);
        UFS_PRINT("bBootLunID:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bBootLunID);
        UFS_PRINT("bLUWriteProtect:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bLUWriteProtect);
        UFS_PRINT("bLUQueueDepth:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bLUQueueDepth);
        UFS_PRINT("bPSASensitive:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bPSASensitive);
        UFS_PRINT("bMemoryType:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bMemoryType);
        UFS_PRINT("bDataReliability:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bDataReliability);
        UFS_PRINT("bLogicalBlockSize:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bLogicalBlockSize);
        UFS_PRINT("qLogicalBlockCount:0x%llx\n", cpu_to_be64(ufs_desc.unit_desc.unit_index_desc[i].qLogicalBlockCount));
        UFS_PRINT("dEraseBlockSize:0x%x\n", to_bigendian32(ufs_desc.unit_desc.unit_index_desc[i].dEraseBlockSize));
        UFS_PRINT("bProvisioningType:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bProvisioningType);
        UFS_PRINT("qPhyMemResourceCount:0x%x\n", to_bigendian32(ufs_desc.unit_desc.unit_index_desc[i].qPhyMemResourceCount));
        UFS_PRINT("wContextCapabilities:0x%x\n", to_bigendian16(ufs_desc.unit_desc.unit_index_desc[i].wContextCapabilities));
        UFS_PRINT("bLargeUnitGranularity_Muint8_t:0x%x\n", ufs_desc.unit_desc.unit_index_desc[i].bLargeUnitGranularity_Muint8_t);
    }
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("--UFS Unit RPMB Descriptor---\n");
    UFS_PRINT("--------------------------\n");
    UFS_PRINT("bLength:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bLength);
    UFS_PRINT("bDescriptorType:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bDescriptorType);
    UFS_PRINT("bUnitIndex:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bUnitIndex);
    UFS_PRINT("bLUEnable:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bLUEnable);
    UFS_PRINT("bBootLunID:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bBootLunID);
    UFS_PRINT("bLUWriteProtect:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bLUWriteProtect);
    UFS_PRINT("bLUQueueDepth:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bLUQueueDepth);
    UFS_PRINT("bPSASensitive:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bPSASensitive);
    UFS_PRINT("bMemoryType:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bMemoryType);
    UFS_PRINT("Reserved1:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.Reserved1);
    UFS_PRINT("bLogicalBlockSize:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bLogicalBlockSize);
    UFS_PRINT("qLogicalBlockCount:0x%llx\n", cpu_to_be64(ufs_desc.unit_desc.unit_RPMB_desc.qLogicalBlockCount));
    UFS_PRINT("dEraseBlockSize:0x%x\n", to_bigendian32(ufs_desc.unit_desc.unit_RPMB_desc.dEraseBlockSize));
    UFS_PRINT("bProvisioningType:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.bProvisioningType);
    UFS_PRINT("qPhyMemResourceCount:0x%x\n", to_bigendian32(ufs_desc.unit_desc.unit_RPMB_desc.qPhyMemResourceCount));
    UFS_PRINT("Reserved2[0]:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.Reserved2[0]);
    UFS_PRINT("Reserved2[1]:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.Reserved2[1]);
    UFS_PRINT("Reserved2[2]:0x%x\n", ufs_desc.unit_desc.unit_RPMB_desc.Reserved2[2]);
}
static void ufs_info_show_conf_desc(void)
{
    int i = 0;
    UFS_PRINT("------------------------------------------\n");
    UFS_PRINT("---UFS Device Descriptor Configuration Param----\n");
    UFS_PRINT("------------------------------------------\n");

    UFS_PRINT("bLength:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bLength);
    UFS_PRINT("bDescriptorType:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bDescriptorType);
    UFS_PRINT("bConfDescContinue:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bConfDescContinue);
    UFS_PRINT("bBootEnable:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bBootEnable);
    UFS_PRINT("bDescrAccessEn:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bDescrAccessEn);
    UFS_PRINT("bInitPowerMode:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bInitPowerMode);
    UFS_PRINT("bHighPriorityLUN:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bHighPriorityLUN);
    UFS_PRINT("bSecureRemovalType:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bSecureRemovalType);
    UFS_PRINT("bInitActiveICCLevel:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.bInitActiveICCLevel);
    UFS_PRINT("wPeriodicRTCUpdate:0x%x\n", to_bigendian16(ufs_desc.conf_desc.dev_desc_conf_param.wPeriodicRTCUpdate));
    UFS_PRINT("Reserved[0]:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.Reserved[0]);
    UFS_PRINT("Reserved[1]:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.Reserved[1]);
    UFS_PRINT("Reserved[2]:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.Reserved[2]);
    UFS_PRINT("Reserved[3]:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.Reserved[3]);
    UFS_PRINT("Reserved[4]:0x%x\n", ufs_desc.conf_desc.dev_desc_conf_param.Reserved[4]);
    for(i = 0; i < UNIT_DESC_MAX; i++) {
        UFS_PRINT("-----------------------------------------------------\n");
        UFS_PRINT("---UFS Unit %d Descriptor Configuration Param  Descriptor----\n", i);
        UFS_PRINT("-----------------------------------------------------\n");

        UFS_PRINT("bLUEnable:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].bLUEnable);
        UFS_PRINT("bBootLunID:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].bBootLunID);
        UFS_PRINT("bLUWriteProtect:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].bLUWriteProtect);
        UFS_PRINT("bMemoryType:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].bMemoryType);
        UFS_PRINT("dNumAllocUnits:0x%x\n", to_bigendian32(ufs_desc.conf_desc.unit_desc_conf_param[i].dNumAllocUnits));
        UFS_PRINT("bDataReliability:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].bDataReliability);
        UFS_PRINT("bLogicalBlockSize:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].bLogicalBlockSize);
        UFS_PRINT("bProvisioningType:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].bProvisioningType);
        UFS_PRINT("wContextCapabilities:0x%x\n", to_bigendian16(ufs_desc.conf_desc.unit_desc_conf_param[i].wContextCapabilities));
        UFS_PRINT("Reserved[0]:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].Reserved[0]);
        UFS_PRINT("Reserved[1]:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].Reserved[1]);
        UFS_PRINT("Reserved[2]:0x%x\n", ufs_desc.conf_desc.unit_desc_conf_param[i].Reserved[2]);
    }
}
static void ufs_info_show_str_desc(void)
{
    UFS_PRINT("Manufacturer Name :%s\n", ufs_desc.str_desc.manufacturer_name);
    UFS_PRINT("Product Name :%s \n", ufs_desc.str_desc.product_name);
}

static void ufs_info_show_all(void)
{
    ufs_info_show_str_desc();
    ufs_info_show_dev_desc();
    ufs_info_show_geo_desc();
    ufs_info_show_unit_desc();
    ufs_info_show_conf_desc();
}
int ufs_show_desc_info(enum info_show_type type)
{
    int ret = 0;

    if(ufs_desc.desc_is_init == FALSE) {
        ret = ufs_read_string_descriptor();
        if(ret != UFS_OK) {
            UFS_PRINT("ufs_read_string_descriptor fail.\n");
            ufs_desc.desc_is_init = FALSE;
            return UFS_ERROR;
        }
        ret = ufs_read_unit_descriptor();
        if(ret != UFS_OK) {
            UFS_PRINT("ufs_read_unit_descriptor fail.\n");
            ufs_desc.desc_is_init = FALSE;
            return UFS_ERROR;
        }
        ret = ufs_read_conf_descriptor();
        if(ret != UFS_OK) {
            UFS_PRINT("ufs_read_conf_descriptor fail.\n");
            ufs_desc.desc_is_init = FALSE;
            return UFS_ERROR;
        }
        ret = ufs_read_health_descriptor();
        if(ret != UFS_OK) {
            UFS_PRINT("ufs_read_health_descriptor fail.\n");
            ufs_desc.desc_is_init = FALSE;
            return UFS_ERROR;
        }
        ufs_desc.desc_is_init = TRUE;
    }

    switch(type) {
        case UFS_INFO_SHOW_BASIC:
            ufs_info_show_portion();
            break;

        case UFS_INFO_SHOW_ALL:
            ufs_info_show_all();
            break;

        case UFS_INFO_SHOW_DEVICE_DESC:
            ufs_info_show_dev_desc();
            break;

        case UFS_INFO_SHOW_CONFIGURATION_DESC:
            ufs_info_show_conf_desc();
            break;

        case UFS_INFO_SHOW_UNIT_DESC:
            ufs_info_show_unit_desc();
            break;

        case UFS_INFO_SHOW_STRING_DESC:
            ufs_info_show_str_desc();
            break;

        case UFS_INFO_SHOW_GEOMETRY_DESC:
            ufs_info_show_geo_desc();
            break;

        case UFS_INFO_SHOW_HEALTH_DESC:
            ufs_info_show_heal_desc();
            break;

        default:
            UFS_PRINT("unknow cmd.\n");
            break;
    }
    return UFS_OK;
}

static void ufs_show_layer_1_5(void)
{
    int i = 0;
    UFS_PRINT("PHY Adapter Layer 1_5\n");
    UFS_PRINT("15000000: %08x\n", uic_cmd_read(DME_GET, 0x15000000));
    UFS_PRINT("15200000: %08x\n", uic_cmd_read(DME_GET, 0x15200000));
    UFS_PRINT("15400000: %08x\n", uic_cmd_read(DME_GET, 0x15400000));
    UFS_PRINT("15430000: %08x\n", uic_cmd_read(DME_GET, 0x15430000));
    for(i = 0x52; i <= 0x57; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
    for(i = 0x5a; i <= 0x61; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
    UFS_PRINT("15640000: %08x\n", uic_cmd_read(DME_GET, 0x15640000));
    for(i = 0x67; i <= 0x6a; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
    UFS_PRINT("15710000: %08x\n", uic_cmd_read(DME_GET, 0x15710000));
    for(i = 0x80; i <= 0x87; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
    for(i = 0x90; i <= 0x91; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
    for(i = 0xa0; i <= 0xab; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
    for(i = 0xb0; i <= 0xbb; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
    for(i = 0xc0; i <= 0xc2; i++) {
        UFS_PRINT("15%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x15000000 + i * 0x10000));
    }
}
static void ufs_show_layer_2(void)
{
    int i = 0;
    UFS_PRINT("Data Link Layer 2\n");
    for(i = 0x00; i <= 0x06; i++) {
        UFS_PRINT("20%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x20000000 + i * 0x10000));
    }
    for(i = 0x40; i <= 0x47; i++) {
        UFS_PRINT("20%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x20000000 + i * 0x10000));
    }
    for(i = 0x60; i <= 0x67; i++) {
        UFS_PRINT("20%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x20000000 + i * 0x10000));
    }
    UFS_PRINT("21000000: %08x\n", uic_cmd_read(DME_GET, 0x21000000));
}
static void ufs_show_layer_3(void)
{
    int i = 0;
    UFS_PRINT("Network Layer 3\n");
    for(i = 0x00; i <= 0x01; i++) {
        UFS_PRINT("30%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x30000000 + i * 0x10000));
    }
    for(i = 0x20; i <= 0x21; i++) {
        UFS_PRINT("30%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x30000000 + i * 0x10000));
    }
}
static void ufs_show_layer_4(void)
{
    int i = 0;
    UFS_PRINT("Transport Layer 4\n");
    for(i = 0x00; i <= 0x01; i++) {
        UFS_PRINT("40%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x40000000 + i * 0x10000));
    }
    for(i = 0x20; i <= 0x2b; i++) {
        UFS_PRINT("40%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x40000000 + i * 0x10000));
    }
    for(i = 0x60; i <= 0x61; i++) {
        UFS_PRINT("40%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x40000000 + i * 0x10000));
    }
    for(i = 0x80; i <= 0x86; i++) {
        UFS_PRINT("40%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x40000000 + i * 0x10000));
    }
    for(i = 0xa1; i <= 0xab; i++) {
        UFS_PRINT("40%02x0000: %08x\n", i, uic_cmd_read(DME_GET, 0x40000000 + i * 0x10000));
    }
}

static void ufs_readreg(uint32_t arg1)
{
    UFS_PRINT("%08x: %08x\n", arg1, uic_cmd_read(DME_GET, arg1));
}

static void ufs_writereg(uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    send_uic_command(DME_SET, arg1, arg2, arg3);
}

void ufs_readreg_all(void)
{
    ufs_show_layer_1_5();
    ufs_show_layer_2();
    ufs_show_layer_3();
    ufs_show_layer_4();
}
void ufs_reg_param(int argc, char *const argv[])
{
    u32 cmd = simple_strtoul(argv[1], NULL, 16);
    u32 attr_sel = simple_strtoul(argv[2], NULL, 16);
    u32 attr_set = 0;
    u32 mib_val = 0;
    u32 ret = 0;
    switch(cmd) {
        case DME_GET:
        case DME_PEER_GET:
            if( 3 != argc ) {
                UFS_PRINT("unknowm cmd!!!Usage: ufs reg cmd(1...DME_GET) attr_sel\n");
                return;
            }
            ufs_readreg(attr_sel);
            break;

        case DME_SET:
        case DME_PEER_SET:
            if( 5 != argc ) {
                UFS_PRINT("unknowm cmd!!!Usage: ufs reg cmd(2...DME_SET) attr_sel attr_set mib_val\n");
                return;
            }
            attr_set = simple_strtoul(argv[3], NULL, 16);
            mib_val = simple_strtoul(argv[4], NULL, 16);
            ufs_writereg(attr_sel, attr_set, mib_val);
            break;

        case DME_HIBERNATE_ENTER:
            if( 2 != argc ) {
                UFS_PRINT("unknowm cmd!!!Usage: ufs reg cmd(17...DME_HIBERNATE_ENTER)\n");
                return;
            }
            ret = ufs_hibernate_enter(1);
            if(ret) {
                UFS_PRINT("ufs_hibernate_enter error %d\n", ret);
                return;
            }
            break;
        case DME_HIBERNATE_EXIT:
            if( 2 != argc ) {
                UFS_PRINT("unknowm cmd!!!Usage: ufs reg cmd(18...DME_HIBERNATE_EXIT)\n");
                return;
            }
            ret = ufs_hibernate_exit(1);
            if(ret) {
                UFS_PRINT("ufs_hibernate_exit error %d\n", ret);
                return;
            }
            break;
        default:
            UFS_PRINT("unknown cmd!!!!!\n");
    }
}


static bool is_boot_from_ufs(void)
{
    unsigned int reg = readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);

    return (GET_SYS_BOOT_MODE(reg) == BOOT_FROM_UFS);
}

void ufshci_dump(void)
{
    UFS_PRINT("===== UFSHCI REGISTER DUMP ======\n");
    UFS_PRINT("CAP:        0x%08x||",
              dwc_ufs_read_reg(UFS_CAP_OFF));
    UFS_PRINT("VER:        0x%08x\n",
              dwc_ufs_read_reg(UFS_VER_OFF));
    UFS_PRINT("HCPID:      0x%08x||",
              dwc_ufs_read_reg(UFS_HCPID_OFF));
    UFS_PRINT("HCMID:      0x%08x\n",
              dwc_ufs_read_reg(UFS_HCMID_OFF));
    UFS_PRINT("AHIT:       0x%08x||",
              dwc_ufs_read_reg(UFS_AHIT_OFF));
    UFS_PRINT("IS:         0x%08x\n",
              dwc_ufs_read_reg(UFS_IS_OFF));
    UFS_PRINT("IE:         0x%08x||",
              dwc_ufs_read_reg(UFS_IE_OFF));
    UFS_PRINT("HCS:        0x%08x\n",
              dwc_ufs_read_reg(UFS_HCS_OFF));
    UFS_PRINT("HCE:        0x%08x||",
              dwc_ufs_read_reg(UFS_HCE_OFF));
    UFS_PRINT("UECPA:      0x%08x\n",
              dwc_ufs_read_reg(UFS_UECPA_OFF));
    UFS_PRINT("UECDL:      0x%08x||",
              dwc_ufs_read_reg(UFS_UECDL_OFF));
    UFS_PRINT("UECN:       0x%08x\n",
              dwc_ufs_read_reg(UFS_UECN_OFF));
    UFS_PRINT("UECT:       0x%08x||",
              dwc_ufs_read_reg(UFS_UECT_OFF));
    UFS_PRINT("UECDME:     0x%08x\n",
              dwc_ufs_read_reg(UFS_UECDME_OFF));
    UFS_PRINT("UTRIACR:    0x%08x||",
              dwc_ufs_read_reg(UFS_UTRIACR_OFF));
    UFS_PRINT("UTRLBA:     0x%08x\n",
              dwc_ufs_read_reg(UFS_UTRLBA_OFF));
    UFS_PRINT("UTRLBAU:    0x%08x||",
              dwc_ufs_read_reg(UFS_UTRLBAU_OFF));
    UFS_PRINT("UTRLDBR:    0x%08x\n",
              dwc_ufs_read_reg(UFS_UTRLDBR_OFF));
    UFS_PRINT("UTRLCLR:    0x%08x||",
              dwc_ufs_read_reg(UFS_UTRLCLR_OFF));
    UFS_PRINT("UTRLRSR:    0x%08x\n",
              dwc_ufs_read_reg(UFS_UTRLRSR_OFF));
    UFS_PRINT("UTMRLBA:    0x%08x||",
              dwc_ufs_read_reg(UFS_UTMRLBA_OFF));
    UFS_PRINT("UTMRLBAU:   0x%08x\n",
              dwc_ufs_read_reg(UFS_UTMRLBAU_OFF));
    UFS_PRINT("UTMRLDBR:   0x%08x||",
              dwc_ufs_read_reg(UFS_UTMRLDBR_OFF));
    UFS_PRINT("UTMRLCLR:   0x%08x\n",
              dwc_ufs_read_reg(UFS_UTMRLCLR_OFF));
    UFS_PRINT("UTMRLRSR:   0x%08x||",
              dwc_ufs_read_reg(UFS_UTMRLRSR_OFF));
    UFS_PRINT("UICCMD:     0x%08x\n",
              dwc_ufs_read_reg(UFS_UICCMD_OFF));
    UFS_PRINT("UICCMDARG1: 0x%08x||",
              dwc_ufs_read_reg(UFS_UICCMDARG1_OFF));
    UFS_PRINT("UICCMDARG2: 0x%08x\n",
              dwc_ufs_read_reg(UFS_UICCMDARG2_OFF));
    UFS_PRINT("UICCMDARG3: 0x%08x||",
              dwc_ufs_read_reg(UFS_UICCMDARG3_OFF));
    UFS_PRINT("BUSTHRTL:   0x%08x\n",
              dwc_ufs_read_reg(UFS_BUSTHRTL_OFF));
    UFS_PRINT("OOCPR:      0x%08x||",
              dwc_ufs_read_reg(UFS_OOCPR_OFF));
    UFS_PRINT("FEIE:       0x%08x\n",
              dwc_ufs_read_reg(UFS_FEIE_OFF));
    UFS_PRINT("CDACFG:     0x%08x||",
              dwc_ufs_read_reg(UFS_CDACFG_OFF));
    UFS_PRINT("CDATX1:     0x%08x\n",
              dwc_ufs_read_reg(UFS_CDATX1_OFF));
    UFS_PRINT("CDATX2:     0x%08x||",
              dwc_ufs_read_reg(UFS_CDATX2_OFF));
    UFS_PRINT("CDARX1:     0x%08x\n",
              dwc_ufs_read_reg(UFS_CDARX1_OFF));
    UFS_PRINT("CDARX2:     0x%08x||",
              dwc_ufs_read_reg(UFS_CDARX2_OFF));
    UFS_PRINT("CDASTA:     0x%08x\n",
              dwc_ufs_read_reg(UFS_CDASTA_OFF));
    UFS_PRINT("LBMCFG:     0x%08x||",
              dwc_ufs_read_reg(UFS_LBMCFG_OFF));
    UFS_PRINT("LBMSTA:     0x%08x\n",
              dwc_ufs_read_reg(UFS_LBMSTA_OFF));
    UFS_PRINT("DBG:        0x%08x||",
              dwc_ufs_read_reg(UFS_DBG_OFF));
    UFS_PRINT("HCLKDIV:    0x%08x\n",
              dwc_ufs_read_reg(UFS_HCLKDIV_OFF));
    UFS_PRINT("============================\n");
}

void ufs_dme_reg_dump(void)
{
    UFS_PRINT("DME_ErrorPHYInd	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0600000));
    UFS_PRINT("DME_ErrorPAInd	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0610000));
    UFS_PRINT("DME_ErrorDInd	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0620000));
    UFS_PRINT("DME_ErrorNInd	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0630000));
    UFS_PRINT("DME_ErrorTInd	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0640000));
    UFS_PRINT("PA_TXPWRSTATE	0x%x\n",
              uic_cmd_read(DME_GET, 0x15670000));
    UFS_PRINT("PA_RXPWRSTATE	0x%x\n",
              uic_cmd_read(DME_GET, 0x15820000));
    UFS_PRINT("DME_30	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0300000));
    UFS_PRINT("DME_31	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0310000));
    UFS_PRINT("DME_32	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0320000));
    UFS_PRINT("DME_HibernateExitInd	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0330000));
    UFS_PRINT("VS_L2Status		0x%x\n",
              uic_cmd_read(DME_GET, 0xd0820000));
    UFS_PRINT("VS_PowerState	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0830000));
    UFS_PRINT("VS_DebugLinkStartUp  0x%x\n",
              uic_cmd_read(DME_GET, 0xd0950000));
    UFS_PRINT("VS_DebugPwrChg	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0960000));
    UFS_PRINT("VS_DebugStates	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0970000));
    UFS_PRINT("VS_DebugCounter0	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0980000));
    UFS_PRINT("VS_DebugCounter1	0x%x\n",
              uic_cmd_read(DME_GET, 0xd0990000));
    UFS_PRINT("PA_PACPFrameCount	0x%x\n",
              uic_cmd_read(DME_GET, 0x15c00000));
    UFS_PRINT("PA_PACPErrorCount	0x%x\n",
              uic_cmd_read(DME_GET, 0x15c10000));
    UFS_PRINT("DL_ReInitCount	0x%x\n",
              uic_cmd_read(DME_GET, 0x21000000));
    UFS_PRINT("DL_TC0RxInitCreditVal 0x%x\n",
              uic_cmd_read(DME_GET, 0x20020000));
    UFS_PRINT("============================================\n");
}

void ufs_reg_read_clean(void)
{
    uic_cmd_read(DME_GET, 0xd0600000); /* DME_ErrorPHYInd */
    uic_cmd_read(DME_GET, 0xd0610000); /* DME_ErrorPAInd */
    uic_cmd_read(DME_GET, 0xd0620000); /* DME_ErrorDInd */
    uic_cmd_read(DME_GET, 0xd0630000); /* DME_ErrorNInd */
    uic_cmd_read(DME_GET, 0xd0640000); /* DME_ErrorTInd */
    uic_cmd_read(DME_GET, 0xd0310000); /* DME_HibernateEnterInd */
    uic_cmd_read(DME_GET, 0xd0330000); /* DME_HibernateExitInd */
#if 0
    uic_cmd_read(DME_GET, 0xd0820000); /* VS_L2Status */
    uic_cmd_read(DME_GET, 0xd0830000); /* VS_PowerState */
    uic_cmd_read(DME_GET, 0xd0950000); /* VS_DebugLinkStartup */
    uic_cmd_read(DME_GET, 0xd0960000); /* VS_DebugPwrChg */
    uic_cmd_read(DME_GET, 0xd0970000); /* VS_DebugStates */
    uic_cmd_read(DME_GET, 0xd0980000); /* VS_DebugCounter0 */
    uic_cmd_read(DME_GET, 0xd0990000); /* VS_DebugCounter0 */
    uic_cmd_read(DME_GET, 0x15c00000); /* PA_PACPFrameCount */
    uic_cmd_read(DME_GET, 0x15c10000); /* PA_PACPErrorCount */
    uic_cmd_read(DME_GET, 0x21000000); /* DL_ReInitCount */
    uic_cmd_read(DME_GET, 0x20020000); /* DL_TC0RxInitCreditVal */
#endif

    dwc_ufs_read_reg(UFS_IS_OFF);
    dwc_ufs_read_reg(UFS_IE_OFF);
    dwc_ufs_read_reg(UFS_HCS_OFF);
    dwc_ufs_read_reg(UFS_HCE_OFF);
    dwc_ufs_read_reg(UFS_UECPA_OFF);
    dwc_ufs_read_reg(UFS_UECDL_OFF);
    dwc_ufs_read_reg(UFS_UECN_OFF);
    dwc_ufs_read_reg(UFS_UECT_OFF);
}

void ufs_phy_reg_dump(void)
{
    int index = find_device_index();

    UFS_PRINT("0x15520000 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x15520000));
    UFS_PRINT("0x15540000 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x15540000));
    UFS_PRINT("0x15560000 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x15560000));

    /*RX LS terminate Enable*/
    UFS_PRINT("RX LS terminate Enable 0x%x\n",
              uic_cmd_read(DME_GET, 0x00A50004));
    /*RX HS terminate Enable*/
    UFS_PRINT("RX HS terminate Enable 0x%x\n",
              uic_cmd_read(DME_GET, 0x00A60004));

    /* RX_HS_DATA_VALID_TIMER_VAL0 */
    UFS_PRINT("RX_HS_DATA_VALID_TIMER_VAL0 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00E90004));
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("RX_HS_DATA_VALID_TIMER_VAL0 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00E90005));
    UFS_PRINT("TX_HS_SYNC_LENGTH 0x28 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00280000));/* TX_HIBERNATE_CONTROL */

    UFS_PRINT("RX_DEBUG_GROUP_SIGNAL lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00ED0004));/* DEBUG_GROUP_SIGNAL*/
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("RX_DEBUG_GROUP_SIGNAL lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00ED0005));

    UFS_PRINT("TX_HS_SYNC_LENGTH 0x28 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00280000));/* TX_HIBERNATE_CONTROL */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_HS_SYNC_LENGTH 0x28 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00280001));

    UFS_PRINT("TX_HS_PREPARE_LENGTH 0x29 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00290000));/* TX_HIBERNATE_CONTROL */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_HS_PREPARE_LENGTH 0x29 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00290001));
    UFS_PRINT("TX_LS_PREPARE_LENGTH 0x2A lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x002a0000));/* TX_HIBERNATE_CONTROL */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_LS_PREPARE_LENGTH 0x2A lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x002a0001));
#if 0
    UFS_PRINT("TX_HIBERNATE_CONTROL 0x2B lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x802b0000));/* TX_HIBERNATE_CONTROL */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_HIBERNATE_CONTROL 0x2B lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x802b0001));
    UFS_PRINT("RX_ENTER_HIBERNATE 0xA7 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00A70004));/* RX_ENTER_HIBERNATE */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("RX_ENTER_HIBERNATE 0xA7 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00A70005));
#endif

    UFS_PRINT("RX_SQ_VREF 0xF1 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00f10004));/* RX_SQ_VREF */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("RX_SQ_VREF 0xF1 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00f10005));

    UFS_PRINT("TX_FSM_STATE 0x41 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00410000));/* TX_FSM_STATE */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_FSM_STATE 0x41 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00410001));

    UFS_PRINT("RX_FSM_STATE 0xC1 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00C10004));/* RX_FSM_STATE */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("RX_FSM_STATE 0xC1 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00C10005));

    UFS_PRINT("RG_PLL_TXLS_EN 0xC8 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00C80000)); /* RG_PLL_TXLS_EN */
    UFS_PRINT("RX_DA_SQUELCH_EN 0xC8 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00C80004));/* RX_DA_SQUELCH_EN */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("RX_DA_SQUELCH_EN 0xC8 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00C80005));

    UFS_PRINT("RX_EXTERNAL_H8_EXIT_EN 0xC3 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00C30004));/* RX_EXTERNAL_H8_EXIT_EN */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("RX_EXTERNAL_H8_EXIT_EN 0xC3 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00C30005));

    UFS_PRINT("RG_PLL_EN 0xCC lane is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00CC0000));/* RG_PLL_EN */
#if 0 /* not necessary */
    UFS_PRINT("TX_AFE_CONFIG I 0x7A lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x007A0000));/* TX_AFE_CONFIG I */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_AFE_CONFIG I 0x7A lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x007A0001));
    UFS_PRINT("TX_AFE_CONFIG II 0x7B lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x007B0000));/* TX_AFE_CONFIG II */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_AFE_CONFIG II 0x7B lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x007B0001));
    UFS_PRINT("TX_AFE_CONFIG III 0x7C lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x007C0000));/* TX_AFE_CONFIG III */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_AFE_CONFIG III 0x7C lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x007C0001));
    UFS_PRINT("TX_AFE_CONFIG IV 0x7D lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x007D0000));/* TX_AFE_CONFIG IV */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_AFE_CONFIG IV 0x7D lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x007D0001));
    UFS_PRINT("TX_AFE_CONFIG V 0x7E lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x007E0000));/* TX_AFE_CONFIG V */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_AFE_CONFIG V 0x7E lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x007E0001));
    UFS_PRINT("TX_HS_EQUALIZER_SETTING 0x37 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00370000));/* TX_HS_EQUALIZER_SETTING */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_HS_EQUALIZER_SETTING 0x37 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00370001));
    UFS_PRINT("TX_AMPLITUDE 0x25 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00250000));/* TX_AMPLITUDE */
    if (g_tx_lane_num[index] == 2)
        UFS_PRINT("TX_AMPLITUDE 0x25 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00250001));
#endif
    UFS_PRINT("RX_MODE 0xA1 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00a10004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_MODE 0xA1 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00a10005));

    UFS_PRINT("RX_HS_CLK_EN 0xCC lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00cc0004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_HS_CLK_EN 0xCC lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00cc0005));

    UFS_PRINT("RX_LS_CLK_EN 0xCD lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00cd0004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_LS_CLK_EN 0xCD lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00cd0005));

    UFS_PRINT("RX_RG_RX_MODE 0xCA lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00ca0004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_RG_RX_MODE 0xCA lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00ca0005));

    UFS_PRINT("RG_PLL_BIAS_EN 0xCA is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00ca0000));

    UFS_PRINT("RX_STALL 0xCF lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00cf0004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_STALL 0xCF lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00cf0005));

    UFS_PRINT("RX_SLEEP 0xD0 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00d00004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_SLEEP 0xD0 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00d00005));

    UFS_PRINT("RX_ERR_STATUS 0xC4 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00c40004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_ERR_STATUS 0xC4 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00C40005));

    UFS_PRINT("RX_SYM_ERR_COUNTER 0xC5 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00c50004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_SYM_ERR_COUNTER 0xC5 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00C50005));

    UFS_PRINT("RX_HSGEAR 0xA3 lane0 is 0x%x\n",
              uic_cmd_read(DME_GET, 0x00a30004));
    if (g_rx_lane_num[index] == 2)
        UFS_PRINT("RX_HSGEAR 0xA3 lane1 is 0x%x\n",
                  uic_cmd_read(DME_GET, 0x00a30005));
}

void ufs_reg_dump(void)
{
    ufshci_dump();
    ufs_phy_reg_dump();
    ufs_dme_reg_dump();
}

static inline int find_first_zero_bit_(unsigned long *area, u8 bits)
{
    unsigned long *pValue = area;
    int i;

    for (i = 0; i < bits; i++) {
        if ((*pValue & BIT(i)) == 0) {
            return i;
        }
    }
    return UFS_ERROR;
}

uint8_t dwc_ufshcd_get_xfer_req_free_slot(struct dwc_ufs_hba *hba)
{
    int  free_slot;

    free_slot =  find_first_zero_bit_(
                     &hba->outstanding_xfer_reqs, hba->nutrs);
    if (free_slot == UFS_ERROR) {
        UFS_PRINT("xfer free_slot got fail %d, "
                  "there is no free slot!\n", free_slot);
        return BAD_SLOT;
    }
    return (uint8_t)free_slot;
}

static uint32_t uic_cmd_read(uint32_t command, uint32_t arg1)
{
    int retry;
    uint32_t reg;

    FUNC_ENTER();

    retry = 100;
    while (--retry) {
        if (dwc_ufs_read_reg(UFS_HCS_OFF) & UFS_HCS_UCRDY_BIT) {
            break;
        }
        ufs_waitms(1);
    }
    if (retry <= 0) {
        UFS_PRINT("%s: wait HCS.UCRDY timeout\n", __func__);
        ufshci_dump();
    }

    dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
    dwc_ufs_write_reg(UFS_UICCMDARG1_OFF, arg1);
    dwc_ufs_write_reg(UFS_UICCMDARG2_OFF, 0x0);
    dwc_ufs_write_reg(UFS_UICCMDARG3_OFF, 0x0);

    dwc_ufs_write_reg(UFS_UICCMD_OFF, (command & 0xFF));

    retry = 100;
    while (--retry) {
        if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UCCS_BIT) {
            break;
        }
        ufs_waitms(1);
    }

    if (retry <= 0) {
        UFS_PRINT("%s: timeout, cmd:0x%x, arg1:0x%x\n",
                  __func__, command, arg1);
        ufshci_dump();
    }

    /* clear interrupt status */
    dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UCCS_BIT);

    if (dwc_ufs_read_reg(UFS_UICCMDARG2_OFF) & 0xFF) {
        UFS_PRINT("%s:response error\n", __func__);
        ufshci_dump();
    }

    if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT) {
        UFS_PRINT("%s:UFS_IS_UE_BIT error\n", __func__);
        /* clear interrupt status */
        /* the UE error cause by PA_Init or some other reason,
        * should clear it, or it will repeatly come out ! */
        dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UE_BIT);
        ufs_waitms(1);
        if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT)
            UFS_PRINT("%s:can not clear the UE_BIT\n",
                      __func__);

        /* sometimes can not clear the UE bit, so not to
        dump HCI register too frequently */
        /*ufshci_dump();*/
    }

    /* get uic result */
    reg = dwc_ufs_read_reg(UFS_UICCMDARG3_OFF);

    FUNC_EXIT();

    return reg;
}


/***************************************************************
 *
 * send_uic_command
 * Description: Programs the Command Argument and the Command
 *     Register to send the DME_LINK_STARTUP command
 *     to the device
 *
 ***************************************************************/
void send_uic_command(uint32_t command,
                      uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    int retry;
    int val;

    FUNC_ENTER();

    retry = 100;
    while (--retry) {
        if (dwc_ufs_read_reg(UFS_HCS_OFF) & UFS_HCS_UCRDY_BIT) {
            break;
        }
        ufs_waitms(1);
    }
    if (retry <= 0) {
        UFS_PRINT("%s: wait HCS.UCRDY timeout\n", __func__);
        ufshci_dump();
    }

    dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
    dwc_ufs_write_reg(UFS_UICCMDARG1_OFF, arg1);
    dwc_ufs_write_reg(UFS_UICCMDARG2_OFF, arg2);
    dwc_ufs_write_reg(UFS_UICCMDARG3_OFF, arg3);

    dwc_ufs_write_reg(UFS_UICCMD_OFF, (command & 0xFF));

    retry = 500;
    while (--retry) {
        if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UCCS_BIT) {
            break;
        }
        ufs_waitms(1);
    }

    if (retry <= 0)
        UFS_PRINT("%s: timeout cmd:0x%x, arg1:0x%x, "
                  "arg2:0x%x, arg3:0x%x\n", __func__,
                  command, arg1, arg2, arg3);

    /* clear interrupt status */
    dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UCCS_BIT);

    val  = dwc_ufs_read_reg(UFS_UICCMDARG2_OFF);
    if (val & 0xFF)
        UFS_PRINT("%s: response error, cmd:0x%x, arg1 is 0x%x, "
                  "response is 0x%x\n", __func__, command, arg1, val);

    if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT) {
        UFS_PRINT("%s: UFS_IS_UE_BIT error, cmd:0x%x, arg1 is 0x%x\n",
                  __func__, command, arg1);
        /* the UE error cause by PA_Init or some other reason,
        * should clear it, or it will repeatly come out ! */
        dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UE_BIT);
        ufs_waitms(1);
        if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT)
            UFS_PRINT("%s:can not clear the UE_BIT\n",
                      __func__);

        /* sometimes can not clear the UE bit, so not to dump
        HCI register too frequently */
        /*ufshci_dump();*/
    }
    FUNC_EXIT();
}


/***************************************************************
 *
 * setup_snps_mphy_tc
 * Description: Programs the Unipro and Synopsys Mphy for
 *
 ***************************************************************/
void setup_snps_mphy_tc(void)
{
    uint32_t retry = 10;

    /* Read the DME_Resest (0xD010) attribute. It must return 0
    indicating that the reset sequence is completed. */
    do {
        if (uic_cmd_read(0x01, 0xD0100000) == 1) {
            break;
        }
        ufs_waitms(1);
    } while (retry--);
#ifdef COMBO_PHY_V100
    /*lane1 TX_LCC_ENABLE*/
    send_uic_command(DME_SET, 0x002c0001, 0x0, 0x0);
    /*lane0 TX_LCC_ENABLE*/
    send_uic_command(DME_SET, 0x002c0000, 0x0, 0x0);
#endif

    /* DME layer enable ---zhaozhiliang, to delete? */
    send_uic_command(DME_SET, 0xd0000000, 0x0, 0x01);
}

int ufs_hc_enable(void)
{
    int retry = 3;
    int i;

    do {
        dwc_ufs_write_reg(UFS_HCE_OFF, UFS_HCE_RESET_BIT);
        i = 0;
        for (;;) {
            if (dwc_ufs_read_reg(UFS_HCE_OFF) == 1)

                //debug
                PRINT_ERROR("HCE = 0x%x\n",
                            dwc_ufs_read_reg(UFS_HCE_OFF));
            //debug

            return UFS_SUCCESS;

            ufs_waitms(1);

            if (i++ > 2) {
                UFS_PRINT("wait HCE time out\n");
                UFS_PRINT("HCE = 0x%x\n",
                          dwc_ufs_read_reg(UFS_HCE_OFF));
                break;
            }
        }
    } while (--retry > 0);

    return -1;
}

static void ufs_clk_init(void)
{
    u32 reg;

    reg = readl(CRG_REG_BASE + PERI_CRG96);
    reg |= BIT_UFS_CLK_EN;
    writel(reg, CRG_REG_BASE + PERI_CRG96);

    reg = readl(CRG_REG_BASE + PERI_CRG96);
    reg |= BIT_UFS_SRST_REQ;
    writel(reg, CRG_REG_BASE + PERI_CRG96);

    udelay(1);

    reg = readl(CRG_REG_BASE + PERI_CRG96);
    reg &= ~BIT_UFS_SRST_REQ;
    writel(reg, CRG_REG_BASE + PERI_CRG96);

    udelay(1);

    reg = readl(CRG_REG_BASE + PERI_CRG96);
    reg |= BIT_UFS_AXI_SRST_REQ;
    writel(reg, CRG_REG_BASE + PERI_CRG96);

    udelay(1);

    reg = readl(CRG_REG_BASE + PERI_CRG96);
    reg &= ~BIT_UFS_AXI_SRST_REQ;
    writel(reg, CRG_REG_BASE + PERI_CRG96);

#ifdef UFS_FPGA
    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    reg |= UFS_SRST_REQ;
    writel(reg, REG_BASE_FPGA2_APB_IF_ADDRESS);
    //debug
    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    UFS_PRINT("SYS REG 1111111 = 0x%x\n", reg);
    //debug

    ufs_waitms(1);

    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    reg &= ~UFS_SRST_REQ;
    writel(reg, REG_BASE_FPGA2_APB_IF_ADDRESS);
    //debug
    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    UFS_PRINT("SYS REG 2222222= 0x%x\n", reg);
    //debug

    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    reg &= ~UFS_RST;
    writel(reg, REG_BASE_FPGA2_APB_IF_ADDRESS);
    //debug
    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    UFS_PRINT("SYS REG 3333333= 0x%x\n", reg);
    //debug
    ufs_waitms(1);

    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    reg |= UFS_RST;
    writel(reg, REG_BASE_FPGA2_APB_IF_ADDRESS);
    //debug
    reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
    UFS_PRINT("SYS REG 4444444= 0x%x\n", reg);
    //debug
    /*
        ufs_waitms(1);

        reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
        reg &= ~UFS_RST;
        writel(reg, REG_BASE_FPGA2_APB_IF_ADDRESS);
        //debug
        reg = readl(REG_BASE_FPGA2_APB_IF_ADDRESS);
            UFS_PRINT("SYS REG 4444444= 0x%x\n",reg);
        //debug
    */

#endif
}

void ufs_hardware_init(void)
{
    u32 reg;

    reg = readl(MISC_REG_BASE + MISC_CTRL17);
    reg |= BIT_UFS_ENABLE;
    writel(reg, MISC_REG_BASE + MISC_CTRL17);

    reg = readl(MISC_REG_BASE + MISC_CTRL17);
    reg &= ~BIT_DA_UFS_REFCLK_OEN;
    reg &= ~MASK_DA_UFS_REFCLK_DS;
    reg |= (BIT_DA_UFS_REFCLK_DS0 |
            BIT_DA_UFS_REFCLK_DS1 |
            BIT_DA_UFS_REFCLK_SL);
    writel(reg, MISC_REG_BASE + MISC_CTRL17);

    reg = readl(MISC_REG_BASE + MISC_CTRL17);
    reg &= ~BIT_DA_UFS_RESET_OEN;
    reg &= ~MASK_DA_UFS_RESET_DS;
    reg |= BIT_DA_UFS_RESET_SL;
    writel(reg, MISC_REG_BASE + MISC_CTRL17);

    reg = readl(MISC_REG_BASE + MISC_CTRL17);
    reg &= ~BIT_UFS_PAD_RESET;
    writel(reg, MISC_REG_BASE + MISC_CTRL17);

    udelay(10);

    reg = readl(MISC_REG_BASE + MISC_CTRL17);
    reg |= BIT_UFS_PAD_RESET;
    writel(reg, MISC_REG_BASE + MISC_CTRL17);
}

void ufs_hc_init(void)
{
    u32 reg;

    /* get the 1us tick clock, the HCLK is 266Mhz? */
#ifdef UFS_FPGA
    dwc_ufs_write_reg(UFS_HCLKDIV_OFF, UFS_HCLKDIV_FPGA_VALUE);
#else
    dwc_ufs_write_reg(UFS_HCLKDIV_OFF, UFS_HCLKDIV_NORMAL_VALUE);
#endif
#if defined(COMBO_PHY_V120)
    /*Rx SKP_DET_SEL, lane0 */
    send_uic_command(DME_SET, ATTR_MRX0(SKP_DET_SEL),
                     0x0, SKP_DET_SEL_EN);
    /*Rx SKP_DET_SEL, lane1 */
    send_uic_command(DME_SET, ATTR_MRX1(SKP_DET_SEL),
                     0x0, SKP_DET_SEL_EN);

    /*VCO_AUTO_CHG */

    send_uic_command(DME_SET, ATTR_MCB(VCO_AUTO_CHG),
                     0x0, (VCO_AUTO_CHG_EN | VCO_FORCE_ON_EN));

    /*RX_SQ_VREF, lane0 */
    send_uic_command(DME_SET, ATTR_MRX0(RX_SQ_VREF),
                     0x0, RX_SQ_VREF_175mv);
    /*RX_SQ_VREF, lane1 */
    send_uic_command(DME_SET, ATTR_MRX1(RX_SQ_VREF),
                     0x0, RX_SQ_VREF_175mv);

    /*Dif_N debouse*/
    send_uic_command(DME_SET, ATTR_MRX0(0xeb), 0x0, 0x64);
    /*Dif_N debouse*/
    send_uic_command(DME_SET, ATTR_MRX1(0xeb), 0x0, 0x64);

    /*dvalid timer*/
    send_uic_command(DME_SET, ATTR_MRX0(0x0e), 0x0, 0xF0);
    /*dvalid timer*/
    send_uic_command(DME_SET, ATTR_MRX1(0x0e), 0x0, 0xF0);
    /*RX LINE RESET DETECT TIME*/
    //send_uic_command(DME_SET, ATTR_MRX0(0xef), 0x0, 0xfa);
    /*RX LINE RESET DETECT TIME*/
    //send_uic_command(DME_SET, ATTR_MRX1(0xef), 0x0, 0xfa);

    /*AD_DIF_P_LS_TIMEOUT_VAL, lane0 */
    send_uic_command(DME_SET, ATTR_MRX0(AD_DIF_P_LS_TIMEOUT_VAL),
                     0x0, PWM_PREPARE_TO);
    /*AD_DIF_P_LS_TIMEOUT_VAL, lane1 */
    send_uic_command(DME_SET, ATTR_MRX1(AD_DIF_P_LS_TIMEOUT_VAL),
                     0x0, PWM_PREPARE_TO);

    send_uic_command(0x00000002, 0x00F40004, 0x00000000, 0x1); /*RX_EQ_SEL_R*/
    send_uic_command(0x00000002, 0x00F40005, 0x00000000, 0x1); /*RX_EQ_SEL_R*/

    send_uic_command(0x00000002, 0x00F20004, 0x00000000, 0x3);/*RX_EQ_SEL_C*/
    send_uic_command(0x00000002, 0x00F20005, 0x00000000, 0x3);/*RX_EQ_SEL_C*/

    send_uic_command(0x00000002, 0x00FB0004, 0x00000000, 0x3); /*RX_VSEL*/
    send_uic_command(0x00000002, 0x00FB0005, 0x00000000, 0x3); /*RX_VSEL*/

    send_uic_command(0x00000002, 0x00f60004, 0x00000000, 0x00000002);   /* RX_DLF Lane 0 */
    send_uic_command(0x00000002, 0x00f60005, 0x00000000, 0x00000002);   /* RX_DLF Lane 1 */

    send_uic_command(0x00000002, 0x000a0004, 0x00000000, 0x00000002);   /* RX H8_TIMEOUT_VAL, Lane 0 */
    send_uic_command(0x00000002, 0x000a0005, 0x00000000, 0x00000002);   /* RX H8_TIMEOUT_VAL, Lane 1 */

    /* in low temperature to solve the PLL's starting of oscillation */
    send_uic_command(0x00000002, 0x00d40000, 0x00000000, 0x00000031);   /* RG_PLL_DMY0 */
    send_uic_command(0x00000002, 0x00730000, 0x00000000, 0x00000004);   /* TX_PHY_CONFIG II */
    send_uic_command(0x00000002, 0x00730001, 0x00000000, 0x00000004);   /* TX_PHY_CONFIG II */
#else
    /* in low temperature to solve the PLL's starting of oscillation */
    /* RG_PLL_CP */
    send_uic_command(DME_SET, 0x00c10000, 0x0, 0x01);
    /* RG_PLL_DMY0 */
    send_uic_command(DME_SET, 0x00d40000, 0x0, 0x51);
    /* rate A->B 's VCO stable time */
    /*send_uic_command(DME_SET, 0x00db0000, 0x0, 0x05);*/
#ifdef COMBO_PHY_V110
    /* H8's workaround */
    /*RX_SQ_VREF, lane0 */
    send_uic_command(DME_SET, 0x00f10004, 0x0, 0x07);
    /*RX_SQ_VREF, lane1 */
    send_uic_command(DME_SET, 0x00f10005, 0x0, 0x07);
#endif
#endif /*end of COMBO_PHY_V120*/
    /*RX enable, lane0 */
    send_uic_command(DME_SET, ATTR_MRX0(MRX_EN), 0x0, MRX_ENABLE);
    /*RX enable, lane1 */
    send_uic_command(DME_SET, ATTR_MRX1(MRX_EN), 0x0, MRX_ENABLE);

#if 1
    /* disable auto H8 */
    reg = dwc_ufs_read_reg(UFS_AHIT_OFF);
    reg = reg & (~UFS_AHIT_AH8ITV_MASK);
    dwc_ufs_write_reg(UFS_AHIT_OFF, reg);
#endif

    setup_snps_mphy_tc();

#if !defined(COMBO_PHY_V120)
    /*RX_MC_PRESENT */
    send_uic_command(DME_SET, 0x00c20004, 0x0, 0x01);
    /*RX_MC_PRESENT */
    send_uic_command(DME_SET, 0x00c20005, 0x0, 0x01);
#endif

    /* disable Vswing change */
    /* measure the power, can close it */
    send_uic_command(DME_SET, 0x00C70000, 0x0, 0x3);
    /* measure the power, can close it */
    send_uic_command(DME_SET, 0x00C80000, 0x0, 0x3);
#if !defined(COMBO_PHY_V120)
    send_uic_command(DME_SET, 0x007A0000, 0x0, 0x1c);
    send_uic_command(DME_SET, 0x007A0001, 0x0, 0x1c);
    send_uic_command(DME_SET, 0x007C0000, 0x0, 0xd4);
    send_uic_command(DME_SET, 0x007C0001, 0x0, 0xd4);
#endif
    /* no need to exitH8 before linkup anymore */
    /*exit TX_HIBERNATE_CONTROL */
    /*send_uic_command(DME_SET, 0x802b0000, 0x0, 0x0);*/
    /*exit TX_HIBERNATE_CONTROL */
    /*send_uic_command(DME_SET, 0x802b0001, 0x0, 0x0);*/
    /* ufs_waitms(20); */

#ifdef CLOSE_CLK_GATING
    /*RX_STALL*/
    send_uic_command(DME_SET, 0x00cf0004, 0x0, 0x02);
    /*RX_STALL*/
    send_uic_command(DME_SET, 0x00cf0005, 0x0, 0x02);
    /*RX_SLEEP*/
    send_uic_command(DME_SET, 0x00d00004, 0x0, 0x02);
    /*RX_SLEEP*/
    send_uic_command(DME_SET, 0x00d00005, 0x0, 0x02);

    /*RX_HS_CLK_EN*/
    send_uic_command(DME_SET, 0x00cc0004, 0x0, 0x03);
    /*RX_HS_CLK_EN*/
    send_uic_command(DME_SET, 0x00cc0005, 0x0, 0x03);
    /*RX_LS_CLK_EN*/
    send_uic_command(DME_SET, 0x00cd0004, 0x0, 0x03);
    /*RX_LS_CLK_EN*/
    send_uic_command(DME_SET, 0x00cd0005, 0x0, 0x03);
#endif

#if defined(COMBO_PHY_V120)
    /*RG_PLL_RXHS_EN*/
    send_uic_command(DME_SET, 0x00c50000, 0x0, 0x03);
    /*RG_PLL_RXLS_EN*/
    send_uic_command(DME_SET, 0x00c60000, 0x0, 0x03);
    send_uic_command(0x00000002, 0x00E90004, 0x00000000, 0x00000000); /*RX_HS_DATA_VALID_TIMER_VAL0*/
    send_uic_command(0x00000002, 0x00E90005, 0x00000000, 0x00000000); /*RX_HS_DATA_VALID_TIMER_VAL0*/
    send_uic_command(0x00000002, 0x00EA0004, 0x00000000, 0x00000010); /*RX_HS_DATA_VALID_TIMER_VAL1*/
    send_uic_command(0x00000002, 0x00EA0005, 0x00000000, 0x00000010); /*RX_HS_DATA_VALID_TIMER_VAL1*/
#else
    /*enhance the accuracy of squelch detection*/
    /*RX_H8_EXIT*/
    send_uic_command(DME_SET, 0x00ce0004, 0x0, 0x03);
    /*RX_H8_EXIT*/
    send_uic_command(DME_SET, 0x00ce0005, 0x0, 0x03);

    /* try to solve the OCS=5 */
    /*RX_HS_DATA_VALID_TIMER_VAL0*/
    send_uic_command(DME_SET, 0x00E90004, 0x0, 0x20);
    /*RX_HS_DATA_VALID_TIMER_VAL0*/
    send_uic_command(DME_SET, 0x00E90005, 0x0, 0x20);
    /*RX_HS_DATA_VALID_TIMER_VAL1*/
    send_uic_command(DME_SET, 0x00EA0004, 0x0, 0x01);
    /*RX_HS_DATA_VALID_TIMER_VAL1*/
    send_uic_command(DME_SET, 0x00EA0005, 0x0, 0x01);
#endif

    /* set the HS-prepare length and sync length to MAX value, try to solve
      the data check error problem, the device seems not receive the write
      cmd. */
    /* PA_TxHsG1SyncLength , can not set MPHY's register directly */
    send_uic_command(DME_SET, 0x15520000, 0x0, 0x4F);
    /* PA_TxHsG2SyncLength , can not set MPHY's register directly */
    send_uic_command(DME_SET, 0x15540000, 0x0, 0x4F);
    /* PA_TxHsG3SyncLength , can not set MPHY's register directly */
    send_uic_command(DME_SET, 0x15560000, 0x0, 0x4F);

#if defined(OCS_5_WORKAROUND)
    send_uic_command(DME_SET, 0x00FF0004, 0x0, 0x2);
    send_uic_command(DME_SET, 0x00FF0005, 0x0, 0x2);
#endif

#if defined(NOISE_PROOF)
    send_uic_command(DME_SET, 0x00F40004, 0x0, 0x2);
    send_uic_command(DME_SET, 0x00F40005, 0x0, 0x2);

    send_uic_command(DME_SET, 0x00F20004, 0x0, 0x2);
    send_uic_command(DME_SET, 0x00F20005, 0x0, 0x2);

    send_uic_command(DME_SET, 0x00FC0004, 0x0, 0x1F);
    send_uic_command(DME_SET, 0x00FC0005, 0x0, 0x1F);

    send_uic_command(DME_SET, 0x00FB0004, 0x0, 0x0);
    send_uic_command(DME_SET, 0x00FB0005, 0x0, 0x0);
#endif
    send_uic_command(DME_SET, 0x00ca0000, 0x0, 0x3); /* pll always on*/
    send_uic_command(DME_SET, 0xD0850000, 0x0, 0x1); /* update */

    /* to check if the unipro have to close the LCC */
    /* Unipro PA_Local_TX_LCC_Enable */
    send_uic_command(DME_SET, 0x155E0000, 0x0, 0x0);
    /* close Unipro VS_Mk2ExtnSupport */
    send_uic_command(DME_SET, 0xD0AB0000, 0x0, 0x0);

    if (uic_cmd_read(0x1, 0xD0AB0000) != 0) {
        /* Ensure close success */
        UFS_PRINT("Warring!!! close VS_Mk2ExtnSupport failed\n");
    }
}

int ufs_link_startup(void)
{
    int retry = 4;
    int i = 0;

    dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
    while (retry-- > 0) {

        dwc_ufs_write_reg(UFS_UICCMDARG1_OFF, 0);
        dwc_ufs_write_reg(UFS_UICCMDARG2_OFF, 0);
        dwc_ufs_write_reg(UFS_UICCMDARG3_OFF, 0);

        dwc_ufs_write_reg(UFS_UICCMD_OFF,
                          (UIC_LINK_STARTUP_CMD & 0xFF));

        i = 0;
        for (;;) {
            if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UCCS_BIT) {
                dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UCCS_BIT);
                break;
            }
            ufs_waitms(1);
            if (i++ > 200) {
                PRINT_ERROR("ufs link startup "
                            "wait UCCS timeout\n");
                break;
            }
        }

        if (dwc_ufs_read_reg(UFS_HCS_OFF) & UFS_HCS_DP_BIT) {
            if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_ULSS_BIT) {
                dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_ULSS_BIT);
            }

            dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UE_BIT);
            return UFS_SUCCESS;
        }

        PRINT_ERROR("ufs link startup check DP fail\n");
        if (retry <= 0) {
            PRINT_ERROR("ufs link startup FAIL\n");
            return UFS_LINK_STARTUP_FAIL;
        }
        i = 0;
        for (;;) {
            if (dwc_ufs_read_reg(UFS_IS_OFF) &
                    UFS_IS_ULSS_BIT) {
                break;
            }
            ufs_waitms(1);
            if (i++ > 50) {
                PRINT_ERROR("ufs link startup "
                            "wait ULSS timeout\n");
                break;
            }
        }
    }

    UFS_PRINT("ufs link startup fail\n");
    return UFS_LINK_STARTUP_FAIL;
}

void dwc_ufshcd_read_caps(struct dwc_ufs_hba *hba)
{
    hba->caps = dwc_ufs_read_reg(UFS_CAP_OFF);

    /* Update:
     * Number of UTP Task management Request Slots(NUTMRS)
     * Number of Pending RTTS Supported (NPRTTS)
     * Number of UTP Transfer Request Slots (NUTRS)
     * Auto Hibernate Support
     * 64 bit Addressing Support
     * Out Of Order Data Delivery Support
     * UIC DME TEST MODE support
     */
    hba->nutrs = 32;
    /*(UCHAR)(hba->caps & DWC_UFS_NUTRS_MASK) + 1;*/
    hba->nprtts = (UCHAR)
                  ((hba->caps & DWC_UFS_NUTRS_MASK) >> DWC_UFS_NPRTTS_SHIFT) + 1;
    hba->nutmrs = 2;
    /*(UCHAR)((hba->caps & DWC_UFS_NUTMRS_MASK) >> DWC_UFS_NUTMRS_SHIFT) + 1;*/
    hba->autoh8 = (UCHAR)
                  ((hba->caps & DWC_UFS_AUTOH8) >> DWC_UFS_AUTOH8_SHIFT);
    hba->as64 = (UCHAR)
                ((hba->caps & DWC_UFS_64AS) >> DWC_UFS_64AS_SHIFT);
    hba->oodds = (UCHAR)
                 ((hba->caps & DWC_UFS_OODDS) >> DWC_UFS_OODDS_SHIFT);
    hba->uicdmetms =
        (UCHAR)((hba->caps & DWC_UFS_UICDMETMS) >> DWC_UFS_UICDMETMS_SHIFT);
}

/**
 * dwc_ufshcd_alloc_interface_memory()
 * Allocate memory for Host controller interface.
 * Following are the memories allocation by this function.
 * - DMA'able memory for UTP transfer request descriptor list
 * - DMA'able memory for UTP task management request list
 * - DMA'able memory for command table
 *    - Command UPIU's
 *    - Response UPIU's
 *    - PRD tables
 * - Non-DMA'able memory for local reference blocks; House keeping
 * @hba: Pointer to private structure
 *
 * Returns 0 for success, non-zero in case of failure
 */
int dwc_ufshcd_alloc_interface_memory(struct dwc_ufs_hba *hba)
{
    size_t utrl_size, utmrl_size, ucdl_size, lrb_size, align_offset;
    uint64_t cur_pool = 0;
    /*
     * Allocate Dma'able memory for UTP Transfer Request List
     * UFS spec constraints: Base of List shoudl be aligned to 1024 byte
     * (1K boundary)
     */
    /* alloc a pc's memory pool here, to match the 128K's
    SRAM in the testchip side */
    hba->mem_pool = (uint64_t)malloc(SRAM_TOTAL_SIZE);
    if (hba->mem_pool == 0) {
        PRINT_WARNING("%s: Memory Allocation Failed\n",
                      __func__);
        return UFS_ERROR;
    }
    UFS_MEM("\n@@ ufs memory pool info @@\n");
    UFS_MEM("poll  start:%llx end:%llx sz:%#x\n", hba->mem_pool,
            SRAM_TOTAL_SIZE +  hba->mem_pool, SRAM_TOTAL_SIZE);
    cur_pool = hba->mem_pool;
    cur_pool = BYTES_ALIGN_1024(cur_pool);
    align_offset = (char *)cur_pool - (char *)hba->mem_pool;
    if (align_offset > SRAM_TOTAL_SIZE) {
        PRINT_WARNING("%s: UTRL Memory Allocation Failed\n",
                      __func__);
        goto err_utrl_alloc;
    }
    hba->utrl_base_addr = (struct dwc_ufs_utrd *)cur_pool;
    utrl_size = (sizeof(struct dwc_ufs_utrd) * hba->nutrs);
    memset((void *)hba->utrl_base_addr, 0, utrl_size);
    UFS_MEM("utrl  start:%llx end:%llx sz:%#x\n",
            cur_pool, cur_pool + utrl_size, utrl_size);
    /* Allocate Dma'able memory for UTP Task management Request list
     * UFS spec constraints: base of list should be aligned to 1024 byte
     * (1K boundary)
     */
    cur_pool += utrl_size;
    cur_pool = BYTES_ALIGN_1024(cur_pool);
    align_offset = (char *)cur_pool - (char *)hba->mem_pool;
    if (align_offset > SRAM_TOTAL_SIZE) {
        PRINT_WARNING("%s: UTMRL Memory Allocation Failed\n",
                      __func__);
        goto err_utmrl_alloc;
    }

    hba->utmrl_base_addr = (struct dwc_ufs_utmrd *)(cur_pool);
    utmrl_size = (sizeof(struct dwc_ufs_utmrd) * hba->nutmrs);
    memset((void *)hba->utmrl_base_addr, 0, utmrl_size);

    UFS_MEM("utmrl start:%llx end:%llx sz:%#x\n",
            cur_pool, cur_pool + utmrl_size, utmrl_size);

    /* Allocate Dma'able memory for UTP Command Descriptor structures (UCDs)
     * Every Command Descriptor block should be aligned to 128 bytes (6:0
     * being)
     * reserved
     */
    cur_pool += utmrl_size;
    cur_pool = BYTES_ALIGN_128(cur_pool);
    align_offset = (char *)cur_pool - (char *)hba->mem_pool;
    if (align_offset > SRAM_TOTAL_SIZE) {
        PRINT_WARNING("%s: UCD Memory Allocation Failed\n",
                      __func__);
        goto err_ucdl_alloc;
    }

    hba->ucdl_base_addr = (struct dwc_ufs_ucd *)((char *)cur_pool);
    ucdl_size = (sizeof(struct dwc_ufs_ucd) * hba->nutrs);
    memset((void *)hba->ucdl_base_addr, 0, ucdl_size);

    UFS_MEM("ucdl  start:%llx end:%llx sz:%#x\n",
            cur_pool, cur_pool + ucdl_size, ucdl_size);

    /* Allocate memory for local reference block */
    cur_pool += ucdl_size;
    align_offset = (char *)cur_pool - (char *)hba->mem_pool;
    if (align_offset > SRAM_TOTAL_SIZE) {
        PRINT_WARNING("%s: LRB Memory Allocation Failed\n",
                      __func__);
        goto err_lrb_alloc;
    }
    hba->lrb = (struct dwc_ufs_hcd_lrb *)((char *)cur_pool);
    lrb_size = (sizeof(struct dwc_ufs_hcd_lrb) * hba->nutrs);
    memset((void *)hba->lrb, 0, lrb_size);

    UFS_MEM("lrb   start:%llx end:%llx sz:%#x\n",
            cur_pool, cur_pool + lrb_size, lrb_size);

    /* the write_buf should be LOGICAL_BLK_SIZE bytes aligned*/
    hba->write_read_buf =
        (void *)((char *)memalign(LOGICAL_BLK_SIZE, LOGICAL_BLK_SIZE));
    if (hba->write_read_buf == NULL) {
        PRINT_WARNING("%s: Write Read Memory Allocation Failed\n",
                      __func__);
        goto err_rw_alloc;
    }
    UFS_MEM("wrbuf start:%llx end:%llx sz:%#x\n",
            hba->write_read_buf,
            hba->write_read_buf + LOGICAL_BLK_SIZE,
            LOGICAL_BLK_SIZE);

    return UFS_OK;

err_ucdl_alloc:
err_utrl_alloc:
err_utmrl_alloc:
err_lrb_alloc:
err_rw_alloc:
    /*no free in fastboot */
    /*dwc_ufshcd_free_interface_memory(hba); */
    if (hba->mem_pool) {
        free((void *)hba->mem_pool);
    }
    if (hba->write_read_buf) {
        free((void *)hba->write_read_buf);
    }
    hba->mem_pool = 0;
    hba->write_read_buf = NULL;
    return UFS_ERROR;
}

/**
 * dwc_ufshcd_configure_interface_memory()
 * This function configures interface memory
 * -  For every UTRD,
 *  - initializes the Command UPIU base address (Lo and High)
 *  - response upiu length and offset
 *  - prdt offset
 * - Some key fields are updated in respective lrbs
 *      - utrd addresses
 *      - command upiu addresses
 *      - response upiu addresses
 *      - prdt base address
 * @hba: Pointer to private structure
 *
 * Returns void
 */
void dwc_ufshcd_configure_interface_memory(const struct dwc_ufs_hba *hba)
{
    uint32_t i;
    struct dwc_ufs_utrd *utrl; /* Pointer to UTR List */
    struct dwc_ufs_ucd *ucdl;  /* Pointer to UCD List */
    uint64_t ucdl_dma_addr;
    uint64_t ucd_dma_addr;
    u32 response_upiu_length;
    u32 response_upiu_offset;
    u32 prdt_offset;
    u32 ucd_size;

    utrl = hba->utrl_base_addr;
    ucdl = hba->ucdl_base_addr;
    /* Response offset and prdt offset are common for all the
     * UTP Transfer Request
     */
    response_upiu_offset = (u32)offsetof(struct dwc_ufs_ucd, resp_upiu);
    response_upiu_length = DWC_UCD_ALIGN;
    /* response_upiu_length = sizeof(struct dwc_ufs_resp_upiu); */
    prdt_offset = (u32)offsetof(struct dwc_ufs_ucd, prdt);

    ucd_size = sizeof(struct dwc_ufs_ucd);
    ucdl_dma_addr =
        (uint64_t)hba->ucdl_base_addr; /* UCD list Base address */

    /* For as many UTP Transfer Requests in the list */
    for (i = 0; i < hba->nutrs; i++) {

        /* Configure UTRD with UCD base address */
        ucd_dma_addr = ucdl_dma_addr + (uint64_t)ucd_size * i;
        utrl[i].ucdba = (LOWER_32_BITS(ucd_dma_addr));
        utrl[i].ucdbau = (UPPER_32_BITS(ucd_dma_addr));

        /* Configure Response UPIU offset and length */
        /* These fields are in Dword format */
        utrl[i].resp_upiu_offset = to_littleendian16(
                                       (uint16_t)(response_upiu_offset >> 2));
        utrl[i].resp_upiu_length = to_littleendian16(
                                       (uint16_t)(response_upiu_length >> 2));
        /* Configure prdt length and offset */
        utrl[i].prdt_offset = to_littleendian16(
                                  (uint16_t)(prdt_offset >> 2));
        utrl[i].prdt_length = to_littleendian16(0);

        /* Update LRB */
        hba->lrb[i].utrd = (utrl + i);
        hba->lrb[i].cmd_upiu = (struct dwc_ufs_cmd_upiu *)(ucdl + i);
        hba->lrb[i].resp_upiu =
            (struct dwc_ufs_resp_upiu *)(ucdl[i].resp_upiu);
        hba->lrb[i].prdt = (struct dwc_ufs_prd *)(ucdl[i].prdt);
    }
}

/**
 * dwc_ufshcd_is_hba_active
 * Get UFS controller state
 * @hba: Private structure pointer
 *
 * Returns TRUE if controller is active, FALSE otherwise
 */
int dwc_ufshcd_is_hba_active(void)
{
    return (dwc_ufs_read_reg(UFS_HCE_OFF) & 0x1) ? UFS_OK : UFS_ERROR;
}


/**
 * dwc_ufshcd_initialize_hba_desc_pointers()
 * This function performs the initialization of DWC UFS HC descriptors
 * with memory base addresses
 * Before updating the descriptor addresses, it checks host controller is
 * enabled. If not returns error. If enabled, both transfer descriptor
 * pointers and tm descriptor pointers are programmed from the drivers
 * private structure
 * @hba: pointer to drivers private structure
 *
 * Returns 0 on success, non-zero value on failure
 */
int dwc_ufshcd_initialize_hba_desc_pointers(const struct dwc_ufs_hba *hba)
{
    UINT result = 0;

#if 1 /*to open*/
    /* If the Host Controller is not active, return error */
    if (dwc_ufshcd_is_hba_active()) {
        UFS_PRINT(" not active , error\n");
        return UFS_ERROR;
    }
#endif
    result = UPPER_32_BITS(0xe0000000);
    /* Configure UTRL and UTMRL base address registers */

    dwc_ufs_write_reg(UFS_UTRLBA_OFF,
                      LOWER_32_BITS((uint64_t)hba->utrl_base_addr));
    dwc_ufs_write_reg(UFS_UTRLBAU_OFF,
                      UPPER_32_BITS((uint64_t)hba->utrl_base_addr));

    dwc_ufs_write_reg(UFS_UTMRLBA_OFF,
                      LOWER_32_BITS((uint64_t)hba->utmrl_base_addr));
    dwc_ufs_write_reg(UFS_UTMRLBAU_OFF,
                      UPPER_32_BITS((uint64_t)hba->utmrl_base_addr));

    return result;
}


/***************************************************************
 *
 * create_cmd_upiu
 * Description: Fills the Command UPIU memory,
 *              updates prdt entries
 * free_slot:free slot in memory, 0~31 in UTRL, 0~7 in UTMRL
 *
 ***************************************************************/
static int create_cmd_upiu(uint32_t opcode,
                           enum dma_data_direction direction,
                           uint64_t buf_addr,
                           uint64_t rel_addr,
                           uint32_t size,
                           uint8_t free_slot)
{
    struct dwc_ufs_cmd_upiu *cmd_upiu_ptr;
    uint32_t data_direction;
    uint8_t upiu_flags;
    struct dwc_ufs_utrd *utrd;
    struct dwc_ufs_ucd *ucd;
    struct dwc_ufs_prd *prdt;
    uint32_t prdt_buf_size = PRDT_BUFFER_SIZE;
    uint64_t buf_addr_phy;
    uint64_t i;

    GET_LOCAL_DWC_HOST();

#ifdef CMD_UPIU_DEBUG
    uint8_t *ptr_b;
    uint32_t *ptr_dw;
    int num_prd;
#endif

    FUNC_ENTER();
    if (opcode == UFS_OP_READ_10 || opcode == UFS_OP_WRITE_10 ||
            opcode == UFS_OP_SYNCHRONIZE_CACHE_10 || opcode == UFS_OP_READ_6 ||
            opcode == UFS_OP_WRITE_6) {
        if (rel_addr % LOGICAL_BLK_SIZE) {
            UFS_PRINT("!!!!!access ufs addr is not round with ufs "
                      "block size, addr is 0x%llx, block size is 0x%x\n",
                      rel_addr, LOGICAL_BLK_SIZE);
            return UFS_SOFTWARE_ERROR;
        }
        if (size % LOGICAL_BLK_SIZE) {
            UFS_PRINT("!!!!!access ufs size is not round with ufs "
                      "block size, size is 0x%x, block size is 0x%x\n",
                      size, LOGICAL_BLK_SIZE);
            return UFS_SOFTWARE_ERROR;
        }
    } else {
        if (size % 0x4) {
            UFS_PRINT("!!!!access ufs size is not round "
                      "with D-Words, size is 0x%x\n", size);
            return UFS_SOFTWARE_ERROR;
        }
    }

    if (LOWER_32_BITS(buf_addr) % 0x4) {
        UFS_PRINT("!!!!buffer addr is not round with D-Words, "
                  "buf_addr is 0x%llx\n", buf_addr);
        return UFS_SOFTWARE_ERROR;
    }

    ucd = dwc_host->ucdl_base_addr;
    /* Get the ucd of the free slot */
    ucd += free_slot;

    cmd_upiu_ptr = (struct dwc_ufs_cmd_upiu *)ucd->cmd_upiu;
    prdt = dwc_host->lrb[free_slot].prdt;

    /* Get the base address of Xfer Req list base address */
    utrd = dwc_host->utrl_base_addr;

    /* Get the xfer descriptor of the free slot */
    utrd += free_slot;

    if (direction == DMA_FROM_DEVICE) {
        data_direction = UTP_DEVICE_TO_HOST;
        upiu_flags = UPIU_CMD_FLAGS_READ;
    } else if (direction == DMA_TO_DEVICE) {
        data_direction = UTP_HOST_TO_DEVICE;
        upiu_flags = UPIU_CMD_FLAGS_WRITE;
    } else {
        data_direction = UTP_NO_DATA_TRANSFER;
        upiu_flags = UPIU_CMD_FLAGS_NONE;
    }

    /* Update cmd_type, flags and response upiu length for transfer requests
     */
    utrd->ct_and_flags =
        (uint8_t)(data_direction | UTP_UFS_STORAGE_COMMAND);
    utrd->resp_upiu_length =  to_littleendian16((uint16_t)
                              (sizeof(struct dwc_ufs_resp_upiu) >> 2));
    utrd->ocs = 0xf;

    cmd_upiu_ptr->trans_type = 0x01;
    /*****************************
    *** Task Attribute Bit 1 Bit 0
    *** Simple           0     0
    *** Ordered          0     1
    *** Head of Queue    1     0
    ******************************/
    cmd_upiu_ptr->flags = upiu_flags;
#if 0
    if (ufs_cmd_task_attr)
        UFS_PRINT("ufs_cmd_task_attr = %d, free_slot is %d\n",
                  ufs_cmd_task_attr, free_slot);
#endif
    cmd_upiu_ptr->lun = dwc_host->active_lun;
    cmd_upiu_ptr->task_tag = free_slot;
    cmd_upiu_ptr->cmd_set_type = 0x0;
    cmd_upiu_ptr->reserved_1_0 = 0x0;
    cmd_upiu_ptr->reserved_1_1 = 0x0;
    cmd_upiu_ptr->reserved_1_2 = 0x0;
    cmd_upiu_ptr->tot_ehs_len = 0x0;
    cmd_upiu_ptr->reserved_2 = 0x0;
    cmd_upiu_ptr->data_seg_len = 0x0;
    cmd_upiu_ptr->exp_data_xfer_len = to_bigendian32(size);

    if (opcode == UFS_OP_SECURITY_PROTOCOL_IN ||
            opcode == UFS_OP_SECURITY_PROTOCOL_OUT) {
        get_cmnd(opcode, 0, size, cmd_upiu_ptr->cdb);
        prdt_buf_size = RPMB_FRAME_SIZE;
    } else if (opcode == UFS_OP_REQUEST_SENSE ||
               opcode == UFS_OP_FORMAT_UNIT ||
               opcode == UFS_OP_INQUIRY ||
               opcode == UFS_OP_REPORT_LUNS ||
               opcode == UFS_OP_MODE_SENSE_10 ||
               opcode == UFS_OP_MODE_SELECT_10 ||
               opcode == UFS_OP_START_STOP_UNIT ||
               opcode == UFS_OP_TEST_UNIT_READY ||
               opcode == UFS_OP_READ_CAPACITY_10 ||
               opcode == UFS_OP_SEND_DIAGNOSTIC ||
               opcode == UFS_OP_UNMAP ||
               opcode == UFS_OP_WRITE_BUFFER) {
        get_cmnd(opcode, 0, size, cmd_upiu_ptr->cdb);
    } else {
        get_cmnd(opcode, (uint32_t)(rel_addr / LOGICAL_BLK_SIZE),
                 (size / LOGICAL_BLK_SIZE), cmd_upiu_ptr->cdb);
    }

    if (opcode == UFS_OP_START_STOP_UNIT &&
            ((cmd_upiu_ptr->cdb[4] & 0xF0) != 0)) {
        /*In Power Management Command: START STOP UNIT, the LUN is fixed
         * to 0x50 or 0xD0 for W-LUN */
        cmd_upiu_ptr->lun = 0xD0;
    }

    /* Update PRDT Length */
    utrd->prdt_length = to_littleendian16((uint16_t)(
            (size & (prdt_buf_size - 1)) ? ((size / prdt_buf_size) + 1) :
            (size / prdt_buf_size)));

    buf_addr_phy = buf_addr;
    /* Fill PRD Table Info */
    for (i = 0; (size); i++) {
        prdt[i].base_addr =
            (LOWER_32_BITS(buf_addr_phy + (i * prdt_buf_size)));
        prdt[i].upper_addr =
            (UPPER_32_BITS(buf_addr_phy + (i * prdt_buf_size)));

        prdt[i].reserved1 = 0x0;
        prdt[i].size = to_littleendian32
                       (((prdt_buf_size < size) ? prdt_buf_size : size) - 1);
        size -= (prdt_buf_size < size) ? prdt_buf_size : size;
    }
#ifdef CMD_UPIU_DEBUG
    num_prd = i;
    ptr_dw = (uint32_t *)&prdt[0];
    UFS_PRINT("buf_addr is 0x%p\n", buf_addr);
    UFS_PRINT("The byte array dump of PRD Table(0x%p) is\n", ptr_dw);
    for (i = 0; i < num_prd * 4; i++) {
        UFS_PRINT("0x%x\n", ptr_dw[i]);
    }
#endif

#ifdef CMD_UPIU_DEBUG
    ptr_dw = (uint32_t *)utrd;

    UFS_PRINT("The byte array dump of UTRD(0x%p) is\n",
              ptr_dw);
    for (i = 0; (i * 4 < (sizeof(struct dwc_ufs_utrd))); i++) {
        UFS_PRINT("0x%x\n", ptr_dw[i]);
    }

    ptr_b = (uint8_t *)cmd_upiu_ptr;
    UFS_PRINT("The byte array dump of cmd upiu(0x%p) is\n",
              ptr_b);
    for (i = 0; (i < (sizeof(struct dwc_ufs_cmd_upiu))); i += 4)
        UFS_PRINT("0x%x 0x%x 0x%x 0x%x\n",
                  ptr_b[i], ptr_b[i + 1], ptr_b[i + 2], ptr_b[i + 3]);
#endif
    /*occupy this slot */
    set_bits(BIT(free_slot),
             (unsigned long)&dwc_host->outstanding_xfer_reqs);

    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(utrd),
                     (char *)utrd,
                     sizeof(struct dwc_ufs_utrd));

    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(cmd_upiu_ptr),
                     (char *)cmd_upiu_ptr,
                     sizeof(struct dwc_ufs_cmd_upiu));

    /* copy the prdt to sram*/
    for (i = 0; i < utrd->prdt_length; i++) {
        memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(prdt),
                         (char *)prdt,
                         sizeof(struct dwc_ufs_prd));
        prdt++;
    }

    FUNC_EXIT();
    return UFS_SUCCESS;
}


int dwc_ufshcd_drv_init(struct dwc_ufs_hba *hba)
{
    int result;
    /* Read host Controller Capabilities */

    dwc_ufshcd_read_caps(hba);

    /* Allocate memory required to interface with host */
    result = dwc_ufshcd_alloc_interface_memory(hba);

    if (result != 0) {
        PRINT_ERROR("%s: Error Allocating the required memory to "
                    "interface DWC UFS HC\n", __func__);
        return result;
    }
    /* Configure the HC memory with required information and the LRB */
    dwc_ufshcd_configure_interface_memory(hba);

    /* Disable debug mode and stop capturing statistics */
    hba->debug_mode = 0;

    return result;
}


/****************************************************************
 * ufs_soft_init
 * Description: alloc memory for dwc_host
 ****************************************************************/
int ufs_soft_init(void)
{
    /*In ufs_reinit function, don't need to alloc memory here again.*/
    int ret = 0;

    GET_LOCAL_DWC_HOST();

    memset((void *)dwc_host, 0, (unsigned int)sizeof(struct dwc_ufs_hba));

    ret = dwc_ufshcd_drv_init(dwc_host);
    if (ret) {
        UFS_PRINT("dwc_ufshcd_drv_init fail!!\n");
        return ret;
    }

    return ret;
}

void ufs_config_init(void)
{
    int i;
    uint32_t value;

    GET_LOCAL_DWC_HOST();
    if (IF_FPGA()) {
#ifdef UFS_USE_SNPS_MPHY_TC
        /*set the granularity to 2. need to check in ASIC...*/
        send_uic_command(DME_SET, 0x15aa0000, 0x0, 2);
        /*set the PA_TActivate to 128. need to check in ASIC...*/
        send_uic_command(DME_SET, 0x15a80000, 0x0, 128);
        /*BUSTHRTL.LP_AH8_PGE = 0, close the Auto-Hibernate's
        auto power-gating,so the MPHY's attribute will not lost*/
        value = dwc_ufs_read_reg(UFS_BUSTHRTL_OFF);
        value &= (uint32_t)(~LP_AH8_PGE);
        dwc_ufs_write_reg(UFS_BUSTHRTL_OFF, value);
        /*VS_ULPH8_Cntrl.Ulp_Ulp_CtrlMode = 0, close the ULP H8,
        so the MPHY's attribute will not be saved and restored
        during H8's enter and exit to improve effeciency*/
#ifndef UFS_USE_HISI_MPHY_TC
        value = uic_cmd_read(0x1, 0xd0af0000);
        value &= (uint32_t)(~ULP_ULP_CTRLMODE);
        send_uic_command(DME_SET, 0xd0af0000, 0x0, value);
#endif
#endif
    }

#if !defined(COMBO_PHY_V120)
    send_uic_command(DME_SET, 0x00ca0000, 0x0, 0x3);
#endif
    if (!IF_FPGA()) {
        /* Unipro DL_AFC0CreditThreshold */
        send_uic_command(DME_SET, 0x20440000, 0, 0x0);
        /* Unipro DL_TC0OutAckThreshold */
        send_uic_command(DME_SET, 0x20450000, 0, 0x0);
        /* Unipro DL_TC0TXFCThreshold */
        send_uic_command(DME_SET, 0x20400000, 0, 0x9);
    }

#ifdef UFS_USE_HISI_MPHY_TC
    /*set the PA_Granularity  to 2. need to check in ASIC...*/
    /*send_uic_command(DME_SET, 0x15aa0000, 0x0, 4);*/
    /*PA_Hibern8Time*/
    /*send_uic_command(DME_SET, 0x15a70000, 0x0, 0x80);*/
#if defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
    /*set the PA_TActivate to 128. need to check in ASIC...*/
    /* H8's workaround */
    /* PA_TActivate */
    send_uic_command(DME_SET, 0x15a80000, 0x0, 10);
    /* PLL_LOCK_TIME_VAL */
    //send_uic_command(DME_SET, 0x80da0000, 0x0, 0x2d);
#endif

#if defined(COMBO_PHY_V120)
    /* RX H8_TIMEOUT_VAL, Lane 0 */
    send_uic_command(DME_SET, 0x000a0004, 0x0, 0x1E);
    /* RX H8_TIMEOUT_VAL, Lane 1 */
    send_uic_command(DME_SET, 0x000a0005, 0x0, 0x1E);
#endif

    /* If the PLL is slow and needs more than 10 us
    * then this field can be used to specify the wait period unit. If
    * the value of this field */
    value = uic_cmd_read(DME_GET, 0xd0a00000); /* VS_DebugSaveConfigTime */
    value &= (uint32_t)(~(0x7 << 2));/* bit[4:2] = 0*/
    value |= 0x3 << 2; /* bit[4:2] = 3*/
    /* enlarge for default's 10us to 31250ns,
         can make rateA->B change smoothly */
    send_uic_command(DME_SET, 0xd0a00000, 0x0, value);
#endif

#if !defined(COMBO_PHY_V120)
    /* close the MC_PRESENT, or will cause the RX_MODE's update to PHY */
    /*RX MC_PRESENT OFF, lane0 */
    send_uic_command(DME_SET, 0x00c20004, 0x0, 0x0);
    /*RX MC_PRESENT OFF, lane1 */
    send_uic_command(DME_SET, 0x00c20005, 0x0, 0x0);
#endif /*!COMBO_PHY_V120*/

    /*the ufs register will be reset, so set the ufs register always*/
    dwc_ufshcd_initialize_hba_desc_pointers(dwc_host);
    for (i = 0; i < UNIT_DESCS_COUNT; i++) {
        dwc_host->lu_request_sense_sent[i] = 0;
    }

    dwc_ufs_write_reg(UFS_UTRLRSR_OFF, UFS_UTP_RUN_BIT);
    dwc_ufs_write_reg(UFS_UTMRLRSR_OFF, UFS_UTP_RUN_BIT);

#ifndef UFSHC_CLK_GATE_BYPASS
    /* not bypass ufs clk gate */
    clr_bits(MASK_UFS_CLK_GATE_BYPASS, UFS_SYS_CLOCK_GATE_BYPASS);
    clr_bits(MASK_UFS_SYSCRTL_BYPASS, UFS_SYS_UFS_SYSCTRL);
#endif

#if 0 /* open if need */
    uint32_t reg;
    /* disable auto H8 Power-Gating */
    reg = dwc_ufs_read_reg(UFS_BUSTHRTL_OFF);
    reg &= (uint32_t)(~LP_AH8_PGE);
    dwc_ufs_write_reg(UFS_BUSTHRTL_OFF, reg);
#endif

#if 0 /* open if need */
    /* enable auto H8 */
    dwc_ufs_write_reg(UFS_AHIT_OFF, UFS_AHIT_AUTOH8_TIMER);
#endif
}

/***************************************************************
 *
 * read_nop_rsp
 * Description: The function reads and validates the response
 *              received for NOP command
 *
 ***************************************************************/
static int read_nop_rsp(uint8_t free_slot)
{
    struct dwc_ufs_nop_resp_upiu *resp_upiu;
    struct dwc_ufs_utrd *utrd;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();

    resp_upiu =
        (struct dwc_ufs_nop_resp_upiu *)dwc_host->lrb[free_slot].resp_upiu;
    utrd = dwc_host->lrb[free_slot].utrd;

    /* copy the sram to PC memory */
    memcpy_sram_2_pc((char *)utrd,
                     (char *)ADDR_MAP_PC_2_SRAM(utrd),
                     sizeof(struct dwc_ufs_utrd));
    /* copy the sram to PC memory */
    memcpy_sram_2_pc((char *)resp_upiu,
                     (char *)ADDR_MAP_PC_2_SRAM(resp_upiu),
                     sizeof(struct dwc_ufs_nop_resp_upiu));

    if (utrd->ocs != UFS_SUCCESS) {
        UFS_PRINT("send nop out ocs err\n");
        return -((utrd->ocs & 0xf) + RET_UTRD_OCS_ERROR_OFF);
    }

    if ((resp_upiu->trans_type & 0x3F) != NOP_TRANS_TYPE) {
        UFS_PRINT("invalid nop in\n");
        return UFS_INVALID_NOP_IN;
    }

    if (resp_upiu->response != UFS_SUCCESS) {
        UFS_PRINT("nop in response error, resp = 0x%x\n",
                  resp_upiu->response);
        return UFS_NOP_RESP_FAIL;
    }

    FUNC_EXIT();
    return UFS_SUCCESS;
}



/***************************************************************
 *
 * wait_for_cmd_completion
 * Description: Sets the DoorBell Register and waits for the
 *              Doorbell to Clear. Returns Zero on Success or
 *      error number on Failure
 *
 ***************************************************************/
int wait_for_cmd_completion(uint32_t slot_mask)
{
    int retry = TIMEOUT_CNT;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();

    /* Set the doorbell for processing the request */
    dwc_ufs_write_reg(UFS_UTRLDBR_OFF, slot_mask);

    /* Wait for the DoorBell to clear */
    for (;;) {
        if ((dwc_ufs_read_reg(UFS_UTRLDBR_OFF) & slot_mask) == 0) {
            ufs_waitms(1);
            break;
        }
        retry--;
        if (retry == 0) {
            PRINT_ERROR("UTRL DoorBell Not Cleared and Timed Out, "
                        "DoorBell is 0x%x, slot_mask is 0x%x\n",
                        dwc_ufs_read_reg(UFS_UTRLDBR_OFF), slot_mask);
            ufs_reg_dump();
            dwc_ufs_write_reg(UFS_UTRLCLR_OFF, 0);
            /*release the outstanding xfer request */
            dwc_host->outstanding_xfer_reqs = 0;
            FUNC_EXIT();
            return UFS_UTRD_DOORBELL_TIMEOUT;
        }
        ufs_waitms(1); /* Platform Specific Implementation */
    }
    FUNC_EXIT();
    return UFS_SUCCESS;
}


/***************************************************************
 *
 * wait_for_cmd_completion_async
 * Description: Sets the DoorBell Register one BIT and the sleep
 *              some time, when all the effective slot over,
 *then
 *              wait Doorbell to Clear. Returns Zero on Success or
 *      error number on Failure
 *
 ***************************************************************/
int wait_for_cmd_completion_async(uint32_t doorbell, uint32_t slot_mask)
{
    int retry = 50000;
    int i;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();

    for (i = 0; i < dwc_host->nutrs; i++) {
        if (slot_mask & BIT(i)) {
            /* Set the doorbell for processing the request  */
            dwc_ufs_write_reg(doorbell, BIT(i));
            /*ufs_waitms(100); */
        }
    }
    /* Wait for the DoorBell to clear */
    for (;;) {
        if ((dwc_ufs_read_reg(doorbell) & slot_mask) == 0) {
            break;
        }
        retry--;
        if (retry == 0) {
            UFS_PRINT("UTRL DoorBell Not Cleared and Timed Out\n");
            ufs_reg_dump();
            FUNC_EXIT();
            /*clear the DoorBell if timeout*/
            dwc_ufs_write_reg(UFS_UTRLCLR_OFF, 0);
            /*release the outstanding xfer request */
            dwc_host->outstanding_xfer_reqs = 0;
            return UFS_UTRD_DOORBELL_TIMEOUT;
        }
        ufs_waitms(1); /* Platform Specific Implementation */
    }
    FUNC_EXIT();
    return UFS_SUCCESS;
}


/***************************************************************
 * create_nop_out_upiu
 * Description: Fills the UPIU memory for NOP OUT command
 *
 ***************************************************************/
static void create_nop_out_upiu(uint8_t free_slot)
{
    struct dwc_ufs_nop_req_upiu *cmd_upiu_ptr;
    struct dwc_ufs_nop_resp_upiu *resp_upiu;
    int i;
    struct dwc_ufs_utrd *utrd;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();

    cmd_upiu_ptr =
        (struct dwc_ufs_nop_req_upiu *)dwc_host->lrb[free_slot].cmd_upiu;

    utrd = dwc_host->lrb[free_slot].utrd;

    utrd->ct_and_flags =
        (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
    utrd->resp_upiu_length =
        to_littleendian16((uint16_t)
                          (sizeof(struct dwc_ufs_nop_resp_upiu) >> 2));
    utrd->prdt_length = 0;
    utrd->ocs = 0xf;

    cmd_upiu_ptr->trans_type = 0x00;
    cmd_upiu_ptr->flags = 0x00;
    cmd_upiu_ptr->reserved_1 = 0x00;
    cmd_upiu_ptr->task_tag = free_slot;
    cmd_upiu_ptr->reserved_2 = 0x0;
    cmd_upiu_ptr->tot_ehs_len = 0x00;
    cmd_upiu_ptr->reserved_3 = 0x00;
    cmd_upiu_ptr->data_seg_len = 0x00;
    for (i = 0; i < 20; i++) {
        cmd_upiu_ptr->reserved_4[i] = 0x00;
    }

    resp_upiu =
        (struct dwc_ufs_nop_resp_upiu *)
        dwc_host->lrb[free_slot].resp_upiu;
    memset((void *)resp_upiu, 0,
           sizeof(struct dwc_ufs_nop_resp_upiu));
    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(utrd),
                     (char *)utrd,
                     sizeof(struct dwc_ufs_utrd));
    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(cmd_upiu_ptr),
                     (char *)cmd_upiu_ptr,
                     sizeof(struct dwc_ufs_nop_req_upiu));

    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(resp_upiu),
                     (char *)utrd,
                     sizeof(struct dwc_ufs_nop_resp_upiu));
    FUNC_EXIT();
}

static int send_nop_out_cmd(void)
{
    int ret;
    int i;
    uint8_t free_slot;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();
    for (i = 0; i < 10; i++) {
        free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
        if (free_slot == BAD_SLOT) {
            return UFS_ERROR;
        }
        create_nop_out_upiu(free_slot);
        ret = wait_for_cmd_completion(BIT(free_slot));
        if (ret == UFS_SUCCESS) {
            ret = read_nop_rsp(free_slot);
        }

        if (ret == UFS_SUCCESS) {
            break;
        }

        UFS_PRINT("nop out nop in fail, ret = %d, "
                  "retry = %d\n", ret, i);
        ufs_waitms(10);
    }

    FUNC_EXIT();
    return ret;
}


/***************************************************************
 *
 * handle_query_response
 * Description: The functon does the following
 *              1. validates the query command's response received
 *              2. updates the ret argument with query data
 *              3. returns the status
 ***************************************************************/
static int handle_query_response(uint8_t *ret, uint8_t free_slot)
{
    struct dwc_ufs_query_upiu *resp_upiu;

    GET_LOCAL_DWC_HOST();

    FUNC_ENTER();

    resp_upiu =
        (struct dwc_ufs_query_upiu *)dwc_host->lrb[free_slot].resp_upiu;

    /* copy the sram to PC memory */
    memcpy_sram_2_pc((char *)resp_upiu,
                     (char *)ADDR_MAP_PC_2_SRAM(resp_upiu),
                     sizeof(struct dwc_ufs_query_upiu));

    /* Update the return value */
    if (ret) {
        ret[0] = resp_upiu->tsf[11];
        ret[1] = resp_upiu->tsf[10];
        ret[2] = resp_upiu->tsf[9];
        ret[3] = resp_upiu->tsf[8];
    }

    FUNC_EXIT();

    if (resp_upiu->query_resp == UFS_SUCCESS) {
        return UFS_SUCCESS;
    }

    UFS_PRINT("Query Response error: 0x%x\n", resp_upiu->query_resp);
    return -(resp_upiu->query_resp);
}


/***************************************************************
 *
 * create_query_upiu
 * Description: Populates the UPIU memory for all query Operations
 *
 ***************************************************************/
static void create_query_upiu(uint8_t opcode,
                              uint8_t query_func,
                              uint8_t selector,
                              uint8_t indexx,
                              uint8_t idn,
                              const uint8_t *val,
                              uint8_t free_slot)
{
    struct dwc_ufs_query_upiu *cmd_upiu_ptr;
    struct dwc_ufs_utrd *utrd;
    int i;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();
    cmd_upiu_ptr =
        (struct dwc_ufs_query_upiu *)dwc_host->lrb[free_slot].cmd_upiu;

    utrd = dwc_host->lrb[free_slot].utrd;

    /* UTRD Descriptor Programming for processing command */
    utrd->ct_and_flags =
        (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
    utrd->resp_upiu_length =
        to_littleendian16((uint16_t)
                          (sizeof(struct dwc_ufs_query_upiu) >> 2));
    utrd->prdt_length = 0;

    /* Command Descriptor Programming */
    cmd_upiu_ptr->trans_type = 0x16;
    cmd_upiu_ptr->flags = UPIU_CMD_FLAGS_NONE;
    cmd_upiu_ptr->reserved_1 = 0x00;
    cmd_upiu_ptr->task_tag = free_slot;
    cmd_upiu_ptr->reserved_2 = 0x00;
    cmd_upiu_ptr->query_func = query_func;
    cmd_upiu_ptr->query_resp = 0x00;
    cmd_upiu_ptr->reserved_3 = 0x00;
    cmd_upiu_ptr->tot_ehs_len = 0x00;
    cmd_upiu_ptr->data_seg_len = 0x00;
    cmd_upiu_ptr->tsf[0] = opcode;
    cmd_upiu_ptr->tsf[1] = idn;
    cmd_upiu_ptr->tsf[2] = indexx;    /* index */
    cmd_upiu_ptr->tsf[3] = selector; /* selector */
    cmd_upiu_ptr->tsf[4] = 0x00;
    cmd_upiu_ptr->tsf[5] = 0x00;
    cmd_upiu_ptr->tsf[6] = 0x00;
    cmd_upiu_ptr->tsf[7] = 0x00;

    /* Value/Flag Updation */
    cmd_upiu_ptr->tsf[8] = val[3];
    cmd_upiu_ptr->tsf[9] = val[2];
    cmd_upiu_ptr->tsf[10] = val[1];
    cmd_upiu_ptr->tsf[11] = val[0];

    for (i = 12; i < 15; i++) {
        cmd_upiu_ptr->tsf[i] = 0x00;
    }

    cmd_upiu_ptr->reserved_5 = 0x0;

    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(utrd),
                     (char *)utrd,
                     sizeof(struct dwc_ufs_utrd));
    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(cmd_upiu_ptr),
                     (char *)cmd_upiu_ptr,
                     sizeof(struct dwc_ufs_cmd_upiu));

    FUNC_EXIT();
}


/***************************************************************
 *
 * send_scsi_cmd()
 * Description: function creates UPIU for scsi commands sends it
 * to the device by setting the DoorBell.
 *
 ****************************************************************/
static int send_scsi_cmd(uint32_t opcode,
                         enum dma_data_direction direction,
                         uint64_t buf_addr,
                         uint64_t rel_addr,
                         uint32_t size)
{
    int ret;
    uint8_t free_slot;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();
    if (LOWER_32_BITS(buf_addr) % 0x4) {
        UFS_PRINT("fail! buf_addr:0x%llx "
                  "is not round to D-Words\n", buf_addr);
        return UFS_SOFTWARE_ERROR;
    }

    if (size % 0x4) {
        UFS_PRINT("fail! size:0x%x is not round to D-Words\n", size);
        return UFS_SOFTWARE_ERROR;
    }
    if (size / PRDT_BUFFER_SIZE > DWC_UFSHCD_MAX_PRD_SIZE) {
        UFS_PRINT("fail! size:0x%x is bigger than PRDT alloc\n", size);
        return UFS_SOFTWARE_ERROR;
    }

    free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
    if (free_slot == BAD_SLOT) {
        return UFS_ERROR;
    }

    ret = create_cmd_upiu(opcode, direction, buf_addr, rel_addr, size,
                          free_slot);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("create_cmd_upiu fail! ret(%d)\n", ret);
        return ret;
    }

    ret = wait_for_cmd_completion(BIT(free_slot));
    FUNC_EXIT();
    return ret;
}

/***************************************************************
 *
 * handle_scsi_completion
 * Description: The functon validates the SCSI command's
 *              response received
 *
 ***************************************************************/
static int handle_scsi_completion(void)
{
    struct dwc_ufs_resp_upiu *resp_upiu;
    struct dwc_ufs_utrd *utrd;
    uint8_t status;
    uint8_t slot_index;
    int i;
    int ret = 0;
#ifdef CMD_UPIU_DEBUG
    uint8_t *ptr;
#endif

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();
    for (i = 0; i < dwc_host->nutrs; i++) {
        slot_index = (uint8_t)i;
        /*the outstanding is set on, so dump the response, and then
         * clear the bit */
        if (dwc_host->outstanding_xfer_reqs & BIT(slot_index)) {
            resp_upiu = dwc_host->lrb[slot_index].resp_upiu;
            utrd = dwc_host->lrb[slot_index].utrd;

            /* copy the sram to PC memory */
            memcpy_sram_2_pc((char *)utrd,
                             (char *)ADDR_MAP_PC_2_SRAM(utrd),
                             sizeof(struct dwc_ufs_utrd));
            /* copy the sram to PC memory */
            memcpy_sram_2_pc((char *)resp_upiu,
                             (char *)ADDR_MAP_PC_2_SRAM(resp_upiu),
                             sizeof(struct dwc_ufs_resp_upiu));

            /*finish the requset here */
            dwc_host->outstanding_xfer_reqs ^= BIT(slot_index);

#ifdef CMD_UPIU_DEBUG
            ptr = (uint8_t *)resp_upiu;
            UFS_PRINT("The SCSI Command Response(0x%p) is\n", ptr);
            for (i = 0; (i < (sizeof(struct dwc_ufs_resp_upiu)));
                    i += 4)
                UFS_PRINT("0x%x 0x%x 0x%x 0x%x\n", ptr[i],
                          ptr[i + 1], ptr[i + 2], ptr[i + 3]);
#endif

            if (utrd->ocs == UFS_SUCCESS) {
                status = resp_upiu->status;
                if (status == SAM_STAT_GOOD) {
                    /*do nothing */
                } else if (status == SAM_STAT_CHECK_CONDITION) {
                    /* 0x20 is added to sense key to return
                     * unique error code */
                    ret = -(RET_SENSE_KEY_OFF +
                            (resp_upiu->sense_data[2] & 0xf));
                    /*because other slot to check, so not
                     * return here */
                    UFS_PRINT(
                        "The sense key is 0x%x, "
                        "ASC is 0x%x, "
                        "ASCQ is 0x%x, "
                        "slot_index is %d\n",
                        ((uint8_t *)
                         resp_upiu)[SENSE_KEY_INDEX] &
                        0xf, ((uint8_t *)
                              resp_upiu)[SENSE_KEY_INDEX + 10],
                        ((uint8_t *)
                         resp_upiu)[SENSE_KEY_INDEX + 11],
                        slot_index);
                } else {

                    switch (status) {
                        case SAM_STAT_CONDITION_MET:
                            ret =
                                RESP_STAT_CONDITION_MET;
                            break;

                        case SAM_STAT_BUSY:
                            ret = RESP_STAT_BUSY;
                            break;

                        case SAM_STAT_RESERVATION_CONFLICT:
                            ret =
                                RESP_STAT_RESERVATION_CONFLICT;
                            break;

                        case SAM_STAT_TASK_SET_FULL:
                            ret =
                                RESP_STAT_TASK_SET_FULL;
                            break;

                        case SAM_STAT_ACA_ACTIVE:
                            ret =
                                RESP_STAT_ACA_ACTIVE;
                            break;

                        case SAM_STAT_TASK_ABORTED:
                            ret =
                                RESP_STAT_TASK_ABORTED;
                            break;

                        default:
                            ret = RESP_STAT_UNKNOWN;
                    }
                }
            } else {
                ret = -((utrd->ocs & 0xf) +
                        RET_UTRD_OCS_ERROR_OFF);
                /*because other slot to check, so not return here */
                /*
                UFS_PRINT("The OCS val returned is %x\n",
                    utrd->ocs);
                */
                ufs_reg_dump();
            }
        }
    }

    FUNC_EXIT();
    return ret;
}

static int do_scsi_cmd(uint32_t opcode,
                       enum dma_data_direction direction,
                       uint64_t buf_addr,
                       uint64_t rel_addr,
                       uint32_t size)
{
    int ret;

    FUNC_ENTER();

    ret = send_scsi_cmd(opcode, direction, buf_addr, rel_addr, size);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("send scsi cmd[0x%x] error: %d\n", opcode, ret);
        FUNC_EXIT();
        return ret;
    }

    ret = handle_scsi_completion();
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("handle scsi cmd[0x%x] completion error: %d\n",
                  opcode, ret);
        FUNC_EXIT();
        return ret;
    }
    FUNC_EXIT();
    return ret;
}


/***************************************************************
 *
 * create_desc_upiu
 * Description: The function does a simple memcpy of the req_upiu
 *              content passed to UPIU memory for Read/Write
 *              descriptor Operation
 *
 ***************************************************************/
static void create_desc_upiu(const void *req_upiu, uint8_t free_slot)
{
    FUNC_ENTER();

    GET_LOCAL_DWC_HOST();
    if (dwc_host->lrb[free_slot].cmd_upiu != req_upiu) {
        memcpy(dwc_host->lrb[free_slot].cmd_upiu, req_upiu,
               (unsigned int)
               (sizeof(struct dwc_ufs_query_upiu) +
                to_bigendian16(((struct dwc_ufs_query_upiu *)
                                req_upiu)->data_seg_len)));

        memcpy_pc_2_sram((char *)
                         ADDR_MAP_PC_2_SRAM(dwc_host->lrb[free_slot].cmd_upiu),
                         (char *)dwc_host->lrb[free_slot].cmd_upiu,
                         (unsigned int)(sizeof(struct dwc_ufs_query_upiu) +
                                        to_bigendian16(((struct dwc_ufs_query_upiu *)
                                                req_upiu)->data_seg_len)));

    }
    FUNC_EXIT();
}

/***************************************************************
 *
 * write_descriptor
 * Description: The functon populates the request upiu structure
 *      with upiu info passed in 1st argument
 *
 ***************************************************************/
int write_descriptor(const void *req_upiu)
{
    int ret;
    struct dwc_ufs_utrd *utrd;
    uint8_t free_slot;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();

    free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
    if (free_slot == BAD_SLOT) {
        return ERROR;
    }
    utrd = dwc_host->lrb[free_slot].utrd;
    /* UTRD Descriptor Programming for processing command */
    utrd->ct_and_flags = (uint8_t)
                         (UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
    utrd->resp_upiu_length = to_littleendian16(
                                 (uint16_t)(sizeof(struct dwc_ufs_query_upiu) >> 2));
    utrd->prdt_length = 0;

    create_desc_upiu(req_upiu, free_slot);

    ret = wait_for_cmd_completion(BIT(free_slot));
    if (ret != UFS_SUCCESS) {
        FUNC_EXIT();
        return ret;
    }

    ret = handle_query_response(NULL, free_slot);
    FUNC_EXIT();

    return ret;
}


/***************************************************************
 *
 * read_attribute
 * Description: The functon sends the query command to read an
 *              attribute and updates the ret_value with the
 *              content of the attribute
 *
 ***************************************************************/
int read_attribute(enum attr_id idn,
                   uint8_t iindex,
                   uint8_t selector,
                   uint32_t *ret_value)
{
    int ret;
    uint8_t free_slot;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();
    free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
    if (free_slot == BAD_SLOT) {
        return ERROR;
    }
    *ret_value = 0;

    create_query_upiu(READ_ATTR_OPCODE, STANDARD_RD_REQ,
                      selector, iindex, idn, (uint8_t *)ret_value, free_slot);
    ret = wait_for_cmd_completion(BIT(free_slot));
    if (ret != UFS_SUCCESS) {
        return ret;
    }

    ret = handle_query_response((uint8_t *)ret_value, free_slot);
    FUNC_EXIT();
    return ret;
}

/***************************************************************
 *
 * write_attribute
 * Description: The functon sends the query command to write an
 *              attribute with the value passed as second argument
 *
 ***************************************************************/
int write_attribute(enum attr_id idn,
                    uint8_t iindex,
                    uint8_t selector,
                    uint32_t *value)
{
    int ret;
    uint8_t free_slot;

    GET_LOCAL_DWC_HOST();
    free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
    if (free_slot == BAD_SLOT) {
        return ERROR;
    }
    FUNC_ENTER();

    create_query_upiu(WRITE_ATTR_OPCODE, STANDARD_WR_REQ,
                      selector, iindex, idn, (uint8_t *)value, free_slot);
    ret = wait_for_cmd_completion(BIT(free_slot));
    if (ret != UFS_SUCCESS) {
        FUNC_EXIT();
        return ret;
    }

    ret = handle_query_response((uint8_t *)value, free_slot);
    FUNC_EXIT();
    return ret;
}

/***************************************************************
 * update_lu_capacity_info
 * Updates the dNumAllocUnits information for the Logic Unit
 * indexed by index. In addition, this also tracks the number
 * of LUs that will be provisioned in the device.
 ***************************************************************/
int update_lu_capacity_info(struct partitionDescTable *pdt)
{
    uint32_t numerator;
    uint32_t denominator;
    int i;
    int max_cap_lu = -1;
    uint32_t alloced_units = 0;
    uint16_t cap_adj_fac = 0;
    uint32_t *p_max_alloc_unit = NULL;

    /* Initialize the LUN tracker to zero */
    pdt->bNumberLU = 0;

    for (i = 0; i < UNIT_DESCS_COUNT; i++) {
        if (pdt->partitionDescPtr[i] == NULL) {
            continue;
        }
        if (pdt->partitionDescPtr[i]->lu_capacity == UFS_MAX_LU_CAP) {
            if (-1 != max_cap_lu) {
                UFS_PRINT("more than one lu set "
                          "UFS_MAX_LU_CAP\n");
                return -1;
            }
            max_cap_lu = i;
            continue;
        }
        if (0 == (BIT(pdt->partitionDescPtr[i]->memoryType) &
                  pdt->wSupportedMemoryTypes)) {
            UFS_PRINT("device not support memoryType: %d\n",
                      pdt->partitionDescPtr[i]->memoryType);
            return -2;
        }
        switch (pdt->partitionDescPtr[i]->memoryType) {
            case 0x0:
                cap_adj_fac = CAPCITY_ADJ_FACTOR;
                p_max_alloc_unit = NULL;
                break;
            case 0x1:
                cap_adj_fac = pdt->wSystemCodeCapAdjFac / 256;
                p_max_alloc_unit = &(pdt->dSystemCodeMaxNAllocU);
                break;
            case 0x2:
                cap_adj_fac = pdt->wNonPersistCapAdjFac / 256;
                p_max_alloc_unit = &(pdt->dNonPersistMaxNAllocU);
                break;
            case 0x3:
                cap_adj_fac = pdt->wEnhanced1CapAdjFac / 256;
                p_max_alloc_unit = &(pdt->dEnhanced1MaxNAllocU);
                break;
            case 0x4:
                cap_adj_fac = pdt->wEnhanced2CapAdjFac / 256;
                p_max_alloc_unit = &(pdt->dEnhanced2MaxNAllocU);
                break;
            case 0x5:
                cap_adj_fac = pdt->wEnhanced3CapAdjFac / 256;
                p_max_alloc_unit = &(pdt->dEnhanced3MaxNAllocU);
                break;
            case 0x6:
                cap_adj_fac = pdt->wEnhanced4CapAdjFac / 256;
                p_max_alloc_unit = &(pdt->dEnhanced4MaxNAllocU);
                break;
            default:
                UFS_PRINT("unknown memory type\n");
                return -3;
        }
        if (pdt->partitionDescPtr[i]->lu_capacity *
                cap_adj_fac >= 0x200000) {
            UFS_PRINT("input lu_capacity set too large\n");
            return -4;
        }
        numerator =
            (pdt->partitionDescPtr[i]->lu_capacity) *
            2048 * cap_adj_fac;
        denominator = (pdt->bAllocationUnitSize) *
                      (pdt->dSegmentSize);
        pdt->partitionDescPtr[i]->dNumAllocUnits =
            (numerator + denominator - 1) / denominator;
        UFS_PRINT("UFS lun(%d)-NumAllocUnits:0x%x\n",
                  i, pdt->partitionDescPtr[i]->dNumAllocUnits);
        if (p_max_alloc_unit) {
            if (pdt->partitionDescPtr[i]->dNumAllocUnits >
                    *p_max_alloc_unit) {
                UFS_PRINT("Alloc units more than this type(0x%x) "
                          "MaxNAllocU\n",
                          pdt->partitionDescPtr[i]->memoryType);
                return -5;
            }
            *p_max_alloc_unit -=
                pdt->partitionDescPtr[i]->dNumAllocUnits;
        }
        alloced_units += pdt->partitionDescPtr[i]->dNumAllocUnits;
        pdt->bNumberLU = (uint8_t)(pdt->bNumberLU + 1);
    }

    if (max_cap_lu != -1) {
        numerator = LOWER_32_BITS(pdt->qTotalRawDeviceCapacity);
        denominator = (pdt->bAllocationUnitSize) * (pdt->dSegmentSize);
        pdt->partitionDescPtr[max_cap_lu]->dNumAllocUnits =
            numerator / denominator - alloced_units;
        if (UPPER_32_BITS(pdt->qTotalRawDeviceCapacity)) {
            /* There is no more than 2048GB device yet */
            UFS_PRINT("not support more than 2048GB device\n");
            return -6;
        }
        pdt->bNumberLU = (uint8_t)(pdt->bNumberLU + 1);
    }

    return 0;
}

int compair_conf_desp(const struct dwc_ufs_query_upiu *resp_upiu,
                      const struct partitionDescTable *pdt)
{
    uint8_t len, offset;
    uint8_t *data;
    struct partitionDesc **desc;
    int i;

    GET_LOCAL_DWC_HOST();

    len = dwc_host->unit_length;
    offset = dwc_host->unit_offset;
    data = (uint8_t *)(resp_upiu + 1);
    if (data[0x3] != pdt->p_conf_header->bBootEnable) {
        return 3;
    }
    if (data[0x4] != pdt->p_conf_header->bDescrAccessEn) {
        return 4;
    }
    if (data[0x5] != pdt->p_conf_header->bInitPowerMode) {
        return 5;
    }
    if (data[0x6] != pdt->p_conf_header->bHighPriorityLUN) {
        return 6;
    }
    if (data[0x7] != pdt->p_conf_header->bSecureRemovalType) {
        return 7;
    }
    if (data[0x8] != pdt->p_conf_header->bInitActiveICCLevel) {
        return 8;
    }
    if (data[0x9] != (uint8_t)
            (((pdt->p_conf_header->wPeriodicRTCUpdate) & 0xff00) >> 8) ||
            data[0xA] != (uint8_t)
            ((pdt->p_conf_header->wPeriodicRTCUpdate) & 0xff)) {
        return 9;
    }

    desc = (struct partitionDesc **)pdt->partitionDescPtr;
    for (i = 0; i < UNIT_DESCS_COUNT; i++) {
        if (desc[i] == NULL) {
            /* the Lun is disable */
            if (data[(unsigned int)((len * i) + offset + 0)] != 0x0) {
                return 0x10 * (i + 1);
            }
            continue;
        }
        if (data[(unsigned int)((len * i) + offset + 0x0)] != 0x1) {
            return 0x10 * (i + 1);
        }
        if (data[(unsigned int)((len * i) + offset + 0x1)] !=
                desc[i]->bootLunId) {
            return 0x10 * (i + 1) + 0x1;
        }
        if (data[(unsigned int)((len * i) + offset + 0x2)] !=
                desc[i]->writeProtect) {
            return 0x10 * (i + 1) + 0x2;
        }
        if (data[(unsigned int)((len * i) + offset + 0x3)] !=
                desc[i]->memoryType) {
            return 0x10 * (i + 1) + 0x3;
        }
        if (data[(unsigned int)((len * i) + offset + 0x4)] !=
                (uint8_t)(((desc[i]->dNumAllocUnits) &
                           0xff000000) >> 24) ||
                data[(unsigned int)((len * i) + offset + 0x5)] !=
                (uint8_t)(((desc[i]->dNumAllocUnits) &
                           0xff0000) >> 16) ||
                data[(unsigned int)((len * i) + offset + 0x6)] !=
                (uint8_t)(((desc[i]->dNumAllocUnits) &
                           0xff00) >> 8) ||
                data[(unsigned int)((len * i) + offset + 0x7)] !=
                (uint8_t)((desc[i]->dNumAllocUnits) &
                          0xff)) {
            return 0x10 * (i + 1) + 0x4;
        }
        if (data[(unsigned int)((len * i) + offset + 0x8)] !=
                desc[i]->dataReliability) {
            return 0x10 * (i + 1) + 0x8;
        }
        if (data[(unsigned int)((len * i) + offset + 0x9)] !=
                desc[i]->blockSize) {
            return 0x10 * (i + 1) + 0x9;
        }
        if (data[(unsigned int)((len * i) + offset + 0xa)] !=
                desc[i]->provType) {
            return 0x10 * (i + 1) + 0xA;
        }
        if (data[(unsigned int)((len * i) + offset + 0xb)] !=
                (uint8_t)((desc[i]->wContextCapabilities) >> 8) ||
                data[(unsigned int)((len * i) + offset + 0xc)] !=
                (uint8_t)((desc[i]->wContextCapabilities) & 0xFF)) {
            return 0x10 * (i + 1) + 0xB;
        }
    }

    return 0;
}


/***************************************************************
 *
 * ufs_device_init()
 * Description: The function does the following
 *            1. Sends the NOP Out command continuosly till it passes
 *            2. Sets the Device init Flag for UFS Device initialization
 *
 ****************************************************************/
int ufs_device_init(void)
{
    int ret;
    uint8_t flags_ret_val = 1;
    int retry = RETRY_CNT;

    FUNC_ENTER();
    ufs_waitms(10);

    /* Send continuos NOP OUT Command unless Response is Valid */
    ret = send_nop_out_cmd();
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("nop out fail\n");
        FUNC_EXIT();
        return ret;
    }

    ufs_waitms(50);
    /* Set the Device Init Flag */
    ret = ufs_set_flag(FDEVICE_INIT, &flags_ret_val);
    if (ret) {
        UFS_PRINT("set device init flag fail\n");
        FUNC_EXIT();
        return ret;
    }

    ufs_waitms(10);

    do {
        retry--;
        ret = ufs_read_flag(FDEVICE_INIT, &flags_ret_val);
        if ((ret == UFS_SUCCESS) && (flags_ret_val == 0)) {
            FUNC_EXIT();
            return UFS_SUCCESS;
        }
        ufs_waitms(10);
    } while (retry > 0);

    if (flags_ret_val != 0) {
        ret = UFS_FDEVICE_INIT_FAIL;
    }

    ufs_waitms(100);
    UFS_PRINT("read device init fail\n");
    FUNC_EXIT();
    return ret;
}

int ufs_host_init(void)
{
    int ret = 0;
    /* no need to config clk because testchip already have configed */
    /* ufs_clk_init(); */

    /* no controller and device reset & unreset also ??? */
    /* ufs_hardware_init(); */

    ret = ufs_soft_init();
    if (ret) {
        UFS_PRINT("ufs_soft_init fail!!\n");
        return ret;
    }

    ret = ufs_hc_enable();
    if (ret) {
        UFS_PRINT("HC enable fail!!\n");
        return ret;
    }
    //debug
    //return -1;
    //debug


    ufs_hc_init();

    ufs_waitms(40);

    ret = ufs_link_startup();
    if (ret) {
        UFS_PRINT("link start up FAIL!!\n");
        return ret;
    }

    ufs_config_init();
    UFS_PRINT("UFS Linkup!\n");
    return UFS_SUCCESS;
}


/*
 * some device need a full reset after lu config
 * And this funciton does not switch to hs mode
 * after lu config and ufs_reset init would continue and switch to hs mode
 */
static int ufs_reset(void)
{
    int ret = 0;

    GET_LOCAL_DWC_HOST();

    ret = ufs_host_init();
    if (ret) {
        PRINT_ERROR("UfsHostInit ret:%d\n", ret);
        return ret;
    }

    /* device reset will cause a new UAC */
    memset(dwc_host->lu_request_sense_sent, 0, UNIT_DESCS_COUNT);

    ret = ufs_device_init();
    if (ret) {
        PRINT_ERROR("UfsDeviceInit ret:%d\n", ret);
    }
    return ret;
}

/***************************************************************
 * update_geometry_info
 * Updates the dSegmentSize and bAllocationUnitSize
 * from the response upiu.
 * The assumption is the response upiu contains the Geometry
 * descriptor information
 ***************************************************************/
void update_geometry_info(struct dwc_ufs_query_upiu *resp_upiu,
                          struct partitionDescTable *pdt)
{
    uint8_t *data;

    data = (uint8_t *)(resp_upiu + 1);

    pdt->dSegmentSize = (uint32_t)
                        (((uint32_t)data[0x0d] << 24) | (data[0x0e] << 16) |
                         (data[0x0f] << 8) | data[0x10]);
    pdt->bAllocationUnitSize = data[0x11];

    pdt->qTotalRawDeviceCapacity = (uint32_t)
                                   (((uint32_t)data[0x04] << 24) | (data[0x05] << 16) |
                                    (data[0x06] << 8) | data[0x07]);
    pdt->qTotalRawDeviceCapacity = pdt->qTotalRawDeviceCapacity << 32;
    pdt->qTotalRawDeviceCapacity |= (uint32_t)
                                    (((uint32_t)data[0x08] << 24) | (data[0x09] << 16) |
                                     (data[0x0a] << 8) | data[0x0b]);

    pdt->bDataOrdering = data[0x19];
    pdt->bMaxContexIDNumber = data[0x1A];
    pdt->wSupportedMemoryTypes = (uint16_t)
                                 ((data[0x1E] << 8) | data[0x1F]);

    pdt->dSystemCodeMaxNAllocU = (uint32_t)
                                 (((uint32_t)data[0x20] << 24) | (data[0x21] << 16) |
                                  (data[0x22] << 8) | data[0x23]);
    pdt->wSystemCodeCapAdjFac = (uint16_t)
                                ((data[0x24] << 8) | data[0x25]);

    pdt->dNonPersistMaxNAllocU = (uint32_t)
                                 (((uint32_t)data[0x26] << 24) | (data[0x27] << 16) |
                                  (data[0x28] << 8) | data[0x29]);
    pdt->wNonPersistCapAdjFac = (uint16_t)
                                ((data[0x2a] << 8) | data[0x2b]);

    pdt->dEnhanced1MaxNAllocU = (uint32_t)
                                (((uint32_t)data[0x2c] << 24) | (data[0x2d] << 16) |
                                 (data[0x2e] << 8) | data[0x2f]);
    pdt->wEnhanced1CapAdjFac = (uint16_t)
                               ((data[0x30] << 8) | data[0x31]);

    pdt->dEnhanced2MaxNAllocU = (uint32_t)
                                (((uint32_t)data[0x32] << 24) | (data[0x33] << 16) |
                                 (data[0x34] << 8) | data[0x35]);
    pdt->wEnhanced2CapAdjFac = (uint16_t)
                               ((data[0x36] << 8) | data[0x37]);

    pdt->dEnhanced3MaxNAllocU = (uint32_t)
                                (((uint32_t)data[0x38] << 24) | (data[0x39] << 16) |
                                 (data[0x3a] << 8) | data[0x3b]);
    pdt->wEnhanced3CapAdjFac = (uint16_t)
                               ((data[0x3c] << 8) | (data[0x3d]));

    pdt->dEnhanced4MaxNAllocU = (uint32_t)
                                (((uint32_t)data[0x3e] << 24) | (data[0x3f] << 16) |
                                 (data[0x40] << 8) | data[0x41]);
    pdt->wEnhanced4CapAdjFac = (uint16_t)
                               ((data[0x42] << 8) | data[0x43]);

    UFS_PRINT("UFS TotalRawDeviceCapacity: 0x%x%x\n",
              UPPER_32_BITS(pdt->qTotalRawDeviceCapacity),
              LOWER_32_BITS(pdt->qTotalRawDeviceCapacity));
    UFS_PRINT("UFS Segment Size: 0x%x\n",
              pdt->dSegmentSize);
    UFS_PRINT("UFS Allocation Unit Size: 0x%x\n",
              pdt->bAllocationUnitSize);
    UFS_PRINT("UFS Data Ordering: 0x%x\n",
              pdt->bDataOrdering);
    UFS_PRINT("UFS bMaxContexIDNumber: 0x%x\n",
              pdt->bMaxContexIDNumber);
    UFS_PRINT("UFS Supported Memory Types: 0x%x\n",
              pdt->wSupportedMemoryTypes);
    UFS_PRINT("UFS dSystemCodeMaxNAllocU: 0x%x\n",
              pdt->dSystemCodeMaxNAllocU);
    UFS_PRINT("UFS wSystemCodeCapAdjFac: 0x%x\n",
              pdt->wSystemCodeCapAdjFac);
    UFS_PRINT("UFS dNonPersistMaxNAllocU: 0x%x\n",
              pdt->dNonPersistMaxNAllocU);
    UFS_PRINT("UFS wNonPersistCapAdjFac: 0x%x\n",
              pdt->wNonPersistCapAdjFac);
    UFS_PRINT("UFS dEnhanced1MaxNAllocU: 0x%x\n",
              pdt->dEnhanced1MaxNAllocU);
    UFS_PRINT("UFS wEnhanced1CapAdjFac: 0x%x\n",
              pdt->wEnhanced1CapAdjFac);
    UFS_PRINT("UFS dEnhanced2MaxNAllocU: 0x%x\n",
              pdt->dEnhanced2MaxNAllocU);
    UFS_PRINT("UFS wEnhanced2CapAdjFac: 0x%x\n",
              pdt->wEnhanced2CapAdjFac);
    UFS_PRINT("UFS dEnhanced3MaxNAllocU: 0x%x\n",
              pdt->dEnhanced3MaxNAllocU);
    UFS_PRINT("UFS wEnhanced3CapAdjFac: 0x%x\n",
              pdt->wEnhanced3CapAdjFac);
    UFS_PRINT("UFS dEnhanced4MaxNAllocU: 0x%x\n",
              pdt->dEnhanced4MaxNAllocU);
    UFS_PRINT("UFS wEnhanced4CapAdjFac: 0x%x\n",
              pdt->wEnhanced4CapAdjFac);
}


/***************************************************************
 * fill_ud_len_offset
 * Description: The function updates the global configurable unit
 *              desc's length and offset values
 ***************************************************************/
static void fill_ud_len_offset(struct dwc_ufs_query_upiu *resp_upiu)
{
    uint8_t *data_ptr;

    GET_LOCAL_DWC_HOST();
    data_ptr = (uint8_t *)(resp_upiu + 1);

    dwc_host->unit_offset = data_ptr[0x1a];
    dwc_host->unit_length = data_ptr[0x1b];
}


/***************************************************************
 * update_ufs_device_spec_version
 * Description: The function updates the global configurable unit
 *              desc's device specification version
 ***************************************************************/
static void update_ufs_device_spec_version(
    struct dwc_ufs_query_upiu *resp_upiu)
{
    uint8_t *data_ptr;

    GET_LOCAL_DWC_HOST();
    data_ptr = (uint8_t *)(resp_upiu + 1);

    dwc_host->dev_spec_version =
        (uint16_t)to_littleendian16(*(uint16_t *)&data_ptr[0x10]);
}

/***************************************************************
 * update_string_desc_idex
 * Description: The function updates the global configurable unit
 *              desc's device specification version
 ***************************************************************/
void update_string_desc_idex(struct dwc_ufs_query_upiu *resp_upiu)
{
    uint8_t *data_ptr;

    GET_LOCAL_DWC_HOST();
    data_ptr = (uint8_t *)(resp_upiu + 1);

    dwc_host->manufacturer_name = data_ptr[0x14];
    dwc_host->product_name = data_ptr[0x15];
    dwc_host->oem_id = data_ptr[0x17];
    dwc_host->serial_number = data_ptr[0x16];
    dwc_host->manufacturer_id =
        (uint16_t)swap_16(*(uint16_t *)&data_ptr[0x18]);
    dwc_host->manufacturer_data =
        (uint16_t)swap_16(*(uint16_t *)&data_ptr[0x12]);

    switch (dwc_host->manufacturer_id) {
        case UFS_MANUFACTURER_ID_TOSHIBA:
            UFS_PRINT("UFS device: TOSHIBA\n");
            break;
        case UFS_MANUFACTURER_ID_HYNIX:
            UFS_PRINT("UFS device: HYNIX\n");
            break;
        case UFS_MANUFACTURER_ID_SUMSANG:
            UFS_PRINT("UFS device: SUMSANG\n");
            break;
        case UFS_MANUFACTURER_ID_SANDISK:
            UFS_PRINT("UFS device: SANDISK\n");
            break;
        default:
            UFS_PRINT("unknown manufacturerid!!!!!\n");
    }
}

static int ufs_get_device_info(void)
{
    int ret;
    struct desc_params params;
    struct dwc_ufs_query_upiu *req_upiu;
    void *tmp_ptr;
    void *resp_upiu;

    GET_LOCAL_DWC_HOST();
    /*use the slot 0 default */
    resp_upiu = dwc_host->lrb[0].resp_upiu;

    FUNC_ENTER();
    tmp_ptr = dwc_host->lrb[0].cmd_upiu;
    req_upiu = (struct dwc_ufs_query_upiu *)tmp_ptr;

    /* Read device descriptor to know Base(UNIT desc 0 offset) and
     * Length(UNIT desc length) */
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = DEVICE_DESC;
    params.desc_index = 0;
    params.length = DEVICE_DESC_LENGTH;
    modify_desc_upiu(&params);
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("READ DEVICE_DESC error\n");
        FUNC_EXIT();
        return ret;
    }
    (void)memcpy((void *)(&ufs_desc.dev_desc), (void *)((u8 *)resp_upiu + 32), DEVICE_DESC_LENGTH);
    ufs_waitms(100);

    /* Stores the Configuration Unit Descriptor Length and Offset */
    fill_ud_len_offset((struct dwc_ufs_query_upiu *)resp_upiu);

    /* Read and Stores UFS device specification version */
    update_ufs_device_spec_version((struct dwc_ufs_query_upiu *)resp_upiu);
    update_string_desc_idex((struct dwc_ufs_query_upiu *)resp_upiu);

    FUNC_EXIT();
    return ret;
}

/***************************************************************
 *
 * ufs_create_partition_inventory
 * Description: The Function does the following actions
 *
 * 1. Reads UNIT desc's and stores the qphymemrescnt of each lun
 * 2. Reads the Device Descriptor to know the Configureable Unit
 *    desc zero's Offset and length of all unit descriptors.
 * 3. Validates the qmemrescnt with the configuration desc contents
 * 4. Reads and edits the content of configuration desc as per the
 *    input arguments
 *
 ***************************************************************/
int ufs_create_partition_inventory(uint8_t partitionInventoryMask,
                                   struct partitionDescTable *pdt)
{
    int ret;
    struct desc_params params;
    struct dwc_ufs_query_upiu *req_upiu;
    void *tmp_ptr;
    void *resp_upiu;
    uint8_t i;
    uint32_t value;

    GET_LOCAL_DWC_HOST();
    /*use the slot 0 default */
    resp_upiu = dwc_host->lrb[0].resp_upiu;

    FUNC_ENTER();
    tmp_ptr = dwc_host->lrb[0].cmd_upiu;
    req_upiu = (struct dwc_ufs_query_upiu *)tmp_ptr;

    /* Read Geometry descriptor to know dSegmentSize bAllocationUnitSize */
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = GEOMETRY_DESC;
    params.desc_index = 0;
    params.length = GEOMETRY_DESC_LENGTH;
    modify_desc_upiu(&params);
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("READ GEOMETRY_DESC error\n");
        FUNC_EXIT();
        return ret;
    }
    (void)memcpy((void *)(&ufs_desc.geo_desc), (void *)((u8 *)resp_upiu + 32), GEOMETRY_DESC_LENGTH);

    /* Update the geometry information in the pdt */
    update_geometry_info((struct dwc_ufs_query_upiu *)resp_upiu, pdt);
    /* Validate the Input Arguments */
    for (i = 0; i < UNIT_DESCS_COUNT; i++) {
        if ((partitionInventoryMask & (BIT(i))) == 0) {
            pdt->partitionDescPtr[i] = NULL;
        }
    }

    update_lu_capacity_info(pdt);
    /* read and modify the config desc as per arg1 and arg2 */
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = CONFIGURATION_DESC;
    params.desc_index = 0;
    params.length = (uint8_t)((dwc_host->unit_length * UNIT_DESCS_COUNT) +
                              dwc_host->unit_offset);
    modify_desc_upiu(&params);
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("READ CONFIGURATION_DESC error\n");
        FUNC_EXIT();
        return ret;
    }

    ret = compair_conf_desp((struct dwc_ufs_query_upiu *)resp_upiu, pdt);
    if (!ret) {
        return 0;
    }

    ret = read_attribute(B_CONFIG_DESC_LOCK, 0, 0, &value);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("read bConfigDescrLock fail. ret = %d\n", ret);
    } else {
        UFS_PRINT("bConfigDescrLock = 0x%x\n", value);
        if (value == 1) {
            UFS_PRINT("write config desc fail: "
                      "descriptor locked\n");
            return -1;
        }
    }

    /* Response of Configuration descriptor
    sent as request UPIU */
    params.req_upiu = resp_upiu;
    params.conf_head = pdt->p_conf_header;
    params.part_desc = pdt->partitionDescPtr;
    params.opcode = WRITE_DESC_OPCODE;
    params.desc_idn = CONFIGURATION_DESC;
    params.desc_index = 0;
    params.length = (uint8_t)((dwc_host->unit_length * UNIT_DESCS_COUNT) +
                              dwc_host->unit_offset);

    modify_desc_upiu(&params);
    ret = write_descriptor(params.req_upiu);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("write configuration fail. ret = %d\n", ret);
        FUNC_EXIT();
        return ret;
    }

    ret = ufs_reset();
    if (ret) {
        UFS_PRINT("ufs_reset fail, ret = %d\n", ret);
        return ret;
    }

    FUNC_EXIT();
    return 0;
}

int ufs_set_bootlun(uint8_t lun)
{
    uint32_t value;
    int ret;

    ret = read_attribute(B_BOOT_LUNEN, 0, 0, &value);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("read bBootLunEn fail. ret = %d\n", ret);
        return ret;
    }

    if ((lun + 1) == value) {
        UFS_PRINT("Same UFS Lu%d Boot W-Lun\n", (value - 1));
        return 0;
    }

    /* set default boot from Boot LU A */
    value = lun + 1;
    ret = write_attribute(B_BOOT_LUNEN, 0, 0, &value);
    if (ret) {
        UFS_PRINT("write bBootLunEn attribute fail. ret = %d\n", ret);
        return ret;
    }
    UFS_PRINT("new UFS Lu%d Boot W-Lun\n", (value - 1));
    return ret;
}

int set_boot_lu_enable(void)
{
    uint32_t value;
    uint32_t target_value = WELL_BOOT_LU_A;
    int ret;

    ret = read_attribute(B_BOOT_LUNEN, 0, 0, &value);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("read bBootLunEn fail. ret = %d\n", ret);
        return ret;
    }

    if (1 == value || 2 == value) {
        UFS_PRINT("UFS Scan Lun(%c) Boot W-Lun\n",
                  (value == WELL_BOOT_LU_A) ? 'A' : 'B');
    }

    if (value == target_value) {
        return 0;
    }

    /* set default boot from Boot LU A */
    value = target_value;
    ret = write_attribute(B_BOOT_LUNEN, 0, 0, &value);
    if (ret) {
        UFS_PRINT("write bBootLunEn attribute fail. ret = %d\n", ret);
        return ret;
    }
    UFS_PRINT("UFS Active Lun(%c) Boot W-Lun\n",
              (value == 1) ? 'A' : 'B');
    return ret;
}

void little_endian_to_big_endian(unsigned int *num)
{
    unsigned int b0, b1, b2, b3;

    b0 = (*num & 0x000000ff) << 24;
    b1 = (*num & 0x0000ff00) << 8;
    b2 = (*num & 0x00ff0000) >> 8;
    b3 = (*num & 0xff000000) >> 24;
    *num = b0 | b1 | b2 | b3;
}

int is_little_endian(void)
{
    union {
        int i;
        char c[sizeof(int)];
    } x;

    x.i = 1;
    if (x.c[0] == 1) {
        return 1;
    } else {
        return 0;
    }
}

#define SERIAL_NUM_SIZE 12
static unsigned int ufs_cid[3];
unsigned int *ufs_pack_cid(void)
{
    struct desc_params params;
    struct dwc_ufs_query_upiu *req_upiu;
    void *tmp_ptr;
    void *resp_upiu;
    int ret;
    u8 *p;
    u8 snum_buf[SERIAL_NUM_SIZE];
    int i;

    GET_LOCAL_DWC_HOST();
    /*use the slot 0 default */
    resp_upiu = dwc_host->lrb[0].resp_upiu;
    memset(snum_buf,  0, (unsigned int)sizeof(snum_buf));
    if (dwc_host->manufacturer_id == 0) {
        ret = ufs_get_device_info();
        if (ret) {
            PRINT_ERROR("%s: ufs_get_device_info ret: %d\n",
                        __func__, ret);
            return NULL;
        }
    }

    tmp_ptr = dwc_host->lrb[0].cmd_upiu;
    req_upiu = (struct dwc_ufs_query_upiu *)tmp_ptr;

    /* Read device descriptor to know Base(UNIT desc 0 offset) and
     * Length(UNIT desc length) */
    params.req_upiu = req_upiu;
    params.part_desc = NULL;
    params.opcode = READ_DESC_OPCODE;
    params.desc_idn = STRING_DESC;
    params.desc_index = dwc_host->serial_number;
    params.length = STRING_DESC_LENGTH;
    modify_desc_upiu(&params);
    ret = read_descriptor(req_upiu, &resp_upiu);
    if (ret != UFS_SUCCESS) {
        PRINT_ERROR("%s: read_descriptor fail. ret = %d\n",
                    __func__, ret);
        return NULL;
    }
    p = (u8 *)resp_upiu;
    /* 32B query response head + 2B string descriptor head*/
    p = p + 32 + 2;
    ufs_cid[0] = 0;
    ufs_cid[1] = 0;
    ufs_cid[2] = 0;
    if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_TOSHIBA) {
        /* toshiba: 20 Byte, every two byte has a prefix of 0x00,
        *  trim the 0x00 byte*/
        for (i = 0; i < 10; i++) {
            snum_buf[i] = p[2 * i + 1];
        }
        /*  append two 0x00 byte in the end */
        snum_buf[10] = 0;
        snum_buf[11] = 0;
    } else if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_SUMSANG) {
        /*
        (void)memcpy_s(snum_buf, 12, p, 12);
        */
    } else if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_HYNIX) {
        /*hynix only have 6 Byte, add a 0x00 before every byte*/
        for (i = 0; i < 6; i++) {
            snum_buf[i * 2] = 0x0;
            snum_buf[i * 2 + 1] = p[i];
        }
    } else {
        PRINT_ERROR("%s: unknown manufacturer_id (0x%x)\n",
                    __func__, dwc_host->manufacturer_id);
        return NULL;
    }

    (void)memcpy(ufs_cid,
                 (unsigned int *)snum_buf,
                 (unsigned int)sizeof(snum_buf));
    if (is_little_endian()) {
        for (i = 0; i < 3; i++) {
            little_endian_to_big_endian(&ufs_cid[i]);
        }
        /*
        ufs_cid[3] = (uint32_t)(dwc_host->manufacturer_data) << 16 |
            dwc_host->manufacturer_id;
        */
    } else {
        /*
        ufs_cid[3] = (uint32_t)(dwc_host->manufacturer_id) << 16 |
            dwc_host->manufacturer_data;
        */
    }

    return ufs_cid;
}


int ufs_lu_init(void)
{
    struct partitionDescTable pdt;
    struct partitionDesc partitionDescPtr[UNIT_DESCS_COUNT];
    struct configuration_header config_header;
    int i;
    int ret;

    GET_LOCAL_DWC_HOST();

    ret = ufs_get_device_info();
    if (ret) {
        UFS_PRINT("ufs_get_device_info fail. ret: %d\n", ret);
        return ret;
    }

    memset(&pdt, 0, sizeof(struct partitionDescTable));
    memset(partitionDescPtr, 0,
           sizeof(struct partitionDesc) * UNIT_DESCS_COUNT);
    memset(&config_header, 0,
           sizeof(struct configuration_header));

    pdt.p_conf_header = &config_header;
    for (i = 0; i < UNIT_DESCS_COUNT; i++) {
        pdt.partitionDescPtr[i] = &partitionDescPtr[i];
    }


    /* configuration header */
    pdt.p_conf_header->bBootEnable = 0x1;
    pdt.p_conf_header->bDescrAccessEn = 0x0;
    pdt.p_conf_header->bInitPowerMode = 0x1;
    pdt.p_conf_header->bHighPriorityLUN = 0x7F;
    pdt.p_conf_header->bSecureRemovalType = 0x0;
    pdt.p_conf_header->bInitActiveICCLevel = 0x0;
    pdt.p_conf_header->wPeriodicRTCUpdate = 0x0;

    /* lu 0: boot lu A */
    pdt.partitionDescPtr[0]->bootLunId = WELL_BOOT_LU_A;
    pdt.partitionDescPtr[0]->writeProtect = 0x0;
    /* Enhanced Memory */
    if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_TOSHIBA) {
        pdt.partitionDescPtr[0]->memoryType = 0x4;
    } else {
        pdt.partitionDescPtr[0]->memoryType = 0x3;
    }
    /* 4 MB is the capacity */
    pdt.partitionDescPtr[0]->lu_capacity = 4;
    pdt.partitionDescPtr[0]->dataReliability = 0x1;
    /* 0x0c => 4096 */
    pdt.partitionDescPtr[0]->blockSize = 0x0c;
    /* 0x2 => Thin Provisioning enabled & TPRZ = 0 */
    pdt.partitionDescPtr[0]->provType = 0x2;
    pdt.partitionDescPtr[0]->wContextCapabilities = 0x0;

    /* lu 1: boot lu B */
    pdt.partitionDescPtr[1]->bootLunId = WELL_BOOT_LU_B;
    pdt.partitionDescPtr[1]->writeProtect = 0x0;
    /* Enhanced Memory */
    if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_TOSHIBA) {
        pdt.partitionDescPtr[1]->memoryType = 0x4;
    } else {
        pdt.partitionDescPtr[1]->memoryType = 0x3;
    }
    /* 4 MB is the capacity */
    pdt.partitionDescPtr[1]->lu_capacity = 4;
    pdt.partitionDescPtr[1]->dataReliability = 0x1;
    /* 0x0c => 4096 */
    pdt.partitionDescPtr[1]->blockSize = 0x0c;
    /* 0x2 => Thin Provisioning enabled & TPRZ = 0 */
    pdt.partitionDescPtr[1]->provType = 0x2;
    pdt.partitionDescPtr[1]->wContextCapabilities = 0x0;

    /* lu 2 data lu */
    pdt.partitionDescPtr[2]->bootLunId = 0x0;
    pdt.partitionDescPtr[2]->writeProtect = 0x0;
    /*Enhanced Memory*/
    pdt.partitionDescPtr[2]->memoryType = 0x3;
    pdt.partitionDescPtr[2]->lu_capacity = 8; /* 8MB */
    pdt.partitionDescPtr[2]->dataReliability = 0x1;
    /* 0x0c => 4096 */
    pdt.partitionDescPtr[2]->blockSize = 0x0c;
    /* 0x2 => Thin Provisioning enabled & TPRZ = 0 */
    pdt.partitionDescPtr[2]->provType = 0x2;
    pdt.partitionDescPtr[2]->wContextCapabilities = 0x0;

    /* lu 3 data lu */
    pdt.partitionDescPtr[3]->bootLunId = 0x0;
    pdt.partitionDescPtr[3]->writeProtect = 0x0;
    pdt.partitionDescPtr[3]->memoryType = 0x0;
    /* Normal Memory */
    /* the capacity is MAX */
    pdt.partitionDescPtr[3]->lu_capacity = UFS_MAX_LU_CAP;
    pdt.partitionDescPtr[3]->dataReliability = 0x1;
    /* 0x0c => 4096 */
    pdt.partitionDescPtr[3]->blockSize = 0x0c;
    /* 0x2 => Thin Provisioning enabled & TPRZ = 0 */
    pdt.partitionDescPtr[3]->provType = 0x2;
    pdt.partitionDescPtr[3]->wContextCapabilities = 0x0;

    for (i = 0; i < UNIT_DESCS_COUNT; i++) {
        if (pdt.partitionDescPtr[i]->bootLunId == WELL_BOOT_LU_A) {
            UFS_PRINT("UFS Config Lun(%d) Lu A\n", i);
        } else if (pdt.partitionDescPtr[i]->bootLunId == WELL_BOOT_LU_B) {
            UFS_PRINT("UFS Config Lun(%d) Lu B\n", i);
        }
    }
    ret = ufs_create_partition_inventory(0xf, &pdt);
    if (ret) {
        goto out;
    }

    ret = set_boot_lu_enable();
    if (ret) {
        goto out;
    }

out:

    return ret;
}


int ufs_set_ref_clk(void)
{
    uint32_t value;
    int ret;
    uint32_t target_ref_clk;

    if (IF_FPGA()) {
        target_ref_clk = 1;    /* 26MHz */
    } else {
        target_ref_clk = 0;    /* 19.2MHz */
    }

    ret = read_attribute(B_REFCLK_FREQ, 0, 0, &value);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("read bRefClkFreq fail. ret = %d\n", ret);
        return ret;
    }

    if (target_ref_clk == value) {
        return 0;
    }

    /* set default boot from Boot LU A */
    ret = write_attribute(B_REFCLK_FREQ, 0, 0, &target_ref_clk);
    if (ret) {
        UFS_PRINT("write bRefClkFreq attribute fail. ret = %d\n", ret);
        return ret;
    }

    ret = read_attribute(B_REFCLK_FREQ, 0, 0, &value);
    if (ret != UFS_SUCCESS) {
        UFS_PRINT("read bRefClkFreq fail. ret = %d\n", ret);
        return ret;
    }

    if (target_ref_clk == value) {
        return 0;
    }

    return -1;
}

static int ufs_request_sense(void)
{
    uint8_t *sense_data = NULL;
    int ret;

    GET_LOCAL_DWC_HOST();

    sense_data = (uint8_t *)dwc_host->write_read_buf;
    memset(sense_data, 0, SENSE_DATA_LENGTH);

    ret = do_scsi_cmd(UFS_OP_REQUEST_SENSE, DMA_FROM_DEVICE,
                      (uint64_t)sense_data, (uint64_t)0, SENSE_DATA_LENGTH);
    /* TODO: if read sense data, must do cache invalid */

    return ret;
}

/****************************************************************
 *
 * ufs_set_active_lun
 * Description: Sets the Lun Number for further Transactions
 *
 ***************************************************************/
int ufs_set_active_lun(uint8_t lun)
{
    int ret;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();
    dwc_host->active_lun = lun;
    if (lun >= UNIT_DESCS_COUNT) {
        UFS_PRINT("well known lun: 0x%x\n", lun);

        if (wlun == lun) {
            return UFS_SUCCESS;
        }

        /* issue REQUEST SENSE command once for lu before accessing it
         */
        ret = ufs_request_sense();
        if (ret != 0) {
            UFS_PRINT("send UFS_OP_REQUEST_SENSE error: %d\n", ret);
            FUNC_EXIT();
            return ret;
        }
        UFS_PRINT("send UFS_OP_REQUEST_SENSE success: %d\n", ret);
        wlun = lun;
        return UFS_SUCCESS;
    }

    if (dwc_host->lu_request_sense_sent[lun]) {
        return UFS_SUCCESS;
    }

    /* issue REQUEST SENSE command once for lu before accessing it */
    ret = ufs_request_sense();
    if (ret != 0) {
        UFS_PRINT("send UFS_OP_REQUEST_SENSE error: %d\n", ret);
        FUNC_EXIT();
        return ret;
    }
    dwc_host->lu_request_sense_sent[lun] = 1;
    FUNC_EXIT();
    return ret;
}


/***************************************************************
 *
 * ufs_write_storage
 * Description: Writes the content of the source Address to
 *              destination offset of the active lun.
 *              The APi assumes the data buffes if unaligned have
 *              valid data above the start address
 *
 ****************************************************************/
int ufs_write_storage(uint64_t src_addr, uint64_t dest_offset, uint32_t size)
{
    int ret;
    uint32_t len;
    uint64_t src_addr_tmp = src_addr;
    uint32_t size_tmp = size;
    uint32_t rate, currate;
    uint32_t maxsize = PRDT_BUFFER_SIZE * DWC_UFSHCD_MAX_PRD_SIZE;

    FUNC_ENTER();
    rate = size / maxsize;
    if (size % maxsize) {
        rate++;
    }
    currate = 0;
    memcpy_pc_2_sram(src_addr, src_addr, size);
    while (size_tmp) {
        if (size_tmp < maxsize) {
            len = size_tmp;
        } else {
            len = maxsize;
        }
        /* Send Write 10 Command and handle its completion */
        ret = do_scsi_cmd(UFS_OP_WRITE_10, DMA_TO_DEVICE,
                          src_addr_tmp, dest_offset, len);
        if (ret != 0) {
            UFS_PRINT("send WRITE_10 error: %d\n", ret);
            FUNC_EXIT();
            return ret;
        }
        size_tmp -= len;
        src_addr_tmp += len;
        dest_offset += len;
        currate++;
        /*UFS_PRINT(" write[%d/%d]\n",currate,rate);*/
    }
    FUNC_EXIT();
    /*  UFS_PRINT("ufs write addr:%#x size:%#x ok\n",src_addr,size);*/
    return UFS_SUCCESS;
}

int ufs_write_boot_storage(uint64_t dest_addr,
                           uint64_t src_offset, uint32_t size)
{
    int ret = -1;
    uint8_t prevlun = DEFAULT_BOOT_LUN;
    /*
        uint32_t len;
        uint64_t dest_addr_tmp = dest_addr;
        uint32_t size_tmp = size;
        uint32_t rate, currate;
        uint32_t maxsize = (PRDT_BUFFER_SIZE * DWC_UFSHCD_MAX_PRD_SIZE);
    */
    FUNC_ENTER();
    GET_LOCAL_DWC_HOST();

    if (dwc_host->active_lun != DEFAULT_BOOT_LUN) {
        prevlun = dwc_host->active_lun;
        ret = ufs_set_active_lun(DEFAULT_BOOT_LUN);
        if (ret) {
            FUNC_EXIT();
            return ret;
        }
    }

    ret = ufs_write_storage(dest_addr, src_offset, size);
    if (ret != 0) {
        FUNC_EXIT();
        return ret;
    }

    if (prevlun != DEFAULT_BOOT_LUN) {
        ret = ufs_set_active_lun(prevlun);
        if (ret) {
            FUNC_EXIT();
            return ret;
        }
    }

    return UFS_SUCCESS;
}

int ufs_read_boot_storage(uint64_t dest_addr,
                          uint64_t src_offset, uint32_t size)
{
    int ret = -1;
    uint8_t prevlun;
    uint32_t len;
    uint64_t dest_addr_tmp = dest_addr;
    uint32_t size_tmp = size;
    uint32_t rate, currate;
    uint32_t maxsize = (PRDT_BUFFER_SIZE * DWC_UFSHCD_MAX_PRD_SIZE);

    FUNC_ENTER();
    GET_LOCAL_DWC_HOST();
    prevlun = dwc_host->active_lun;

    ret = ufs_set_active_lun(0xb0);
    if (ret) {
        return -1;
    }

    rate = size / maxsize;
    if (size % maxsize) {
        rate++;
    }
    currate = 0;
    while (size_tmp) {
        if (size_tmp < maxsize) {
            len = size_tmp;
        } else {
            len = maxsize;
        }
        /* Send Read 10 Command and handle its completion */
        ret = do_scsi_cmd(UFS_OP_READ_10, DMA_FROM_DEVICE,
                          dest_addr_tmp, src_offset, len);
        if (ret != UFS_SUCCESS) {
            UFS_PRINT("send READ_10 error: %d\n", ret);
            FUNC_EXIT();
            return ret;
        }
        size_tmp -= len;
        dest_addr_tmp += len;
        src_offset += len;
        currate++;
        /*UFS_PRINT(" read[%d/%d]\n",currate,rate);*/
    }
    ret = ufs_set_active_lun(prevlun);
    FUNC_EXIT();
    /*  UFS_PRINT("ufs read addr:%#x size:%#x ok\n",
            (uint32_t)dest_addr,size);*/
    return ret;
}

int ufs_hibernate_enter(int psw)
{
    unsigned int getvalue;
    unsigned int getvalue1 = 0;
    unsigned int getvalue2 = 0;
    unsigned int getvalue3 = 0;
    unsigned int getvalue4 = 0;
    int index = find_device_index();
    uint32_t retry = 500;
#if 0
    send_uic_command(0x02, 0x00760000, 0x0, 0x28);
    send_uic_command(0x02, 0x00760001, 0x0, 0x28);
    send_uic_command(DME_SET, 0xd0850000, 0x0, 0x1); /*update*/

    getvalue = dwc_ufs_read_reg(UFS_UTRLDBR_OFF);
    if (getvalue != 0) {
        PRINT_ERROR("uic_hibernate_enter: "
                    "UTRLDBR is not ZERO : 0x%x\n", getvalue);
        return UFS_ERROR;
    }
#endif
    /*read clean registers*/
    ufs_reg_read_clean();

    g_h8_cnt[index] += 1;

#if !defined(COMBO_PHY_V120)
    if (g_rx_lane_num[index] == 2) {
        send_uic_command(0x02, 0x00C30005, 0x0, 0x1);
    }

    send_uic_command(0x02, 0x00C30004, 0x0, 0x1);
    send_uic_command(0x02, 0xd0850000, 0x0, 0x1);
#endif
    send_uic_command(DME_HIBERNATE_ENTER, 0, 0, 0);
    /* 6. UIC Hibernate Enter Status (UHES) */
    while (retry--) {
        if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UHES_BIT) {
            break;
        }
        ufs_waitms(1);
    }

    if (0xFFFFFFFF == retry) {
        PRINT_ERROR("UHES wait timeout, total cnt is %d\n",
                    g_h8_cnt[index]);
        ufshci_dump();
        ufs_phy_reg_dump();
        ufs_dme_reg_dump();
        return UFS_ERROR;
    }

    /* clear interrupt status */
    dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UHES_BIT);

    /* 7. check the UPMCRS */
    getvalue = dwc_ufs_read_reg(UFS_HCS_OFF);
    getvalue >>= 8;
    getvalue &= 7;
    /* PWR_LOCAL is set */
    if (getvalue == 1) {
        /* PRINT_ERROR("HIBERNATE ENTER success\n"); */

        getvalue1 = uic_cmd_read(DME_GET, 0x00410000);
        if (g_tx_lane_num[index] == 2) {
            getvalue2 = uic_cmd_read(DME_GET, 0x00410001);
        }

        getvalue3 = uic_cmd_read(DME_GET, 0x00C10004);
        if (g_tx_lane_num[index] == 2) {
            getvalue4 = uic_cmd_read(DME_GET, 0x00C10005);
        }

        if (g_tx_lane_num[index] == 2) {
            if (getvalue1 != 1 || getvalue2 != 1 ||
                    getvalue3 != 1 || getvalue4 != 1) {
                UFS_PRINT("H8 Enter Error 0x41 lane0 0x%x , "
                          "0x41 lane1:0x%x, 0xc1 lane0 = 0x%x,"
                          "0xc1 lane1 = 0x%x\n",
                          getvalue1, getvalue2,
                          getvalue3, getvalue4);
                UFS_PRINT("H8 Enter Error 0xFF lane0 0x%x , "
                          "0xFF lane1 0x%x, 0xA7 Lane0 = 0x%x,"
                          "0xA7 Lane1 = 0x%x \n",
                          uic_cmd_read(DME_GET, 0x00FF0004),
                          uic_cmd_read(DME_GET, 0x00FF0005),
                          uic_cmd_read(DME_GET, 0x00A70004),
                          uic_cmd_read(DME_GET, 0x00A70005));
                UFS_PRINT("H8 Enter Error 0xCE lane0 0x%x , "
                          "0xCE lane1 0x%x\n",
                          uic_cmd_read(DME_GET, 0x00CE0004),
                          uic_cmd_read(DME_GET, 0x00CE0005));
            }
        }   else {
            if (getvalue1 != 1 || getvalue3 != 1) {
                UFS_PRINT("H8 Enter Error 0x41 lane0 0x%x , "
                          "0xc1 lane0 0x%x\n",
                          getvalue1, getvalue3);
                UFS_PRINT("H8 Enter Error 0xFF lane0 0x%x , "
                          "0xA7 Lane0 0x%x\n",
                          uic_cmd_read(DME_GET, 0x00FF0004),
                          uic_cmd_read(DME_GET, 0x00A70004));
                UFS_PRINT("H8 Enter Error :"
                          "0xCE lane0 = 0x%x\n",
                          uic_cmd_read(DME_GET, 0x00CE0004));
            }
        }

    } else {
        PRINT_ERROR("ENTER, UPMCRS isn't PWR_LOCAL, it's %d, "
                    "total cnt is %d\n",
                    getvalue, g_h8_cnt[index]);
        ufs_phy_reg_dump();
        return UFS_ERROR;
    }

    ufs_phy_reg_dump();
    return UFS_OK;
}

int ufs_hibernate_exit(int psw)
{
    int ret = 0;
    unsigned int getvalue1;
    unsigned int getvalue2;
    unsigned int getvalue3;
    unsigned int getvalue4;
    uint32_t retry;
    int index = find_device_index();

    getvalue1 = uic_cmd_read(DME_GET, 0x00410000);
    getvalue2 = uic_cmd_read(DME_GET, 0x00C10004);

    if (g_tx_lane_num[index] == 2) {
        getvalue3 = uic_cmd_read(DME_GET, 0x00410001);
        if (getvalue3 != 1) {
            PRINT_ERROR("H8 not actually enter success, "
                        "getvalue3 is %d, total cnt is %d\n",
                        getvalue3, g_h8_cnt[index]);
            ufs_phy_reg_dump();
            return UFS_ERROR;
        }
    }
    /* some single-leg brothers can work well */
    if (g_rx_lane_num[index] == 2) {
        getvalue4 = uic_cmd_read(DME_GET, 0x00C10005);
        if (getvalue4 != 1) {
            PRINT_ERROR("H8 not actually enter success, "
                        "getvalue4 is %d, total cnt is %d\n",
                        getvalue4, g_h8_cnt[index]);
            ufs_phy_reg_dump();
            return UFS_ERROR;
        }
    }

    if (1 != getvalue1 || 1 != getvalue2) {
        PRINT_ERROR("H8 not actually enter success, getvalue1 is %d,"
                    "getvalue2 is %d, total cnt is %d\n",
                    getvalue1, getvalue2, g_h8_cnt[index]);
        ufs_phy_reg_dump();
        return UFS_ERROR;
    }


    /*DL_ReInitCount*/
    send_uic_command(DME_SET, 0x21000000, 0x0, 0x0);
    /*VS_DebugCounterControl*/
    send_uic_command(DME_SET, 0xd09c0000, 0x0, 0xf);

    /*read clean registers*/
    ufs_reg_read_clean();

#if !defined(COMBO_PHY_V120)
    /* lane0 go to exit H8 first, so let the lane1 go first, have a try */
    if (g_rx_lane_num[index] == 2) {
        send_uic_command(0x02, 0x00C30005, 0x0, 0x0);
    }

    send_uic_command(0x02, 0x00C30004, 0x0, 0x0);
    send_uic_command(0x02, 0xd0850000, 0x0, 0x1);
#endif

    /* don't add anything here, or the glitch will
        have enough time to get in */
    /* 9. UIC Hibernate Exit */
    //ufshci_dump();
    send_uic_command(DME_HIBERNATE_EXIT, 0, 0, 0);

    /* 10. Polling IS.UHXS */
    retry = 500;
    while (retry--) {
        if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UHXS_BIT) {
            UFS_PRINT("\tUFS_IS_UHXS_BIT active\n");
            break;
        }
        ufs_waitms(1);
    }
    UFS_PRINT("IS reg= %#x\n\n", dwc_ufs_read_reg(UFS_IS_OFF));
    if (0xFFFFFFFF == retry) {
        PRINT_ERROR("UHXS wait timeout, total cnt is %d\n",
                    g_h8_cnt[index]);
        ufs_phy_reg_dump();
        ufs_dme_reg_dump();
        return UFS_ERROR;
    }

    /* clear interrupt status */
    dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UHXS_BIT);

    /* 11. check the UPMCRS */
    getvalue1 = dwc_ufs_read_reg(UFS_HCS_OFF);
    getvalue1 >>= 8;
    getvalue1 &= 7;
    /* PWR_LOCAL is set */
    if (getvalue1 == 1) {
        /* PRINT_ERROR("HIBERNATE EXIT success\n"); */
    } else {
        PRINT_ERROR("EXIT, UPMCRS isn't PWR_LOCAL, it's %u, "
                    "total cnt is %u\n", getvalue1, g_h8_cnt[index]);
        /* maybe caused by the gitch */
        if ((getvalue1 == 2) && (0 == dwc_ufs_read_reg(UFS_UECDL_OFF))) {
            return UFS_GLITCH_BYPASS;
        }
        ufs_phy_reg_dump();
        ufs_dme_reg_dump();
        return UFS_ERROR;
    }
    ufs_phy_reg_dump();
    return ret;
}

/********************************************************************
 *
 * ufs_read_storage
 * Description: Reads the content of the source offset of active lun
 *              and copies the content to dest_addr.
 *              The API assumes there is enough memory allocated and
 *              available above and below start address for unaligned
 *              and multi block access
 ********************************************************************/
int ufs_read_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size)
{
    int ret = -1;
    uint32_t len;
    uint64_t dest_addr_tmp = dest_addr;
    uint32_t size_tmp = size;
    uint32_t rate, currate;
    uint32_t maxsize = (PRDT_BUFFER_SIZE * DWC_UFSHCD_MAX_PRD_SIZE);

    FUNC_ENTER();

    rate = size / maxsize;
    if (size % maxsize) {
        rate++;
    }
    currate = 0;
    memcpy_sram_2_pc(dest_addr, dest_addr, size);
    while (size_tmp) {
        if (size_tmp < maxsize) {
            len = size_tmp;
        } else {
            len = maxsize;
        }
        /* Send Read 10 Command and handle its completion */
        ret = do_scsi_cmd(UFS_OP_READ_10, DMA_FROM_DEVICE,
                          dest_addr_tmp, src_offset, len);
        if (ret != UFS_SUCCESS) {
            UFS_PRINT("send READ_10 error: %d\n", ret);
            FUNC_EXIT();
            return ret;
        }
        size_tmp -= len;
        dest_addr_tmp += len;
        src_offset += len;
        currate++;
        /*UFS_PRINT(" read[%d/%d]\n",currate,rate);*/
    }
    memcpy_sram_2_pc(dest_addr, dest_addr, size);
    FUNC_EXIT();
    /*  UFS_PRINT("ufs read addr:%#x size:%#x ok\n",dest_addr,size); */
    return ret;
}

/***************************************************************
 * do_flag_operation
 * Description: The function can be used for any operation on flags
        1. fills the query upiu memory content
        2. Handles the response of query command sent
        3. updates the flag return value
 ***************************************************************/
static int do_flag_operation(int opcode,
                             int query_func,
                             enum flags_id idn,
                             uint8_t *flags_ret)
{
    int ret, i;
    uint8_t val[4];
    uint8_t free_slot;

    GET_LOCAL_DWC_HOST();

    FUNC_ENTER();
    for (i = 0; i < 4; i++) {
        val[i] = 0x00;
    }

    free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
    if (free_slot == BAD_SLOT) {
        return UFS_ERROR;
    }

    create_query_upiu((uint8_t)opcode, (uint8_t)query_func, 0, 0,
                      (uint8_t)idn, val, free_slot);

    ret = wait_for_cmd_completion(BIT(free_slot));
    if (ret != UFS_SUCCESS) {
        FUNC_EXIT();
        return ret;
    }

    ret = handle_query_response(val, free_slot);
    *flags_ret = val[0];
    FUNC_EXIT();
    return ret;
}



/***************************************************************
 *
 * ufs_set_flag
 * Description: The function invokes do_flag_operation for set flag
 *              operation
 ***************************************************************/
int ufs_set_flag(enum flags_id idn, uint8_t *flags_ret)
{
    int ret;

    FUNC_ENTER();
    ret =
        do_flag_operation(SET_FLAG_OPCODE, STANDARD_WR_REQ, idn, flags_ret);
    FUNC_EXIT();
    return ret;
}


/***************************************************************
 *
 * modify_desc_upiu
 * Description: The function performs the following
 *            1.Fills the request upiu for read/write desc operation
 *            2.Updates the Data Memory below the request UPIU
 *
 ***************************************************************/
void modify_desc_upiu(const struct desc_params *params)
{
    uint8_t i;
    uint8_t *data;
    uint8_t len, offset;
    struct partitionDesc **desc;
    struct dwc_ufs_query_upiu *upiu_ptr =
        (struct dwc_ufs_query_upiu *)params->req_upiu;

    GET_LOCAL_DWC_HOST();
    FUNC_ENTER();

    /* Command Descriptor Programming */
    upiu_ptr->trans_type = 0x16;
    upiu_ptr->flags = UPIU_CMD_FLAGS_NONE;
    upiu_ptr->reserved_1 = 0x00;
    upiu_ptr->task_tag = 0x01;
    upiu_ptr->reserved_2 = 0x00;

    if (params->opcode == READ_DESC_OPCODE) {
        upiu_ptr->query_func = STANDARD_RD_REQ;
    } else {
        upiu_ptr->query_func = STANDARD_WR_REQ;
    }

    upiu_ptr->query_resp = 0x00;
    upiu_ptr->reserved_3 = 0x00;
    upiu_ptr->tot_ehs_len = 0x00;
    if (params->opcode == READ_DESC_OPCODE) {
        upiu_ptr->data_seg_len = 0x00;
    } else {
        upiu_ptr->data_seg_len = (to_bigendian16(params->length));
    }

    upiu_ptr->tsf[0] = params->opcode;
    upiu_ptr->tsf[1] = params->desc_idn;
    upiu_ptr->tsf[2] = params->desc_index; /* index */
    upiu_ptr->tsf[3] = 0x0; /* selector */
    upiu_ptr->tsf[4] = 0x0;
    upiu_ptr->tsf[5] = 0x0;
    upiu_ptr->tsf[6] = (uint8_t)(params->length >> 8);
    upiu_ptr->tsf[7] = params->length & 0xff;

    for (i = 8; i < 15; i++) {
        upiu_ptr->tsf[i] = 0x00;
    }

    upiu_ptr->reserved_5 = 0x0;

    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(upiu_ptr),
                     (char *)upiu_ptr,
                     sizeof(struct dwc_ufs_query_upiu));

    /* Populate the data segment with length bytes
        for the configuration desc only*/
    len = dwc_host->unit_length;
    offset = dwc_host->unit_offset;
    desc = params->part_desc;
    if (params->opcode == WRITE_DESC_OPCODE) {
        if (params->desc_idn == CONFIGURATION_DESC) {
            data = (uint8_t *)(upiu_ptr + 1);
            /* boot enable */
            data[0x3] = params->conf_head->bBootEnable;
            data[0x4] = params->conf_head->bDescrAccessEn;
            data[0x5] = params->conf_head->bInitPowerMode;
            data[0x6] = params->conf_head->bHighPriorityLUN;
            data[0x7] = params->conf_head->bSecureRemovalType;
            data[0x8] = params->conf_head->bInitActiveICCLevel;
            data[0x9] = (uint8_t)
                        (((params->conf_head->wPeriodicRTCUpdate) &
                          0xff00) >> 8);
            data[0xA] = (uint8_t)
                        ((params->conf_head->wPeriodicRTCUpdate) &
                         0xff);
            for (i = 0; i < UNIT_DESCS_COUNT; i++) {
                if (desc[i] == NULL) {
                    /* Disable the Lun */
                    data[(len * i) + offset] = 0x0;
                    continue;
                }
                data[(len * i) + offset] = 0x1;
                data[(len * i) + offset + 0x1] =
                    desc[i]->bootLunId;
                data[(len * i) + offset + 0x2] =
                    desc[i]->writeProtect;
                data[(len * i) + offset + 0x3] =
                    desc[i]->memoryType;
                data[(len * i) + offset + 0x4] = (uint8_t)
                                                 (((desc[i]->dNumAllocUnits) &
                                                   0xff000000) >> 24);
                data[(len * i) + offset + 0x5] = (uint8_t)
                                                 (((desc[i]->dNumAllocUnits) &
                                                   0xff0000) >> 16);
                data[(len * i) + offset + 0x6] = (uint8_t)
                                                 (((desc[i]->dNumAllocUnits) &
                                                   0xff00) >> 8);
                data[(len * i) + offset + 0x7] = (uint8_t)
                                                 ((desc[i]->dNumAllocUnits) & 0xff);
                data[(len * i) + offset + 0x8] =
                    desc[i]->dataReliability;
                data[(len * i) + offset + 0x9] =
                    desc[i]->blockSize;
                data[(len * i) + offset + 0xa] =
                    desc[i]->provType;
                data[(len * i) + offset + 0xb] = (uint8_t)
                                                 ((desc[i]->wContextCapabilities) >> 8);
                data[(len * i) + offset + 0xc] = (uint8_t)
                                                 ((desc[i]->wContextCapabilities) & 0xFF);
            }

            /* copy the PC memory to sram */
            memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(data),
                             (char *)data,
                             (len * UNIT_DESCS_COUNT + offset));
        }
    }

    FUNC_EXIT();
}



/***************************************************************
 *
 * read_descriptor
 * Description: The functon populates the request upiu structure
 *      with upiu info passed in 1st argument
 *
 ***************************************************************/
int read_descriptor(const void *req_upiu, void **resp_upiu_out)
{
    int ret;
#ifdef READ_DESCRIPTOR_DEBUG
    int i;
    uint8_t *ptr;
#endif
    struct dwc_ufs_utrd *utrd;
    struct dwc_ufs_resp_upiu *resp_upiu;
    uint8_t free_slot;

    GET_LOCAL_DWC_HOST();
    free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
    if (free_slot == BAD_SLOT) {
        return UFS_ERROR;
    }
    utrd = dwc_host->lrb[free_slot].utrd;
    resp_upiu = dwc_host->lrb[free_slot].resp_upiu;
    FUNC_ENTER();

    /* UTRD Descriptor Programming for processing command */
    utrd->ct_and_flags =
        (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
    utrd->resp_upiu_length =
        to_littleendian16((uint16_t)
                          (sizeof(struct dwc_ufs_query_upiu) >> 2));
    utrd->prdt_length = 0;

    create_desc_upiu(req_upiu, free_slot);

    /* copy the PC memory to sram */
    memcpy_pc_2_sram((char *)ADDR_MAP_PC_2_SRAM(utrd),
                     (char *)utrd, sizeof(struct dwc_ufs_utrd));

    ret = wait_for_cmd_completion(BIT(free_slot));
    if (ret != UFS_SUCCESS) {
        FUNC_EXIT();
        return ret;
    }

    /* copy the sram to PC memory */
    memcpy_sram_2_pc((char *)resp_upiu,
                     (char *)ADDR_MAP_PC_2_SRAM(resp_upiu), 0x10 + 8 * 16);

    *((uint8_t **)resp_upiu_out) = (uint8_t *)(void *)resp_upiu;
#ifdef READ_DESCRIPTOR_DEBUG
    ptr = (uint8_t *)resp_upiu;
    UFS_PRINT("The data segment of length %d is\n",
              DWC_UCD_ALIGN - sizeof(struct dwc_ufs_query_upiu));
    for (i = 32; i < DWC_UCD_ALIGN; i = i + 4)
        UFS_PRINT("0x%x 0x%x 0x%x 0x%x\n",
                  ptr[i], ptr[1 + i], ptr[i + 2], ptr[i + 3]);
#endif

    ret = handle_query_response(NULL, free_slot);
    FUNC_EXIT();
    return ret;
}


/***************************************************************
 *
 * ufs_read_flag
 * Description: The function invokes do_flag_operation for Read
 *               flag operation
 *
 ***************************************************************/
int ufs_read_flag(enum flags_id idn, uint8_t *flags_ret)
{
    int ret;

    FUNC_ENTER();
    ret = do_flag_operation(READ_FLAG_OPCODE, STANDARD_RD_REQ, idn,
                            flags_ret);
    FUNC_EXIT();
    return ret;
}




/***************************************************************
 *
 * do_mode_change
 * Description: The function issues the the powermode change to
 *              UFS device to work using RX and Tx lanes and Gears
 *              as provided in pwrModeParams structure.
 *
 ****************************************************************/
int do_mode_change(const struct pwrModeParams *pmp, uint8_t gear,
                   uint8_t rate, int scramble, int termination)
{
    FUNC_ENTER();

    /* PA_TxSkip */
    send_uic_command(DME_SET, 0x155c0000, 0x0, 0x0);
    /* PA_TxGear */
    send_uic_command(DME_SET, 0x15680000, 0x0, pmp->txGear);
    /* PA_RxGear */
    send_uic_command(DME_SET, 0x15830000, 0x0, pmp->rxGear);

    if (pmp->pwrMode == FAST_MODE ||
            pmp->pwrMode == FASTAUTO_MODE) {
        /* PA_HSSeries */
        send_uic_command(DME_SET, 0x156a0000, 0x0, pmp->hsSeries);
        if (termination) {
            /* PA_TxTermination */
            send_uic_command(DME_SET, 0x15690000, 0x0, 0x1);
            /* PA_RxTermination */
            send_uic_command(DME_SET, 0x15840000, 0x0, 0x1);
        } else {
            /* PA_TxTermination */
            send_uic_command(DME_SET, 0x15690000, 0x0, 0x0);
            /* PA_RxTermination */
            send_uic_command(DME_SET, 0x15840000, 0x0, 0x0);
        }
        if (scramble) {
            /* PA_Scrambling */
            send_uic_command(DME_SET, 0x15850000, 0x0, 0x1);
        } else {
            /* PA_Scrambling */
            send_uic_command(DME_SET, 0x15850000, 0x0, 0x0);
        }
    } else if (pmp->pwrMode == SLOW_MODE ||
               pmp->pwrMode == SLOWAUTO_MODE) {
        send_uic_command(DME_SET, 0x15690000, 0x0, 0x0);
        send_uic_command(DME_SET, 0x15840000, 0x0, 0x0);
        /* PA_Scrambling */
        send_uic_command(DME_SET, 0x15850000, 0x0, 0x0);
    }
    /* PA_ActiveTxDataLanes */
    send_uic_command(DME_SET, 0x15600000, 0x0, pmp->txLanes);
    /* PA_ActiveRxDataLanes */
    send_uic_command(DME_SET, 0x15800000, 0x0, pmp->rxLanes);

    /*PA_PWRModeUserData0 = 8191, default is 0*/
    send_uic_command(DME_SET, 0x15b00000, 0x0, 8191);
    /*PA_PWRModeUserData1 = 65535, default is 0*/
    send_uic_command(DME_SET, 0x15b10000, 0x0, 65535);
    /*PA_PWRModeUserData2 = 32767, default is 0*/
    send_uic_command(DME_SET, 0x15b20000, 0x0, 32767);
    /*DME_FC0ProtectionTimeOutVal = 8191, default is 0*/
    send_uic_command(DME_SET, 0xd0410000, 0x0, 8191);
    /*DME_TC0ReplayTimeOutVal = 65535, default is 0*/
    send_uic_command(DME_SET, 0xd0420000, 0x0, 65535);
    /*DME_AFC0ReqTimeOutVal = 32767, default is 0*/
    send_uic_command(DME_SET, 0xd0430000, 0x0, 32767);

    /*PA_PWRModeUserData3 = 8191, default is 0*/
    send_uic_command(DME_SET, 0x15b30000, 0x0, 8191);
    /*PA_PWRModeUserData4 = 65535, default is 0*/
    send_uic_command(DME_SET, 0x15b40000, 0x0, 65535);
    /*PA_PWRModeUserData5 = 32767, default is 0*/
    send_uic_command(DME_SET, 0x15b50000, 0x0, 32767);
    /*DME_FC1ProtectionTimeOutVal = 8191, default is 0*/
    send_uic_command(DME_SET, 0xd0440000, 0x0, 8191);
    /*DME_TC1ReplayTimeOutVal = 65535, default is 0*/
    send_uic_command(DME_SET, 0xd0450000, 0x0, 65535);
    /*DME_AFC1ReqTimeOutVal = 32767, default is 0*/
    send_uic_command(DME_SET, 0xd0460000, 0x0, 32767);

    /*VS_DebugCounter0Mask*/
    send_uic_command(DME_SET, 0xd09a0000, 0x0, 0x80000000);

    /*VS_DebugCounter1Mask*/
    send_uic_command(DME_SET, 0xd09b0000, 0x0, 0x78000000);
    /* PA_PWRMode */
    send_uic_command(DME_SET, 0x15710000, 0x0, pmp->pwrMode);

    FUNC_EXIT();
    return 0;
}

void adapt_pll_to_power_mode(enum POWER_MODE pwrmode,
                             uint8_t gear, uint8_t rate)
{
#ifdef COMBO_PHY_V100
    uint32_t value;

    if (FAST_MODE == pwrmode || SLOW_MODE == pwrmode)
        /*don't change PLL in fast and slow mode*/
    {
        return 0;
    }
#endif

#ifdef COMBO_PHY_V100
    /*Note that CB registers for PLL can only be
    set at SAVE (Stall/Sleep) state*/
    while (1) {
        value = uic_cmd_read(0x1, 0x00410000);
        PRINT_ERROR("value is %d\n", value);
        if ((value == 3) || (2 == value)) {
            break;
        }
    }
#endif

    if (FAST_MODE == pwrmode || FASTAUTO_MODE == pwrmode) {
        if (gear == 1) {
            if (rate == 1) {
#ifdef COMBO_PHY_V100
                /* config the PLL to the related gear-rate */
                send_uic_command(DME_SET, 0xc30000, 0x0, 0x20);
                send_uic_command(DME_SET, 0xc40000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xc90000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xd00000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xce0000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_TXHSGR), 0x0, 0x02);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_RXHSGR), 0x0, 0x02);
#endif
            } else if (rate == 2) {
#ifdef COMBO_PHY_V100
                /* config the PLL to the related gear-rate */
                send_uic_command(DME_SET, 0xc30000, 0x0, 0x13);
                send_uic_command(DME_SET, 0xc40000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xc90000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xd00000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xce0000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_PRE_DIV), 0x0, 0x0);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_SWC_EN), 0x0, 0x0);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_FBK_S), 0x0, 0x01);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_FBK_P), 0x0, 0x4c);

                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_TXHSGR), 0x0, 0x02);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_RXHSGR), 0x0, 0x02);
#endif
            }

        } else if (gear == 2) {
            if (rate == 1) {
#ifdef COMBO_PHY_V100
                /* config the PLL to the related gear-rate */
                send_uic_command(DME_SET, 0xc30000, 0x0, 0x20);
                send_uic_command(DME_SET, 0xc40000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xc90000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xd00000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xce0000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_TXHSGR), 0x0, 0x01);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_RXHSGR), 0x0, 0x01);
#endif
            } else if (rate == 2) {
#ifdef COMBO_PHY_V100
                /* config the PLL to the related gear-rate */
                send_uic_command(DME_SET, 0xc30000, 0x0, 0x26);
                send_uic_command(DME_SET, 0xc40000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xc90000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xd00000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xce0000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_TXHSGR), 0x0, 0x01);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_RXHSGR), 0x0, 0x01);
#endif
            }

        } else if (gear == 3) {
            if (rate == 1) {
#ifdef COMBO_PHY_V100
                /* config the PLL to the related gear-rate */
                send_uic_command(DME_SET, 0xc30000, 0x0, 0x41);
                send_uic_command(DME_SET, 0xc40000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xc90000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xd00000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xce0000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_TXHSGR), 0x0, 0x0);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_RXHSGR), 0x0, 0x0);
#endif
            } else if (rate == 2) {
#ifdef COMBO_PHY_V100
                /* config the PLL to the related gear-rate */
                send_uic_command(DME_SET, 0xc30000, 0x0, 0x4c);
                send_uic_command(DME_SET, 0xc40000, 0x0, 0x01);
                send_uic_command(DME_SET, 0xc90000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xd00000, 0x0, 0x0);
                send_uic_command(DME_SET, 0xce0000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_TXHSGR), 0x0, 0x0);
                send_uic_command(DME_SET,
                                 ATTR_MCB(RG_PLL_RXHSGR), 0x0, 0x0);
#endif
            }

        }
#ifdef COMBO_PHY_V100
        /* config the common register after the PLL configuration */
        /* lcc disable in phy */
        send_uic_command(DME_SET, 0x002c0000, 0x0, 0x0);
        /*READ_ONLY_MIB_ATTRIBUTE*/
        send_uic_command(DME_SET, 0x00210000, 0x0, 0x02);
        /*READ_ONLY_MIB_ATTRIBUTE*/
        send_uic_command(DME_SET, 0x80210000, 0x0, 0x02);
        /* TX_MIN_ACTIVATETIME */
        send_uic_command(DME_SET, 0x00330000, 0x0, 0x01);
        /* TX_PHY_CONFIG I */
        send_uic_command(DME_SET, 0x00710000, 0x0, 0x0c);
        /* TX_AMPLITUDE */
        send_uic_command(DME_SET, 0x007F0000, 0x0, 0x0d);
#endif
    }

    /*the PWM's clk is been derived from the pll above*/
    if (SLOW_MODE == pwrmode || SLOWAUTO_MODE == pwrmode) {
        /*base on the HS-Gear-1-RateB*/
#ifdef COMBO_PHY_V100
        /* config the PLL to the related gear-rate */
        send_uic_command(DME_SET, 0x00c30000, 0x0, 0x13);
        send_uic_command(DME_SET, 0x00c40000, 0x0, 0x01);
        send_uic_command(DME_SET, 0x00c90000, 0x0, 0x0);
        send_uic_command(DME_SET, 0x00d00000, 0x0, 0x0);
        send_uic_command(DME_SET, 0x00ce0000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110)
        /* no matter which HS's PLL will be based,
        the PWM's divide is the same */
#endif

        if (gear == 1) {
#ifdef COMBO_PHY_V100
            /*RG_TX_PWM_DIVP*/
            send_uic_command(DME_SET, 0x00c10000, 0x0, 0x1a);
            /*RG_RXPWMDIV*/
            send_uic_command(DME_SET, 0x00d30000, 0x0, 0x04);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_TXLSGR), 0x0, 0x07);
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_RXLSGR), 0x0, 0x06);
#else
            COMPILE_ERROR;
#endif
        } else if (gear == 2) {
#ifdef COMBO_PHY_V100
            send_uic_command(DME_SET, 0x00c10000, 0x0, 0x0d);
            send_uic_command(DME_SET, 0x00d30000, 0x0, 0x03);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_TXLSGR), 0x0, 0x06);
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_RXLSGR), 0x0, 0x05);
#else
            COMPILE_ERROR;
#endif
        } else if (gear == 3) {
#ifdef COMBO_PHY_V100
            send_uic_command(DME_SET, 0x00c10000, 0x0, 0x07);
            send_uic_command(DME_SET, 0x00d30000, 0x0, 0x02);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_TXLSGR), 0x0, 0x05);
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_RXLSGR), 0x0, 0x04);
#else
            COMPILE_ERROR;
#endif
        } else if (gear == 4) {
#ifdef COMBO_PHY_V100
            send_uic_command(DME_SET, 0x00c10000, 0x0, 0x04);
            send_uic_command(DME_SET, 0x00d30000, 0x0, 0x01);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_TXLSGR), 0x0, 0x04);
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_RXLSGR), 0x0, 0x03);
#else
            COMPILE_ERROR;
#endif
        } else if (gear == 5) {
#ifdef COMBO_PHY_V100
            /*RG_TX_PWM_DIVP*/
            send_uic_command(DME_SET, 0x00c10000, 0x0, 0x02);
            /*RG_RXPWMDIV*/
            send_uic_command(DME_SET, 0x00d30000, 0x0, 0x0);
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_TXLSGR), 0x0, 0x03);
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_RXLSGR), 0x0, 0x02);
#else
            COMPILE_ERROR;
#endif
        } else if (gear == 6) {
#ifdef COMBO_PHY_V100
            PRINT_ERROR("only support gear-5 in COMBO_PHY_V100\n");
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_TXLSGR), 0x0, 0x02);
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_RXLSGR), 0x0, 0x01);
#else
            COMPILE_ERROR;
#endif
        } else if (gear == 7) {
#ifdef COMBO_PHY_V100
            PRINT_ERROR("only support gear-5 in COMBO_PHY_V100\n");
#elif defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_TXLSGR), 0x0, 0x01);
            send_uic_command(DME_SET,
                             ATTR_MCB(RG_PLL_RXLSGR), 0x0, 0x0);
#else
            COMPILE_ERROR;
#endif
        }
    }
#ifdef COMBO_PHY_V100
    /* just for test begin */
    PRINT_ERROR("before 0x00f50004 is 0x%x\n",
                uic_cmd_read(DME_GET, 0x00f50004));
    send_uic_command(DME_SET, 0x00f50004, 0x0, 0x01);
    /* mphy config update */
    send_uic_command(DME_SET, 0xd0850000, 0x0, 0x01);
    PRINT_ERROR("after 0x00f50004 is 0x%x\n",
                uic_cmd_read(DME_GET, 0x00f50004));
    /* just for test end */
#endif

    /* mphy config update ---not do it here because software update will
    * cause the speed not equal to the device, so update the PLL until the
    * RCT comes*/
    /*send_uic_command(DME_SET, 0xd0850000, 0x0, 0x01);*/

}

#if defined(COMBO_PHY_V120)
/*We need to know if the PLL-auto-change works well,
so check the values of registers,All the values listed in
"PLL clock setting" chapter in Hisi M-PHY spec*/
int vco_auto_check_pll_status(enum POWER_MODE pwrmode,
                              uint8_t gear, uint8_t rate)
{
    struct pllChkInfo tempInfo[RG_PLL_END_INDEX] = {0};
    /*firstly, check if the VCO auto change enabled or not,
        check VCO_AUTO_CHG*/
#if 0
    if (!(uic_cmd_read(DME_GET, ATTR_MCB(VCO_AUTO_CHG)) &
            VCO_AUTO_CHG_EN)) {
        /*VCO auto change was not enabled, just return success*/
        return UFS_OK;
    }
#endif

    memcpy(tempInfo, HsDefault, sizeof(struct pllChkInfo));
    if (FAST_MODE == pwrmode || FASTAUTO_MODE == pwrmode) {
        int index = 0;

        if (gear > 3) {
            PRINT_ERROR("Invalid gear : %d\n", gear);
            return UFS_ERROR;
        }

        tempInfo[RG_PLL_TXHSGR_INDEX].expect_val =
            (3 - gear);
        tempInfo[RG_PLL_RXHSGR_INDEX].expect_val =
            (3 - gear);

        if (rate == 1) {
            tempInfo[RG_PLL_FBK_P_INDEX].expect_val = HS_R_A_FBK_P;
        } else if (rate == 2) {
            tempInfo[RG_PLL_FBK_P_INDEX].expect_val = HS_R_B_FBK_P;
        } else {
            PRINT_ERROR("Invalid rate : %d\n", rate);
            return UFS_ERROR;
        }

        for (index = 0; index < RG_PLL_END_INDEX; index++) {
            if ((uic_cmd_read(
                        DME_GET, tempInfo[index].reg_addr) &
                    tempInfo[index].bit_mask) !=
                    tempInfo[index].expect_val) {
                PRINT_ERROR("%s error : 0x%x\n",
                            tempInfo[index].string,
                            tempInfo[index].expect_val);
                return UFS_ERROR;
            }
        }
    } else if (SLOW_MODE == pwrmode || SLOWAUTO_MODE == pwrmode) {
        /*
            RG_PLL_TXLSGR    RG_PLL_RXLSGR
        PWM G1      7       6
        PWM G2      6       5
        PWM G3      5       4
        PWM G4      4       3
        PWM G5      3       2
        PWM G6      2       1
        PWM G7      1       0
                            */
        uint8_t val = 0;

        val = uic_cmd_read(DME_GET, ATTR_MCB(RG_PLL_TXLSGR));
        if ((val & 0x0F) != (8 - gear)) {
            PRINT_ERROR("PWM %s Gear%d error : 0x%x\n",
                        "RG_PLL_TXLSGR", gear, val);
            return UFS_ERROR;
        }
        val = uic_cmd_read(DME_GET, ATTR_MCB(RG_PLL_RXLSGR));
        if ((val & 0x0F) != (7 - gear)) {
            PRINT_ERROR("PWM %s Gear%d error : 0x%x\n",
                        "RG_PLL_RXLSGR", gear, val);
            return UFS_ERROR;
        }
    }
    return UFS_OK;
}
#endif

int change_power_mode(enum POWER_MODE pwrmode, uint8_t gear, uint8_t rate,
                      int line, int scramble, int termination)
{
    int err;
    uint32_t value = 0;
    struct pwrModeParams pmp;
    char modename[16] = {0};
    int retry = 1000;
    static uint32_t justone = 1;

    GET_LOCAL_DWC_HOST();

    if (justone == 1) {
        justone = 0;
#ifdef COMBO_PHY_V100
        PRINT_ERROR("xxxxx open the clk gate xxxxxxxx\n");
        send_uic_command(DME_SET, TX_SLEEP_CONTROL, 0x0, 0x02);
        send_uic_command(DME_SET, 0x00c60000, 0x0, 0x02);
        send_uic_command(DME_SET, RX_SLEEP_CONTROL, 0x0, 0x02);
        send_uic_command(DME_SET, 0x00c80000, 0x0, 0x02);

        send_uic_command(DME_SET, 0x00ca0000, 0x0, 0x03);
        send_uic_command(DME_SET, 0x00cb0000, 0x0, 0x03);
        send_uic_command(DME_SET, 0x00cc0000, 0x0, 0x03);

        send_uic_command(DME_SET, 0x00d10000, 0x0, 0x03);
        send_uic_command(DME_SET, 0x00d20000, 0x0, 0x03);
#endif
    }

    /*hynix not support fastauto now*/
    if (((UFS_MANUFACTURER_ID_HYNIX ==
            dwc_host->manufacturer_id) ||
            (UFS_MANUFACTURER_ID_SUMSANG ==
             dwc_host->manufacturer_id)) &&
            (pwrmode == FASTAUTO_MODE)) {
        pwrmode = FASTAUTO_MODE;
    }

    if (pwrmode == FAST_MODE)
        strncpy(modename, "FAST_MODE",
                (uint32_t)strlen("FAST_MODE"));
    else if (pwrmode == SLOW_MODE)
        strncpy(modename, "SLOW_MODE",
                (uint32_t)strlen("SLOW_MODE"));
    else if (pwrmode == FASTAUTO_MODE)
        strncpy(modename, "FASTAUTO_MODE",
                (uint32_t)strlen("FASTAUTO_MODE"));
    else if (pwrmode == SLOWAUTO_MODE)
        strncpy(modename, "SLOWAUTO_MODE",
                (uint32_t)strlen("SLOWAUTO_MODE"));
    else {
        return UFS_ERROR;
    }

    if (UFS_MANUFACTURER_ID_HYNIX ==
            dwc_host->manufacturer_id) {
        UFS_PRINT("H**** device must set "
                  "VS_DebugSaveConfigTime 0x10\n");
        /* VS_DebugSaveConfigTime */
        send_uic_command(DME_SET, 0xd0a00000, 0x0, 0x10);
        /* sync length */
        send_uic_command(DME_SET, 0x15560000, 0x0, 0x48);
        /* no need to update in unipro register */
        /* send_uic_command(DME_SET, 0xD0850000, 0x0, 0x01); */

    }

    pmp.txGear = gear;
    pmp.rxGear = gear;
    pmp.hsSeries = rate;
    if (line == 1) {
        g_tx_lane_num[index] = 1;
        g_rx_lane_num[index] = 1;
    } else {
        /* PA_ConnectedTxDataLanes */
        g_tx_lane_num[index] =
            (uint8_t)uic_cmd_read(0x1, 0x15610000);
        /* PA_ConnectedRxDataLanes */
        g_rx_lane_num[index] =
            (uint8_t)uic_cmd_read(0x1, 0x15810000);
    }

#if defined(COMBO_PHY_V110) || defined(COMBO_PHY_V120)
    /*  de-emphasis level map
        5¡¯bx0000: 0 dB
        5¡¯bx0001: 0.72 dB
        5¡¯bx0010: 1.45 dB
        5¡¯bx0011: 2.18 dB
        5¡¯bx0100: 2.92 dB
        5¡¯bx0101: 3.67 dB
        5¡¯bx0110: 4.44 dB
        5¡¯bx0111: 5.22 dB
        5¡¯bx1110: 6.02 dB
        5¡¯bx1111: 6.85 dB
    */
    /* the de-emphasis level you want to select, for example ,
    * value = 0x5, it's 3.67 dB */

    if (FAST_MODE == pwrmode || FASTAUTO_MODE == pwrmode) {
        if (gear == 3) {
            value = 0x26; /* 4.44 dB */
            send_uic_command(DME_SET, 0x007e0000, 0x0, 0x05);
            send_uic_command(DME_SET, 0x00fc0004, 0x0, 0x1f);
            send_uic_command(DME_SET, 0x00fd0004, 0x0, 0x0);
            if ((g_tx_lane_num[index] > 1) &&
                    (g_rx_lane_num[index] > 1)) {
                send_uic_command(DME_SET,
                                 0x007e0001, 0x0, 0x05);
                send_uic_command(DME_SET,
                                 0x00fc0005, 0x0, 0x1f);
                send_uic_command(DME_SET,
                                 0x00fd0005, 0x0, 0x0);
            }
            if (rate == 2) {
                send_uic_command(DME_SET, 0x007F0000, 0x0, 0x24);
                send_uic_command(DME_SET, 0x007d0000, 0x0, 0x24);
                if ((g_tx_lane_num[index] > 1) &&
                        (g_rx_lane_num[index] > 1)) {
                    send_uic_command(DME_SET,
                                     0x007F0001, 0x0, 0x24);
                    send_uic_command(DME_SET,
                                     0x007d0001, 0x0, 0x24);
                }
            } else if (rate == 1) {
                send_uic_command(DME_SET, 0x007F0000, 0x0, 0x22);
                send_uic_command(DME_SET, 0x007d0000, 0x0, 0x22);
                if ((g_tx_lane_num[index] > 1) &&
                        (g_rx_lane_num[index] > 1)) {
                    send_uic_command(DME_SET,
                                     0x007F0001, 0x0, 0x22);
                    send_uic_command(DME_SET,
                                     0x007d0001, 0x0, 0x22);
                }
            }

#if defined(NOISE_PROOF)
            /*overwrite some settings to
            enhance noise proof*/
            send_uic_command(DME_SET,
                             0x007F0000, 0x0, 0x1B);
            if (g_tx_lane_num[index] > 1)
                send_uic_command(DME_SET,
                                 0x007F0001, 0x0, 0x1B);

            send_uic_command(DME_SET,
                             0x007C0000, 0x0, 0x14);
            if (g_tx_lane_num[index] > 1)
                send_uic_command(DME_SET,
                                 0x007C0001, 0x0, 0x14);

            send_uic_command(DME_SET,
                             0x007D0000, 0x0, 0x1B);
            if (g_tx_lane_num[index] > 1)
                send_uic_command(DME_SET,
                                 0x007D0001, 0x0, 0x1B);

#endif

        } else if (gear == 2) {
            value = 0x23;
            send_uic_command(DME_SET, 0x007e0000, 0x0, 0x05);
            send_uic_command(DME_SET, 0x00fc0004, 0x0, 0x1b);
            send_uic_command(DME_SET, 0x00fd0004, 0x0, 0x0);
            if ((g_tx_lane_num[index] > 1) &&
                    (g_rx_lane_num[index] > 1)) {
                send_uic_command(DME_SET,
                                 0x007e0001, 0x0, 0x05);
                send_uic_command(DME_SET,
                                 0x00fc0005, 0x0, 0x1b);
                send_uic_command(DME_SET,
                                 0x00fd0005, 0x0, 0x0);
            }
            if (rate == 2) {
                send_uic_command(DME_SET, 0x007F0000, 0x0, 0x21);
                send_uic_command(DME_SET, 0x007d0000, 0x0, 0x21);
                if ((g_tx_lane_num[index] > 1) &&
                        (g_rx_lane_num[index] > 1)) {
                    send_uic_command(DME_SET,
                                     0x007F0001, 0x0, 0x21);
                    send_uic_command(DME_SET,
                                     0x007d0001, 0x0, 0x21);
                }
            } else if (rate == 1) {
                send_uic_command(DME_SET, 0x007F0000, 0x0, 0x21);
                send_uic_command(DME_SET, 0x007d0000, 0x0, 0x21);
                if ((g_tx_lane_num[index] > 1) &&
                        (g_rx_lane_num[index] > 1)) {
                    send_uic_command(DME_SET,
                                     0x007F0001, 0x0, 0x21);
                    send_uic_command(DME_SET,
                                     0x007d0001, 0x0, 0x21);
                }
            }
        } else if (gear == 1) {
            value = 0x20;
            send_uic_command(DME_SET, 0x007e0000, 0x0, 0x05);
            send_uic_command(DME_SET, 0x00fc0004, 0x0, 0x1b);
            send_uic_command(DME_SET, 0x00fd0004, 0x0, 0x1);
            if ((g_tx_lane_num[index] > 1) &&
                    (g_rx_lane_num[index] > 1)) {
                send_uic_command(DME_SET,
                                 0x007e0001, 0x0, 0x05);
                send_uic_command(DME_SET,
                                 0x00fc0005, 0x0, 0x1b);
                send_uic_command(DME_SET,
                                 0x00fd0005, 0x0, 0x1);
            }
            if (rate == 2) {
                send_uic_command(DME_SET, 0x007F0000, 0x0, 0x13);
                send_uic_command(DME_SET, 0x007d0000, 0x0, 0x13);
                if ((g_tx_lane_num[index] > 1) &&
                        (g_rx_lane_num[index] > 1)) {
                    send_uic_command(DME_SET,
                                     0x007F0001, 0x0, 0x13);
                    send_uic_command(DME_SET,
                                     0x007d0001, 0x0, 0x13);
                }
            } else if (rate == 1) {
                send_uic_command(DME_SET, 0x007F0000, 0x0, 0x13);
                send_uic_command(DME_SET, 0x007d0000, 0x0, 0x13);
                if ((g_tx_lane_num[index] > 1) &&
                        (g_rx_lane_num[index] > 1)) {
                    send_uic_command(DME_SET,
                                     0x007F0001, 0x0, 0x13);
                    send_uic_command(DME_SET,
                                     0x007d0001, 0x0, 0x13);
                }
            }
        }

        send_uic_command(DME_SET,
                         0x00370000, 0x0, value);
        send_uic_command(DME_SET,
                         0x007b0000, 0x0, value);
        if ((g_tx_lane_num[index] > 1) &&
                (g_rx_lane_num[index] > 1)) {
            send_uic_command(DME_SET,
                             0x00370001, 0x0, value);
            send_uic_command(DME_SET,
                             0x007b0001, 0x0, value);
        }

#if defined(NOISE_PROOF)
        /*overwrite some settings to
        enhance noise proof*/
        if (gear == 3) {
            send_uic_command(DME_SET,
                             0x00370000, 0x0, 0x23);
            if (g_tx_lane_num[index] > 1)
                send_uic_command(DME_SET,
                                 0x00370001, 0x0, 0x23);

            send_uic_command(DME_SET,
                             0x007B0000, 0x0, 0x23);
            if (g_tx_lane_num[index] > 1)
                send_uic_command(DME_SET,
                                 0x007B0001, 0x0, 0x23);

        }
#endif

    }
#else
#ifdef TX_EQUALIZER_35DB
    send_uic_command(DME_SET, 0x00370000, 0x0, 0x1);
    if ((g_tx_lane_num[index] > 1) &&
            (g_rx_lane_num[index] > 1))
        send_uic_command(DME_SET,
                         0x00370001, 0x0, 0x1);
#endif
#ifdef TX_EQUALIZER_60DB
    send_uic_command(DME_SET, 0x00370000, 0x0, 0x2);
    if ((g_tx_lane_num[index] > 1) &&
            (g_rx_lane_num[index] > 1))
        send_uic_command(DME_SET,
                         0x00370001, 0x0, 0x2);
#endif
#endif

    pmp.txLanes = g_tx_lane_num[index];    /* Tx One Lane */
    pmp.rxLanes = g_rx_lane_num[index];    /* Rx One Lane */
    pmp.pwrMode = pwrmode;

#ifdef UFS_USE_HISI_MPHY_TC
#if defined(COMBO_PHY_V120)
    /*if (!(uic_cmd_read(DME_GET, ATTR_MCB(VCO_AUTO_CHG))
            & VCO_AUTO_CHG_EN))*/
    adapt_pll_to_power_mode(pwrmode,  gear,  rate);
#else
    adapt_pll_to_power_mode(pwrmode,  gear,  rate);
#endif
#endif

    err = do_mode_change(&pmp, gear, rate, scramble, termination);
    if (err) {
        UFS_PRINT("do_mode_change failed\n");
        return err;
    }

    while (--retry) {
        value = dwc_ufs_read_reg(UFS_IS_OFF);
        if (value & UFS_IS_UPMS_BIT) {
            dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UPMS_BIT);
            break;
        }
        ufs_waitms(1);
    }
    value = dwc_ufs_read_reg(UFS_HCS_OFF);
    if (((value & UFS_HCS_UPMCRS_MASK) >> UFS_HCS_UPMCRS_OFF) != 0x1) {
        UFS_PRINT("check HCS.UPMCRS error, HCS = 0x%x\n", value);
        return -1;
    }
    /*
    #ifdefined(COMBO_PHY_V120)
        err = vco_auto_check_pll_status(pwrmode, gear, rate);
        if (err)
            return err;
    #endif
    */

    /* should be here */
#if 1
    /*set 0xc4 to 0x80 after mode changes*/
    /* RX_ERR_STATUS */
    send_uic_command(DME_SET, 0x00c40004, 0x0, 0x80);
    send_uic_command(DME_SET, 0x00c50004, 0x0, 0x01);
    if (g_rx_lane_num[index] == 2) {
        /* RX_ERR_STATUS */
        send_uic_command(DME_SET, 0x00c40005, 0x0, 0x80);
        send_uic_command(DME_SET, 0x00c50005, 0x0, 0x01);
    }
#endif

    return SUCCESS;
}


int ufs_init(enum POWER_MODE mode, int hs_gear, int rate,
             int lane, int scramble, int termination)
{
    int ret = 0;

    GET_LOCAL_DWC_HOST();

    if (dwc_host->is_init) {
        return 0;
    }

    if (!is_boot_from_ufs()) {
        ufs_clk_init();
        ufs_hardware_init();
    } else {
        UFS_PRINT("Boot-From-UFS\n");
        ufs_clk_init();
        ufs_hardware_init();
    }


    ret = ufs_host_init();
    if (ret) {
        PRINT_ERROR("ufs host init fail. ret: %d\n", ret);
        return ret;
    }
    memset((void *)&ufs_desc, 0, (unsigned int)sizeof(struct ufs_descriptor));
    ret = ufs_device_init();
    if (ret) {
        PRINT_ERROR("ufs device init fail. ret: %d\n", ret);
        return ret;
    }

    ret = ufs_lu_init();
    if (ret) {
        PRINT_ERROR("ufs lu init fail. ret: %d\n", ret);
        return ret;
    }

    ret = ufs_get_device_info();
    if (ret) {
        PRINT_ERROR("ufs get device info fail. ret: %d\n", ret);
        return ret;
    }

    ret = ufs_set_ref_clk();
    if (ret) {
        PRINT_ERROR("UfsSetRefClk ret:%d\n", ret);
        return ret;
    }

    ufs_waitms(10);
    UFS_PRINT("UFS %s Gear-%d Rate-%c Lanes-%d Scrmbl-%d Termn-%d\n",
              ((mode == SLOW_MODE) ? "Slow" :
               ((mode == SLOWAUTO_MODE) ? "SlowAuto" :
                ((mode == FAST_MODE) ? "Fast" : "FastAuto"))),
              hs_gear, (rate == 1) ? 'A' : 'B', lane,
              scramble, termination);
    ret = change_power_mode(mode, hs_gear, rate,
                            lane, scramble, termination);
    if (ret) {
        PRINT_ERROR("UFS change MODE fail.\n");
        return ret;
    }

    ret = ufs_set_active_lun(DEFAULT_ACTIVE_LUN);
    if (ret) {
        PRINT_ERROR("ufs_set_active_lun fail.\n");
        return ret;
    }
    UFS_PRINT("UFS set active lu(0x%x)\n", dwc_host->active_lun);
    dwc_host->is_init = 1;
    return ret;
}

int ufs_reinit(enum POWER_MODE mode, int hs_gear,
               int rate, int lane, int scramble, int termination)
{
    return ufs_init(mode, hs_gear, rate, lane, scramble, termination);
}

int ufs_storage_init(void)
{
    GET_LOCAL_DWC_HOST();

    if (ufs_init(DEFAULT_POWER_MODE,
                 DEFAULT_GEAR,
                 DEFAULT_RATE,
                 DEFAULT_LANE, 0, 1) != 0) {
        /*relese resource*/
        if (dwc_host->mem_pool) {
            free((void *)dwc_host->mem_pool);
        }
        if (dwc_host->write_read_buf) {
            free((void *)dwc_host->write_read_buf);
        }
        dwc_host->mem_pool = 0;
        dwc_host->write_read_buf = NULL;
        UFS_PRINT("release memory pool\n");
    }
    UFS_PRINT("\n");
    return 0;
}

