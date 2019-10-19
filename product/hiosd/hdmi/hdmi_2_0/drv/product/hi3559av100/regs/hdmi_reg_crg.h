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

#ifndef __HDMI_REG_CRG_H__
#define __HDMI_REG_CRG_H__

/* Define the union PERI_CRG_PLL12 MPLL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_frac                   : 24  ; /* [23..0]  */
        unsigned int    mpll_postdiv1               : 3   ; /* [26..24]  */
        unsigned int    reserved0                   : 1   ; /* [27]  */
        unsigned int    mpll_postdiv2               : 3   ; /* [30..28]  */
        unsigned int    reserved1                   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG_MPLL0;

/* Define the union PERI_CRG_PLL13 MPLL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_fbdiv                  : 12  ; /* [11..0]  */
        unsigned int    mpll_refdiv                 : 6   ; /* [17..12]  */
        unsigned int    reserved0                   : 2   ; /* [19..18]  */
        unsigned int    mpll_fout4phasepd           : 1   ; /* [20]  */
        unsigned int    mpll_postdivpd              : 1   ; /* [21]  */
        unsigned int    mpll_foutvcopd              : 1   ; /* [22]  */
        unsigned int    mpll_pd                     : 1   ; /* [23]  */
        unsigned int    mpll_dsmpd                  : 1   ; /* [24]  */
        unsigned int    mpll_dacpd                  : 1   ; /* [25]  */
        unsigned int    mpll_bypass                 : 1   ; /* [26]  */
        unsigned int    mpll_foutvco2xpd            : 1   ; /* [27]  */
        unsigned int    reserved1                   : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG_MPLL1;

/* Define the union R_PERI_CRG68 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0                  : 2   ; /* [1..0]  */
        unsigned int    hdmitx_ctrl_osc_24m_cken    : 1   ; /* [2]  */
        unsigned int    hdmitx_ctrl_cec_cken        : 1   ; /* [3]  */
        unsigned int    hdmitx_ctrl_os_cken         : 1   ; /* [4]  */
        unsigned int    hdmitx_ctrl_as_cken         : 1   ; /* [5]  */
        unsigned int    hdmitx_ctrl_bus_srst_req    : 1   ; /* [6]  */
        unsigned int    hdmitx_ctrl_srst_req        : 1   ; /* [7]  */
        unsigned int    hdmitx_ctrl_cec_srst_req    : 1   ; /* [8]  */
        unsigned int    reserved_1                  : 7   ; /* [15..9]  */
        unsigned int    mpll_tmds_cken              : 1   ; /* [16]  */
        unsigned int    mpll_refclk_cksel           : 1   ; /* [17]  */
        unsigned int    reserved_2                  : 14  ; /* [31..18] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG68;

/* Define the union R_PERI_CRG70 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmirx_phy_tmds_cken     : 1   ; /* [0]  */
        unsigned int    hdmirx_phy_modclk_cken   : 1   ; /* [1]  */
        unsigned int    ac_ctrl_modclk_cken      : 1   ; /* [2]  */
        unsigned int    reserved_0               : 1   ; /* [3]  */
        unsigned int    hdmitx_phy_srst_req      : 1   ; /* [4]  */
        unsigned int    hdmitx_phy_bus_srst_req  : 1   ; /* [5]  */
        unsigned int    ac_ctrl_srst_req         : 1   ; /* [6]  */
        unsigned int    ac_ctrl_bus_srst_req     : 1   ; /* [7]  */
        unsigned int    hdmitx_phy_clk_pctrl     : 1   ; /* [8]  */
        unsigned int    mpll_tmds_cksel          : 1   ; /* [10..9]  */
        unsigned int    reserved_1               : 22  ; /* [31..11] */

    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG70;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           reserved_0[12]           ; /* 0x00~0x2c */
    volatile R_PERI_CRG_MPLL0       PERI_CRG_MPLL0           ; /* 0x30 */
    volatile R_PERI_CRG_MPLL0       PERI_CRG_MPLL1           ; /* 0x34 */
    volatile unsigned int           reserved_1[54]           ; /* 0x38~0x10c */
    volatile R_PERI_CRG68           PERI_CRG68               ; /* 0x0110 */
    volatile unsigned int           reserved_2               ;
    volatile R_PERI_CRG70           PERI_CRG70               ; /* 0x0118 */
} HDMI_REG_CRG_S;

//extern volatile HDMI_REG_CRG_S *s_pstRegCrg;

int REG_HDMI_CRG_reg_Init(void);
int REG_HDMI_CRG_reg_DeInit(void);

// mpll0
int REG_MPLL_CRG_mpll_postdiv1_Set(unsigned int umpll_postdiv1);
int REG_MPLL_CRG_mpll_postdiv2_Set(unsigned int umpll_postdiv2);
// mpll1
int REG_MPLL_CRG_mpll_dsmpd_Set(unsigned int umpll_dsmpd);
int REG_MPLL_CRG_mpll_refdiv_Set(unsigned int umpll_refdiv);
int REG_MPLL_CRG_mpll_fbdiv_Set(unsigned int umpll_fbdiv);
int REG_MPLL_CRG_mpll_pd_Set(unsigned int umpll_pd);

//hdmitx ctrl
int REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Set(unsigned int uhdmitx_ctrl_osc_24m_cken);
int REG_HDMI_CRG_hdmitx_ctrl_cec_cken_Set(unsigned int uhdmitx_ctrl_cec_cken);
int REG_HDMI_CRG_hdmitx_ctrl_os_cken_Set(unsigned int uhdmitx_ctrl_os_cken);
int REG_HDMI_CRG_hdmitx_ctrl_as_cken_Set(unsigned int uhdmitx_ctrl_as_cken);
int REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(unsigned int uhdmitx_ctrl_bus_srst_req);
int REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(unsigned int uhdmitx_ctrl_srst_req);
int REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Set(unsigned int uhdmitx_ctrl_cec_srst_req);
int REG_HDMI_CRG_mpll_tmds_cken_Set(unsigned int umpll_tmds_cken);
int REG_HDMI_CRG_mpll_refclk_cksel_Set(unsigned int umpll_refclk_cksel);

//hdmitx phy
int REG_HDMI_CRG_hdmirx_phy_tmds_cken_Set(unsigned int uhdmirx_phy_tmds_cken);
int REG_HDMI_CRG_hdmirx_phy_modclk_cken_Set(unsigned int uhdmirx_phy_modclk_cken);
int REG_HDMI_CRG_ac_ctrl_modclk_cken_Set(unsigned int uac_ctrl_modclk_cken);
int REG_HDMI_CRG_hdmitx_phy_srst_req_Set(unsigned int uhdmitx_phy_srst_req);
int REG_HDMI_CRG_hdmitx_phy_srst_req_Get(void);
int REG_HDMI_CRG_hdmitx_phy_bus_srst_req_Set(unsigned int uhdmitx_phy_bus_srst_req);
int REG_HDMI_CRG_ac_ctrl_srst_req_Set(unsigned int uac_ctrl_srst_req);
int REG_HDMI_CRG_ac_ctrl_bus_srst_req_Set(unsigned int uac_ctrl_bus_srst_req);
int REG_HDMI_CRG_hdmitx_phy_clk_pctrl_Set(unsigned int uhdmitx_phy_clk_pctrl);
int REG_HDMI_CRG_mpll_tmds_cksel_Set(unsigned int umpll_tmds_cksel);

#endif /* __HDMI_REG_HI3559AV100_CRG_H__ */
