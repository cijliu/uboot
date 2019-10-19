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

#ifndef __HI3559A_DPHY_REG_C_UNION_DEFINE_H__
#define __HI3559A_DPHY_REG_C_UNION_DEFINE_H__
#define prOffset 0x20000
/* Define the union U_T2GPPORT0 */
/* Define the union U_T2GPPORT0,ATTR:RW,ADDR:0,INIT:00000000,MASK:ffff,CMMNT:T2GPPORT0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpport0 : 16  ; /* [15:0] */
        unsigned int    rsv_0   : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_T2GPPORT0;

/* Define the union U_T2GPPORT1 */
/* Define the union U_T2GPPORT1,ATTR:RW,ADDR:4,INIT:00000000,MASK:ffff,CMMNT:T2GPPORT1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpport1 : 16  ; /* [15:0] */
        unsigned int    rsv_1   : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_T2GPPORT1;

/* Define the union U_PHY_CSEN */
/* Define the union U_PHY_CSEN,ATTR:RW,ADDR:8,INIT:00000000,MASK:ffff,CMMNT:stb_cs_en*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stb_cs_en : 16  ; /* [15:0] */
        unsigned int    rsv_2     : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PHY_CSEN;

/* Define the union U_PHY_WR */
/* Define the union U_PHY_WR,ATTR:RW,ADDR:C,INIT:00000000,MASK:1,CMMNT:stb_write_en*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stb_wen : 1  ; /* [0] */
        unsigned int    rsv_3   : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PHY_WR;

/* Define the union U_RESETN */
/* Define the union U_RESETN,ATTR:RW,ADDR:10,INIT:00000000,MASK:1,CMMNT:stb_reset*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    resetn : 1  ; /* [0] */
        unsigned int    rsv_4  : 31 ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_RESETN;

/* Define the union U_PHY_ADDR */
/* Define the union U_PHY_ADDR,ATTR:RW,ADDR:14,INIT:00000000,MASK:f,CMMNT:stb_addr*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stb_addr : 4  ; /* [3:0] */
        unsigned int    rsv_5    : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PHY_ADDR;

/* Define the union U_PHY_WDATA */
/* Define the union U_PHY_WDATA,ATTR:RW,ADDR:18,INIT:00000000,MASK:ff,CMMNT:stb_wdata*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stb_wdata : 8  ; /* [7:0] */
        unsigned int    rsv_6     : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PHY_WDATA;

/* Define the union U_PHY_RDATA */
/* Define the union U_PHY_RDATA,ATTR:RW,ADDR:1C,INIT:00000000,MASK:ff,CMMNT:stb_rdata*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stb_rdata : 8  ; /* [7:0] */
        unsigned int    rsv_7     : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PHY_RDATA;

/* Define the union U_ZCALREG */
/* Define the union U_ZCALREG,ATTR:RW,ADDR:20,INIT:00000000,MASK:fff,CMMNT:ZCALREG*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zcal     : 5  ; /* [4:0] */
        unsigned int    zcaldone : 1  ; /* [5] */
        unsigned int    zcalsub  : 2  ; /* [7:6] */
        unsigned int    rxsense  : 4  ; /* [11:8] */
        unsigned int    rsv_8    : 20  ; /* [31:12] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ZCALREG;

/* Define the union U_ZCALCLK */
/* Define the union U_ZCALCLK,ATTR:RW,ADDR:24,INIT:00000000,MASK:1,CMMNT:ZCALCLK*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zcalclk : 1  ; /* [0] */
        unsigned int    rsv_9   : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ZCALCLK;

/* Define the union U_SHORTDET */
/* Define the union U_SHORTDET,ATTR:RW,ADDR:28,INIT:00000000,MASK:f,CMMNT:SHORTDET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    c0shortdet  : 1  ; /* [0] */
        unsigned int    c1shortdet  : 1  ; /* [1] */
        unsigned int    c2shortdet  : 1  ; /* [2] */
        unsigned int    clkshortdet : 1  ; /* [3] */
        unsigned int    rsv_10      : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SHORTDET;

/* Define the union U_DET */
/* Define the union U_DET,ATTR:RW,ADDR:2C,INIT:00000000,MASK:1f000,CMMNT:DET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rsv_11        : 12  ; /* [11:0] */
        unsigned int    t2_plllkvdetl : 1  ; /* [12] */
        unsigned int    t2_plllkcdet  : 1  ; /* [13] */
        unsigned int    t2_plllkvdet2 : 1  ; /* [14] */
        unsigned int    t2_lkvdetlow  : 1  ; /* [15] */
        unsigned int    t2_lkvdethigh : 1  ; /* [16] */
        unsigned int    rsv_12        : 15  ; /* [31:17] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DET;

/* Define the union U_FDSRCPARAM */
/* Define the union U_FDSRCPARAM,ATTR:RW,ADDR:30,INIT:00000404,MASK:fffff,CMMNT:FDSRCPARAM*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_lock_val      : 8  ; /* [7:0] */
        unsigned int    src_lock_cnt      : 8  ; /* [15:8] */
        unsigned int    src_enable        : 1  ; /* [16] */
        unsigned int    fdsrcparam_unused : 3  ; /* [19:17] */
        unsigned int    rsv_13            : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDSRCPARAM;

/* Define the union U_FDSRCFREQ */
/* Define the union U_FDSRCFREQ,ATTR:RW,ADDR:34,INIT:00000000,MASK:ffffff,CMMNT:FDSRCFREQ*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_cnt_opt        : 3  ; /* [2:0] */
        unsigned int    fdsrcfreq_unused_1 : 1  ; /* [3] */
        unsigned int    src_freq_opt       : 2  ; /* [5:4] */
        unsigned int    fdsrcfreq_unused_2 : 2  ; /* [7:6] */
        unsigned int    src_freq_ext       : 16  ; /* [23:8] */
        unsigned int    rsv_14             : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDSRCFREQ;

/* Define the union U_FDSRCRES */
/* Define the union U_FDSRCRES,ATTR:RW,ADDR:38,INIT:00000000,MASK:ffffff,CMMNT:FDSRCRES*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_det_stat : 4  ; /* [3:0] */
        unsigned int    src_cnt_out  : 20  ; /* [23:4] */
        unsigned int    rsv_15       : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDSRCRES;

/* Define the union U_CTSET0 */
/* Define the union U_CTSET0,ATTR:RW,ADDR:3C,INIT:00000000,MASK:f,CMMNT:CTSET0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_enable      : 1  ; /* [0] */
        unsigned int    i_run         : 1  ; /* [1] */
        unsigned int    ctset0_unused : 2  ; /* [3:2] */
        unsigned int    rsv_16        : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CTSET0;

/* Define the union U_CTSET1 */
/* Define the union U_CTSET1,ATTR:RW,ADDR:40,INIT:00000000,MASK:ffffffff,CMMNT:CTSET1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_mpll_fcon   : 10  ; /* [9:0] */
        unsigned int    i_mpll_divn   : 3  ; /* [12:10] */
        unsigned int    i_mpll_ctlck  : 1  ; /* [13] */
        unsigned int    ctset1_unused : 18  ; /* [31:14] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CTSET1;

/* Define the union U_FCCNTR0 */
/* Define the union U_FCCNTR0,ATTR:RW,ADDR:48,INIT:00000000,MASK:ffffffff,CMMNT:FCCNTR0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_deci_cnt_len     : 8  ; /* [7:0] */
        unsigned int    i_vco_st_wait_len  : 8  ; /* [15:8] */
        unsigned int    i_vco_end_wait_len : 8  ; /* [23:16] */
        unsigned int    i_ref_cnt_len      : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCCNTR0;

/* Define the union U_FCOPT */
/* Define the union U_FCOPT,ATTR:RW,ADDR:4C,INIT:00000000,MASK:ffff,CMMNT:FCOPT*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_ct_sel       : 1  ; /* [0] */
        unsigned int    i_clkdet_sel   : 1  ; /* [1] */
        unsigned int    i_ct_mode      : 2  ; /* [3:2] */
        unsigned int    fcopt_unused_1 : 4  ; /* [7:4] */
        unsigned int    i_ct_en        : 1  ; /* [8] */
        unsigned int    fcopt_unused_2 : 3  ; /* [11:9] */
        unsigned int    i_ct_idx_sel   : 1  ; /* [12] */
        unsigned int    i_deci_try_sel : 1  ; /* [13] */
        unsigned int    fcopt_unused   : 2  ; /* [15:14] */
        unsigned int    rsv_17         : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCOPT;

/* Define the union U_FCSTAT */
/* Define the union U_FCSTAT,ATTR:RW,ADDR:50,INIT:00000000,MASK:3fffffff,CMMNT:FCSTAT*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clk_ok          : 1  ; /* [0] */
        unsigned int    busy            : 1  ; /* [1] */
        unsigned int    done            : 1  ; /* [2] */
        unsigned int    error           : 1  ; /* [3] */
        unsigned int    divn            : 3  ; /* [6:4] */
        unsigned int    fcstat_unused_1 : 1  ; /* [7] */
        unsigned int    ref_clk_stat    : 1  ; /* [8] */
        unsigned int    pllvco_clk_stat : 1  ; /* [9] */
        unsigned int    fcstat_unused_2 : 2  ; /* [11:10] */
        unsigned int    confin_stat     : 6  ; /* [17:12] */
        unsigned int    fcstat_unused_3 : 2  ; /* [19:18] */
        unsigned int    fcon_init       : 10  ; /* [29:20] */
        unsigned int    rsv_18          : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCSTAT;

/* Define the union U_FCCNTVAL0 */
/* Define the union U_FCCNTVAL0,ATTR:RW,ADDR:54,INIT:00000000,MASK:ffff,CMMNT:FCCNTVAL0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    o_cnt_ref : 16  ; /* [15:0] */
        unsigned int    rsv_19    : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCCNTVAL0;

/* Define the union U_FCCNTVAL1 */
/* Define the union U_FCCNTVAL1,ATTR:RW,ADDR:58,INIT:00000000,MASK:ffff,CMMNT:FCCNTVAL1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    o_cnt_mpll : 16  ; /* [15:0] */
        unsigned int    rsv_20     : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCCNTVAL1;

/* Define the union U_FCRESVAL */
/* Define the union U_FCRESVAL,ATTR:RW,ADDR:5C,INIT:00000000,MASK:3fff,CMMNT:FCRESVAL*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    o_divn_mpll     : 3  ; /* [2:0] */
        unsigned int    fcresval_unused : 1  ; /* [3] */
        unsigned int    o_fcon_mpll     : 10  ; /* [13:4] */
        unsigned int    rsv_21          : 18  ; /* [31:14] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCRESVAL;

/* Define the union U_FCDSTEPSET */
/* Define the union U_FCDSTEPSET,ATTR:RW,ADDR:60,INIT:00000000,MASK:1f,CMMNT:FCDSTEPSET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_divn_h20           : 3  ; /* [2:0] */
        unsigned int    fcdstepset_unused    : 1  ; /* [3] */
        unsigned int    up_sampler_ratio_sel : 1  ; /* [4] */
        unsigned int    rsv_22               : 27  ; /* [31:5] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCDSTEPSET;

/* Define the union U_FCDSTEPTH */
/* Define the union U_FCDSTEPTH,ATTR:RW,ADDR:64,INIT:00000000,MASK:3,CMMNT:FCDSTEPTH*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_h2_sel   : 1  ; /* [0] */
        unsigned int    i_deci_sel : 1  ; /* [1] */
        unsigned int    rsv_23     : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCDSTEPTH;

/* Define the union U_FCDSTEPTH0 */
/* Define the union U_FCDSTEPTH0,ATTR:RW,ADDR:68,INIT:00000000,MASK:ffffffff,CMMNT:FCDSTEPTH0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_deci2x_th : 16  ; /* [15:0] */
        unsigned int    i_deci4x_th : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCDSTEPTH0;

/* Define the union U_FCDSTEPTH1 */
/* Define the union U_FCDSTEPTH1,ATTR:RW,ADDR:6C,INIT:00000000,MASK:ffffffff,CMMNT:FCDSTEPTH1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_deci8x_th  : 16  ; /* [15:0] */
        unsigned int    i_deci16x_th : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCDSTEPTH1;

/* Define the union U_FCCNTR1 */
/* Define the union U_FCCNTR1,ATTR:RW,ADDR:70,INIT:00000000,MASK:ffff,CMMNT:FCCNTR1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_ref_cnt : 16  ; /* [15:0] */
        unsigned int    rsv_24    : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCCNTR1;

/* Define the union U_FCCONTINSET0 */
/* Define the union U_FCCONTINSET0,ATTR:RW,ADDR:74,INIT:00000000,MASK:ff,CMMNT:FCCONTINSET0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_contin_upd_en     : 1  ; /* [0] */
        unsigned int    p_contin_upd_opt    : 1  ; /* [1] */
        unsigned int    p_contin_upd_pol    : 1  ; /* [2] */
        unsigned int    fccontinset0_unused : 1  ; /* [3] */
        unsigned int    p_contin_upd_step   : 4  ; /* [7:4] */
        unsigned int    rsv_25              : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCCONTINSET0;

/* Define the union U_FCCONTINSET1 */
/* Define the union U_FCCONTINSET1,ATTR:RW,ADDR:78,INIT:00000000,MASK:ffffffff,CMMNT:FCCONTINSET1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_contin_upd_rate : 28  ; /* [27:0] */
        unsigned int    p_contin_upd_time : 4  ; /* [31:28] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCCONTINSET1;

/* Define the union U_FCCONTINSET2 */
/* Define the union U_FCCONTINSET2,ATTR:RW,ADDR:7C,INIT:00000000,MASK:3fffff,CMMNT:FCCONTINSET2*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_contin_upd_th_dn  : 10  ; /* [9:0] */
        unsigned int    fccontinset2_unused : 2  ; /* [11:10] */
        unsigned int    p_contin_upd_th_up  : 10  ; /* [21:12] */
        unsigned int    rsv_26              : 10  ; /* [31:22] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCCONTINSET2;

/* Define the union U_FDIVSET0 */
/* Define the union U_FDIVSET0,ATTR:RW,ADDR:90,INIT:00000000,MASK:f,CMMNT:FDIVSET0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    init    : 1  ; /* [0] */
        unsigned int    en_ctrl : 1  ; /* [1] */
        unsigned int    en_mod  : 1  ; /* [2] */
        unsigned int    en_sdm  : 1  ; /* [3] */
        unsigned int    rsv_27  : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSET0;

/* Define the union U_FDIVSET1 */
/* Define the union U_FDIVSET1,ATTR:RW,ADDR:94,INIT:00000000,MASK:ffffffff,CMMNT:FDIVSET1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    step_d : 8  ; /* [7:0] */
        unsigned int    step_t : 8  ; /* [15:8] */
        unsigned int    step_n : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSET1;

/* Define the union U_FDIVSET2 */
/* Define the union U_FDIVSET2,ATTR:RW,ADDR:98,INIT:00000000,MASK:3,CMMNT:FDIVSET2*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    up     : 1  ; /* [0] */
        unsigned int    dn     : 1  ; /* [1] */
        unsigned int    rsv_28 : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSET2;

/* Define the union U_FDIVSET3 */
/* Define the union U_FDIVSET3,ATTR:RW,ADDR:9C,INIT:00000000,MASK:ffffffff,CMMNT:FDIVSET3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mod_len : 8  ; /* [7:0] */
        unsigned int    mod_t   : 8  ; /* [15:8] */
        unsigned int    mod_n   : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSET3;

/* Define the union U_FDIVSET4 */
/* Define the union U_FDIVSET4,ATTR:RW,ADDR:A0,INIT:00000000,MASK:ffff,CMMNT:FDIVSET4*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mod_d  : 16  ; /* [15:0] */
        unsigned int    rsv_29 : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSET4;

/* Define the union U_FDIVSET5 */
/* Define the union U_FDIVSET5,ATTR:RW,ADDR:A4,INIT:00000000,MASK:f,CMMNT:FDIVSET5*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_mod_up        : 1  ; /* [0] */
        unsigned int    p_mod_dn        : 1  ; /* [1] */
        unsigned int    fdivset5_unused : 2  ; /* [3:2] */
        unsigned int    rsv_30          : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSET5;

/* Define the union U_FDIVSTAT0 */
/* Define the union U_FDIVSTAT0,ATTR:RW,ADDR:A8,INIT:00000000,MASK:fffff,CMMNT:FDIVSTAT0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stc_run : 1  ; /* [0] */
        unsigned int    stc_dir : 1  ; /* [1] */
        unsigned int    stc_ov  : 1  ; /* [2] */
        unsigned int    stc_un  : 1  ; /* [3] */
        unsigned int    stc_cnt : 16  ; /* [19:4] */
        unsigned int    rsv_31  : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSTAT0;

/* Define the union U_FDIVSTAT1 */
/* Define the union U_FDIVSTAT1,ATTR:RW,ADDR:AC,INIT:00000000,MASK:ffffffff,CMMNT:FDIVSTAT1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_fdiv_in : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSTAT1;

/* Define the union U_FDIVSTAT2 */
/* Define the union U_FDIVSTAT2,ATTR:RW,ADDR:B0,INIT:00000000,MASK:ffffffff,CMMNT:FDIVSTAT2*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    div_out : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSTAT2;

/* Define the union U_FDIVSTAT3 */
/* Define the union U_FDIVSTAT3,ATTR:RW,ADDR:B4,INIT:00000000,MASK:ffff,CMMNT:FDIVSTAT3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    div_sdm : 16  ; /* [15:0] */
        unsigned int    rsv_32  : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSTAT3;

/* Define the union U_FDIVSTAT4 */
/* Define the union U_FDIVSTAT4,ATTR:RW,ADDR:B8,INIT:00000000,MASK:ffffff,CMMNT:FDIVSTAT4*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stm_run          : 1  ; /* [0] */
        unsigned int    stm_ph           : 2  ; /* [2:1] */
        unsigned int    stm_ov           : 1  ; /* [3] */
        unsigned int    stm_un           : 1  ; /* [4] */
        unsigned int    fdivstat4_unused : 3  ; /* [7:5] */
        unsigned int    stm_cnt          : 16  ; /* [23:8] */
        unsigned int    rsv_33           : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVSTAT4;

/* Define the union U_FDIVMANUAL */
/* Define the union U_FDIVMANUAL,ATTR:RW,ADDR:BC,INIT:00000000,MASK:ffffff,CMMNT:FDIVMANUAL*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i_manual_en       : 4  ; /* [3:0] */
        unsigned int    i_divn            : 3  ; /* [6:4] */
        unsigned int    fdivmanual_unused : 1  ; /* [7] */
        unsigned int    i_mdiv            : 4  ; /* [11:8] */
        unsigned int    i_ref_cnt_div     : 2  ; /* [13:12] */
        unsigned int    i_dc_sel          : 2  ; /* [15:14] */
        unsigned int    i_vic             : 8  ; /* [23:16] */
        unsigned int    rsv_34            : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDIVMANUAL;

/* Define the union U_REFCLKSEL */
/* Define the union U_REFCLKSEL,ATTR:RW,ADDR:C0,INIT:00000004,MASK:ff,CMMNT:REFCLKSEL*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    t2_refclksel       : 1  ; /* [0] */
        unsigned int    t2_refclksel2      : 1  ; /* [1] */
        unsigned int    i_ref_clk_sel      : 1  ; /* [2] */
        unsigned int    refclksel_unused_1 : 1  ; /* [3] */
        unsigned int    t2_pixelclksel     : 1  ; /* [4] */
        unsigned int    refclksel_unused_2 : 1  ; /* [5] */
        unsigned int    p_pr_enc_val       : 2  ; /* [7:6] */
        unsigned int    rsv_35             : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFCLKSEL;

/* Define the union U_FDPLLPARAM */
/* Define the union U_FDPLLPARAM,ATTR:RW,ADDR:100,INIT:00000404,MASK:fffff,CMMNT:FDPLLPARAM*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pll_lock_val      : 8  ; /* [7:0] */
        unsigned int    pll_lock_cnt      : 8  ; /* [15:8] */
        unsigned int    pll_enable        : 1  ; /* [16] */
        unsigned int    fdpllparam_unused : 3  ; /* [19:17] */
        unsigned int    rsv_36            : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDPLLPARAM;

/* Define the union U_FDPLLFREQ */
/* Define the union U_FDPLLFREQ,ATTR:RW,ADDR:104,INIT:00000000,MASK:ffffff,CMMNT:FDPLLFREQ*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pll_cnt_opt        : 3  ; /* [2:0] */
        unsigned int    fdpllfreq_unused_1 : 1  ; /* [3] */
        unsigned int    pll_freq_opt       : 2  ; /* [5:4] */
        unsigned int    fdpllfreq_unused_2 : 2  ; /* [7:6] */
        unsigned int    pll_freq_ext       : 16  ; /* [23:8] */
        unsigned int    rsv_37             : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDPLLFREQ;

/* Define the union U_FDPLLRES */
/* Define the union U_FDPLLRES,ATTR:RW,ADDR:108,INIT:00000000,MASK:ffffff,CMMNT:FDPLLRES*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pll_det_stat : 4  ; /* [3:0] */
        unsigned int    pll_cnt_out  : 20  ; /* [23:4] */
        unsigned int    rsv_38       : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FDPLLRES;

/* Define the union U_FCGSET */
/* Define the union U_FCGSET,ATTR:RW,ADDR:120,INIT:00000000,MASK:f,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_fcg_en        : 1  ; /* [0] */
        unsigned int    p_fcg_dlf_en    : 1  ; /* [1] */
        unsigned int    p_fcg_dither_en : 1  ; /* [2] */
        unsigned int    p_fcg_lock_en   : 1  ; /* [3] */
        unsigned int    rsv_39          : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCGSET;

/* Define the union U_FCGCNT */
/* Define the union U_FCGCNT,ATTR:RW,ADDR:124,INIT:00000000,MASK:ffffffff,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_tmds_cnt_val : 16  ; /* [15:0] */
        unsigned int    p_cnt1_target  : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCGCNT;

/* Define the union U_FCGPARAM */
/* Define the union U_FCGPARAM,ATTR:RW,ADDR:128,INIT:00000000,MASK:7fffff,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_lock_cnt  : 8  ; /* [7:0] */
        unsigned int    p_lock_th   : 8  ; /* [15:8] */
        unsigned int    p_ki        : 6  ; /* [21:16] */
        unsigned int    p_lock_mode : 1  ; /* [22] */
        unsigned int    rsv_40      : 9  ; /* [31:23] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCGPARAM;

/* Define the union U_FCGSTATE */
/* Define the union U_FCGSTATE,ATTR:RW,ADDR:12C,INIT:00000000,MASK:7,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    o_dlf_lock : 1  ; /* [0] */
        unsigned int    o_dlf_ov   : 1  ; /* [1] */
        unsigned int    o_dlf_un   : 1  ; /* [2] */
        unsigned int    rsv_41     : 29  ; /* [31:3] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FCGSTATE;

/* Define the union U_TXTELOSET */
/* Define the union U_TXTELOSET,ATTR:RW,ADDR:200,INIT:00000000,MASK:fffffff,CMMNT:TXTELOSET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_ch_en_h20          : 4  ; /* [3:0] */
        unsigned int    p_prbs_clr_h20       : 4  ; /* [7:4] */
        unsigned int    p_ch_en_h21          : 4  ; /* [11:8] */
        unsigned int    p_prbs_clr_h21       : 4  ; /* [15:12] */
        unsigned int    p_test_pat_type      : 3  ; /* [18:16] */
        unsigned int    p_ch_test_en         : 1  ; /* [19] */
        unsigned int    p_test_4to1_mux_sel0 : 2  ; /* [21:20] */
        unsigned int    p_test_4to1_mux_sel1 : 2  ; /* [23:22] */
        unsigned int    p_test_4to1_mux_sel2 : 2  ; /* [25:24] */
        unsigned int    p_test_4to1_mux_sel3 : 2  ; /* [27:26] */
        unsigned int    rsv_42               : 4  ; /* [31:28] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXTELOSET;

/* Define the union U_TXTELOCONT0 */
/* Define the union U_TXTELOCONT0,ATTR:RW,ADDR:204,INIT:00000000,MASK:3fffffff,CMMNT:TXTELOCONT0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_test_pat_ch0   : 20  ; /* [19:0] */
        unsigned int    p_test_pat_ch1_l : 10  ; /* [29:20] */
        unsigned int    rsv_43           : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXTELOCONT0;

/* Define the union U_TXTELOCONT1 */
/* Define the union U_TXTELOCONT1,ATTR:RW,ADDR:208,INIT:00000000,MASK:3fffffff,CMMNT:TXTELOCONT1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_test_pat_ch1_h : 10  ; /* [9:0] */
        unsigned int    p_test_pat_ch2   : 20  ; /* [29:10] */
        unsigned int    rsv_44           : 2  ; /* [31:30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXTELOCONT1;

/* Define the union U_TXTELOCONT2 */
/* Define the union U_TXTELOCONT2,ATTR:RW,ADDR:20C,INIT:00000000,MASK:fffff,CMMNT:TXTELOCONT2*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_test_pat_ch3 : 20  ; /* [19:0] */
        unsigned int    rsv_45         : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXTELOCONT2;

/* Define the union U_TXFIFOSET0 */
/* Define the union U_TXFIFOSET0,ATTR:RW,ADDR:210,INIT:00000000,MASK:ff,CMMNT:TXFIFOSET0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_pr_en_h20       : 1  ; /* [0] */
        unsigned int    p_enable_h20      : 1  ; /* [1] */
        unsigned int    txfifoset0_unused : 6  ; /* [7:2] */
        unsigned int    rsv_46            : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXFIFOSET0;

/* Define the union U_TXFIFOSET1 */
/* Define the union U_TXFIFOSET1,ATTR:RW,ADDR:214,INIT:E400E400,MASK:ffffffff,CMMNT:TXFIFOSET1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_pol_inv0_h20   : 4  ; /* [3:0] */
        unsigned int    p_data_swap0_h20 : 4  ; /* [7:4] */
        unsigned int    p_ch_sel0_h20    : 8  ; /* [15:8] */
        unsigned int    p_pol_inv1_h20   : 4  ; /* [19:16] */
        unsigned int    p_data_swap1_h20 : 4  ; /* [23:20] */
        unsigned int    p_ch_sel1_h20    : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXFIFOSET1;

/* Define the union U_TXFIFOSTAT0 */
/* Define the union U_TXFIFOSTAT0,ATTR:RW,ADDR:218,INIT:000000C3,MASK:ffffff,CMMNT:TXFIFOSTAT0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    o_pr_fifo_state_h20 : 12  ; /* [11:0] */
        unsigned int    txfifostat0_unused  : 12  ; /* [23:12] */
        unsigned int    rsv_47              : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXFIFOSTAT0;

/* Define the union U_TXFIFOSTAT1 */
/* Define the union U_TXFIFOSTAT1,ATTR:RW,ADDR:21C,INIT:00000000,MASK:ffffff,CMMNT:TXFIFOSTAT1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    txfifostat1_unused_0 : 12  ; /* [11:0] */
        unsigned int    txfifostat1_unused_1 : 12  ; /* [23:12] */
        unsigned int    rsv_48               : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXFIFOSTAT1;

/* Define the union U_TXFIFOSTAT2 */
/* Define the union U_TXFIFOSTAT2,ATTR:RW,ADDR:220,INIT:000000C3,MASK:ffffff,CMMNT:TXFIFOSTAT2*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    o_tx_fifo_state_h20 : 12  ; /* [11:0] */
        unsigned int    txfifostat2_unused  : 12  ; /* [23:12] */
        unsigned int    rsv_49              : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXFIFOSTAT2;

/* Define the union U_TXFIFOSTAT3 */
/* Define the union U_TXFIFOSTAT3,ATTR:RW,ADDR:224,INIT:00000000,MASK:ffffff,CMMNT:TXFIFOSTAT3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    txfifostat3_unused_0 : 12  ; /* [11:0] */
        unsigned int    txfifostat3_unused_1 : 12  ; /* [23:12] */
        unsigned int    rsv_50               : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXFIFOSTAT3;

/* Define the union U_DATACLKINV */
/* Define the union U_DATACLKINV,ATTR:RW,ADDR:228,INIT:00000000,MASK:1,CMMNT:DATACLKINV*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_dataclkinv : 1  ; /* [0] */
        unsigned int    rsv_51       : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATACLKINV;

/* Define the union U_TXDATAOUTSEL */
/* Define the union U_TXDATAOUTSEL,ATTR:RW,ADDR:22C,INIT:00000000,MASK:3,CMMNT:TXDATAOUTSEL*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_ch_out_sel : 2  ; /* [1:0] */
        unsigned int    rsv_52       : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TXDATAOUTSEL;

/* Define the union U_HDMI_MODE */
/* Define the union U_HDMI_MODE,ATTR:RW,ADDR:230,INIT:00000000,MASK:1,CMMNT:HDMI mode*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_hdmi_mode_en : 1  ; /* [0] */
        unsigned int    rsv_53           : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDMI_MODE;

/* Define the union U_CLK_DATA_1 */
/* Define the union U_CLK_DATA_1,ATTR:RW,ADDR:234,INIT:00000000,MASK:1fffff,CMMNT:CLK_DATA_1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_clk_data_phase0 : 10  ; /* [9:0] */
        unsigned int    reg_clk_data_phase1 : 10  ; /* [19:10] */
        unsigned int    reg_sw_clk_en       : 1  ; /* [20] */
        unsigned int    rsv_54              : 11  ; /* [31:21] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CLK_DATA_1;

/* Define the union U_CLK_DATA_2 */
/* Define the union U_CLK_DATA_2,ATTR:RW,ADDR:238,INIT:00000000,MASK:fffff,CMMNT:CLK_DATA_2*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_clk_data_phase2 : 10  ; /* [9:0] */
        unsigned int    reg_clk_data_phase3 : 10  ; /* [19:10] */
        unsigned int    rsv_55              : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CLK_DATA_2;

/* Define the union U_CFG18TO20 */
/* Define the union U_CFG18TO20,ATTR:RW,ADDR:23C,INIT:00000000,MASK:1f,CMMNT:CFG18TO20*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reg_18to20_fifo_rd_rst : 1  ; /* [0] */
        unsigned int    reg_18to20_fifo_wr_rst : 1  ; /* [1] */
        unsigned int    reg_rd_bypass          : 1  ; /* [2] */
        unsigned int    reg_status_rrst        : 1  ; /* [3] */
        unsigned int    reg_status_wrst        : 1  ; /* [4] */
        unsigned int    rsv_56                 : 27  ; /* [31:5] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CFG18TO20;

/* Define the union U_FIFOSTAT18TO20 */
/* Define the union U_FIFOSTAT18TO20,ATTR:RW,ADDR:240,INIT:00000000,MASK:f,CMMNT:FIFOSTAT18TO20*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    empty_status  : 1  ; /* [0] */
        unsigned int    aempty_status : 1  ; /* [1] */
        unsigned int    full_status   : 1  ; /* [2] */
        unsigned int    afull_status  : 1  ; /* [3] */
        unsigned int    rsv_57        : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FIFOSTAT18TO20;

/* Define the union U_HSSET */
/* Define the union U_HSSET,ATTR:RW,ADDR:260,INIT:00000000,MASK:3,CMMNT:HSSET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_hsset : 2  ; /* [1:0] */
        unsigned int    rsv_58  : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HSSET;

/* Define the union U_HSRXSENSE */
/* Define the union U_HSRXSENSE,ATTR:RW,ADDR:264,INIT:00000000,MASK:3,CMMNT:HSRXSENSE*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w_hsrxsense : 2  ; /* [1:0] */
        unsigned int    rsv_59      : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HSRXSENSE;

/* Define the union U_HSFIFOSTAT */
/* Define the union U_HSFIFOSTAT,ATTR:RW,ADDR:268,INIT:000000C3,MASK:fff,CMMNT:HSFIFOSTAT*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    o_fifo_state_hs : 12  ; /* [11:0] */
        unsigned int    rsv_60          : 20  ; /* [31:12] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HSFIFOSTAT;

/* Define the union U_INTRSTAT */
/* Define the union U_INTRSTAT,ATTR:RW,ADDR:300,INIT:00000000,MASK:1ff,CMMNT:INTRSTAT*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hs_fifo_empty_intr          : 1  ; /* [0] */
        unsigned int    hs_fifo_full_intr           : 1  ; /* [1] */
        unsigned int    up_sample_fifo_empty_intr   : 1  ; /* [2] */
        unsigned int    up_sample_fifo_full_intr    : 1  ; /* [3] */
        unsigned int    trinsmitter_fifo_empty_intr : 1  ; /* [4] */
        unsigned int    trinsmitter_fifo_full_intr  : 1  ; /* [5] */
        unsigned int    lkvdethigh_intr             : 1  ; /* [6] */
        unsigned int    lkvdetlow_intr              : 1  ; /* [7] */
        unsigned int    ct_fcon_intr                : 1  ; /* [8] */
        unsigned int    rsv_61                      : 23  ; /* [31:9] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRSTAT;

/* Define the union U_INTRMASK */
/* Define the union U_INTRMASK,ATTR:RW,ADDR:304,INIT:000001FF,MASK:1ff,CMMNT:INTRMASK*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hs_fifo_empty_intr_mask          : 1  ; /* [0] */
        unsigned int    hs_fifo_full_intr_mask           : 1  ; /* [1] */
        unsigned int    up_sample_fifo_empty_intr_mask   : 1  ; /* [2] */
        unsigned int    up_sample_fifo_full_intr_mask    : 1  ; /* [3] */
        unsigned int    trinsmitter_fifo_empty_intr_mask : 1  ; /* [4] */
        unsigned int    trinsmitter_fifo_full_intr_mask  : 1  ; /* [5] */
        unsigned int    lkvdethigh_intr_mask             : 1  ; /* [6] */
        unsigned int    lkvdetlow_intr_mask              : 1  ; /* [7] */
        unsigned int    ct_fcon_intr_mask                : 1  ; /* [8] */
        unsigned int    rsv_62                           : 23  ; /* [31:9] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRMASK;

/* Define the union U_INTRSET */
/* Define the union U_INTRSET,ATTR:RW,ADDR:308,INIT:00000000,MASK:ffffffff,CMMNT:INTRSET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hs_fifo_empty_triger_type          : 3  ; /* [2:0] */
        unsigned int    hs_fifo_empty_intr_en              : 1  ; /* [3] */
        unsigned int    hs_fifo_full_triger_type           : 3  ; /* [6:4] */
        unsigned int    hs_fifo_full_intr_en               : 1  ; /* [7] */
        unsigned int    up_sample_fifo_empty_triger_type   : 3  ; /* [10:8] */
        unsigned int    up_sample_fifo_empty_intr_en       : 1  ; /* [11] */
        unsigned int    up_sample_fifo_full_triger_type    : 3  ; /* [14:12] */
        unsigned int    up_sample_fifo_full_intr_en        : 1  ; /* [15] */
        unsigned int    transmitter_fifo_empty_triger_type : 3  ; /* [18:16] */
        unsigned int    transmitter_fifo_empty_intr_en     : 1  ; /* [19] */
        unsigned int    transmitter_fifo_full_triger_type  : 3  ; /* [22:20] */
        unsigned int    transmitter_fifo_full_intr_en      : 1  ; /* [23] */
        unsigned int    lkvdethigh_triger_type             : 3  ; /* [26:24] */
        unsigned int    lkvdethigh_intr_en                 : 1  ; /* [27] */
        unsigned int    lkvdetlow_triger_type              : 3  ; /* [30:28] */
        unsigned int    lkvdetlow_intr_en                  : 1  ; /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRSET;

/* Define the union U_CLKSET */
/* Define the union U_CLKSET,ATTR:RW,ADDR:30C,INIT:00000040,MASK:fff,CMMNT:CLKSET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p_fd_clk_sel  : 2  ; /* [1:0] */
        unsigned int    p_refclk_sel  : 2  ; /* [3:2] */
        unsigned int    p_ctman       : 2  ; /* [5:4] */
        unsigned int    p_modclk_sel  : 1  ; /* [6] */
        unsigned int    p_fdivclk_sel : 1  ; /* [7] */
        unsigned int    mod_div_val   : 4  ; /* [11:8] */
        unsigned int    rsv_63        : 20  ; /* [31:12] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CLKSET;

/* Define the union U_SWRESET */
/* Define the union U_SWRESET,ATTR:RW,ADDR:310,INIT:00000000,MASK:ffffffff,CMMNT:SWRESET*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sw_reset_mod_clock          : 1  ; /* [0] */
        unsigned int    sw_reset_tmds_clock         : 1  ; /* [1] */
        unsigned int    sw_reset_mpll_clock         : 1  ; /* [2] */
        unsigned int    sw_reset_nco_clock          : 1  ; /* [3] */
        unsigned int    sw_reset_fd_clock           : 1  ; /* [4] */
        unsigned int    sw_reset_mod_and_mpll_clock : 1  ; /* [5] */
        unsigned int    sw_reset_mod_and_nco_clock  : 1  ; /* [6] */
        unsigned int    sw_reset_mod_and_fd_clock   : 1  ; /* [7] */
        unsigned int    sw_reset_hsfifo_clock       : 1  ; /* [8] */
        unsigned int    sw_reset_txfifo_clock       : 1  ; /* [9] */
        unsigned int    sw_reset_data_clock         : 1  ; /* [10] */
        unsigned int    sw_reset_hs_clock           : 1  ; /* [11] */
        unsigned int    sw_reset_pllref_clock       : 1  ; /* [12] */
        unsigned int    sw_reset_dac_clock          : 1  ; /* [13] */
        unsigned int    dac_clock_gat               : 1  ; /* [14] */
        unsigned int    up_sample_fifo_clock_swrst  : 1  ; /* [15] */
        unsigned int    sw_reset_frl_clock          : 1  ; /* [16] */
        unsigned int    swreset_unused              : 14  ; /* [30:17] */
        unsigned int    global_reset                : 1  ; /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SWRESET;

/* Define the union U_GLUESET0 */
/* Define the union U_GLUESET0,ATTR:RW,ADDR:314,INIT:00000000,MASK:ffffffff,CMMNT:GLUESET0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clk0_div : 4  ; /* [3:0] */
        unsigned int    clk1_div : 4  ; /* [7:4] */
        unsigned int    clk2_div : 4  ; /* [11:8] */
        unsigned int    clk3_div : 4  ; /* [15:12] */
        unsigned int    clk4_div : 4  ; /* [19:16] */
        unsigned int    clk5_div : 4  ; /* [23:20] */
        unsigned int    clk6_div : 4  ; /* [27:24] */
        unsigned int    clk7_div : 4  ; /* [31:28] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GLUESET0;

/* Define the union U_GLUESET1 */
/* Define the union U_GLUESET1,ATTR:RW,ADDR:318,INIT:00000000,MASK:ffffffff,CMMNT:GLUESET1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clk8_div          : 4  ; /* [3:0] */
        unsigned int    glueset1_unused_1 : 4  ; /* [7:4] */
        unsigned int    clk10_div         : 4  ; /* [11:8] */
        unsigned int    clk11_div         : 4  ; /* [15:12] */
        unsigned int    clk_sel           : 4  ; /* [19:16] */
        unsigned int    glueset1_unused_2 : 12  ; /* [31:20] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GLUESET1;

/* Define the union U_CT_INTRSET */
/* Define the union U_CT_INTRSET,ATTR:RW,ADDR:31C,INIT:00000000,MASK:f,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ct_fcon_triger_type : 3  ; /* [2:0] */
        unsigned int    ct_fcon_intr_en     : 1  ; /* [3] */
        unsigned int    rsv_64              : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CT_INTRSET;

/* Define the union U_HW_INFO */
/* Define the union U_HW_INFO,ATTR:RW,ADDR:400,INIT:07E10713,MASK:ffffffff,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hw_info : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HW_INFO;

/* Define the union U_HW_VERS */
/* Define the union U_HW_VERS,ATTR:RW,ADDR:404,INIT:00101030,MASK:ffffffff,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hw_vers_unused_1  : 4  ; /* [3:0] */
        unsigned int    hdmi20_compliance : 1  ; /* [4] */
        unsigned int    hdmi21_compliance : 1  ; /* [5] */
        unsigned int    hw_vers_unused_2  : 26  ; /* [31:6] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HW_VERS;

/* Define the union U_RASMODE */
/* Define the union U_RASMODE,ATTR:RW,ADDR:420,INIT:00005059,MASK:ffffffff,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ras_mode : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_RASMODE;

/* Define the union U_RFSMODE */
/* Define the union U_RFSMODE,ATTR:RW,ADDR:424,INIT:00005057,MASK:ffffffff,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rfs_mode : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_RFSMODE;

/* Define the union U_RFTMODE */
/* Define the union U_RFTMODE,ATTR:RW,ADDR:428,INIT:00035389,MASK:ffffffff,CMMNT:*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rft_mode : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_RFTMODE;

/* Define the union U_STBOPT */
/* Define the union U_STBOPT,ATTR:RW,ADDR:700,INIT:00000888,MASK:ffff,CMMNT:STBOPT*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_length  : 2  ; /* [1:0] */
        unsigned int    stb_delay2  : 4  ; /* [5:2] */
        unsigned int    stb_delay1  : 4  ; /* [9:6] */
        unsigned int    stb_delay0  : 4  ; /* [13:10] */
        unsigned int    stb_acc_sel : 1  ; /* [14] */
        unsigned int    stb_cs_sel  : 1  ; /* [15] */
        unsigned int    rsv_65      : 16 ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_STBOPT;

/* Define the union U_STBREQ */
/* Define the union U_STBREQ,ATTR:RW,ADDR:704,INIT:00000001,MASK:1,CMMNT:STBREQ*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_done : 1  ; /* [0] */
        unsigned int    rsv_66   : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_STBREQ;

/* Define the union U_STBRDATA */
/* Define the union U_STBRDATA,ATTR:,ADDR:708,INIT:00000000,MASK:ffffffff,CMMNT:STBRDATA*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stb_auto_rdata : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_STBRDATA;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_T2GPPORT0      T2GPPORT0      ; /* 0 */
    volatile U_T2GPPORT1      T2GPPORT1      ; /* 4 */
    volatile U_PHY_CSEN       PHY_CSEN       ; /* 8 */
    volatile U_PHY_WR         PHY_WR         ; /* C */
    volatile U_RESETN         RESETN         ; /* 10 */
    volatile U_PHY_ADDR       PHY_ADDR       ; /* 14 */
    volatile U_PHY_WDATA      PHY_WDATA      ; /* 18 */
    volatile U_PHY_RDATA      PHY_RDATA      ; /* 1C */
    volatile U_ZCALREG        ZCALREG        ; /* 20 */
    volatile U_ZCALCLK        ZCALCLK        ; /* 24 */
    volatile U_SHORTDET       SHORTDET       ; /* 28 */
    volatile U_DET            DET            ; /* 2C */
    volatile U_FDSRCPARAM     FDSRCPARAM     ; /* 30 */
    volatile U_FDSRCFREQ      FDSRCFREQ      ; /* 34 */
    volatile U_FDSRCRES       FDSRCRES       ; /* 38 */
    volatile U_CTSET0         CTSET0         ; /* 3C */
    volatile U_CTSET1         CTSET1         ; /* 40 */
    unsigned int              reserved_0     ; /* 44 */
    volatile U_FCCNTR0        FCCNTR0        ; /* 48 */
    volatile U_FCOPT          FCOPT          ; /* 4C */
    volatile U_FCSTAT         FCSTAT         ; /* 50 */
    volatile U_FCCNTVAL0      FCCNTVAL0      ; /* 54 */
    volatile U_FCCNTVAL1      FCCNTVAL1      ; /* 58 */
    volatile U_FCRESVAL       FCRESVAL       ; /* 5C */
    volatile U_FCDSTEPSET     FCDSTEPSET     ; /* 60 */
    volatile U_FCDSTEPTH      FCDSTEPTH      ; /* 64 */
    volatile U_FCDSTEPTH0     FCDSTEPTH0     ; /* 68 */
    volatile U_FCDSTEPTH1     FCDSTEPTH1     ; /* 6C */
    volatile U_FCCNTR1        FCCNTR1        ; /* 70 */
    volatile U_FCCONTINSET0   FCCONTINSET0   ; /* 74 */
    volatile U_FCCONTINSET1   FCCONTINSET1   ; /* 78 */
    volatile U_FCCONTINSET2   FCCONTINSET2   ; /* 7C */
    unsigned int              reserved_1[4]  ; /* 80-8C */
    volatile U_FDIVSET0       FDIVSET0       ; /* 90 */
    volatile U_FDIVSET1       FDIVSET1       ; /* 94 */
    volatile U_FDIVSET2       FDIVSET2       ; /* 98 */
    volatile U_FDIVSET3       FDIVSET3       ; /* 9C */
    volatile U_FDIVSET4       FDIVSET4       ; /* A0 */
    volatile U_FDIVSET5       FDIVSET5       ; /* A4 */
    volatile U_FDIVSTAT0      FDIVSTAT0      ; /* A8 */
    volatile U_FDIVSTAT1      FDIVSTAT1      ; /* AC */
    volatile U_FDIVSTAT2      FDIVSTAT2      ; /* B0 */
    volatile U_FDIVSTAT3      FDIVSTAT3      ; /* B4 */
    volatile U_FDIVSTAT4      FDIVSTAT4      ; /* B8 */
    volatile U_FDIVMANUAL     FDIVMANUAL     ; /* BC */
    volatile U_REFCLKSEL      REFCLKSEL      ; /* C0 */
    unsigned int              reserved_2[15] ; /* C4-FC*/
    volatile U_FDPLLPARAM     FDPLLPARAM     ; /* 100 */
    volatile U_FDPLLFREQ      FDPLLFREQ      ; /* 104 */
    volatile U_FDPLLRES       FDPLLRES       ; /* 108 */
    unsigned int              reserved_3[5]  ; /*10c-11c*/
    volatile U_FCGSET         FCGSET         ; /* 120 */
    volatile U_FCGCNT         FCGCNT         ; /* 124 */
    volatile U_FCGPARAM       FCGPARAM       ; /* 128 */
    volatile U_FCGSTATE       FCGSTATE       ; /* 12C */
    unsigned int              reserved_4[52] ; /* 130-1FC*/
    volatile U_TXTELOSET      TXTELOSET      ; /* 200 */
    volatile U_TXTELOCONT0    TXTELOCONT0    ; /* 204 */
    volatile U_TXTELOCONT1    TXTELOCONT1    ; /* 208 */
    volatile U_TXTELOCONT2    TXTELOCONT2    ; /* 20C */
    volatile U_TXFIFOSET0     TXFIFOSET0     ; /* 210 */
    volatile U_TXFIFOSET1     TXFIFOSET1     ; /* 214 */
    volatile U_TXFIFOSTAT0    TXFIFOSTAT0    ; /* 218 */
    volatile U_TXFIFOSTAT1    TXFIFOSTAT1    ; /* 21C */
    volatile U_TXFIFOSTAT2    TXFIFOSTAT2    ; /* 220 */
    volatile U_TXFIFOSTAT3    TXFIFOSTAT3    ; /* 224 */
    volatile U_DATACLKINV     DATACLKINV     ; /* 228 */
    volatile U_TXDATAOUTSEL   TXDATAOUTSEL   ; /* 22C */
    volatile U_HDMI_MODE      HDMI_MODE      ; /* 230 */
    volatile U_CLK_DATA_1     CLK_DATA_1     ; /* 234 */
    volatile U_CLK_DATA_2     CLK_DATA_2     ; /* 238 */
    volatile U_CFG18TO20      CFG18TO20      ; /* 23C */
    volatile U_FIFOSTAT18TO20 FIFOSTAT18TO20 ; /* 240 */
    unsigned int              reserved_5[7]  ; /* 244-25c*/
    volatile U_HSSET          HSSET          ; /* 260 */
    volatile U_HSRXSENSE      HSRXSENSE      ; /* 264 */
    volatile U_HSFIFOSTAT     HSFIFOSTAT     ; /* 268 */
    unsigned int              reserved_6[37] ; /* 26C-2FC*/
    volatile U_INTRSTAT       INTRSTAT       ; /* 300 */
    volatile U_INTRMASK       INTRMASK       ; /* 304 */
    volatile U_INTRSET        INTRSET        ; /* 308 */
    volatile U_CLKSET         CLKSET         ; /* 30C */
    volatile U_SWRESET        SWRESET        ; /* 310 */
    volatile U_GLUESET0       GLUESET0       ; /* 314 */
    volatile U_GLUESET1       GLUESET1       ; /* 318 */
    volatile U_CT_INTRSET     CT_INTRSET     ; /* 31C */
    unsigned int              reserved_7[56] ; /*320-3FC*/
    volatile U_HW_INFO        HW_INFO        ; /* 400 */
    volatile U_HW_VERS        HW_VERS        ; /* 404 */
    unsigned int              reserved_8[6]  ; /*408-41C*/
    volatile U_RASMODE        RASMODE        ; /* 420 */
    volatile U_RFSMODE        RFSMODE        ; /* 424 */
    volatile U_RFTMODE        RFTMODE        ; /* 428 */
    unsigned int              reserved_9[181]; /* 42C-6FC*/
    volatile U_STBOPT         STBOPT         ; /* 700 */
    volatile U_STBREQ         STBREQ         ; /* 704 */
    volatile U_STBRDATA       STBRDATA       ; /* 708 */

} S_3559a_dphy_reg_REGS_TYPE;

/* Declare the struct pointor of the module hi3559a_dphy_reg */
extern volatile S_3559a_dphy_reg_REGS_TYPE *hi3559a_dphy_regAllReg ;
HI_S32 HDMI_HDMITX_PHY_reg_Init(HI_CHAR *pcAddr);
HI_S32 HDMI_HDMITX_PHY_reg_DeInit(HI_VOID);


/* Declare the functions that set the member value */
int HDMI_PHY_CSEN_stb_cs_enSet(unsigned int ustb_cs_en);
int HDMI_PHY_WR_stb_wenSet(unsigned int ustb_wen);
int HDMI_RESETN_resetnSet(unsigned int uresetn);
int HDMI_RESETN_resetnGet(HI_VOID);
int HDMI_PHY_ADDR_stb_addrSet(unsigned int ustb_addr);
int HDMI_PHY_WDATA_stb_wdataSet(unsigned int ustb_wdata);
int HDMI_PHY_RDATA_stb_rdataGet(HI_VOID);
int HDMI_FDSRCPARAM_src_lock_valSet(unsigned int usrc_lock_val);
int HDMI_FDSRCPARAM_src_lock_cntSet(unsigned int usrc_lock_cnt);
int HDMI_FDSRCPARAM_src_enableSet(unsigned int usrc_enable);
int HDMI_FDSRCFREQ_src_cnt_optSet(unsigned int usrc_cnt_opt);
int HDMI_FDSRCFREQ_fdsrcfreq_unused_1Set(unsigned int ufdsrcfreq_unused_1);
int HDMI_FDSRCFREQ_src_freq_optSet(unsigned int usrc_freq_opt);
int HDMI_FDSRCFREQ_fdsrcfreq_unused_2Set(unsigned int ufdsrcfreq_unused_2);
int HDMI_FDSRCFREQ_src_freq_extSet(unsigned int usrc_freq_ext);
int HDMI_FDSRCRES_src_det_statGet(HI_VOID);
int HDMI_FDSRCRES_src_cnt_outGet(HI_VOID);
int HDMI_CTSET0_i_enableSet(unsigned int ui_enable);
int HDMI_CTSET0_i_runSet(unsigned int ui_run);
int HDMI_CTSET0_ctset0_unusedSet(unsigned int uctset0_unused);
int HDMI_FCCNTR0_i_vco_st_wait_lenSet(unsigned int ui_vco_st_wait_len);
int HDMI_FCCNTR0_i_vco_end_wait_lenSet(unsigned int ui_vco_end_wait_len);
int HDMI_FCCNTR0_i_ref_cnt_lenSet(unsigned int ui_ref_cnt_len);
int HDMI_FCOPT_i_ct_selSet(unsigned int ui_ct_sel);
int HDMI_FCOPT_i_clkdet_selSet(unsigned int ui_clkdet_sel);
int HDMI_FCOPT_i_ct_modeSet(unsigned int ui_ct_mode);
int HDMI_FCOPT_fcopt_unused_1Set(unsigned int ufcopt_unused_1);
int HDMI_FCOPT_i_ct_enSet(unsigned int ui_ct_en);
int HDMI_FCOPT_fcopt_unused_2Set(unsigned int ufcopt_unused_2);
int HDMI_FCOPT_i_ct_idx_selSet(unsigned int ui_ct_idx_sel);
int HDMI_FCOPT_fcopt_unusedSet(unsigned int ufcopt_unused);
int HDMI_FCSTAT_busyGet(HI_VOID);
int HDMI_FCDSTEPSET_p_divn_h20Set(unsigned int up_divn_h20);
int HDMI_FCDSTEPSET_up_sampler_ratio_selSet(unsigned int uup_sampler_ratio_sel);
int HDMI_FCDSTEPSET_up_sampler_ratio_selGet(HI_VOID);
int HDMI_FCCNTR1_i_ref_cntSet(unsigned int ui_ref_cnt);
int HDMI_FCCONTINSET0_p_contin_upd_enSet(unsigned int up_contin_upd_en);
int HDMI_FCCONTINSET0_p_contin_upd_optSet(unsigned int up_contin_upd_opt);
int HDMI_FCCONTINSET0_p_contin_upd_polSet(unsigned int up_contin_upd_pol);
int HDMI_FCCONTINSET0_p_contin_upd_stepSet(unsigned int up_contin_upd_step);
int HDMI_FCCONTINSET1_p_contin_upd_rateSet(unsigned int up_contin_upd_rate);
int HDMI_FCCONTINSET1_p_contin_upd_timeSet(unsigned int up_contin_upd_time);
int HDMI_FCCONTINSET2_p_contin_upd_th_dnSet(unsigned int up_contin_upd_th_dn);
int HDMI_FCCONTINSET2_fccontinset2_unusedSet(unsigned int ufccontinset2_unused);
int HDMI_FCCONTINSET2_p_contin_upd_th_upSet(unsigned int up_contin_upd_th_up);
int HDMI_FDIVSET0_initSet(unsigned int uinit);
int HDMI_FDIVSET0_en_ctrlSet(unsigned int uen_ctrl);
int HDMI_FDIVSET0_en_ctrlGet(HI_VOID);
int HDMI_FDIVSET0_en_modSet(unsigned int uen_mod);
int HDMI_FDIVSET0_en_modGet(HI_VOID);
int HDMI_FDIVSET0_en_sdmSet(unsigned int uen_sdm);
int HDMI_FDIVSET0_en_sdmGet(HI_VOID);
int HDMI_FDIVSET3_mod_lenSet(unsigned int umod_len);
int HDMI_FDIVSET3_mod_tSet(unsigned int umod_t);
int HDMI_FDIVSET3_mod_nSet(unsigned int umod_n);
int HDMI_FDIVSET4_mod_dSet(unsigned int umod_d);
int HDMI_FDIVSTAT1_i_fdiv_inSet(unsigned int ui_fdiv_in);
int HDMI_FDIVMANUAL_i_manual_enSet(unsigned int ui_manual_en);
int HDMI_FDIVMANUAL_i_mdivSet(unsigned int ui_mdiv);
int HDMI_REFCLKSEL_i_ref_clk_selSet(unsigned int ui_ref_clk_sel);
int HDMI_TXFIFOSET0_p_pr_en_h20Set(unsigned int up_pr_en_h20);
int HDMI_TXFIFOSET0_p_enable_h20Set(unsigned int up_enable_h20);
int HDMI_TXDATAOUTSEL_p_ch_out_selSet(unsigned int up_ch_out_sel);
int HDMI_TXDATAOUTSEL_p_ch_out_selGet(HI_VOID);
int HDMI_HSSET_p_hssetSet(unsigned int up_hsset);
int HDMI_CLKSET_p_fd_clk_selSet(unsigned int up_fd_clk_sel);
int HDMI_CLKSET_p_refclk_selSet(unsigned int up_refclk_sel);
int HDMI_CLKSET_p_ctmanSet(unsigned int up_ctman);
int HDMI_CLKSET_p_modclk_selSet(unsigned int up_modclk_sel);
int HDMI_CLKSET_p_fdivclk_selSet(unsigned int up_fdivclk_sel);
int HDMI_CLKSET_mod_div_valSet(unsigned int umod_div_val);
int HDMI_SWRESET_dac_clock_gatSet(unsigned int udac_clock_gat);
int HDMI_SWRESET_swreset_unusedSet(unsigned int uswreset_unused);
int HDMI_SWRESET_global_resetSet(unsigned int uglobal_reset);

int HDMI_SWRESET_sw_reset_mod_clockSet(unsigned int usw_reset_mod_clock);
int HDMI_SWRESET_sw_reset_tmds_clockSet(unsigned int usw_reset_tmds_clock);
int HDMI_SWRESET_sw_reset_mpll_clockSet(unsigned int usw_reset_mpll_clock);
int HDMI_SWRESET_sw_reset_nco_clockSet(unsigned int usw_reset_nco_clock);
int HDMI_SWRESET_sw_reset_fd_clockSet(unsigned int usw_reset_fd_clock);
int HDMI_SWRESET_sw_reset_mod_and_mpll_clockSet(unsigned int usw_reset_mod_and_mpll_clock);
int HDMI_SWRESET_sw_reset_mod_and_nco_clockSet(unsigned int usw_reset_mod_and_nco_clock);
int HDMI_SWRESET_sw_reset_mod_and_fd_clockSet(unsigned int usw_reset_mod_and_fd_clock);
int HDMI_SWRESET_sw_reset_hsfifo_clockSet(unsigned int usw_reset_hsfifo_clock);
int HDMI_SWRESET_sw_reset_txfifo_clockSet(unsigned int usw_reset_txfifo_clock);
int HDMI_SWRESET_sw_reset_data_clockSet(unsigned int usw_reset_data_clock);
int HDMI_SWRESET_sw_reset_hs_clockSet(unsigned int usw_reset_hs_clock);
int HDMI_SWRESET_sw_reset_pllref_clockSet(unsigned int usw_reset_pllref_clock);
int HDMI_SWRESET_sw_reset_dac_clockSet(unsigned int usw_reset_dac_clock);

int HDMI_SWRESET_up_sample_fifo_clock_swrstSet(unsigned int uup_sample_fifo_clock_swrst);

int HDMI_FCCONTINSET0_fccontinset0_unusedSet(unsigned int ufccontinset0_unused);
int HDMI_CTSET1_i_mpll_fconSet(unsigned int ui_mpll_fcon);
int HDMI_CTSET1_i_mpll_ctlckSet(unsigned int ui_mpll_ctlck);
int HDMI_CTSET1_ctset1_unusedSet(unsigned int uctset1_unused);
int HDMI_FCDSTEPSET_fcdstepset_unusedSet(unsigned int ufcdstepset_unused);
int HDMI_STBOPT_req_lengthSet(unsigned int ureq_length);
int HDMI_STBOPT_stb_cs_selSet(unsigned int ustb_cs_sel);
int HDMI_FDSRCPARAM_fdsrcparam_unusedSet(unsigned int ufdsrcparam_unused);
int HDMI_FCGSET_p_fcg_enSet(unsigned int up_fcg_en);
int HDMI_FCGSET_p_fcg_dlf_enSet(unsigned int up_fcg_dlf_en);
int HDMI_FCGSET_p_fcg_dither_enSet(unsigned int up_fcg_dither_en);
int HDMI_FCGSET_p_fcg_lock_enSet(unsigned int up_fcg_lock_en);
int HDMI_FCGCNT_p_tmds_cnt_valSet(unsigned int up_tmds_cnt_val);
int HDMI_FCGCNT_p_cnt1_targetSet(unsigned int up_cnt1_target);
int HDMI_FCGPARAM_p_lock_cntSet(unsigned int up_lock_cnt);
int HDMI_FCGPARAM_p_lock_thSet(unsigned int up_lock_th);
int HDMI_FCGPARAM_p_kiSet(unsigned int up_ki);
int HDMI_FCGPARAM_p_lock_modeSet(unsigned int up_lock_mode);
int HDMI_FCGSTATE_o_dlf_lockGet(HI_VOID);
int HDMI_FCGSTATE_o_dlf_ovGet(HI_VOID);
int HDMI_FCGSTATE_o_dlf_unGet(HI_VOID);
int HDMI_TXFIFOSET0_txfifoset0_unusedSet(unsigned int utxfifoset0_unused);
int HDMI_HDMI_MODE_reg_hdmi_mode_enSet(unsigned int ureg_hdmi_mode_en);
int HDMI_SWRESET_sw_reset_frl_clockSet(unsigned int usw_reset_frl_clock);
int HDMI_STBOPT_stb_delay2Set(unsigned int ustb_delay2);
int HDMI_STBOPT_stb_delay1Set(unsigned int ustb_delay1);
int HDMI_STBOPT_stb_delay0Set(unsigned int ustb_delay0);
int HDMI_STBOPT_stb_acc_selSet(unsigned int ustb_acc_sel);
int HDMI_FCSTAT_clk_okGet(HI_VOID);
int HDMI_FCSTAT_doneGet(HI_VOID);
int HDMI_FCSTAT_errorGet(HI_VOID);
int HDMI_FCGCNT_p_tmds_cnt_valGet(HI_VOID);

#ifdef HI3559A_TEST
int HDMI_T2GPPORT0_gpport0Set(unsigned int ugpport0);
int HDMI_T2GPPORT0_gpport0Get(HI_VOID);
int HDMI_T2GPPORT1_gpport1Set(unsigned int ugpport1);
int HDMI_T2GPPORT1_gpport1Get(HI_VOID);
int HDMI_PHY_CSEN_stb_cs_enGet(HI_VOID);
int HDMI_PHY_WR_stb_wenGet(HI_VOID);
int HDMI_PHY_ADDR_stb_addrGet(HI_VOID);
int HDMI_PHY_WDATA_stb_wdataGet(HI_VOID);
int HDMI_PHY_RDATA_stb_rdataSet(unsigned int ustb_rdata);
int HDMI_ZCALREG_zcalSet(unsigned int uzcal);
int HDMI_ZCALREG_zcalGet(HI_VOID);
int HDMI_ZCALREG_zcaldoneSet(unsigned int uzcaldone);
int HDMI_ZCALREG_zcaldoneGet(HI_VOID);
int HDMI_ZCALREG_zcalsubSet(unsigned int uzcalsub);
int HDMI_ZCALREG_zcalsubGet(HI_VOID);
int HDMI_ZCALREG_rxsenseSet(unsigned int urxsense);
int HDMI_ZCALREG_rxsenseGet(HI_VOID);
int HDMI_ZCALCLK_zcalclkSet(unsigned int uzcalclk);
int HDMI_ZCALCLK_zcalclkGet(HI_VOID);
int HDMI_SHORTDET_c0shortdetSet(unsigned int uc0shortdet);
int HDMI_SHORTDET_c0shortdetGet(HI_VOID);
int HDMI_SHORTDET_c1shortdetSet(unsigned int uc1shortdet);
int HDMI_SHORTDET_c1shortdetGet(HI_VOID);
int HDMI_SHORTDET_c2shortdetSet(unsigned int uc2shortdet);
int HDMI_SHORTDET_c2shortdetGet(HI_VOID);
int HDMI_SHORTDET_clkshortdetSet(unsigned int uclkshortdet);
int HDMI_SHORTDET_clkshortdetGet(HI_VOID);
int HDMI_DET_t2_plllkvdetlSet(unsigned int ut2_plllkvdetl);
int HDMI_DET_t2_plllkvdetlGet(HI_VOID);
int HDMI_DET_t2_plllkcdetSet(unsigned int ut2_plllkcdet);
int HDMI_DET_t2_plllkcdetGet(HI_VOID);
int HDMI_DET_t2_plllkvdet2Set(unsigned int ut2_plllkvdet2);
int HDMI_DET_t2_plllkvdet2Get(HI_VOID);
int HDMI_DET_t2_lkvdetlowSet(unsigned int ut2_lkvdetlow);
int HDMI_DET_t2_lkvdetlowGet(HI_VOID);
int HDMI_DET_t2_lkvdethighSet(unsigned int ut2_lkvdethigh);
int HDMI_DET_t2_lkvdethighGet(HI_VOID);
int HDMI_FDSRCPARAM_src_enableGet(HI_VOID);
int HDMI_FDSRCPARAM_fdsrcparam_unusedGet(HI_VOID);
int HDMI_FDSRCPARAM_src_lock_valGet(HI_VOID);
int HDMI_FDSRCFREQ_src_cnt_optGet(HI_VOID);
int HDMI_FDSRCPARAM_src_lock_cntGet(HI_VOID);
int HDMI_FDSRCFREQ_fdsrcfreq_unused_1Get(HI_VOID);
int HDMI_FDSRCFREQ_src_freq_optGet(HI_VOID);
int HDMI_FDSRCFREQ_fdsrcfreq_unused_2Get(HI_VOID);
int HDMI_FDSRCFREQ_src_freq_extGet(HI_VOID);
int HDMI_FDSRCRES_src_det_statSet(unsigned int usrc_det_stat);
int HDMI_FDSRCRES_src_cnt_outSet(unsigned int usrc_cnt_out);
int HDMI_CTSET0_i_enableGet(HI_VOID);
int HDMI_CTSET0_i_runGet(HI_VOID);
int HDMI_CTSET0_ctset0_unusedGet(HI_VOID);
int HDMI_CTSET1_i_mpll_fconGet(HI_VOID);
int HDMI_CTSET1_i_mpll_divnGet(HI_VOID);
int HDMI_CTSET1_i_mpll_ctlckGet(HI_VOID);
int HDMI_CTSET1_ctset1_unusedGet(HI_VOID);
int HDMI_FCCNTR0_i_deci_cnt_lenGet(HI_VOID);
int HDMI_FCCNTR0_i_vco_st_wait_lenGet(HI_VOID);
int HDMI_FCCNTR0_i_vco_end_wait_lenGet(HI_VOID);
int HDMI_FCCNTR0_i_ref_cnt_lenGet(HI_VOID);
int HDMI_FCOPT_i_ct_selGet(HI_VOID);
int HDMI_FCOPT_i_clkdet_selGet(HI_VOID);
int HDMI_FCOPT_i_ct_modeGet(HI_VOID);
int HDMI_FCOPT_fcopt_unused_1Get(HI_VOID);
int HDMI_FCOPT_i_ct_enGet(HI_VOID);
int HDMI_FCOPT_fcopt_unused_2Get(HI_VOID);
int HDMI_FCOPT_i_ct_idx_selGet(HI_VOID);
int HDMI_FCOPT_i_deci_try_selGet(HI_VOID);
int HDMI_FCOPT_fcopt_unusedGet(HI_VOID);
int HDMI_FCSTAT_clk_okSet(unsigned int uclk_ok);
int HDMI_FCSTAT_busySet(unsigned int ubusy);
int HDMI_FCDSTEPSET_p_divn_h20Get(HI_VOID);
int HDMI_FCDSTEPSET_fcdstepset_unusedGet(HI_VOID);
int HDMI_FCSTAT_doneSet(unsigned int udone);
int HDMI_FCSTAT_errorSet(unsigned int uerror);
int HDMI_FCSTAT_divnSet(unsigned int udivn);
int HDMI_FCSTAT_divnGet(HI_VOID);
int HDMI_FCSTAT_fcstat_unused_1Set(unsigned int ufcstat_unused_1);
int HDMI_FCSTAT_fcstat_unused_1Get(HI_VOID);
int HDMI_FCSTAT_ref_clk_statSet(unsigned int uref_clk_stat);
int HDMI_FCSTAT_ref_clk_statGet(HI_VOID);
int HDMI_FCSTAT_pllvco_clk_statSet(unsigned int upllvco_clk_stat);
int HDMI_FCSTAT_pllvco_clk_statGet(HI_VOID);
int HDMI_FCSTAT_fcstat_unused_2Set(unsigned int ufcstat_unused_2);
int HDMI_FCSTAT_fcstat_unused_2Get(HI_VOID);
int HDMI_FCSTAT_confin_statSet(unsigned int uconfin_stat);
int HDMI_FCSTAT_confin_statGet(HI_VOID);
int HDMI_FCSTAT_fcstat_unused_3Set(unsigned int ufcstat_unused_3);
int HDMI_FCSTAT_fcstat_unused_3Get(HI_VOID);
int HDMI_FCSTAT_fcon_initSet(unsigned int ufcon_init);
int HDMI_FCSTAT_fcon_initGet(HI_VOID);
int HDMI_FCCNTVAL0_o_cnt_refSet(unsigned int uo_cnt_ref);
int HDMI_FCCNTVAL0_o_cnt_refGet(HI_VOID);
int HDMI_FCCNTVAL1_o_cnt_mpllSet(unsigned int uo_cnt_mpll);
int HDMI_FCCNTVAL1_o_cnt_mpllGet(HI_VOID);
int HDMI_FCRESVAL_o_divn_mpllSet(unsigned int uo_divn_mpll);
int HDMI_FCRESVAL_o_divn_mpllGet(HI_VOID);
int HDMI_FCRESVAL_fcresval_unusedSet(unsigned int ufcresval_unused);
int HDMI_FCRESVAL_fcresval_unusedGet(HI_VOID);
int HDMI_FCRESVAL_o_fcon_mpllSet(unsigned int uo_fcon_mpll);
int HDMI_FCRESVAL_o_fcon_mpllGet(HI_VOID);
int HDMI_FCDSTEPTH_i_h2_selSet(unsigned int ui_h2_sel);
int HDMI_FCDSTEPTH_i_h2_selGet(HI_VOID);
int HDMI_FCDSTEPTH_i_deci_selSet(unsigned int ui_deci_sel);
int HDMI_FCDSTEPTH_i_deci_selGet(HI_VOID);
int HDMI_FCDSTEPTH0_i_deci2x_thSet(unsigned int ui_deci2x_th);
int HDMI_FCDSTEPTH0_i_deci2x_thGet(HI_VOID);
int HDMI_FCDSTEPTH0_i_deci4x_thSet(unsigned int ui_deci4x_th);
int HDMI_FCDSTEPTH0_i_deci4x_thGet(HI_VOID);
int HDMI_FCDSTEPTH1_i_deci8x_thSet(unsigned int ui_deci8x_th);
int HDMI_FCDSTEPTH1_i_deci8x_thGet(HI_VOID);
int HDMI_FCDSTEPTH1_i_deci16x_thSet(unsigned int ui_deci16x_th);
int HDMI_FCDSTEPTH1_i_deci16x_thGet(HI_VOID);
int HDMI_FCCNTR1_i_ref_cntGet(HI_VOID);
int HDMI_FCCONTINSET0_p_contin_upd_enGet(HI_VOID);
int HDMI_FCCONTINSET0_p_contin_upd_optGet(HI_VOID);
int HDMI_FCCONTINSET0_p_contin_upd_polGet(HI_VOID);
int HDMI_FCCONTINSET0_fccontinset0_unusedGet(HI_VOID);
int HDMI_FCCONTINSET0_p_contin_upd_stepGet(HI_VOID);
int HDMI_FCCONTINSET1_p_contin_upd_rateGet(HI_VOID);
int HDMI_FCCONTINSET1_p_contin_upd_timeGet(HI_VOID);
int HDMI_FCCONTINSET2_p_contin_upd_th_dnGet(HI_VOID);
int HDMI_FCCONTINSET2_fccontinset2_unusedGet(HI_VOID);
int HDMI_FCCONTINSET2_p_contin_upd_th_upGet(HI_VOID);
int HDMI_FDIVSET0_initGet(HI_VOID);
int HDMI_FDIVSET1_step_dGet(HI_VOID);
int HDMI_FDIVSET1_step_tGet(HI_VOID);
int HDMI_FDIVSET1_step_nGet(HI_VOID);
int HDMI_FDIVSET2_upSet(unsigned int uup);
int HDMI_FDIVSET2_upGet(HI_VOID);
int HDMI_FDIVSET2_dnSet(unsigned int udn);
int HDMI_FDIVSET2_dnGet(HI_VOID);
int HDMI_FDIVSET3_mod_lenGet(HI_VOID);
int HDMI_FDIVSET3_mod_lenGet(HI_VOID);
int HDMI_FDIVSET3_mod_tGet(HI_VOID);
int HDMI_FDIVSET3_mod_nGet(HI_VOID);
int HDMI_FDIVSET4_mod_dGet(HI_VOID);
int HDMI_FDIVSET5_p_mod_upSet(unsigned int up_mod_up);
int HDMI_FDIVSET5_p_mod_upGet(HI_VOID);
int HDMI_FDIVSET5_p_mod_dnSet(unsigned int up_mod_dn);
int HDMI_FDIVSET5_p_mod_dnGet(HI_VOID);
int HDMI_FDIVSET5_fdivset5_unusedSet(unsigned int ufdivset5_unused);
int HDMI_FDIVSET5_fdivset5_unusedGet(HI_VOID);
int HDMI_FDIVSTAT0_stc_runSet(unsigned int ustc_run);
int HDMI_FDIVSTAT0_stc_runGet(HI_VOID);
int HDMI_FDIVSTAT0_stc_dirSet(unsigned int ustc_dir);
int HDMI_FDIVSTAT0_stc_dirGet(HI_VOID);
int HDMI_FDIVSTAT0_stc_ovSet(unsigned int ustc_ov);
int HDMI_FDIVSTAT0_stc_ovGet(HI_VOID);
int HDMI_FDIVSTAT0_stc_unSet(unsigned int ustc_un);
int HDMI_FDIVSTAT0_stc_unGet(HI_VOID);
int HDMI_FDIVSTAT0_stc_cntSet(unsigned int ustc_cnt);
int HDMI_FDIVSTAT0_stc_cntGet(HI_VOID);
int HDMI_FDIVMANUAL_i_manual_enGet(HI_VOID);
int HDMI_FDIVSTAT1_i_fdiv_inGet(HI_VOID);
int HDMI_FDIVSTAT2_div_outSet(unsigned int udiv_out);
int HDMI_FDIVSTAT2_div_outGet(HI_VOID);
int HDMI_FDIVSTAT3_div_sdmSet(unsigned int udiv_sdm);
int HDMI_FDIVSTAT3_div_sdmGet(HI_VOID);
int HDMI_FDIVSTAT4_stm_runSet(unsigned int ustm_run);
int HDMI_FDIVSTAT4_stm_runGet(HI_VOID);
int HDMI_FDIVSTAT4_stm_phSet(unsigned int ustm_ph);
int HDMI_FDIVSTAT4_stm_phGet(HI_VOID);
int HDMI_FDIVSTAT4_stm_ovSet(unsigned int ustm_ov);
int HDMI_FDIVSTAT4_stm_ovGet(HI_VOID);
int HDMI_FDIVSTAT4_stm_unSet(unsigned int ustm_un);
int HDMI_FDIVSTAT4_stm_unGet(HI_VOID);
int HDMI_FDIVMANUAL_i_divnGet(HI_VOID);
int HDMI_FDIVSTAT4_fdivstat4_unusedSet(unsigned int ufdivstat4_unused);
int HDMI_FDIVSTAT4_fdivstat4_unusedGet(HI_VOID);
int HDMI_FDIVSTAT4_stm_cntSet(unsigned int ustm_cnt);
int HDMI_FDIVSTAT4_stm_cntGet(HI_VOID);
int HDMI_FDIVMANUAL_fdivmanual_unusedGet(HI_VOID);
int HDMI_FDIVMANUAL_i_mdivGet(HI_VOID);
int HDMI_FDIVMANUAL_i_ref_cnt_divGet(HI_VOID);
int HDMI_FDIVMANUAL_i_dc_selGet(HI_VOID);
int HDMI_FDIVMANUAL_i_vicGet(HI_VOID);
int HDMI_REFCLKSEL_t2_refclkselGet(HI_VOID);
int HDMI_REFCLKSEL_t2_refclksel2Get(HI_VOID);
int HDMI_REFCLKSEL_i_ref_clk_selGet(HI_VOID);
int HDMI_REFCLKSEL_refclksel_unused_1Get(HI_VOID);
int HDMI_REFCLKSEL_refclksel_unused_2Get(HI_VOID);
int HDMI_REFCLKSEL_t2_pixelclkselGet(HI_VOID);
int HDMI_REFCLKSEL_p_pr_enc_valGet(HI_VOID);
int HDMI_FDPLLPARAM_pll_lock_valSet(unsigned int upll_lock_val);
int HDMI_FDPLLPARAM_pll_lock_valGet(HI_VOID);
int HDMI_FDPLLPARAM_pll_lock_cntSet(unsigned int upll_lock_cnt);
int HDMI_FDPLLPARAM_pll_lock_cntGet(HI_VOID);
int HDMI_FDPLLPARAM_pll_enableSet(unsigned int upll_enable);
int HDMI_FDPLLPARAM_pll_enableGet(HI_VOID);
int HDMI_FDPLLPARAM_fdpllparam_unusedSet(unsigned int ufdpllparam_unused);
int HDMI_FDPLLPARAM_fdpllparam_unusedGet(HI_VOID);
int HDMI_FDPLLFREQ_pll_cnt_optSet(unsigned int upll_cnt_opt);
int HDMI_FDPLLFREQ_pll_cnt_optGet(HI_VOID);
int HDMI_FDPLLFREQ_fdpllfreq_unused_1Set(unsigned int ufdpllfreq_unused_1);
int HDMI_FDPLLFREQ_fdpllfreq_unused_1Get(HI_VOID);
int HDMI_FDPLLFREQ_pll_freq_optSet(unsigned int upll_freq_opt);
int HDMI_FDPLLFREQ_pll_freq_optGet(HI_VOID);
int HDMI_FDPLLFREQ_fdpllfreq_unused_2Set(unsigned int ufdpllfreq_unused_2);
int HDMI_FDPLLFREQ_fdpllfreq_unused_2Get(HI_VOID);
int HDMI_FDPLLFREQ_pll_freq_extSet(unsigned int upll_freq_ext);
int HDMI_FDPLLFREQ_pll_freq_extGet(HI_VOID);
int HDMI_FDPLLRES_pll_det_statSet(unsigned int upll_det_stat);
int HDMI_FDPLLRES_pll_det_statGet(HI_VOID);
int HDMI_FDPLLRES_pll_cnt_outSet(unsigned int upll_cnt_out);
int HDMI_FDPLLRES_pll_cnt_outGet(HI_VOID);
int HDMI_FCGCNT_p_cnt1_targetGet(HI_VOID);
int HDMI_FCGSET_p_fcg_enGet(HI_VOID);
int HDMI_FCGSET_p_fcg_dlf_enGet(HI_VOID);
int HDMI_FCGPARAM_p_lock_cntGet(HI_VOID);
int HDMI_FCGSET_p_fcg_dither_enGet(HI_VOID);
int HDMI_FCGPARAM_p_lock_thGet(HI_VOID);
int HDMI_FCGSET_p_fcg_lock_enGet(HI_VOID);
int HDMI_FCGPARAM_p_lock_modeGet(HI_VOID);
int HDMI_FCGPARAM_p_kiGet(HI_VOID);
int HDMI_FCGSTATE_o_dlf_unSet(unsigned int uo_dlf_un);
int HDMI_FCGSTATE_o_dlf_ovSet(unsigned int uo_dlf_ov);
int HDMI_FCGSTATE_o_dlf_lockSet(unsigned int uo_dlf_lock);
int HDMI_TXTELOSET_p_ch_en_h20Get(HI_VOID);
int HDMI_TXTELOSET_p_ch_en_h20Get(HI_VOID);
int HDMI_TXTELOSET_p_prbs_clr_h20Get(HI_VOID);
int HDMI_TXTELOSET_p_ch_en_h21Get(HI_VOID);
int HDMI_TXTELOSET_p_prbs_clr_h21Get(HI_VOID);
int HDMI_TXTELOSET_p_test_pat_typeGet(HI_VOID);
int HDMI_TXTELOSET_p_ch_test_enGet(HI_VOID);
int HDMI_TXTELOSET_p_test_4to1_mux_sel0Set(unsigned int up_test_4to1_mux_sel0);
int HDMI_TXTELOSET_p_test_4to1_mux_sel0Get(HI_VOID);
int HDMI_TXTELOSET_p_test_4to1_mux_sel1Set(unsigned int up_test_4to1_mux_sel1);
int HDMI_TXTELOSET_p_test_4to1_mux_sel1Get(HI_VOID);
int HDMI_TXTELOSET_p_test_4to1_mux_sel2Set(unsigned int up_test_4to1_mux_sel2);
int HDMI_TXTELOSET_p_test_4to1_mux_sel2Get(HI_VOID);
int HDMI_TXTELOSET_p_test_4to1_mux_sel3Set(unsigned int up_test_4to1_mux_sel3);
int HDMI_TXTELOSET_p_test_4to1_mux_sel3Get(HI_VOID);
int HDMI_TXTELOCONT0_p_test_pat_ch0Set(unsigned int up_test_pat_ch0);
int HDMI_TXTELOCONT0_p_test_pat_ch0Get(HI_VOID);
int HDMI_TXTELOCONT0_p_test_pat_ch1_lSet(unsigned int up_test_pat_ch1_l);
int HDMI_TXTELOCONT0_p_test_pat_ch1_lGet(HI_VOID);
int HDMI_TXTELOCONT1_p_test_pat_ch1_hSet(unsigned int up_test_pat_ch1_h);
int HDMI_TXTELOCONT1_p_test_pat_ch1_hGet(HI_VOID);
int HDMI_TXTELOCONT1_p_test_pat_ch2Set(unsigned int up_test_pat_ch2);
int HDMI_TXTELOCONT1_p_test_pat_ch2Get(HI_VOID);
int HDMI_TXTELOCONT2_p_test_pat_ch3Get(HI_VOID);
int HDMI_TXFIFOSET0_p_pr_en_h20Get(HI_VOID);
int HDMI_TXFIFOSET0_p_enable_h20Get(HI_VOID);
int HDMI_TXFIFOSET0_txfifoset0_unusedGet(HI_VOID);
int HDMI_TXFIFOSET1_p_pol_inv0_h20Set(unsigned int up_pol_inv0_h20);
int HDMI_TXFIFOSET1_p_pol_inv0_h20Get(HI_VOID);
int HDMI_TXFIFOSET1_p_data_swap0_h20Set(unsigned int up_data_swap0_h20);
int HDMI_TXFIFOSET1_p_data_swap0_h20Get(HI_VOID);
int HDMI_TXFIFOSET1_p_ch_sel0_h20Set(unsigned int up_ch_sel0_h20);
int HDMI_TXFIFOSET1_p_ch_sel0_h20Get(HI_VOID);
int HDMI_TXFIFOSET1_p_pol_inv1_h20Set(unsigned int up_pol_inv1_h20);
int HDMI_TXFIFOSET1_p_pol_inv1_h20Get(HI_VOID);
int HDMI_TXFIFOSET1_p_data_swap1_h20Set(unsigned int up_data_swap1_h20);
int HDMI_TXFIFOSET1_p_data_swap1_h20Get(HI_VOID);
int HDMI_TXFIFOSET1_p_ch_sel1_h20Set(unsigned int up_ch_sel1_h20);
int HDMI_TXFIFOSET1_p_ch_sel1_h20Get(HI_VOID);
int HDMI_TXFIFOSTAT0_o_pr_fifo_state_h20Set(unsigned int uo_pr_fifo_state_h20);
int HDMI_TXFIFOSTAT0_o_pr_fifo_state_h20Get(HI_VOID);
int HDMI_TXFIFOSTAT0_txfifostat0_unusedSet(unsigned int utxfifostat0_unused);
int HDMI_TXFIFOSTAT0_txfifostat0_unusedGet(HI_VOID);
int HDMI_TXFIFOSTAT1_txfifostat1_unused_0Set(unsigned int utxfifostat1_unused_0);
int HDMI_TXFIFOSTAT1_txfifostat1_unused_0Get(HI_VOID);
int HDMI_TXFIFOSTAT1_txfifostat1_unused_1Set(unsigned int utxfifostat1_unused_1);
int HDMI_TXFIFOSTAT1_txfifostat1_unused_1Get(HI_VOID);
int HDMI_TXFIFOSTAT2_o_tx_fifo_state_h20Set(unsigned int uo_tx_fifo_state_h20);
int HDMI_TXFIFOSTAT2_o_tx_fifo_state_h20Get(HI_VOID);
int HDMI_TXFIFOSTAT2_txfifostat2_unusedSet(unsigned int utxfifostat2_unused);
int HDMI_TXFIFOSTAT2_txfifostat2_unusedGet(HI_VOID);
int HDMI_TXFIFOSTAT3_txfifostat3_unused_0Set(unsigned int utxfifostat3_unused_0);
int HDMI_TXFIFOSTAT3_txfifostat3_unused_0Get(HI_VOID);
int HDMI_TXFIFOSTAT3_txfifostat3_unused_1Set(unsigned int utxfifostat3_unused_1);
int HDMI_TXFIFOSTAT3_txfifostat3_unused_1Get(HI_VOID);
int HDMI_DATACLKINV_p_dataclkinvGet(HI_VOID);
int HDMI_HDMI_MODE_reg_hdmi_mode_enGet(HI_VOID);
int HDMI_CLK_DATA_1_reg_clk_data_phase0Set(unsigned int ureg_clk_data_phase0);
int HDMI_CLK_DATA_1_reg_clk_data_phase0Get(HI_VOID);
int HDMI_CLK_DATA_1_reg_clk_data_phase1Set(unsigned int ureg_clk_data_phase1);
int HDMI_CLK_DATA_1_reg_clk_data_phase1Get(HI_VOID);
int HDMI_CLK_DATA_1_reg_sw_clk_enSet(unsigned int ureg_sw_clk_en);
int HDMI_CLK_DATA_1_reg_sw_clk_enGet(HI_VOID);
int HDMI_CLK_DATA_2_reg_clk_data_phase2Set(unsigned int ureg_clk_data_phase2);
int HDMI_CLK_DATA_2_reg_clk_data_phase2Get(HI_VOID);
int HDMI_CLK_DATA_2_reg_clk_data_phase3Set(unsigned int ureg_clk_data_phase3);
int HDMI_CLK_DATA_2_reg_clk_data_phase3Get(HI_VOID);
int HDMI_CFG18TO20_reg_18to20_fifo_rd_rstSet(unsigned int ureg_18to20_fifo_rd_rst);
int HDMI_CFG18TO20_reg_18to20_fifo_rd_rstGet(HI_VOID);
int HDMI_CFG18TO20_reg_18to20_fifo_wr_rstSet(unsigned int ureg_18to20_fifo_wr_rst);
int HDMI_CFG18TO20_reg_18to20_fifo_wr_rstGet(HI_VOID);
int HDMI_CFG18TO20_reg_rd_bypassSet(unsigned int ureg_rd_bypass);
int HDMI_CFG18TO20_reg_rd_bypassGet(HI_VOID);
int HDMI_CFG18TO20_reg_status_rrstSet(unsigned int ureg_status_rrst);
int HDMI_CFG18TO20_reg_status_rrstGet(HI_VOID);
int HDMI_CFG18TO20_reg_status_wrstSet(unsigned int ureg_status_wrst);
int HDMI_CFG18TO20_reg_status_wrstGet(HI_VOID);
int HDMI_FIFOSTAT18TO20_empty_statusSet(unsigned int uempty_status);
int HDMI_FIFOSTAT18TO20_empty_statusGet(HI_VOID);
int HDMI_FIFOSTAT18TO20_aempty_statusSet(unsigned int uaempty_status);
int HDMI_FIFOSTAT18TO20_aempty_statusGet(HI_VOID);
int HDMI_FIFOSTAT18TO20_full_statusSet(unsigned int ufull_status);
int HDMI_FIFOSTAT18TO20_full_statusGet(HI_VOID);
int HDMI_FIFOSTAT18TO20_afull_statusSet(unsigned int uafull_status);
int HDMI_FIFOSTAT18TO20_afull_statusGet(HI_VOID);
int HDMI_HSSET_p_hssetGet(HI_VOID);
int HDMI_HSRXSENSE_w_hsrxsenseSet(unsigned int uw_hsrxsense);
int HDMI_HSRXSENSE_w_hsrxsenseGet(HI_VOID);
int HDMI_HSFIFOSTAT_o_fifo_state_hsSet(unsigned int uo_fifo_state_hs);
int HDMI_HSFIFOSTAT_o_fifo_state_hsGet(HI_VOID);
int HDMI_INTRSTAT_hs_fifo_empty_intrSet(unsigned int uhs_fifo_empty_intr);
int HDMI_INTRSTAT_hs_fifo_empty_intrGet(HI_VOID);
int HDMI_INTRSTAT_hs_fifo_full_intrSet(unsigned int uhs_fifo_full_intr);
int HDMI_INTRSTAT_hs_fifo_full_intrGet(HI_VOID);
int HDMI_INTRSTAT_up_sample_fifo_empty_intrSet(unsigned int uup_sample_fifo_empty_intr);
int HDMI_INTRSTAT_up_sample_fifo_empty_intrGet(HI_VOID);
int HDMI_INTRSTAT_up_sample_fifo_full_intrSet(unsigned int uup_sample_fifo_full_intr);
int HDMI_INTRSTAT_up_sample_fifo_full_intrGet(HI_VOID);
int HDMI_INTRSTAT_trinsmitter_fifo_empty_intrSet(unsigned int utrinsmitter_fifo_empty_intr);
int HDMI_INTRSTAT_trinsmitter_fifo_empty_intrGet(HI_VOID);
int HDMI_INTRSTAT_trinsmitter_fifo_full_intrSet(unsigned int utrinsmitter_fifo_full_intr);
int HDMI_INTRSTAT_trinsmitter_fifo_full_intrGet(HI_VOID);
int HDMI_INTRSTAT_lkvdethigh_intrSet(unsigned int ulkvdethigh_intr);
int HDMI_INTRSTAT_lkvdethigh_intrGet(HI_VOID);
int HDMI_INTRSTAT_lkvdetlow_intrSet(unsigned int ulkvdetlow_intr);
int HDMI_INTRSTAT_lkvdetlow_intrGet(HI_VOID);
int HDMI_INTRSTAT_ct_fcon_intrSet(unsigned int uct_fcon_intr);
int HDMI_INTRSTAT_ct_fcon_intrGet(HI_VOID);
int HDMI_INTRMASK_hs_fifo_empty_intr_maskSet(unsigned int uhs_fifo_empty_intr_mask);
int HDMI_INTRMASK_hs_fifo_empty_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_hs_fifo_full_intr_maskSet(unsigned int uhs_fifo_full_intr_mask);
int HDMI_INTRMASK_hs_fifo_full_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_up_sample_fifo_empty_intr_maskSet(unsigned int uup_sample_fifo_empty_intr_mask);
int HDMI_INTRMASK_up_sample_fifo_empty_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_up_sample_fifo_full_intr_maskSet(unsigned int uup_sample_fifo_full_intr_mask);
int HDMI_INTRMASK_up_sample_fifo_full_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_trinsmitter_fifo_empty_intr_maskSet(unsigned int utrinsmitter_fifo_empty_intr_mask);
int HDMI_INTRMASK_trinsmitter_fifo_empty_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_trinsmitter_fifo_full_intr_maskSet(unsigned int utrinsmitter_fifo_full_intr_mask);
int HDMI_INTRMASK_trinsmitter_fifo_full_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_lkvdethigh_intr_maskSet(unsigned int ulkvdethigh_intr_mask);
int HDMI_INTRMASK_lkvdethigh_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_lkvdetlow_intr_maskSet(unsigned int ulkvdetlow_intr_mask);
int HDMI_INTRMASK_lkvdetlow_intr_maskGet(HI_VOID);
int HDMI_INTRMASK_ct_fcon_intr_maskSet(unsigned int uct_fcon_intr_mask);
int HDMI_INTRMASK_ct_fcon_intr_maskGet(HI_VOID);
int HDMI_INTRSET_hs_fifo_empty_triger_typeSet(unsigned int uhs_fifo_empty_triger_type);
int HDMI_INTRSET_hs_fifo_empty_triger_typeGet(HI_VOID);
int HDMI_INTRSET_hs_fifo_empty_intr_enSet(unsigned int uhs_fifo_empty_intr_en);
int HDMI_INTRSET_hs_fifo_empty_intr_enGet(HI_VOID);
int HDMI_INTRSET_hs_fifo_full_triger_typeSet(unsigned int uhs_fifo_full_triger_type);
int HDMI_INTRSET_hs_fifo_full_triger_typeGet(HI_VOID);
int HDMI_INTRSET_hs_fifo_full_intr_enSet(unsigned int uhs_fifo_full_intr_en);
int HDMI_INTRSET_hs_fifo_full_intr_enGet(HI_VOID);
int HDMI_INTRSET_up_sample_fifo_empty_triger_typeSet(unsigned int uup_sample_fifo_empty_triger_type);
int HDMI_INTRSET_up_sample_fifo_empty_triger_typeGet(HI_VOID);
int HDMI_INTRSET_up_sample_fifo_empty_intr_enSet(unsigned int uup_sample_fifo_empty_intr_en);
int HDMI_INTRSET_up_sample_fifo_empty_intr_enGet(HI_VOID);
int HDMI_INTRSET_up_sample_fifo_full_triger_typeSet(unsigned int uup_sample_fifo_full_triger_type);
int HDMI_INTRSET_up_sample_fifo_full_triger_typeGet(HI_VOID);
int HDMI_INTRSET_up_sample_fifo_full_intr_enSet(unsigned int uup_sample_fifo_full_intr_en);
int HDMI_INTRSET_up_sample_fifo_full_intr_enGet(HI_VOID);
int HDMI_INTRSET_transmitter_fifo_empty_triger_typeSet(unsigned int utransmitter_fifo_empty_triger_type);
int HDMI_INTRSET_transmitter_fifo_empty_triger_typeGet(HI_VOID);
int HDMI_INTRSET_transmitter_fifo_empty_intr_enSet(unsigned int utransmitter_fifo_empty_intr_en);
int HDMI_INTRSET_transmitter_fifo_empty_intr_enGet(HI_VOID);
int HDMI_INTRSET_transmitter_fifo_full_triger_typeSet(unsigned int utransmitter_fifo_full_triger_type);
int HDMI_INTRSET_transmitter_fifo_full_triger_typeGet(HI_VOID);
int HDMI_INTRSET_transmitter_fifo_full_intr_enSet(unsigned int utransmitter_fifo_full_intr_en);
int HDMI_INTRSET_transmitter_fifo_full_intr_enGet(HI_VOID);
int HDMI_INTRSET_lkvdethigh_triger_typeSet(unsigned int ulkvdethigh_triger_type);
int HDMI_INTRSET_lkvdethigh_triger_typeGet(HI_VOID);
int HDMI_INTRSET_lkvdethigh_intr_enSet(unsigned int ulkvdethigh_intr_en);
int HDMI_INTRSET_lkvdethigh_intr_enGet(HI_VOID);
int HDMI_INTRSET_lkvdetlow_triger_typeSet(unsigned int ulkvdetlow_triger_type);
int HDMI_INTRSET_lkvdetlow_triger_typeGet(HI_VOID);
int HDMI_INTRSET_lkvdetlow_intr_enSet(unsigned int ulkvdetlow_intr_en);
int HDMI_INTRSET_lkvdetlow_intr_enGet(HI_VOID);
int HDMI_CLKSET_p_refclk_selGet(HI_VOID);
int HDMI_CLKSET_p_fd_clk_selGet(HI_VOID);
int HDMI_CLKSET_p_ctmanGet(HI_VOID);
int HDMI_CLKSET_p_modclk_selGet(HI_VOID);
int HDMI_CLKSET_p_fdivclk_selGet(HI_VOID);
int HDMI_CLKSET_mod_div_valGet(HI_VOID);
int HDMI_SWRESET_sw_reset_mod_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_tmds_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_mpll_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_nco_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_fd_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_mod_and_mpll_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_mod_and_nco_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_mod_and_fd_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_hsfifo_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_txfifo_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_data_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_hs_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_pllref_clockGet(HI_VOID);
int HDMI_SWRESET_sw_reset_dac_clockGet(HI_VOID);
int HDMI_SWRESET_dac_clock_gatGet(HI_VOID);

int HDMI_SWRESET_up_sample_fifo_clock_swrstGet(HI_VOID);
int HDMI_SWRESET_sw_reset_frl_clockGet(HI_VOID);
int HDMI_SWRESET_swreset_unusedGet(HI_VOID);
int HDMI_SWRESET_global_resetGet(HI_VOID);
int HDMI_GLUESET0_clk0_divSet(unsigned int uclk0_div);
int HDMI_GLUESET0_clk0_divGet(HI_VOID);
int HDMI_GLUESET0_clk1_divSet(unsigned int uclk1_div);
int HDMI_GLUESET0_clk1_divGet(HI_VOID);
int HDMI_GLUESET0_clk2_divSet(unsigned int uclk2_div);
int HDMI_GLUESET0_clk2_divGet(HI_VOID);
int HDMI_GLUESET0_clk3_divSet(unsigned int uclk3_div);
int HDMI_GLUESET0_clk3_divGet(HI_VOID);
int HDMI_GLUESET0_clk4_divSet(unsigned int uclk4_div);
int HDMI_GLUESET0_clk4_divGet(HI_VOID);
int HDMI_GLUESET0_clk5_divSet(unsigned int uclk5_div);
int HDMI_GLUESET0_clk5_divGet(HI_VOID);
int HDMI_GLUESET0_clk6_divSet(unsigned int uclk6_div);
int HDMI_GLUESET0_clk6_divGet(HI_VOID);
int HDMI_GLUESET0_clk7_divSet(unsigned int uclk7_div);
int HDMI_GLUESET0_clk7_divGet(HI_VOID);
int HDMI_GLUESET1_clk8_divSet(unsigned int uclk8_div);
int HDMI_GLUESET1_clk8_divGet(HI_VOID);
int HDMI_GLUESET1_glueset1_unused_1Set(unsigned int uglueset1_unused_1);
int HDMI_GLUESET1_glueset1_unused_1Get(HI_VOID);
int HDMI_GLUESET1_clk10_divSet(unsigned int uclk10_div);
int HDMI_GLUESET1_clk10_divGet(HI_VOID);
int HDMI_GLUESET1_clk11_divSet(unsigned int uclk11_div);
int HDMI_GLUESET1_clk11_divGet(HI_VOID);
int HDMI_GLUESET1_clk_selSet(unsigned int uclk_sel);
int HDMI_GLUESET1_clk_selGet(HI_VOID);
int HDMI_GLUESET1_glueset1_unused_2Set(unsigned int uglueset1_unused_2);
int HDMI_GLUESET1_glueset1_unused_2Get(HI_VOID);
int HDMI_CT_INTRSET_ct_fcon_triger_typeSet(unsigned int uct_fcon_triger_type);
int HDMI_CT_INTRSET_ct_fcon_triger_typeGet(HI_VOID);
int HDMI_CT_INTRSET_ct_fcon_intr_enSet(unsigned int uct_fcon_intr_en);
int HDMI_CT_INTRSET_ct_fcon_intr_enGet(HI_VOID);
int HDMI_HW_INFO_hw_infoSet(unsigned int uhw_info);
int HDMI_HW_INFO_hw_infoGet(HI_VOID);
int HDMI_HW_VERS_hw_vers_unused_1Set(unsigned int uhw_vers_unused_1);
int HDMI_HW_VERS_hw_vers_unused_1Get(HI_VOID);
int HDMI_HW_VERS_hdmi20_complianceSet(unsigned int uhdmi20_compliance);
int HDMI_HW_VERS_hdmi20_complianceGet(HI_VOID);
int HDMI_HW_VERS_hdmi21_complianceSet(unsigned int uhdmi21_compliance);
int HDMI_HW_VERS_hdmi21_complianceGet(HI_VOID);
int HDMI_HW_VERS_hw_vers_unused_2Set(unsigned int uhw_vers_unused_2);
int HDMI_HW_VERS_hw_vers_unused_2Get(HI_VOID);
int HDMI_RASMODE_ras_modeSet(unsigned int uras_mode);
int HDMI_RASMODE_ras_modeGet(HI_VOID);
int HDMI_RFSMODE_rfs_modeSet(unsigned int urfs_mode);
int HDMI_RFSMODE_rfs_modeGet(HI_VOID);
int HDMI_RFTMODE_rft_modeSet(unsigned int urft_mode);
int HDMI_RFTMODE_rft_modeGet(HI_VOID);
int HDMI_STBOPT_stb_delay2Get(HI_VOID);
int HDMI_STBOPT_req_lengthGet(HI_VOID);
int HDMI_STBOPT_stb_delay1Get(HI_VOID);
int HDMI_STBOPT_stb_delay0Get(HI_VOID);
int HDMI_STBOPT_stb_acc_selGet(HI_VOID);
int HDMI_STBOPT_stb_cs_selGet(HI_VOID);
int HDMI_STBREQ_req_doneSet(unsigned int ureq_done);
int HDMI_STBREQ_req_doneGet(HI_VOID);
int HDMI_FCDSTEPSET_up_sampler_ratio_selGet(HI_VOID);
int HDMI_STBRDATA_stb_auto_rdataSet(unsigned int ustb_auto_rdata);
int HDMI_STBRDATA_stb_auto_rdataGet(HI_VOID);

#endif
#endif // __TX_DPHY_REG_C_UNION_DEFINE_H__
