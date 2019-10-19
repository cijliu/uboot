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


#ifndef __DRV_HDMI_FRL__
#define __DRV_HDMI_FRL__

#ifdef __cplusplus
extern "C" {
#endif

#include "hi_type.h"
#include "drv_hdmi_common.h"
#include "drv_hdmi_dfm.h"

#define MAX(a, b) (((a) < (b)) ?  (b) : (a))
#define MIN(a, b) (((a) > (b)) ?  (b) : (a))

typedef enum
{
    HDMI_FRL_TRAIN_STEP_READY_CHECK,    //LTS:2
    HDMI_FRL_TRAIN_STEP_TRAIN_START,    //LTS:3
    HDMI_FRL_TRAIN_STEP_RESULT_CHECK,   //LTS:3
    HDMI_FRL_TRAIN_STEP_RATE_CHANGE,    //LTS:4
    HDMI_FRL_TRAIN_STEP_RESULT_HANDLE,  //LTS:P
    HDMI_FRL_TRAIN_STEP_RETRAIN_CHECK,  //LTS:P
    HDMI_FRL_TRAIN_STEP_STOP,
    HDMI_FRL_TRAIN_STEP_BUTT,
}HDMI_FRL_TRAIN_STEP_E;

typedef enum
{
    HDMI_FRL_MODE_TMDS,
    HDMI_FRL_MODE_FRL,
    HDMI_FRL_MODE_BUTT,
}HDMI_FRL_MODE_E;

typedef enum
{
    HDMI_FRL_STRATEGY_MODE_1,
    HDMI_FRL_STRATEGY_MODE_2,
    HDMI_FRL_STRATEGY_MODE_3,
    HDMI_FRL_STRATEGY_MODE_BUTT,
}HDMI_FRL_STRATEGY_MODE_E;

typedef enum
{
    HDMI_FRL_RATE_SELECT_LITTLE,
    HDMI_FRL_RATE_SELECT_BIG,
    HDMI_FRL_RATE_SELECT_BUTT,
}HDMI_FRL_RATE_SELECT_E;

typedef struct
{
    HI_BOOL                    bStartMach;
    HDMI_FRL_TRAIN_STEP_E      enTrainStatus;
    HI_U64                     u64StartTime;
    HI_U64                     u32WaitReadyMs;
    HI_U64                     u32WaitHandleMs;
    HI_U64                     u32WaitRetrainMs;
}HDMI_FRL_STATE_MACH_INFO_S;

typedef struct
{
    HI_U8                     u8MaxRate;
    HI_U8                     u8MinRate;
    HI_U8                     u8CurRate;
}HDMI_FRL_RATE_INFO_S;

typedef struct
{
    HI_U8             u8Total;
    HI_BOOL           bSWDFM;
    DFM_OUT_S         stDFMOut[MAX_FRL_RATE];
}HDMI_FRL_DFM_S;

typedef struct
{
    HI_BOOL                    bStart;
    HI_BOOL                    bDscEnable;
    HI_BOOL                    bSupportFFE;
    HI_BOOL                    bScdcPresent;
    HI_BOOL                    bCTSMode;
    HI_BOOL                    bFrlReset;
    HI_BOOL                    bWorkEn;
    HI_U32                     u32TmdsClk;
    HDMI_FRL_MODE_E            enMode;
    HDMI_FRL_STRATEGY_MODE_E   enStrategyMode;
    HDMI_FRL_RATE_SELECT_E     enRateSelect;
    HDMI_FRL_STATE_MACH_INFO_S stStateMachInfo;
    HDMI_FRL_RATE_INFO_S       stRateInfo;
    HDMI_FRL_DFM_S             stDFM;
    HDMI_FRL_TRAIN_STATUS_S    stTrainStatus;
    HI_U32                     u32FailCount;
    HI_U32                     u32MaxFailTimes;
    HDMI_FRL_TRAIN_SEL_E       enTrainSel;
    FRL_TXFFE_MODE_E           aenCurTxFFE[4];
    HI_U32                     u32Bypass;
}HDMI_FRL_INFO_S;

typedef struct
{
    HDMI_FRL_MODE_E            enHdmiMode;
    HI_BOOL                    bSWDFM;
    FRL_WORK_MODE_E            enRate;
}HDMI_FRL_DEBUG_S;

typedef enum
{
    FRL_BYPASS_READY_CHECK  = 0x1,
    FRL_BYPASS_RESULT_CHECK = 0x2,
}HDMI_FRL_BYPASS_S;

HI_VOID DRV_HDMI_FrlMachInit(HDMI_DEVICE_ID_E enHdmiID);
HI_VOID DRV_HDMI_FrlEnable(HDMI_DEVICE_ID_E enHdmiID, HI_BOOL bEnable);
HI_S32 DRV_HDMI_FrlModeStrategy(HDMI_DEVICE_ID_E enHdmiID);
HI_VOID DRV_HDMI_FrlTrainMach(HDMI_DEVICE_ID_E enHdmiID);
HI_S32 DRV_HDMI_FrlModeChange(HDMI_DEVICE_ID_E enHdmiID, HDMI_FRL_DEBUG_S *pstDebug);

#ifdef __cplusplus
}
#endif

#endif //__DRV_HDMI_FRL__

