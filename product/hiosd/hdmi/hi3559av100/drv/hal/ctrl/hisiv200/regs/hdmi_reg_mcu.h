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

#ifndef __MCU_CPU_REG_C_UNION_DEFINE_H__
#define __MCU_CPU_REG_C_UNION_DEFINE_H__

/* Define the union U_HDCP2X_HW_VER_B0 */
/* Define the union U_HDCP2X_HW_VER_B0,ATTR:,ADDR:1C000,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_hw_ver_b0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_HW_VER_B0;

/* Define the union U_HDCP2X_HW_VER_B1 */
/* Define the union U_HDCP2X_HW_VER_B1,ATTR:,ADDR:1C004,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_hw_ver_b1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_HW_VER_B1;

/* Define the union U_HDCP2X_HW_VER_B2 */
/* Define the union U_HDCP2X_HW_VER_B2,ATTR:,ADDR:1C008,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_hw_ver_b2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_HW_VER_B2;

/* Define the union U_HDCP2X_HW_VER_B3 */
/* Define the union U_HDCP2X_HW_VER_B3,ATTR:,ADDR:1C00C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_hw_ver_b3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_HW_VER_B3;

/* Define the union U_HDCP2X_SW_VER_B0 */
/* Define the union U_HDCP2X_SW_VER_B0,ATTR:,ADDR:1C010,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sw_ver_b0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SW_VER_B0;

/* Define the union U_HDCP2X_SW_VER_B1 */
/* Define the union U_HDCP2X_SW_VER_B1,ATTR:,ADDR:1C014,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sw_ver_b1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SW_VER_B1;

/* Define the union U_HDCP2X_SW_VER_B2 */
/* Define the union U_HDCP2X_SW_VER_B2,ATTR:,ADDR:1C018,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sw_ver_b2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SW_VER_B2;

/* Define the union U_HDCP2X_SW_VER_B3 */
/* Define the union U_HDCP2X_SW_VER_B3,ATTR:,ADDR:1C01C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sw_ver_b3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SW_VER_B3;

/* Define the union U_HDCP2X_AUTH_CTRL */
/* Define the union U_HDCP2X_AUTH_CTRL,ATTR:,ADDR:1C054,INIT:00,MASK:3*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mcu_auth_start : 1  ; /* [0] */
        unsigned int    mcu_auth_stop  : 1  ; /* [1] */
        unsigned int    rsv_0          : 6  ; /* [7:2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_AUTH_CTRL;

/* Define the union U_HDCP2X_SEC_INTR_B0 */
/* Define the union U_HDCP2X_SEC_INTR_B0,ATTR:,ADDR:1C080,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_intr0 : 1  ; /* [0] */
        unsigned int    hdcp2x_sec_intr1 : 1  ; /* [1] */
        unsigned int    hdcp2x_sec_intr2 : 1  ; /* [2] */
        unsigned int    hdcp2x_sec_intr3 : 1  ; /* [3] */
        unsigned int    hdcp2x_sec_intr4 : 1  ; /* [4] */
        unsigned int    hdcp2x_sec_intr5 : 1  ; /* [5] */
        unsigned int    hdcp2x_sec_intr6 : 1  ; /* [6] */
        unsigned int    hdcp2x_sec_intr7 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_INTR_B0;

/* Define the union U_HDCP2X_SEC_INTR_B1 */
/* Define the union U_HDCP2X_SEC_INTR_B1,ATTR:,ADDR:1C084,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_intr8  : 1  ; /* [0] */
        unsigned int    hdcp2x_sec_intr9  : 1  ; /* [1] */
        unsigned int    hdcp2x_sec_intr10 : 1  ; /* [2] */
        unsigned int    hdcp2x_sec_intr11 : 1  ; /* [3] */
        unsigned int    hdcp2x_sec_intr12 : 1  ; /* [4] */
        unsigned int    hdcp2x_sec_intr13 : 1  ; /* [5] */
        unsigned int    hdcp2x_sec_intr14 : 1  ; /* [6] */
        unsigned int    hdcp2x_sec_intr15 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_INTR_B1;

/* Define the union U_HDCP2X_SEC_MASK_B0 */
/* Define the union U_HDCP2X_SEC_MASK_B0,ATTR:,ADDR:1C088,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_mask0 : 1  ; /* [0] */
        unsigned int    hdcp2x_sec_mask1 : 1  ; /* [1] */
        unsigned int    hdcp2x_sec_mask2 : 1  ; /* [2] */
        unsigned int    hdcp2x_sec_mask3 : 1  ; /* [3] */
        unsigned int    hdcp2x_sec_mask4 : 1  ; /* [4] */
        unsigned int    hdcp2x_sec_mask5 : 1  ; /* [5] */
        unsigned int    hdcp2x_sec_mask6 : 1  ; /* [6] */
        unsigned int    hdcp2x_sec_mask7 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_MASK_B0;

/* Define the union U_HDCP2X_SEC_MASK_B1 */
/* Define the union U_HDCP2X_SEC_MASK_B1,ATTR:,ADDR:1C08C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_mask8  : 1  ; /* [0] */
        unsigned int    hdcp2x_sec_mask9  : 1  ; /* [1] */
        unsigned int    hdcp2x_sec_mask10 : 1  ; /* [2] */
        unsigned int    hdcp2x_sec_mask11 : 1  ; /* [3] */
        unsigned int    hdcp2x_sec_mask12 : 1  ; /* [4] */
        unsigned int    hdcp2x_sec_mask13 : 1  ; /* [5] */
        unsigned int    hdcp2x_sec_mask14 : 1  ; /* [6] */
        unsigned int    hdcp2x_sec_mask15 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_MASK_B1;

/* Define the union U_HDCP2X_MCU_INTR_B0 */
/* Define the union U_HDCP2X_MCU_INTR_B0,ATTR:,ADDR:1C0A4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_intr0 : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_intr1 : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_intr2 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_intr3 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_intr4 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_intr5 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_intr6 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_intr7 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_INTR_B0;

/* Define the union U_HDCP2X_MCU_INTR_B1 */
/* Define the union U_HDCP2X_MCU_INTR_B1,ATTR:,ADDR:1C0A8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_intr8  : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_intr9  : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_intr10 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_intr11 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_intr12 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_intr13 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_intr14 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_intr15 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_INTR_B1;

/* Define the union U_HDCP2X_MCU_INTR_B2 */
/* Define the union U_HDCP2X_MCU_INTR_B2,ATTR:,ADDR:1C0AC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_intr16 : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_intr17 : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_intr18 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_intr19 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_intr20 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_intr21 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_intr22 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_intr23 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_INTR_B2;

/* Define the union U_HDCP2X_MCU_INTR_B3 */
/* Define the union U_HDCP2X_MCU_INTR_B3,ATTR:,ADDR:1C0B0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_intr24 : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_intr25 : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_intr26 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_intr27 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_intr28 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_intr29 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_intr30 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_intr31 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_INTR_B3;

/* Define the union U_HDCP2X_MCU_MASK_B0 */
/* Define the union U_HDCP2X_MCU_MASK_B0,ATTR:,ADDR:1C0B4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_mask0 : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_mask1 : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_mask2 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_mask3 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_mask4 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_mask5 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_mask6 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_mask7 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_MASK_B0;

/* Define the union U_HDCP2X_MCU_MASK_B1 */
/* Define the union U_HDCP2X_MCU_MASK_B1,ATTR:,ADDR:1C0B8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_mask8  : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_mask9  : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_mask10 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_mask11 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_mask12 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_mask13 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_mask14 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_mask15 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_MASK_B1;

/* Define the union U_HDCP2X_MCU_MASK_B2 */
/* Define the union U_HDCP2X_MCU_MASK_B2,ATTR:,ADDR:1C0BC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_mask16 : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_mask17 : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_mask18 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_mask19 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_mask20 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_mask21 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_mask22 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_mask23 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_MASK_B2;

/* Define the union U_HDCP2X_MCU_MASK_B3 */
/* Define the union U_HDCP2X_MCU_MASK_B3,ATTR:,ADDR:1C0C0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_mask24 : 1  ; /* [0] */
        unsigned int    hdcp2x_mcu_mask25 : 1  ; /* [1] */
        unsigned int    hdcp2x_mcu_mask26 : 1  ; /* [2] */
        unsigned int    hdcp2x_mcu_mask27 : 1  ; /* [3] */
        unsigned int    hdcp2x_mcu_mask28 : 1  ; /* [4] */
        unsigned int    hdcp2x_mcu_mask29 : 1  ; /* [5] */
        unsigned int    hdcp2x_mcu_mask30 : 1  ; /* [6] */
        unsigned int    hdcp2x_mcu_mask31 : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_MASK_B3;

/* Define the union U_HDCP2X_MCU_STATE_B0 */
/* Define the union U_HDCP2X_MCU_STATE_B0,ATTR:,ADDR:1C0CC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_state_b0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_STATE_B0;

/* Define the union U_HDCP2X_MCU_STATE_B1 */
/* Define the union U_HDCP2X_MCU_STATE_B1,ATTR:,ADDR:1C0D0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_state_b1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_STATE_B1;

/* Define the union U_HDCP2X_MCU_STATE_B2 */
/* Define the union U_HDCP2X_MCU_STATE_B2,ATTR:,ADDR:1C0D4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_state_b2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_STATE_B2;

/* Define the union U_HDCP2X_MCU_STATE_B3 */
/* Define the union U_HDCP2X_MCU_STATE_B3,ATTR:,ADDR:1C0D8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_mcu_state_b3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_MCU_STATE_B3;

/* Define the union U_HDCP2X_RX_AUTH_STATE */
/* Define the union U_HDCP2X_RX_AUTH_STATE,ATTR:,ADDR:1C0E8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_ake_init_done  : 1  ; /* [0] */
        unsigned int    hdcp2x_send_cert_done : 1  ; /* [1] */
        unsigned int    hdcp2x_km_done        : 1  ; /* [2] */
        unsigned int    hdcp2x_send_h_done    : 1  ; /* [3] */
        unsigned int    hdcp2x_pairing_done   : 1  ; /* [4] */
        unsigned int    hdcp2x_lc_init_done   : 1  ; /* [5] */
        unsigned int    hdcp2x_send_l_done    : 1  ; /* [6] */
        unsigned int    hdcp2x_send_sks_done  : 1  ; /* [7] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RX_AUTH_STATE;

/* Define the union U_HDCP2X_RPT_AUTH_STATE */
/* Define the union U_HDCP2X_RPT_AUTH_STATE,ATTR:,ADDR:1C0EC,INIT:00,MASK:f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_id_list_done  : 1  ; /* [0] */
        unsigned int    hdcp2x_send_ack_done : 1  ; /* [1] */
        unsigned int    hdcp2x_strm_id_done  : 1  ; /* [2] */
        unsigned int    hdcp2x_strm_rdy_done : 1  ; /* [3] */
        unsigned int    rsv_1                : 4  ; /* [7:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_AUTH_STATE;

/* Define the union U_HDCP2X_AUTH_STATE0 */
/* Define the union U_HDCP2X_AUTH_STATE0,ATTR:,ADDR:1C0F0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_auth_state0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_AUTH_STATE0;

/* Define the union U_HDCP2X_AUTH_STATE1 */
/* Define the union U_HDCP2X_AUTH_STATE1,ATTR:,ADDR:1C0F4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_auth_state1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_AUTH_STATE1;

/* Define the union U_HDCP2X_AUTH_STATE2 */
/* Define the union U_HDCP2X_AUTH_STATE2,ATTR:,ADDR:1C0F8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_auth_state2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_AUTH_STATE2;

/* Define the union U_HDCP2X_AUTH_STATE3 */
/* Define the union U_HDCP2X_AUTH_STATE3,ATTR:,ADDR:1C0FC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_auth_state3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_AUTH_STATE3;

/* Define the union U_HDCP2X_CERT_INFO */
/* Define the union U_HDCP2X_CERT_INFO,ATTR:,ADDR:1C114,INIT:00,MASK:1*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_cert_rpt : 1  ; /* [0] */
        unsigned int    rsv_2           : 7  ; /* [7:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_CERT_INFO;

/* Define the union U_HDCP2X_CERT_VER */
/* Define the union U_HDCP2X_CERT_VER,ATTR:,ADDR:1C118,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_cert_ver : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_CERT_VER;

/* Define the union U_HDCP2X_RPT_INFO */
/* Define the union U_HDCP2X_RPT_INFO,ATTR:,ADDR:1C11C,INIT:00,MASK:f*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp1x_dev_on      : 1  ; /* [0] */
        unsigned int    hdcp20_rpt_on      : 1  ; /* [1] */
        unsigned int    hdcp2x_rpt_cas_exc : 1  ; /* [2] */
        unsigned int    hdcp2x_rpt_dev_exc : 1  ; /* [3] */
        unsigned int    rsv_3              : 4  ; /* [7:4] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_INFO;

/* Define the union U_HDCP2X_RPT_DEV */
/* Define the union U_HDCP2X_RPT_DEV,ATTR:,ADDR:1C120,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_dev_cnt : 5  ; /* [4:0] */
        unsigned int    hdcp2x_rpt_dep_cnt : 3  ; /* [7:5] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_DEV;

/* Define the union U_HDCP2X_RPT_V0 */
/* Define the union U_HDCP2X_RPT_V0,ATTR:,ADDR:1C124,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_v0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_V0;

/* Define the union U_HDCP2X_RPT_V1 */
/* Define the union U_HDCP2X_RPT_V1,ATTR:,ADDR:1C128,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_v1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_V1;

/* Define the union U_HDCP2X_RPT_V2 */
/* Define the union U_HDCP2X_RPT_V2,ATTR:,ADDR:1C12C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_v2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_V2;

/* Define the union U_HDCP2X_RPT_K0 */
/* Define the union U_HDCP2X_RPT_K0,ATTR:,ADDR:1C130,INIT:01,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_k0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_K0;

/* Define the union U_HDCP2X_RPT_K1 */
/* Define the union U_HDCP2X_RPT_K1,ATTR:,ADDR:1C134,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_k1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_K1;

/* Define the union U_HDCP2X_RPT_M0 */
/* Define the union U_HDCP2X_RPT_M0,ATTR:,ADDR:1C138,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_m0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_M0;

/* Define the union U_HDCP2X_RPT_M1 */
/* Define the union U_HDCP2X_RPT_M1,ATTR:,ADDR:1C13C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_m1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_M1;

/* Define the union U_HDCP2X_RPT_M2 */
/* Define the union U_HDCP2X_RPT_M2,ATTR:,ADDR:1C140,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_m2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_M2;

/* Define the union U_HDCP2X_RPT_STRM_ID */
/* Define the union U_HDCP2X_RPT_STRM_ID,ATTR:,ADDR:1C144,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_strm_id : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_STRM_ID;

/* Define the union U_HDCP2X_RPT_STRM_TPYE */
/* Define the union U_HDCP2X_RPT_STRM_TPYE,ATTR:,ADDR:1C148,INIT:01,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_rpt_strm_type : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_RPT_STRM_TPYE;

/* Define the union U_HDCP2X_TIMING_CFG0 */
/* Define the union U_HDCP2X_TIMING_CFG0,ATTR:,ADDR:1C1A4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG0;

/* Define the union U_HDCP2X_TIMING_CFG1 */
/* Define the union U_HDCP2X_TIMING_CFG1,ATTR:,ADDR:1C1A8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG1;

/* Define the union U_HDCP2X_TIMING_CFG2 */
/* Define the union U_HDCP2X_TIMING_CFG2,ATTR:,ADDR:1C1AC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG2;

/* Define the union U_HDCP2X_TIMING_CFG3 */
/* Define the union U_HDCP2X_TIMING_CFG3,ATTR:,ADDR:1C1B0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG3;

/* Define the union U_HDCP2X_TIMING_CFG4 */
/* Define the union U_HDCP2X_TIMING_CFG4,ATTR:,ADDR:1C1B4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg4 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG4;

/* Define the union U_HDCP2X_TIMING_CFG5 */
/* Define the union U_HDCP2X_TIMING_CFG5,ATTR:,ADDR:1C1B8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg5 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG5;

/* Define the union U_HDCP2X_TIMING_CFG6 */
/* Define the union U_HDCP2X_TIMING_CFG6,ATTR:,ADDR:1C1BC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg6 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG6;

/* Define the union U_HDCP2X_TIMING_CFG7 */
/* Define the union U_HDCP2X_TIMING_CFG7,ATTR:,ADDR:1C1C0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg7 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG7;

/* Define the union U_HDCP2X_TIMING_CFG8 */
/* Define the union U_HDCP2X_TIMING_CFG8,ATTR:,ADDR:1C1C4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg8 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG8;

/* Define the union U_HDCP2X_TIMING_CFG9 */
/* Define the union U_HDCP2X_TIMING_CFG9,ATTR:,ADDR:1C1C8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg9 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG9;

/* Define the union U_HDCP2X_TIMING_CFG10 */
/* Define the union U_HDCP2X_TIMING_CFG10,ATTR:,ADDR:1C1CC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg10 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG10;

/* Define the union U_HDCP2X_TIMING_CFG11 */
/* Define the union U_HDCP2X_TIMING_CFG11,ATTR:,ADDR:1C1D0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg11 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG11;

/* Define the union U_HDCP2X_TIMING_CFG12 */
/* Define the union U_HDCP2X_TIMING_CFG12,ATTR:,ADDR:1C1D4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg12 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG12;

/* Define the union U_HDCP2X_TIMING_CFG13 */
/* Define the union U_HDCP2X_TIMING_CFG13,ATTR:,ADDR:1C1D8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg13 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG13;

/* Define the union U_HDCP2X_TIMING_CFG14 */
/* Define the union U_HDCP2X_TIMING_CFG14,ATTR:,ADDR:1C1DC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg14 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG14;

/* Define the union U_HDCP2X_TIMING_CFG15 */
/* Define the union U_HDCP2X_TIMING_CFG15,ATTR:,ADDR:1C1E0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg15 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG15;

/* Define the union U_HDCP2X_TIMING_CFG16 */
/* Define the union U_HDCP2X_TIMING_CFG16,ATTR:,ADDR:1C1E4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg16 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG16;

/* Define the union U_HDCP2X_TIMING_CFG17 */
/* Define the union U_HDCP2X_TIMING_CFG17,ATTR:,ADDR:1C1E8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg17 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG17;

/* Define the union U_HDCP2X_TIMING_CFG18 */
/* Define the union U_HDCP2X_TIMING_CFG18,ATTR:,ADDR:1C1EC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg18 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG18;

/* Define the union U_HDCP2X_TIMING_CFG19 */
/* Define the union U_HDCP2X_TIMING_CFG19,ATTR:,ADDR:1C1F0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg19 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG19;

/* Define the union U_HDCP2X_TIMING_CFG20 */
/* Define the union U_HDCP2X_TIMING_CFG20,ATTR:,ADDR:1C1F4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg20 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG20;

/* Define the union U_HDCP2X_TIMING_CFG21 */
/* Define the union U_HDCP2X_TIMING_CFG21,ATTR:,ADDR:1C1F8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg21 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG21;

/* Define the union U_HDCP2X_TIMING_CFG22 */
/* Define the union U_HDCP2X_TIMING_CFG22,ATTR:,ADDR:1C1FC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg22 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG22;

/* Define the union U_HDCP2X_TIMING_CFG23 */
/* Define the union U_HDCP2X_TIMING_CFG23,ATTR:,ADDR:1C200,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg23 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG23;

/* Define the union U_HDCP2X_TIMING_CFG24 */
/* Define the union U_HDCP2X_TIMING_CFG24,ATTR:,ADDR:1C204,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg24 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG24;

/* Define the union U_HDCP2X_TIMING_CFG25 */
/* Define the union U_HDCP2X_TIMING_CFG25,ATTR:,ADDR:1C208,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg25 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG25;

/* Define the union U_HDCP2X_TIMING_CFG26 */
/* Define the union U_HDCP2X_TIMING_CFG26,ATTR:,ADDR:1C20C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg26 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG26;

/* Define the union U_HDCP2X_TIMING_CFG27 */
/* Define the union U_HDCP2X_TIMING_CFG27,ATTR:,ADDR:1C210,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg27 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG27;

/* Define the union U_HDCP2X_TIMING_CFG28 */
/* Define the union U_HDCP2X_TIMING_CFG28,ATTR:,ADDR:1C214,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg28 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG28;

/* Define the union U_HDCP2X_TIMING_CFG29 */
/* Define the union U_HDCP2X_TIMING_CFG29,ATTR:,ADDR:1C218,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg29 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG29;

/* Define the union U_HDCP2X_TIMING_CFG30 */
/* Define the union U_HDCP2X_TIMING_CFG30,ATTR:,ADDR:1C21C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg30 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG30;

/* Define the union U_HDCP2X_TIMING_CFG31 */
/* Define the union U_HDCP2X_TIMING_CFG31,ATTR:,ADDR:1C220,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_timing_cfg31 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_TIMING_CFG31;

/* Define the union U_HDCP2X_GEN_IN0 */
/* Define the union U_HDCP2X_GEN_IN0,ATTR:,ADDR:1C224,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN0;

/* Define the union U_HDCP2X_GEN_IN1 */
/* Define the union U_HDCP2X_GEN_IN1,ATTR:,ADDR:1C228,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN1;

/* Define the union U_HDCP2X_GEN_IN2 */
/* Define the union U_HDCP2X_GEN_IN2,ATTR:,ADDR:1C22C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN2;

/* Define the union U_HDCP2X_GEN_IN3 */
/* Define the union U_HDCP2X_GEN_IN3,ATTR:,ADDR:1C230,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN3;

/* Define the union U_HDCP2X_GEN_IN4 */
/* Define the union U_HDCP2X_GEN_IN4,ATTR:,ADDR:1C234,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in4 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN4;

/* Define the union U_HDCP2X_GEN_IN5 */
/* Define the union U_HDCP2X_GEN_IN5,ATTR:,ADDR:1C238,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in5 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN5;

/* Define the union U_HDCP2X_GEN_IN6 */
/* Define the union U_HDCP2X_GEN_IN6,ATTR:,ADDR:1C23C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in6 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN6;

/* Define the union U_HDCP2X_GEN_IN7 */
/* Define the union U_HDCP2X_GEN_IN7,ATTR:,ADDR:1C240,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in7 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN7;

/* Define the union U_HDCP2X_GEN_IN8 */
/* Define the union U_HDCP2X_GEN_IN8,ATTR:,ADDR:1C244,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in8 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN8;

/* Define the union U_HDCP2X_GEN_IN9 */
/* Define the union U_HDCP2X_GEN_IN9,ATTR:,ADDR:1C248,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in9 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN9;

/* Define the union U_HDCP2X_GEN_IN10 */
/* Define the union U_HDCP2X_GEN_IN10,ATTR:,ADDR:1C24C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in10 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN10;

/* Define the union U_HDCP2X_GEN_IN11 */
/* Define the union U_HDCP2X_GEN_IN11,ATTR:,ADDR:1C250,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in11 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN11;

/* Define the union U_HDCP2X_GEN_IN12 */
/* Define the union U_HDCP2X_GEN_IN12,ATTR:,ADDR:1C254,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in12 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN12;

/* Define the union U_HDCP2X_GEN_IN13 */
/* Define the union U_HDCP2X_GEN_IN13,ATTR:,ADDR:1C258,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in13 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN13;

/* Define the union U_HDCP2X_GEN_IN14 */
/* Define the union U_HDCP2X_GEN_IN14,ATTR:,ADDR:1C25C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in14 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN14;

/* Define the union U_HDCP2X_GEN_IN15 */
/* Define the union U_HDCP2X_GEN_IN15,ATTR:,ADDR:1C260,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in15 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN15;

/* Define the union U_HDCP2X_GEN_IN16 */
/* Define the union U_HDCP2X_GEN_IN16,ATTR:,ADDR:1C264,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in16 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN16;

/* Define the union U_HDCP2X_GEN_IN17 */
/* Define the union U_HDCP2X_GEN_IN17,ATTR:,ADDR:1C268,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in17 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN17;

/* Define the union U_HDCP2X_GEN_IN18 */
/* Define the union U_HDCP2X_GEN_IN18,ATTR:,ADDR:1C26C,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in18 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN18;

/* Define the union U_HDCP2X_GEN_IN19 */
/* Define the union U_HDCP2X_GEN_IN19,ATTR:,ADDR:1C270,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in19 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN19;

/* Define the union U_HDCP2X_GEN_IN20 */
/* Define the union U_HDCP2X_GEN_IN20,ATTR:,ADDR:1C274,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in20 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN20;

/* Define the union U_HDCP2X_GEN_IN21 */
/* Define the union U_HDCP2X_GEN_IN21,ATTR:,ADDR:1C278,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in21 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN21;

/* Define the union U_HDCP2X_GEN_IN22 */
/* Define the union U_HDCP2X_GEN_IN22,ATTR:,ADDR:1C27C,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in22 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN22;

/* Define the union U_HDCP2X_GEN_IN23 */
/* Define the union U_HDCP2X_GEN_IN23,ATTR:,ADDR:1C280,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in23 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN23;

/* Define the union U_HDCP2X_GEN_IN24 */
/* Define the union U_HDCP2X_GEN_IN24,ATTR:,ADDR:1C284,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in24 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN24;

/* Define the union U_HDCP2X_GEN_IN25 */
/* Define the union U_HDCP2X_GEN_IN25,ATTR:,ADDR:1C288,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in25 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN25;

/* Define the union U_HDCP2X_GEN_IN26 */
/* Define the union U_HDCP2X_GEN_IN26,ATTR:,ADDR:1C28C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in26 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN26;

/* Define the union U_HDCP2X_GEN_IN27 */
/* Define the union U_HDCP2X_GEN_IN27,ATTR:,ADDR:1C290,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in27 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN27;

/* Define the union U_HDCP2X_GEN_IN28 */
/* Define the union U_HDCP2X_GEN_IN28,ATTR:,ADDR:1C294,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in28 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN28;

/* Define the union U_HDCP2X_GEN_IN29 */
/* Define the union U_HDCP2X_GEN_IN29,ATTR:,ADDR:1C298,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in29 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN29;

/* Define the union U_HDCP2X_GEN_IN30 */
/* Define the union U_HDCP2X_GEN_IN30,ATTR:,ADDR:1C29C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in30 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN30;

/* Define the union U_HDCP2X_GEN_IN31 */
/* Define the union U_HDCP2X_GEN_IN31,ATTR:,ADDR:1C2A0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_in31 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_IN31;

/* Define the union U_HDCP2X_GEN_OUT0 */
/* Define the union U_HDCP2X_GEN_OUT0,ATTR:,ADDR:1C2A4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT0;

/* Define the union U_HDCP2X_GEN_OUT1 */
/* Define the union U_HDCP2X_GEN_OUT1,ATTR:,ADDR:1C2A8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT1;

/* Define the union U_HDCP2X_GEN_OUT2 */
/* Define the union U_HDCP2X_GEN_OUT2,ATTR:,ADDR:1C2AC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT2;

/* Define the union U_HDCP2X_GEN_OUT3 */
/* Define the union U_HDCP2X_GEN_OUT3,ATTR:,ADDR:1C2B0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT3;

/* Define the union U_HDCP2X_GEN_OUT4 */
/* Define the union U_HDCP2X_GEN_OUT4,ATTR:,ADDR:1C2B4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out4 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT4;

/* Define the union U_HDCP2X_GEN_OUT5 */
/* Define the union U_HDCP2X_GEN_OUT5,ATTR:,ADDR:1C2B8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out5 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT5;

/* Define the union U_HDCP2X_GEN_OUT6 */
/* Define the union U_HDCP2X_GEN_OUT6,ATTR:,ADDR:1C2BC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out6 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT6;

/* Define the union U_HDCP2X_GEN_OUT7 */
/* Define the union U_HDCP2X_GEN_OUT7,ATTR:,ADDR:1C2C0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out7 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT7;

/* Define the union U_HDCP2X_GEN_OUT8 */
/* Define the union U_HDCP2X_GEN_OUT8,ATTR:,ADDR:1C2C4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out8 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT8;

/* Define the union U_HDCP2X_GEN_OUT9 */
/* Define the union U_HDCP2X_GEN_OUT9,ATTR:,ADDR:1C2C8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out9 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT9;

/* Define the union U_HDCP2X_GEN_OUT10 */
/* Define the union U_HDCP2X_GEN_OUT10,ATTR:,ADDR:1C2CC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out10 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT10;

/* Define the union U_HDCP2X_GEN_OUT11 */
/* Define the union U_HDCP2X_GEN_OUT11,ATTR:,ADDR:1C2D0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out11 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT11;

/* Define the union U_HDCP2X_GEN_OUT12 */
/* Define the union U_HDCP2X_GEN_OUT12,ATTR:,ADDR:1C2D4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out12 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT12;

/* Define the union U_HDCP2X_GEN_OUT13 */
/* Define the union U_HDCP2X_GEN_OUT13,ATTR:,ADDR:1C2D8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out13 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT13;

/* Define the union U_HDCP2X_GEN_OUT14 */
/* Define the union U_HDCP2X_GEN_OUT14,ATTR:,ADDR:1C2DC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out14 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT14;

/* Define the union U_HDCP2X_GEN_OUT15 */
/* Define the union U_HDCP2X_GEN_OUT15,ATTR:,ADDR:1C2E0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out15 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT15;

/* Define the union U_HDCP2X_GEN_OUT16 */
/* Define the union U_HDCP2X_GEN_OUT16,ATTR:,ADDR:1C2E4,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out16 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT16;

/* Define the union U_HDCP2X_GEN_OUT17 */
/* Define the union U_HDCP2X_GEN_OUT17,ATTR:,ADDR:1C2E8,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out17 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT17;

/* Define the union U_HDCP2X_GEN_OUT18 */
/* Define the union U_HDCP2X_GEN_OUT18,ATTR:,ADDR:1C2EC,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out18 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT18;

/* Define the union U_HDCP2X_GEN_OUT19 */
/* Define the union U_HDCP2X_GEN_OUT19,ATTR:,ADDR:1C2F0,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out19 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT19;

/* Define the union U_HDCP2X_GEN_OUT20 */
/* Define the union U_HDCP2X_GEN_OUT20,ATTR:,ADDR:1C2F4,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out20 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT20;

/* Define the union U_HDCP2X_GEN_OUT21 */
/* Define the union U_HDCP2X_GEN_OUT21,ATTR:,ADDR:1C2F8,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out21 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT21;

/* Define the union U_HDCP2X_GEN_OUT22 */
/* Define the union U_HDCP2X_GEN_OUT22,ATTR:,ADDR:1C2FC,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out22 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT22;

/* Define the union U_HDCP2X_GEN_OUT23 */
/* Define the union U_HDCP2X_GEN_OUT23,ATTR:,ADDR:1C300,INIT:FF,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out23 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT23;

/* Define the union U_HDCP2X_GEN_OUT24 */
/* Define the union U_HDCP2X_GEN_OUT24,ATTR:,ADDR:1C304,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out24 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT24;

/* Define the union U_HDCP2X_GEN_OUT25 */
/* Define the union U_HDCP2X_GEN_OUT25,ATTR:,ADDR:1C308,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out25 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT25;

/* Define the union U_HDCP2X_GEN_OUT26 */
/* Define the union U_HDCP2X_GEN_OUT26,ATTR:,ADDR:1C30C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out26 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT26;

/* Define the union U_HDCP2X_GEN_OUT27 */
/* Define the union U_HDCP2X_GEN_OUT27,ATTR:,ADDR:1C310,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out27 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT27;

/* Define the union U_HDCP2X_GEN_OUT28 */
/* Define the union U_HDCP2X_GEN_OUT28,ATTR:,ADDR:1C314,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out28 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT28;

/* Define the union U_HDCP2X_GEN_OUT29 */
/* Define the union U_HDCP2X_GEN_OUT29,ATTR:,ADDR:1C318,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out29 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT29;

/* Define the union U_HDCP2X_GEN_OUT30 */
/* Define the union U_HDCP2X_GEN_OUT30,ATTR:,ADDR:1C31C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out30 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT30;

/* Define the union U_HDCP2X_GEN_OUT31 */
/* Define the union U_HDCP2X_GEN_OUT31,ATTR:,ADDR:1C320,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_gen_out31 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_GEN_OUT31;

/* Define the union U_HDCP2X_SEC_IN0 */
/* Define the union U_HDCP2X_SEC_IN0,ATTR:,ADDR:1C380,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN0;

/* Define the union U_HDCP2X_SEC_IN1 */
/* Define the union U_HDCP2X_SEC_IN1,ATTR:,ADDR:1C384,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN1;

/* Define the union U_HDCP2X_SEC_IN2 */
/* Define the union U_HDCP2X_SEC_IN2,ATTR:,ADDR:1C388,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN2;

/* Define the union U_HDCP2X_SEC_IN3 */
/* Define the union U_HDCP2X_SEC_IN3,ATTR:,ADDR:1C38C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN3;

/* Define the union U_HDCP2X_SEC_IN4 */
/* Define the union U_HDCP2X_SEC_IN4,ATTR:,ADDR:1C390,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in4 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN4;

/* Define the union U_HDCP2X_SEC_IN5 */
/* Define the union U_HDCP2X_SEC_IN5,ATTR:,ADDR:1C394,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in5 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN5;

/* Define the union U_HDCP2X_SEC_IN6 */
/* Define the union U_HDCP2X_SEC_IN6,ATTR:,ADDR:1C398,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in6 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN6;

/* Define the union U_HDCP2X_SEC_IN7 */
/* Define the union U_HDCP2X_SEC_IN7,ATTR:,ADDR:1C39C,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_in7 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_IN7;

/* Define the union U_HDCP2X_SEC_OUT0 */
/* Define the union U_HDCP2X_SEC_OUT0,ATTR:,ADDR:1C3A0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out0 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT0;

/* Define the union U_HDCP2X_SEC_OUT1 */
/* Define the union U_HDCP2X_SEC_OUT1,ATTR:,ADDR:1C3A4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out1 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT1;

/* Define the union U_HDCP2X_SEC_OUT2 */
/* Define the union U_HDCP2X_SEC_OUT2,ATTR:,ADDR:1C3A8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out2 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT2;

/* Define the union U_HDCP2X_SEC_OUT3 */
/* Define the union U_HDCP2X_SEC_OUT3,ATTR:,ADDR:1C3AC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out3 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT3;

/* Define the union U_HDCP2X_SEC_OUT4 */
/* Define the union U_HDCP2X_SEC_OUT4,ATTR:,ADDR:1C3B0,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out4 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT4;

/* Define the union U_HDCP2X_SEC_OUT5 */
/* Define the union U_HDCP2X_SEC_OUT5,ATTR:,ADDR:1C3B4,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out5 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT5;

/* Define the union U_HDCP2X_SEC_OUT6 */
/* Define the union U_HDCP2X_SEC_OUT6,ATTR:,ADDR:1C3B8,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out6 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT6;

/* Define the union U_HDCP2X_SEC_OUT7 */
/* Define the union U_HDCP2X_SEC_OUT7,ATTR:,ADDR:1C3BC,INIT:00,MASK:ff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp2x_sec_out7 : 8  ; /* [7:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP2X_SEC_OUT7;


//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_HDCP2X_HW_VER_B0      HDCP2X_HW_VER_B0      ; /* 1C000 */
    volatile U_HDCP2X_HW_VER_B1      HDCP2X_HW_VER_B1      ; /* 1C004 */
    volatile U_HDCP2X_HW_VER_B2      HDCP2X_HW_VER_B2      ; /* 1C008 */
    volatile U_HDCP2X_HW_VER_B3      HDCP2X_HW_VER_B3      ; /* 1C00C */
    volatile U_HDCP2X_SW_VER_B0      HDCP2X_SW_VER_B0      ; /* 1C010 */
    volatile U_HDCP2X_SW_VER_B1      HDCP2X_SW_VER_B1      ; /* 1C014 */
    volatile U_HDCP2X_SW_VER_B2      HDCP2X_SW_VER_B2      ; /* 1C018 */
    volatile U_HDCP2X_SW_VER_B3      HDCP2X_SW_VER_B3      ; /* 1C01C */
    unsigned int                     Reserved_0[13]        ; /* 1C020-1C050 */
    volatile U_HDCP2X_AUTH_CTRL      HDCP2X_AUTH_CTRL      ; /* 1C054 */
    unsigned int                     Reserved_1[10]        ; /* 1C058-1C07C */
    volatile U_HDCP2X_SEC_INTR_B0    HDCP2X_SEC_INTR_B0    ; /* 1C080 */
    volatile U_HDCP2X_SEC_INTR_B1    HDCP2X_SEC_INTR_B1    ; /* 1C084 */
    volatile U_HDCP2X_SEC_MASK_B0    HDCP2X_SEC_MASK_B0    ; /* 1C088 */
    volatile U_HDCP2X_SEC_MASK_B1    HDCP2X_SEC_MASK_B1    ; /* 1C08C */
    unsigned int                     Reserved_2[5]         ; /* 1C090-1C0A0 */
    volatile U_HDCP2X_MCU_INTR_B0    HDCP2X_MCU_INTR_B0    ; /* 1C0A4 */
    volatile U_HDCP2X_MCU_INTR_B1    HDCP2X_MCU_INTR_B1    ; /* 1C0A8 */
    volatile U_HDCP2X_MCU_INTR_B2    HDCP2X_MCU_INTR_B2    ; /* 1C0AC */
    volatile U_HDCP2X_MCU_INTR_B3    HDCP2X_MCU_INTR_B3    ; /* 1C0B0 */
    volatile U_HDCP2X_MCU_MASK_B0    HDCP2X_MCU_MASK_B0    ; /* 1C0B4 */
    volatile U_HDCP2X_MCU_MASK_B1    HDCP2X_MCU_MASK_B1    ; /* 1C0B8 */
    volatile U_HDCP2X_MCU_MASK_B2    HDCP2X_MCU_MASK_B2    ; /* 1C0BC */
    volatile U_HDCP2X_MCU_MASK_B3    HDCP2X_MCU_MASK_B3    ; /* 1C0C0 */
    unsigned int                     Reserved_3[2]         ; /* 1C0C4-1C0C8 */
    volatile U_HDCP2X_MCU_STATE_B0   HDCP2X_MCU_STATE_B0   ; /* 1C0CC */
    volatile U_HDCP2X_MCU_STATE_B1   HDCP2X_MCU_STATE_B1   ; /* 1C0D0 */
    volatile U_HDCP2X_MCU_STATE_B2   HDCP2X_MCU_STATE_B2   ; /* 1C0D4 */
    volatile U_HDCP2X_MCU_STATE_B3   HDCP2X_MCU_STATE_B3   ; /* 1C0D8 */
    unsigned int                     Reserved_4[3]         ; /* 1C0DC-1C0E4 */
    volatile U_HDCP2X_RX_AUTH_STATE  HDCP2X_RX_AUTH_STATE  ; /* 1C0E8 */
    volatile U_HDCP2X_RPT_AUTH_STATE HDCP2X_RPT_AUTH_STATE ; /* 1C0EC */
    volatile U_HDCP2X_AUTH_STATE0    HDCP2X_AUTH_STATE0    ; /* 1C0F0 */
    volatile U_HDCP2X_AUTH_STATE1    HDCP2X_AUTH_STATE1    ; /* 1C0F4 */
    volatile U_HDCP2X_AUTH_STATE2    HDCP2X_AUTH_STATE2    ; /* 1C0F8 */
    volatile U_HDCP2X_AUTH_STATE3    HDCP2X_AUTH_STATE3    ; /* 1C0FC */
    unsigned int                     Reserved_5[5]         ; /* 1C100-1C110 */
    volatile U_HDCP2X_CERT_INFO      HDCP2X_CERT_INFO      ; /* 1C114 */
    volatile U_HDCP2X_CERT_VER       HDCP2X_CERT_VER       ; /* 1C118 */
    volatile U_HDCP2X_RPT_INFO       HDCP2X_RPT_INFO       ; /* 1C11C */
    volatile U_HDCP2X_RPT_DEV        HDCP2X_RPT_DEV        ; /* 1C120 */
    volatile U_HDCP2X_RPT_V0         HDCP2X_RPT_V0         ; /* 1C124 */
    volatile U_HDCP2X_RPT_V1         HDCP2X_RPT_V1         ; /* 1C128 */
    volatile U_HDCP2X_RPT_V2         HDCP2X_RPT_V2         ; /* 1C12C */
    volatile U_HDCP2X_RPT_K0         HDCP2X_RPT_K0         ; /* 1C130 */
    volatile U_HDCP2X_RPT_K1         HDCP2X_RPT_K1         ; /* 1C134 */
    volatile U_HDCP2X_RPT_M0         HDCP2X_RPT_M0         ; /* 1C138 */
    volatile U_HDCP2X_RPT_M1         HDCP2X_RPT_M1         ; /* 1C13C */
    volatile U_HDCP2X_RPT_M2         HDCP2X_RPT_M2         ; /* 1C140 */
    volatile U_HDCP2X_RPT_STRM_ID    HDCP2X_RPT_STRM_ID    ; /* 1C144 */
    volatile U_HDCP2X_RPT_STRM_TPYE  HDCP2X_RPT_STRM_TPYE  ; /* 1C148 */
    unsigned int                     Reserved_6[22]        ; /* 1C14C-1C1A0 */
    volatile U_HDCP2X_TIMING_CFG0    HDCP2X_TIMING_CFG0    ; /* 1C1A4 */
    volatile U_HDCP2X_TIMING_CFG1    HDCP2X_TIMING_CFG1    ; /* 1C1A8 */
    volatile U_HDCP2X_TIMING_CFG2    HDCP2X_TIMING_CFG2    ; /* 1C1AC */
    volatile U_HDCP2X_TIMING_CFG3    HDCP2X_TIMING_CFG3    ; /* 1C1B0 */
    volatile U_HDCP2X_TIMING_CFG4    HDCP2X_TIMING_CFG4    ; /* 1C1B4 */
    volatile U_HDCP2X_TIMING_CFG5    HDCP2X_TIMING_CFG5    ; /* 1C1B8 */
    volatile U_HDCP2X_TIMING_CFG6    HDCP2X_TIMING_CFG6    ; /* 1C1BC */
    volatile U_HDCP2X_TIMING_CFG7    HDCP2X_TIMING_CFG7    ; /* 1C1C0 */
    volatile U_HDCP2X_TIMING_CFG8    HDCP2X_TIMING_CFG8    ; /* 1C1C4 */
    volatile U_HDCP2X_TIMING_CFG9    HDCP2X_TIMING_CFG9    ; /* 1C1C8 */
    volatile U_HDCP2X_TIMING_CFG10   HDCP2X_TIMING_CFG10   ; /* 1C1CC */
    volatile U_HDCP2X_TIMING_CFG11   HDCP2X_TIMING_CFG11   ; /* 1C1D0 */
    volatile U_HDCP2X_TIMING_CFG12   HDCP2X_TIMING_CFG12   ; /* 1C1D4 */
    volatile U_HDCP2X_TIMING_CFG13   HDCP2X_TIMING_CFG13   ; /* 1C1D8 */
    volatile U_HDCP2X_TIMING_CFG14   HDCP2X_TIMING_CFG14   ; /* 1C1DC */
    volatile U_HDCP2X_TIMING_CFG15   HDCP2X_TIMING_CFG15   ; /* 1C1E0 */
    volatile U_HDCP2X_TIMING_CFG16   HDCP2X_TIMING_CFG16   ; /* 1C1E4 */
    volatile U_HDCP2X_TIMING_CFG17   HDCP2X_TIMING_CFG17   ; /* 1C1E8 */
    volatile U_HDCP2X_TIMING_CFG18   HDCP2X_TIMING_CFG18   ; /* 1C1EC */
    volatile U_HDCP2X_TIMING_CFG19   HDCP2X_TIMING_CFG19   ; /* 1C1F0 */
    volatile U_HDCP2X_TIMING_CFG20   HDCP2X_TIMING_CFG20   ; /* 1C1F4 */
    volatile U_HDCP2X_TIMING_CFG21   HDCP2X_TIMING_CFG21   ; /* 1C1F8 */
    volatile U_HDCP2X_TIMING_CFG22   HDCP2X_TIMING_CFG22   ; /* 1C1FC */
    volatile U_HDCP2X_TIMING_CFG23   HDCP2X_TIMING_CFG23   ; /* 1C200 */
    volatile U_HDCP2X_TIMING_CFG24   HDCP2X_TIMING_CFG24   ; /* 1C204 */
    volatile U_HDCP2X_TIMING_CFG25   HDCP2X_TIMING_CFG25   ; /* 1C208 */
    volatile U_HDCP2X_TIMING_CFG26   HDCP2X_TIMING_CFG26   ; /* 1C20C */
    volatile U_HDCP2X_TIMING_CFG27   HDCP2X_TIMING_CFG27   ; /* 1C210 */
    volatile U_HDCP2X_TIMING_CFG28   HDCP2X_TIMING_CFG28   ; /* 1C214 */
    volatile U_HDCP2X_TIMING_CFG29   HDCP2X_TIMING_CFG29   ; /* 1C218 */
    volatile U_HDCP2X_TIMING_CFG30   HDCP2X_TIMING_CFG30   ; /* 1C21C */
    volatile U_HDCP2X_TIMING_CFG31   HDCP2X_TIMING_CFG31   ; /* 1C220 */
    volatile U_HDCP2X_GEN_IN0        HDCP2X_GEN_IN0        ; /* 1C224 */
    volatile U_HDCP2X_GEN_IN1        HDCP2X_GEN_IN1        ; /* 1C228 */
    volatile U_HDCP2X_GEN_IN2        HDCP2X_GEN_IN2        ; /* 1C22C */
    volatile U_HDCP2X_GEN_IN3        HDCP2X_GEN_IN3        ; /* 1C230 */
    volatile U_HDCP2X_GEN_IN4        HDCP2X_GEN_IN4        ; /* 1C234 */
    volatile U_HDCP2X_GEN_IN5        HDCP2X_GEN_IN5        ; /* 1C238 */
    volatile U_HDCP2X_GEN_IN6        HDCP2X_GEN_IN6        ; /* 1C23C */
    volatile U_HDCP2X_GEN_IN7        HDCP2X_GEN_IN7        ; /* 1C240 */
    volatile U_HDCP2X_GEN_IN8        HDCP2X_GEN_IN8        ; /* 1C244 */
    volatile U_HDCP2X_GEN_IN9        HDCP2X_GEN_IN9        ; /* 1C248 */
    volatile U_HDCP2X_GEN_IN10       HDCP2X_GEN_IN10       ; /* 1C24C */
    volatile U_HDCP2X_GEN_IN11       HDCP2X_GEN_IN11       ; /* 1C250 */
    volatile U_HDCP2X_GEN_IN12       HDCP2X_GEN_IN12       ; /* 1C254 */
    volatile U_HDCP2X_GEN_IN13       HDCP2X_GEN_IN13       ; /* 1C258 */
    volatile U_HDCP2X_GEN_IN14       HDCP2X_GEN_IN14       ; /* 1C25C */
    volatile U_HDCP2X_GEN_IN15       HDCP2X_GEN_IN15       ; /* 1C260 */
    volatile U_HDCP2X_GEN_IN16       HDCP2X_GEN_IN16       ; /* 1C264 */
    volatile U_HDCP2X_GEN_IN17       HDCP2X_GEN_IN17       ; /* 1C268 */
    volatile U_HDCP2X_GEN_IN18       HDCP2X_GEN_IN18       ; /* 1C26C */
    volatile U_HDCP2X_GEN_IN19       HDCP2X_GEN_IN19       ; /* 1C270 */
    volatile U_HDCP2X_GEN_IN20       HDCP2X_GEN_IN20       ; /* 1C274 */
    volatile U_HDCP2X_GEN_IN21       HDCP2X_GEN_IN21       ; /* 1C278 */
    volatile U_HDCP2X_GEN_IN22       HDCP2X_GEN_IN22       ; /* 1C27C */
    volatile U_HDCP2X_GEN_IN23       HDCP2X_GEN_IN23       ; /* 1C280 */
    volatile U_HDCP2X_GEN_IN24       HDCP2X_GEN_IN24       ; /* 1C284 */
    volatile U_HDCP2X_GEN_IN25       HDCP2X_GEN_IN25       ; /* 1C288 */
    volatile U_HDCP2X_GEN_IN26       HDCP2X_GEN_IN26       ; /* 1C28C */
    volatile U_HDCP2X_GEN_IN27       HDCP2X_GEN_IN27       ; /* 1C290 */
    volatile U_HDCP2X_GEN_IN28       HDCP2X_GEN_IN28       ; /* 1C294 */
    volatile U_HDCP2X_GEN_IN29       HDCP2X_GEN_IN29       ; /* 1C298 */
    volatile U_HDCP2X_GEN_IN30       HDCP2X_GEN_IN30       ; /* 1C29C */
    volatile U_HDCP2X_GEN_IN31       HDCP2X_GEN_IN31       ; /* 1C2A0 */
    volatile U_HDCP2X_GEN_OUT0       HDCP2X_GEN_OUT0       ; /* 1C2A4 */
    volatile U_HDCP2X_GEN_OUT1       HDCP2X_GEN_OUT1       ; /* 1C2A8 */
    volatile U_HDCP2X_GEN_OUT2       HDCP2X_GEN_OUT2       ; /* 1C2AC */
    volatile U_HDCP2X_GEN_OUT3       HDCP2X_GEN_OUT3       ; /* 1C2B0 */
    volatile U_HDCP2X_GEN_OUT4       HDCP2X_GEN_OUT4       ; /* 1C2B4 */
    volatile U_HDCP2X_GEN_OUT5       HDCP2X_GEN_OUT5       ; /* 1C2B8 */
    volatile U_HDCP2X_GEN_OUT6       HDCP2X_GEN_OUT6       ; /* 1C2BC */
    volatile U_HDCP2X_GEN_OUT7       HDCP2X_GEN_OUT7       ; /* 1C2C0 */
    volatile U_HDCP2X_GEN_OUT8       HDCP2X_GEN_OUT8       ; /* 1C2C4 */
    volatile U_HDCP2X_GEN_OUT9       HDCP2X_GEN_OUT9       ; /* 1C2C8 */
    volatile U_HDCP2X_GEN_OUT10      HDCP2X_GEN_OUT10      ; /* 1C2CC */
    volatile U_HDCP2X_GEN_OUT11      HDCP2X_GEN_OUT11      ; /* 1C2D0 */
    volatile U_HDCP2X_GEN_OUT12      HDCP2X_GEN_OUT12      ; /* 1C2D4 */
    volatile U_HDCP2X_GEN_OUT13      HDCP2X_GEN_OUT13      ; /* 1C2D8 */
    volatile U_HDCP2X_GEN_OUT14      HDCP2X_GEN_OUT14      ; /* 1C2DC */
    volatile U_HDCP2X_GEN_OUT15      HDCP2X_GEN_OUT15      ; /* 1C2E0 */
    volatile U_HDCP2X_GEN_OUT16      HDCP2X_GEN_OUT16      ; /* 1C2E4 */
    volatile U_HDCP2X_GEN_OUT17      HDCP2X_GEN_OUT17      ; /* 1C2E8 */
    volatile U_HDCP2X_GEN_OUT18      HDCP2X_GEN_OUT18      ; /* 1C2EC */
    volatile U_HDCP2X_GEN_OUT19      HDCP2X_GEN_OUT19      ; /* 1C2F0 */
    volatile U_HDCP2X_GEN_OUT20      HDCP2X_GEN_OUT20      ; /* 1C2F4 */
    volatile U_HDCP2X_GEN_OUT21      HDCP2X_GEN_OUT21      ; /* 1C2F8 */
    volatile U_HDCP2X_GEN_OUT22      HDCP2X_GEN_OUT22      ; /* 1C2FC */
    volatile U_HDCP2X_GEN_OUT23      HDCP2X_GEN_OUT23      ; /* 1C300 */
    volatile U_HDCP2X_GEN_OUT24      HDCP2X_GEN_OUT24      ; /* 1C304 */
    volatile U_HDCP2X_GEN_OUT25      HDCP2X_GEN_OUT25      ; /* 1C308 */
    volatile U_HDCP2X_GEN_OUT26      HDCP2X_GEN_OUT26      ; /* 1C30C */
    volatile U_HDCP2X_GEN_OUT27      HDCP2X_GEN_OUT27      ; /* 1C310 */
    volatile U_HDCP2X_GEN_OUT28      HDCP2X_GEN_OUT28      ; /* 1C314 */
    volatile U_HDCP2X_GEN_OUT29      HDCP2X_GEN_OUT29      ; /* 1C318 */
    volatile U_HDCP2X_GEN_OUT30      HDCP2X_GEN_OUT30      ; /* 1C31C */
    volatile U_HDCP2X_GEN_OUT31      HDCP2X_GEN_OUT31      ; /* 1C320 */
    unsigned int                     Reserved_7[23]        ; /* 1C324-1C37C */
    volatile U_HDCP2X_SEC_IN0        HDCP2X_SEC_IN0        ; /* 1C380 */
    volatile U_HDCP2X_SEC_IN1        HDCP2X_SEC_IN1        ; /* 1C384 */
    volatile U_HDCP2X_SEC_IN2        HDCP2X_SEC_IN2        ; /* 1C388 */
    volatile U_HDCP2X_SEC_IN3        HDCP2X_SEC_IN3        ; /* 1C38C */
    volatile U_HDCP2X_SEC_IN4        HDCP2X_SEC_IN4        ; /* 1C390 */
    volatile U_HDCP2X_SEC_IN5        HDCP2X_SEC_IN5        ; /* 1C394 */
    volatile U_HDCP2X_SEC_IN6        HDCP2X_SEC_IN6        ; /* 1C398 */
    volatile U_HDCP2X_SEC_IN7        HDCP2X_SEC_IN7        ; /* 1C39C */
    volatile U_HDCP2X_SEC_OUT0       HDCP2X_SEC_OUT0       ; /* 1C3A0 */
    volatile U_HDCP2X_SEC_OUT1       HDCP2X_SEC_OUT1       ; /* 1C3A4 */
    volatile U_HDCP2X_SEC_OUT2       HDCP2X_SEC_OUT2       ; /* 1C3A8 */
    volatile U_HDCP2X_SEC_OUT3       HDCP2X_SEC_OUT3       ; /* 1C3AC */
    volatile U_HDCP2X_SEC_OUT4       HDCP2X_SEC_OUT4       ; /* 1C3B0 */
    volatile U_HDCP2X_SEC_OUT5       HDCP2X_SEC_OUT5       ; /* 1C3B4 */
    volatile U_HDCP2X_SEC_OUT6       HDCP2X_SEC_OUT6       ; /* 1C3B8 */
    volatile U_HDCP2X_SEC_OUT7       HDCP2X_SEC_OUT7       ; /* 1C3BC */

} S_mcu_cpu_reg_REGS_TYPE;

/* Declare the struct pointor of the module mcu_cpu_reg */
//extern volatile S_mcu_cpu_reg_REGS_TYPE *gopmcu_cpu_regAllReg;
int HDMI_TX_S_mcu_cpu_reg_REGS_TYPE_Init(HI_CHAR *pcAddr);
int HDMI_TX_S_mcu_cpu_reg_REGS_TYPE_DeInit(void);

/* Declare the functions that set the member value */
int HDMI_HDCP2X_HW_VER_B0_hdcp2x_hw_ver_b0Set(unsigned int uhdcp2x_hw_ver_b0);
int HDMI_HDCP2X_HW_VER_B1_hdcp2x_hw_ver_b1Set(unsigned int uhdcp2x_hw_ver_b1);
int HDMI_HDCP2X_HW_VER_B2_hdcp2x_hw_ver_b2Set(unsigned int uhdcp2x_hw_ver_b2);
int HDMI_HDCP2X_HW_VER_B3_hdcp2x_hw_ver_b3Set(unsigned int uhdcp2x_hw_ver_b3);
int HDMI_HDCP2X_SW_VER_B0_hdcp2x_sw_ver_b0Get(HI_VOID);
int HDMI_HDCP2X_SW_VER_B1_hdcp2x_sw_ver_b1Get(HI_VOID);
int HDMI_HDCP2X_SW_VER_B2_hdcp2x_sw_ver_b2Get(HI_VOID);
int HDMI_HDCP2X_SW_VER_B3_hdcp2x_sw_ver_b3Get(HI_VOID);
int HDMI_HDCP2X_AUTH_CTRL_mcu_auth_startSet(unsigned int umcu_auth_start);
int HDMI_HDCP2X_AUTH_CTRL_mcu_auth_stopSet(unsigned int umcu_auth_stop);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr0Set(unsigned int uhdcp2x_mcu_intr0);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr0Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr1Set(unsigned int uhdcp2x_mcu_intr1);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr1Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr2Set(unsigned int uhdcp2x_mcu_intr2);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr2Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr3Set(unsigned int uhdcp2x_mcu_intr3);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr3Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr4Set(unsigned int uhdcp2x_mcu_intr4);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr4Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr5Set(unsigned int uhdcp2x_mcu_intr5);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr5Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr6Set(unsigned int uhdcp2x_mcu_intr6);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr6Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr7Set(unsigned int uhdcp2x_mcu_intr7);
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr7Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr8Set(unsigned int uhdcp2x_mcu_intr8);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr8Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr9Set(unsigned int uhdcp2x_mcu_intr9);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr9Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr10Set(unsigned int uhdcp2x_mcu_intr10);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr10Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr11Set(unsigned int uhdcp2x_mcu_intr11);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr11Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr12Set(unsigned int uhdcp2x_mcu_intr12);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr12Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr13Set(unsigned int uhdcp2x_mcu_intr13);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr13Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr14Set(unsigned int uhdcp2x_mcu_intr14);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr14Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr15Set(unsigned int uhdcp2x_mcu_intr15);
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr15Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr16Set(unsigned int uhdcp2x_mcu_intr16);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr16Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr17Set(unsigned int uhdcp2x_mcu_intr17);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr17Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr18Set(unsigned int uhdcp2x_mcu_intr18);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr18Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr19Set(unsigned int uhdcp2x_mcu_intr19);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr19Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr20Set(unsigned int uhdcp2x_mcu_intr20);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr20Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr21Set(unsigned int uhdcp2x_mcu_intr21);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr21Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr22Set(unsigned int uhdcp2x_mcu_intr22);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr22Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr23Set(unsigned int uhdcp2x_mcu_intr23);
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr23Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr24Set(unsigned int uhdcp2x_mcu_intr24);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr24Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr25Set(unsigned int uhdcp2x_mcu_intr25);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr25Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr26Set(unsigned int uhdcp2x_mcu_intr26);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr26Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr27Set(unsigned int uhdcp2x_mcu_intr27);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr27Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr28Set(unsigned int uhdcp2x_mcu_intr28);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr28Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr29Set(unsigned int uhdcp2x_mcu_intr29);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr29Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr30Set(unsigned int uhdcp2x_mcu_intr30);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr30Get(HI_VOID);
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr31Set(unsigned int uhdcp2x_mcu_intr31);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_ake_init_doneGet(HI_VOID);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_cert_doneGet(HI_VOID);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_km_doneGet(HI_VOID);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_h_doneGet(HI_VOID);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_pairing_doneGet(HI_VOID);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_lc_init_doneGet(HI_VOID);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_l_doneGet(HI_VOID);
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_sks_doneGet(HI_VOID);
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_id_list_doneGet(HI_VOID);
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_send_ack_doneGet(HI_VOID);
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_strm_id_doneGet(HI_VOID);
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_strm_rdy_doneGet(HI_VOID);
int HDMI_HDCP2X_AUTH_STATE0_hdcp2x_auth_state0Get(HI_VOID);
int HDMI_HDCP2X_AUTH_STATE1_hdcp2x_auth_state1Get(HI_VOID);
int HDMI_HDCP2X_AUTH_STATE2_hdcp2x_auth_state2Get(HI_VOID);
int HDMI_HDCP2X_AUTH_STATE3_hdcp2x_auth_state3Get(HI_VOID);
int HDMI_HDCP2X_CERT_INFO_hdcp2x_cert_rptGet(HI_VOID);
int HDMI_HDCP2X_CERT_VER_hdcp2x_cert_verGet(HI_VOID);
int HDMI_HDCP2X_RPT_INFO_hdcp1x_dev_onGet(HI_VOID);
int HDMI_HDCP2X_RPT_INFO_hdcp20_rpt_onGet(HI_VOID);
int HDMI_HDCP2X_RPT_INFO_hdcp2x_rpt_cas_excGet(HI_VOID);
int HDMI_HDCP2X_RPT_INFO_hdcp2x_rpt_dev_excGet(HI_VOID);
int HDMI_HDCP2X_RPT_DEV_hdcp2x_rpt_dev_cntGet(HI_VOID);
int HDMI_HDCP2X_RPT_DEV_hdcp2x_rpt_dep_cntGet(HI_VOID);
int HDMI_HDCP2X_RPT_V0_hdcp2x_rpt_v0Get(HI_VOID);
int HDMI_HDCP2X_RPT_V1_hdcp2x_rpt_v1Get(HI_VOID);
int HDMI_HDCP2X_RPT_V2_hdcp2x_rpt_v2Get(HI_VOID);
int HDMI_HDCP2X_RPT_K0_hdcp2x_rpt_k0Set(unsigned int uhdcp2x_rpt_k0);
int HDMI_HDCP2X_RPT_K0_hdcp2x_rpt_k0Get(HI_VOID);
int HDMI_HDCP2X_RPT_K1_hdcp2x_rpt_k1Set(unsigned int uhdcp2x_rpt_k1);
int HDMI_HDCP2X_RPT_K1_hdcp2x_rpt_k1Get(HI_VOID);
int HDMI_HDCP2X_RPT_M0_hdcp2x_rpt_m0Set(unsigned int uhdcp2x_rpt_m0);
int HDMI_HDCP2X_RPT_M0_hdcp2x_rpt_m0Get(HI_VOID);
int HDMI_HDCP2X_RPT_M1_hdcp2x_rpt_m1Set(unsigned int uhdcp2x_rpt_m1);
int HDMI_HDCP2X_RPT_M1_hdcp2x_rpt_m1Get(HI_VOID);
int HDMI_HDCP2X_RPT_M2_hdcp2x_rpt_m2Set(unsigned int uhdcp2x_rpt_m2);
int HDMI_HDCP2X_RPT_M2_hdcp2x_rpt_m2Get(HI_VOID);
int HDMI_HDCP2X_RPT_STRM_ID_hdcp2x_rpt_strm_idSet(unsigned int uhdcp2x_rpt_strm_id);
int HDMI_HDCP2X_RPT_STRM_ID_hdcp2x_rpt_strm_idGet(HI_VOID);
int HDMI_HDCP2X_RPT_STRM_TPYE_hdcp2x_rpt_strm_typeSet(unsigned int uhdcp2x_rpt_strm_type);
int HDMI_HDCP2X_RPT_STRM_TPYE_hdcp2x_rpt_strm_typeGet(HI_VOID);

#endif // __MCU_CPU_REG_C_UNION_DEFINE_H__
