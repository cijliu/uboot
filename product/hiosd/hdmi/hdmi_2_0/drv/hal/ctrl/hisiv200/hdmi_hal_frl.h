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
#ifndef __HDMI_HAL_FRL_H__
#define __HDMI_HAL_FRL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "drv_hdmi_common.h"
#include "hdmi_hal_frl.h"


#define FRL_LANE_MAX_NUM  4

/******************************************************************************/
/* Enum define                                                                 */
/******************************************************************************/
typedef enum
{
    FRL_TRAIN_NONE,
    FRL_TRAIN_FAIL,
    FRL_TRAIN_SUCCESS,
    FRL_TRAIN_BUSY,
    FRL_TRAIN_BUTT,
}FRL_TRAIN_STATUS_E;

typedef enum
{
    FRL_TRAIN_FAIL_RES_NORMAL,
    FRL_TRAIN_FAIL_RES_FLTTIMEOUT,
    FRL_TRAIN_FAIL_RES_FLTSTEPTIMEOUT,
    FRL_TRAIN_FAIL_RES_RATECHANGE,
    FRL_TRAIN_FAIL_RES_FFECHANGE,
    FRL_TRAIN_FAIL_RES_BUTT,
}FRL_TRAIN_FAIL_RES_E;

typedef enum
{
    FRL_TRAIN_FAIL_FSM_OTHER,
    FRL_TRAIN_FAIL_FSM_POLL,
    FRL_TRAIN_FAIL_FSM_STATUS,
    FRL_TRAIN_FAIL_FSM_PTN,
    FRL_TRAIN_FAIL_FSM_BUTT,
}FRL_TRAIN_FAIL_FSM_E;

typedef enum
{
    FRL_TRAIN_PATTERN_NONE = 0,
    FRL_TRAIN_PATTERN_LP1,
    FRL_TRAIN_PATTERN_LP2,
    FRL_TRAIN_PATTERN_LP3,
    FRL_TRAIN_PATTERN_LP4,
    FRL_TRAIN_PATTERN_LP5,
    FRL_TRAIN_PATTERN_LP6,
    FRL_TRAIN_PATTERN_LP7,
    FRL_TRAIN_PATTERN_LP8,
    FRL_TRAIN_PATTERN_RESERVED,
    FRL_TRAIN_PATTERN_0E = 0xE,
    FRL_TRAIN_PATTERN_0F = 0xF,
    FRL_TRAIN_PATTERN_BUTT,
}FRL_TRAIN_PATTERN_E;

typedef enum
{
    FRL_WORK_CHANNEL_NORMAL,
    FRL_WORK_CHANNEL_TRAIN,
    FRL_WORK_CHANNEL_BUTT,
}FRL_WORK_CHANNEL_E;

typedef enum
{
    FRL_WORK_LANE_NUM_3L,
    FRL_WORK_LANE_NUM_4L,
    FRL_WORK_LANE_NUM_BUTT,
}FRL_WORK_LANE_NUM_E;

typedef enum
{
    FRL_LANE_IDX_0,
    FRL_LANE_IDX_1,
    FRL_LANE_IDX_2,
    FRL_LANE_IDX_3,
    FRL_LANE_IDX_MAX
}FRL_LANE_IDX_E;
/******************************************************************************/
/* Data structure                                                             */
/******************************************************************************/
typedef struct
{
    HI_U32				   u32FltCounter;
    FRL_TRAIN_STATUS_E     enTrainStatus;
    FRL_WORK_MODE_E        enWorkMode;
    FRL_TRAIN_FAIL_RES_E   enFailRes;
    FRL_TRAIN_FAIL_FSM_E   enFailFsm;
}FRL_TRAIN_RESULT_S;

typedef struct
{
    HI_BOOL                 bStart;
    HI_U32				    u32FrlCurFsm;
    FRL_WORK_MODE_E         enTrainMode;
    FRL_TRAIN_PATTERN_E     enPattern[FRL_LANE_MAX_NUM];
    FRL_WORK_CHANNEL_E	    enWorkChannel;
    FRL_WORK_LANE_NUM_E     enWorkLaneNum;
}FRL_TRAIN_RUN_STATUS_S;

typedef struct
{
    FRL_TRAIN_RUN_STATUS_S  stRunStatus;
    FRL_TRAIN_RESULT_S      stResult;
}FRL_TRAIN_INFO_S;

typedef struct
{
    HI_U32         u32AvMaxLen;
    HI_U32         u32AvGapLen;
    HI_U32         u32BlankMaxLen;
    HI_U32         u32BlankGapLen;
    HI_U32         u32HblankCycles;
    HI_U32         u32HactiveTime;
    HI_U32         u32ExtraBlankMaxLen;
    HI_U32         u32ExtraBlankGapLen;
    HI_U32         u32Vactive;
    HI_U32         u32Vblank1Lines;
    HI_BOOL        bExtraNoGapFlags;
    HI_BOOL        bIsExtraMode;
    HI_BOOL        bSWDFM;
}FRL_DFM_S;

typedef struct
{
    HI_U32          u32FltWaitConfigMs;
    HI_U32          u32FltWaitResultMs;
    HI_U32          u32FltTimeOut;
    HI_U32          u32FltStepTimeOut;
    HI_U32          u32FltUpdateTimeOut;
}FRL_TIMER_INFO_S;

typedef struct
{
    HI_U32     u32Year;
    HI_U32     u32Month;
    HI_U32     u32Day;
}FRL_VERSION_INFO_S;

typedef struct
{
    HI_BOOL                  bFrlNoTimeout;
    HI_U8                    u8FrlRate;
    HI_U8                    u8FFELevels;
    FRL_TIMER_INFO_S         stTimer;
    HDMI_FRL_TRAIN_SEL_E     enTrainSel;
}FRL_CFG_S;

typedef struct
{
    HI_BOOL    bSrcEn;
    HI_U32     u32RfdInit;
    HI_U32     u32SrcInit0;
    HI_U32     u32SrcInit1;
}FRL_SRC_INFO_S;

typedef struct
{
    HI_BOOL              bWorkEn;
    HI_BOOL			     bLmLoad;
    FRL_VERSION_INFO_S	 stVersionInfo;
    FRL_TRAIN_INFO_S     stTrainInfo;
    FRL_TIMER_INFO_S     stTimerInfo;
}FRL_STATUS_S;

typedef struct
{
    HI_BOOL              bInit;
    HI_BOOL              bNoReset;
    HDMI_DEVICE_ID_E     enHdmiId;
    FRL_CFG_S            stCFG;
    FRL_STATUS_S         stStatus;
}FRL_INFO_S;

typedef struct
{
    HI_U8                u8Rate;
}FRL_DEBUG_S;


/******************************************************************************/
/* public interface                                                           */
/******************************************************************************/
HI_S32 HAL_HDMI_FrlInit(HDMI_DEVICE_ID_E enHdmi, HDMI_HAL_INIT_S *pstHalInit);

HI_VOID HAL_HDMI_FrlDeInit(HDMI_DEVICE_ID_E enHdmi);

HI_S32 HAL_HDMI_FrlGetStatus(HDMI_DEVICE_ID_E enHdmi, FRL_STATUS_S *pstStatus);

HI_S32 HAL_HDMI_FrlConfig(HDMI_DEVICE_ID_E enHdmi, FRL_CFG_S * pstCfg);

HI_S32 HAL_HDMI_FrlStartTraining(HDMI_DEVICE_ID_E enHdmi);

HI_S32 HAL_HDMI_FrlEnableWorkEn(HDMI_DEVICE_ID_E enHdmi, HI_BOOL bEnable);

HI_S32 HAL_HDMI_FrlDebug(FRL_DEBUG_S *pstDebug);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_HAL_FRL_H__ */




