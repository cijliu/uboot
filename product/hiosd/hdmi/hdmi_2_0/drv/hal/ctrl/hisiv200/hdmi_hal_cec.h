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
#ifndef __HDMI_HAL_CEC_H__
#define __HDMI_HAL_CEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef HDMI_BUILD_IN_BOOT

#include "hi_type.h"
#include "drv_hdmi_common.h"
#include "hdmi_product_define.h"




//#define CEC_MAX_CMD_SIZE            16
#define CEC_MAX_RAW_SIZE            15
#define CEC_MAX_MSG_NUM             64
#define CEC_DEFAULT_MACH_INTERVAL   10


/***************************CEC data Structure *******************************************/
typedef enum
{
    CEC_LOGICALADD_TV               = 0X00,
    CEC_LOGICALADD_RECORDDEV_1      = 0X01,
    CEC_LOGICALADD_RECORDDEV_2      = 0X02,
    CEC_LOGICALADD_TUNER_1          = 0X03,
    CEC_LOGICALADD_PLAYDEV_1        = 0X04,
    CEC_LOGICALADD_AUDIOSYSTEM      = 0X05,
    CEC_LOGICALADD_TUNER_2          = 0X06,
    CEC_LOGICALADD_TUNER_3          = 0X07,
    CEC_LOGICALADD_PLAYDEV_2        = 0X08,
    CEC_LOGICALADD_RECORDDEV_3      = 0X09,
    CEC_LOGICALADD_TUNER_4          = 0X0A,
    CEC_LOGICALADD_PLAYDEV_3        = 0X0B,
    CEC_LOGICALADD_RESERVED_1       = 0X0C,
    CEC_LOGICALADD_RESERVED_2       = 0X0D,
    CEC_LOGICALADD_SPECIALUSE       = 0X0E,
    CEC_LOGICALADD_BROADCAST        = 0X0F,
    CEC_LOGICALADD_BUTT
}CEC_LOGICALADD_E;



typedef enum
{
    CEC_UICMD_SELECT                      = 0x00,
    CEC_UICMD_UP                          = 0x01,
    CEC_UICMD_DOWN                        = 0x02,
    CEC_UICMD_LEFT                        = 0x03,
    CEC_UICMD_RIGHT                       = 0x04,
    CEC_UICMD_RIGHT_UP                    = 0x05,
    CEC_UICMD_RIGHT_DOWN                  = 0x06,
    CEC_UICMD_LEFT_UP                     = 0x07,
    CEC_UICMD_LEFT_DOWN                   = 0x08,
    CEC_UICMD_ROOT_MENU                   = 0x09,
    CEC_UICMD_SETUP_MENU                  = 0x0A,
    CEC_UICMD_CONTENTS_MENU               = 0x0B,
    CEC_UICMD_FAVORITE_MENU               = 0x0C,
    CEC_UICMD_EXIT                        = 0x0D,
    CEC_UICMD_NUM_0                       = 0x20,
    CEC_UICMD_NUM_1                       = 0x21,
    CEC_UICMD_NUM_2                       = 0x22,
    CEC_UICMD_NUM_3                       = 0x23,
    CEC_UICMD_NUM_4                       = 0x24,
    CEC_UICMD_NUM_5                       = 0x25,
    CEC_UICMD_NUM_6                       = 0x26,
    CEC_UICMD_NUM_7                       = 0x27,
    CEC_UICMD_NUM_8                       = 0x28,
    CEC_UICMD_NUM_9                       = 0x29,
    CEC_UICMD_DOT                         = 0x2A,
    CEC_UICMD_ENTER                       = 0x2B,
    CEC_UICMD_CLEAR                       = 0x2C,
    CEC_UICMD_NEXT_FAVORITE               = 0x2F,
    CEC_UICMD_CHANNEL_UP                  = 0x30,
    CEC_UICMD_CHANNEL_DOWN                = 0x31,
    CEC_UICMD_PREVIOUS_CHANNEL            = 0x32,
    CEC_UICMD_SOUND_SELECT                = 0x33,
    CEC_UICMD_INPUT_SELECT                = 0x34,
    CEC_UICMD_DISPLAY_INFORMATION         = 0x35,
    CEC_UICMD_HELP                        = 0x36,
    CEC_UICMD_PAGE_UP                     = 0x37,
    CEC_UICMD_PAGE_DOWN                   = 0x38,
    CEC_UICMD_POWER                       = 0x40,
    CEC_UICMD_VOLUME_UP                   = 0x41,
    CEC_UICMD_VOLUME_DOWN                 = 0x42,
    CEC_UICMD_MUTE                        = 0x43,
    CEC_UICMD_PLAY                        = 0x44,
    CEC_UICMD_STOP                        = 0x45,
    CEC_UICMD_PAUSE                       = 0x46,
    CEC_UICMD_RECORD                      = 0x47,
    CEC_UICMD_REWIND                      = 0x48,
    CEC_UICMD_FAST_FORWARD                = 0x49,
    CEC_UICMD_EJECT                       = 0x4A,
    CEC_UICMD_FORWARD                     = 0x4B,
    CEC_UICMD_BACKWARD                    = 0x4C,
    CEC_UICMD_STOP_RECORD                 = 0x4D,
    CEC_UICMD_PAUSE_RECORD                = 0x4E,
    CEC_UICMD_ANGLE                       = 0x50,
    CEC_UICMD_SUBPICTURE                  = 0x51,
    CEC_UICMD_VIDEO_ON_DEMAND             = 0x52,
    CEC_UICMD_ELECTRONIC_PROGRAM_GUIDE    = 0x53,
    CEC_UICMD_TIMER_PROGRAMMING           = 0x54,
    CEC_UICMD_INITIAL_CONFIGURATION       = 0x55,
    CEC_UICMD_PLAY_FUNCTION               = 0x60,
    CEC_UICMD_PAUSE_PLAY_FUNCTION         = 0x61,
    CEC_UICMD_RECORD_FUNCTION             = 0x62,
    CEC_UICMD_PAUSE_RECORD_FUNCTION       = 0x63,
    CEC_UICMD_STOP_FUNCTION               = 0x64,
    CEC_UICMD_MUTE_FUNCTION               = 0x65,
    CEC_UICMD_RESTORE_VOLUME_FUNCTION     = 0x66,
    CEC_UICMD_TUNE_FUNCTION               = 0x67,
    CEC_UICMD_SELECT_MEDIA_FUNCTION       = 0x68,
    CEC_UICMD_SELECT_AV_INPUT_FUNCTION    = 0x69,
    CEC_UICMD_SELECT_AUDIO_INPUT_FUNCTION = 0x6A,
    CEC_UICMD_POWER_TOGGLE_FUNCTION       = 0x6B,
    CEC_UICMD_POWER_OFF_FUNCTION          = 0x6C,
    CEC_UICMD_POWER_ON_FUNCTION           = 0x6D,
    CEC_UICMD_F1_BLUE                     = 0x71,
    CEC_UICMD_F2_RED                      = 0x72,
    CEC_UICMD_F3_GREEN                    = 0x73,
    CEC_UICMD_F4_YELLOW                   = 0x74,
    CEC_UICMD_F5                          = 0x75,
    CEC_UICMD_DATA                        = 0x76,

    CEC_UICMD_REPORT_PHYADDR              = 0x84
}CEC_UICMD_E;


typedef enum
{
    CEC_MACH_IDLE,

    CEC_MACH_PING_START,
    CEC_MACH_PING_WAIT_DONE,

    CEC_MACH_RX_WAIT_DONE,

    CEC_MACH_TX_START,
    CEC_MACH_TX_WAIT_DONE,

}CEC_MACH_STATUS_E;

typedef enum{
    CEC_PROCESS_UNDO,
    CEC_PROCESS_OK,
    CEC_PROCESS_FAIL,
    CEC_PROCESS_ING,
}CEC_PROCESS_E;

typedef struct
{
    HI_U8                   u8Length;
    HI_U8                   u8Data[CEC_MAX_RAW_SIZE];
}CEC_RAWDATA_S;

typedef struct
{
    CEC_LOGICALADD_E        enSrcAddr;
    CEC_LOGICALADD_E        enDestAddr;
    HI_U8                   u8Opcode;
    CEC_RAWDATA_S           stRawData;
}CEC_MSG_S;

typedef struct
{
    HI_BOOL             bInit;

    HDMI_CEC_INFO_S     stDrvInfo;
    HI_U32              u32MachId;
    CEC_PROCESS_E       enPingProcess;
    CEC_MACH_STATUS_E   enMachStatus;


    /* tx */
    HI_U32              u32TxMsgCnt;
    HI_U32              u32TxRecordWtPtr;

    HI_U32              u32TxPoolWtPtr;
    HI_U32              u32TxPoolRdPtr;
	HI_U32              u32TxPoolRdAbleCnt;

    /* rx */
    HI_U32              u32RxMsgCnt;
    HI_U32              u32RxRecordWtPtr;

    HI_U32              u32RxPoolWtPtr;
    HI_U32              u32RxPoolRdPtr;
	HI_U32              u32RxPoolRdAbleCnt;

}CEC_STATUS_S;


typedef enum
{
    CEC_MSG_TYPE_RECV,
    CEC_MSG_TYPE_SENT,

}CEC_MSG_TYPE_E;


typedef struct
{
    HI_U32              u32Idx;
    CEC_MSG_TYPE_E      enType;

}CEC_ELEM_IDX_S;

typedef struct
{
    HI_BOOL             bCecEnable;
    CEC_PROCESS_E       enProcess;
    CEC_MSG_S           stMsg;
    HI_U64              u64TimeStamp;
}CEC_MSG_ELEM_S;


typedef struct
{
    HI_BOOL             bInit;

    HDMI_DEVICE_ID_E    enHdmiId;
    HDMI_CEC_INFO_S     stDrvInfo;
    HI_U32              u32MachId;
    HI_U32              u32MaxPingTime;
    CEC_PROCESS_E       enPingProcess;
    HI_U64              u64MachStamp;
    CEC_MACH_STATUS_E   enMachStatus;
    HI_U64              u64StopStamp;

    /* tx */
    HI_U32              u32TxMsgCnt;
    HI_U32              u32TxRecordWtPtr;
    CEC_MSG_ELEM_S      stTxRecord[CEC_MAX_MSG_NUM];

    CEC_PROCESS_E       enTxProcess;
    HI_U32              u32TxPoolWtPtr;
    HI_U32              u32TxPoolRdPtr;
	HI_U32              u32TxPoolRdAbleCnt;
    CEC_MSG_ELEM_S      stTxPool[CEC_MAX_MSG_NUM];
    HDMI_SEMAPHORE      stTxMute;

    /* rx */
    HI_U32              u32RxMsgCnt;
    HI_U32              u32RxRecordWtPtr;
    CEC_MSG_ELEM_S      stRxRecord[CEC_MAX_MSG_NUM];

    CEC_PROCESS_E       enRxProcess;
    HI_U32              u32RxPoolWtPtr;
    HI_U32              u32RxPoolRdPtr;
	HI_U32              u32RxPoolRdAbleCnt;
    CEC_MSG_ELEM_S      stRxPool[CEC_MAX_MSG_NUM];
    HDMI_SEMAPHORE      stRxMute;

    HI_BOOL             bRxWakeUpFlag;			/* wake up flag */
    HDMI_WAIT_QUEUE     stRxWaitQueue;


}CEC_INFO_S;


HI_S32 HAL_HDMI_CecInit(HDMI_DEVICE_ID_E enHdmiId, HDMI_HAL_INIT_S *pstHalInit);

HI_S32 HAL_HDMI_CecDeInit(HDMI_DEVICE_ID_E enHdmiId);

HI_S32 HAL_HDMI_CecReset(HDMI_DEVICE_ID_E enHdmiId);

HI_S32 HAL_HDMI_CecNetGet(HDMI_DEVICE_ID_E enHdmiId,HI_U8 *pu8PhyAddr);

HI_S32 HAL_HDMI_CecEnable(HDMI_DEVICE_ID_E enHdmiId,HI_BOOL bEnanble);

HI_S32 HAL_HDMI_CecInfoGet(HDMI_DEVICE_ID_E enHdmiId, HDMI_CEC_INFO_S *pstDrvCecInfo);

HI_S32 HAL_HDMI_CecMsgTx(HDMI_DEVICE_ID_E enHdmiId,CEC_MSG_S *pstMsg);

HI_S32 HAL_HDMI_CecMsgRx(HDMI_DEVICE_ID_E enHdmiId,CEC_MSG_S *pstMsg);

HI_S32 HAL_HDMI_CecStatGet(HDMI_DEVICE_ID_E enHdmiId,CEC_STATUS_S *pstStatus);

HI_S32 HAL_HDMI_CecRecordMsgGet(HDMI_DEVICE_ID_E enHdmiId,CEC_ELEM_IDX_S *pstIdx,CEC_MSG_ELEM_S *pstElem);

#endif /* HDMI_BUILD_IN_BOOT */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_HAL_CEC_H__ */





