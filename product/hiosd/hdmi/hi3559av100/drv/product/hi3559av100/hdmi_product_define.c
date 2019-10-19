/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/
#include "hdmi_reg_crg.h"
#include "hdmi_product_define.h"

#ifndef HDMI_BUILD_IN_BOOT
#include "mod_ext.h"
#include "proc_ext.h"
#include "hi_debug.h"
#include "mm_ext.h"
#include "dev_ext.h"
#endif

/******************************************************************************/
/* Macro define                                                               */
/******************************************************************************/

#define HDMI_IO_CFG_FUNCTION1_SEL       0x1

#define PRODUCT_NULL_CHK(p) do{\
	if(HI_NULL == p)\
    {HDMI_ERR("%s is null pointer!return fail.\n",#p);\
	return HI_FAILURE;}\
}while(0)

#define PRODUCT_NULL_CHK_NORET(p) do{\
        if(HI_NULL == p)\
        {HDMI_ERR("%s is null pointer!return fail.\n",#p);\
        return ;}\
}while(0)

/******************************************************************************/
/* Public Interface                                                          */
/******************************************************************************/
HI_S32 HDMITXRegWrite  (HI_U32 *pu32RegAddr, HI_U32 u32Value)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    *(volatile HI_U32*)pu32RegAddr = u32Value;
    return HI_SUCCESS;
}

HI_U32 HDMITXRegRead(HI_U32 *pu32RegAddr)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    return *(volatile HI_U32*)(pu32RegAddr);
}

HI_S32 HDMIRegWriteU32(HI_U32 u32RegAddr, HI_U32 u32Value)
{
    volatile HI_U32 *pu32RegAddr = HI_NULL;

    pu32RegAddr = (volatile HI_U32 *)HDMI_IO_MAP((HI_U64)u32RegAddr, 4);

    if (pu32RegAddr)
    {
        *pu32RegAddr = u32Value ;
        HDMI_IO_UNMAP(pu32RegAddr);
        return HI_SUCCESS;
    }
    else
    {
        HDMI_ERR("HDMI_IO_MAP addr=0x%x err!\n",u32RegAddr);
        return HI_FAILURE;
    }
}


HI_U32 HDMIRegReadU32 (HI_U32 u32RegAddr)
{
    volatile HI_U32 *pu32RegAddr = HI_NULL;
	HI_U32  u32Value = 0;

    pu32RegAddr = (volatile HI_U32 *)HDMI_IO_MAP((HI_U64)u32RegAddr,4);

    if (pu32RegAddr)
    {
        u32Value = *pu32RegAddr ;
        HDMI_IO_UNMAP(pu32RegAddr);
    }
    else
    {
        HDMI_ERR("HDMI_IO_MAP addr=0x%x\n err!\n",u32RegAddr);
    }

	return  u32Value;
}


//==========================================================================

HI_VOID DRV_HDMI_ProdIoCfgSet(HI_VOID)
{
    /* no IO multiplex */
    return ;
}

/* only used at open HDMI and hardware init */
HI_VOID DRV_HDMI_ProdCrgGateSet(HI_BOOL bEnable)
{
#ifndef HDMI_FPGA_SUPPORT
    /* Gate */
    /* PERI_CRG68  HDMITX_CTRL CRG  0x00 */
    REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_cec_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_os_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_as_cken_Set(bEnable);
    REG_HDMI_CRG_mpll_tmds_cken_Set(bEnable);

    /* PERI_CRG70  HDMITX_PHY CRG 0x00 */
    REG_HDMI_CRG_hdmirx_phy_tmds_cken_Set(bEnable);
    REG_HDMI_CRG_hdmirx_phy_modclk_cken_Set(bEnable);
    REG_HDMI_CRG_ac_ctrl_modclk_cken_Set(bEnable);

    REG_HDMI_CRG_hdmitx_phy_clk_pctrl_Set(HI_FALSE);
    REG_HDMI_CRG_mpll_tmds_cksel_Set(0);
#endif

    return ;
}

HI_VOID DRV_HDMI_ProdCrgAllResetSet(HI_BOOL bEnable)
{
#ifndef HDMI_FPGA_SUPPORT
    /* PERI_CRG68  HDMITX_CTRL CRG  0x00EC   0x0001043F */
    REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Set(bEnable);
    /* PERI_CRG70  HDMITX_PHY       0x00F0  0x00000001 */
    REG_HDMI_CRG_hdmitx_phy_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_phy_bus_srst_req_Set(bEnable);
    REG_HDMI_CRG_ac_ctrl_srst_req_Set(bEnable);
    REG_HDMI_CRG_ac_ctrl_bus_srst_req_Set(bEnable);

    bEnable = !bEnable;
    /* delay 2us, to ensure ctrl reset success. */
    /* Because internal clock of HDMI is smaller than APB clock. */
    HDMI_UDELAY(2);
    /* PERI_CRG68  HDMITX_CTRL CRG  0x00EC   0x0001043F */
    REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Set(bEnable);
    /* PERI_CRG70  HDMITX_PHY       0x00F0  0x00000001 */
    REG_HDMI_CRG_hdmitx_phy_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_phy_bus_srst_req_Set(bEnable);
    REG_HDMI_CRG_ac_ctrl_srst_req_Set(bEnable);
    REG_HDMI_CRG_ac_ctrl_bus_srst_req_Set(bEnable);
    /* delay 2us, avoid system crash when start HDMI(no boot) */
    /* delay 100ms, HPD can not read after reset when enable HPD filtering if not delay. */
    HDMI_MSLEEP(100);

#endif
    return ;
}

HI_VOID DRV_HDMI_ProdRegDefautCfg(HI_VOID)
{
    /* The following register should be set default values */
    HDMIRegWriteU32(HDMI_CTRL_BASE_ADDR | 0x14b8, 0x00);

    return;
}

HI_VOID DRV_HDMI_LowPowerSet(HI_BOOL bEnable)
{
#ifndef HDMI_FPGA_SUPPORT
    bEnable = !bEnable;

    /* PERI_CRG68 */
    REG_HDMI_CRG_hdmitx_ctrl_os_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_as_cken_Set(bEnable);
    REG_HDMI_CRG_mpll_tmds_cken_Set(bEnable);

    /* MPLL 0-open, 1-close */
    REG_MPLL_CRG_mpll_pd_Set(!bEnable);
#endif

    return;
}

HI_VOID DRV_HDMI_ProdCrgInit(HI_VOID)
{
    DRV_HDMI_ProdIoCfgSet();
    DRV_HDMI_ProdCrgGateSet(HI_TRUE);
    DRV_HDMI_ProdCrgAllResetSet(HI_TRUE);
#ifndef HDMI_BUILD_IN_BOOT
    DRV_HDMI_LowPowerSet(HI_TRUE); /* disable clk */
#endif
    DRV_HDMI_ProdRegDefautCfg();

    return ;
}

HI_VOID DRV_HDMI_HardwareReset(HI_VOID)
{
#ifndef HDMI_FPGA_SUPPORT
    if(HI_SUCCESS != REG_HDMI_CRG_reg_Init())
    {
        HDMI_ERR("CRG reg io map error!\n");
        return;
    }

    /* reset all module */
    REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(HI_TRUE);
    REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(HI_TRUE);
    REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Set(HI_TRUE);

    REG_HDMI_CRG_hdmitx_phy_srst_req_Set(HI_TRUE);
    REG_HDMI_CRG_hdmitx_phy_bus_srst_req_Set(HI_TRUE);
    REG_HDMI_CRG_ac_ctrl_srst_req_Set(HI_TRUE);
    REG_HDMI_CRG_ac_ctrl_bus_srst_req_Set(HI_TRUE);

    /* close all clk */
    DRV_HDMI_ProdCrgGateSet(HI_FALSE);
    DRV_HDMI_LowPowerSet(HI_TRUE);

    REG_HDMI_CRG_reg_DeInit();
#endif
}

#ifndef HDMI_BUILD_IN_BOOT
HI_S32 HI_HDMI_PROC_AddModule(HI_CHAR * pEntry_name, HDMI_PROC_ITEM_S *pProcItem, HI_VOID *pData)
{
#ifndef CONFIG_HDMI_PROC_DISABLE
    osal_proc_entry_t *proc = NULL;
    proc = osal_create_proc_entry(pEntry_name, NULL);
    if (HI_NULL == proc)
    {
        return HI_FAILURE;
    }
    proc->read = (HI_VOID *)pProcItem->fnRead;
    proc->write = (HI_VOID *)pProcItem->fnWrite;
#endif

    return HI_SUCCESS;
}

HI_VOID HI_HDMI_PROC_RemoveModule(HI_CHAR *pEntry_name)
{
#ifndef CONFIG_HDMI_PROC_DISABLE
    osal_remove_proc_entry(pEntry_name, NULL);
    return ;
#else
#endif
}
#endif

