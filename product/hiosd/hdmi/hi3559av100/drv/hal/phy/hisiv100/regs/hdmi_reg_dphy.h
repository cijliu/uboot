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

#ifndef __HDMI2TX_DPHY_REG_C_UNION_DEFINE_H__
#define __HDMI2TX_DPHY_REG_C_UNION_DEFINE_H__

/* Define the union U_HDMITX_INSSC_SET */
/* Define the union U_HDMITX_INSSC_SET,ATTR:RW,ADDR:0,INIT:C0000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_set               : 24  ; /* [23:0] */
        unsigned int    reg_set_load          : 1  ; /* [24] */
        unsigned int    reg_sscfifo_tune_en   : 1  ; /* [25] */
        unsigned int    reg_sscfifo_depth_clr : 1  ; /* [26] */
        unsigned int    reg_deep_color        : 2  ; /* [28:27] */
        unsigned int    reg_ssc_mode          : 1  ; /* [29] */
        unsigned int    reg_pllfbmash111_en   : 1  ; /* [30] */
        unsigned int    reg_sscin_bypass_en   : 1  ; /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_INSSC_SET;

/* Define the union U_HDMITX_INSSC_FIFO */
/* Define the union U_HDMITX_INSSC_FIFO,ATTR:RW,ADDR:4,INIT:01C01001,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_tune_step            : 8  ; /* [7:0] */
        unsigned int    reg_sscfifo_lower_thresh : 10  ; /* [17:8] */
        unsigned int    reg_sscfifo_upper_thresh : 10  ; /* [27:18] */
        unsigned int    reg_tune_reverse         : 1  ; /* [28] */
        unsigned int    reg_ssc_sync             : 1  ; /* [29] */
        unsigned int    rsv_0                    : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_INSSC_FIFO;

/* Define the union U_HDMITX_INSSC_STEP */
/* Define the union U_HDMITX_INSSC_STEP,ATTR:RW,ADDR:8,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_step  : 10  ; /* [9:0] */
        unsigned int    reg_span  : 14  ; /* [23:10] */
        unsigned int    reg_testd : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_INSSC_STEP;

/* Define the union U_HDMITX_INSSC_TUNE */
/* Define the union U_HDMITX_INSSC_TUNE,ATTR:RW,ADDR:C,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_tune_interval : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_INSSC_TUNE;

/* Define the union U_HDMITX_DPHY_RST */
/* Define the union U_HDMITX_DPHY_RST,ATTR:RW,ADDR:C,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_dphy_srst_req : 1   ; /* [0] */
        unsigned int    rsv_0             : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_DPHY_RST;

/* Define the union U_HDMITX_SSC_HK */
/* Define the union U_HDMITX_SSC_HK,ATTR:RW,ADDR:14,INIT:00000000,MASK:7f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_dnum           : 5  ; /* [4:0] */
        unsigned int    reg_hkmash_en      : 1  ; /* [5] */
        unsigned int    reg_mash111_hk_sel : 1  ; /* [6] */
        unsigned int    rsv_1              : 25  ; /* [31:7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSC_HK;

/* Define the union U_HDMITX_SSCIN_STATUS0 */
/* Define the union U_HDMITX_SSCIN_STATUS0,ATTR:RW,ADDR:20,INIT:00000000,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sscin_span_cnt     : 15  ; /* [14:0] */
        unsigned int    sscin_segment      : 2  ; /* [16:15] */
        unsigned int    sscin_stop_flag    : 1  ; /* [17] */
        unsigned int    sscin_reverse_flag : 1  ; /* [18] */
        unsigned int    sscin_div          : 5  ; /* [23:19] */
        unsigned int    rsv_2              : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCIN_STATUS0;

/* Define the union U_HDMITX_SSCIN_STATUS1 */
/* Define the union U_HDMITX_SSCIN_STATUS1,ATTR:RW,ADDR:24,INIT:00000000,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sscin_ssc_offset : 24  ; /* [23:0] */
        unsigned int    rsv_3            : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCIN_STATUS1;

/* Define the union U_HDMITX_SSCIN_STATUS2 */
/* Define the union U_HDMITX_SSCIN_STATUS2,ATTR:RW,ADDR:28,INIT:00000000,MASK:fffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sscin_sscfifo_depth_max : 10  ; /* [9:0] */
        unsigned int    sscin_sscfifo_depth_min : 10  ; /* [19:10] */
        unsigned int    rsv_4                   : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCIN_STATUS2;

/* Define the union U_HDMITX_SSCFB_STATUS0 */
/* Define the union U_HDMITX_SSCFB_STATUS0,ATTR:RW,ADDR:2C,INIT:00000000,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sscfb_span_cnt     : 15  ; /* [14:0] */
        unsigned int    sscfb_segment      : 2  ; /* [16:15] */
        unsigned int    sscfb_stop_flag    : 1  ; /* [17] */
        unsigned int    sscfb_reverse_flag : 1  ; /* [18] */
        unsigned int    sscfb_div          : 5  ; /* [23:19] */
        unsigned int    rsv_5              : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCFB_STATUS0;

/* Define the union U_HDMITX_SSCFB_STATUS1 */
/* Define the union U_HDMITX_SSCFB_STATUS1,ATTR:RW,ADDR:30,INIT:00000000,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sscfb_ssc_offset : 24  ; /* [23:0] */
        unsigned int    rsv_6            : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCFB_STATUS1;

/* Define the union U_HDMITX_SSCFB_STATUS2 */
/* Define the union U_HDMITX_SSCFB_STATUS2,ATTR:RW,ADDR:34,INIT:00000000,MASK:fffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sscfb_sscfifo_depth_max : 10  ; /* [9:0] */
        unsigned int    sscfb_sscfifo_depth_min : 10  ; /* [19:10] */
        unsigned int    rsv_7                   : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCFB_STATUS2;

/* Define the union U_HDMITX_SSCFBMASH111_STATUS0 */
/* Define the union U_HDMITX_SSCFBMASH111_STATUS0,ATTR:RW,ADDR:38,INIT:00000000,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbmash_span_cnt     : 15  ; /* [14:0] */
        unsigned int    fbmash_segment      : 2  ; /* [16:15] */
        unsigned int    fbmash_stop_flag    : 1  ; /* [17] */
        unsigned int    fbmash_reverse_flag : 1  ; /* [18] */
        unsigned int    fbmash_div          : 5  ; /* [23:19] */
        unsigned int    rsv_8               : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCFBMASH111_STATUS0;

/* Define the union U_HDMITX_SSCFBMASH111_STATUS1 */
/* Define the union U_HDMITX_SSCFBMASH111_STATUS1,ATTR:RW,ADDR:3C,INIT:00000000,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbmash_ssc_offset : 24  ; /* [23:0] */
        unsigned int    rsv_9             : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCFBMASH111_STATUS1;

/* Define the union U_HDMITX_SSCFBMASH111_STATUS2 */
/* Define the union U_HDMITX_SSCFBMASH111_STATUS2,ATTR:RW,ADDR:40,INIT:00000000,MASK:fffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbmash_sscfifo_depth_max : 10  ; /* [9:0] */
        unsigned int    fbmash_sscfifo_depth_min : 10  ; /* [19:10] */
        unsigned int    rsv_10                   : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_SSCFBMASH111_STATUS2;

/* Define the union U_HDMITX_AFIFO_DATA_H */
/* Define the union U_HDMITX_AFIFO_DATA_H,ATTR:RW,ADDR:4C,INIT:00000000,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_aphy_data_ch0_h : 10  ; /* [9:0] */
        unsigned int    reg_aphy_data_ch1_h : 10  ; /* [19:10] */
        unsigned int    reg_aphy_data_ch2_h : 10  ; /* [29:20] */
        unsigned int    rsv_11              : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_AFIFO_DATA_H;

/* Define the union U_HDMITX_AFIFO_DATA_SEL */
/* Define the union U_HDMITX_AFIFO_DATA_SEL,ATTR:RW,ADDR:50,INIT:00003E00,MASK:7ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_txafifo_status_rst : 1  ; /* [0] */
        unsigned int    reg_txafifo_rst        : 1  ; /* [1] */
        unsigned int    reg_aphy_data_ch0_sel  : 1  ; /* [2] */
        unsigned int    reg_aphy_data_ch1_sel  : 1  ; /* [3] */
        unsigned int    reg_aphy_data_ch2_sel  : 1  ; /* [4] */
        unsigned int    txafifo_aful_status    : 1  ; /* [5] */
        unsigned int    txafifo_full_status    : 1  ; /* [6] */
        unsigned int    txafifo_aempt_status   : 1  ; /* [7] */
        unsigned int    txafifo_empt_status    : 1  ; /* [8] */
        unsigned int    reg_aphy_data_clk_h    : 10  ; /* [18:9] */
        unsigned int    rsv_12                 : 13  ; /* [31:19] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_AFIFO_DATA_SEL;

/* Define the union U_HDMITX_AFIFO_CLK */
/* Define the union U_HDMITX_AFIFO_CLK,ATTR:RW,ADDR:54,INIT:01F07C1F,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_aphy_data_clk_l : 30  ; /* [29:0] */
        unsigned int    rsv_13              : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_AFIFO_CLK;

/* Define the union U_HDMITX_AFIFO_DATA_L */
/* Define the union U_HDMITX_AFIFO_DATA_L,ATTR:RW,ADDR:58,INIT:00000000,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_aphy_data_ch0 : 10  ; /* [9:0] */
        unsigned int    reg_aphy_data_ch1 : 10  ; /* [19:10] */
        unsigned int    reg_aphy_data_ch2 : 10  ; /* [29:20] */
        unsigned int    rsv_14            : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_AFIFO_DATA_L;

/* Define the union U_HDMITX_AFIFO_CHANNEL */
/* Define the union U_HDMITX_AFIFO_CHANNEL,ATTR:RW,ADDR:5C,INIT:00003440,MASK:7fff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_prbs7_en        : 1  ; /* [0] */
        unsigned int    reg_prbs7_clr       : 1  ; /* [1] */
        unsigned int    reg_prbs7_errinject : 1  ; /* [2] */
        unsigned int    reg_ck_dataout_sel  : 3  ; /* [5:3] */
        unsigned int    reg_d0_dataout_sel  : 3  ; /* [8:6] */
        unsigned int    reg_d1_dataout_sel  : 3  ; /* [11:9] */
        unsigned int    reg_d2_dataout_sel  : 3  ; /* [14:12] */
        unsigned int    rsv_15              : 17  ; /* [31:15] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_AFIFO_CHANNEL;

/* Define the union U_APHY_STATUS0 */
/* Define the union U_APHY_STATUS0,ATTR:RW,ADDR:60,INIT:00000000,MASK:7*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ad_rxsense      : 1  ; /* [0] */
        unsigned int    ad_txpll_hvflag : 1  ; /* [1] */
        unsigned int    ad_txpll_lock   : 1  ; /* [2] */
        unsigned int    rsv_16          : 29  ; /* [31:3] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_STATUS0;

/* Define the union U_APHY_TOP_PD */
/* Define the union U_APHY_TOP_PD,ATTR:RW,ADDR:64,INIT:0017FFFF,MASK:7fffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_gc_pd         : 4  ; /* [3:0] */
        unsigned int    reg_gc_pd_bist    : 1  ; /* [4] */
        unsigned int    reg_gc_pd_de      : 4  ; /* [8:5] */
        unsigned int    reg_gc_pd_ldo     : 2  ; /* [10:9] */
        unsigned int    reg_gc_pd_rterm   : 8  ; /* [18:11] */
        unsigned int    reg_gc_pd_rxsense : 1  ; /* [19] */
        unsigned int    reg_gc_txpll_pd   : 1  ; /* [20] */
        unsigned int    reg_divsel        : 2  ; /* [22:21] */
        unsigned int    rsv_17            : 9  ; /* [31:23] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_TOP_PD;

/* Define the union U_APHY_DRIVER_IMAIN */
/* Define the union U_APHY_DRIVER_IMAIN,ATTR:RW,ADDR:68,INIT:00C71C60,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_isel_main_clk    : 6  ; /* [5:0] */
        unsigned int    reg_isel_main_d0     : 6  ; /* [11:6] */
        unsigned int    reg_isel_main_d1     : 6  ; /* [17:12] */
        unsigned int    reg_isel_main_d2     : 6  ; /* [23:18] */
        unsigned int    reg_isel_main_de_clk : 6  ; /* [29:24] */
        unsigned int    rsv_18               : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_DRIVER_IMAIN;

/* Define the union U_APHY_DRIVER_IPRE */
/* Define the union U_APHY_DRIVER_IPRE,ATTR:RW,ADDR:6C,INIT:18180000,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_isel_main_de_d0 : 6  ; /* [5:0] */
        unsigned int    reg_isel_main_de_d1 : 6  ; /* [11:6] */
        unsigned int    reg_isel_main_de_d2 : 6  ; /* [17:12] */
        unsigned int    reg_isel_pre_clk    : 6  ; /* [23:18] */
        unsigned int    reg_isel_pre_d0     : 6  ; /* [29:24] */
        unsigned int    rsv_19              : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_DRIVER_IPRE;

/* Define the union U_APHY_DRIVER_IPREDE */
/* Define the union U_APHY_DRIVER_IPREDE,ATTR:RW,ADDR:70,INIT:00000618,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_isel_pre_d1     : 6  ; /* [5:0] */
        unsigned int    reg_isel_pre_d2     : 6  ; /* [11:6] */
        unsigned int    reg_isel_pre_de_clk : 6  ; /* [17:12] */
        unsigned int    reg_isel_pre_de_d0  : 6  ; /* [23:18] */
        unsigned int    reg_isel_pre_de_d1  : 6  ; /* [29:24] */
        unsigned int    rsv_20              : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_DRIVER_IPREDE;

/* Define the union U_APHY_DRIVER_RPRE */
/* Define the union U_APHY_DRIVER_RPRE,ATTR:RW,ADDR:74,INIT:0001B780,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_isel_pre_de_d2  : 6  ; /* [5:0] */
        unsigned int    reg_rsel_pre_clk    : 3  ; /* [8:6] */
        unsigned int    reg_rsel_pre_d0     : 3  ; /* [11:9] */
        unsigned int    reg_rsel_pre_d1     : 3  ; /* [14:12] */
        unsigned int    reg_rsel_pre_d2     : 3  ; /* [17:15] */
        unsigned int    reg_rsel_pre_de_clk : 3  ; /* [20:18] */
        unsigned int    reg_rsel_pre_de_d0  : 3  ; /* [23:21] */
        unsigned int    reg_rsel_pre_de_d1  : 3  ; /* [26:24] */
        unsigned int    reg_rsel_pre_de_d2  : 3  ; /* [29:27] */
        unsigned int    rsv_21              : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_DRIVER_RPRE;

/* Define the union U_APHY_RTERM_CTRL */
/* Define the union U_APHY_RTERM_CTRL,ATTR:RW,ADDR:78,INIT:60606060,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_rt_clk : 8  ; /* [7:0] */
        unsigned int    reg_rt_d0  : 8  ; /* [15:8] */
        unsigned int    reg_rt_d1  : 8  ; /* [23:16] */
        unsigned int    reg_rt_d2  : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_RTERM_CTRL;

/* Define the union U_APHY_MISC_CTRL */
/* Define the union U_APHY_MISC_CTRL,ATTR:RW,ADDR:7C,INIT:00000000,MASK:7ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_sel_ldo     : 6  ; /* [5:0] */
        unsigned int    reg_sel_rxsense : 3  ; /* [8:6] */
        unsigned int    reg_sr_clk      : 2  ; /* [10:9] */
        unsigned int    rsv_22          : 21  ; /* [31:11] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_MISC_CTRL;

/* Define the union U_APHY_TEST_CTRL */
/* Define the union U_APHY_TEST_CTRL,ATTR:RW,ADDR:80,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_test    : 16  ; /* [15:0] */
        unsigned int    reg_test_dc : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_TEST_CTRL;

/* Define the union U_APHY_TXPLL_CTRL */
/* Define the union U_APHY_TXPLL_CTRL,ATTR:RW,ADDR:8C,INIT:0000C400,MASK:fffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_txpll_clkin_sel         : 2  ; /* [1:0] */
        unsigned int    reg_txpll_divsel_in         : 3  ; /* [4:2] */
        unsigned int    reg_txpll_divsel_loop       : 7  ; /* [11:5] */
        unsigned int    reg_txpll_divsel_post       : 2  ; /* [13:12] */
        unsigned int    reg_txpll_icp_ictrl         : 4  ; /* [17:14] */
        unsigned int    reg_gc_txpll_en_ref_fb_div2 : 1  ; /* [18] */
        unsigned int    reg_gc_txpll_en_sscdiv      : 1  ; /* [19] */
        unsigned int    rsv_23                      : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_TXPLL_CTRL;

/* Define the union U_APHY_TXPLL_TEST */
/* Define the union U_APHY_TXPLL_TEST,ATTR:RW,ADDR:90,INIT:00000000,MASK:fffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_txpll_test : 20  ; /* [19:0] */
        unsigned int    rsv_24         : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_APHY_TXPLL_TEST;

/* Define the union U_PLL_LOCK_CTRL */
/* Define the union U_PLL_LOCK_CTRL,ATTR:RW,ADDR:94,INIT:0288080F,MASK:7ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_fb_div_sel       : 2  ; /* [1:0] */
        unsigned int    reg_fb_prd_sel       : 2  ; /* [3:2] */
        unsigned int    reg_ref_lock_timer   : 8  ; /* [11:4] */
        unsigned int    reg_ref_unlock_timer : 8  ; /* [19:12] */
        unsigned int    reg_pll_lock_sel     : 2  ; /* [21:20] */
        unsigned int    reg_pll_unlock_sel   : 1  ; /* [22] */
        unsigned int    reg_pll_lockext_sel  : 3  ; /* [25:23] */
        unsigned int    reg_pll_lock_times   : 1  ; /* [26] */
        unsigned int    rsv_25               : 5  ; /* [31:27] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PLL_LOCK_CTRL;

/* Define the union U_PLL_LOCK_STATUS */
/* Define the union U_PLL_LOCK_STATUS,ATTR:RW,ADDR:98,INIT:00000000,MASK:1fffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clk_fb_exist     : 1  ; /* [0] */
        unsigned int    pll_ena_edge     : 1  ; /* [1] */
        unsigned int    test_pll_cnt     : 17  ; /* [18:2] */
        unsigned int    pll_lock_oneshot : 1  ; /* [19] */
        unsigned int    hdmi_clk_lock    : 1  ; /* [20] */
        unsigned int    rsv_26           : 11  ; /* [31:21] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PLL_LOCK_STATUS;

/* Define the union U_REG_TXDPHY_DUMMY_CTRL */
/* Define the union U_REG_TXDPHY_DUMMY_CTRL,ATTR:RW,ADDR:9C,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_txdphy_dummy_ctrl : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REG_TXDPHY_DUMMY_CTRL;

/* Define the union U_HDMITX_FBSSC_SET */
/* Define the union U_HDMITX_FBSSC_SET,ATTR:RW,ADDR:B0,INIT:01640000,MASK:fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_set_fb               : 24  ; /* [23:0] */
        unsigned int    reg_set_load_fb          : 1  ; /* [24] */
        unsigned int    reg_sscfifo_tune_en_fb   : 1  ; /* [25] */
        unsigned int    reg_sscfifo_depth_clr_fb : 1  ; /* [26] */
        unsigned int    reg_ssc_mode_fb          : 1  ; /* [27] */
        unsigned int    rsv_27                   : 4  ; /* [31:28] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_FBSSC_SET;

/* Define the union U_HDMITX_FBSSC_FIFO */
/* Define the union U_HDMITX_FBSSC_FIFO,ATTR:RW,ADDR:B4,INIT:01C01001,MASK:3fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_tune_step_fb            : 8  ; /* [7:0] */
        unsigned int    reg_sscfifo_lower_thresh_fb : 10  ; /* [17:8] */
        unsigned int    reg_sscfifo_upper_thresh_fb : 10  ; /* [27:18] */
        unsigned int    reg_tune_reverse_fb         : 1  ; /* [28] */
        unsigned int    reg_ssc_sync_fb             : 1  ; /* [29] */
        unsigned int    rsv_28                      : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_FBSSC_FIFO;

/* Define the union U_HDMITX_FBSSC_STEP */
/* Define the union U_HDMITX_FBSSC_STEP,ATTR:RW,ADDR:B8,INIT:00074046,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_step_fb  : 10  ; /* [9:0] */
        unsigned int    reg_span_fb  : 14  ; /* [23:10] */
        unsigned int    reg_testd_fb : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_FBSSC_STEP;

/* Define the union U_HDMITX_FBSSC_TUNE */
/* Define the union U_HDMITX_FBSSC_TUNE,ATTR:RW,ADDR:BC,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_tune_interval_fb : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMITX_FBSSC_TUNE;


//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_HDMITX_INSSC_SET            HDMITX_INSSC_SET            ; /* 0 */
    volatile U_HDMITX_INSSC_FIFO           HDMITX_INSSC_FIFO           ; /* 4 */
    volatile U_HDMITX_INSSC_STEP           HDMITX_INSSC_STEP           ; /* 8 */
    volatile U_HDMITX_INSSC_TUNE           HDMITX_INSSC_TUNE           ; /* C */
    volatile U_HDMITX_DPHY_RST             HDMITX_DPHY_RST             ; /* 0x10 */
    volatile U_HDMITX_SSC_HK               HDMITX_SSC_HK               ; /* 14 */
    volatile unsigned int           reserved_1[2]                     ; /* 0x18~0x1c */
    volatile U_HDMITX_SSCIN_STATUS0        HDMITX_SSCIN_STATUS0        ; /* 20 */
    volatile U_HDMITX_SSCIN_STATUS1        HDMITX_SSCIN_STATUS1        ; /* 24 */
    volatile U_HDMITX_SSCIN_STATUS2        HDMITX_SSCIN_STATUS2        ; /* 28 */
    volatile U_HDMITX_SSCFB_STATUS0        HDMITX_SSCFB_STATUS0        ; /* 2C */
    volatile U_HDMITX_SSCFB_STATUS1        HDMITX_SSCFB_STATUS1        ; /* 30 */
    volatile U_HDMITX_SSCFB_STATUS2        HDMITX_SSCFB_STATUS2        ; /* 34 */
    volatile U_HDMITX_SSCFBMASH111_STATUS0 HDMITX_SSCFBMASH111_STATUS0 ; /* 38 */
    volatile U_HDMITX_SSCFBMASH111_STATUS1 HDMITX_SSCFBMASH111_STATUS1 ; /* 3C */
    volatile U_HDMITX_SSCFBMASH111_STATUS2 HDMITX_SSCFBMASH111_STATUS2 ; /* 40 */
    volatile unsigned int           reserved_2[2]                     ; /* 0x44~0x48 */
    volatile U_HDMITX_AFIFO_DATA_H         HDMITX_AFIFO_DATA_H         ; /* 4C */
    volatile U_HDMITX_AFIFO_DATA_SEL       HDMITX_AFIFO_DATA_SEL       ; /* 50 */
    volatile U_HDMITX_AFIFO_CLK            HDMITX_AFIFO_CLK            ; /* 54 */
    volatile U_HDMITX_AFIFO_DATA_L         HDMITX_AFIFO_DATA_L         ; /* 58 */
    volatile U_HDMITX_AFIFO_CHANNEL        HDMITX_AFIFO_CHANNEL        ; /* 5C */
    volatile U_APHY_STATUS0                APHY_STATUS0                ; /* 60 */
    volatile U_APHY_TOP_PD                 APHY_TOP_PD                 ; /* 64 */
    volatile U_APHY_DRIVER_IMAIN           APHY_DRIVER_IMAIN           ; /* 68 */
    volatile U_APHY_DRIVER_IPRE            APHY_DRIVER_IPRE            ; /* 6C */
    volatile U_APHY_DRIVER_IPREDE          APHY_DRIVER_IPREDE          ; /* 70 */
    volatile U_APHY_DRIVER_RPRE            APHY_DRIVER_RPRE            ; /* 74 */
    volatile U_APHY_RTERM_CTRL             APHY_RTERM_CTRL             ; /* 78 */
    volatile U_APHY_MISC_CTRL              APHY_MISC_CTRL              ; /* 7C */
    volatile U_APHY_TEST_CTRL              APHY_TEST_CTRL              ; /* 80 */
    volatile unsigned int           reserved_3[2]                     ; /* 0x84~0x88 */
    volatile U_APHY_TXPLL_CTRL             APHY_TXPLL_CTRL             ; /* 8C */
    volatile U_APHY_TXPLL_TEST             APHY_TXPLL_TEST             ; /* 90 */
    volatile U_PLL_LOCK_CTRL               PLL_LOCK_CTRL               ; /* 94 */
    volatile U_PLL_LOCK_STATUS             PLL_LOCK_STATUS             ; /* 98 */
    volatile U_REG_TXDPHY_DUMMY_CTRL       REG_TXDPHY_DUMMY_CTRL       ; /* 9C */
    volatile unsigned int           reserved_4[4]                     ; /* 0xa0~0xac */
    volatile U_HDMITX_FBSSC_SET            HDMITX_FBSSC_SET            ; /* B0 */
    volatile U_HDMITX_FBSSC_FIFO           HDMITX_FBSSC_FIFO           ; /* B4 */
    volatile U_HDMITX_FBSSC_STEP           HDMITX_FBSSC_STEP           ; /* B8 */
    volatile U_HDMITX_FBSSC_TUNE           HDMITX_FBSSC_TUNE        ; /* 0xbc */

} S_hdmi2tx_dphy_reg_REGS_TYPE;

/* Declare the struct pointor of the module hdmi2tx_dphy_reg */
//extern volatile S_hdmi2tx_dphy_reg_REGS_TYPE *gophdmi2tx_dphy_regAllReg;

HI_S32 HDMI_HDMITX_PHY_reg_Init(HI_CHAR *pcAddr);
HI_S32 HDMI_HDMITX_PHY_reg_DeInit(HI_VOID);

/* Declare the functions that set the member value */
HI_S32 HDMI_HDMITX_INSSC_SET_reg_pllfbmash111_enSet(HI_U32 ureg_pllfbmash111_en);
HI_S32 HDMI_HDMITX_INSSC_SET_reg_sscin_bypass_enSet(HI_U32 ureg_sscin_bypass_en);
/* phy software rest use this reg */
HI_S32 HDMI_HDMITX_DPHY_RST_reg_rstSet(HI_U32 ureg_rst);
HI_S32 HDMI_HDMITX_AFIFO_DATA_SEL_reg_aphy_data_clk_hSet(HI_U32 ureg_aphy_data_clk_h);
HI_S32 HDMI_HDMITX_AFIFO_CLK_reg_aphy_data_clk_lSet(HI_U32 ureg_aphy_data_clk_l);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pdSet(HI_U32 ureg_gc_pd);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pdGet(HI_VOID);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_bistSet(HI_U32 ureg_gc_pd_bist);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_bistGet(HI_VOID);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_deSet(HI_U32 ureg_gc_pd_de);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_deGet(HI_VOID);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_ldoSet(HI_U32 ureg_gc_pd_ldo);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_ldoGet(HI_VOID);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_rtermSet(HI_U32 ureg_gc_pd_rterm);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_rxsenseSet(HI_U32 ureg_gc_pd_rxsense);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_pd_rxsenseGet(HI_VOID);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_txpll_pdSet(HI_U32 ureg_gc_txpll_pd);
HI_S32 HDMI_APHY_TOP_PD_reg_gc_txpll_pdGet(HI_VOID);
HI_S32 HDMI_APHY_TOP_PD_reg_divselSet(HI_U32 ureg_divsel);
HI_S32 HDMI_APHY_DRIVER_IMAIN_reg_isel_main_clkSet(HI_U32 ureg_isel_main_clk);
HI_S32 HDMI_APHY_DRIVER_IMAIN_reg_isel_main_d0Set(HI_U32 ureg_isel_main_d0);
HI_S32 HDMI_APHY_DRIVER_IMAIN_reg_isel_main_d1Set(HI_U32 ureg_isel_main_d1);
HI_S32 HDMI_APHY_DRIVER_IMAIN_reg_isel_main_d2Set(HI_U32 ureg_isel_main_d2);
HI_S32 HDMI_APHY_DRIVER_IMAIN_reg_isel_main_de_clkSet(HI_U32 ureg_isel_main_de_clk);
HI_S32 HDMI_APHY_DRIVER_IMAIN_reg_isel_main_de_clkGet(HI_VOID);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_main_de_d0Set(HI_U32 ureg_isel_main_de_d0);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_main_de_d0Get(HI_VOID);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_main_de_d1Set(HI_U32 ureg_isel_main_de_d1);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_main_de_d1Get(HI_VOID);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_main_de_d2Set(HI_U32 ureg_isel_main_de_d2);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_main_de_d2Get(HI_VOID);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_pre_clkSet(HI_U32 ureg_isel_pre_clk);
HI_S32 HDMI_APHY_DRIVER_IPRE_reg_isel_pre_d0Set(HI_U32 ureg_isel_pre_d0);
HI_S32 HDMI_APHY_DRIVER_IPREDE_reg_isel_pre_d1Set(HI_U32 ureg_isel_pre_d1);
HI_S32 HDMI_APHY_DRIVER_IPREDE_reg_isel_pre_d2Set(HI_U32 ureg_isel_pre_d2);
HI_S32 HDMI_APHY_DRIVER_IPREDE_reg_isel_pre_de_clkSet(HI_U32 ureg_isel_pre_de_clk);
HI_S32 HDMI_APHY_DRIVER_IPREDE_reg_isel_pre_de_d0Set(HI_U32 ureg_isel_pre_de_d0);
HI_S32 HDMI_APHY_DRIVER_IPREDE_reg_isel_pre_de_d1Set(HI_U32 ureg_isel_pre_de_d1);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_isel_pre_de_d2Set(HI_U32 ureg_isel_pre_de_d2);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_clkSet(HI_U32 ureg_rsel_pre_clk);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_d0Set(HI_U32 ureg_rsel_pre_d0);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_d1Set(HI_U32 ureg_rsel_pre_d1);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_d2Set(HI_U32 ureg_rsel_pre_d2);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_de_clkSet(HI_U32 ureg_rsel_pre_de_clk);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_de_d0Set(HI_U32 ureg_rsel_pre_de_d0);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_de_d1Set(HI_U32 ureg_rsel_pre_de_d1);
HI_S32 HDMI_APHY_DRIVER_RPRE_reg_rsel_pre_de_d2Set(HI_U32 ureg_rsel_pre_de_d2);
HI_S32 HDMI_APHY_RTERM_CTRL_reg_rt_clkSet(HI_U32 ureg_rt_clk);
HI_S32 HDMI_APHY_RTERM_CTRL_reg_rt_d0Set(HI_U32 ureg_rt_d0);
HI_S32 HDMI_APHY_RTERM_CTRL_reg_rt_d1Set(HI_U32 ureg_rt_d1);
HI_S32 HDMI_APHY_RTERM_CTRL_reg_rt_d2Set(HI_U32 ureg_rt_d2);
HI_S32 HDMI_APHY_TXPLL_CTRL_reg_txpll_divsel_loopSet(HI_U32 ureg_txpll_divsel_loop);
HI_S32 HDMI_APHY_TXPLL_CTRL_reg_txpll_icp_ictrlSet(HI_U32 ureg_txpll_icp_ictrl);
HI_S32 HDMI_APHY_TXPLL_CTRL_reg_gc_txpll_en_sscdivSet(HI_U32 ureg_gc_txpll_en_sscdiv);
HI_S32 HDMI_APHY_TXPLL_TEST_reg_txpll_testSet(HI_U32 ureg_txpll_test);
HI_S32 HDMI_HDMITX_FBSSC_SET_reg_set_fbSet(HI_U32 ureg_set_fb);
HI_S32 HDMI_HDMITX_FBSSC_SET_reg_set_load_fbSet(HI_U32 ureg_set_load_fb);
HI_S32 HDMI_HDMITX_FBSSC_SET_reg_ssc_mode_fbSet(HI_U32 ureg_ssc_mode_fb);
HI_S32 HDMI_HDMITX_FBSSC_STEP_reg_step_fbSet(HI_U32 ureg_step_fb);
HI_S32 HDMI_HDMITX_FBSSC_STEP_reg_step_fbGet(HI_VOID);
HI_S32 HDMI_HDMITX_FBSSC_STEP_reg_span_fbSet(HI_U32 ureg_span_fb);
HI_S32 HDMI_HDMITX_FBSSC_STEP_reg_span_fbGet(HI_VOID);
#endif // __HDMI2TX_DPHY_REG_C_UNION_DEFINE_H__
