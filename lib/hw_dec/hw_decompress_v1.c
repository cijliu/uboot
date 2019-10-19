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

#include <asm/io.h>
#ifndef error
#include <common.h>
#endif

#include "hw_decompress_v1.h"

#if (defined CONFIG_TARGET_HI3556V200)
#include "hw_decompress_hi3556v200.c"
#endif

#if (defined CONFIG_TARGET_HI3559V200)
#include "hw_decompress_hi3559v200.c"
#endif

#if ((defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300))
#include "hw_decompress_hi3516dv300.c"
#endif

#if (defined CONFIG_TARGET_HI3516CV500)
#include "hw_decompress_hi3516cv500.c"
#endif

#if (defined CONFIG_TARGET_HI3516EV200)
#include "hw_decompress_hi3516ev200.c"
#endif

#if (defined CONFIG_TARGET_HI3516EV300)
#include "hw_decompress_hi3516ev300.c"
#endif

#if (defined CONFIG_TARGET_HI3518EV300)
#include "hw_decompress_hi3518ev300.c"
#endif

#if (defined CONFIG_TARGET_HI3516DV200)
#include "hw_decompress_hi3516dv200.c"
#endif

unsigned int hw_dec_type;
unsigned int hw_dec_sop;
unsigned int hw_dec_eop;
unsigned int hw_dec_cur_blk;
unsigned int hw_blk_total_num;

void hw_dec_sop_eop_first_set(int block_num)
{
    if (block_num == 1) {
        hw_dec_sop = 1;
        hw_dec_eop = 1;
    } else {
        hw_dec_sop = 1;
        hw_dec_eop = 0;
    }

    hw_dec_cur_blk = 0;
    hw_blk_total_num = block_num;
}

static inline void hw_dec_work_en_set(int work_en_flg)
{
    /* Enable the emar */
    writel(work_en_flg, HW_DEC_REG_BASE_ADDR + EAMR_WORK_EN_REG_OFST);
}

static inline void hw_dec_rtn_baddr_set(unsigned int addr)
{
    writel(addr, HW_DEC_REG_BASE_ADDR + DPRS_DATA_RTN_BADDR);
}

static inline void hw_dec_dprs_data_baddr_set(unsigned int addr)
{
    writel(addr, HW_DEC_REG_BASE_ADDR + DPRS_DATA_INFO_BADDR);
}

static inline void hw_dec_data_rtn_len_set(unsigned int len)
{
    writel(len, HW_DEC_REG_BASE_ADDR + DPRS_DATA_RTN_LEN);
}

static inline void hw_dec_dprs_data_len_set(unsigned int len)
{
    writel(len, HW_DEC_REG_BASE_ADDR + DPRS_DATA_INFO_LEN);
}

static inline void hw_dec_crc_check_en(unsigned int crc_en)
{
    writel(crc_en, HW_DEC_REG_BASE_ADDR + CRC_CHECK_EN);
}

static inline void hw_dec_data_crc32_set(unsigned int crc32)
{
    writel(crc32, HW_DEC_REG_BASE_ADDR + DPRS_DATA_CRC32);
}

static inline unsigned int hw_dec_buf_status_get(void)
{
    return readl(HW_DEC_REG_BASE_ADDR + BUF_INFO);
}

static inline unsigned int hw_dec_dprs_rtn_status_get(void)
{
    return readl(HW_DEC_REG_BASE_ADDR + DPRS_RTN_INFO);
}

static inline void hw_dec_buf_status_clr(void)
{
    writel(0x1, HW_DEC_REG_BASE_ADDR + BUF_INFO_CLR);
}

static inline void hw_dec_dprs_rtn_status_clr(void)
{
    writel(0x1, HW_DEC_REG_BASE_ADDR + RLT_INFO_CLR);
}

static inline void hw_dec_intr_en_set(int blk_intr_en, int task_intr_en)
{
    U_INTR_EN intr_en;
    intr_en.bits.task_intrpt_en = task_intr_en;
    intr_en.bits.block_intrpt_en = blk_intr_en;
    writel(intr_en.u32, HW_DEC_REG_BASE_ADDR + INT_EN_REG_ADDR);
}

static inline unsigned int hw_dec_intr_status_get(void)
{
    return readl(HW_DEC_REG_BASE_ADDR + INT_STATUS_REG_ADDR);
}

static inline void hw_dec_block_intr_status_clr(void)
{
    U_INTR_CLR intr_clr;

    intr_clr.u32 = readl(HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
    intr_clr.bits.block_intrpt_clr = 0x1;
    writel(intr_clr.u32, HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
}

static inline void hw_dec_task_intr_status_clr(void)
{
    U_INTR_CLR intr_clr;

    intr_clr.u32 = readl(HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
    intr_clr.bits.task_intrpt_clr = 0x1;
    writel(intr_clr.u32, HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
}

int hw_dec_intr_proc(int irq, void *para)
{
    U_BUF_STATUS buf_status;
    U_INTR_STATUS intr_status;
    U_DPRS_RTN_STATUS dprs_status;
    int ret = 0;

    intr_status.u32 = hw_dec_intr_status_get();
    if (intr_status.bits.block_intrpt) {
        buf_status.u32 = hw_dec_buf_status_get();
        if (buf_status.bits.aval_flg) {
            hw_dec_buf_status_clr();
        }

        hw_dec_block_intr_status_clr();
    }

    if (intr_status.bits.task_intrpt) {
        dprs_status.u32 = hw_dec_dprs_rtn_status_get();
        if (dprs_status.bits.aval_flg) {
            if (dprs_status.bits.err_info) {
#if 0
                printf("err = 0x%x, dec_data_len = 0x%x\n",
                       dprs_status.bits.err_info,
                       readl(HW_DEC_REG_BASE_ADDR
                             + DPRS_RTN_LEN));
#endif
                ret = -2;
            }

            hw_dec_dprs_rtn_status_clr();
        }

        hw_dec_task_intr_status_clr();
        goto out;
    }

    ret = -1;
out:
    return ret;
}

void hw_dec_start(unsigned int src_baddr,
                  unsigned int dst_baddr,
                  unsigned int src_len,
                  unsigned int dst_len,
                  unsigned int crc_en,
                  unsigned int crc32,
                  unsigned int dec_type)
{
    unsigned int val;

    if (hw_dec_sop) {
        if (!dec_type) {
            /* set the parameters of output buffer */
            hw_dec_rtn_baddr_set(dst_baddr);
            hw_dec_data_rtn_len_set(dst_len);
        } else {

            /* set the parameter of output buffer */
            hw_dec_dprs_data_baddr_set(dst_baddr);
            hw_dec_dprs_data_len_set(PAGE_NR(dst_len) * 4);

        }
    }

    /* set the parameter of input buffer */
    writel(src_baddr, HW_DEC_REG_BASE_ADDR + DPRS_DATA_SRC_BADDR);

    val = src_len | (hw_dec_sop << 28)
          | (hw_dec_eop << 29) | (!dec_type << 31);
    writel(val, HW_DEC_REG_BASE_ADDR + DPRS_DATA_SRC_LEN);

    hw_dec_crc_check_en(crc_en);
}

int hw_dec_wait_finish(void)
{
    int ret;
    int times = 0;

    do {
        ret = hw_dec_intr_proc(HW_DEC_INTR, NULL);
        times++;
        if (times > 100000) {
            // printf("hardware decompress overtime!"
            //      " func:%s, line:%d\n",
            //      __func__, __LINE__);
            break;
        }

    } while (-1 == ret);

    return ret;
}

int hw_dec_decompress(unsigned char *dst, int *dstlen,
                      unsigned char *src, int srclen,
                      void *unused)
{
    int ret;
    // printf("dst=0x%08x dstlen=0x%08x,src=0x%0x srclen=0x%08x\n",(int)dst,*dstlen,(int)src,srclen);
    hw_dec_sop_eop_first_set(1);
    hw_dec_start((unsigned int)src, (unsigned int)dst,
                 srclen, *dstlen, 1, 0, hw_dec_type);

    ret = hw_dec_wait_finish();

    *dstlen = readl(HW_DEC_REG_BASE_ADDR + DPRS_RTN_LEN);

    if (ret) {
        return -1;
    }

    return 0;
}

void hw_dec_init(void)
{
    /* enable decompress clock */
    enable_decompress_clock();
    /* Init the emar interface */
    writel(0, HW_DEC_REG_BASE_ADDR + EAMR_RID_REG_OFST);
    writel(0x3, HW_DEC_REG_BASE_ADDR + EAMR_ROSD_REG_OFST);
    writel(0, HW_DEC_REG_BASE_ADDR + EAMR_WID_REG_OFST);
    writel(0x3, HW_DEC_REG_BASE_ADDR + EAMR_WOSD_REG_OFST);

    /*Enable interrupt */
    hw_dec_intr_en_set(0x1, 0x1);

    /* Enable emar */
    hw_dec_work_en_set(0x1);
}

void hw_dec_uinit(void)
{
    hw_dec_work_en_set(0x0);
    hw_dec_intr_en_set(0x0, 0x0);

    /* disable decompress clock */
    disable_decompress_clock();
}

