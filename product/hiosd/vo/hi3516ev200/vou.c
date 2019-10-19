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
#include <version.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <config.h>

#include "vou_drv.h"
#include "vou_hal.h"
// #include "bootlogo.dat" // for debug,bootlogo.dat is a bin file(image)
static hi_u32 g_bg_color = 0x00FF;
static hi_bool g_inited = HI_FALSE;
static rect g_max_rect = {0};

#define ALIGN_BACK(x, a) ((a) * (((x) / (a))))

static unsigned int gfx_convert_layer(unsigned int layer)
{
    unsigned int u_gfx_layer;

    /* hard cursor is not supported. */
    switch (layer) {
        case 0:
            u_gfx_layer = VO_LAYER_G0;
            break;

        default:
            u_gfx_layer = VO_LAYER_G0;
            break;
    }

    return u_gfx_layer;
}

static hal_disp_layer gfx_convert_to_hal_layer(unsigned int layer)
{
    hal_disp_layer hal_gfx_layer;

    /* hard cursor is not supported. */
    switch (layer) {
        case 0:
            hal_gfx_layer = HAL_DISP_LAYER_GFX0;
            break;

        default:
            hal_gfx_layer = HAL_DISP_LAYER_GFX0;
            break;
    }

    return hal_gfx_layer;
}

static hal_disp_layer video_layer_convert_to_hal(unsigned int layer)
{
    hal_disp_layer hal_video_layer;

    /* hard cursor is not supported. */
    switch (layer) {
        case 0:
            hal_video_layer = HAL_DISP_LAYER_VHD0;
            break;

        default:
            hal_video_layer = HAL_DISP_LAYER_VHD0;
            break;
    }

    return hal_video_layer;
}

int set_vobg(unsigned int dev, unsigned int rgb)
{
    if (dev < 1) {
        g_bg_color = rgb;
    }

    return 0;
}

hi_void vo_set_disp_max_size(vo_hal_dev vo_dev, vo_intf_sync vo_out_mode)
{
    hi_u32 max_width = 720;
    hi_u32 max_height = 576;

    switch (vo_out_mode) {
        case VO_OUTPUT_PAL:
        case VO_OUTPUT_576P50:
            max_width = 720;
            max_height = 576;
            break;

        case VO_OUTPUT_NTSC:
        case VO_OUTPUT_480P60:
            max_width = 720;
            max_height = 480;
            break;

        case VO_OUTPUT_720P60:
        case VO_OUTPUT_720P50:
            max_width = 1280;
            max_height = 720;
            break;

        case VO_OUTPUT_1080I50:
        case VO_OUTPUT_1080I60:
        case VO_OUTPUT_1080P24:
        case VO_OUTPUT_1080P25:
        case VO_OUTPUT_1080P30:
        case VO_OUTPUT_1080P50:
        case VO_OUTPUT_1080P60:
            max_width = 1920;
            max_height = 1080;
            break;

        case VO_OUTPUT_800x600_60:
        case VO_OUTPUT_800x600_50:
            max_width = 800;
            max_height = 600;
            break;

        case VO_OUTPUT_1024x768_60:
            max_width = 1024;
            max_height = 768;
            break;

        case VO_OUTPUT_1280x1024_60:
            max_width = 1280;
            max_height = 1024;
            break;

        case VO_OUTPUT_1366x768_60:
            max_width = 1366;
            max_height = 768;
            break;

        case VO_OUTPUT_1440x900_60:
            max_width = 1440;
            max_height = 900;
            break;

        case VO_OUTPUT_1280x800_60:
            max_width = 1280;
            max_height = 800;
            break;

        case VO_OUTPUT_1600x1200_60:
            max_width = 1600;
            max_height = 1200;
            break;

        case VO_OUTPUT_1680x1050_60:
            max_width = 1680;
            max_height = 1050;
            break;

        case VO_OUTPUT_1920x1200_60:
            max_width = 1920;
            max_height = 1200;
            break;

        case VO_OUTPUT_640x480_60:
            max_width = 640;
            max_height = 480;
            break;

        case VO_OUTPUT_1920x2160_30:
            max_width = 1920;
            max_height = 2160;
            break;

        case VO_OUTPUT_2560x1440_30:
        case VO_OUTPUT_2560x1440_60:
            max_width = 2560;
            max_height = 1440;
            break;

        case VO_OUTPUT_2560x1600_60:
            max_width = 2560;
            max_height = 1600;
            break;

        case VO_OUTPUT_3840x2160_24:
        case VO_OUTPUT_3840x2160_25:
        case VO_OUTPUT_3840x2160_30:
        case VO_OUTPUT_3840x2160_50:
        case VO_OUTPUT_3840x2160_60:
            max_width = 3840;
            max_height = 2160;
            break;

        case VO_OUTPUT_4096x2160_24:
        case VO_OUTPUT_4096x2160_25:
        case VO_OUTPUT_4096x2160_30:
        case VO_OUTPUT_4096x2160_50:
        case VO_OUTPUT_4096x2160_60:
            max_width = 4096;
            max_height = 2160;
            break;

        case VO_OUTPUT_320x240_50:
        case VO_OUTPUT_320x240_60: /* just for hi3518ev200 hi3519 */
            max_width = 320;
            max_height = 240;
            break;

        case VO_OUTPUT_240x320_50: /* just for hi3518ev200 hi3519 */
        case VO_OUTPUT_240x320_60:
            max_width = 240;
            max_height = 320;
            break;

        case VO_OUTPUT_720x1280_60:
            max_width = 720;
            max_height = 1280;
            break;

        case VO_OUTPUT_1080x1920_60:
            max_width = 1080;
            max_height = 1920;
            break;

        case VO_OUTPUT_7680x4320_30:
            max_width = 7680;
            max_height = 4320;
            break;

        default:
            max_width = 4096;
            max_height = 2160;
    }

    g_max_rect.width = max_width;
    g_max_rect.height = max_height;
}

int start_vo(unsigned int dev, unsigned int type, unsigned int sync)
{
    if (g_inited == HI_FALSE) {
        sys_hal_vo_bus_reset_sel(HI_FALSE);
        /* open clk */
        vo_drv_set_all_crg_clk(HI_TRUE);
        vo_drv_board_init();
        hal_sys_control();

        g_inited = HI_TRUE;
    }

    sys_hal_vo_dev_clk_en(dev, HI_TRUE);
    sys_hal_vo_core_clk_en(dev, HI_TRUE);

    vo_drv_def_layer_bind_dev();
    vo_set_disp_max_size(dev, sync);
    vo_drv_set_dev_intf_type(dev, type);
    vo_drv_set_dev_out_sync(dev, sync);

    vo_drv_set_dev_bk_grd(dev, g_bg_color);

    vo_drv_set_dev_clk(dev);
    vo_drv_open(dev);
    return 0;
}

int stop_vo(unsigned int dev)
{
    vo_drv_close(dev);
    sys_hal_vo_dev_clk_en(dev, HI_FALSE);
    return 0;
}

int start_videolayer(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect layer_rect)
{
    int i = 0;
    rect disp_rect = { layer_rect.x, layer_rect.y, layer_rect.w, layer_rect.h };
    hal_disp_layer vo_layer;
    hfir_coef hfir_coef = { 42, -10, -20, 28, -40, 61, -107, 330 };

    vo_intf_type vo_intf_type;

    vdp_vid_ip_cfg vid_cfg = {0};
    vo_csc_matrix csc_matrix = VO_CSC_MATRIX_IDENTITY;

    vo_layer = video_layer_convert_to_hal(layer);
    hal_layer_set_layer_data_fmt(vo_layer, VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_420);
    vdp_fdr_vid_set_chm_copy_en(vo_layer, HI_TRUE);
    vo_intf_type = vo_drv_get_dev_intf_type(vo_layer);

    if (vo_intf_type == VO_INTF_BT1120) {
        csc_matrix = VO_CSC_MATRIX_IDENTITY;
    } else if ((vo_intf_type == VO_INTF_LCD_6BIT) ||
               (vo_intf_type == VO_INTF_LCD_8BIT) ||
               (vo_intf_type == VO_INTF_LCD_16BIT)) {
        csc_matrix = VO_CSC_MATRIX_BT709_TO_RGB_PC;
    }

    vo_drv_video_set_csc_coef(vo_layer, csc_matrix);
    hal_layer_set_csc_en(vo_layer, HI_TRUE);

    for (i = 0; i < HAL_DISP_LAYER_VHD1; i++) {
        hal_video_set_layer_alpha(i, 255);
        hal_video_set_hfir_mode(i, HAL_HFIRMODE_COPY);
        hal_video_hfir_set_coef(i, &hfir_coef);
        hal_video_hfir_set_mid_en(i, HI_TRUE);
    }

    hal_video_hfir_set_ck_gt_en(vo_layer, HI_TRUE);
    hal_video_set_layer_disp_rect(vo_layer, &disp_rect);
    hal_video_set_layer_video_rect(vo_layer, &disp_rect);
    hal_layer_set_layer_in_rect(vo_layer, &disp_rect);
    hal_layer_set_layer_galpha(vo_layer, 255);
    hal_layer_set_src_resolution(vo_layer, &disp_rect);
    hal_layer_set_zme_enable(vo_layer, HAL_DISP_ZMEMODE_ALL, HI_FALSE);

    vid_cfg.csc_en = 0;
    vid_cfg.hfir_en = 1;
    vid_cfg.vid_iw = disp_rect.width;
    vid_cfg.vid_ih = disp_rect.height;
    vid_cfg.vid_ow = disp_rect.width;
    vid_cfg.vid_oh = disp_rect.height;
    vid_cfg.zme_en = HI_FALSE;
    vo_vid_set_zme_enable(vo_layer, &vid_cfg);
    hal_layer_set_zme_info(vo_layer, disp_rect.width, disp_rect.height, HAL_DISP_ZME_OUTFMT420);

    hal_video_set_multi_area_l_addr(vo_layer, 0, addr, strd);
    hal_video_set_multi_area_c_addr(vo_layer, 0, addr + layer_rect.h * ALIGN_BACK(layer_rect.w, 8), strd);

    hal_layer_enable_layer(vo_layer, HI_TRUE);
    hal_layer_set_reg_up(vo_layer);

    return 0;
}

int stop_videolayer(unsigned int layer)
{
    hal_disp_layer hal_video_layer;

    hal_video_layer = video_layer_convert_to_hal(layer);

    hal_layer_enable_layer(hal_video_layer, HI_FALSE);
    hal_layer_set_reg_up(hal_video_layer);

    return 0;
}

int start_gx(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect gx_rect)
{
    OSD_LOGO_T scroll_image_logo = {0};
    vo_layer vo_layer;
    vo_intf_type vo_intf_type;
    vo_csc gfx_csc;
    csc_coef_param csc_coef_param;

    vo_layer = gfx_convert_layer(layer);
    vo_intf_type = vo_drv_get_dev_intf_type(layer);
    load_bmp((hi_u32 *)addr, &scroll_image_logo);
    rect disp_rect = { gx_rect.x, gx_rect.y, scroll_image_logo.width, scroll_image_logo.height };

    hal_graphic_set_gfx_ext(vo_layer, HAL_GFX_BITEXTEND_3RD);
    hal_graphic_set_gfx_palpha(vo_layer, HI_TRUE, HI_TRUE, 0xff, 0xff);
    hal_layer_set_layer_galpha(vo_layer, 0xff);
    hal_graphic_set_gfx_pre_mult(vo_layer, HI_FALSE);

    // for mipi_tx, do not do this two line.
    if ((VO_INTF_BT1120 & vo_intf_type) || (VO_INTF_BT656 & vo_intf_type)) {
        gfx_csc.csc_matrix = VO_CSC_MATRIX_RGB_TO_BT709_PC;
        gfx_csc.luma = 50;
        gfx_csc.contrast = 50;
        gfx_csc.hue = 50;
        gfx_csc.satuature = 50;

        csc_coef_param.csc_scale2p = GFX_CSC_SCALE;
        csc_coef_param.csc_clip_min = GFX_CSC_CLIP_MIN;
        csc_coef_param.csc_clip_max = GFX_CSC_CLIP_MAX;

        // do rgb to yuv.
        graphic_drv_set_csc_coef(vo_layer, &gfx_csc, &csc_coef_param);
        hal_layer_set_csc_en(vo_layer, HI_TRUE);
    } else if ((vo_intf_type == VO_INTF_LCD_6BIT) ||
               (vo_intf_type == VO_INTF_LCD_8BIT) ||
               (vo_intf_type == VO_INTF_LCD_16BIT)) {
        // do yuv to rgb or do nothing.
        hal_layer_set_csc_en(vo_layer, HI_FALSE);
    }

    hal_graphic_set_gfx_addr (vo_layer, (hi_u64)(hi_u32)scroll_image_logo.rgb_buffer);
    hal_graphic_set_gfx_stride(vo_layer, (scroll_image_logo.stride) >> 4);

    hal_layer_set_layer_in_rect(vo_layer, &disp_rect);
    hal_video_set_layer_disp_rect(vo_layer, &disp_rect);
    hal_video_set_layer_video_rect(vo_layer, &disp_rect);
    hal_gfx_set_src_resolution(vo_layer, &disp_rect);
    hal_layer_set_layer_data_fmt(vo_layer, HAL_INPUTFMT_ARGB_1555);
    hal_layer_enable_layer(vo_layer, HI_TRUE);
    hal_layer_set_reg_up(vo_layer);

    return 0;
}

int stop_gx(unsigned int layer)
{
    vo_layer vo_layer;
    hal_disp_layer hal_gfx_layer;

    vo_layer = gfx_convert_layer(layer);
    hal_gfx_layer = gfx_convert_to_hal_layer(layer);

    hal_layer_set_reg_up(vo_layer);
    hal_layer_enable_layer(vo_layer, HI_FALSE);
    hal_layer_set_reg_up(hal_gfx_layer);

    return 0;
}

