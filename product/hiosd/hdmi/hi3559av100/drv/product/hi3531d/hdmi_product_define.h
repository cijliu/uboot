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

#ifndef __HDMI_PRODUCT_DEFINE_H__
#define __HDMI_PRODUCT_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hi_type.h"
#include "hdmi_reg_crg.h"


#ifdef HDMI_BUILD_IN_BOOT

#include "boot_hdmi_intf.h"

#if defined(CONFIG_HDMI_STB_SDK)
#ifndef HI_MINIBOOT_SUPPORT
#include <uboot.h>
#else
#include "stdio.h"
#include "string.h"
#include "boot_hdmi_intf.h"
#endif
#elif defined(CONFIG_HDMI_BVT_SDK)
#include "ubi_uboot.h"
#include "malloc.h"
#include "boot_hdmi_intf.h"
#endif

#define HDMI_MEMSET             memset
#define HDMI_MEMCPY             memcpy

#define msleep(x) do{\
    HI_U32 i,j;\
    for(i=0;i<x;i++)\
        for(j=0;j<500;j++);\
}while(0)



#endif //#ifdef HDMI_BUILD_IN_BOOT

/******************** HI3531DV100 define start *****************************/

/* HDMI TX CRG */
#define HDMI_TX_BASE_ADDR           0x13000000
/* HDMI TX SUB-module */
#define HDMI_TX_BASE_ADDR_CTRL      0x0000
#define HDMI_TX_BASE_ADDR_AIDEO     0x0800
#define HDMI_TX_BASE_ADDR_AUDIO     0x1000
#define HDMI_TX_BASE_ADDR_HDMITX    0x1800
#define HDMI_TX_BASE_ADDR_HDCP1X    0x2000
#define HDMI_TX_BASE_ADDR_AON       0x4000
#define HDMI_TX_BASE_ADDR_CEC       0x4800
#define HDMI_TX_BASE_ADDR_MCU_PRAM  0x10000
#define HDMI_TX_BASE_ADDR_MCU_DRAM  0x18000
#define HDMI_TX_BASE_ADDR_MCU       0x1c000

#define BASE_ADDR_tx_ctrl_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_CTRL)
#define BASE_ADDR_video_path_reg    (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_AIDEO)
#define BASE_ADDR_audio_path_reg    (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_AUDIO)
#define BASE_ADDR_tx_hdmi_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_HDMITX)
#define BASE_ADDR_tx_hdcp_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_HDCP1X)
#define BASE_ADDR_tx_aon_reg        (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_AON)
#define BASE_ADDR_tx_cec_reg        (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_CEC)
#define BASE_ADDR_mcu_cpu_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_MCU)
#define BASE_ADDR_mcu_pram          (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_MCU_PRAM)
#define BASE_ADDR_mcu_dram          (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_MCU_DRAM)

/******************** HI3531DV100 define end *****************************/

typedef struct
{
    HI_U32 u32SscBypassDiv;
    HI_U32 u32TmdsClkDiv;
}HDMI_CRG_CFG_S;


HI_S32  HDMITXRegWrite(HI_U32 *pu32RegAddr, HI_U32 u32Value);
HI_U32  HDMITXRegRead(HI_U32 *pu32RegAddr);
HI_S32  HDMITXVerifyRegWrite(HI_U32 *pu32RegAddr, HI_U32 u32RegValue, HI_CHAR *pRegName);
HI_S32  HDMIRegWriteU32(HI_U32 u32RegAddr, HI_U32 u32Value);
HI_U32  HDMIRegReadU32 (HI_U32 u32RegAddr);

HI_VOID DRV_HDMI_ProdIoCfgSet(HI_VOID);

HI_VOID DRV_HDMI_ProdCrgAllResetSet(HI_BOOL bEnable);
HI_VOID DRV_HDMI_ProdCrgGateSet(HI_BOOL bEnable);
HI_VOID DRV_HDMI_ProdCrgDivSet(HDMI_CRG_CFG_S *pstCrgCfg);
HI_VOID DRV_HDMI_ProdCrgPhyResetSet(HI_BOOL bEnable);
HI_VOID DRV_HDMI_ProdCrgPhyResetGet(HI_BOOL *pbEnable);
HI_VOID DRV_HDMI_ProdCrgInit(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_PRODUCT_DEFINE_H__ */


