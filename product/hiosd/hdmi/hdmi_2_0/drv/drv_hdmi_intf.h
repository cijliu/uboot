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
#ifndef __DRV_HDMI_INTF_H__
#define __DRV_HDMI_INTF_H__
#include "hi_type.h"
#include "hdmi_hal.h"
#include "drv_hdmi_common.h"
#include "drv_hdmi_ioctl.h"
#include "drv_hdmi_edid.h"
#include "drv_hdmi_event.h"

#ifdef HDMI_FRL_SUPPORT
#include "drv_hdmi_frl.h"
#endif

#ifdef HDMI_TEE_SUPPORT
#include "drv_hdmi_tee.h"
#endif

typedef enum
{
	STATE_PLUG_UNKNOWN = -1,
	STATE_HOTPLUGOUT = 0,
	STATE_HOTPLUGIN = 1
}HDMI_SWITCH_STATE;

typedef struct
{
    HDMI_THREAD_STATE_E  kThreadTimerSate;
    HDMI_TASK_T         *kThreadTimer;
    HI_BOOL              bThreadRun;
}HDMI_THREAD_INFO_S;

typedef struct
{
    HI_BOOL              bAttrBusy;
    HI_BOOL              bAttrSet;
    HDMI_SPIN_S          stAttrSpin;
}HDMI_HDR_MUTEX_S;

typedef struct
{
    HI_U32                   u32HdmiDevId;
    HI_U32                   u32KernelCnt;
    HI_U32                   u32UserCnt;
    HI_U32                   u32UserCallBackCnt;
    HI_CHAR                  *pcVirtualBaseAddr;
    HI_BOOL                  bEmiEnable;
    HI_BOOL                  bHpdDetected;
    HDMI_RUN_STATE_E         enRunState;
    HDMI_TRANSITION_STATE_E  enTransitionState;
    HDMI_TMDS_MODE_E         enTmdsMode;
    HMDI_CALLBACK            pKCallback;
    HDMI_THREAD_INFO_S       stThreadInfo;
    HDMI_EDID_INFO_S         stEdidInfo;
    HDMI_INFOFRAME_S         stInfoFrame;
    HDMI_ATTR_S              stAttr;
    HDMI_DELAY_S             stDelay;
    HDMI_HAL_S*              pstHdmiHal;
    HDMI_DEBUG_S             stDebug;
    HDMI_SEMAPHORE			 stMutexThread;
    HDMI_SEMAPHORE           stMutexProc;

#ifdef HDMI_HDCP_SUPPORT
    HDMI_HDCP_INFO_S         stHdcpInfo;
#endif
#ifdef HDMI_CEC_SUPPORT
    HDMI_CEC_INFO_S          stCecInfo;
#endif
#ifdef HDMI_HDR_SUPPORT
    HDMI_HDR_INFO_S          stHdrInfo;
    HDMI_HDR_MUTEX_S         stHdrMutex;
#endif
#ifdef HDMI_TEE_SUPPORT
    HDMI_TEE_INFO_S          stTeeInfo;
#endif
#ifdef HDMI_FRL_SUPPORT
	HDMI_FRL_INFO_S          stFrlInfo;
#endif

    HDMI_MOD_PARAM_S         stModParam;
}HDMI_DEVICE_S;

HI_S32 DRV_HDMI_Init(HI_VOID);
HI_S32 DRV_HDMI_DeInit(HI_VOID);
HI_S32 DRV_HDMI_Open(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bUser);
HI_S32 DRV_HDMI_Close(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bUser);
HI_S32 DRV_HDMI_Start(HDMI_DEVICE_S* pstHdmiDev);
HI_S32 DRV_HDMI_Stop(HDMI_DEVICE_S* pstHdmiDev);

HI_S32 DRV_HDMI_DeepColorSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DEEP_COLOR_E enDeepColor);
HI_S32 DRV_HDMI_DeepColorGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DEEP_COLOR_E* enDeepColor);
HI_S32 DRV_HDMI_XvYCCModeSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable);

HI_VOID DRV_HDMI_AVMuteSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bAvMute);
HI_S32 DRV_HDMI_VOAttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstVOAttr);

HI_S32 DRV_HDMI_PlayStatusGet(HDMI_DEVICE_S* pstHdmiDev, HI_U32* u32Status);
#ifdef HDMI_HDCP_SUPPORT
HI_S32 DRV_HDMI_KeyLoad(HDMI_DEVICE_S* pstHdmiDev, HDMI_LOAD_KEY_S *pstLoadKey);
#endif
HI_S32 DRV_HDMI_AOAttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr);
HI_S32 DRV_HDMI_AOAttrGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr);
HI_VOID DRV_HDMI_AudioPathEnable(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable);
HI_S32 DRV_HDMI_AudioOutputEnableSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bMute);

HI_S32 DRV_HDMI_AttrGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr);
HI_S32 DRV_HDMI_AttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr);

#ifdef CONFIG_HDMI_STB_SDK
HI_S32 HI_DRV_HDMI_PixClkGet(HI_UNF_ENC_FMT_E enFormat,HI_U32 *pu32PixClk);
#endif

#ifdef HDMI_CEC_SUPPORT
HI_S32 DRV_HDMI_CecCmdSend(HDMI_DEVICE_S* pstHdmiDev,  HDMI_CEC_CMD_S  *pstCecCmd);
HI_S32 DRV_HDMI_CecCmdReceive(HDMI_DEVICE_S* pstHdmiDev, HDMI_CEC_CMD_S  *pstCecCmd);
HI_S32 DRV_HDMI_CecStatusGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_CEC_INFO_S  *pstCecStatus);
HI_S32 DRV_HDMI_CecEnableSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable);
#endif
HI_S32 DRV_HDMI_InfoFrameGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_INFOFRAME_ID_E enInfoFrameId, HDMI_INFOFRAME_U *puInfoFrame);
HI_S32 DRV_HDMI_InfoFrameSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_INFOFRAME_ID_E enInfoFrameId, HDMI_INFOFRAME_U *puInfoFrame);

HI_S32 DRV_HDMI_CmdProcess(unsigned int cmd, HI_VOID *arg, HI_BOOL bUser);
HDMI_VIDEO_TIMING_E DispFmt2HdmiTiming(HDMI_DEVICE_S* pstHdmiDev, HI_U32 u32DispFmt);
HDMI_DEVICE_S* GetHdmiDevice(HDMI_DEVICE_ID_E enHdmiID);
HI_S32 DRV_HDMI_DefaultActionSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DEFAULT_ACTION_E enAction);
HI_S32 DRV_HDMI_ThreadStateSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_THREAD_STATE_E enState);

HI_S32 DRV_HDMI_DelayGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DELAY_S *pHdmiDelay);
HI_S32 DRV_HDMI_DelaySet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DELAY_S *pHdmiDelay);
HI_S32 DRV_HDMI_EmiSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstHwVOAttr, HDMI_APP_ATTR_S* pstHwAPPAttr);
HI_S32 HdmiModeStrategy(HDMI_DEVICE_S* pstHdmiDev);

#endif
