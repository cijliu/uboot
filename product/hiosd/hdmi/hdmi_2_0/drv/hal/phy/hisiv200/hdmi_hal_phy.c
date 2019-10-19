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
#include "hdmi_hal_phy.h"
#include "hdmi_reg_tx.h"
#include "hdmi_reg_dphy.h"

#define PHY_NULL_CHK(p) \
do{\
    if(HI_NULL == p) {\
	    HDMI_ERR("%s is null pointer!return fail.\n",#p);\
	    return HI_FAILURE;}\
}while(0)

#define PHY_NULL_CHK_NO_RET(p) \
do{\
    if(HI_NULL == p) {\
        HDMI_ERR("%s is null pointer!return fail.\n",#p);}\
}while(0)

#define PHY_RET_CHK(ret) \
do{\
    if(HI_FAILURE == ret) {\
        HDMI_ERR("Line: %d ret is failure\n", __LINE__);\
        return HI_FAILURE;}\
}while(0)

#define PHY_INIT_CHK do{\
    if(HI_TRUE != s_stHDMIPhyInfo.bInit)\
    {HDMI_ERR("phy intf module didn't init!return fail.\n");\
    return HI_FAILURE;}\
}while(0)


#define PHY_ARRAY_SIZEOF(a)  (sizeof(a)/sizeof(a[0]))

/******************************************************************************/
/* APHY_CS DEFINE                                                      */
/******************************************************************************/
#define APHY_CS_012              0x7
#define APHY_CS_3                0x8
#define APHY_CS_4567             0xf0
#define APHY_CS_8                0x100
#define APHY_CS_9                0x200
/******************************************************************************/
/* CLOCK_SET DEFINE                                                              */
/******************************************************************************/
#define PHY_CPIS_VAL            (0x6 <<3)
#define PHY_MPLL20CLK_EN        (1<<2)
#define PHY_DATACLK_EN          (1<<3)
#define PHY_DCCCLK_EN           (1<<4)
#define PHY_VP_OUTEN            (1<<5)
#define PHY_VP_DIVNEN           (1<<7)
#define PHY_TMDS_OUTEN          (1<<5)
#define PHY_TMDS_DIVNEN         (1<<7)
#define PHY_CAS_CON             (0x02<<5)
#define PHY_ZCAL                (0x02<<5)

#define PHY_CPZS_BIT            3
#define PHY_VP_MODE             5
#define PHY_MAINEN_BIT          1
#define PHY_TXTERM_BIT          7
#define PHY_ITERM               4

volatile HI_U32 *gophdmi21tx_dphy_regAllReg = HI_NULL;
/******************************************************************************/
/* enum                                                             */
/******************************************************************************/
typedef enum
{
	APHY_OFFSET_0 = 0x0,
	APHY_OFFSET_1,
	APHY_OFFSET_2,
	APHY_OFFSET_3,
	APHY_OFFSET_4,
	APHY_OFFSET_5,
	APHY_OFFSET_6,
	APHY_OFFSET_7,
	APHY_OFFSET_8,
	APHY_OFFSET_9,
	APHY_OFFSET_A,
	APHY_OFFSET_B,
	APHY_OFFSET_C,
	APHY_OFFSET_D,
	APHY_OFFSET_E,
	APHY_OFFSET_F,
	APHY_OFFSET_BUTT
}APHY_OFFSET_ADDR_E;

/******************************************************************************/
/* Data structure                                                             */
/******************************************************************************/
typedef struct
{
    HI_U32              u32ClkMin;
    HI_U32              u32ClkMax;
}PHY_CLK_RANGE_S;

typedef struct
{
    PHY_CLK_RANGE_S     stPhyTmdsClkRange;
    PHY_HWSPEC_CFG_S    stPhyHWSpecCfg;
}PHY_HWSPEC_S;

typedef struct
{
    PHY_CLK_RANGE_S     stPhyClkRange;
    HI_U8               u8SeekValue;
}PHY_CLK_RANG_VALUE_S;

typedef struct
{
	HI_U8 	            u8FconmPll;
	HI_FLOAT            fPllVcoFrep;
}PHY_I_FCON_MPLL_S;

typedef struct
{
	HI_U16 u16ModN;
	HI_U8 u8ModT;
	HI_U8 u8ModD;
	HI_U8 u8SscgMode;
}PHY_FDIV_PARA_S;

typedef struct
{
	PHY_FCON_MODE_E enFconMode;
	HI_U32          u32IRefCnt;
}PHY_FCON_PARA_S;

typedef struct
{
	PHY_LINK_MODE_E enLinkMode;
}PHY_INIT_PARA_S;

typedef struct
{
	HDMI_PHY_TMDS_CFG_S stTmdsCfg;
	HI_U8               u8RefClkDiv;
	HI_U8               u8VpDivnsel;
	HI_U8               u8Cpzs;
	HI_U8               u8TmdsDivnsel;
	HI_U8               u8VpMode;
	HI_U8               u8FcdStep;
}PHY_CLK_SET_S;

typedef struct
{
	HI_U8  u8MVal;
	HI_U8  u8NVal;
	HI_U32 u32PllRefClk;
	HI_U32 u32MnValue;
}PHY_MNX_S;

/******************************************************************************/
/* Private value                                                              */
/******************************************************************************/
static PHY_MNX_S       s_stMnxGet;
static HDMI_PHY_INFO_S s_stHDMIPhyInfo;
PHY_CLK_RANG_VALUE_S s_stPhyHWFcdStepSet[]=
{
	{{     0, 37500},4},
	{{ 37500, 75000},3},
	{{ 75000,150000},2},
	{{150000,300000},1},
	{{300000,600000},0}
};

PHY_CLK_RANG_VALUE_S s_stPhyHWRefClkDiv[]=
{
	{{     0, 37500}, 0},
	{{ 37500, 75000}, 1},
	{{ 75000,150000}, 2},
	{{150000,300000}, 3},
	{{300000,600000}, 4},
};

PHY_CLK_RANG_VALUE_S s_stPhyHWCpzs[]=
{
	{{     0, 30000},0xf},
	{{ 30000, 37000},0x13},
	{{ 37000, 58000},0x11},
	{{ 58000, 84000},0xf},
	{{ 84000,103000},0x9},
	{{103000,130000},0xb},
	{{130000,168000},0xf},
	{{168000,204000},0x9},
	{{204000,260000},0xb},
	{{260000,445000},0xf},
	{{445000,600000},0xf},
};

PHY_CLK_RANG_VALUE_S s_stPhyHWVpDivnsel[]=
{
	{{     0, 37500},4},
	{{ 37500, 75000},3},
	{{ 75000,150000},2},
	{{150000,300000},1},
	{{300000,600000},0}
};

PHY_CLK_RANG_VALUE_S  s_stPhyHWTmdsDivnselTab[]=
{
/****|TmdsclkRange |*|DivnselValue|**************
*****|   Min  Max  |*|DivnselValue|**************/
	{{300000,600000}, 0},
	{{150000,300000}, 1},
	{{ 75000,150000}, 2},
	{{ 37500, 75000}, 3},
	{{     0, 37500}, 4},
};
/******************************************************************************/
/* Private interface                                                          */
/******************************************************************************/

static HI_S32 PhyHWWriteStb1Byte(HI_U32 u32CS, APHY_OFFSET_ADDR_E enAphyOffset, HI_U32 u32Wdata)
{
	HDMI_PHY_CSEN_stb_cs_enSet(0x00);
	HDMI_PHY_WR_stb_wenSet(0);
	HDMI_PHY_WDATA_stb_wdataSet(u32Wdata);
	HDMI_PHY_ADDR_stb_addrSet(enAphyOffset);
	HDMI_UDELAY(1);
	HDMI_PHY_WR_stb_wenSet(1);
	HDMI_PHY_CSEN_stb_cs_enSet(u32CS);
	HDMI_UDELAY(1);
	HDMI_PHY_CSEN_stb_cs_enSet(0x00);
	HDMI_PHY_WR_stb_wenSet(00);
	return HI_SUCCESS;
}

static HI_S32 PhyHWReadStb1Byte(HI_U32 u32CS, APHY_OFFSET_ADDR_E enAphyOffset, HI_U8 *pu8Rdata)
{
	PHY_NULL_CHK(pu8Rdata);
	HDMI_PHY_CSEN_stb_cs_enSet(0x00);
	HDMI_PHY_WR_stb_wenSet(0);
	HDMI_PHY_ADDR_stb_addrSet(enAphyOffset);
	HDMI_UDELAY(1);
	HDMI_PHY_CSEN_stb_cs_enSet(u32CS);
	HDMI_UDELAY(1);
	*pu8Rdata = HDMI_PHY_RDATA_stb_rdataGet();
	HDMI_PHY_CSEN_stb_cs_enSet(0x00);
	return HI_SUCCESS;
}

static HI_S32 PhyHWWriteStb(HI_U32 u32CS, APHY_OFFSET_ADDR_E enAphyOffset, HI_U8 u8Msb, HI_U8 u8Lsb, HI_U32 u32Wdata)
{
	HI_U8 u8Rdata;
	HI_U8 u8MaskValue;
	HI_U8 u8WriteValue = 0;
	if((u8Msb == 7) && (u8Lsb == 0))
	{
		PhyHWWriteStb1Byte(u32CS, enAphyOffset, u32Wdata);
	}
	else
	{
		PhyHWReadStb1Byte(u32CS, enAphyOffset, &u8Rdata);
		u8MaskValue = (255 >> (7 - u8Msb)) & (255 << u8Lsb);
		u8WriteValue = (~u8MaskValue & u8Rdata) + (u8MaskValue & (u32Wdata << u8Lsb));
		PhyHWWriteStb1Byte(u32CS, enAphyOffset, u8WriteValue);
	}
	HDMI_INFO("u32CS = %x,u8Addr = %x,u8WriteValue = %x\r\n",u32CS,enAphyOffset,u8WriteValue);
	return HI_SUCCESS;
}

static HI_S32 PhyHWInitset(PHY_INIT_PARA_S stPhyInitPara)
{
	if (stPhyInitPara.enLinkMode == PHY_LINK_MODE_HI) //If HS MODE
	{
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_0, 0x20);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_1, 0x20);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_2, 0x20);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_3, 0x20);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_4, 0x10);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_5, 0x10);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_6, 0x10);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_7, 0x10);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_8, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_4567,  APHY_OFFSET_9, 0x00);
		//#PLL Settings
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_1, 0x53);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_2, 0x30);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_0, 0xFF);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_3, 0x78);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_3, 0x18);
		//PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_4, 0x82);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_4, 0x83);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_5, 0x13);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_6, 0x4C);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_7, 0x46);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_5, 0x09);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_6, 0x98);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_7, 0x8C);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_8, 0x84);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_9, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_A, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_B, 0xE0);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_C, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_D, 0xF0);
		PhyHWWriteStb1Byte(APHY_CS_8, APHY_OFFSET_E, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_0, 0x1C);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_1, 0xA0);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_2, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_3, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_4, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_5, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_6, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_7, 0xA0);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_8, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_9, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_A, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_B, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_C, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_D, 0x00);
		PhyHWWriteStb1Byte(APHY_CS_9, APHY_OFFSET_E, 0x00);
	}
	else
	{
		//IF FRL_MODE
	}
	return HI_SUCCESS;
}

static HI_S32 PhyHWInputClockCheck(HI_U32 *pu32PixelClk)
{
	HI_U32 u32RegRetValue = 0;
	HI_U32 u32InputClk = 0;
	PHY_NULL_CHK(pu32PixelClk);
	HDMI_INFO("10:55 function: %s  \r\n",__FUNCTION__);
	/* set lock_val and lock_cnt*/
	HDMI_FDSRCPARAM_src_lock_valSet(0x04);
	HDMI_FDSRCPARAM_src_lock_cntSet(0x02);
	HDMI_FDSRCPARAM_src_enableSet(0x0);

	/* set frequency options*/
	HDMI_FDSRCFREQ_src_cnt_optSet(0x1);
	HDMI_FDSRCFREQ_fdsrcfreq_unused_1Set(0);
	HDMI_FDSRCFREQ_src_freq_optSet(0);
	HDMI_FDSRCFREQ_fdsrcfreq_unused_2Set(0);
	HDMI_FDSRCFREQ_src_freq_extSet(0);

	/* FD enable*/
	HDMI_FDSRCPARAM_src_enableSet(0x1);
	HDMI_UDELAY(2000);
	/* read status and result*/
	u32RegRetValue = HDMI_FDSRCRES_src_det_statGet();
	u32InputClk = HDMI_FDSRCRES_src_cnt_outGet();
	HDMI_INFO("input clock = : %d  kHz\r\n",u32InputClk);
	if ((u32RegRetValue & 0xF) == 0xF)
	{
		HDMI_INFO(">> input clock quality : stable,\n");
		*pu32PixelClk = u32InputClk;
	}
	else
	{
		HDMI_INFO(">> Warning !!!! input clock is unstable !!!!\n");
		*pu32PixelClk = u32InputClk;
		return HI_FAILURE;
	}

	return HI_SUCCESS;
}

static HI_S32 PhyHWResetRelease(HI_VOID)
{

	HDMI_HSSET_p_hssetSet(0x0);
	HDMI_TXFIFOSET0_p_pr_en_h20Set(0x0);
	HDMI_TXFIFOSET0_p_enable_h20Set(0x0);
	HDMI_RESETN_resetnSet(0x0);

	/* SPPHHTG2 Set 8010*/
	HDMI_RESETN_resetnSet(0x1);

	/* SPPDHTG2 Software Reset 8310*/
	HDMI_SWRESET_sw_reset_mod_clockSet(0);
	HDMI_SWRESET_sw_reset_tmds_clockSet(0);
	HDMI_SWRESET_sw_reset_mpll_clockSet(0);
	HDMI_SWRESET_sw_reset_nco_clockSet(0);
	HDMI_SWRESET_sw_reset_fd_clockSet(0);
	HDMI_SWRESET_sw_reset_mod_and_mpll_clockSet(0);
	HDMI_SWRESET_sw_reset_mod_and_nco_clockSet(0);
	HDMI_SWRESET_sw_reset_mod_and_fd_clockSet(0);
	HDMI_SWRESET_sw_reset_hsfifo_clockSet(0);
	HDMI_SWRESET_sw_reset_txfifo_clockSet(0);
	HDMI_SWRESET_sw_reset_data_clockSet(0);
	HDMI_SWRESET_sw_reset_hs_clockSet(0);
	HDMI_SWRESET_sw_reset_pllref_clockSet(0);
	HDMI_SWRESET_sw_reset_dac_clockSet(0);
	HDMI_SWRESET_dac_clock_gatSet(0);
	HDMI_SWRESET_swreset_unusedSet(0);
	HDMI_SWRESET_global_resetSet(1);

	/* SPPDHTG2 Software Reset 8310*/
	HDMI_SWRESET_global_resetSet(0);

	/* [1:0] 0 : VPCLK, 1:VPCLK4X, 2:DSCCLK, 3:HSCLK, [6] 0:VPCLK/VPCLK4X/DSCCLK/HSCLK, 1:24MHz 830c*/
	HDMI_CLKSET_p_fd_clk_selSet(0);
	HDMI_CLKSET_p_refclk_selSet(0);
	HDMI_CLKSET_p_ctmanSet(0);
	HDMI_CLKSET_p_fdivclk_selSet(0);
	HDMI_CLKSET_mod_div_valSet(0);
	HDMI_CLKSET_p_modclk_selSet(0x1);


	/* DAC CLOCK enable 8310*/
	HDMI_SWRESET_dac_clock_gatSet(1);
	return HI_SUCCESS;
}

static HI_S32 PhyHWFCON(PHY_FCON_PARA_S stFconMode)
{
	HI_U32 u32FconResult;
	if(stFconMode.enFconMode == PHY_FCON_MODE_AUTO)
	{
		HDMI_REFCLKSEL_t2_refclkselSet(0);
		HDMI_REFCLKSEL_t2_refclksel2Set(0);
		HDMI_REFCLKSEL_i_ref_clk_selSet(0x1);
		HDMI_REFCLKSEL_refclksel_unused_1Set(0);
		HDMI_REFCLKSEL_t2_pixelclkselSet(0);
		HDMI_REFCLKSEL_refclksel_unused_2Set(0);
		HDMI_REFCLKSEL_p_pr_enc_valSet(0);
		HDMI_CTSET0_i_enableSet(0x1);
		HDMI_CTSET0_i_runSet(0 );
		HDMI_FCCNTR0_i_deci_cnt_lenSet(0x80);
		HDMI_FCCNTR0_i_vco_st_wait_lenSet(0x50);
		HDMI_FCCNTR0_i_vco_end_wait_lenSet(0x50);
		HDMI_FCCNTR0_i_ref_cnt_lenSet(0x80);
		HDMI_FCOPT_i_ct_selSet(0x1);
		HDMI_FCOPT_i_clkdet_selSet(0x1);
		HDMI_FCOPT_i_ct_modeSet(0x2);
		HDMI_FCOPT_fcopt_unused_1Set(0);
		HDMI_FCOPT_i_ct_enSet(0x1);
		HDMI_FCOPT_fcopt_unused_2Set(0);
		HDMI_FCOPT_i_ct_idx_selSet(0);
		HDMI_FCOPT_i_deci_try_selSet(0);
		HDMI_FCOPT_fcopt_unusedSet(0);

		HDMI_FCCNTR1_i_ref_cntSet(stFconMode.u32IRefCnt);
		HDMI_INFO("stFconMode.u32IRefCnt = %x\r\n",stFconMode.u32IRefCnt);

		HDMI_FCCONTINSET1_p_contin_upd_rateSet(0x0000960);
		HDMI_FCCONTINSET1_p_contin_upd_timeSet(0x0);

		// FCCONRINSET2, fcon max value : 0x3FF, min value : 0x5 2017.3.21updataed
		HDMI_FCCONTINSET2_p_contin_upd_th_dnSet(0x005);
		HDMI_FCCONTINSET2_fccontinset2_unusedSet(0);
		HDMI_FCCONTINSET2_p_contin_upd_th_upSet(0x3ff);

		// FCCONRINSET0, [0] enable, [2] LKVDET polarity
		HDMI_FCCONTINSET0_p_contin_upd_enSet(0x1);
		HDMI_FCCONTINSET0_p_contin_upd_optSet(0x0);
		HDMI_FCCONTINSET0_p_contin_upd_polSet(0x1);
		HDMI_FCCONTINSET0_fccontinset0_unusedSet(0);
		HDMI_FCCONTINSET0_p_contin_upd_stepSet(0);

		// CTSET0, [0] i_enable, [1] run
		HDMI_CTSET0_i_enableSet(0x1);
		HDMI_CTSET0_i_runSet(0x1 );
		HDMI_CTSET0_ctset0_unusedSet(0);
		HDMI_UDELAY(2000);
		// FCSTAT
		u32FconResult = HDMI_FCSTAT_busyGet();
		if (u32FconResult== 1)
		{
			return HI_FAILURE;
		}
		else
		{
			HDMI_UDELAY(2000);
			// FCSTAT
			if(HDMI_FCSTAT_busyGet() == 1)//clock exist  , operation of the CT is not finished yet
			{
				HDMI_INFO("FCON is done\n");
			}
		}
	}
	else
	{
		HDMI_FCOPT_i_ct_selSet(0x0);
		HDMI_FCOPT_i_clkdet_selSet(0x0);
		HDMI_FCOPT_i_ct_modeSet(0x0);
		HDMI_FCOPT_fcopt_unused_1Set(0);
		HDMI_FCOPT_i_ct_enSet(0x0);
		HDMI_FCOPT_fcopt_unused_2Set(0);
		HDMI_FCOPT_i_ct_idx_selSet(0);
		HDMI_FCOPT_i_deci_try_selSet(0);
		HDMI_FCOPT_fcopt_unusedSet(0);
		HDMI_FCCONTINSET0_p_contin_upd_enSet(0x0);
		HDMI_FCCONTINSET0_p_contin_upd_optSet(0x0);
		HDMI_FCCONTINSET0_p_contin_upd_polSet(0x0);
		HDMI_FCCONTINSET0_fccontinset0_unusedSet(0);
		HDMI_FCCONTINSET0_p_contin_upd_stepSet(0);
		HDMI_CTSET1_i_mpll_fconSet(0x022);
		HDMI_CTSET1_i_mpll_divnSet(0x0);
		HDMI_CTSET1_i_mpll_ctlckSet(0x1);
		HDMI_CTSET1_ctset1_unusedSet(0x0);
	}
	return HI_SUCCESS;
}

static HI_S32 PhyHWPostSetup(PHY_LINK_MODE_E enLinkMode)
{
	/*HS FIFO enable HS_link input mode enable*/
	//HS FIFO enable  , HS LINK external
	HDMI_HSSET_p_hssetSet(0x03);

	/*transmitter FIFO and up sampler enable*/
	HDMI_TXFIFOSET0_p_pr_en_h20Set(1);
	HDMI_TXFIFOSET0_p_enable_h20Set(1);
#if 0
	if (enLinkMode==PHY_LINK_MODE_FRL)
	{
		/*HDMI2.1 input selection*/
		HDMI_TXDATAOUTSEL_p_ch_out_selSet(0x1);
	}
	else
#endif
	{
		/*HS input data selection */
		HDMI_TXDATAOUTSEL_p_ch_out_selSet(0x0);
	}
	HDMI_DATACLKINV_p_dataclkinvSet(0x01);
	//PhyHWWriteStb(APHY_CS_012|APHY_CS_3, APHY_OFFSET_0, 1, 1, 0x0);
	PhyHWWriteStb(1, APHY_OFFSET_0, 1, 1, 0x0);
	PhyHWWriteStb(2, APHY_OFFSET_0, 1, 1, 0x0);
	PhyHWWriteStb(4, APHY_OFFSET_0, 1, 1, 0x0);
	PhyHWWriteStb(8, APHY_OFFSET_0, 1, 1, 0x0);
	//PhyHWWriteStb(APHY_CS_012|APHY_CS_3, APHY_OFFSET_0, 1, 1, 0x1);
	PhyHWWriteStb(1, APHY_OFFSET_0, 1, 1, 0x1);
	PhyHWWriteStb(2, APHY_OFFSET_0, 1, 1, 0x1);
	PhyHWWriteStb(4, APHY_OFFSET_0, 1, 1, 0x1);
	PhyHWWriteStb(8, APHY_OFFSET_0, 1, 1, 0x1);
	return HI_SUCCESS;
}

/*********obtain  PLL voc frequency ***********/
static HI_S32 PhyHWDivnselGet(HI_U32 u32TmdsClk, HI_U8 *pu8TmdsDivn)
{
	PHY_CLK_RANG_VALUE_S *pstPhyTmdsDivnsel = HI_NULL;
	HI_U32  i = 0;
    for(pstPhyTmdsDivnsel= &s_stPhyHWTmdsDivnselTab[0];
        (pstPhyTmdsDivnsel && (i<PHY_ARRAY_SIZEOF(s_stPhyHWTmdsDivnselTab)));
        pstPhyTmdsDivnsel++, i++)
    {
        if( (u32TmdsClk >= pstPhyTmdsDivnsel->stPhyClkRange.u32ClkMin) \
            && (u32TmdsClk <= pstPhyTmdsDivnsel->stPhyClkRange.u32ClkMax) )
        {
        	*pu8TmdsDivn = pstPhyTmdsDivnsel->u8SeekValue;
            return HI_SUCCESS;
        }
    }
	HDMI_ERR("can't find param,u32TmdsClk:%u\n", u32TmdsClk);
	return HI_FAILURE;
}

static HI_U32 PhyHWPow(HI_U32 u32BaseNum, HI_U32 u32IndexNum)
{
	HI_U32 u32RetVal = 1;
	HI_U8 i;
	for(i = 0; i < u32IndexNum; i++)
	{
		u32RetVal = u32RetVal * u32BaseNum;
	}
	return u32RetVal;
}

static HI_S32 PhyHWPllVcoFreGet(HI_U32 u32TmdsClk, HI_U32 *pu32PllVcoFre)
{
	HI_U8 u8TmdsDivnsel;
	if(HI_SUCCESS != PhyHWDivnselGet(u32TmdsClk,&u8TmdsDivnsel))
	{
		return HI_FAILURE;
	}
	HDMI_INFO("u8TmdsDivnsel = %d \r\n",u8TmdsDivnsel);
	*pu32PllVcoFre = u32TmdsClk*5*PhyHWPow(2,u8TmdsDivnsel);
	HDMI_INFO("<<<<<<<<u32TmdsClk = %d,u32PllVcoFre=%d\r\n",u32TmdsClk,*pu32PllVcoFre);
	return HI_SUCCESS;
}

static HI_S32 PhyHWPhyHWClkRangValueGet(HI_U32 u32TmdsClk, HI_U8 u8Size, PHY_CLK_RANG_VALUE_S *pstPhyRangSel, HI_U8 *pu8SeekValue)
{
	PHY_CLK_RANG_VALUE_S *pstPhyRang = HI_NULL;
	HI_U32 i = 0;
	for(pstPhyRang = &pstPhyRangSel[0];
	   (pstPhyRang && (i<u8Size));
		pstPhyRang ++ ,i++)
	{
		if( (u32TmdsClk >= pstPhyRang->stPhyClkRange.u32ClkMin)  \
			&& (u32TmdsClk <= pstPhyRang->stPhyClkRange.u32ClkMax) )
		{
			*pu8SeekValue = pstPhyRang->u8SeekValue;

			return HI_SUCCESS;
		}
	}
	HDMI_ERR("can't find param,u32TmdsClk:%d,i=%d\n",u32TmdsClk,i);
	return HI_FAILURE;
}

static HI_S32 PhyHWFractionalMnxGet(HI_U32 u32TmdsClk, HI_U32 u32PixelClk, HDMI_DEEP_COLOR_E enDeepColor)
{
	HI_U8  u8MValue,u32MnValue;
	HI_U8  k;
	HI_U8 u8SeekValue;
	HI_U8 u8Size;
	HI_U32 u32PllRefClk;
	HI_U8 u8TmdsDivnsel;

#if 0
    HI_U32 u32PllVcoFre;
	u8Size = PHY_ARRAY_SIZEOF(s_stPhyHWRefClkDiv);
	/***********MNX = VCO_freq / pll_ref_freq ( video_clock_frequence / RefClksel )   */
	PhyHWPllVcoFreGet(u32TmdsClk, &u32PllVcoFre);

	if(HI_SUCCESS != PhyHWPhyHWClkRangValueGet(u32TmdsClk, u8Size, &s_stPhyHWRefClkDiv[0], &u8SeekValue))
	{
		return HI_FAILURE;
	}
	u32PllRefClk = u32PixelClk/PhyHWPow(2, u8SeekValue);
	s_stMnxGet.u32PllRefClk = u32PllRefClk;

	u32MnValue = u32PllVcoFre/u32PllRefClk;

	HDMI_INFO("u32MnValue = %d \r\n",u32MnValue);
	s_stMnxGet.u32MnValue = u32MnValue;
	/*calculate N value*/
	s_stMnxGet.u8NVal= u32MnValue%10;
	if(0 == s_stMnxGet.u8NVal)
	{
		s_stMnxGet.u8NVal = 10;
		k = 2;
	}
	else
	{
		k = 1;
	}
	/*calculate M value*/
	u8MValue = u32MnValue/10;
	s_stMnxGet.u8MVal= u8MValue - k;
#endif
	u8Size = PHY_ARRAY_SIZEOF(s_stPhyHWRefClkDiv);
	if(HI_SUCCESS != PhyHWPhyHWClkRangValueGet(u32PixelClk, u8Size, &s_stPhyHWRefClkDiv[0], &u8SeekValue))
	{
		return HI_FAILURE;
	}

	if(HI_SUCCESS != PhyHWDivnselGet(u32TmdsClk,&u8TmdsDivnsel))
	{
		return HI_FAILURE;
	}
	u32PllRefClk = u32PixelClk/PhyHWPow(2, u8SeekValue);
	s_stMnxGet.u32PllRefClk = u32PllRefClk;
	HDMI_INFO("u8TmdsDivnsel = %d \r\n",u8TmdsDivnsel);
	//*pu32PllVcoFre = u32TmdsClk*5*PhyHWPow(2,u8TmdsDivnsel);
	switch(enDeepColor)
	{
		case HDMI_DEEP_COLOR_24BIT:
			u32MnValue = 5*PhyHWPow(2, u8TmdsDivnsel)*PhyHWPow(2, u8SeekValue)*1;break;
		case HDMI_DEEP_COLOR_30BIT:
			u32MnValue = 5*PhyHWPow(2, u8TmdsDivnsel)*PhyHWPow(2, u8SeekValue)*5/4;break;
		case HDMI_DEEP_COLOR_36BIT:
			u32MnValue = 5*PhyHWPow(2, u8TmdsDivnsel)*PhyHWPow(2, u8SeekValue)*3/2;break;
		default :
			u32MnValue = 5*PhyHWPow(2, u8TmdsDivnsel)*PhyHWPow(2, u8SeekValue)*1;break;
	}
	HDMI_INFO("u32MnValue = %d \r\n",u32MnValue);
	s_stMnxGet.u32MnValue = u32MnValue;
	/*calculate N value*/
	s_stMnxGet.u8NVal= u32MnValue%10;
	if(0 == s_stMnxGet.u8NVal)
	{
		s_stMnxGet.u8NVal = 10;
		k = 2;
	}
	else
	{
		k = 1;
	}
	/*calculate M value*/
	u8MValue = u32MnValue/10;
	s_stMnxGet.u8MVal= u8MValue - k;

	HDMI_INFO("Get Mnx value.  M:%x,N:%x\r\n",s_stMnxGet.u8MVal,s_stMnxGet.u8NVal);
	return HI_SUCCESS;
}

static HI_S32 PhyHWClockSet(PHY_CLK_SET_S  stPhyClkSet)
{
	HDMI_INFO("10:55 function: %s  \r\n",__FUNCTION__);

	/*CPIS<7:3>	(6)		|REFCLKDIV<2:0>		*/
	PhyHWWriteStb1Byte(APHY_CS_8 ,APHY_OFFSET_2 , stPhyClkSet.u8RefClkDiv|PHY_CPIS_VAL);
	/*CPZS<7:3>			|REFCLKSEL<2:0>(0)		*/
	PhyHWWriteStb1Byte(APHY_CS_8 ,APHY_OFFSET_3 , stPhyClkSet.u8Cpzs<<PHY_CPZS_BIT);
	/*FRL_MODE<7>(0) VP_MODE<6:5> 	DCCCLK_EN<4>(1) DATACLK_EN<3>(1)	MPLL20CLK_EN<2>(1)	DCC_DIV<1:0>(0)	*/
	PhyHWWriteStb1Byte(APHY_CS_9 ,APHY_OFFSET_0 , (stPhyClkSet.u8VpMode<<PHY_VP_MODE)|PHY_MPLL20CLK_EN|PHY_DATACLK_EN|PHY_DCCCLK_EN);
	/*VP_DIVNEN<7>(1)	VP_DIVFRACEN<6>(0)	VP_OUTEN<5>(1)	VP4_EN<4>(0)	VP_BYPASSEN<3>(0)	VP_DIVNSEL<2:0>*/
	PhyHWWriteStb1Byte(APHY_CS_9 ,APHY_OFFSET_1 , stPhyClkSet.u8VpDivnsel|PHY_VP_OUTEN|PHY_VP_DIVNEN);
	/*TMDS_DIVNEN<7>(1)TMDS_DIVFRACEN<6>(0)TMDS_OUTEN<5>(1)TMDS4_EN<4>(0)TMDS_BYPASSEN<3>(0)TMDS_DIVNSEL<2:0>*/
	PhyHWWriteStb1Byte(APHY_CS_9 ,APHY_OFFSET_7 , stPhyClkSet.u8TmdsDivnsel|PHY_TMDS_OUTEN|PHY_TMDS_DIVNEN);

	if((stPhyClkSet.stTmdsCfg.u32TmdsClk >= 300000) && (stPhyClkSet.stTmdsCfg.u32TmdsClk <= 340000))
	{
		/*0x11160200 0x9000F*/
		HDMI_TXTELOSET_p_ch_en_h20Set(0xf);
		HDMI_TXTELOSET_p_prbs_clr_h20Set(0);
		HDMI_TXTELOSET_p_ch_en_h21Set(0);
		HDMI_TXTELOSET_p_prbs_clr_h21Set(0);
		HDMI_TXTELOSET_p_test_pat_typeSet(1);
		HDMI_TXTELOSET_p_ch_test_enSet(1);
		/*0x1116020c 0x7C1F*/
		HDMI_TXTELOCONT2_p_test_pat_ch3Set(0x7C1F);
	}
	else
	{
		/*0x11160200 0x9000F*/
		HDMI_TXTELOSET_p_ch_en_h20Set(0);
		HDMI_TXTELOSET_p_prbs_clr_h20Set(0);
		HDMI_TXTELOSET_p_ch_en_h21Set(0);
		HDMI_TXTELOSET_p_prbs_clr_h21Set(0);
		HDMI_TXTELOSET_p_test_pat_typeSet(0);
		HDMI_TXTELOSET_p_ch_test_enSet(0);
		/*0x1116020c 0x7C1F*/
		HDMI_TXTELOCONT2_p_test_pat_ch3Set(0);
	}

	/*TX link repetition rate 2*/
	HDMI_FCDSTEPSET_p_divn_h20Set(stPhyClkSet.u8FcdStep);
	HDMI_FCDSTEPSET_fcdstepset_unusedSet(0x00);
	HDMI_FCDSTEPSET_up_sampler_ratio_selSet(0x00);

	HDMI_FDIVMANUAL_i_manual_enSet(0xe);
	HDMI_FDIVMANUAL_i_divnSet(0);
	HDMI_FDIVMANUAL_fdivmanual_unusedSet(0);
	HDMI_FDIVMANUAL_i_mdivSet(s_stMnxGet.u8MVal);
	HDMI_FDIVMANUAL_i_ref_cnt_divSet(0);
	HDMI_FDIVMANUAL_i_dc_selSet(0);
	HDMI_FDIVMANUAL_i_vicSet(0);

	HDMI_FDIVSTAT1_i_fdiv_inSet(s_stMnxGet.u8NVal<<24);

	/* FDIV init  */
	HDMI_FDIVSET0_initSet(0);
	HDMI_FDIVSET0_en_ctrlSet(0);
	HDMI_FDIVSET0_en_modSet(0);
	HDMI_FDIVSET0_en_sdmSet(0);
	return HI_SUCCESS;
}

//#define FREITEBEADS

/******************************************************
*****************u32TmdsClk< 100000********************
******************************************************/
static HI_S32 PHYSpaceCfg100M(HI_VOID)
{
#ifdef FREITEBEADS
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07 );
	PhyHWWriteStb1Byte(0x007,	0x01,	0x3e);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x67);	// MAIN_ICAL<4:0> : Data Swing Control
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0e);    // POST1_ICAL<4:0> : Pre Emphasis Strength Control
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);	// TXTERM : Termination on/off
	PhyHWWriteStb1Byte(0x007,	0x08,	0x40);	// TXTERMEN <5:0> : Termination Impedance Control. 1~31: 3.2k~200ohm, 32~63:200~68ohm
	PhyHWWriteStb1Byte(0x007,	0x09,	0x8D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x007,	0x0B,	0x2F);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x67);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x0C);
	//PhyHWWriteStb1Byte(0x008,	0x0A,	0x48);
	//new code is not work in 800*600,this code is work in 800*600 ,need vendor check 0x48
	PhyHWWriteStb1Byte(0x008,   0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x0B,	0x00);
#else
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,	0x3e);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x66);	// MAIN_ICAL<4:0> : Data Swing Control
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0e);    // POST1_ICAL<4:0> : Pre Emphasis Strength Control
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);	// TXTERM : Termination on/off
	PhyHWWriteStb1Byte(0x007,	0x08,	0x40);	// TXTERMEN <5:0> : Termination Impedance Control. 1~31: 3.2k~200ohm, 32~63:200~68ohm
	PhyHWWriteStb1Byte(0x007,	0x09,	0x8D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x007,	0x0B,	0x2F);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x67);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x0C);
	//PhyHWWriteStb1Byte(0x008,	0x0A,	0x48);
	//new code is not work in 800*600,this code is work in 800*600 ,need vendor check 0x48
	PhyHWWriteStb1Byte(0x008, 	0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x0B,	0x00);
#endif
		return HI_SUCCESS;
}

/******************************************************
**u32TmdsClk >= 100000 && u32TmdsClk < 150000********************
******************************************************/
static HI_S32 PHYSpaceCfg100M_150M(HI_VOID)
{
#ifdef FREITEBEADS
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,	0x3e);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x68);	// MAIN_ICAL<4:0> : Data Swing Control
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0e);    // POST1_ICAL<4:0> : Pre Emphasis Strength Control
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);	// TXTERM : Termination on/off
	PhyHWWriteStb1Byte(0x007,	0x08,	0x40);	// TXTERMEN <5:0> : Termination Impedance Control. 1~31: 3.2k~200ohm, 32~63:200~68ohm
	PhyHWWriteStb1Byte(0x007,	0x09,	0x8D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x007,	0x0B,	0x2F);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x68);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x0C);
	PhyHWWriteStb1Byte(0x008,   0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x0B,	0x00);
#else
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,	0x3e);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x67);	// MAIN_ICAL<4:0> : Data Swing Control
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0e);    // POST1_ICAL<4:0> : Pre Emphasis Strength Control
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);	// TXTERM : Termination on/off
	PhyHWWriteStb1Byte(0x007,	0x08,	0x40);	// TXTERMEN <5:0> : Termination Impedance Control. 1~31: 3.2k~200ohm, 32~63:200~68ohm
	PhyHWWriteStb1Byte(0x007,	0x09,	0x8D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x007,	0x0B,	0x2F);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x68);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x0C);
	PhyHWWriteStb1Byte(0x008,   0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x0B,	0x00);
#endif
	return HI_SUCCESS;
}

/******************************************************
*****************u32TmdsClk >= 150000 && u32TmdsClk < 165000********************
******************************************************/
static HI_S32 PHYSpaceCfg150M_165M(HI_VOID)
{
#ifdef FREITEBEADS
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,	0x3e);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x68);	// MAIN_ICAL<4:0> : Data Swing Control
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0e);    // POST1_ICAL<4:0> : Pre Emphasis Strength Control
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);	// TXTERM : Termination on/off
	PhyHWWriteStb1Byte(0x007,	0x08,	0x40);	// TXTERMEN <5:0> : Termination Impedance Control. 1~31: 3.2k~200ohm, 32~63:200~68ohm
	PhyHWWriteStb1Byte(0x007,	0x09,	0x8D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x007,	0x0B,	0x2F);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x68);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x0C);
	PhyHWWriteStb1Byte(0x008,   0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x0B,	0x00);
#else
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,	0x3e);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x68);	// MAIN_ICAL<4:0> : Data Swing Control
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0e);    // POST1_ICAL<4:0> : Pre Emphasis Strength Control
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);	// TXTERM : Termination on/off
	PhyHWWriteStb1Byte(0x007,	0x08,	0x40);	// TXTERMEN <5:0> : Termination Impedance Control. 1~31: 3.2k~200ohm, 32~63:200~68ohm
	PhyHWWriteStb1Byte(0x007,	0x09,	0x8D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x007,	0x0B,	0x2F);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x68);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x0C);
	PhyHWWriteStb1Byte(0x008,   0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x0B,	0x00);
#endif
		return HI_SUCCESS;
}

/******************************************************
*****************u32TmdsClk >= 165000 && u32TmdsClk < 300000********************
******************************************************/
static HI_S32 PHYSpaceCfg165M_300M(HI_VOID)
{
#ifdef FREITEBEADS
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,	0x7E);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x6D);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x6A);
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0E);
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x007,	0x08,	0x48);
	PhyHWWriteStb1Byte(0x007,	0x09,	0x8D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x7E);
	PhyHWWriteStb1Byte(0x007,	0x0B,   0x2F);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x6A);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0xC0);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x48);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x8C);
	PhyHWWriteStb1Byte(0x008,   0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,   0x0B,   0x00);
#else

#if 0
//default
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,	0x78);
	PhyHWWriteStb1Byte(0x007,	0x02,	0x8F);
	PhyHWWriteStb1Byte(0x007,	0x03,	0x6D);
	PhyHWWriteStb1Byte(0x007,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,	0x6E);
	PhyHWWriteStb1Byte(0x007,	0x06,	0x0C);
	PhyHWWriteStb1Byte(0x007,	0x07,	0x40);
	PhyHWWriteStb1Byte(0x007,	0x08,	0x40);
	PhyHWWriteStb1Byte(0x007,	0x09,	0x0D);
	PhyHWWriteStb1Byte(0x007,	0x0A,	0x78);
	PhyHWWriteStb1Byte(0x007,	0x0B,	0x00);
	//#CLK Drv Settings
	PhyHWWriteStb1Byte(0x008,	0x00,	0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,	0x3E);
	PhyHWWriteStb1Byte(0x008,	0x02,	0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,	0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,	0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,	0x6A);
	PhyHWWriteStb1Byte(0x008,	0x06,	0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,	0xC0);
	PhyHWWriteStb1Byte(0x008,	0x08,	0x48);
	PhyHWWriteStb1Byte(0x008,	0x09,	0x8C);
	PhyHWWriteStb1Byte(0x008,   0x0A,	0x3E);
	PhyHWWriteStb1Byte(0x008,   0x0B,	0x00);
#endif
	/* use 4k60 params  */
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,  0x07);	//FFE Controller setting
	PhyHWWriteStb1Byte(0x007,	0x01,  0x3E);	//4:1 Mux setting
	PhyHWWriteStb1Byte(0x007,	0x02,  0x8F);	//PreDrvier swing change 0x83,0x85,0x87,0x89,0x8b,0x8d,0x8f to increase swing
	PhyHWWriteStb1Byte(0x007,	0x03,  0x6D);	//DV_VREF<2:0> and Driver bias on/off
	PhyHWWriteStb1Byte(0x007,	0x04,  0xE0);	//Pre1 tap Pre-emphasis setting,change to E0 to FF to increase Pre1 tap emphasis if needed.
	PhyHWWriteStb1Byte(0x007,	0x05,  0x32);	//Data swing changed from 0x20 to 0x3F to increase swing
	PhyHWWriteStb1Byte(0x007,	0x06,  0x00);	//Pre-emphasis setting, change to 0x00 to 0x1f to increase pre-emphasis if needed.


	//emp term off
	PhyHWWriteStb1Byte(0x007,	0x07,  0xC0);	//0xC0 Termination on; 0x40 Termination off.

	PhyHWWriteStb1Byte(0x007,	0x08,  0x70);	//Termination impedance control [5:0] in this setting termination 100-ohm
	PhyHWWriteStb1Byte(0x007,	0x09,  0x8D);		//Termination bias current control 0x0D to 0xFD
	//vendor cfg is 0x8d,but 0x8d swing only 200+mV,8D is ok
	PhyHWWriteStb1Byte(0x007,	0x0A,  0x7E);	//Pre Driver setting <7>:Post2,<6>:Post1,<5:1>Main,<0>Pre1
	PhyHWWriteStb1Byte(0x007,	0x0B,  0x00);	//Bleeding settings [5] =1'b1 to enable; [4:0]: bleeding strength settings.


	//#CLK Drv Settings,
	PhyHWWriteStb1Byte(0x008,	0x00,  0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,  0x78);
	PhyHWWriteStb1Byte(0x008,	0x02,  0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,  0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,  0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,  0x6B);
	PhyHWWriteStb1Byte(0x008,	0x06,  0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,  0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,  0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,  0x8C);
	PhyHWWriteStb1Byte(0x008,	0x0A,  0x38);
	PhyHWWriteStb1Byte(0x008,	0x0B,  0x00);

#endif
		return HI_SUCCESS;
}

/******************************************************
*****************u32TmdsClk >= 300000 && u32TmdsClk < 600000********************
******************************************************/
static HI_S32 PHYSpaceCfg300M_600M(HI_VOID)
{
#ifdef FREITEBEADS
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,  0x07);
	PhyHWWriteStb1Byte(0x007,	0x01,  0x7E);
	PhyHWWriteStb1Byte(0x007,	0x02,  0x8B);
	PhyHWWriteStb1Byte(0x007,	0x03,  0x4D);
	PhyHWWriteStb1Byte(0x007,	0x04,  0xE0);
	PhyHWWriteStb1Byte(0x007,	0x05,  0x6c);
	PhyHWWriteStb1Byte(0x007,	0x06,  0x10);
	//emp term off
	PhyHWWriteStb1Byte(0x007,	0x07,  0x40);
	PhyHWWriteStb1Byte(0x007,	0x08,  0x70);
	PhyHWWriteStb1Byte(0x007,	0x09,  0x8D);
	//vendor cfg is 0x8d,but 0x8d swing only 200+mV,8D is ok
	//PhyHWWriteStb1Byte(0x007,	0x9,0x0D);
 	PhyHWWriteStb1Byte(0x007,	0x0A,  0x7E);
 	PhyHWWriteStb1Byte(0x007,	0x0B,  0x2F);
	//#CLK Drv Settings,
	PhyHWWriteStb1Byte(0x008,	0x00,  0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,  0x7E);
	PhyHWWriteStb1Byte(0x008,	0x02,  0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,  0x6D);
	PhyHWWriteStb1Byte(0x008,	0x04,  0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,  0x34);
	PhyHWWriteStb1Byte(0x008,	0x06,  0x04);
	PhyHWWriteStb1Byte(0x008,	0x07,  0xC0);
	PhyHWWriteStb1Byte(0x008,	0x08,  0x70);
	PhyHWWriteStb1Byte(0x008,	0x09,  0x8F);
	PhyHWWriteStb1Byte(0x008,	0x0A,  0x7E);
	PhyHWWriteStb1Byte(0x008,	0x0B,  0x00);
#else
	//#Data Drv Settings
	PhyHWWriteStb1Byte(0x007,	0x00,  0x07);	//FFE Controller setting
	PhyHWWriteStb1Byte(0x007,	0x01,  0x3E);	//4:1 Mux setting
	PhyHWWriteStb1Byte(0x007,	0x02,  0x8F);	//PreDrvier swing change 0x83,0x85,0x87,0x89,0x8b,0x8d,0x8f to increase swing
	PhyHWWriteStb1Byte(0x007,	0x03,  0x6D);	//DV_VREF<2:0> and Driver bias on/off
	PhyHWWriteStb1Byte(0x007,	0x04,  0xE0);	//Pre1 tap Pre-emphasis setting,change to E0 to FF to increase Pre1 tap emphasis if needed.
	PhyHWWriteStb1Byte(0x007,	0x05,  0x32);	//Data swing changed from 0x20 to 0x3F to increase swing
	PhyHWWriteStb1Byte(0x007,	0x06,  0x00);	//Pre-emphasis setting, change to 0x00 to 0x1f to increase pre-emphasis if needed.

	//emp term off
	PhyHWWriteStb1Byte(0x007,	0x07,  0xC0);	//0xC0 Termination on; 0x40 Termination off.

	PhyHWWriteStb1Byte(0x007,	0x08,  0x70);	//Termination impedance control [5:0] in this setting termination 100-ohm
	PhyHWWriteStb1Byte(0x007,	0x09,  0x8D);		//Termination bias current control 0x0D to 0xFD
	//vendor cfg is 0x8d,but 0x8d swing only 200+mV,8D is ok
	PhyHWWriteStb1Byte(0x007,	0x0A,  0x7E);	//Pre Driver setting <7>:Post2,<6>:Post1,<5:1>Main,<0>Pre1
	PhyHWWriteStb1Byte(0x007,	0x0B,  0x00);	//Bleeding settings [5] =1'b1 to enable; [4:0]: bleeding strength settings.

	//#CLK Drv Settings,
	PhyHWWriteStb1Byte(0x008,	0x00,  0x07);
	PhyHWWriteStb1Byte(0x008,	0x01,  0x78);
	PhyHWWriteStb1Byte(0x008,	0x02,  0x8B);
	PhyHWWriteStb1Byte(0x008,	0x03,  0x65);
	PhyHWWriteStb1Byte(0x008,	0x04,  0xE0);
	PhyHWWriteStb1Byte(0x008,	0x05,  0x6B);
	PhyHWWriteStb1Byte(0x008,	0x06,  0x00);
	PhyHWWriteStb1Byte(0x008,	0x07,  0x40);
	PhyHWWriteStb1Byte(0x008,	0x08,  0x40);
	PhyHWWriteStb1Byte(0x008,	0x09,  0x8C);
	PhyHWWriteStb1Byte(0x008,	0x0A,  0x38);
	PhyHWWriteStb1Byte(0x008,	0x0B,  0x00);
#endif
		return HI_SUCCESS;
}

static HI_S32 PhyHWSpecSet(HDMI_PHY_HWSPEC_CFG_S *pstHdmiSpecCfg)
{
    PHY_NULL_CHK(pstHdmiSpecCfg);
	if(pstHdmiSpecCfg->u32TmdsClk< 100000)
	{
		PHYSpaceCfg100M();
	}
	else if(pstHdmiSpecCfg->u32TmdsClk >= 100000 && pstHdmiSpecCfg->u32TmdsClk < 150000)
	{
		PHYSpaceCfg100M_150M();
	}
	else if(pstHdmiSpecCfg->u32TmdsClk >= 150000 && pstHdmiSpecCfg->u32TmdsClk < 165000)
	{
		PHYSpaceCfg150M_165M();
	}
	else if(pstHdmiSpecCfg->u32TmdsClk >= 165000 && pstHdmiSpecCfg->u32TmdsClk < 300000)
	{
		PHYSpaceCfg165M_300M();
	}
	else if(pstHdmiSpecCfg->u32TmdsClk >= 300000 && pstHdmiSpecCfg->u32TmdsClk < 600000)
	{
		PHYSpaceCfg300M_600M();
	}
	return HI_SUCCESS;
}

static HI_S32 HAL_HDMI_ClkSetParaGet(PHY_CLK_SET_S *pstPhyClkSet)
{
 	HI_U8 u8Size;

	u8Size = PHY_ARRAY_SIZEOF(s_stPhyHWFcdStepSet);
	if(HI_SUCCESS != PhyHWPhyHWClkRangValueGet(pstPhyClkSet->stTmdsCfg.u32TmdsClk, u8Size,  \
		&s_stPhyHWFcdStepSet[0], &pstPhyClkSet->u8FcdStep))
	{
		return HI_FAILURE;
	}
	HDMI_INFO("Get u8FcdStep = %x\r\n",pstPhyClkSet->u8FcdStep);

	u8Size = PHY_ARRAY_SIZEOF(s_stPhyHWRefClkDiv);
	if(HI_SUCCESS != PhyHWPhyHWClkRangValueGet(pstPhyClkSet->stTmdsCfg.u32PixelClk, u8Size,  \
		&s_stPhyHWRefClkDiv[0], &pstPhyClkSet->u8RefClkDiv))
	{
		return HI_FAILURE;
	}
	HDMI_INFO("Get u8RefClkDiv = %x\r\n",pstPhyClkSet->u8RefClkDiv);

	u8Size = PHY_ARRAY_SIZEOF(s_stPhyHWCpzs);
	if(HI_SUCCESS != PhyHWPhyHWClkRangValueGet(pstPhyClkSet->stTmdsCfg.u32TmdsClk, u8Size,  \
		&s_stPhyHWCpzs[0], &pstPhyClkSet->u8Cpzs))
	{
		return HI_FAILURE;
	}
	HDMI_INFO("Get u8Cpzs = %x\r\n",pstPhyClkSet->u8Cpzs);

	u8Size = PHY_ARRAY_SIZEOF(s_stPhyHWVpDivnsel);
	if(HI_SUCCESS != PhyHWPhyHWClkRangValueGet(pstPhyClkSet->stTmdsCfg.u32TmdsClk, u8Size,  \
		&s_stPhyHWVpDivnsel[0], &pstPhyClkSet->u8VpDivnsel))
	{
		return HI_FAILURE;
	}
	HDMI_INFO("Get u8VpDivnsel = %x\r\n",pstPhyClkSet->u8VpDivnsel);

	u8Size = PHY_ARRAY_SIZEOF(s_stPhyHWTmdsDivnselTab);
	if(HI_SUCCESS != PhyHWPhyHWClkRangValueGet(pstPhyClkSet->stTmdsCfg.u32TmdsClk, u8Size,  \
		&s_stPhyHWTmdsDivnselTab[0], &pstPhyClkSet->u8TmdsDivnsel))
	{
		return HI_FAILURE;
	}
	HDMI_INFO("Get u8TmdsDivnsel = %x\r\n",pstPhyClkSet->u8TmdsDivnsel);

	return HI_SUCCESS;
}

/******************************************************************************/
/* Public interface                                                           */
/******************************************************************************/
HI_S32 HAL_HDMI_PhyInit(HDMI_HAL_INIT_S *pstHalInit)
{
	//reg init
    PHY_NULL_CHK(pstHalInit);

	if(!s_stHDMIPhyInfo.bInit)
	{
		HDMI_HDMITX_PHY_reg_Init(pstHalInit->pcBaseAddr);

		s_stHDMIPhyInfo.bInit = HI_TRUE;
	}

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhyReset(HI_VOID)
{
	PhyHWResetRelease();

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhyDeInit(HI_VOID)
{
	//the base addr of the register  map
	HDMI_HDMITX_PHY_reg_DeInit();
	s_stHDMIPhyInfo.bInit = HI_FALSE;

	return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhyPowerGet(HI_BOOL *pbEnable)
{
	//obtain power's status
	if(0x00 == HDMI_RESETN_resetnGet())
	{
		*pbEnable = HI_FALSE;
	}
	else
	{
		*pbEnable = HI_TRUE;
	}

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhyPowerSet(HI_BOOL bEnable)
{
    //low power consumption
    //PHY MODE power on  or off
    if(bEnable == HI_TRUE)
    {
		HDMI_RESETN_resetnSet(0x01);
    }
	else
	{
		HDMI_RESETN_resetnSet(0x00);
	}
	s_stHDMIPhyInfo.bPowerEnable  = bEnable;

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhyOeSet(HI_BOOL bEnable)
{
    HI_U8 u8PhyOeStat = 0;

    u8PhyOeStat = (HI_TRUE == bEnable) ? 0X01 : 0X00;

    PhyHWWriteStb(0x01, 0x03, 0x00, 0x00, u8PhyOeStat);
    PhyHWWriteStb(0x02, 0x03, 0x00, 0x00, u8PhyOeStat);
    PhyHWWriteStb(0x04, 0x03, 0x00, 0x00, u8PhyOeStat);
    PhyHWWriteStb(0x08, 0x03, 0x00, 0x00, u8PhyOeStat);

	s_stHDMIPhyInfo.bOeEnable = bEnable;

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhyOeGet(HI_BOOL *pbEnable)
{
    //get oe's status
    HI_U8 u8OeD0Status = 0;
    HI_U8 u8OeD1Status = 0;
    HI_U8 u8OeD2Status = 0;
    HI_U8 u8OeClkStatus = 0;

    if(HI_NULL == pbEnable)
    {
        return HI_FAILURE;
    }

    if(0 == HDMI_RESETN_resetnGet())
    {
        HDMI_INFO("phy is reset now, OE disable.\n");
        *pbEnable = HI_FALSE;
        return HI_SUCCESS;
    }

    PhyHWReadStb1Byte(0x1, 0x03, &u8OeD0Status);
    PhyHWReadStb1Byte(0x2, 0x03, &u8OeD1Status);
    PhyHWReadStb1Byte(0x4, 0x03, &u8OeD2Status);
    PhyHWReadStb1Byte(0x8, 0x03, &u8OeClkStatus);

    if(   (u8OeD0Status & 0x01)
       && (u8OeD1Status & 0x01)
       && (u8OeD2Status & 0x01)
       && (u8OeClkStatus & 0x01))
    {
        *pbEnable = HI_TRUE;
    }
    else
    {
        *pbEnable = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhySpecSet(HDMI_PHY_HWSPEC_CFG_S * pstHdmiSpecCfg)
{
	HI_S32  s32Ret  = HI_SUCCESS;

	HDMI_INFO("function:%s,line:%d!!!!!!!!!!!!!!!!\r\n",__FUNCTION__,__LINE__);
	PHY_NULL_CHK(pstHdmiSpecCfg);

	s32Ret = PhyHWSpecSet(pstHdmiSpecCfg);

	return s32Ret;
}

//for video path
HI_S32 HAL_HDMI_PhyTmdsSet(HDMI_PHY_TMDS_CFG_S *pstHdmiTmdsCfg)
{
	HI_U32 u32PixelClk = 0;
	PHY_FCON_PARA_S stFconMode;
	HDMI_PHY_SSC_CFG_S stHdmiSscCfg;
	PHY_LINK_MODE_E enLinkMode;
	PHY_INIT_PARA_S stPhyInitPara;
	HI_U32 u32PllVcoFre;
	PHY_CLK_SET_S  stPhyClkSet;
	HDMI_PHY_HWSPEC_CFG_S stHdmiSpecCfg;

    PhyHWResetRelease();

	if(HI_SUCCESS != PhyHWInputClockCheck(&u32PixelClk))
	{
		HDMI_INFO("input clock unstable\r\n");
		return HI_FAILURE;
	}

	stPhyInitPara.enLinkMode = PHY_LINK_MODE_HI;
    PhyHWInitset(stPhyInitPara);

	stHdmiSpecCfg.u32TmdsClk = pstHdmiTmdsCfg->u32TmdsClk;
	stHdmiSpecCfg.stHDMIPhySpec.bHWSpecDebugEn = 0;
	PhyHWSpecSet(&stHdmiSpecCfg);

	stPhyClkSet.stTmdsCfg.enDeepColor = pstHdmiTmdsCfg->enDeepColor;
	stPhyClkSet.stTmdsCfg.u32PixelClk = pstHdmiTmdsCfg->u32PixelClk;
	stPhyClkSet.stTmdsCfg.u32TmdsClk = pstHdmiTmdsCfg->u32TmdsClk;

	switch(stPhyClkSet.stTmdsCfg.enDeepColor)
	{
		case HDMI_DEEP_COLOR_24BIT:
			stPhyClkSet.u8VpMode = 0;break;
		case HDMI_DEEP_COLOR_30BIT:
			stPhyClkSet.u8VpMode = 1;break;
		case HDMI_DEEP_COLOR_36BIT:
			stPhyClkSet.u8VpMode = 2;break;
		case HDMI_DEEP_COLOR_48BIT:
			stPhyClkSet.u8VpMode = 0;break;
		default :
			stPhyClkSet.u8VpMode = 0;break;
	}
	HDMI_INFO("Get u8VpMode = %x\r\n",stPhyClkSet.u8VpMode);
	if(HI_SUCCESS != HAL_HDMI_ClkSetParaGet(&stPhyClkSet))
	{
		HDMI_INFO("Init para get fail\r\n");
		return HI_FAILURE;
	}
	if(HI_SUCCESS != PhyHWFractionalMnxGet(stPhyClkSet.stTmdsCfg.u32TmdsClk,stPhyClkSet.stTmdsCfg.u32PixelClk, stPhyClkSet.stTmdsCfg.enDeepColor))
	{
		HDMI_INFO("MNX get fail\r\n");
		return HI_FAILURE;
	}
	PhyHWClockSet(stPhyClkSet);

	stFconMode.enFconMode = PHY_FCON_MODE_AUTO;
	if(HI_SUCCESS != PhyHWPllVcoFreGet(pstHdmiTmdsCfg->u32TmdsClk,&u32PllVcoFre))
	{
		return HI_FAILURE;
	}

	/***************************
				 PLL_VCO_FRE(MHz)
	I_REF_CNT = ----------------- *  16(constant)*32(FCCNTR0[31:24])
					24 * 20
	***************************/
	stFconMode.u32IRefCnt = (u32PllVcoFre*2*128/(1000 * 20 * 3));
	HDMI_INFO("I_REF_CNT : %x\r\n",stFconMode.u32IRefCnt);
	if(HI_SUCCESS!= PhyHWFCON(stFconMode))
	{
		HDMI_INFO("Fcon is failed and You have to restart FCON\n");
		//return HI_FAILURE;
	}

    HDMI_MEMSET(&stHdmiSscCfg, 0, sizeof(stHdmiSscCfg));
	stHdmiSscCfg.stHDMIPhySsc.bSscEnable = 0;
	HAL_HDMI_PhySscSet(&stHdmiSscCfg);

	enLinkMode = PHY_LINK_MODE_HI;
	PhyHWPostSetup(enLinkMode);

    /* Then disable output and enable by user. */
    HAL_HDMI_PhyOeSet(HI_FALSE);

    /* status info set */
    HDMI_MEMCPY(&s_stHDMIPhyInfo.stTmdsCfg, &pstHdmiTmdsCfg, sizeof(HDMI_PHY_TMDS_CFG_S));

    return HI_SUCCESS;
}


//for video path & debug
HI_S32 HAL_HDMI_PhySscSet(HDMI_PHY_SSC_CFG_S * pstHdmiSscCfg)
{
	//SSC
	HI_U32 u32ModDN;
	HI_U16 u16ModD,u16ModN;
	HI_U8 u8ModT;
	if(pstHdmiSscCfg->stHDMIPhySsc.bSscEnable)
	{
		if(HI_SUCCESS != PhyHWFractionalMnxGet(pstHdmiSscCfg->u32TmdsClk,pstHdmiSscCfg->u32PixClk, 0))
		{
			HDMI_INFO("MNX get fail\r\n");
			//return HI_FAILURE;
		}
		u32ModDN = s_stMnxGet.u32PllRefClk*10000/pstHdmiSscCfg->stHDMIPhySsc.stPhySscCfg.u32SscFreq*4;
		if(5000 <= u32ModDN%10000)
		{
			u16ModN = u32ModDN/10000 + 1;
		}
		else
		{
			u16ModN = u32ModDN/10000;
		}
		u8ModT = 1;

		/*Relative deviation = (MOD_D(0x80A0[15:0])*MOD_N(0x809C[31:16])) /
	(65536*(((M+1)*10)+(N+X)))*/

		u16ModD = 65536 * s_stMnxGet.u32MnValue * \
		          pstHdmiSscCfg->stHDMIPhySsc.stPhySscCfg.u32SscAmptd/u16ModN;

		if(5000 <= u16ModD%10000)
		{
			u16ModD = u16ModD/10000 + 1;
		}
		else
		{
			u16ModD = u16ModD/10000;
		}
		/*FDIV step setup*/
		HDMI_FDIVSET1_step_dSet(0x05);
		HDMI_FDIVSET1_step_tSet(0x90);
		HDMI_FDIVSET1_step_nSet(0x00);
		/* FDIV up/dn*/
		HDMI_FDIVSET3_mod_lenSet(0x01);
		HDMI_FDIVSET3_mod_tSet(0x01);
		HDMI_FDIVSET3_mod_nSet(u16ModN);
		/*FDIV peak top peak setup*/
		HDMI_FDIVSET4_mod_dSet(u16ModD);
		/*FRACN[7:0] : FRACX[X:0]*/
		HDMI_FDIVSTAT1_i_fdiv_inSet(s_stMnxGet.u8NVal<<24);
		/*FDIV init*/
		HDMI_FDIVSET0_initSet(0x0);
		HDMI_FDIVSET0_en_ctrlSet(0x0);
		HDMI_FDIVSET0_en_modSet(0x0);
		HDMI_FDIVSET0_en_sdmSet(0x0);
		/*FDIV control enable*/
		HDMI_FDIVSET0_initSet(0x1);
		HDMI_FDIVSET0_en_ctrlSet(0x0);
		HDMI_FDIVSET0_en_modSet(0x0);
		HDMI_FDIVSET0_en_sdmSet(0x0);
		HDMI_UDELAY(1);	/* 150 nsec */
		/*FDIV control enable*/
		HDMI_FDIVSET0_initSet(0x0);
		HDMI_FDIVSET0_en_ctrlSet(0x0);
		HDMI_FDIVSET0_en_modSet(0x0);
		HDMI_FDIVSET0_en_sdmSet(0x0);
		HDMI_UDELAY(1);	/* 150 nsec  */
		/*FDIV control enable*/
		HDMI_FDIVSET0_initSet(0x0);
		HDMI_FDIVSET0_en_ctrlSet(0x1);
		HDMI_FDIVSET0_en_modSet(0x0);
		HDMI_FDIVSET0_en_sdmSet(0x0);
		/*FDIV control enable*/
		HDMI_FDIVSET0_initSet(0x0);
		HDMI_FDIVSET0_en_ctrlSet(0x1);
		HDMI_FDIVSET0_en_modSet(0x1);
		HDMI_FDIVSET0_en_sdmSet(0x0);
		/*FDIV control enable*/
		HDMI_FDIVSET0_initSet(0x0);
		HDMI_FDIVSET0_en_ctrlSet(0x1);
		HDMI_FDIVSET0_en_modSet(0x1);
		HDMI_FDIVSET0_en_sdmSet(0x1);
	}
	else
	{
		/*FDIV step setup*/
		HDMI_FDIVSET1_step_dSet(0x05);
		HDMI_FDIVSET1_step_tSet(0x90);
		HDMI_FDIVSET1_step_nSet(0x00);
		/* FDIV up/dn*/
		HDMI_FDIVSET3_mod_lenSet(0x01);
		HDMI_FDIVSET3_mod_tSet(0x01);
		HDMI_FDIVSET3_mod_nSet(0x1);
		/* FDIV peak top peak setup*/
		HDMI_FDIVSET4_mod_dSet(0x2EEE);
		/*FDIV init*/
		HDMI_FDIVSET0_initSet(0x0);
		HDMI_FDIVSET0_en_ctrlSet(0x0);
		HDMI_FDIVSET0_en_modSet(0x0);
		HDMI_FDIVSET0_en_sdmSet(0x0);
		/*FDIV control enable*/
		HDMI_FDIVSET0_initSet(0x1);
		HDMI_FDIVSET0_en_ctrlSet(0x0);
		HDMI_FDIVSET0_en_modSet(0x0);
		HDMI_FDIVSET0_en_sdmSet(0x0);
	}

    return HI_SUCCESS;

}

HI_S32 HAL_HDMI_PhySscGet(HI_BOOL * pbEnable)
{
	if( HDMI_FDIVSET0_en_modGet() && \
	    HDMI_FDIVSET0_en_ctrlGet() && \
	    HDMI_FDIVSET0_en_sdmGet() )
	{
		*pbEnable = HI_TRUE;
	}
	else
	{
		*pbEnable = HI_FALSE;
	}

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_PhyInfoGet(HDMI_PHY_INFO_S *pstPhyStatus)
{
    //status information obtain
	HDMI_MEMCPY(pstPhyStatus, &s_stHDMIPhyInfo, sizeof(HDMI_PHY_INFO_S));
    return HI_SUCCESS;
}
