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
#include "hdmi_reg_cec.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module tx_cec_reg */
volatile S_tx_cec_reg_REGS_TYPE *goptx_cec_regAllReg = NULL;


int HDMI_TX_S_tx_cec_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
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

    goptx_cec_regAllReg = (volatile S_tx_cec_reg_REGS_TYPE *)(pcAddr + HDMI_TX_BASE_ADDR_CEC);

    return HI_SUCCESS;

}

int HDMI_TX_S_tx_cec_reg_REGS_TYPE_DeInit(void)
{
    if (goptx_cec_regAllReg)
    {
        goptx_cec_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_START_PRIOD_cec_start_low_priodSet
//  Description : Set the value of the member CEC_START_PRIOD.cec_start_low_priod
//  Input       : unsigned int ucec_start_low_priod: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_START_PRIOD_cec_start_low_priodSet(unsigned int ucec_start_low_priod)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_START_PRIOD o_cec_start_priod;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_START_PRIOD.u32);
    o_cec_start_priod.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_start_priod.bits.cec_start_low_priod = ucec_start_low_priod;
    HDMITXRegWrite(pu32RegAddr, o_cec_start_priod.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_cec_reg_rx_clr_allSet
//  Description : Set the value of the member CEC_TX_CTRL.cec_reg_rx_clr_all
//  Input       : unsigned int ucec_reg_rx_clr_all: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_cec_reg_rx_clr_allSet(unsigned int ucec_reg_rx_clr_all)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.cec_reg_rx_clr_all = ucec_reg_rx_clr_all;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_cec_reg_rx_clr_cur_setSet
//  Description : Set the value of the member CEC_TX_CTRL.cec_reg_rx_clr_cur_set
//  Input       : unsigned int ucec_reg_rx_clr_cur_set: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_cec_reg_rx_clr_cur_setSet(unsigned int ucec_reg_rx_clr_cur_set)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.cec_reg_rx_clr_cur_set = ucec_reg_rx_clr_cur_set;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_cec_reg_tx_retry_limitSet
//  Description : Set the value of the member CEC_TX_CTRL.cec_reg_tx_retry_limit
//  Input       : unsigned int ucec_reg_tx_retry_limit: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_cec_reg_tx_retry_limitSet(unsigned int ucec_reg_tx_retry_limit)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.cec_reg_tx_retry_limit = ucec_reg_tx_retry_limit;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_cec_reg_tx_cmd_cntSet
//  Description : Set the value of the member CEC_TX_CTRL.cec_reg_tx_cmd_cnt
//  Input       : unsigned int ucec_reg_tx_cmd_cnt: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_cec_reg_tx_cmd_cntSet(unsigned int ucec_reg_tx_cmd_cnt)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.cec_reg_tx_cmd_cnt = ucec_reg_tx_cmd_cnt;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_cec_reg_i2c_cec_passthruSet
//  Description : Set the value of the member CEC_TX_CTRL.cec_reg_i2c_cec_passthru
//  Input       : unsigned int ucec_reg_i2c_cec_passthru: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_cec_reg_i2c_cec_passthruSet(unsigned int ucec_reg_i2c_cec_passthru)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.cec_reg_i2c_cec_passthru = ucec_reg_i2c_cec_passthru;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_manual_cmd_setSet
//  Description : Set the value of the member CEC_TX_CTRL.manual_cmd_set
//  Input       : unsigned int umanual_cmd_set: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_manual_cmd_setSet(unsigned int umanual_cmd_set)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.manual_cmd_set = umanual_cmd_set;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_cec_reg_flush_tx_ffSet
//  Description : Set the value of the member CEC_TX_CTRL.cec_reg_flush_tx_ff
//  Input       : unsigned int ucec_reg_flush_tx_ff: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_cec_reg_flush_tx_ffSet(unsigned int ucec_reg_flush_tx_ff)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.cec_reg_flush_tx_ff = ucec_reg_flush_tx_ff;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_CTRL_cec_reg_nack_hdrSet
//  Description : Set the value of the member CEC_TX_CTRL.cec_reg_nack_hdr
//  Input       : unsigned int ucec_reg_nack_hdr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_CTRL_cec_reg_nack_hdrSet(unsigned int ucec_reg_nack_hdr)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_CTRL o_cec_tx_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_CTRL.u32);
    o_cec_tx_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_ctrl.bits.cec_reg_nack_hdr = ucec_reg_nack_hdr;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_AUTO_DISC_cec_auto_ping_clearSet
//  Description : Set the value of the member CEC_AUTO_DISC.cec_auto_ping_clear
//  Input       : unsigned int ucec_auto_ping_clear: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_AUTO_DISC_cec_auto_ping_clearSet(unsigned int ucec_auto_ping_clear)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_AUTO_DISC o_cec_auto_disc;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_AUTO_DISC.u32);
    o_cec_auto_disc.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_auto_disc.bits.cec_auto_ping_clear = ucec_auto_ping_clear;
    HDMITXRegWrite(pu32RegAddr, o_cec_auto_disc.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_AUTO_DISC_cec_auto_ping_startSet
//  Description : Set the value of the member CEC_AUTO_DISC.cec_auto_ping_start
//  Input       : unsigned int ucec_auto_ping_start: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_AUTO_DISC_cec_auto_ping_startSet(unsigned int ucec_auto_ping_start)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_AUTO_DISC o_cec_auto_disc;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_AUTO_DISC.u32);
    o_cec_auto_disc.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_auto_disc.bits.cec_auto_ping_start = ucec_auto_ping_start;
    HDMITXRegWrite(pu32RegAddr, o_cec_auto_disc.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_INIT_cec_tx_init_idSet
//  Description : Set the value of the member CEC_TX_INIT.cec_tx_init_id
//  Input       : unsigned int ucec_tx_init_id: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_INIT_cec_tx_init_idSet(unsigned int ucec_tx_init_id)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_INIT o_cec_tx_init;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_INIT.u32);
    o_cec_tx_init.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_init.bits.cec_tx_init_id = ucec_tx_init_id;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_init.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_TX_DEST_cec_tx_dest_idSet
//  Description : Set the value of the member CEC_TX_DEST.cec_tx_dest_id
//  Input       : unsigned int ucec_tx_dest_id: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_TX_DEST_cec_tx_dest_idSet(unsigned int ucec_tx_dest_id)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_TX_DEST o_cec_tx_dest;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_TX_DEST.u32);
    o_cec_tx_dest.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_tx_dest.bits.cec_tx_dest_id = ucec_tx_dest_id;
    HDMITXRegWrite(pu32RegAddr, o_cec_tx_dest.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_CAPTUTR_ID_cec_capture_idSet
//  Description : Set the value of the member CEC_CAPTUTR_ID.cec_capture_id
//  Input       : unsigned int ucec_capture_id: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_CAPTUTR_ID_cec_capture_idSet(unsigned int ucec_capture_id)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_CAPTUTR_ID o_cec_captutr_id;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_CAPTUTR_ID.u32);
    o_cec_captutr_id.u32 = HDMITXRegRead(pu32RegAddr);
    o_cec_captutr_id.bits.cec_capture_id = ucec_capture_id;
    HDMITXRegWrite(pu32RegAddr, o_cec_captutr_id.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD0_tx_cec_operand2Set
//  Description : Set the value of the member TX_CEC_CMD0.tx_cec_operand2
//  Input       : unsigned int utx_cec_operand2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD0_tx_cec_operand2Set(unsigned int utx_cec_operand2)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD0 o_tx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD0.u32);
    o_tx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd0.bits.tx_cec_operand2 = utx_cec_operand2;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD0_tx_cec_operand1Set
//  Description : Set the value of the member TX_CEC_CMD0.tx_cec_operand1
//  Input       : unsigned int utx_cec_operand1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD0_tx_cec_operand1Set(unsigned int utx_cec_operand1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD0 o_tx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD0.u32);
    o_tx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd0.bits.tx_cec_operand1 = utx_cec_operand1;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD0_tx_cec_operand0Set
//  Description : Set the value of the member TX_CEC_CMD0.tx_cec_operand0
//  Input       : unsigned int utx_cec_operand0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD0_tx_cec_operand0Set(unsigned int utx_cec_operand0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD0 o_tx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD0.u32);
    o_tx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd0.bits.tx_cec_operand0 = utx_cec_operand0;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD0_tx_cec_commandSet
//  Description : Set the value of the member TX_CEC_CMD0.tx_cec_command
//  Input       : unsigned int utx_cec_command: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD0_tx_cec_commandSet(unsigned int utx_cec_command)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD0 o_tx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD0.u32);
    o_tx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd0.bits.tx_cec_command = utx_cec_command;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD1_tx_cec_operand6Set
//  Description : Set the value of the member TX_CEC_CMD1.tx_cec_operand6
//  Input       : unsigned int utx_cec_operand6: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD1_tx_cec_operand6Set(unsigned int utx_cec_operand6)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD1 o_tx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD1.u32);
    o_tx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd1.bits.tx_cec_operand6 = utx_cec_operand6;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD1_tx_cec_operand5Set
//  Description : Set the value of the member TX_CEC_CMD1.tx_cec_operand5
//  Input       : unsigned int utx_cec_operand5: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD1_tx_cec_operand5Set(unsigned int utx_cec_operand5)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD1 o_tx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD1.u32);
    o_tx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd1.bits.tx_cec_operand5 = utx_cec_operand5;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD1_tx_cec_operand4Set
//  Description : Set the value of the member TX_CEC_CMD1.tx_cec_operand4
//  Input       : unsigned int utx_cec_operand4: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD1_tx_cec_operand4Set(unsigned int utx_cec_operand4)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD1 o_tx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD1.u32);
    o_tx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd1.bits.tx_cec_operand4 = utx_cec_operand4;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD1_tx_cec_operand3Set
//  Description : Set the value of the member TX_CEC_CMD1.tx_cec_operand3
//  Input       : unsigned int utx_cec_operand3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD1_tx_cec_operand3Set(unsigned int utx_cec_operand3)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD1 o_tx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD1.u32);
    o_tx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd1.bits.tx_cec_operand3 = utx_cec_operand3;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD2_tx_cec_operand10Set
//  Description : Set the value of the member TX_CEC_CMD2.tx_cec_operand10
//  Input       : unsigned int utx_cec_operand10: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD2_tx_cec_operand10Set(unsigned int utx_cec_operand10)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD2 o_tx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD2.u32);
    o_tx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd2.bits.tx_cec_operand10 = utx_cec_operand10;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD2_tx_cec_operand9Set
//  Description : Set the value of the member TX_CEC_CMD2.tx_cec_operand9
//  Input       : unsigned int utx_cec_operand9: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD2_tx_cec_operand9Set(unsigned int utx_cec_operand9)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD2 o_tx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD2.u32);
    o_tx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd2.bits.tx_cec_operand9 = utx_cec_operand9;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD2_tx_cec_operand8Set
//  Description : Set the value of the member TX_CEC_CMD2.tx_cec_operand8
//  Input       : unsigned int utx_cec_operand8: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD2_tx_cec_operand8Set(unsigned int utx_cec_operand8)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD2 o_tx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD2.u32);
    o_tx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd2.bits.tx_cec_operand8 = utx_cec_operand8;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD2_tx_cec_operand7Set
//  Description : Set the value of the member TX_CEC_CMD2.tx_cec_operand7
//  Input       : unsigned int utx_cec_operand7: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD2_tx_cec_operand7Set(unsigned int utx_cec_operand7)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD2 o_tx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD2.u32);
    o_tx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd2.bits.tx_cec_operand7 = utx_cec_operand7;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD3_tx_cec_operand14Set
//  Description : Set the value of the member TX_CEC_CMD3.tx_cec_operand14
//  Input       : unsigned int utx_cec_operand14: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD3_tx_cec_operand14Set(unsigned int utx_cec_operand14)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD3 o_tx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD3.u32);
    o_tx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd3.bits.tx_cec_operand14 = utx_cec_operand14;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD3_tx_cec_operand13Set
//  Description : Set the value of the member TX_CEC_CMD3.tx_cec_operand13
//  Input       : unsigned int utx_cec_operand13: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD3_tx_cec_operand13Set(unsigned int utx_cec_operand13)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD3 o_tx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD3.u32);
    o_tx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd3.bits.tx_cec_operand13 = utx_cec_operand13;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD3_tx_cec_operand12Set
//  Description : Set the value of the member TX_CEC_CMD3.tx_cec_operand12
//  Input       : unsigned int utx_cec_operand12: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD3_tx_cec_operand12Set(unsigned int utx_cec_operand12)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD3 o_tx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD3.u32);
    o_tx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd3.bits.tx_cec_operand12 = utx_cec_operand12;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_CEC_CMD3_tx_cec_operand11Set
//  Description : Set the value of the member TX_CEC_CMD3.tx_cec_operand11
//  Input       : unsigned int utx_cec_operand11: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_CEC_CMD3_tx_cec_operand11Set(unsigned int utx_cec_operand11)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_CEC_CMD3 o_tx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->TX_CEC_CMD3.u32);
    o_tx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_cec_cmd3.bits.tx_cec_operand11 = utx_cec_operand11;
    HDMITXRegWrite(pu32RegAddr, o_tx_cec_cmd3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEC_RX_STATE_cec_reg_rx_ff_wr_selGet
//  Description : Set the value of the member CEC_RX_STATE.cec_reg_rx_ff_wr_sel
//  Input       : unsigned int ucec_reg_rx_ff_wr_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_RX_STATE_cec_reg_rx_ff_wr_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_RX_STATE o_cec_rx_state;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_RX_STATE.u32);
    o_cec_rx_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cec_rx_state.bits.cec_reg_rx_ff_wr_sel;
}

//******************************************************************************
//  Function    : HDMI_CEC_RX_STATE_cec_rx_init_cmd_headerGet
//  Description : Set the value of the member CEC_RX_STATE.cec_rx_init_cmd_header
//  Input       : unsigned int ucec_rx_init_cmd_header: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_RX_STATE_cec_rx_init_cmd_headerGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_RX_STATE o_cec_rx_state;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_RX_STATE.u32);
    o_cec_rx_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cec_rx_state.bits.cec_rx_init_cmd_header;
}

//******************************************************************************
//  Function    : HDMI_CEC_RX_STATE_cec_rx_dest_cmd_headerGet
//  Description : Set the value of the member CEC_RX_STATE.cec_rx_dest_cmd_header
//  Input       : unsigned int ucec_rx_dest_cmd_header: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_RX_STATE_cec_rx_dest_cmd_headerGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_RX_STATE o_cec_rx_state;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_RX_STATE.u32);
    o_cec_rx_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cec_rx_state.bits.cec_rx_dest_cmd_header;
}

//******************************************************************************
//  Function    : HDMI_CEC_RX_STATE_cec_rx_errorGet
//  Description : Set the value of the member CEC_RX_STATE.cec_rx_error
//  Input       : unsigned int ucec_rx_error: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_RX_STATE_cec_rx_errorGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_RX_STATE o_cec_rx_state;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_RX_STATE.u32);
    o_cec_rx_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cec_rx_state.bits.cec_rx_error;
}

//******************************************************************************
//  Function    : HDMI_CEC_RX_STATE_cec_reg_rx_cmd_byte_cntGet
//  Description : Set the value of the member CEC_RX_STATE.cec_reg_rx_cmd_byte_cnt
//  Input       : unsigned int ucec_reg_rx_cmd_byte_cnt: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_RX_STATE_cec_reg_rx_cmd_byte_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_RX_STATE o_cec_rx_state;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_RX_STATE.u32);
    o_cec_rx_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cec_rx_state.bits.cec_reg_rx_cmd_byte_cnt;
}

//******************************************************************************
//  Function    : HDMI_CEC_AUTO_DISC_cec_auto_ping_doneGet
//  Description : Set the value of the member CEC_AUTO_DISC.cec_auto_ping_done
//  Input       : unsigned int ucec_auto_ping_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_AUTO_DISC_cec_auto_ping_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_AUTO_DISC o_cec_auto_disc;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_AUTO_DISC.u32);
    o_cec_auto_disc.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cec_auto_disc.bits.cec_auto_ping_done;
}

//******************************************************************************
//  Function    : HDMI_CEC_AUTODISC_MAP_cec_auto_ping_mapGet
//  Description : Set the value of the member CEC_AUTODISC_MAP.cec_auto_ping_map
//  Input       : unsigned int ucec_auto_ping_map: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEC_AUTODISC_MAP_cec_auto_ping_mapGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_CEC_AUTODISC_MAP o_cec_autodisc_map;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->CEC_AUTODISC_MAP.u32);
    o_cec_autodisc_map.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cec_autodisc_map.bits.cec_auto_ping_map;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD0_rx_cec_operand2Get
//  Description : Set the value of the member RX_CEC_CMD0.rx_cec_operand2
//  Input       : unsigned int urx_cec_operand2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD0_rx_cec_operand2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD0 o_rx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD0.u32);
    o_rx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd0.bits.rx_cec_operand2;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD0_rx_cec_operand1Get
//  Description : Set the value of the member RX_CEC_CMD0.rx_cec_operand1
//  Input       : unsigned int urx_cec_operand1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD0_rx_cec_operand1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD0 o_rx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD0.u32);
    o_rx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd0.bits.rx_cec_operand1;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD0_rx_cec_operand0Get
//  Description : Set the value of the member RX_CEC_CMD0.rx_cec_operand0
//  Input       : unsigned int urx_cec_operand0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD0_rx_cec_operand0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD0 o_rx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD0.u32);
    o_rx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd0.bits.rx_cec_operand0;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD0_rx_cec_commandGet
//  Description : Set the value of the member RX_CEC_CMD0.rx_cec_command
//  Input       : unsigned int urx_cec_command: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD0_rx_cec_commandGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD0 o_rx_cec_cmd0;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD0.u32);
    o_rx_cec_cmd0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd0.bits.rx_cec_command;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD1_rx_cec_operand6Get
//  Description : Set the value of the member RX_CEC_CMD1.rx_cec_operand6
//  Input       : unsigned int urx_cec_operand6: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD1_rx_cec_operand6Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD1 o_rx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD1.u32);
    o_rx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd1.bits.rx_cec_operand6;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD1_rx_cec_operand5Get
//  Description : Set the value of the member RX_CEC_CMD1.rx_cec_operand5
//  Input       : unsigned int urx_cec_operand5: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD1_rx_cec_operand5Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD1 o_rx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD1.u32);
    o_rx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd1.bits.rx_cec_operand5;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD1_rx_cec_operand4Get
//  Description : Set the value of the member RX_CEC_CMD1.rx_cec_operand4
//  Input       : unsigned int urx_cec_operand4: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD1_rx_cec_operand4Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD1 o_rx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD1.u32);
    o_rx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd1.bits.rx_cec_operand4;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD1_rx_cec_operand3Get
//  Description : Set the value of the member RX_CEC_CMD1.rx_cec_operand3
//  Input       : unsigned int urx_cec_operand3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD1_rx_cec_operand3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD1 o_rx_cec_cmd1;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD1.u32);
    o_rx_cec_cmd1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd1.bits.rx_cec_operand3;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD2_rx_cec_operand10Get
//  Description : Set the value of the member RX_CEC_CMD2.rx_cec_operand10
//  Input       : unsigned int urx_cec_operand10: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD2_rx_cec_operand10Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD2 o_rx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD2.u32);
    o_rx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd2.bits.rx_cec_operand10;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD2_rx_cec_operand9Get
//  Description : Set the value of the member RX_CEC_CMD2.rx_cec_operand9
//  Input       : unsigned int urx_cec_operand9: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD2_rx_cec_operand9Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD2 o_rx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD2.u32);
    o_rx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd2.bits.rx_cec_operand9;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD2_rx_cec_operand8Get
//  Description : Set the value of the member RX_CEC_CMD2.rx_cec_operand8
//  Input       : unsigned int urx_cec_operand8: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD2_rx_cec_operand8Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD2 o_rx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD2.u32);
    o_rx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd2.bits.rx_cec_operand8;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD2_rx_cec_operand7Get
//  Description : Set the value of the member RX_CEC_CMD2.rx_cec_operand7
//  Input       : unsigned int urx_cec_operand7: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD2_rx_cec_operand7Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD2 o_rx_cec_cmd2;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD2.u32);
    o_rx_cec_cmd2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd2.bits.rx_cec_operand7;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD3_rx_cec_operand14Get
//  Description : Set the value of the member RX_CEC_CMD3.rx_cec_operand14
//  Input       : unsigned int urx_cec_operand14: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD3_rx_cec_operand14Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD3 o_rx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD3.u32);
    o_rx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd3.bits.rx_cec_operand14;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD3_rx_cec_operand13Get
//  Description : Set the value of the member RX_CEC_CMD3.rx_cec_operand13
//  Input       : unsigned int urx_cec_operand13: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD3_rx_cec_operand13Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD3 o_rx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD3.u32);
    o_rx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd3.bits.rx_cec_operand13;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD3_rx_cec_operand12Get
//  Description : Set the value of the member RX_CEC_CMD3.rx_cec_operand12
//  Input       : unsigned int urx_cec_operand12: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD3_rx_cec_operand12Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD3 o_rx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD3.u32);
    o_rx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd3.bits.rx_cec_operand12;
}

//******************************************************************************
//  Function    : HDMI_RX_CEC_CMD3_rx_cec_operand11Get
//  Description : Set the value of the member RX_CEC_CMD3.rx_cec_operand11
//  Input       : unsigned int urx_cec_operand11: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RX_CEC_CMD3_rx_cec_operand11Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_RX_CEC_CMD3 o_rx_cec_cmd3;
    pu32RegAddr = (HI_U32*)&(goptx_cec_regAllReg->RX_CEC_CMD3.u32);
    o_rx_cec_cmd3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_rx_cec_cmd3.bits.rx_cec_operand11;
}

