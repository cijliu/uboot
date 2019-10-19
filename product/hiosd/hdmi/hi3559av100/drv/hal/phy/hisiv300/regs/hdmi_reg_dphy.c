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
#include "hdmi_reg_dphy.h"
#include "hdmi_product_define.h"

/* The base address of the module hi3559a_dphy_reg */
#define PRODUCT_NULL_CHK(p) do{\
	if(HI_NULL == p)\
    {\
	return HI_FAILURE;}\
}while(0)

/* The base address of the module hi3559a_dphy_reg */
//#define hi3559a_dphy_reg_BASE_ADDR (DATE_CTRL_BASE_ADDR|0x11160000)

/* Define the struct pointor of the module tx_dphy_reg */
volatile S_3559a_dphy_reg_REGS_TYPE *hi3559a_dphy_regAllReg = HI_NULL;
HI_S32 HDMI_HDMITX_PHY_reg_Init(HI_CHAR *pcAddr)
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

    hi3559a_dphy_regAllReg = (S_3559a_dphy_reg_REGS_TYPE*)(pcAddr + HDMI_TX_BASE_ADDR_DPHY);
    if(HI_NULL == hi3559a_dphy_regAllReg)
    {
    	HDMI_ERR("ioremap_nocache hi3559a_dphy_regAllReg failed!\n");
    	return HI_FAILURE;
    }

	return HI_SUCCESS;
}

HI_S32 HDMI_HDMITX_PHY_reg_DeInit(HI_VOID)
{
    if(HI_NULL != hi3559a_dphy_regAllReg)
    {
        hi3559a_dphy_regAllReg = HI_NULL;
    }

	return HI_SUCCESS;
}

static HI_S32 HDMI21TXRegWrite(HI_U32 *pu32RegAddr, HI_U32 u32Value)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    *(volatile HI_U32*)pu32RegAddr = u32Value;
    return HI_SUCCESS;
}

static HI_U32 HDMI21TXRegRead(HI_U32 *pu32RegAddr)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    return *(volatile HI_U32*)(pu32RegAddr);
}

//******************************************************************************
//  Function    : DATE_PHY_CSEN_stb_cs_enSet
//  Description : Set the value of the member PHY_CSEN.stb_cs_en
//  Input       : unsigned int ustb_cs_en: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_CSEN_stb_cs_enSet(unsigned int ustb_cs_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_CSEN o_phy_csen;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_CSEN.u32);
    o_phy_csen.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_csen.bits.stb_cs_en = ustb_cs_en;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_csen.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_phy_csen.u32, "PHY_CSEN");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_PHY_WR_stb_wenSet
//  Description : Set the value of the member PHY_WR.stb_wen
//  Input       : unsigned int ustb_wen: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WR_stb_wenSet(unsigned int ustb_wen)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WR o_phy_wr;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_WR.u32);
    o_phy_wr.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_wr.bits.stb_wen = ustb_wen;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_wr.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_phy_wr.u32, "PHY_WR");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_RESETN_resetnSet
//  Description : Set the value of the member RESETN.resetn
//  Input       : unsigned int uresetn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RESETN_resetnSet(unsigned int uresetn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RESETN o_resetn;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RESETN.u32);
    o_resetn.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_resetn.bits.resetn = uresetn;
    HDMI21TXRegWrite(pu32RegAddr, o_resetn.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_resetn.u32, "RESETN");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_RESETN_resetnGet
//  Description : Set the value of the member RESETN.resetn
//  Input       : unsigned int uresetn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RESETN_resetnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RESETN o_resetn;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RESETN.u32);
    o_resetn.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_resetn.bits.resetn;
}

//******************************************************************************
//  Function    : DATE_FDSRCPARAM_src_enableSet
//  Description : Set the value of the member FDSRCPARAM.src_enable
//  Input       : unsigned int usrc_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_enableSet(unsigned int usrc_enable)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.src_enable = usrc_enable;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcparam.u32, "FDSRCPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_PHY_WDATA_stb_wdataSet
//  Description : Set the value of the member PHY_WDATA.stb_wdata
//  Input       : unsigned int ustb_wdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WDATA_stb_wdataSet(unsigned int ustb_wdata)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WDATA o_phy_wdata;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_WDATA.u32);
    o_phy_wdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_wdata.bits.stb_wdata = ustb_wdata;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_wdata.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_phy_wdata.u32, "PHY_WDATA");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_lock_enSet
//  Description : Set the value of the member FCGSET.p_fcg_lock_en
//  Input       : unsigned int up_fcg_lock_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_lock_enSet(unsigned int up_fcg_lock_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgset.bits.p_fcg_lock_en = up_fcg_lock_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgset.u32, "FCGSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_PHY_ADDR_stb_addrSet
//  Description : Set the value of the member PHY_ADDR.stb_addr
//  Input       : unsigned int ustb_addr: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_ADDR_stb_addrSet(unsigned int ustb_addr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_ADDR o_phy_addr;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_ADDR.u32);
    o_phy_addr.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_addr.bits.stb_addr = ustb_addr;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_addr.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_phy_addr.u32, "PHY_ADDR");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_PHY_RDATA_stb_rdataGet
//  Description : Set the value of the member PHY_RDATA.stb_rdata
//  Input       : unsigned int ustb_rdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_RDATA_stb_rdataGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_RDATA o_phy_rdata;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_RDATA.u32);
    o_phy_rdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_rdata.bits.stb_rdata;

}

//******************************************************************************
//  Function    : DATE_FDSRCPARAM_src_lock_cntSet
//  Description : Set the value of the member FDSRCPARAM.src_lock_cnt
//  Input       : unsigned int usrc_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_cntSet(unsigned int usrc_lock_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.src_lock_cnt = usrc_lock_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcparam.u32, "FDSRCPARAM");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FDSRCPARAM_src_lock_valSet
//  Description : Set the value of the member FDSRCPARAM.src_lock_val
//  Input       : unsigned int usrc_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_valSet(unsigned int usrc_lock_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.src_lock_val = usrc_lock_val;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcparam.u32, "FDSRCPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_src_freq_extSet
//  Description : Set the value of the member FDSRCFREQ.src_freq_ext
//  Input       : unsigned int usrc_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_extSet(unsigned int usrc_freq_ext)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.src_freq_ext = usrc_freq_ext;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcfreq.u32, "FDSRCFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_fdsrcfreq_unused_2Set
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_2
//  Input       : unsigned int ufdsrcfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_2Set(unsigned int ufdsrcfreq_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.fdsrcfreq_unused_2 = ufdsrcfreq_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcfreq.u32, "FDSRCFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET0_txfifoset0_unusedSet
//  Description : Set the value of the member TXFIFOSET0.txfifoset0_unused
//  Input       : unsigned int utxfifoset0_unused: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_txfifoset0_unusedSet(unsigned int utxfifoset0_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset0.bits.txfifoset0_unused = utxfifoset0_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset0.u32, "TXFIFOSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_src_freq_optSet
//  Description : Set the value of the member FDSRCFREQ.src_freq_opt
//  Input       : unsigned int usrc_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_optSet(unsigned int usrc_freq_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.src_freq_opt = usrc_freq_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcfreq.u32, "FDSRCFREQ");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FDSRCFREQ_fdsrcfreq_unused_1Set
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_1
//  Input       : unsigned int ufdsrcfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_1Set(unsigned int ufdsrcfreq_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.fdsrcfreq_unused_1 = ufdsrcfreq_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcfreq.u32, "FDSRCFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_src_cnt_optSet
//  Description : Set the value of the member FDSRCFREQ.src_cnt_opt
//  Input       : unsigned int usrc_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_cnt_optSet(unsigned int usrc_cnt_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.src_cnt_opt = usrc_cnt_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcfreq.u32, "FDSRCFREQ");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FDSRCRES_src_cnt_outGet
//  Description : Set the value of the member FDSRCRES.src_cnt_out
//  Input       : unsigned int usrc_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_cnt_outGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcres.bits.src_cnt_out;


}
//******************************************************************************
//  Function    : DATE_FDSRCRES_src_det_statGet
//  Description : Set the value of the member FDSRCRES.src_det_stat
//  Input       : unsigned int usrc_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_det_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcres.bits.src_det_stat;


}
//******************************************************************************
//  Function    : DATE_CTSET0_ctset0_unusedSet
//  Description : Set the value of the member CTSET0.ctset0_unused
//  Input       : unsigned int uctset0_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_ctset0_unusedSet(unsigned int uctset0_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset0.bits.ctset0_unused = uctset0_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ctset0.u32, "CTSET0");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_CTSET0_i_runSet
//  Description : Set the value of the member CTSET0.i_run
//  Input       : unsigned int ui_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_runSet(unsigned int ui_run)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset0.bits.i_run = ui_run;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ctset0.u32, "CTSET0");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_CTSET0_i_enableSet
//  Description : Set the value of the member CTSET0.i_enable
//  Input       : unsigned int ui_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_enableSet(unsigned int ui_enable)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset0.bits.i_enable = ui_enable;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ctset0.u32, "CTSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCGPARAM_p_lock_modeSet
//  Description : Set the value of the member FCGPARAM.p_lock_mode
//  Input       : unsigned int up_lock_mode: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_lock_modeSet(unsigned int up_lock_mode)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgparam.bits.p_lock_mode = up_lock_mode;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgparam.u32, "FCGPARAM");

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : DATE_FCGPARAM_p_kiSet
//  Description : Set the value of the member FCGPARAM.p_ki
//  Input       : unsigned int up_ki: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_kiSet(unsigned int up_ki)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgparam.bits.p_ki = up_ki;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgparam.u32, "FCGPARAM");

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : DATE_FCGPARAM_p_lock_thSet
//  Description : Set the value of the member FCGPARAM.p_lock_th
//  Input       : unsigned int up_lock_th: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_lock_thSet(unsigned int up_lock_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgparam.bits.p_lock_th = up_lock_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgparam.u32, "FCGPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCNTR0_i_ref_cnt_lenSet
//  Description : Set the value of the member FCCNTR0.i_ref_cnt_len
//  Input       : unsigned int ui_ref_cnt_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_ref_cnt_lenSet(unsigned int ui_ref_cnt_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr0.bits.i_ref_cnt_len = ui_ref_cnt_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccntr0.u32, "FCCNTR0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCNTR0_i_vco_end_wait_lenSet
//  Description : Set the value of the member FCCNTR0.i_vco_end_wait_len
//  Input       : unsigned int ui_vco_end_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_end_wait_lenSet(unsigned int ui_vco_end_wait_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr0.bits.i_vco_end_wait_len = ui_vco_end_wait_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccntr0.u32, "FCCNTR0");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCCNTR0_i_vco_st_wait_lenSet
//  Description : Set the value of the member FCCNTR0.i_vco_st_wait_len
//  Input       : unsigned int ui_vco_st_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_st_wait_lenSet(unsigned int ui_vco_st_wait_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr0.bits.i_vco_st_wait_len = ui_vco_st_wait_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccntr0.u32, "FCCNTR0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCOPT_fcopt_unusedSet
//  Description : Set the value of the member FCOPT.fcopt_unused
//  Input       : unsigned int ufcopt_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unusedSet(unsigned int ufcopt_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.fcopt_unused = ufcopt_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_idx_selSet
//  Description : Set the value of the member FCOPT.i_ct_idx_sel
//  Input       : unsigned int ui_ct_idx_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_idx_selSet(unsigned int ui_ct_idx_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_idx_sel = ui_ct_idx_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCOPT_fcopt_unused_2Set
//  Description : Set the value of the member FCOPT.fcopt_unused_2
//  Input       : unsigned int ufcopt_unused_2: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_2Set(unsigned int ufcopt_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.fcopt_unused_2 = ufcopt_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_enSet
//  Description : Set the value of the member FCOPT.i_ct_en
//  Input       : unsigned int ui_ct_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_enSet(unsigned int ui_ct_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_en = ui_ct_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCOPT_fcopt_unused_1Set
//  Description : Set the value of the member FCOPT.fcopt_unused_1
//  Input       : unsigned int ufcopt_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_1Set(unsigned int ufcopt_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.fcopt_unused_1 = ufcopt_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_modeSet
//  Description : Set the value of the member FCOPT.i_ct_mode
//  Input       : unsigned int ui_ct_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_modeSet(unsigned int ui_ct_mode)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_mode = ui_ct_mode;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCOPT_i_clkdet_selSet
//  Description : Set the value of the member FCOPT.i_clkdet_sel
//  Input       : unsigned int ui_clkdet_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_clkdet_selSet(unsigned int ui_clkdet_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_clkdet_sel = ui_clkdet_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_selSet
//  Description : Set the value of the member FCOPT.i_ct_sel
//  Input       : unsigned int ui_ct_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_selSet(unsigned int ui_ct_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_sel = ui_ct_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcopt.u32, "FCOPT");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCSTAT_busyGet
//  Description : Set the value of the member FCSTAT.busy
//  Input       : unsigned int ubusy: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_busyGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.busy;


}

//******************************************************************************
//  Function    : DATE_FCDSTEPSET_up_sampler_ratio_selSet
//  Description : Set the value of the member FCDSTEPSET.up_sampler_ratio_sel
//  Input       : unsigned int uup_sampler_ratio_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_up_sampler_ratio_selSet(unsigned int uup_sampler_ratio_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepset.bits.up_sampler_ratio_sel = uup_sampler_ratio_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepset.u32, "FCDSTEPSET");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCDSTEPSET_fcdstepset_unusedSet
//  Description : Set the value of the member FCDSTEPSET.fcdstepset_unused
//  Input       : unsigned int ufcdstepset_unused: 1 bits
//  Return      : int: 0-Error, 1-Succes
//******************************************************************************
int HDMI_FCDSTEPSET_fcdstepset_unusedSet(unsigned int ufcdstepset_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepset.bits.fcdstepset_unused = ufcdstepset_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepset.u32, "FCDSTEPSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCDSTEPSET_p_divn_h20Set
//  Description : Set the value of the member FCDSTEPSET.p_divn_h20
//  Input       : unsigned int up_divn_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_p_divn_h20Set(unsigned int up_divn_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepset.bits.p_divn_h20 = up_divn_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepset.u32, "FCDSTEPSET");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCCNTR1_i_ref_cntSet
//  Description : Set the value of the member FCCNTR1.i_ref_cnt
//  Input       : unsigned int ui_ref_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR1_i_ref_cntSet(unsigned int ui_ref_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR1 o_fccntr1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR1.u32);
    o_fccntr1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr1.bits.i_ref_cnt = ui_ref_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccntr1.u32, "FCCNTR1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_stepSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_step
//  Input       : unsigned int up_contin_upd_step: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_stepSet(unsigned int up_contin_upd_step)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_step = up_contin_upd_step;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset0.u32, "FCCONTINSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_fccontinset0_unusedSet
//  Description : Set the value of the member FCCONTINSET0.fccontinset0_unused
//  Input       : unsigned int ufccontinset0_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_fccontinset0_unusedSet(unsigned int ufccontinset0_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.fccontinset0_unused = ufccontinset0_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset0.u32, "FCCONTINSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_polSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_pol
//  Input       : unsigned int up_contin_upd_pol: 1 bits
//  Return      : int: 0-Error, 1-Succes
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_polSet(unsigned int up_contin_upd_pol)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_pol = up_contin_upd_pol;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset0.u32, "FCCONTINSET0");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_optSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_opt
//  Input       : unsigned int up_contin_upd_opt: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_optSet(unsigned int up_contin_upd_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_opt = up_contin_upd_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset0.u32, "FCCONTINSET0");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_enSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_en
//  Input       : unsigned int up_contin_upd_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_enSet(unsigned int up_contin_upd_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_en = up_contin_upd_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset0.u32, "FCCONTINSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCONTINSET1_p_contin_upd_timeSet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_time
//  Input       : unsigned int up_contin_upd_time: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_timeSet(unsigned int up_contin_upd_time)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset1.bits.p_contin_upd_time = up_contin_upd_time;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset1.u32, "FCCONTINSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCONTINSET1_p_contin_upd_rateSet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_rate
//  Input       : unsigned int up_contin_upd_rate: 28 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_rateSet(unsigned int up_contin_upd_rate)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset1.bits.p_contin_upd_rate = up_contin_upd_rate;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset1.u32, "FCCONTINSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCONTINSET2_p_contin_upd_th_upSet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_up
//  Input       : unsigned int up_contin_upd_th_up: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_upSet(unsigned int up_contin_upd_th_up)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset2.bits.p_contin_upd_th_up = up_contin_upd_th_up;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset2.u32, "FCCONTINSET2");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCCONTINSET2_fccontinset2_unusedSet
//  Description : Set the value of the member FCCONTINSET2.fccontinset2_unused
//  Input       : unsigned int ufccontinset2_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_fccontinset2_unusedSet(unsigned int ufccontinset2_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset2.bits.fccontinset2_unused = ufccontinset2_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset2.u32, "FCCONTINSET2");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FCCONTINSET2_p_contin_upd_th_dnSet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_dn
//  Input       : unsigned int up_contin_upd_th_dn: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_dnSet(unsigned int up_contin_upd_th_dn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset2.bits.p_contin_upd_th_dn = up_contin_upd_th_dn;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccontinset2.u32, "FCCONTINSET2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET0_en_sdmSet
//  Description : Set the value of the member FDIVSET0.en_sdm
//  Input       : unsigned int uen_sdm: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************


int HDMI_FDIVSET0_en_sdmSet(unsigned int uen_sdm)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.en_sdm = uen_sdm;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset0.u32, "FDIVSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HDMI_MODE_reg_hdmi_mode_enSet
//  Description : Set the value of the member HDMI_MODE.reg_hdmi_mode_en
//  Input       : unsigned int ureg_hdmi_mode_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDMI_MODE_reg_hdmi_mode_enSet(unsigned int ureg_hdmi_mode_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HDMI_MODE o_hdmi_mode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HDMI_MODE.u32);
    o_hdmi_mode.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hdmi_mode.bits.reg_hdmi_mode_en = ureg_hdmi_mode_en;
    HDMI21TXRegWrite(pu32RegAddr, o_hdmi_mode.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hdmi_mode.u32, "HDMI_MODE");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET0_en_sdmGet
//  Description : Set the value of the member FDIVSET0.en_sdm
//  Input       : unsigned int uen_sdm: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_sdmGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.en_sdm;


}

//******************************************************************************
//  Function    : DATE_FDIVSET0_en_modSet
//  Description : Set the value of the member FDIVSET0.en_mod
//  Input       : unsigned int uen_mod: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_modSet(unsigned int uen_mod)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.en_mod = uen_mod;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset0.u32, "FDIVSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET0_en_modGet
//  Description : Set the value of the member FDIVSET0.en_mod
//  Input       : unsigned int uen_mod: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_modGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.en_mod;


}

//******************************************************************************
//  Function    : DATE_FDIVSET0_en_ctrlSet
//  Description : Set the value of the member FDIVSET0.en_ctrl
//  Input       : unsigned int uen_ctrl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_ctrlSet(unsigned int uen_ctrl)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.en_ctrl = uen_ctrl;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset0.u32, "FDIVSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET0_en_ctrlGet
//  Description : Set the value of the member FDIVSET0.en_ctrl
//  Input       : unsigned int uen_ctrl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_ctrlGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.en_ctrl;


}

//******************************************************************************
//  Function    : DATE_FDIVSET0_initSet
//  Description : Set the value of the member FDIVSET0.init
//  Input       : unsigned int uinit: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_initSet(unsigned int uinit)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.init = uinit;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset0.u32, "FDIVSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET3_mod_nSet
//  Description : Set the value of the member FDIVSET3.mod_n
//  Input       : unsigned int umod_n: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_nSet(unsigned int umod_n)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset3.bits.mod_n = umod_n;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset3.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset3.u32, "FDIVSET3");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FDIVSET3_mod_tSet
//  Description : Set the value of the member FDIVSET3.mod_t
//  Input       : unsigned int umod_t: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_tSet(unsigned int umod_t)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset3.bits.mod_t = umod_t;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset3.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset3.u32, "FDIVSET3");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FDIVSET3_mod_lenSet
//  Description : Set the value of the member FDIVSET3.mod_len
//  Input       : unsigned int umod_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_lenSet(unsigned int umod_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset3.bits.mod_len = umod_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset3.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset3.u32, "FDIVSET3");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET4_mod_dSet
//  Description : Set the value of the member FDIVSET4.mod_d
//  Input       : unsigned int umod_d: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET4_mod_dSet(unsigned int umod_d)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET4 o_fdivset4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET4.u32);
    o_fdivset4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset4.bits.mod_d = umod_d;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset4.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset4.u32, "FDIVSET4");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDSRCPARAM_fdsrcparam_unusedSet
//  Description : Set the value of the member FDSRCPARAM.fdsrcparam_unused
//  Input       : unsigned int ufdsrcparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_fdsrcparam_unusedSet(unsigned int ufdsrcparam_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.fdsrcparam_unused = ufdsrcparam_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcparam.u32, "FDSRCPARAM");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_FDIVSTAT1_i_fdiv_inSet
//  Description : Set the value of the member FDIVSTAT1.i_fdiv_in
//  Input       : unsigned int ui_fdiv_in: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT1_i_fdiv_inSet(unsigned int ui_fdiv_in)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT1 o_fdivstat1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT1.u32);
    o_fdivstat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat1.bits.i_fdiv_in = ui_fdiv_in;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat1.u32, "FDIVSTAT1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_mdivSet
//  Description : Set the value of the member FDIVMANUAL.i_mdiv
//  Input       : unsigned int ui_mdiv: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_mdivSet(unsigned int ui_mdiv)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_mdiv = ui_mdiv;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivmanual.u32, "FDIVMANUAL");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_frl_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_frl_clock
//  Input       : unsigned int usw_reset_frl_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_frl_clockSet(unsigned int usw_reset_frl_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_frl_clock = usw_reset_frl_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_swreset.u32, "SWRESET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_manual_enSet
//  Description : Set the value of the member FDIVMANUAL.i_manual_en
//  Input       : unsigned int ui_manual_en: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_manual_enSet(unsigned int ui_manual_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_manual_en = ui_manual_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivmanual.u32, "FDIVMANUAL");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_STBOPT_stb_delay1Set
//  Description : Set the value of the member STBOPT.stb_delay1
//  Input       : unsigned int ustb_delay1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay1Set(unsigned int ustb_delay1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_delay1 = ustb_delay1;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_stbopt.u32, "STBOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_REFCLKSEL_i_ref_clk_selSet
//  Description : Set the value of the member REFCLKSEL.i_ref_clk_sel
//  Input       : unsigned int ui_ref_clk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_i_ref_clk_selSet(unsigned int ui_ref_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.i_ref_clk_sel = ui_ref_clk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_refclksel.u32, "REFCLKSEL");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCGPARAM_p_lock_cntSet
//  Description : Set the value of the member FCGPARAM.p_lock_cnt
//  Input       : unsigned int up_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_lock_cntSet(unsigned int up_lock_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgparam.bits.p_lock_cnt = up_lock_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgparam.u32, "FCGPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_dither_enSet
//  Description : Set the value of the member FCGSET.p_fcg_dither_en
//  Input       : unsigned int up_fcg_dither_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_dither_enSet(unsigned int up_fcg_dither_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgset.bits.p_fcg_dither_en = up_fcg_dither_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgset.u32, "FCGSET");

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_dlf_enSet
//  Description : Set the value of the member FCGSET.p_fcg_dlf_en
//  Input       : unsigned int up_fcg_dlf_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_dlf_enSet(unsigned int up_fcg_dlf_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgset.bits.p_fcg_dlf_en = up_fcg_dlf_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgset.u32, "FCGSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCGSTATE_o_dlf_unGet
//  Description : Set the value of the member FCGSTATE.o_dlf_un
//  Input       : unsigned int uo_dlf_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSTATE_o_dlf_unGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSTATE o_fcgstate;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSTATE.u32);
    o_fcgstate.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgstate.bits.o_dlf_un;


}

//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_enSet
//  Description : Set the value of the member FCGSET.p_fcg_en
//  Input       : unsigned int up_fcg_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_enSet(unsigned int up_fcg_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgset.bits.p_fcg_en = up_fcg_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgset.u32, "FCGSET");

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : DATE_FCGCNT_p_cnt1_targetSet
//  Description : Set the value of the member FCGCNT.p_cnt1_target
//  Input       : unsigned int up_cnt1_target: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGCNT_p_cnt1_targetSet(unsigned int up_cnt1_target)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGCNT o_fcgcnt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGCNT.u32);
    o_fcgcnt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgcnt.bits.p_cnt1_target = up_cnt1_target;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgcnt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgcnt.u32, "FCGCNT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET0_p_enable_h20Set
//  Description : Set the value of the member TXFIFOSET0.p_enable_h20
//  Input       : unsigned int up_enable_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_enable_h20Set(unsigned int up_enable_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset0.bits.p_enable_h20 = up_enable_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset0.u32, "TXFIFOSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET0_p_pr_en_h20Set
//  Description : Set the value of the member TXFIFOSET0.p_pr_en_h20
//  Input       : unsigned int up_pr_en_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_pr_en_h20Set(unsigned int up_pr_en_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset0.bits.p_pr_en_h20 = up_pr_en_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset0.u32, "TXFIFOSET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXDATAOUTSEL_p_ch_out_selSet
//  Description : Set the value of the member TXDATAOUTSEL.p_ch_out_sel
//  Input       : unsigned int up_ch_out_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXDATAOUTSEL_p_ch_out_selSet(unsigned int up_ch_out_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXDATAOUTSEL o_txdataoutsel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXDATAOUTSEL.u32);
    o_txdataoutsel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txdataoutsel.bits.p_ch_out_sel = up_ch_out_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_txdataoutsel.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txdataoutsel.u32, "TXDATAOUTSEL");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXDATAOUTSEL_p_ch_out_selGet
//  Description : Set the value of the member TXDATAOUTSEL.p_ch_out_sel
//  Input       : unsigned int up_ch_out_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXDATAOUTSEL_p_ch_out_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXDATAOUTSEL o_txdataoutsel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXDATAOUTSEL.u32);
    o_txdataoutsel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txdataoutsel.bits.p_ch_out_sel;
}


//******************************************************************************
//  Function    : DATE_HSSET_p_hssetSet
//  Description : Set the value of the member HSSET.p_hsset
//  Input       : unsigned int up_hsset: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************

int HDMI_HSSET_p_hssetSet(unsigned int up_hsset)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSSET o_hsset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HSSET.u32);
    o_hsset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hsset.bits.p_hsset = up_hsset;
    HDMI21TXRegWrite(pu32RegAddr, o_hsset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hsset.u32, "HSSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_SWRESET_global_resetSet
//  Description : Set the value of the member SWRESET.global_reset
//  Input       : unsigned int uglobal_reset: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_global_resetSet(unsigned int uglobal_reset)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.global_reset = uglobal_reset;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_swreset.u32, "SWRESET");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_SWRESET_swreset_unusedSet
//  Description : Set the value of the member SWRESET.swreset_unused
//  Input       : unsigned int uswreset_unused: 14 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_swreset_unusedSet(unsigned int uswreset_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.swreset_unused = uswreset_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_swreset.u32, "SWRESET");

    return HI_SUCCESS;
}
//******************************************************************************
//  Function    : DATE_SWRESET_dac_clock_gatSet
//  Description : Set the value of the member SWRESET.dac_clock_gat
//  Input       : unsigned int udac_clock_gat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_dac_clock_gatSet(unsigned int udac_clock_gat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.dac_clock_gat = udac_clock_gat;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_swreset.u32, "SWRESET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_STBOPT_stb_delay2Set
//  Description : Set the value of the member STBOPT.stb_delay2
//  Input       : unsigned int ustb_delay2: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay2Set(unsigned int ustb_delay2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_delay2 = ustb_delay2;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_stbopt.u32, "STBOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_STBOPT_stb_cs_selSet
//  Description : Set the value of the member STBOPT.stb_cs_sel
//  Input       : unsigned int ustb_cs_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_cs_selSet(unsigned int ustb_cs_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_cs_sel = ustb_cs_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_stbopt.u32, "STBOPT");

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : DATE_STBOPT_stb_acc_selSet
//  Description : Set the value of the member STBOPT.stb_acc_sel
//  Input       : unsigned int ustb_acc_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_acc_selSet(unsigned int ustb_acc_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_acc_sel = ustb_acc_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_stbopt.u32, "STBOPT");

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : DATE_STBOPT_stb_delay0Set
//  Description : Set the value of the member STBOPT.stb_delay0
//  Input       : unsigned int ustb_delay0: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay0Set(unsigned int ustb_delay0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_delay0 = ustb_delay0;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_stbopt.u32, "STBOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCGSTATE_o_dlf_ovGet
//  Description : Set the value of the member FCGSTATE.o_dlf_ov
//  Input       : unsigned int uo_dlf_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSTATE_o_dlf_ovGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSTATE o_fcgstate;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSTATE.u32);
    o_fcgstate.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgstate.bits.o_dlf_ov;
}

//******************************************************************************
//  Function    : DATE_FCGSTATE_o_dlf_lockGet
//  Description : Set the value of the member FCGSTATE.o_dlf_lock
//  Input       : unsigned int uo_dlf_lock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSTATE_o_dlf_lockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSTATE o_fcgstate;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSTATE.u32);
    o_fcgstate.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgstate.bits.o_dlf_lock;
}

//******************************************************************************
//  Function    : DATE_CLKSET_p_fd_clk_selSet
//  Description : Set the value of the member CLKSET.p_fd_clk_sel
//  Input       : unsigned int up_fd_clk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fd_clk_selSet(unsigned int up_fd_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_fd_clk_sel = up_fd_clk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clkset.u32, "CLKSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLKSET_p_refclk_selSet
//  Description : Set the value of the member CLKSET.p_refclk_sel
//  Input       : unsigned int up_refclk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_refclk_selSet(unsigned int up_refclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_refclk_sel = up_refclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clkset.u32, "CLKSET");

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : DATE_CLKSET_p_ctmanSet
//  Description : Set the value of the member CLKSET.p_ctman
//  Input       : unsigned int up_ctman: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_ctmanSet(unsigned int up_ctman)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_ctman = up_ctman;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clkset.u32, "CLKSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_STBOPT_req_lengthSet
//  Description : Set the value of the member STBOPT.req_length
//  Input       : unsigned int ureq_length: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_req_lengthSet(unsigned int ureq_length)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.req_length = ureq_length;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_stbopt.u32, "STBOPT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLKSET_p_fdivclk_selSet
//  Description : Set the value of the member CLKSET.p_fdivclk_sel
//  Input       : unsigned int up_fdivclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fdivclk_selSet(unsigned int up_fdivclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_fdivclk_sel = up_fdivclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clkset.u32, "CLKSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLKSET_mod_div_valSet
//  Description : Set the value of the member CLKSET.mod_div_val
//  Input       : unsigned int umod_div_val: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_mod_div_valSet(unsigned int umod_div_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.mod_div_val = umod_div_val;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clkset.u32, "CLKSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLKSET_p_modclk_selSet
//  Description : Set the value of the member CLKSET.p_modclk_sel
//  Input       : unsigned int up_modclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_modclk_selSet(unsigned int up_modclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_modclk_sel = up_modclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clkset.u32, "CLKSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CTSET1_i_mpll_fconSet
//  Description : Set the value of the member CTSET1.i_mpll_fcon
//  Input       : unsigned int ui_mpll_fcon: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_fconSet(unsigned int ui_mpll_fcon)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset1.bits.i_mpll_fcon = ui_mpll_fcon;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ctset1.u32, "CTSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CTSET1_i_mpll_ctlckSet
//  Description : Set the value of the member CTSET1.i_mpll_ctlck
//  Input       : unsigned int ui_mpll_ctlck: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_ctlckSet(unsigned int ui_mpll_ctlck)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset1.bits.i_mpll_ctlck = ui_mpll_ctlck;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ctset1.u32, "CTSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CTSET1_ctset1_unusedSet
//  Description : Set the value of the member CTSET1.ctset1_unused
//  Input       : unsigned int uctset1_unused: 18 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_ctset1_unusedSet(unsigned int uctset1_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset1.bits.ctset1_unused = uctset1_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ctset1.u32, "CTSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_errorGet
//  Description : Set the value of the member FCSTAT.error
//  Input       : unsigned int uerror: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_errorGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.error;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_doneGet
//  Description : Set the value of the member FCSTAT.done
//  Input       : unsigned int udone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.done;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_clk_okGet
//  Description : Set the value of the member FCSTAT.clk_ok
//  Input       : unsigned int uclk_ok: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_clk_okGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.clk_ok;
}

//******************************************************************************
//  Function    : DATE_FCGCNT_p_tmds_cnt_valGet
//  Description : Set the value of the member FCGCNT.p_tmds_cnt_val
//  Input       : unsigned int up_tmds_cnt_val: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGCNT_p_tmds_cnt_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGCNT o_fcgcnt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGCNT.u32);
    o_fcgcnt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgcnt.bits.p_tmds_cnt_val;
}

//******************************************************************************
//  Function    : DATE_FCGCNT_p_tmds_cnt_valSet
//  Description : Set the value of the member FCGCNT.p_tmds_cnt_val
//  Input       : unsigned int up_tmds_cnt_val: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGCNT_p_tmds_cnt_valSet(unsigned int up_tmds_cnt_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGCNT o_fcgcnt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGCNT.u32);
    o_fcgcnt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgcnt.bits.p_tmds_cnt_val = up_tmds_cnt_val;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgcnt.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgcnt.u32, "FCGCNT");

    return HI_SUCCESS;
}

#ifdef HI3559A_TEST
//******************************************************************************
//  Function    : DATE_T2GPPORT0_gpport0Set
//  Description : Set the value of the member T2GPPORT0.gpport0
//  Input       : unsigned int ugpport0: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT0_gpport0Set(unsigned int ugpport0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT0 o_t2gpport0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->T2GPPORT0.u32);
    o_t2gpport0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_t2gpport0.bits.gpport0 = ugpport0;
    HDMI21TXRegWrite(pu32RegAddr, o_t2gpport0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_T2GPPORT0_gpport0Get
//  Description : Set the value of the member T2GPPORT0.gpport0
//  Input       : unsigned int ugpport0: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT0_gpport0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT0 o_t2gpport0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->T2GPPORT0.u32);
    o_t2gpport0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_t2gpport0.bits.gpport0;
}

//******************************************************************************
//  Function    : DATE_T2GPPORT1_gpport1Set
//  Description : Set the value of the member T2GPPORT1.gpport1
//  Input       : unsigned int ugpport1: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT1_gpport1Set(unsigned int ugpport1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT1 o_t2gpport1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->T2GPPORT1.u32);
    o_t2gpport1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_t2gpport1.bits.gpport1 = ugpport1;
    HDMI21TXRegWrite(pu32RegAddr, o_t2gpport1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_t2gpport1.u32, "T2GPPORT1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_T2GPPORT1_gpport1Get
//  Description : Set the value of the member T2GPPORT1.gpport1
//  Input       : unsigned int ugpport1: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT1_gpport1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT1 o_t2gpport1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->T2GPPORT1.u32);
    o_t2gpport1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_t2gpport1.bits.gpport1;


}

//******************************************************************************
//  Function    : DATE_PHY_CSEN_stb_cs_enGet
//  Description : Set the value of the member PHY_CSEN.stb_cs_en
//  Input       : unsigned int ustb_cs_en: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_CSEN_stb_cs_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_CSEN o_phy_csen;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_CSEN.u32);
    o_phy_csen.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_csen.bits.stb_cs_en;


}

//******************************************************************************
//  Function    : DATE_PHY_WR_stb_wenGet
//  Description : Set the value of the member PHY_WR.stb_wen
//  Input       : unsigned int ustb_wen: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WR_stb_wenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WR o_phy_wr;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_WR.u32);
    o_phy_wr.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_wr.bits.stb_wen;


}

//******************************************************************************
//  Function    : DATE_PHY_ADDR_stb_addrGet
//  Description : Set the value of the member PHY_ADDR.stb_addr
//  Input       : unsigned int ustb_addr: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_ADDR_stb_addrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_ADDR o_phy_addr;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_ADDR.u32);
    o_phy_addr.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_addr.bits.stb_addr;


}

//******************************************************************************
//  Function    : DATE_PHY_WDATA_stb_wdataGet
//  Description : Set the value of the member PHY_WDATA.stb_wdata
//  Input       : unsigned int ustb_wdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WDATA_stb_wdataGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WDATA o_phy_wdata;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_WDATA.u32);
    o_phy_wdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_wdata.bits.stb_wdata;


}

//******************************************************************************
//  Function    : DATE_PHY_RDATA_stb_rdataSet
//  Description : Set the value of the member PHY_RDATA.stb_rdata
//  Input       : unsigned int ustb_rdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_RDATA_stb_rdataSet(unsigned int ustb_rdata)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_RDATA o_phy_rdata;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->PHY_RDATA.u32);
    o_phy_rdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_rdata.bits.stb_rdata = ustb_rdata;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_rdata.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_phy_rdata.u32, "PHY_RDATA");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_ZCALREG_rxsenseSet
//  Description : Set the value of the member ZCALREG.rxsense
//  Input       : unsigned int urxsense: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_rxsenseSet(unsigned int urxsense)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.rxsense = urxsense;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_zcalreg.u32, "ZCALREG");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_ZCALREG_rxsenseGet
//  Description : Set the value of the member ZCALREG.rxsense
//  Input       : unsigned int urxsense: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_rxsenseGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.rxsense;

}

//******************************************************************************
//  Function    : DATE_ZCALREG_zcalsubSet
//  Description : Set the value of the member ZCALREG.zcalsub
//  Input       : unsigned int uzcalsub: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalsubSet(unsigned int uzcalsub)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.zcalsub = uzcalsub;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_zcalreg.u32, "ZCALREG");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_ZCALREG_zcalsubGet
//  Description : Set the value of the member ZCALREG.zcalsub
//  Input       : unsigned int uzcalsub: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalsubGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.zcalsub;


}

//******************************************************************************
//  Function    : DATE_ZCALREG_zcaldoneSet
//  Description : Set the value of the member ZCALREG.zcaldone
//  Input       : unsigned int uzcaldone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcaldoneSet(unsigned int uzcaldone)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.zcaldone = uzcaldone;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_zcalreg.u32, "ZCALREG");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_ZCALREG_zcaldoneGet
//  Description : Set the value of the member ZCALREG.zcaldone
//  Input       : unsigned int uzcaldone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcaldoneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.zcaldone;


}

//******************************************************************************
//  Function    : DATE_ZCALREG_zcalSet
//  Description : Set the value of the member ZCALREG.zcal
//  Input       : unsigned int uzcal: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalSet(unsigned int uzcal)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.zcal = uzcal;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_zcalreg.u32, "ZCALREG");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_ZCALREG_zcalGet
//  Description : Set the value of the member ZCALREG.zcal
//  Input       : unsigned int uzcal: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.zcal;


}

//******************************************************************************
//  Function    : DATE_ZCALCLK_zcalclkSet
//  Description : Set the value of the member ZCALCLK.zcalclk
//  Input       : unsigned int uzcalclk: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALCLK_zcalclkSet(unsigned int uzcalclk)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALCLK o_zcalclk;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALCLK.u32);
    o_zcalclk.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalclk.bits.zcalclk = uzcalclk;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalclk.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_zcalclk.u32, "ZCALCLK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_ZCALCLK_zcalclkGet
//  Description : Set the value of the member ZCALCLK.zcalclk
//  Input       : unsigned int uzcalclk: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALCLK_zcalclkGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALCLK o_zcalclk;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->ZCALCLK.u32);
    o_zcalclk.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalclk.bits.zcalclk;


}

//******************************************************************************
//  Function    : DATE_SHORTDET_clkshortdetSet
//  Description : Set the value of the member SHORTDET.clkshortdet
//  Input       : unsigned int uclkshortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_clkshortdetSet(unsigned int uclkshortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.clkshortdet = uclkshortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_shortdet.u32, "SHORTDET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_SHORTDET_clkshortdetGet
//  Description : Set the value of the member SHORTDET.clkshortdet
//  Input       : unsigned int uclkshortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_clkshortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.clkshortdet;


}

//******************************************************************************
//  Function    : DATE_SHORTDET_c2shortdetSet
//  Description : Set the value of the member SHORTDET.c2shortdet
//  Input       : unsigned int uc2shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c2shortdetSet(unsigned int uc2shortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.c2shortdet = uc2shortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_shortdet.u32, "SHORTDET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_SHORTDET_c2shortdetGet
//  Description : Set the value of the member SHORTDET.c2shortdet
//  Input       : unsigned int uc2shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c2shortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.c2shortdet;


}

//******************************************************************************
//  Function    : DATE_SHORTDET_c1shortdetSet
//  Description : Set the value of the member SHORTDET.c1shortdet
//  Input       : unsigned int uc1shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c1shortdetSet(unsigned int uc1shortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.c1shortdet = uc1shortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_shortdet.u32, "SHORTDET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_SHORTDET_c1shortdetGet
//  Description : Set the value of the member SHORTDET.c1shortdet
//  Input       : unsigned int uc1shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c1shortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.c1shortdet;


}

//******************************************************************************
//  Function    : DATE_SHORTDET_c0shortdetSet
//  Description : Set the value of the member SHORTDET.c0shortdet
//  Input       : unsigned int uc0shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c0shortdetSet(unsigned int uc0shortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.c0shortdet = uc0shortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_shortdet.u32, "SHORTDET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_SHORTDET_c0shortdetGet
//  Description : Set the value of the member SHORTDET.c0shortdet
//  Input       : unsigned int uc0shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c0shortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.c0shortdet;


}

//******************************************************************************
//  Function    : DATE_DET_t2_lkvdethighSet
//  Description : Set the value of the member DET.t2_lkvdethigh
//  Input       : unsigned int ut2_lkvdethigh: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdethighSet(unsigned int ut2_lkvdethigh)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_lkvdethigh = ut2_lkvdethigh;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_det.u32, "DET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_DET_t2_lkvdethighGet
//  Description : Set the value of the member DET.t2_lkvdethigh
//  Input       : unsigned int ut2_lkvdethigh: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdethighGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_lkvdethigh;


}

//******************************************************************************
//  Function    : DATE_DET_t2_lkvdetlowSet
//  Description : Set the value of the member DET.t2_lkvdetlow
//  Input       : unsigned int ut2_lkvdetlow: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdetlowSet(unsigned int ut2_lkvdetlow)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_lkvdetlow = ut2_lkvdetlow;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_det.u32, "DET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_DET_t2_lkvdetlowGet
//  Description : Set the value of the member DET.t2_lkvdetlow
//  Input       : unsigned int ut2_lkvdetlow: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdetlowGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_lkvdetlow;


}

//******************************************************************************
//  Function    : DATE_DET_t2_plllkvdet2Set
//  Description : Set the value of the member DET.t2_plllkvdet2
//  Input       : unsigned int ut2_plllkvdet2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdet2Set(unsigned int ut2_plllkvdet2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_plllkvdet2 = ut2_plllkvdet2;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_det.u32, "DET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_DET_t2_plllkvdet2Get
//  Description : Set the value of the member DET.t2_plllkvdet2
//  Input       : unsigned int ut2_plllkvdet2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdet2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_plllkvdet2;


}

//******************************************************************************
//  Function    : DATE_DET_t2_plllkcdetSet
//  Description : Set the value of the member DET.t2_plllkcdet
//  Input       : unsigned int ut2_plllkcdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkcdetSet(unsigned int ut2_plllkcdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_plllkcdet = ut2_plllkcdet;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_det.u32, "DET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_DET_t2_plllkcdetGet
//  Description : Set the value of the member DET.t2_plllkcdet
//  Input       : unsigned int ut2_plllkcdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkcdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_plllkcdet;


}

//******************************************************************************
//  Function    : DATE_DET_t2_plllkvdetlSet
//  Description : Set the value of the member DET.t2_plllkvdetl
//  Input       : unsigned int ut2_plllkvdetl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdetlSet(unsigned int ut2_plllkvdetl)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_plllkvdetl = ut2_plllkvdetl;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_det.u32, "DET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_DET_t2_plllkvdetlGet
//  Description : Set the value of the member DET.t2_plllkvdetl
//  Input       : unsigned int ut2_plllkvdetl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdetlGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_plllkvdetl;


}

//******************************************************************************
//  Function    : DATE_FDSRCPARAM_fdsrcparam_unusedGet
//  Description : Set the value of the member FDSRCPARAM.fdsrcparam_unused
//  Input       : unsigned int ufdsrcparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_fdsrcparam_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.fdsrcparam_unused;


}

//******************************************************************************
//  Function    : DATE_FDSRCPARAM_src_enableGet
//  Description : Set the value of the member FDSRCPARAM.src_enable
//  Input       : unsigned int usrc_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_enableGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.src_enable;


}

//******************************************************************************
//  Function    : DATE_FDSRCPARAM_src_lock_cntGet
//  Description : Set the value of the member FDSRCPARAM.src_lock_cnt
//  Input       : unsigned int usrc_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.src_lock_cnt;


}

//******************************************************************************
//  Function    : DATE_FDSRCPARAM_src_lock_valGet
//  Description : Set the value of the member FDSRCPARAM.src_lock_val
//  Input       : unsigned int usrc_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.src_lock_val;


}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_src_freq_extGet
//  Description : Set the value of the member FDSRCFREQ.src_freq_ext
//  Input       : unsigned int usrc_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_extGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.src_freq_ext;


}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_fdsrcfreq_unused_2Get
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_2
//  Input       : unsigned int ufdsrcfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.fdsrcfreq_unused_2;


}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_src_freq_optGet
//  Description : Set the value of the member FDSRCFREQ.src_freq_opt
//  Input       : unsigned int usrc_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.src_freq_opt;


}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_fdsrcfreq_unused_1Get
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_1
//  Input       : unsigned int ufdsrcfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.fdsrcfreq_unused_1;


}

//******************************************************************************
//  Function    : DATE_FDSRCFREQ_src_cnt_optGet
//  Description : Set the value of the member FDSRCFREQ.src_cnt_opt
//  Input       : unsigned int usrc_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_cnt_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.src_cnt_opt;


}

//******************************************************************************
//  Function    : DATE_FDSRCRES_src_cnt_outSet
//  Description : Set the value of the member FDSRCRES.src_cnt_out
//  Input       : unsigned int usrc_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_cnt_outSet(unsigned int usrc_cnt_out)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcres.bits.src_cnt_out = usrc_cnt_out;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcres.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcres.u32, "FDSRCRES");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDSRCRES_src_det_statSet
//  Description : Set the value of the member FDSRCRES.src_det_stat
//  Input       : unsigned int usrc_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_det_statSet(unsigned int usrc_det_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcres.bits.src_det_stat = usrc_det_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcres.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdsrcres.u32, "FDSRCRES");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CTSET0_ctset0_unusedGet
//  Description : Set the value of the member CTSET0.ctset0_unused
//  Input       : unsigned int uctset0_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_ctset0_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset0.bits.ctset0_unused;


}

//******************************************************************************
//  Function    : DATE_CTSET0_i_runGet
//  Description : Set the value of the member CTSET0.i_run
//  Input       : unsigned int ui_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_runGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset0.bits.i_run;


}

//******************************************************************************
//  Function    : DATE_CTSET0_i_enableGet
//  Description : Set the value of the member CTSET0.i_enable
//  Input       : unsigned int ui_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_enableGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset0.bits.i_enable;


}

//******************************************************************************
//  Function    : DATE_CTSET1_ctset1_unusedGet
//  Description : Set the value of the member CTSET1.ctset1_unused
//  Input       : unsigned int uctset1_unused: 18 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_ctset1_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.ctset1_unused;


}

//******************************************************************************
//  Function    : DATE_CTSET1_i_mpll_ctlckGet
//  Description : Set the value of the member CTSET1.i_mpll_ctlck
//  Input       : unsigned int ui_mpll_ctlck: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_ctlckGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.i_mpll_ctlck;


}



//******************************************************************************
//  Function    : DATE_CTSET1_i_mpll_divnGet
//  Description : Set the value of the member CTSET1.i_mpll_divn
//  Input       : unsigned int ui_mpll_divn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_divnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.i_mpll_divn;


}


//******************************************************************************
//  Function    : DATE_CTSET1_i_mpll_fconGet
//  Description : Set the value of the member CTSET1.i_mpll_fcon
//  Input       : unsigned int ui_mpll_fcon: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_fconGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.i_mpll_fcon;


}

//******************************************************************************
//  Function    : DATE_FCCNTR0_i_ref_cnt_lenGet
//  Description : Set the value of the member FCCNTR0.i_ref_cnt_len
//  Input       : unsigned int ui_ref_cnt_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_ref_cnt_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_ref_cnt_len;


}

//******************************************************************************
//  Function    : DATE_FCCNTR0_i_vco_end_wait_lenGet
//  Description : Set the value of the member FCCNTR0.i_vco_end_wait_len
//  Input       : unsigned int ui_vco_end_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_end_wait_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_vco_end_wait_len;


}

//******************************************************************************
//  Function    : DATE_FCCNTR0_i_vco_st_wait_lenGet
//  Description : Set the value of the member FCCNTR0.i_vco_st_wait_len
//  Input       : unsigned int ui_vco_st_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_st_wait_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_vco_st_wait_len;


}

//******************************************************************************
//  Function    : DATE_FCCNTR0_i_deci_cnt_lenGet
//  Description : Set the value of the member FCCNTR0.i_deci_cnt_len
//  Input       : unsigned int ui_deci_cnt_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_deci_cnt_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_deci_cnt_len;


}

//******************************************************************************
//  Function    : DATE_FCOPT_fcopt_unusedGet
//  Description : Set the value of the member FCOPT.fcopt_unused
//  Input       : unsigned int ufcopt_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.fcopt_unused;


}

//******************************************************************************
//  Function    : DATE_FCOPT_i_deci_try_selGet
//  Description : Set the value of the member FCOPT.i_deci_try_sel
//  Input       : unsigned int ui_deci_try_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_deci_try_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_deci_try_sel;


}

//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_idx_selGet
//  Description : Set the value of the member FCOPT.i_ct_idx_sel
//  Input       : unsigned int ui_ct_idx_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_idx_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_idx_sel;


}

//******************************************************************************
//  Function    : DATE_FCOPT_fcopt_unused_2Get
//  Description : Set the value of the member FCOPT.fcopt_unused_2
//  Input       : unsigned int ufcopt_unused_2: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.fcopt_unused_2;


}

//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_enGet
//  Description : Set the value of the member FCOPT.i_ct_en
//  Input       : unsigned int ui_ct_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_en;


}

//******************************************************************************
//  Function    : DATE_FCOPT_fcopt_unused_1Get
//  Description : Set the value of the member FCOPT.fcopt_unused_1
//  Input       : unsigned int ufcopt_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.fcopt_unused_1;


}

//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_modeGet
//  Description : Set the value of the member FCOPT.i_ct_mode
//  Input       : unsigned int ui_ct_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_mode;


}

//******************************************************************************
//  Function    : DATE_FCOPT_i_clkdet_selGet
//  Description : Set the value of the member FCOPT.i_clkdet_sel
//  Input       : unsigned int ui_clkdet_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_clkdet_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_clkdet_sel;


}

//******************************************************************************
//  Function    : DATE_FCOPT_i_ct_selGet
//  Description : Set the value of the member FCOPT.i_ct_sel
//  Input       : unsigned int ui_ct_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_sel;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcon_initSet
//  Description : Set the value of the member FCSTAT.fcon_init
//  Input       : unsigned int ufcon_init: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcon_initSet(unsigned int ufcon_init)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcon_init = ufcon_init;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcon_initGet
//  Description : Set the value of the member FCSTAT.fcon_init
//  Input       : unsigned int ufcon_init: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcon_initGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcon_init;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcstat_unused_3Set
//  Description : Set the value of the member FCSTAT.fcstat_unused_3
//  Input       : unsigned int ufcstat_unused_3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_3Set(unsigned int ufcstat_unused_3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcstat_unused_3 = ufcstat_unused_3;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcstat_unused_3Get
//  Description : Set the value of the member FCSTAT.fcstat_unused_3
//  Input       : unsigned int ufcstat_unused_3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcstat_unused_3;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_confin_statSet
//  Description : Set the value of the member FCSTAT.confin_stat
//  Input       : unsigned int uconfin_stat: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_confin_statSet(unsigned int uconfin_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.confin_stat = uconfin_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_confin_statGet
//  Description : Set the value of the member FCSTAT.confin_stat
//  Input       : unsigned int uconfin_stat: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_confin_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.confin_stat;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcstat_unused_2Set
//  Description : Set the value of the member FCSTAT.fcstat_unused_2
//  Input       : unsigned int ufcstat_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_2Set(unsigned int ufcstat_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcstat_unused_2 = ufcstat_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcstat_unused_2Get
//  Description : Set the value of the member FCSTAT.fcstat_unused_2
//  Input       : unsigned int ufcstat_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcstat_unused_2;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_pllvco_clk_statSet
//  Description : Set the value of the member FCSTAT.pllvco_clk_stat
//  Input       : unsigned int upllvco_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_pllvco_clk_statSet(unsigned int upllvco_clk_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.pllvco_clk_stat = upllvco_clk_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_pllvco_clk_statGet
//  Description : Set the value of the member FCSTAT.pllvco_clk_stat
//  Input       : unsigned int upllvco_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_pllvco_clk_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.pllvco_clk_stat;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_ref_clk_statSet
//  Description : Set the value of the member FCSTAT.ref_clk_stat
//  Input       : unsigned int uref_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_ref_clk_statSet(unsigned int uref_clk_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.ref_clk_stat = uref_clk_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_ref_clk_statGet
//  Description : Set the value of the member FCSTAT.ref_clk_stat
//  Input       : unsigned int uref_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_ref_clk_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.ref_clk_stat;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcstat_unused_1Set
//  Description : Set the value of the member FCSTAT.fcstat_unused_1
//  Input       : unsigned int ufcstat_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_1Set(unsigned int ufcstat_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcstat_unused_1 = ufcstat_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_fcstat_unused_1Get
//  Description : Set the value of the member FCSTAT.fcstat_unused_1
//  Input       : unsigned int ufcstat_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcstat_unused_1;


}

//******************************************************************************
//  Function    : DATE_FCSTAT_divnSet
//  Description : Set the value of the member FCSTAT.divn
//  Input       : unsigned int udivn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_divnSet(unsigned int udivn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.divn = udivn;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_divnGet
//  Description : Set the value of the member FCSTAT.divn
//  Input       : unsigned int udivn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_divnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.divn;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_errorSet
//  Description : Set the value of the member FCSTAT.error
//  Input       : unsigned int uerror: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_errorSet(unsigned int uerror)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.error = uerror;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_doneSet
//  Description : Set the value of the member FCSTAT.done
//  Input       : unsigned int udone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_doneSet(unsigned int udone)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.done = udone;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCSTAT_busySet
//  Description : Set the value of the member FCSTAT.busy
//  Input       : unsigned int ubusy: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_busySet(unsigned int ubusy)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.busy = ubusy;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : DATE_FCSTAT_clk_okSet
//  Description : Set the value of the member FCSTAT.clk_ok
//  Input       : unsigned int uclk_ok: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_clk_okSet(unsigned int uclk_ok)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.clk_ok = uclk_ok;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcstat.u32, "FCSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCNTVAL0_o_cnt_refSet
//  Description : Set the value of the member FCCNTVAL0.o_cnt_ref
//  Input       : unsigned int uo_cnt_ref: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL0_o_cnt_refSet(unsigned int uo_cnt_ref)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL0 o_fccntval0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTVAL0.u32);
    o_fccntval0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntval0.bits.o_cnt_ref = uo_cnt_ref;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntval0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccntval0.u32, "FCCNTVAL0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCNTVAL0_o_cnt_refGet
//  Description : Set the value of the member FCCNTVAL0.o_cnt_ref
//  Input       : unsigned int uo_cnt_ref: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL0_o_cnt_refGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL0 o_fccntval0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTVAL0.u32);
    o_fccntval0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntval0.bits.o_cnt_ref;


}

//******************************************************************************
//  Function    : DATE_FCCNTVAL1_o_cnt_mpllSet
//  Description : Set the value of the member FCCNTVAL1.o_cnt_mpll
//  Input       : unsigned int uo_cnt_mpll: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL1_o_cnt_mpllSet(unsigned int uo_cnt_mpll)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL1 o_fccntval1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTVAL1.u32);
    o_fccntval1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntval1.bits.o_cnt_mpll = uo_cnt_mpll;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntval1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fccntval1.u32, "FCCNTVAL1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCCNTVAL1_o_cnt_mpllGet
//  Description : Set the value of the member FCCNTVAL1.o_cnt_mpll
//  Input       : unsigned int uo_cnt_mpll: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL1_o_cnt_mpllGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL1 o_fccntval1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTVAL1.u32);
    o_fccntval1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntval1.bits.o_cnt_mpll;


}

//******************************************************************************
//  Function    : DATE_FCRESVAL_o_fcon_mpllSet
//  Description : Set the value of the member FCRESVAL.o_fcon_mpll
//  Input       : unsigned int uo_fcon_mpll: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_fcon_mpllSet(unsigned int uo_fcon_mpll)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcresval.bits.o_fcon_mpll = uo_fcon_mpll;
    HDMI21TXRegWrite(pu32RegAddr, o_fcresval.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcresval.u32, "FCRESVAL");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCRESVAL_o_fcon_mpllGet
//  Description : Set the value of the member FCRESVAL.o_fcon_mpll
//  Input       : unsigned int uo_fcon_mpll: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_fcon_mpllGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcresval.bits.o_fcon_mpll;


}

//******************************************************************************
//  Function    : DATE_FCRESVAL_fcresval_unusedSet
//  Description : Set the value of the member FCRESVAL.fcresval_unused
//  Input       : unsigned int ufcresval_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_fcresval_unusedSet(unsigned int ufcresval_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcresval.bits.fcresval_unused = ufcresval_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fcresval.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcresval.u32, "FCRESVAL");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCRESVAL_fcresval_unusedGet
//  Description : Set the value of the member FCRESVAL.fcresval_unused
//  Input       : unsigned int ufcresval_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_fcresval_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcresval.bits.fcresval_unused;


}

//******************************************************************************
//  Function    : DATE_FCRESVAL_o_divn_mpllSet
//  Description : Set the value of the member FCRESVAL.o_divn_mpll
//  Input       : unsigned int uo_divn_mpll: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_divn_mpllSet(unsigned int uo_divn_mpll)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcresval.bits.o_divn_mpll = uo_divn_mpll;
    HDMI21TXRegWrite(pu32RegAddr, o_fcresval.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcresval.u32, "FCRESVAL");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCRESVAL_o_divn_mpllGet
//  Description : Set the value of the member FCRESVAL.o_divn_mpll
//  Input       : unsigned int uo_divn_mpll: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_divn_mpllGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcresval.bits.o_divn_mpll;


}



//******************************************************************************
//  Function    : DATE_FCDSTEPSET_up_sampler_ratio_selGet
//  Description : Set the value of the member FCDSTEPSET.up_sampler_ratio_sel
//  Input       : unsigned int uup_sampler_ratio_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_up_sampler_ratio_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepset.bits.up_sampler_ratio_sel;


}



//******************************************************************************
//  Function    : DATE_FCDSTEPSET_fcdstepset_unusedGet
//  Description : Set the value of the member FCDSTEPSET.fcdstepset_unused
//  Input       : unsigned int ufcdstepset_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_fcdstepset_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepset.bits.fcdstepset_unused;


}



//******************************************************************************
//  Function    : DATE_FCDSTEPSET_p_divn_h20Get
//  Description : Set the value of the member FCDSTEPSET.p_divn_h20
//  Input       : unsigned int up_divn_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_p_divn_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepset.bits.p_divn_h20;


}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH_i_deci_selSet
//  Description : Set the value of the member FCDSTEPTH.i_deci_sel
//  Input       : unsigned int ui_deci_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_deci_selSet(unsigned int ui_deci_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth.bits.i_deci_sel = ui_deci_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepth.u32, "FCDSTEPTH");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH_i_deci_selGet
//  Description : Set the value of the member FCDSTEPTH.i_deci_sel
//  Input       : unsigned int ui_deci_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_deci_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth.bits.i_deci_sel;


}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH_i_h2_selSet
//  Description : Set the value of the member FCDSTEPTH.i_h2_sel
//  Input       : unsigned int ui_h2_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_h2_selSet(unsigned int ui_h2_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth.bits.i_h2_sel = ui_h2_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepth.u32, "FCDSTEPTH");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH_i_h2_selGet
//  Description : Set the value of the member FCDSTEPTH.i_h2_sel
//  Input       : unsigned int ui_h2_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_h2_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth.bits.i_h2_sel;


}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH0_i_deci4x_thSet
//  Description : Set the value of the member FCDSTEPTH0.i_deci4x_th
//  Input       : unsigned int ui_deci4x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci4x_thSet(unsigned int ui_deci4x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth0.bits.i_deci4x_th = ui_deci4x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepth0.u32, "FCDSTEPTH0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH0_i_deci4x_thGet
//  Description : Set the value of the member FCDSTEPTH0.i_deci4x_th
//  Input       : unsigned int ui_deci4x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci4x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth0.bits.i_deci4x_th;


}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH0_i_deci2x_thSet
//  Description : Set the value of the member FCDSTEPTH0.i_deci2x_th
//  Input       : unsigned int ui_deci2x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci2x_thSet(unsigned int ui_deci2x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth0.bits.i_deci2x_th = ui_deci2x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepth0.u32, "FCDSTEPTH0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH0_i_deci2x_thGet
//  Description : Set the value of the member FCDSTEPTH0.i_deci2x_th
//  Input       : unsigned int ui_deci2x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci2x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth0.bits.i_deci2x_th;


}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH1_i_deci16x_thSet
//  Description : Set the value of the member FCDSTEPTH1.i_deci16x_th
//  Input       : unsigned int ui_deci16x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci16x_thSet(unsigned int ui_deci16x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth1.bits.i_deci16x_th = ui_deci16x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepth1.u32, "FCDSTEPTH1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH1_i_deci16x_thGet
//  Description : Set the value of the member FCDSTEPTH1.i_deci16x_th
//  Input       : unsigned int ui_deci16x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci16x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth1.bits.i_deci16x_th;


}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH1_i_deci8x_thSet
//  Description : Set the value of the member FCDSTEPTH1.i_deci8x_th
//  Input       : unsigned int ui_deci8x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci8x_thSet(unsigned int ui_deci8x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth1.bits.i_deci8x_th = ui_deci8x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcdstepth1.u32, "FCDSTEPTH1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCDSTEPTH1_i_deci8x_thGet
//  Description : Set the value of the member FCDSTEPTH1.i_deci8x_th
//  Input       : unsigned int ui_deci8x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci8x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth1.bits.i_deci8x_th;


}

//******************************************************************************
//  Function    : DATE_FCCNTR1_i_ref_cntGet
//  Description : Set the value of the member FCCNTR1.i_ref_cnt
//  Input       : unsigned int ui_ref_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR1_i_ref_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR1 o_fccntr1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCNTR1.u32);
    o_fccntr1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr1.bits.i_ref_cnt;


}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_stepGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_step
//  Input       : unsigned int up_contin_upd_step: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_stepGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_step;


}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_fccontinset0_unusedGet
//  Description : Set the value of the member FCCONTINSET0.fccontinset0_unused
//  Input       : unsigned int ufccontinset0_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_fccontinset0_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.fccontinset0_unused;


}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_polGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_pol
//  Input       : unsigned int up_contin_upd_pol: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_polGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_pol;


}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_optGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_opt
//  Input       : unsigned int up_contin_upd_opt: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_opt;


}

//******************************************************************************
//  Function    : DATE_FCCONTINSET0_p_contin_upd_enGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_en
//  Input       : unsigned int up_contin_upd_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_en;


}

//******************************************************************************
//  Function    : DATE_FCCONTINSET1_p_contin_upd_timeGet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_time
//  Input       : unsigned int up_contin_upd_time: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_timeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset1.bits.p_contin_upd_time;


}

//******************************************************************************
//  Function    : DATE_FCCONTINSET1_p_contin_upd_rateGet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_rate
//  Input       : unsigned int up_contin_upd_rate: 28 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_rateGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset1.bits.p_contin_upd_rate;


}


//******************************************************************************
//  Function    : DATE_FCCONTINSET2_p_contin_upd_th_upGet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_up
//  Input       : unsigned int up_contin_upd_th_up: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_upGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset2.bits.p_contin_upd_th_up;


}


//******************************************************************************
//  Function    : DATE_FCCONTINSET2_fccontinset2_unusedGet
//  Description : Set the value of the member FCCONTINSET2.fccontinset2_unused
//  Input       : unsigned int ufccontinset2_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_fccontinset2_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset2.bits.fccontinset2_unused;


}



//******************************************************************************
//  Function    : DATE_FCCONTINSET2_p_contin_upd_th_dnGet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_dn
//  Input       : unsigned int up_contin_upd_th_dn: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_dnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset2.bits.p_contin_upd_th_dn;


}



//******************************************************************************
//  Function    : DATE_FDIVSET0_initGet
//  Description : Set the value of the member FDIVSET0.init
//  Input       : unsigned int uinit: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_initGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.init;


}



//******************************************************************************
//  Function    : DATE_FDIVSET1_step_nGet
//  Description : Set the value of the member FDIVSET1.step_n
//  Input       : unsigned int ustep_n: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_nGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset1.bits.step_n;


}



//******************************************************************************
//  Function    : DATE_FDIVSET1_step_tGet
//  Description : Set the value of the member FDIVSET1.step_t
//  Input       : unsigned int ustep_t: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_tGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset1.bits.step_t;


}



//******************************************************************************
//  Function    : DATE_FDIVSET1_step_dGet
//  Description : Set the value of the member FDIVSET1.step_d
//  Input       : unsigned int ustep_d: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_dGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset1.bits.step_d;


}

//******************************************************************************
//  Function    : DATE_FDIVSET2_dnSet
//  Description : Set the value of the member FDIVSET2.dn
//  Input       : unsigned int udn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_dnSet(unsigned int udn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset2.bits.dn = udn;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset2.u32, "FDIVSET2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET2_dnGet
//  Description : Set the value of the member FDIVSET2.dn
//  Input       : unsigned int udn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_dnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset2.bits.dn;


}

//******************************************************************************
//  Function    : DATE_FDIVSET2_upSet
//  Description : Set the value of the member FDIVSET2.up
//  Input       : unsigned int uup: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_upSet(unsigned int uup)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset2.bits.up = uup;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset2.u32, "FDIVSET2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET2_upGet
//  Description : Set the value of the member FDIVSET2.up
//  Input       : unsigned int uup: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_upGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset2.bits.up;


}


//******************************************************************************
//  Function    : DATE_FDIVSET3_mod_nGet
//  Description : Set the value of the member FDIVSET3.mod_n
//  Input       : unsigned int umod_n: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_nGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset3.bits.mod_n;


}

//******************************************************************************
//  Function    : DATE_FDIVSET3_mod_tGet
//  Description : Set the value of the member FDIVSET3.mod_t
//  Input       : unsigned int umod_t: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_tGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset3.bits.mod_t;


}

//******************************************************************************
//  Function    : DATE_FDIVSET3_mod_lenGet
//  Description : Set the value of the member FDIVSET3.mod_len
//  Input       : unsigned int umod_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset3.bits.mod_len;


}

//******************************************************************************
//  Function    : DATE_FDIVSET4_mod_dGet
//  Description : Set the value of the member FDIVSET4.mod_d
//  Input       : unsigned int umod_d: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET4_mod_dGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET4 o_fdivset4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET4.u32);
    o_fdivset4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset4.bits.mod_d;


}

//******************************************************************************
//  Function    : DATE_FDIVSET5_fdivset5_unusedSet
//  Description : Set the value of the member FDIVSET5.fdivset5_unused
//  Input       : unsigned int ufdivset5_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_fdivset5_unusedSet(unsigned int ufdivset5_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset5.bits.fdivset5_unused = ufdivset5_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset5.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset5.u32, "FDIVSET5");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET5_fdivset5_unusedGet
//  Description : Set the value of the member FDIVSET5.fdivset5_unused
//  Input       : unsigned int ufdivset5_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_fdivset5_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset5.bits.fdivset5_unused;


}

//******************************************************************************
//  Function    : DATE_FDIVSET5_p_mod_dnSet
//  Description : Set the value of the member FDIVSET5.p_mod_dn
//  Input       : unsigned int up_mod_dn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_dnSet(unsigned int up_mod_dn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset5.bits.p_mod_dn = up_mod_dn;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset5.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset5.u32, "FDIVSET5");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET5_p_mod_dnGet
//  Description : Set the value of the member FDIVSET5.p_mod_dn
//  Input       : unsigned int up_mod_dn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_dnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset5.bits.p_mod_dn;


}

//******************************************************************************
//  Function    : DATE_FDIVSET5_p_mod_upSet
//  Description : Set the value of the member FDIVSET5.p_mod_up
//  Input       : unsigned int up_mod_up: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_upSet(unsigned int up_mod_up)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset5.bits.p_mod_up = up_mod_up;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset5.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivset5.u32, "FDIVSET5");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSET5_p_mod_upGet
//  Description : Set the value of the member FDIVSET5.p_mod_up
//  Input       : unsigned int up_mod_up: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_upGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset5.bits.p_mod_up;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_cntSet
//  Description : Set the value of the member FDIVSTAT0.stc_cnt
//  Input       : unsigned int ustc_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_cntSet(unsigned int ustc_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_cnt = ustc_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat0.u32, "FDIVSTAT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_cntGet
//  Description : Set the value of the member FDIVSTAT0.stc_cnt
//  Input       : unsigned int ustc_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_cnt;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_unSet
//  Description : Set the value of the member FDIVSTAT0.stc_un
//  Input       : unsigned int ustc_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_unSet(unsigned int ustc_un)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_un = ustc_un;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat0.u32, "FDIVSTAT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_unGet
//  Description : Set the value of the member FDIVSTAT0.stc_un
//  Input       : unsigned int ustc_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_unGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_un;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_ovSet
//  Description : Set the value of the member FDIVSTAT0.stc_ov
//  Input       : unsigned int ustc_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_ovSet(unsigned int ustc_ov)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_ov = ustc_ov;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat0.u32, "FDIVSTAT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_ovGet
//  Description : Set the value of the member FDIVSTAT0.stc_ov
//  Input       : unsigned int ustc_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_ovGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_ov;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_dirSet
//  Description : Set the value of the member FDIVSTAT0.stc_dir
//  Input       : unsigned int ustc_dir: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_dirSet(unsigned int ustc_dir)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_dir = ustc_dir;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat0.u32, "FDIVSTAT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_dirGet
//  Description : Set the value of the member FDIVSTAT0.stc_dir
//  Input       : unsigned int ustc_dir: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_dirGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_dir;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_runSet
//  Description : Set the value of the member FDIVSTAT0.stc_run
//  Input       : unsigned int ustc_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_runSet(unsigned int ustc_run)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_run = ustc_run;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat0.u32, "FDIVSTAT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT0_stc_runGet
//  Description : Set the value of the member FDIVSTAT0.stc_run
//  Input       : unsigned int ustc_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_runGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_run;


}



//******************************************************************************
//  Function    : DATE_FDIVSTAT1_i_fdiv_inGet
//  Description : Set the value of the member FDIVSTAT1.i_fdiv_in
//  Input       : unsigned int ui_fdiv_in: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT1_i_fdiv_inGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT1 o_fdivstat1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT1.u32);
    o_fdivstat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat1.bits.i_fdiv_in;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT2_div_outSet
//  Description : Set the value of the member FDIVSTAT2.div_out
//  Input       : unsigned int udiv_out: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT2_div_outSet(unsigned int udiv_out)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT2 o_fdivstat2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT2.u32);
    o_fdivstat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat2.bits.div_out = udiv_out;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat2.u32, "FDIVSTAT2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT2_div_outGet
//  Description : Set the value of the member FDIVSTAT2.div_out
//  Input       : unsigned int udiv_out: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT2_div_outGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT2 o_fdivstat2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT2.u32);
    o_fdivstat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat2.bits.div_out;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT3_div_sdmSet
//  Description : Set the value of the member FDIVSTAT3.div_sdm
//  Input       : unsigned int udiv_sdm: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT3_div_sdmSet(unsigned int udiv_sdm)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT3 o_fdivstat3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT3.u32);
    o_fdivstat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat3.bits.div_sdm = udiv_sdm;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat3.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat3.u32, "FDIVSTAT3");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT3_div_sdmGet
//  Description : Set the value of the member FDIVSTAT3.div_sdm
//  Input       : unsigned int udiv_sdm: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT3_div_sdmGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT3 o_fdivstat3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT3.u32);
    o_fdivstat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat3.bits.div_sdm;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_cntSet
//  Description : Set the value of the member FDIVSTAT4.stm_cnt
//  Input       : unsigned int ustm_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_cntSet(unsigned int ustm_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_cnt = ustm_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat4.u32, "FDIVSTAT4");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_cntGet
//  Description : Set the value of the member FDIVSTAT4.stm_cnt
//  Input       : unsigned int ustm_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_cnt;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_fdivstat4_unusedSet
//  Description : Set the value of the member FDIVSTAT4.fdivstat4_unused
//  Input       : unsigned int ufdivstat4_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_fdivstat4_unusedSet(unsigned int ufdivstat4_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.fdivstat4_unused = ufdivstat4_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat4.u32, "FDIVSTAT4");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_fdivstat4_unusedGet
//  Description : Set the value of the member FDIVSTAT4.fdivstat4_unused
//  Input       : unsigned int ufdivstat4_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_fdivstat4_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.fdivstat4_unused;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_unSet
//  Description : Set the value of the member FDIVSTAT4.stm_un
//  Input       : unsigned int ustm_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_unSet(unsigned int ustm_un)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_un = ustm_un;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat4.u32, "FDIVSTAT4");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_unGet
//  Description : Set the value of the member FDIVSTAT4.stm_un
//  Input       : unsigned int ustm_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_unGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_un;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_ovSet
//  Description : Set the value of the member FDIVSTAT4.stm_ov
//  Input       : unsigned int ustm_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_ovSet(unsigned int ustm_ov)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_ov = ustm_ov;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat4.u32, "FDIVSTAT4");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_ovGet
//  Description : Set the value of the member FDIVSTAT4.stm_ov
//  Input       : unsigned int ustm_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_ovGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_ov;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_phSet
//  Description : Set the value of the member FDIVSTAT4.stm_ph
//  Input       : unsigned int ustm_ph: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_phSet(unsigned int ustm_ph)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_ph = ustm_ph;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat4.u32, "FDIVSTAT4");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_phGet
//  Description : Set the value of the member FDIVSTAT4.stm_ph
//  Input       : unsigned int ustm_ph: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_phGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_ph;


}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_runSet
//  Description : Set the value of the member FDIVSTAT4.stm_run
//  Input       : unsigned int ustm_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_runSet(unsigned int ustm_run)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_run = ustm_run;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdivstat4.u32, "FDIVSTAT4");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDIVSTAT4_stm_runGet
//  Description : Set the value of the member FDIVSTAT4.stm_run
//  Input       : unsigned int ustm_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_runGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_run;


}


//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_vicGet
//  Description : Set the value of the member FDIVMANUAL.i_vic
//  Input       : unsigned int ui_vic: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_vicGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_vic;


}


//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_dc_selGet
//  Description : Set the value of the member FDIVMANUAL.i_dc_sel
//  Input       : unsigned int ui_dc_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_dc_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_dc_sel;


}



//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_ref_cnt_divGet
//  Description : Set the value of the member FDIVMANUAL.i_ref_cnt_div
//  Input       : unsigned int ui_ref_cnt_div: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_ref_cnt_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_ref_cnt_div;


}



//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_mdivGet
//  Description : Set the value of the member FDIVMANUAL.i_mdiv
//  Input       : unsigned int ui_mdiv: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_mdivGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_mdiv;


}



//******************************************************************************
//  Function    : DATE_FDIVMANUAL_fdivmanual_unusedGet
//  Description : Set the value of the member FDIVMANUAL.fdivmanual_unused
//  Input       : unsigned int ufdivmanual_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_fdivmanual_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.fdivmanual_unused;


}



//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_divnGet
//  Description : Set the value of the member FDIVMANUAL.i_divn
//  Input       : unsigned int ui_divn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_divnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_divn;


}



//******************************************************************************
//  Function    : DATE_FDIVMANUAL_i_manual_enGet
//  Description : Set the value of the member FDIVMANUAL.i_manual_en
//  Input       : unsigned int ui_manual_en: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_manual_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_manual_en;


}


//******************************************************************************
//  Function    : DATE_REFCLKSEL_p_pr_enc_valGet
//  Description : Set the value of the member REFCLKSEL.p_pr_enc_val
//  Input       : unsigned int up_pr_enc_val: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_p_pr_enc_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.p_pr_enc_val;


}



//******************************************************************************
//  Function    : DATE_REFCLKSEL_refclksel_unused_2Get
//  Description : Set the value of the member REFCLKSEL.refclksel_unused_2
//  Input       : unsigned int urefclksel_unused_2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_refclksel_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.refclksel_unused_2;


}



//******************************************************************************
//  Function    : DATE_REFCLKSEL_t2_pixelclkselGet
//  Description : Set the value of the member REFCLKSEL.t2_pixelclksel
//  Input       : unsigned int ut2_pixelclksel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_pixelclkselGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.t2_pixelclksel;


}


//******************************************************************************
//  Function    : DATE_REFCLKSEL_refclksel_unused_1Get
//  Description : Set the value of the member REFCLKSEL.refclksel_unused_1
//  Input       : unsigned int urefclksel_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_refclksel_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.refclksel_unused_1;


}



//******************************************************************************
//  Function    : DATE_REFCLKSEL_i_ref_clk_selGet
//  Description : Set the value of the member REFCLKSEL.i_ref_clk_sel
//  Input       : unsigned int ui_ref_clk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_i_ref_clk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.i_ref_clk_sel;


}



//******************************************************************************
//  Function    : DATE_REFCLKSEL_t2_refclksel2Get
//  Description : Set the value of the member REFCLKSEL.t2_refclksel2
//  Input       : unsigned int ut2_refclksel2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_refclksel2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.t2_refclksel2;


}


//******************************************************************************
//  Function    : DATE_REFCLKSEL_t2_refclkselGet
//  Description : Set the value of the member REFCLKSEL.t2_refclksel
//  Input       : unsigned int ut2_refclksel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_refclkselGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.t2_refclksel;


}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_fdpllparam_unusedSet
//  Description : Set the value of the member FDPLLPARAM.fdpllparam_unused
//  Input       : unsigned int ufdpllparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_fdpllparam_unusedSet(unsigned int ufdpllparam_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.fdpllparam_unused = ufdpllparam_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllparam.u32, "FDPLLPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_fdpllparam_unusedGet
//  Description : Set the value of the member FDPLLPARAM.fdpllparam_unused
//  Input       : unsigned int ufdpllparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_fdpllparam_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.fdpllparam_unused;


}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_pll_enableSet
//  Description : Set the value of the member FDPLLPARAM.pll_enable
//  Input       : unsigned int upll_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_enableSet(unsigned int upll_enable)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.pll_enable = upll_enable;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllparam.u32, "FDPLLPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_pll_enableGet
//  Description : Set the value of the member FDPLLPARAM.pll_enable
//  Input       : unsigned int upll_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_enableGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.pll_enable;


}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_pll_lock_cntSet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_cnt
//  Input       : unsigned int upll_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_cntSet(unsigned int upll_lock_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.pll_lock_cnt = upll_lock_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllparam.u32, "FDPLLPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_pll_lock_cntGet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_cnt
//  Input       : unsigned int upll_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.pll_lock_cnt;


}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_pll_lock_valSet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_val
//  Input       : unsigned int upll_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_valSet(unsigned int upll_lock_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.pll_lock_val = upll_lock_val;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllparam.u32, "FDPLLPARAM");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLPARAM_pll_lock_valGet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_val
//  Input       : unsigned int upll_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.pll_lock_val;


}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_pll_freq_extSet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_ext
//  Input       : unsigned int upll_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_extSet(unsigned int upll_freq_ext)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.pll_freq_ext = upll_freq_ext;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllfreq.u32, "FDPLLFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_pll_freq_extGet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_ext
//  Input       : unsigned int upll_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_extGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.pll_freq_ext;


}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_fdpllfreq_unused_2Set
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_2
//  Input       : unsigned int ufdpllfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_2Set(unsigned int ufdpllfreq_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.fdpllfreq_unused_2 = ufdpllfreq_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllfreq.u32, "FDPLLFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_fdpllfreq_unused_2Get
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_2
//  Input       : unsigned int ufdpllfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.fdpllfreq_unused_2;


}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_pll_freq_optSet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_opt
//  Input       : unsigned int upll_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_optSet(unsigned int upll_freq_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.pll_freq_opt = upll_freq_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllfreq.u32, "FDPLLFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_pll_freq_optGet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_opt
//  Input       : unsigned int upll_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.pll_freq_opt;


}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_fdpllfreq_unused_1Set
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_1
//  Input       : unsigned int ufdpllfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_1Set(unsigned int ufdpllfreq_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.fdpllfreq_unused_1 = ufdpllfreq_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllfreq.u32, "FDPLLFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_fdpllfreq_unused_1Get
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_1
//  Input       : unsigned int ufdpllfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.fdpllfreq_unused_1;


}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_pll_cnt_optSet
//  Description : Set the value of the member FDPLLFREQ.pll_cnt_opt
//  Input       : unsigned int upll_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_cnt_optSet(unsigned int upll_cnt_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.pll_cnt_opt = upll_cnt_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllfreq.u32, "FDPLLFREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLFREQ_pll_cnt_optGet
//  Description : Set the value of the member FDPLLFREQ.pll_cnt_opt
//  Input       : unsigned int upll_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_cnt_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.pll_cnt_opt;


}

//******************************************************************************
//  Function    : DATE_FDPLLRES_pll_cnt_outSet
//  Description : Set the value of the member FDPLLRES.pll_cnt_out
//  Input       : unsigned int upll_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_cnt_outSet(unsigned int upll_cnt_out)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllres.bits.pll_cnt_out = upll_cnt_out;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllres.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllres.u32, "FDPLLRES");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLRES_pll_cnt_outGet
//  Description : Set the value of the member FDPLLRES.pll_cnt_out
//  Input       : unsigned int upll_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_cnt_outGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllres.bits.pll_cnt_out;


}

//******************************************************************************
//  Function    : DATE_FDPLLRES_pll_det_statSet
//  Description : Set the value of the member FDPLLRES.pll_det_stat
//  Input       : unsigned int upll_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_det_statSet(unsigned int upll_det_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllres.bits.pll_det_stat = upll_det_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllres.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fdpllres.u32, "FDPLLRES");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FDPLLRES_pll_det_statGet
//  Description : Set the value of the member FDPLLRES.pll_det_stat
//  Input       : unsigned int upll_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_det_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllres.bits.pll_det_stat;


}



//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_lock_enGet
//  Description : Set the value of the member FCGSET.p_fcg_lock_en
//  Input       : unsigned int up_fcg_lock_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_lock_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgset.bits.p_fcg_lock_en;


}

//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_dither_enGet
//  Description : Set the value of the member FCGSET.p_fcg_dither_en
//  Input       : unsigned int up_fcg_dither_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_dither_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgset.bits.p_fcg_dither_en;


}

//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_enGet
//  Description : Set the value of the member FCGSET.p_fcg_en
//  Input       : unsigned int up_fcg_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgset.bits.p_fcg_en;


}


//******************************************************************************
//  Function    : DATE_FCGSET_p_fcg_dlf_enGet
//  Description : Set the value of the member FCGSET.p_fcg_dlf_en
//  Input       : unsigned int up_fcg_dlf_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSET_p_fcg_dlf_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSET o_fcgset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSET.u32);
    o_fcgset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgset.bits.p_fcg_dlf_en;


}



//******************************************************************************
//  Function    : DATE_FCGCNT_p_cnt1_targetGet
//  Description : Set the value of the member FCGCNT.p_cnt1_target
//  Input       : unsigned int up_cnt1_target: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGCNT_p_cnt1_targetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGCNT o_fcgcnt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGCNT.u32);
    o_fcgcnt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgcnt.bits.p_cnt1_target;


}

//******************************************************************************
//  Function    : DATE_FCGPARAM_p_kiGet
//  Description : Set the value of the member FCGPARAM.p_ki
//  Input       : unsigned int up_ki: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_kiGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgparam.bits.p_ki;


}

//******************************************************************************
//  Function    : DATE_FCGPARAM_p_lock_modeGet
//  Description : Set the value of the member FCGPARAM.p_lock_mode
//  Input       : unsigned int up_lock_mode: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_lock_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgparam.bits.p_lock_mode;


}

//******************************************************************************
//  Function    : DATE_FCGPARAM_p_lock_thGet
//  Description : Set the value of the member FCGPARAM.p_lock_th
//  Input       : unsigned int up_lock_th: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_lock_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgparam.bits.p_lock_th;


}



//******************************************************************************
//  Function    : DATE_FCGPARAM_p_lock_cntGet
//  Description : Set the value of the member FCGPARAM.p_lock_cnt
//  Input       : unsigned int up_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGPARAM_p_lock_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGPARAM o_fcgparam;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGPARAM.u32);
    o_fcgparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcgparam.bits.p_lock_cnt;


}

//******************************************************************************
//  Function    : DATE_FCGSTATE_o_dlf_unSet
//  Description : Set the value of the member FCGSTATE.o_dlf_un
//  Input       : unsigned int uo_dlf_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSTATE_o_dlf_unSet(unsigned int uo_dlf_un)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSTATE o_fcgstate;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSTATE.u32);
    o_fcgstate.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgstate.bits.o_dlf_un = uo_dlf_un;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgstate.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgstate.u32, "FCGSTATE");

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : DATE_FCGSTATE_o_dlf_ovSet
//  Description : Set the value of the member FCGSTATE.o_dlf_ov
//  Input       : unsigned int uo_dlf_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSTATE_o_dlf_ovSet(unsigned int uo_dlf_ov)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSTATE o_fcgstate;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSTATE.u32);
    o_fcgstate.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgstate.bits.o_dlf_ov = uo_dlf_ov;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgstate.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgstate.u32, "FCGSTATE");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FCGSTATE_o_dlf_lockSet
//  Description : Set the value of the member FCGSTATE.o_dlf_lock
//  Input       : unsigned int uo_dlf_lock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCGSTATE_o_dlf_lockSet(unsigned int uo_dlf_lock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCGSTATE o_fcgstate;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FCGSTATE.u32);
    o_fcgstate.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcgstate.bits.o_dlf_lock = uo_dlf_lock;
    HDMI21TXRegWrite(pu32RegAddr, o_fcgstate.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fcgstate.u32, "FCGSTATE");

    return HI_SUCCESS;
}



//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel3Set
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel3
//  Input       : unsigned int up_test_4to1_mux_sel3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel3Set(unsigned int up_test_4to1_mux_sel3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_test_4to1_mux_sel3 = up_test_4to1_mux_sel3;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txteloset.u32, "TXTELOSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel3Get
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel3
//  Input       : unsigned int up_test_4to1_mux_sel3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_test_4to1_mux_sel3;


}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel2Set
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel2
//  Input       : unsigned int up_test_4to1_mux_sel2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel2Set(unsigned int up_test_4to1_mux_sel2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_test_4to1_mux_sel2 = up_test_4to1_mux_sel2;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txteloset.u32, "TXTELOSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel2Get
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel2
//  Input       : unsigned int up_test_4to1_mux_sel2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_test_4to1_mux_sel2;


}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel1Set
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel1
//  Input       : unsigned int up_test_4to1_mux_sel1: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel1Set(unsigned int up_test_4to1_mux_sel1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_test_4to1_mux_sel1 = up_test_4to1_mux_sel1;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txteloset.u32, "TXTELOSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel1Get
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel1
//  Input       : unsigned int up_test_4to1_mux_sel1: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_test_4to1_mux_sel1;


}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel0Set
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel0
//  Input       : unsigned int up_test_4to1_mux_sel0: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel0Set(unsigned int up_test_4to1_mux_sel0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_test_4to1_mux_sel0 = up_test_4to1_mux_sel0;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txteloset.u32, "TXTELOSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_4to1_mux_sel0Get
//  Description : Set the value of the member TXTELOSET.p_test_4to1_mux_sel0
//  Input       : unsigned int up_test_4to1_mux_sel0: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_4to1_mux_sel0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_test_4to1_mux_sel0;


}



//******************************************************************************
//  Function    : DATE_TXTELOSET_p_ch_test_enGet
//  Description : Set the value of the member TXTELOSET.p_ch_test_en
//  Input       : unsigned int up_ch_test_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_test_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_ch_test_en;


}



//******************************************************************************
//  Function    : DATE_TXTELOSET_p_test_pat_typeGet
//  Description : Set the value of the member TXTELOSET.p_test_pat_type
//  Input       : unsigned int up_test_pat_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_pat_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_test_pat_type;


}



//******************************************************************************
//  Function    : DATE_TXTELOSET_p_prbs_clr_h21Get
//  Description : Set the value of the member TXTELOSET.p_prbs_clr_h21
//  Input       : unsigned int up_prbs_clr_h21: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_prbs_clr_h21Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_prbs_clr_h21;


}

//******************************************************************************
//  Function    : DATE_TXTELOSET_p_ch_en_h21Get
//  Description : Set the value of the member TXTELOSET.p_ch_en_h21
//  Input       : unsigned int up_ch_en_h21: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_en_h21Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_ch_en_h21;


}



//******************************************************************************
//  Function    : DATE_TXTELOSET_p_prbs_clr_h20Get
//  Description : Set the value of the member TXTELOSET.p_prbs_clr_h20
//  Input       : unsigned int up_prbs_clr_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_prbs_clr_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_prbs_clr_h20;


}



//******************************************************************************
//  Function    : DATE_TXTELOSET_p_ch_en_h20Get
//  Description : Set the value of the member TXTELOSET.p_ch_en_h20
//  Input       : unsigned int up_ch_en_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_en_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_ch_en_h20;


}

//******************************************************************************
//  Function    : DATE_TXTELOCONT0_p_test_pat_ch1_lSet
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch1_l
//  Input       : unsigned int up_test_pat_ch1_l: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch1_lSet(unsigned int up_test_pat_ch1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont0.bits.p_test_pat_ch1_l = up_test_pat_ch1_l;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txtelocont0.u32, "TXTELOCONT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOCONT0_p_test_pat_ch1_lGet
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch1_l
//  Input       : unsigned int up_test_pat_ch1_l: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch1_lGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont0.bits.p_test_pat_ch1_l;


}

//******************************************************************************
//  Function    : DATE_TXTELOCONT0_p_test_pat_ch0Set
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch0
//  Input       : unsigned int up_test_pat_ch0: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch0Set(unsigned int up_test_pat_ch0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont0.bits.p_test_pat_ch0 = up_test_pat_ch0;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txtelocont0.u32, "TXTELOCONT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOCONT0_p_test_pat_ch0Get
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch0
//  Input       : unsigned int up_test_pat_ch0: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont0.bits.p_test_pat_ch0;


}

//******************************************************************************
//  Function    : DATE_TXTELOCONT1_p_test_pat_ch2Set
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch2
//  Input       : unsigned int up_test_pat_ch2: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch2Set(unsigned int up_test_pat_ch2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont1.bits.p_test_pat_ch2 = up_test_pat_ch2;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txtelocont1.u32, "TXTELOCONT1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOCONT1_p_test_pat_ch2Get
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch2
//  Input       : unsigned int up_test_pat_ch2: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont1.bits.p_test_pat_ch2;


}

//******************************************************************************
//  Function    : DATE_TXTELOCONT1_p_test_pat_ch1_hSet
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch1_h
//  Input       : unsigned int up_test_pat_ch1_h: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch1_hSet(unsigned int up_test_pat_ch1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont1.bits.p_test_pat_ch1_h = up_test_pat_ch1_h;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txtelocont1.u32, "TXTELOCONT1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXTELOCONT1_p_test_pat_ch1_hGet
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch1_h
//  Input       : unsigned int up_test_pat_ch1_h: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch1_hGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont1.bits.p_test_pat_ch1_h;


}


//******************************************************************************
//  Function    : DATE_TXTELOCONT2_p_test_pat_ch3Get
//  Description : Set the value of the member TXTELOCONT2.p_test_pat_ch3
//  Input       : unsigned int up_test_pat_ch3: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT2_p_test_pat_ch3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT2 o_txtelocont2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXTELOCONT2.u32);
    o_txtelocont2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont2.bits.p_test_pat_ch3;


}



//******************************************************************************
//  Function    : DATE_TXFIFOSET0_txfifoset0_unusedGet
//  Description : Set the value of the member TXFIFOSET0.txfifoset0_unused
//  Input       : unsigned int utxfifoset0_unused: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_txfifoset0_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset0.bits.txfifoset0_unused;


}



//******************************************************************************
//  Function    : DATE_TXFIFOSET0_p_enable_h20Get
//  Description : Set the value of the member TXFIFOSET0.p_enable_h20
//  Input       : unsigned int up_enable_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_enable_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset0.bits.p_enable_h20;


}


//******************************************************************************
//  Function    : DATE_TXFIFOSET0_p_pr_en_h20Get
//  Description : Set the value of the member TXFIFOSET0.p_pr_en_h20
//  Input       : unsigned int up_pr_en_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_pr_en_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset0.bits.p_pr_en_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_ch_sel1_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel1_h20
//  Input       : unsigned int up_ch_sel1_h20: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel1_h20Set(unsigned int up_ch_sel1_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_ch_sel1_h20 = up_ch_sel1_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset1.u32, "TXFIFOSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_ch_sel1_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel1_h20
//  Input       : unsigned int up_ch_sel1_h20: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel1_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_ch_sel1_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_data_swap1_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_data_swap1_h20
//  Input       : unsigned int up_data_swap1_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap1_h20Set(unsigned int up_data_swap1_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_data_swap1_h20 = up_data_swap1_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset1.u32, "TXFIFOSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_data_swap1_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_data_swap1_h20
//  Input       : unsigned int up_data_swap1_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap1_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_data_swap1_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_pol_inv1_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv1_h20
//  Input       : unsigned int up_pol_inv1_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv1_h20Set(unsigned int up_pol_inv1_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_pol_inv1_h20 = up_pol_inv1_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset1.u32, "TXFIFOSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_pol_inv1_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv1_h20
//  Input       : unsigned int up_pol_inv1_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv1_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_pol_inv1_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_ch_sel0_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel0_h20
//  Input       : unsigned int up_ch_sel0_h20: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel0_h20Set(unsigned int up_ch_sel0_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_ch_sel0_h20 = up_ch_sel0_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset1.u32, "TXFIFOSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_ch_sel0_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel0_h20
//  Input       : unsigned int up_ch_sel0_h20: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel0_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_ch_sel0_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_data_swap0_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_data_swap0_h20
//  Input       : unsigned int up_data_swap0_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap0_h20Set(unsigned int up_data_swap0_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_data_swap0_h20 = up_data_swap0_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset1.u32, "TXFIFOSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_data_swap0_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_data_swap0_h20
//  Input       : unsigned int up_data_swap0_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap0_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_data_swap0_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_pol_inv0_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv0_h20
//  Input       : unsigned int up_pol_inv0_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv0_h20Set(unsigned int up_pol_inv0_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_pol_inv0_h20 = up_pol_inv0_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifoset1.u32, "TXFIFOSET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSET1_p_pol_inv0_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv0_h20
//  Input       : unsigned int up_pol_inv0_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv0_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_pol_inv0_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT0_txfifostat0_unusedSet
//  Description : Set the value of the member TXFIFOSTAT0.txfifostat0_unused
//  Input       : unsigned int utxfifostat0_unused: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_txfifostat0_unusedSet(unsigned int utxfifostat0_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat0.bits.txfifostat0_unused = utxfifostat0_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat0.u32, "TXFIFOSTAT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT0_txfifostat0_unusedGet
//  Description : Set the value of the member TXFIFOSTAT0.txfifostat0_unused
//  Input       : unsigned int utxfifostat0_unused: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_txfifostat0_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat0.bits.txfifostat0_unused;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT0_o_pr_fifo_state_h20Set
//  Description : Set the value of the member TXFIFOSTAT0.o_pr_fifo_state_h20
//  Input       : unsigned int uo_pr_fifo_state_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_o_pr_fifo_state_h20Set(unsigned int uo_pr_fifo_state_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat0.bits.o_pr_fifo_state_h20 = uo_pr_fifo_state_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat0.u32, "TXFIFOSTAT0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT0_o_pr_fifo_state_h20Get
//  Description : Set the value of the member TXFIFOSTAT0.o_pr_fifo_state_h20
//  Input       : unsigned int uo_pr_fifo_state_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_o_pr_fifo_state_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat0.bits.o_pr_fifo_state_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT1_txfifostat1_unused_1Set
//  Description : Set the value of the member TXFIFOSTAT1.txfifostat1_unused_1
//  Input       : unsigned int utxfifostat1_unused_1: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_txfifostat1_unused_1Set(unsigned int utxfifostat1_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat1.bits.txfifostat1_unused_1 = utxfifostat1_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat1.u32, "TXFIFOSTAT1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT1_txfifostat1_unused_1Get
//  Description : Set the value of the member TXFIFOSTAT1.txfifostat1_unused_1
//  Input       : unsigned int utxfifostat1_unused_1: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_txfifostat1_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat1.bits.txfifostat1_unused_1;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT1_txfifostat1_unused_0Set
//  Description : Set the value of the member TXFIFOSTAT1.txfifostat1_unused_0
//  Input       : unsigned int utxfifostat1_unused_0: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_txfifostat1_unused_0Set(unsigned int utxfifostat1_unused_0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat1.bits.txfifostat1_unused_0 = utxfifostat1_unused_0;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat1.u32, "TXFIFOSTAT1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT1_txfifostat1_unused_0Get
//  Description : Set the value of the member TXFIFOSTAT1.txfifostat1_unused_0
//  Input       : unsigned int utxfifostat1_unused_0: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_txfifostat1_unused_0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat1.bits.txfifostat1_unused_0;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT2_txfifostat2_unusedSet
//  Description : Set the value of the member TXFIFOSTAT2.txfifostat2_unused
//  Input       : unsigned int utxfifostat2_unused: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_txfifostat2_unusedSet(unsigned int utxfifostat2_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat2.bits.txfifostat2_unused = utxfifostat2_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat2.u32, "TXFIFOSTAT2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT2_txfifostat2_unusedGet
//  Description : Set the value of the member TXFIFOSTAT2.txfifostat2_unused
//  Input       : unsigned int utxfifostat2_unused: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_txfifostat2_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat2.bits.txfifostat2_unused;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT2_o_tx_fifo_state_h20Set
//  Description : Set the value of the member TXFIFOSTAT2.o_tx_fifo_state_h20
//  Input       : unsigned int uo_tx_fifo_state_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_o_tx_fifo_state_h20Set(unsigned int uo_tx_fifo_state_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat2.bits.o_tx_fifo_state_h20 = uo_tx_fifo_state_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat2.u32, "TXFIFOSTAT2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT2_o_tx_fifo_state_h20Get
//  Description : Set the value of the member TXFIFOSTAT2.o_tx_fifo_state_h20
//  Input       : unsigned int uo_tx_fifo_state_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_o_tx_fifo_state_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat2.bits.o_tx_fifo_state_h20;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT3_txfifostat3_unused_1Set
//  Description : Set the value of the member TXFIFOSTAT3.txfifostat3_unused_1
//  Input       : unsigned int utxfifostat3_unused_1: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_txfifostat3_unused_1Set(unsigned int utxfifostat3_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat3.bits.txfifostat3_unused_1 = utxfifostat3_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat3.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat3.u32, "TXFIFOSTAT3");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT3_txfifostat3_unused_1Get
//  Description : Set the value of the member TXFIFOSTAT3.txfifostat3_unused_1
//  Input       : unsigned int utxfifostat3_unused_1: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_txfifostat3_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat3.bits.txfifostat3_unused_1;


}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT3_txfifostat3_unused_0Set
//  Description : Set the value of the member TXFIFOSTAT3.txfifostat3_unused_0
//  Input       : unsigned int utxfifostat3_unused_0: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_txfifostat3_unused_0Set(unsigned int utxfifostat3_unused_0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat3.bits.txfifostat3_unused_0 = utxfifostat3_unused_0;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat3.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_txfifostat3.u32, "TXFIFOSTAT3");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_TXFIFOSTAT3_txfifostat3_unused_0Get
//  Description : Set the value of the member TXFIFOSTAT3.txfifostat3_unused_0
//  Input       : unsigned int utxfifostat3_unused_0: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_txfifostat3_unused_0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat3.bits.txfifostat3_unused_0;


}



//******************************************************************************
//  Function    : DATE_DATACLKINV_p_dataclkinvGet
//  Description : Set the value of the member DATACLKINV.p_dataclkinv
//  Input       : unsigned int up_dataclkinv: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DATACLKINV_p_dataclkinvGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DATACLKINV o_dataclkinv;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->DATACLKINV.u32);
    o_dataclkinv.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_dataclkinv.bits.p_dataclkinv;


}

//******************************************************************************
//  Function    : DATE_HDMI_MODE_reg_hdmi_mode_enGet
//  Description : Set the value of the member HDMI_MODE.reg_hdmi_mode_en
//  Input       : unsigned int ureg_hdmi_mode_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDMI_MODE_reg_hdmi_mode_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HDMI_MODE o_hdmi_mode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HDMI_MODE.u32);
    o_hdmi_mode.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hdmi_mode.bits.reg_hdmi_mode_en;
}

//******************************************************************************
//  Function    : DATE_CLK_DATA_1_reg_sw_clk_enSet
//  Description : Set the value of the member CLK_DATA_1.reg_sw_clk_en
//  Input       : unsigned int ureg_sw_clk_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_1_reg_sw_clk_enSet(unsigned int ureg_sw_clk_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_1 o_clk_data_1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_1.u32);
    o_clk_data_1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clk_data_1.bits.reg_sw_clk_en = ureg_sw_clk_en;
    HDMI21TXRegWrite(pu32RegAddr, o_clk_data_1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clk_data_1.u32, "CLK_DATA_1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLK_DATA_1_reg_sw_clk_enGet
//  Description : Set the value of the member CLK_DATA_1.reg_sw_clk_en
//  Input       : unsigned int ureg_sw_clk_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_1_reg_sw_clk_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_1 o_clk_data_1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_1.u32);
    o_clk_data_1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clk_data_1.bits.reg_sw_clk_en;


}

//******************************************************************************
//  Function    : DATE_CLK_DATA_1_reg_clk_data_phase1Set
//  Description : Set the value of the member CLK_DATA_1.reg_clk_data_phase1
//  Input       : unsigned int ureg_clk_data_phase1: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_1_reg_clk_data_phase1Set(unsigned int ureg_clk_data_phase1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_1 o_clk_data_1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_1.u32);
    o_clk_data_1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clk_data_1.bits.reg_clk_data_phase1 = ureg_clk_data_phase1;
    HDMI21TXRegWrite(pu32RegAddr, o_clk_data_1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clk_data_1.u32, "CLK_DATA_1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLK_DATA_1_reg_clk_data_phase1Get
//  Description : Set the value of the member CLK_DATA_1.reg_clk_data_phase1
//  Input       : unsigned int ureg_clk_data_phase1: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_1_reg_clk_data_phase1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_1 o_clk_data_1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_1.u32);
    o_clk_data_1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clk_data_1.bits.reg_clk_data_phase1;


}

//******************************************************************************
//  Function    : DATE_CLK_DATA_1_reg_clk_data_phase0Set
//  Description : Set the value of the member CLK_DATA_1.reg_clk_data_phase0
//  Input       : unsigned int ureg_clk_data_phase0: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_1_reg_clk_data_phase0Set(unsigned int ureg_clk_data_phase0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_1 o_clk_data_1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_1.u32);
    o_clk_data_1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clk_data_1.bits.reg_clk_data_phase0 = ureg_clk_data_phase0;
    HDMI21TXRegWrite(pu32RegAddr, o_clk_data_1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clk_data_1.u32, "CLK_DATA_1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLK_DATA_1_reg_clk_data_phase0Get
//  Description : Set the value of the member CLK_DATA_1.reg_clk_data_phase0
//  Input       : unsigned int ureg_clk_data_phase0: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_1_reg_clk_data_phase0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_1 o_clk_data_1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_1.u32);
    o_clk_data_1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clk_data_1.bits.reg_clk_data_phase0;


}

//******************************************************************************
//  Function    : DATE_CLK_DATA_2_reg_clk_data_phase3Set
//  Description : Set the value of the member CLK_DATA_2.reg_clk_data_phase3
//  Input       : unsigned int ureg_clk_data_phase3: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_2_reg_clk_data_phase3Set(unsigned int ureg_clk_data_phase3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_2 o_clk_data_2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_2.u32);
    o_clk_data_2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clk_data_2.bits.reg_clk_data_phase3 = ureg_clk_data_phase3;
    HDMI21TXRegWrite(pu32RegAddr, o_clk_data_2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clk_data_2.u32, "CLK_DATA_2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLK_DATA_2_reg_clk_data_phase3Get
//  Description : Set the value of the member CLK_DATA_2.reg_clk_data_phase3
//  Input       : unsigned int ureg_clk_data_phase3: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_2_reg_clk_data_phase3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_2 o_clk_data_2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_2.u32);
    o_clk_data_2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clk_data_2.bits.reg_clk_data_phase3;


}

//******************************************************************************
//  Function    : DATE_CLK_DATA_2_reg_clk_data_phase2Set
//  Description : Set the value of the member CLK_DATA_2.reg_clk_data_phase2
//  Input       : unsigned int ureg_clk_data_phase2: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_2_reg_clk_data_phase2Set(unsigned int ureg_clk_data_phase2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_2 o_clk_data_2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_2.u32);
    o_clk_data_2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clk_data_2.bits.reg_clk_data_phase2 = ureg_clk_data_phase2;
    HDMI21TXRegWrite(pu32RegAddr, o_clk_data_2.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_clk_data_2.u32, "CLK_DATA_2");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CLK_DATA_2_reg_clk_data_phase2Get
//  Description : Set the value of the member CLK_DATA_2.reg_clk_data_phase2
//  Input       : unsigned int ureg_clk_data_phase2: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLK_DATA_2_reg_clk_data_phase2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLK_DATA_2 o_clk_data_2;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLK_DATA_2.u32);
    o_clk_data_2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clk_data_2.bits.reg_clk_data_phase2;


}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_status_wrstSet
//  Description : Set the value of the member CFG18TO20.reg_status_wrst
//  Input       : unsigned int ureg_status_wrst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_status_wrstSet(unsigned int ureg_status_wrst)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cfg18to20.bits.reg_status_wrst = ureg_status_wrst;
    HDMI21TXRegWrite(pu32RegAddr, o_cfg18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_cfg18to20.u32, "CFG18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_status_wrstGet
//  Description : Set the value of the member CFG18TO20.reg_status_wrst
//  Input       : unsigned int ureg_status_wrst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_status_wrstGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_cfg18to20.bits.reg_status_wrst;


}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_status_rrstSet
//  Description : Set the value of the member CFG18TO20.reg_status_rrst
//  Input       : unsigned int ureg_status_rrst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_status_rrstSet(unsigned int ureg_status_rrst)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cfg18to20.bits.reg_status_rrst = ureg_status_rrst;
    HDMI21TXRegWrite(pu32RegAddr, o_cfg18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_cfg18to20.u32, "CFG18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_status_rrstGet
//  Description : Set the value of the member CFG18TO20.reg_status_rrst
//  Input       : unsigned int ureg_status_rrst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_status_rrstGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_cfg18to20.bits.reg_status_rrst;


}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_rd_bypassSet
//  Description : Set the value of the member CFG18TO20.reg_rd_bypass
//  Input       : unsigned int ureg_rd_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_rd_bypassSet(unsigned int ureg_rd_bypass)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cfg18to20.bits.reg_rd_bypass = ureg_rd_bypass;
    HDMI21TXRegWrite(pu32RegAddr, o_cfg18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_cfg18to20.u32, "CFG18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_rd_bypassGet
//  Description : Set the value of the member CFG18TO20.reg_rd_bypass
//  Input       : unsigned int ureg_rd_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_rd_bypassGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_cfg18to20.bits.reg_rd_bypass;


}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_18to20_fifo_wr_rstSet
//  Description : Set the value of the member CFG18TO20.reg_18to20_fifo_wr_rst
//  Input       : unsigned int ureg_18to20_fifo_wr_rst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_18to20_fifo_wr_rstSet(unsigned int ureg_18to20_fifo_wr_rst)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cfg18to20.bits.reg_18to20_fifo_wr_rst = ureg_18to20_fifo_wr_rst;
    HDMI21TXRegWrite(pu32RegAddr, o_cfg18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_cfg18to20.u32, "CFG18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_18to20_fifo_wr_rstGet
//  Description : Set the value of the member CFG18TO20.reg_18to20_fifo_wr_rst
//  Input       : unsigned int ureg_18to20_fifo_wr_rst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_18to20_fifo_wr_rstGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_cfg18to20.bits.reg_18to20_fifo_wr_rst;


}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_18to20_fifo_rd_rstSet
//  Description : Set the value of the member CFG18TO20.reg_18to20_fifo_rd_rst
//  Input       : unsigned int ureg_18to20_fifo_rd_rst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_18to20_fifo_rd_rstSet(unsigned int ureg_18to20_fifo_rd_rst)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_cfg18to20.bits.reg_18to20_fifo_rd_rst = ureg_18to20_fifo_rd_rst;
    HDMI21TXRegWrite(pu32RegAddr, o_cfg18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_cfg18to20.u32, "CFG18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CFG18TO20_reg_18to20_fifo_rd_rstGet
//  Description : Set the value of the member CFG18TO20.reg_18to20_fifo_rd_rst
//  Input       : unsigned int ureg_18to20_fifo_rd_rst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CFG18TO20_reg_18to20_fifo_rd_rstGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CFG18TO20 o_cfg18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CFG18TO20.u32);
    o_cfg18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_cfg18to20.bits.reg_18to20_fifo_rd_rst;


}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_afull_statusSet
//  Description : Set the value of the member FIFOSTAT18TO20.afull_status
//  Input       : unsigned int uafull_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_afull_statusSet(unsigned int uafull_status)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fifostat18to20.bits.afull_status = uafull_status;
    HDMI21TXRegWrite(pu32RegAddr, o_fifostat18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fifostat18to20.u32, "FIFOSTAT18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_afull_statusGet
//  Description : Set the value of the member FIFOSTAT18TO20.afull_status
//  Input       : unsigned int uafull_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_afull_statusGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fifostat18to20.bits.afull_status;


}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_full_statusSet
//  Description : Set the value of the member FIFOSTAT18TO20.full_status
//  Input       : unsigned int ufull_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_full_statusSet(unsigned int ufull_status)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fifostat18to20.bits.full_status = ufull_status;
    HDMI21TXRegWrite(pu32RegAddr, o_fifostat18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fifostat18to20.u32, "FIFOSTAT18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_full_statusGet
//  Description : Set the value of the member FIFOSTAT18TO20.full_status
//  Input       : unsigned int ufull_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_full_statusGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fifostat18to20.bits.full_status;


}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_aempty_statusSet
//  Description : Set the value of the member FIFOSTAT18TO20.aempty_status
//  Input       : unsigned int uaempty_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_aempty_statusSet(unsigned int uaempty_status)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fifostat18to20.bits.aempty_status = uaempty_status;
    HDMI21TXRegWrite(pu32RegAddr, o_fifostat18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fifostat18to20.u32, "FIFOSTAT18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_aempty_statusGet
//  Description : Set the value of the member FIFOSTAT18TO20.aempty_status
//  Input       : unsigned int uaempty_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_aempty_statusGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fifostat18to20.bits.aempty_status;


}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_empty_statusSet
//  Description : Set the value of the member FIFOSTAT18TO20.empty_status
//  Input       : unsigned int uempty_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_empty_statusSet(unsigned int uempty_status)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fifostat18to20.bits.empty_status = uempty_status;
    HDMI21TXRegWrite(pu32RegAddr, o_fifostat18to20.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_fifostat18to20.u32, "FIFOSTAT18TO20");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_FIFOSTAT18TO20_empty_statusGet
//  Description : Set the value of the member FIFOSTAT18TO20.empty_status
//  Input       : unsigned int uempty_status: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FIFOSTAT18TO20_empty_statusGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FIFOSTAT18TO20 o_fifostat18to20;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->FIFOSTAT18TO20.u32);
    o_fifostat18to20.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fifostat18to20.bits.empty_status;


}



//******************************************************************************
//  Function    : DATE_HSSET_p_hssetGet
//  Description : Set the value of the member HSSET.p_hsset
//  Input       : unsigned int up_hsset: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSSET_p_hssetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSSET o_hsset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HSSET.u32);
    o_hsset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hsset.bits.p_hsset;


}

//******************************************************************************
//  Function    : DATE_HSRXSENSE_w_hsrxsenseSet
//  Description : Set the value of the member HSRXSENSE.w_hsrxsense
//  Input       : unsigned int uw_hsrxsense: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSRXSENSE_w_hsrxsenseSet(unsigned int uw_hsrxsense)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSRXSENSE o_hsrxsense;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HSRXSENSE.u32);
    o_hsrxsense.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hsrxsense.bits.w_hsrxsense = uw_hsrxsense;
    HDMI21TXRegWrite(pu32RegAddr, o_hsrxsense.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hsrxsense.u32, "HSRXSENSE");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HSRXSENSE_w_hsrxsenseGet
//  Description : Set the value of the member HSRXSENSE.w_hsrxsense
//  Input       : unsigned int uw_hsrxsense: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSRXSENSE_w_hsrxsenseGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSRXSENSE o_hsrxsense;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HSRXSENSE.u32);
    o_hsrxsense.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hsrxsense.bits.w_hsrxsense;


}

//******************************************************************************
//  Function    : DATE_HSFIFOSTAT_o_fifo_state_hsSet
//  Description : Set the value of the member HSFIFOSTAT.o_fifo_state_hs
//  Input       : unsigned int uo_fifo_state_hs: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSFIFOSTAT_o_fifo_state_hsSet(unsigned int uo_fifo_state_hs)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSFIFOSTAT o_hsfifostat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HSFIFOSTAT.u32);
    o_hsfifostat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hsfifostat.bits.o_fifo_state_hs = uo_fifo_state_hs;
    HDMI21TXRegWrite(pu32RegAddr, o_hsfifostat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hsfifostat.u32, "HSFIFOSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HSFIFOSTAT_o_fifo_state_hsGet
//  Description : Set the value of the member HSFIFOSTAT.o_fifo_state_hs
//  Input       : unsigned int uo_fifo_state_hs: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSFIFOSTAT_o_fifo_state_hsGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSFIFOSTAT o_hsfifostat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HSFIFOSTAT.u32);
    o_hsfifostat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hsfifostat.bits.o_fifo_state_hs;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_ct_fcon_intrSet
//  Description : Set the value of the member INTRSTAT.ct_fcon_intr
//  Input       : unsigned int uct_fcon_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_ct_fcon_intrSet(unsigned int uct_fcon_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.ct_fcon_intr = uct_fcon_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_ct_fcon_intrGet
//  Description : Set the value of the member INTRSTAT.ct_fcon_intr
//  Input       : unsigned int uct_fcon_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_ct_fcon_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.ct_fcon_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_lkvdetlow_intrSet
//  Description : Set the value of the member INTRSTAT.lkvdetlow_intr
//  Input       : unsigned int ulkvdetlow_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdetlow_intrSet(unsigned int ulkvdetlow_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.lkvdetlow_intr = ulkvdetlow_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_lkvdetlow_intrGet
//  Description : Set the value of the member INTRSTAT.lkvdetlow_intr
//  Input       : unsigned int ulkvdetlow_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdetlow_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.lkvdetlow_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_lkvdethigh_intrSet
//  Description : Set the value of the member INTRSTAT.lkvdethigh_intr
//  Input       : unsigned int ulkvdethigh_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdethigh_intrSet(unsigned int ulkvdethigh_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.lkvdethigh_intr = ulkvdethigh_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_lkvdethigh_intrGet
//  Description : Set the value of the member INTRSTAT.lkvdethigh_intr
//  Input       : unsigned int ulkvdethigh_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdethigh_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.lkvdethigh_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_trinsmitter_fifo_full_intrSet
//  Description : Set the value of the member INTRSTAT.trinsmitter_fifo_full_intr
//  Input       : unsigned int utrinsmitter_fifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_trinsmitter_fifo_full_intrSet(unsigned int utrinsmitter_fifo_full_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.trinsmitter_fifo_full_intr = utrinsmitter_fifo_full_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_trinsmitter_fifo_full_intrGet
//  Description : Set the value of the member INTRSTAT.trinsmitter_fifo_full_intr
//  Input       : unsigned int utrinsmitter_fifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_trinsmitter_fifo_full_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.trinsmitter_fifo_full_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_trinsmitter_fifo_empty_intrSet
//  Description : Set the value of the member INTRSTAT.trinsmitter_fifo_empty_intr
//  Input       : unsigned int utrinsmitter_fifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_trinsmitter_fifo_empty_intrSet(unsigned int utrinsmitter_fifo_empty_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.trinsmitter_fifo_empty_intr = utrinsmitter_fifo_empty_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_trinsmitter_fifo_empty_intrGet
//  Description : Set the value of the member INTRSTAT.trinsmitter_fifo_empty_intr
//  Input       : unsigned int utrinsmitter_fifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_trinsmitter_fifo_empty_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.trinsmitter_fifo_empty_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_up_sample_fifo_full_intrSet
//  Description : Set the value of the member INTRSTAT.up_sample_fifo_full_intr
//  Input       : unsigned int uup_sample_fifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_up_sample_fifo_full_intrSet(unsigned int uup_sample_fifo_full_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.up_sample_fifo_full_intr = uup_sample_fifo_full_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_up_sample_fifo_full_intrGet
//  Description : Set the value of the member INTRSTAT.up_sample_fifo_full_intr
//  Input       : unsigned int uup_sample_fifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_up_sample_fifo_full_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.up_sample_fifo_full_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_up_sample_fifo_empty_intrSet
//  Description : Set the value of the member INTRSTAT.up_sample_fifo_empty_intr
//  Input       : unsigned int uup_sample_fifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_up_sample_fifo_empty_intrSet(unsigned int uup_sample_fifo_empty_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.up_sample_fifo_empty_intr = uup_sample_fifo_empty_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_up_sample_fifo_empty_intrGet
//  Description : Set the value of the member INTRSTAT.up_sample_fifo_empty_intr
//  Input       : unsigned int uup_sample_fifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_up_sample_fifo_empty_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.up_sample_fifo_empty_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_hs_fifo_full_intrSet
//  Description : Set the value of the member INTRSTAT.hs_fifo_full_intr
//  Input       : unsigned int uhs_fifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_hs_fifo_full_intrSet(unsigned int uhs_fifo_full_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.hs_fifo_full_intr = uhs_fifo_full_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_hs_fifo_full_intrGet
//  Description : Set the value of the member INTRSTAT.hs_fifo_full_intr
//  Input       : unsigned int uhs_fifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_hs_fifo_full_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.hs_fifo_full_intr;


}

//******************************************************************************
//  Function    : DATE_INTRSTAT_hs_fifo_empty_intrSet
//  Description : Set the value of the member INTRSTAT.hs_fifo_empty_intr
//  Input       : unsigned int uhs_fifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_hs_fifo_empty_intrSet(unsigned int uhs_fifo_empty_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.hs_fifo_empty_intr = uhs_fifo_empty_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrstat.u32, "INTRSTAT");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSTAT_hs_fifo_empty_intrGet
//  Description : Set the value of the member INTRSTAT.hs_fifo_empty_intr
//  Input       : unsigned int uhs_fifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_hs_fifo_empty_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.hs_fifo_empty_intr;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_ct_fcon_intr_maskSet
//  Description : Set the value of the member INTRMASK.ct_fcon_intr_mask
//  Input       : unsigned int uct_fcon_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_ct_fcon_intr_maskSet(unsigned int uct_fcon_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.ct_fcon_intr_mask = uct_fcon_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_ct_fcon_intr_maskGet
//  Description : Set the value of the member INTRMASK.ct_fcon_intr_mask
//  Input       : unsigned int uct_fcon_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_ct_fcon_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.ct_fcon_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_lkvdetlow_intr_maskSet
//  Description : Set the value of the member INTRMASK.lkvdetlow_intr_mask
//  Input       : unsigned int ulkvdetlow_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdetlow_intr_maskSet(unsigned int ulkvdetlow_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.lkvdetlow_intr_mask = ulkvdetlow_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_lkvdetlow_intr_maskGet
//  Description : Set the value of the member INTRMASK.lkvdetlow_intr_mask
//  Input       : unsigned int ulkvdetlow_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdetlow_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.lkvdetlow_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_lkvdethigh_intr_maskSet
//  Description : Set the value of the member INTRMASK.lkvdethigh_intr_mask
//  Input       : unsigned int ulkvdethigh_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdethigh_intr_maskSet(unsigned int ulkvdethigh_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.lkvdethigh_intr_mask = ulkvdethigh_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_lkvdethigh_intr_maskGet
//  Description : Set the value of the member INTRMASK.lkvdethigh_intr_mask
//  Input       : unsigned int ulkvdethigh_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdethigh_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.lkvdethigh_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_trinsmitter_fifo_full_intr_maskSet
//  Description : Set the value of the member INTRMASK.trinsmitter_fifo_full_intr_mask
//  Input       : unsigned int utrinsmitter_fifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_trinsmitter_fifo_full_intr_maskSet(unsigned int utrinsmitter_fifo_full_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.trinsmitter_fifo_full_intr_mask = utrinsmitter_fifo_full_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_trinsmitter_fifo_full_intr_maskGet
//  Description : Set the value of the member INTRMASK.trinsmitter_fifo_full_intr_mask
//  Input       : unsigned int utrinsmitter_fifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_trinsmitter_fifo_full_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.trinsmitter_fifo_full_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_trinsmitter_fifo_empty_intr_maskSet
//  Description : Set the value of the member INTRMASK.trinsmitter_fifo_empty_intr_mask
//  Input       : unsigned int utrinsmitter_fifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_trinsmitter_fifo_empty_intr_maskSet(unsigned int utrinsmitter_fifo_empty_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.trinsmitter_fifo_empty_intr_mask = utrinsmitter_fifo_empty_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_trinsmitter_fifo_empty_intr_maskGet
//  Description : Set the value of the member INTRMASK.trinsmitter_fifo_empty_intr_mask
//  Input       : unsigned int utrinsmitter_fifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_trinsmitter_fifo_empty_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.trinsmitter_fifo_empty_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_up_sample_fifo_full_intr_maskSet
//  Description : Set the value of the member INTRMASK.up_sample_fifo_full_intr_mask
//  Input       : unsigned int uup_sample_fifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_up_sample_fifo_full_intr_maskSet(unsigned int uup_sample_fifo_full_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.up_sample_fifo_full_intr_mask = uup_sample_fifo_full_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_up_sample_fifo_full_intr_maskGet
//  Description : Set the value of the member INTRMASK.up_sample_fifo_full_intr_mask
//  Input       : unsigned int uup_sample_fifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_up_sample_fifo_full_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.up_sample_fifo_full_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_up_sample_fifo_empty_intr_maskSet
//  Description : Set the value of the member INTRMASK.up_sample_fifo_empty_intr_mask
//  Input       : unsigned int uup_sample_fifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_up_sample_fifo_empty_intr_maskSet(unsigned int uup_sample_fifo_empty_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.up_sample_fifo_empty_intr_mask = uup_sample_fifo_empty_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_up_sample_fifo_empty_intr_maskGet
//  Description : Set the value of the member INTRMASK.up_sample_fifo_empty_intr_mask
//  Input       : unsigned int uup_sample_fifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_up_sample_fifo_empty_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.up_sample_fifo_empty_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_hs_fifo_full_intr_maskSet
//  Description : Set the value of the member INTRMASK.hs_fifo_full_intr_mask
//  Input       : unsigned int uhs_fifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_hs_fifo_full_intr_maskSet(unsigned int uhs_fifo_full_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.hs_fifo_full_intr_mask = uhs_fifo_full_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_hs_fifo_full_intr_maskGet
//  Description : Set the value of the member INTRMASK.hs_fifo_full_intr_mask
//  Input       : unsigned int uhs_fifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_hs_fifo_full_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.hs_fifo_full_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRMASK_hs_fifo_empty_intr_maskSet
//  Description : Set the value of the member INTRMASK.hs_fifo_empty_intr_mask
//  Input       : unsigned int uhs_fifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_hs_fifo_empty_intr_maskSet(unsigned int uhs_fifo_empty_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.hs_fifo_empty_intr_mask = uhs_fifo_empty_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrmask.u32, "INTRMASK");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRMASK_hs_fifo_empty_intr_maskGet
//  Description : Set the value of the member INTRMASK.hs_fifo_empty_intr_mask
//  Input       : unsigned int uhs_fifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_hs_fifo_empty_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.hs_fifo_empty_intr_mask;


}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdetlow_intr_enSet
//  Description : Set the value of the member INTRSET.lkvdetlow_intr_en
//  Input       : unsigned int ulkvdetlow_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdetlow_intr_enSet(unsigned int ulkvdetlow_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.lkvdetlow_intr_en = ulkvdetlow_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdetlow_intr_enGet
//  Description : Set the value of the member INTRSET.lkvdetlow_intr_en
//  Input       : unsigned int ulkvdetlow_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdetlow_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.lkvdetlow_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdetlow_triger_typeSet
//  Description : Set the value of the member INTRSET.lkvdetlow_triger_type
//  Input       : unsigned int ulkvdetlow_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdetlow_triger_typeSet(unsigned int ulkvdetlow_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.lkvdetlow_triger_type = ulkvdetlow_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdetlow_triger_typeGet
//  Description : Set the value of the member INTRSET.lkvdetlow_triger_type
//  Input       : unsigned int ulkvdetlow_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdetlow_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.lkvdetlow_triger_type;


}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdethigh_intr_enSet
//  Description : Set the value of the member INTRSET.lkvdethigh_intr_en
//  Input       : unsigned int ulkvdethigh_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdethigh_intr_enSet(unsigned int ulkvdethigh_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.lkvdethigh_intr_en = ulkvdethigh_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdethigh_intr_enGet
//  Description : Set the value of the member INTRSET.lkvdethigh_intr_en
//  Input       : unsigned int ulkvdethigh_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdethigh_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.lkvdethigh_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdethigh_triger_typeSet
//  Description : Set the value of the member INTRSET.lkvdethigh_triger_type
//  Input       : unsigned int ulkvdethigh_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdethigh_triger_typeSet(unsigned int ulkvdethigh_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.lkvdethigh_triger_type = ulkvdethigh_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_lkvdethigh_triger_typeGet
//  Description : Set the value of the member INTRSET.lkvdethigh_triger_type
//  Input       : unsigned int ulkvdethigh_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdethigh_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.lkvdethigh_triger_type;


}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_full_intr_enSet
//  Description : Set the value of the member INTRSET.transmitter_fifo_full_intr_en
//  Input       : unsigned int utransmitter_fifo_full_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_full_intr_enSet(unsigned int utransmitter_fifo_full_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.transmitter_fifo_full_intr_en = utransmitter_fifo_full_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_full_intr_enGet
//  Description : Set the value of the member INTRSET.transmitter_fifo_full_intr_en
//  Input       : unsigned int utransmitter_fifo_full_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_full_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.transmitter_fifo_full_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_full_triger_typeSet
//  Description : Set the value of the member INTRSET.transmitter_fifo_full_triger_type
//  Input       : unsigned int utransmitter_fifo_full_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_full_triger_typeSet(unsigned int utransmitter_fifo_full_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.transmitter_fifo_full_triger_type = utransmitter_fifo_full_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_full_triger_typeGet
//  Description : Set the value of the member INTRSET.transmitter_fifo_full_triger_type
//  Input       : unsigned int utransmitter_fifo_full_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_full_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.transmitter_fifo_full_triger_type;


}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_empty_intr_enSet
//  Description : Set the value of the member INTRSET.transmitter_fifo_empty_intr_en
//  Input       : unsigned int utransmitter_fifo_empty_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_empty_intr_enSet(unsigned int utransmitter_fifo_empty_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.transmitter_fifo_empty_intr_en = utransmitter_fifo_empty_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_empty_intr_enGet
//  Description : Set the value of the member INTRSET.transmitter_fifo_empty_intr_en
//  Input       : unsigned int utransmitter_fifo_empty_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_empty_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.transmitter_fifo_empty_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_empty_triger_typeSet
//  Description : Set the value of the member INTRSET.transmitter_fifo_empty_triger_type
//  Input       : unsigned int utransmitter_fifo_empty_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_empty_triger_typeSet(unsigned int utransmitter_fifo_empty_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.transmitter_fifo_empty_triger_type = utransmitter_fifo_empty_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_transmitter_fifo_empty_triger_typeGet
//  Description : Set the value of the member INTRSET.transmitter_fifo_empty_triger_type
//  Input       : unsigned int utransmitter_fifo_empty_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_transmitter_fifo_empty_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.transmitter_fifo_empty_triger_type;


}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_full_intr_enSet
//  Description : Set the value of the member INTRSET.up_sample_fifo_full_intr_en
//  Input       : unsigned int uup_sample_fifo_full_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_full_intr_enSet(unsigned int uup_sample_fifo_full_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.up_sample_fifo_full_intr_en = uup_sample_fifo_full_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_full_intr_enGet
//  Description : Set the value of the member INTRSET.up_sample_fifo_full_intr_en
//  Input       : unsigned int uup_sample_fifo_full_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_full_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.up_sample_fifo_full_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_full_triger_typeSet
//  Description : Set the value of the member INTRSET.up_sample_fifo_full_triger_type
//  Input       : unsigned int uup_sample_fifo_full_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_full_triger_typeSet(unsigned int uup_sample_fifo_full_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.up_sample_fifo_full_triger_type = uup_sample_fifo_full_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_full_triger_typeGet
//  Description : Set the value of the member INTRSET.up_sample_fifo_full_triger_type
//  Input       : unsigned int uup_sample_fifo_full_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_full_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.up_sample_fifo_full_triger_type;


}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_empty_intr_enSet
//  Description : Set the value of the member INTRSET.up_sample_fifo_empty_intr_en
//  Input       : unsigned int uup_sample_fifo_empty_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_empty_intr_enSet(unsigned int uup_sample_fifo_empty_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.up_sample_fifo_empty_intr_en = uup_sample_fifo_empty_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_empty_intr_enGet
//  Description : Set the value of the member INTRSET.up_sample_fifo_empty_intr_en
//  Input       : unsigned int uup_sample_fifo_empty_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_empty_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.up_sample_fifo_empty_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_empty_triger_typeSet
//  Description : Set the value of the member INTRSET.up_sample_fifo_empty_triger_type
//  Input       : unsigned int uup_sample_fifo_empty_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_empty_triger_typeSet(unsigned int uup_sample_fifo_empty_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.up_sample_fifo_empty_triger_type = uup_sample_fifo_empty_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_up_sample_fifo_empty_triger_typeGet
//  Description : Set the value of the member INTRSET.up_sample_fifo_empty_triger_type
//  Input       : unsigned int uup_sample_fifo_empty_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_up_sample_fifo_empty_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.up_sample_fifo_empty_triger_type;


}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_full_intr_enSet
//  Description : Set the value of the member INTRSET.hs_fifo_full_intr_en
//  Input       : unsigned int uhs_fifo_full_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_full_intr_enSet(unsigned int uhs_fifo_full_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.hs_fifo_full_intr_en = uhs_fifo_full_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_full_intr_enGet
//  Description : Set the value of the member INTRSET.hs_fifo_full_intr_en
//  Input       : unsigned int uhs_fifo_full_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_full_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.hs_fifo_full_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_full_triger_typeSet
//  Description : Set the value of the member INTRSET.hs_fifo_full_triger_type
//  Input       : unsigned int uhs_fifo_full_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_full_triger_typeSet(unsigned int uhs_fifo_full_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.hs_fifo_full_triger_type = uhs_fifo_full_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_full_triger_typeGet
//  Description : Set the value of the member INTRSET.hs_fifo_full_triger_type
//  Input       : unsigned int uhs_fifo_full_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_full_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.hs_fifo_full_triger_type;


}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_empty_intr_enSet
//  Description : Set the value of the member INTRSET.hs_fifo_empty_intr_en
//  Input       : unsigned int uhs_fifo_empty_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_empty_intr_enSet(unsigned int uhs_fifo_empty_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.hs_fifo_empty_intr_en = uhs_fifo_empty_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_empty_intr_enGet
//  Description : Set the value of the member INTRSET.hs_fifo_empty_intr_en
//  Input       : unsigned int uhs_fifo_empty_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_empty_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.hs_fifo_empty_intr_en;


}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_empty_triger_typeSet
//  Description : Set the value of the member INTRSET.hs_fifo_empty_triger_type
//  Input       : unsigned int uhs_fifo_empty_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_empty_triger_typeSet(unsigned int uhs_fifo_empty_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.hs_fifo_empty_triger_type = uhs_fifo_empty_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_intrset.u32, "INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_INTRSET_hs_fifo_empty_triger_typeGet
//  Description : Set the value of the member INTRSET.hs_fifo_empty_triger_type
//  Input       : unsigned int uhs_fifo_empty_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_hs_fifo_empty_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.hs_fifo_empty_triger_type;


}



//******************************************************************************
//  Function    : DATE_CLKSET_mod_div_valGet
//  Description : Set the value of the member CLKSET.mod_div_val
//  Input       : unsigned int umod_div_val: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_mod_div_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.mod_div_val;


}



//******************************************************************************
//  Function    : DATE_CLKSET_p_fdivclk_selGet
//  Description : Set the value of the member CLKSET.p_fdivclk_sel
//  Input       : unsigned int up_fdivclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fdivclk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_fdivclk_sel;


}



//******************************************************************************
//  Function    : DATE_CLKSET_p_modclk_selGet
//  Description : Set the value of the member CLKSET.p_modclk_sel
//  Input       : unsigned int up_modclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_modclk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_modclk_sel;


}


//******************************************************************************
//  Function    : DATE_CLKSET_p_ctmanGet
//  Description : Set the value of the member CLKSET.p_ctman
//  Input       : unsigned int up_ctman: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_ctmanGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_ctman;


}



//******************************************************************************
//  Function    : DATE_CLKSET_p_refclk_selGet
//  Description : Set the value of the member CLKSET.p_refclk_sel
//  Input       : unsigned int up_refclk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_refclk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_refclk_sel;


}


//******************************************************************************
//  Function    : DATE_CLKSET_p_fd_clk_selGet
//  Description : Set the value of the member CLKSET.p_fd_clk_sel
//  Input       : unsigned int up_fd_clk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fd_clk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_fd_clk_sel;


}


//******************************************************************************
//  Function    : DATE_SWRESET_global_resetGet
//  Description : Set the value of the member SWRESET.global_reset
//  Input       : unsigned int uglobal_reset: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_global_resetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.global_reset;


}


//******************************************************************************
//  Function    : DATE_SWRESET_swreset_unusedGet
//  Description : Set the value of the member SWRESET.swreset_unused
//  Input       : unsigned int uswreset_unused: 14 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_swreset_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.swreset_unused;


}

//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_frl_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_frl_clock
//  Input       : unsigned int usw_reset_frl_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_frl_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_frl_clock;


}

//******************************************************************************
//  Function    : DATE_SWRESET_up_sample_fifo_clock_swrstSet
//  Description : Set the value of the member SWRESET.up_sample_fifo_clock_swrst
//  Input       : unsigned int uup_sample_fifo_clock_swrst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_up_sample_fifo_clock_swrstSet(unsigned int uup_sample_fifo_clock_swrst)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.up_sample_fifo_clock_swrst = uup_sample_fifo_clock_swrst;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_swreset.u32, "SWRESET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_SWRESET_up_sample_fifo_clock_swrstGet
//  Description : Set the value of the member SWRESET.up_sample_fifo_clock_swrst
//  Input       : unsigned int uup_sample_fifo_clock_swrst: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_up_sample_fifo_clock_swrstGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.up_sample_fifo_clock_swrst;


}



//******************************************************************************
//  Function    : DATE_SWRESET_dac_clock_gatGet
//  Description : Set the value of the member SWRESET.dac_clock_gat
//  Input       : unsigned int udac_clock_gat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_dac_clock_gatGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.dac_clock_gat;


}


//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_dac_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_dac_clock
//  Input       : unsigned int usw_reset_dac_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_dac_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_dac_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_pllref_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_pllref_clock
//  Input       : unsigned int usw_reset_pllref_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_pllref_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_pllref_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_hs_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_hs_clock
//  Input       : unsigned int usw_reset_hs_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_hs_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_hs_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_data_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_data_clock
//  Input       : unsigned int usw_reset_data_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_data_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_data_clock;


}


//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_txfifo_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_txfifo_clock
//  Input       : unsigned int usw_reset_txfifo_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_txfifo_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_txfifo_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_hsfifo_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_hsfifo_clock
//  Input       : unsigned int usw_reset_hsfifo_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_hsfifo_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_hsfifo_clock;


}


//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_mod_and_fd_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_fd_clock
//  Input       : unsigned int usw_reset_mod_and_fd_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_fd_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_and_fd_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_mod_and_nco_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_nco_clock
//  Input       : unsigned int usw_reset_mod_and_nco_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_nco_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_and_nco_clock;


}


//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_mod_and_mpll_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_mpll_clock
//  Input       : unsigned int usw_reset_mod_and_mpll_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_mpll_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_and_mpll_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_fd_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_fd_clock
//  Input       : unsigned int usw_reset_fd_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_fd_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_fd_clock;


}


//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_nco_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_nco_clock
//  Input       : unsigned int usw_reset_nco_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_nco_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_nco_clock;


}

//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_mpll_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mpll_clock
//  Input       : unsigned int usw_reset_mpll_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mpll_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mpll_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_tmds_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_tmds_clock
//  Input       : unsigned int usw_reset_tmds_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_tmds_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_tmds_clock;


}



//******************************************************************************
//  Function    : DATE_SWRESET_sw_reset_mod_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_clock
//  Input       : unsigned int usw_reset_mod_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_clock;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk7_divSet
//  Description : Set the value of the member GLUESET0.clk7_div
//  Input       : unsigned int uclk7_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk7_divSet(unsigned int uclk7_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk7_div = uclk7_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk7_divGet
//  Description : Set the value of the member GLUESET0.clk7_div
//  Input       : unsigned int uclk7_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk7_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk7_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk6_divSet
//  Description : Set the value of the member GLUESET0.clk6_div
//  Input       : unsigned int uclk6_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk6_divSet(unsigned int uclk6_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk6_div = uclk6_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk6_divGet
//  Description : Set the value of the member GLUESET0.clk6_div
//  Input       : unsigned int uclk6_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk6_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk6_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk5_divSet
//  Description : Set the value of the member GLUESET0.clk5_div
//  Input       : unsigned int uclk5_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk5_divSet(unsigned int uclk5_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk5_div = uclk5_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk5_divGet
//  Description : Set the value of the member GLUESET0.clk5_div
//  Input       : unsigned int uclk5_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk5_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk5_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk4_divSet
//  Description : Set the value of the member GLUESET0.clk4_div
//  Input       : unsigned int uclk4_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk4_divSet(unsigned int uclk4_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk4_div = uclk4_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk4_divGet
//  Description : Set the value of the member GLUESET0.clk4_div
//  Input       : unsigned int uclk4_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk4_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk4_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk3_divSet
//  Description : Set the value of the member GLUESET0.clk3_div
//  Input       : unsigned int uclk3_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk3_divSet(unsigned int uclk3_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk3_div = uclk3_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk3_divGet
//  Description : Set the value of the member GLUESET0.clk3_div
//  Input       : unsigned int uclk3_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk3_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk3_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk2_divSet
//  Description : Set the value of the member GLUESET0.clk2_div
//  Input       : unsigned int uclk2_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk2_divSet(unsigned int uclk2_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk2_div = uclk2_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk2_divGet
//  Description : Set the value of the member GLUESET0.clk2_div
//  Input       : unsigned int uclk2_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk2_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk2_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk1_divSet
//  Description : Set the value of the member GLUESET0.clk1_div
//  Input       : unsigned int uclk1_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk1_divSet(unsigned int uclk1_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk1_div = uclk1_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk1_divGet
//  Description : Set the value of the member GLUESET0.clk1_div
//  Input       : unsigned int uclk1_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk1_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk1_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk0_divSet
//  Description : Set the value of the member GLUESET0.clk0_div
//  Input       : unsigned int uclk0_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk0_divSet(unsigned int uclk0_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk0_div = uclk0_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset0.u32, "GLUESET0");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET0_clk0_divGet
//  Description : Set the value of the member GLUESET0.clk0_div
//  Input       : unsigned int uclk0_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk0_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk0_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET1_glueset1_unused_2Set
//  Description : Set the value of the member GLUESET1.glueset1_unused_2
//  Input       : unsigned int uglueset1_unused_2: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_2Set(unsigned int uglueset1_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.glueset1_unused_2 = uglueset1_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset1.u32, "GLUESET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET1_glueset1_unused_2Get
//  Description : Set the value of the member GLUESET1.glueset1_unused_2
//  Input       : unsigned int uglueset1_unused_2: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.glueset1_unused_2;


}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk_selSet
//  Description : Set the value of the member GLUESET1.clk_sel
//  Input       : unsigned int uclk_sel: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk_selSet(unsigned int uclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk_sel = uclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset1.u32, "GLUESET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk_selGet
//  Description : Set the value of the member GLUESET1.clk_sel
//  Input       : unsigned int uclk_sel: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk_sel;


}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk11_divSet
//  Description : Set the value of the member GLUESET1.clk11_div
//  Input       : unsigned int uclk11_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk11_divSet(unsigned int uclk11_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk11_div = uclk11_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset1.u32, "GLUESET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk11_divGet
//  Description : Set the value of the member GLUESET1.clk11_div
//  Input       : unsigned int uclk11_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk11_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk11_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk10_divSet
//  Description : Set the value of the member GLUESET1.clk10_div
//  Input       : unsigned int uclk10_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk10_divSet(unsigned int uclk10_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk10_div = uclk10_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset1.u32, "GLUESET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk10_divGet
//  Description : Set the value of the member GLUESET1.clk10_div
//  Input       : unsigned int uclk10_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk10_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk10_div;


}

//******************************************************************************
//  Function    : DATE_GLUESET1_glueset1_unused_1Set
//  Description : Set the value of the member GLUESET1.glueset1_unused_1
//  Input       : unsigned int uglueset1_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_1Set(unsigned int uglueset1_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.glueset1_unused_1 = uglueset1_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset1.u32, "GLUESET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET1_glueset1_unused_1Get
//  Description : Set the value of the member GLUESET1.glueset1_unused_1
//  Input       : unsigned int uglueset1_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.glueset1_unused_1;


}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk8_divSet
//  Description : Set the value of the member GLUESET1.clk8_div
//  Input       : unsigned int uclk8_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk8_divSet(unsigned int uclk8_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk8_div = uclk8_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_glueset1.u32, "GLUESET1");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_GLUESET1_clk8_divGet
//  Description : Set the value of the member GLUESET1.clk8_div
//  Input       : unsigned int uclk8_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk8_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk8_div;


}

//******************************************************************************
//  Function    : DATE_CT_INTRSET_ct_fcon_intr_enSet
//  Description : Set the value of the member CT_INTRSET.ct_fcon_intr_en
//  Input       : unsigned int uct_fcon_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CT_INTRSET_ct_fcon_intr_enSet(unsigned int uct_fcon_intr_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CT_INTRSET o_ct_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CT_INTRSET.u32);
    o_ct_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ct_intrset.bits.ct_fcon_intr_en = uct_fcon_intr_en;
    HDMI21TXRegWrite(pu32RegAddr, o_ct_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ct_intrset.u32, "CT_INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CT_INTRSET_ct_fcon_intr_enGet
//  Description : Set the value of the member CT_INTRSET.ct_fcon_intr_en
//  Input       : unsigned int uct_fcon_intr_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CT_INTRSET_ct_fcon_intr_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CT_INTRSET o_ct_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CT_INTRSET.u32);
    o_ct_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ct_intrset.bits.ct_fcon_intr_en;


}

//******************************************************************************
//  Function    : DATE_CT_INTRSET_ct_fcon_triger_typeSet
//  Description : Set the value of the member CT_INTRSET.ct_fcon_triger_type
//  Input       : unsigned int uct_fcon_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CT_INTRSET_ct_fcon_triger_typeSet(unsigned int uct_fcon_triger_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CT_INTRSET o_ct_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CT_INTRSET.u32);
    o_ct_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ct_intrset.bits.ct_fcon_triger_type = uct_fcon_triger_type;
    HDMI21TXRegWrite(pu32RegAddr, o_ct_intrset.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_ct_intrset.u32, "CT_INTRSET");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_CT_INTRSET_ct_fcon_triger_typeGet
//  Description : Set the value of the member CT_INTRSET.ct_fcon_triger_type
//  Input       : unsigned int uct_fcon_triger_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CT_INTRSET_ct_fcon_triger_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CT_INTRSET o_ct_intrset;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->CT_INTRSET.u32);
    o_ct_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ct_intrset.bits.ct_fcon_triger_type;


}

//******************************************************************************
//  Function    : DATE_HW_INFO_hw_infoSet
//  Description : Set the value of the member HW_INFO.hw_info
//  Input       : unsigned int uhw_info: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_INFO_hw_infoSet(unsigned int uhw_info)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_INFO o_hw_info;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_INFO.u32);
    o_hw_info.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hw_info.bits.hw_info = uhw_info;
    HDMI21TXRegWrite(pu32RegAddr, o_hw_info.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hw_info.u32, "HW_INFO");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HW_INFO_hw_infoGet
//  Description : Set the value of the member HW_INFO.hw_info
//  Input       : unsigned int uhw_info: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_INFO_hw_infoGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_INFO o_hw_info;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_INFO.u32);
    o_hw_info.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hw_info.bits.hw_info;


}

//******************************************************************************
//  Function    : DATE_HW_VERS_hw_vers_unused_2Set
//  Description : Set the value of the member HW_VERS.hw_vers_unused_2
//  Input       : unsigned int uhw_vers_unused_2: 26 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hw_vers_unused_2Set(unsigned int uhw_vers_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hw_vers.bits.hw_vers_unused_2 = uhw_vers_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_hw_vers.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hw_vers.u32, "HW_VERS");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HW_VERS_hw_vers_unused_2Get
//  Description : Set the value of the member HW_VERS.hw_vers_unused_2
//  Input       : unsigned int uhw_vers_unused_2: 26 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hw_vers_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hw_vers.bits.hw_vers_unused_2;


}

//******************************************************************************
//  Function    : DATE_HW_VERS_hdmi21_complianceSet
//  Description : Set the value of the member HW_VERS.hdmi21_compliance
//  Input       : unsigned int uhdmi21_compliance: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hdmi21_complianceSet(unsigned int uhdmi21_compliance)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hw_vers.bits.hdmi21_compliance = uhdmi21_compliance;
    HDMI21TXRegWrite(pu32RegAddr, o_hw_vers.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hw_vers.u32, "HW_VERS");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HW_VERS_hdmi21_complianceGet
//  Description : Set the value of the member HW_VERS.hdmi21_compliance
//  Input       : unsigned int uhdmi21_compliance: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hdmi21_complianceGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hw_vers.bits.hdmi21_compliance;


}

//******************************************************************************
//  Function    : DATE_HW_VERS_hdmi20_complianceSet
//  Description : Set the value of the member HW_VERS.hdmi20_compliance
//  Input       : unsigned int uhdmi20_compliance: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hdmi20_complianceSet(unsigned int uhdmi20_compliance)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hw_vers.bits.hdmi20_compliance = uhdmi20_compliance;
    HDMI21TXRegWrite(pu32RegAddr, o_hw_vers.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hw_vers.u32, "HW_VERS");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HW_VERS_hdmi20_complianceGet
//  Description : Set the value of the member HW_VERS.hdmi20_compliance
//  Input       : unsigned int uhdmi20_compliance: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hdmi20_complianceGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hw_vers.bits.hdmi20_compliance;


}

//******************************************************************************
//  Function    : DATE_HW_VERS_hw_vers_unused_1Set
//  Description : Set the value of the member HW_VERS.hw_vers_unused_1
//  Input       : unsigned int uhw_vers_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hw_vers_unused_1Set(unsigned int uhw_vers_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hw_vers.bits.hw_vers_unused_1 = uhw_vers_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_hw_vers.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_hw_vers.u32, "HW_VERS");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_HW_VERS_hw_vers_unused_1Get
//  Description : Set the value of the member HW_VERS.hw_vers_unused_1
//  Input       : unsigned int uhw_vers_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HW_VERS_hw_vers_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HW_VERS o_hw_vers;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->HW_VERS.u32);
    o_hw_vers.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hw_vers.bits.hw_vers_unused_1;


}

//******************************************************************************
//  Function    : DATE_RASMODE_ras_modeSet
//  Description : Set the value of the member RASMODE.ras_mode
//  Input       : unsigned int uras_mode: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RASMODE_ras_modeSet(unsigned int uras_mode)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RASMODE o_rasmode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RASMODE.u32);
    o_rasmode.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_rasmode.bits.ras_mode = uras_mode;
    HDMI21TXRegWrite(pu32RegAddr, o_rasmode.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_rasmode.u32, "RASMODE");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_RASMODE_ras_modeGet
//  Description : Set the value of the member RASMODE.ras_mode
//  Input       : unsigned int uras_mode: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RASMODE_ras_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RASMODE o_rasmode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RASMODE.u32);
    o_rasmode.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_rasmode.bits.ras_mode;


}

//******************************************************************************
//  Function    : DATE_RFSMODE_rfs_modeSet
//  Description : Set the value of the member RFSMODE.rfs_mode
//  Input       : unsigned int urfs_mode: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RFSMODE_rfs_modeSet(unsigned int urfs_mode)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RFSMODE o_rfsmode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RFSMODE.u32);
    o_rfsmode.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_rfsmode.bits.rfs_mode = urfs_mode;
    HDMI21TXRegWrite(pu32RegAddr, o_rfsmode.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_rfsmode.u32, "RFSMODE");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_RFSMODE_rfs_modeGet
//  Description : Set the value of the member RFSMODE.rfs_mode
//  Input       : unsigned int urfs_mode: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RFSMODE_rfs_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RFSMODE o_rfsmode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RFSMODE.u32);
    o_rfsmode.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_rfsmode.bits.rfs_mode;


}

//******************************************************************************
//  Function    : DATE_RFTMODE_rft_modeSet
//  Description : Set the value of the member RFTMODE.rft_mode
//  Input       : unsigned int urft_mode: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RFTMODE_rft_modeSet(unsigned int urft_mode)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RFTMODE o_rftmode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RFTMODE.u32);
    o_rftmode.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_rftmode.bits.rft_mode = urft_mode;
    HDMI21TXRegWrite(pu32RegAddr, o_rftmode.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_rftmode.u32, "RFTMODE");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_RFTMODE_rft_modeGet
//  Description : Set the value of the member RFTMODE.rft_mode
//  Input       : unsigned int urft_mode: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RFTMODE_rft_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RFTMODE o_rftmode;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->RFTMODE.u32);
    o_rftmode.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_rftmode.bits.rft_mode;


}

//******************************************************************************
//  Function    : DATE_STBOPT_stb_cs_selGet
//  Description : Set the value of the member STBOPT.stb_cs_sel
//  Input       : unsigned int ustb_cs_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_cs_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_cs_sel;


}

//******************************************************************************
//  Function    : DATE_STBOPT_stb_acc_selGet
//  Description : Set the value of the member STBOPT.stb_acc_sel
//  Input       : unsigned int ustb_acc_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_acc_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_acc_sel;


}




//******************************************************************************
//  Function    : DATE_STBOPT_stb_delay0Get
//  Description : Set the value of the member STBOPT.stb_delay0
//  Input       : unsigned int ustb_delay0: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_delay0;


}



//******************************************************************************
//  Function    : DATE_STBOPT_stb_delay1Get
//  Description : Set the value of the member STBOPT.stb_delay1
//  Input       : unsigned int ustb_delay1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_delay1;


}



//******************************************************************************
//  Function    : DATE_STBOPT_stb_delay2Get
//  Description : Set the value of the member STBOPT.stb_delay2
//  Input       : unsigned int ustb_delay2: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_delay2;


}



//******************************************************************************
//  Function    : DATE_STBOPT_req_lengthGet
//  Description : Set the value of the member STBOPT.req_length
//  Input       : unsigned int ureq_length: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_req_lengthGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.req_length;


}

//******************************************************************************
//  Function    : DATE_STBREQ_req_doneSet
//  Description : Set the value of the member STBREQ.req_done
//  Input       : unsigned int ureq_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBREQ_req_doneSet(unsigned int ureq_done)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBREQ o_stbreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBREQ.u32);
    o_stbreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbreq.bits.req_done = ureq_done;
    HDMI21TXRegWrite(pu32RegAddr, o_stbreq.u32);
    //DATEVerifyRegWrite(pu32RegAddr, o_stbreq.u32, "STBREQ");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : DATE_STBREQ_req_doneGet
//  Description : Set the value of the member STBREQ.req_done
//  Input       : unsigned int ureq_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBREQ_req_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBREQ o_stbreq;
    pu32RegAddr = (HI_U32*)&(hi3559a_dphy_regAllReg->STBREQ.u32);
    o_stbreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbreq.bits.req_done;

}

//******************************************************************************
//  Function    : HDMI_STBRDATA_stb_auto_rdataSet
//  Description : Set the value of the member STBRDATA.stb_auto_rdata
//  Input       : unsigned int ustb_auto_rdata: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBRDATA_stb_auto_rdataSet(unsigned int ustb_auto_rdata)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBRDATA o_stbrdata;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBRDATA.u32);
    o_stbrdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbrdata.bits.stb_auto_rdata = ustb_auto_rdata;
    HDMI21TXRegWrite(pu32RegAddr, o_stbrdata.u32);
    //HDMITXVerifyRegWrite(pu32RegAddr, o_stbrdata.u32, "STBRDATA");

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_STBRDATA_stb_auto_rdataGet
//  Description : Set the value of the member STBRDATA.stb_auto_rdata
//  Input       : unsigned int ustb_auto_rdata: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBRDATA_stb_auto_rdataGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBRDATA o_stbrdata;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBRDATA.u32);
    o_stbrdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbrdata.bits.stb_auto_rdata;
}

#endif
