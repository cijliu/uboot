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
#ifndef __DRV_HDMI_TEE_H__
#define __DRV_HDMI_TEE_H__

#include "drv_hdmi_common.h"
#include "teek_client_api.h"    // tee

#define HDMI_TEE_DATA_SIZE 1024
typedef enum {
    HI_HDMI_HDCP14_INIT,
    HI_HDMI_HDCP14_BKSV_SET,
    HI_HDMI_HDCP14_RPT_ENABLE,
    HI_HDMI_HDCP14_R0_VERIFY,
    HI_HDMI_HDCP14_KSVLIST_SET,
    HI_HDMI_HDCP14_VI_VERIFY,
    HI_HDMI_HDCP14_ENC_ENABLE,
    HI_HDMI_HDCP14_EVENT,
    HI_HDMI_HDCP22_INIT,
    HI_HDMI_TEE_STATUS_VIEW,
    HI_HDMI_HDCP_CAPS,
    HI_HDMI_STOP,
    HI_HDMI_TEST_SET_HDCP_STRATEGY,
    HI_HDMI_COMM_BUTT,
} HI_HDMI_COMMID_E;

enum TEE_Result_Value{
    TEE_SUCCESS = 0x0,                          
    TEE_ERROR_INVALID_CMD,                      
    TEE_ERROR_SERVICE_NOT_EXIST,                
    TEE_ERROR_SESSION_NOT_EXIST,                
    TEE_ERROR_SESSION_MAXIMUM,                  
    TEE_ERROR_REGISTER_EXIST_SERVICE,           
    TEE_ERROR_TARGET_DEAD_FATAL,                 
    TEE_ERROR_READ_DATA,                        
    TEE_ERROR_WRITE_DATA,                       
    TEE_ERROR_TRUNCATE_OBJECT,                  
    TEE_ERROR_SEEK_DATA,                        
    TEE_ERROR_SYNC_DATA,                        
    TEE_ERROR_RENAME_OBJECT,                    
    TEE_ERROR_TRUSTED_APP_LOAD_ERROR,           
#ifdef GP_V1_1_SUPPORTED
    TEE_ERROR_CORRUPT_OBJECT=0xF0100001,/**If the persistent object is corrupt. The object handle is closed.*/
    TEE_ERROR_CORRUPT_OBJECT_2=0xF0100002,/**If the persistent object is stored in a storage area which is currently inaccessible.*/
    TEE_ERROR_STORAGE_NOT_AVAILABLE=0xF0100003,
    TEE_ERROR_STORAGE_NOT_AVAILABLE_2=0xF0100004,
#endif
    TEE_ERROR_GENERIC = 0xFFFF0000,             
    TEE_ERROR_ACCESS_DENIED = 0xFFFF0001 ,      
    TEE_ERROR_CANCEL = 0xFFFF0002 ,             
    TEE_ERROR_ACCESS_CONFLICT = 0xFFFF0003 ,    
    TEE_ERROR_EXCESS_DATA = 0xFFFF0004 ,        
    TEE_ERROR_BAD_FORMAT = 0xFFFF0005 ,         
    TEE_ERROR_BAD_PARAMETERS = 0xFFFF0006 ,     
    TEE_ERROR_BAD_STATE = 0xFFFF0007,           
    TEE_ERROR_ITEM_NOT_FOUND = 0xFFFF0008,      
    TEE_ERROR_NOT_IMPLEMENTED = 0xFFFF0009,     
    TEE_ERROR_NOT_SUPPORTED = 0xFFFF000A,       
    TEE_ERROR_NO_DATA = 0xFFFF000B,             
    TEE_ERROR_OUT_OF_MEMORY = 0xFFFF000C,       
    TEE_ERROR_BUSY = 0xFFFF000D,                
    TEE_ERROR_COMMUNICATION = 0xFFFF000E,       
    TEE_ERROR_SECURITY = 0xFFFF000F,            
    TEE_ERROR_SHORT_BUFFER = 0xFFFF0010,        
    TEE_PENDING = 0xFFFF2000,                   
    TEE_PENDING2 = 0xFFFF2001,                  
    TEE_PENDING3 = 0xFFFF2002,
    TEE_ERROR_TIMEOUT = 0xFFFF3001,             
    TEE_ERROR_OVERFLOW = 0xFFFF300f,            
    TEE_ERROR_TARGET_DEAD = 0xFFFF3024,          
    TEE_ERROR_STORAGE_NO_SPACE = 0xFFFF3041,    
    TEE_ERROR_FILE_CORRUPT = 0xFFFF3042,        
    TEE_ERROR_MAC_INVALID = 0xFFFF3071,         
    TEE_ERROR_SIGNATURE_INVALID = 0xFFFF3072,   
    TEE_ERROR_TIME_NOT_SET = 0xFFFF5000,        
    TEE_ERROR_TIME_NEEDS_RESET = 0xFFFF5001,    
    TEE_FAIL = 0xFFFF5002,    
    TEE_ERROR_TIMER = 0xFFFF6000,
    TEE_ERROR_TIMER_CREATE_FAILED,
    TEE_ERROR_TIMER_DESTORY_FAILED,
    TEE_ERROR_TIMER_NOT_FOUND,
    TEE_ERROR_RPMB_BASE = 0xFFFF7000,    
    TEE_ERROR_RPMB_GENERIC = 0xFFFF7001,    
    TEE_ERROR_RPMB_MAC_FAIL,    
    TEE_ERROR_RPMB_COUNTER_FAIL,    
    TEE_ERROR_RPMB_ADDR_FAIL,    
    TEE_ERROR_RPMB_WRITE_FAIL,    
    TEE_ERROR_RPMB_READ_FAIL,    
    TEE_ERROR_RPMB_KEY_NOT_PROGRAM,    
    TEE_ERROR_RPMB_RESP_UNEXPECT_MSGTYPE = 0xFFFF7100,    
    TEE_ERROR_RPMB_RESP_UNEXPECT_BLKCNT,    
    TEE_ERROR_RPMB_RESP_UNEXPECT_BLKIDX,    
    TEE_ERROR_RPMB_RESP_UNEXPECT_WRCNT,    
    TEE_ERROR_RPMB_RESP_UNEXPECT_NONCE,    
    TEE_ERROR_RPMB_RESP_UNEXPECT_MAC,    
    TEE_ERROR_RPMB_FILE_NOT_FOUND,    
    TEE_ERROR_RPMB_NOSPC,    
    TEE_ERROR_TUI_IN_USE = 0xFFFF7110,
    TEE_ERROR_TUI_SWITCH_CHANNAL,
    TEE_ERROR_TUI_CFG_DRIVER,
    TEE_ERROR_TUI_INVALID_EVENT,
    TEE_ERROR_TUI_POLL_EVENT,
    TEE_ERROR_TUI_CANCELED,
    TEE_FAIL2
};

typedef struct hiHDMI_TEE_INFO_S
{
    HI_BOOL         bTeeOpen;
    TEEC_Context    stTeecContext;
    TEEC_Operation  stTeecOperation;
    TEEC_Session    stTeecSession;
    HI_U8           au8TeeDataBuf[HDMI_TEE_DATA_SIZE];
    HI_U32          u32DataSize;
}HDMI_TEE_INFO_S;

typedef struct hiHDMI_TEE_HDCP_CAPS_S
{
    HI_BOOL         bHdcp14Support;
    HI_BOOL         bHdcp22Support;
}HDMI_TEE_HDCP_CAPS_S;

typedef struct hiHDMI_TEE_PARAM_S
{
    HI_HDMI_COMMID_E        enTeeCmd;
    HDMI_TEE_HDCP_CAPS_S    seHdcpCaps;
    HI_U32                  u32TestParam;
    HI_U32                  *pvData;
    HI_U32                  u32Size;
}HDMI_TEE_PARAM_S;

extern TEEC_UUID HdmiTaskUUID;
HI_S32 DRV_HDMI_TeeOpen(HDMI_DEVICE_ID_E enHdmiId);
HI_S32 DRV_HDMI_TeeCmdSend(HDMI_DEVICE_ID_E enHdmiId, HDMI_TEE_PARAM_S *pstParam);
HI_S32 DRV_HDMI_TeeClose(HDMI_DEVICE_ID_E enHdmiId);


#endif

