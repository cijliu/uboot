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
        unsigned int    hdmitx_pxl_cken             : 1   ; /* [16]  */
        unsigned int    reserved_2                  : 15  ; /* [31..17]  */
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
        unsigned int    phy_tmds_cken            : 1   ; /* [0]  */
        unsigned int    phy_modclk_cken          : 1   ; /* [1]  */
        unsigned int    ac_ctrl_modclk_cken      : 1   ; /* [2]  */
        unsigned int    ac_ctrl_vpxl_cken        : 1   ; /* [3]  */
        unsigned int    hdmitx_phy_srst_req      : 1   ; /* [4]  */
        unsigned int    hdmitx_phy_bus_srst_req  : 1   ; /* [5]  */
        unsigned int    ac_ctrl_srst_req         : 1   ; /* [6]  */
        unsigned int    ac_ctrl_bus_srst_req     : 1   ; /* [7]  */
        unsigned int    hdmitxphy_clk_pctrl      : 1   ; /* [8]  */
        unsigned int    reserved_0               : 23  ; /* [31..9]  */

    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} R_PERI_CRG70;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           reserved_0[68]           ; /* 0x00~0x10c */
    volatile R_PERI_CRG68           PERI_CRG68               ; /* 0x0110 */
    volatile unsigned int           reserved_1               ;
    volatile R_PERI_CRG70           PERI_CRG70               ; /* 0x0118 */
} HDMI_REG_CRG_S;

//extern volatile HDMI_REG_CRG_S *s_pstRegCrg;

int REG_HDMI_CRG_reg_Init(void);
int REG_HDMI_CRG_reg_DeInit(void);


//hdmitx ctrl
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
int REG_HDMI_CRG_hdmitx_pxl_cken_Set(unsigned int uhdmitx_pxl_cken);
int REG_HDMI_CRG_hdmitx_pxl_cken_Get(HI_VOID);

//hdmitx phy
int REG_HDMI_CRG_phy_tmds_cken_Set(unsigned int uphy_tmds_cken);
int REG_HDMI_CRG_phy_tmds_cken_Get(HI_VOID);
int REG_HDMI_CRG_phy_modclk_cken_Set(unsigned int uphy_modclk_cken);
int REG_HDMI_CRG_phy_modclk_cken_Get(HI_VOID);
int REG_HDMI_CRG_ac_ctrl_modclk_cken_Set(unsigned int uac_ctrl_modclk_cken);
int REG_HDMI_CRG_ac_ctrl_modclk_cken_Get(HI_VOID);
int REG_HDMI_CRG_ac_ctrl_vpxl_cken_Set(unsigned int uac_ctrl_vpxl_cken);
int REG_HDMI_CRG_ac_ctrl_vpxl_cken_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_phy_srst_req_Set(unsigned int uhdmitx_phy_srst_req);
int REG_HDMI_CRG_hdmitx_phy_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_hdmitx_phy_bus_srst_req_Set(unsigned int uhdmitx_phy_bus_srst_req);
int REG_HDMI_CRG_hdmitx_phy_bus_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_ac_ctrl_srst_req_Set(unsigned int uac_ctrl_srst_req);
int REG_HDMI_CRG_ac_ctrl_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_ac_ctrl_bus_srst_req_Set(unsigned int uac_ctrl_bus_srst_req);
int REG_HDMI_CRG_ac_ctrl_bus_srst_req_Get(HI_VOID);
int REG_HDMI_CRG_hdmitxphy_clk_pctrl_Set(unsigned int uhdmitxphy_clk_pctrl);
int REG_HDMI_CRG_hdmitxphy_clk_pctrl_Get(HI_VOID);


#endif /* __HDMI_REG_HI3559AV100ES_CRG_H__ */
