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

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <version.h>

#include <asm/arch/platform.h>

#include "hi_type.h"
#include "vou_reg.h"
#include "vou_def.h"
#include "vou_hal.h"
#include "vou_drv.h"
#include "vou_coef_org.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

/****************************************************************************
 * MACRO DEFINITION                                                         *
 ****************************************************************************/
#define VO_DEV_MAX_NUM   2
#define VO_LAYER_MAX_NUM 2

#define VO_SD_VTTH_WATERLINE 100
#define VO_HD_VTTH_WATERLINE 240

#define VO_BACKGROUD_BLACK   0x8080
#define VO_BACKGROUD_GREEN   0x804D3A42
#define VO_BACKGROUD_WHITE   0x3fffffff
#define VO_BACKGROUD_DEFAULT VO_BACKGROUD_WHITE

/* vou interrupt mask type */
typedef enum {
    VO_INTMSK_NONE = 0,
    VO_INTMSK_DHD0_VTTHD1 = 0x1,
    VO_INTMSK_DHD0_VTTHD2 = 0x2,
    VO_INTMSK_DHD0_VTTHD3 = 0x4,
    VO_INTMSK_DHD0_UFINT = 0x8,

    VO_INTMSK_DHD1_VTTHD1 = 0x10,
    VO_INTMSK_DHD1_VTTHD2 = 0x20,
    VO_INTMSK_DHD1_VTTHD3 = 0x40,
    VO_INTMSK_DHD1_UFINT = 0x80,

    VO_INTMSK_DSD_VTTHD1 = 0x100,
    VO_INTMSK_DSD_VTTHD2 = 0x200,
    VO_INTMSK_DSD_VTTHD3 = 0x400,
    VO_INTMSK_DSD_UFINT = 0x800,

    VO_INTMSK_B0_ERR = 0x1000,
    VO_INTMSK_B1_ERR = 0x2000,
    VO_INTMSK_B2_ERR = 0x4000,

    VO_INTMSK_WBC_DHDOVER = 0x8000,

    VO_INTREPORT_ALL = 0xffffffff
} vo_int_mask;

typedef struct {
    hi_bool enable;
    hi_u32 bk_grd;
    vo_intf_type intf_type;
    vo_intf_sync out_sync;
    hal_disp_pixel_format pixel_fmt;
} hal_dev_config;

typedef struct {
    hi_u32 bk_grd;
} hal_layer_config;

typedef struct {
    hi_s32 luma;
    hi_s32 cont;
    hi_s32 hue;
    hi_s32 satu;
} hal_csc_value;

typedef struct {
    hi_u32 base_phys;
    hi_void *base_virt;
    hi_u32 hor;
    hi_u32 ver422;
    hi_u32 ver420;
    hi_u32 lut;
    hi_u32 gam;
    hi_u32 acc;
} hal_coef_addr;

/****************************************************************************
 * GLOBAL VARIABLES                                                         *
 ****************************************************************************/

vo_user_intfsync_info g_user_intfsync_info;

hal_disp_syncinfo g_sync_timing[VO_OUTPUT_BUTT] = {
    /* |--INTFACE---||-----TOP-----||----HORIZON--------||----BOTTOM-----||-PULSE-||-INVERSE-| */
    /* synm, iop, itf,   vact, vbb,  vfb,  hact,   hbb,  hfb, hmid,bvact,bvbb, bvfb, hpw, vpw,idv, ihs, ivs */
    { 0, 0, 0, 288,  22, 2,  720,  132, 12,   1,    288, 23, 2, 126, 3,  0, 0, 0 }, /* 576I(PAL)  */
    { 0, 0, 0, 240,  18, 4,  720,  119, 19,   1,    240, 19, 4, 124, 3,  0, 0, 0 }, /* 480I(NTSC) */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 638,  1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@24Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 528,  1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@25Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 88,   1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@30Hz */
    { 0, 1, 1, 720,  25, 5,  1280, 260, 440,  1,    1,   1,  1, 40,  5,  0, 0, 0 }, /* 720P@50Hz */
    { 0, 1, 1, 720,  25, 5,  1280, 260, 110,  1,    1,   1,  1, 40,  5,  0, 0, 0 }, /* 720P@60Hz */
    { 0, 0, 1, 540,  20, 2,  1920, 192, 528,  1128, 540, 21, 2, 44,  5,  0, 0, 0 }, /* 1080I@50Hz */
    { 0, 0, 1, 540,  20, 2,  1920, 192, 88,   908,  540, 21, 2, 44,  5,  0, 0, 0 }, /* 1080I@60Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 528,  1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@50Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 88,   1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@60Hz */
    { 1, 1, 1, 576,  44, 5,  720,  132, 12,   1,    1,   1,  1, 64,  5,  0, 0, 0 }, /* 576P@50Hz */
    { 1, 1, 1, 480,  36, 9,  720,  122, 16,   1,    1,   1,  1, 62,  6,  0, 0, 0 }, /* 480P@60Hz */
    { 1, 1, 2, 600,  27, 1,  800,  216, 40,   1,    1,   1,  1, 128, 4,  0, 0, 0 }, /* 800*600@60Hz VGA@60Hz */
    { 1, 1, 2, 768,  35, 3,  1024, 296, 24,   1,    1,   1,  1, 136, 6,  0, 1, 1 }, /* 1024x768@60Hz */
    { 1, 1, 2, 1024, 41, 1,  1280, 360, 48,   1,    1,   1,  1, 112, 3,  0, 0, 0 }, /* 1280x1024@60Hz */
    { 1, 1, 2, 768,  27, 3,  1366, 356, 70,   1,    1,   1,  1, 143, 3,  0, 0, 0 }, /* 1366x768@60Hz */
    { 1, 1, 2, 900,  31, 3,  1440, 384, 80,   1,    1,   1,  1, 152, 6,  0, 1, 0 }, /* 1440x900@60Hz */
    { 1, 1, 2, 800,  28, 3,  1280, 328, 72,   1,    1,   1,  1, 128, 6,  0, 1, 0 }, /* 1280*800@60Hz VGA@60Hz */
    { 1, 1, 2, 1200, 49, 1,  1600, 496, 64,   1,    1,   1,  1, 192, 3,  0, 0, 0 }, /* 1600*1200@60Hz */
    { 1, 1, 2, 1050, 36, 3,  1680, 456, 104,  1,    1,   1,  1, 176, 6,  0, 1, 0 }, /* 1680*1050@60Hz */
    /* 1920*1200@60Hz CVT (reduced blanking) */
    { 1, 1, 2, 1200, 32, 3,  1920, 112, 48,   1,    1,   1,  1, 32,  6,  0, 0, 1 },
    { 1, 1, 2, 480,  35, 10, 640,  144, 16,   1,    1,   1,  1, 96,  2,  0, 1, 1 }, /* 640*480@60Hz CVT */
    { 0, 0, 0, 288,  22, 2,  960,  176, 16,   1,    288, 23, 2, 168, 3,  0, 0, 0 }, /* 960H(PAL) */
    { 0, 0, 0, 240,  18, 4,  960,  163, 21,   1,    240, 19, 4, 168, 3,  0, 0, 0 }, /* 960H(NTSC) */
    { 0, 1, 1, 2160, 72, 8,  1920, 192, 88,   1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1920*2160@30Hz */
    { 1, 1, 2, 1440, 39, 2,  2560, 112, 48,   1,    1,   1,  1, 32,  5,  0, 0, 0 }, /* 2560*1440@30Hz */
    { 1, 1, 2, 1440, 39, 2,  2560, 112, 48,   1,    1,   1,  1, 32,  5,  0, 0, 0 }, /* 2560*1440@60Hz */
    /* 2560*1600@60Hz CVT (reduced blanking) */
    { 0, 1, 2, 1600, 43, 3,  2560, 112, 48,   1,    1,   1,  1, 32,  6,  0, 0, 1 },
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 1276, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@24Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 1056, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@25Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 176,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@30Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 1056, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@50Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 176,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@60Hz */
    { 0, 1, 1, 2160, 82, 8,  4096, 384, 1020, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@24 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 968,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@25 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 88,   1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@30 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 968,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@50 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 88,   1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@60 */
    { 0, 1, 1, 240,  15, 9,  320,  65,  7,    1,    240, 14, 9, 1,   1,  0, 0, 0 }, /* 320X240@60  8bit LCD */
    { 0, 1, 1, 240,  2,  2,  320,  5,   10,   1,    1,   1,  1, 10,  1,  0, 0, 0 }, /* 320X240@50  6bit LCD */
    { 0, 1, 1, 320,  10, 4,  240,  30,  10,   1,    1,   1,  1, 10,  2,  0, 0, 0 }, /* 240X320@50  6bit LCD */
    { 0, 1, 1, 320,  2,  2,  240,  20,  10,   1,    1,   1,  1, 2,   1,  0, 0, 0 }, /* 240X320@60 16bit LCD */
    { 0, 1, 1, 600,  23, 12, 800,  210, 46,   1,    1,   1,  1, 2,   1,  0, 0, 0 }, /* 800X600@60 24bit LCD */
    { 0, 1, 1, 1280, 24, 8,  720,  123, 99,   1,    1,   1,  1, 24,  4,  0, 0, 0 }, /* 720 x1280 at 60 hz */
    { 0, 1, 1, 1920, 36, 16, 1080, 28,  130,  1,    1,   1,  1, 24,  4,  0, 0, 0 }, /* 1080 x1920 at 60 hz */
    { 0, 1, 1, 4320, 64, 16, 7680, 768, 552,  1,    1,   1,  1, 176, 20, 0, 0, 0 }, /* 7680x4320@30 */
    {}                                                                              /* user */
};

static hal_dev_config g_hal_dev_cfg[VO_DEV_MAX_NUM] = {
    {
        .enable = HI_FALSE,
        .bk_grd = VO_BACKGROUD_DEFAULT,
        .intf_type = VO_INTF_HDMI | VO_INTF_BT1120 | VO_INTF_BT656,
        .out_sync = VO_OUTPUT_1080P60,                  /* for debug: VO_OUTPUT_800x600_60 */
        .pixel_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_422, /* VOU_PIXERL_FORMAT_RGB888, VOU_PIXERL_FORMAT_YCBCR422 */
    }
};

/****************************************************************************
 * VOU FUNCTION                                                             *
 *            ---- assistant function area                                  *
 ****************************************************************************/
#define MAX2(x, y)       ( (x) > (y) ? (x):(y) )
#define MIN2(x, y)       ( (x) < (y) ? (x):(y) )
#define CLIP_MIN(x, min)          (((x) >= min) ? (x) : min)

hi_void rgb_to_yc_full(HI_U16 r, HI_U16 g, HI_U16 b, HI_U16 *py, HI_U16 *pcb, HI_U16 *pcr)
{
    HI_U16 py_temp, pcb_temp, pcr_temp;

    py_temp  = (HI_U16)(((r*76 + g*150 + b*29)>>8) * 4);
    pcb_temp = (HI_U16)(CLIP_MIN(((((b*130 - r*44 ) - g*86) >> 8)+128), 0) * 4);
    pcr_temp = (HI_U16)(CLIP_MIN(((((r*130 - g*109) - b*21) >> 8)+128), 0) * 4);

    *py = MAX2(MIN2(py_temp, 1023), 0);
    *pcb = MAX2(MIN2(pcb_temp, 1023), 0);
    *pcr = MAX2(MIN2(pcr_temp, 1023), 0);
}


hi_u32 rgb_to_yuv_full(hi_u32 u32Rgb)
{
    HI_U16 y, u, v;

    rgb_to_yc_full(RGB_R(u32Rgb), RGB_G(u32Rgb), RGB_B(u32Rgb), &y, &u, &v);

    return YUV(y, u, v);
}

hi_void vo_drv_board_init(hi_void)
{
    hal_vo_init();
    vo_drv_default_setting();

    return;
}

hi_void vo_drv_int_reg_up_mode(vo_hal_layer vo_layer, vo_int_mode int_mode)
{
    hal_video_set_layer_up_mode(vo_layer, int_mode);

    return;
}

hi_void vo_drv_set_dev_intf_type(hi_s32 vo_dev, vo_intf_type intf_type)
{
    g_hal_dev_cfg[vo_dev].intf_type = intf_type;

    return;
}

hi_void vo_drv_set_dev_bk_grd(hi_s32 vo_dev, hi_u32 bg_color)
{
    g_hal_dev_cfg[vo_dev].bk_grd = bg_color;

    return;
}

hi_void vo_drv_set_dev_out_sync(hi_s32 vo_dev, vo_intf_sync vo_out_mode)
{
    g_hal_dev_cfg[vo_dev].out_sync = vo_out_mode;

    return;
}

/* interrupt relative                                                       */
hi_void vo_drv_dev_int_enable(vo_hal_dev vo_dev, hi_bool enable)
{
    vo_int_mask int_type;
    vo_int_mask hifb_int_type = 0x0;

    switch (vo_dev) {
        case VO_DEV_DHD0:
            int_type = VO_INTMSK_DHD0_VTTHD1;
            hifb_int_type = VO_INTMSK_DHD0_VTTHD2 | VO_INTMSK_DHD0_VTTHD3;
            break;

        default:
            return;
    }

    if (enable == HI_TRUE) {
        hal_disp_set_int_mask(int_type);
        hal_disp_set_int_mask1(hifb_int_type);
    } else {
        hal_disp_clr_int_mask(int_type);
        hal_disp_clr_int_mask1(hifb_int_type);
    }

    return;
}

hi_void vo_drv_int_set_mode(hi_s32 vo_dev, vo_int_mode int_mode)
{
    hal_disp_set_vt_thd_mode(vo_dev, int_mode);

    return;
}

hi_void vo_drv_layer_enable(vo_hal_layer vo_layer, hi_bool enable)
{
    hal_layer_enable_layer(vo_layer, enable);

    return;
}

hi_void vo_drv_def_layer_bind_dev(hi_void)
{
    hal_cbm_set_cbm_mixer_prio(HAL_DISP_LAYER_VHD0, VO_MIX_PRIO0, HAL_CBMMIX1);
    hal_cbm_set_cbm_mixer_prio(HAL_DISP_LAYER_GFX0, VO_MIX_PRIO1, HAL_CBMMIX1);

    return;
}

hi_void vo_drv_set_dev_clk(vo_hal_dev vo_dev)
{
    hi_u32 ppc_sel = 0;
    hi_u32 frac = 0;
    hi_u32 postdiv1 = 0;
    hi_u32 postdiv2 = 0;
    hi_u32 fbdiv = 0;
    hi_u32 refdiv = 0;
    hi_u32 vdp_out_clk_sel = 0x0;
    hi_u32 lcd_mclk_div = 0x015E4C3;
    hi_u32 hdmiclk_div = 0x0;
    hi_u32 clk_div = 0x0;

    if (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_USER) {
        if (g_user_intfsync_info.user_intfsync_attr.user_sync_pll.fbdiv == 0) {
            printf("please set g_user_intfsync_info value!\n");
            return;
        }
        if (g_user_intfsync_info.user_intfsync_attr.clk_source == VO_CLK_SOURCE_PLL) {
            vdp_out_clk_sel = 0x0;
            sys_hal_vo_out_clk_sel(vdp_out_clk_sel);
            sys_hal_vo_hd_clk_sel(0);  // hd clk max

            sys_hal_set_vo_pll_fbdiv(g_user_intfsync_info.user_intfsync_attr.user_sync_pll.fbdiv);
            sys_hal_set_vo_pll_frac(g_user_intfsync_info.user_intfsync_attr.user_sync_pll.frac);
            sys_hal_set_vo_pll_refdiv(g_user_intfsync_info.user_intfsync_attr.user_sync_pll.refdiv);
            sys_hal_set_vo_pll_postdiv2(g_user_intfsync_info.user_intfsync_attr.user_sync_pll.postdiv2);
            sys_hal_set_vo_pll_postdiv1(g_user_intfsync_info.user_intfsync_attr.user_sync_pll.postdiv1);
        } else if (g_user_intfsync_info.user_intfsync_attr.clk_source == VO_CLK_SOURCE_LCDMCLK) {
            vdp_out_clk_sel = 0x6;
            sys_hal_vo_out_clk_sel(vdp_out_clk_sel);
            sys_hal_vo_hd_clk_sel(0);
            sys_hal_lcd_mclk_div(g_user_intfsync_info.user_intfsync_attr.lcd_mclk_div);
            sys_hal_vo_lcd_clk_en(HI_TRUE);
        } else {
            printf("vo clk source is illegal\n");
            return;
        }

        sys_hal_vo_hd_out_pctrl(g_user_intfsync_info.clk_reverse);
        sys_hal_vo_hd0_div_mode(g_user_intfsync_info.dev_div - 1);
        sys_hal_vo_hd_hdmi_clk_div(g_user_intfsync_info.pre_div - 1);

        return;
    }

    switch (g_hal_dev_cfg[vo_dev].out_sync) {
        case VO_OUTPUT_PAL:
        case VO_OUTPUT_NTSC:
        case VO_OUTPUT_576P50:
        case VO_OUTPUT_480P60: {
            // 27MHz
            fbdiv = 72;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0xf;
            break;
        }

        case VO_OUTPUT_1080P24:
        case VO_OUTPUT_1080P25:
        case VO_OUTPUT_1080P30:
        case VO_OUTPUT_720P50:
        case VO_OUTPUT_720P60:
        case VO_OUTPUT_1080I50:
        case VO_OUTPUT_1080I60:
        // for MIPI tx interface.
        case VO_OUTPUT_720x1280_60: {
            // 74.25MHz
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x7;
            break;
        }

        case VO_OUTPUT_1080P50:
        case VO_OUTPUT_1080P60:
        case VO_OUTPUT_1920x2160_30:
        // for MIPI tx interface.
        case VO_OUTPUT_1080x1920_60: {
            // 148.5MHz
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x3;
            break;
        }

        case VO_OUTPUT_640x480_60: {
            fbdiv = 67;      // 33;
            frac = 5035000;  // 9507089;
            refdiv = 2;      // 1;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0xf;
            break;
        }

        case VO_OUTPUT_800x600_60: {
            // 40MHz
            fbdiv = 160;
            frac = 0;
            refdiv = 3;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0xf;
            break;
        }
        case VO_OUTPUT_1024x768_60: {
            // 65MHz
            fbdiv = 130;  // 65;
            frac = 0;
            refdiv = 3;  // 12;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x7;
            break;
        }

        case VO_OUTPUT_1280x1024_60: {
            // 108MHz
            fbdiv = 72;  // 9;
            frac = 0;
            refdiv = 2;  // 1;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x3;
            break;
        }
        case VO_OUTPUT_1366x768_60: {
            // 85.5MHz
            fbdiv = 114;  // 171;
            frac = 0;
            refdiv = 2;  // 24;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x7;
            break;
        }
        case VO_OUTPUT_1440x900_60: {
            // 106.5MHz
            fbdiv = 71;  // 213;
            frac = 0;
            refdiv = 2;  // 24;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x3;
            break;
        }
        case VO_OUTPUT_1280x800_60: {
            // 83.5MHz
            fbdiv = 167;
            frac = 0;
            refdiv = 3;  // 24;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x7;
            break;
        }
        case VO_OUTPUT_1600x1200_60: {
            // 162MHz
            fbdiv = 162;  // 81;
            frac = 0;
            refdiv = 3;  // 6;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x3;
            break;
        }
        case VO_OUTPUT_1680x1050_60: {
            // 146.25MHz
            fbdiv = 146;  // 585;
            frac = 4195000;
            refdiv = 3;  // 48;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x3;
            break;
        }
        case VO_OUTPUT_1920x1200_60: {
            // 154MHz,VESA 1920 x 1600 at 60 hz (non-interlaced) CVT (reduced blanking)
            fbdiv = 154;  // 77;//77;
            frac = 0;
            refdiv = 3;  // 6;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x3;
            break;
        }
        case VO_OUTPUT_320x240_60: {
            vdp_out_clk_sel = 0x6;
            lcd_mclk_div = 0x2aE4C3;
            sys_hal_lcd_mclk_div(lcd_mclk_div);
            hdmiclk_div = 0x0;
            break;
        }

        case VO_OUTPUT_320x240_50: {
            vdp_out_clk_sel = 0x6;
            lcd_mclk_div = 0x152306;
            sys_hal_lcd_mclk_div(lcd_mclk_div);
            hdmiclk_div = 0x0;
            break;
        }

        case VO_OUTPUT_240x320_50: {
            vdp_out_clk_sel = 0x6;
            lcd_mclk_div = 0x182ed6;
            sys_hal_lcd_mclk_div(lcd_mclk_div);
            hdmiclk_div = 0x0;
            break;
        }

        case VO_OUTPUT_240x320_60: {
            vdp_out_clk_sel = 0x6;
            lcd_mclk_div = 0x90c54;
            sys_hal_lcd_mclk_div(lcd_mclk_div);
            hdmiclk_div = 0x0;
            break;
        }

        case VO_OUTPUT_800x600_50: {
            vdp_out_clk_sel = 0x6;
            lcd_mclk_div = 0x3a9cc2;  // 0x39cc92;
            sys_hal_lcd_mclk_div(lcd_mclk_div);
            hdmiclk_div = 0x0;
            break;
        }

        case VO_OUTPUT_2560x1440_30: {
            // 148.5MHz
            fbdiv = 119;     // 99;
            frac = 6295000;  // 0;
            refdiv = 3;      // 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x3;
            break;
        }
        case VO_OUTPUT_2560x1440_60: {
            // 238.75MHz
            fbdiv = 119;     // 99;
            frac = 6295000;  // 0;
            refdiv = 3;      // 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x1;
            break;
        }

        case VO_OUTPUT_2560x1600_60: {
            // 268.5MHz
            fbdiv = 537;
            frac = 0;
            refdiv = 12;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x1;
            break;
        }
        case VO_OUTPUT_3840x2160_24:
        case VO_OUTPUT_3840x2160_25:
        case VO_OUTPUT_3840x2160_30: {
            // 297MHz
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x1;
            break;
        }
        case VO_OUTPUT_3840x2160_60: {
            // 594MHz
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x0;
            break;
        }
        case VO_OUTPUT_7680x4320_30: {
            // 594MHz
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;

            hdmiclk_div = 0x0;
            break;
        }

        default: {
            return;
        }
    }

    sys_hal_vo_hd_clk_sel(ppc_sel);

    sys_hal_vo_hd_clk_sel(clk_div);

    sys_hal_vo_hd_hdmi_clk_div(hdmiclk_div);

    sys_hal_vo_out_clk_sel(vdp_out_clk_sel);

    sys_hal_set_vo_pll_fbdiv(fbdiv);
    sys_hal_set_vo_pll_frac(frac);
    sys_hal_set_vo_pll_refdiv(refdiv);
    sys_hal_set_vo_pll_postdiv2(postdiv2);
    sys_hal_set_vo_pll_postdiv1(postdiv1);
    return;
}

hi_void vo_drv_set_dev_dither_mode(vo_hal_dev VoDev , vdp_dither_mode DitherMode, vdp_dither_cfg* pstCfg)
{
    hal_disp_outputchannel vo_channel = HAL_DISP_CHANNEL_BUTT;
    hal_disp_dihter_sed    dither_sed;
    // filed declare
    hi_u32 dither_round_unlim    =  0;
    hi_u32 i_data_width_dither    =  0;
    hi_u32 o_data_width_dither    =  0;
    hi_u32 dither_en    =  0;
    hi_u32 dither_io_mode    =  0;
    hi_u32 dither_mode    =  0;
    hi_u32 dither_round    =  0;
    hi_u32 dither_domain_mode    =  0;
    hi_u32 dither_tap_mode    =  0;
    hi_u32 dither_sed_y0    =  0;
    hi_u32 dither_sed_u0    =  0;
    hi_u32 dither_sed_v0    =  0;
    hi_u32 dither_sed_w0    =  0;
    hi_u32 dither_sed_y1    =  0;
    hi_u32 dither_sed_u1    =  0;
    hi_u32 dither_sed_v1    =  0;
    hi_u32 dither_sed_w1    =  0;
    hi_u32 dither_sed_y2    =  0;
    hi_u32 dither_sed_u2    =  0;
    hi_u32 dither_sed_v2    =  0;
    hi_u32 dither_sed_w2    =  0;
    hi_u32 dither_sed_y3    =  0;
    hi_u32 dither_sed_u3    =  0;
    hi_u32 dither_sed_v3    =  0;
    hi_u32 dither_sed_w3    =  0;
    hi_u32 dither_thr_max    =  0;
    hi_u32 dither_thr_min    =  0;

    dither_en          = pstCfg->dither_en        ;
    dither_round       = pstCfg->dither_round     ;
    dither_round_unlim = pstCfg->dither_round_unlim;
    dither_domain_mode = pstCfg->dither_domain_mode;
    dither_tap_mode    = pstCfg->dither_tap_mode  ;
    dither_io_mode     = pstCfg->dither_io_mode  ;

    if (dither_io_mode == DITHER_IO_MODE_12_10) {
        dither_mode           = DITHER_MODE_10BIT;
        i_data_width_dither   = DITHER_IWIDTH_MODE_12BIT;
        o_data_width_dither   = DITHER_OWIDTH_MODE_10BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_12_8) {
        dither_mode           = DITHER_MODE_8BIT;
        i_data_width_dither   = DITHER_IWIDTH_MODE_12BIT;
        o_data_width_dither   = DITHER_OWIDTH_MODE_8BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_10_8) {
        dither_mode           = DITHER_MODE_8BIT;
        i_data_width_dither   = DITHER_IWIDTH_MODE_10BIT;
        o_data_width_dither   = DITHER_OWIDTH_MODE_8BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_10_6) {
        dither_mode           = DITHER_MODE_8BIT;
        i_data_width_dither   = DITHER_IWIDTH_MODE_10BIT;
        o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_9_6) {
        dither_mode           = DITHER_MODE_8BIT;
        i_data_width_dither   = DITHER_IWIDTH_MODE_9BIT;
        o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_8_6) {
        dither_mode           = DITHER_MODE_8BIT;
        i_data_width_dither   = DITHER_IWIDTH_MODE_8BIT;
        o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else if (dither_io_mode == 0) {
        dither_mode           = DITHER_MODE_8BIT;
        i_data_width_dither   = DITHER_IWIDTH_MODE_8BIT;
        o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else {
        return;
    }

    if (DitherMode == VDP_DITHER_MODE_TYP) {
        // typ mode
        dither_sed_y0          = 2147483647;
        dither_sed_u0          = 2147482647;
        dither_sed_v0          = 2147481647;
        dither_sed_w0          = 2147480647;
        dither_sed_y1          = dither_sed_y0;
        dither_sed_u1          = dither_sed_u0;
        dither_sed_v1          = dither_sed_v0;
        dither_sed_w1          = dither_sed_w0;
        dither_sed_y2          = dither_sed_y0;
        dither_sed_u2          = dither_sed_u0;
        dither_sed_v2          = dither_sed_v0;
        dither_sed_w2          = dither_sed_w0;
        dither_sed_y3          = dither_sed_y0;
        dither_sed_u3          = dither_sed_u0;
        dither_sed_v3          = dither_sed_v0;
        dither_sed_w3          = dither_sed_w0;
        dither_thr_max         = 60000;
        dither_thr_min         = 120;
    } else {
        return;
    }

    // VO_DRV_GetChannelHalId(VoDev,&vo_channel);
    vo_channel = HAL_DISP_CHANNEL_DHD0;
    // drv transfer
    hal_disp_set_dither_round_unlim(vo_channel, dither_round_unlim);
    hal_disp_set_dither_data_in_out(vo_channel, i_data_width_dither, o_data_width_dither);
    hal_disp_set_dither_en(vo_channel, dither_en);
    hal_disp_set_dither_mode(vo_channel, dither_mode);
    hal_disp_set_dither_round(vo_channel, dither_round);
    hal_disp_set_dither_domain_mode(vo_channel, dither_domain_mode);
    hal_disp_set_dither_tap_mode(vo_channel, dither_tap_mode);
    dither_sed.dither_sed_y0 = dither_sed_y0;
    dither_sed.dither_sed_u0 = dither_sed_u0;
    dither_sed.dither_sed_v0 = dither_sed_v0;
    dither_sed.dither_sed_w0 = dither_sed_w0;
    dither_sed.dither_sed_y1 = dither_sed_y1;
    dither_sed.dither_sed_u1 = dither_sed_u1;
    dither_sed.dither_sed_v1 = dither_sed_v1;
    dither_sed.dither_sed_w1 = dither_sed_w1;
    dither_sed.dither_sed_y2 = dither_sed_y2;
    dither_sed.dither_sed_u2 = dither_sed_u2;
    dither_sed.dither_sed_v2 = dither_sed_v2;
    dither_sed.dither_sed_w2 = dither_sed_w2;
    dither_sed.dither_sed_y3 = dither_sed_y3;
    dither_sed.dither_sed_u3 = dither_sed_u3;
    dither_sed.dither_sed_v3 = dither_sed_v3;
    dither_sed.dither_sed_w3 = dither_sed_w3;
    hal_disp_set_dither_sed(vo_channel, &dither_sed);
    hal_disp_set_dither_thr_min_max(vo_channel, dither_thr_min, dither_thr_max);
}
hi_void vo_drv_set_dev_dither_cfg(vo_hal_dev vo_dev, hi_u32 in_bit_width, hi_u32 out_bit_width)
{
    vdp_dither_cfg  dither_cfg;

    if ((in_bit_width == 10) &&  (out_bit_width == 8)) {
        dither_cfg.dither_en          = 1;
        dither_cfg.dither_round       = 1;
        dither_cfg.dither_round_unlim = 1;
        dither_cfg.dither_domain_mode = 1;
        dither_cfg.dither_tap_mode    = 1;
        dither_cfg.dither_io_mode  = DITHER_IO_MODE_12_8;

        vo_drv_set_dev_dither_mode(vo_dev, VDP_DITHER_MODE_TYP , &dither_cfg);
        hal_disp_set_dither_en(vo_dev, HI_TRUE);
        hal_disp_set_dither_data_in_out(vo_dev, 0x4, 0x5);  // 4:12bit     // 5:10bit;3:8bit
    } else if ((in_bit_width == 10) &&  (out_bit_width == 6)) {
        dither_cfg.dither_en          = 1;
        dither_cfg.dither_round       = 0;
        dither_cfg.dither_round_unlim = 1;
        dither_cfg.dither_domain_mode = 1;
        dither_cfg.dither_tap_mode    = 1;
        dither_cfg.dither_io_mode  = DITHER_IO_MODE_10_6;
        vo_drv_set_dev_dither_mode(vo_dev, VDP_DITHER_MODE_TYP , &dither_cfg);
        hal_disp_set_dither_en(vo_dev, HI_TRUE);
        hal_disp_set_dither_data_in_out(vo_dev, 0x2, 0x1);  // 4:12bit     // 5:10bit;3:8bit
    } else if (((in_bit_width  == 10) &&  (out_bit_width == 10)) ||
             ((in_bit_width  == 8) &&  (out_bit_width == 8))) {
        hal_disp_set_dither_en(vo_dev, HI_FALSE);
    }
}

hi_u32 vo_drv_get_dev_vtth(vo_hal_dev vo_dev)
{
    hi_u32 dev_vtth;

    switch (g_hal_dev_cfg[vo_dev].out_sync) {
        case VO_OUTPUT_3840x2160_60:
        case VO_OUTPUT_3840x2160_50:
        case VO_OUTPUT_4096x2160_60:
        case VO_OUTPUT_4096x2160_50:
            dev_vtth = 4 * VO_HD_VTTH_WATERLINE;
            break;
        case VO_OUTPUT_2560x1600_60:
        case VO_OUTPUT_3840x2160_24:
        case VO_OUTPUT_3840x2160_25:
        case VO_OUTPUT_3840x2160_30:
        case VO_OUTPUT_4096x2160_24:
        case VO_OUTPUT_4096x2160_25:
        case VO_OUTPUT_4096x2160_30:
            dev_vtth = 2 * VO_HD_VTTH_WATERLINE;
            break;
        default:
            dev_vtth = VO_HD_VTTH_WATERLINE;
    }

    return dev_vtth;
}

/* turn on clk */
hi_void vo_drv_set_all_crg_clk(hi_bool clk_en)
{
    hi_bool vo_clk_en = clk_en;

    sys_hal_vo_cfg_clk_en(vo_clk_en);
    sys_hal_vo_apb_clk_en(vo_clk_en);
    sys_hal_vo_bus_clk_en(vo_clk_en);
    return;
}

hi_u32 vo_drv_get_dev_intf_type(vo_hal_dev vo_dev)
{
    return g_hal_dev_cfg[vo_dev].intf_type;
}

void vo_drv_set_cbm_bkg(hi_s32 vo_dev)
{
    hal_disp_bkcolor bkg;
    hi_u32 yuv_bk_grd;
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    vo_intf_type intf_type;
    intf_type = hal_dev_cfg->intf_type;

    if (VO_INTF_LCD & intf_type ||
        VO_INTF_LCD_6BIT & intf_type ||
        VO_INTF_LCD_8BIT & intf_type ||
        VO_INTF_LCD_16BIT & intf_type ||
        VO_INTF_LCD_18BIT & intf_type ||
        VO_INTF_LCD_24BIT & intf_type ||
        VO_INTF_MIPI & intf_type ||
        VO_INTF_MIPI_SLAVE & intf_type) {
        bkg.bkg_y = RGB_R(hal_dev_cfg->bk_grd);
        bkg.bkg_cb = RGB_G(hal_dev_cfg->bk_grd);
        bkg.bkg_cr = RGB_B(hal_dev_cfg->bk_grd);
        bkg.bkg_y = bkg.bkg_y << 2;
        bkg.bkg_cb = bkg.bkg_cb << 2;
        bkg.bkg_cr = bkg.bkg_cr << 2;
    } else {
        yuv_bk_grd = rgb_to_yuv_full(hal_dev_cfg->bk_grd);
        bkg.bkg_y = YUV_Y(yuv_bk_grd);
        bkg.bkg_cb = YUV_U(yuv_bk_grd);
        bkg.bkg_cr = YUV_V(yuv_bk_grd);
    }

    hal_cbm_set_cbm_bkg(HAL_CBMMIX1, &bkg);

}

void vo_drv_get_intf_property(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    memcpy(sync_info, &g_sync_timing[hal_dev_cfg->out_sync], sizeof(hal_disp_syncinfo));
    inv->hs_inv = sync_info->ihs ? 1 : 0;
    inv->vs_inv = sync_info->ivs ? 1 : 0;
    inv->dv_inv = sync_info->idv ? 1 : 0;
}

void vo_drv_set_intf_hdmi_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    hi_bool hdmi_clk_en = 0x1;
    hi_u32 hd0_div_mod = 0x0;
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    sys_hal_vo_hdmi_clk_en(hdmi_clk_en);     // [27] VDP hdmiclk en.
    sys_hal_vo_hd0_div_mode(hd0_div_mod);  // [12:13] VDP HD0 div mode

    if ((hal_dev_cfg->out_sync == VO_OUTPUT_576P50) ||
        (hal_dev_cfg->out_sync == VO_OUTPUT_480P60)) {
        inv->hs_inv = 1 - inv->hs_inv;
        inv->vs_inv = 1 - inv->vs_inv;
    }

}

void vo_drv_set_intf_bt1120_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    hi_u32 data_mode;
    sys_hal_vo_bt_clk_en(HI_TRUE);

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_BT1120);
    hal_intf_bt_set_dfir_en(0x1);

    data_mode = 5;
    sys_hal_lcd_data_mode(data_mode);
}
void vo_drv_set_intf_mipi_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    U_INTF_LCD_CTRL LCD_CTRL;
    hi_bool mipi_clk_en = 0x1;
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    sys_hal_vo_mipi_clk_en(mipi_clk_en);

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_MIPI);

    LCD_CTRL.bits.hdmi_mode = 1;
    hal_disp_set_intf_ctrl(hal_dev_cfg->intf_type, &(LCD_CTRL.u32));
    hal_intf_bt_set_dfir_en(0x1);
    inv->hs_inv = 0;
    inv->vs_inv = 0;
    inv->dv_inv = 0;
}

void vo_drv_set_intf_6bit_lcd_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, vo_intf_sync out_sync)
{
    hi_bool clk_reverse;
    hi_u32 hd0_div_mode;
    hi_u32 data_mode;
    U_INTF_LCD_CTRL LCD_CTRL;

    hd0_div_mode  = 2;
    data_mode = 4;
    clk_reverse = HI_TRUE;

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_LCD_6BIT);
    LCD_CTRL.bits.lcd_serial_mode    = 1;
    LCD_CTRL.bits.lcd_serial_perd    = 0;
    LCD_CTRL.bits.lcd_parallel_order = 0;
    LCD_CTRL.bits.lcd_data_inv       = 0;
    LCD_CTRL.bits.lcd_parallel_mode  = 0;

    sys_hal_lcd_data_mode(data_mode);
    hal_disp_set_intf_ctrl(VO_INTF_LCD_6BIT, &(LCD_CTRL.u32));

    if (out_sync != VO_OUTPUT_USER) {
        hal_disp_set_lcd_serial_perd(LCD_CTRL.bits.lcd_serial_perd);
        sys_hal_vo_hd_out_pctrl(clk_reverse);
        sys_hal_vo_hd0_div_mode(hd0_div_mode);
    }
}

void vo_drv_set_intf_8bit_lcd_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, vo_intf_sync out_sync)
{
    hi_bool clk_reverse;
    hi_u32 hd0_div_mode;
    hi_u32 data_mode;
    U_INTF_LCD_CTRL LCD_CTRL;

    hd0_div_mode  = 3;
    data_mode = 3;
    clk_reverse = HI_TRUE;

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_LCD_6BIT);
    LCD_CTRL.bits.hdmi_mode          = 1;
    LCD_CTRL.bits.lcd_serial_mode    = 1;
    LCD_CTRL.bits.lcd_serial_perd    = 1;
    LCD_CTRL.bits.lcd_parallel_order = 0;
    LCD_CTRL.bits.lcd_data_inv       = 0;
    LCD_CTRL.bits.lcd_parallel_mode  = 1;

    sys_hal_lcd_data_mode(data_mode);
    hal_disp_set_intf_ctrl(VO_INTF_LCD_8BIT, &(LCD_CTRL.u32));

    if (out_sync != VO_OUTPUT_USER) {
        hal_disp_set_lcd_serial_perd(LCD_CTRL.bits.lcd_serial_perd);
        sys_hal_vo_hd_out_pctrl(clk_reverse);
        sys_hal_vo_hd0_div_mode(hd0_div_mode);
    }
}

void vo_drv_set_intf_16bit_lcd_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, vo_intf_sync out_sync)
{
    hi_bool clk_reverse;
    hi_u32 hd0_div_mode;
    hi_u32 data_mode;
    U_INTF_LCD_CTRL LCD_CTRL;

    hd0_div_mode  = 0;
    data_mode = 2;
    clk_reverse = HI_TRUE;

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_LCD_16BIT);
    LCD_CTRL.bits.lcd_serial_mode    = 0;
    LCD_CTRL.bits.lcd_serial_perd    = 0;
    LCD_CTRL.bits.lcd_parallel_order = 0;
    LCD_CTRL.bits.lcd_data_inv       = 0;
    LCD_CTRL.bits.lcd_parallel_mode  = 1;

    sys_hal_lcd_data_mode(data_mode);
    hal_disp_set_intf_ctrl(VO_INTF_LCD_16BIT, &(LCD_CTRL.u32));

    if (out_sync != VO_OUTPUT_USER) {
        hal_disp_set_lcd_serial_perd(LCD_CTRL.bits.lcd_serial_perd);
        sys_hal_vo_hd_out_pctrl(clk_reverse);
        sys_hal_vo_hd0_div_mode(hd0_div_mode);
    }
}

void vo_drv_set_intf_18bit_lcd_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, vo_intf_sync out_sync)
{
    hi_bool clk_reverse;
    hi_u32 hd0_div_mode;
    hi_u32 data_mode;
    U_INTF_LCD_CTRL LCD_CTRL;

    hd0_div_mode  = 0;
    data_mode = 1;
    clk_reverse = HI_TRUE;

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_LCD_6BIT);
    LCD_CTRL.bits.lcd_serial_mode    = 0;
    LCD_CTRL.bits.lcd_serial_perd    = 0;
    LCD_CTRL.bits.lcd_parallel_order = 0;
    LCD_CTRL.bits.lcd_data_inv       = 0;
    LCD_CTRL.bits.lcd_parallel_mode  = 1;

    sys_hal_lcd_data_mode(data_mode);
    hal_disp_set_intf_ctrl(VO_INTF_LCD_6BIT, &(LCD_CTRL.u32));

    if (out_sync != VO_OUTPUT_USER) {
        hal_disp_set_lcd_serial_perd(LCD_CTRL.bits.lcd_serial_perd);
        sys_hal_vo_hd_out_pctrl(clk_reverse);
        sys_hal_vo_hd0_div_mode(hd0_div_mode);
    }
}

void vo_drv_set_intf_24bit_lcd_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, vo_intf_sync out_sync)
{
    hi_bool clk_reverse;
    hi_u32 hd0_div_mode;
    hi_u32 data_mode;
    U_INTF_LCD_CTRL LCD_CTRL;

    hd0_div_mode  = 0;
    data_mode = 0;
    clk_reverse = HI_FALSE;

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_LCD_24BIT);
    LCD_CTRL.bits.lcd_serial_mode    = 0;
    LCD_CTRL.bits.lcd_serial_perd    = 0;
    LCD_CTRL.bits.lcd_parallel_order = 0;
    LCD_CTRL.bits.lcd_data_inv       = 0;
    LCD_CTRL.bits.lcd_parallel_mode  = 1;

    sys_hal_lcd_data_mode(data_mode);
    hal_disp_set_intf_ctrl(VO_INTF_LCD_6BIT, &(LCD_CTRL.u32));

    if (out_sync != VO_OUTPUT_USER) {
        hal_disp_set_lcd_serial_perd(LCD_CTRL.bits.lcd_serial_perd);
        sys_hal_vo_hd_out_pctrl(clk_reverse);
        sys_hal_vo_hd0_div_mode(hd0_div_mode);
    }
}

void vo_drv_set_intf_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    vo_intf_sync out_sync;
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    out_sync = hal_dev_cfg->out_sync;

    if (VO_INTF_HDMI & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_hdmi_cfg(vo_dev, sync_info, inv);
    }

    if (VO_INTF_BT1120 & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_bt1120_cfg(vo_dev, sync_info, inv);
    }

    if (VO_INTF_MIPI & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_mipi_cfg(vo_dev, sync_info, inv);
    }

    if(VO_INTF_LCD_6BIT & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_6bit_lcd_cfg(vo_dev,sync_info,out_sync);
    }

    if(VO_INTF_LCD_8BIT & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_8bit_lcd_cfg(vo_dev,sync_info,out_sync);
    }

    if(VO_INTF_LCD_16BIT & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_16bit_lcd_cfg(vo_dev,sync_info,out_sync);
    }

    if(VO_INTF_LCD_18BIT & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_18bit_lcd_cfg(vo_dev,sync_info,out_sync);
    }

    if(VO_INTF_LCD_24BIT & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_24bit_lcd_cfg(vo_dev,sync_info,out_sync);
    }
}

void vo_drv_set_dev_multichn(hi_s32 vo_dev)
{
    HAL_MULTICHN_EN multi_chn_en;

    multi_chn_en = HAL_MULTICHN_EN_1P1C;
    hal_disp_set_dev_multi_chn_en(vo_dev, multi_chn_en);
}

void vo_drv_set_dev_clip_by_intf(hi_s32 vo_dev)
{
    /* set clip */
    if (VO_INTF_HDMI & g_hal_dev_cfg[vo_dev].intf_type) {
        hal_disp_clip clip_data = { 0x10, 0x10, 0x10, 0x3ff, 0x3ff, 0x3ff };
        hal_disp_set_intf_clip(VO_INTF_HDMI, HI_TRUE, &clip_data);
    }
    if (VO_INTF_BT1120 & g_hal_dev_cfg[vo_dev].intf_type) {
        hal_disp_clip clip_data = { 0x40, 0x40, 0x40, 0x3ac, 0x3ac, 0x3ac };
        hal_disp_set_intf_clip(VO_INTF_BT1120, HI_TRUE, &clip_data);
    }
}

void vo_drv_set_dev_int_mode(hi_s32 vo_dev, hal_disp_syncinfo *sync_info)
{
    vo_int_mode int_mode;
    if (sync_info->iop == 0) {
        int_mode = VO_INT_MODE_FIELD;
    } else {
        int_mode = VO_INT_MODE_FRAME;
    }
    vo_drv_int_set_mode(vo_dev, int_mode);
    vo_drv_int_reg_up_mode(vo_dev, int_mode);
}

hi_void vo_drv_set_dev_dither(hi_s32 VoDev)
{
    if((VO_INTF_LCD_6BIT & g_hal_dev_cfg[VoDev].intf_type) ||
        (VO_INTF_LCD_16BIT & g_hal_dev_cfg[VoDev].intf_type) ||
        (VO_INTF_LCD_18BIT & g_hal_dev_cfg[VoDev].intf_type)) {
        vo_drv_set_dev_dither_cfg(VoDev, 10, 6);
    } else {
        vo_drv_set_dev_dither_cfg(VoDev, 10, 8);
    }
}

hi_void vo_drv_open(hi_s32 vo_dev)
{
    hal_disp_syncinfo sync_info;
    hi_u16 vtth_line;
    hal_disp_syncinv inv = {0};

    vo_drv_set_all_crg_clk(HI_TRUE);

    hal_disp_set_intf_enable(vo_dev, HI_FALSE);

    sys_hal_vo_dev_clk_en(0, HI_TRUE);
    sys_hal_vo_dev_clk_en(1, HI_TRUE);

    vo_drv_set_cbm_bkg(vo_dev);

    /* set interface property */
    vo_drv_get_intf_property(vo_dev, &sync_info, &inv);

    vo_drv_set_intf_cfg(vo_dev, &sync_info, &inv);

    hal_disp_set_intf_sync(vo_dev, &sync_info, &inv);

    vo_drv_set_dev_multichn(vo_dev);

    vo_drv_set_dev_clip_by_intf(vo_dev);
    vo_drv_set_dev_int_mode(vo_dev, &sync_info);

    vtth_line = sync_info.vact + sync_info.vfb + sync_info.vbb - vo_drv_get_dev_vtth(vo_dev);
    hal_disp_set_vt_thd(vo_dev, vtth_line);
    vo_drv_set_dev_dither(vo_dev);

    hal_disp_set_intf_enable(vo_dev, HI_TRUE);
    vo_drv_dev_int_enable(vo_dev, HI_TRUE);
    hal_disp_set_reg_up(vo_dev);
    g_hal_dev_cfg[vo_dev].enable = HI_TRUE;

    return;
}

hi_void vo_drv_close(hi_s32 vo_dev)
{
    hi_u32 i;

    hal_disp_set_intf_enable(vo_dev, HI_FALSE);
    hal_disp_set_reg_up(vo_dev);

    udelay(25 * 1000);

    hal_disp_set_intf_mux_sel(vo_dev, HAL_DISP_INTF_BUTT);

    g_hal_dev_cfg[vo_dev].enable = HI_FALSE;

    for (i = 0; i < VO_DEV_MAX_NUM; i++) {
        if (g_hal_dev_cfg[vo_dev].enable) {
            break;
        }
    }

    if (i == VO_DEV_MAX_NUM) {
        vo_drv_set_all_crg_clk(HI_FALSE);
    }

    return;
}

hi_void vo_drv_default_setting(hi_void)
{
    // set each layer global alpha
    hal_layer_set_layer_galpha(HAL_DISP_LAYER_VHD0, 255);

    /* outstanding */
    vo_drv_layer_enable(HAL_DISP_LAYER_VHD0, HI_FALSE);

    return;
}

hi_void vo_drv_func_get_cvfir_pq_cfg(vo_zme_ds_info *ds_info, vo_zme_mode zme_mode,
                               vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 zme_vprec;

    if (zme_mode == VO_ZME_TYP) {
        zme_vprec = ds_info->zme_vprec;
        comm_pq_cfg->vluma_offset = 0;    //  v_phase_rand   ;
        comm_pq_cfg->vchroma_offset = 0;  //  v_phase_rand_c ;
        comm_pq_cfg->vbluma_offset = -1 * zme_vprec / 2;
        comm_pq_cfg->vbchroma_offset = -1 * zme_vprec / 2;
        comm_pq_cfg->vl_flatdect_mode = 1;
        comm_pq_cfg->vl_coringadj_en = 1;
        comm_pq_cfg->vl_gain = 32;
        comm_pq_cfg->vl_coring = 16;
        comm_pq_cfg->vc_flatdect_mode = 1;
        comm_pq_cfg->vc_coringadj_en = 1;
        comm_pq_cfg->vc_gain = 32;
        comm_pq_cfg->vc_coring = 16;
        comm_pq_cfg->lhfir_offset = 0;
        comm_pq_cfg->chfir_offset = 0;
        comm_pq_cfg->hl_flatdect_mode = 1;
        comm_pq_cfg->hl_coringadj_en = 1;
        comm_pq_cfg->hl_gain = 32;
        comm_pq_cfg->hl_coring = 16;
        comm_pq_cfg->hc_flatdect_mode = 1;
        comm_pq_cfg->hc_coringadj_en = 1;
        comm_pq_cfg->hc_gain = 32;
        comm_pq_cfg->hc_coring = 16;
    }
}

static hi_void vo_drv_set_layer_cvfir_mode(hi_u32 layer, vo_zme_mode zme_mode, vdp_v1_cvfir_cfg *cfg)
{
    // filed declare
    hi_u32 vzme_ck_gt_en;
    hi_u32 out_pro;
    hi_u32 out_fmt;
    hi_u32 out_height;
    hi_u32 cvfir_en;
    hi_u32 cvmid_en;
    hi_u32 cvfir_mode;
    hi_u32 vratio;
    hi_u32 vchroma_offset;
    hi_u32 vbchroma_offset;
    vo_zme_ds_info ds_info = {0};
    vo_zme_comm_pq_cfg comm_pq_cfg = {0};

    ds_info.zme_vprec = ZME_VPREC;
    ds_info.zme_hprec = ZME_HPREC;

    vzme_ck_gt_en = cfg->ck_gt_en;
    cvfir_en = cfg->cvfir_en;
    cvfir_mode = cfg->cvfir_mode;
    cvmid_en = cfg->cvmid_en;

    out_pro = cfg->out_pro;
    out_fmt = cfg->out_fmt;
    out_height = cfg->in_height;
    vratio = ds_info.zme_vprec;

    vo_drv_func_get_cvfir_pq_cfg(&ds_info, zme_mode, &comm_pq_cfg);

    vchroma_offset = comm_pq_cfg.vchroma_offset;  //  v_phase_rand_c ;
    vbchroma_offset = comm_pq_cfg.vbchroma_offset;

    // drv transfer
    hal_video_cvfir_set_out_height(layer, out_height);
    hal_video_cvfir_set_out_fmt(layer, out_fmt);
    hal_video_cvfir_set_out_pro(layer, out_pro);
    hal_video_cvfir_set_vzme_ck_gt_en(layer, vzme_ck_gt_en);

    hal_video_cvfir_set_cvfir_en(layer, cvfir_en);
    hal_video_cvfir_set_cvmid_en(layer, cvmid_en);
    hal_video_cvfir_set_cvfir_mode(layer, cvfir_mode);
    hal_video_cvfir_set_vratio(layer, vratio);

    hal_video_cvfir_set_v_chroma_offset(layer, vchroma_offset);
    hal_video_cvfir_set_vb_chroma_offset(layer, vbchroma_offset);
}

hi_void vo_vid_set_zme_enable(hi_u32 layer, vdp_vid_ip_cfg *vid_cfg)
{
    vdp_v1_cvfir_cfg cvfir_cfg;
    cvfir_cfg.hfir_order = 0;
    cvfir_cfg.lhfir_en = 0;
    cvfir_cfg.chfir_en = 0;
    cvfir_cfg.lhmid_en = 0;
    cvfir_cfg.chmid_en = 0;
    cvfir_cfg.lhfir_mode = 0;
    cvfir_cfg.chfir_mode = 0;
    cvfir_cfg.hl_shootctrl_en = 0;
    cvfir_cfg.hl_shootctrl_mode = 0;
    cvfir_cfg.hc_shootctrl_en = 0;
    cvfir_cfg.hc_shootctrl_mode = 0;
    cvfir_cfg.lvfir_en = 0;
    cvfir_cfg.lvmid_en = 0;
    cvfir_cfg.lvfir_mode = 0;
    cvfir_cfg.vl_shootctrl_en = 0;
    cvfir_cfg.vl_shootctrl_mode = 0;
    cvfir_cfg.vc_shootctrl_en = 0;
    cvfir_cfg.vc_shootctrl_mode = 0;

    /* CVFIR */
    cvfir_cfg.ck_gt_en = 0;
    cvfir_cfg.cvfir_en = 1;
    cvfir_cfg.cvmid_en = 0;
    cvfir_cfg.cvfir_mode = 0;
    cvfir_cfg.out_pro = VDP_RMODE_PROGRESSIVE;
    cvfir_cfg.out_fmt = VDP_PROC_FMT_SP_422;
    cvfir_cfg.in_width = vid_cfg->vid_iw;
    cvfir_cfg.in_height = vid_cfg->vid_ih;
    cvfir_cfg.out_width = vid_cfg->vid_ow;
    cvfir_cfg.out_height = vid_cfg->vid_oh;
    vo_drv_set_layer_cvfir_mode(layer, VO_ZME_TYP, &cvfir_cfg);
}

hi_void vo_drv_layer_csc_enable(vo_hal_layer vo_layer, hi_bool csc_en)
{
    hal_layer_set_csc_en(vo_layer, csc_en);
    return;
}
hi_s32 vo_drv_get_csc_matrix(hal_csc_mode csc_mode, const csc_coef **csc_tmp)
{
    switch (csc_mode) {
        case HAL_CSC_MODE_BT601_TO_BT601:
        case HAL_CSC_MODE_BT709_TO_BT709:
        case HAL_CSC_MODE_RGB_TO_RGB:
            *csc_tmp = &g_csc_init;
            break;
        case HAL_CSC_MODE_BT709_TO_BT601:
            *csc_tmp = &g_csc_yuv_to_yuv_709_601;
            break;
        case HAL_CSC_MODE_BT601_TO_BT709:
            *csc_tmp = &g_csc_yuv_to_yuv_601_709;
            break;
        case HAL_CSC_MODE_BT601_TO_RGB_PC:
            *csc_tmp = &g_csc_yuv601_to_rgb_pc;
            break;
        case HAL_CSC_MODE_BT709_TO_RGB_PC:
            *csc_tmp = &g_csc_yuv709_to_rgb_pc;
            break;
        case HAL_CSC_MODE_RGB_TO_BT601_PC:
            *csc_tmp = &g_csc_rgb_to_yuv601_pc;
            break;
        case HAL_CSC_MODE_RGB_TO_BT709_PC:
            *csc_tmp = &g_csc_rgb_to_yuv709_pc;
            break;
        case HAL_CSC_MODE_RGB_TO_BT601_TV:
            *csc_tmp = &g_csc_rgb_to_yuv601_tv;
            break;
        case HAL_CSC_MODE_RGB_TO_BT709_TV:
            *csc_tmp = &g_csc_rgb_to_yuv709_tv;
            break;
        default:
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

hi_void vo_drv_get_hal_cscvalue(vo_csc *vo_csc, hal_csc_value *hal_csc_value)
{
    hal_csc_value->luma = (hi_s32)vo_csc->luma * 64 / 100 - 32;
    hal_csc_value->cont = ((hi_s32)vo_csc->contrast - 50) * 2 + 100;
    hal_csc_value->hue = (hi_s32)vo_csc->hue * 60 / 100;
    hal_csc_value->satu = ((hi_s32)vo_csc->satuature - 50) * 2 + 100;
}

hi_void vo_drv_set_csc_coef_y2r(hal_csc_value *hal_csc_value, const csc_coef *csc_tmp, csc_coef *csc_coef)
{
    hi_s32 luma;
    hi_s32 contrast;
    hi_s32 hue;
    hi_s32 satu;

    luma = hal_csc_value->luma;
    contrast = hal_csc_value->cont;
    hue = hal_csc_value->hue;
    satu = hal_csc_value->satu;


    csc_coef->csc_coef00 = (contrast * csc_tmp->csc_coef00) / 100;
    csc_coef->csc_coef01 = (contrast * satu * ((csc_tmp->csc_coef01 * COS_TABLE[hue] -
                                                        csc_tmp->csc_coef02 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef02 = (contrast * satu * ((csc_tmp->csc_coef01 * SIN_TABLE[hue] +
                                                        csc_tmp->csc_coef02 * COS_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef10 = (contrast * csc_tmp->csc_coef10) / 100;
    csc_coef->csc_coef11 = (contrast * satu * ((csc_tmp->csc_coef11 * COS_TABLE[hue] -
                                                        csc_tmp->csc_coef12 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef12 = (contrast * satu * ((csc_tmp->csc_coef11 * SIN_TABLE[hue] +
                                                        csc_tmp->csc_coef12 * COS_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef20 = (contrast * csc_tmp->csc_coef20) / 100;
    csc_coef->csc_coef21 = (contrast * satu * ((csc_tmp->csc_coef21 * COS_TABLE[hue] -
                                                        csc_tmp->csc_coef22 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef22 = (contrast * satu * ((csc_tmp->csc_coef21 * SIN_TABLE[hue] +
                                                        csc_tmp->csc_coef22 * COS_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_in_dc0 += (contrast != 0) ? (luma * 100 / contrast) : luma * 100;
}

hi_void vo_drv_set_csc_coef_r2y(hal_csc_value *hal_csc_value, const csc_coef *csc_tmp, csc_coef *csc_coef)
{
    hi_s32 luma;
    hi_s32 contrast;
    hi_s32 hue;
    hi_s32 satu;

    luma = hal_csc_value->luma;
    contrast = hal_csc_value->cont;
    hue = hal_csc_value->hue;
    satu = hal_csc_value->satu;


    csc_coef->csc_coef00 = (contrast * csc_tmp->csc_coef00) / 100;
    csc_coef->csc_coef01 = (contrast * csc_tmp->csc_coef01) / 100;
    csc_coef->csc_coef02 = (contrast * csc_tmp->csc_coef02) / 100;
    csc_coef->csc_coef10 = (contrast * satu * ((csc_tmp->csc_coef10 * COS_TABLE[hue] +
                                                        csc_tmp->csc_coef20 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef11 = (contrast * satu * ((csc_tmp->csc_coef11 * COS_TABLE[hue] +
                                                        csc_tmp->csc_coef21 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef12 = (contrast * satu * ((csc_tmp->csc_coef12 * COS_TABLE[hue] +
                                                        csc_tmp->csc_coef22 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef20 = (contrast * satu * ((csc_tmp->csc_coef20 * COS_TABLE[hue] -
                                                        csc_tmp->csc_coef10 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef21 = (contrast * satu * ((csc_tmp->csc_coef21 * COS_TABLE[hue] -
                                                        csc_tmp->csc_coef11 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_coef22 = (contrast * satu * ((csc_tmp->csc_coef22 * COS_TABLE[hue] -
                                                        csc_tmp->csc_coef12 * SIN_TABLE[hue]) / 1000)) / 10000;
    csc_coef->csc_out_dc0 += luma;
}

hi_void vo_drv_calc_csc_matrix(vo_csc *csc, hal_csc_mode csc_mode, csc_coef *cst_coef)
{
    const csc_coef *csc_tmp = NULL;
    hi_s32 ret;
    hal_csc_value hal_csc_value = {0};

    vo_drv_get_hal_cscvalue(csc, &hal_csc_value);

    ret = vo_drv_get_csc_matrix(csc_mode, &csc_tmp);
    if (ret != HI_SUCCESS) {
        return;
    }

    cst_coef->csc_in_dc0 = csc_tmp->csc_in_dc0;
    cst_coef->csc_in_dc1 = csc_tmp->csc_in_dc1;
    cst_coef->csc_in_dc2 = csc_tmp->csc_in_dc2;
    cst_coef->csc_out_dc0 = csc_tmp->csc_out_dc0;
    cst_coef->csc_out_dc1 = csc_tmp->csc_out_dc1;
    cst_coef->csc_out_dc2 = csc_tmp->csc_out_dc2;

    if ((csc_mode == HAL_CSC_MODE_BT601_TO_RGB_PC) || (csc_mode == HAL_CSC_MODE_BT709_TO_RGB_PC) ||
        (csc_mode == HAL_CSC_MODE_BT601_TO_RGB_TV) || (csc_mode == HAL_CSC_MODE_BT709_TO_RGB_TV)) {
        vo_drv_set_csc_coef_y2r(&hal_csc_value, csc_tmp, cst_coef);
    } else {
        vo_drv_set_csc_coef_r2y(&hal_csc_value, csc_tmp, cst_coef);
    }
    return;
}

hi_void vo_drv_get_hal_cscmode(vo_csc_matrix csc_matrix, hal_csc_mode *csc_mode)
{
    if (csc_matrix == VO_CSC_MATRIX_RGB_TO_BT601_PC) {
        *csc_mode = HAL_CSC_MODE_RGB_TO_BT601_PC;
    } else if (csc_matrix == VO_CSC_MATRIX_RGB_TO_BT709_PC) {
        *csc_mode = HAL_CSC_MODE_RGB_TO_BT709_PC;
    } else if (csc_matrix == VO_CSC_MATRIX_RGB_TO_BT601_TV) {
        *csc_mode = HAL_CSC_MODE_RGB_TO_BT601_TV;
    } else if (csc_matrix == VO_CSC_MATRIX_RGB_TO_BT709_TV) {
        *csc_mode = HAL_CSC_MODE_RGB_TO_BT709_TV;
    } else if (csc_matrix == VO_CSC_MATRIX_BT601_TO_RGB_PC) {
        *csc_mode = HAL_CSC_MODE_BT601_TO_RGB_PC;
    } else if (csc_matrix == VO_CSC_MATRIX_BT709_TO_RGB_PC) {
        *csc_mode = HAL_CSC_MODE_BT709_TO_RGB_PC;
    } else if (csc_matrix == VO_CSC_MATRIX_IDENTITY) {
        *csc_mode = HAL_CSC_MODE_RGB_TO_RGB;
    } else {
        *csc_mode = HAL_CSC_MODE_RGB_TO_RGB;
    }
}

hi_s32 graphic_drv_set_csc_coef(hal_disp_layer gfx_layer, vo_csc *gfx_csc, csc_coef_param *csc_coef_param)
{
    csc_coef csc_coef;
    hal_csc_mode csc_mode = HAL_CSC_MODE_RGB_TO_BT601_TV;

    hi_u32 pre = 8;
    hi_u32 dc_pre = 4;

    vo_drv_get_hal_cscmode(gfx_csc->csc_matrix, &csc_mode);

    vo_drv_calc_csc_matrix(gfx_csc, csc_mode, &csc_coef);

    csc_coef.new_csc_clip_max = GFX_CSC_CLIP_MAX;
    csc_coef.new_csc_clip_min = GFX_CSC_CLIP_MIN;
    csc_coef.new_csc_scale2p = GFX_CSC_SCALE;

    csc_coef.csc_coef00 = (hi_s32)pre * csc_coef.csc_coef00 * 1024 / 1000;
    csc_coef.csc_coef01 = (hi_s32)pre * csc_coef.csc_coef01 * 1024 / 1000;
    csc_coef.csc_coef02 = (hi_s32)pre * csc_coef.csc_coef02 * 1024 / 1000;
    csc_coef.csc_coef10 = (hi_s32)pre * csc_coef.csc_coef10 * 1024 / 1000;
    csc_coef.csc_coef11 = (hi_s32)pre * csc_coef.csc_coef11 * 1024 / 1000;
    csc_coef.csc_coef12 = (hi_s32)pre * csc_coef.csc_coef12 * 1024 / 1000;
    csc_coef.csc_coef20 = (hi_s32)pre * csc_coef.csc_coef20 * 1024 / 1000;
    csc_coef.csc_coef21 = (hi_s32)pre * csc_coef.csc_coef21 * 1024 / 1000;
    csc_coef.csc_coef22 = (hi_s32)pre * csc_coef.csc_coef22 * 1024 / 1000;

    csc_coef.csc_in_dc0 = (hi_s32)dc_pre * csc_coef.csc_in_dc0;
    csc_coef.csc_in_dc1 = (hi_s32)dc_pre * csc_coef.csc_in_dc1;
    csc_coef.csc_in_dc2 = (hi_s32)dc_pre * csc_coef.csc_in_dc2;

    csc_coef.csc_out_dc0 = (hi_s32)dc_pre * csc_coef.csc_out_dc0;
    csc_coef.csc_out_dc1 = (hi_s32)dc_pre * csc_coef.csc_out_dc1;
    csc_coef.csc_out_dc2 = (hi_s32)dc_pre * csc_coef.csc_out_dc2;

    hal_layer_set_csc_coef(gfx_layer, &csc_coef);

    return HI_SUCCESS;
}

hi_s32 vo_drv_video_set_csc_coef(vo_hal_layer vo_layer, vo_csc_matrix csc_matrix)
{
    csc_coef csc_coef;
    hal_csc_mode csc_mode;
    hi_u32 dc_pre = 4;
    vo_csc csc = {0};

    csc.contrast = 50;
    csc.hue = 50;
    csc.luma = 50;
    csc.satuature = 50;

    if ((vo_layer < LAYER_VHD_START) || (vo_layer > LAYER_VHD_END)) {
        printf("[%s][%d] vo_layer:%d not supported\n", __FUNCTION__, __LINE__, vo_layer);
        return HI_FAILURE;
    }

    vo_drv_get_hal_cscmode(csc_matrix, &csc_mode);

    vo_drv_calc_csc_matrix(&csc, csc_mode, &csc_coef);

    csc_coef.new_csc_clip_max = 0xfff;
    csc_coef.new_csc_clip_min = 0x0;
    csc_coef.new_csc_scale2p = 0xa;

    csc_coef.csc_coef00 = csc_coef.csc_coef00 * 1024 / 1000;
    csc_coef.csc_coef01 = csc_coef.csc_coef01 * 1024 / 1000;
    csc_coef.csc_coef02 = csc_coef.csc_coef02 * 1024 / 1000;
    csc_coef.csc_coef10 = csc_coef.csc_coef10 * 1024 / 1000;
    csc_coef.csc_coef11 = csc_coef.csc_coef11 * 1024 / 1000;
    csc_coef.csc_coef12 = csc_coef.csc_coef12 * 1024 / 1000;
    csc_coef.csc_coef20 = csc_coef.csc_coef20 * 1024 / 1000;
    csc_coef.csc_coef21 = csc_coef.csc_coef21 * 1024 / 1000;
    csc_coef.csc_coef22 = csc_coef.csc_coef22 * 1024 / 1000;

    csc_coef.csc_in_dc0 = (hi_s32)dc_pre * csc_coef.csc_in_dc0;
    csc_coef.csc_in_dc1 = (hi_s32)dc_pre * csc_coef.csc_in_dc1;
    csc_coef.csc_in_dc2 = (hi_s32)dc_pre * csc_coef.csc_in_dc2;

    csc_coef.csc_out_dc0 = (hi_s32)dc_pre * csc_coef.csc_out_dc0;
    csc_coef.csc_out_dc1 = (hi_s32)dc_pre * csc_coef.csc_out_dc1;
    csc_coef.csc_out_dc2 = (hi_s32)dc_pre * csc_coef.csc_out_dc2;

    hal_layer_set_csc_coef(vo_layer, &csc_coef);

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

