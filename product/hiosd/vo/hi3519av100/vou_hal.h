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

#ifndef __VOU_HAL_H__
#define __VOU_HAL_H__

#include "vou_reg.h"
#include "vou_def.h"
#include "vou_coef_org.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

hi_void hal_vo_init(hi_void);
hi_void hal_vo_exit(hi_void);

hi_void hal_write_reg(hi_u32 *address, hi_u32 value);
hi_u32 hal_read_reg(hi_u32 *address);

hi_void hal_video_hfir_set_ck_gt_en(hal_disp_layer layer, hi_u32 ck_gt_en);
hi_bool hal_layer_set_src_resolution(hal_disp_layer layer,
                                   rect *rect);

hi_bool hal_intf_bt_set_dfir_en(hi_u32 dfir_en);

hi_s32 sys_hal_sel_vo_bt1120_pin_conifg(hi_void);

hi_s32 sys_hal_vo_bus_reset_sel(hi_bool reset);
hi_s32 sys_hal_vo_hd_out_pctrl(hi_bool clk_reverse);
hi_s32 sys_hal_vo_cfg_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_core_clk_en(hi_s32 dev, hi_bool clk_en);
hi_s32 sys_hal_vou_ppc_clk_en(hi_s32 dev, hi_bool clk_en);
hi_s32 sys_hal_vo_out_clk_en(hi_s32 dev, hi_bool clk_en);
hi_s32 sys_hal_vo_apb_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_bus_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_dev_clk_en(hi_s32 vo_dev, hi_bool clk_en);
hi_s32 sys_hal_vo_hd0_ppc_sel(hi_u32 clk_sel);
hi_s32 sys_hal_vo_hd0_div_mode(hi_s32 dev, hi_u32 hd0_div_mod);
hi_s32 sys_hal_vo_hd1_ppc_sel(hi_u32 bt_clk_ch_sel);
hi_s32 sys_hal_vo_hd1_div_mode(hi_u32 hd1_div_mod);
hi_s32 sys_hal_vo_out_clk_sel(hi_u32 clk_sel);
hi_s32 sys_hal_vo_lcd_clk_en(hi_bool clk_en);
hi_s32 sys_hal_lcd_mclk_div(hi_u32 mclk_div);
hi_s32 sys_hal_lcd_data_mode(hi_u32 data_mode);
hi_s32 sys_hal_vo_bt_clk_en(hi_bool bt_clk_en);
hi_s32 sys_hal_vo_hdmi_clk_en(hi_bool hdmi_clk_en);
hi_s32 sys_hal_vo_bt_clk_sel(hi_u32 bt_clk_ch_sel);
hi_s32 sys_hal_vo_mipi_clk_en(hi_bool mipi_clk_en);
hi_s32 sys_hal_vo_mipi_chn_sel(hi_u32 mipi_ch_sel);
hi_s32 sys_hal_set_vo_low_power_ctrl(hi_bool low_power_clk_en);

hi_s32 sys_hal_set_vo_pll_frac(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_postdiv1(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_postdiv2(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_refdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_fbdiv(hi_s32 pll, hi_u32 bits_set);

hi_s32 sys_hal_set_vo_s_pll_frac(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_postdiv1(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_postdiv2(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_refdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_fbdiv(hi_s32 pll, hi_u32 bits_set);

hi_void hal_sys_control(hi_void);
hi_bool hal_disp_set_intvsync_te_mode(hal_disp_outputchannel chan, hi_bool slave);

/*****************************************************************************
 prototype       : sys relative
 description     :

*****************************************************************************/
hi_void hal_sys_set_arb_mode(hi_u32 mode);
hi_void hal_sys_vdp_reset_clk(hi_u32 sel);

/*****************************************************************************
 prototype       : device relative
 description     :

*****************************************************************************/
hi_bool hal_disp_set_intf_enable(hal_disp_outputchannel chan, hi_bool intf);
hi_bool hal_disp_set_intf_ctrl(hal_disp_intf intf, hi_u32 *ctrl_info);
hi_bool hal_disp_set_intf_sync(hal_disp_outputchannel chan,
                             hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv);
hi_void hal_disp_set_hdmi_mode(hal_disp_outputchannel chan, hi_u32 color_space);
hi_bool hal_disp_set_dev_multi_chn_en(hal_disp_outputchannel chn, HAL_MULTICHN_EN multi_chn_en);
hi_bool hal_disp_set_intf_sync_inv(hal_disp_intf intf, hal_disp_syncinv *inv);
hi_bool hal_disp_set_intf_mux_sel(hal_disp_outputchannel chan, hal_disp_intf intf);
hi_bool hal_disp_set_bt1120_sel(hal_disp_outputchannel chan);

hi_bool hal_disp_set_intf_csc_en(hal_disp_intf intf, hi_bool csc_en);
hi_bool hal_disp_set_intf_clip(hal_disp_intf intf, hi_bool clip, hal_disp_clip *clip_data);
hi_bool hal_disp_set_vt_thd_mode(hal_disp_outputchannel chan, hi_u32 u_field_mode);
hi_bool hal_disp_set_vt_thd(hal_disp_outputchannel chan, hi_u32 vtthd);

hi_bool hal_disp_set_int_mask(hi_u32 mask_en);
hi_bool hal_disp_clr_int_mask(hi_u32 mask_en);
hi_bool hal_disp_set_int_mask1(hi_u32 mask_en);
hi_bool hal_disp_clr_int_mask1(hi_u32 mask_en);

hi_void hal_disp_set_reg_up(hal_disp_outputchannel chan);

/*****************************************************************************
 prototype       : video layer relative
 description     :

*****************************************************************************/
hi_bool hal_video_set_layer_up_mode(hal_disp_layer layer, hi_u32 up_mode);
hi_bool hal_video_set_hfir_mode(hal_disp_layer layer, hal_hfirmode mode);
hi_bool hal_video_set_hfir_coef(hal_disp_layer layer, hi_s32 *coef);
hi_bool hal_video_set_layer_disp_rect(hal_disp_layer layer, rect *rect);
hi_bool hal_video_set_layer_video_rect(hal_disp_layer layer, rect *rect);
hi_bool hal_video_set_multi_area_l_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong ul_l_addr, hi_u16 stride);
hi_bool hal_video_set_multi_area_c_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong ul_c_addr, hi_u16 stride);
hi_void hal_video_cvfir_set_out_height(hal_disp_layer layer, hi_u32 out_height);
hi_void hal_video_cvfir_set_out_fmt(hal_disp_layer layer, hi_u32 out_fmt);
hi_void hal_video_cvfir_set_out_pro(hal_disp_layer layer, hi_u32 out_pro);
hi_void hal_video_cvfir_set_vzme_ck_gt_en(hal_disp_layer layer, hi_bool vzme_ck_gt_en);

hi_void hal_video_cvfir_set_cvfir_en(hal_disp_layer layer, hi_u32 cvfir_en);
hi_void hal_video_cvfir_set_cvmid_en(hal_disp_layer layer, hi_u32 cvmid_en);
hi_void hal_video_cvfir_set_cvfir_mode(hal_disp_layer layer, hi_u32 cvfir_mode);
hi_void hal_video_cvfir_set_vratio(hal_disp_layer layer, hi_u32 vratio);

hi_void hal_video_cvfir_set_v_chroma_offset(hal_disp_layer layer, hi_u32 vchroma_offset);
hi_void hal_video_cvfir_set_vb_chroma_offset(hal_disp_layer layer, hi_u32 vbchroma_offset);

/*****************************************************************************
 prototype       : layer relative
 description     :

*****************************************************************************/
hi_bool hal_layer_enable_layer(hal_disp_layer layer, hi_u32 enable);
hi_bool hal_layer_set_layer_data_fmt(hal_disp_layer layer,
                                  hal_disp_pixel_format data_fmt);
hi_bool hal_layer_set_layer_in_rect(hal_disp_layer layer, rect *rect);
hi_bool hal_layer_set_layer_galpha(hal_disp_layer layer,
                                 hi_u8 alpha0);
hi_bool hal_layer_set_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                             hal_disp_zme_outfmt zme_out_fmt);
hi_bool hal_layer_set_zme_enable(hal_disp_layer layer,
                               hal_disp_zmemode mode,
                               hi_u32 enable);
hi_bool hal_layer_set_reg_up(hal_disp_layer layer);

/*****************************************************************************
 prototype       : cbm layer relative
 description     :

*****************************************************************************/
hi_bool hal_cbm_set_cbm_bkg(hi_u32 mixer_id, hal_disp_bkcolor *bkg);
hi_bool hal_cbm_set_cbm_mixer_prio(hal_disp_layer layer, hi_u8 prio, hi_u8 mixer_id);
hi_bool hal_disp_set_vga_csc_en(hal_disp_layer layer, hi_bool csc_en);
hi_void hal_hihdr_g_set_hihdr_r2y_scale2p(hi_u32 hihdr_r2y_scale2p);
hi_void hal_hihdr_g_set_hihdr_r2y_clip_min(hi_u32 hihdr_r2y_clip_min);
hi_void hal_hihdr_g_set_hihdr_r2y_clip_max(hi_u32 hihdr_r2y_clip_max);

hi_bool hal_graphic_set_gfx_ext(hal_disp_layer layer,
                              hal_gfx_bitextend mode);

hi_bool hal_graphic_set_gfx_pre_mult(hal_disp_layer layer, hi_u32 enable);
hi_bool hal_graphic_set_gfx_palpha(hal_disp_layer layer,
                                 hi_u32 alpha_en, hi_u32 arange,
                                 hi_u8 alpha0, hi_u8 alpha1);

hi_bool hal_graphic_set_gfx_addr(hal_disp_layer layer, hi_u64 l_addr);
hi_bool hal_graphic_set_gfx_stride(hal_disp_layer layer, hi_u16 u16pitch);
hi_bool hal_layer_set_csc_coef(hal_disp_layer layer, csc_coef *csc_coef);
hi_bool hal_layer_set_csc_en(hal_disp_layer layer, hi_bool csc_en);
hi_bool hal_gfx_set_src_resolution(hal_disp_layer layer, rect *rect);

__inline static hi_u32 get_low_addr(hi_u64 phyaddr)
{
    return (hi_u32)phyaddr;
}

__inline static hi_u32 get_high_addr(hi_u64 phyaddr)
{
    return (hi_u32)(phyaddr >> 32);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
#endif /* end of __VOU_HAL_H__ */

