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
#include "hdmi_reg_audio_path.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "hdmi_product_define.h"
#endif

/* Define the struct pointor of the module audio_path_reg */
volatile S_audio_path_reg_REGS_TYPE *gopaudio_path_regAllReg = NULL;

int HDMI_TX_S_audio_path_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
{
    if (HI_NULL == pcAddr)
    {
        HDMI_ERR("pcAddr is NULL! \n");
        return HI_FAILURE;
    }

    gopaudio_path_regAllReg = (volatile S_audio_path_reg_REGS_TYPE *)(pcAddr + (HDMI_TX_BASE_ADDR_AUDIO));

    return HI_SUCCESS;
}

int HDMI_TX_S_audio_path_reg_REGS_TYPE_DeInit(void)
{
    if (gopaudio_path_regAllReg)
    {
        gopaudio_path_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_spdif_enSet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_spdif_en
//  Input       : unsigned int uaud_spdif_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_spdif_enSet(unsigned int uaud_spdif_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_audio_ctrl.bits.aud_spdif_en = uaud_spdif_en;
    HDMITXRegWrite(pu32RegAddr, o_tx_audio_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_i2s_enSet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_i2s_en
//  Input       : unsigned int uaud_i2s_en: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_i2s_enSet(unsigned int uaud_i2s_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_audio_ctrl.bits.aud_i2s_en = uaud_i2s_en;
    HDMITXRegWrite(pu32RegAddr, o_tx_audio_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_layoutSet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_layout
//  Input       : unsigned int uaud_layout: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_layoutSet(unsigned int uaud_layout)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_audio_ctrl.bits.aud_layout = uaud_layout;
    HDMITXRegWrite(pu32RegAddr, o_tx_audio_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_mute_enSet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_mute_en
//  Input       : unsigned int uaud_mute_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_mute_enSet(unsigned int uaud_mute_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_audio_ctrl.bits.aud_mute_en = uaud_mute_en;
    HDMITXRegWrite(pu32RegAddr, o_tx_audio_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_in_enSet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_in_en
//  Input       : unsigned int uaud_in_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_in_enSet(unsigned int uaud_in_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_audio_ctrl.bits.aud_in_en = uaud_in_en;
    HDMITXRegWrite(pu32RegAddr, o_tx_audio_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_ch_swapSet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_ch_swap
//  Input       : unsigned int ui2s_ch_swap: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_ch_swapSet(unsigned int ui2s_ch_swap)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_ch_swap = ui2s_ch_swap;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_lengthSet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_length
//  Input       : unsigned int ui2s_length: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_lengthSet(unsigned int ui2s_length)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_length = ui2s_length;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_vbitSet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_vbit
//  Input       : unsigned int ui2s_vbit: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_vbitSet(unsigned int ui2s_vbit)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_vbit = ui2s_vbit;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_data_dirSet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_data_dir
//  Input       : unsigned int ui2s_data_dir: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_data_dirSet(unsigned int ui2s_data_dir)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_data_dir = ui2s_data_dir;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_justifySet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_justify
//  Input       : unsigned int ui2s_justify: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_justifySet(unsigned int ui2s_justify)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_justify = ui2s_justify;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_ws_polaritySet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_ws_polarity
//  Input       : unsigned int ui2s_ws_polarity: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_ws_polaritySet(unsigned int ui2s_ws_polarity)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_ws_polarity = ui2s_ws_polarity;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_1st_shiftSet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_1st_shift
//  Input       : unsigned int ui2s_1st_shift: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_1st_shiftSet(unsigned int ui2s_1st_shift)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_1st_shift = ui2s_1st_shift;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_hbra_onSet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_hbra_on
//  Input       : unsigned int ui2s_hbra_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_hbra_onSet(unsigned int ui2s_hbra_on)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_i2s_ctrl.bits.i2s_hbra_on = ui2s_hbra_on;
    HDMITXRegWrite(pu32RegAddr, o_aud_i2s_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG0_chst_byte3_clock_accuracySet
//  Description : Set the value of the member AUD_CHST_CFG0.chst_byte3_clock_accuracy
//  Input       : unsigned int uchst_byte3_clock_accuracy: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG0_chst_byte3_clock_accuracySet(unsigned int uchst_byte3_clock_accuracy)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG0 o_aud_chst_cfg0;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG0.u32);
    o_aud_chst_cfg0.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_chst_cfg0.bits.chst_byte3_clock_accuracy = uchst_byte3_clock_accuracy;
    HDMITXRegWrite(pu32RegAddr, o_aud_chst_cfg0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG0_chst_byte3_fsSet
//  Description : Set the value of the member AUD_CHST_CFG0.chst_byte3_fs
//  Input       : unsigned int uchst_byte3_fs: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG0_chst_byte3_fsSet(unsigned int uchst_byte3_fs)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG0 o_aud_chst_cfg0;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG0.u32);
    o_aud_chst_cfg0.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_chst_cfg0.bits.chst_byte3_fs = uchst_byte3_fs;
    HDMITXRegWrite(pu32RegAddr, o_aud_chst_cfg0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG0_chst_byte0_bSet
//  Description : Set the value of the member AUD_CHST_CFG0.chst_byte0_b
//  Input       : unsigned int uchst_byte0_b: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG0_chst_byte0_bSet(unsigned int uchst_byte0_b)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG0 o_aud_chst_cfg0;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG0.u32);
    o_aud_chst_cfg0.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_chst_cfg0.bits.chst_byte0_b = uchst_byte0_b;
    HDMITXRegWrite(pu32RegAddr, o_aud_chst_cfg0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG0_chst_byte0_aSet
//  Description : Set the value of the member AUD_CHST_CFG0.chst_byte0_a
//  Input       : unsigned int uchst_byte0_a: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG0_chst_byte0_aSet(unsigned int uchst_byte0_a)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG0 o_aud_chst_cfg0;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG0.u32);
    o_aud_chst_cfg0.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_chst_cfg0.bits.chst_byte0_a = uchst_byte0_a;
    HDMITXRegWrite(pu32RegAddr, o_aud_chst_cfg0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG1_chst_byte4_org_fsSet
//  Description : Set the value of the member AUD_CHST_CFG1.chst_byte4_org_fs
//  Input       : unsigned int uchst_byte4_org_fs: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG1_chst_byte4_org_fsSet(unsigned int uchst_byte4_org_fs)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG1 o_aud_chst_cfg1;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG1.u32);
    o_aud_chst_cfg1.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_chst_cfg1.bits.chst_byte4_org_fs = uchst_byte4_org_fs;
    HDMITXRegWrite(pu32RegAddr, o_aud_chst_cfg1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG1_chst_byte4_lengthSet
//  Description : Set the value of the member AUD_CHST_CFG1.chst_byte4_length
//  Input       : unsigned int uchst_byte4_length: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG1_chst_byte4_lengthSet(unsigned int uchst_byte4_length)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG1 o_aud_chst_cfg1;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG1.u32);
    o_aud_chst_cfg1.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_chst_cfg1.bits.chst_byte4_length = uchst_byte4_length;
    HDMITXRegWrite(pu32RegAddr, o_aud_chst_cfg1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_FIFO_CTRL_aud_fifo_hbr_maskSet
//  Description : Set the value of the member AUD_FIFO_CTRL.aud_fifo_hbr_mask
//  Input       : unsigned int uaud_fifo_hbr_mask: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_FIFO_CTRL_aud_fifo_hbr_maskSet(unsigned int uaud_fifo_hbr_mask)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_FIFO_CTRL o_aud_fifo_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_FIFO_CTRL.u32);
    o_aud_fifo_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_fifo_ctrl.bits.aud_fifo_hbr_mask = uaud_fifo_hbr_mask;
    HDMITXRegWrite(pu32RegAddr, o_aud_fifo_ctrl.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AUD_FIFO_CTRL_aud_fifo_testSet
//  Description : Set the value of the member AUD_FIFO_CTRL.aud_fifo_test
//  Input       : unsigned int uaud_fifo_test: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_FIFO_CTRL_aud_fifo_testSet(unsigned int uaud_fifo_test)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_FIFO_CTRL o_aud_fifo_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_FIFO_CTRL.u32);
    o_aud_fifo_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_fifo_ctrl.bits.aud_fifo_test = uaud_fifo_test;
    HDMITXRegWrite(pu32RegAddr, o_aud_fifo_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AUD_ACR_CTRL_acr_cts_hw_sw_selSet
//  Description : Set the value of the member AUD_ACR_CTRL.acr_cts_hw_sw_sel
//  Input       : unsigned int uacr_cts_hw_sw_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_ACR_CTRL_acr_cts_hw_sw_selSet(unsigned int uacr_cts_hw_sw_sel)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_ACR_CTRL o_aud_acr_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_ACR_CTRL.u32);
    o_aud_acr_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_aud_acr_ctrl.bits.acr_cts_hw_sw_sel = uacr_cts_hw_sw_sel;
    HDMITXRegWrite(pu32RegAddr, o_aud_acr_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_ACR_N_VAL_SW_acr_n_val_swSet
//  Description : Set the value of the member ACR_N_VAL_SW.acr_n_val_sw
//  Input       : unsigned int uacr_n_val_sw: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ACR_N_VAL_SW_acr_n_val_swSet(unsigned int uacr_n_val_sw)
{
    HI_U32 *pu32RegAddr = NULL;

    U_ACR_N_VAL_SW o_acr_n_val_sw;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->ACR_N_VAL_SW.u32);
    o_acr_n_val_sw.u32 = HDMITXRegRead(pu32RegAddr);
    o_acr_n_val_sw.bits.acr_n_val_sw = uacr_n_val_sw;
    HDMITXRegWrite(pu32RegAddr, o_acr_n_val_sw.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_spdif_enGet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_spdif_en
//  Input       : unsigned int uaud_spdif_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_spdif_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_audio_ctrl.bits.aud_spdif_en;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_i2s_enGet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_i2s_en
//  Input       : unsigned int uaud_i2s_en: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_i2s_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_audio_ctrl.bits.aud_i2s_en;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_layoutGet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_layout
//  Input       : unsigned int uaud_layout: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_layoutGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_audio_ctrl.bits.aud_layout;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_mute_enGet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_mute_en
//  Input       : unsigned int uaud_mute_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_mute_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_audio_ctrl.bits.aud_mute_en;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_CTRL_aud_in_enGet
//  Description : Set the value of the member TX_AUDIO_CTRL.aud_in_en
//  Input       : unsigned int uaud_in_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_CTRL_aud_in_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_CTRL o_tx_audio_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_CTRL.u32);
    o_tx_audio_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_audio_ctrl.bits.aud_in_en;
}

//******************************************************************************
//  Function    : HDMI_AUD_I2S_CTRL_i2s_hbra_onGet
//  Description : Set the value of the member AUD_I2S_CTRL.i2s_hbra_on
//  Input       : unsigned int ui2s_hbra_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_I2S_CTRL_i2s_hbra_onGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_I2S_CTRL o_aud_i2s_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_I2S_CTRL.u32);
    o_aud_i2s_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_aud_i2s_ctrl.bits.i2s_hbra_on;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG0_chst_byte3_fsGet
//  Description : Set the value of the member AUD_CHST_CFG0.chst_byte3_fs
//  Input       : unsigned int uchst_byte3_fs: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG0_chst_byte3_fsGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG0 o_aud_chst_cfg0;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG0.u32);
    o_aud_chst_cfg0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_aud_chst_cfg0.bits.chst_byte3_fs;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG1_chst_byte4_org_fsGet
//  Description : Set the value of the member AUD_CHST_CFG1.chst_byte4_org_fs
//  Input       : unsigned int uchst_byte4_org_fs: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG1_chst_byte4_org_fsGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG1 o_aud_chst_cfg1;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG1.u32);
    o_aud_chst_cfg1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_aud_chst_cfg1.bits.chst_byte4_org_fs;
}

//******************************************************************************
//  Function    : HDMI_AUD_CHST_CFG1_chst_byte4_lengthGet
//  Description : Set the value of the member AUD_CHST_CFG1.chst_byte4_length
//  Input       : unsigned int uchst_byte4_length: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_CHST_CFG1_chst_byte4_lengthGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_CHST_CFG1 o_aud_chst_cfg1;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_CHST_CFG1.u32);
    o_aud_chst_cfg1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_aud_chst_cfg1.bits.chst_byte4_length;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_STATE_aud_spdif_fsGet
//  Description : Set the value of the member TX_AUDIO_STATE.aud_spdif_fs
//  Input       : unsigned int uaud_spdif_fs: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_STATE_aud_spdif_fsGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_STATE o_tx_audio_state;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_STATE.u32);
    o_tx_audio_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_audio_state.bits.aud_spdif_fs;
}

//******************************************************************************
//  Function    : HDMI_TX_AUDIO_STATE_aud_lengthGet
//  Description : Set the value of the member TX_AUDIO_STATE.aud_length
//  Input       : unsigned int uaud_length: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AUDIO_STATE_aud_lengthGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AUDIO_STATE o_tx_audio_state;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->TX_AUDIO_STATE.u32);
    o_tx_audio_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_audio_state.bits.aud_length;
}

//******************************************************************************
//  Function    : HDMI_AUD_ACR_CTRL_acr_cts_hw_sw_selGet
//  Description : Set the value of the member AUD_ACR_CTRL.acr_cts_hw_sw_sel
//  Input       : unsigned int uacr_cts_hw_sw_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AUD_ACR_CTRL_acr_cts_hw_sw_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_AUD_ACR_CTRL o_aud_acr_ctrl;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->AUD_ACR_CTRL.u32);
    o_aud_acr_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_aud_acr_ctrl.bits.acr_cts_hw_sw_sel;
}

//******************************************************************************
//  Function    : HDMI_ACR_N_VAL_SW_acr_n_val_swGet
//  Description : Set the value of the member ACR_N_VAL_SW.acr_n_val_sw
//  Input       : unsigned int uacr_n_val_sw: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ACR_N_VAL_SW_acr_n_val_swGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_ACR_N_VAL_SW o_acr_n_val_sw;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->ACR_N_VAL_SW.u32);
    o_acr_n_val_sw.u32 = HDMITXRegRead(pu32RegAddr);
    return o_acr_n_val_sw.bits.acr_n_val_sw;
}

//******************************************************************************
//  Function    : HDMI_ACR_CTS_VAL_SW_acr_cts_val_swGet
//  Description : Set the value of the member ACR_CTS_VAL_SW.acr_cts_val_sw
//  Input       : unsigned int uacr_cts_val_sw: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ACR_CTS_VAL_SW_acr_cts_val_swGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_ACR_CTS_VAL_SW o_acr_cts_val_sw;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->ACR_CTS_VAL_SW.u32);
    o_acr_cts_val_sw.u32 = HDMITXRegRead(pu32RegAddr);
    return o_acr_cts_val_sw.bits.acr_cts_val_sw;
}

//******************************************************************************
//  Function    : HDMI_ACR_CTS_VAL_HW_acr_cts_val_hwGet
//  Description : Set the value of the member ACR_CTS_VAL_HW.acr_cts_val_hw
//  Input       : unsigned int uacr_cts_val_hw: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ACR_CTS_VAL_HW_acr_cts_val_hwGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_ACR_CTS_VAL_HW o_acr_cts_val_hw;
    pu32RegAddr = (HI_U32*)&(gopaudio_path_regAllReg->ACR_CTS_VAL_HW.u32);
    o_acr_cts_val_hw.u32 = HDMITXRegRead(pu32RegAddr);
    return o_acr_cts_val_hw.bits.acr_cts_val_hw;
}
