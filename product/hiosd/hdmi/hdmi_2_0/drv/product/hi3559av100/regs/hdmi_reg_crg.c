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
#include "hdmi_reg_crg.h"
#include "hdmi_product_define.h"
/* Define the struct pointor of the module hdmi2tx_dphy_reg */
volatile HDMI_REG_CRG_S *s_pstRegCrg = NULL;


int REG_HDMI_CRG_reg_Init(void)
{
    if (NULL != s_pstRegCrg)
    {
        return HI_SUCCESS;
    }

    s_pstRegCrg  = (volatile HDMI_REG_CRG_S *)HDMI_IO_MAP(HDMI_ADDR_CRG, sizeof(HDMI_REG_CRG_S));

    if(NULL == s_pstRegCrg)
    {
        HDMI_ERR("ioremap_nocache gophdmi2tx_dphy_regAllReg failed!!!!!!!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

int REG_HDMI_CRG_reg_DeInit(void)
{
    if(HI_NULL != s_pstRegCrg)
    {
        HDMI_IO_UNMAP(s_pstRegCrg);
        s_pstRegCrg = HI_NULL;
    }

    return HI_SUCCESS;
}

int REG_MPLL_CRG_mpll_postdiv1_Set(unsigned int umpll_postdiv1)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_MPLL0 o_peri_crgmpll0;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_MPLL0.u32);

    o_peri_crgmpll0.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgmpll0.bits.mpll_postdiv1 = umpll_postdiv1;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgmpll0.u32);

    return HI_SUCCESS;
}

int REG_MPLL_CRG_mpll_postdiv2_Set(unsigned int umpll_postdiv2)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_MPLL0 o_peri_crgmpll0;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_MPLL0.u32);

    o_peri_crgmpll0.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgmpll0.bits.mpll_postdiv2 = umpll_postdiv2;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgmpll0.u32);

    return HI_SUCCESS;
}

int REG_MPLL_CRG_mpll_dsmpd_Set(unsigned int umpll_dsmpd)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_MPLL1 o_peri_crgmpll1;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_MPLL1.u32);

    o_peri_crgmpll1.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgmpll1.bits.mpll_dsmpd = umpll_dsmpd;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int REG_MPLL_CRG_mpll_refdiv_Set(unsigned int umpll_refdiv)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_MPLL1 o_peri_crgmpll1;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_MPLL1.u32);

    o_peri_crgmpll1.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgmpll1.bits.mpll_refdiv = umpll_refdiv;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int REG_MPLL_CRG_mpll_fbdiv_Set(unsigned int umpll_fbdiv)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_MPLL1 o_peri_crgmpll1;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_MPLL1.u32);

    o_peri_crgmpll1.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgmpll1.bits.mpll_fbdiv = umpll_fbdiv;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int REG_MPLL_CRG_mpll_pd_Set(unsigned int umpll_pd)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_MPLL1 o_peri_crgmpll1;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_MPLL1.u32);

    o_peri_crgmpll1.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgmpll1.bits.mpll_pd = umpll_pd;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Set(unsigned int uhdmitx_ctrl_osc_24m_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);
    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ctrl_osc_24m_cken = uhdmitx_ctrl_osc_24m_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_cken_Set(unsigned int uhdmitx_ctrl_cec_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ctrl_cec_cken = uhdmitx_ctrl_cec_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_os_cken_Set(unsigned int uhdmitx_ctrl_os_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ctrl_os_cken = uhdmitx_ctrl_os_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_as_cken_Set(unsigned int uhdmitx_ctrl_as_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ctrl_as_cken = uhdmitx_ctrl_as_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(unsigned int uhdmitx_ctrl_bus_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ctrl_bus_srst_req = uhdmitx_ctrl_bus_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(unsigned int uhdmitx_ctrl_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ctrl_srst_req = uhdmitx_ctrl_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Set(unsigned int uhdmitx_ctrl_cec_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ctrl_cec_srst_req = uhdmitx_ctrl_cec_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_mpll_tmds_cken_Set(unsigned int umpll_tmds_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.mpll_tmds_cken = umpll_tmds_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_mpll_refclk_cksel_Set(unsigned int umpll_refclk_cksel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.mpll_refclk_cksel = umpll_refclk_cksel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;

}

int REG_HDMI_CRG_hdmirx_phy_tmds_cken_Set(unsigned int uhdmirx_phy_tmds_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.hdmirx_phy_tmds_cken = uhdmirx_phy_tmds_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmirx_phy_modclk_cken_Set(unsigned int uhdmirx_phy_modclk_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.hdmirx_phy_modclk_cken = uhdmirx_phy_modclk_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_ac_ctrl_modclk_cken_Set(unsigned int uac_ctrl_modclk_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.ac_ctrl_modclk_cken = uac_ctrl_modclk_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_phy_srst_req_Set(unsigned int uhdmitx_phy_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.hdmitx_phy_srst_req = uhdmitx_phy_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_phy_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);
    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg70.bits.hdmitx_phy_srst_req;
}

int REG_HDMI_CRG_hdmitx_phy_bus_srst_req_Set(unsigned int uhdmitx_phy_bus_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.hdmitx_phy_bus_srst_req = uhdmitx_phy_bus_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_ac_ctrl_srst_req_Set(unsigned int uac_ctrl_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.ac_ctrl_srst_req = uac_ctrl_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_ac_ctrl_bus_srst_req_Set(unsigned int uac_ctrl_bus_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.ac_ctrl_bus_srst_req = uac_ctrl_bus_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_phy_clk_pctrl_Set(unsigned int uhdmitx_phy_clk_pctrl)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.hdmitx_phy_clk_pctrl = uhdmitx_phy_clk_pctrl;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_mpll_tmds_cksel_Set(unsigned int umpll_tmds_cksel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG70 o_peri_crg70;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG70.u32);

    o_peri_crg70.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg70.bits.mpll_tmds_cksel = umpll_tmds_cksel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg70.u32);

    return HI_SUCCESS;
}


