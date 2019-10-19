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

#ifndef __VOU_COEF_ORG_H__
#define __VOU_COEF_ORG_H__

#include "vou_coef.h"

/* RGB->YUV601 */
extern const csc_coef g_csc_rgb_to_yuv601_tv;
/* RGB->YUV601 */
extern const csc_coef g_csc_rgb_to_yuv601_pc;
/* RGB->YUV709 */
extern const csc_coef g_csc_rgb_to_yuv709_tv;
/* RGB->YUV709 */
extern const csc_coef g_csc_rgb_to_yuv709_pc;
/* YUV601->RGB */
extern const csc_coef g_csc_yuv601_to_rgb_pc;
/* YUV709->RGB */
extern const csc_coef g_csc_yuv709_to_rgb_pc;
/* YUV601->YUV709 */
extern const csc_coef g_csc_yuv_to_yuv_601_709;
/* YUV709->YUV601 */
extern const csc_coef g_csc_yuv_to_yuv_709_601;
/* YUV601->YUV709 */
extern const csc_coef g_csc_init;

extern const int SIN_TABLE[61];
extern const int COS_TABLE[61];

#endif
