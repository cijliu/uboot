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
#include "hi_type.h"
#include "hdmi_reg_video_path.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module video_path_reg */
volatile S_video_path_reg_REGS_TYPE *gopvideo_path_regAllReg = NULL;

int HDMI_TX_S_video_path_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
{
#ifdef HDMI_BUILD_IN_BOOT
    pcAddr = (HI_CHAR *)HDMI_IO_MAP(HDMI_TX_BASE_ADDR, 4);
#else
    if (HI_NULL == pcAddr)
    {
        HDMI_ERR("pcAddr is NULL!\n");
        return HI_FAILURE;
    }
#endif

    gopvideo_path_regAllReg = (volatile S_video_path_reg_REGS_TYPE*)(pcAddr + HDMI_TX_BASE_ADDR_AIDEO);

    return HI_SUCCESS;
}

int HDMI_TX_S_video_path_reg_REGS_TYPE_DeInit(void)
{
    if (gopvideo_path_regAllReg)
    {
        gopvideo_path_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

#ifndef HDMI_BUILD_IN_BOOT

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_sync_polaritySet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_sync_polarity
//  Input       : unsigned int ureg_sync_polarity: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_sync_polaritySet(unsigned int ureg_sync_polarity)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_timing_gen_ctrl.bits.reg_sync_polarity = ureg_sync_polarity;
    HDMITXRegWrite(pu32RegAddr, o_timing_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_sync_polarityGet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_sync_polarity
//  Input       : unsigned int ureg_sync_polarity: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_sync_polarityGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_timing_gen_ctrl.bits.reg_sync_polarity;
}

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_timing_selSet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_timing_sel
//  Input       : unsigned int ureg_timing_sel: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_timing_selSet(unsigned int ureg_timing_sel)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_timing_gen_ctrl.bits.reg_timing_sel = ureg_timing_sel;
    HDMITXRegWrite(pu32RegAddr, o_timing_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_timing_selGet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_timing_sel
//  Input       : unsigned int ureg_timing_sel: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_timing_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_timing_gen_ctrl.bits.reg_timing_sel;
}

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_extmodeSet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_extmode
//  Input       : unsigned int ureg_extmode: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_extmodeSet(unsigned int ureg_extmode)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_timing_gen_ctrl.bits.reg_extmode = ureg_extmode;
    HDMITXRegWrite(pu32RegAddr, o_timing_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_extmodeGet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_extmode
//  Input       : unsigned int ureg_extmode: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_extmodeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_timing_gen_ctrl.bits.reg_extmode;
}

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_timing_gen_enSet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_timing_gen_en
//  Input       : unsigned int ureg_timing_gen_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_timing_gen_enSet(unsigned int ureg_timing_gen_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_timing_gen_ctrl.bits.reg_timing_gen_en = ureg_timing_gen_en;
    HDMITXRegWrite(pu32RegAddr, o_timing_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TIMING_GEN_CTRL_reg_timing_gen_enGet
//  Description : Set the value of the member TIMING_GEN_CTRL.reg_timing_gen_en
//  Input       : unsigned int ureg_timing_gen_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TIMING_GEN_CTRL_reg_timing_gen_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TIMING_GEN_CTRL o_timing_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->TIMING_GEN_CTRL.u32);
    o_timing_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_timing_gen_ctrl.bits.reg_timing_gen_en;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_PATH_CTRL_reg_video_blank_enSet
//  Description : Set the value of the member VIDEO_PATH_CTRL.reg_video_blank_en
//  Input       : unsigned int ureg_video_blank_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_PATH_CTRL_reg_video_blank_enSet(unsigned int ureg_video_blank_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_PATH_CTRL o_video_path_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_PATH_CTRL.u32);
    o_video_path_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_path_ctrl.bits.reg_video_blank_en = ureg_video_blank_en;
    HDMITXRegWrite(pu32RegAddr, o_video_path_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_PATH_CTRL_reg_video_blank_enGet
//  Description : Get the value of the member VIDEO_PATH_CTRL.reg_video_blank_en
//  Input       : unsigned int reg_video_blank_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_PATH_CTRL_reg_video_blank_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_PATH_CTRL o_video_path_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_PATH_CTRL.u32);
    o_video_path_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_path_ctrl.bits.reg_video_blank_en;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_PATH_CTRL_reg_video_lp_disableSet
//  Description : Set the value of the member VIDEO_PATH_CTRL.reg_video_lp_disable
//  Input       : unsigned int ureg_video_lp_disable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_PATH_CTRL_reg_video_lp_disableSet(unsigned int ureg_video_lp_disable)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_PATH_CTRL o_video_path_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_PATH_CTRL.u32);
    o_video_path_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_path_ctrl.bits.reg_video_lp_disable = ureg_video_lp_disable;
    HDMITXRegWrite(pu32RegAddr, o_video_path_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_PATH_CTRL_reg_video_lp_disableGet
//  Description : Get the value of the member VIDEO_PATH_CTRL.reg_video_lp_disable
//  Input       : unsigned int reg_video_lp_disable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_PATH_CTRL_reg_video_lp_disableGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_PATH_CTRL o_video_path_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_PATH_CTRL.u32);
    o_video_path_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_path_ctrl.bits.reg_video_lp_disable;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_cbar_pattern_selSet
//  Description : Set the value of the member PATTERN_GEN_CTRL.cbar_pattern_sel
//  Input       : unsigned int ucbar_pattern_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_cbar_pattern_selSet(unsigned int ucbar_pattern_sel)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_pattern_gen_ctrl.bits.cbar_pattern_sel = ucbar_pattern_sel;
    HDMITXRegWrite(pu32RegAddr, o_pattern_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_mask_pattern_enSet
//  Description : Set the value of the member PATTERN_GEN_CTRL.mask_pattern_en
//  Input       : unsigned int umask_pattern_en: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_mask_pattern_enSet(unsigned int umask_pattern_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_pattern_gen_ctrl.bits.mask_pattern_en = umask_pattern_en;
    HDMITXRegWrite(pu32RegAddr, o_pattern_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_mask_pattern_enGet
//  Description : Set the value of the member PATTERN_GEN_CTRL.mask_pattern_en
//  Input       : unsigned int umask_pattern_en: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_mask_pattern_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pattern_gen_ctrl.bits.mask_pattern_en;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_square_pattern_enSet
//  Description : Set the value of the member PATTERN_GEN_CTRL.square_pattern_en
//  Input       : unsigned int usquare_pattern_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_square_pattern_enSet(unsigned int usquare_pattern_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_pattern_gen_ctrl.bits.square_pattern_en = usquare_pattern_en;
    HDMITXRegWrite(pu32RegAddr, o_pattern_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_square_pattern_enGet
//  Description : Set the value of the member PATTERN_GEN_CTRL.square_pattern_en
//  Input       : unsigned int usquare_pattern_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_square_pattern_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pattern_gen_ctrl.bits.square_pattern_en;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_colorbar_enSet
//  Description : Set the value of the member PATTERN_GEN_CTRL.colorbar_en
//  Input       : unsigned int ucolorbar_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_colorbar_enSet(unsigned int ucolorbar_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_pattern_gen_ctrl.bits.colorbar_en = ucolorbar_en;
    HDMITXRegWrite(pu32RegAddr, o_pattern_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_colorbar_enGet
//  Description : Set the value of the member PATTERN_GEN_CTRL.colorbar_en
//  Input       : unsigned int ucolorbar_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_colorbar_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pattern_gen_ctrl.bits.colorbar_en;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_solid_pattern_enSet
//  Description : Set the value of the member PATTERN_GEN_CTRL.solid_pattern_en
//  Input       : unsigned int usolid_pattern_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_solid_pattern_enSet(unsigned int usolid_pattern_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_pattern_gen_ctrl.bits.solid_pattern_en = usolid_pattern_en;
    HDMITXRegWrite(pu32RegAddr, o_pattern_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_solid_pattern_enGet
//  Description : Set the value of the member PATTERN_GEN_CTRL.solid_pattern_en
//  Input       : unsigned int usolid_pattern_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_solid_pattern_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pattern_gen_ctrl.bits.solid_pattern_en;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_video_formatSet
//  Description : Set the value of the member PATTERN_GEN_CTRL.video_format
//  Input       : unsigned int uvideo_format: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_video_formatSet(unsigned int uvideo_format)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_pattern_gen_ctrl.bits.video_format = uvideo_format;
    HDMITXRegWrite(pu32RegAddr, o_pattern_gen_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PATTERN_GEN_CTRL_video_formatGet
//  Description : Set the value of the member PATTERN_GEN_CTRL.video_format
//  Input       : unsigned int uvideo_format: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PATTERN_GEN_CTRL_video_formatGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_PATTERN_GEN_CTRL o_pattern_gen_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->PATTERN_GEN_CTRL.u32);
    o_pattern_gen_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pattern_gen_ctrl.bits.video_format;
}

//******************************************************************************
//  Function    : HDMI_SOLID_PATTERN_CONFIG_solid_pattern_crSet
//  Description : Set the value of the member SOLID_PATTERN_CONFIG.solid_pattern_cr
//  Input       : unsigned int usolid_pattern_cr: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SOLID_PATTERN_CONFIG_solid_pattern_crSet(unsigned int usolid_pattern_cr)
{
    HI_U32 *pu32RegAddr = NULL;

    U_SOLID_PATTERN_CONFIG o_solid_pattern_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->SOLID_PATTERN_CONFIG.u32);
    o_solid_pattern_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_solid_pattern_config.bits.solid_pattern_cr = usolid_pattern_cr;
    HDMITXRegWrite(pu32RegAddr, o_solid_pattern_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SOLID_PATTERN_CONFIG_solid_pattern_ySet
//  Description : Set the value of the member SOLID_PATTERN_CONFIG.solid_pattern_y
//  Input       : unsigned int usolid_pattern_y: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SOLID_PATTERN_CONFIG_solid_pattern_ySet(unsigned int usolid_pattern_y)
{
    HI_U32 *pu32RegAddr = NULL;

    U_SOLID_PATTERN_CONFIG o_solid_pattern_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->SOLID_PATTERN_CONFIG.u32);
    o_solid_pattern_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_solid_pattern_config.bits.solid_pattern_y = usolid_pattern_y;
    HDMITXRegWrite(pu32RegAddr, o_solid_pattern_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SOLID_PATTERN_CONFIG_solid_pattern_cbSet
//  Description : Set the value of the member SOLID_PATTERN_CONFIG.solid_pattern_cb
//  Input       : unsigned int usolid_pattern_cb: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SOLID_PATTERN_CONFIG_solid_pattern_cbSet(unsigned int usolid_pattern_cb)
{
    HI_U32 *pu32RegAddr = NULL;

    U_SOLID_PATTERN_CONFIG o_solid_pattern_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->SOLID_PATTERN_CONFIG.u32);
    o_solid_pattern_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_solid_pattern_config.bits.solid_pattern_cb = usolid_pattern_cb;
    HDMITXRegWrite(pu32RegAddr, o_solid_pattern_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FORMAT_DET_CONFIG_fdt_status_clearSet
//  Description : Set the value of the member FORMAT_DET_CONFIG.fdt_status_clear
//  Input       : unsigned int ufdt_status_clear: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FORMAT_DET_CONFIG_fdt_status_clearSet(unsigned int ufdt_status_clear)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FORMAT_DET_CONFIG o_format_det_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FORMAT_DET_CONFIG.u32);
    o_format_det_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_format_det_config.bits.fdt_status_clear = ufdt_status_clear;
    HDMITXRegWrite(pu32RegAddr, o_format_det_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FORMAT_DET_CONFIG_sync_polarity_forceSet
//  Description : Set the value of the member FORMAT_DET_CONFIG.sync_polarity_force
//  Input       : unsigned int usync_polarity_force: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FORMAT_DET_CONFIG_sync_polarity_forceSet(unsigned int usync_polarity_force)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FORMAT_DET_CONFIG o_format_det_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FORMAT_DET_CONFIG.u32);
    o_format_det_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_format_det_config.bits.sync_polarity_force = usync_polarity_force;
    HDMITXRegWrite(pu32RegAddr, o_format_det_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDET_STATUS_vsync_polarityGet
//  Description : Set the value of the member FDET_STATUS.vsync_polarity
//  Input       : unsigned int uvsync_polarity: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDET_STATUS_vsync_polarityGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FDET_STATUS o_fdet_status;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FDET_STATUS.u32);
    o_fdet_status.u32 = HDMITXRegRead(pu32RegAddr);
    return o_fdet_status.bits.vsync_polarity;
}

//******************************************************************************
//  Function    : HDMI_FDET_STATUS_hsync_polarityGet
//  Description : Set the value of the member FDET_STATUS.hsync_polarity
//  Input       : unsigned int uhsync_polarity: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDET_STATUS_hsync_polarityGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FDET_STATUS o_fdet_status;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FDET_STATUS.u32);
    o_fdet_status.u32 = HDMITXRegRead(pu32RegAddr);
    return o_fdet_status.bits.hsync_polarity;
}

//******************************************************************************
//  Function    : HDMI_FDET_STATUS_interlacedGet
//  Description : Set the value of the member FDET_STATUS.interlaced
//  Input       : unsigned int uinterlaced: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDET_STATUS_interlacedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FDET_STATUS o_fdet_status;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FDET_STATUS.u32);
    o_fdet_status.u32 = HDMITXRegRead(pu32RegAddr);
    return o_fdet_status.bits.interlaced;
}

//******************************************************************************
//  Function    : HDMI_FDET_HORI_RES_hsync_total_cntGet
//  Description : Set the value of the member FDET_HORI_RES.hsync_total_cnt
//  Input       : unsigned int uhsync_total_cnt: 13 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDET_HORI_RES_hsync_total_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FDET_HORI_RES o_fdet_hori_res;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FDET_HORI_RES.u32);
    o_fdet_hori_res.u32 = HDMITXRegRead(pu32RegAddr);
    return o_fdet_hori_res.bits.hsync_total_cnt;
}

//******************************************************************************
//  Function    : HDMI_FDET_HORI_RES_hsync_active_cntGet
//  Description : Set the value of the member FDET_HORI_RES.hsync_active_cnt
//  Input       : unsigned int uhsync_active_cnt: 13 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDET_HORI_RES_hsync_active_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FDET_HORI_RES o_fdet_hori_res;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FDET_HORI_RES.u32);
    o_fdet_hori_res.u32 = HDMITXRegRead(pu32RegAddr);
    return o_fdet_hori_res.bits.hsync_active_cnt;
}

//******************************************************************************
//  Function    : HDMI_FDET_VERT_RES_vsync_total_cntGet
//  Description : Set the value of the member FDET_VERT_RES.vsync_total_cnt
//  Input       : unsigned int uvsync_total_cnt: 13 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDET_VERT_RES_vsync_total_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FDET_VERT_RES o_fdet_vert_res;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FDET_VERT_RES.u32);
    o_fdet_vert_res.u32 = HDMITXRegRead(pu32RegAddr);
    return o_fdet_vert_res.bits.vsync_total_cnt;
}

//******************************************************************************
//  Function    : HDMI_FDET_VERT_RES_vsync_active_cntGet
//  Description : Set the value of the member FDET_VERT_RES.vsync_active_cnt
//  Input       : unsigned int uvsync_active_cnt: 13 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDET_VERT_RES_vsync_active_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_FDET_VERT_RES o_fdet_vert_res;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->FDET_VERT_RES.u32);
    o_fdet_vert_res.u32 = HDMITXRegRead(pu32RegAddr);
    return o_fdet_vert_res.bits.vsync_active_cnt;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_bypGet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_dwsm_vert_byp
//  Input       : unsigned int ureg_dwsm_vert_byp: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_bypGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dwsm_ctrl.bits.reg_dwsm_vert_byp;
}


//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_enGet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_dwsm_vert_en
//  Input       : unsigned int ureg_dwsm_vert_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dwsm_ctrl.bits.reg_dwsm_vert_en;
}



//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_hori_filter_enGet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_hori_filter_en
//  Input       : unsigned int ureg_hori_filter_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_hori_filter_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dwsm_ctrl.bits.reg_hori_filter_en;
}


//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_dwsm_hori_enGet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_dwsm_hori_en
//  Input       : unsigned int ureg_dwsm_hori_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_dwsm_hori_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dwsm_ctrl.bits.reg_dwsm_hori_en;
}



//******************************************************************************
//  Function    : HDMI_DATA_ALIGN_CTRL_reg_pxl_div_enGet
//  Description : Set the value of the member DATA_ALIGN_CTRL.reg_pxl_div_en
//  Input       : unsigned int ureg_pxl_div_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DATA_ALIGN_CTRL_reg_pxl_div_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DATA_ALIGN_CTRL o_data_align_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DATA_ALIGN_CTRL.u32);
    o_data_align_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_data_align_ctrl.bits.reg_pxl_div_en;
}

//******************************************************************************
//  Function    : HDMI_DATA_ALIGN_CTRL_reg_demux_420_enGet
//  Description : Set the value of the member DATA_ALIGN_CTRL.reg_demux_420_en
//  Input       : unsigned int ureg_demux_420_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DATA_ALIGN_CTRL_reg_demux_420_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DATA_ALIGN_CTRL o_data_align_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DATA_ALIGN_CTRL.u32);
    o_data_align_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_data_align_ctrl.bits.reg_demux_420_en;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_inver_syncGet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_inver_sync
//  Input       : unsigned int ureg_inver_sync: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_inver_syncGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dmux_ctrl.bits.reg_inver_sync;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_vmux_cr_selGet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_vmux_cr_sel
//  Input       : unsigned int ureg_vmux_cr_sel: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_vmux_cr_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dmux_ctrl.bits.reg_vmux_cr_sel;
}



//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_vmux_cb_selGet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_vmux_cb_sel
//  Input       : unsigned int ureg_vmux_cb_sel: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_vmux_cb_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dmux_ctrl.bits.reg_vmux_cb_sel;
}



//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_vmux_y_selGet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_vmux_y_sel
//  Input       : unsigned int ureg_vmux_y_sel: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_vmux_y_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_video_dmux_ctrl.bits.reg_vmux_y_sel;
}

//******************************************************************************
//  Function    : HDMI_DITHER_CONFIG_dither_modeGet
//  Description : Set the value of the member DITHER_CONFIG.dither_mode
//  Input       : unsigned int udither_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DITHER_CONFIG_dither_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DITHER_CONFIG o_dither_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DITHER_CONFIG.u32);
    o_dither_config.u32 = HDMITXRegRead(pu32RegAddr);
    return o_dither_config.bits.dither_mode;
}



//******************************************************************************
//  Function    : HDMI_DITHER_CONFIG_dither_rnd_bypGet
//  Description : Set the value of the member DITHER_CONFIG.dither_rnd_byp
//  Input       : unsigned int udither_rnd_byp: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DITHER_CONFIG_dither_rnd_bypGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DITHER_CONFIG o_dither_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DITHER_CONFIG.u32);
    o_dither_config.u32 = HDMITXRegRead(pu32RegAddr);
    return o_dither_config.bits.dither_rnd_byp;
}

//******************************************************************************
//  Function    : HDMI_MULTI_CSC_CTRL_reg_csc_enGet
//  Description : Set the value of the member MULTI_CSC_CTRL.reg_csc_en
//  Input       : unsigned int ureg_csc_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_MULTI_CSC_CTRL_reg_csc_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_MULTI_CSC_CTRL o_multi_csc_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->MULTI_CSC_CTRL.u32);
    o_multi_csc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_multi_csc_ctrl.bits.reg_csc_en;
}



#endif

//******************************************************************************
//  Function    : HDMI_MULTI_CSC_CTRL_reg_csc_modeGet
//  Description : Set the value of the member MULTI_CSC_CTRL.reg_csc_mode
//  Input       : unsigned int ureg_csc_mode: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_MULTI_CSC_CTRL_reg_csc_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_MULTI_CSC_CTRL o_multi_csc_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->MULTI_CSC_CTRL.u32);
    o_multi_csc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_multi_csc_ctrl.bits.reg_csc_mode;
}

//******************************************************************************
//  Function    : HDMI_DITHER_CONFIG_dither_modeSet
//  Description : Set the value of the member DITHER_CONFIG.dither_mode
//  Input       : unsigned int udither_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DITHER_CONFIG_dither_modeSet(unsigned int udither_mode)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DITHER_CONFIG o_dither_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DITHER_CONFIG.u32);
    o_dither_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_dither_config.bits.dither_mode = udither_mode;
    HDMITXRegWrite(pu32RegAddr, o_dither_config.u32);

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : HDMI_DITHER_CONFIG_dither_rnd_bypSet
//  Description : Set the value of the member DITHER_CONFIG.dither_rnd_byp
//  Input       : unsigned int udither_rnd_byp: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DITHER_CONFIG_dither_rnd_bypSet(unsigned int udither_rnd_byp)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DITHER_CONFIG o_dither_config;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DITHER_CONFIG.u32);
    o_dither_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_dither_config.bits.dither_rnd_byp = udither_rnd_byp;
    HDMITXRegWrite(pu32RegAddr, o_dither_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_MULTI_CSC_CTRL_reg_csc_modeSet
//  Description : Set the value of the member MULTI_CSC_CTRL.reg_csc_mode
//  Input       : unsigned int ureg_csc_mode: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_MULTI_CSC_CTRL_reg_csc_modeSet(unsigned int ureg_csc_mode)
{
    HI_U32 *pu32RegAddr = NULL;

    U_MULTI_CSC_CTRL o_multi_csc_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->MULTI_CSC_CTRL.u32);
    o_multi_csc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_multi_csc_ctrl.bits.reg_csc_mode = ureg_csc_mode;
    HDMITXRegWrite(pu32RegAddr, o_multi_csc_ctrl.u32);

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : HDMI_MULTI_CSC_CTRL_reg_csc_saturate_enSet
//  Description : Set the value of the member MULTI_CSC_CTRL.reg_csc_saturate_en
//  Input       : unsigned int ureg_csc_saturate_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_MULTI_CSC_CTRL_reg_csc_saturate_enSet(unsigned int ureg_csc_saturate_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_MULTI_CSC_CTRL o_multi_csc_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->MULTI_CSC_CTRL.u32);
    o_multi_csc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_multi_csc_ctrl.bits.reg_csc_saturate_en = ureg_csc_saturate_en;
    HDMITXRegWrite(pu32RegAddr, o_multi_csc_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_MULTI_CSC_CTRL_reg_csc_enSet
//  Description : Set the value of the member MULTI_CSC_CTRL.reg_csc_en
//  Input       : unsigned int ureg_csc_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_MULTI_CSC_CTRL_reg_csc_enSet(unsigned int ureg_csc_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_MULTI_CSC_CTRL o_multi_csc_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->MULTI_CSC_CTRL.u32);
    o_multi_csc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_multi_csc_ctrl.bits.reg_csc_en = ureg_csc_en;
    HDMITXRegWrite(pu32RegAddr, o_multi_csc_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_bypSet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_dwsm_vert_byp
//  Input       : unsigned int ureg_dwsm_vert_byp: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_bypSet(unsigned int ureg_dwsm_vert_byp)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dwsm_ctrl.bits.reg_dwsm_vert_byp = ureg_dwsm_vert_byp;
    HDMITXRegWrite(pu32RegAddr, o_video_dwsm_ctrl.u32);

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_enSet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_dwsm_vert_en
//  Input       : unsigned int ureg_dwsm_vert_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_dwsm_vert_enSet(unsigned int ureg_dwsm_vert_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dwsm_ctrl.bits.reg_dwsm_vert_en = ureg_dwsm_vert_en;
    HDMITXRegWrite(pu32RegAddr, o_video_dwsm_ctrl.u32);

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_hori_filter_enSet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_hori_filter_en
//  Input       : unsigned int ureg_hori_filter_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_hori_filter_enSet(unsigned int ureg_hori_filter_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dwsm_ctrl.bits.reg_hori_filter_en = ureg_hori_filter_en;
    HDMITXRegWrite(pu32RegAddr, o_video_dwsm_ctrl.u32);

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : HDMI_VIDEO_DWSM_CTRL_reg_dwsm_hori_enSet
//  Description : Set the value of the member VIDEO_DWSM_CTRL.reg_dwsm_hori_en
//  Input       : unsigned int ureg_dwsm_hori_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DWSM_CTRL_reg_dwsm_hori_enSet(unsigned int ureg_dwsm_hori_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DWSM_CTRL o_video_dwsm_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DWSM_CTRL.u32);
    o_video_dwsm_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dwsm_ctrl.bits.reg_dwsm_hori_en = ureg_dwsm_hori_en;
    HDMITXRegWrite(pu32RegAddr, o_video_dwsm_ctrl.u32);

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : HDMI_DATA_ALIGN_CTRL_reg_pxl_div_enSet
//  Description : Set the value of the member DATA_ALIGN_CTRL.reg_pxl_div_en
//  Input       : unsigned int ureg_pxl_div_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DATA_ALIGN_CTRL_reg_pxl_div_enSet(unsigned int ureg_pxl_div_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DATA_ALIGN_CTRL o_data_align_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DATA_ALIGN_CTRL.u32);
    o_data_align_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_data_align_ctrl.bits.reg_pxl_div_en = ureg_pxl_div_en;
    HDMITXRegWrite(pu32RegAddr, o_data_align_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DATA_ALIGN_CTRL_reg_demux_420_enSet
//  Description : Set the value of the member DATA_ALIGN_CTRL.reg_demux_420_en
//  Input       : unsigned int ureg_demux_420_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DATA_ALIGN_CTRL_reg_demux_420_enSet(unsigned int ureg_demux_420_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DATA_ALIGN_CTRL o_data_align_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->DATA_ALIGN_CTRL.u32);
    o_data_align_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_data_align_ctrl.bits.reg_demux_420_en = ureg_demux_420_en;
    HDMITXRegWrite(pu32RegAddr, o_data_align_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_inver_syncSet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_inver_sync
//  Input       : unsigned int ureg_inver_sync: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_inver_syncSet(unsigned int ureg_inver_sync)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dmux_ctrl.bits.reg_inver_sync = ureg_inver_sync;
    HDMITXRegWrite(pu32RegAddr, o_video_dmux_ctrl.u32);

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_syncmask_enSet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_syncmask_en
//  Input       : unsigned int ureg_syncmask_en: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_syncmask_enSet(unsigned int ureg_syncmask_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dmux_ctrl.bits.reg_syncmask_en = ureg_syncmask_en;
    HDMITXRegWrite(pu32RegAddr, o_video_dmux_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_vmux_cr_selSet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_vmux_cr_sel
//  Input       : unsigned int ureg_vmux_cr_sel: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_vmux_cr_selSet(unsigned int ureg_vmux_cr_sel)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dmux_ctrl.bits.reg_vmux_cr_sel = ureg_vmux_cr_sel;
    HDMITXRegWrite(pu32RegAddr, o_video_dmux_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_vmux_cb_selSet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_vmux_cb_sel
//  Input       : unsigned int ureg_vmux_cb_sel: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_vmux_cb_selSet(unsigned int ureg_vmux_cb_sel)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dmux_ctrl.bits.reg_vmux_cb_sel = ureg_vmux_cb_sel;
    HDMITXRegWrite(pu32RegAddr, o_video_dmux_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VIDEO_DMUX_CTRL_reg_vmux_y_selSet
//  Description : Set the value of the member VIDEO_DMUX_CTRL.reg_vmux_y_sel
//  Input       : unsigned int ureg_vmux_y_sel: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VIDEO_DMUX_CTRL_reg_vmux_y_selSet(unsigned int ureg_vmux_y_sel)
{
    HI_U32 *pu32RegAddr = NULL;

    U_VIDEO_DMUX_CTRL o_video_dmux_ctrl;
    pu32RegAddr = (HI_U32*)&(gopvideo_path_regAllReg->VIDEO_DMUX_CTRL.u32);
    o_video_dmux_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_video_dmux_ctrl.bits.reg_vmux_y_sel = ureg_vmux_y_sel;
    HDMITXRegWrite(pu32RegAddr, o_video_dmux_ctrl.u32);

    return HI_SUCCESS;
}

