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

#ifndef __TX_AON_REG_C_UNION_DEFINE_H__
#define __TX_AON_REG_C_UNION_DEFINE_H__

/* Define the union U_TX_HW_INFO */
/* Define the union U_TX_HW_INFO,ATTR:,ADDR:4000,INIT:07DF0912,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tx_hw_day   : 8  ; /* [7:0] */
        unsigned int    tx_hw_month : 8  ; /* [15:8] */
        unsigned int    tx_hw_year  : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_HW_INFO;

/* Define the union U_TX_HW_VERSION */
/* Define the union U_TX_HW_VERSION,ATTR:,ADDR:4004,INIT:00101010,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tx_reg_version : 8  ; /* [7:0] */
        unsigned int    tx_drv_version : 8  ; /* [15:8] */
        unsigned int    tx_rtl_version : 8  ; /* [23:16] */
        unsigned int    rsv_0          : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_HW_VERSION;

/* Define the union U_TX_HW_FEATURE */
/* Define the union U_TX_HW_FEATURE,ATTR:,ADDR:4008,INIT:00000000,MASK:0*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rsv_1 : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_HW_FEATURE;

/* Define the union U_TX_AON_RST_CTRL */
/* Define the union U_TX_AON_RST_CTRL,ATTR:,ADDR:401C,INIT:00000000,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tx_aon_soft_arst_req : 1  ; /* [0] */
        unsigned int    rsv_2                : 31  ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_AON_RST_CTRL;

/* Define the union U_HOTPLUG_ST_CFG */
/* Define the union U_HOTPLUG_ST_CFG,ATTR:,ADDR:4020,INIT:00007CF1,MASK:ffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpd_fillter_en   : 1  ; /* [0] */
        unsigned int    hpd_override_en  : 1  ; /* [1] */
        unsigned int    hpd_polarity_ctl : 1  ; /* [2] */
        unsigned int    hpd_soft_value   : 1  ; /* [3] */
        unsigned int    osc_div_cnt      : 12  ; /* [15:4] */
        unsigned int    rsv_3            : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HOTPLUG_ST_CFG;

/* Define the union U_HOTPLUG_FILLTER_CFG */
/* Define the union U_HOTPLUG_FILLTER_CFG,ATTR:,ADDR:4024,INIT:00090063,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpd_high_reshold : 16  ; /* [15:0] */
        unsigned int    hpd_low_reshold  : 16  ; /* [31:16] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HOTPLUG_FILLTER_CFG;

/* Define the union U_TX_AON_STATE */
/* Define the union U_TX_AON_STATE,ATTR:,ADDR:4028,INIT:00000000,MASK:3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hotplug_state : 1  ; /* [0] */
        unsigned int    phy_rx_sense  : 1  ; /* [1] */
        unsigned int    rsv_4         : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_AON_STATE;

/* Define the union U_TX_AON_INTR_MASK */
/* Define the union U_TX_AON_INTR_MASK,ATTR:,ADDR:4030,INIT:00000000,MASK:3ff3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aon_intr_mask0  : 1  ; /* [0] */
        unsigned int    aon_intr_mask1  : 1  ; /* [1] */
        unsigned int    rsv_5           : 1  ; /* [2] */
        unsigned int    rsv_6           : 1  ; /* [3] */
        unsigned int    aon_intr_mask4  : 1  ; /* [4] */
        unsigned int    aon_intr_mask5  : 1  ; /* [5] */
        unsigned int    aon_intr_mask6  : 1  ; /* [6] */
        unsigned int    aon_intr_mask7  : 1  ; /* [7] */
        unsigned int    aon_intr_mask8  : 1  ; /* [8] */
        unsigned int    aon_intr_mask9  : 1  ; /* [9] */
        unsigned int    aon_intr_mask10 : 1  ; /* [10] */
        unsigned int    aon_intr_mask11 : 1  ; /* [11] */
        unsigned int    aon_intr_mask12 : 1  ; /* [12] */
        unsigned int    aon_intr_mask13 : 1  ; /* [13] */
        unsigned int    rsv_7           : 18  ; /* [31:14] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_AON_INTR_MASK;

/* Define the union U_TX_AON_INTR_STATE */
/* Define the union U_TX_AON_INTR_STATE,ATTR:,ADDR:4034,INIT:00000000,MASK:3ff3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aon_intr_stat0  : 1  ; /* [0] */
        unsigned int    aon_intr_stat1  : 1  ; /* [1] */
        unsigned int    rsv_8           : 1  ; /* [2] */
        unsigned int    rsv_9           : 1  ; /* [3] */
        unsigned int    aon_intr_stat4  : 1  ; /* [4] */
        unsigned int    aon_intr_stat5  : 1  ; /* [5] */
        unsigned int    aon_intr_stat6  : 1  ; /* [6] */
        unsigned int    aon_intr_stat7  : 1  ; /* [7] */
        unsigned int    aon_intr_stat8  : 1  ; /* [8] */
        unsigned int    aon_intr_stat9  : 1  ; /* [9] */
        unsigned int    aon_intr_stat10 : 1  ; /* [10] */
        unsigned int    aon_intr_stat11 : 1  ; /* [11] */
        unsigned int    aon_intr_stat12 : 1  ; /* [12] */
        unsigned int    aon_intr_stat13 : 1  ; /* [13] */
        unsigned int    rsv_10          : 18  ; /* [31:14] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TX_AON_INTR_STATE;

/* Define the union U_DDC_MST_CTRL */
/* Define the union U_DDC_MST_CTRL,ATTR:,ADDR:4040,INIT:000004A0,MASK:1ff3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_aon_access : 1  ; /* [0] */
        unsigned int    dcc_man_en     : 1  ; /* [1] */
        unsigned int    rsv_11         : 2  ; /* [3:2] */
        unsigned int    ddc_speed_cnt  : 9  ; /* [12:4] */
        unsigned int    rsv_12         : 19  ; /* [31:13] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_MST_CTRL;

/* Define the union U_DDC_FIFO_RDATA */
/* Define the union U_DDC_FIFO_RDATA,ATTR:,ADDR:4044,INIT:00000000,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_fifo_data_out : 8  ; /* [7:0] */
        unsigned int    rsv_13            : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_FIFO_RDATA;

/* Define the union U_DDC_FIFO_WDATA */
/* Define the union U_DDC_FIFO_WDATA,ATTR:,ADDR:4048,INIT:00000000,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_fifo_data_in : 8  ; /* [7:0] */
        unsigned int    rsv_14           : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_FIFO_WDATA;

/* Define the union U_DDC_DATA_CNT */
/* Define the union U_DDC_DATA_CNT,ATTR:,ADDR:404C,INIT:00000000,MASK:3ff1f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_fifo_data_cnt : 5  ; /* [4:0] */
        unsigned int    rsv_15            : 3  ; /* [7:5] */
        unsigned int    ddc_data_out_cnt  : 10  ; /* [17:8] */
        unsigned int    rsv_16            : 14  ; /* [31:18] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_DATA_CNT;

/* Define the union U_DDC_SLAVE_CFG */
/* Define the union U_DDC_SLAVE_CFG,ATTR:,ADDR:4050,INIT:00000000,MASK:ffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_slave_addr   : 8  ; /* [7:0] */
        unsigned int    ddc_slave_offset : 8  ; /* [15:8] */
        unsigned int    ddc_slave_seg    : 8  ; /* [23:16] */
        unsigned int    rsv_17           : 8  ; /* [31:24] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_SLAVE_CFG;

/* Define the union U_DDC_MST_STATE */
/* Define the union U_DDC_MST_STATE,ATTR:,ADDR:4054,INIT:00000020,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_i2c_no_ack     : 1  ; /* [0] */
        unsigned int    ddc_i2c_bus_low    : 1  ; /* [1] */
        unsigned int    ddc_i2c_in_prog    : 1  ; /* [2] */
        unsigned int    ddc_fifo_wr_in_use : 1  ; /* [3] */
        unsigned int    ddc_fifo_rd_in_use : 1  ; /* [4] */
        unsigned int    ddc_fifo_empty     : 1  ; /* [5] */
        unsigned int    ddc_fifo_half_full : 1  ; /* [6] */
        unsigned int    ddc_fifo_full      : 1  ; /* [7] */
        unsigned int    rsv_18             : 24  ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_MST_STATE;

/* Define the union U_DDC_MST_CMD */
/* Define the union U_DDC_MST_CMD,ATTR:,ADDR:4058,INIT:00000000,MASK:f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_mst_cmd : 4  ; /* [3:0] */
        unsigned int    rsv_19      : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_MST_CMD;

/* Define the union U_DDC_MAN_CTRL */
/* Define the union U_DDC_MAN_CTRL,ATTR:,ADDR:405C,INIT:0000000C,MASK:f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_scl_st  : 1  ; /* [0] */
        unsigned int    ddc_sda_st  : 1  ; /* [1] */
        unsigned int    ddc_scl_oen : 1  ; /* [2] */
        unsigned int    ddc_sda_oen : 1  ; /* [3] */
        unsigned int    rsv_20      : 28  ; /* [31:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_MAN_CTRL;

/* Define the union U_DDC_STATE_CLR */
/* Define the union U_DDC_STATE_CLR,ATTR:,ADDR:4060,INIT:00000000,MASK:3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddc_clr_bus_low : 1  ; /* [0] */
        unsigned int    ddc_clr_no_ack  : 1  ; /* [1] */
        unsigned int    rsv_21          : 30  ; /* [31:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDC_STATE_CLR;


//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_TX_HW_INFO          TX_HW_INFO          ; /* 4000 */
    volatile U_TX_HW_VERSION       TX_HW_VERSION       ; /* 4004 */
    volatile U_TX_HW_FEATURE       TX_HW_FEATURE       ; /* 4008 */
	unsigned int                             Reserved_0[4];	  /* 400C-4018*/
    volatile U_TX_AON_RST_CTRL     TX_AON_RST_CTRL     ; /* 401C */
    volatile U_HOTPLUG_ST_CFG      HOTPLUG_ST_CFG      ; /* 4020 */
    volatile U_HOTPLUG_FILLTER_CFG HOTPLUG_FILLTER_CFG ; /* 4024 */
    volatile U_TX_AON_STATE        TX_AON_STATE        ; /* 4028 */
	unsigned int                             Reserved_2[1];	  /* 402C*/
    volatile U_TX_AON_INTR_MASK    TX_AON_INTR_MASK    ; /* 4030 */
    volatile U_TX_AON_INTR_STATE   TX_AON_INTR_STATE   ; /* 4034 */
	unsigned int                             Reserved_3[2];	  /* 4038-403C*/
    volatile U_DDC_MST_CTRL        DDC_MST_CTRL        ; /* 4040 */
    volatile U_DDC_FIFO_RDATA      DDC_FIFO_RDATA      ; /* 4044 */
    volatile U_DDC_FIFO_WDATA      DDC_FIFO_WDATA      ; /* 4048 */
    volatile U_DDC_DATA_CNT        DDC_DATA_CNT        ; /* 404C */
    volatile U_DDC_SLAVE_CFG       DDC_SLAVE_CFG       ; /* 4050 */
    volatile U_DDC_MST_STATE       DDC_MST_STATE       ; /* 4054 */
    volatile U_DDC_MST_CMD         DDC_MST_CMD         ; /* 4058 */
    volatile U_DDC_MAN_CTRL        DDC_MAN_CTRL        ; /* 405C */
    volatile U_DDC_STATE_CLR       DDC_STATE_CLR       ; /* 4060 */

} S_tx_aon_reg_REGS_TYPE;

/* Declare the struct pointor of the module tx_aon_reg */
//extern volatile S_tx_aon_reg_REGS_TYPE *goptx_aon_regAllReg;

int HDMI_TX_S_tx_aon_reg_REGS_TYPE_Init(char *pcAddr);
int HDMI_TX_S_tx_aon_reg_REGS_TYPE_DeInit(void);

int HDMI_TX_AON_INTR_MASK_aon_intr_mask0Set(unsigned int uaon_intr_mask0);
#ifdef HDMI_CEC_SUPPORT
int HDMI_TX_AON_INTR_MASK_aon_intr_mask4Set(unsigned int uaon_intr_mask4);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask5Set(unsigned int uaon_intr_mask5);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask6Set(unsigned int uaon_intr_mask6);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask7Set(unsigned int uaon_intr_mask7);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask8Set(unsigned int uaon_intr_mask8);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask9Set(unsigned int uaon_intr_mask9);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask10Set(unsigned int uaon_intr_mask10);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask11Set(unsigned int uaon_intr_mask11);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask12Set(unsigned int uaon_intr_mask12);
int HDMI_TX_AON_INTR_MASK_aon_intr_mask13Set(unsigned int uaon_intr_mask13);
#endif

int HDMI_TX_AON_INTR_STATE_aon_intr_stat0Set(unsigned int uaon_intr_stat0);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat1Set(unsigned int uaon_intr_stat1);
#ifdef HDMI_CEC_SUPPORT
int HDMI_TX_AON_INTR_STATE_aon_intr_stat4Set(unsigned int uaon_intr_stat4);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat5Set(unsigned int uaon_intr_stat5);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat6Set(unsigned int uaon_intr_stat6);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat7Set(unsigned int uaon_intr_stat7);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat8Set(unsigned int uaon_intr_stat8);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat9Set(unsigned int uaon_intr_stat9);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat10Set(unsigned int uaon_intr_stat10);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set(unsigned int uaon_intr_stat11);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat12Set(unsigned int uaon_intr_stat12);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat13Set(unsigned int uaon_intr_stat13);
#endif

int HDMI_DDC_MST_CTRL_dcc_man_enSet(unsigned int udcc_man_en);
int HDMI_DDC_MAN_CTRL_ddc_scl_oenSet(unsigned int uddc_scl_oen);
int HDMI_DDC_MAN_CTRL_ddc_sda_oenSet(unsigned int uddc_sda_oen);

int HDMI_DDC_MST_STATE_ddc_i2c_bus_lowGet(void);
int HDMI_DDC_MST_STATE_ddc_i2c_no_ackGet(void);

int HDMI_HOTPLUG_ST_CFG_hpd_polarity_ctlGet(void);
int HDMI_TX_AON_STATE_hotplug_stateGet(void);
int HDMI_TX_AON_STATE_phy_rx_senseGet(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat0Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat1Get(void);
#ifdef HDMI_CEC_SUPPORT
int HDMI_TX_AON_INTR_STATE_aon_intr_stat4Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat5Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat6Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat7Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat8Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat9Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat11Get(void);
int HDMI_TX_AON_INTR_STATE_aon_intr_stat12Get(void);
#endif

int HDMI_DDC_MAN_CTRL_ddc_scl_stGet(void);
int HDMI_DDC_MAN_CTRL_ddc_sda_stGet(void);

#endif // __TX_AON_REG_C_UNION_DEFINE_H__
