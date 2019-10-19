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
#ifndef __HDMI_EMI_H__
#define __HDMI_EMI_H__

#include "drv_hdmi_common.h"
#if defined(HDMI_CHIP_TYPE_HI3798CV200)
#include "hi_reg_crg.h"

#define HDMI_CRG_PLL10      g_pstRegCrg->PERI_CRG_PLL10.u32
#define HDMI_CRG_PLL11      g_pstRegCrg->PERI_CRG_PLL11.u32
#define HDMI_CRG_80         g_pstRegCrg->PERI_CRG80.u32

#define HDMI_CRG_PLL10_ADDR     0x2028
#define HDMI_CRG_PLL11_ADDR     0x202c
#define HDMI_CRG_80_ADDR        0x2140
#endif

typedef struct hiHDMI_EMI_CONFIG
{
    HI_BOOL                 bEmiEnable;
    HI_BOOL                 bDebugEnable;
    HI_BOOL                 bVesaFmt;
    HI_U32                  u32TmdsClk;
    HDMI_COLORSPACE_E       enOutColorSpace;
    HDMI_DEEP_COLOR_E       enDeepColor;
}HDMI_EMI_CONFIG_S;

typedef struct hiEmi_Status_S
{
    HI_BOOL bSWEmiEnable;
    HI_BOOL bHWEmiEnable;
    HI_BOOL bDebugEnable;   // user debug
}HDMI_EMI_STATUS_S;


HI_S32 HDMI_EmiSet(HDMI_EMI_CONFIG_S* pstEmiCfg);
HI_VOID HDMI_EmiStatusGet(HDMI_EMI_STATUS_S *pstEmiStatus);


#endif

