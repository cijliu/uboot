/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute  it and/or modify it
* under  the terms of  the GNU General Public License as published by the
* Free Software Foundation;  either version 2 of the  License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/


#define PAGE_SIZE       4096
#define PAGE_NR(x) (((x)+PAGE_SIZE-1)/PAGE_SIZE)

/* The base address for emar */
#define HW_DEC_REG_BASE_ADDR    (GZIP_REG_BASE)

/* The global init registers for emar interface */
#define EAMR_RID_REG_OFST   (0x0108)
#define EAMR_ROSD_REG_OFST  (0x010C)
#define EAMR_WID_REG_OFST   (0x0110)
#define EAMR_WOSD_REG_OFST  (0x0114)

/* The enable register */
#define EAMR_WORK_EN_REG_OFST   (0x0100)

#define DPRS_DATA_SRC_BADDR (0x2040)
#define DPRS_DATA_SRC_LEN   (0x2044)

/* Decompress parameter reigsters for page address */
#define DPRS_DATA_RTN_BADDR (0x2020)
#define DPRS_DATA_RTN_LEN   (0x2024)

/* Decompress parameter registers for page data */
#define DPRS_DATA_INFO_BADDR    (0x2028)
#define DPRS_DATA_INFO_LEN  (0x202C)

#define DPRS_DATA_CRC32     (0x2030)

#define CRC_CHECK_EN            (0x4000)

/* The status registers */
#define BUF_INFO        (0x2080)
#define DPRS_RTN_INFO       (0x2084)
#define DPRS_RTN_LEN        (0x2088)
#define BUF_INFO_CLR        (0x2090)
#define RLT_INFO_CLR        (0x2094)

/* The intr registers */
#define INT_EN_REG_ADDR     (0x0128)
#define INT_STATUS_REG_ADDR (0x0124)
#define INT_CLEAR_REG_ADDR  (0x0130)

#define TASK_MODE_REG       (0x2134)

/* Define the union U_DPRS_DATA_BUF_INFO */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    buf_len: 24; /* [23..0] */
        unsigned int    buf_id: 2; /* [25..24] */
        unsigned int    reserved_1: 2; /* [27..26] */
        unsigned int    eop: 1; /* [28] */
        unsigned int    sop: 1; /* [29] */
        unsigned int    reserved_0: 1; /* [30] */
        unsigned int    mode: 1; /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DPRS_DATA_BUF_INFO;

typedef union {
    struct {
        unsigned int buf_id: 2; /* [1:0] */
        unsigned int rsv: 29;   /* [30:2] */
        unsigned int aval_flg: 1;   /* [31] */
    } bits;
    unsigned int u32;
} U_BUF_STATUS;

typedef union {
    struct {
        unsigned int err_info: 8;   /* [7:0] */
        unsigned int rsv: 23;   /* [30:8] */
        unsigned int aval_flg: 1;   /* [31] */
    } bits;

    unsigned int u32;

} U_DPRS_RTN_STATUS;

/* Define the union U_INT_EN */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    task_intrpt_en: 1; /* [0] */
        unsigned int    block_intrpt_en: 1; /* [1] */
        unsigned int    reserved_0: 30; /* [31..2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTR_EN;

typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    task_intrpt: 1; /* [0] */
        unsigned int    block_intrpt: 1; /* [1] */
        unsigned int    reserved_0: 30; /* [31..2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTR_STATUS;

typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    task_intrpt_clr: 1; /* [0] */
        unsigned int    block_intrpt_clr: 1; /* [1] */
        unsigned int    reserved_0: 30; /* [31..2] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} U_INTR_CLR;

