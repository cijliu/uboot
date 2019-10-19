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

#include "hdmi_reg_frl.h"
#include "hi_type.h"
#include "hdmi_product_define.h"
//#include "hdmi_platform.h"

/* Define the struct pointor of the module tx_frl_reg */
volatile S_tx_frl_reg_REGS_TYPE *goptx_frl_regAllReg = NULL;

#define PRODUCT_NULL_CHK(p) do{\
	if(HI_NULL == p)\
        {\
    	return HI_FAILURE;\
        }\
}while(0)

HI_S32 HDMI_HDMITX_FRL_reg_Init(HI_CHAR *pcAddr)
{
#ifdef HDMI_BUILD_IN_BOOT
    pcAddr = (HI_CHAR *)HDMI_IO_MAP(HDMI_TX_BASE_ADDR, 4);
#else
    if (HI_NULL == pcAddr)
    {
    	HDMI_ERR("pcAddr is NULL! \n");
        return HI_FAILURE;
    }
#endif

	goptx_frl_regAllReg  = (S_tx_frl_reg_REGS_TYPE *)(pcAddr + HDMI_RX_BASE_ADDR_FRL);

    return HI_SUCCESS;
}

HI_S32 HDMI_HDMITX_FRL_reg_DeInit(HI_VOID)
{
    if(HI_NULL != goptx_frl_regAllReg)
    {
        goptx_frl_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;

}
static HI_S32 HDMI21TXRegWrite  (HI_U32 *pu32RegAddr, HI_U32 u32Value)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    //HDMI_ERR("u32Value = %x!!!!!!!\n",u32Value);
    *(volatile HI_U32*)pu32RegAddr = u32Value;
    return HI_SUCCESS;
}


static HI_U32 HDMI21TXRegRead(HI_U32 *pu32RegAddr)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    return *(volatile HI_U32*)(pu32RegAddr);
}
//******************************************************************************
//  Description : Set the value of the member TX_FRL_VERSION.frl_tx_hw_day
//  Input       : unsigned int ufrl_tx_hw_day: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_FRL_VERSION_frl_tx_hw_dayGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_FRL_VERSION o_tx_frl_version;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->TX_FRL_VERSION.u32);
    o_tx_frl_version.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_tx_frl_version.bits.frl_tx_hw_day;
}

//******************************************************************************
//  Function    : HDMI_TX_FRL_VERSION_frl_tx_hw_monthGet
//  Description : Set the value of the member TX_FRL_VERSION.frl_tx_hw_month
//  Input       : unsigned int ufrl_tx_hw_month: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_FRL_VERSION_frl_tx_hw_monthGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_FRL_VERSION o_tx_frl_version;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->TX_FRL_VERSION.u32);
    o_tx_frl_version.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_tx_frl_version.bits.frl_tx_hw_month;
}

//******************************************************************************
//  Function    : HDMI_TX_FRL_VERSION_frl_tx_hw_yearGet
//  Description : Set the value of the member TX_FRL_VERSION.frl_tx_hw_year
//  Input       : unsigned int ufrl_tx_hw_year: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_FRL_VERSION_frl_tx_hw_yearGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TX_FRL_VERSION o_tx_frl_version;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->TX_FRL_VERSION.u32);
    o_tx_frl_version.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_tx_frl_version.bits.frl_tx_hw_year;
}

//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_RDATA_in_ac0_rdataGet
//  Description : Set the value of the member LM_IN_AC0_RDATA.in_ac0_rdata
//  Input       : unsigned int uin_ac0_rdata: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_RDATA_in_ac0_rdataGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_RDATA o_lm_in_ac0_rdata;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_RDATA.u32);
    o_lm_in_ac0_rdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_in_ac0_rdata.bits.in_ac0_rdata;
}

//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_WDATA_in_ac0_wdataSet
//  Description : Set the value of the member LM_IN_AC0_WDATA.in_ac0_wdata
//  Input       : unsigned int uin_ac0_wdata: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_WDATA_in_ac0_wdataSet(unsigned int uin_ac0_wdata)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_WDATA o_lm_in_ac0_wdata;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_WDATA.u32);
    o_lm_in_ac0_wdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_in_ac0_wdata.bits.in_ac0_wdata = uin_ac0_wdata;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_in_ac0_wdata.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_WDATA_in_ac0_wdataGet
//  Description : Set the value of the member LM_IN_AC0_WDATA.in_ac0_wdata
//  Input       : unsigned int uin_ac0_wdata: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_WDATA_in_ac0_wdataGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_WDATA o_lm_in_ac0_wdata;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_WDATA.u32);
    o_lm_in_ac0_wdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_in_ac0_wdata.bits.in_ac0_wdata;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_commandSet
//  Description : Set the value of the member LM_IN_AC0_CMD.command
//  Input       : unsigned int ucommand: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_commandSet(unsigned int ucommand)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_in_ac0_cmd.bits.command = ucommand;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_in_ac0_cmd.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_commandGet
//  Description : Set the value of the member LM_IN_AC0_CMD.command
//  Input       : unsigned int ucommand: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_commandGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_in_ac0_cmd.bits.command;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_protect_numberSet
//  Description : Set the value of the member LM_IN_AC0_CMD.protect_number
//  Input       : unsigned int uprotect_number: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_protect_numberSet(unsigned int uprotect_number)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_in_ac0_cmd.bits.protect_number = uprotect_number;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_in_ac0_cmd.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_protect_numberGet
//  Description : Set the value of the member LM_IN_AC0_CMD.protect_number
//  Input       : unsigned int uprotect_number: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_protect_numberGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_in_ac0_cmd.bits.protect_number;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_in_ac0_numberSet
//  Description : Set the value of the member LM_IN_AC0_CMD.in_ac0_number
//  Input       : unsigned int uin_ac0_number: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_in_ac0_numberSet(unsigned int uin_ac0_number)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_in_ac0_cmd.bits.in_ac0_number = uin_ac0_number;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_in_ac0_cmd.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_in_ac0_numberGet
//  Description : Set the value of the member LM_IN_AC0_CMD.in_ac0_number
//  Input       : unsigned int uin_ac0_number: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_in_ac0_numberGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_in_ac0_cmd.bits.in_ac0_number;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_in_ac0_addrSet
//  Description : Set the value of the member LM_IN_AC0_CMD.in_ac0_addr
//  Input       : unsigned int uin_ac0_addr: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_in_ac0_addrSet(unsigned int uin_ac0_addr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_in_ac0_cmd.bits.in_ac0_addr = uin_ac0_addr;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_in_ac0_cmd.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_IN_AC0_CMD_in_ac0_addrGet
//  Description : Set the value of the member LM_IN_AC0_CMD.in_ac0_addr
//  Input       : unsigned int uin_ac0_addr: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_IN_AC0_CMD_in_ac0_addrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_IN_AC0_CMD o_lm_in_ac0_cmd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_IN_AC0_CMD.u32);
    o_lm_in_ac0_cmd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_in_ac0_cmd.bits.in_ac0_addr;
}
//******************************************************************************
//  Function    : HDMI_LM_COMMAND_EN_command_enSet
//  Description : Set the value of the member LM_COMMAND_EN.command_en
//  Input       : unsigned int ucommand_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_COMMAND_EN_command_enSet(unsigned int ucommand_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_COMMAND_EN o_lm_command_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_COMMAND_EN.u32);
    o_lm_command_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_command_en.bits.command_en = ucommand_en;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_command_en.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_LM_COMMAND_EN_command_enGet
//  Description : Set the value of the member LM_COMMAND_EN.command_en
//  Input       : unsigned int ucommand_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_COMMAND_EN_command_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_COMMAND_EN o_lm_command_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_COMMAND_EN.u32);
    o_lm_command_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_command_en.bits.command_en;
}

//******************************************************************************
//  Function    : HDMI_LM_SRC_EN_scram_enSet
//  Description : Set the value of the member LM_SRC_EN.scram_en
//  Input       : unsigned int uscram_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_EN_scram_enSet(unsigned int uscram_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_EN o_lm_src_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_EN.u32);
    o_lm_src_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_src_en.bits.scram_en = uscram_en;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_src_en.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_SRC_EN_scram_enGet
//  Description : Set the value of the member LM_SRC_EN.scram_en
//  Input       : unsigned int uscram_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_EN_scram_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_EN o_lm_src_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_EN.u32);
    o_lm_src_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_src_en.bits.scram_en;
}
//******************************************************************************
//  Function    : HDMI_LM_SRC_EN_ram_config_enSet
//  Description : Set the value of the member LM_SRC_EN.ram_config_en
//  Input       : unsigned int uram_config_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_EN_ram_config_enSet(unsigned int uram_config_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_EN o_lm_src_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_EN.u32);
    o_lm_src_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_src_en.bits.ram_config_en = uram_config_en;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_src_en.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_SRC_EN_ram_config_enGet
//  Description : Set the value of the member LM_SRC_EN.ram_config_en
//  Input       : unsigned int uram_config_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_EN_ram_config_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_EN o_lm_src_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_EN.u32);
    o_lm_src_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_src_en.bits.ram_config_en;
}
//******************************************************************************
//  Function    : HDMI_AV_MAX_LEN_av_max_lenSet
//  Description : Set the value of the member AV_MAX_LEN.av_max_len
//  Input       : unsigned int uav_max_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AV_MAX_LEN_av_max_lenSet(unsigned int uav_max_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AV_MAX_LEN o_av_max_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->AV_MAX_LEN.u32);
    o_av_max_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_av_max_len.bits.av_max_len = uav_max_len;
    HDMI21TXRegWrite(pu32RegAddr, o_av_max_len.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_AV_MAX_LEN_av_max_lenGet
//  Description : Set the value of the member AV_MAX_LEN.av_max_len
//  Input       : unsigned int uav_max_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AV_MAX_LEN_av_max_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AV_MAX_LEN o_av_max_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->AV_MAX_LEN.u32);
    o_av_max_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_av_max_len.bits.av_max_len;
}



//******************************************************************************
//  Function    : HDMI_AV_GAP_LEN_av_gap_lenSet
//  Description : Set the value of the member AV_GAP_LEN.av_gap_len
//  Input       : unsigned int uav_gap_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AV_GAP_LEN_av_gap_lenSet(unsigned int uav_gap_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AV_GAP_LEN o_av_gap_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->AV_GAP_LEN.u32);
    o_av_gap_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_av_gap_len.bits.av_gap_len = uav_gap_len;
    HDMI21TXRegWrite(pu32RegAddr, o_av_gap_len.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_BLK_MAX_LEN_blk_max_lenSet
//  Description : Set the value of the member BLK_MAX_LEN.blk_max_len
//  Input       : unsigned int ublk_max_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_BLK_MAX_LEN_blk_max_lenSet(unsigned int ublk_max_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_BLK_MAX_LEN o_blk_max_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->BLK_MAX_LEN.u32);
    o_blk_max_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_blk_max_len.bits.blk_max_len = ublk_max_len;
    HDMI21TXRegWrite(pu32RegAddr, o_blk_max_len.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_BLK_MAX_LEN_blk_max_lenGet
//  Description : Set the value of the member BLK_MAX_LEN.blk_max_len
//  Input       : unsigned int ublk_max_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_BLK_MAX_LEN_blk_max_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_BLK_MAX_LEN o_blk_max_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->BLK_MAX_LEN.u32);
    o_blk_max_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_blk_max_len.bits.blk_max_len;
}
//******************************************************************************
//  Function    : HDMI_BLK_GAP_LEN_blk_gap_lenSet
//  Description : Set the value of the member BLK_GAP_LEN.blk_gap_len
//  Input       : unsigned int ublk_gap_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_BLK_GAP_LEN_blk_gap_lenSet(unsigned int ublk_gap_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_BLK_GAP_LEN o_blk_gap_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->BLK_GAP_LEN.u32);
    o_blk_gap_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_blk_gap_len.bits.blk_gap_len = ublk_gap_len;
    HDMI21TXRegWrite(pu32RegAddr, o_blk_gap_len.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_BLK_GAP_LEN_blk_gap_lenGet
//  Description : Set the value of the member BLK_GAP_LEN.blk_gap_len
//  Input       : unsigned int ublk_gap_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_BLK_GAP_LEN_blk_gap_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_BLK_GAP_LEN o_blk_gap_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->BLK_GAP_LEN.u32);
    o_blk_gap_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_blk_gap_len.bits.blk_gap_len;
}
//******************************************************************************
//  Function    : HDMI_AV_GAP_LEN_av_gap_lenGet
//  Description : Set the value of the member AV_GAP_LEN.av_gap_len
//  Input       : unsigned int uav_gap_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AV_GAP_LEN_av_gap_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AV_GAP_LEN o_av_gap_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->AV_GAP_LEN.u32);
    o_av_gap_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_av_gap_len.bits.av_gap_len;
}


//******************************************************************************
//  Function    : HDMI_HBLANK_hblankSet
//  Description : Set the value of the member HBLANK.hblank
//  Input       : unsigned int uhblank: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HBLANK_hblankSet(unsigned int uhblank)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HBLANK o_hblank;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->HBLANK.u32);
    o_hblank.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hblank.bits.hblank = uhblank;
    HDMI21TXRegWrite(pu32RegAddr, o_hblank.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_HBLANK_hblankGet
//  Description : Set the value of the member HBLANK.hblank
//  Input       : unsigned int uhblank: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HBLANK_hblankGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HBLANK o_hblank;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->HBLANK.u32);
    o_hblank.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hblank.bits.hblank;
}


//******************************************************************************
//  Function    : HDMI_HACTIVE_hactiveSet
//  Description : Set the value of the member HACTIVE.hactive
//  Input       : unsigned int uhactive: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HACTIVE_hactiveSet(unsigned int uhactive)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HACTIVE o_hactive;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->HACTIVE.u32);
    o_hactive.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hactive.bits.hactive = uhactive;
    HDMI21TXRegWrite(pu32RegAddr, o_hactive.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_HACTIVE_hactiveGet
//  Description : Set the value of the member HACTIVE.hactive
//  Input       : unsigned int uhactive: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HACTIVE_hactiveGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HACTIVE o_hactive;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->HACTIVE.u32);
    o_hactive.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hactive.bits.hactive;
}
//******************************************************************************
//  Function    : HDMI_EXTRA_BLANK_MAX_LEN_extra_blank_max_lenSet
//  Description : Set the value of the member EXTRA_BLANK_MAX_LEN.extra_blank_max_len
//  Input       : unsigned int uextra_blank_max_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_BLANK_MAX_LEN_extra_blank_max_lenSet(unsigned int uextra_blank_max_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_BLANK_MAX_LEN o_extra_blank_max_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_BLANK_MAX_LEN.u32);
    o_extra_blank_max_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_extra_blank_max_len.bits.extra_blank_max_len = uextra_blank_max_len;
    HDMI21TXRegWrite(pu32RegAddr, o_extra_blank_max_len.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_EXTRA_BLANK_MAX_LEN_extra_blank_max_lenGet
//  Description : Set the value of the member EXTRA_BLANK_MAX_LEN.extra_blank_max_len
//  Input       : unsigned int uextra_blank_max_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_BLANK_MAX_LEN_extra_blank_max_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_BLANK_MAX_LEN o_extra_blank_max_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_BLANK_MAX_LEN.u32);
    o_extra_blank_max_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_extra_blank_max_len.bits.extra_blank_max_len;
}


//******************************************************************************
//  Function    : HDMI_EXTRA_BLANK_GAP_LEN_extra_blank_gap_lenSet
//  Description : Set the value of the member EXTRA_BLANK_GAP_LEN.extra_blank_gap_len
//  Input       : unsigned int uextra_blank_gap_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_BLANK_GAP_LEN_extra_blank_gap_lenSet(unsigned int uextra_blank_gap_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_BLANK_GAP_LEN o_extra_blank_gap_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_BLANK_GAP_LEN.u32);
    o_extra_blank_gap_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_extra_blank_gap_len.bits.extra_blank_gap_len = uextra_blank_gap_len;
    HDMI21TXRegWrite(pu32RegAddr, o_extra_blank_gap_len.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_EXTRA_BLANK_GAP_LEN_extra_blank_gap_lenGet
//  Description : Set the value of the member EXTRA_BLANK_GAP_LEN.extra_blank_gap_len
//  Input       : unsigned int uextra_blank_gap_len: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_BLANK_GAP_LEN_extra_blank_gap_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_BLANK_GAP_LEN o_extra_blank_gap_len;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_BLANK_GAP_LEN.u32);
    o_extra_blank_gap_len.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_extra_blank_gap_len.bits.extra_blank_gap_len;
}
//******************************************************************************
//  Function    : HDMI_EXTRA_MODE_EN_extra_mode_enSet
//  Description : Set the value of the member EXTRA_MODE_EN.extra_mode_en
//  Input       : unsigned int uextra_mode_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_MODE_EN_extra_mode_enSet(unsigned int uextra_mode_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_MODE_EN o_extra_mode_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_MODE_EN.u32);
    o_extra_mode_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_extra_mode_en.bits.extra_mode_en = uextra_mode_en;
    HDMI21TXRegWrite(pu32RegAddr, o_extra_mode_en.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_EXTRA_MODE_EN_extra_mode_enGet
//  Description : Set the value of the member EXTRA_MODE_EN.extra_mode_en
//  Input       : unsigned int uextra_mode_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_MODE_EN_extra_mode_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_MODE_EN o_extra_mode_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_MODE_EN.u32);
    o_extra_mode_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_extra_mode_en.bits.extra_mode_en;
}
//******************************************************************************
//  Function    : HDMI_VBLANK1_LINES_vblank1_linesSet
//  Description : Set the value of the member VBLANK1_LINES.vblank1_lines
//  Input       : unsigned int uvblank1_lines: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VBLANK1_LINES_vblank1_linesSet(unsigned int uvblank1_lines)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VBLANK1_LINES o_vblank1_lines;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->VBLANK1_LINES.u32);
    o_vblank1_lines.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_vblank1_lines.bits.vblank1_lines = uvblank1_lines;
    HDMI21TXRegWrite(pu32RegAddr, o_vblank1_lines.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_VBLANK1_LINES_vblank1_linesGet
//  Description : Set the value of the member VBLANK1_LINES.vblank1_lines
//  Input       : unsigned int uvblank1_lines: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VBLANK1_LINES_vblank1_linesGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VBLANK1_LINES o_vblank1_lines;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->VBLANK1_LINES.u32);
    o_vblank1_lines.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_vblank1_lines.bits.vblank1_lines;
}
//******************************************************************************
//  Function    : HDMI_VACTIVE_vactiveSet
//  Description : Set the value of the member VACTIVE.vactive
//  Input       : unsigned int uvactive: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VACTIVE_vactiveSet(unsigned int uvactive)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VACTIVE o_vactive;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->VACTIVE.u32);
    o_vactive.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_vactive.bits.vactive = uvactive;
    HDMI21TXRegWrite(pu32RegAddr, o_vactive.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_VACTIVE_vactiveGet
//  Description : Set the value of the member VACTIVE.vactive
//  Input       : unsigned int uvactive: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_VACTIVE_vactiveGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VACTIVE o_vactive;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->VACTIVE.u32);
    o_vactive.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_vactive.bits.vactive;
}
//******************************************************************************
//  Function    : HDMI_EXTRA_NO_GAP_FLAG_extra_no_gap_flagSet
//  Description : Set the value of the member EXTRA_NO_GAP_FLAG.extra_no_gap_flag
//  Input       : unsigned int uextra_no_gap_flag: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_NO_GAP_FLAG_extra_no_gap_flagSet(unsigned int uextra_no_gap_flag)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_NO_GAP_FLAG o_extra_no_gap_flag;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_NO_GAP_FLAG.u32);
    o_extra_no_gap_flag.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_extra_no_gap_flag.bits.extra_no_gap_flag = uextra_no_gap_flag;
    HDMI21TXRegWrite(pu32RegAddr, o_extra_no_gap_flag.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_EXTRA_NO_GAP_FLAG_extra_no_gap_flagGet
//  Description : Set the value of the member EXTRA_NO_GAP_FLAG.extra_no_gap_flag
//  Input       : unsigned int uextra_no_gap_flag: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_EXTRA_NO_GAP_FLAG_extra_no_gap_flagGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_EXTRA_NO_GAP_FLAG o_extra_no_gap_flag;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->EXTRA_NO_GAP_FLAG.u32);
    o_extra_no_gap_flag.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_extra_no_gap_flag.bits.extra_no_gap_flag;
}
//******************************************************************************
//  Function    : HDMI_CPU_SET_RES_soft_train_okSet
//  Description : Set the value of the member CPU_SET_RES.soft_train_ok
//  Input       : unsigned int usoft_train_ok: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CPU_SET_RES_soft_train_okSet(unsigned int usoft_train_ok)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_RES o_cpu_set_res;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_RES.u32);
    o_cpu_set_res.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_res.bits.soft_train_ok = usoft_train_ok;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_res.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_CPU_SET_RES_soft_train_okGet
//  Description : Set the value of the member CPU_SET_RES.soft_train_ok
//  Input       : unsigned int usoft_train_ok: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CPU_SET_RES_soft_train_okGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_RES o_cpu_set_res;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_RES.u32);
    o_cpu_set_res.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_cpu_set_res.bits.soft_train_ok;
}
//******************************************************************************
//  Function    : HDMI_FLT_START_flt_startSet
//  Description : Set the value of the member FLT_START.flt_start
//  Input       : unsigned int uflt_start: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_START_flt_startSet(unsigned int uflt_start)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_START o_flt_start;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_START.u32);
    o_flt_start.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_flt_start.bits.flt_start = uflt_start;
    HDMI21TXRegWrite(pu32RegAddr, o_flt_start.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_FLT_START_flt_startGet
//  Description : Set the value of the member FLT_START.flt_start
//  Input       : unsigned int uflt_start: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_START_flt_startGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_START o_flt_start;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_START.u32);
    o_flt_start.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_start.bits.flt_start;
}



//******************************************************************************
//  Function    : HDMI_FLT_LTP_ltp_patternGet
//  Description : Set the value of the member FLT_LTP.ltp_pattern
//  Input       : unsigned int ultp_pattern: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_LTP_ltp_patternGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_LTP o_flt_ltp;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_LTP.u32);
    o_flt_ltp.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_ltp.bits.ltp_pattern;
}

//******************************************************************************
//  Function    : HDMI_FRL_MODE_ACT_frl_mode_actGet
//  Description : Set the value of the member FRL_MODE_ACT.frl_mode_act
//  Input       : unsigned int ufrl_mode_act: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FRL_MODE_ACT_frl_mode_actGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FRL_MODE_ACT o_frl_mode_act;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FRL_MODE_ACT.u32);
    o_frl_mode_act.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_frl_mode_act.bits.frl_mode_act;
}


//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_initSet
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init0
//  Input       : unsigned int ucode_rfd_init0: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init0Set(unsigned int ucode_rfd_init0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_code_rfd.bits.code_rfd_init0 = ucode_rfd_init0;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_code_rfd.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_init0Get
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init0
//  Input       : unsigned int ucode_rfd_init0: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_code_rfd.bits.code_rfd_init0;
}

//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_init1Set
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init1
//  Input       : unsigned int ucode_rfd_init1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init1Set(unsigned int ucode_rfd_init1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_code_rfd.bits.code_rfd_init1 = ucode_rfd_init1;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_code_rfd.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_init1Get
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init1
//  Input       : unsigned int ucode_rfd_init1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_code_rfd.bits.code_rfd_init1;
}
//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_init2Set
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init2
//  Input       : unsigned int ucode_rfd_init2: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init2Set(unsigned int ucode_rfd_init2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_code_rfd.bits.code_rfd_init2 = ucode_rfd_init2;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_code_rfd.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_init2Get
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init2
//  Input       : unsigned int ucode_rfd_init2: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_code_rfd.bits.code_rfd_init2;
}

//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_init3Set
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init3
//  Input       : unsigned int ucode_rfd_init3: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init3Set(unsigned int ucode_rfd_init3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_code_rfd.bits.code_rfd_init3 = ucode_rfd_init3;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_code_rfd.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_code_rfd_init3Get
//  Description : Set the value of the member LM_CODE_RFD.code_rfd_init3
//  Input       : unsigned int ucode_rfd_init3: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_code_rfd_init3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_code_rfd.bits.code_rfd_init3;
}


//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_lm_ptn_rsv_enSet
//  Description : Set the value of the member LM_CODE_RFD.lm_ptn_rsv_en
//  Input       : unsigned int ulm_ptn_rsv_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_lm_ptn_rsv_enSet(unsigned int ulm_ptn_rsv_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_code_rfd.bits.lm_ptn_rsv_en = ulm_ptn_rsv_en;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_code_rfd.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_lm_ptn_rsv_enGet
//  Description : Set the value of the member LM_CODE_RFD.lm_ptn_rsv_en
//  Input       : unsigned int ulm_ptn_rsv_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_lm_ptn_rsv_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_code_rfd.bits.lm_ptn_rsv_en;
}

//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_trn_ptn_rsv_setSet
//  Description : Set the value of the member LM_CODE_RFD.trn_ptn_rsv_set
//  Input       : unsigned int utrn_ptn_rsv_set: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_trn_ptn_rsv_setSet(unsigned int utrn_ptn_rsv_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_code_rfd.bits.trn_ptn_rsv_set = utrn_ptn_rsv_set;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_code_rfd.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_LM_CODE_RFD_trn_ptn_rsv_setGet
//  Description : Set the value of the member LM_CODE_RFD.trn_ptn_rsv_set
//  Input       : unsigned int utrn_ptn_rsv_set: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_CODE_RFD_trn_ptn_rsv_setGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_CODE_RFD o_lm_code_rfd;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_CODE_RFD.u32);
    o_lm_code_rfd.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_code_rfd.bits.trn_ptn_rsv_set;
}
//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT0_lane0_init_valueSet
//  Description : Set the value of the member LM_SRC_INIT0.lane0_init_value
//  Input       : unsigned int ulane0_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT0_lane0_init_valueSet(unsigned int ulane0_init_value)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT0 o_lm_src_init0;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT0.u32);
    o_lm_src_init0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_src_init0.bits.lane0_init_value = ulane0_init_value;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_src_init0.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT0_lane0_init_valueGet
//  Description : Set the value of the member LM_SRC_INIT0.lane0_init_value
//  Input       : unsigned int ulane0_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT0_lane0_init_valueGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT0 o_lm_src_init0;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT0.u32);
    o_lm_src_init0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_src_init0.bits.lane0_init_value;
}
//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT0_lane1_init_valueSet
//  Description : Set the value of the member LM_SRC_INIT0.lane1_init_value
//  Input       : unsigned int ulane1_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT0_lane1_init_valueSet(unsigned int ulane1_init_value)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT0 o_lm_src_init0;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT0.u32);
    o_lm_src_init0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_src_init0.bits.lane1_init_value = ulane1_init_value;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_src_init0.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT0_lane1_init_valueGet
//  Description : Set the value of the member LM_SRC_INIT0.lane1_init_value
//  Input       : unsigned int ulane1_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT0_lane1_init_valueGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT0 o_lm_src_init0;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT0.u32);
    o_lm_src_init0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_src_init0.bits.lane1_init_value;
}

//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT1_lane2_init_valueSet
//  Description : Set the value of the member LM_SRC_INIT1.lane2_init_value
//  Input       : unsigned int ulane2_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT1_lane2_init_valueSet(unsigned int ulane2_init_value)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT1 o_lm_src_init1;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT1.u32);
    o_lm_src_init1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_src_init1.bits.lane2_init_value = ulane2_init_value;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_src_init1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT1_lane2_init_valueGet
//  Description : Set the value of the member LM_SRC_INIT1.lane2_init_value
//  Input       : unsigned int ulane2_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT1_lane2_init_valueGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT1 o_lm_src_init1;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT1.u32);
    o_lm_src_init1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_src_init1.bits.lane2_init_value;
}

//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT1_lane3_init_valueSet
//  Description : Set the value of the member LM_SRC_INIT1.lane3_init_value
//  Input       : unsigned int ulane3_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT1_lane3_init_valueSet(unsigned int ulane3_init_value)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT1 o_lm_src_init1;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT1.u32);
    o_lm_src_init1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_lm_src_init1.bits.lane3_init_value = ulane3_init_value;
    HDMI21TXRegWrite(pu32RegAddr, o_lm_src_init1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_LM_SRC_INIT1_lane3_init_valueGet
//  Description : Set the value of the member LM_SRC_INIT1.lane3_init_value
//  Input       : unsigned int ulane3_init_value: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LM_SRC_INIT1_lane3_init_valueGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LM_SRC_INIT1 o_lm_src_init1;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LM_SRC_INIT1.u32);
    o_lm_src_init1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_lm_src_init1.bits.lane3_init_value;
}

//******************************************************************************
//  Function    : HDMI_LINE_START_HSYNC_EN_line_start_hsync_enSet
//  Description : Set the value of the member LINE_START_HSYNC_EN.line_start_hsync_en
//  Input       : unsigned int uline_start_hsync_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LINE_START_HSYNC_EN_line_start_hsync_enSet(unsigned int uline_start_hsync_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LINE_START_HSYNC_EN o_line_start_hsync_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LINE_START_HSYNC_EN.u32);
    o_line_start_hsync_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_line_start_hsync_en.bits.line_start_hsync_en = uline_start_hsync_en;
    HDMI21TXRegWrite(pu32RegAddr, o_line_start_hsync_en.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_LINE_START_HSYNC_EN_line_start_hsync_enGet
//  Description : Set the value of the member LINE_START_HSYNC_EN.line_start_hsync_en
//  Input       : unsigned int uline_start_hsync_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_LINE_START_HSYNC_EN_line_start_hsync_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_LINE_START_HSYNC_EN o_line_start_hsync_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->LINE_START_HSYNC_EN.u32);
    o_line_start_hsync_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_line_start_hsync_en.bits.line_start_hsync_en;
}
//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_vsync_polarSet
//  Description : Set the value of the member SYNC_POLAR.vsync_polar
//  Input       : unsigned int uvsync_polar: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_vsync_polarSet(unsigned int uvsync_polar)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_sync_polar.bits.vsync_polar = uvsync_polar;
    HDMI21TXRegWrite(pu32RegAddr, o_sync_polar.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_vsync_polarGet
//  Description : Set the value of the member SYNC_POLAR.vsync_polar
//  Input       : unsigned int uvsync_polar: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_vsync_polarGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_sync_polar.bits.vsync_polar;
}
//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_vsync_polar_enSet
//  Description : Set the value of the member SYNC_POLAR.vsync_polar_en
//  Input       : unsigned int uvsync_polar_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_vsync_polar_enSet(unsigned int uvsync_polar_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_sync_polar.bits.vsync_polar_en = uvsync_polar_en;
    HDMI21TXRegWrite(pu32RegAddr, o_sync_polar.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_vsync_polar_enGet
//  Description : Set the value of the member SYNC_POLAR.vsync_polar_en
//  Input       : unsigned int uvsync_polar_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_vsync_polar_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_sync_polar.bits.vsync_polar_en;
}

//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_hsync_polarSet
//  Description : Set the value of the member SYNC_POLAR.hsync_polar
//  Input       : unsigned int uhsync_polar: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_hsync_polarSet(unsigned int uhsync_polar)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_sync_polar.bits.hsync_polar = uhsync_polar;
    HDMI21TXRegWrite(pu32RegAddr, o_sync_polar.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_hsync_polarGet
//  Description : Set the value of the member SYNC_POLAR.hsync_polar
//  Input       : unsigned int uhsync_polar: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_hsync_polarGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_sync_polar.bits.hsync_polar;
}

//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_hsync_polar_enSet
//  Description : Set the value of the member SYNC_POLAR.hsync_polar_en
//  Input       : unsigned int uhsync_polar_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_hsync_polar_enSet(unsigned int uhsync_polar_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_sync_polar.bits.hsync_polar_en = uhsync_polar_en;
    HDMI21TXRegWrite(pu32RegAddr, o_sync_polar.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SYNC_POLAR_hsync_polar_enGet
//  Description : Set the value of the member SYNC_POLAR.hsync_polar_en
//  Input       : unsigned int uhsync_polar_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SYNC_POLAR_hsync_polar_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SYNC_POLAR o_sync_polar;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SYNC_POLAR.u32);
    o_sync_polar.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_sync_polar.bits.hsync_polar_en;
}
//******************************************************************************
//  Function    : HDMI_SCDCS_CONFIG_scdcs_config_inSet
//  Description : Set the value of the member SCDCS_CONFIG.scdcs_config_in
//  Input       : unsigned int uscdcs_config_in: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SCDCS_CONFIG_scdcs_config_inSet(unsigned int uscdcs_config_in)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SCDCS_CONFIG o_scdcs_config;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SCDCS_CONFIG.u32);
    o_scdcs_config.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_scdcs_config.bits.scdcs_config_in = uscdcs_config_in;
    HDMI21TXRegWrite(pu32RegAddr, o_scdcs_config.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_SCDCS_CONFIG_scdcs_config_inGet
//  Description : Set the value of the member SCDCS_CONFIG.scdcs_config_in
//  Input       : unsigned int uscdcs_config_in: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SCDCS_CONFIG_scdcs_config_inGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SCDCS_CONFIG o_scdcs_config;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->SCDCS_CONFIG.u32);
    o_scdcs_config.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_scdcs_config.bits.scdcs_config_in;
}
//******************************************************************************
//  Function    : HDMI_UPDATE_FLAG_TIMER_update_flag_timerSet
//  Description : Set the value of the member UPDATE_FLAG_TIMER.update_flag_timer
//  Input       : unsigned int uupdate_flag_timer: 24 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_UPDATE_FLAG_TIMER_update_flag_timerSet(unsigned int uupdate_flag_timer)
{
    HI_U32 *pu32RegAddr = NULL;
    U_UPDATE_FLAG_TIMER o_update_flag_timer;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->UPDATE_FLAG_TIMER.u32);
    o_update_flag_timer.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_update_flag_timer.bits.update_flag_timer = uupdate_flag_timer;
    HDMI21TXRegWrite(pu32RegAddr, o_update_flag_timer.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_UPDATE_FLAG_TIMER_update_flag_timerGet
//  Description : Set the value of the member UPDATE_FLAG_TIMER.update_flag_timer
//  Input       : unsigned int uupdate_flag_timer: 24 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_UPDATE_FLAG_TIMER_update_flag_timerGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_UPDATE_FLAG_TIMER o_update_flag_timer;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->UPDATE_FLAG_TIMER.u32);
    o_update_flag_timer.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_update_flag_timer.bits.update_flag_timer;
}
//******************************************************************************
//  Function    : HDMI_FLT_STEP_TIMER_step_timeout_timerSet
//  Description : Set the value of the member FLT_STEP_TIMER.step_timeout_timer
//  Input       : unsigned int ustep_timeout_timer: 28 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_STEP_TIMER_step_timeout_timerSet(unsigned int ustep_timeout_timer)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_STEP_TIMER o_flt_step_timer;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_STEP_TIMER.u32);
    o_flt_step_timer.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_flt_step_timer.bits.step_timeout_timer = ustep_timeout_timer;
    HDMI21TXRegWrite(pu32RegAddr, o_flt_step_timer.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_FLT_STEP_TIMER_step_timeout_timerGet
//  Description : Set the value of the member FLT_STEP_TIMER.step_timeout_timer
//  Input       : unsigned int ustep_timeout_timer: 28 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_STEP_TIMER_step_timeout_timerGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_STEP_TIMER o_flt_step_timer;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_STEP_TIMER.u32);
    o_flt_step_timer.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_step_timer.bits.step_timeout_timer;
}
//******************************************************************************
//  Function    : HDMI_FLT_TIMEOUT_TIMER_flt_timeout_timerSet
//  Description : Set the value of the member FLT_TIMEOUT_TIMER.flt_timeout_timer
//  Input       : unsigned int uflt_timeout_timer: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_TIMEOUT_TIMER_flt_timeout_timerSet(unsigned int uflt_timeout_timer)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_TIMEOUT_TIMER o_flt_timeout_timer;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_TIMEOUT_TIMER.u32);
    o_flt_timeout_timer.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_flt_timeout_timer.bits.flt_timeout_timer = uflt_timeout_timer;
    HDMI21TXRegWrite(pu32RegAddr, o_flt_timeout_timer.u32);

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : HDMI_FLT_TIMEOUT_TIMER_flt_timeout_timerGet
//  Description : Set the value of the member FLT_TIMEOUT_TIMER.flt_timeout_timer
//  Input       : unsigned int uflt_timeout_timer: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_TIMEOUT_TIMER_flt_timeout_timerGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_TIMEOUT_TIMER o_flt_timeout_timer;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_TIMEOUT_TIMER.u32);
    o_flt_timeout_timer.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_timeout_timer.bits.flt_timeout_timer;
}
//******************************************************************************
//  Function    : HDMI_WORK_EN_work_enSet
//  Description : Set the value of the member WORK_EN.work_en
//  Input       : unsigned int uwork_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_WORK_EN_work_enSet(unsigned int uwork_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_WORK_EN o_work_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->WORK_EN.u32);
    o_work_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_work_en.bits.work_en = uwork_en;
    HDMI21TXRegWrite(pu32RegAddr, o_work_en.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_WORK_EN_work_enGet
//  Description : Set the value of the member WORK_EN.work_en
//  Input       : unsigned int uwork_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_WORK_EN_work_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_WORK_EN o_work_en;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->WORK_EN.u32);
    o_work_en.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_work_en.bits.work_en;
}
//******************************************************************************
//  Function    : HDMI_FLT_RESULT_train_successGet
//  Description : Set the value of the member FLT_RESULT.train_success
//  Input       : unsigned int utrain_success: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_RESULT_train_successGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_RESULT o_flt_result;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_RESULT.u32);
    o_flt_result.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_result.bits.train_success;
}
//******************************************************************************
//  Function    : HDMI_FLT_RESULT_train_failGet
//  Description : Set the value of the member FLT_RESULT.train_fail
//  Input       : unsigned int utrain_fail: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_RESULT_train_failGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_RESULT o_flt_result;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_RESULT.u32);
    o_flt_result.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_result.bits.train_fail;
}
//******************************************************************************
//  Function    : HDMI_FLT_RESULT_train_busyGet
//  Description : Set the value of the member FLT_RESULT.train_busy
//  Input       : unsigned int utrain_busy: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_RESULT_train_busyGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_RESULT o_flt_result;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_RESULT.u32);
    o_flt_result.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_result.bits.train_busy;
}

//******************************************************************************
//  Function    : HDMI_FLT_RESULT_sink_ffe_reqGet
//  Description : Set the value of the member FLT_RESULT.sink_ffe_req
//  Input       : unsigned int usink_ffe_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_RESULT_sink_ffe_reqGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_RESULT o_flt_result;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_RESULT.u32);
    o_flt_result.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_result.bits.sink_ffe_req;
}
//******************************************************************************
//  Function    : HDMI_FLT_RESULT_train_fail_resGet
//  Description : Set the value of the member FLT_RESULT.train_fail_res
//  Input       : unsigned int utrain_fail_res: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_RESULT_train_fail_resGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_RESULT o_flt_result;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_RESULT.u32);
    o_flt_result.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_result.bits.train_fail_res;
}
//******************************************************************************
//  Function    : HDMI_FLT_RESULT_flt_cntGet
//  Description : Set the value of the member FLT_RESULT.flt_cnt
//  Input       : unsigned int uflt_cnt: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_RESULT_flt_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_RESULT o_flt_result;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_RESULT.u32);
    o_flt_result.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_result.bits.flt_cnt;
}
//******************************************************************************
//  Function    : HDMI_FLT_RESULT_frl_work_modeGet
//  Description : Set the value of the member FLT_RESULT.frl_work_mode
//  Input       : unsigned int ufrl_work_mode: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_RESULT_frl_work_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_RESULT o_flt_result;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_RESULT.u32);
    o_flt_result.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_result.bits.frl_work_mode;
}


//******************************************************************************
//  Function    : HDMI_FLT_FSM_STATUS_ddc_in_progGet
//  Description : Set the value of the member FLT_FSM_STATUS.ddc_in_prog
//  Input       : unsigned int uddc_in_prog: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_FSM_STATUS_ddc_in_progGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_FSM_STATUS o_flt_fsm_status;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_FSM_STATUS.u32);
    o_flt_fsm_status.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_fsm_status.bits.ddc_in_prog;
}



//******************************************************************************
//  Function    : HDMI_FLT_FSM_STATUS_work_channelGet
//  Description : Set the value of the member FLT_FSM_STATUS.work_channel
//  Input       : unsigned int uwork_channel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_FSM_STATUS_work_channelGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_FSM_STATUS o_flt_fsm_status;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_FSM_STATUS.u32);
    o_flt_fsm_status.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_fsm_status.bits.work_channel;
}



//******************************************************************************
//  Function    : HDMI_FLT_FSM_STATUS_work_lane_numGet
//  Description : Set the value of the member FLT_FSM_STATUS.work_lane_num
//  Input       : unsigned int uwork_lane_num: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_FSM_STATUS_work_lane_numGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_FSM_STATUS o_flt_fsm_status;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_FSM_STATUS.u32);
    o_flt_fsm_status.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_fsm_status.bits.work_lane_num;
}



//******************************************************************************
//  Function    : HDMI_FLT_FSM_STATUS_flt_fsm_currGet
//  Description : Set the value of the member FLT_FSM_STATUS.flt_fsm_curr
//  Input       : unsigned int uflt_fsm_curr: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FLT_FSM_STATUS_flt_fsm_currGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FLT_FSM_STATUS o_flt_fsm_status;
    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->FLT_FSM_STATUS.u32);
    o_flt_fsm_status.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_flt_fsm_status.bits.flt_fsm_curr;
}

//******************************************************************************
//  Function    : HDMI_CPU_SET_PATTERN_lane0_train_ptnSet
//  Description : Set the value of the member U_CPU_SET_PATTERN.lane0_train_ptn_set
//  Input       : unsigned int ulane0_train_ptn_set: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CPU_SET_PATTERN_lane0_train_ptnSet(unsigned int ulane0_train_ptn_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_PATTERN o_cpu_set_pattern;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_PATTERN.u32);
    o_cpu_set_pattern.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_pattern.bits.lane0_train_ptn_set = ulane0_train_ptn_set;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_pattern.u32);
    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CPU_SET_PATTERN_lane1_train_ptnSet
//  Description : Set the value of the member U_CPU_SET_PATTERN.lane1_train_ptn_set
//  Input       : unsigned int ulane1_train_ptn_set: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CPU_SET_PATTERN_lane1_train_ptnSet(unsigned int ulane1_train_ptn_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_PATTERN o_cpu_set_pattern;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_PATTERN.u32);
    o_cpu_set_pattern.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_pattern.bits.lane1_train_ptn_set = ulane1_train_ptn_set;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_pattern.u32);
    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CPU_SET_PATTERN_lane2_train_ptnSet
//  Description : Set the value of the member U_CPU_SET_PATTERN.lane2_train_ptn_set
//  Input       : unsigned int ulane2_train_ptn_set: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CPU_SET_PATTERN_lane2_train_ptnSet(unsigned int ulane2_train_ptn_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_PATTERN o_cpu_set_pattern;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_PATTERN.u32);
    o_cpu_set_pattern.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_pattern.bits.lane2_train_ptn_set = ulane2_train_ptn_set;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_pattern.u32);
    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CPU_SET_PATTERN_lane3_train_ptnSet
//  Description : Set the value of the member U_CPU_SET_PATTERN.lane3_train_ptn_set
//  Input       : unsigned int ulane3_train_ptn_set: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CPU_SET_PATTERN_lane3_train_ptnSet(unsigned int ulane3_train_ptn_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_PATTERN o_cpu_set_pattern;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_PATTERN.u32);
    o_cpu_set_pattern.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_pattern.bits.lane3_train_ptn_set = ulane3_train_ptn_set;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_pattern.u32);
    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CPU_CFG_SEL_flt_no_timeoutSet
//  Description : Set the value of the member U_CPU_CFG_SEL.flt_no_timeout
//  Input       : unsigned int uflt_no_timeout: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CPU_CFG_SEL_flt_no_timeoutSet(unsigned int uflt_no_timeout)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_CFG_SEL o_cpu_cfg_sel;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_CFG_SEL.u32);
    o_cpu_cfg_sel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_cfg_sel.bits.flt_no_timeout = uflt_no_timeout;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_cfg_sel.u32);
    return HI_SUCCESS;
}

int HDMI_CPU_SET_RES_software_train_setSet(unsigned int usoftware_train_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_RES o_cpu_set_res;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_RES.u32);
    o_cpu_set_res.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_res.bits.software_train_set = usoftware_train_set;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_res.u32);
    return HI_SUCCESS;
}

int HDMI_CPU_SET_RES_flt_skipSet(unsigned int uflt_skip)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_RES o_cpu_set_res;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_RES.u32);
    o_cpu_set_res.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_res.bits.flt_skip = uflt_skip;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_res.u32);
    return HI_SUCCESS;
}

int HDMI_CPU_SET_RES_frl_lane_sel_setSet(unsigned int ufrl_lane_sel_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_RES o_cpu_set_res;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_RES.u32);
    o_cpu_set_res.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_res.bits.frl_lane_sel_set = ufrl_lane_sel_set;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_res.u32);
    return HI_SUCCESS;
}

int HDMI_CPU_SET_RES_soft_train_rateSet(unsigned int usoft_train_rate)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CPU_SET_RES o_cpu_set_res;

    pu32RegAddr = (HI_U32*)&(goptx_frl_regAllReg->CPU_SET_RES.u32);
    o_cpu_set_res.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cpu_set_res.bits.soft_train_rate = usoft_train_rate;
    HDMI21TXRegWrite(pu32RegAddr, o_cpu_set_res.u32);
    return HI_SUCCESS;
}


