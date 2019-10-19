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

/* Define the union R_PERI_CRG59 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ssc_in_cken                 : 1   ; /* [0]  */
        unsigned int    ssc_bypass_cken             : 1   ; /* [1]  */
        unsigned int    hdmitx_ctrl_osc_24m_cken    : 1   ; /* [2]  */
        unsigned int    hdmitx_ctrl_cec_cken        : 1   ; /* [3]  */
        unsigned int    hdmitx_ctrl_os_cken         : 1   ; /* [4]  */
        unsigned int    hdmitx_ctrl_as_cken         : 1   ; /* [5]  */
        unsigned int    hdmitx_ctrl_bus_srst_req    : 1   ; /* [6]  */
        unsigned int    hdmitx_ctrl_srst_req        : 1   ; /* [7]  */
        unsigned int    hdmitx_ctrl_cec_srst_req    : 1   ; /* [8]  */
        unsigned int    hdmitx_ssc_srst_req         : 1   ; /* [9]  */
        unsigned int    ssc_clk_div                 : 4   ; /* [13..10]  */
        unsigned int    reserved_0                  : 2   ; /* [15..14]  */
        unsigned int    hdmitx_pxl_cken             : 1   ; /* [16]  */
        unsigned int    reserved_1                  : 2   ; /* [18..17]  */
        unsigned int    ssc_bypass_clk_sel          : 1   ; /* [19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG59;

/* Define the union R_PERI_CRG60 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    phy_tmds_cken         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    hdmitx_phy_srst_req   : 1   ; /* [4]  */
        unsigned int    phy_tmds_srst_req     : 1   ; /* [5]  */
        unsigned int    tmds_clk_div          : 3   ; /* [8..6]  */
        unsigned int    reserved_1            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG60;

/* Define the union R_PERI_CRG61 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vo_hd0_hdmi_clk_div   : 5   ; /* [4..0]  */
        unsigned int    vo_hd1_hdmi_clk_div   : 5   ; /* [9..5]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG61;


//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           reserved_0[59]                     ; /* 0x00~0xe8  */
    volatile R_PERI_CRG59           PERI_CRG59            ; /* 0xec */
    volatile R_PERI_CRG60           PERI_CRG60            ; /* 0xf0 */
    volatile R_PERI_CRG61           PERI_CRG61            ; /* 0xf4 */
    volatile unsigned int           reserved_1[85]                     ; /* 0xf8~0x248 */
} HDMI_REG_CRG_S;

//extern volatile HDMI_REG_CRG_S *s_pstRegCrg;

int REG_HDMI_CRG_reg_Init(void);
int REG_HDMI_CRG_reg_DeInit(void);


//hdmitx ctrl
int REG_HDMI_CRG_ssc_in_cken_Set(unsigned int ussc_in_cken);
int REG_HDMI_CRG_ssc_in_cken_Get(HI_VOID);
int REG_HDMI_CRG_ssc_bypass_cken_Set(unsigned int ussc_bypass_cken);
int REG_HDMI_CRG_ssc_bypass_cken_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Set(unsigned int uhdmitx_ctrl_osc_24m_cken);
int REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ctrl_cec_cken_Set(unsigned int uhdmitx_ctrl_cec_cken);
int REG_HDMI_CRG_hdmitx_ctrl_cec_cken_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ctrl_os_cken_Set(unsigned int uhdmitx_ctrl_os_cken);
int REG_HDMI_CRG_hdmitx_ctrl_os_cken_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ctrl_as_cken_Set(unsigned int uhdmitx_ctrl_as_cken);
int REG_HDMI_CRG_hdmitx_ctrl_as_cken_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(unsigned int uhdmitx_ctrl_bus_srst_req);
int REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(unsigned int uhdmitx_ctrl_srst_req);
int REG_HDMI_CRG_hdmitx_ctrl_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Set(unsigned int uhdmitx_ctrl_cec_srst_req);
int REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_ssc_srst_req_Set(unsigned int uhdmitx_ssc_srst_req);
int REG_HDMI_CRG_hdmitx_ssc_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_ssc_clk_div_Set(unsigned int ussc_clk_div);
int REG_HDMI_CRG_ssc_clk_div_Get(HI_VOID);
// 31d, add compare with 98mv200
int REG_HDMI_CRG_hdmitx_pxl_cken_Set(unsigned int uhdmitx_pxl_cken);
int REG_HDMI_CRG_hdmitx_pxl_cken_Get(HI_VOID);
int REG_HDMI_CRG_ssc_bypass_clk_sel_Set(unsigned int ussc_bypass_clk_sel);
int REG_HDMI_CRG_ssc_bypass_clk_sel_Get(HI_VOID);


//hdmitx phy
int REG_HDMI_CRG_phy_tmds_cken_Set(unsigned int uphy_tmds_cken);
int REG_HDMI_CRG_phy_tmds_cken_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_phy_srst_req_Set(unsigned int uhdmitx_phy_srst_req);
int REG_HDMI_CRG_hdmitx_phy_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_phy_tmds_srst_req_Set(unsigned int uphy_tmds_srst_req);
int REG_HDMI_CRG_phy_tmds_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_tmds_clk_div_Set(unsigned int utmds_clk_div);
int REG_HDMI_CRG_tmds_clk_div_Get(HI_VOID);

//hdmitx phy_vo_hdx 31d add, compare with 98mv200
int REG_HDMI_CRG_vo_hd0_hdmi_clk_div_Set(unsigned int uvo_hd0_hdmi_clk_div);
int REG_HDMI_CRG_vo_hd0_hdmi_clk_div_Get(HI_VOID);
int REG_HDMI_CRG_vo_hd1_hdmi_clk_div_Set(unsigned int uvo_hd1_hdmi_clk_div);
int REG_HDMI_CRG_vo_hd1_hdmi_clk_div_Get(HI_VOID);

#endif /* __HDMI_REG_HI3531DV100_CRG_H__ */
