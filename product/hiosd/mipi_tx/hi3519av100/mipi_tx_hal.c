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

#include "type.h"
#include "hi_mipi_tx.h"
#include "mipi_tx_hal.h"
#include "mipi_tx_reg.h"
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <version.h>
#include <net.h>
#include <asm/io.h>
#include <asm/arch/platform.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

/****************************************************************************
 * macro definition                                                         *
 ****************************************************************************/
#define MIPI_TX_REGS_ADDR 0x04780000
#define MIPI_TX_REGS_SIZE 0x10000

#define MIPI_TX_CRG 0x0451011C
#ifndef HI_FPGA
#define MIPI_TX_IO_CONFIG 0x1F001088
#define MIPI_TX_GPIO0_0   0x12140010
#define MIPI_TX_GPIO0_1   0x12140400
#define MIPI_TX_GPIO6_0   0x12146004
#define MIPI_TX_GPIO6_1   0x12146400
#endif

#define MIPI_TX_REF_CLK 27

#define TLPX         80
#define TCLK_PREPARE 70
#define TCLK_ZERO    260
#define TCLK_TRAIL   80
#define TPRE_DELAY   120
#define THS_PREPARE  70
#define THS_ZERO     90
#define THS_TRAIL    80

/* phy addr */
#define PLL_SET0 0x14
#define PLL_SET1 0x15
#define PLL_SET2 0x16
#ifdef HI_FPGA
#define PLL_SET3 0x17
#endif
#define PLL_SET4  0x1E
#define PLL_SET12 0x12
#define PLL_SET13 0x13

#define DATA0_TPRE_DELAY 0x30
#define DATA1_TPRE_DELAY 0x40
#define DATA2_TPRE_DELAY 0x50
#define DATA3_TPRE_DELAY 0x60

#define CLK_TLPX         0x22
#define CLK_TCLK_PREPARE 0x23
#define CLK_TCLK_ZERO    0x24
#define CLK_TCLK_TRAIL   0x25

#define DATA0_TLPX        0x32
#define DATA0_THS_PREPARE 0x33
#define DATA0_THS_ZERO    0x34
#define DATA0_THS_TRAIL   0x35
#define DATA1_TLPX        0x42
#define DATA1_THS_PREPARE 0x43
#define DATA1_THS_ZERO    0x44
#define DATA1_THS_TRAIL   0x45
#define DATA2_TLPX        0x52
#define DATA2_THS_PREPARE 0x53
#define DATA2_THS_ZERO    0x54
#define DATA2_THS_TRAIL   0x55
#define DATA3_TLPX        0x62
#define DATA3_THS_PREPARE 0x63
#define DATA3_THS_ZERO    0x64
#define DATA3_THS_TRAIL   0x65

#define MIPI_TX_MAX_RESET_PHY_TIMES 10

#define IO_ADDRESS(x) (x)

/****************************************************************************
 * global variables definition                                              *
 ****************************************************************************/
mipi_tx_regs_type_t *g_mipi_tx_regs_va = NULL;

unsigned int g_actual_phy_data_rate;

/****************************************************************************
 * function definition                                                      *
 ****************************************************************************/
static inline void write_reg32(unsigned long addr,
                               unsigned int value,
                               unsigned int mask)
{
    unsigned int t;

    t = readl((void *)addr);
    t &= ~mask;
    t |= value & mask;
    writel(t, (void *)addr);
}

int mipi_tx_drv_reset_phy(combo_dev_cfg_t *dev_cfg)
{
    static int count = 0;
    count++;
#if MIPI_TX_DEBUG
    printf("reset phy count ===================================== %d\n", count);
#endif
    /* set phy config */
    mipi_tx_drv_set_phy_cfg(dev_cfg);

    return count;
}

static void set_phy_reg(unsigned int addr, unsigned char value)
{
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL1.u32 = (0x10000 + addr);
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x2;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x0;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL1.u32 = value;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x2;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x0;
    isb();
    dsb();
    dmb();
}

void mipi_tx_pll_status_check(combo_dev_cfg_t *dev_cfg);

void mipi_tx_drv_set_phy_cfg(combo_dev_cfg_t *dev_cfg)
{
    unsigned char pll_set0;
    unsigned char pll_set1;
    unsigned char pll_set2;
    unsigned char pll_set12;
#ifdef HI_FPGA
    unsigned char pll_set3;
#endif
    unsigned char pll_set4;
    unsigned char data_tpre_delay;
    unsigned char clk_tlpx;
    unsigned char clk_tclk_prepare;
    unsigned char clk_tclk_zero;
    unsigned char clk_tclk_trail;
    unsigned char data_tlpx;
    unsigned char data_ths_prepare;
    unsigned char data_ths_zero;
    unsigned char data_ths_trail;

    /* disable input */
    g_mipi_tx_regs_va->OPERATION_MODE.u32 = 0x0;

    /* pwr_up unreset */
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x0;
    udelay(1);
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x1;

    /* stop phy driver output */
    pll_set12 = 0x20;
    set_phy_reg(PLL_SET12, pll_set12);
    pll_set12 = 0x30;
    set_phy_reg(PLL_SET12, pll_set12);

    /* step1: phy exit ulps mode */
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.u32 = 0x0;

    /* phy power down */
    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0x0;
    udelay(5);

    /* pll_set0 */
    pll_set0 = 0x0;
    set_phy_reg(PLL_SET0, pll_set0);

    /* pll_set1 */
    pll_set1 = 0xf;
    set_phy_reg(PLL_SET1, pll_set1);
    /* pll_set2 */
    pll_set2 = 0x61;
    set_phy_reg(PLL_SET2, pll_set2);
    /* pll_set4 */
    pll_set4 = 0x68;
    set_phy_reg(PLL_SET4, pll_set4);

    /* step3 :phy power on */
    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0xf;
    /* step4 */
    udelay(100);

    /* step5:999M start pll  */
    /* pll_set1 */
    pll_set1 = 0x25;
    set_phy_reg(PLL_SET1, pll_set1);

    /* pll_set4 */
    pll_set4 = 0x68;
    set_phy_reg(PLL_SET4, pll_set4);

    /* pll_set0 */
    pll_set0 = 0x02;
    set_phy_reg(PLL_SET0, pll_set0);

    /* pll_set2 */
    pll_set2 = 0xe1;
    set_phy_reg(PLL_SET2, pll_set2);

    udelay(100);

    /* pll_set0 */
    pll_set0 = 0x0;
    set_phy_reg(PLL_SET0, pll_set0);

    /* pll_set2 */
    pll_set2 = 0x61;
    set_phy_reg(PLL_SET2, pll_set2);

    /* pll_set1 */
#ifndef HI_FPGA
    if (dev_cfg->phy_data_rate >= 320) {
        pll_set1 = (dev_cfg->phy_data_rate + MIPI_TX_REF_CLK - 1) / MIPI_TX_REF_CLK;  // 594/27=22
        g_actual_phy_data_rate = pll_set1 * MIPI_TX_REF_CLK;      // 22*27=594
    } else {
        pll_set1 = (dev_cfg->phy_data_rate * 4 + MIPI_TX_REF_CLK - 1) / MIPI_TX_REF_CLK;
        g_actual_phy_data_rate = pll_set1 * MIPI_TX_REF_CLK / 4;
    }
#else
    if (dev_cfg->phy_data_rate >= 320) {
        pll_set1 = dev_cfg->phy_data_rate / MIPI_TX_REF_CLK / 2;
        g_actual_phy_data_rate = dev_cfg->phy_data_rate / MIPI_TX_REF_CLK * MIPI_TX_REF_CLK;
    } else {
        pll_set1 = dev_cfg->phy_data_rate * 4 / MIPI_TX_REF_CLK / 2;
        g_actual_phy_data_rate = dev_cfg->phy_data_rate * 4 / MIPI_TX_REF_CLK * MIPI_TX_REF_CLK / 4;
    }
#endif
    set_phy_reg(PLL_SET1, pll_set1);

    /* pll_set4 */
#ifndef HI_FPGA
    if (dev_cfg->phy_data_rate >= 320) {
        pll_set4 = 0x68;
    } else {
        pll_set4 = 0x6c;
    }
#else
    if (dev_cfg->phy_data_rate >= 320) {
        if (dev_cfg->phy_data_rate >= 750) {
            pll_set4 = 0x68;
        } else {
            pll_set4 = 0x28;
        }
    } else {
        pll_set4 = 0x2c;
    }
#endif
    set_phy_reg(PLL_SET4, pll_set4);

#ifdef HI_FPGA
    pll_set3 = 0x1;
    set_phy_reg(PLL_SET3, pll_set3);
#endif

    /* DATA0~3 TPRE-DELAY */
    data_tpre_delay = (g_actual_phy_data_rate * TPRE_DELAY + 4000) / 8000;  // 9
    set_phy_reg(DATA0_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA1_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA2_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA3_TPRE_DELAY, data_tpre_delay);

    /* CLK_TLPX */
    clk_tlpx = (g_actual_phy_data_rate * TLPX + 4000) / 8000;  // 6
    set_phy_reg(CLK_TLPX, clk_tlpx);

    /* CLK_TCLK_PREPARE */
    clk_tclk_prepare = (g_actual_phy_data_rate * TCLK_PREPARE + 4000) / 8000;  // 5
    set_phy_reg(CLK_TCLK_PREPARE, clk_tclk_prepare);

    /* CLK_TCLK_ZERO */
    clk_tclk_zero = (g_actual_phy_data_rate * TCLK_ZERO + 4000) / 8000;  // 19 = 0x13
    set_phy_reg(CLK_TCLK_ZERO, clk_tclk_zero);

    /* CLK_TCLK_TRAIL */
    clk_tclk_trail = (g_actual_phy_data_rate * TCLK_TRAIL + 4000) / 8000;  // 6
    set_phy_reg(CLK_TCLK_TRAIL, clk_tclk_trail);

    /* ------------------
       DATA_TLPX
       DATA_THS_PREPARE
       DATA_THS_ZERO
       DATA_THS_TRAIL
    ------------------ */
    data_tlpx = (g_actual_phy_data_rate * TLPX + 4000) / 8000;                // 6
    data_ths_prepare = (g_actual_phy_data_rate * THS_PREPARE + 4000) / 8000;  // 5
    data_ths_zero = (g_actual_phy_data_rate * THS_ZERO + 4000) / 8000;        // 7
    data_ths_trail = (g_actual_phy_data_rate * THS_TRAIL + 4000) / 8000;      // 6

    set_phy_reg(DATA0_TLPX, data_tlpx);
    set_phy_reg(DATA0_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA0_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA0_THS_TRAIL, data_ths_trail);
    set_phy_reg(DATA1_TLPX, data_tlpx);
    set_phy_reg(DATA1_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA1_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA1_THS_TRAIL, data_ths_trail);
    set_phy_reg(DATA2_TLPX, data_tlpx);
    set_phy_reg(DATA2_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA2_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA2_THS_TRAIL, data_ths_trail);
    set_phy_reg(DATA3_TLPX, data_tlpx);
    set_phy_reg(DATA3_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA3_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA3_THS_TRAIL, data_ths_trail);

#ifdef MIPI_TX_DEBUG
    printf("\n==========phy info=======\n");
    printf("pll_set0(0x14): 0x%x\n", pll_set0);
    printf("pll_set1(0x15): 0x%x\n", pll_set1);
    printf("pll_set2(0x16): 0x%x\n", pll_set2);
#ifdef HI_FPGA
    printf("pll_set3(0x17): 0x%x\n", pll_set3);
#endif
    printf("pll_set4(0x1e): 0x%x\n", pll_set4);
    printf("data_tpre_delay(0x30/40/50/60): 0x%x\n", data_tpre_delay);
    printf("clk_tlpx(0x22): 0x%x\n", clk_tlpx);
    printf("clk_tclk_prepare(0x23): 0x%x\n", clk_tclk_prepare);
    printf("clk_tclk_zero(0x24): 0x%x\n", clk_tclk_zero);
    printf("clk_tclk_trail(0x25): 0x%x\n", clk_tclk_trail);
    printf("data_tlpx(0x32/42/52/62): 0x%x\n", data_tlpx);
    printf("data_ths_prepare(0x33/43/53/63): 0x%x\n", data_ths_prepare);
    printf("data_ths_zero(0x34/44/54/64): 0x%x\n", data_ths_zero);
    printf("data_ths_trail(0x35/45/55/65): 0x%x\n", data_ths_trail);
    printf("=========================\n");
#endif

    /* data lp2hs,hs2lp time */
    g_mipi_tx_regs_va->PHY_TMR_CFG.u32 = (data_ths_trail << 16) +
                                       (data_tpre_delay + data_tlpx + data_ths_prepare + data_ths_zero);
    /* clk lp2hs,hs2lp time */
    g_mipi_tx_regs_va->PHY_TMR_LPCLK_CFG.u32 = ((32 + data_ths_trail) << 16) + (clk_tlpx + clk_tclk_prepare +
                                                                              clk_tclk_zero);

#ifdef MIPI_TX_DEBUG
    printf("PHY_TMR_CFG(0x9C): 0x%x\n", g_mipi_tx_regs_va->PHY_TMR_CFG.u32);
    printf("PHY_TMR_LPCLK_CFG(0x98): 0x%x\n", g_mipi_tx_regs_va->PHY_TMR_LPCLK_CFG.u32);
#endif

    udelay(1000);
}

static void set_output_format(combo_dev_cfg_t *dev_cfg)
{
    int color_coding = 0;

    if (dev_cfg->output_mode == OUTPUT_MODE_CSI) {
        if (dev_cfg->output_format == OUT_FORMAT_YUV420_8_BIT_NORMAL) {
            color_coding = 0xd;
        } else if (dev_cfg->output_format == OUT_FORMAT_YUV422_8_BIT) {
            color_coding = 0x1;
        }
    } else {
        if (dev_cfg->output_format == OUT_FORMAT_RGB_16_BIT) {
            color_coding = 0x0;
        } else if (dev_cfg->output_format == OUT_FORMAT_RGB_18_BIT) {
            color_coding = 0x3;
        } else if (dev_cfg->output_format == OUT_FORMAT_RGB_24_BIT) {
            color_coding = 0x5;
        }
    }

    g_mipi_tx_regs_va->COLOR_CODING.u32 = color_coding;
#ifdef MIPI_TX_DEBUG
    printf("set_output_format: 0x%x\n", color_coding);
#endif
}

static void set_video_mode_cfg(combo_dev_cfg_t *dev_cfg)
{
    int video_mode;

    if (dev_cfg->video_mode == NON_BURST_MODE_SYNC_PULSES) {
        video_mode = 0;
    } else if (dev_cfg->video_mode == NON_BURST_MODE_SYNC_EVENTS) {
        video_mode = 1;
    } else {
        video_mode = 2;
    }

    if ((dev_cfg->output_mode == OUTPUT_MODE_CSI) || (dev_cfg->output_mode == OUTPUT_MODE_DSI_CMD)) {
        video_mode = 2;
    }

    g_mipi_tx_regs_va->VID_MODE_CFG.u32 = 0x3f00 + video_mode;
}

static void set_timing_config(combo_dev_cfg_t *dev_cfg)
{
    unsigned int hsa_time;
    unsigned int hbp_time;
    unsigned int hline_time;

    if (dev_cfg->pixel_clk == 0) {
        printf("dev_cfg->pixel_clk is 0, illegal.\n");
        return;
    }

    hsa_time = g_actual_phy_data_rate * dev_cfg->sync_info.vid_hsa_pixels * 125 / dev_cfg->pixel_clk;
    hbp_time = g_actual_phy_data_rate * dev_cfg->sync_info.vid_hbp_pixels * 125 / dev_cfg->pixel_clk;
    hline_time = g_actual_phy_data_rate * dev_cfg->sync_info.vid_hline_pixels * 125 / dev_cfg->pixel_clk;

    g_mipi_tx_regs_va->VID_HSA_TIME.u32 = hsa_time;
    g_mipi_tx_regs_va->VID_HBP_TIME.u32 = hbp_time;
    g_mipi_tx_regs_va->VID_HLINE_TIME.u32 = hline_time;

    g_mipi_tx_regs_va->VID_VSA_LINES.u32 = dev_cfg->sync_info.vid_vsa_lines;
    g_mipi_tx_regs_va->VID_VBP_LINES.u32 = dev_cfg->sync_info.vid_vbp_lines;
    g_mipi_tx_regs_va->VID_VFP_LINES.u32 = dev_cfg->sync_info.vid_vfp_lines;
    g_mipi_tx_regs_va->VID_VACTIVE_LINES.u32 = dev_cfg->sync_info.vid_active_lines;

#ifdef MIPI_TX_DEBUG
    printf("VID_HSA_TIME(0x48): 0x%x\n", hsa_time);
    printf("VID_HBP_TIME(0x4c): 0x%x\n", hbp_time);
    printf("VID_HLINE_TIME(0x50): 0x%x\n", hline_time);
    printf("VID_VSA_LINES(0x54): 0x%x\n", dev_cfg->sync_info.vid_vsa_lines);
    printf("VID_VBP_LINES(0x58): 0x%x\n", dev_cfg->sync_info.vid_vbp_lines);
    printf("VID_VFP_LINES(0x5c): 0x%x\n", dev_cfg->sync_info.vid_vfp_lines);
    printf("VID_VACTIVE_LINES(0x60): 0x%x\n", dev_cfg->sync_info.vid_active_lines);
#endif
}

void set_lane_config(short lane_id[])
{
    int lane_num = 0;
    int i;
    U_LANE_ID lane_id_reg;

    for (i = 0; i < LANE_MAX_NUM; i++) {
        if (-1 != lane_id[i]) {
            lane_num++;
        }
    }

    g_mipi_tx_regs_va->PHY_IF_CFG.u32 = lane_num - 1;

    lane_id_reg.u32 = g_mipi_tx_regs_va->LANE_ID.u32;
    if (lane_id[0] >= 0) {
        lane_id_reg.bits.lane0_id = lane_id[0];
    }
    if (lane_id[1] >= 0) {
        lane_id_reg.bits.lane1_id = lane_id[1];
    }
    if (lane_id[2] >= 0) {
        lane_id_reg.bits.lane2_id = lane_id[2];
    }
    if (lane_id[3] >= 0) {
        lane_id_reg.bits.lane3_id = lane_id[3];
    }
    g_mipi_tx_regs_va->LANE_ID.u32 = lane_id_reg.u32;

#ifdef MIPI_TX_DEBUG
    printf("LANE_ID(0x250): 0x%x\n", lane_id_reg);
#endif
}

void mipi_tx_drv_set_controller_cfg(combo_dev_cfg_t *dev_cfg)
{
    /* vc_id */
    g_mipi_tx_regs_va->VCID.u32 = 0x0;

    /* output format */
    set_output_format(dev_cfg);

    /* txescclk,timeout */
    g_mipi_tx_regs_va->CLKMGR_CFG.u32 = 0x100 + (g_actual_phy_data_rate + 159) / 160;

    /* cmd transmission mode */
    if (dev_cfg->output_mode == OUTPUT_MODE_DSI_CMD) {
        g_mipi_tx_regs_va->CMD_MODE_CFG.u32 = 0x0;
    } else {
        g_mipi_tx_regs_va->CMD_MODE_CFG.u32 = 0xffffff00;
    }

    /* crc,ecc,eotp tran */
    g_mipi_tx_regs_va->PCKHDL_CFG.u32 = 0x1e;
    /* gen_vcid_rx */
    g_mipi_tx_regs_va->GEN_VCID.u32 = 0x0;

    /* mode config */
    g_mipi_tx_regs_va->MODE_CFG.u32 = 0x1;

    /* video mode cfg */
    set_video_mode_cfg(dev_cfg);
    if ((dev_cfg->output_mode == OUTPUT_MODE_DSI_VIDEO) || (dev_cfg->output_mode == OUTPUT_MODE_CSI)) {
        g_mipi_tx_regs_va->VID_PKT_SIZE.u32 = dev_cfg->sync_info.vid_pkt_size;
    } else {
        g_mipi_tx_regs_va->EDPI_CMD_SIZE.u32 = dev_cfg->sync_info.edpi_cmd_size;
    }

    /* num_chunks/null_size */
    g_mipi_tx_regs_va->VID_NUM_CHUNKS.u32 = 0x0;
    g_mipi_tx_regs_va->VID_NULL_SIZE.u32 = 0x0;

    /* timing config */
    set_timing_config(dev_cfg);

    /* invact,outvact time */
    g_mipi_tx_regs_va->LP_CMD_TIM.u32 = 0x0;

    /* lp_wr_to_cnt */
    g_mipi_tx_regs_va->LP_WR_TO_CNT.u32 = 0x0;
    /* bta_to_cnt */
    g_mipi_tx_regs_va->BTA_TO_CNT.u32 = 0x0;

    /* phy_txrequlpsclk */
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.u32 = 0x0;

    if (dev_cfg->output_mode == OUTPUT_MODE_CSI) {
        if (dev_cfg->output_format == OUT_FORMAT_YUV420_8_BIT_NORMAL) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x10218;
            g_mipi_tx_regs_va->DATATYPE1 = 0x31081909;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x1111;
        } else if (dev_cfg->output_format == OUT_FORMAT_YUV422_8_BIT) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x1021E;
            g_mipi_tx_regs_va->DATATYPE1 = 0x31081909;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x1111;
        }
    }

    /* pll status check program */
    udelay(100);
    mipi_tx_pll_status_check(dev_cfg);

    /* lanes */
    set_lane_config(dev_cfg->lane_id);

    g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x1;
}

void mipi_tx_drv_set_cmd_info(cmd_info_t *cmd_info)
{
    U_GEN_HDR gen_hdr;
    U_GEN_PLD_DATA gen_pld_data;
    unsigned char *cmd;
    int i, j;

    gen_hdr.u32 = g_mipi_tx_regs_va->GEN_HDR.u32;
    gen_pld_data.u32 = g_mipi_tx_regs_va->GEN_PLD_DATA.u32;

    if (cmd_info->cmd != NULL) {
        if (cmd_info->cmd_size > 800) {
            return;
        }

        cmd = (unsigned char *)malloc(cmd_info->cmd_size);
        if (cmd == NULL) {
            return;
        }

        memcpy(cmd, cmd_info->cmd, cmd_info->cmd_size);

        for (i = 0; i < (cmd_info->cmd_size / 4); i++) {
            gen_pld_data.bits.gen_pld_b1 = cmd[i * 4];
            gen_pld_data.bits.gen_pld_b2 = cmd[i * 4 + 1];
            gen_pld_data.bits.gen_pld_b3 = cmd[i * 4 + 2];
            gen_pld_data.bits.gen_pld_b4 = cmd[i * 4 + 3];

            g_mipi_tx_regs_va->GEN_PLD_DATA.u32 = gen_pld_data.u32;
        }

        j = cmd_info->cmd_size % 4;
        if (j != 0) {
            if (j > 0) {
                gen_pld_data.bits.gen_pld_b1 = cmd[i * 4];
            }
            if (j > 1) {
                gen_pld_data.bits.gen_pld_b2 = cmd[i * 4 + 1];
            }
            if (j > 2) {
                gen_pld_data.bits.gen_pld_b3 = cmd[i * 4 + 2];
            }
            g_mipi_tx_regs_va->GEN_PLD_DATA.u32 = gen_pld_data.u32;
        }

        free(cmd);
    }

    gen_hdr.bits.gen_dt = cmd_info->data_type;
    gen_hdr.bits.gen_wc_lsbyte = cmd_info->cmd_size & 0xff;
    gen_hdr.bits.gen_wc_msbyte = (cmd_info->cmd_size & 0xff00) >> 8;
    g_mipi_tx_regs_va->GEN_HDR.u32 = gen_hdr.u32;

#ifdef MIPI_TX_DEBUG
    printf("\n=====set cmd=======\n");
    printf("cmd_info->cmd_size: 0x%x\n", cmd_info->cmd_size);
    printf("cmd_info->data_type: 0x%x\n", cmd_info->data_type);
    printf("GEN_PLD_DATA(0x70): 0x%x\n", gen_pld_data);
    printf("GEN_HDR(0x6C): 0x%x\n", gen_hdr);
#endif
}

void mipi_tx_drv_enable_input(output_mode_t output_mode)
{
    if ((output_mode == OUTPUT_MODE_DSI_VIDEO) || (output_mode == OUTPUT_MODE_CSI)) {
        g_mipi_tx_regs_va->MODE_CFG.u32 = 0x0;
    }

    /* enable input */
    g_mipi_tx_regs_va->OPERATION_MODE.u32 = 0x80150000;
    // reset mipi_tx
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x0;
    udelay(1);
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x1;
}

static int mipi_tx_drv_reg_init(void)
{
    g_mipi_tx_regs_va = (mipi_tx_regs_type_t *)IO_ADDRESS(MIPI_TX_REGS_ADDR);

    return 0;
}

static void mipi_tx_drv_reg_exit(void)
{
}

static void mipi_tx_drv_hw_init(void)
{
    unsigned long mipi_tx_crg_addr;

    mipi_tx_crg_addr = (unsigned long)IO_ADDRESS(MIPI_TX_CRG);

    /* mipi_tx gate clk enable */
    write_reg32(mipi_tx_crg_addr, 1, 0x1);

    /* unreset */
    write_reg32(mipi_tx_crg_addr, 0, 0x1 << 2);

    /* ref clk */
    write_reg32(mipi_tx_crg_addr, 1 << 4, 0x1 << 4);
}

unsigned int mipi_tx_drv_get_phy_status_phy_lock(void)
{
    unsigned int u32phy_lock;

    u32phy_lock = g_mipi_tx_regs_va->PHY_STATUS.bits.phy_lock;
    return u32phy_lock;
}

int hal_phy_getphy_statusphy_stopstate_xlane(unsigned int x, unsigned int *phy_stopstate_xlane)
{
    U_PHY_STATUS phy_status;
    phy_status.u32 = g_mipi_tx_regs_va->PHY_STATUS.u32;
    switch (x) {
        // 0lane
        case 0:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate0lane;
            break;
        // 1lane
        case 1:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate1lane;
            break;
        // 2lane
        case 2:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate2lane;
            break;
        // 3lane
        case 3:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate3lane;
            break;
        default:
            // do nothing.
            break;
    }

    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txrequlpslan(unsigned int uphy_txrequlpslan)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txrequlpslan = uphy_txrequlpslan;
    return 1;
}

int hal_phy_getphy_statusphy_ulpsactivenot_xlane(unsigned int x, unsigned int *phy_ulpsactivenot_xlane)
{
    U_PHY_STATUS phy_status;
    phy_status.u32 = g_mipi_tx_regs_va->PHY_STATUS.u32;

    switch (x) {
        // 0lane
        case 0:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot0lane;
            break;
        // 1lane
        case 1:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot1lane;
            break;
        // 2lane
        case 2:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot2lane;
            break;
        // 3lane
        case 3:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot3lane;
            break;
        default:
            // do nothing.
            break;
    }
    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txexitulpslan(unsigned int uphy_txexitulpslan)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txexitulpslan = uphy_txexitulpslan;
    return 1;
}

int hal_phy_getphy_statusphy_ulpsactivenotclk(unsigned int *phy_ulpsactivenotclk)
{
    *phy_ulpsactivenotclk = g_mipi_tx_regs_va->PHY_STATUS.bits.phy_ulpsactivenotclk;
    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txrequlpsclk(unsigned int uphy_txrequlpsclk)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txrequlpsclk = uphy_txrequlpsclk;
    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txexitulpsclk(unsigned int uphy_txexitulpsclk)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txexitulpsclk = uphy_txexitulpsclk;
    return 1;
}

int mipi_tx_drv_get_phy_status_phy_stopstate_xlane(unsigned int xlane)
{
    unsigned int u32phy_stopstate_xlane = 0;

    hal_phy_getphy_statusphy_stopstate_xlane(xlane, &u32phy_stopstate_xlane);
    return u32phy_stopstate_xlane;
}

unsigned int mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(unsigned int xlane)
{
    unsigned int u32phy_ulpsactivenot_xlane = 0;

    hal_phy_getphy_statusphy_ulpsactivenot_xlane(xlane, &u32phy_ulpsactivenot_xlane);
    return u32phy_ulpsactivenot_xlane;
}

void mipi_tx_drv_set_ulps_mode(void)
{
    hal_phy_setphy_ulps_ctrlphy_txrequlpslan(0x1);
}

void mipi_tx_drv_exit_ulps_mode(void)
{
    hal_phy_setphy_ulps_ctrlphy_txrequlpslan(0x1);
    hal_phy_setphy_ulps_ctrlphy_txexitulpslan(0x1);
    hal_phy_setphy_ulps_ctrlphy_txrequlpsclk(0x0);
    hal_phy_setphy_ulps_ctrlphy_txexitulpsclk(0x0);
}

unsigned int mipi_tx_drv_get_phy_status_phy_stopstateclklane(void)
{
    unsigned int u32phy_ulpsactivenotclk = 0;

    hal_phy_getphy_statusphy_ulpsactivenotclk(&u32phy_ulpsactivenotclk);

    return u32phy_ulpsactivenotclk;
}

void mipi_tx_pll_status_check(combo_dev_cfg_t *dev_cfg)
{
    unsigned int i;
    unsigned int trytimes = 4;
    unsigned int pll_set12;
    int count = 0;

step2:
    // step2
    // step3
    i = 0;
    while (i < trytimes) {
        if (mipi_tx_drv_get_phy_status_phy_lock() == 1) {
            // check phy lock
            break;
        } else {
            udelay(5);
        }
        i++;
    }
    if (i == trytimes) {
        // reset phy
        count = mipi_tx_drv_reset_phy(dev_cfg);
        if (count == MIPI_TX_MAX_RESET_PHY_TIMES) {
            goto exit;
        }
        // goto step2
        goto step2;
    }

    // step 4
    i = 0;
    while (i < trytimes) {
        if ((mipi_tx_drv_get_phy_status_phy_stopstate_xlane(0) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(1) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(2) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(3) == 1)) {
            // check data lane stop status
            break;
        } else {
            udelay(5);
        }
        i++;
    }
    if (i == trytimes) {
        // reset phy
        count = mipi_tx_drv_reset_phy(dev_cfg);
        if (count == MIPI_TX_MAX_RESET_PHY_TIMES) {
            goto exit;
        }
        // goto step2
        goto step2;
    }

    // step 5
    mipi_tx_drv_set_ulps_mode();

    // step 6
    i = 0;
    while (i < trytimes) {
        if ((mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(0) == 0) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(1) == 0) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(2) == 0) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(3) == 0)) {
            // check data lane ulps status
            break;
        } else {
            udelay(5);
        }
        i++;
    }
    if (i == trytimes) {
        // reset phy
        count = mipi_tx_drv_reset_phy(dev_cfg);
        if (count == MIPI_TX_MAX_RESET_PHY_TIMES) {
            goto exit;
        }
        // goto step2
        goto step2;
    }

    // step 7 exit ulps mode
    mipi_tx_drv_exit_ulps_mode();

    // step 8
    i = 0;
    while (i < trytimes) {
        if ((mipi_tx_drv_get_phy_status_phy_stopstateclklane() == 1) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(0) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(1) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(2) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(3) == 1)) {
            // check clklane and datalane exit ulps mode.
            break;
        } else {
            udelay(5);
        }
        i++;
    }
    if (i == trytimes) {
        // reset phy
        count = mipi_tx_drv_reset_phy(dev_cfg);
        if (count == MIPI_TX_MAX_RESET_PHY_TIMES) {
            goto exit;
        }
        // goto step2
        goto step2;
    }

    // step 9
    hal_phy_setphy_ulps_ctrlphy_txrequlpslan(0x0);
    hal_phy_setphy_ulps_ctrlphy_txexitulpslan(0x0);
    hal_phy_setphy_ulps_ctrlphy_txrequlpsclk(0x0);
    hal_phy_setphy_ulps_ctrlphy_txexitulpsclk(0x0);

    // step 10
    i = 0;
    while (i < trytimes) {
        if ((mipi_tx_drv_get_phy_status_phy_stopstate_xlane(0) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(1) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(2) == 1) &&
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(3) == 1)) {
            // check phy lock
            break;
        } else {
            udelay(5);
        }
        i++;
    }
    if (i == trytimes) {
        // reset phy
        count = mipi_tx_drv_reset_phy(dev_cfg);
        if (count == MIPI_TX_MAX_RESET_PHY_TIMES) {
            goto exit;
        }
        // goto step2
        goto step2;
    }

    // step11
    pll_set12 = 0x20;
    set_phy_reg(PLL_SET12, pll_set12);

    // step 12
    pll_set12 = 0x0;
    set_phy_reg(PLL_SET12, pll_set12);
    printf("[%s][%d]check pll status success.\n", __FUNCTION__, __LINE__);
    return;

exit:
#ifdef MIPI_TX_DEBUG
    printf("[%s][%d]check pll status failed.\n", __FUNCTION__, __LINE__);
#endif
    return;
}

int mipi_tx_drv_init(void)
{
    int ret;

    ret = mipi_tx_drv_reg_init();
    if (ret < 0) {
        HI_ERR("mipi_tx_drv_reg_init fail!\n");
        goto fail0;
    }

    mipi_tx_drv_hw_init();

    return 0;

fail0:
    return -1;
}

void mipi_tx_drv_exit(void)
{
    mipi_tx_drv_reg_exit();
}

#ifdef __cplusplus
#if __cplusplus
}

#endif
#endif /* end of #ifdef __cplusplus */
