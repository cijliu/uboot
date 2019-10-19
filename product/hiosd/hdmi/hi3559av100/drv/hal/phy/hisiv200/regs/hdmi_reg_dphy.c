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
#ifndef HDMI_BUILD_IN_BOOT
#include "hdmi_product_define.h"
#endif

/* The base address of the module hifonev500_dphy_reg */
#define PRODUCT_NULL_CHK(p) do{\
	if(HI_NULL == p)\
    {\
	return HI_FAILURE;}\
}while(0)

/* Define the struct pointor of the module hifonev500_dphy_reg */
volatile S_hifonev500_dphy_reg_REGS_TYPE *gophifonev500_dphy_regAllReg = 0;

HI_S32 HDMI_HDMITX_PHY_reg_Init(HI_CHAR *pcAddr)
{
    if (NULL != gophifonev500_dphy_regAllReg)
    {
    	HDMI_INFO("ioremap_nocache gophifonev500_dphy_regAllReg have SUCCESSED!\n");
        return HI_SUCCESS;
    }

	gophifonev500_dphy_regAllReg  = (S_hifonev500_dphy_reg_REGS_TYPE*)HDMI_IO_MAP(BASE_ADDR_tx_dphy, 4);

	if(NULL == gophifonev500_dphy_regAllReg)
    {
        HDMI_ERR("ioremap_nocache gophifonev500_dphy_regAllReg failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HDMI_HDMITX_PHY_reg_DeInit(HI_VOID)
{
    if(HI_NULL != gophifonev500_dphy_regAllReg)
    {
        HDMI_IO_UNMAP(gophifonev500_dphy_regAllReg);
        gophifonev500_dphy_regAllReg = HI_NULL;
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

/* Define the struct pointor of the module hifonev500_dphy_reg */
//volatile S_hifonev500_dphy_reg_REGS_TYPE *gophifonev500_dphy_regAllReg = NULL;

//******************************************************************************
//  Function    : HDMI_T2GPPORT0_gpport0Set
//  Description : Set the value of the member T2GPPORT0.gpport0
//  Input       : unsigned int ugpport0: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT0_gpport0Set(unsigned int ugpport0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT0 o_t2gpport0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->T2GPPORT0.u32);
    o_t2gpport0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_t2gpport0.bits.gpport0 = ugpport0;
    HDMI21TXRegWrite(pu32RegAddr, o_t2gpport0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_T2GPPORT0_gpport0Get
//  Description : Set the value of the member T2GPPORT0.gpport0
//  Input       : unsigned int ugpport0: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT0_gpport0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT0 o_t2gpport0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->T2GPPORT0.u32);
    o_t2gpport0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_t2gpport0.bits.gpport0;
}

//******************************************************************************
//  Function    : HDMI_T2GPPORT1_gpport1Set
//  Description : Set the value of the member T2GPPORT1.gpport1
//  Input       : unsigned int ugpport1: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT1_gpport1Set(unsigned int ugpport1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT1 o_t2gpport1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->T2GPPORT1.u32);
    o_t2gpport1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_t2gpport1.bits.gpport1 = ugpport1;
    HDMI21TXRegWrite(pu32RegAddr, o_t2gpport1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_T2GPPORT1_gpport1Get
//  Description : Set the value of the member T2GPPORT1.gpport1
//  Input       : unsigned int ugpport1: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_T2GPPORT1_gpport1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_T2GPPORT1 o_t2gpport1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->T2GPPORT1.u32);
    o_t2gpport1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_t2gpport1.bits.gpport1;
}

//******************************************************************************
//  Function    : HDMI_PHY_CSEN_stb_cs_enSet
//  Description : Set the value of the member PHY_CSEN.stb_cs_en
//  Input       : unsigned int ustb_cs_en: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_CSEN_stb_cs_enSet(unsigned int ustb_cs_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_CSEN o_phy_csen;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_CSEN.u32);
    o_phy_csen.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_csen.bits.stb_cs_en = ustb_cs_en;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_csen.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PHY_CSEN_stb_cs_enGet
//  Description : Set the value of the member PHY_CSEN.stb_cs_en
//  Input       : unsigned int ustb_cs_en: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_CSEN_stb_cs_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_CSEN o_phy_csen;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_CSEN.u32);
    o_phy_csen.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_csen.bits.stb_cs_en;
}

//******************************************************************************
//  Function    : HDMI_PHY_WR_stb_wenSet
//  Description : Set the value of the member PHY_WR.stb_wen
//  Input       : unsigned int ustb_wen: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WR_stb_wenSet(unsigned int ustb_wen)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WR o_phy_wr;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_WR.u32);
    o_phy_wr.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_wr.bits.stb_wen = ustb_wen;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_wr.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PHY_WR_stb_wenGet
//  Description : Set the value of the member PHY_WR.stb_wen
//  Input       : unsigned int ustb_wen: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WR_stb_wenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WR o_phy_wr;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_WR.u32);
    o_phy_wr.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_wr.bits.stb_wen;
}

//******************************************************************************
//  Function    : HDMI_RESETN_resetnSet
//  Description : Set the value of the member RESETN.resetn
//  Input       : unsigned int uresetn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RESETN_resetnSet(unsigned int uresetn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RESETN o_resetn;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->RESETN.u32);
    o_resetn.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_resetn.bits.resetn = uresetn;
    HDMI21TXRegWrite(pu32RegAddr, o_resetn.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_RESETN_resetnGet
//  Description : Set the value of the member RESETN.resetn
//  Input       : unsigned int uresetn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_RESETN_resetnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_RESETN o_resetn;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->RESETN.u32);
    o_resetn.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_resetn.bits.resetn;
}

//******************************************************************************
//  Function    : HDMI_PHY_ADDR_stb_addrSet
//  Description : Set the value of the member PHY_ADDR.stb_addr
//  Input       : unsigned int ustb_addr: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_ADDR_stb_addrSet(unsigned int ustb_addr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_ADDR o_phy_addr;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_ADDR.u32);
    o_phy_addr.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_addr.bits.stb_addr = ustb_addr;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_addr.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PHY_ADDR_stb_addrGet
//  Description : Set the value of the member PHY_ADDR.stb_addr
//  Input       : unsigned int ustb_addr: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_ADDR_stb_addrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_ADDR o_phy_addr;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_ADDR.u32);
    o_phy_addr.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_addr.bits.stb_addr;
}

//******************************************************************************
//  Function    : HDMI_PHY_WDATA_stb_wdataSet
//  Description : Set the value of the member PHY_WDATA.stb_wdata
//  Input       : unsigned int ustb_wdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WDATA_stb_wdataSet(unsigned int ustb_wdata)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WDATA o_phy_wdata;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_WDATA.u32);
    o_phy_wdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_wdata.bits.stb_wdata = ustb_wdata;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_wdata.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PHY_WDATA_stb_wdataGet
//  Description : Set the value of the member PHY_WDATA.stb_wdata
//  Input       : unsigned int ustb_wdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_WDATA_stb_wdataGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_WDATA o_phy_wdata;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_WDATA.u32);
    o_phy_wdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_wdata.bits.stb_wdata;
}

//******************************************************************************
//  Function    : HDMI_PHY_RDATA_stb_rdataSet
//  Description : Set the value of the member PHY_RDATA.stb_rdata
//  Input       : unsigned int ustb_rdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_RDATA_stb_rdataSet(unsigned int ustb_rdata)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_RDATA o_phy_rdata;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_RDATA.u32);
    o_phy_rdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_phy_rdata.bits.stb_rdata = ustb_rdata;
    HDMI21TXRegWrite(pu32RegAddr, o_phy_rdata.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_PHY_RDATA_stb_rdataGet
//  Description : Set the value of the member PHY_RDATA.stb_rdata
//  Input       : unsigned int ustb_rdata: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_PHY_RDATA_stb_rdataGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_PHY_RDATA o_phy_rdata;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->PHY_RDATA.u32);
    o_phy_rdata.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_phy_rdata.bits.stb_rdata;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_rxsenseSet
//  Description : Set the value of the member ZCALREG.rxsense
//  Input       : unsigned int urxsense: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_rxsenseSet(unsigned int urxsense)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.rxsense = urxsense;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_rxsenseGet
//  Description : Set the value of the member ZCALREG.rxsense
//  Input       : unsigned int urxsense: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_rxsenseGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.rxsense;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_zcalsubSet
//  Description : Set the value of the member ZCALREG.zcalsub
//  Input       : unsigned int uzcalsub: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalsubSet(unsigned int uzcalsub)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.zcalsub = uzcalsub;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_zcalsubGet
//  Description : Set the value of the member ZCALREG.zcalsub
//  Input       : unsigned int uzcalsub: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalsubGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.zcalsub;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_zcaldoneSet
//  Description : Set the value of the member ZCALREG.zcaldone
//  Input       : unsigned int uzcaldone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcaldoneSet(unsigned int uzcaldone)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.zcaldone = uzcaldone;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_zcaldoneGet
//  Description : Set the value of the member ZCALREG.zcaldone
//  Input       : unsigned int uzcaldone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcaldoneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.zcaldone;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_zcalSet
//  Description : Set the value of the member ZCALREG.zcal
//  Input       : unsigned int uzcal: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalSet(unsigned int uzcal)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalreg.bits.zcal = uzcal;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalreg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_ZCALREG_zcalGet
//  Description : Set the value of the member ZCALREG.zcal
//  Input       : unsigned int uzcal: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALREG_zcalGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALREG o_zcalreg;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALREG.u32);
    o_zcalreg.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalreg.bits.zcal;
}

//******************************************************************************
//  Function    : HDMI_ZCALCLK_zcalclkSet
//  Description : Set the value of the member ZCALCLK.zcalclk
//  Input       : unsigned int uzcalclk: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALCLK_zcalclkSet(unsigned int uzcalclk)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALCLK o_zcalclk;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALCLK.u32);
    o_zcalclk.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_zcalclk.bits.zcalclk = uzcalclk;
    HDMI21TXRegWrite(pu32RegAddr, o_zcalclk.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_ZCALCLK_zcalclkGet
//  Description : Set the value of the member ZCALCLK.zcalclk
//  Input       : unsigned int uzcalclk: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_ZCALCLK_zcalclkGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_ZCALCLK o_zcalclk;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->ZCALCLK.u32);
    o_zcalclk.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_zcalclk.bits.zcalclk;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_clkshortdetSet
//  Description : Set the value of the member SHORTDET.clkshortdet
//  Input       : unsigned int uclkshortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_clkshortdetSet(unsigned int uclkshortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.clkshortdet = uclkshortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_clkshortdetGet
//  Description : Set the value of the member SHORTDET.clkshortdet
//  Input       : unsigned int uclkshortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_clkshortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.clkshortdet;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_c2shortdetSet
//  Description : Set the value of the member SHORTDET.c2shortdet
//  Input       : unsigned int uc2shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c2shortdetSet(unsigned int uc2shortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.c2shortdet = uc2shortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_c2shortdetGet
//  Description : Set the value of the member SHORTDET.c2shortdet
//  Input       : unsigned int uc2shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c2shortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.c2shortdet;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_c1shortdetSet
//  Description : Set the value of the member SHORTDET.c1shortdet
//  Input       : unsigned int uc1shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c1shortdetSet(unsigned int uc1shortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.c1shortdet = uc1shortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_c1shortdetGet
//  Description : Set the value of the member SHORTDET.c1shortdet
//  Input       : unsigned int uc1shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c1shortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.c1shortdet;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_c0shortdetSet
//  Description : Set the value of the member SHORTDET.c0shortdet
//  Input       : unsigned int uc0shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c0shortdetSet(unsigned int uc0shortdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_shortdet.bits.c0shortdet = uc0shortdet;
    HDMI21TXRegWrite(pu32RegAddr, o_shortdet.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SHORTDET_c0shortdetGet
//  Description : Set the value of the member SHORTDET.c0shortdet
//  Input       : unsigned int uc0shortdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SHORTDET_c0shortdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SHORTDET o_shortdet;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SHORTDET.u32);
    o_shortdet.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_shortdet.bits.c0shortdet;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_lkvdethighSet
//  Description : Set the value of the member DET.t2_lkvdethigh
//  Input       : unsigned int ut2_lkvdethigh: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdethighSet(unsigned int ut2_lkvdethigh)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_lkvdethigh = ut2_lkvdethigh;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_lkvdethighGet
//  Description : Set the value of the member DET.t2_lkvdethigh
//  Input       : unsigned int ut2_lkvdethigh: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdethighGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_lkvdethigh;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_lkvdetlowSet
//  Description : Set the value of the member DET.t2_lkvdetlow
//  Input       : unsigned int ut2_lkvdetlow: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdetlowSet(unsigned int ut2_lkvdetlow)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_lkvdetlow = ut2_lkvdetlow;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_lkvdetlowGet
//  Description : Set the value of the member DET.t2_lkvdetlow
//  Input       : unsigned int ut2_lkvdetlow: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_lkvdetlowGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_lkvdetlow;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_plllkvdet2Set
//  Description : Set the value of the member DET.t2_plllkvdet2
//  Input       : unsigned int ut2_plllkvdet2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdet2Set(unsigned int ut2_plllkvdet2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_plllkvdet2 = ut2_plllkvdet2;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_plllkvdet2Get
//  Description : Set the value of the member DET.t2_plllkvdet2
//  Input       : unsigned int ut2_plllkvdet2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdet2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_plllkvdet2;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_plllkcdetSet
//  Description : Set the value of the member DET.t2_plllkcdet
//  Input       : unsigned int ut2_plllkcdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkcdetSet(unsigned int ut2_plllkcdet)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_plllkcdet = ut2_plllkcdet;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_plllkcdetGet
//  Description : Set the value of the member DET.t2_plllkcdet
//  Input       : unsigned int ut2_plllkcdet: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkcdetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_plllkcdet;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_plllkvdetlSet
//  Description : Set the value of the member DET.t2_plllkvdetl
//  Input       : unsigned int ut2_plllkvdetl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdetlSet(unsigned int ut2_plllkvdetl)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_det.bits.t2_plllkvdetl = ut2_plllkvdetl;
    HDMI21TXRegWrite(pu32RegAddr, o_det.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DET_t2_plllkvdetlGet
//  Description : Set the value of the member DET.t2_plllkvdetl
//  Input       : unsigned int ut2_plllkvdetl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DET_t2_plllkvdetlGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DET o_det;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DET.u32);
    o_det.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_det.bits.t2_plllkvdetl;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_fdsrcparam_unusedSet
//  Description : Set the value of the member FDSRCPARAM.fdsrcparam_unused
//  Input       : unsigned int ufdsrcparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_fdsrcparam_unusedSet(unsigned int ufdsrcparam_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.fdsrcparam_unused = ufdsrcparam_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_fdsrcparam_unusedGet
//  Description : Set the value of the member FDSRCPARAM.fdsrcparam_unused
//  Input       : unsigned int ufdsrcparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_fdsrcparam_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.fdsrcparam_unused;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_src_enableSet
//  Description : Set the value of the member FDSRCPARAM.src_enable
//  Input       : unsigned int usrc_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_enableSet(unsigned int usrc_enable)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.src_enable = usrc_enable;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_src_enableGet
//  Description : Set the value of the member FDSRCPARAM.src_enable
//  Input       : unsigned int usrc_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_enableGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.src_enable;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_src_lock_cntSet
//  Description : Set the value of the member FDSRCPARAM.src_lock_cnt
//  Input       : unsigned int usrc_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_cntSet(unsigned int usrc_lock_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.src_lock_cnt = usrc_lock_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_src_lock_cntGet
//  Description : Set the value of the member FDSRCPARAM.src_lock_cnt
//  Input       : unsigned int usrc_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.src_lock_cnt;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_src_lock_valSet
//  Description : Set the value of the member FDSRCPARAM.src_lock_val
//  Input       : unsigned int usrc_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_valSet(unsigned int usrc_lock_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcparam.bits.src_lock_val = usrc_lock_val;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCPARAM_src_lock_valGet
//  Description : Set the value of the member FDSRCPARAM.src_lock_val
//  Input       : unsigned int usrc_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCPARAM_src_lock_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCPARAM o_fdsrcparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCPARAM.u32);
    o_fdsrcparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcparam.bits.src_lock_val;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_src_freq_extSet
//  Description : Set the value of the member FDSRCFREQ.src_freq_ext
//  Input       : unsigned int usrc_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_extSet(unsigned int usrc_freq_ext)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.src_freq_ext = usrc_freq_ext;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_src_freq_extGet
//  Description : Set the value of the member FDSRCFREQ.src_freq_ext
//  Input       : unsigned int usrc_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_extGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.src_freq_ext;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_fdsrcfreq_unused_2Set
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_2
//  Input       : unsigned int ufdsrcfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_2Set(unsigned int ufdsrcfreq_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.fdsrcfreq_unused_2 = ufdsrcfreq_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_fdsrcfreq_unused_2Get
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_2
//  Input       : unsigned int ufdsrcfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.fdsrcfreq_unused_2;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_src_freq_optSet
//  Description : Set the value of the member FDSRCFREQ.src_freq_opt
//  Input       : unsigned int usrc_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_optSet(unsigned int usrc_freq_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.src_freq_opt = usrc_freq_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_src_freq_optGet
//  Description : Set the value of the member FDSRCFREQ.src_freq_opt
//  Input       : unsigned int usrc_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_freq_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.src_freq_opt;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_fdsrcfreq_unused_1Set
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_1
//  Input       : unsigned int ufdsrcfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_1Set(unsigned int ufdsrcfreq_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.fdsrcfreq_unused_1 = ufdsrcfreq_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_fdsrcfreq_unused_1Get
//  Description : Set the value of the member FDSRCFREQ.fdsrcfreq_unused_1
//  Input       : unsigned int ufdsrcfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_fdsrcfreq_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.fdsrcfreq_unused_1;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_src_cnt_optSet
//  Description : Set the value of the member FDSRCFREQ.src_cnt_opt
//  Input       : unsigned int usrc_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_cnt_optSet(unsigned int usrc_cnt_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcfreq.bits.src_cnt_opt = usrc_cnt_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCFREQ_src_cnt_optGet
//  Description : Set the value of the member FDSRCFREQ.src_cnt_opt
//  Input       : unsigned int usrc_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCFREQ_src_cnt_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCFREQ o_fdsrcfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCFREQ.u32);
    o_fdsrcfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcfreq.bits.src_cnt_opt;
}

//******************************************************************************
//  Function    : HDMI_FDSRCRES_src_cnt_outSet
//  Description : Set the value of the member FDSRCRES.src_cnt_out
//  Input       : unsigned int usrc_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_cnt_outSet(unsigned int usrc_cnt_out)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcres.bits.src_cnt_out = usrc_cnt_out;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcres.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCRES_src_cnt_outGet
//  Description : Set the value of the member FDSRCRES.src_cnt_out
//  Input       : unsigned int usrc_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_cnt_outGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcres.bits.src_cnt_out;
}

//******************************************************************************
//  Function    : HDMI_FDSRCRES_src_det_statSet
//  Description : Set the value of the member FDSRCRES.src_det_stat
//  Input       : unsigned int usrc_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_det_statSet(unsigned int usrc_det_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdsrcres.bits.src_det_stat = usrc_det_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fdsrcres.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDSRCRES_src_det_statGet
//  Description : Set the value of the member FDSRCRES.src_det_stat
//  Input       : unsigned int usrc_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDSRCRES_src_det_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDSRCRES o_fdsrcres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDSRCRES.u32);
    o_fdsrcres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdsrcres.bits.src_det_stat;
}

//******************************************************************************
//  Function    : HDMI_CTSET0_ctset0_unusedSet
//  Description : Set the value of the member CTSET0.ctset0_unused
//  Input       : unsigned int uctset0_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_ctset0_unusedSet(unsigned int uctset0_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset0.bits.ctset0_unused = uctset0_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CTSET0_ctset0_unusedGet
//  Description : Set the value of the member CTSET0.ctset0_unused
//  Input       : unsigned int uctset0_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_ctset0_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset0.bits.ctset0_unused;
}

//******************************************************************************
//  Function    : HDMI_CTSET0_i_runSet
//  Description : Set the value of the member CTSET0.i_run
//  Input       : unsigned int ui_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_runSet(unsigned int ui_run)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset0.bits.i_run = ui_run;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CTSET0_i_runGet
//  Description : Set the value of the member CTSET0.i_run
//  Input       : unsigned int ui_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_runGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset0.bits.i_run;
}

//******************************************************************************
//  Function    : HDMI_CTSET0_i_enableSet
//  Description : Set the value of the member CTSET0.i_enable
//  Input       : unsigned int ui_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_enableSet(unsigned int ui_enable)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset0.bits.i_enable = ui_enable;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CTSET0_i_enableGet
//  Description : Set the value of the member CTSET0.i_enable
//  Input       : unsigned int ui_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET0_i_enableGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET0 o_ctset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET0.u32);
    o_ctset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset0.bits.i_enable;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_ctset1_unusedSet
//  Description : Set the value of the member CTSET1.ctset1_unused
//  Input       : unsigned int uctset1_unused: 18 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_ctset1_unusedSet(unsigned int uctset1_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset1.bits.ctset1_unused = uctset1_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_ctset1_unusedGet
//  Description : Set the value of the member CTSET1.ctset1_unused
//  Input       : unsigned int uctset1_unused: 18 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_ctset1_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.ctset1_unused;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_i_mpll_ctlckSet
//  Description : Set the value of the member CTSET1.i_mpll_ctlck
//  Input       : unsigned int ui_mpll_ctlck: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_ctlckSet(unsigned int ui_mpll_ctlck)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset1.bits.i_mpll_ctlck = ui_mpll_ctlck;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_i_mpll_ctlckGet
//  Description : Set the value of the member CTSET1.i_mpll_ctlck
//  Input       : unsigned int ui_mpll_ctlck: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_ctlckGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.i_mpll_ctlck;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_i_mpll_divnSet
//  Description : Set the value of the member CTSET1.i_mpll_divn
//  Input       : unsigned int ui_mpll_divn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_divnSet(unsigned int ui_mpll_divn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset1.bits.i_mpll_divn = ui_mpll_divn;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_i_mpll_divnGet
//  Description : Set the value of the member CTSET1.i_mpll_divn
//  Input       : unsigned int ui_mpll_divn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_divnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.i_mpll_divn;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_i_mpll_fconSet
//  Description : Set the value of the member CTSET1.i_mpll_fcon
//  Input       : unsigned int ui_mpll_fcon: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_fconSet(unsigned int ui_mpll_fcon)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_ctset1.bits.i_mpll_fcon = ui_mpll_fcon;
    HDMI21TXRegWrite(pu32RegAddr, o_ctset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CTSET1_i_mpll_fconGet
//  Description : Set the value of the member CTSET1.i_mpll_fcon
//  Input       : unsigned int ui_mpll_fcon: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTSET1_i_mpll_fconGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTSET1 o_ctset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CTSET1.u32);
    o_ctset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_ctset1.bits.i_mpll_fcon;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_ref_cnt_lenSet
//  Description : Set the value of the member FCCNTR0.i_ref_cnt_len
//  Input       : unsigned int ui_ref_cnt_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_ref_cnt_lenSet(unsigned int ui_ref_cnt_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr0.bits.i_ref_cnt_len = ui_ref_cnt_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_ref_cnt_lenGet
//  Description : Set the value of the member FCCNTR0.i_ref_cnt_len
//  Input       : unsigned int ui_ref_cnt_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_ref_cnt_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_ref_cnt_len;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_vco_end_wait_lenSet
//  Description : Set the value of the member FCCNTR0.i_vco_end_wait_len
//  Input       : unsigned int ui_vco_end_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_end_wait_lenSet(unsigned int ui_vco_end_wait_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr0.bits.i_vco_end_wait_len = ui_vco_end_wait_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_vco_end_wait_lenGet
//  Description : Set the value of the member FCCNTR0.i_vco_end_wait_len
//  Input       : unsigned int ui_vco_end_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_end_wait_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_vco_end_wait_len;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_vco_st_wait_lenSet
//  Description : Set the value of the member FCCNTR0.i_vco_st_wait_len
//  Input       : unsigned int ui_vco_st_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_st_wait_lenSet(unsigned int ui_vco_st_wait_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr0.bits.i_vco_st_wait_len = ui_vco_st_wait_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_vco_st_wait_lenGet
//  Description : Set the value of the member FCCNTR0.i_vco_st_wait_len
//  Input       : unsigned int ui_vco_st_wait_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_vco_st_wait_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_vco_st_wait_len;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_deci_cnt_lenSet
//  Description : Set the value of the member FCCNTR0.i_deci_cnt_len
//  Input       : unsigned int ui_deci_cnt_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_deci_cnt_lenSet(unsigned int ui_deci_cnt_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr0.bits.i_deci_cnt_len = ui_deci_cnt_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR0_i_deci_cnt_lenGet
//  Description : Set the value of the member FCCNTR0.i_deci_cnt_len
//  Input       : unsigned int ui_deci_cnt_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR0_i_deci_cnt_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR0 o_fccntr0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR0.u32);
    o_fccntr0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr0.bits.i_deci_cnt_len;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_fcopt_unusedSet
//  Description : Set the value of the member FCOPT.fcopt_unused
//  Input       : unsigned int ufcopt_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unusedSet(unsigned int ufcopt_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.fcopt_unused = ufcopt_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_fcopt_unusedGet
//  Description : Set the value of the member FCOPT.fcopt_unused
//  Input       : unsigned int ufcopt_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.fcopt_unused;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_deci_try_selSet
//  Description : Set the value of the member FCOPT.i_deci_try_sel
//  Input       : unsigned int ui_deci_try_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_deci_try_selSet(unsigned int ui_deci_try_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_deci_try_sel = ui_deci_try_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_deci_try_selGet
//  Description : Set the value of the member FCOPT.i_deci_try_sel
//  Input       : unsigned int ui_deci_try_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_deci_try_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_deci_try_sel;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_idx_selSet
//  Description : Set the value of the member FCOPT.i_ct_idx_sel
//  Input       : unsigned int ui_ct_idx_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_idx_selSet(unsigned int ui_ct_idx_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_idx_sel = ui_ct_idx_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_idx_selGet
//  Description : Set the value of the member FCOPT.i_ct_idx_sel
//  Input       : unsigned int ui_ct_idx_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_idx_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_idx_sel;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_fcopt_unused_2Set
//  Description : Set the value of the member FCOPT.fcopt_unused_2
//  Input       : unsigned int ufcopt_unused_2: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_2Set(unsigned int ufcopt_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.fcopt_unused_2 = ufcopt_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_fcopt_unused_2Get
//  Description : Set the value of the member FCOPT.fcopt_unused_2
//  Input       : unsigned int ufcopt_unused_2: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.fcopt_unused_2;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_enSet
//  Description : Set the value of the member FCOPT.i_ct_en
//  Input       : unsigned int ui_ct_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_enSet(unsigned int ui_ct_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_en = ui_ct_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_enGet
//  Description : Set the value of the member FCOPT.i_ct_en
//  Input       : unsigned int ui_ct_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_en;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_fcopt_unused_1Set
//  Description : Set the value of the member FCOPT.fcopt_unused_1
//  Input       : unsigned int ufcopt_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_1Set(unsigned int ufcopt_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.fcopt_unused_1 = ufcopt_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_fcopt_unused_1Get
//  Description : Set the value of the member FCOPT.fcopt_unused_1
//  Input       : unsigned int ufcopt_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_fcopt_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.fcopt_unused_1;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_modeSet
//  Description : Set the value of the member FCOPT.i_ct_mode
//  Input       : unsigned int ui_ct_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_modeSet(unsigned int ui_ct_mode)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_mode = ui_ct_mode;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_modeGet
//  Description : Set the value of the member FCOPT.i_ct_mode
//  Input       : unsigned int ui_ct_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_mode;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_clkdet_selSet
//  Description : Set the value of the member FCOPT.i_clkdet_sel
//  Input       : unsigned int ui_clkdet_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_clkdet_selSet(unsigned int ui_clkdet_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_clkdet_sel = ui_clkdet_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_clkdet_selGet
//  Description : Set the value of the member FCOPT.i_clkdet_sel
//  Input       : unsigned int ui_clkdet_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_clkdet_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_clkdet_sel;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_selSet
//  Description : Set the value of the member FCOPT.i_ct_sel
//  Input       : unsigned int ui_ct_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_selSet(unsigned int ui_ct_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcopt.bits.i_ct_sel = ui_ct_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCOPT_i_ct_selGet
//  Description : Set the value of the member FCOPT.i_ct_sel
//  Input       : unsigned int ui_ct_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCOPT_i_ct_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCOPT o_fcopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCOPT.u32);
    o_fcopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcopt.bits.i_ct_sel;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcon_initSet
//  Description : Set the value of the member FCSTAT.fcon_init
//  Input       : unsigned int ufcon_init: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcon_initSet(unsigned int ufcon_init)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcon_init = ufcon_init;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcon_initGet
//  Description : Set the value of the member FCSTAT.fcon_init
//  Input       : unsigned int ufcon_init: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcon_initGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcon_init;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcstat_unused_3Set
//  Description : Set the value of the member FCSTAT.fcstat_unused_3
//  Input       : unsigned int ufcstat_unused_3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_3Set(unsigned int ufcstat_unused_3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcstat_unused_3 = ufcstat_unused_3;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcstat_unused_3Get
//  Description : Set the value of the member FCSTAT.fcstat_unused_3
//  Input       : unsigned int ufcstat_unused_3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcstat_unused_3;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_confin_statSet
//  Description : Set the value of the member FCSTAT.confin_stat
//  Input       : unsigned int uconfin_stat: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_confin_statSet(unsigned int uconfin_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.confin_stat = uconfin_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_confin_statGet
//  Description : Set the value of the member FCSTAT.confin_stat
//  Input       : unsigned int uconfin_stat: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_confin_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.confin_stat;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcstat_unused_2Set
//  Description : Set the value of the member FCSTAT.fcstat_unused_2
//  Input       : unsigned int ufcstat_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_2Set(unsigned int ufcstat_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcstat_unused_2 = ufcstat_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcstat_unused_2Get
//  Description : Set the value of the member FCSTAT.fcstat_unused_2
//  Input       : unsigned int ufcstat_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcstat_unused_2;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_pllvco_clk_statSet
//  Description : Set the value of the member FCSTAT.pllvco_clk_stat
//  Input       : unsigned int upllvco_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_pllvco_clk_statSet(unsigned int upllvco_clk_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.pllvco_clk_stat = upllvco_clk_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_pllvco_clk_statGet
//  Description : Set the value of the member FCSTAT.pllvco_clk_stat
//  Input       : unsigned int upllvco_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_pllvco_clk_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.pllvco_clk_stat;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_ref_clk_statSet
//  Description : Set the value of the member FCSTAT.ref_clk_stat
//  Input       : unsigned int uref_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_ref_clk_statSet(unsigned int uref_clk_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.ref_clk_stat = uref_clk_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_ref_clk_statGet
//  Description : Set the value of the member FCSTAT.ref_clk_stat
//  Input       : unsigned int uref_clk_stat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_ref_clk_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.ref_clk_stat;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcstat_unused_1Set
//  Description : Set the value of the member FCSTAT.fcstat_unused_1
//  Input       : unsigned int ufcstat_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_1Set(unsigned int ufcstat_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.fcstat_unused_1 = ufcstat_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_fcstat_unused_1Get
//  Description : Set the value of the member FCSTAT.fcstat_unused_1
//  Input       : unsigned int ufcstat_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_fcstat_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.fcstat_unused_1;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_divnSet
//  Description : Set the value of the member FCSTAT.divn
//  Input       : unsigned int udivn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_divnSet(unsigned int udivn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.divn = udivn;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_divnGet
//  Description : Set the value of the member FCSTAT.divn
//  Input       : unsigned int udivn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_divnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.divn;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_errorSet
//  Description : Set the value of the member FCSTAT.error
//  Input       : unsigned int uerror: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_errorSet(unsigned int uerror)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.error = uerror;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_errorGet
//  Description : Set the value of the member FCSTAT.error
//  Input       : unsigned int uerror: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_errorGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.error;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_doneSet
//  Description : Set the value of the member FCSTAT.done
//  Input       : unsigned int udone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_doneSet(unsigned int udone)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.done = udone;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_doneGet
//  Description : Set the value of the member FCSTAT.done
//  Input       : unsigned int udone: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.done;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_busySet
//  Description : Set the value of the member FCSTAT.busy
//  Input       : unsigned int ubusy: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_busySet(unsigned int ubusy)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.busy = ubusy;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_busyGet
//  Description : Set the value of the member FCSTAT.busy
//  Input       : unsigned int ubusy: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_busyGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.busy;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_clk_okSet
//  Description : Set the value of the member FCSTAT.clk_ok
//  Input       : unsigned int uclk_ok: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_clk_okSet(unsigned int uclk_ok)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcstat.bits.clk_ok = uclk_ok;
    HDMI21TXRegWrite(pu32RegAddr, o_fcstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCSTAT_clk_okGet
//  Description : Set the value of the member FCSTAT.clk_ok
//  Input       : unsigned int uclk_ok: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCSTAT_clk_okGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCSTAT o_fcstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCSTAT.u32);
    o_fcstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcstat.bits.clk_ok;
}

//******************************************************************************
//  Function    : HDMI_FCCNTVAL0_o_cnt_refSet
//  Description : Set the value of the member FCCNTVAL0.o_cnt_ref
//  Input       : unsigned int uo_cnt_ref: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL0_o_cnt_refSet(unsigned int uo_cnt_ref)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL0 o_fccntval0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTVAL0.u32);
    o_fccntval0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntval0.bits.o_cnt_ref = uo_cnt_ref;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntval0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCNTVAL0_o_cnt_refGet
//  Description : Set the value of the member FCCNTVAL0.o_cnt_ref
//  Input       : unsigned int uo_cnt_ref: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL0_o_cnt_refGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL0 o_fccntval0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTVAL0.u32);
    o_fccntval0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntval0.bits.o_cnt_ref;
}

//******************************************************************************
//  Function    : HDMI_FCCNTVAL1_o_cnt_mpllSet
//  Description : Set the value of the member FCCNTVAL1.o_cnt_mpll
//  Input       : unsigned int uo_cnt_mpll: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL1_o_cnt_mpllSet(unsigned int uo_cnt_mpll)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL1 o_fccntval1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTVAL1.u32);
    o_fccntval1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntval1.bits.o_cnt_mpll = uo_cnt_mpll;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntval1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCNTVAL1_o_cnt_mpllGet
//  Description : Set the value of the member FCCNTVAL1.o_cnt_mpll
//  Input       : unsigned int uo_cnt_mpll: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTVAL1_o_cnt_mpllGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTVAL1 o_fccntval1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTVAL1.u32);
    o_fccntval1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntval1.bits.o_cnt_mpll;
}

//******************************************************************************
//  Function    : HDMI_FCRESVAL_o_fcon_mpllSet
//  Description : Set the value of the member FCRESVAL.o_fcon_mpll
//  Input       : unsigned int uo_fcon_mpll: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_fcon_mpllSet(unsigned int uo_fcon_mpll)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcresval.bits.o_fcon_mpll = uo_fcon_mpll;
    HDMI21TXRegWrite(pu32RegAddr, o_fcresval.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCRESVAL_o_fcon_mpllGet
//  Description : Set the value of the member FCRESVAL.o_fcon_mpll
//  Input       : unsigned int uo_fcon_mpll: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_fcon_mpllGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcresval.bits.o_fcon_mpll;
}

//******************************************************************************
//  Function    : HDMI_FCRESVAL_fcresval_unusedSet
//  Description : Set the value of the member FCRESVAL.fcresval_unused
//  Input       : unsigned int ufcresval_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_fcresval_unusedSet(unsigned int ufcresval_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcresval.bits.fcresval_unused = ufcresval_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fcresval.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCRESVAL_fcresval_unusedGet
//  Description : Set the value of the member FCRESVAL.fcresval_unused
//  Input       : unsigned int ufcresval_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_fcresval_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcresval.bits.fcresval_unused;
}

//******************************************************************************
//  Function    : HDMI_FCRESVAL_o_divn_mpllSet
//  Description : Set the value of the member FCRESVAL.o_divn_mpll
//  Input       : unsigned int uo_divn_mpll: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_divn_mpllSet(unsigned int uo_divn_mpll)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcresval.bits.o_divn_mpll = uo_divn_mpll;
    HDMI21TXRegWrite(pu32RegAddr, o_fcresval.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCRESVAL_o_divn_mpllGet
//  Description : Set the value of the member FCRESVAL.o_divn_mpll
//  Input       : unsigned int uo_divn_mpll: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCRESVAL_o_divn_mpllGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCRESVAL o_fcresval;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCRESVAL.u32);
    o_fcresval.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcresval.bits.o_divn_mpll;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPSET_up_sampler_ratio_selSet
//  Description : Set the value of the member FCDSTEPSET.up_sampler_ratio_sel
//  Input       : unsigned int uup_sampler_ratio_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_up_sampler_ratio_selSet(unsigned int uup_sampler_ratio_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepset.bits.up_sampler_ratio_sel = uup_sampler_ratio_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPSET_up_sampler_ratio_selGet
//  Description : Set the value of the member FCDSTEPSET.up_sampler_ratio_sel
//  Input       : unsigned int uup_sampler_ratio_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_up_sampler_ratio_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepset.bits.up_sampler_ratio_sel;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPSET_fcdstepset_unusedSet
//  Description : Set the value of the member FCDSTEPSET.fcdstepset_unused
//  Input       : unsigned int ufcdstepset_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_fcdstepset_unusedSet(unsigned int ufcdstepset_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepset.bits.fcdstepset_unused = ufcdstepset_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPSET_fcdstepset_unusedGet
//  Description : Set the value of the member FCDSTEPSET.fcdstepset_unused
//  Input       : unsigned int ufcdstepset_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_fcdstepset_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepset.bits.fcdstepset_unused;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPSET_p_divn_h20Set
//  Description : Set the value of the member FCDSTEPSET.p_divn_h20
//  Input       : unsigned int up_divn_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_p_divn_h20Set(unsigned int up_divn_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepset.bits.p_divn_h20 = up_divn_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPSET_p_divn_h20Get
//  Description : Set the value of the member FCDSTEPSET.p_divn_h20
//  Input       : unsigned int up_divn_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPSET_p_divn_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPSET o_fcdstepset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPSET.u32);
    o_fcdstepset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepset.bits.p_divn_h20;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH_i_deci_selSet
//  Description : Set the value of the member FCDSTEPTH.i_deci_sel
//  Input       : unsigned int ui_deci_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_deci_selSet(unsigned int ui_deci_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth.bits.i_deci_sel = ui_deci_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH_i_deci_selGet
//  Description : Set the value of the member FCDSTEPTH.i_deci_sel
//  Input       : unsigned int ui_deci_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_deci_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth.bits.i_deci_sel;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH_i_h2_selSet
//  Description : Set the value of the member FCDSTEPTH.i_h2_sel
//  Input       : unsigned int ui_h2_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_h2_selSet(unsigned int ui_h2_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth.bits.i_h2_sel = ui_h2_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH_i_h2_selGet
//  Description : Set the value of the member FCDSTEPTH.i_h2_sel
//  Input       : unsigned int ui_h2_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH_i_h2_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH o_fcdstepth;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH.u32);
    o_fcdstepth.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth.bits.i_h2_sel;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH0_i_deci4x_thSet
//  Description : Set the value of the member FCDSTEPTH0.i_deci4x_th
//  Input       : unsigned int ui_deci4x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci4x_thSet(unsigned int ui_deci4x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth0.bits.i_deci4x_th = ui_deci4x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH0_i_deci4x_thGet
//  Description : Set the value of the member FCDSTEPTH0.i_deci4x_th
//  Input       : unsigned int ui_deci4x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci4x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth0.bits.i_deci4x_th;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH0_i_deci2x_thSet
//  Description : Set the value of the member FCDSTEPTH0.i_deci2x_th
//  Input       : unsigned int ui_deci2x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci2x_thSet(unsigned int ui_deci2x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth0.bits.i_deci2x_th = ui_deci2x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH0_i_deci2x_thGet
//  Description : Set the value of the member FCDSTEPTH0.i_deci2x_th
//  Input       : unsigned int ui_deci2x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH0_i_deci2x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH0 o_fcdstepth0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH0.u32);
    o_fcdstepth0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth0.bits.i_deci2x_th;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH1_i_deci16x_thSet
//  Description : Set the value of the member FCDSTEPTH1.i_deci16x_th
//  Input       : unsigned int ui_deci16x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci16x_thSet(unsigned int ui_deci16x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth1.bits.i_deci16x_th = ui_deci16x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH1_i_deci16x_thGet
//  Description : Set the value of the member FCDSTEPTH1.i_deci16x_th
//  Input       : unsigned int ui_deci16x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci16x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth1.bits.i_deci16x_th;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH1_i_deci8x_thSet
//  Description : Set the value of the member FCDSTEPTH1.i_deci8x_th
//  Input       : unsigned int ui_deci8x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci8x_thSet(unsigned int ui_deci8x_th)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fcdstepth1.bits.i_deci8x_th = ui_deci8x_th;
    HDMI21TXRegWrite(pu32RegAddr, o_fcdstepth1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCDSTEPTH1_i_deci8x_thGet
//  Description : Set the value of the member FCDSTEPTH1.i_deci8x_th
//  Input       : unsigned int ui_deci8x_th: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCDSTEPTH1_i_deci8x_thGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCDSTEPTH1 o_fcdstepth1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCDSTEPTH1.u32);
    o_fcdstepth1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fcdstepth1.bits.i_deci8x_th;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR1_i_ref_cntSet
//  Description : Set the value of the member FCCNTR1.i_ref_cnt
//  Input       : unsigned int ui_ref_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR1_i_ref_cntSet(unsigned int ui_ref_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR1 o_fccntr1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR1.u32);
    o_fccntr1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccntr1.bits.i_ref_cnt = ui_ref_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fccntr1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCNTR1_i_ref_cntGet
//  Description : Set the value of the member FCCNTR1.i_ref_cnt
//  Input       : unsigned int ui_ref_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCNTR1_i_ref_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCNTR1 o_fccntr1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCNTR1.u32);
    o_fccntr1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccntr1.bits.i_ref_cnt;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_stepSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_step
//  Input       : unsigned int up_contin_upd_step: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_stepSet(unsigned int up_contin_upd_step)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_step = up_contin_upd_step;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_stepGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_step
//  Input       : unsigned int up_contin_upd_step: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_stepGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_step;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_fccontinset0_unusedSet
//  Description : Set the value of the member FCCONTINSET0.fccontinset0_unused
//  Input       : unsigned int ufccontinset0_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_fccontinset0_unusedSet(unsigned int ufccontinset0_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.fccontinset0_unused = ufccontinset0_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_fccontinset0_unusedGet
//  Description : Set the value of the member FCCONTINSET0.fccontinset0_unused
//  Input       : unsigned int ufccontinset0_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_fccontinset0_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.fccontinset0_unused;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_polSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_pol
//  Input       : unsigned int up_contin_upd_pol: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_polSet(unsigned int up_contin_upd_pol)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_pol = up_contin_upd_pol;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_polGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_pol
//  Input       : unsigned int up_contin_upd_pol: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_polGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_pol;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_optSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_opt
//  Input       : unsigned int up_contin_upd_opt: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_optSet(unsigned int up_contin_upd_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_opt = up_contin_upd_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_optGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_opt
//  Input       : unsigned int up_contin_upd_opt: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_opt;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_enSet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_en
//  Input       : unsigned int up_contin_upd_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_enSet(unsigned int up_contin_upd_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset0.bits.p_contin_upd_en = up_contin_upd_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET0_p_contin_upd_enGet
//  Description : Set the value of the member FCCONTINSET0.p_contin_upd_en
//  Input       : unsigned int up_contin_upd_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET0_p_contin_upd_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET0 o_fccontinset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET0.u32);
    o_fccontinset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset0.bits.p_contin_upd_en;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET1_p_contin_upd_timeSet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_time
//  Input       : unsigned int up_contin_upd_time: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_timeSet(unsigned int up_contin_upd_time)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset1.bits.p_contin_upd_time = up_contin_upd_time;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET1_p_contin_upd_timeGet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_time
//  Input       : unsigned int up_contin_upd_time: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_timeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset1.bits.p_contin_upd_time;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET1_p_contin_upd_rateSet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_rate
//  Input       : unsigned int up_contin_upd_rate: 28 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_rateSet(unsigned int up_contin_upd_rate)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset1.bits.p_contin_upd_rate = up_contin_upd_rate;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET1_p_contin_upd_rateGet
//  Description : Set the value of the member FCCONTINSET1.p_contin_upd_rate
//  Input       : unsigned int up_contin_upd_rate: 28 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET1_p_contin_upd_rateGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET1 o_fccontinset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET1.u32);
    o_fccontinset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset1.bits.p_contin_upd_rate;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET2_p_contin_upd_th_upSet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_up
//  Input       : unsigned int up_contin_upd_th_up: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_upSet(unsigned int up_contin_upd_th_up)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset2.bits.p_contin_upd_th_up = up_contin_upd_th_up;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET2_p_contin_upd_th_upGet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_up
//  Input       : unsigned int up_contin_upd_th_up: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_upGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset2.bits.p_contin_upd_th_up;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET2_fccontinset2_unusedSet
//  Description : Set the value of the member FCCONTINSET2.fccontinset2_unused
//  Input       : unsigned int ufccontinset2_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_fccontinset2_unusedSet(unsigned int ufccontinset2_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset2.bits.fccontinset2_unused = ufccontinset2_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET2_fccontinset2_unusedGet
//  Description : Set the value of the member FCCONTINSET2.fccontinset2_unused
//  Input       : unsigned int ufccontinset2_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_fccontinset2_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset2.bits.fccontinset2_unused;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET2_p_contin_upd_th_dnSet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_dn
//  Input       : unsigned int up_contin_upd_th_dn: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_dnSet(unsigned int up_contin_upd_th_dn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fccontinset2.bits.p_contin_upd_th_dn = up_contin_upd_th_dn;
    HDMI21TXRegWrite(pu32RegAddr, o_fccontinset2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FCCONTINSET2_p_contin_upd_th_dnGet
//  Description : Set the value of the member FCCONTINSET2.p_contin_upd_th_dn
//  Input       : unsigned int up_contin_upd_th_dn: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FCCONTINSET2_p_contin_upd_th_dnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FCCONTINSET2 o_fccontinset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FCCONTINSET2.u32);
    o_fccontinset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fccontinset2.bits.p_contin_upd_th_dn;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_en_sdmSet
//  Description : Set the value of the member FDIVSET0.en_sdm
//  Input       : unsigned int uen_sdm: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_sdmSet(unsigned int uen_sdm)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.en_sdm = uen_sdm;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_en_sdmGet
//  Description : Set the value of the member FDIVSET0.en_sdm
//  Input       : unsigned int uen_sdm: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_sdmGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.en_sdm;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_en_modSet
//  Description : Set the value of the member FDIVSET0.en_mod
//  Input       : unsigned int uen_mod: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_modSet(unsigned int uen_mod)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.en_mod = uen_mod;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_en_modGet
//  Description : Set the value of the member FDIVSET0.en_mod
//  Input       : unsigned int uen_mod: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_modGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.en_mod;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_en_ctrlSet
//  Description : Set the value of the member FDIVSET0.en_ctrl
//  Input       : unsigned int uen_ctrl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_ctrlSet(unsigned int uen_ctrl)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.en_ctrl = uen_ctrl;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_en_ctrlGet
//  Description : Set the value of the member FDIVSET0.en_ctrl
//  Input       : unsigned int uen_ctrl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_en_ctrlGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.en_ctrl;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_initSet
//  Description : Set the value of the member FDIVSET0.init
//  Input       : unsigned int uinit: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_initSet(unsigned int uinit)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset0.bits.init = uinit;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET0_initGet
//  Description : Set the value of the member FDIVSET0.init
//  Input       : unsigned int uinit: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET0_initGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET0 o_fdivset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET0.u32);
    o_fdivset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset0.bits.init;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET1_step_nSet
//  Description : Set the value of the member FDIVSET1.step_n
//  Input       : unsigned int ustep_n: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_nSet(unsigned int ustep_n)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset1.bits.step_n = ustep_n;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET1_step_nGet
//  Description : Set the value of the member FDIVSET1.step_n
//  Input       : unsigned int ustep_n: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_nGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset1.bits.step_n;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET1_step_tSet
//  Description : Set the value of the member FDIVSET1.step_t
//  Input       : unsigned int ustep_t: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_tSet(unsigned int ustep_t)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset1.bits.step_t = ustep_t;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET1_step_tGet
//  Description : Set the value of the member FDIVSET1.step_t
//  Input       : unsigned int ustep_t: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_tGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset1.bits.step_t;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET1_step_dSet
//  Description : Set the value of the member FDIVSET1.step_d
//  Input       : unsigned int ustep_d: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_dSet(unsigned int ustep_d)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset1.bits.step_d = ustep_d;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET1_step_dGet
//  Description : Set the value of the member FDIVSET1.step_d
//  Input       : unsigned int ustep_d: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET1_step_dGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET1 o_fdivset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET1.u32);
    o_fdivset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset1.bits.step_d;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET2_dnSet
//  Description : Set the value of the member FDIVSET2.dn
//  Input       : unsigned int udn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_dnSet(unsigned int udn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset2.bits.dn = udn;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET2_dnGet
//  Description : Set the value of the member FDIVSET2.dn
//  Input       : unsigned int udn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_dnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset2.bits.dn;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET2_upSet
//  Description : Set the value of the member FDIVSET2.up
//  Input       : unsigned int uup: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_upSet(unsigned int uup)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset2.bits.up = uup;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET2_upGet
//  Description : Set the value of the member FDIVSET2.up
//  Input       : unsigned int uup: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET2_upGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET2 o_fdivset2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET2.u32);
    o_fdivset2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset2.bits.up;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET3_mod_nSet
//  Description : Set the value of the member FDIVSET3.mod_n
//  Input       : unsigned int umod_n: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_nSet(unsigned int umod_n)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset3.bits.mod_n = umod_n;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET3_mod_nGet
//  Description : Set the value of the member FDIVSET3.mod_n
//  Input       : unsigned int umod_n: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_nGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset3.bits.mod_n;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET3_mod_tSet
//  Description : Set the value of the member FDIVSET3.mod_t
//  Input       : unsigned int umod_t: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_tSet(unsigned int umod_t)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset3.bits.mod_t = umod_t;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET3_mod_tGet
//  Description : Set the value of the member FDIVSET3.mod_t
//  Input       : unsigned int umod_t: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_tGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset3.bits.mod_t;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET3_mod_lenSet
//  Description : Set the value of the member FDIVSET3.mod_len
//  Input       : unsigned int umod_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_lenSet(unsigned int umod_len)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset3.bits.mod_len = umod_len;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET3_mod_lenGet
//  Description : Set the value of the member FDIVSET3.mod_len
//  Input       : unsigned int umod_len: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET3_mod_lenGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET3 o_fdivset3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET3.u32);
    o_fdivset3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset3.bits.mod_len;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET4_mod_dSet
//  Description : Set the value of the member FDIVSET4.mod_d
//  Input       : unsigned int umod_d: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET4_mod_dSet(unsigned int umod_d)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET4 o_fdivset4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET4.u32);
    o_fdivset4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset4.bits.mod_d = umod_d;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET4_mod_dGet
//  Description : Set the value of the member FDIVSET4.mod_d
//  Input       : unsigned int umod_d: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET4_mod_dGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET4 o_fdivset4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET4.u32);
    o_fdivset4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset4.bits.mod_d;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET5_fdivset5_unusedSet
//  Description : Set the value of the member FDIVSET5.fdivset5_unused
//  Input       : unsigned int ufdivset5_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_fdivset5_unusedSet(unsigned int ufdivset5_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset5.bits.fdivset5_unused = ufdivset5_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset5.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET5_fdivset5_unusedGet
//  Description : Set the value of the member FDIVSET5.fdivset5_unused
//  Input       : unsigned int ufdivset5_unused: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_fdivset5_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset5.bits.fdivset5_unused;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET5_p_mod_dnSet
//  Description : Set the value of the member FDIVSET5.p_mod_dn
//  Input       : unsigned int up_mod_dn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_dnSet(unsigned int up_mod_dn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset5.bits.p_mod_dn = up_mod_dn;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset5.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET5_p_mod_dnGet
//  Description : Set the value of the member FDIVSET5.p_mod_dn
//  Input       : unsigned int up_mod_dn: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_dnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset5.bits.p_mod_dn;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET5_p_mod_upSet
//  Description : Set the value of the member FDIVSET5.p_mod_up
//  Input       : unsigned int up_mod_up: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_upSet(unsigned int up_mod_up)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivset5.bits.p_mod_up = up_mod_up;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivset5.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSET5_p_mod_upGet
//  Description : Set the value of the member FDIVSET5.p_mod_up
//  Input       : unsigned int up_mod_up: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSET5_p_mod_upGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSET5 o_fdivset5;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSET5.u32);
    o_fdivset5.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivset5.bits.p_mod_up;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_cntSet
//  Description : Set the value of the member FDIVSTAT0.stc_cnt
//  Input       : unsigned int ustc_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_cntSet(unsigned int ustc_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_cnt = ustc_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_cntGet
//  Description : Set the value of the member FDIVSTAT0.stc_cnt
//  Input       : unsigned int ustc_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_cnt;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_unSet
//  Description : Set the value of the member FDIVSTAT0.stc_un
//  Input       : unsigned int ustc_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_unSet(unsigned int ustc_un)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_un = ustc_un;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_unGet
//  Description : Set the value of the member FDIVSTAT0.stc_un
//  Input       : unsigned int ustc_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_unGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_un;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_ovSet
//  Description : Set the value of the member FDIVSTAT0.stc_ov
//  Input       : unsigned int ustc_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_ovSet(unsigned int ustc_ov)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_ov = ustc_ov;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_ovGet
//  Description : Set the value of the member FDIVSTAT0.stc_ov
//  Input       : unsigned int ustc_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_ovGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_ov;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_dirSet
//  Description : Set the value of the member FDIVSTAT0.stc_dir
//  Input       : unsigned int ustc_dir: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_dirSet(unsigned int ustc_dir)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_dir = ustc_dir;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_dirGet
//  Description : Set the value of the member FDIVSTAT0.stc_dir
//  Input       : unsigned int ustc_dir: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_dirGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_dir;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_runSet
//  Description : Set the value of the member FDIVSTAT0.stc_run
//  Input       : unsigned int ustc_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_runSet(unsigned int ustc_run)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat0.bits.stc_run = ustc_run;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT0_stc_runGet
//  Description : Set the value of the member FDIVSTAT0.stc_run
//  Input       : unsigned int ustc_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT0_stc_runGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT0 o_fdivstat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT0.u32);
    o_fdivstat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat0.bits.stc_run;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT1_i_fdiv_inSet
//  Description : Set the value of the member FDIVSTAT1.i_fdiv_in
//  Input       : unsigned int ui_fdiv_in: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT1_i_fdiv_inSet(unsigned int ui_fdiv_in)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT1 o_fdivstat1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT1.u32);
    o_fdivstat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat1.bits.i_fdiv_in = ui_fdiv_in;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT1_i_fdiv_inGet
//  Description : Set the value of the member FDIVSTAT1.i_fdiv_in
//  Input       : unsigned int ui_fdiv_in: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT1_i_fdiv_inGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT1 o_fdivstat1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT1.u32);
    o_fdivstat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat1.bits.i_fdiv_in;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT2_div_outSet
//  Description : Set the value of the member FDIVSTAT2.div_out
//  Input       : unsigned int udiv_out: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT2_div_outSet(unsigned int udiv_out)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT2 o_fdivstat2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT2.u32);
    o_fdivstat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat2.bits.div_out = udiv_out;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT2_div_outGet
//  Description : Set the value of the member FDIVSTAT2.div_out
//  Input       : unsigned int udiv_out: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT2_div_outGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT2 o_fdivstat2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT2.u32);
    o_fdivstat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat2.bits.div_out;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT3_div_sdmSet
//  Description : Set the value of the member FDIVSTAT3.div_sdm
//  Input       : unsigned int udiv_sdm: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT3_div_sdmSet(unsigned int udiv_sdm)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT3 o_fdivstat3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT3.u32);
    o_fdivstat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat3.bits.div_sdm = udiv_sdm;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT3_div_sdmGet
//  Description : Set the value of the member FDIVSTAT3.div_sdm
//  Input       : unsigned int udiv_sdm: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT3_div_sdmGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT3 o_fdivstat3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT3.u32);
    o_fdivstat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat3.bits.div_sdm;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_cntSet
//  Description : Set the value of the member FDIVSTAT4.stm_cnt
//  Input       : unsigned int ustm_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_cntSet(unsigned int ustm_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_cnt = ustm_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_cntGet
//  Description : Set the value of the member FDIVSTAT4.stm_cnt
//  Input       : unsigned int ustm_cnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_cnt;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_fdivstat4_unusedSet
//  Description : Set the value of the member FDIVSTAT4.fdivstat4_unused
//  Input       : unsigned int ufdivstat4_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_fdivstat4_unusedSet(unsigned int ufdivstat4_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.fdivstat4_unused = ufdivstat4_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_fdivstat4_unusedGet
//  Description : Set the value of the member FDIVSTAT4.fdivstat4_unused
//  Input       : unsigned int ufdivstat4_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_fdivstat4_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.fdivstat4_unused;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_unSet
//  Description : Set the value of the member FDIVSTAT4.stm_un
//  Input       : unsigned int ustm_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_unSet(unsigned int ustm_un)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_un = ustm_un;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_unGet
//  Description : Set the value of the member FDIVSTAT4.stm_un
//  Input       : unsigned int ustm_un: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_unGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_un;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_ovSet
//  Description : Set the value of the member FDIVSTAT4.stm_ov
//  Input       : unsigned int ustm_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_ovSet(unsigned int ustm_ov)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_ov = ustm_ov;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_ovGet
//  Description : Set the value of the member FDIVSTAT4.stm_ov
//  Input       : unsigned int ustm_ov: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_ovGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_ov;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_phSet
//  Description : Set the value of the member FDIVSTAT4.stm_ph
//  Input       : unsigned int ustm_ph: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_phSet(unsigned int ustm_ph)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_ph = ustm_ph;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_phGet
//  Description : Set the value of the member FDIVSTAT4.stm_ph
//  Input       : unsigned int ustm_ph: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_phGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_ph;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_runSet
//  Description : Set the value of the member FDIVSTAT4.stm_run
//  Input       : unsigned int ustm_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_runSet(unsigned int ustm_run)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivstat4.bits.stm_run = ustm_run;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivstat4.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVSTAT4_stm_runGet
//  Description : Set the value of the member FDIVSTAT4.stm_run
//  Input       : unsigned int ustm_run: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVSTAT4_stm_runGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVSTAT4 o_fdivstat4;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVSTAT4.u32);
    o_fdivstat4.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivstat4.bits.stm_run;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_vicSet
//  Description : Set the value of the member FDIVMANUAL.i_vic
//  Input       : unsigned int ui_vic: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_vicSet(unsigned int ui_vic)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_vic = ui_vic;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_vicGet
//  Description : Set the value of the member FDIVMANUAL.i_vic
//  Input       : unsigned int ui_vic: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_vicGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_vic;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_dc_selSet
//  Description : Set the value of the member FDIVMANUAL.i_dc_sel
//  Input       : unsigned int ui_dc_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_dc_selSet(unsigned int ui_dc_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_dc_sel = ui_dc_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_dc_selGet
//  Description : Set the value of the member FDIVMANUAL.i_dc_sel
//  Input       : unsigned int ui_dc_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_dc_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_dc_sel;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_ref_cnt_divSet
//  Description : Set the value of the member FDIVMANUAL.i_ref_cnt_div
//  Input       : unsigned int ui_ref_cnt_div: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_ref_cnt_divSet(unsigned int ui_ref_cnt_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_ref_cnt_div = ui_ref_cnt_div;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_ref_cnt_divGet
//  Description : Set the value of the member FDIVMANUAL.i_ref_cnt_div
//  Input       : unsigned int ui_ref_cnt_div: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_ref_cnt_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_ref_cnt_div;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_mdivSet
//  Description : Set the value of the member FDIVMANUAL.i_mdiv
//  Input       : unsigned int ui_mdiv: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_mdivSet(unsigned int ui_mdiv)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_mdiv = ui_mdiv;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_mdivGet
//  Description : Set the value of the member FDIVMANUAL.i_mdiv
//  Input       : unsigned int ui_mdiv: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_mdivGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_mdiv;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_fdivmanual_unusedSet
//  Description : Set the value of the member FDIVMANUAL.fdivmanual_unused
//  Input       : unsigned int ufdivmanual_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_fdivmanual_unusedSet(unsigned int ufdivmanual_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.fdivmanual_unused = ufdivmanual_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_fdivmanual_unusedGet
//  Description : Set the value of the member FDIVMANUAL.fdivmanual_unused
//  Input       : unsigned int ufdivmanual_unused: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_fdivmanual_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.fdivmanual_unused;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_divnSet
//  Description : Set the value of the member FDIVMANUAL.i_divn
//  Input       : unsigned int ui_divn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_divnSet(unsigned int ui_divn)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_divn = ui_divn;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_divnGet
//  Description : Set the value of the member FDIVMANUAL.i_divn
//  Input       : unsigned int ui_divn: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_divnGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_divn;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_manual_enSet
//  Description : Set the value of the member FDIVMANUAL.i_manual_en
//  Input       : unsigned int ui_manual_en: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_manual_enSet(unsigned int ui_manual_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdivmanual.bits.i_manual_en = ui_manual_en;
    HDMI21TXRegWrite(pu32RegAddr, o_fdivmanual.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDIVMANUAL_i_manual_enGet
//  Description : Set the value of the member FDIVMANUAL.i_manual_en
//  Input       : unsigned int ui_manual_en: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDIVMANUAL_i_manual_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDIVMANUAL o_fdivmanual;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDIVMANUAL.u32);
    o_fdivmanual.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdivmanual.bits.i_manual_en;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_p_pr_enc_valSet
//  Description : Set the value of the member REFCLKSEL.p_pr_enc_val
//  Input       : unsigned int up_pr_enc_val: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_p_pr_enc_valSet(unsigned int up_pr_enc_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.p_pr_enc_val = up_pr_enc_val;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_p_pr_enc_valGet
//  Description : Set the value of the member REFCLKSEL.p_pr_enc_val
//  Input       : unsigned int up_pr_enc_val: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_p_pr_enc_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.p_pr_enc_val;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_refclksel_unused_2Set
//  Description : Set the value of the member REFCLKSEL.refclksel_unused_2
//  Input       : unsigned int urefclksel_unused_2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_refclksel_unused_2Set(unsigned int urefclksel_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.refclksel_unused_2 = urefclksel_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_refclksel_unused_2Get
//  Description : Set the value of the member REFCLKSEL.refclksel_unused_2
//  Input       : unsigned int urefclksel_unused_2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_refclksel_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.refclksel_unused_2;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_t2_pixelclkselSet
//  Description : Set the value of the member REFCLKSEL.t2_pixelclksel
//  Input       : unsigned int ut2_pixelclksel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_pixelclkselSet(unsigned int ut2_pixelclksel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.t2_pixelclksel = ut2_pixelclksel;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_t2_pixelclkselGet
//  Description : Set the value of the member REFCLKSEL.t2_pixelclksel
//  Input       : unsigned int ut2_pixelclksel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_pixelclkselGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.t2_pixelclksel;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_refclksel_unused_1Set
//  Description : Set the value of the member REFCLKSEL.refclksel_unused_1
//  Input       : unsigned int urefclksel_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_refclksel_unused_1Set(unsigned int urefclksel_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.refclksel_unused_1 = urefclksel_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_refclksel_unused_1Get
//  Description : Set the value of the member REFCLKSEL.refclksel_unused_1
//  Input       : unsigned int urefclksel_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_refclksel_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.refclksel_unused_1;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_i_ref_clk_selSet
//  Description : Set the value of the member REFCLKSEL.i_ref_clk_sel
//  Input       : unsigned int ui_ref_clk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_i_ref_clk_selSet(unsigned int ui_ref_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.i_ref_clk_sel = ui_ref_clk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_i_ref_clk_selGet
//  Description : Set the value of the member REFCLKSEL.i_ref_clk_sel
//  Input       : unsigned int ui_ref_clk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_i_ref_clk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.i_ref_clk_sel;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_t2_refclksel2Set
//  Description : Set the value of the member REFCLKSEL.t2_refclksel2
//  Input       : unsigned int ut2_refclksel2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_refclksel2Set(unsigned int ut2_refclksel2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.t2_refclksel2 = ut2_refclksel2;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_t2_refclksel2Get
//  Description : Set the value of the member REFCLKSEL.t2_refclksel2
//  Input       : unsigned int ut2_refclksel2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_refclksel2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.t2_refclksel2;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_t2_refclkselSet
//  Description : Set the value of the member REFCLKSEL.t2_refclksel
//  Input       : unsigned int ut2_refclksel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_refclkselSet(unsigned int ut2_refclksel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_refclksel.bits.t2_refclksel = ut2_refclksel;
    HDMI21TXRegWrite(pu32RegAddr, o_refclksel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REFCLKSEL_t2_refclkselGet
//  Description : Set the value of the member REFCLKSEL.t2_refclksel
//  Input       : unsigned int ut2_refclksel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REFCLKSEL_t2_refclkselGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_REFCLKSEL o_refclksel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->REFCLKSEL.u32);
    o_refclksel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_refclksel.bits.t2_refclksel;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_fdpllparam_unusedSet
//  Description : Set the value of the member FDPLLPARAM.fdpllparam_unused
//  Input       : unsigned int ufdpllparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_fdpllparam_unusedSet(unsigned int ufdpllparam_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.fdpllparam_unused = ufdpllparam_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_fdpllparam_unusedGet
//  Description : Set the value of the member FDPLLPARAM.fdpllparam_unused
//  Input       : unsigned int ufdpllparam_unused: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_fdpllparam_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.fdpllparam_unused;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_pll_enableSet
//  Description : Set the value of the member FDPLLPARAM.pll_enable
//  Input       : unsigned int upll_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_enableSet(unsigned int upll_enable)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.pll_enable = upll_enable;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_pll_enableGet
//  Description : Set the value of the member FDPLLPARAM.pll_enable
//  Input       : unsigned int upll_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_enableGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.pll_enable;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_pll_lock_cntSet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_cnt
//  Input       : unsigned int upll_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_cntSet(unsigned int upll_lock_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.pll_lock_cnt = upll_lock_cnt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_pll_lock_cntGet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_cnt
//  Input       : unsigned int upll_lock_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.pll_lock_cnt;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_pll_lock_valSet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_val
//  Input       : unsigned int upll_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_valSet(unsigned int upll_lock_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllparam.bits.pll_lock_val = upll_lock_val;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllparam.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLPARAM_pll_lock_valGet
//  Description : Set the value of the member FDPLLPARAM.pll_lock_val
//  Input       : unsigned int upll_lock_val: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLPARAM_pll_lock_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLPARAM o_fdpllparam;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLPARAM.u32);
    o_fdpllparam.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllparam.bits.pll_lock_val;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_pll_freq_extSet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_ext
//  Input       : unsigned int upll_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_extSet(unsigned int upll_freq_ext)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.pll_freq_ext = upll_freq_ext;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_pll_freq_extGet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_ext
//  Input       : unsigned int upll_freq_ext: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_extGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.pll_freq_ext;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_fdpllfreq_unused_2Set
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_2
//  Input       : unsigned int ufdpllfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_2Set(unsigned int ufdpllfreq_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.fdpllfreq_unused_2 = ufdpllfreq_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_fdpllfreq_unused_2Get
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_2
//  Input       : unsigned int ufdpllfreq_unused_2: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.fdpllfreq_unused_2;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_pll_freq_optSet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_opt
//  Input       : unsigned int upll_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_optSet(unsigned int upll_freq_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.pll_freq_opt = upll_freq_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_pll_freq_optGet
//  Description : Set the value of the member FDPLLFREQ.pll_freq_opt
//  Input       : unsigned int upll_freq_opt: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_freq_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.pll_freq_opt;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_fdpllfreq_unused_1Set
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_1
//  Input       : unsigned int ufdpllfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_1Set(unsigned int ufdpllfreq_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.fdpllfreq_unused_1 = ufdpllfreq_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_fdpllfreq_unused_1Get
//  Description : Set the value of the member FDPLLFREQ.fdpllfreq_unused_1
//  Input       : unsigned int ufdpllfreq_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_fdpllfreq_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.fdpllfreq_unused_1;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_pll_cnt_optSet
//  Description : Set the value of the member FDPLLFREQ.pll_cnt_opt
//  Input       : unsigned int upll_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_cnt_optSet(unsigned int upll_cnt_opt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllfreq.bits.pll_cnt_opt = upll_cnt_opt;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllfreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLFREQ_pll_cnt_optGet
//  Description : Set the value of the member FDPLLFREQ.pll_cnt_opt
//  Input       : unsigned int upll_cnt_opt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLFREQ_pll_cnt_optGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLFREQ o_fdpllfreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLFREQ.u32);
    o_fdpllfreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllfreq.bits.pll_cnt_opt;
}

//******************************************************************************
//  Function    : HDMI_FDPLLRES_pll_cnt_outSet
//  Description : Set the value of the member FDPLLRES.pll_cnt_out
//  Input       : unsigned int upll_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_cnt_outSet(unsigned int upll_cnt_out)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllres.bits.pll_cnt_out = upll_cnt_out;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllres.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLRES_pll_cnt_outGet
//  Description : Set the value of the member FDPLLRES.pll_cnt_out
//  Input       : unsigned int upll_cnt_out: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_cnt_outGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllres.bits.pll_cnt_out;
}

//******************************************************************************
//  Function    : HDMI_FDPLLRES_pll_det_statSet
//  Description : Set the value of the member FDPLLRES.pll_det_stat
//  Input       : unsigned int upll_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_det_statSet(unsigned int upll_det_stat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_fdpllres.bits.pll_det_stat = upll_det_stat;
    HDMI21TXRegWrite(pu32RegAddr, o_fdpllres.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_FDPLLRES_pll_det_statGet
//  Description : Set the value of the member FDPLLRES.pll_det_stat
//  Input       : unsigned int upll_det_stat: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_FDPLLRES_pll_det_statGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_FDPLLRES o_fdpllres;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->FDPLLRES.u32);
    o_fdpllres.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_fdpllres.bits.pll_det_stat;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_ch_test_enSet
//  Description : Set the value of the member TXTELOSET.p_ch_test_en
//  Input       : unsigned int up_ch_test_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_test_enSet(unsigned int up_ch_test_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_ch_test_en = up_ch_test_en;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_ch_test_enGet
//  Description : Set the value of the member TXTELOSET.p_ch_test_en
//  Input       : unsigned int up_ch_test_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_test_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_ch_test_en;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_test_pat_typeSet
//  Description : Set the value of the member TXTELOSET.p_test_pat_type
//  Input       : unsigned int up_test_pat_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_pat_typeSet(unsigned int up_test_pat_type)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_test_pat_type = up_test_pat_type;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_test_pat_typeGet
//  Description : Set the value of the member TXTELOSET.p_test_pat_type
//  Input       : unsigned int up_test_pat_type: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_test_pat_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_test_pat_type;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_prbs_clr_h21Set
//  Description : Set the value of the member TXTELOSET.p_prbs_clr_h21
//  Input       : unsigned int up_prbs_clr_h21: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_prbs_clr_h21Set(unsigned int up_prbs_clr_h21)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_prbs_clr_h21 = up_prbs_clr_h21;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_prbs_clr_h21Get
//  Description : Set the value of the member TXTELOSET.p_prbs_clr_h21
//  Input       : unsigned int up_prbs_clr_h21: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_prbs_clr_h21Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_prbs_clr_h21;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_ch_en_h21Set
//  Description : Set the value of the member TXTELOSET.p_ch_en_h21
//  Input       : unsigned int up_ch_en_h21: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_en_h21Set(unsigned int up_ch_en_h21)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_ch_en_h21 = up_ch_en_h21;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_ch_en_h21Get
//  Description : Set the value of the member TXTELOSET.p_ch_en_h21
//  Input       : unsigned int up_ch_en_h21: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_en_h21Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_ch_en_h21;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_prbs_clr_h20Set
//  Description : Set the value of the member TXTELOSET.p_prbs_clr_h20
//  Input       : unsigned int up_prbs_clr_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_prbs_clr_h20Set(unsigned int up_prbs_clr_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_prbs_clr_h20 = up_prbs_clr_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_prbs_clr_h20Get
//  Description : Set the value of the member TXTELOSET.p_prbs_clr_h20
//  Input       : unsigned int up_prbs_clr_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_prbs_clr_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_prbs_clr_h20;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_ch_en_h20Set
//  Description : Set the value of the member TXTELOSET.p_ch_en_h20
//  Input       : unsigned int up_ch_en_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_en_h20Set(unsigned int up_ch_en_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txteloset.bits.p_ch_en_h20 = up_ch_en_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txteloset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOSET_p_ch_en_h20Get
//  Description : Set the value of the member TXTELOSET.p_ch_en_h20
//  Input       : unsigned int up_ch_en_h20: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOSET_p_ch_en_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOSET o_txteloset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOSET.u32);
    o_txteloset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txteloset.bits.p_ch_en_h20;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT0_p_test_pat_ch1_lSet
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch1_l
//  Input       : unsigned int up_test_pat_ch1_l: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch1_lSet(unsigned int up_test_pat_ch1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont0.bits.p_test_pat_ch1_l = up_test_pat_ch1_l;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT0_p_test_pat_ch1_lGet
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch1_l
//  Input       : unsigned int up_test_pat_ch1_l: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch1_lGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont0.bits.p_test_pat_ch1_l;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT0_p_test_pat_ch0Set
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch0
//  Input       : unsigned int up_test_pat_ch0: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch0Set(unsigned int up_test_pat_ch0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont0.bits.p_test_pat_ch0 = up_test_pat_ch0;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT0_p_test_pat_ch0Get
//  Description : Set the value of the member TXTELOCONT0.p_test_pat_ch0
//  Input       : unsigned int up_test_pat_ch0: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT0_p_test_pat_ch0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT0 o_txtelocont0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT0.u32);
    o_txtelocont0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont0.bits.p_test_pat_ch0;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT1_p_test_pat_ch2Set
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch2
//  Input       : unsigned int up_test_pat_ch2: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch2Set(unsigned int up_test_pat_ch2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont1.bits.p_test_pat_ch2 = up_test_pat_ch2;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT1_p_test_pat_ch2Get
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch2
//  Input       : unsigned int up_test_pat_ch2: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont1.bits.p_test_pat_ch2;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT1_p_test_pat_ch1_hSet
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch1_h
//  Input       : unsigned int up_test_pat_ch1_h: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch1_hSet(unsigned int up_test_pat_ch1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont1.bits.p_test_pat_ch1_h = up_test_pat_ch1_h;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT1_p_test_pat_ch1_hGet
//  Description : Set the value of the member TXTELOCONT1.p_test_pat_ch1_h
//  Input       : unsigned int up_test_pat_ch1_h: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT1_p_test_pat_ch1_hGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT1 o_txtelocont1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT1.u32);
    o_txtelocont1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont1.bits.p_test_pat_ch1_h;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT2_p_test_pat_ch3Set
//  Description : Set the value of the member TXTELOCONT2.p_test_pat_ch3
//  Input       : unsigned int up_test_pat_ch3: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT2_p_test_pat_ch3Set(unsigned int up_test_pat_ch3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT2 o_txtelocont2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT2.u32);
    o_txtelocont2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txtelocont2.bits.p_test_pat_ch3 = up_test_pat_ch3;
    HDMI21TXRegWrite(pu32RegAddr, o_txtelocont2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXTELOCONT2_p_test_pat_ch3Get
//  Description : Set the value of the member TXTELOCONT2.p_test_pat_ch3
//  Input       : unsigned int up_test_pat_ch3: 20 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXTELOCONT2_p_test_pat_ch3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXTELOCONT2 o_txtelocont2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXTELOCONT2.u32);
    o_txtelocont2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txtelocont2.bits.p_test_pat_ch3;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET0_txfifoset0_unusedSet
//  Description : Set the value of the member TXFIFOSET0.txfifoset0_unused
//  Input       : unsigned int utxfifoset0_unused: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_txfifoset0_unusedSet(unsigned int utxfifoset0_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset0.bits.txfifoset0_unused = utxfifoset0_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET0_txfifoset0_unusedGet
//  Description : Set the value of the member TXFIFOSET0.txfifoset0_unused
//  Input       : unsigned int utxfifoset0_unused: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_txfifoset0_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset0.bits.txfifoset0_unused;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET0_p_enable_h20Set
//  Description : Set the value of the member TXFIFOSET0.p_enable_h20
//  Input       : unsigned int up_enable_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_enable_h20Set(unsigned int up_enable_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset0.bits.p_enable_h20 = up_enable_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET0_p_enable_h20Get
//  Description : Set the value of the member TXFIFOSET0.p_enable_h20
//  Input       : unsigned int up_enable_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_enable_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset0.bits.p_enable_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET0_p_pr_en_h20Set
//  Description : Set the value of the member TXFIFOSET0.p_pr_en_h20
//  Input       : unsigned int up_pr_en_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_pr_en_h20Set(unsigned int up_pr_en_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset0.bits.p_pr_en_h20 = up_pr_en_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET0_p_pr_en_h20Get
//  Description : Set the value of the member TXFIFOSET0.p_pr_en_h20
//  Input       : unsigned int up_pr_en_h20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET0_p_pr_en_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET0 o_txfifoset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET0.u32);
    o_txfifoset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset0.bits.p_pr_en_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_ch_sel1_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel1_h20
//  Input       : unsigned int up_ch_sel1_h20: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel1_h20Set(unsigned int up_ch_sel1_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_ch_sel1_h20 = up_ch_sel1_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_ch_sel1_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel1_h20
//  Input       : unsigned int up_ch_sel1_h20: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel1_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_ch_sel1_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_5Set
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_5
//  Input       : unsigned int utxfifoset1_unused_5: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_5Set(unsigned int utxfifoset1_unused_5)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.txfifoset1_unused_5 = utxfifoset1_unused_5;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_5Get
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_5
//  Input       : unsigned int utxfifoset1_unused_5: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_5Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.txfifoset1_unused_5;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_data_swap1_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_data_swap1_h20
//  Input       : unsigned int up_data_swap1_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap1_h20Set(unsigned int up_data_swap1_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_data_swap1_h20 = up_data_swap1_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_data_swap1_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_data_swap1_h20
//  Input       : unsigned int up_data_swap1_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap1_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_data_swap1_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_4Set
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_4
//  Input       : unsigned int utxfifoset1_unused_4: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_4Set(unsigned int utxfifoset1_unused_4)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.txfifoset1_unused_4 = utxfifoset1_unused_4;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_4Get
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_4
//  Input       : unsigned int utxfifoset1_unused_4: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_4Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.txfifoset1_unused_4;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_pol_inv1_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv1_h20
//  Input       : unsigned int up_pol_inv1_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv1_h20Set(unsigned int up_pol_inv1_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_pol_inv1_h20 = up_pol_inv1_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_pol_inv1_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv1_h20
//  Input       : unsigned int up_pol_inv1_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv1_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_pol_inv1_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_3Set
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_3
//  Input       : unsigned int utxfifoset1_unused_3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_3Set(unsigned int utxfifoset1_unused_3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.txfifoset1_unused_3 = utxfifoset1_unused_3;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_3Get
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_3
//  Input       : unsigned int utxfifoset1_unused_3: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.txfifoset1_unused_3;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_ch_sel0_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel0_h20
//  Input       : unsigned int up_ch_sel0_h20: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel0_h20Set(unsigned int up_ch_sel0_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_ch_sel0_h20 = up_ch_sel0_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_ch_sel0_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_ch_sel0_h20
//  Input       : unsigned int up_ch_sel0_h20: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_ch_sel0_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_ch_sel0_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_2Set
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_2
//  Input       : unsigned int utxfifoset1_unused_2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_2Set(unsigned int utxfifoset1_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.txfifoset1_unused_2 = utxfifoset1_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_2Get
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_2
//  Input       : unsigned int utxfifoset1_unused_2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.txfifoset1_unused_2;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_data_swap0_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_data_swap0_h20
//  Input       : unsigned int up_data_swap0_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap0_h20Set(unsigned int up_data_swap0_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_data_swap0_h20 = up_data_swap0_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_data_swap0_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_data_swap0_h20
//  Input       : unsigned int up_data_swap0_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_data_swap0_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_data_swap0_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_1Set
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_1
//  Input       : unsigned int utxfifoset1_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_1Set(unsigned int utxfifoset1_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.txfifoset1_unused_1 = utxfifoset1_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_txfifoset1_unused_1Get
//  Description : Set the value of the member TXFIFOSET1.txfifoset1_unused_1
//  Input       : unsigned int utxfifoset1_unused_1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_txfifoset1_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.txfifoset1_unused_1;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_pol_inv0_h20Set
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv0_h20
//  Input       : unsigned int up_pol_inv0_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv0_h20Set(unsigned int up_pol_inv0_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifoset1.bits.p_pol_inv0_h20 = up_pol_inv0_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifoset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSET1_p_pol_inv0_h20Get
//  Description : Set the value of the member TXFIFOSET1.p_pol_inv0_h20
//  Input       : unsigned int up_pol_inv0_h20: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSET1_p_pol_inv0_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSET1 o_txfifoset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSET1.u32);
    o_txfifoset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifoset1.bits.p_pol_inv0_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT0_o_fifo_state1_h20Set
//  Description : Set the value of the member TXFIFOSTAT0.o_fifo_state1_h20
//  Input       : unsigned int uo_fifo_state1_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_o_fifo_state1_h20Set(unsigned int uo_fifo_state1_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat0.bits.o_fifo_state1_h20 = uo_fifo_state1_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT0_o_fifo_state1_h20Get
//  Description : Set the value of the member TXFIFOSTAT0.o_fifo_state1_h20
//  Input       : unsigned int uo_fifo_state1_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_o_fifo_state1_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat0.bits.o_fifo_state1_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT0_o_fifo_state0_h20Set
//  Description : Set the value of the member TXFIFOSTAT0.o_fifo_state0_h20
//  Input       : unsigned int uo_fifo_state0_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_o_fifo_state0_h20Set(unsigned int uo_fifo_state0_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat0.bits.o_fifo_state0_h20 = uo_fifo_state0_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT0_o_fifo_state0_h20Get
//  Description : Set the value of the member TXFIFOSTAT0.o_fifo_state0_h20
//  Input       : unsigned int uo_fifo_state0_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT0_o_fifo_state0_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT0 o_txfifostat0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT0.u32);
    o_txfifostat0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat0.bits.o_fifo_state0_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT1_o_fifo_state3_h20Set
//  Description : Set the value of the member TXFIFOSTAT1.o_fifo_state3_h20
//  Input       : unsigned int uo_fifo_state3_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_o_fifo_state3_h20Set(unsigned int uo_fifo_state3_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat1.bits.o_fifo_state3_h20 = uo_fifo_state3_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT1_o_fifo_state3_h20Get
//  Description : Set the value of the member TXFIFOSTAT1.o_fifo_state3_h20
//  Input       : unsigned int uo_fifo_state3_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_o_fifo_state3_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat1.bits.o_fifo_state3_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT1_o_fifo_state2_h20Set
//  Description : Set the value of the member TXFIFOSTAT1.o_fifo_state2_h20
//  Input       : unsigned int uo_fifo_state2_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_o_fifo_state2_h20Set(unsigned int uo_fifo_state2_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat1.bits.o_fifo_state2_h20 = uo_fifo_state2_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT1_o_fifo_state2_h20Get
//  Description : Set the value of the member TXFIFOSTAT1.o_fifo_state2_h20
//  Input       : unsigned int uo_fifo_state2_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT1_o_fifo_state2_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT1 o_txfifostat1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT1.u32);
    o_txfifostat1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat1.bits.o_fifo_state2_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT2_o_fifo_state5_h20Set
//  Description : Set the value of the member TXFIFOSTAT2.o_fifo_state5_h20
//  Input       : unsigned int uo_fifo_state5_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_o_fifo_state5_h20Set(unsigned int uo_fifo_state5_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat2.bits.o_fifo_state5_h20 = uo_fifo_state5_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT2_o_fifo_state5_h20Get
//  Description : Set the value of the member TXFIFOSTAT2.o_fifo_state5_h20
//  Input       : unsigned int uo_fifo_state5_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_o_fifo_state5_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat2.bits.o_fifo_state5_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT2_o_fifo_state4_h20Set
//  Description : Set the value of the member TXFIFOSTAT2.o_fifo_state4_h20
//  Input       : unsigned int uo_fifo_state4_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_o_fifo_state4_h20Set(unsigned int uo_fifo_state4_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat2.bits.o_fifo_state4_h20 = uo_fifo_state4_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT2_o_fifo_state4_h20Get
//  Description : Set the value of the member TXFIFOSTAT2.o_fifo_state4_h20
//  Input       : unsigned int uo_fifo_state4_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT2_o_fifo_state4_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT2 o_txfifostat2;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT2.u32);
    o_txfifostat2.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat2.bits.o_fifo_state4_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT3_o_fifo_state7_h20Set
//  Description : Set the value of the member TXFIFOSTAT3.o_fifo_state7_h20
//  Input       : unsigned int uo_fifo_state7_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_o_fifo_state7_h20Set(unsigned int uo_fifo_state7_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat3.bits.o_fifo_state7_h20 = uo_fifo_state7_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT3_o_fifo_state7_h20Get
//  Description : Set the value of the member TXFIFOSTAT3.o_fifo_state7_h20
//  Input       : unsigned int uo_fifo_state7_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_o_fifo_state7_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat3.bits.o_fifo_state7_h20;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT3_o_fifo_state6_h20Set
//  Description : Set the value of the member TXFIFOSTAT3.o_fifo_state6_h20
//  Input       : unsigned int uo_fifo_state6_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_o_fifo_state6_h20Set(unsigned int uo_fifo_state6_h20)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txfifostat3.bits.o_fifo_state6_h20 = uo_fifo_state6_h20;
    HDMI21TXRegWrite(pu32RegAddr, o_txfifostat3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXFIFOSTAT3_o_fifo_state6_h20Get
//  Description : Set the value of the member TXFIFOSTAT3.o_fifo_state6_h20
//  Input       : unsigned int uo_fifo_state6_h20: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXFIFOSTAT3_o_fifo_state6_h20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXFIFOSTAT3 o_txfifostat3;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXFIFOSTAT3.u32);
    o_txfifostat3.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txfifostat3.bits.o_fifo_state6_h20;
}

//******************************************************************************
//  Function    : HDMI_DATACLKINV_p_dataclkinvSet
//  Description : Set the value of the member DATACLKINV.p_dataclkinv
//  Input       : unsigned int up_dataclkinv: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DATACLKINV_p_dataclkinvSet(unsigned int up_dataclkinv)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DATACLKINV o_dataclkinv;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DATACLKINV.u32);
    o_dataclkinv.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_dataclkinv.bits.p_dataclkinv = up_dataclkinv;
    HDMI21TXRegWrite(pu32RegAddr, o_dataclkinv.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DATACLKINV_p_dataclkinvGet
//  Description : Set the value of the member DATACLKINV.p_dataclkinv
//  Input       : unsigned int up_dataclkinv: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DATACLKINV_p_dataclkinvGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DATACLKINV o_dataclkinv;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->DATACLKINV.u32);
    o_dataclkinv.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_dataclkinv.bits.p_dataclkinv;
}

//******************************************************************************
//  Function    : HDMI_TXDATAOUTSEL_p_ch_out_selSet
//  Description : Set the value of the member TXDATAOUTSEL.p_ch_out_sel
//  Input       : unsigned int up_ch_out_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXDATAOUTSEL_p_ch_out_selSet(unsigned int up_ch_out_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXDATAOUTSEL o_txdataoutsel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXDATAOUTSEL.u32);
    o_txdataoutsel.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_txdataoutsel.bits.p_ch_out_sel = up_ch_out_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_txdataoutsel.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TXDATAOUTSEL_p_ch_out_selGet
//  Description : Set the value of the member TXDATAOUTSEL.p_ch_out_sel
//  Input       : unsigned int up_ch_out_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TXDATAOUTSEL_p_ch_out_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TXDATAOUTSEL o_txdataoutsel;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->TXDATAOUTSEL.u32);
    o_txdataoutsel.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_txdataoutsel.bits.p_ch_out_sel;
}

//******************************************************************************
//  Function    : HDMI_HSSET_p_hssetSet
//  Description : Set the value of the member HSSET.p_hsset
//  Input       : unsigned int up_hsset: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSSET_p_hssetSet(unsigned int up_hsset)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSSET o_hsset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->HSSET.u32);
    o_hsset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hsset.bits.p_hsset = up_hsset;
    HDMI21TXRegWrite(pu32RegAddr, o_hsset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HSSET_p_hssetGet
//  Description : Set the value of the member HSSET.p_hsset
//  Input       : unsigned int up_hsset: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSSET_p_hssetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSSET o_hsset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->HSSET.u32);
    o_hsset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hsset.bits.p_hsset;
}

//******************************************************************************
//  Function    : HDMI_HSRXSENSE_w_hsrxsenseSet
//  Description : Set the value of the member HSRXSENSE.w_hsrxsense
//  Input       : unsigned int uw_hsrxsense: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSRXSENSE_w_hsrxsenseSet(unsigned int uw_hsrxsense)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSRXSENSE o_hsrxsense;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->HSRXSENSE.u32);
    o_hsrxsense.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hsrxsense.bits.w_hsrxsense = uw_hsrxsense;
    HDMI21TXRegWrite(pu32RegAddr, o_hsrxsense.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HSRXSENSE_w_hsrxsenseGet
//  Description : Set the value of the member HSRXSENSE.w_hsrxsense
//  Input       : unsigned int uw_hsrxsense: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSRXSENSE_w_hsrxsenseGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSRXSENSE o_hsrxsense;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->HSRXSENSE.u32);
    o_hsrxsense.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hsrxsense.bits.w_hsrxsense;
}

//******************************************************************************
//  Function    : HDMI_HSFIFOSTAT_o_fifo_state_hsSet
//  Description : Set the value of the member HSFIFOSTAT.o_fifo_state_hs
//  Input       : unsigned int uo_fifo_state_hs: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSFIFOSTAT_o_fifo_state_hsSet(unsigned int uo_fifo_state_hs)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSFIFOSTAT o_hsfifostat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->HSFIFOSTAT.u32);
    o_hsfifostat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_hsfifostat.bits.o_fifo_state_hs = uo_fifo_state_hs;
    HDMI21TXRegWrite(pu32RegAddr, o_hsfifostat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HSFIFOSTAT_o_fifo_state_hsGet
//  Description : Set the value of the member HSFIFOSTAT.o_fifo_state_hs
//  Input       : unsigned int uo_fifo_state_hs: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HSFIFOSTAT_o_fifo_state_hsGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HSFIFOSTAT o_hsfifostat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->HSFIFOSTAT.u32);
    o_hsfifostat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_hsfifostat.bits.o_fifo_state_hs;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_lkvdetlow_intrSet
//  Description : Set the value of the member INTRSTAT.lkvdetlow_intr
//  Input       : unsigned int ulkvdetlow_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdetlow_intrSet(unsigned int ulkvdetlow_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.lkvdetlow_intr = ulkvdetlow_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_lkvdetlow_intrGet
//  Description : Set the value of the member INTRSTAT.lkvdetlow_intr
//  Input       : unsigned int ulkvdetlow_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdetlow_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.lkvdetlow_intr;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_lkvdethigh_intrSet
//  Description : Set the value of the member INTRSTAT.lkvdethigh_intr
//  Input       : unsigned int ulkvdethigh_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdethigh_intrSet(unsigned int ulkvdethigh_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.lkvdethigh_intr = ulkvdethigh_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_lkvdethigh_intrGet
//  Description : Set the value of the member INTRSTAT.lkvdethigh_intr
//  Input       : unsigned int ulkvdethigh_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_lkvdethigh_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.lkvdethigh_intr;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_fifo_empty_intrSet
//  Description : Set the value of the member INTRSTAT.fifo_empty_intr
//  Input       : unsigned int ufifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_fifo_empty_intrSet(unsigned int ufifo_empty_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.fifo_empty_intr = ufifo_empty_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_fifo_empty_intrGet
//  Description : Set the value of the member INTRSTAT.fifo_empty_intr
//  Input       : unsigned int ufifo_empty_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_fifo_empty_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.fifo_empty_intr;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_fifo_full_intrSet
//  Description : Set the value of the member INTRSTAT.fifo_full_intr
//  Input       : unsigned int ufifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_fifo_full_intrSet(unsigned int ufifo_full_intr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrstat.bits.fifo_full_intr = ufifo_full_intr;
    HDMI21TXRegWrite(pu32RegAddr, o_intrstat.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSTAT_fifo_full_intrGet
//  Description : Set the value of the member INTRSTAT.fifo_full_intr
//  Input       : unsigned int ufifo_full_intr: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSTAT_fifo_full_intrGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSTAT o_intrstat;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSTAT.u32);
    o_intrstat.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrstat.bits.fifo_full_intr;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_lkvdetlow_intr_maskSet
//  Description : Set the value of the member INTRMASK.lkvdetlow_intr_mask
//  Input       : unsigned int ulkvdetlow_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdetlow_intr_maskSet(unsigned int ulkvdetlow_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.lkvdetlow_intr_mask = ulkvdetlow_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_lkvdetlow_intr_maskGet
//  Description : Set the value of the member INTRMASK.lkvdetlow_intr_mask
//  Input       : unsigned int ulkvdetlow_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdetlow_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.lkvdetlow_intr_mask;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_lkvdethigh_intr_maskSet
//  Description : Set the value of the member INTRMASK.lkvdethigh_intr_mask
//  Input       : unsigned int ulkvdethigh_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdethigh_intr_maskSet(unsigned int ulkvdethigh_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.lkvdethigh_intr_mask = ulkvdethigh_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_lkvdethigh_intr_maskGet
//  Description : Set the value of the member INTRMASK.lkvdethigh_intr_mask
//  Input       : unsigned int ulkvdethigh_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_lkvdethigh_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.lkvdethigh_intr_mask;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_fifo_empty_intr_maskSet
//  Description : Set the value of the member INTRMASK.fifo_empty_intr_mask
//  Input       : unsigned int ufifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_fifo_empty_intr_maskSet(unsigned int ufifo_empty_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.fifo_empty_intr_mask = ufifo_empty_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_fifo_empty_intr_maskGet
//  Description : Set the value of the member INTRMASK.fifo_empty_intr_mask
//  Input       : unsigned int ufifo_empty_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_fifo_empty_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.fifo_empty_intr_mask;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_fifo_full_intr_maskSet
//  Description : Set the value of the member INTRMASK.fifo_full_intr_mask
//  Input       : unsigned int ufifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_fifo_full_intr_maskSet(unsigned int ufifo_full_intr_mask)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrmask.bits.fifo_full_intr_mask = ufifo_full_intr_mask;
    HDMI21TXRegWrite(pu32RegAddr, o_intrmask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRMASK_fifo_full_intr_maskGet
//  Description : Set the value of the member INTRMASK.fifo_full_intr_mask
//  Input       : unsigned int ufifo_full_intr_mask: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRMASK_fifo_full_intr_maskGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRMASK o_intrmask;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRMASK.u32);
    o_intrmask.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrmask.bits.fifo_full_intr_mask;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_lkvdetlow_intr_setSet
//  Description : Set the value of the member INTRSET.lkvdetlow_intr_set
//  Input       : unsigned int ulkvdetlow_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdetlow_intr_setSet(unsigned int ulkvdetlow_intr_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.lkvdetlow_intr_set = ulkvdetlow_intr_set;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_lkvdetlow_intr_setGet
//  Description : Set the value of the member INTRSET.lkvdetlow_intr_set
//  Input       : unsigned int ulkvdetlow_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdetlow_intr_setGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.lkvdetlow_intr_set;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_lkvdethigh_intr_setSet
//  Description : Set the value of the member INTRSET.lkvdethigh_intr_set
//  Input       : unsigned int ulkvdethigh_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdethigh_intr_setSet(unsigned int ulkvdethigh_intr_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.lkvdethigh_intr_set = ulkvdethigh_intr_set;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_lkvdethigh_intr_setGet
//  Description : Set the value of the member INTRSET.lkvdethigh_intr_set
//  Input       : unsigned int ulkvdethigh_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_lkvdethigh_intr_setGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.lkvdethigh_intr_set;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_fifo_empty_intr_setSet
//  Description : Set the value of the member INTRSET.fifo_empty_intr_set
//  Input       : unsigned int ufifo_empty_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_fifo_empty_intr_setSet(unsigned int ufifo_empty_intr_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.fifo_empty_intr_set = ufifo_empty_intr_set;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_fifo_empty_intr_setGet
//  Description : Set the value of the member INTRSET.fifo_empty_intr_set
//  Input       : unsigned int ufifo_empty_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_fifo_empty_intr_setGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.fifo_empty_intr_set;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_fifo_full_intr_setSet
//  Description : Set the value of the member INTRSET.fifo_full_intr_set
//  Input       : unsigned int ufifo_full_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_fifo_full_intr_setSet(unsigned int ufifo_full_intr_set)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_intrset.bits.fifo_full_intr_set = ufifo_full_intr_set;
    HDMI21TXRegWrite(pu32RegAddr, o_intrset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_INTRSET_fifo_full_intr_setGet
//  Description : Set the value of the member INTRSET.fifo_full_intr_set
//  Input       : unsigned int ufifo_full_intr_set: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_INTRSET_fifo_full_intr_setGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_INTRSET o_intrset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->INTRSET.u32);
    o_intrset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_intrset.bits.fifo_full_intr_set;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_mod_div_valSet
//  Description : Set the value of the member CLKSET.mod_div_val
//  Input       : unsigned int umod_div_val: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_mod_div_valSet(unsigned int umod_div_val)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.mod_div_val = umod_div_val;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_mod_div_valGet
//  Description : Set the value of the member CLKSET.mod_div_val
//  Input       : unsigned int umod_div_val: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_mod_div_valGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.mod_div_val;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_fdivclk_selSet
//  Description : Set the value of the member CLKSET.p_fdivclk_sel
//  Input       : unsigned int up_fdivclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fdivclk_selSet(unsigned int up_fdivclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_fdivclk_sel = up_fdivclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_fdivclk_selGet
//  Description : Set the value of the member CLKSET.p_fdivclk_sel
//  Input       : unsigned int up_fdivclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fdivclk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_fdivclk_sel;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_modclk_selSet
//  Description : Set the value of the member CLKSET.p_modclk_sel
//  Input       : unsigned int up_modclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_modclk_selSet(unsigned int up_modclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_modclk_sel = up_modclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_modclk_selGet
//  Description : Set the value of the member CLKSET.p_modclk_sel
//  Input       : unsigned int up_modclk_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_modclk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_modclk_sel;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_ctmanSet
//  Description : Set the value of the member CLKSET.p_ctman
//  Input       : unsigned int up_ctman: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_ctmanSet(unsigned int up_ctman)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_ctman = up_ctman;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_ctmanGet
//  Description : Set the value of the member CLKSET.p_ctman
//  Input       : unsigned int up_ctman: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_ctmanGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_ctman;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_refclk_selSet
//  Description : Set the value of the member CLKSET.p_refclk_sel
//  Input       : unsigned int up_refclk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_refclk_selSet(unsigned int up_refclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_refclk_sel = up_refclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_refclk_selGet
//  Description : Set the value of the member CLKSET.p_refclk_sel
//  Input       : unsigned int up_refclk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_refclk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_refclk_sel;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_fd_clk_selSet
//  Description : Set the value of the member CLKSET.p_fd_clk_sel
//  Input       : unsigned int up_fd_clk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fd_clk_selSet(unsigned int up_fd_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_clkset.bits.p_fd_clk_sel = up_fd_clk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_clkset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CLKSET_p_fd_clk_selGet
//  Description : Set the value of the member CLKSET.p_fd_clk_sel
//  Input       : unsigned int up_fd_clk_sel: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CLKSET_p_fd_clk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CLKSET o_clkset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->CLKSET.u32);
    o_clkset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_clkset.bits.p_fd_clk_sel;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_global_resetSet
//  Description : Set the value of the member SWRESET.global_reset
//  Input       : unsigned int uglobal_reset: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_global_resetSet(unsigned int uglobal_reset)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.global_reset = uglobal_reset;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_global_resetGet
//  Description : Set the value of the member SWRESET.global_reset
//  Input       : unsigned int uglobal_reset: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_global_resetGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.global_reset;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_swreset_unusedSet
//  Description : Set the value of the member SWRESET.swreset_unused
//  Input       : unsigned int uswreset_unused: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_swreset_unusedSet(unsigned int uswreset_unused)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.swreset_unused = uswreset_unused;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_swreset_unusedGet
//  Description : Set the value of the member SWRESET.swreset_unused
//  Input       : unsigned int uswreset_unused: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_swreset_unusedGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.swreset_unused;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_dac_clock_gatSet
//  Description : Set the value of the member SWRESET.dac_clock_gat
//  Input       : unsigned int udac_clock_gat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_dac_clock_gatSet(unsigned int udac_clock_gat)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.dac_clock_gat = udac_clock_gat;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_dac_clock_gatGet
//  Description : Set the value of the member SWRESET.dac_clock_gat
//  Input       : unsigned int udac_clock_gat: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_dac_clock_gatGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.dac_clock_gat;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_dac_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_dac_clock
//  Input       : unsigned int usw_reset_dac_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_dac_clockSet(unsigned int usw_reset_dac_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_dac_clock = usw_reset_dac_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_dac_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_dac_clock
//  Input       : unsigned int usw_reset_dac_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_dac_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_dac_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_pllref_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_pllref_clock
//  Input       : unsigned int usw_reset_pllref_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_pllref_clockSet(unsigned int usw_reset_pllref_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_pllref_clock = usw_reset_pllref_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_pllref_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_pllref_clock
//  Input       : unsigned int usw_reset_pllref_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_pllref_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_pllref_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_hs_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_hs_clock
//  Input       : unsigned int usw_reset_hs_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_hs_clockSet(unsigned int usw_reset_hs_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_hs_clock = usw_reset_hs_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_hs_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_hs_clock
//  Input       : unsigned int usw_reset_hs_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_hs_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_hs_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_data_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_data_clock
//  Input       : unsigned int usw_reset_data_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_data_clockSet(unsigned int usw_reset_data_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_data_clock = usw_reset_data_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_data_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_data_clock
//  Input       : unsigned int usw_reset_data_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_data_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_data_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_txfifo_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_txfifo_clock
//  Input       : unsigned int usw_reset_txfifo_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_txfifo_clockSet(unsigned int usw_reset_txfifo_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_txfifo_clock = usw_reset_txfifo_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_txfifo_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_txfifo_clock
//  Input       : unsigned int usw_reset_txfifo_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_txfifo_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_txfifo_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_hsfifo_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_hsfifo_clock
//  Input       : unsigned int usw_reset_hsfifo_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_hsfifo_clockSet(unsigned int usw_reset_hsfifo_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_hsfifo_clock = usw_reset_hsfifo_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_hsfifo_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_hsfifo_clock
//  Input       : unsigned int usw_reset_hsfifo_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_hsfifo_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_hsfifo_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_and_fd_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_fd_clock
//  Input       : unsigned int usw_reset_mod_and_fd_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_fd_clockSet(unsigned int usw_reset_mod_and_fd_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_mod_and_fd_clock = usw_reset_mod_and_fd_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_and_fd_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_fd_clock
//  Input       : unsigned int usw_reset_mod_and_fd_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_fd_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_and_fd_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_and_nco_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_nco_clock
//  Input       : unsigned int usw_reset_mod_and_nco_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_nco_clockSet(unsigned int usw_reset_mod_and_nco_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_mod_and_nco_clock = usw_reset_mod_and_nco_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_and_nco_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_nco_clock
//  Input       : unsigned int usw_reset_mod_and_nco_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_nco_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_and_nco_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_and_mpll_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_mpll_clock
//  Input       : unsigned int usw_reset_mod_and_mpll_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_mpll_clockSet(unsigned int usw_reset_mod_and_mpll_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_mod_and_mpll_clock = usw_reset_mod_and_mpll_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_and_mpll_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_and_mpll_clock
//  Input       : unsigned int usw_reset_mod_and_mpll_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_and_mpll_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_and_mpll_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_fd_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_fd_clock
//  Input       : unsigned int usw_reset_fd_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_fd_clockSet(unsigned int usw_reset_fd_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_fd_clock = usw_reset_fd_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_fd_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_fd_clock
//  Input       : unsigned int usw_reset_fd_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_fd_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_fd_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_nco_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_nco_clock
//  Input       : unsigned int usw_reset_nco_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_nco_clockSet(unsigned int usw_reset_nco_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_nco_clock = usw_reset_nco_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_nco_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_nco_clock
//  Input       : unsigned int usw_reset_nco_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_nco_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_nco_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mpll_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_mpll_clock
//  Input       : unsigned int usw_reset_mpll_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mpll_clockSet(unsigned int usw_reset_mpll_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_mpll_clock = usw_reset_mpll_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mpll_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mpll_clock
//  Input       : unsigned int usw_reset_mpll_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mpll_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mpll_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_tmds_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_tmds_clock
//  Input       : unsigned int usw_reset_tmds_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_tmds_clockSet(unsigned int usw_reset_tmds_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_tmds_clock = usw_reset_tmds_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_tmds_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_tmds_clock
//  Input       : unsigned int usw_reset_tmds_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_tmds_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_tmds_clock;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_clockSet
//  Description : Set the value of the member SWRESET.sw_reset_mod_clock
//  Input       : unsigned int usw_reset_mod_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_clockSet(unsigned int usw_reset_mod_clock)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_swreset.bits.sw_reset_mod_clock = usw_reset_mod_clock;
    HDMI21TXRegWrite(pu32RegAddr, o_swreset.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_SWRESET_sw_reset_mod_clockGet
//  Description : Set the value of the member SWRESET.sw_reset_mod_clock
//  Input       : unsigned int usw_reset_mod_clock: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_SWRESET_sw_reset_mod_clockGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SWRESET o_swreset;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->SWRESET.u32);
    o_swreset.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_swreset.bits.sw_reset_mod_clock;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk7_divSet
//  Description : Set the value of the member GLUESET0.clk7_div
//  Input       : unsigned int uclk7_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk7_divSet(unsigned int uclk7_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk7_div = uclk7_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk7_divGet
//  Description : Set the value of the member GLUESET0.clk7_div
//  Input       : unsigned int uclk7_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk7_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk7_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk6_divSet
//  Description : Set the value of the member GLUESET0.clk6_div
//  Input       : unsigned int uclk6_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk6_divSet(unsigned int uclk6_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk6_div = uclk6_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk6_divGet
//  Description : Set the value of the member GLUESET0.clk6_div
//  Input       : unsigned int uclk6_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk6_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk6_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk5_divSet
//  Description : Set the value of the member GLUESET0.clk5_div
//  Input       : unsigned int uclk5_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk5_divSet(unsigned int uclk5_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk5_div = uclk5_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk5_divGet
//  Description : Set the value of the member GLUESET0.clk5_div
//  Input       : unsigned int uclk5_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk5_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk5_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk4_divSet
//  Description : Set the value of the member GLUESET0.clk4_div
//  Input       : unsigned int uclk4_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk4_divSet(unsigned int uclk4_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk4_div = uclk4_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk4_divGet
//  Description : Set the value of the member GLUESET0.clk4_div
//  Input       : unsigned int uclk4_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk4_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk4_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk3_divSet
//  Description : Set the value of the member GLUESET0.clk3_div
//  Input       : unsigned int uclk3_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk3_divSet(unsigned int uclk3_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk3_div = uclk3_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk3_divGet
//  Description : Set the value of the member GLUESET0.clk3_div
//  Input       : unsigned int uclk3_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk3_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk3_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk2_divSet
//  Description : Set the value of the member GLUESET0.clk2_div
//  Input       : unsigned int uclk2_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk2_divSet(unsigned int uclk2_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk2_div = uclk2_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk2_divGet
//  Description : Set the value of the member GLUESET0.clk2_div
//  Input       : unsigned int uclk2_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk2_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk2_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk1_divSet
//  Description : Set the value of the member GLUESET0.clk1_div
//  Input       : unsigned int uclk1_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk1_divSet(unsigned int uclk1_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk1_div = uclk1_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk1_divGet
//  Description : Set the value of the member GLUESET0.clk1_div
//  Input       : unsigned int uclk1_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk1_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk1_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk0_divSet
//  Description : Set the value of the member GLUESET0.clk0_div
//  Input       : unsigned int uclk0_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk0_divSet(unsigned int uclk0_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset0.bits.clk0_div = uclk0_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET0_clk0_divGet
//  Description : Set the value of the member GLUESET0.clk0_div
//  Input       : unsigned int uclk0_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET0_clk0_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET0 o_glueset0;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET0.u32);
    o_glueset0.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset0.bits.clk0_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_glueset1_unused_2Set
//  Description : Set the value of the member GLUESET1.glueset1_unused_2
//  Input       : unsigned int uglueset1_unused_2: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_2Set(unsigned int uglueset1_unused_2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.glueset1_unused_2 = uglueset1_unused_2;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_glueset1_unused_2Get
//  Description : Set the value of the member GLUESET1.glueset1_unused_2
//  Input       : unsigned int uglueset1_unused_2: 12 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.glueset1_unused_2;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk_selSet
//  Description : Set the value of the member GLUESET1.clk_sel
//  Input       : unsigned int uclk_sel: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk_selSet(unsigned int uclk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk_sel = uclk_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk_selGet
//  Description : Set the value of the member GLUESET1.clk_sel
//  Input       : unsigned int uclk_sel: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk_sel;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk11_divSet
//  Description : Set the value of the member GLUESET1.clk11_div
//  Input       : unsigned int uclk11_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk11_divSet(unsigned int uclk11_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk11_div = uclk11_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk11_divGet
//  Description : Set the value of the member GLUESET1.clk11_div
//  Input       : unsigned int uclk11_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk11_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk11_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk10_divSet
//  Description : Set the value of the member GLUESET1.clk10_div
//  Input       : unsigned int uclk10_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk10_divSet(unsigned int uclk10_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk10_div = uclk10_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk10_divGet
//  Description : Set the value of the member GLUESET1.clk10_div
//  Input       : unsigned int uclk10_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk10_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk10_div;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_glueset1_unused_1Set
//  Description : Set the value of the member GLUESET1.glueset1_unused_1
//  Input       : unsigned int uglueset1_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_1Set(unsigned int uglueset1_unused_1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.glueset1_unused_1 = uglueset1_unused_1;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_glueset1_unused_1Get
//  Description : Set the value of the member GLUESET1.glueset1_unused_1
//  Input       : unsigned int uglueset1_unused_1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_glueset1_unused_1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.glueset1_unused_1;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk8_divSet
//  Description : Set the value of the member GLUESET1.clk8_div
//  Input       : unsigned int uclk8_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk8_divSet(unsigned int uclk8_div)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_glueset1.bits.clk8_div = uclk8_div;
    HDMI21TXRegWrite(pu32RegAddr, o_glueset1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_GLUESET1_clk8_divGet
//  Description : Set the value of the member GLUESET1.clk8_div
//  Input       : unsigned int uclk8_div: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_GLUESET1_clk8_divGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GLUESET1 o_glueset1;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->GLUESET1.u32);
    o_glueset1.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_glueset1.bits.clk8_div;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_acc_selSet
//  Description : Set the value of the member STBOPT.stb_acc_sel
//  Input       : unsigned int ustb_acc_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_acc_selSet(unsigned int ustb_acc_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_acc_sel = ustb_acc_sel;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_acc_selGet
//  Description : Set the value of the member STBOPT.stb_acc_sel
//  Input       : unsigned int ustb_acc_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_acc_selGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_acc_sel;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_delay0Set
//  Description : Set the value of the member STBOPT.stb_delay0
//  Input       : unsigned int ustb_delay0: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay0Set(unsigned int ustb_delay0)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_delay0 = ustb_delay0;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_delay0Get
//  Description : Set the value of the member STBOPT.stb_delay0
//  Input       : unsigned int ustb_delay0: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_delay0;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_delay1Set
//  Description : Set the value of the member STBOPT.stb_delay1
//  Input       : unsigned int ustb_delay1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay1Set(unsigned int ustb_delay1)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_delay1 = ustb_delay1;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_delay1Get
//  Description : Set the value of the member STBOPT.stb_delay1
//  Input       : unsigned int ustb_delay1: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_delay1;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_delay2Set
//  Description : Set the value of the member STBOPT.stb_delay2
//  Input       : unsigned int ustb_delay2: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay2Set(unsigned int ustb_delay2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.stb_delay2 = ustb_delay2;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_stb_delay2Get
//  Description : Set the value of the member STBOPT.stb_delay2
//  Input       : unsigned int ustb_delay2: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_stb_delay2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.stb_delay2;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_req_lengthSet
//  Description : Set the value of the member STBOPT.req_length
//  Input       : unsigned int ureq_length: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_req_lengthSet(unsigned int ureq_length)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbopt.bits.req_length = ureq_length;
    HDMI21TXRegWrite(pu32RegAddr, o_stbopt.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_STBOPT_req_lengthGet
//  Description : Set the value of the member STBOPT.req_length
//  Input       : unsigned int ureq_length: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBOPT_req_lengthGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBOPT o_stbopt;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBOPT.u32);
    o_stbopt.u32 = HDMI21TXRegRead(pu32RegAddr);
    return o_stbopt.bits.req_length;
}

//******************************************************************************
//  Function    : HDMI_STBREQ_req_doneSet
//  Description : Set the value of the member STBREQ.req_done
//  Input       : unsigned int ureq_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBREQ_req_doneSet(unsigned int ureq_done)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBREQ o_stbreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBREQ.u32);
    o_stbreq.u32 = HDMI21TXRegRead(pu32RegAddr);
    o_stbreq.bits.req_done = ureq_done;
    HDMI21TXRegWrite(pu32RegAddr, o_stbreq.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_STBREQ_req_doneGet
//  Description : Set the value of the member STBREQ.req_done
//  Input       : unsigned int ureq_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_STBREQ_req_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_STBREQ o_stbreq;
    pu32RegAddr = (HI_U32*)&(gophifonev500_dphy_regAllReg->STBREQ.u32);
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

