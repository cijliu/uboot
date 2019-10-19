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
#ifndef __BOOT_HDMI_INTF_H__
#define __BOOT_HDMI_INTF_H__
#include "hi_type.h"
#include "hdmi_hal.h"
#include "drv_hdmi_common.h"
#if defined(CONFIG_HDMI_STB_SDK)
#include <uboot.h>
#elif defined(CONFIG_HDMI_BVT_SDK)
#include "ubi_uboot.h"
#endif

#define HDMI_INFO(fmt...)
#define HDMI_WARN(fmt...)
#define HDMI_ERR(fmt...)
#define HDMI_FATAL(fmt...)

#undef offsetof
#define offsetof(TYPE, MEMBER)    ((size_t)&((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#undef container_of
#define container_of(ptr, type, member) ({            \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#define HDMI_CONTAINER_OF  container_of

typedef struct
{
    HI_U32             u32HdmiDevId;
    HDMI_TMDS_MODE_E   enTmdsMode;
    HDMI_ATTR_S        stAttr;
    HDMI_INFOFRAME_S   stInfoFrame;
    HDMI_HAL_S*        pstHdmiHal;
}HDMI_DEVICE_S;

typedef enum hiVO_INTF_SYNC_E
{
    VO_OUTPUT_PAL = 0,               /* PAL standard*/
    VO_OUTPUT_NTSC,                  /* NTSC standard */

    VO_OUTPUT_1080P24,               /* 1920 x 1080 at 24 Hz. */
    VO_OUTPUT_1080P25,               /* 1920 x 1080 at 25 Hz. */
    VO_OUTPUT_1080P30,               /* 1920 x 1080 at 30 Hz. */

    VO_OUTPUT_720P50,                /* 1280 x  720 at 50 Hz. */
    VO_OUTPUT_720P60,                /* 1280 x  720 at 60 Hz. */
    VO_OUTPUT_1080I50,               /* 1920 x 1080 at 50 Hz, interlace. */
    VO_OUTPUT_1080I60,               /* 1920 x 1080 at 60 Hz, interlace. */
    VO_OUTPUT_1080P50,               /* 1920 x 1080 at 50 Hz. */
    VO_OUTPUT_1080P60,               /* 1920 x 1080 at 60 Hz. */

    VO_OUTPUT_576P50,                /* 720  x  576 at 50 Hz. */
    VO_OUTPUT_480P60,                /* 720  x  480 at 60 Hz. */

    VO_OUTPUT_800x600_60,            /* VESA 800 x 600 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1024x768_60,           /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1280x1024_60,          /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1366x768_60,           /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1440x900_60,           /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
    VO_OUTPUT_1280x800_60,           /* 1280*800@60Hz VGA@60Hz*/
    VO_OUTPUT_1600x1200_60,          /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1680x1050_60,          /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1920x1200_60,          /* VESA 1920 x 1600 at 60 Hz (non-interlaced) CVT (Reduced Blanking)*/
    VO_OUTPUT_640x480_60,            /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
    VO_OUTPUT_960H_PAL,              /* ITU-R BT.1302 960 x 576 at 50 Hz (interlaced)*/
    VO_OUTPUT_960H_NTSC,             /* ITU-R BT.1302 960 x 480 at 60 Hz (interlaced)*/
    VO_OUTPUT_1920x2160_30,          /* 1920x2160_30 */
    VO_OUTPUT_2560x1440_30,          /* 2560x1440_30 */
    VO_OUTPUT_2560x1440_60,          /* 2560x1440_60 */
    VO_OUTPUT_2560x1600_60,          /* 2560x1600_60 */
    VO_OUTPUT_3840x2160_24,          /* 3840x2160_24 */
    VO_OUTPUT_3840x2160_25,          /* 3840x2160_25 */
    VO_OUTPUT_3840x2160_30,          /* 3840x2160_30 */
    VO_OUTPUT_3840x2160_50,          /* 3840x2160_50 */
    VO_OUTPUT_3840x2160_60,          /* 3840x2160_60 */
    VO_OUTPUT_4096x2160_24,          /* 4096x2160_24 */
    VO_OUTPUT_4096x2160_25,          /* 4096x2160_25 */
    VO_OUTPUT_4096x2160_30,          /* 4096x2160_30 */
    VO_OUTPUT_4096x2160_50,          /* 4096x2160_50 */
    VO_OUTPUT_4096x2160_60,          /* 4096x2160_60 */
    VO_OUTPUT_320x240_60,            /* For ota5182 at 60 Hz (8bit)  */
    VO_OUTPUT_320x240_50,            /* For ili9342 at 50 Hz (6bit)  */
    VO_OUTPUT_240x320_50,            /* Hi3559AV100: For ili9341 at 50 Hz (6bit) Hi3556AV100/Hi3519AV100: For st7789 at 50Hz(6bit) */
    VO_OUTPUT_240x320_60,            /* For ili9341 at 60 Hz (16bit) */
    VO_OUTPUT_800x600_50,            /* For LCD     at 50 Hz (24bit) */
    VO_OUTPUT_720x1280_60,           /* For MIPI DSI Tx 720 x1280 at 60 Hz */
    VO_OUTPUT_1080x1920_60,          /* For MIPI DSI Tx 1080x1920 at 60 Hz */
    VO_OUTPUT_7680x4320_30,          /* For HDMI2.0 at 30 Hz         */
    VO_OUTPUT_USER,                  /* User timing. */

    VO_OUTPUT_BUTT

} VO_INTF_SYNC_E;

#endif//__BOOT_HDMI_INTF_H__
