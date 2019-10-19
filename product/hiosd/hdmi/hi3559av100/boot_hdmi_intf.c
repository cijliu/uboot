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
#include "hi_hdmi.h"

#include "boot_hdmi_intf.h"
#include "hdmi_product_define.h"

#define HDMI_MULTIPLE_2P0(x)         (x*=2)
#define HDMI_MULTIPLE_1P5(x)         (x=(x * 3) >> 1)
#define HDMI_MULTIPLE_1P25(x)        (x=(x * 5) >> 2)
#define HDMI_MULTIPLE_0P5(x)         (x>>=1)
#define HDMI_MAX_HDMI14_TMDS_RATE    340000


typedef struct{
	HI_U32	        	u32Vic;
    HI_U32	        	u32PixlFreq;                /* KHz */
	HI_U32	        	u32HorActive;
    HI_U32	        	u32VerActive;
	HI_U32	        	u32FieldRate;                /* 0.01Hz */
	HI_U32	        	u32Format;
} HDMI_FMT_PARAM_S;


#define HDMI_BOOT_ERR   printf("HDMI_ERR :%s[%d] ,", __func__, __LINE__); printf
#define HDMI_BOOT_INFO  printf("HDMI_INFO:%s[%d] ,", __func__, __LINE__); printf

#define CHECK_POINTER(p) \
do{                      \
    if(HI_NULL == p){\
        HDMI_BOOT_ERR("null pointer!\n"); \
        return HI_FAILURE;\
    } \
}while(0)

#define CHECK_FAILURE_RET(s32Ret) \
do{                      \
    if (HI_SUCCESS != s32Ret)\
    {\
        printf("ERROR:%s[%d] ,return fail!\n",__func__,__LINE__);\
        return HI_FAILURE;\
    }\
}while(0)

#define	HDMI_INVALID_PIXFREQ    0xffffffff
#define	HDMI_VIC_VIRTUAL_BASE   255U
#define	HDMI_VIC_PC_BASE        ((HDMI_VIC_VIRTUAL_BASE)+0x100)
#define	HDMI_ARRAY_SIZE(a)      (sizeof(a)/sizeof(a[0]))

#define VIDMODE_2_COLORSPACE(VidMode, ColorSpace) \
do \
{   \
    if (HI_HDMI_VIDEO_MODE_RGB444 == VidMode)\
    {\
        ColorSpace = HDMI_COLORSPACE_RGB;\
    }\
    else if (HI_HDMI_VIDEO_MODE_YCBCR422 == VidMode)\
    {\
        ColorSpace = HDMI_COLORSPACE_YCbCr422;\
    }\
    else if (HI_HDMI_VIDEO_MODE_YCBCR444 == VidMode)\
    {\
        ColorSpace = HDMI_COLORSPACE_YCbCr444;\
    }\
    else\
    {\
        ColorSpace = HDMI_COLORSPACE_YCbCr444;\
    }\
}while(0)


static HDMI_DEVICE_S s_stHdmiDev[HDMI_DEVICE_ID_BUTT];


static const HDMI_FMT_PARAM_S s_stFmtParamTable[] = {
    /********************VIC,PixFreq  , HACT ,VACT,FldRate,    EncFmt************************/
    {                         0, 106500 ,   1440,  900,  6000 ,	VO_OUTPUT_1440x900_60	    },        /* no std, vesa define */
    {                         0, 71000 ,   1280,  800,  6000 ,	VO_OUTPUT_1280x800_60	    },        /* no std, vesa define */
    {                         0, 119000 ,  1680,  1560, 6000 ,	VO_OUTPUT_1680x1050_60	    },        /* no std, vesa define */
    {                         0, 162000 ,  1600,  1200, 6000 ,	VO_OUTPUT_1600x1200_60	    },        /* no std, vesa define */
    {                         0, 268500 ,  2560,  1600, 6000 ,	VO_OUTPUT_2560x1600_60	    },        /* no std, vesa define */
    {                         0, 130000 ,  2560,  1440, 3000 ,	VO_OUTPUT_2560x1440_30	    },        /* no std, BVT define ,user defined */
    {                        0, 238750 ,  2560,  1440, 6000 ,   VO_OUTPUT_2560x1440_60      },          /* no std, BVT define ,user defined */
    {                         0, 170000 ,  1920,  2160, 3000 ,   VO_OUTPUT_1920x2160_30      },      /* no std, BVT define ,user defined */


    {                         1, 25175 ,   640 ,  480 , 6000 ,	VO_OUTPUT_640x480_60	    },        /* 1. 640 x 480p @ 60 VGA */
    {                         2, 27000 ,   720 ,  480 , 6000 ,	VO_OUTPUT_480P60	        },        /* 2,3 720 x 480p */
    {                         3, 27000 ,   720 ,  480 , 6000 ,	VO_OUTPUT_480P60	        },        /* 2,3 720 x 480p */
    {                         4, 74170 ,   1280,  720 , 6000 ,	VO_OUTPUT_720P60	        },        /* 4   1280 x 720p */
    {                         5, 74170 ,   1920,  1080, 6000 ,	VO_OUTPUT_1080I60	        },        /* 5 1920 x 1080i */
    {                         6, 27000 ,   720 ,  480 , 6000 ,	VO_OUTPUT_NTSC	            },        /* 6,7 720 x 480i, pix repl */
    {                         7, 27000 ,   720 ,  480 , 6000 ,	VO_OUTPUT_NTSC	            },        /* 6,7 720 x 480i, pix repl */
    {                    	16, 148500,   1920,  1080, 6000 ,	VO_OUTPUT_1080P60	        },        /* 16 1920 x 1080p */
    {                    	17, 27000 ,   720 ,  576 , 5000 ,	VO_OUTPUT_576P50	        },        /* 17,18 720 x 576p */
    {                    	18, 27000 ,   720 ,  576 , 5000 ,	VO_OUTPUT_576P50	        },        /* 17,18 720 x 576p */
    {                    	19, 74250 ,   1280,  720 , 5000 ,	VO_OUTPUT_720P50	        },        /* 19 1280 x 720p */
    {                    	20, 74250 ,   1920,  1080, 5000 ,	VO_OUTPUT_1080I50	        },        /* 20 1920 x 1080i */
    {                    	21, 27000 ,   1440,  576 , 5000 ,	VO_OUTPUT_PAL	            },        /* 21,22 1440 x 576i */
    {                    	22, 27000 ,   1440,  576 , 5000 ,	VO_OUTPUT_PAL	            },        /* 21,22 1440 x 576i */

    /********************VIC,PixFreq  , HACT ,VACT,FldRate,    EncFmt************************/
    {                    	31, 148500,   1920,  1080, 5000 ,	VO_OUTPUT_1080P50	        },        /* 31(1) 1920 x 1080p */
    {                    	32, 74170 ,   1920,  1080, 2400 ,	VO_OUTPUT_1080P24	        },        /* 32(2) 1920 x 1080p */
    {                    	33, 74250 ,   1920,  1080, 2500 ,	VO_OUTPUT_1080P25	        },        /* 33(3) 1920 x 1080p */
    {                    	34, 74170 ,   1920,  1080, 3000 ,	VO_OUTPUT_1080P30	        },        /* 34(4) 1920 x 1080p */



    {                        93, 297000 ,  3840,  2160, 2400 ,	VO_OUTPUT_3840x2160_24                  },
    {                        94, 297000 ,  3840,  2160, 2500 ,	VO_OUTPUT_3840x2160_25                  },
    {                    	95, 297000 ,  3840,  2160, 3000 ,	VO_OUTPUT_3840x2160_30                  },
    {                       96, 594000 ,  3840,  2160, 5000 ,   VO_OUTPUT_3840x2160_50	                },
    {                    	97, 594000 ,  3840,  2160, 6000 ,	VO_OUTPUT_3840x2160_60                  },
    {                       98, 297000 ,  4096,  2160, 2400 ,   VO_OUTPUT_4096x2160_24                  },
    {                       99, 297000 ,  4096,  2160, 2500 ,   VO_OUTPUT_4096x2160_25                  },
    {                       100, 297000 ,  4096,  2160, 3000 ,  VO_OUTPUT_4096x2160_30                  },
    {                       101, 594000 ,  4096,  2160, 5000 ,  VO_OUTPUT_4096x2160_50                  },
    {                       102, 594000 ,  4096,  2160, 6000 ,  VO_OUTPUT_4096x2160_60                  },
 /* {                    	98, 297000 ,  4096,  2160, 2400 ,	HI_HDMI_VIDEO_FMT_4096X2160P_24         }, */
 /* {                    	99, 297000 ,  4096,  2160, 2500 ,	HI_HDMI_VIDEO_FMT_4096X2160P_25         }, */
 /* {                       100, 297000 ,  4096,  2160, 3000 ,	HI_HDMI_VIDEO_FMT_4096X2160P_30         }, */
 /* {                       101, 594000 ,  4096,  2160, 5000 ,	HI_HDMI_VIDEO_FMT_4096X2160P_50         }, */
 /* {                       102, 594000 ,  4096,  2160, 6000 ,	HI_HDMI_VIDEO_FMT_4096X2160P_60         }, */
 /* {                       103, 297000 ,  3840,  2160, 2400 ,	HI_HDMI_VIDEO_FMT_3840X2160P_24         }, */
 /* {                       104, 297000 ,  3840,  2160, 2500 ,	HI_HDMI_VIDEO_FMT_3840X2160P_25         }, */
 /* {                       105, 297000 ,  3840,  2160, 3000 ,	HI_HDMI_VIDEO_FMT_3840X2160P_30         }, */
 /* {                       106, 594000 ,  3840,  2160, 5000 ,	HI_HDMI_VIDEO_FMT_3840X2160P_50         }, */
 /* {                       107, 594000 ,  3840,  2160, 6000 ,	HI_HDMI_VIDEO_FMT_3840X2160P_60         }, */

    /********************VIC,PixFreq  , HACT ,VACT,FldRate,    EncFmt************************/
    { HDMI_VIC_PC_BASE+      9, 37879 , 800 ,600 ,	6000 ,	VO_OUTPUT_800x600_60	},    /* 800x600@60.317 */
    { HDMI_VIC_PC_BASE+ 	13, 65000 , 1024,768 ,	6000 ,	VO_OUTPUT_1024x768_60	},    /* 1024x768@60 */
    /* { HDMI_VIC_PC_BASE+ 	18, 162000, 1600,1200,	6000 ,	HI_HDMI_VIDEO_FMT_VESA_1600X1200_60 }, */  /* 1600x1200@60 */
    { HDMI_VIC_PC_BASE+ 	25, 108000, 1280,1024,	6000 ,	VO_OUTPUT_1280x1024_60  },    /* 1280x1024@60 */
    { HDMI_VIC_PC_BASE+ 	28, 85500 , 1360,768 ,	6000 ,	VO_OUTPUT_1366x768_60	},    /* 1360x768@60 */
    { HDMI_VIC_PC_BASE+ 	41, 154000, 1920,1200,	6000 ,	VO_OUTPUT_1920x1200_60  },    /* 1920x1200@59.95 */

    /*for 2k & 4k ,we use VIRTUAL VIC*/
    /********************VIC,PixFreq  , HACT ,VACT,FldRate,    EncFmt************************/
    /* { HDMI_VIC_VIRTUAL_BASE+ 1, 297000,  3840,2160, 3000 ,	HI_HDMI_VIDEO_FMT_3840X2160P_30     }, */  /* 1 2160P@30 */
    /* { HDMI_VIC_VIRTUAL_BASE+ 2, 297000,  3840,2160, 2500 ,	HI_HDMI_VIDEO_FMT_3840X2160P_25     }, */  /* 2 2160P@25 */
    /* { HDMI_VIC_VIRTUAL_BASE+ 3, 297000,  3840,2160, 2400 ,	HI_HDMI_VIDEO_FMT_3840X2160P_24     }, */  /* 3 2160P@24 */
    /* { HDMI_VIC_VIRTUAL_BASE+ 4, 297000,  4096,2160, 2400 ,	HI_HDMI_VIDEO_FMT_4096X2160P_24     }, */  /* 4 4k*2K SMTP 4096*2160@24 */

};

static HI_U32 Hdmi_PixelFreqSearch(HI_U32 u32Fmt)
{
	HI_U32 i = 0;
	HDMI_FMT_PARAM_S *pstFmtParam = HI_NULL;

    HDMI_INFO("u32Fmt:%d. \n", u32Fmt);

	if (u32Fmt >= VO_OUTPUT_BUTT){
    	return HDMI_INVALID_PIXFREQ;
    }

	for (i = 0; i < HDMI_ARRAY_SIZE(s_stFmtParamTable); i++){
    	pstFmtParam = (HDMI_FMT_PARAM_S *)&s_stFmtParamTable[i];
    	if ((pstFmtParam != HI_NULL) && (pstFmtParam->u32Format == u32Fmt))
        {
        	return pstFmtParam->u32PixlFreq;
        }
    }

	HDMI_BOOT_INFO("PixFreq search fail,invalid format=%u\n", u32Fmt);

	return HDMI_INVALID_PIXFREQ;

}


static HDMI_VIDEO_TIMING_E DispFmt2HdmiTiming(HI_U32 u32Fmt)
{
    HDMI_VIDEO_TIMING_E enVideoTimingMode;
#if defined(CONFIG_HDMI_STB_SDK)
    switch (u32Fmt)
    {
        case HI_DRV_DISP_FMT_1080P_60:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_60000;
            break;
        case HI_DRV_DISP_FMT_1080P_50:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_50000;
            break;
        case HI_DRV_DISP_FMT_1080P_30:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_30000;
            break;
        case HI_DRV_DISP_FMT_1080P_25:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_25000;
            break;
        case HI_DRV_DISP_FMT_1080P_24:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_24000;
            break;
        case HI_DRV_DISP_FMT_1080i_60:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080I_60000;
            break;
        case HI_DRV_DISP_FMT_1080i_50:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080I_50000;
            break;
        case HI_DRV_DISP_FMT_720P_60:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1280X720P_60000;
            break;
        case HI_DRV_DISP_FMT_720P_50:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1280X720P_50000;
            break;
        case HI_DRV_DISP_FMT_576P_50:
            enVideoTimingMode = HDMI_VIDEO_TIMING_720X576P_50000;
            break;
        case HI_DRV_DISP_FMT_480P_60:
            enVideoTimingMode = HDMI_VIDEO_TIMING_720X480P_60000;
            break;
        case HI_DRV_DISP_FMT_3840X2160_24:
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_24000;
            break;
        case HI_DRV_DISP_FMT_3840X2160_25:
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_25000;
            break;
        case HI_DRV_DISP_FMT_3840X2160_30:
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_30000;
            break;
        case HI_DRV_DISP_FMT_4096X2160_24:
            enVideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_24000;
            break;
#if 0
        case HI_DRV_DISP_FMT_3840X2160_50:
            VideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_50000;
            break;
        case HI_DRV_DISP_FMT_3840X2160_60:
            VideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_60000;
            break;
#endif
        case HI_DRV_DISP_FMT_PAL:
        case HI_DRV_DISP_FMT_PAL_B:
        case HI_DRV_DISP_FMT_PAL_B1:
        case HI_DRV_DISP_FMT_PAL_D:
        case HI_DRV_DISP_FMT_PAL_D1:
        case HI_DRV_DISP_FMT_PAL_G:
        case HI_DRV_DISP_FMT_PAL_H:
        case HI_DRV_DISP_FMT_PAL_K:
        case HI_DRV_DISP_FMT_PAL_I:
        case HI_DRV_DISP_FMT_PAL_M:
        case HI_DRV_DISP_FMT_PAL_N:
        case HI_DRV_DISP_FMT_PAL_Nc:
        case HI_DRV_DISP_FMT_PAL_60:

        case HI_DRV_DISP_FMT_SECAM_SIN:
        case HI_DRV_DISP_FMT_SECAM_COS:
        case HI_DRV_DISP_FMT_SECAM_L:
        case HI_DRV_DISP_FMT_SECAM_B:
        case HI_DRV_DISP_FMT_SECAM_G:
        case HI_DRV_DISP_FMT_SECAM_D:
        case HI_DRV_DISP_FMT_SECAM_K:
        case HI_DRV_DISP_FMT_SECAM_H:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1440X576I_50000;
            break;
        case HI_DRV_DISP_FMT_NTSC:
        case HI_DRV_DISP_FMT_NTSC_J:
        case HI_DRV_DISP_FMT_NTSC_443:
            enVideoTimingMode = HDMI_VIDEO_TIMING_1440X480I_60000;
            break;
        case HI_DRV_DISP_FMT_861D_640X480_60:
            enVideoTimingMode = HDMI_VIDEO_TIMING_640X480P_60000;
            break;
        default:
            HDMI_BOOT_INFO("Non CEA video timing:%d\n", u32DispFmt);
            /* 4k2k && vesa */
            enVideoTimingMode = HDMI_VIDEO_TIMING_UNKNOWN;
            break;
    }

#elif defined(CONFIG_HDMI_BVT_SDK)
    switch (u32Fmt)
    {
        case VO_OUTPUT_PAL:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1440X576I_50000;
            break;
        case VO_OUTPUT_NTSC:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1440X480I_60000;
            break;

        case VO_OUTPUT_1080P24:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_24000;
            break;
        case VO_OUTPUT_1080P25:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_25000;
            break;
        case VO_OUTPUT_1080P30:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_30000;
            break;

        case VO_OUTPUT_720P50:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1280X720P_50000;
            break;
        case VO_OUTPUT_720P60:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1280X720P_60000;
            break;
        case VO_OUTPUT_1080I50:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080I_50000;
            break;
        case VO_OUTPUT_1080I60:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080I_60000;
            break;
        case VO_OUTPUT_1080P50:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_50000;
            break;
        case VO_OUTPUT_1080P60:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_60000;
            break;

        case VO_OUTPUT_576P50:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_720X576P_50000;
            break;
        case VO_OUTPUT_480P60:
        	enVideoTimingMode = HDMI_VIDEO_TIMING_720X480P_60000;
            break;

        case VO_OUTPUT_640x480_60:            /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
        	enVideoTimingMode = HDMI_VIDEO_TIMING_640X480P_60000;
            break;
        case VO_OUTPUT_3840x2160_30:          /* 3840x2160_30 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_30000;
            break;

        case VO_OUTPUT_3840x2160_60:          /* 3840x2160_60 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_60000;
            break;

        case VO_OUTPUT_3840x2160_24:          /* 3840x2160_24 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_24000;
            break;

        case VO_OUTPUT_3840x2160_25:          /* 3840x2160_25 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_25000;
            break;

        case VO_OUTPUT_3840x2160_50:          /* 3840x2160_50 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_50000;
            break;

        case VO_OUTPUT_4096x2160_30:          /* 4096x2160_30 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_30000;
            break;

        case VO_OUTPUT_4096x2160_60:          /* 4096x2160_60 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_60000;
            break;

        case VO_OUTPUT_4096x2160_24:          /* 4096x2160_24 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_24000;
            break;

        case VO_OUTPUT_4096x2160_25:          /* 4096x2160_25 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_25000;
            break;

        case VO_OUTPUT_4096x2160_50:          /* 4096x2160_50 */
            enVideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_50000;
            break;

        case VO_OUTPUT_800x600_60:            /* VESA 800 x 600 at 60 Hz (non-interlaced) */
        case VO_OUTPUT_1024x768_60:           /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
        case VO_OUTPUT_1280x1024_60:          /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
        case VO_OUTPUT_1366x768_60:           /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
        case VO_OUTPUT_1440x900_60:           /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
        case VO_OUTPUT_1280x800_60:           /* 1280*800@60Hz VGA@60Hz*/
        case VO_OUTPUT_1680x1050_60:          /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */
        case VO_OUTPUT_1920x2160_30:          /* 1920x2160_30 */
        case VO_OUTPUT_1600x1200_60:          /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
        case VO_OUTPUT_1920x1200_60:          /* VESA 1920 x 1600 at 60 Hz (non-interlaced) CVT (Reduced Blanking)*/
        case VO_OUTPUT_2560x1440_30:          /* 2560x1440_30 */
        case VO_OUTPUT_2560x1440_60:          /* 2560x1440_60 */
        case VO_OUTPUT_2560x1600_60:          /* 2560x1600_60 */
        case VO_OUTPUT_960H_PAL:              /* ITU-R BT.1302 960 x 576 at 50 Hz (interlaced)*/
        case VO_OUTPUT_960H_NTSC:             /* ITU-R BT.1302 960 x 480 at 60 Hz (interlaced)*/

        case VO_OUTPUT_USER:
        case VO_OUTPUT_BUTT:
        default:
            HDMI_BOOT_INFO("Non CEA video timing:%d\n", u32Fmt);
            /* 4k2k && vesa */
            enVideoTimingMode = HDMI_VIDEO_TIMING_UNKNOWN;
            break;

    }
#endif
    return enVideoTimingMode;
}

static HI_S32 DispFmt2VOAttr(HI_U32 u32DispFmt, HDMI_VO_ATTR_S *pstVideoAttr)
{
    pstVideoAttr->enVideoTiming = DispFmt2HdmiTiming(u32DispFmt);
    pstVideoAttr->u32ClkFs      = Hdmi_PixelFreqSearch(u32DispFmt);
    if (HDMI_INVALID_PIXFREQ == pstVideoAttr->u32ClkFs)
    {
        return HI_FAILURE;
    }

    if(pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_640X480P_60000 ||
       pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_720X480P_60000 ||
       pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_720X576P_50000)
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_709;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_4_3;
    }
    else if( pstVideoAttr->enVideoTiming <= HDMI_VIDEO_TIMING_4096X2160P_60000
          && pstVideoAttr->enVideoTiming >= HDMI_VIDEO_TIMING_4096X2160P_24000)
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_709;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_256_135;
    }
    else
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_709;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_16_9;
    }

    pstVideoAttr->bDEPol          = HI_FALSE;
    pstVideoAttr->bHSyncPol       = HI_FALSE;
    pstVideoAttr->bVSyncPol       = HI_FALSE;

    pstVideoAttr->u32PixelRepeat = 1;
    if (pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_1440X480I_60000 ||
        pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_1440X576I_50000)
    {
        pstVideoAttr->u32PixelRepeat = 2;
    }

    if (pstVideoAttr->enVideoTiming <= HDMI_VIDEO_TIMING_640X480P_60000)
    {
        pstVideoAttr->enRGBQuantization = HDMI_QUANTIZATION_RANGE_FULL;
    }
    else
    {
        pstVideoAttr->enYCCQuantization = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
    }

    if (pstVideoAttr->enVideoTiming != HDMI_VIDEO_TIMING_UNKNOWN)
    {
        pstVideoAttr->enInColorSpace = HDMI_COLORSPACE_YCbCr444;
    }
    else
    {
        pstVideoAttr->enInColorSpace = HDMI_COLORSPACE_RGB;
    }

    pstVideoAttr->enStereoMode    = HDMI_3D_BUTT;
    pstVideoAttr->enInBitDepth    = HDMI_VIDEO_BITDEPTH_10;
    pstVideoAttr->enActiveAspect  = HDMI_ACTIVE_ASPECT_PICTURE;

    return HI_SUCCESS;
}

static HI_S32 HdmiDeviceInit(HDMI_DEVICE_S * pstHdmiDev)
{
    HDMI_AO_ATTR_S*          pstAudioAttr;
    HDMI_VO_ATTR_S*          pstVideoAttr;
    HDMI_APP_ATTR_S*         pstAppAttr;
    CHECK_POINTER(pstHdmiDev);

    pstAudioAttr = &pstHdmiDev->stAttr.stAOAttr;
    pstVideoAttr = &pstHdmiDev->stAttr.stVOAttr;
    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;

    pstHdmiDev->enTmdsMode           = HDMI_TMDS_MODE_HDMI_1_4;
    /* application attribute init */
    pstAppAttr->bEnableHdmi          = HI_TRUE;
    pstAppAttr->bEnableClrSpaceAdapt = HI_TRUE;
    pstAppAttr->bEnableDeepClrAdapt  = HI_TRUE;

    /* video attribute init*/
    pstVideoAttr->enVideoTiming = HDMI_VIDEO_TIMING_1280X720P_50000;
    if(pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_640X480P_60000 ||
       pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_720X480P_60000 ||
       pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_720X576P_50000)
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_709;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_4_3;
    }
    else if( pstVideoAttr->enVideoTiming <= HDMI_VIDEO_TIMING_4096X2160P_60000
          && pstVideoAttr->enVideoTiming >= HDMI_VIDEO_TIMING_4096X2160P_24000)
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_709;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_256_135;
    }
    else
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_709;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_16_9;
    }

    pstVideoAttr->bDEPol          = HI_FALSE;
    pstVideoAttr->bHSyncPol       = HI_FALSE;
    pstVideoAttr->bVSyncPol       = HI_FALSE;

    pstVideoAttr->u32PixelRepeat  = 1;
    if (pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_1440X480I_60000 ||
        pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_1440X576I_50000)
    {
        pstVideoAttr->u32PixelRepeat = 2;
    }

    if (pstVideoAttr->enVideoTiming <= HDMI_VIDEO_TIMING_640X480P_60000)
    {
        pstVideoAttr->enRGBQuantization = HDMI_QUANTIZATION_RANGE_FULL;
    }
    else
    {
        pstVideoAttr->enYCCQuantization = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
    }

    if (pstVideoAttr->enVideoTiming != HDMI_VIDEO_TIMING_UNKNOWN)
    {
        pstVideoAttr->enInColorSpace = HDMI_COLORSPACE_YCbCr444;
    }
    else
    {
        pstVideoAttr->enInColorSpace = HDMI_COLORSPACE_RGB;
    }

    pstVideoAttr->enStereoMode    = HDMI_3D_BUTT;
    pstVideoAttr->enInBitDepth    = HDMI_VIDEO_BITDEPTH_10;
    pstVideoAttr->enActiveAspect  = HDMI_ACTIVE_ASPECT_PICTURE;

    /* audio attribute init*/
    pstAudioAttr->enSoundIntf   = HDMI_AUDIO_INTERFACE__I2S;
    pstAudioAttr->enSampleFs    = HDMI_SAMPLE_RATE_48K;
    pstAudioAttr->enSampleDepth = HDMI_AUDIO_BIT_DEPTH_16;
    pstAudioAttr->enChanels     = HDMI_AUDIO_FORMAT_2CH;

    return HI_SUCCESS;
}

#ifdef HDMI_SCDC_SUPPORT
static HI_S32 HdmiScrambleEnableSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable)
{
    HDMI_SCDC_STATUS_S      stScdcStatus;
    HDMI_SCDC_STATUS_S      stCurrentStatus;

    HDMI_INFO("scdc bEnable=%d\n",bEnable);

    stScdcStatus.u32ScrambleInterval    = 20;
    stScdcStatus.u32ScrambleTimeout     = 200;
    stScdcStatus.bSinkReadQuest         = HI_FALSE;
    stScdcStatus.bSinkScrambleOn        = bEnable;
    stScdcStatus.bSourceScrambleOn      = bEnable;
    stScdcStatus.u8TmdsBitClkRatio      = bEnable ? 40 : 10;

    pstHdmiDev->pstHdmiHal->HAL_HDMI_ScdcStatusGet(pstHdmiDev->pstHdmiHal, &stCurrentStatus);
    if ( stCurrentStatus.u8TmdsBitClkRatio != stScdcStatus.u8TmdsBitClkRatio
        || stCurrentStatus.bSinkScrambleOn != stScdcStatus.bSinkScrambleOn
        || stCurrentStatus.bSourceScrambleOn != stScdcStatus.bSourceScrambleOn )
    {
        HDMI_INFO("cur ClkRatio=%d,SinkScrambleOn=%d, SourceScramble=%d,set scdc!\n",
                                        stCurrentStatus.u8TmdsBitClkRatio ,
                                        stCurrentStatus.bSinkScrambleOn,
                                        stCurrentStatus.bSourceScrambleOn);
        pstHdmiDev->pstHdmiHal->HAL_HDMI_ScdcStatusSet(pstHdmiDev->pstHdmiHal, &stScdcStatus);
    }
    return HI_SUCCESS;
}
#endif

static HI_S32 HdmiModeSchedule(HDMI_DEVICE_S* pstHdmiDev)
{
#ifdef HDMI_SCDC_SUPPORT
    HI_BOOL  bScrambleEnable = HI_FALSE;
#endif

    if (pstHdmiDev->stAttr.stVOAttr.u32HdmiAdaptPixClk >= HDMI_MAX_HDMI14_TMDS_RATE)
    {
        //HDMI_INFO("AdaptPixClk(%d) is bigger than 340M, deepcolor will change to 8bit(%d). \n", pstVideoAttr->u32HdmiAdaptPixClk, pstAppAttr->enDeepColorMode);
        /* sdk@2016.02.22, when the u32HdmiAdaptPixClk is bigger than 340 at 10bit or 12bit,
        the fmt will force change yuv422, 8bit, the u32HdmiAdaptPixClk must restore. */
        //pstVideoAttr->u32HdmiAdaptPixClk = pstVideoAttr->u32ClkFs;
        //pstAppAttr->enDeepColorMode = HDMI_DEEP_COLOR_24BIT;
        /* enOutColorSpace should change to YCbCr422 for 10bit out. */
        //pstAppAttr->enOutColorSpace = HDMI_COLORSPACE_YCbCr422;
        pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_2_0;
    }
    else
    {
        if (pstHdmiDev->stAttr.stAppAttr.bEnableHdmi == HI_TRUE)
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_1_4;
        }
        else
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_DVI;
            pstHdmiDev->stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_RGB;
        }
    }
    HDMI_INFO("Tmds mode switch to %d,outSpace=%d\n",pstHdmiDev->enTmdsMode,pstHdmiDev->stAttr.stAppAttr.enOutColorSpace);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_TmdsModeSet(pstHdmiDev->pstHdmiHal, pstHdmiDev->enTmdsMode);
#ifdef HDMI_SCDC_SUPPORT
    bScrambleEnable = (pstHdmiDev->enTmdsMode == HDMI_TMDS_MODE_HDMI_2_0) ? HI_TRUE : HI_FALSE;
    HdmiScrambleEnableSet(pstHdmiDev, bScrambleEnable);
#endif

    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_Open(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_S32 s32Ret = HI_FAILURE;
    CHECK_POINTER(pstHdmiDev);

    /* open hdmi hal module*/
    s32Ret = HAL_HDMI_Open(HI_NULL, &pstHdmiDev->pstHdmiHal);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    HdmiDeviceInit(pstHdmiDev);
    pstHdmiDev->pstHdmiHal->stHalCtx.hHdmiDev = pstHdmiDev;
    pstHdmiDev->pstHdmiHal->stHalCtx.u32HdmiID = pstHdmiDev->u32HdmiDevId;

    pstHdmiDev->pstHdmiHal->HAL_HDMI_HardwareInit(pstHdmiDev->pstHdmiHal);

    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_AVMuteSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bAvMute)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_AvMuteSet(pstHdmiDev->pstHdmiHal, bAvMute);

    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_Start(HDMI_DEVICE_S* pstHdmiDev)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);

    HdmiModeSchedule(pstHdmiDev);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyPowerEnableSet(pstHdmiDev->pstHdmiHal, HI_TRUE);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyOutputEnableSet(pstHdmiDev->pstHdmiHal, HI_TRUE);
    DRV_HDMI_AVMuteSet(pstHdmiDev, HI_FALSE);

    return HI_SUCCESS;
}


HI_S32 DRV_HDMI_Stop(HDMI_DEVICE_S* pstHdmiDev)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    DRV_HDMI_AVMuteSet(pstHdmiDev, HI_TRUE);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyOutputEnableSet(pstHdmiDev->pstHdmiHal, HI_FALSE);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyPowerEnableSet(pstHdmiDev->pstHdmiHal, HI_FALSE);
    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_Close(HDMI_DEVICE_S* pstHdmiDev)
{
    CHECK_POINTER(pstHdmiDev);

    DRV_HDMI_Stop(pstHdmiDev);
    HAL_HDMI_Close(pstHdmiDev->pstHdmiHal);
    return HI_SUCCESS;
}


static HI_S32 CheckVideoAttr(HDMI_VO_ATTR_S* pstVOAttr)
{
    CHECK_POINTER(pstVOAttr);

    if (pstVOAttr->enVideoTiming >= HDMI_VIDEO_TIMING_BUTT)
    {
        HDMI_BOOT_INFO("Hdmi video timing(%d) is wrong\n", pstVOAttr->enVideoTiming);
        return HI_FAILURE;
    }

/*
    if (pstVOAttr->enHvSyncPol > HDMI_HV_SYNC_POL_HNVN ||
        pstVOAttr->enHvSyncPol < 0)
    {
        HDMI_BOOT_INFO("Hdmi video HvSyncPol(%d) is wrong\n", pstVOAttr->enHvSyncPol);
        return HI_FAILURE;
    }
*/

    if (pstVOAttr->enInColorSpace >= HDMI_COLORSPACE_BUTT)
    {
        HDMI_BOOT_INFO("Hdmi video InColorSpace(%d) is wrong\n", pstVOAttr->enInColorSpace);
        return HI_FAILURE;
    }

    if (pstVOAttr->enColorimetry <= HDMI_COLORIMETRY__NONE ||
        pstVOAttr->enColorimetry > HDMI_COLORIMETRY__EXTENDED)
    {
        HDMI_BOOT_INFO("Hdmi video Colorimetry(%d) is wrong\n", pstVOAttr->enColorimetry);
        return HI_FAILURE;
    }

    if (pstVOAttr->enRGBQuantization > HDMI_QUANTIZATION_RANGE_FULL)
    {
        HDMI_BOOT_INFO("Hdmi video RGBQuantization(%d) is wrong\n", pstVOAttr->enRGBQuantization);
        return HI_FAILURE;
    }

    if (pstVOAttr->enPictureAspect < HDMI_PICTURE_ASPECT_4_3 ||
        pstVOAttr->enPictureAspect > HDMI_PICTURE_ASPECT_256_135)
    {
        HDMI_BOOT_INFO("Hdmi video PictureAspect(%d) is wrong\n", pstVOAttr->enPictureAspect);
        return HI_FAILURE;
    }

    if (pstVOAttr->enInBitDepth > HDMI_VIDEO_BITDEPTH_12)
    {
        HDMI_BOOT_INFO("Hdmi video InBitDepth(%d) is wrong\n", pstVOAttr->enInBitDepth);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 HdmiVideoPathSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstVOAttr)
{
    HDMI_VIDEO_CONFIG_S stVideoCfg = {0};
    HDMI_APP_ATTR_S*    pstAppAttr;
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstVOAttr);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);

    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;

    stVideoCfg.enInBitDepth     = pstVOAttr->enInBitDepth;
    stVideoCfg.enQuantization   = pstVOAttr->enRGBQuantization;
    stVideoCfg.enInColorSpace   = pstVOAttr->enInColorSpace;
    stVideoCfg.u32PixelClk      = (pstAppAttr->enOutColorSpace == HDMI_COLORSPACE_YCbCr420) ?
                                  (pstVOAttr->u32ClkFs >> 1) : pstVOAttr->u32ClkFs;
    stVideoCfg.u32TmdsClk       = pstVOAttr->u32HdmiAdaptPixClk;
    stVideoCfg.enDeepColor      = pstAppAttr->enDeepColorMode;
    stVideoCfg.enOutColorSpace  = pstAppAttr->enOutColorSpace;
    stVideoCfg.bDEPol           = pstVOAttr->bDEPol;
    stVideoCfg.bHSyncPol        = pstVOAttr->bHSyncPol;
    stVideoCfg.bVSyncPol        = pstVOAttr->bVSyncPol;

    switch (pstVOAttr->enColorimetry)
    {
        case HDMI_COLORIMETRY__ITU_601:
            stVideoCfg.enConvStd = HDMI_CONV_STD_BT_601;
            break;
        case HDMI_COLORIMETRY__ITU_709:
            stVideoCfg.enConvStd = HDMI_CONV_STD_BT_709;
            break;
        case HDMI_COLORIMETRY__EXTENDED:
            if (pstVOAttr->enExtendedColorimetry == HDMI_EXTENDED_COLORIMETRY_2020_non_const_luminous)
                stVideoCfg.enConvStd = HDMI_CONV_STD_BT_2020_non_const_luminous;
            else if (pstVOAttr->enExtendedColorimetry == HDMI_EXTENDED_COLORIMETRY_2020_const_luminous)
                stVideoCfg.enConvStd = HDMI_CONV_STD_BT_2020_const_luminous;
            break;
        default:
            break;
    }

    HDMI_INFO("u32PixelClk(%d), u32TmdsClk(%d)\n", stVideoCfg.u32PixelClk, stVideoCfg.u32TmdsClk);

    /* Video will mute and unmute in this function call*/
    pstHdmiDev->pstHdmiHal->HAL_HDMI_VideoPathSet(pstHdmiDev->pstHdmiHal, &stVideoCfg);
    return HI_SUCCESS;
}

#if 0
static HI_S32 HdmiAudioPathSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr)
{
    HDMI_AUDIO_CONFIG_S      stAudioCfg;

    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAOAttr);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);

    stAudioCfg.bDownSample   = pstAOAttr->bDownSample;
    stAudioCfg.enLayout      = pstAOAttr->enChanels;
    stAudioCfg.enSampleDepth = pstAOAttr->enSampleDepth;
    stAudioCfg.enSampleFs    = pstAOAttr->enSampleFs;
    stAudioCfg.enSoundIntf   = pstAOAttr->enSoundIntf;
    pstHdmiDev->pstHdmiHal->HAL_HDMI_AudioPathSet(pstHdmiDev->pstHdmiHal, &stAudioCfg);

    return HI_SUCCESS;

}

HI_S32 DRV_HDMI_VOAttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstVOAttr)
{
    HDMI_AO_ATTR_S*          pstAudioAttr;
    HDMI_VO_ATTR_S*          pstVideoAttr;
    HDMI_APP_ATTR_S*         pstAppAttr;
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstVOAttr);

    if (HI_SUCCESS != CheckVideoAttr(pstVOAttr))
    {
        HDMI_COM_ERR("HDMI_CheckVideoAttr fail\n");
        return HI_FAILURE;
    }

    pstAudioAttr = &pstHdmiDev->stAttr.stAOAttr;
    pstVideoAttr = &pstHdmiDev->stAttr.stVOAttr;
    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;

    memcpy(pstVideoAttr, pstVOAttr, sizeof(HDMI_VO_ATTR_S));

    if (pstAppAttr->bEnableHdmi && pstVideoAttr->enVideoTiming >= HDMI_VIDEO_TIMING_3840X2160P_50000)
    {
        if (pstAppAttr->enOutColorSpace != HDMI_COLORSPACE_YCbCr420)
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_2_0;
        }
        else
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_1_4;
        }
    }

    HdmiVideoPathSet(pstHdmiDev, pstVOAttr);
    DRV_HDMI_AVIInfoFrameSet(&pstHdmiDev->stInfoFrame);
#if 0
    HdmiAudioPathSet(pstHdmiDev, pstAudioAttr);
    HDMI_AudioInfoFrameSet(&pstHdmiDev->stInfoFrame);
#endif
    DRV_HDMI_VendorInfoFrameSet(&pstHdmiDev->stInfoFrame);

    //DRV_HDMI_Start(pstHdmiDev);
    return HI_SUCCESS;
}
#endif

HI_S32 DRV_HDMI_AttrGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAttr);

    memcpy(pstAttr, &pstHdmiDev->stAttr, sizeof(HDMI_ATTR_S));
    return HI_SUCCESS;
}

#ifdef HDMI_EMI_SUPPORT
HI_S32 DRV_HDMI_EmiSet(HDMI_DEVICE_S* pstHdmiDev)
{
    HDMI_EMI_CONFIG_S stEmiConfig;
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);

    HDMI_INFO(">>> DRV_HDMI_EmiSet in...\n");
#ifdef HDMI_EMI_ENABLE
    pstHdmiDev->bEmiEnable = HI_TRUE;
#else
    pstHdmiDev->bEmiEnable = HI_FALSE;
#endif
    stEmiConfig.bVesaFmt = (pstHdmiDev->stAttr.stVOAttr.enVideoTiming >= HDMI_VIDEO_TIMING_VESA_DEFINE) ? HI_TRUE : HI_FALSE;
    stEmiConfig.bEmiEnable = pstHdmiDev->bEmiEnable;
    stEmiConfig.bDebugEnable = HI_FALSE;
    stEmiConfig.u32PixClk = pstHdmiDev->stAttr.stVOAttr.u32HdmiAdaptPixClk;
    stEmiConfig.enDeepColor = pstHdmiDev->stAttr.stAppAttr.enDeepColorMode;
    stEmiConfig.enOutColorSpace = pstHdmiDev->stAttr.stAppAttr.enOutColorSpace;

    pstHdmiDev->pstHdmiHal->HAL_HDMI_EmiSet(pstHdmiDev->pstHdmiHal, &stEmiConfig);

    HDMI_INFO("<<< DRV_HDMI_EmiSet out...\n");
    return HI_SUCCESS;
}
#endif

static HI_S32 HdmiTMDSClkGet(HDMI_DEVICE_S* pstHdmiDev)
{
    HDMI_APP_ATTR_S*         pstAppAttr;
    HDMI_VO_ATTR_S*          pstVideoAttr;

    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;
    pstVideoAttr = &pstHdmiDev->stAttr.stVOAttr;

    pstVideoAttr->u32HdmiAdaptPixClk = pstVideoAttr->u32ClkFs;

    //if(pstVideoAttr->u32HdmiAdaptPixClk >= HDMI_MAX_HDMI14_TMDS_RATE)
    if(pstAppAttr->enOutColorSpace == HDMI_COLORSPACE_YCbCr420)
    {
        HDMI_MULTIPLE_0P5(pstVideoAttr->u32HdmiAdaptPixClk);//Y420
        HDMI_MULTIPLE_0P5(pstVideoAttr->u32ClkFs);
        //pstAppAttr->enDeepColorMode = HDMI_DEEP_COLOR_24BIT;
        //pstAppAttr->enOutColorSpace = HDMI_COLORSPACE_YCbCr420;
        //HDMI_INFO("Enable YUV420,force 8bit & pixClk=%u\n",pstVideoAttr->u32HdmiAdaptPixClk);
    }
    if (pstAppAttr->enOutColorSpace != HDMI_COLORSPACE_YCbCr422)
    {
        switch(pstAppAttr->enDeepColorMode)
        {
            case HDMI_DEEP_COLOR_30BIT:
                    HDMI_MULTIPLE_1P25(pstVideoAttr->u32HdmiAdaptPixClk);
                    break;

            case HDMI_DEEP_COLOR_36BIT:
                    HDMI_MULTIPLE_1P5(pstVideoAttr->u32HdmiAdaptPixClk);
                    break;

            case HDMI_DEEP_COLOR_48BIT:
                    HDMI_MULTIPLE_2P0(pstVideoAttr->u32HdmiAdaptPixClk);
                    break;

            case HDMI_DEEP_COLOR_24BIT:
            case HDMI_DEEP_COLOR_OFF:
            default:
                    pstAppAttr->enDeepColorMode = HDMI_DEEP_COLOR_24BIT;
                    break;
        }
    }
    else
    {
        pstAppAttr->enDeepColorMode = HDMI_DEEP_COLOR_OFF;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_AttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr)
{
    HDMI_VO_ATTR_S*          pstVideoAttr;

    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAttr);

    pstVideoAttr = &pstAttr->stVOAttr;
    CheckVideoAttr(pstVideoAttr);
    memcpy(&pstHdmiDev->stAttr, pstAttr, sizeof(HDMI_ATTR_S));

    /* YUV422 is not support when the fmt is PAL or NTSC. */
    if(   HDMI_VIDEO_TIMING_1440X480I_60000 == pstHdmiDev->stAttr.stVOAttr.enVideoTiming
       || HDMI_VIDEO_TIMING_1440X576I_50000 == pstHdmiDev->stAttr.stVOAttr.enVideoTiming)
    {
        if(HDMI_COLORSPACE_YCbCr422 == pstHdmiDev->stAttr.stAppAttr.enOutColorSpace)
        {
            HDMI_INFO("Y422 is not support at pal and ntsc, force adapt to rgb.\n");
            pstHdmiDev->stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_RGB;
        }
    }

    HdmiTMDSClkGet(pstHdmiDev);

    HdmiVideoPathSet(pstHdmiDev, &pstHdmiDev->stAttr.stVOAttr);
    DRV_HDMI_AVIInfoFrameSend(&pstHdmiDev->stInfoFrame, HI_TRUE);

    DRV_HDMI_VendorInfoFrameSend(&pstHdmiDev->stInfoFrame, HI_TRUE);
#ifdef HDMI_EMI_SUPPORT
    DRV_HDMI_EmiSet(pstHdmiDev);
#endif
    return HI_SUCCESS;
}

HI_S32 HI_DRV_HDMI_Init(HI_VOID)
{
   return HI_SUCCESS;
}

HI_S32 HI_DRV_HDMI_Open(HI_UNF_HDMI_ID_E enHdmiID)
{
    memset(&s_stHdmiDev[enHdmiID], 0, sizeof(HDMI_DEVICE_S));

    s_stHdmiDev[enHdmiID].u32HdmiDevId = enHdmiID;

    return DRV_HDMI_Open(&s_stHdmiDev[enHdmiID]);
}

HI_S32 HI_DRV_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmiID, HI_DRV_HDMI_ATTR_S *pstAttr)
{
    HDMI_ATTR_S stAttr;
    HI_S32 s32Ret = HI_SUCCESS;

    memset(&stAttr, 0, sizeof(HDMI_ATTR_S));
    DRV_HDMI_AttrGet(&s_stHdmiDev[enHdmiID], &stAttr);
    s32Ret = DispFmt2VOAttr(pstAttr->u32DispFmt, &stAttr.stVOAttr);
    if (s32Ret != HI_SUCCESS)
    {
        HDMI_BOOT_INFO("Please input a correct Fmt(%d)!\n", pstAttr->u32DispFmt);
        return s32Ret;
    }

    stAttr.stAppAttr.bEnableHdmi     = pstAttr->bEnableHdmi;

    VIDMODE_2_COLORSPACE(pstAttr->enVidOutMode, stAttr.stAppAttr.enOutColorSpace);
    VIDMODE_2_COLORSPACE(pstAttr->enVidInMode, stAttr.stVOAttr.enInColorSpace);

    return DRV_HDMI_AttrSet(&s_stHdmiDev[enHdmiID], &stAttr);
}

void hdmi_stop(void)
{
    HI_DRV_HDMI_Close( HI_HDMI_ID_0);
    HI_DRV_HDMI_DeInit();
    return ;
}

int hdmi_display(unsigned int vosync, unsigned int input, unsigned int output)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_HDMI_ATTR_S stAttr;

    s32Ret = HI_DRV_HDMI_Init();
    CHECK_FAILURE_RET(s32Ret);

    s32Ret = HI_DRV_HDMI_Open(HI_HDMI_ID_0);
    CHECK_FAILURE_RET(s32Ret);

    stAttr.bEnableHdmi = HI_TRUE;
    stAttr.u32DispFmt = vosync;
    stAttr.enVidOutMode = output;
    stAttr.enVidInMode = input;
    s32Ret = HI_DRV_HDMI_SetAttr(HI_HDMI_ID_0, &stAttr);
    CHECK_FAILURE_RET(s32Ret);

    s32Ret = HI_DRV_HDMI_Start(HI_HDMI_ID_0 );
    CHECK_FAILURE_RET(s32Ret);

    return s32Ret;
}

#if 0
HI_S32 HI_DRV_HDMI_GetAttr(HI_UNF_HDMI_ID_E enHdmiID, HDMI_ATTR_S *pstAttr)
{
    return DRV_HDMI_AttrGet(&s_stHdmiDev[enHdmiID], pstAttr);
}
#endif
HI_S32 HI_DRV_HDMI_Start(HI_UNF_HDMI_ID_E enHdmiID)
{
    return DRV_HDMI_Start(&s_stHdmiDev[enHdmiID]);
}

HI_S32 HI_DRV_HDMI_Close(HI_UNF_HDMI_ID_E enHdmiID)
{
    return DRV_HDMI_Close(&s_stHdmiDev[enHdmiID]);
}

HI_S32 HI_DRV_HDMI_DeInit(HI_VOID)
{
   return HI_SUCCESS;
}

HI_S32 HI_UNF_HDMI_Init(void)
{
    return HI_DRV_HDMI_Init();
}

HI_S32 HI_UNF_HDMI_DeInit(void)
{
    return HI_DRV_HDMI_DeInit();
}


HI_S32 HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_E enHdmi)
{
    return HI_DRV_HDMI_Open(enHdmi);
}
#if 0
HI_S32 HI_UNF_HDMI_SetFormat(HI_UNF_HDMI_ID_E enHdmi, HI_U32 u32DispFmt)
{
    return HI_DRV_HDMI_SetFormat(enHdmi, u32DispFmt);
}
#endif
HI_S32 HI_UNF_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr)
{
    return HI_DRV_HDMI_SetAttr(enHdmi, (HI_DRV_HDMI_ATTR_S*)pstAttr);
}
#if 0
HI_S32 HI_UNF_HDMI_GetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr)
{
    return HI_DRV_HDMI_GetAttr(enHdmi, pstAttr);
}
#endif
HI_S32 HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_E enHdmi)
{
    return HI_DRV_HDMI_Start(enHdmi);
}


HI_S32 HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_E enHdmi)
{
    return HI_DRV_HDMI_Close(enHdmi);
}




