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
#include "hdmi_reg_hdcp.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module tx_hdcp_reg */
volatile S_tx_hdcp_reg_REGS_TYPE *goptx_hdcp_regAllReg = NULL;


int HDMI_TX_S_tx_hdcp_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
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

    goptx_hdcp_regAllReg = (volatile S_tx_hdcp_reg_REGS_TYPE*)(pcAddr + HDMI_TX_BASE_ADDR_HDCP1X);

    return HI_SUCCESS;
}

int HDMI_TX_S_tx_hdcp_reg_REGS_TYPE_DeInit(void)
{
    if (goptx_hdcp_regAllReg)
    {
        goptx_hdcp_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}




//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist2_errSet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_bist2_err
//  Input       : unsigned int uhdcp1x_bist2_err: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist2_errSet(unsigned int uhdcp1x_bist2_err)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = 0;
    o_hdcp1x_mem_ctrl.bits.hdcp1x_bist2_err = uhdcp1x_bist2_err;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_mem_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist2_errGet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_bist2_err
//  Input       : unsigned int uhdcp1x_bist2_err: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist2_errGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_mem_ctrl.bits.hdcp1x_bist2_err;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist1_errSet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_bist1_err
//  Input       : unsigned int uhdcp1x_bist1_err: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist1_errSet(unsigned int uhdcp1x_bist1_err)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = 0;
    o_hdcp1x_mem_ctrl.bits.hdcp1x_bist1_err = uhdcp1x_bist1_err;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_mem_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist1_errGet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_bist1_err
//  Input       : unsigned int uhdcp1x_bist1_err: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist1_errGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_mem_ctrl.bits.hdcp1x_bist1_err;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist0_errSet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_bist0_err
//  Input       : unsigned int uhdcp1x_bist0_err: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist0_errSet(unsigned int uhdcp1x_bist0_err)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = 0;
    o_hdcp1x_mem_ctrl.bits.hdcp1x_bist0_err = uhdcp1x_bist0_err;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_mem_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist0_errGet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_bist0_err
//  Input       : unsigned int uhdcp1x_bist0_err: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_bist0_errGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_mem_ctrl.bits.hdcp1x_bist0_err;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_cmd_doneSet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_cmd_done
//  Input       : unsigned int uhdcp1x_cmd_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_cmd_doneSet(unsigned int uhdcp1x_cmd_done)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = 0;
    o_hdcp1x_mem_ctrl.bits.hdcp1x_cmd_done = uhdcp1x_cmd_done;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_mem_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_cmd_doneGet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_cmd_done
//  Input       : unsigned int uhdcp1x_cmd_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_cmd_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_mem_ctrl.bits.hdcp1x_cmd_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_key_cmd_validSet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_key_cmd_valid
//  Input       : unsigned int uhdcp1x_key_cmd_valid: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_key_cmd_validSet(unsigned int uhdcp1x_key_cmd_valid)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_mem_ctrl.bits.hdcp1x_key_cmd_valid = uhdcp1x_key_cmd_valid;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_mem_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_key_cmdSet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_key_cmd
//  Input       : unsigned int uhdcp1x_key_cmd: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_key_cmdSet(unsigned int uhdcp1x_key_cmd)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_mem_ctrl.bits.hdcp1x_key_cmd = uhdcp1x_key_cmd;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_mem_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_MEM_CTRL_hdcp1x_key_loadSet
//  Description : Set the value of the member HDCP1X_MEM_CTRL.hdcp1x_key_load
//  Input       : unsigned int uhdcp1x_key_load: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_MEM_CTRL_hdcp1x_key_loadSet(unsigned int uhdcp1x_key_load)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_MEM_CTRL o_hdcp1x_mem_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_MEM_CTRL.u32);
    o_hdcp1x_mem_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_mem_ctrl.bits.hdcp1x_key_load = uhdcp1x_key_load;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_mem_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte3Get
//  Description : Set the value of the member HDCP1X_KEY_AKSV0.hdcp1x_key_aksv_byte3
//  Input       : unsigned int uhdcp1x_key_aksv_byte3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_KEY_AKSV0 o_hdcp1x_key_aksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_KEY_AKSV0.u32);
    o_hdcp1x_key_aksv0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_key_aksv0.bits.hdcp1x_key_aksv_byte3;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte2Get
//  Description : Set the value of the member HDCP1X_KEY_AKSV0.hdcp1x_key_aksv_byte2
//  Input       : unsigned int uhdcp1x_key_aksv_byte2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_KEY_AKSV0 o_hdcp1x_key_aksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_KEY_AKSV0.u32);
    o_hdcp1x_key_aksv0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_key_aksv0.bits.hdcp1x_key_aksv_byte2;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte1Get
//  Description : Set the value of the member HDCP1X_KEY_AKSV0.hdcp1x_key_aksv_byte1
//  Input       : unsigned int uhdcp1x_key_aksv_byte1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_KEY_AKSV0 o_hdcp1x_key_aksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_KEY_AKSV0.u32);
    o_hdcp1x_key_aksv0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_key_aksv0.bits.hdcp1x_key_aksv_byte1;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte0Get
//  Description : Set the value of the member HDCP1X_KEY_AKSV0.hdcp1x_key_aksv_byte0
//  Input       : unsigned int uhdcp1x_key_aksv_byte0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_KEY_AKSV0_hdcp1x_key_aksv_byte0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_KEY_AKSV0 o_hdcp1x_key_aksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_KEY_AKSV0.u32);
    o_hdcp1x_key_aksv0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_key_aksv0.bits.hdcp1x_key_aksv_byte0;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_KEY_AKSV1_hdcp1x_key_aksv_byte4Get
//  Description : Set the value of the member HDCP1X_KEY_AKSV1.hdcp1x_key_aksv_byte4
//  Input       : unsigned int uhdcp1x_key_aksv_byte4: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_KEY_AKSV1_hdcp1x_key_aksv_byte4Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_KEY_AKSV1 o_hdcp1x_key_aksv1;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_KEY_AKSV1.u32);
    o_hdcp1x_key_aksv1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_key_aksv1.bits.hdcp1x_key_aksv_byte4;
}

//******************************************************************************
//  Function    : HDMI_HDCP_MUTE_CTRL_hdcp1x_amute_ctrlGet
//  Description : Set the value of the member HDCP_MUTE_CTRL.hdcp1x_amute_ctrl
//  Input       : unsigned int uhdcp1x_amute_ctrl: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP_MUTE_CTRL_hdcp1x_amute_ctrlGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP_MUTE_CTRL o_hdcp_mute_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP_MUTE_CTRL.u32);
    o_hdcp_mute_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp_mute_ctrl.bits.hdcp1x_amute_ctrl;
}

//******************************************************************************
//  Function    : HDMI_HDCP_MUTE_CTRL_hdcp1x_vmute_ctrlGet
//  Description : Set the value of the member HDCP_MUTE_CTRL.hdcp1x_vmute_ctrl
//  Input       : unsigned int uhdcp1x_vmute_ctrl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP_MUTE_CTRL_hdcp1x_vmute_ctrlGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP_MUTE_CTRL o_hdcp_mute_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP_MUTE_CTRL.u32);
    o_hdcp_mute_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp_mute_ctrl.bits.hdcp1x_vmute_ctrl;
}

//******************************************************************************
//  Function    : HDMI_HDCP_FUN_SEL_hdcp_fun_selSet
//  Description : Set the value of the member HDCP_FUN_SEL.hdcp_fun_sel
//  Input       : unsigned int uhdcp_fun_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP_FUN_SEL_hdcp_fun_selSet(unsigned int uhdcp_fun_sel)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP_FUN_SEL o_hdcp_fun_sel;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP_FUN_SEL.u32);
    o_hdcp_fun_sel.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp_fun_sel.bits.hdcp_fun_sel = uhdcp_fun_sel;
    HDMITXRegWrite(pu32RegAddr, o_hdcp_fun_sel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP_FUN_SEL_hdcp_fun_selGet
//  Description : Set the value of the member HDCP_FUN_SEL.hdcp_fun_sel
//  Input       : unsigned int uhdcp_fun_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP_FUN_SEL_hdcp_fun_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP_FUN_SEL o_hdcp_fun_sel;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP_FUN_SEL.u32);
    o_hdcp_fun_sel.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp_fun_sel.bits.hdcp_fun_sel;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SEC_CFG_hdcp1x_sec_rpt_onSet
//  Description : Set the value of the member HDCP1X_SEC_CFG.hdcp1x_sec_rpt_on
//  Input       : unsigned int uhdcp1x_sec_rpt_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SEC_CFG_hdcp1x_sec_rpt_onSet(unsigned int uhdcp1x_sec_rpt_on)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SEC_CFG o_hdcp1x_sec_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SEC_CFG.u32);
    o_hdcp1x_sec_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_sec_cfg.bits.hdcp1x_sec_rpt_on = uhdcp1x_sec_rpt_on;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_sec_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SEC_CFG_hdcp1x_sec_enc_enSet
//  Description : Set the value of the member HDCP1X_SEC_CFG.hdcp1x_sec_enc_en
//  Input       : unsigned int uhdcp1x_sec_enc_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SEC_CFG_hdcp1x_sec_enc_enSet(unsigned int uhdcp1x_sec_enc_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SEC_CFG o_hdcp1x_sec_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SEC_CFG.u32);
    o_hdcp1x_sec_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_sec_cfg.bits.hdcp1x_sec_enc_en = uhdcp1x_sec_enc_en;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_sec_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_CTRL_hdcp1x_rpt_onGet
//  Description : Set the value of the member HDCP1X_ENG_CTRL.hdcp1x_rpt_on
//  Input       : unsigned int uhdcp1x_rpt_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_CTRL_hdcp1x_rpt_onGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_CTRL o_hdcp1x_eng_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_CTRL.u32);
    o_hdcp1x_eng_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_ctrl.bits.hdcp1x_rpt_on;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_CTRL_hdcp1x_an_stopSet
//  Description : Set the value of the member HDCP1X_ENG_CTRL.hdcp1x_an_stop
//  Input       : unsigned int uhdcp1x_an_stop: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_CTRL_hdcp1x_an_stopSet(unsigned int uhdcp1x_an_stop)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_CTRL o_hdcp1x_eng_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_CTRL.u32);
    o_hdcp1x_eng_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_eng_ctrl.bits.hdcp1x_an_stop = uhdcp1x_an_stop;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_eng_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_CTRL_hdcp1x_enc_enGet
//  Description : Set the value of the member HDCP1X_ENG_CTRL.hdcp1x_enc_en
//  Input       : unsigned int uhdcp1x_enc_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_CTRL_hdcp1x_enc_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_CTRL o_hdcp1x_eng_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_CTRL.u32);
    o_hdcp1x_eng_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_ctrl.bits.hdcp1x_enc_en;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_STATUS_hdcp1x_ri_rdyGet
//  Description : Set the value of the member HDCP1X_ENG_STATUS.hdcp1x_ri_rdy
//  Input       : unsigned int uhdcp1x_ri_rdy: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_STATUS_hdcp1x_ri_rdyGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_STATUS o_hdcp1x_eng_status;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_STATUS.u32);
    o_hdcp1x_eng_status.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_status.bits.hdcp1x_ri_rdy;
}
//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_STATUS_hdcp1x_bksv_errGet
//  Description : Set the value of the member HDCP1X_ENG_STATUS.hdcp1x_bksv_err
//  Input       : unsigned int uhdcp1x_bksv_err: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_STATUS_hdcp1x_bksv_errGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_STATUS o_hdcp1x_eng_status;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_STATUS.u32);
    o_hdcp1x_eng_status.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_status.bits.hdcp1x_bksv_err;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_STATUS_hdcp1x_i_cntGet
//  Description : Set the value of the member HDCP1X_ENG_STATUS.hdcp1x_i_cnt
//  Input       : unsigned int uhdcp1x_i_cnt: 7 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_STATUS_hdcp1x_i_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_STATUS o_hdcp1x_eng_status;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_STATUS.u32);
    o_hdcp1x_eng_status.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_status.bits.hdcp1x_i_cnt;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte3Set
//  Description : Set the value of the member HDCP1X_ENG_BKSV0.hdcp1x_key_bksv_byte3
//  Input       : unsigned int uhdcp1x_key_bksv_byte3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte3Set(unsigned int uhdcp1x_key_bksv_byte3)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_BKSV0 o_hdcp1x_eng_bksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_BKSV0.u32);
    o_hdcp1x_eng_bksv0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_eng_bksv0.bits.hdcp1x_key_bksv_byte3 = uhdcp1x_key_bksv_byte3;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_eng_bksv0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte2Set
//  Description : Set the value of the member HDCP1X_ENG_BKSV0.hdcp1x_key_bksv_byte2
//  Input       : unsigned int uhdcp1x_key_bksv_byte2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte2Set(unsigned int uhdcp1x_key_bksv_byte2)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_BKSV0 o_hdcp1x_eng_bksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_BKSV0.u32);
    o_hdcp1x_eng_bksv0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_eng_bksv0.bits.hdcp1x_key_bksv_byte2 = uhdcp1x_key_bksv_byte2;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_eng_bksv0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte1Set
//  Description : Set the value of the member HDCP1X_ENG_BKSV0.hdcp1x_key_bksv_byte1
//  Input       : unsigned int uhdcp1x_key_bksv_byte1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte1Set(unsigned int uhdcp1x_key_bksv_byte1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_BKSV0 o_hdcp1x_eng_bksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_BKSV0.u32);
    o_hdcp1x_eng_bksv0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_eng_bksv0.bits.hdcp1x_key_bksv_byte1 = uhdcp1x_key_bksv_byte1;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_eng_bksv0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte0Set
//  Description : Set the value of the member HDCP1X_ENG_BKSV0.hdcp1x_key_bksv_byte0
//  Input       : unsigned int uhdcp1x_key_bksv_byte0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_BKSV0_hdcp1x_key_bksv_byte0Set(unsigned int uhdcp1x_key_bksv_byte0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_BKSV0 o_hdcp1x_eng_bksv0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_BKSV0.u32);
    o_hdcp1x_eng_bksv0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_eng_bksv0.bits.hdcp1x_key_bksv_byte0 = uhdcp1x_key_bksv_byte0;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_eng_bksv0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_BKSV1_hdcp1x_key_bksv_byte4Set
//  Description : Set the value of the member HDCP1X_ENG_BKSV1.hdcp1x_key_bksv_byte4
//  Input       : unsigned int uhdcp1x_key_bksv_byte4: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_BKSV1_hdcp1x_key_bksv_byte4Set(unsigned int uhdcp1x_key_bksv_byte4)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_BKSV1 o_hdcp1x_eng_bksv1;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_BKSV1.u32);
    o_hdcp1x_eng_bksv1.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_eng_bksv1.bits.hdcp1x_key_bksv_byte4 = uhdcp1x_key_bksv_byte4;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_eng_bksv1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_GEN_AN0_hdcp1x_eng_gen_an0Get
//  Description : Set the value of the member HDCP1X_ENG_GEN_AN0.hdcp1x_eng_gen_an0
//  Input       : unsigned int uhdcp1x_eng_gen_an0: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_GEN_AN0_hdcp1x_eng_gen_an0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_GEN_AN0 o_hdcp1x_eng_gen_an0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_GEN_AN0.u32);
    o_hdcp1x_eng_gen_an0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_gen_an0.bits.hdcp1x_eng_gen_an0;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_GEN_AN1_hdcp1x_eng_gen_an1Get
//  Description : Set the value of the member HDCP1X_ENG_GEN_AN1.hdcp1x_eng_gen_an1
//  Input       : unsigned int uhdcp1x_eng_gen_an1: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_GEN_AN1_hdcp1x_eng_gen_an1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_GEN_AN1 o_hdcp1x_eng_gen_an1;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_GEN_AN1.u32);
    o_hdcp1x_eng_gen_an1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_gen_an1.bits.hdcp1x_eng_gen_an1;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_RI_hdcp1x_eng_ri1Get
//  Description : Set the value of the member HDCP1X_ENG_RI.hdcp1x_eng_ri1
//  Input       : unsigned int uhdcp1x_eng_ri1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_RI_hdcp1x_eng_ri1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_RI o_hdcp1x_eng_ri;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_RI.u32);
    o_hdcp1x_eng_ri.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_ri.bits.hdcp1x_eng_ri1;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_ENG_RI_hdcp1x_eng_ri0Get
//  Description : Set the value of the member HDCP1X_ENG_RI.hdcp1x_eng_ri0
//  Input       : unsigned int uhdcp1x_eng_ri0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_ENG_RI_hdcp1x_eng_ri0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_ENG_RI o_hdcp1x_eng_ri;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_ENG_RI.u32);
    o_hdcp1x_eng_ri.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_eng_ri.bits.hdcp1x_eng_ri0;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_RPT_BSTATUS_hdcp1x_bstatusSet
//  Description : Set the value of the member HDCP1X_RPT_BSTATUS.hdcp1x_bstatus
//  Input       : unsigned int uhdcp1x_bstatus: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_RPT_BSTATUS_hdcp1x_bstatusSet(unsigned int uhdcp1x_bstatus)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_RPT_BSTATUS o_hdcp1x_rpt_bstatus;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_RPT_BSTATUS.u32);
    o_hdcp1x_rpt_bstatus.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_rpt_bstatus.bits.hdcp1x_bstatus = uhdcp1x_bstatus;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_rpt_bstatus.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_RPT_KLIST_hdcp1x_rpt_klistSet
//  Description : Set the value of the member HDCP1X_RPT_KLIST.hdcp1x_rpt_klist
//  Input       : unsigned int uhdcp1x_rpt_klist: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_RPT_KLIST_hdcp1x_rpt_klistSet(unsigned int uhdcp1x_rpt_klist)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_RPT_KLIST o_hdcp1x_rpt_klist;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_RPT_KLIST.u32);
    o_hdcp1x_rpt_klist.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_rpt_klist.bits.hdcp1x_rpt_klist = uhdcp1x_rpt_klist;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_rpt_klist.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_readyGet
//  Description : Set the value of the member HDCP1X_SHA_CTRL.hdcp1x_sha_ready
//  Input       : unsigned int uhdcp1x_sha_ready: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_readyGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_CTRL o_hdcp1x_sha_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_CTRL.u32);
    o_hdcp1x_sha_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_ctrl.bits.hdcp1x_sha_ready;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_no_dsSet
//  Description : Set the value of the member HDCP1X_SHA_CTRL.hdcp1x_sha_no_ds
//  Input       : unsigned int uhdcp1x_sha_no_ds: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_no_dsSet(unsigned int uhdcp1x_sha_no_ds)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_CTRL o_hdcp1x_sha_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_CTRL.u32);
    o_hdcp1x_sha_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_sha_ctrl.bits.hdcp1x_sha_no_ds = uhdcp1x_sha_no_ds;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_sha_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_startSet
//  Description : Set the value of the member HDCP1X_SHA_CTRL.hdcp1x_sha_start
//  Input       : unsigned int uhdcp1x_sha_start: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_startSet(unsigned int uhdcp1x_sha_start)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_CTRL o_hdcp1x_sha_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_CTRL.u32);
    o_hdcp1x_sha_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_sha_ctrl.bits.hdcp1x_sha_start = uhdcp1x_sha_start;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_sha_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_startGet
//  Description : Set the value of the member HDCP1X_SHA_CTRL.hdcp1x_sha_start
//  Input       : unsigned int uhdcp1x_sha_start: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_CTRL_hdcp1x_sha_startGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_CTRL o_hdcp1x_sha_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_CTRL.u32);
    o_hdcp1x_sha_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_ctrl.bits.hdcp1x_sha_start;
}
//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_V0_hdcp1x_rpt_vh0Get
//  Description : Set the value of the member HDCP1X_SHA_V0.hdcp1x_rpt_vh0
//  Input       : unsigned int uhdcp1x_rpt_vh0: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_V0_hdcp1x_rpt_vh0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_V0 o_hdcp1x_sha_v0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_V0.u32);
    o_hdcp1x_sha_v0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_v0.bits.hdcp1x_rpt_vh0;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_V1_hdcp1x_rpt_vh1Get
//  Description : Set the value of the member HDCP1X_SHA_V1.hdcp1x_rpt_vh1
//  Input       : unsigned int uhdcp1x_rpt_vh1: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_V1_hdcp1x_rpt_vh1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_V1 o_hdcp1x_sha_v1;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_V1.u32);
    o_hdcp1x_sha_v1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_v1.bits.hdcp1x_rpt_vh1;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_V2_hdcp1x_rpt_vh2Get
//  Description : Set the value of the member HDCP1X_SHA_V2.hdcp1x_rpt_vh2
//  Input       : unsigned int uhdcp1x_rpt_vh2: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_V2_hdcp1x_rpt_vh2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_V2 o_hdcp1x_sha_v2;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_V2.u32);
    o_hdcp1x_sha_v2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_v2.bits.hdcp1x_rpt_vh2;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_V3_hdcp1x_rpt_vh3Get
//  Description : Set the value of the member HDCP1X_SHA_V3.hdcp1x_rpt_vh3
//  Input       : unsigned int uhdcp1x_rpt_vh3: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_V3_hdcp1x_rpt_vh3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_V3 o_hdcp1x_sha_v3;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_V3.u32);
    o_hdcp1x_sha_v3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_v3.bits.hdcp1x_rpt_vh3;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_V4_hdcp1x_rpt_vh4Get
//  Description : Set the value of the member HDCP1X_SHA_V4.hdcp1x_rpt_vh4
//  Input       : unsigned int uhdcp1x_rpt_vh4: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_V4_hdcp1x_rpt_vh4Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_V4 o_hdcp1x_sha_v4;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_V4.u32);
    o_hdcp1x_sha_v4.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_v4.bits.hdcp1x_rpt_vh4;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_CHK_CTRL_hdcp1x_auto_check_enSet
//  Description : Set the value of the member HDCP1X_CHK_CTRL.hdcp1x_auto_check_en
//  Input       : unsigned int uhdcp1x_auto_check_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_CHK_CTRL_hdcp1x_auto_check_enSet(unsigned int uhdcp1x_auto_check_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_CHK_CTRL o_hdcp1x_chk_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_CHK_CTRL.u32);
    o_hdcp1x_chk_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_chk_ctrl.bits.hdcp1x_auto_check_en = uhdcp1x_auto_check_en;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_chk_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_CHK_ERR_hdcp1x_nodone_err_cntGet
//  Description : Set the value of the member HDCP1X_CHK_ERR.hdcp1x_nodone_err_cnt
//  Input       : unsigned int uhdcp1x_nodone_err_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_CHK_ERR_hdcp1x_nodone_err_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_CHK_ERR o_hdcp1x_chk_err;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_CHK_ERR.u32);
    o_hdcp1x_chk_err.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_chk_err.bits.hdcp1x_nodone_err_cnt;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_CHK_ERR_hdcp1x_notchg_err_cntGet
//  Description : Set the value of the member HDCP1X_CHK_ERR.hdcp1x_notchg_err_cnt
//  Input       : unsigned int uhdcp1x_notchg_err_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_CHK_ERR_hdcp1x_notchg_err_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_CHK_ERR o_hdcp1x_chk_err;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_CHK_ERR.u32);
    o_hdcp1x_chk_err.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_chk_err.bits.hdcp1x_notchg_err_cnt;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_CHK_ERR_hdcp1x_000frm_err_cntGet
//  Description : Set the value of the member HDCP1X_CHK_ERR.hdcp1x_000frm_err_cnt
//  Input       : unsigned int uhdcp1x_000frm_err_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_CHK_ERR_hdcp1x_000frm_err_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_CHK_ERR o_hdcp1x_chk_err;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_CHK_ERR.u32);
    o_hdcp1x_chk_err.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_chk_err.bits.hdcp1x_000frm_err_cnt;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_CHK_ERR_hdcp1x_127frm_err_cntGet
//  Description : Set the value of the member HDCP1X_CHK_ERR.hdcp1x_127frm_err_cnt
//  Input       : unsigned int uhdcp1x_127frm_err_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_CHK_ERR_hdcp1x_127frm_err_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_CHK_ERR o_hdcp1x_chk_err;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_CHK_ERR.u32);
    o_hdcp1x_chk_err.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_chk_err.bits.hdcp1x_127frm_err_cnt;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_CHK_STATE_hdcp1x_fsm_stateGet
//  Description : Set the value of the member HDCP1X_CHK_STATE.hdcp1x_fsm_state
//  Input       : unsigned int uhdcp1x_fsm_state: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_CHK_STATE_hdcp1x_fsm_stateGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_CHK_STATE o_hdcp1x_chk_state;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_CHK_STATE.u32);
    o_hdcp1x_chk_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_chk_state.bits.hdcp1x_fsm_state;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_RPT_V0_hdcp1x_rpt_calc_vh0Set
//  Description : Set the value of the member HDCP1X_RPT_V0.hdcp1x_rpt_calc_vh0
//  Input       : unsigned int uhdcp1x_rpt_calc_vh0: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_RPT_V0_hdcp1x_rpt_calc_vh0Set(unsigned int uhdcp1x_rpt_calc_vh0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_RPT_V0 o_hdcp1x_rpt_v0;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_RPT_V0.u32);
    o_hdcp1x_rpt_v0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_rpt_v0.bits.hdcp1x_rpt_calc_vh0 = uhdcp1x_rpt_calc_vh0;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_rpt_v0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_RPT_V1_hdcp1x_rpt_calc_vh1Set
//  Description : Set the value of the member HDCP1X_RPT_V1.hdcp1x_rpt_calc_vh1
//  Input       : unsigned int uhdcp1x_rpt_calc_vh1: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_RPT_V1_hdcp1x_rpt_calc_vh1Set(unsigned int uhdcp1x_rpt_calc_vh1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_RPT_V1 o_hdcp1x_rpt_v1;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_RPT_V1.u32);
    o_hdcp1x_rpt_v1.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_rpt_v1.bits.hdcp1x_rpt_calc_vh1 = uhdcp1x_rpt_calc_vh1;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_rpt_v1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_RPT_V2_hdcp1x_rpt_calc_vh2Set
//  Description : Set the value of the member HDCP1X_RPT_V2.hdcp1x_rpt_calc_vh2
//  Input       : unsigned int uhdcp1x_rpt_calc_vh2: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_RPT_V2_hdcp1x_rpt_calc_vh2Set(unsigned int uhdcp1x_rpt_calc_vh2)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_RPT_V2 o_hdcp1x_rpt_v2;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_RPT_V2.u32);
    o_hdcp1x_rpt_v2.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_rpt_v2.bits.hdcp1x_rpt_calc_vh2 = uhdcp1x_rpt_calc_vh2;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_rpt_v2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_RPT_V3_hdcp1x_rpt_calc_vh3Set
//  Description : Set the value of the member HDCP1X_RPT_V3.hdcp1x_rpt_calc_vh3
//  Input       : unsigned int uhdcp1x_rpt_calc_vh3: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_RPT_V3_hdcp1x_rpt_calc_vh3Set(unsigned int uhdcp1x_rpt_calc_vh3)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_RPT_V3 o_hdcp1x_rpt_v3;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_RPT_V3.u32);
    o_hdcp1x_rpt_v3.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_rpt_v3.bits.hdcp1x_rpt_calc_vh3 = uhdcp1x_rpt_calc_vh3;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_rpt_v3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_RPT_V4_hdcp1x_rpt_calc_vh4Set
//  Description : Set the value of the member HDCP1X_RPT_V4.hdcp1x_rpt_calc_vh4
//  Input       : unsigned int uhdcp1x_rpt_calc_vh4: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_RPT_V4_hdcp1x_rpt_calc_vh4Set(unsigned int uhdcp1x_rpt_calc_vh4)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_RPT_V4 o_hdcp1x_rpt_v4;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_RPT_V4.u32);
    o_hdcp1x_rpt_v4.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_rpt_v4.bits.hdcp1x_rpt_calc_vh4 = uhdcp1x_rpt_calc_vh4;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_rpt_v4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_CHECK_hdcp1x_sha_checkSet
//  Description : Set the value of the member HDCP1X_SHA_CHECK.hdcp1x_sha_check
//  Input       : unsigned int uhdcp1x_sha_check: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_CHECK_hdcp1x_sha_checkSet(unsigned int uhdcp1x_sha_check)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_CHECK o_hdcp1x_sha_check;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_CHECK.u32);
    o_hdcp1x_sha_check.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp1x_sha_check.bits.hdcp1x_sha_check = uhdcp1x_sha_check;
    HDMITXRegWrite(pu32RegAddr, o_hdcp1x_sha_check.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_RESULT_hdcp1x_sha_invalidGet
//  Description : Set the value of the member HDCP1X_SHA_RESULT.hdcp1x_sha_invalid
//  Input       : unsigned int uhdcp1x_sha_invalid: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_RESULT_hdcp1x_sha_invalidGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_RESULT o_hdcp1x_sha_result;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_RESULT.u32);
    o_hdcp1x_sha_result.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_result.bits.hdcp1x_sha_invalid;
}

//******************************************************************************
//  Function    : HDMI_HDCP1X_SHA_RESULT_hdcp1x_sha_okGet
//  Description : Set the value of the member HDCP1X_SHA_RESULT.hdcp1x_sha_ok
//  Input       : unsigned int uhdcp1x_sha_ok: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP1X_SHA_RESULT_hdcp1x_sha_okGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP1X_SHA_RESULT o_hdcp1x_sha_result;
    pu32RegAddr = (HI_U32*)&(goptx_hdcp_regAllReg->HDCP1X_SHA_RESULT.u32);
    o_hdcp1x_sha_result.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp1x_sha_result.bits.hdcp1x_sha_ok;
}
