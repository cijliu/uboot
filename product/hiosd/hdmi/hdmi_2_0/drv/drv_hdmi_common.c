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
#include "drv_hdmi_common.h"
#include "drv_hdmi_infoframe.h"
#include "hdmi_product_define.h"
#ifdef HDMI_BUILD_IN_BOOT
#include "boot_hdmi_intf.h"
#endif


#define CHECK_MAX_VALUE(out, in, max)    out = (HI_U32)(((in) > (max))? (max): (in))


HDMI_VIDEO_DEF_S s_stVESAVideoCodesDes[VESAVideoCodesMax] =
{
    /*VIC******PixelClk****Vfreq*****Hactive****Vactive***Hblank***Vblank***Hfront***Hsync***Hback***Vfront**Vsync**Vback**Aspect********************Timing************************************I/P**********************Descriptor*****/
    {0,        0,          0,        0,         0,        0,       0,       0,       0,      0,      0,      0,     0,     HDMI_PICTURE_ASPECT_NONE, HDMI_VIDEO_TIMING_UNKNOWN,                HDMI_VIDEO_UNKNOWN,      (HI_CHAR *)"NONE"},
    {0, 	   40000,  	   60317,    800,       600,      256,     28,      40,      128,    88,     1,      4,     23,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_800X600_60,        HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA800*600p60"},
    {0,		   33750,  	   60000,    848,       480,      240,     37,      16,      112,    112,    6,      8,     23,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_848X480_60,        HDMI_VIDEO_PROGRESSIVE,  (HI_CHAR *)"VESA848*480p60"},
    {0,        65000,      60004,    1024,      768,      320,     38,      24,      136,    160,    3,      6,     29,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1024X768_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1024*768p60"},
    {0,		   74250,  	   60000,    1280,      720,      370,     30,      110,     40,     220,    5,      5,     20,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1280X720_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1280*720p60"},
    {0,		   68250,  	   59995,    1280,      768,      160,     22,      48,      32,     80,     3,      7,     12,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1280X768_60_RB,    HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1280*768p60RB"},
    {0,        79500,      59870,    1280,      768,      384,     30,      64,      128,    192,    3,      7,     20,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1280X768_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1280*768p60"},
    {0,		   71001,  	   59910,    1280,      800,      160,     23,      48,      32,     80,     3,      6,     14,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1280X800_60_RB,    HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1280*800p60RB"},
    {0,		   83500,  	   59810,    1280,      800,      400,     31,      72,      128,    200,    3,      6,     22,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1280X800_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1280*800p60"},
    {0,	       108000,     60000,    1280,      960,      520,     40,      96,      112,    312,    1,      3,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1280X960_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1280*960p60"},
    {0,		   108000, 	   60020,    1280,      1024,     408,     42,      48,      112,    248,    1,      3,     38,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1280X1024_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1280*1024p60"},
    {0,	       85500,      60015,    1360,      768,      432,     27,      64,      112,    256,    3,      6,     18,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1360X768_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1360*768p60"},
    {0,		   85501,  	   59790,    1366,      768,      426,     30,      70,      143,    213,    3,      3,     24,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1366X768_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1366*768p60"},
    {0,	       121749,     59978,    1400,      1050,     464,     39,      88,      144,    232,    3,      4,     32,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1400X1050_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1400*1050p60"},
    {0,		   88749,  	   59901,    1440,      900,      160,     26,      48,      32,     80,     3,      6,     17,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1440X900_60_RB,    HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1440*900p60RB"},
    {0,		   106499, 	   59887,    1440,      900,      464,     34,      80,      152,    232,    3,      6,     25,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1440X900_60,       HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1440*900p60"},
/**/{0,        108000,     60000,    1440,      1050,     144,     49,      12,      64,     68,     3,      6,     25,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1440X1050_60,      HDMI_VIDEO_PROGRESSIVE,  (HI_CHAR *)"VESA1440*1050p60"},
/**/{0,        108000,     60000,    1440,      1050,     144,     49,      12,      64,     68,     3,      6,     25,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1440X1050_60_RB,   HDMI_VIDEO_PROGRESSIVE,  (HI_CHAR *)"VESA1440*1050p60RB"},
    {0,		   108000, 	   60000,    1600,      900,      200,     100,     24,      80,     96,     1,      3,     96,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1600X900_60_RB,    HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1600*900p60"},
    {0,	       162000,     60000,    1600,      1200,     560,     50,      64,      192,    304,    1,      3,     46,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1600X1200_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1600*1200p60"},
    {0,		   118999, 	   59883,    1680,      1050,     160,     30,      48,      32,     80,	 3,      6,     21,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1680X1050_60_RB,   HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1680*1050p60RB"},
    {0,		   146249, 	   59954,    1680,      1050,     560,     39,      104,     176,    280,	 3,      6,     30,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1680X1050_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1680*1050p60"},
    {0,	       204751,     60000,    1792,      1344,     656,     50,      128,     200,    328,	 1,      3,     46,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1792X1344_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1792*1344p60"},
    {0,	       218249,     59995,    1856,      1392,     672,     47,      96,      224,    352,    1,      3,     43,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1856X1392_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1856*1392p60"},
    {0,        148500,     60000,    1920,      1080,     280,     45,      88,      44,     148,    4,      5,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1920X1080_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1920*1080p60"},
    {0,        154000,     59950,    1920,      1200,     160,     35,      48,      32,     80,	 3,      6,     26,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1920X1200_60_RB,   HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1920*1200p60RB"},
    {0,        193251,     59885,    1920,      1200,     672,     45,      136,     200,    336,    3,      6,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1920X1200_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1920*1200p60"},
    {0,	       234000,     60000,    1920,      1440,     680,     60,      128,     208,    344,    1,      3,     56,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_1920X1440_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA1920*1440p60"},
    {0,	       162000,     60000,    2048,      1152,     202,     48,      26,      80,     96,     1,      3,     44,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_2048x1152_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA2048*1152p60"},
/**/{0,	       82500,      50000,	 2560,	    1440,     520,     30,      260,     40,     220,    3,      3,     24,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_2560x1440_60_RB,   HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA2560*1440p60RB"},
    {0,	       348502,     59987,    2560,      1600,     944,     58,      192,     280,    472,    3,      6,     49,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_VESA_2560x1600_60,      HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"VESA2560*1600p60"},
};

HDMI_VIDEO_DEF_S s_stCEAVideoCodesDes[CEAVideoCodesMax] =
{
    /********VIC****************PixelClk****Vfreq*****Hactive****Vactive***Hblank***Vblank***Hfront***Hsync***Hback***Vfront**Vsync**Vback**Aspect********************Timing******************************I/P************************Descriptor*****/
    {0,                     	0,          0,        0,         0,        0,       0,       0,       0,      0,      0,      0,     0,     HDMI_PICTURE_ASPECT_NONE, HDMI_VIDEO_TIMING_UNKNOWN,          HDMI_VIDEO_UNKNOWN,     	(HI_CHAR *)"NONE"},
    {HDMI_640X480P60_4_3,   	25175,      59940,    640,       480,      160,     45,      16,      96,     48,     10,     2,     33,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_640X480P_60000,   HDMI_VIDEO_PROGRESSIVE, 	(HI_CHAR *)"640*480p60 4:3"},
    {HDMI_720X480P60_4_3,   	27000,      59940,    720,       480,      138,     45,      16,      62,     60,     9,      6,     30,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_720X480P_60000,   HDMI_VIDEO_PROGRESSIVE, 	(HI_CHAR *)"720*480p60 4:3"},
    {HDMI_720X480P60_16_9,		27000,	    59940,    720,       480,      138,     45,      16,      62,     60,     9,      6,     30,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_720X480P_60000,   HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"720*480p60 16:9"},
    {HDMI_1280X720P60_16_9,		74250,	    60000,    1280,      720,      370,     30,      110,     40,     220,    5,      5,     20,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1280X720P_60000,  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1280*720p60 16:9"},
    {HDMI_1920X1080I60_16_9, 	74250,	    60000,    1920,      1080,     280,     22,      88,      44,     148,    2,      5,     15,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1920X1080I_60000, HDMI_VIDEO_INTERLACE,		(HI_CHAR *)"1920*1080i60 16:9"},
    {HDMI_1440X480I60_4_3,		27000,	    59940,    1440,      480,      276,     22,      38,      124,    114,    4,      3,     15,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_1440X480I_60000,  HDMI_VIDEO_INTERLACE,		(HI_CHAR *)"1440*480i60 4:3"},
    {HDMI_1440X480I60_16_9,		27000,	    59940,    1440,      480,      276,     22,      38,      124,    114,    4,      3,     15,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1440X480I_60000,  HDMI_VIDEO_INTERLACE,     (HI_CHAR *)"1440*480i60 16:9"},
    {HDMI_1440X240P60_4_3,		27000,	    60054,    1440,      240,      276,     22,      38,      124,    114,    4,      3,     15,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_1440X240P_60000,  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1440*240p60 4:3"},
    {HDMI_1440X240P60_16_9, 	27000,	    60054,    1440,      240,      276,     22,      38,      124,    114,    4,      3,     15,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1440X240P_60000,  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1440*240p60 16:9"},
    {HDMI_2880X480I60_4_3,		54000,	    59940,    2880,      480,      552,     22,      76,      248,    228,    4,      3,     15,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_2880X480I_60000,  HDMI_VIDEO_INTERLACE,		(HI_CHAR *)"2880*480i60 4:3"},
    {HDMI_2880X480I60_16_9,		54000,	    59940,    2880,      480,      552,     22,      76,      248,    228,    4,      3,     15,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_2880X480I_60000,  HDMI_VIDEO_INTERLACE,		(HI_CHAR *)"2880*480i60 16:9"},
    {HDMI_2880X240P60_4_3,		54000,	    60054,    2880,      240,      552,     22,      76,      248,    228,    4,      3,     15,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_2880X240I_60000,  HDMI_VIDEO_PROGRESSIVE,  	(HI_CHAR *)"2880*240i60 4:3"},
    {HDMI_2880X240P60_16_9,     54000,	    60054,    2880,      240,      552,     23,      76,      248,    228,    4,      3,     15,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_2880X240I_60000,  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"2880*240i60 16:9"},
    {HDMI_1440X480P60_4_3,		54000,	    59940,    1440,      480,      276,     45,      32,      124,    120,    9,      6,     30,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_1440X480P_60000,  HDMI_VIDEO_PROGRESSIVE,   (HI_CHAR *)"1440*480p60 4:3"},
    {HDMI_1440X480P60_16_9,     54000,	    59940,    1440,      480,      276,     45,      32,      124,    120,    9,      6,     30,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1440X480P_60000,  HDMI_VIDEO_PROGRESSIVE,   (HI_CHAR *)"1440*480p60 16:9"},
    {HDMI_1920X1080P60_16_9,    148500,	    60000,    1920,      1080,     280,     45,      88,      44,     148,    4,      5,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1920X1080P_60000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1920*1080p60 16:9"},
    {HDMI_720X576P50_4_3,		27000,	    50000,    720,	     576,      144,     49,      12,      64,     68,     5,      5,     39,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_720X576P_50000,	  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"720*576p50 4:3"},
    {HDMI_720X576P50_16_9,		27000,	    50000,    720,       576,      144,     49,      12,      64,     68,     5,      5,     39,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_720X576P_50000,	  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"720*576p50 16:9"},
    {HDMI_1280X720P50_16_9,		74250,	    50000,    1280,      720,      700,     30,      440,     40,     220,    5,      5,     20,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1280X720P_50000,  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1280*720p50 16:9"},
    {HDMI_1920X1080I50_16_9,	74250,	    50000,    1920,      1080,     720,     24,      528,     44,     148,    2,      5,     15,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1920X1080I_50000, HDMI_VIDEO_INTERLACE,		(HI_CHAR *)"1920*1080i50 16:9"},
    {HDMI_1440X576I50_4_3,		27000,	    50000,    1440,      576,      288,     24,      24,      126,    138,    2,      3,     19,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_1440X576I_50000,  HDMI_VIDEO_INTERLACE,		(HI_CHAR *)"1440*576i50 4:3"},
    {HDMI_1440X576I50_16_9,		27000,	    50000,    1440,      576,      288,     24,      24,      126,    138,    2,      3,     19,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1440X576I_50000,  HDMI_VIDEO_INTERLACE,		(HI_CHAR *)"1440*576i50 16:9"},
    {HDMI_1440X576P50_4_3,		54000,	    50000,    1440,      576,      288,     49,      24,      128,    136,    5,      5,     39,    HDMI_PICTURE_ASPECT_4_3,  HDMI_VIDEO_TIMING_1440X576P_50000,  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1440*576p50 4:3"},
    {HDMI_1440X576P50_16_9,     54000,	    50000,    1440,      576,      288,     49,      24,      128,    136,    5,      5,     39,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1440X576P_50000,  HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1440*576p50 16:9"},
    {HDMI_1920X1080P50_16_9, 	148500,	    50000,    1920,      1080,     720,     45,      528,     44,     148,    4,      5,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1920X1080P_50000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1920*1080p50 16:9"},
    {HDMI_1920X1080P24_16_9,	742500,	    24000,    1920,      1080,     830,     45,      638,     44,     148,    4,      5,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1920X1080P_24000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1920*1080p24 16:9"},
    {HDMI_1920X1080P25_16_9,	742500,	    25000,    1920,      1080,     720,     45,      528,     44,     148,    4,      5,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1920X1080P_25000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1920*1080p25 16:9"},
    {HDMI_1920X1080P30_16_9,	742500,	    30000,    1920,      1080,     280,     45,      88,      44,     148,    4,      5,     36,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_1920X1080P_30000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"1920*1080p30 16:9"},
    {HDMI_3840X2160P24_16_9,	297000,	    24000,    3840,      2160,     1660,    90,      1276,    88,     296,    8,      10,    72,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_24000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"3840*2160p24 16:9"},
    {HDMI_3840X2160P25_16_9,	297000,	    25000,    3840,      2160,     1440,    90,      1056,    88,     296,    8,      10,    72,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_25000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"3840*2160p25 16:9"},
    {HDMI_3840X2160P30_16_9,	297000,	    30000,    3840,      2160,     560,     90,      176,     88,     296,    8,      10,    72,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_30000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"3840*2160p30 16:9"},
    {HDMI_3840X2160P50_16_9,	594000,	    50000,    3840,      2160,     1440,    90,      1056,    88,     296,    8,      10,    72,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_50000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"3840*2160p50 16:9"},
    {HDMI_3840X2160P60_16_9,	594000,	    60000,    3840,      2160,     560,     90,      176,     88,     296,    8,      10,    72,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_60000, HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"3840*2160p60 16:9"},
    {HDMI_4096X2160P24_256_135,	297000,	    24000,    4096,      2160,     1404,    90,      1020,    88,     296,    8,      10,    72,    HDMI_PICTURE_ASPECT_256_135,HDMI_VIDEO_TIMING_4096X2160P_24000,HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"4096*2160p24 256:135"},
    {HDMI_4096X2160P25_256_135,	297000,	    25000,    4096,      2160,     1184,    90,      968,     88,     128,    8,      10,    72,    HDMI_PICTURE_ASPECT_256_135,HDMI_VIDEO_TIMING_4096X2160P_25000,HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"4096*2160p25 256:135"},
    {HDMI_4096X2160P30_256_135,	297000,	    30000,    4096,      2160,     304,     90,      88,      88,     128,    8,      10,    72,    HDMI_PICTURE_ASPECT_256_135,HDMI_VIDEO_TIMING_4096X2160P_30000,HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"4096*2160p30 256:135"},
    {HDMI_4096X2160P50_256_135,	594000,	    50000,    4096,      2160,     1184,    90,      968,     88,     128,    8,      10,    72,    HDMI_PICTURE_ASPECT_256_135,HDMI_VIDEO_TIMING_4096X2160P_50000,HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"4096*2160p50 256:135"},
    {HDMI_4096X2160P60_256_135,	594000,	    60000,    4096,      2160,     304,     90,      88,      88,     128,    8,      10,    72,    HDMI_PICTURE_ASPECT_256_135,HDMI_VIDEO_TIMING_4096X2160P_60000,HDMI_VIDEO_PROGRESSIVE,	(HI_CHAR *)"4096*2160p60 256:135"},
    {HDMI_3840X2160P120_16_9,   1188000,    120000,   3840,      2160,     560,     90,      176,     88,     296,    8,      10,    72,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_120000,HDMI_VIDEO_PROGRESSIVE,   (HI_CHAR *)"3840*2160p120 16:9"},
    {HDMI_7680X4320P24_16_9,    1188000,    24000,    7680,      4320,     3320,    180,     2552,    176,    592,    16,     20,    144,   HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_7680X4320P_24000, HDMI_VIDEO_PROGRESSIVE,   (HI_CHAR *)"7680*4320p24 16:9"},
    {HDMI_7680X4320P25_16_9,    1188000,    25000,    7680,      4320,     3120,    80,      2352,    176,    592,    16,     20,    44,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_7680X4320P_25000, HDMI_VIDEO_PROGRESSIVE,   (HI_CHAR *)"7680*4320p25 16:9"},
    {HDMI_7680X4320P30_16_9,    1188000,    30000,    7680,      4320,     1320,    80,      552,     176,    592,    16,     20,    44,    HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_7680X4320P_30000, HDMI_VIDEO_PROGRESSIVE,   (HI_CHAR *)"7680*4320p30 16:9"},
};

// 4k mode
HDMI_VIDEO_4K_DEF_S s_stH14bHdmiVideoCodes_4K[CEA861FVideoCodesMax_4k] =
{
    {1, HDMI_3840X2160P30_16_9,     296703, 30, 3840,  2160, HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_30000, HDMI_VIDEO_PROGRESSIVE, 		(HI_CHAR *)"3840*2160p30 16:9"},
    {2, HDMI_3840X2160P25_16_9,     297000, 25, 3840,  2160, HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_25000, HDMI_VIDEO_PROGRESSIVE, 		(HI_CHAR *)"3840*2160p25 16:9"},
    {3, HDMI_3840X2160P24_16_9,     296703, 24, 3840,  2160, HDMI_PICTURE_ASPECT_16_9, HDMI_VIDEO_TIMING_3840X2160P_24000, HDMI_VIDEO_PROGRESSIVE, 		(HI_CHAR *)"3840*2160p24 16:9"},
    {4, HDMI_4096X2160P24_256_135,  297000, 24, 4096,  2160, HDMI_PICTURE_ASPECT_256_135, HDMI_VIDEO_TIMING_4096X2160P_24000, HDMI_VIDEO_PROGRESSIVE, 	(HI_CHAR *)"4096*2160p24 256:135"},
};



/*
** Des: vic search
**
*/
HDMI_VIDEO_CODE_E DRV_HDMI_VicSearch(HDMI_VIDEO_TIMING_E enTimming, HDMI_PICTURE_ASPECT enAspect, HI_BOOL b3DEnable)
{
    HI_U32 i = 0, u32VICSize = 0;
    HDMI_VIDEO_DEF_S *pstVideoId = &s_stCEAVideoCodesDes[0];
    HDMI_VIDEO_CODE_E enVic = 0;

    u32VICSize = sizeof(s_stCEAVideoCodesDes)/sizeof(s_stCEAVideoCodesDes[0]);

    for (i = 0; i < u32VICSize; i++, pstVideoId++)
    {
        if (enTimming == pstVideoId->enTiming && enAspect == pstVideoId->enAspectRatio)
        {
            enVic = pstVideoId->enVideoCode;
            break;
        }
    }

    if(HI_TRUE == b3DEnable)
    {
        // VIC = 0 when the timing is HDMI_3840X2160P24_16_9, HDMI_3840X2160P25_16_9,
        // HDMI_3840X2160P30_16_9, HDMI_4096X2160P24_256_135 at 2D mode
        if(enVic == HDMI_3840X2160P24_16_9 || enVic == HDMI_3840X2160P25_16_9 ||
           enVic == HDMI_3840X2160P30_16_9 || enVic == HDMI_4096X2160P24_256_135)
        {
            HDMI_INFO("4k x 2k 2D vic:%d \n", enVic);
            enVic = 0;
        }
    }

    return enVic;
}

HI_U32 DRV_HDMI_VicToIndex(HI_U32 u32Vic)
{
    HI_U32 i = 0, u32VICSize = 0;
    HDMI_VIDEO_DEF_S *pstVideoId = &s_stCEAVideoCodesDes[0];

    u32VICSize = sizeof(s_stCEAVideoCodesDes)/sizeof(s_stCEAVideoCodesDes[0]);

    for (i = 0; i < u32VICSize; i++, pstVideoId++)
    {
        if (u32Vic == pstVideoId->enVideoCode)
        {
            break;
        }
    }

    return  i;
}

#ifdef HDMI_FRL_SUPPORT
HDMI_VIDEO_DEF_S *DRV_HDMI_CommFormatParamGet(HDMI_VIC_E enVic)
{
    HI_U32              i = 0;
    HDMI_VIDEO_DEF_S    *pstTmpFmt= HI_NULL;

    for (i = 0,pstTmpFmt=&s_stCEAVideoCodesDes[0];
         i < HDMI_ARRAY_SIZE(s_stCEAVideoCodesDes);
         i++,pstTmpFmt++)
    {
        if (pstTmpFmt->enVideoCode == enVic )
        {
            return pstTmpFmt;
        }
    }
    HDMI_WARN("not support vic=%u\n",enVic);
    return HI_NULL;
}

HDMI_VIDEO_DEF_S *DRV_HDMI_VESAFormatParamGet(HDMI_VIDEO_TIMING_E enTimming)
{
    HI_U32              i = 0;
    HDMI_VIDEO_DEF_S    *pstTmpFmt= HI_NULL;

    for (i = 0,pstTmpFmt=&s_stVESAVideoCodesDes[0];
         i < HDMI_ARRAY_SIZE(s_stVESAVideoCodesDes);
         i++,pstTmpFmt++)
    {
        if (pstTmpFmt->enTiming == enTimming)
        {
            return pstTmpFmt;
        }
    }
    HDMI_WARN("not support vic=%u\n",enTimming);
    return HI_NULL;
}
#endif

HI_VOID HdmiRegWrite(volatile HI_VOID *pRegAddr, HI_U32 value)
{
    if (pRegAddr)
    {
        *(volatile HI_U32*)pRegAddr = value;
    }
}

HI_U32 HdmiRegRead(volatile HI_VOID *pRegAddr)
{
    if (HI_NULL == pRegAddr)
    {
        return 0;
    }
    return *(volatile HI_U32*)pRegAddr;
}

/** delay xx ms
**/
HI_VOID DRV_HDMI_MilliDelay(HI_U32 mSec)
{
#ifndef HDMI_BUILD_IN_BOOT
    HDMI_MSLEEP(mSec);
#else
    HDMI_UDELAY(mSec * 1000);
#endif
}
