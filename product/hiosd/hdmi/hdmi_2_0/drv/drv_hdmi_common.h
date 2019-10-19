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
#ifndef __DRV_HDMI_COMMON_H_
#define __DRV_HDMI_COMMON_H_

#include "hi_type.h"
#include "drv_hdmi_infoframe.h"
#include "drv_hdmi_dfm.h"

/******************************************************************************/
/* HDMI Version                                                               */
/******************************************************************************/
#define HDMI_VER_MAJOR    2
#define HDMI_VER_MINOR    0
#define HDMI_VER_REVISE   0
#define HDMI_VER_DATE     20181130
#define HDMI_VER_TIMES    0

#define MAKE_VER_BIT(x) # x
#define MAKE_MACRO2STR(exp) MAKE_VER_BIT(exp)
#define MAKE_VERSION \
    MAKE_MACRO2STR(HDMI_VER_MAJOR) "."  \
    MAKE_MACRO2STR(HDMI_VER_MINOR) "."  \
    MAKE_MACRO2STR(HDMI_VER_REVISE) "." \
    MAKE_MACRO2STR(HDMI_VER_DATE) "."   \
    MAKE_MACRO2STR(HDMI_VER_TIMES)
//FRL
#define MAX_FRL_RATE            6
#define HDMI_FRL_LANE_MAX_NUM   4

/******************************************************************************/
/* HDMI define                                                                */
/******************************************************************************/
#ifndef HDMI_BUILD_IN_BOOT
#define HAL_CALL_RET(pfunc,param...) ({\
    HI_S32 s32Return = HI_ERR_HDMI_NUL_PTR;\
    if (pstHdmiDev && pstHdmiDev->pstHdmiHal && pstHdmiDev->pstHdmiHal->pfunc){\
        s32Return = pstHdmiDev->pstHdmiHal->pfunc(pstHdmiDev->pstHdmiHal, param);}\
    else{\
        HDMI_WARN("null pointer! \n");}\
    s32Return;\
})

#define HAL_CALL(pfunc,param...) ({\
    HI_S32 s32Return = HI_ERR_HDMI_NUL_PTR;\
    if (pstHdmiDev && pstHdmiDev->pstHdmiHal && pstHdmiDev->pstHdmiHal->pfunc){\
        pstHdmiDev->pstHdmiHal->pfunc(pstHdmiDev->pstHdmiHal, param);\
        s32Return = HI_SUCCESS;}\
    else{\
        HDMI_WARN("null pointer! \n");}\
    s32Return; \
})

#define HAL_CALL_NOPARAM(pfunc) ({\
    HI_S32 s32Return = HI_ERR_HDMI_NUL_PTR;\
    if (pstHdmiDev && pstHdmiDev->pstHdmiHal && pstHdmiDev->pstHdmiHal->pfunc){\
        pstHdmiDev->pstHdmiHal->pfunc(pstHdmiDev->pstHdmiHal);\
        s32Return = HI_SUCCESS;}\
    else{\
        HDMI_WARN("null pointer! \n");}\
    s32Return;\
})
#else
#define HAL_CALL_RET(pfunc,param...) ({\
        HI_S32 s32Return = HI_FAILURE;\
        if (pstHdmiDev && pstHdmiDev->pstHdmiHal && pstHdmiDev->pstHdmiHal->pfunc){\
            s32Return = pstHdmiDev->pstHdmiHal->pfunc(pstHdmiDev->pstHdmiHal, param);}\
        else{\
            HDMI_WARN("null pointer! \n");}\
        s32Return;\
    })

#define HAL_CALL(pfunc,param...) ({\
        HI_S32 s32Return = HI_FAILURE;\
        if (pstHdmiDev && pstHdmiDev->pstHdmiHal && pstHdmiDev->pstHdmiHal->pfunc){\
            pstHdmiDev->pstHdmiHal->pfunc(pstHdmiDev->pstHdmiHal, param);\
            s32Return = HI_SUCCESS;}\
        else{\
            HDMI_WARN("null pointer! \n");}\
        s32Return; \
    })

#define HAL_CALL_NOPARAM(pfunc) ({\
        HI_S32 s32Return = HI_FAILURE;\
        if (pstHdmiDev && pstHdmiDev->pstHdmiHal && pstHdmiDev->pstHdmiHal->pfunc){\
            pstHdmiDev->pstHdmiHal->pfunc(pstHdmiDev->pstHdmiHal);\
            s32Return = HI_SUCCESS;}\
        else{\
            HDMI_WARN("null pointer! \n");}\
        s32Return;\
    })

#endif

#define HDMI_HAL_CALL(pfunc,param...) ({\
    s32Ret = HAL_CALL(pfunc, param); \
    if (HI_SUCCESS != s32Ret) \
    {\
        return s32Ret; \
    }\
})

/******************************************************************************/
/* Enum define                                                                */
/******************************************************************************/
typedef enum
{
    HDMI_DEVICE_ID0,
    HDMI_DEVICE_ID_BUTT,
}HDMI_DEVICE_ID_E;

typedef enum
{
    HDMI_THREAD_STATE_RUN,
    HDMI_THREAD_STATE_STOP,
}HDMI_THREAD_STATE_E;

typedef enum
{
    HDMI_EVENT_HOTPLUG = 0x10,
    HDMI_EVENT_HOTUNPLUG,
    HDMI_EVENT_EDID_FAIL,
    HDMI_EVENT_HDCP_FAIL,
    HDMI_EVENT_HDCP_SUCCESS,
    HDMI_EVENT_RSEN_CONNECT,
    HDMI_EVENT_RSEN_DISCONNECT,
    HDMI_EVENT_HDCP_USERSETTING,
    HDMI_EVENT_HDCP_OFF,
    HDMI_EVENT_SCRAMBLE_FAIL,
    HDMI_EVENT_SCRAMBLE_SUCCESS,
    HDMI_EVENT_ZERO_DRMIF_TIMEOUT,
    HDMI_EVENT_SWITCH_TO_HDRMODE_TIMEOUT,
    HDMI_EVENT_BUTT
}HDMI_EVENT_E;

typedef enum
{
    HDMI_INT_TYPE_NONE,
    HDMI_INT_TYPE_HPD_RSEN,
    HDMI_INT_TYPE_HDCP,
    HDMI_INT_TYPE_HDCP2x,
    HDMI_INT_TYPE_CEC,
} HDMI_INT_TYPE_E;

typedef HI_S32 (*HMDI_CALLBACK)(HI_VOID*, HDMI_EVENT_E);

typedef struct
{
    HI_VOID         *pvEventData;
    HMDI_CALLBACK   pfnEventCallBack;
    HI_U32          u32HdmiDevId;
    HI_CHAR         *pcBaseAddr;
}HDMI_HAL_INIT_S;
#define HDMI_ARRAY_SIZE(a)              (sizeof(a)/sizeof(a[0]))

#define FMT_PIX_CLK_13400                13400
#define FMT_PIX_CLK_74250                74250
#define FMT_PIX_CLK_165000               165000
#define FMT_PIX_CLK_190000               190000
#define FMT_PIX_CLK_297000               297000
#define FMT_PIX_CLK_340000               340000

#define ZERO_DRMIF_SEND_TIME             2000   /* unit: ms */
#define HDRMODE_CHANGE_TIME              500    /* unit: ms */

#define HDMI_EDID_BLOCK_SIZE             128
#define HDMI_EDID_TOTAL_BLOCKS           4
#define HDMI_EDID_SIZE (HDMI_EDID_BLOCK_SIZE * HDMI_EDID_TOTAL_BLOCKS)

typedef struct
{
    HI_U8                           u8EdidValid;
    HI_U32                          u32EdidLen;
    HI_U8                           u8Edid[HDMI_EDID_SIZE];
}HDMI_EDID_RAWDATA_S;

typedef struct
{
    HI_U8  *pu8InputEncryptedKeyAddr;
    HI_U32  u32KeyLength;
}HDMI_LOAD_KEY_S;

typedef struct
{
    HI_U32  u32InputEncryptedKeyAddr;
    HI_U32  u32KeyLength;
}HDMI_COMPAT_LOAD_KEY_S;

typedef enum
{
    HDMI_HDCP_VERSION_NONE,
    HDMI_HDCP_VERSION_1_4,
    HDMI_HDCP_VERSION_2_2,
    HDMI_HDCP_VERSION_BUTT
}HDMI_HDCP_VERSION_E;

/**HDMI status*/
typedef struct
{
    HI_BOOL             bConnected;
    HI_BOOL             bSinkPowerOn;
    HI_BOOL             bAuthed;
    HI_U8               u8Bksv[5];
    HDMI_HDCP_VERSION_E enHdcpVersion;
}HDMI_STATUS_S;

/*********************video data Structure*******************************************/

/**HDMI Deep color mode*/
typedef enum
{
    HDMI_DEEP_COLOR_24BIT = 0x00,
    HDMI_DEEP_COLOR_30BIT,
    HDMI_DEEP_COLOR_36BIT,
    HDMI_DEEP_COLOR_48BIT,
    HDMI_DEEP_COLOR_OFF   = 0xff,
    HDMI_DEEP_COLOR_BUTT
}HDMI_DEEP_COLOR_E;

typedef enum
{
    HDMI_VIDEO_BITDEPTH_8,
    HDMI_VIDEO_BITDEPTH_10,
    HDMI_VIDEO_BITDEPTH_12,
    HDMI_VIDEO_BITDEPTH_16,
    HDMI_VIDEO_BITDEPTH_OFF,
    HDMI_VIDEO_BITDEPTH_BUTT
}HDMI_VIDEO_BITDEPTH_E;

typedef enum
{
    HDMI_HV_SYNC_POL_HPVP,
    HDMI_HV_SYNC_POL_HPVN,
    HDMI_HV_SYNC_POL_HNVP,
    HDMI_HV_SYNC_POL_HNVN,
    HDMI_HV_SYNC_POL_BUTT
} HDMI_HVSYNC_POLARITY_E;

typedef enum
{
    HDMI_PICTURE_NON_UNIFORM__SCALING,
    HDMI_PICTURE_SCALING__H,
    HDMI_PICTURE_SCALING__V,
    HDMI_PICTURE_SCALING__HV
}HDMI_PICTURE_SCALING_E;


typedef struct
{
    HI_U32                      u32ClkFs;                   /* VDP setting(in)*/
    HI_U32                      u32HdmiAdaptPixClk;         /* HDMI adapt setting(out)*/
    HI_U32                      u32PixelRepeat;
    HI_BOOL                     bVSyncPol;
    HI_BOOL                     bHSyncPol;
    HI_BOOL                     bDEPol;
    HDMI_VIDEO_TIMING_E         enVideoTiming;
    HDMI_3D_MODE_E              enStereoMode;
    HDMI_COLORSPACE_E           enInColorSpace;
    HDMI_COLORIMETRY_E          enColorimetry;
    HDMI_EXTENDED_COLORIMETRY   enExtendedColorimetry;
    HDMI_QUANTIZATION_RANGE     enRGBQuantization;
    HDMI_YCC_QUANTIZATION_RANGE enYCCQuantization;
    HDMI_PICTURE_ASPECT         enPictureAspect;
    HDMI_ACTIVE_ASPECT          enActiveAspect;
    HDMI_PICTURE_SCALING_E      enPictureScaling;
    HDMI_VIDEO_BITDEPTH_E       enInBitDepth;
    HI_U32                      u32DispFmt;

}HDMI_VO_ATTR_S;

/*********************audio data Structure*******************************************/
typedef enum
{
    HDMI_AUDIO_FORMAT_2CH = 0x02,
    HDMI_AUDIO_FORMAT_3CH,
    HDMI_AUDIO_FORMAT_4CH,
    HDMI_AUDIO_FORMAT_5CH,
    HDMI_AUDIO_FORMAT_6CH,
    HDMI_AUDIO_FORMAT_7CH,
    HDMI_AUDIO_FORMAT_8CH,
    HDMI_AUDIO_FORMAT_BUTT
} HDMI_AUDIO_CH_E;

/*hdmi audio interface */
typedef enum
{
    HDMI_AUDIO_INTERFACE__I2S,
    HDMI_AUDIO_INTERFACE__SPDIF,
    HDMI_AUDIO_INTERFACE__HBRA,
    HDMI_AUDIO_INTERFACE__BUTT
}HDMI_AUDIO_INTERFACE_E;

typedef enum
{
    HDMI_AUDIO_BIT_DEPTH_UNKNOWN =0,
    HDMI_AUDIO_BIT_DEPTH_8  = 8,
    HDMI_AUDIO_BIT_DEPTH_16 = 16,
    HDMI_AUDIO_BIT_DEPTH_18 = 18,
    HDMI_AUDIO_BIT_DEPTH_20 = 20,
    HDMI_AUDIO_BIT_DEPTH_24 = 24,
    HDMI_AUDIO_BIT_DEPTH_32 = 32,
    HDMI_AUDIO_BIT_DEPTH_BUTT
}HDMI_AUDIO_BIT_DEPTH_E;


typedef enum
{
    HDMI_SAMPLE_RATE_UNKNOWN=0,
    HDMI_SAMPLE_RATE_8K    = 8000,
    HDMI_SAMPLE_RATE_11K   = 11025,
    HDMI_SAMPLE_RATE_12K   = 12000,
    HDMI_SAMPLE_RATE_16K   = 16000,
    HDMI_SAMPLE_RATE_22K   = 22050,
    HDMI_SAMPLE_RATE_24K   = 24000,
    HDMI_SAMPLE_RATE_32K   = 32000,
    HDMI_SAMPLE_RATE_44K   = 44100,
    HDMI_SAMPLE_RATE_48K   = 48000,
    HDMI_SAMPLE_RATE_88K   = 88200,
    HDMI_SAMPLE_RATE_96K   = 96000,
    HDMI_SAMPLE_RATE_176K  = 176400,
    HDMI_SAMPLE_RATE_192K  = 192000,
    HDMI_SAMPLE_RATE_768K  = 768000,
    HDMI_SAMPLE_RATE_BUTT
}HDMI_SAMPLE_RATE_E;


typedef struct
{
    HI_BOOL                  bDownSample;
    HDMI_SAMPLE_RATE_E       enSampleFs;
    HDMI_AUDIO_CH_E          enChanels;
    HDMI_AUDIO_INTERFACE_E   enSoundIntf;
    HDMI_AUDIO_BIT_DEPTH_E   enSampleDepth;
    HDMI_AUDIO_FORMAT_CODE_E enAudioCode;
}HDMI_AO_ATTR_S;


/*********************APP data Structure*******************************************/
typedef enum
{
    HDMI_TMDS_MODE_NONE,
    HDMI_TMDS_MODE_DVI,
    HDMI_TMDS_MODE_HDMI_1_4,
    HDMI_TMDS_MODE_HDMI_2_0,
    HDMI_TMDS_MODE_AUTO,
    HDMI_TMDS_MODE_HDMI_2_1,
    HDMI_TMDS_MODE_BUTT
}HDMI_TMDS_MODE_E;

typedef enum
{
    HDMI_HDCP_MODE_AUTO,
    HDMI_HDCP_MODE_1_4,
    HDMI_HDCP_MODE_2_2,
    HDMI_HDCP_MODE_BUTT
}HDMI_HDCP_MODE_E;

typedef enum
{
    HDMI_DEFAULT_ACTION_NULL,
    HDMI_DEFAULT_ACTION_HDMI,
    HDMI_DEFAULT_ACTION_DVI,
    HDMI_DEFAULT_ACTION_BUTT
}HDMI_DEFAULT_ACTION_E;


typedef enum
{
    HDMI_VIDEO_DITHER_12_10	    = 0x00,
    HDMI_VIDEO_DITHER_12_8	    = 0x01,
    HDMI_VIDEO_DITHER_10_8	    = 0x02,
    HDMI_VIDEO_DITHER_DISALBE	= 0x03,
} HDMI_VIDEO_DITHER_E;


/*In order to extern ,so we define struct*/
typedef struct hiHDMI_APP_ATTR_S
{
    HI_BOOL                 bEnableHdmi;
    HI_BOOL                 bEnableVideo;
    HI_BOOL                 bEnableAudio;

    HDMI_COLORSPACE_E       enOutColorSpace;
    HDMI_QUANTIZATION_RANGE enOutCscQuantization;
    HDMI_DEEP_COLOR_E       enDeepColorMode;
    HI_BOOL                 bxvYCCMode;

    HI_BOOL                 bEnableAviInfoFrame;
    HI_BOOL                 bEnableSpdInfoFrame;
    HI_BOOL                 bEnableMpegInfoFrame;
    HI_BOOL                 bEnableAudInfoFrame;

    HI_U32                  bDebugFlag;
    HI_BOOL                 bHDCPEnable;
    HDMI_DEFAULT_ACTION_E   enHdmiAction;

    HI_BOOL                 bEnableClrSpaceAdapt;
    HI_BOOL                 bEnableDeepClrAdapt;
    HI_BOOL                 bAuthMode;

    HI_BOOL                 bEnableDRMInfoFrame;
    HDMI_HDCP_MODE_E        enHDCPMode;
}HDMI_APP_ATTR_S;

/***********************************HDR****************************************************/
typedef enum hdmi_hdr_colorimetry
{
    HDMI_HDR_COLORIMETRY_NONE,
    HDMI_HDR_COLORIMETRY_ITU_601,
    HDMI_HDR_COLORIMETRY_ITU_709,
    HDMI_HDR_COLORIMETRY_EXTENDED,
    HDMI_HDR_EXTENDED_COLORIMETRY_XV_YCC_601,
    HDMI_HDR_EXTENDED_COLORIMETRY_XV_YCC_709,
    HDMI_HDR_EXTENDED_COLORIMETRY_S_YCC_601,
    HDMI_HDR_EXTENDED_COLORIMETRY_ADOBE_YCC_601,
    HDMI_HDR_EXTENDED_COLORIMETRY_ADOBE_RGB,
    HDMI_HDR_EXTENDED_COLORIMETRY_2020_const_luminous,      /* BT2020 cYCC */
    HDMI_HDR_EXTENDED_COLORIMETRY_2020_non_const_luminous,
}HDMI_HDR_COLORIMETRY;

/* HDR mode */
typedef enum
{
    HDMI_HDR_MODE_DISABLE,           /* HDR & Dolby mode disable */
    HDMI_HDR_MODE_DOLBY_NORMAL,      /* Dolby normal(YCbCr422-12bit) mode enable */
    HDMI_HDR_MODE_DOLBY_TUNNELING,   /* Dolby tunneling(RGB-8bit) mode enable*/
    HDMI_HDR_MODE_CEA_861_3,         /* HDR standar mode enable(according to <CEA-861-3.2015>) */
    HDMI_HDR_MODE_CEA_861_3_AUTHEN,  /* HDR authen mode */
    HDMI_HDR_MODE_BUTT,

}HDMI_HDR_MODE_E;


typedef enum
{
    HDMI_HDR_USERMODE_SDR,
    HDMI_HDR_USERMODE_HDR10,
    HDMI_HDR_USERMODE_DOLBY,
    HDMI_HDR_USERMODE_BUTT,

}HDMI_HDR_USERMODE_E;


/* HDR attribute */
typedef struct
{
    HDMI_HDR_MODE_E              enHdrMode;          /* HDR mode */
    HDMI_HDR_USERMODE_E          enUserHdrMode;      /* User HDR mode */
    HDMI_EOTF_TYPE_E             enEotfType;         /* EOTF type.  When enHdrMode==HI_UNF_HDMI_HDR_MODE_CEA_861_3 valid */
    HDMI_STATIC_META_TYPE_ID_E   enMetadataId;       /* Metadata Descriptor type(ID).  When enHdrMode==HI_UNF_HDMI_HDR_MODE_CEA_861_3 valid*/
    HDMI_META_DESCRIPTOR_UN      unDescriptor;       /* Static Metadata Descriptor Type.  When enHdrMode==HI_UNF_HDMI_HDR_MODE_CEA_861_3 valid */
    HDMI_HDR_COLORIMETRY         enColorimetry;      /* Colorimetry.  When enHdrMode==HI_UNF_HDMI_HDR_MODE_CEA_861_3 valid  */

}HDMI_HDR_ATTR_S;

/***************************************************************************************/

typedef struct
{
    HDMI_AO_ATTR_S  stAOAttr;
    HDMI_VO_ATTR_S  stVOAttr;
    HDMI_APP_ATTR_S stAppAttr;
#ifdef HDMI_HDR_SUPPORT
    HDMI_HDR_ATTR_S stHdrAttr;
#endif
}HDMI_ATTR_S;


/***************************CEC data Structure *******************************************/
typedef enum
{
    HDMI_CEC_LOGICALADD_TV               = 0X00,
    HDMI_CEC_LOGICALADD_RECORDDEV_1      = 0X01,
    HDMI_CEC_LOGICALADD_RECORDDEV_2      = 0X02,
    HDMI_CEC_LOGICALADD_TUNER_1          = 0X03,
    HDMI_CEC_LOGICALADD_PLAYDEV_1        = 0X04,
    HDMI_CEC_LOGICALADD_AUDIOSYSTEM      = 0X05,
    HDMI_CEC_LOGICALADD_TUNER_2          = 0X06,
    HDMI_CEC_LOGICALADD_TUNER_3          = 0X07,
    HDMI_CEC_LOGICALADD_PLAYDEV_2        = 0X08,
    HDMI_CEC_LOGICALADD_RECORDDEV_3      = 0X09,
    HDMI_CEC_LOGICALADD_TUNER_4          = 0X0A,
    HDMI_CEC_LOGICALADD_PLAYDEV_3        = 0X0B,
    HDMI_CEC_LOGICALADD_RESERVED_1       = 0X0C,
    HDMI_CEC_LOGICALADD_RESERVED_2       = 0X0D,
    HDMI_CEC_LOGICALADD_SPECIALUSE       = 0X0E,
    HDMI_CEC_LOGICALADD_BROADCAST        = 0X0F,
    HDMI_CEC_LOGICALADD_BUTT
}HDMI_CEC_LOGICALADD_S;

typedef enum
{
    HDMI_CEC_UICMD_SELECT                      = 0x00,
    HDMI_CEC_UICMD_UP                          = 0x01,
    HDMI_CEC_UICMD_DOWN                        = 0x02,
    HDMI_CEC_UICMD_LEFT                        = 0x03,
    HDMI_CEC_UICMD_RIGHT                       = 0x04,
    HDMI_CEC_UICMD_RIGHT_UP                    = 0x05,
    HDMI_CEC_UICMD_RIGHT_DOWN                  = 0x06,
    HDMI_CEC_UICMD_LEFT_UP                     = 0x07,
    HDMI_CEC_UICMD_LEFT_DOWN                   = 0x08,
    HDMI_CEC_UICMD_ROOT_MENU                   = 0x09,
    HDMI_CEC_UICMD_SETUP_MENU                  = 0x0A,
    HDMI_CEC_UICMD_CONTENTS_MENU               = 0x0B,
    HDMI_CEC_UICMD_FAVORITE_MENU               = 0x0C,
    HDMI_CEC_UICMD_EXIT                        = 0x0D,
    HDMI_CEC_UICMD_NUM_0                       = 0x20,
    HDMI_CEC_UICMD_NUM_1                       = 0x21,
    HDMI_CEC_UICMD_NUM_2                       = 0x22,
    HDMI_CEC_UICMD_NUM_3                       = 0x23,
    HDMI_CEC_UICMD_NUM_4                       = 0x24,
    HDMI_CEC_UICMD_NUM_5                       = 0x25,
    HDMI_CEC_UICMD_NUM_6                       = 0x26,
    HDMI_CEC_UICMD_NUM_7                       = 0x27,
    HDMI_CEC_UICMD_NUM_8                       = 0x28,
    HDMI_CEC_UICMD_NUM_9                       = 0x29,
    HDMI_CEC_UICMD_DOT                         = 0x2A,
    HDMI_CEC_UICMD_ENTER                       = 0x2B,
    HDMI_CEC_UICMD_CLEAR                       = 0x2C,
    HDMI_CEC_UICMD_NEXT_FAVORITE               = 0x2F,
    HDMI_CEC_UICMD_CHANNEL_UP                  = 0x30,
    HDMI_CEC_UICMD_CHANNEL_DOWN                = 0x31,
    HDMI_CEC_UICMD_PREVIOUS_CHANNEL            = 0x32,
    HDMI_CEC_UICMD_SOUND_SELECT                = 0x33,
    HDMI_CEC_UICMD_INPUT_SELECT                = 0x34,
    HDMI_CEC_UICMD_DISPLAY_INFORMATION         = 0x35,
    HDMI_CEC_UICMD_HELP                        = 0x36,
    HDMI_CEC_UICMD_PAGE_UP                     = 0x37,
    HDMI_CEC_UICMD_PAGE_DOWN                   = 0x38,
    HDMI_CEC_UICMD_POWER                       = 0x40,
    HDMI_CEC_UICMD_VOLUME_UP                   = 0x41,
    HDMI_CEC_UICMD_VOLUME_DOWN                 = 0x42,
    HDMI_CEC_UICMD_MUTE                        = 0x43,
    HDMI_CEC_UICMD_PLAY                        = 0x44,
    HDMI_CEC_UICMD_STOP                        = 0x45,
    HDMI_CEC_UICMD_PAUSE                       = 0x46,
    HDMI_CEC_UICMD_RECORD                      = 0x47,
    HDMI_CEC_UICMD_REWIND                      = 0x48,
    HDMI_CEC_UICMD_FAST_FORWARD                = 0x49,
    HDMI_CEC_UICMD_EJECT                       = 0x4A,
    HDMI_CEC_UICMD_FORWARD                     = 0x4B,
    HDMI_CEC_UICMD_BACKWARD                    = 0x4C,
    HDMI_CEC_UICMD_STOP_RECORD                 = 0x4D,
    HDMI_CEC_UICMD_PAUSE_RECORD                = 0x4E,
    HDMI_CEC_UICMD_ANGLE                       = 0x50,
    HDMI_CEC_UICMD_SUBPICTURE                  = 0x51,
    HDMI_CEC_UICMD_VIDEO_ON_DEMAND             = 0x52,
    HDMI_CEC_UICMD_ELECTRONIC_PROGRAM_GUIDE    = 0x53,
    HDMI_CEC_UICMD_TIMER_PROGRAMMING           = 0x54,
    HDMI_CEC_UICMD_INITIAL_CONFIGURATION       = 0x55,
    HDMI_CEC_UICMD_PLAY_FUNCTION               = 0x60,
    HDMI_CEC_UICMD_PAUSE_PLAY_FUNCTION         = 0x61,
    HDMI_CEC_UICMD_RECORD_FUNCTION             = 0x62,
    HDMI_CEC_UICMD_PAUSE_RECORD_FUNCTION       = 0x63,
    HDMI_CEC_UICMD_STOP_FUNCTION               = 0x64,
    HDMI_CEC_UICMD_MUTE_FUNCTION               = 0x65,
    HDMI_CEC_UICMD_RESTORE_VOLUME_FUNCTION     = 0x66,
    HDMI_CEC_UICMD_TUNE_FUNCTION               = 0x67,
    HDMI_CEC_UICMD_SELECT_MEDIA_FUNCTION       = 0x68,
    HDMI_CEC_UICMD_SELECT_AV_INPUT_FUNCTION    = 0x69,
    HDMI_CEC_UICMD_SELECT_AUDIO_INPUT_FUNCTION = 0x6A,
    HDMI_CEC_UICMD_POWER_TOGGLE_FUNCTION       = 0x6B,
    HDMI_CEC_UICMD_POWER_OFF_FUNCTION          = 0x6C,
    HDMI_CEC_UICMD_POWER_ON_FUNCTION           = 0x6D,
    HDMI_CEC_UICMD_F1_BLUE                     = 0x71,
    HDMI_CEC_UICMD_F2_RED                      = 0x72,
    HDMI_CEC_UICMD_F3_GREEN                    = 0x73,
    HDMI_CEC_UICMD_F4_YELLOW                   = 0x74,
    HDMI_CEC_UICMD_F5                          = 0x75,
    HDMI_CEC_UICMD_DATA                        = 0x76,
    HDMI_CEC_UICMD_REPORT_PHYADDR              = 0x84
}HDMI_CEC_UICMD_E;


typedef struct
{
    HI_U8                              u8Length;
    HI_U8                              u8Data[15];
}HDMI_CEC_RAWDATA_S;

typedef struct
{
    HDMI_CEC_LOGICALADD_S  enSrcAdd;
    HDMI_CEC_LOGICALADD_S  enDstAdd;
    HI_U8                  u8Opcode;
    HDMI_CEC_RAWDATA_S     stRawData;
}HDMI_CEC_CMD_S;


typedef struct
{
    HI_BOOL                 bCecEnable;
    HI_U8                   au8PhysicalAddr[4];
    HI_U32                  u32RecieveCnt;      /* recieve message count */
    HI_BOOL                 bNetValid;          /* u8LogicalAddr & au8Network valid flag  */
    HI_U8                   u8LogicalAddr;
    HI_U8                   au8Network[HDMI_CEC_LOGICALADD_BUTT];
}HDMI_CEC_INFO_S;

typedef enum
{
    HDMI_TRANSITION_NONE        = 0x0,
    HDMI_TRANSITION_BOOT_MCE    = 0x1,
    HDMI_TRANSITION_MCE_APP     = 0x2,
    HDMI_TRANSITION_BOOT_APP    = 0x4,
}HDMI_TRANSITION_STATE_E;

typedef enum
{
    HDMI_RUN_STATE_NONE 	= 0x00,
    HDMI_RUN_STATE_INIT 	= 0x01,
    HDMI_RUN_STATE_OPEN 	= 0x02,
    HDMI_RUN_STATE_START 	= 0x04,
    HDMI_RUN_STATE_STOP 	= 0x08,
    HDMI_RUN_STATE_CLOSE 	= 0x10,
    HDMI_RUN_STATE_DEINIT 	= 0x20,
}HDMI_RUN_STATE_E;

typedef struct
{
    HI_U16      length;
    HI_U8*      pList;
    HI_U8*      pListStart;
}HDMI_HDCP_KSVLIST_S;

typedef enum hdmi_hdcp_support
{
    HDMI_HDCP_SINK_UNKNOWN,
    HDMI_HDCP_SINK_SUPPORT,
    HDMI_HDCP_SINK_NOSUPPORT,
}HDMI_HDCP_SUPPORT_E;

typedef struct
{
    HI_BOOL                 bHdcpIsOn;
    HI_BOOL                 bHdcpWasOn;
    HI_BOOL                 bHdcp1Prep;
    HI_BOOL                 bHdcp2Prep;
    HI_BOOL                 bHdcpAuthSuc;
    HDMI_HDCP_SUPPORT_E     eHdcp14Support;
    HDMI_HDCP_SUPPORT_E     eHdcp22Support;
    HDMI_HDCP_MODE_E        enHdcpMode;
}HDMI_HDCP_INFO_S;

typedef enum
{
    HDMI_TX_SUPPORT_HDMI1_4    = 0x1,
    HDMI_TX_SUPPORT_HDMI2_0    = 0x2,
    HDMI_TX_SUPPORT_HDCP1_4    = 0x4,
    HDMI_TX_SUPPORT_HDCP2_2    = 0x8,
    HDMI_TX_SUPPORT_YUV420     = 0x10,
    HDMI_TX_SUPPORT_YUV420_422 = 0x20,
    HDMI_TX_SUPPORT_YUV422_444 = 0x40,
    HDMI_TX_SUPPORT_YUV444_422 = 0x80,
    HDMI_TX_SUPPORT_YUV422_420 = 0x100,
    HDMI_TX_SUPPORT_YUV2RGB    = 0x200,
    HDMI_TX_SUPPORT_RGB2YUV    = 0x400,
    HDMI_TX_SUPPORT_SCRAMBLE   = 0x800,
}HDMI_TX_CAPABILITY_E;

typedef struct
{
    HI_BOOL     bTxHdmi_14;
    HI_BOOL     bTxHdmi_20;

    HI_BOOL     bTxHdmi_21;

    HI_BOOL     bTxHdcp_14;
    HI_BOOL     bTxHdcp_22;

    HI_BOOL     bTxRGB444;
    HI_BOOL     bTxYCBCR444;
    HI_BOOL     bTxYCBCR422;
    HI_BOOL     bTxYCBCR420;

    HI_BOOL     bTxDeepClr10Bit;
    HI_BOOL     bTxDeepClr12Bit;
    HI_BOOL     bTxDeepClr16Bit;

    HI_BOOL     bTxRGB_YCbCR444;
    HI_BOOL     bTxYCBCR444_422;
    HI_BOOL     bTxYCBCR422_420;

    HI_BOOL     bTxYCBCR420_422;
    HI_BOOL     bTxYCBCR422_444;
    HI_BOOL     bTxYCBCR444_RGB;

    HI_BOOL     bTxScdc;
    HI_U32      u32TxMaxTmdsClk; /*in MHz*/

}HDMI_TX_CAPABILITY_S;

typedef enum
{
    HDMI_CONV_STD_BT_709,
    HDMI_CONV_STD_BT_601,
    HDMI_CONV_STD_BT_2020_non_const_luminous,
    HDMI_CONV_STD_BT_2020_const_luminous,
    HDMI_CONV_STD_BUTT
}HDMI_CONVERSION_STD_E;

typedef struct
{
    HDMI_VIDEO_TIMING_E     enTimming;
    HI_U32                  u32PixelClk;
    HI_U32                  u32TmdsClk;
    HI_BOOL                 bVSyncPol;
    HI_BOOL                 bHSyncPol;
    HI_BOOL                 bDEPol;
    HDMI_CONVERSION_STD_E   enConvStd;
    HDMI_QUANTIZATION_RANGE enQuantization;
    HDMI_COLORSPACE_E       enInColorSpace;
    HDMI_COLORSPACE_E       enOutColorSpace;
    HDMI_DEEP_COLOR_E       enDeepColor;
    HDMI_VIDEO_BITDEPTH_E   enInBitDepth;
    HDMI_QUANTIZATION_RANGE eOutCscQuantization;
    HI_BOOL                 bEmiEnable;
}HDMI_VIDEO_CONFIG_S;

typedef struct
{
    HI_BOOL                  bEnableAudio;
    HI_BOOL                  bDownSample;
    HI_U32                   u32TmdsClk;
    HI_U32                   u32PixelRepeat;
    HDMI_SAMPLE_RATE_E       enSampleFs;
    HDMI_AUDIO_CH_E          enLayout;
    HDMI_AUDIO_INTERFACE_E   enSoundIntf;
    HDMI_AUDIO_BIT_DEPTH_E   enSampleDepth;
}HDMI_AUDIO_CONFIG_S;

typedef struct
{
    HI_U8              u8DataSwing;      //data-swing
    HI_U8              u8CLKSwing;       //CLK-swing
    HI_U8              u8SrcTermination; //source termination
    HI_U8              u8TxVnbValue;     //Tx driver vnb value setting
    HI_U8              u8AdjustClk;      //Fine adjust clock source termination
    HI_U8              u8TxRegZone;      //tx_reg_zone
}HDMI_PHY_CONFIG_S;

typedef struct
{
    HI_BOOL                 bPhyOe;
    HI_BOOL                 bPhyPowerOn;
    HDMI_VIDEO_BITDEPTH_E   enDeepColor;
    HDMI_PHY_CONFIG_S       stPhyConfig;
}HDMI_PHY_STATUS_S;

typedef struct
{
    HI_BOOL                     bVideoMute;
    HI_BOOL                     bYCbCr2RGB;
    HI_BOOL                     bRGB2YCbCr;
    HI_BOOL                     bYCbCr444_422;
    HI_BOOL                     bYCbCr422_420;
    HI_BOOL                     bYCbCr420_422;
    HI_BOOL                     bYCbCr422_444;
    HI_BOOL                     bIn420Ydemux;
    HI_BOOL                     bOut420Ydemux;
    HDMI_VIDEO_DITHER_E         enDither;
    HI_BOOL                     bVSyncPol;
    HI_BOOL                     bHSyncPol;
    HI_BOOL                     bCSyncPol;
    HI_BOOL                     bDEPol;
    HI_BOOL                     bSwapHsCs;
    HDMI_COLORSPACE_E           enInColorSpace;
    HDMI_COLORSPACE_E           enOutColorSpace;
    HDMI_VIDEO_BITDEPTH_E       enOutBitDepth;
    HDMI_HVSYNC_POLARITY_E      enHvSyncPol;
    HDMI_QUANTIZATION_RANGE     enOutCscQuantization;
#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    /* detect timming */
    HI_BOOL                     bSyncSwEnable;
    HI_BOOL                     bVsyncPolarity;     /* when bSyncSwEnable==0,indicates hw;or ,indicates sw */
    HI_BOOL                     bHsyncPolarity;     /* when bSyncSwEnable==0,indicates hw;or ,indicates sw */
    HI_BOOL                     bProgressive;
    HI_U32                      u32HsyncTotal;
    HI_U32                      u32HactiveCnt;
    HI_U32                      u32VsyncTotal;
    HI_U32                      u32VactiveCnt;
#endif
}HDMI_VIDEO_STATUS_S;

typedef struct hiHDMI_HDCP_CAPABILITY_S
{
    HI_BOOL                     bHdcp14Support;
    HI_BOOL                     bHdcp22Support;
}HDMI_HDCP_CAPABILITY_S;

typedef struct
{
    HI_BOOL                  bAudioMute;
    HI_BOOL                  bAudioEnable;
    HI_BOOL                  bDownSample;
    HDMI_SAMPLE_RATE_E       enSampleFs;
    HDMI_AUDIO_CH_E          enLayout;
    HDMI_AUDIO_INTERFACE_E   enSoundIntf;
    HDMI_AUDIO_BIT_DEPTH_E   enSampleDepth;
    HI_U32                   u32RefNvalue;
    HI_U32                   u32RegNvalue;
    HI_U32                   u32RefCtsvalue;
    HI_U32                   u32RegCtsvalue;
}HDMI_AUDIO_STATUS_S;

typedef struct
{
    HI_BOOL                     bHotPlug;
    HI_BOOL                     bRsen;
    HI_BOOL                     bAvMute;
    HDMI_TMDS_MODE_E            enTmdsMode;
}HDMI_COMMON_STATUS_S;

typedef struct
{
    HI_BOOL                     bSourceScrambleOn;
    HI_BOOL                     bSinkScrambleOn;
    HI_U8                       u8TmdsBitClkRatio;

#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    HI_BOOL                     bSinkReadQuest;
    HI_U32                      u32ScrambleTimeout;         /* in unit of ms.for [0,200],force to default 200;or,set the value cfg(>200). */
    HI_U32                      u32ScrambleInterval;        /* in unit of ms,range[20,200).for [0,20] or >=200,force to default 20;or,set the value cfg[20,200). */
#endif

}HDMI_SCDC_STATUS_S;


#define HDMI_INFO_FRAME_MAX_SIZE			31

typedef struct
{
    HI_BOOL        bAVIEnable;
    HI_BOOL        bAUDIOEnable;
    HI_BOOL        bVSIFEnable;
    HI_BOOL        bSPDEnable;
    HI_BOOL        bMPEGEnable;
    HI_BOOL        bGBDEnable;
    HI_U8          u8AVI[HDMI_INFO_FRAME_MAX_SIZE];
    HI_U8          u8AUDIO[HDMI_INFO_FRAME_MAX_SIZE];
    HI_U8          u8VSIF[HDMI_INFO_FRAME_MAX_SIZE];
    HI_U8          u8SPD[HDMI_INFO_FRAME_MAX_SIZE];
    HI_U8          u8MPEG[HDMI_INFO_FRAME_MAX_SIZE];
    HI_U8          u8GDB[HDMI_INFO_FRAME_MAX_SIZE];
    HI_BOOL        bDRMEnable;
    HI_U8          u8DRM[HDMI_INFO_FRAME_MAX_SIZE];
}HDMI_INFOFRAME_STATUS_S;

typedef struct
{
    HI_BOOL        bHdcp2_2Enable;
    HI_BOOL        bHdcp1_4Enable;
    HI_BOOL        bRepeaterOn;
    HI_U8          u8BKSVs[5];
    HI_U8          u8AKSVs[5];
    HI_U8          hdcpStatus;
}HDMI_HDCP_STATUS_S;

typedef enum
{
    FRL_WORK_MODE_NONE,
    FRL_WORK_MODE_3L3G,
    FRL_WORK_MODE_3L6G,
    FRL_WORK_MODE_4L6G,
    FRL_WORK_MODE_4L8G,
    FRL_WORK_MODE_4L10G,
    FRL_WORK_MODE_4L12G,
    FRL_WORK_MODE_BUTT,
}FRL_WORK_MODE_E;

typedef struct
{
    HI_BOOL             bFrlStart;
    HI_BOOL             bWorkEn;
    FRL_WORK_MODE_E     enWorkMode;
}HDMI_FRL_STATUS_S;

typedef enum
{
    FRL_TXFFE_MODE_0,
    FRL_TXFFE_MODE_1,
    FRL_TXFFE_MODE_2,
    FRL_TXFFE_MODE_3,
    FRL_TXFFE_MODE_BUTT,
}FRL_TXFFE_MODE_E;

typedef struct
{
    HDMI_COMMON_STATUS_S        stCommonStatus;
    HDMI_PHY_STATUS_S           stPhyStatus;
    HDMI_VIDEO_STATUS_S         stVideoStatus;
    HDMI_AUDIO_STATUS_S         stAudioStatus;
    HDMI_INFOFRAME_STATUS_S     stInfoFrameStatus;
    HDMI_HDCP_STATUS_S          stHdcpStatus;
#ifdef HDMI_FRL_SUPPORT
    HDMI_FRL_STATUS_S           stFrlStatus;
#endif
}HDMI_HARDWARE_STATUS_S;

typedef struct
{
    HI_U32    u32MaxTmdsCharacterRate;
    HI_BOOL   bScdcPresent;
    HI_BOOL   bRRCapable;
    HI_BOOL   bLTE340McscScramble;
    HI_BOOL   b3DOsdDisparity;
    HI_BOOL   bDualView;
    HI_BOOL   bIndependentView;
    HI_BOOL   bDc30bit420;
    HI_BOOL   bDc36bit420;
    HI_BOOL   bDc48bit420;
    HI_BOOL   bScdcEnable;
} HDMI_SCDC_CONFIG_S;

/**HDMI Delay struct*/
typedef struct
{
    HI_U32  u32MuteDelay;           /**<delay for avmute */
    HI_U32  u32FmtDelay;            /**<delay for setformat */
    HI_BOOL bForceFmtDelay;         /**<force setformat delay mode */
    HI_BOOL bForceMuteDelay;        /**<force avmute delay mode */
}HDMI_DELAY_S;

typedef enum
{
    HDMI_VIDEO_UNKNOWN,
    HDMI_VIDEO_PROGRESSIVE,
    HDMI_VIDEO_INTERLACE,
    HDMI_VIDEO_BUTT
}HDMI_VIDEO_P_I_TYPE_E;

typedef struct
{
    HDMI_VIDEO_CODE_E           enVideoCode;
    HI_U32                      u32Pixclk;
    HI_U32                      u32Rate;
    HI_U32                      u32Hactive;
    HI_U32                      u32Vactive;
    HI_U32                      u32Hblank;
    HI_U32                      u32Vblank;
    HI_U32                      u32Hfront;
    HI_U32                      u32Hsync;
    HI_U32                      u32Hback;
    HI_U32                      u32Vfront;
    HI_U32                      u32Vsync;
    HI_U32                      u32Vback;
    HDMI_PICTURE_ASPECT         enAspectRatio;
    HDMI_VIDEO_TIMING_E         enTiming;
    HDMI_VIDEO_P_I_TYPE_E       enPIType;
    HI_CHAR                     *pcFmtStr;
}HDMI_VIDEO_DEF_S;

typedef struct
{
    HDMI_VSIF_VIC_E             enHdmiVic;
    HDMI_VIDEO_CODE_E           enEquivalentVideoCode;  // real vic
    HI_U32                      enPixclk;
    HI_U32                      enRate;
    HI_U32                      enHactive;
    HI_U32                      enVactive;
    HDMI_PICTURE_ASPECT         enAspectRatio;
    HDMI_VIDEO_TIMING_E         enTiming;
    HDMI_VIDEO_P_I_TYPE_E       enPIType;
    HI_CHAR                     *pcFmtStr;
}HDMI_VIDEO_4K_DEF_S;

typedef struct
{
    HI_U32                      u32AttachInTime;
    HI_U32                      u32AttachOutTime;
    HI_U32                      u32DeAttachInTime;
    HI_U32                      u32DeAttachOutTime;
    HI_U32                      u32PreformatInTime;
    HI_U32                      u32PreformatOutTime;
    HI_U32                      u32SetformatInTime;
    HI_U32                      u32SetformatOutTime;
    HI_U32                      u32SuspendInTime;
    HI_U32                      u32SuspendOutTime;
    HI_U32                      u32ResumeInTime;
    HI_U32                      u32ResumeOutTime;
}HDMI_INTF_STATUS_S;

typedef struct
{
    HI_BOOL bBlacEnable;
    HI_U8   inColorSpace;
    HI_U8   inBitDepth;
    HI_U8   inQuantization;
}HDMI_BLACK_FRAME_INFO_S;

typedef struct
{
    HI_U32                      u32StopDelay;
    HDMI_INTF_STATUS_S          stIntfStatus;
}HDMI_DEBUG_S;

typedef enum
{
    HDMI_TIMER_ZERO_DRMIF,
    HDMI_TIMER_SDR_TO_HDR10,
    HDMI_TIMER_TYPE_BUTT,
}HDMI_TIMER_TYPE_E;

typedef struct
{
    HDMI_TIMER_TYPE_E       enTimerType;
    HI_BOOL                 bTimerStart;
    HI_U32                  u32Time;
}HDMI_TIMER_CONFIG_S;

typedef enum
{
    HDMI_HDR_DEBUG_MODE_NONE,   /**< HDR mode change, SDR->HDR10 don't change anything */
    HDMI_HDR_DEBUG_MODE_OE,     /**< HDR mode change, SDR->HDR10 output disable and enable */
    HDMI_HDR_DEBUG_MODE_AVMUTE, /**< HDR mode change, SDR->HDR10 send avmute */
    HDMI_HDR_DEBUG_MODE_BUTT
}HDMI_HDR_DEBUG_MOD_E;

typedef struct
{
    HDMI_HDR_DEBUG_MOD_E    enHdrDebugMode;      /* HDR debug mode. To solve the problem of some TV can not switch smoothly from non-HDR10 to HDR10. */
    HDMI_TIMER_CONFIG_S     stZeroDrmIfTimer;    /* should send Zero DRM Infoframe when the HDR mode from HDR10 to non-HDR10. */
    HDMI_TIMER_CONFIG_S     stHdrModeChnTimer;   /* HDR debug timer. */
}HDMI_HDR_INFO_S;

typedef struct{
    HI_BOOL     bMutePkgEn;
    HI_BOOL     bMuteSet;
    HI_BOOL     bMuteClr;
    HI_BOOL     bMuteRptEn;
    HI_U32      u32RptCnt;
}HDMI_AVMUTE_CFG_S;

//FRL
typedef enum
{
    HDMI_FRL_SCDC_TYPE_SINK_VERSION,
    HDMI_FRL_SCDC_TYPE_SOURCE_VERSION,
    HDMI_FRL_SCDC_TYPE_UPDATE_FLAGS,
    HDMI_FRL_SCDC_TYPE_STATUS_FLAGS,
    HDMI_FRL_SCDC_TYPE_CONFIG,
    HDMI_FRL_SCDC_TYPE_TXFFE_REQ,
    HDMI_FRL_FLAGS_TYPE_BUTT,
}HDMI_FRL_SCDC_TYPE_E;

typedef enum
{
    HDMI_FRL_TRAIN_PATTERN_NONE = 0,
    HDMI_FRL_TRAIN_PATTERN_LP1,
    HDMI_FRL_TRAIN_PATTERN_LP2,
    HDMI_FRL_TRAIN_PATTERN_LP3,
    HDMI_FRL_TRAIN_PATTERN_LP4,
    HDMI_FRL_TRAIN_PATTERN_LP5,
    HDMI_FRL_TRAIN_PATTERN_LP6,
    HDMI_FRL_TRAIN_PATTERN_LP7,
    HDMI_FRL_TRAIN_PATTERN_LP8,
    HDMI_FRL_TRAIN_PATTERN_RESERVED,
    HDMI_FRL_TRAIN_PATTERN_0E = 0xE,
    HDMI_FRL_TRAIN_PATTERN_0F = 0xF,
    HDMI_FRL_TRAIN_PATTERN_BUTT,
}HDMI_FRL_TRAIN_PATTERN_E;

typedef enum
{
    HDMI_FRL_TRAIN_NONE, //
    HDMI_FRL_TRAIN_FAIL,
    HDMI_FRL_TRAIN_SUCCESS,
    HDMI_FRL_TRAIN_BUSY,
    HDMI_FRL_TRAIN_BUTT,
}HDMI_FRL_TRAIN_STATUS_E;

typedef enum
{
    HDMI_FRL_TRAIN_FAIL_NORMAL,
    HDMI_FRL_TRAIN_FAIL_FLTTIMEOUT,
    HDMI_FRL_TRAIN_FAIL_FLTSTEPTIMEOUT,
    HDMI_FRL_TRAIN_FAIL_RATECHANGE,
    HDMI_FRL_TRAIN_FAIL_FFECHANGE,
    HDMI_FRL_TRAIN_FAIL_BUTT,
}HDMI_FRL_TRAIN_FAIL_E;

typedef enum
{
    HDMI_FRL_TRAIN_SEL_SW,
    HDMI_FRL_TRAIN_SEL_HW,
    HDMI_FRL_TRAIN_SEL_BUTT,
}HDMI_FRL_TRAIN_SEL_E;

typedef struct
{
    HDMI_FRL_TRAIN_STATUS_E     enFrlTrainStatus;
    HDMI_FRL_TRAIN_PATTERN_E    enTrainPattern[HDMI_FRL_LANE_MAX_NUM];
    HDMI_FRL_TRAIN_FAIL_E       enTrainFailRes;
}HDMI_FRL_TRAIN_STATUS_S;

typedef struct
{
    HI_U32          u32FltWaitConfigMs;
    HI_U32          u32FltWaitResultMs;
    HI_U32          u32FltTimeOut;
    HI_U32          u32FltStepTimeOut;
    HI_U32          u32FltUpdateTimeOut;
}HDMI_FRL_TIMER_INFO_S;

typedef struct
{
    HI_BOOL                  bFrlNoTimeOut;
    HI_U8                    u8FrlRate;
    HI_U8                    u8FFELevels;
    HDMI_FRL_TIMER_INFO_S    stTimer;
    HDMI_FRL_TRAIN_SEL_E     enTrainSel;
}HDMI_FRL_TRAIN_CONFIG_S;

//SCDC
typedef enum
{
    SCDC_CMD_SET_SOURCE_VER,
    SCDC_CMD_GET_SOURCE_VER,
    SCDC_CMD_GET_SINK_VER,
    SCDC_CMD_SET_FLT_UPDATE,
    SCDC_CMD_GET_FLT_UPDATE,
    SCDC_CMD_SET_FLT_UPDATE_TRIM,
    SCDC_CMD_GET_FLT_UPDATE_TRIM,
    SCDC_CMD_SET_FLT_START,
    SCDC_CMD_GET_FLT_START,
    SCDC_CMD_SET_CONFIG1,
    SCDC_CMD_GET_CONFIG1,
    SCDC_CMD_GET_TEST_CONFIG,
    SCDC_CMD_GET_FLT_READY,
    SCDC_CMD_GET_LTP_REQ,
    SCDC_CMD_BUTT,
}SCDC_CMD_E;

typedef struct
{
    HI_U8	u8FrlRate;
    HI_U8   u8FfeLevels;
}SCDC_CONFIG1_S;

typedef struct
{
    HI_BOOL     bPreShootOnly;
    HI_BOOL     bDeEmphasisOnly;
    HI_BOOL     bNoFfe;
    HI_BOOL     bFltNoTimeout;
    HI_BOOL     bDscFrlMax;
    HI_BOOL     bFrlMax;
}SCDC_TEST_CONFIG_S;

typedef struct
{
    HI_U8  u8Ln0Ltp;
    HI_U8  u8Ln1Ltp;
    HI_U8  u8Ln2Ltp;
    HI_U8  u8Ln3Ltp;
}SCDC_LTP_REQ_S;

typedef enum
{
    HDMI_PHY_MODE_CFG_TMDS,
    HDMI_PHY_MODE_CFG_FRL,
    HDMI_PHY_MODE_CFG_TXFFE,
}HDMI_PHY_MODE_CFG_E;

typedef enum
{
    HDMI_TRACE_LEN_0,
    HDMI_TRACE_LEN_1,
	HDMI_TRACE_LEN_2,
    HDMI_TRACE_LEN_BUTT,
}HDMI_TRACE_LEN_E;

typedef struct
{
    HDMI_TRACE_LEN_E enTraceLen;
}HDMI_MOD_PARAM_S;

/* public struct */
typedef struct
{
    HI_U32              u32PixelClk;
    HI_U32              u32TmdsClk;     /* TMDS colck,in kHz */
    HI_BOOL             bEmiEnable;
    HDMI_DEEP_COLOR_E   enDeepColor;    /* Deep color(color depth)  */
    HDMI_PHY_MODE_CFG_E enModeCfg;      /* TMDS/FRL/TxFFE */
    HDMI_TRACE_LEN_E    enTraceLen;

#ifdef HDMI_FRL_SUPPORT
    HDMI_COLORSPACE_E   enColorSpace;
    FRL_WORK_MODE_E     enRate;         /* Lane and Rate */
    FRL_TXFFE_MODE_E    aenTxFFE[4];    /* TxFFE */
#endif
}HDMI_PHY_CFG_S;

#define CEAVideoCodesMax        43
#define VESAVideoCodesMax       31

extern HDMI_VIDEO_DEF_S s_stCEAVideoCodesDes[CEAVideoCodesMax];

#define CEA861FVideoCodesMax_4k    4
extern HDMI_VIDEO_4K_DEF_S s_stH14bHdmiVideoCodes_4K[CEA861FVideoCodesMax_4k];

HDMI_VIDEO_CODE_E DRV_HDMI_VicSearch(HDMI_VIDEO_TIMING_E enTimming, HDMI_PICTURE_ASPECT enAspect, HI_BOOL isAVIPackOr3DEnable);
HI_VOID HdmiRegWrite(volatile HI_VOID *pRegAddr, HI_U32 value);
HI_U32 HdmiRegRead(volatile HI_VOID *pRegAddr);
HI_VOID DRV_HDMI_MilliDelay(HI_U32 mSec);
HI_U32 DRV_HDMI_VicToIndex(HI_U32 u32Vic);
#ifdef HDMI_FRL_SUPPORT
HDMI_VIDEO_DEF_S *DRV_HDMI_CommFormatParamGet(HDMI_VIC_E enVic);
HDMI_VIDEO_DEF_S *DRV_HDMI_VESAFormatParamGet(HDMI_VIDEO_TIMING_E enTimming);
#endif

#endif //__DRV_HDMI_COMMON_H_
