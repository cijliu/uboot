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
#include "hdmi_reg_ctrl.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module tx_ctrl_reg */
volatile S_tx_ctrl_reg_REGS_TYPE *goptx_ctrl_regAllReg = NULL;


int HDMI_TX_S_tx_ctrl_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
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

    goptx_ctrl_regAllReg = (volatile S_tx_ctrl_reg_REGS_TYPE *)(pcAddr + HDMI_TX_BASE_ADDR_CTRL);

    return HI_SUCCESS;
}

int HDMI_TX_S_tx_ctrl_reg_REGS_TYPE_DeInit(void)
{
    if (goptx_ctrl_regAllReg)
    {
        goptx_ctrl_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_PWD_RST_CTRL_tx_mcu_srst_reqSet
//  Description : Set the value of the member TX_PWD_RST_CTRL.tx_mcu_srst_req
//  Input       : unsigned int utx_mcu_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_PWD_RST_CTRL_tx_mcu_srst_reqSet(unsigned int utx_mcu_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_PWD_RST_CTRL o_tx_pwd_rst_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->TX_PWD_RST_CTRL.u32);
    o_tx_pwd_rst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_pwd_rst_ctrl.bits.tx_mcu_srst_req = utx_mcu_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_tx_pwd_rst_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_PWD_RST_CTRL_tx_afifo_srst_reqSet
//  Description : Set the value of the member TX_PWD_RST_CTRL.tx_afifo_srst_req
//  Input       : unsigned int utx_afifo_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_PWD_RST_CTRL_tx_afifo_srst_reqSet(unsigned int utx_afifo_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_PWD_RST_CTRL o_tx_pwd_rst_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->TX_PWD_RST_CTRL.u32);
    o_tx_pwd_rst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_pwd_rst_ctrl.bits.tx_afifo_srst_req = utx_afifo_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_tx_pwd_rst_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_PWD_RST_CTRL_tx_acr_srst_reqSet
//  Description : Set the value of the member TX_PWD_RST_CTRL.tx_acr_srst_req
//  Input       : unsigned int utx_acr_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_PWD_RST_CTRL_tx_acr_srst_reqSet(unsigned int utx_acr_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_PWD_RST_CTRL o_tx_pwd_rst_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->TX_PWD_RST_CTRL.u32);
    o_tx_pwd_rst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_pwd_rst_ctrl.bits.tx_acr_srst_req = utx_acr_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_tx_pwd_rst_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_PWD_RST_CTRL_tx_aud_srst_reqSet
//  Description : Set the value of the member TX_PWD_RST_CTRL.tx_aud_srst_req
//  Input       : unsigned int utx_aud_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_PWD_RST_CTRL_tx_aud_srst_reqSet(unsigned int utx_aud_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_PWD_RST_CTRL o_tx_pwd_rst_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->TX_PWD_RST_CTRL.u32);
    o_tx_pwd_rst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_pwd_rst_ctrl.bits.tx_aud_srst_req = utx_aud_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_tx_pwd_rst_ctrl.u32);

    return HI_SUCCESS;
}

int HDMI_TX_PWD_RST_CTRL_tx_hdmi_srst_reqSet(unsigned int utx_hdmi_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_PWD_RST_CTRL o_tx_pwd_rst_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->TX_PWD_RST_CTRL.u32);
    o_tx_pwd_rst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_pwd_rst_ctrl.bits.tx_hdmi_srst_req = utx_hdmi_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_tx_pwd_rst_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_PWD_RST_CTRL_tx_pwd_srst_reqSet
//  Description : Set the value of the member TX_PWD_RST_CTRL.tx_pwd_srst_req
//  Input       : unsigned int utx_pwd_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_PWD_RST_CTRL_tx_pwd_srst_reqSet(unsigned int utx_pwd_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_PWD_RST_CTRL o_tx_pwd_rst_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->TX_PWD_RST_CTRL.u32);
    o_tx_pwd_rst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_pwd_rst_ctrl.bits.tx_pwd_srst_req = utx_pwd_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_tx_pwd_rst_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PWD_FIFO_WDATA_pwd_fifo_data_inSet
//  Description : Set the value of the member PWD_FIFO_WDATA.pwd_fifo_data_in
//  Input       : unsigned int upwd_fifo_data_in: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_FIFO_WDATA_pwd_fifo_data_inSet(unsigned int upwd_fifo_data_in)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_FIFO_WDATA o_pwd_fifo_wdata;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_FIFO_WDATA.u32);
    o_pwd_fifo_wdata.u32 = HDMITXRegRead(pu32RegAddr);
    o_pwd_fifo_wdata.bits.pwd_fifo_data_in = upwd_fifo_data_in;
    HDMITXRegWrite(pu32RegAddr, o_pwd_fifo_wdata.u32);


    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PWD_DATA_CNT_pwd_data_out_cntSet
//  Description : Set the value of the member PWD_DATA_CNT.pwd_data_out_cnt
//  Input       : unsigned int upwd_data_out_cnt: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_DATA_CNT_pwd_data_out_cntSet(unsigned int upwd_data_out_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_DATA_CNT o_pwd_data_cnt;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_DATA_CNT.u32);
    o_pwd_data_cnt.u32 = HDMITXRegRead(pu32RegAddr);
    o_pwd_data_cnt.bits.pwd_data_out_cnt = upwd_data_out_cnt;
    HDMITXRegWrite(pu32RegAddr, o_pwd_data_cnt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PWD_SLAVE_CFG_pwd_slave_segSet
//  Description : Set the value of the member PWD_SLAVE_CFG.pwd_slave_seg
//  Input       : unsigned int upwd_slave_seg: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_SLAVE_CFG_pwd_slave_segSet(unsigned int upwd_slave_seg)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_SLAVE_CFG o_pwd_slave_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_SLAVE_CFG.u32);
    o_pwd_slave_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_pwd_slave_cfg.bits.pwd_slave_seg = upwd_slave_seg;
    HDMITXRegWrite(pu32RegAddr, o_pwd_slave_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PWD_SLAVE_CFG_pwd_slave_offsetSet
//  Description : Set the value of the member PWD_SLAVE_CFG.pwd_slave_offset
//  Input       : unsigned int upwd_slave_offset: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_SLAVE_CFG_pwd_slave_offsetSet(unsigned int upwd_slave_offset)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_SLAVE_CFG o_pwd_slave_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_SLAVE_CFG.u32);
    o_pwd_slave_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_pwd_slave_cfg.bits.pwd_slave_offset = upwd_slave_offset;
    HDMITXRegWrite(pu32RegAddr, o_pwd_slave_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PWD_SLAVE_CFG_pwd_slave_addrSet
//  Description : Set the value of the member PWD_SLAVE_CFG.pwd_slave_addr
//  Input       : unsigned int upwd_slave_addr: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_SLAVE_CFG_pwd_slave_addrSet(unsigned int upwd_slave_addr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_SLAVE_CFG o_pwd_slave_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_SLAVE_CFG.u32);
    o_pwd_slave_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_pwd_slave_cfg.bits.pwd_slave_addr = upwd_slave_addr;
    HDMITXRegWrite(pu32RegAddr, o_pwd_slave_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PWD_MST_CMD_pwd_mst_cmdSet
//  Description : Set the value of the member PWD_MST_CMD.pwd_mst_cmd
//  Input       : unsigned int upwd_mst_cmd: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_MST_CMD_pwd_mst_cmdSet(unsigned int upwd_mst_cmd)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_MST_CMD o_pwd_mst_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_MST_CMD.u32);
    o_pwd_mst_cmd.u32 = HDMITXRegRead(pu32RegAddr);
    o_pwd_mst_cmd.bits.pwd_mst_cmd = upwd_mst_cmd;
    HDMITXRegWrite(pu32RegAddr, o_pwd_mst_cmd.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DDC_MST_ARB_REQ_cpu_ddc_reqSet
//  Description : Set the value of the member DDC_MST_ARB_REQ.cpu_ddc_req
//  Input       : unsigned int ucpu_ddc_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MST_ARB_REQ_cpu_ddc_reqSet(unsigned int ucpu_ddc_req)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DDC_MST_ARB_REQ o_ddc_mst_arb_req;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->DDC_MST_ARB_REQ.u32);
    o_ddc_mst_arb_req.u32 = HDMITXRegRead(pu32RegAddr);
    o_ddc_mst_arb_req.bits.cpu_ddc_req = ucpu_ddc_req;
    HDMITXRegWrite(pu32RegAddr, o_ddc_mst_arb_req.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PWD_FIFO_RDATA_pwd_fifo_data_outGet
//  Description : Set the value of the member PWD_FIFO_RDATA.pwd_fifo_data_out
//  Input       : unsigned int upwd_fifo_data_out: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_FIFO_RDATA_pwd_fifo_data_outGet(void)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_FIFO_RDATA o_pwd_fifo_rdata;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_FIFO_RDATA.u32);
    o_pwd_fifo_rdata.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pwd_fifo_rdata.bits.pwd_fifo_data_out;
}

//******************************************************************************
//  Function    : HDMI_PWD_DATA_CNT_pwd_fifo_data_cntGet
//  Description : Set the value of the member PWD_DATA_CNT.pwd_fifo_data_cnt
//  Input       : unsigned int upwd_fifo_data_cnt: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_DATA_CNT_pwd_fifo_data_cntGet(void)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_DATA_CNT o_pwd_data_cnt;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_DATA_CNT.u32);
    o_pwd_data_cnt.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pwd_data_cnt.bits.pwd_fifo_data_cnt;
}

//******************************************************************************
//  Function    : HDMI_PWD_MST_STATE_pwd_fifo_emptyGet
//  Description : Set the value of the member PWD_MST_STATE.pwd_fifo_empty
//  Input       : unsigned int upwd_fifo_empty: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_MST_STATE_pwd_fifo_emptyGet(void)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_MST_STATE o_pwd_mst_state;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_MST_STATE.u32);
    o_pwd_mst_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pwd_mst_state.bits.pwd_fifo_empty;
}

//******************************************************************************
//  Function    : HDMI_PWD_MST_STATE_pwd_i2c_in_progGet
//  Description : Set the value of the member PWD_MST_STATE.pwd_i2c_in_prog
//  Input       : unsigned int upwd_i2c_in_prog: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PWD_MST_STATE_pwd_i2c_in_progGet(void)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PWD_MST_STATE o_pwd_mst_state;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->PWD_MST_STATE.u32);
    o_pwd_mst_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_pwd_mst_state.bits.pwd_i2c_in_prog;
}

//******************************************************************************
//  Function    : HDMI_DDC_MST_ARB_ACK_cpu_ddc_req_ackGet
//  Description : Set the value of the member DDC_MST_ARB_ACK.cpu_ddc_req_ack
//  Input       : unsigned int ucpu_ddc_req_ack: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MST_ARB_ACK_cpu_ddc_req_ackGet(void)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DDC_MST_ARB_ACK o_ddc_mst_arb_ack;
    pu32RegAddr = (HI_U32*)&(goptx_ctrl_regAllReg->DDC_MST_ARB_ACK.u32);
    o_ddc_mst_arb_ack.u32 = HDMITXRegRead(pu32RegAddr);
    return o_ddc_mst_arb_ack.bits.cpu_ddc_req_ack;
}

