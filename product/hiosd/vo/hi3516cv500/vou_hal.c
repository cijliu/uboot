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

#ifdef __LINUX_OS__
#include <linux/kernel.h> /* printk */
#include <asm/hardware.h> /* IO_ADDRESS */
#include <asm/io.h>       /* ioremap_nocache */
#include <linux/delay.h>  /* for ndelay(ns) */
#else
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <version.h>
#include <net.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#endif

#include "vou_hal.h"

#include "hi3519av100_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

/****************************************************************************
 * MACRO DEFINITION                                                         *
 ****************************************************************************/
#define HAL_PRINT     printf
#define IO_ADDRESS(x) (x)

#define HI_INVALID_LAYER (-1)

/***************************************/
#define CRG_REGS_ADDR 0x12010000
#define CRG_REGS_SIZE 0X10000

#define CRG_PERCTL2_ADDR (0x0008 + CRG_REGS_ADDR)
#define CRG_PERCTL3_ADDR (0x000C + CRG_REGS_ADDR)
#define CRG_PERCTL4_ADDR (0x0010 + CRG_REGS_ADDR)
#define CRG_PERCTL5_ADDR (0x0014 + CRG_REGS_ADDR)
#define CRG_PERCTL6_ADDR (0x0018 + CRG_REGS_ADDR)
#define CRG_PERCTL7_ADDR (0x001c + CRG_REGS_ADDR)

#define CRG_PERCTL10_ADDR (0x0028 + CRG_REGS_ADDR)
#define CRG_PERCTL11_ADDR (0x002c + CRG_REGS_ADDR)
#define CRG_PERCTL18_ADDR (0x0048 + CRG_REGS_ADDR)

#define CRG_PERCTL19_ADDR (0x004c + CRG_REGS_ADDR)
#define CRG_PERCTL59_ADDR (0x00ec + CRG_REGS_ADDR)

#define CRG_PERCTL65_ADDR (0x0104 + CRG_REGS_ADDR) /* LCD CRG */
#define CRG_PERCTL66_ADDR (0x0108 + CRG_REGS_ADDR) /* VDP low power CRG */
#define CRG_PERCTL72_ADDR (0x0120 + CRG_REGS_ADDR)
#define CRG_PERCTL73_ADDR (0x0124 + CRG_REGS_ADDR) /* VDP CRG */
#define CRG_PERCTL15_ADDR (0x003C + CRG_REGS_ADDR)

#define LCD_CRG_PERCTL_ADDR CRG_PERCTL65_ADDR
#define VOU_CRG_PERCTL_ADDR CRG_PERCTL66_ADDR

#define MISC_REGS_ADDR 0x12030000
#define MISC_REGS_SIZE 0x8000

#define MISC_CTL18_ADDR (0x18 + MISC_REGS_ADDR)

/****************************************************************************
 * GLOBAL VARIABLES                                                         *
 ****************************************************************************/
volatile S_VDP_REGS_TYPE *g_vo_reg = NULL;

/*****************************************************************************
 prototype         : hal initial
 description     :

*****************************************************************************/
hi_void hal_vo_init(hi_void)
{
    g_vo_reg = (volatile S_VDP_REGS_TYPE *)IO_ADDRESS(VO_BASE_ADDR);
}

hi_void hal_vo_exit(hi_void)
{
}

static inline void hi_reg_set_bit(unsigned long value, unsigned long offset,
                                unsigned long addr)
{
    unsigned long t, mask;

    mask = 1 << offset;
    t = readl(addr);
    t &= ~mask;
    t |= (value << offset) & mask;
    writel(t, addr);
}

static inline void hi_reg_write32(unsigned long value, unsigned long mask,
                                 unsigned long addr)
{
    unsigned long t;

    t = readl(addr);
    t &= ~mask;
    t |= value & mask;
    writel(t, addr);
}

hi_void hal_write_reg(hi_u32 *address, hi_u32 value)
{
    *(volatile hi_u32 *)address = value;
    return;
}

hi_u32 hal_read_reg(hi_u32 *address)
{
    return *(volatile hi_u32 *)(address);
}

hi_s32 sys_hal_sel_vo_bt1120_pin_conifg(hi_void)
{
    return 0;
}

hi_bool hal_intf_bt_set_dfir_en(hi_u32 dfir_en)
{
    U_INTF_BT_CTRL INTF_BT_CTRL;

    INTF_BT_CTRL.u32 = hal_read_reg((hi_u32 *)(hi_ulong) & (g_vo_reg->INTF_BT_CTRL.u32));
    INTF_BT_CTRL.bits.dfir_en = dfir_en;
    hal_write_reg ((hi_u32 *)(hi_ulong) & (g_vo_reg->INTF_BT_CTRL.u32), INTF_BT_CTRL.u32);

    return HI_TRUE;
}

hi_ulong vo_get_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            reg_abs_addr = (reg) + (layer - HAL_DISP_LAYER_VHD0) * VHD_REGS_LEN;
            break;
        }

        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            reg_abs_addr = (reg) + (layer - HAL_DISP_LAYER_GFX0) * GFX_REGS_LEN;
            break;
        }

        // one wbc dev
        case HAL_DISP_LAYER_WBC:
            reg_abs_addr = (reg);
            break;

        default: {
            return 0;
        }
    }

    return reg_abs_addr;
}

hi_ulong vo_get_chn_abs_addr(hal_disp_outputchannel chan, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            reg_abs_addr = reg + (chan - HAL_DISP_CHANNEL_DHD0) * DHD_REGS_LEN;
            break;
        }

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }

    return reg_abs_addr;
}

hi_s32 sys_hal_vo_bus_reset_sel(hi_bool reset)
{
    hi_u32 tmp = (reset == HI_TRUE) ? 1 : 0;
    hi_reg_set_bit(tmp, 0, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_apb_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;
    hi_reg_set_bit(tmp, 1, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_bus_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;
    hi_reg_set_bit(tmp, 2, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_cfg_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;
    hi_reg_set_bit(tmp, 3, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_dev_clk_en(hi_s32 vo_dev, hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if (vo_dev == 0) {
        hi_reg_set_bit(tmp, 5, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));
        hi_reg_set_bit(tmp, 6, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));
    } else {
        return -1;
    }

    return 0;
}

hi_s32 sys_hal_vo_bt_clk_en(hi_bool bt_clk_en)
{
    hi_u32 tmp = (bt_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 8, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));
    hi_reg_set_bit(tmp, 9, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_hdmi_clk_en(hi_bool hdmi_clk_en)
{
    hi_u32 tmp = (hdmi_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 10, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));
    hi_reg_set_bit(tmp, 18, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_mipi_clk_en(hi_bool mipi_clk_en)
{
    hi_u32 tmp = (mipi_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 11, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));
    hi_reg_set_bit(tmp, 19, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_hd0_div_mode(hi_u32 hd0_div_mod)
{
    hi_reg_write32(hd0_div_mod << 12, 0x3 << 12, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_hd_clk_sel(hi_u32 clk_sel)
{
    hi_reg_write32(clk_sel << 14, 0x1 << 14, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_hd_out_pctrl(hi_bool clk_reverse)
{
    hi_u32 tmp = (clk_reverse == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 20, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_out_clk_sel(hi_u32 clk_sel)
{
    hi_reg_write32(clk_sel << 21, 0xf << 21, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_hd_hdmi_clk_div(hi_u32 hdmi_clk_div)
{
    hi_reg_write32(hdmi_clk_div << 25, 0x1f << 25, IO_ADDRESS(VOU_CRG_PERCTL_ADDR));

    return 0;
}

hi_bool hal_disp_set_intvsync_te_mode(hal_disp_outputchannel chan, hi_bool slave)
{
    volatile U_DHD0_PRECHARGE_THD DHD0_PRECHARGE_THD;
    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_PRECHARGE_THD.u32));
            DHD0_PRECHARGE_THD.u32 = hal_read_reg((hi_u32 *)addr_reg);

            DHD0_PRECHARGE_THD.bits.vsync_te_mode = slave;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_PRECHARGE_THD.u32);
            break;
        }

        default: {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_s32 sys_hal_vo_lcd_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 27, IO_ADDRESS(LCD_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_lcd_mclk_div(hi_u32 mclk_div)
{
    hi_reg_write32(mclk_div, 0x7ffffff, IO_ADDRESS(LCD_CRG_PERCTL_ADDR));

    return 0;
}

hi_s32 sys_hal_lcd_data_mode(hi_u32 data_mode)
{
    hi_reg_write32(data_mode << 8, 0x7 << 26, IO_ADDRESS(MISC_CTL18_ADDR));

    return 0;
}

hi_s32 sys_hal_set_vo_pll_frac(hi_u32 bits_set)
{
    hi_reg_write32(bits_set << 0, 0xffffff << 0, IO_ADDRESS(CRG_PERCTL6_ADDR));

    return 0;
}

hi_s32 sys_hal_set_vo_pll_postdiv1(hi_u32 bits_set)
{
    hi_reg_write32(bits_set << 24, 0x7 << 24, IO_ADDRESS(CRG_PERCTL6_ADDR));

    return 0;
}

hi_s32 sys_hal_set_vo_pll_postdiv2(hi_u32 bits_set)
{
    hi_reg_write32(bits_set << 28, 0x7 << 28, IO_ADDRESS(CRG_PERCTL6_ADDR));

    return 0;
}

hi_s32 sys_hal_set_vo_pll_refdiv(hi_u32 bits_set)
{
    hi_reg_write32(bits_set << 12, 0x3f << 12, IO_ADDRESS(CRG_PERCTL7_ADDR));

    return 0;
}

hi_s32 sys_hal_set_vo_pll_fbdiv(hi_u32 bits_set)
{
    hi_reg_write32(bits_set << 0, 0xfff << 0, IO_ADDRESS(CRG_PERCTL7_ADDR));

    return 0;
}

hi_s32 sys_hal_set_vo_s_pll_frac(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 0, 0xffffff << 0, IO_ADDRESS(CRG_PERCTL18_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, 24, IO_ADDRESS(CRG_PERCTL19_ADDR));
        } else {
            hi_reg_set_bit(0, 24, IO_ADDRESS(CRG_PERCTL19_ADDR));
        }
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 0, 0xffffff << 0, IO_ADDRESS(CRG_PERCTL18_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, 24, IO_ADDRESS(CRG_PERCTL19_ADDR));
        } else {
            hi_reg_set_bit(0, 24, IO_ADDRESS(CRG_PERCTL19_ADDR));
        }
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_s_pll_postdiv1(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 24, 0x7 << 24, IO_ADDRESS(CRG_PERCTL18_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 24, 0x7 << 24, IO_ADDRESS(CRG_PERCTL18_ADDR));
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_s_pll_postdiv2(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 28, 0x7 << 28, IO_ADDRESS(CRG_PERCTL18_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 28, 0x7 << 28, IO_ADDRESS(CRG_PERCTL18_ADDR));
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_s_pll_refdiv(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 12, 0x3f << 12, IO_ADDRESS(CRG_PERCTL19_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 12, 0x3f << 12, IO_ADDRESS(CRG_PERCTL19_ADDR));
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_s_pll_fbdiv(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 0, 0xfff << 0, IO_ADDRESS(CRG_PERCTL19_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 0, 0xfff << 0, IO_ADDRESS(CRG_PERCTL19_ADDR));
    } else {
        return -1;
    }
    return 0;
}

hi_s32 sys_hal_set_vo_low_power_ctrl(hi_bool low_power_clk_en)
{
    return 0;
}

hi_void hal_sys_control(hi_void)
{
    volatile U_VOCTRL VOCTRL;

    /* outstand */
    VOCTRL.u32 = g_vo_reg->VOCTRL.u32;
    VOCTRL.u32 = 0x80000000;
    g_vo_reg->VOCTRL.u32 = VOCTRL.u32;
}

hi_u32 inline hal_get_xdc_buma(hi_s32 value)
{
    hi_u32 abs_value = value << 2;

    if (value >= 0) {
        return abs_value & 0x7ff;
    } else {
        abs_value = (~((-1) * abs_value) + 1);
        abs_value = ((abs_value & 0x7ff) | 0x400);
        return abs_value;
    }
}

hi_u32 inline hal_conver_csc_coef(hi_s32 value)
{
    hi_s32 result = ((value << 10) / 1000);

    if (result < 0) {
        result = (~((-1) * result) + 1);

        /* 5.8 format */
        result = ((result & 0x7fff) | 0x4000);
    } else {
        result = result & 0x7fff;
    }

    return result;
}

hi_ulong vo_get_hdmi_or_mipi_intf_abs_addr(hal_disp_intf intf, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (intf) {
        case HAL_DISP_INTF_HDMI: {
            reg_abs_addr = reg;
            break;
        }

        case HAL_DISP_INTF_MIPI: {
            reg_abs_addr = reg + 0x80;  // reg INTF_MIPI_CTRL's offset ralative reg INTF_HDMI_CTRL
            break;
        }
        default: {
            return 0;
        }
    }

    return reg_abs_addr;
}

// for get intf abs addr
hi_ulong vo_get_intf_abs_addr(hal_disp_intf intf, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (intf) {
        case HAL_DISP_INTF_HDMI: {
            reg_abs_addr = reg;
            break;
        }

        case HAL_DISP_INTF_MIPI: {
            reg_abs_addr = reg + 0x80;  // reg INTF_MIPI_CTRL's offset ralative reg INTF_HDMI_CTRL
            break;
        }

        case HAL_DISP_INTF_BT656:
        case HAL_DISP_INTF_BT1120: {
            reg_abs_addr = reg + 1 * INTF_REGS_LEN;
            break;
        }

        case HAL_DISP_INTF_LCD:
        case HAL_DISP_INTF_LCD_6BIT:
        case HAL_DISP_INTF_LCD_8BIT:
        case HAL_DISP_INTF_LCD_16BIT:
        case HAL_DISP_INTF_LCD_24BIT: {
            reg_abs_addr = reg + 2 * INTF_REGS_LEN;
            break;
        }

        default: {
            printf("error intf id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }
    return reg_abs_addr;
}

/*
* name : vo_get_vid_abs_addr
* desc : VID means vi_deo,related to video's input resolution,
         video's luma address,video's chrom address,video's data fmt,
**/
hi_ulong vo_get_vid_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_VHD0) * VID_REGS_LEN;
            break;
        }

        case HAL_DISP_LAYER_WBC:
            reg_abs_addr = reg;
            break;

        default: {
            return 0;
        }
    }

    return reg_abs_addr;
}

/*
* name : vo_get_gfx_abs_addr
* desc : GFX means graphics,related to graphics' input resolution,
         graphics' luma address,graphics' chrom address,graphics' data fmt,
**/
hi_ulong vo_get_gfx_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_GFX0) * GRF_REGS_LEN;
            break;
        }
        default: {
            return 0;
        }
    }

    return reg_abs_addr;
}

hi_bool hal_disp_set_lcd_serial_perd(hi_u32 u32SerialPerd)
{
    U_INTF_LCD_CTRL   INTF_LCD_CTRL;
    volatile hi_ulong    addr_reg;

    addr_reg   = vo_get_intf_abs_addr(HAL_DISP_INTF_LCD_8BIT, (hi_ulong) & (g_vo_reg->INTF_HDMI_CTRL.u32));
    INTF_LCD_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);

    INTF_LCD_CTRL.bits.lcd_serial_perd    = u32SerialPerd;

    hal_write_reg((hi_u32*)addr_reg, INTF_LCD_CTRL.u32);
    return HI_TRUE;
}

hi_bool hal_disp_set_intf_enable(hal_disp_outputchannel chan, hi_bool intf)
{
    volatile U_DHD0_CTRL DHD0_CTRL;
    volatile hi_ulong addr_reg;
    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_CTRL.u32));
            DHD0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_CTRL.bits.intf_en = intf;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_CTRL.u32);
            break;
        }

        default: {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_ctrl(hal_disp_intf intf, hi_u32 *ctrl_info)
{
    U_INTF_HDMI_CTRL INTF_HDMI_CTRL;
    U_INTF_BT_CTRL INTF_BT_CTRL;
    U_INTF_LCD_CTRL INTF_LCD_CTRL;
    volatile hi_ulong addr_reg;
    U_INTF_HDMI_CTRL *hdmi_ctrl;
    U_INTF_BT_CTRL *bt_ctrl;
    U_INTF_LCD_CTRL *lcd_ctrl;

    if ((intf == VO_INTF_BT1120) ||
        (intf == VO_INTF_BT656)) {
        bt_ctrl = (U_INTF_BT_CTRL *)ctrl_info;
        addr_reg = vo_get_intf_abs_addr(intf, (hi_ulong) & (g_vo_reg->INTF_HDMI_CTRL.u32));
        INTF_BT_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        INTF_BT_CTRL.bits.hdmi_mode = bt_ctrl->bits.hdmi_mode;
        INTF_BT_CTRL.bits.lcd_serial_mode = bt_ctrl->bits.lcd_serial_mode;
        INTF_BT_CTRL.bits.lcd_serial_perd = bt_ctrl->bits.lcd_serial_perd;
        INTF_BT_CTRL.bits.lcd_parallel_order = bt_ctrl->bits.lcd_parallel_order;
        INTF_BT_CTRL.bits.lcd_data_inv = bt_ctrl->bits.lcd_data_inv;
        INTF_BT_CTRL.bits.lcd_parallel_mode = bt_ctrl->bits.lcd_parallel_mode;
        hal_write_reg((hi_u32 *)addr_reg, INTF_BT_CTRL.u32);
    } else if ((intf == VO_INTF_LCD) ||
           (intf == VO_INTF_LCD_6BIT) ||
           (intf == VO_INTF_LCD_8BIT) ||
           (intf == VO_INTF_LCD_16BIT) ||
           (intf == VO_INTF_LCD_18BIT) ||
           (intf == VO_INTF_LCD_24BIT)) {
        lcd_ctrl = (U_INTF_LCD_CTRL *)ctrl_info;
        addr_reg = vo_get_intf_abs_addr(intf, (hi_ulong) & (g_vo_reg->INTF_HDMI_CTRL.u32));
        INTF_LCD_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        INTF_LCD_CTRL.bits.hdmi_mode = lcd_ctrl->bits.hdmi_mode;
        INTF_LCD_CTRL.bits.lcd_serial_mode = lcd_ctrl->bits.lcd_serial_mode;
        INTF_LCD_CTRL.bits.lcd_serial_perd = lcd_ctrl->bits.lcd_serial_perd;
        INTF_LCD_CTRL.bits.lcd_parallel_order = lcd_ctrl->bits.lcd_parallel_order;
        INTF_LCD_CTRL.bits.lcd_data_inv = lcd_ctrl->bits.lcd_data_inv;
        INTF_LCD_CTRL.bits.lcd_parallel_mode = lcd_ctrl->bits.lcd_parallel_mode;
        hal_write_reg((hi_u32 *)addr_reg, INTF_LCD_CTRL.u32);
    } else if ((intf == VO_INTF_HDMI) ||
           (intf == VO_INTF_MIPI)) {
        hdmi_ctrl = (U_INTF_HDMI_CTRL *)ctrl_info;
        addr_reg = vo_get_hdmi_or_mipi_intf_abs_addr(intf, (hi_ulong) & (g_vo_reg->INTF_HDMI_CTRL.u32));
        INTF_HDMI_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        INTF_HDMI_CTRL.bits.hdmi_mode = hdmi_ctrl->bits.hdmi_mode;
        INTF_HDMI_CTRL.bits.intf_420_mode = hdmi_ctrl->bits.intf_420_mode;
        INTF_HDMI_CTRL.bits.intf_420_en = hdmi_ctrl->bits.intf_420_en;
        INTF_HDMI_CTRL.bits.intf_422_en = hdmi_ctrl->bits.intf_422_en;
        hal_write_reg((hi_u32 *)addr_reg, INTF_HDMI_CTRL.u32);
    } else {
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_sync(hal_disp_outputchannel chan,
                             hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    volatile U_DHD0_CTRL DHD0_CTRL;
    volatile U_DHD0_VSYNC1 DHD0_VSYNC1;
    volatile U_DHD0_VSYNC2 DHD0_VSYNC2;
    volatile U_DHD0_HSYNC1 DHD0_HSYNC1;
    volatile U_DHD0_HSYNC2 DHD0_HSYNC2;
    volatile U_DHD0_VPLUS1 DHD0_VPLUS1;
    volatile U_DHD0_VPLUS2 DHD0_VPLUS2;
    volatile U_DHD0_PWR DHD0_PWR;

    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_CTRL.u32));
            DHD0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_CTRL.bits.iop = sync_info->iop;
            DHD0_CTRL.bits.intf_ihs = inv->hs_inv;
            DHD0_CTRL.bits.intf_ivs = inv->vs_inv;
            DHD0_CTRL.bits.intf_idv = inv->dv_inv;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_CTRL.u32);

            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_HSYNC1.u32));
            DHD0_HSYNC1.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_HSYNC1.bits.hact = sync_info->hact - 1;
            DHD0_HSYNC1.bits.hbb = (sync_info->hbb) - 1;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_HSYNC1.u32);

            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_HSYNC2.u32));
            DHD0_HSYNC2.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_HSYNC2.bits.hmid = (sync_info->hmid == 0) ? 0 : sync_info->hmid - 1;
            DHD0_HSYNC2.bits.hfb = (sync_info->hfb) - 1;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_HSYNC2.u32);

            // config VHD interface veritical timming
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_VSYNC1.u32));
            DHD0_VSYNC1.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_VSYNC1.bits.vact = sync_info->vact - 1;
            DHD0_VSYNC1.bits.vbb = sync_info->vbb - 1;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_VSYNC1.u32);

            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_VSYNC2.u32));
            DHD0_VSYNC2.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_VSYNC2.bits.vfb = sync_info->vfb - 1;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_VSYNC2.u32);

            // config VHD interface veritical bottom timming,no use in progressive mode
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_VPLUS1.u32));
            DHD0_VPLUS1.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_VPLUS1.bits.bvact = sync_info->bvact - 1;
            DHD0_VPLUS1.bits.bvbb = sync_info->bvbb - 1;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_VPLUS1.u32);

            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_VPLUS2.u32));
            DHD0_VPLUS2.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_VPLUS2.bits.bvfb = sync_info->bvfb - 1;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_VPLUS2.u32);

            // config VHD interface veritical bottom timming,
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_PWR.u32));
            DHD0_PWR.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_PWR.bits.hpw = sync_info->hpw - 1;
            DHD0_PWR.bits.vpw = sync_info->vpw - 1;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_PWR.u32);

            break;
        }

        default: {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_dev_multi_chn_en(hal_disp_outputchannel chn, HAL_MULTICHN_EN multi_chn_en)
{
    volatile U_DHD0_PWR DHD0_PWR;
    volatile hi_ulong addr_reg;
    addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->DHD0_PWR.u32));
    DHD0_PWR.u32 = hal_read_reg((hi_u32 *)addr_reg);
    DHD0_PWR.bits.multichn_en = multi_chn_en;
    hal_write_reg((hi_u32 *)addr_reg, DHD0_PWR.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_sync_inv(hal_disp_intf intf, hal_disp_syncinv *inv)
{
    volatile U_INTF_HDMI_SYNC_INV INTF_HDMI_SYNC_INV;
    volatile hi_ulong addr_reg;
    addr_reg = vo_get_intf_abs_addr(intf, (hi_ulong) & (g_vo_reg->INTF_HDMI_SYNC_INV.u32));
    INTF_HDMI_SYNC_INV.u32 = hal_read_reg((hi_u32 *)addr_reg);
    INTF_HDMI_SYNC_INV.bits.f_inv = inv->f_inv;
    INTF_HDMI_SYNC_INV.bits.vs_inv = inv->vs_inv;
    INTF_HDMI_SYNC_INV.bits.hs_inv = inv->hs_inv;
    INTF_HDMI_SYNC_INV.bits.dv_inv = inv->dv_inv;
    hal_write_reg((hi_u32 *)addr_reg, INTF_HDMI_SYNC_INV.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_mux_sel(hal_disp_outputchannel chan, hal_disp_intf intf)
{
    volatile U_VO_MUX VO_MUX;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong) & (g_vo_reg->VO_MUX.u32);
    VO_MUX.u32 = hal_read_reg((hi_u32 *)addr_reg);

    switch (intf) {
        case HAL_DISP_INTF_BT1120: {
            VO_MUX.bits.digital_sel = 0;
            VO_MUX.bits.bt_sel = 0;
            VO_MUX.bits.lcd_sel = 3;
            VO_MUX.bits.mipi_sel = 3;
            break;
        }

        case HAL_DISP_INTF_BT656: {
            VO_MUX.bits.digital_sel = 1;
            VO_MUX.bits.bt_sel = 0;
            VO_MUX.bits.lcd_sel = 3;
            VO_MUX.bits.mipi_sel = 3;
            break;
        }

        case HAL_DISP_INTF_LCD:
        case HAL_DISP_INTF_LCD_6BIT:
        case HAL_DISP_INTF_LCD_8BIT:
        case HAL_DISP_INTF_LCD_16BIT:
        case HAL_DISP_INTF_LCD_24BIT: {
            VO_MUX.bits.digital_sel = 2;
            VO_MUX.bits.bt_sel = 3;
            VO_MUX.bits.lcd_sel = 1;
            VO_MUX.bits.mipi_sel = 3;
            break;
        }

        case HAL_DISP_INTF_MIPI: {
            VO_MUX.bits.digital_sel = 3;
            VO_MUX.bits.bt_sel = 3;
            VO_MUX.bits.lcd_sel = 3;
            VO_MUX.bits.mipi_sel = 0;
            break;
        }

        default: {
            VO_MUX.bits.digital_sel = 15;
            VO_MUX.bits.bt_sel = 3;
            VO_MUX.bits.lcd_sel = 3;
            VO_MUX.bits.mipi_sel = 3;
        }
    }

    hal_write_reg((hi_u32 *)&(g_vo_reg->VO_MUX.u32), VO_MUX.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_csc_en(hal_disp_intf intf, hi_bool csc_en)
{
    return HI_TRUE;
}

hi_bool hal_disp_set_intf_clip(hal_disp_intf intf,
                             hi_bool clip,
                             hal_disp_clip *clip_data)
{
    volatile U_BT_CLIP0_L BT_CLIP0_L;
    volatile U_BT_CLIP0_H BT_CLIP0_H;

    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong) & (g_vo_reg->BT_CLIP0_L.u32);
    BT_CLIP0_L.u32 = hal_read_reg((hi_u32 *)addr_reg);
    BT_CLIP0_L.bits.clip_en = clip;
    BT_CLIP0_L.bits.clip_cl2 = clip_data->clip_low_y;
    BT_CLIP0_L.bits.clip_cl1 = clip_data->clip_low_cb;
    BT_CLIP0_L.bits.clip_cl0 = clip_data->clip_low_cr;
    hal_write_reg((hi_u32 *)addr_reg, BT_CLIP0_L.u32);

    addr_reg = (hi_ulong) & (g_vo_reg->BT_CLIP0_H.u32);
    BT_CLIP0_H.u32 = hal_read_reg((hi_u32 *)addr_reg);
    BT_CLIP0_H.bits.clip_ch2 = clip_data->clip_high_y;
    BT_CLIP0_H.bits.clip_ch1 = clip_data->clip_high_cb;
    BT_CLIP0_H.bits.clip_ch0 = clip_data->clip_high_cr;
    hal_write_reg((hi_u32 *)addr_reg, BT_CLIP0_H.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_vt_thd_mode(hal_disp_outputchannel chan, hi_u32 u_field_mode)
{
    volatile U_DHD0_VTTHD DHD0_VTTHD;
    volatile U_WBC_DHD0_CTRL WBC_DHD0_CTRL;
    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_VTTHD.u32));
            DHD0_VTTHD.u32 = hal_read_reg((hi_u32 *)addr_reg);

            DHD0_VTTHD.bits.thd1_mode = u_field_mode;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_VTTHD.u32);
            break;
        }

        case HAL_DISP_CHANNEL_WBC: {
            addr_reg = (hi_ulong) & (g_vo_reg->WBC_DHD0_CTRL.u32);
            WBC_DHD0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            WBC_DHD0_CTRL.bits.mode_out = u_field_mode;
            hal_write_reg((hi_u32 *)addr_reg, WBC_DHD0_CTRL.u32);
            break;
        }

        default: {
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

hi_bool hal_disp_set_vt_thd(hal_disp_outputchannel chan, hi_u32 vtthd)
{
    volatile U_DHD0_VTTHD DHD0_VTTHD;
    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_VTTHD.u32));
            DHD0_VTTHD.u32 = hal_read_reg((hi_u32 *)addr_reg);
            DHD0_VTTHD.bits.vtmgthd1 = vtthd;
            hal_write_reg((hi_u32 *)addr_reg, DHD0_VTTHD.u32);
            break;
        }

        default: {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_int_mask(hi_u32 mask_en)
{
    volatile U_VOINTMSK VOINTMSK;
    /* dispaly interrupt mask enable */
    VOINTMSK.u32 = hal_read_reg((hi_u32 *)&(g_vo_reg->VOINTMSK.u32));
    VOINTMSK.u32 = VOINTMSK.u32 | mask_en;
    hal_write_reg((hi_u32 *)&(g_vo_reg->VOINTMSK.u32), VOINTMSK.u32);

    return HI_TRUE;
}

hi_bool hal_disp_clr_int_mask(hi_u32 mask_en)
{
    volatile U_VOINTMSK VOINTMSK;

    /* dispaly interrupt mask enable */
    VOINTMSK.u32 = hal_read_reg((hi_u32 *)&(g_vo_reg->VOINTMSK.u32));
    VOINTMSK.u32 = VOINTMSK.u32 & (~mask_en);
    hal_write_reg((hi_u32 *)&(g_vo_reg->VOINTMSK.u32), VOINTMSK.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_int_mask1(hi_u32 mask_en)
{
    volatile U_VOINTMSK1 VOINTMSK1;
    /* dispaly interrupt mask enable */
    VOINTMSK1.u32 = hal_read_reg((hi_u32 *)&(g_vo_reg->VOINTMSK1.u32));
    VOINTMSK1.u32 = VOINTMSK1.u32 | mask_en;

    hal_write_reg((hi_u32 *)&(g_vo_reg->VOINTMSK1.u32), VOINTMSK1.u32);
    VOINTMSK1.u32 = hal_read_reg((hi_u32 *)&(g_vo_reg->VOINTMSK1.u32));

    return HI_TRUE;
}

hi_bool hal_disp_clr_int_mask1(hi_u32 mask_en)
{
    volatile U_VOINTMSK1 VOINTMSK1;

    /* dispaly interrupt mask enable */
    VOINTMSK1.u32 = hal_read_reg((hi_u32 *)&(g_vo_reg->VOINTMSK1.u32));
    VOINTMSK1.u32 = VOINTMSK1.u32 & (~mask_en);
    hal_write_reg((hi_u32 *)&(g_vo_reg->VOINTMSK1.u32), VOINTMSK1.u32);

    return HI_TRUE;
}

hi_void hal_disp_set_reg_up(hal_disp_outputchannel chan)
{
    volatile U_DHD0_CTRL DHD0_CTRL;
    volatile hi_ulong addr_reg;

    if (chan > HAL_DISP_CHANNEL_DHD1) {
        printf("error,hal_disp_set_reg_up select wrong CHANNEL ID\n");
        return;
    }

    // if wbc?
    // if DHD0 or DHD1
    addr_reg = vo_get_chn_abs_addr(chan, (hi_ulong) & (g_vo_reg->DHD0_CTRL.u32));
    DHD0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
    DHD0_CTRL.bits.regup = 0x1;
    hal_write_reg((hi_u32 *)addr_reg, DHD0_CTRL.u32);
    return;
}

hi_bool hal_video_set_layer_up_mode(hal_disp_layer layer, hi_u32 up_mode)
{
    U_V0_CTRL V0_CTRL;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_CTRL.u32));
            V0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_CTRL.bits.rgup_mode = up_mode;
            hal_write_reg((hi_u32 *)addr_reg, V0_CTRL.u32);
            break;
        }

        default: {
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

hi_void hal_video_hfir_set_ck_gt_en(hal_disp_layer layer, hi_u32 ck_gt_en)
{
    U_V0_HFIR_CTRL V0_HFIR_CTRL;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HFIR_CTRL.u32));
        V0_HFIR_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HFIR_CTRL.bits.ck_gt_en = ck_gt_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_HFIR_CTRL.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_out_height(hal_disp_layer layer, hi_u32 out_height)
{
    U_V0_CVFIR_VINFO V0_CVFIR_VINFO;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VINFO.u32));
        V0_CVFIR_VINFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VINFO.bits.out_height = out_height - 1;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VINFO.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_out_fmt(hal_disp_layer layer, hi_u32 out_fmt)
{
    U_V0_CVFIR_VINFO V0_CVFIR_VINFO;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VINFO.u32));
        V0_CVFIR_VINFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VINFO.bits.out_fmt = out_fmt;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VINFO.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_out_pro(hal_disp_layer layer, hi_u32 out_pro)
{
    U_V0_CVFIR_VINFO V0_CVFIR_VINFO;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VINFO.u32));
        V0_CVFIR_VINFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VINFO.bits.out_pro = out_pro;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VINFO.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_vzme_ck_gt_en(hal_disp_layer layer, hi_bool vzme_ck_gt_en)
{
    U_V0_CVFIR_VINFO V0_CVFIR_VINFO;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VINFO.u32));
        V0_CVFIR_VINFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VINFO.bits.vzme_ck_gt_en = vzme_ck_gt_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VINFO.u32);
    }

    return;
}

/* VSP */
hi_void hal_video_cvfir_set_cvfir_en(hal_disp_layer layer, hi_u32 cvfir_en)
{
    U_V0_CVFIR_VSP V0_CVFIR_VSP;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VSP.u32));
        V0_CVFIR_VSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VSP.bits.cvfir_en = cvfir_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VSP.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_cvmid_en(hal_disp_layer layer, hi_u32 cvmid_en)
{
    U_V0_CVFIR_VSP V0_CVFIR_VSP;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VSP.u32));
        V0_CVFIR_VSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VSP.bits.cvmid_en = cvmid_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VSP.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_cvfir_mode(hal_disp_layer layer, hi_u32 cvfir_mode)
{
    U_V0_CVFIR_VSP V0_CVFIR_VSP;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VSP.u32));
        V0_CVFIR_VSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VSP.bits.cvfir_mode = cvfir_mode;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VSP.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_vratio(hal_disp_layer layer, hi_u32 vratio)
{
    U_V0_CVFIR_VSP V0_CVFIR_VSP;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VSP.u32));
        V0_CVFIR_VSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VSP.bits.vratio = vratio;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VSP.u32);
    }

    return;
}

hi_void hal_video_cvfir_set_v_chroma_offset(hal_disp_layer layer, hi_u32 vchroma_offset)
{
    U_V0_CVFIR_VOFFSET V0_CVFIR_VOFFSET;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VOFFSET.u32));
        V0_CVFIR_VOFFSET.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VOFFSET.bits.vchroma_offset = vchroma_offset;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VOFFSET.u32);
    }

    return;
}

/* VBOFFSET */
hi_void hal_video_cvfir_set_vb_chroma_offset(hal_disp_layer layer, hi_u32 vbchroma_offset)
{
    U_V1_CVFIR_VBOFFSET V0_CVFIR_VBOFFSET;
    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_CVFIR_VBOFFSET.u32));
        V0_CVFIR_VBOFFSET.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_CVFIR_VBOFFSET.bits.vbchroma_offset = vbchroma_offset;
        hal_write_reg((hi_u32 *)addr_reg, V0_CVFIR_VBOFFSET.u32);
    }

    return;
}

hi_bool hal_video_set_hfir_mode(hal_disp_layer layer, hal_hfirmode mode)
{
    volatile U_V0_HFIR_CTRL V0_HFIR_CTRL;
    volatile U_WD_HPZME_CTRL WD_HPZME_CTRL;
    volatile U_WD_HCDS_CTRL WD_HCDS_CTRL;

    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_HFIR_CTRL.u32));
            V0_HFIR_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_HFIR_CTRL.bits.hfir_mode = mode;
            hal_write_reg((hi_u32 *)addr_reg, V0_HFIR_CTRL.u32);
            break;
        }

        case HAL_DISP_LAYER_WBC: {
            // HPZME
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->WD_HPZME_CTRL.u32));
            WD_HPZME_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            WD_HPZME_CTRL.bits.ck_gt_en = 1;
            WD_HPZME_CTRL.bits.hfir_mode = mode;
            hal_write_reg((hi_u32 *)addr_reg, WD_HPZME_CTRL.u32);

            // HCDS
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->WD_HCDS_CTRL.u32));
            WD_HCDS_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            WD_HCDS_CTRL.bits.ck_gt_en = 1;
            WD_HCDS_CTRL.bits.hfir_en = 1;
            WD_HCDS_CTRL.bits.hfir_mode = 0x0;
            hal_write_reg((hi_u32 *)addr_reg, WD_HCDS_CTRL.u32);

            break;
        }

        default: {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_hfir_coef(hal_disp_layer layer, hi_s32 *coef)
{
    volatile U_V0_HFIRCOEF01 V0_HFIRCOEF01;
    volatile U_V0_HFIRCOEF23 V0_HFIRCOEF23;
    volatile U_V0_HFIRCOEF45 V0_HFIRCOEF45;
    volatile U_V0_HFIRCOEF67 V0_HFIRCOEF67;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_HFIRCOEF01.u32));
            V0_HFIRCOEF01.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_HFIRCOEF01.bits.coef0 = coef[0];
            V0_HFIRCOEF01.bits.coef1 = coef[1];
            hal_write_reg((hi_u32 *)addr_reg, V0_HFIRCOEF01.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_HFIRCOEF23.u32));
            V0_HFIRCOEF23.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_HFIRCOEF23.bits.coef2 = coef[2];
            V0_HFIRCOEF23.bits.coef3 = coef[3];
            hal_write_reg((hi_u32 *)addr_reg, V0_HFIRCOEF23.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_HFIRCOEF45.u32));
            V0_HFIRCOEF45.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_HFIRCOEF45.bits.coef4 = coef[4];
            V0_HFIRCOEF45.bits.coef5 = coef[5];
            hal_write_reg((hi_u32 *)addr_reg, V0_HFIRCOEF45.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_HFIRCOEF67.u32));
            V0_HFIRCOEF67.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_HFIRCOEF67.bits.coef6 = coef[6];
            V0_HFIRCOEF67.bits.coef7 = coef[7];
            hal_write_reg((hi_u32 *)addr_reg, V0_HFIRCOEF67.u32);
            break;
        }

        default: {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_layer_disp_rect(hal_disp_layer layer, rect *rect)
{
    volatile U_V0_DFPOS V0_DFPOS;
    volatile U_V0_DLPOS V0_DLPOS;

    volatile U_G0_DFPOS G0_DFPOS;
    volatile U_G0_DLPOS G0_DLPOS;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_DFPOS.u32));
            V0_DFPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_DFPOS.bits.disp_xfpos = rect->x;
            V0_DFPOS.bits.disp_yfpos = rect->y;
            hal_write_reg((hi_u32 *)addr_reg, V0_DFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_DLPOS.u32));
            V0_DLPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_DLPOS.bits.disp_xlpos = rect->x + rect->width - 1;
            V0_DLPOS.bits.disp_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32 *)addr_reg, V0_DLPOS.u32);
            break;
        }

        case HAL_DISP_LAYER_GFX0: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->G0_DFPOS));
            G0_DFPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            G0_DFPOS.bits.disp_xfpos = rect->x;
            G0_DFPOS.bits.disp_yfpos = rect->y;
            hal_write_reg((hi_u32 *)addr_reg, G0_DFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->G0_DLPOS));
            G0_DLPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            G0_DLPOS.bits.disp_xlpos = rect->x + rect->width - 1;
            G0_DLPOS.bits.disp_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32 *)addr_reg, G0_DLPOS.u32);
            break;
        }

        default: {
            HAL_PRINT("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_layer_video_rect(hal_disp_layer layer, rect *rect)
{
    volatile U_V0_VFPOS V0_VFPOS;
    volatile U_V0_VLPOS V0_VLPOS;

    volatile U_G0_VFPOS G0_VFPOS;
    volatile U_G0_VLPOS G0_VLPOS;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_VFPOS.u32));
            V0_VFPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_VFPOS.bits.video_xfpos = rect->x;
            V0_VFPOS.bits.video_yfpos = rect->y;
            hal_write_reg((hi_u32 *)addr_reg, V0_VFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_VLPOS.u32));
            V0_VLPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_VLPOS.bits.video_xlpos = rect->x + rect->width - 1;
            V0_VLPOS.bits.video_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32 *)addr_reg, V0_VLPOS.u32);

            break;
        }

        case HAL_DISP_LAYER_GFX0: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->G0_VFPOS));
            G0_VFPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            G0_VFPOS.bits.video_xfpos = rect->x;
            G0_VFPOS.bits.video_yfpos = rect->y;
            hal_write_reg((hi_u32 *)addr_reg, G0_VFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->G0_VLPOS));
            G0_VLPOS.u32 = hal_read_reg((hi_u32 *)addr_reg);
            G0_VLPOS.bits.video_xlpos = rect->x + rect->width - 1;
            G0_VLPOS.bits.video_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32 *)addr_reg, G0_VLPOS.u32);
            break;
        }

        default: {
            HAL_PRINT("error layer id %d# found in %s,%s: L%d\n", layer, __FILE__, __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_multi_area_l_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong ul_l_addr, hi_u16 stride)
{
    hi_ulong ul_pxaddr_addr = 0;
    hi_ulong ul_pxstride_addr = 0;
    U_VID_STRIDE VID_STRIDE;

    if ((layer == HAL_DISP_LAYER_VHD0) || (layer == HAL_DISP_LAYER_VHD1)) {
        // low 32 bits to VID_ADDR_L
        ul_pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_ADDR_L));
        hal_write_reg((hi_u32 *)ul_pxaddr_addr, get_low_addr(ul_l_addr));

        // high 32 bits to  VID_ADDR_H
        ul_pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_ADDR_H));
        hal_write_reg((hi_u32 *)ul_pxaddr_addr, get_high_addr(ul_l_addr));

        ul_pxstride_addr = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_STRIDE.u32));
        VID_STRIDE.u32 = hal_read_reg((hi_u32 *)ul_pxstride_addr);
        VID_STRIDE.bits.lm_stride = stride;
        hal_write_reg((hi_u32 *)ul_pxstride_addr, VID_STRIDE.u32);
    } else {
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_video_set_multi_area_c_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong ul_c_addr, hi_u16 stride)
{
    hi_ulong u_l_pxaddr_addr = 0;
    hi_ulong u_l_pxstride_addr = 0;
    U_VID_STRIDE VID_STRIDE;

    if ((layer == HAL_DISP_LAYER_VHD0) || (layer == HAL_DISP_LAYER_VHD1)) {
        // low 32 bits to VID_CADDR_L
        u_l_pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_CADDR_L));
        hal_write_reg((hi_u32 *)u_l_pxaddr_addr, get_low_addr(ul_c_addr));

        // high 32 bits to VID_CADDR_H
        u_l_pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_CADDR_H));
        hal_write_reg((hi_u32 *)u_l_pxaddr_addr, get_high_addr(ul_c_addr));

        u_l_pxstride_addr = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_STRIDE.u32));
        VID_STRIDE.u32 = hal_read_reg((hi_u32 *)u_l_pxstride_addr);
        VID_STRIDE.bits.chm_stride = stride;
        hal_write_reg((hi_u32 *)u_l_pxstride_addr, VID_STRIDE.u32);
    } else {
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_layer_enable_layer(hal_disp_layer layer, hi_u32 enable)
{
    volatile U_V0_CTRL V0_CTRL;
    volatile U_G0_CTRL G0_CTRL;
    volatile hi_ulong addr_reg;
    switch (layer) {
        case HAL_DISP_LAYER_VHD0: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_CTRL.u32));
            V0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_CTRL.bits.surface_en = enable;
            V0_CTRL.bits.nosec_flag = 0;
            hal_write_reg((hi_u32 *)addr_reg, V0_CTRL.u32);
            break;
        }

        case HAL_DISP_LAYER_GFX0: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->G0_CTRL));
            G0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            G0_CTRL.bits.surface_en = enable;
            hal_write_reg((hi_u32 *)addr_reg, G0_CTRL.u32);
            break;
        }

        default: {
            HAL_PRINT("error layer:%d id found in %s: L%d\n", layer, __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_layer_data_fmt(hal_disp_layer layer,
                                  hal_disp_pixel_format data_fmt)
{
    volatile U_VID_SRC_INFO VID_SRC_INFO;
    volatile U_GFX_SRC_INFO GFX_SRC_INFO;
    volatile hi_ulong addr_reg;

    // only for v0 and v1
    if ((layer == HAL_DISP_LAYER_VHD0) ||
        (layer == HAL_DISP_LAYER_VHD1) ||
        (layer == HAL_DISP_LAYER_VHD2)) {
        addr_reg = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_SRC_INFO.u32));
        VID_SRC_INFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        VID_SRC_INFO.bits.data_type = data_fmt;
        hal_write_reg((hi_u32 *)addr_reg, VID_SRC_INFO.u32);
    } else if ((layer == HAL_DISP_LAYER_GFX0) ||
       (layer == HAL_DISP_LAYER_GFX1) ||
       (layer == HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_SRC_INFO.u32));
        GFX_SRC_INFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        GFX_SRC_INFO.bits.ifmt = data_fmt;
        hal_write_reg((hi_u32 *)addr_reg, GFX_SRC_INFO.u32);
    } else {
        HAL_PRINT("error layer id%d found in %s: L%d\n", layer, __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_layer_in_rect(hal_disp_layer layer, rect *rect)
{
    U_VID_IN_RESO VID_IN_RESO;
    U_GFX_IRESO GFX_IRESO;
    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        addr_reg = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_IN_RESO.u32));
        VID_IN_RESO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        VID_IN_RESO.bits.ireso_w = rect->width - 1;
        VID_IN_RESO.bits.ireso_h = rect->height - 1;
        hal_write_reg((hi_u32 *)addr_reg, VID_IN_RESO.u32);
    } else if (layer == HAL_DISP_LAYER_GFX0) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_IRESO.u32));
        GFX_IRESO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        GFX_IRESO.bits.ireso_w = rect->width - 1;
        GFX_IRESO.bits.ireso_h = rect->height - 1;
        hal_write_reg((hi_u32 *)addr_reg, GFX_IRESO.u32);
    } else {
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_layer_set_layer_galpha(hal_disp_layer layer,
                                 hi_u8 alpha0)
{
    volatile U_V0_CTRL V0_CTRL;

    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_CTRL.u32));
            V0_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_CTRL.bits.galpha = alpha0;
            hal_write_reg((hi_u32 *)addr_reg, V0_CTRL.u32);
            break;
        }

        default: {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                             hal_disp_zme_outfmt zme_out_fmt)
{
    volatile U_V0_ZME_HINFO V0_ZME_HINFO;
    volatile U_V0_ZME_VINFO V0_ZME_VINFO;

    volatile U_V1_CVFIR_VINFO V1_CVFIR_VINFO;

    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        // horiz info
        addr_reg = (hi_ulong) & (g_vo_reg->V0_ZME_HINFO.u32);
        V0_ZME_HINFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_ZME_HINFO.bits.out_width = width - 1;
        hal_write_reg((hi_u32 *)addr_reg, V0_ZME_HINFO.u32);

        // vertical info
        addr_reg = (hi_ulong) & (g_vo_reg->V0_ZME_VINFO.u32);
        V0_ZME_VINFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_ZME_VINFO.bits.out_pro = 1;
        V0_ZME_VINFO.bits.out_height = height - 1;
        V0_ZME_VINFO.bits.out_fmt = zme_out_fmt;
        hal_write_reg((hi_u32 *)addr_reg, V0_ZME_VINFO.u32);
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        // vertical info
        addr_reg = (hi_ulong) & (g_vo_reg->V1_CVFIR_VINFO.u32);
        V1_CVFIR_VINFO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V1_CVFIR_VINFO.bits.vzme_ck_gt_en = 1;
        V1_CVFIR_VINFO.bits.out_pro = 1;
        V1_CVFIR_VINFO.bits.out_height = height;
        V1_CVFIR_VINFO.bits.out_fmt = zme_out_fmt;
        hal_write_reg((hi_u32 *)addr_reg, V1_CVFIR_VINFO.u32);
    } else {

        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_src_resolution(hal_disp_layer layer,
                                   rect *rect)
{
    U_VID_SRC_RESO VID_SRC_RESO;

    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        addr_reg = vo_get_vid_abs_addr(layer, (hi_ulong) & (g_vo_reg->VID_SRC_RESO.u32));
        VID_SRC_RESO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        VID_SRC_RESO.bits.src_w = rect->width - 1;
        VID_SRC_RESO.bits.src_h = rect->height - 1;
        hal_write_reg((hi_u32 *)addr_reg, VID_SRC_RESO.u32);
    }

    return HI_TRUE;
}

/* vou zoom enable */
hi_bool hal_layer_set_zme_enable(hal_disp_layer layer,
                               hal_disp_zmemode mode,
                               hi_u32 enable)
{
    volatile U_V0_ZME_HSP V0_ZME_HSP;
    volatile U_V0_ZME_VSP V0_ZME_VSP;

    volatile U_V1_CVFIR_VSP V1_CVFIR_VSP;

    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        // layer zoom enable
        if ((mode == HAL_DISP_ZMEMODE_HORL) || (mode == HAL_DISP_ZMEMODE_HOR) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_ZME_HSP.u32));
            V0_ZME_HSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_ZME_HSP.bits.lhfir_en = enable;
            hal_write_reg((hi_u32 *)addr_reg, V0_ZME_HSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_HORC) || (mode == HAL_DISP_ZMEMODE_HOR) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_ZME_HSP.u32));
            V0_ZME_HSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_ZME_HSP.bits.chfir_en = enable;
            hal_write_reg((hi_u32 *)addr_reg, V0_ZME_HSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_VERL) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_ZME_VSP.u32));
            V0_ZME_VSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_ZME_VSP.bits.lvfir_en = enable;
            hal_write_reg((hi_u32 *)addr_reg, V0_ZME_VSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_VERC) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_ZME_VSP.u32));
            V0_ZME_VSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V0_ZME_VSP.bits.cvfir_en = enable;
            hal_write_reg((hi_u32 *)addr_reg, V0_ZME_VSP.u32);
        }
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        if ((mode == HAL_DISP_ZMEMODE_VERL) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = (hi_ulong) & (g_vo_reg->V1_CVFIR_VSP.u32);
            V1_CVFIR_VSP.u32 = hal_read_reg((hi_u32 *)addr_reg);
            V1_CVFIR_VSP.bits.cvfir_en = enable;
            V1_CVFIR_VSP.bits.cvmid_en = enable;
            hal_write_reg((hi_u32 *)addr_reg, V1_CVFIR_VSP.u32);
        }
    } else {

        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_disp_set_dither_round_unlim(hal_disp_outputchannel chn, hi_u32 dither_round_unlim)
{
    volatile  U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;
    volatile  hi_ulong addr_reg;
    switch (chn) {
        case HAL_DISP_CHANNEL_DHD0 :
        case HAL_DISP_CHANNEL_DHD1 : {
            addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_CTRL.u32));
            INTF0_DITHER_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);
            INTF0_DITHER_CTRL.bits.dither_round_unlim = dither_round_unlim;
            hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_CTRL.u32);
            break;
        }
        default : {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}
hi_bool hal_disp_set_dither_data_in_out(hal_disp_outputchannel chn,
        hi_u32 i_data_width_dither, hi_u32 o_data_width_dither)
{
    volatile  U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;
    volatile  hi_ulong               addr_reg;

    switch (chn) {
        case HAL_DISP_CHANNEL_DHD0 :
        case HAL_DISP_CHANNEL_DHD1 : {
            addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_CTRL.u32));
            INTF0_DITHER_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);
            INTF0_DITHER_CTRL.bits.i_data_width_dither = i_data_width_dither;
            INTF0_DITHER_CTRL.bits.o_data_width_dither = o_data_width_dither;
            hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_CTRL.u32);
            break;
        }
        default : {
             return HI_FALSE;
         }
     }

    return HI_TRUE;
}

hi_bool hal_disp_set_dither_en(hal_disp_outputchannel chn, hi_u32 dither_en)
{
    volatile  U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;
    volatile  hi_ulong               addr_reg;
    switch (chn) {
        case HAL_DISP_CHANNEL_DHD0 :
        case HAL_DISP_CHANNEL_DHD1 : {
            addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_CTRL.u32));
            INTF0_DITHER_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);
            INTF0_DITHER_CTRL.bits.dither_en = dither_en;
            hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_CTRL.u32);
            break;
        }
        default : {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}
hi_bool hal_disp_set_dither_mode(hal_disp_outputchannel chn, hi_u32 dither_mode)
{
    volatile  U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;
    volatile  hi_ulong               addr_reg;

    switch (chn) {
       case HAL_DISP_CHANNEL_DHD0 :
       case HAL_DISP_CHANNEL_DHD1 : {
           addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_CTRL.u32));
           INTF0_DITHER_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);
           INTF0_DITHER_CTRL.bits.dither_mode = dither_mode;
           hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_CTRL.u32);
           break;
       }
       default : {
           return HI_FALSE;
       }
    }
    return HI_TRUE;
}
hi_bool hal_disp_set_dither_round(hal_disp_outputchannel chn, hi_u32 dither_round)
{
    volatile  U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;
    volatile  hi_ulong               addr_reg;

    switch (chn) {
        case HAL_DISP_CHANNEL_DHD0 :
        case HAL_DISP_CHANNEL_DHD1 : {
            addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_CTRL.u32));
            INTF0_DITHER_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);
            INTF0_DITHER_CTRL.bits.dither_round = dither_round;
            hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_CTRL.u32);
            break;
        }
        default : {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}
hi_bool hal_disp_set_dither_domain_mode(hal_disp_outputchannel chn, hi_u32 dither_domain_mode)
{
    volatile  U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;
    volatile  hi_ulong               addr_reg;

    switch (chn) {
        case HAL_DISP_CHANNEL_DHD0 :
        case HAL_DISP_CHANNEL_DHD1 : {
            addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_CTRL.u32));
            INTF0_DITHER_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);
            INTF0_DITHER_CTRL.bits.dither_domain_mode = dither_domain_mode;
            hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_CTRL.u32);
            break;
        }
        default : {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}
hi_bool hal_disp_set_dither_tap_mode(hal_disp_outputchannel chn, hi_u32 dither_tap_mode)
{
    volatile  U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;
    volatile  hi_ulong               addr_reg;

    switch (chn) {
        case HAL_DISP_CHANNEL_DHD0 :
        case HAL_DISP_CHANNEL_DHD1 : {
             addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_CTRL.u32));
             INTF0_DITHER_CTRL.u32 = hal_read_reg((hi_u32*)addr_reg);
             INTF0_DITHER_CTRL.bits.dither_tap_mode = dither_tap_mode;
             hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_CTRL.u32);
             break;
         }
        default : {
             return HI_FALSE;
        }
     }

    return HI_TRUE;
}

hi_bool hal_disp_set_dither_sed0(hal_disp_outputchannel chn, hal_disp_dihter_sed *dither_sed)
{
    volatile  U_INTF0_DITHER_SED_Y0 INTF0_DITHER_SED_Y0;
    volatile  U_INTF0_DITHER_SED_U0 INTF0_DITHER_SED_U0;
    volatile  U_INTF0_DITHER_SED_V0 INTF0_DITHER_SED_V0;
    volatile  U_INTF0_DITHER_SED_W0 INTF0_DITHER_SED_W0;
    volatile  hi_ulong                 addr_reg;

    if (chn == HAL_DISP_CHANNEL_DHD0) {
        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_Y0.u32));
        INTF0_DITHER_SED_Y0.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_Y0.bits.dither_sed_y0 = dither_sed->dither_sed_y0;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_Y0.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_U0.u32));
        INTF0_DITHER_SED_U0.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_U0.bits.dither_sed_u0 = dither_sed->dither_sed_u0;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_U0.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_V0.u32));
        INTF0_DITHER_SED_V0.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_V0.bits.dither_sed_v0 = dither_sed->dither_sed_v0;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_V0.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_W0.u32));
        INTF0_DITHER_SED_W0.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_W0.bits.dither_sed_w0 = dither_sed->dither_sed_w0;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_W0.u32);
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_dither_sed1(hal_disp_outputchannel chn, hal_disp_dihter_sed *dither_sed)
{
    volatile  U_INTF0_DITHER_SED_Y1 INTF0_DITHER_SED_Y1;
    volatile  U_INTF0_DITHER_SED_U1 INTF0_DITHER_SED_U1;
    volatile  U_INTF0_DITHER_SED_V1 INTF0_DITHER_SED_V1;
    volatile  U_INTF0_DITHER_SED_W1 INTF0_DITHER_SED_W1;
    volatile  hi_ulong                 addr_reg;

    if (chn == HAL_DISP_CHANNEL_DHD0) {
        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_Y1.u32));
        INTF0_DITHER_SED_Y1.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_Y1.bits.dither_sed_y1 = dither_sed->dither_sed_y1;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_Y1.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_U1.u32));
        INTF0_DITHER_SED_U1.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_U1.bits.dither_sed_u1 = dither_sed->dither_sed_u1;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_U1.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_V1.u32));
        INTF0_DITHER_SED_V1.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_V1.bits.dither_sed_v1 = dither_sed->dither_sed_v1;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_V1.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_W1.u32));
        INTF0_DITHER_SED_W1.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_W1.bits.dither_sed_w1 = dither_sed->dither_sed_w1;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_W1.u32);
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_dither_sed2(hal_disp_outputchannel chn, hal_disp_dihter_sed *dither_sed)
{
    volatile  U_INTF0_DITHER_SED_Y2 INTF0_DITHER_SED_Y2;
    volatile  U_INTF0_DITHER_SED_U2 INTF0_DITHER_SED_U2;
    volatile  U_INTF0_DITHER_SED_V2 INTF0_DITHER_SED_V2;
    volatile  U_INTF0_DITHER_SED_W2 INTF0_DITHER_SED_W2;
    volatile  hi_ulong                 addr_reg;

    if (chn == HAL_DISP_CHANNEL_DHD0) {
        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_Y2.u32));
        INTF0_DITHER_SED_Y2.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_Y2.bits.dither_sed_y2 = dither_sed->dither_sed_y2;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_Y2.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_U2.u32));
        INTF0_DITHER_SED_U2.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_U2.bits.dither_sed_u2 = dither_sed->dither_sed_u2;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_U2.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_V2.u32));
        INTF0_DITHER_SED_V2.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_V2.bits.dither_sed_v2 = dither_sed->dither_sed_v2;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_V2.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_W2.u32));
        INTF0_DITHER_SED_W2.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_W2.bits.dither_sed_w2 = dither_sed->dither_sed_w2;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_W2.u32);
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_dither_sed3(hal_disp_outputchannel chn, hal_disp_dihter_sed *dither_sed)
{
    volatile  U_INTF0_DITHER_SED_Y3 INTF0_DITHER_SED_Y3;
    volatile  U_INTF0_DITHER_SED_U3 INTF0_DITHER_SED_U3;
    volatile  U_INTF0_DITHER_SED_V3 INTF0_DITHER_SED_V3;
    volatile  U_INTF0_DITHER_SED_W3 INTF0_DITHER_SED_W3;
    volatile  hi_ulong                 addr_reg;

    if (chn == HAL_DISP_CHANNEL_DHD0) {
        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_Y3.u32));
        INTF0_DITHER_SED_Y3.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_Y3.bits.dither_sed_y3 = dither_sed->dither_sed_y3;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_Y3.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_U3.u32));
        INTF0_DITHER_SED_U3.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_U3.bits.dither_sed_u3 = dither_sed->dither_sed_u3;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_U3.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_V3.u32));
        INTF0_DITHER_SED_V3.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_V3.bits.dither_sed_v3 = dither_sed->dither_sed_v3;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_V3.u32);

        addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_SED_W3.u32));
        INTF0_DITHER_SED_W3.u32 = hal_read_reg((hi_u32*)addr_reg);
        INTF0_DITHER_SED_W3.bits.dither_sed_w3 = dither_sed->dither_sed_w3;
        hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_SED_W3.u32);
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_dither_sed(hal_disp_outputchannel chn, hal_disp_dihter_sed *dither_sed)
{
    hal_disp_set_dither_sed0(chn, dither_sed);
    hal_disp_set_dither_sed1(chn, dither_sed);
    hal_disp_set_dither_sed2(chn, dither_sed);
    hal_disp_set_dither_sed3(chn, dither_sed);

    return HI_TRUE;
}

hi_bool hal_disp_set_dither_thr_min_max(hal_disp_outputchannel chn, hi_u32 thr_min, hi_u32 thr_max)
{
    volatile  U_INTF0_DITHER_THR    INTF0_DITHER_THR;
    volatile  hi_ulong                 addr_reg;

    switch (chn) {
        case HAL_DISP_CHANNEL_DHD0 :
        case HAL_DISP_CHANNEL_DHD1 : {
            addr_reg = vo_get_chn_abs_addr(chn, (hi_ulong) & (g_vo_reg->INTF0_DITHER_THR.u32));
            INTF0_DITHER_THR.u32 = hal_read_reg((hi_u32*)addr_reg);
            INTF0_DITHER_THR.bits.dither_thr_min = thr_min;
            INTF0_DITHER_THR.bits.dither_thr_max = thr_max;
            hal_write_reg((hi_u32*)addr_reg, INTF0_DITHER_THR.u32);
            break;
        }
        default : {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_reg_up(hal_disp_layer layer)
{
    U_V0_UPD V0_UPD;
    U_G0_UPD G0_UPD;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1:
        case HAL_DISP_LAYER_VHD2: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->V0_UPD.u32));
            V0_UPD.u32 = hal_read_reg((hi_u32 *)addr_reg);
            /* video layer register update */
            V0_UPD.bits.regup = 0x1;
            hal_write_reg((hi_u32 *)addr_reg, V0_UPD.u32);
            break;
        }

        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1:
        case HAL_DISP_LAYER_GFX3: {
            addr_reg = vo_get_abs_addr(layer, (hi_ulong) & (g_vo_reg->G0_UPD));
            G0_UPD.u32 = hal_read_reg((hi_u32 *)addr_reg);
            /* graphic layer register update */
            G0_UPD.bits.regup = 0x1;
            hal_write_reg((hi_u32 *)addr_reg, G0_UPD.u32);
            break;
        }

        default:
        {
            HAL_PRINT("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_cbm_set_cbm_bkg(hi_u32 mixer_id, hal_disp_bkcolor *bkg)
{
    U_CBM_BKG1 CBM_BKG1;

    if (mixer_id == HAL_CBMMIX1) {
        CBM_BKG1.u32 = hal_read_reg((hi_u32 *)&(g_vo_reg->CBM_BKG1.u32));
        CBM_BKG1.bits.cbm_bkgy1 = (bkg->bkg_y);
        CBM_BKG1.bits.cbm_bkgcb1 = (bkg->bkg_cb);
        CBM_BKG1.bits.cbm_bkgcr1 = (bkg->bkg_cr);
        hal_write_reg((hi_u32 *)&(g_vo_reg->CBM_BKG1.u32), CBM_BKG1.u32);
    } else {
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_cbm_set_cbm_mixer_prio(hal_disp_layer layer, hi_u8 prio, hi_u8 mixer_id)
{
    U_CBM_MIX1 CBM_MIX1;

    hi_u8 layer_id = 0;

    // settings for v0 and g0
    if (mixer_id == HAL_CBMMIX1) {
        // check layer availability
        switch (layer) {
            case HAL_DISP_LAYER_VHD0: {
                layer_id = 0x1;
                break;
            }

            case HAL_DISP_LAYER_GFX0: {
                layer_id = 0x2;
                break;
            }

            default:
            {
                return HI_FALSE;
            }
        }

        // set mixer prio
        CBM_MIX1.u32 = hal_read_reg((hi_u32 *)&(g_vo_reg->CBM_MIX1.u32));

        switch (prio) {
            case 0: {
                CBM_MIX1.bits.mixer_prio0 = layer_id;
                break;
            }

            case 1: {
                CBM_MIX1.bits.mixer_prio1 = layer_id;
                break;
            }

            case 2: {
                CBM_MIX1.bits.mixer_prio2 = layer_id;
                break;
            }

            default:
            {
                return HI_FALSE;
            }
        }

        hal_write_reg((hi_u32 *)&(g_vo_reg->CBM_MIX1.u32), CBM_MIX1.u32);
    } else {
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_ext(hal_disp_layer layer,
                              hal_gfx_bitextend mode)
{
    U_GFX_OUT_CTRL GFX_OUT_CTRL;

    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) ||
    (layer == HAL_DISP_LAYER_GFX1) ||
    (layer == HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_OUT_CTRL.u32));
        GFX_OUT_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        GFX_OUT_CTRL.bits.bitext = mode;
        hal_write_reg ((hi_u32 *)(hi_ulong) addr_reg, GFX_OUT_CTRL.u32);
    } else {
        HAL_PRINT("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_palpha(hal_disp_layer layer,
                                 hi_u32 alpha_en, hi_u32 arange,
                                 hi_u8 alpha0, hi_u8 alpha1)
{
    U_GFX_OUT_CTRL GFX_OUT_CTRL;

    U_GFX_1555_ALPHA GFX_1555_ALPHA;

    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) ||
    (layer == HAL_DISP_LAYER_GFX1) ||
    (layer == HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_OUT_CTRL.u32));
        GFX_OUT_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        GFX_OUT_CTRL.bits.palpha_en = alpha_en;
        hal_write_reg((hi_u32 *)addr_reg, GFX_OUT_CTRL.u32);

        if (alpha_en == HI_TRUE) {
            addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32 *)addr_reg);
            GFX_1555_ALPHA.bits.alpha_1 = alpha1;
            hal_write_reg((hi_u32 *)addr_reg, GFX_1555_ALPHA.u32);

            addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32 *)addr_reg);
            GFX_1555_ALPHA.bits.alpha_0 = alpha0;
            hal_write_reg((hi_u32 *)addr_reg, GFX_1555_ALPHA.u32);
        } else {
            addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32 *)(hi_ulong) addr_reg);
            GFX_1555_ALPHA.bits.alpha_1 = 0xff;
            hal_write_reg ((hi_u32 *)(hi_ulong) addr_reg, GFX_1555_ALPHA.u32);

            addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32 *)(hi_ulong) addr_reg);
            GFX_1555_ALPHA.bits.alpha_0 = 0xff;
            hal_write_reg ((hi_u32 *)(hi_ulong) addr_reg, GFX_1555_ALPHA.u32);
        }
    } else {
        HAL_PRINT("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_pre_mult(hal_disp_layer layer, hi_u32 enable)
{
    U_GFX_OUT_CTRL GFX_OUT_CTRL;

    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) ||
    (layer == HAL_DISP_LAYER_GFX1) ||
    (layer == HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_OUT_CTRL.u32));
        GFX_OUT_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        GFX_OUT_CTRL.bits.premulti_en = enable;
        hal_write_reg((hi_u32 *)addr_reg, GFX_OUT_CTRL.u32);
    } else {
        HAL_PRINT("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_addr(hal_disp_layer layer, hi_u64 l_addr)
{
    volatile hi_ulong ul_gfx_addr_h = 0;
    volatile hi_ulong ul_gfx_addr_l = 0;

    if ((layer == HAL_DISP_LAYER_GFX0) ||
    (layer == HAL_DISP_LAYER_GFX1) ||
    (layer == HAL_DISP_LAYER_GFX3)) {
        // write low address to register.
        ul_gfx_addr_l = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_ADDR_L));
        hal_write_reg((hi_u32 *)ul_gfx_addr_l, get_low_addr(l_addr));
        // write high address to register.
        ul_gfx_addr_h = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_ADDR_H));
        hal_write_reg((hi_u32 *)ul_gfx_addr_h, get_high_addr(l_addr));
    } else {
        HAL_PRINT("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }
    return HI_TRUE;
}
hi_bool hal_graphic_set_gfx_stride(hal_disp_layer layer, hi_u16 u16pitch)
{
    volatile U_GFX_STRIDE GFX_STRIDE;
    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) ||
    (layer == HAL_DISP_LAYER_GFX1) ||
    (layer == HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_STRIDE.u32));
        GFX_STRIDE.u32 = hal_read_reg((hi_u32 *)addr_reg);
        GFX_STRIDE.bits.surface_stride = u16pitch;
        hal_write_reg((hi_u32 *)addr_reg, GFX_STRIDE.u32);
    } else {
        HAL_PRINT("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_gfx_set_src_resolution(hal_disp_layer layer, rect *rect)
{
    U_GFX_SRC_RESO GFX_SRC_RESO;
    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) ||
    (layer == HAL_DISP_LAYER_GFX1) ||
    (layer == HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_ulong) & (g_vo_reg->GFX_SRC_RESO.u32));
        GFX_SRC_RESO.u32 = hal_read_reg((hi_u32 *)addr_reg);
        GFX_SRC_RESO.bits.src_w = rect->width - 1;
        GFX_SRC_RESO.bits.src_h = rect->height - 1;
        hal_write_reg((hi_u32 *)addr_reg, GFX_SRC_RESO.u32);
    } else {
        HAL_PRINT("error:layer id not found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_void hal_layer_csc_set_dc_coef(hal_disp_layer layer, vdp_csc_dc_coef *csc_dc_coef)
{
    U_V0_HIPP_CSC_IDC0 V0_HIPP_CSC_IDC0;
    U_V0_HIPP_CSC_IDC1 V0_HIPP_CSC_IDC1;
    U_V0_HIPP_CSC_IDC2 V0_HIPP_CSC_IDC2;
    U_V0_HIPP_CSC_ODC0 V0_HIPP_CSC_ODC0;
    U_V0_HIPP_CSC_ODC1 V0_HIPP_CSC_ODC1;
    U_V0_HIPP_CSC_ODC2 V0_HIPP_CSC_ODC2;

    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_IDC0.u32));
        V0_HIPP_CSC_IDC0.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_IDC0.bits.hipp_csc_idc0 = csc_dc_coef->csc_in_dc0;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_IDC0.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_IDC1.u32));
        V0_HIPP_CSC_IDC1.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_IDC1.bits.hipp_csc_idc1 = csc_dc_coef->csc_in_dc1;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_IDC1.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_IDC2.u32));
        V0_HIPP_CSC_IDC2.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_IDC2.bits.hipp_csc_idc2 = csc_dc_coef->csc_in_dc2;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_IDC2.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_ODC0.u32));
        V0_HIPP_CSC_ODC0.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_ODC0.bits.hipp_csc_odc0 = csc_dc_coef->csc_out_dc0;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_ODC0.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_ODC1.u32));
        V0_HIPP_CSC_ODC1.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_ODC1.bits.hipp_csc_odc1 = csc_dc_coef->csc_out_dc1;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_ODC1.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_ODC2.u32));
        V0_HIPP_CSC_ODC2.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_ODC2.bits.hipp_csc_odc2 = csc_dc_coef->csc_out_dc2;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_ODC2.u32);
    } else if ((layer >= HAL_DISP_LAYER_GFX0) && (layer <= HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_IDC0.u32));
        V0_HIPP_CSC_IDC0.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_IDC0.bits.hipp_csc_idc0 = csc_dc_coef->csc_in_dc0;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_IDC0.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_IDC1.u32));
        V0_HIPP_CSC_IDC1.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_IDC1.bits.hipp_csc_idc1 = csc_dc_coef->csc_in_dc1;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_IDC1.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_IDC2.u32));
        V0_HIPP_CSC_IDC2.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_IDC2.bits.hipp_csc_idc2 = csc_dc_coef->csc_in_dc2;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_IDC2.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_ODC0.u32));
        V0_HIPP_CSC_ODC0.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_ODC0.bits.hipp_csc_odc0 = csc_dc_coef->csc_out_dc0;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_ODC0.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_ODC1.u32));
        V0_HIPP_CSC_ODC1.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_ODC1.bits.hipp_csc_odc1 = csc_dc_coef->csc_out_dc1;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_ODC1.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_ODC2.u32));
        V0_HIPP_CSC_ODC2.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_ODC2.bits.hipp_csc_odc2 = csc_dc_coef->csc_out_dc2;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_ODC2.u32);
    } else {
        HAL_PRINT("error layer id found in %s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    }
}

hi_void hal_layer_csc_set_param(hal_disp_layer layer, csc_coef_param *coef_param)
{
    U_V0_HIPP_CSC_SCALE V0_HIPP_CSC_SCALE;
    U_V0_HIPP_CSC_MIN_Y V0_HIPP_CSC_MIN_Y;
    U_V0_HIPP_CSC_MIN_C V0_HIPP_CSC_MIN_C;
    U_V0_HIPP_CSC_MAX_Y V0_HIPP_CSC_MAX_Y;
    U_V0_HIPP_CSC_MAX_C V0_HIPP_CSC_MAX_C;

    volatile hi_u32 addr_reg;
    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_SCALE.u32));
        V0_HIPP_CSC_SCALE.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_SCALE.bits.hipp_csc_scale = coef_param->csc_scale2p;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_SCALE.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_MIN_Y.u32));
        V0_HIPP_CSC_MIN_Y.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MIN_Y.bits.hipp_csc_min_y = coef_param->csc_clip_min;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MIN_Y.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_MIN_C.u32));
        V0_HIPP_CSC_MIN_C.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MIN_C.bits.hipp_csc_min_c = coef_param->csc_clip_min;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MIN_C.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_MAX_Y.u32));
        V0_HIPP_CSC_MAX_Y.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MAX_Y.bits.hipp_csc_max_y = coef_param->csc_clip_max;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MAX_Y.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_MAX_C.u32));
        V0_HIPP_CSC_MAX_C.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MAX_C.bits.hipp_csc_max_c = coef_param->csc_clip_max;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MAX_C.u32);
    } else if ((layer >= LAYER_GFX_START) && (layer <= LAYER_GFX_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_SCALE.u32));
        V0_HIPP_CSC_SCALE.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_SCALE.bits.hipp_csc_scale = coef_param->csc_scale2p;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_SCALE.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_MIN_Y.u32));
        V0_HIPP_CSC_MIN_Y.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MIN_Y.bits.hipp_csc_min_y = coef_param->csc_clip_min;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MIN_Y.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_MIN_C.u32));
        V0_HIPP_CSC_MIN_C.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MIN_C.bits.hipp_csc_min_c = coef_param->csc_clip_min;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MIN_C.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_MAX_Y.u32));
        V0_HIPP_CSC_MAX_Y.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MAX_Y.bits.hipp_csc_max_y = coef_param->csc_clip_max;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MAX_Y.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_MAX_C.u32));
        V0_HIPP_CSC_MAX_C.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_MAX_C.bits.hipp_csc_max_c = coef_param->csc_clip_max;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_MAX_C.u32);
    }
}

hi_void hal_layer_csc_set_coef(hal_disp_layer layer, vdp_csc_coef *csc_coef)
{
    U_V0_HIPP_CSC_COEF00 V0_HIPP_CSC_COEF00;
    U_V0_HIPP_CSC_COEF01 V0_HIPP_CSC_COEF01;
    U_V0_HIPP_CSC_COEF02 V0_HIPP_CSC_COEF02;
    U_V0_HIPP_CSC_COEF10 V0_HIPP_CSC_COEF10;
    U_V0_HIPP_CSC_COEF11 V0_HIPP_CSC_COEF11;
    U_V0_HIPP_CSC_COEF12 V0_HIPP_CSC_COEF12;
    U_V0_HIPP_CSC_COEF20 V0_HIPP_CSC_COEF20;
    U_V0_HIPP_CSC_COEF21 V0_HIPP_CSC_COEF21;
    U_V0_HIPP_CSC_COEF22 V0_HIPP_CSC_COEF22;

    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF00.u32));
        V0_HIPP_CSC_COEF00.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF00.bits.hipp_csc_coef00 = csc_coef->csc_coef00;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF00.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF01.u32));
        V0_HIPP_CSC_COEF01.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF01.bits.hipp_csc_coef01 = csc_coef->csc_coef01;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF01.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF02.u32));
        V0_HIPP_CSC_COEF02.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF02.bits.hipp_csc_coef02 = csc_coef->csc_coef02;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF02.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF10.u32));
        V0_HIPP_CSC_COEF10.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF10.bits.hipp_csc_coef10 = csc_coef->csc_coef10;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF10.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF11.u32));
        V0_HIPP_CSC_COEF11.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF11.bits.hipp_csc_coef11 = csc_coef->csc_coef11;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF11.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF12.u32));
        V0_HIPP_CSC_COEF12.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF12.bits.hipp_csc_coef12 = csc_coef->csc_coef12;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF12.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF20.u32));
        V0_HIPP_CSC_COEF20.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF20.bits.hipp_csc_coef20 = csc_coef->csc_coef20;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF20.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF21.u32));
        V0_HIPP_CSC_COEF21.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF21.bits.hipp_csc_coef21 = csc_coef->csc_coef21;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF21.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_COEF22.u32));
        V0_HIPP_CSC_COEF22.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF22.bits.hipp_csc_coef22 = csc_coef->csc_coef22;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF22.u32);
    } else if ((layer >= HAL_DISP_LAYER_GFX0) && (layer <= HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF00.u32));
        V0_HIPP_CSC_COEF00.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF00.bits.hipp_csc_coef00 = csc_coef->csc_coef00;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF00.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF01.u32));
        V0_HIPP_CSC_COEF01.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF01.bits.hipp_csc_coef01 = csc_coef->csc_coef01;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF01.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF02.u32));
        V0_HIPP_CSC_COEF02.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF02.bits.hipp_csc_coef02 = csc_coef->csc_coef02;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF02.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF10.u32));
        V0_HIPP_CSC_COEF10.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF10.bits.hipp_csc_coef10 = csc_coef->csc_coef10;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF10.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF11.u32));
        V0_HIPP_CSC_COEF11.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF11.bits.hipp_csc_coef11 = csc_coef->csc_coef11;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF11.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF12.u32));
        V0_HIPP_CSC_COEF12.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF12.bits.hipp_csc_coef12 = csc_coef->csc_coef12;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF12.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF20.u32));
        V0_HIPP_CSC_COEF20.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF20.bits.hipp_csc_coef20 = csc_coef->csc_coef20;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF20.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF21.u32));
        V0_HIPP_CSC_COEF21.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF21.bits.hipp_csc_coef21 = csc_coef->csc_coef21;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF21.u32);

        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_COEF22.u32));
        V0_HIPP_CSC_COEF22.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_COEF22.bits.hipp_csc_coef22 = csc_coef->csc_coef22;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_COEF22.u32);
    } else {
        HAL_PRINT("error layer id found in %s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    }

    return;
}

hi_bool hal_layer_set_csc_coef(hal_disp_layer layer, csc_coef *csc_coef)
{
    hal_layer_csc_set_dc_coef (layer, (vdp_csc_dc_coef *)(&csc_coef->csc_in_dc0));
    hal_layer_csc_set_coef (layer, (vdp_csc_coef *)(&csc_coef->csc_coef00));
    hal_layer_csc_set_param (layer, (csc_coef_param *)(&csc_coef->new_csc_scale2p));

    return HI_TRUE;
}

hi_void hal_layer_csc_set_ck_gt_en(hal_disp_layer layer, hi_bool ck_gt_en)
{
    U_V0_HIPP_CSC_CTRL V0_HIPP_CSC_CTRL;

    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_CTRL.u32));
        V0_HIPP_CSC_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_CTRL.bits.hipp_csc_ck_gt_en = ck_gt_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_CTRL.u32);
    } else if ((layer >= LAYER_GFX_START) && (layer <= LAYER_GFX_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_CTRL.u32));
        V0_HIPP_CSC_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_CTRL.bits.hipp_csc_ck_gt_en = ck_gt_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_CTRL.u32);
    }
}

hi_void hal_layer_csc_set_enable(hal_disp_layer layer, hi_bool csc_en)
{
    U_V0_HIPP_CSC_CTRL V0_HIPP_CSC_CTRL;

    volatile hi_u32 addr_reg;

    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->V0_HIPP_CSC_CTRL.u32));
        V0_HIPP_CSC_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_CTRL.bits.hipp_csc_en = csc_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_CTRL.u32);
    } else if ((layer >= LAYER_GFX_START) && (layer <= LAYER_GFX_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_u32) & (g_vo_reg->G0_HIPP_CSC_CTRL.u32));
        V0_HIPP_CSC_CTRL.u32 = hal_read_reg((hi_u32 *)addr_reg);
        V0_HIPP_CSC_CTRL.bits.hipp_csc_en = csc_en;
        hal_write_reg((hi_u32 *)addr_reg, V0_HIPP_CSC_CTRL.u32);
    }
}

hi_bool hal_layer_set_csc_en(hal_disp_layer layer, hi_bool csc_en)
{
    if ((layer < HAL_DISP_LAYER_VHD0) || (layer > HAL_DISP_LAYER_GFX3)) {
        HAL_PRINT("error, wrong layer ID!%d\n", __LINE__);
        return HI_FALSE;
    }

    hal_layer_csc_set_ck_gt_en(layer, csc_en);
    hal_layer_csc_set_enable(layer, csc_en);

    return HI_TRUE;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

