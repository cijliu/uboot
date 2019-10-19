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

    s_pstRegCrg  = (HDMI_REG_CRG_S*)HDMI_IO_MAP(HDMI_ADDR_CRG, sizeof(HDMI_REG_CRG_S));

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

int REG_HDMI_CRG_ssc_in_cken_Set(unsigned int ussc_in_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.ssc_in_cken = ussc_in_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_ssc_bypass_cken_Set(unsigned int ussc_bypass_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.ssc_bypass_cken = ussc_bypass_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

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

int REG_HDMI_CRG_hdmitx_ssc_srst_req_Set(unsigned int uhdmitx_ssc_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_ssc_srst_req = uhdmitx_ssc_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_ssc_clk_div_Set(unsigned int ussc_clk_div)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.ssc_clk_div = ussc_clk_div;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

/*  */
int REG_HDMI_CRG_hdmitx_pxl_cken_Set(unsigned int uhdmitx_pxl_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_pxl_cken = uhdmitx_pxl_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_ssc_bypass_clk_sel_Set(unsigned int ussc_bypass_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.ssc_bypass_clk_sel = ussc_bypass_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_phy_tmds_cken_Set(unsigned int uphy_tmds_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG69 o_peri_crg69;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG69.u32);

    o_peri_crg69.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg69.bits.phy_tmds_cken = uphy_tmds_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg69.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_phy_srst_req_Set(unsigned int uhdmitx_phy_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG69 o_peri_crg69;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG69.u32);

    o_peri_crg69.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg69.bits.hdmitx_phy_srst_req = uhdmitx_phy_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg69.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_phy_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG69 o_peri_crg69;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG69.u32);
    o_peri_crg69.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg69.bits.hdmitx_phy_srst_req;
}

int REG_HDMI_CRG_phy_tmds_srst_req_Set(unsigned int uphy_tmds_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG69 o_peri_crg69;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG69.u32);

    o_peri_crg69.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg69.bits.phy_tmds_srst_req = uphy_tmds_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg69.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_phy_tmds_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG69 o_peri_crg69;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG69.u32);
    o_peri_crg69.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg69.bits.phy_tmds_srst_req;
}

int REG_HDMI_CRG_tmds_clk_div_Set(unsigned int utmds_clk_div)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG69 o_peri_crg69;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG69.u32);

    o_peri_crg69.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg69.bits.tmds_clk_div = utmds_clk_div;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg69.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_tmds_clk_div_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG69 o_peri_crg69;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG69.u32);
    o_peri_crg69.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg69.bits.tmds_clk_div;
}

