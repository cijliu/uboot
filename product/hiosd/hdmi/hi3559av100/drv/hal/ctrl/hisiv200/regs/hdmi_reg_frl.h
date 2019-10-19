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

#ifndef __TX_FRL_REG_C_UNION_DEFINE_H__
#define __TX_FRL_REG_C_UNION_DEFINE_H__
#include "hi_type.h"
/* Define the union U_TX_FRL_VERSION */
/* Define the union U_TX_FRL_VERSION,ATTR:,ADDR:3000,INIT:07E10307,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frl_tx_hw_day   : 8  ; /* [7:0] */
        unsigned int    frl_tx_hw_month : 8  ; /* [15:8] */
        unsigned int    frl_tx_hw_year  : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_FRL_VERSION;

/* Define the union U_TX_FRL_TEST */
/* Define the union U_TX_FRL_TEST,ATTR:,ADDR:3004,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tx_frl_test : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_FRL_TEST;

/* Define the union U_WORK_EN */
/* Define the union U_WORK_EN,ATTR:,ADDR:3010,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    work_en : 1  ; /* [0] */
        unsigned int    rsv_0   : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WORK_EN;

/* Define the union U_LINE_START_TIME */
/* Define the union U_LINE_START_TIME,ATTR:,ADDR:3100,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    line_start_time : 16  ; /* [15:0] */
        unsigned int    rsv_1           : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LINE_START_TIME;

/* Define the union U_AV_MAX_LEN */
/* Define the union U_AV_MAX_LEN,ATTR:,ADDR:3104,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    av_max_len : 16  ; /* [15:0] */
        unsigned int    rsv_2      : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AV_MAX_LEN;

/* Define the union U_AV_GAP_LEN */
/* Define the union U_AV_GAP_LEN,ATTR:,ADDR:3108,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    av_gap_len : 16  ; /* [15:0] */
        unsigned int    rsv_3      : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AV_GAP_LEN;

/* Define the union U_BLK_MAX_LEN */
/* Define the union U_BLK_MAX_LEN,ATTR:,ADDR:310C,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blk_max_len : 16  ; /* [15:0] */
        unsigned int    rsv_4       : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_BLK_MAX_LEN;

/* Define the union U_BLK_GAP_LEN */
/* Define the union U_BLK_GAP_LEN,ATTR:,ADDR:3110,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blk_gap_len : 16  ; /* [15:0] */
        unsigned int    rsv_5       : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_BLK_GAP_LEN;

/* Define the union U_HBLANK */
/* Define the union U_HBLANK,ATTR:,ADDR:3114,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hblank : 16  ; /* [15:0] */
        unsigned int    rsv_6  : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HBLANK;

/* Define the union U_HACTIVE */
/* Define the union U_HACTIVE,ATTR:,ADDR:3118,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hactive : 16  ; /* [15:0] */
        unsigned int    rsv_7   : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HACTIVE;

/* Define the union U_EXTRA_BLANK_MAX_LEN */
/* Define the union U_EXTRA_BLANK_MAX_LEN,ATTR:,ADDR:311C,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    extra_blank_max_len : 16  ; /* [15:0] */
        unsigned int    rsv_8               : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EXTRA_BLANK_MAX_LEN;

/* Define the union U_EXTRA_BLANK_GAP_LEN */
/* Define the union U_EXTRA_BLANK_GAP_LEN,ATTR:,ADDR:3120,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    extra_blank_gap_len : 16  ; /* [15:0] */
        unsigned int    rsv_9               : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EXTRA_BLANK_GAP_LEN;

/* Define the union U_SBC_CFIFO_STATUS */
/* Define the union U_SBC_CFIFO_STATUS,ATTR:,ADDR:3124,INIT:00000000,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfifo_status : 8  ; /* [7:0] */
        unsigned int    rsv_10       : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SBC_CFIFO_STATUS;

/* Define the union U_SBC_DFIFO_STATUS */
/* Define the union U_SBC_DFIFO_STATUS,ATTR:,ADDR:3128,INIT:00000000,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfifo_status : 8  ; /* [7:0] */
        unsigned int    rsv_11       : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SBC_DFIFO_STATUS;

/* Define the union U_VACTIVE */
/* Define the union U_VACTIVE,ATTR:,ADDR:312C,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vactive : 16  ; /* [15:0] */
        unsigned int    rsv_12  : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VACTIVE;

/* Define the union U_SYNC_POLAR */
/* Define the union U_SYNC_POLAR,ATTR:,ADDR:3134,INIT:00000000,MASK:f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsync_polar    : 1  ; /* [0] */
        unsigned int    vsync_polar_en : 1  ; /* [1] */
        unsigned int    hsync_polar    : 1  ; /* [2] */
        unsigned int    hsync_polar_en : 1  ; /* [3] */
        unsigned int    rsv_13         : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SYNC_POLAR;

/* Define the union U_EXTRA_MODE_EN */
/* Define the union U_EXTRA_MODE_EN,ATTR:,ADDR:3138,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    extra_mode_en : 1  ; /* [0] */
        unsigned int    rsv_14        : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EXTRA_MODE_EN;

/* Define the union U_SBC_INT_STATUS */
/* Define the union U_SBC_INT_STATUS,ATTR:,ADDR:3140,INIT:00000000,MASK:f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sbc_int_status : 4  ; /* [3:0] */
        unsigned int    rsv_15         : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SBC_INT_STATUS;

/* Define the union U_VBLANK1_LINES */
/* Define the union U_VBLANK1_LINES,ATTR:,ADDR:3144,INIT:00000000,MASK:3ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vblank1_lines : 10  ; /* [9:0] */
        unsigned int    rsv_16        : 22  ; /* [31:10] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VBLANK1_LINES;

/* Define the union U_LINE_START_HSYNC_EN */
/* Define the union U_LINE_START_HSYNC_EN,ATTR:,ADDR:3148,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    line_start_hsync_en : 1  ; /* [0] */
        unsigned int    rsv_17              : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LINE_START_HSYNC_EN;

/* Define the union U_EXTRA_NO_GAP_FLAG */
/* Define the union U_EXTRA_NO_GAP_FLAG,ATTR:,ADDR:3150,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    extra_no_gap_flag : 1  ; /* [0] */
        unsigned int    rsv_18            : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EXTRA_NO_GAP_FLAG;

/* Define the union U_LM_IN_AC0_CMD */
/* Define the union U_LM_IN_AC0_CMD,ATTR:,ADDR:3200,INIT:00000000,MASK:fffffff1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    command        : 1  ; /* [0] */
        unsigned int    rsv_19         : 1  ; /* [1] */
        unsigned int    rsv_20         : 2  ; /* [3:2] */
        unsigned int    protect_number : 4  ; /* [7:4] */
        unsigned int    in_ac0_number  : 8  ; /* [15:8] */
        unsigned int    in_ac0_addr    : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LM_IN_AC0_CMD;

/* Define the union U_LM_CODE_RFD */
/* Define the union U_LM_CODE_RFD,ATTR:,ADDR:3204,INIT:91111111,MASK:cf0f0f0f*/
typedef union
{
    /* Define the struct bits */
	struct
    {
    	unsigned int    code_rfd_init0  : 4  ; /* [3:0] */
    	unsigned int    rsv_3           : 4  ; /* [7:4] */
    	unsigned int    code_rfd_init1  : 4  ; /* [11:8] */
    	unsigned int    rsv_4           : 4  ; /* [15:12] */
    	unsigned int    code_rfd_init2  : 4  ; /* [19:16] */
    	unsigned int    rsv_5           : 4  ; /* [23:20] */
    	unsigned int    code_rfd_init3  : 4  ; /* [27:24] */
    	unsigned int    rsv_6           : 2  ; /* [29:28] */
    	unsigned int    trn_ptn_rsv_set : 1  ; /* [30] */
    	unsigned int    lm_ptn_rsv_en   : 1  ; /* [31] */
    } bits;    /* Define an unsigned member */

	unsigned int    u32;
} U_LM_CODE_RFD;

/* Define the union U_LM_IN_AC0_RDATA */
/* Define the union U_LM_IN_AC0_RDATA,ATTR:,ADDR:3208,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    in_ac0_rdata : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LM_IN_AC0_RDATA;

/* Define the union U_LM_IN_AC0_WDATA */
/* Define the union U_LM_IN_AC0_WDATA,ATTR:,ADDR:320C,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    in_ac0_wdata : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LM_IN_AC0_WDATA;

/* Define the union U_LM_SRC_EN */
/* Define the union U_LM_SRC_EN,ATTR:,ADDR:3210,INIT:00000001,MASK:3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scram_en      : 1  ; /* [0] */
        unsigned int    ram_config_en : 1  ; /* [1] */
        unsigned int    rsv_22        : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LM_SRC_EN;

/* Define the union U_LM_SRC_INIT0 */
/* Define the union U_LM_SRC_INIT0,ATTR:,ADDR:3214,INIT:FFFEFFFF,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lane0_init_value : 16  ; /* [15:0] */
        unsigned int    lane1_init_value : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LM_SRC_INIT0;

/* Define the union U_LM_SRC_INIT1 */
/* Define the union U_LM_SRC_INIT1,ATTR:,ADDR:3218,INIT:FFFCFFFD,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lane2_init_value : 16  ; /* [15:0] */
        unsigned int    lane3_init_value : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LM_SRC_INIT1;

/* Define the union U_LM_COMMAND_EN */
/* Define the union U_LM_COMMAND_EN,ATTR:,ADDR:321C,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    command_en : 1  ; /* [0] */
        unsigned int    rsv_23     : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LM_COMMAND_EN;

/* Define the union U_RS_SPLIT_SB_CNT */
/* Define the union U_RS_SPLIT_SB_CNT,ATTR:,ADDR:3300,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rs_split_sb_cnt : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_RS_SPLIT_SB_CNT;

/* Define the union U_FLT_START */
/* Define the union U_FLT_START,ATTR:,ADDR:3400,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    flt_start : 1  ; /* [0] */
        unsigned int    rsv_24    : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FLT_START;

/* Define the union U_FLT_STOP */
/* Define the union U_FLT_STOP,ATTR:,ADDR:3404,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    flt_stop : 1  ; /* [0] */
        unsigned int    rsv_25   : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FLT_STOP;

/* Define the union U_SCDCS_CONFIG */
/* Define the union U_SCDCS_CONFIG,ATTR:,ADDR:3408,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scdcs_config_in : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCDCS_CONFIG;

/* Define the union U_FFE_LEVELS */
/* Define the union U_FFE_LEVELS,ATTR:,ADDR:340C,INIT:00000000,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    update_clr0_set   : 1  ; /* [0] */
        unsigned int    update_clr1_set   : 1  ; /* [1] */
        unsigned int    req_illegal_noclr : 1  ; /* [2] */
        unsigned int    flt_no_timeout    : 1  ; /* [3] */
        unsigned int    cfg_rd_back_en    : 1  ; /* [4] */
        unsigned int    set_step_abort    : 1  ; /* [5] */
        unsigned int    ptn_100m_rsv      : 1  ; /* [6] */
        unsigned int    rsv_26            : 25 ; /* [31:7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_CFG_SEL;

/* Define the union U_UPDATE_FLAG_TIMER */
/* Define the union U_UPDATE_FLAG_TIMER,ATTR:,ADDR:3414,INIT:00006100,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    update_flag_timer : 24  ; /* [23:0] */
        unsigned int    rsv_27            : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_UPDATE_FLAG_TIMER;

/* Define the union U_FLT_STEP_TIMER */
/* Define the union U_FLT_STEP_TIMER,ATTR:,ADDR:3418,INIT:0003D090,MASK:fffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    step_timeout_timer : 28  ; /* [27:0] */
        unsigned int    rsv_28             : 4  ; /* [31:28] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FLT_STEP_TIMER;

/* Define the union U_FLT_TIMEOUT_TIMER */
/* Define the union U_FLT_TIMEOUT_TIMER,ATTR:,ADDR:341C,INIT:004C4B00,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    flt_timeout_timer : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FLT_TIMEOUT_TIMER;

/* Define the union U_CPU_SET_PATTERN */
/* Define the union U_CPU_SET_PATTERN,ATTR:,ADDR:3420,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lane0_train_ptn_set : 8  ; /* [7:0] */
        unsigned int    lane1_train_ptn_set : 8  ; /* [15:8] */
        unsigned int    lane2_train_ptn_set : 8  ; /* [23:16] */
        unsigned int    lane3_train_ptn_set : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_SET_PATTERN;

/* Define the union U_CPU_SET_RES */
/* Define the union U_CPU_SET_RES,ATTR:,ADDR:3424,INIT:00000000,MASK:f33*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    software_train_set : 1  ; /* [0] */
        unsigned int    flt_skip           : 1  ; /* [1] */
        unsigned int    rsv_29             : 2  ; /* [3:2] */
        unsigned int    soft_train_ok      : 1  ; /* [4] */
        unsigned int    frl_lane_sel_set   : 1  ; /* [5] */
        unsigned int    rsv_30             : 2  ; /* [7:6] */
        unsigned int    soft_train_rate    : 4  ; /* [11:8] */
        unsigned int    rsv_31             : 20  ; /* [31:12] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_SET_RES;

/* Define the union U_FLT_FSM_STATUS */
/* Define the union U_FLT_FSM_STATUS,ATTR:,ADDR:3430,INIT:00000000,MASK:7f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    flt_fsm_curr  : 4  ; /* [3:0] */
        unsigned int    work_lane_num : 1  ; /* [4] */
        unsigned int    work_channel  : 1  ; /* [5] */
        unsigned int    ddc_in_prog   : 1  ; /* [6] */
        unsigned int    rsv_32        : 25  ; /* [31:7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FLT_FSM_STATUS;

/* Define the union U_FLT_LTP */
/* Define the union U_FLT_LTP,ATTR:,ADDR:3434,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ltp_pattern : 16  ; /* [15:0] */
        unsigned int    rsv_33      : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FLT_LTP;

/* Define the union U_FRL_MODE_ACT */
/* Define the union U_FRL_MODE_ACT,ATTR:,ADDR:3438,INIT:00000000,MASK:f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frl_mode_act : 4  ; /* [3:0] */
        unsigned int    rsv_34       : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FRL_MODE_ACT;

/* Define the union U_FLT_RESULT */
/* Define the union U_FLT_RESULT,ATTR:,ADDR:343C,INIT:00000000,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    train_success  : 1  ; /* [0] */
        unsigned int    train_fail     : 1  ; /* [1] */
        unsigned int    train_busy     : 1  ; /* [2] */
        unsigned int    sink_ffe_req   : 1  ; /* [3] */
        unsigned int    train_fail_res : 4  ; /* [7:4] */
        unsigned int    flt_cnt        : 4  ; /* [11:8] */
        unsigned int    frl_work_mode  : 4  ; /* [15:12] */
        unsigned int    rsv_35         : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FLT_RESULT;


//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_TX_FRL_VERSION      TX_FRL_VERSION      ; /* 3000 */
    volatile U_TX_FRL_TEST         TX_FRL_TEST         ; /* 3004 */
    unsigned int           reserved_0[2]                     ; /* 0x3008~0x300c */
    volatile U_WORK_EN             WORK_EN             ; /* 3010 */
    unsigned int           reserved_1[59]                     ; /* 0x3014~0x30fc */
    volatile U_LINE_START_TIME     LINE_START_TIME     ; /* 3100 */
    volatile U_AV_MAX_LEN          AV_MAX_LEN          ; /* 3104 */
    volatile U_AV_GAP_LEN          AV_GAP_LEN          ; /* 3108 */
    volatile U_BLK_MAX_LEN         BLK_MAX_LEN         ; /* 310C */
    volatile U_BLK_GAP_LEN         BLK_GAP_LEN         ; /* 3110 */
    volatile U_HBLANK              HBLANK              ; /* 3114 */
    volatile U_HACTIVE             HACTIVE             ; /* 3118 */
    volatile U_EXTRA_BLANK_MAX_LEN EXTRA_BLANK_MAX_LEN ; /* 311C */
    volatile U_EXTRA_BLANK_GAP_LEN EXTRA_BLANK_GAP_LEN ; /* 3120 */
    volatile U_SBC_CFIFO_STATUS    SBC_CFIFO_STATUS    ; /* 3124 */
    volatile U_SBC_DFIFO_STATUS    SBC_DFIFO_STATUS    ; /* 3128 */
    volatile U_VACTIVE             VACTIVE             ; /* 312C */
    unsigned int           reserved_2                     ; /* 0x3130 */
    volatile U_SYNC_POLAR          SYNC_POLAR          ; /* 3134 */
    volatile U_EXTRA_MODE_EN       EXTRA_MODE_EN       ; /* 3138 */
    unsigned int           reserved_3                     ; /* 0x313c */
    volatile U_SBC_INT_STATUS      SBC_INT_STATUS      ; /* 3140 */
    volatile U_VBLANK1_LINES       VBLANK1_LINES       ; /* 3144 */
    volatile U_LINE_START_HSYNC_EN LINE_START_HSYNC_EN ; /* 3148 */
    unsigned int           reserved_4                     ; /* 0x314c */
    volatile U_EXTRA_NO_GAP_FLAG   EXTRA_NO_GAP_FLAG   ; /* 3150 */
    unsigned int           reserved_5[43]                     ; /* 0x3154~0x31fc */
    volatile U_LM_IN_AC0_CMD       LM_IN_AC0_CMD       ; /* 3200 */
    volatile U_LM_CODE_RFD         LM_CODE_RFD         ; /* 3204 */
    volatile U_LM_IN_AC0_RDATA     LM_IN_AC0_RDATA     ; /* 3208 */
    volatile U_LM_IN_AC0_WDATA     LM_IN_AC0_WDATA     ; /* 320C */
    volatile U_LM_SRC_EN           LM_SRC_EN           ; /* 3210 */
    volatile U_LM_SRC_INIT0        LM_SRC_INIT0        ; /* 3214 */
    volatile U_LM_SRC_INIT1        LM_SRC_INIT1        ; /* 3218 */
    volatile U_LM_COMMAND_EN       LM_COMMAND_EN       ; /* 321C */
    unsigned int           reserved_6[56]                     ; /* 0x3220~0x32fc */
    volatile U_RS_SPLIT_SB_CNT     RS_SPLIT_SB_CNT     ; /* 3300 */
    unsigned int           reserved_7[63]                     ; /* 0x3304~0x33fc */
    volatile U_FLT_START           FLT_START           ; /* 3400 */
    volatile U_FLT_STOP            FLT_STOP            ; /* 3404 */
    volatile U_SCDCS_CONFIG        SCDCS_CONFIG        ; /* 3408 */
    volatile U_CPU_CFG_SEL         CPU_CFG_SEL         ; /* 340C */
    unsigned int           reserved_8                     ; /* 0x3410 */
    volatile U_UPDATE_FLAG_TIMER   UPDATE_FLAG_TIMER   ; /* 3414 */
    volatile U_FLT_STEP_TIMER      FLT_STEP_TIMER      ; /* 3418 */
    volatile U_FLT_TIMEOUT_TIMER   FLT_TIMEOUT_TIMER   ; /* 341C */
    volatile U_CPU_SET_PATTERN     CPU_SET_PATTERN     ; /* 3420 */
    volatile U_CPU_SET_RES         CPU_SET_RES         ; /* 3424 */
    unsigned int           reserved_9[2]                     ; /* 0x3428~0x342c */
    volatile U_FLT_FSM_STATUS      FLT_FSM_STATUS      ; /* 3430 */
    volatile U_FLT_LTP             FLT_LTP             ; /* 3434 */
    volatile U_FRL_MODE_ACT        FRL_MODE_ACT        ; /* 3438 */
    volatile U_FLT_RESULT          FLT_RESULT          ; /* 343C */

} S_tx_frl_reg_REGS_TYPE;

/* Declare the struct pointor of the module tx_frl_reg */
extern volatile S_tx_frl_reg_REGS_TYPE *goptx_frl_regAllReg;

/* Declare the functions that set the member value */


HI_S32 HDMI_HDMITX_FRL_reg_Init(HI_CHAR *pcAddr);
HI_S32 HDMI_HDMITX_FRL_reg_DeInit(HI_VOID);


int HDMI_TX_FRL_VERSION_frl_tx_hw_dayGet(HI_VOID);
int HDMI_TX_FRL_VERSION_frl_tx_hw_monthGet(HI_VOID);
int HDMI_TX_FRL_VERSION_frl_tx_hw_yearGet(HI_VOID);

int HDMI_WORK_EN_work_enSet(unsigned int uwork_en);
int HDMI_WORK_EN_work_enGet(HI_VOID);

int HDMI_AV_MAX_LEN_av_max_lenSet(unsigned int uav_max_len);
int HDMI_AV_MAX_LEN_av_max_lenGet(HI_VOID);
int HDMI_AV_GAP_LEN_av_gap_lenSet(unsigned int uav_gap_len);
int HDMI_AV_GAP_LEN_av_gap_lenGet(HI_VOID);
int HDMI_BLK_MAX_LEN_blk_max_lenSet(unsigned int ublk_max_len);
int HDMI_BLK_MAX_LEN_blk_max_lenGet(HI_VOID);
int HDMI_BLK_GAP_LEN_blk_gap_lenSet(unsigned int ublk_gap_len);
int HDMI_BLK_GAP_LEN_blk_gap_lenGet(HI_VOID);
int HDMI_HBLANK_hblankSet(unsigned int uhblank);
int HDMI_HBLANK_hblankGet(HI_VOID);
int HDMI_HACTIVE_hactiveSet(unsigned int uhactive);
int HDMI_HACTIVE_hactiveGet(HI_VOID);
int HDMI_EXTRA_BLANK_MAX_LEN_extra_blank_max_lenSet(unsigned int uextra_blank_max_len);
int HDMI_EXTRA_BLANK_MAX_LEN_extra_blank_max_lenGet(HI_VOID);
int HDMI_EXTRA_BLANK_GAP_LEN_extra_blank_gap_lenSet(unsigned int uextra_blank_gap_len);
int HDMI_EXTRA_BLANK_GAP_LEN_extra_blank_gap_lenGet(HI_VOID);

int HDMI_VACTIVE_vactiveSet(unsigned int uvactive);
int HDMI_VACTIVE_vactiveGet(HI_VOID);

int HDMI_SYNC_POLAR_vsync_polarSet(unsigned int uvsync_polar);
int HDMI_SYNC_POLAR_vsync_polarGet(HI_VOID);
int HDMI_SYNC_POLAR_vsync_polar_enSet(unsigned int uvsync_polar_en);
int HDMI_SYNC_POLAR_vsync_polar_enGet(HI_VOID);
int HDMI_SYNC_POLAR_hsync_polarSet(unsigned int uhsync_polar);
int HDMI_SYNC_POLAR_hsync_polarGet(HI_VOID);
int HDMI_SYNC_POLAR_hsync_polar_enSet(unsigned int uhsync_polar_en);
int HDMI_SYNC_POLAR_hsync_polar_enGet(HI_VOID);

int HDMI_EXTRA_MODE_EN_extra_mode_enSet(unsigned int uextra_mode_en);
int HDMI_EXTRA_MODE_EN_extra_mode_enGet(HI_VOID);

int HDMI_VBLANK1_LINES_vblank1_linesSet(unsigned int uvblank1_lines);
int HDMI_VBLANK1_LINES_vblank1_linesGet(HI_VOID);
int HDMI_LINE_START_HSYNC_EN_line_start_hsync_enSet(unsigned int uline_start_hsync_en);
int HDMI_LINE_START_HSYNC_EN_line_start_hsync_enGet(HI_VOID);
int HDMI_EXTRA_NO_GAP_FLAG_extra_no_gap_flagSet(unsigned int uextra_no_gap_flag);
int HDMI_EXTRA_NO_GAP_FLAG_extra_no_gap_flagGet(HI_VOID);
int HDMI_LM_IN_AC0_CMD_commandSet(unsigned int ucommand);
int HDMI_LM_IN_AC0_CMD_commandGet(HI_VOID);
int HDMI_LM_IN_AC0_CMD_protect_numberSet(unsigned int uprotect_number);
int HDMI_LM_IN_AC0_CMD_protect_numberGet(HI_VOID);
int HDMI_LM_IN_AC0_CMD_in_ac0_numberSet(unsigned int uin_ac0_number);
int HDMI_LM_IN_AC0_CMD_in_ac0_numberGet(HI_VOID);
int HDMI_LM_IN_AC0_CMD_in_ac0_addrSet(unsigned int uin_ac0_addr);
int HDMI_LM_IN_AC0_CMD_in_ac0_addrGet(HI_VOID);

int HDMI_LM_CODE_RFD_code_rfd_init0Set(unsigned int ucode_rfd_init0);
int HDMI_LM_CODE_RFD_code_rfd_init0Get(HI_VOID);
int HDMI_LM_CODE_RFD_code_rfd_init1Set(unsigned int ucode_rfd_init1);
int HDMI_LM_CODE_RFD_code_rfd_init1Get(HI_VOID);
int HDMI_LM_CODE_RFD_code_rfd_init2Set(unsigned int ucode_rfd_init2);
int HDMI_LM_CODE_RFD_code_rfd_init2Get(HI_VOID);
int HDMI_LM_CODE_RFD_code_rfd_init3Set(unsigned int ucode_rfd_init3);
int HDMI_LM_CODE_RFD_code_rfd_init3Get(HI_VOID);
int HDMI_LM_CODE_RFD_trn_ptn_rsv_setSet(unsigned int utrn_ptn_rsv_set);
int HDMI_LM_CODE_RFD_trn_ptn_rsv_setGet(HI_VOID);
int HDMI_LM_CODE_RFD_lm_ptn_rsv_enSet(unsigned int ulm_ptn_rsv_en);
int HDMI_LM_CODE_RFD_lm_ptn_rsv_enGet(HI_VOID);

int HDMI_LM_IN_AC0_RDATA_in_ac0_rdataGet(HI_VOID);
int HDMI_LM_IN_AC0_WDATA_in_ac0_wdataSet(unsigned int uin_ac0_wdata);
int HDMI_LM_IN_AC0_WDATA_in_ac0_wdataGet(HI_VOID);
int HDMI_LM_SRC_EN_scram_enSet(unsigned int uscram_en);
int HDMI_LM_SRC_EN_scram_enGet(HI_VOID);
int HDMI_LM_SRC_EN_ram_config_enSet(unsigned int uram_config_en);
int HDMI_LM_SRC_EN_ram_config_enGet(HI_VOID);
int HDMI_LM_SRC_INIT0_lane0_init_valueSet(unsigned int ulane0_init_value);
int HDMI_LM_SRC_INIT0_lane0_init_valueGet(HI_VOID);
int HDMI_LM_SRC_INIT0_lane1_init_valueSet(unsigned int ulane1_init_value);
int HDMI_LM_SRC_INIT0_lane1_init_valueGet(HI_VOID);
int HDMI_LM_SRC_INIT1_lane2_init_valueSet(unsigned int ulane2_init_value);
int HDMI_LM_SRC_INIT1_lane2_init_valueGet(HI_VOID);
int HDMI_LM_SRC_INIT1_lane3_init_valueSet(unsigned int ulane3_init_value);
int HDMI_LM_SRC_INIT1_lane3_init_valueGet(HI_VOID);


int HDMI_LM_COMMAND_EN_command_enSet(unsigned int ucommand_en);
int HDMI_LM_COMMAND_EN_command_enGet(HI_VOID);

int HDMI_FLT_START_flt_startSet(unsigned int uflt_start);
int HDMI_FLT_START_flt_startGet(HI_VOID);
int HDMI_SCDCS_CONFIG_scdcs_config_inSet(unsigned int uscdcs_config_in);
int HDMI_SCDCS_CONFIG_scdcs_config_inGet(HI_VOID);

int HDMI_UPDATE_FLAG_TIMER_update_flag_timerSet(unsigned int uupdate_flag_timer);
int HDMI_UPDATE_FLAG_TIMER_update_flag_timerGet(HI_VOID);
int HDMI_FLT_STEP_TIMER_step_timeout_timerSet(unsigned int ustep_timeout_timer);
int HDMI_FLT_STEP_TIMER_step_timeout_timerGet(HI_VOID);
int HDMI_FLT_TIMEOUT_TIMER_flt_timeout_timerSet(unsigned int uflt_timeout_timer);
int HDMI_FLT_TIMEOUT_TIMER_flt_timeout_timerGet(HI_VOID);

int HDMI_CPU_SET_RES_soft_train_okSet(unsigned int usoft_train_ok);
int HDMI_CPU_SET_RES_soft_train_okGet(HI_VOID);

int HDMI_FLT_FSM_STATUS_flt_fsm_currGet(HI_VOID);
int HDMI_FLT_FSM_STATUS_work_lane_numGet(HI_VOID);
int HDMI_FLT_FSM_STATUS_work_channelGet(HI_VOID);
int HDMI_FLT_FSM_STATUS_ddc_in_progGet(HI_VOID);

int HDMI_FLT_LTP_ltp_patternGet(HI_VOID);
int HDMI_FRL_MODE_ACT_frl_mode_actGet(HI_VOID);

int HDMI_FLT_RESULT_train_successGet(HI_VOID);
int HDMI_FLT_RESULT_train_failGet(HI_VOID);
int HDMI_FLT_RESULT_train_busyGet(HI_VOID);
int HDMI_FLT_RESULT_sink_ffe_reqGet(HI_VOID);
int HDMI_FLT_RESULT_train_fail_resGet(HI_VOID);
int HDMI_FLT_RESULT_flt_cntGet(HI_VOID);
int HDMI_FLT_RESULT_frl_work_modeGet(HI_VOID);

int HDMI_CPU_SET_PATTERN_lane0_train_ptnSet(unsigned int ulane0_train_ptn_set);
int HDMI_CPU_SET_PATTERN_lane1_train_ptnSet(unsigned int ulane1_train_ptn_set);
int HDMI_CPU_SET_PATTERN_lane2_train_ptnSet(unsigned int ulane2_train_ptn_set);
int HDMI_CPU_SET_PATTERN_lane3_train_ptnSet(unsigned int ulane3_train_ptn_set);
int HDMI_CPU_CFG_SEL_flt_no_timeoutSet(unsigned int uflt_no_timeout);

int HDMI_CPU_SET_RES_software_train_setSet(unsigned int usoftware_train_set);
int HDMI_CPU_SET_RES_flt_skipSet(unsigned int uflt_skip);
int HDMI_CPU_SET_RES_frl_lane_sel_setSet(unsigned int ufrl_lane_sel_set);
int HDMI_CPU_SET_RES_soft_train_rateSet(unsigned int usoft_train_rate);

#endif // __TX_FRL_REG_C_UNION_DEFINE_H__
