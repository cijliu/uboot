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
#ifndef HDMI_LITEOS_SUPPORT
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/major.h>
#include <asm/uaccess.h>
#endif
#include "drv_hdmi_debug.h"
#include "drv_hdmi_common.h"
#include "drv_hdmi_intf.h"
#include "drv_hdmi_event.h"
#include "drv_hdmi_edid.h"
#include "drv_hdmi_common.h"
#include "hdmi_osal.h"

#ifdef HDMI_FRL_SUPPORT
#include "hdmi_hal_timer.h"
#endif

#define HDMI_DBG_PRINT              DEBUG_EchoHelper
#define HDMI_DBG_ERR                HDMI_DBG_PRINT("[HDMI DBG ERROR]: %s [%d],",__func__,__LINE__);HDMI_DBG_PRINT

#define DEBUG_MAX_CMD_CHAR_NUM      2048
#define DEBUG_MAX_ARGV_NUM          10

#define DEBUG_CHAR_SPACE            0x20
#define DEBUG_CHAR_TAB              0x09
#define DEBUG_CHAR_END              0x0a

#define DEBUG_MAX_EDIDBUF_SIZE      2048

#define DEBUG_PROC_BUFFER_SIZE      1024
#define SERIAL_MAJOR                204


#define STR_SUCC                    "success"
#define STR_FAIL                    "fail"

#ifndef TOLOWER
#define TOLOWER(x)                  ((x) | 0x20)
#endif


#define DEBUG_NULL_CHK(p) do{\
	if(HI_NULL == p)\
    {HDMI_WARN("%s null pointer!\n",#p);\
	HDMI_DBG_ERR("%s null pointer!\n",#p);\
	return HI_FAILURE;}\
}while(0)

#define DEBUG_NULL_CHK_NO_RET(p) do{\
    if(HI_NULL == p)\
    {HDMI_WARN("%s is null pointer!return fail.\n",#p);\
    return ;}\
}while(0)


#define DEBUG_FAILURE_RET_CHK(s32Ret) do{\
	if(HI_SUCCESS != s32Ret)\
    {HDMI_WARN("return failure!\n");\
	HDMI_DBG_ERR("return failure!\n");\
	return HI_FAILURE;}\
}while(0)


typedef struct {
    HI_BOOL bDataValid;
    HI_S32  s32Len;
    HI_U8   au8Data[HDMI_EDID_TOTAL_SIZE];
}HDMI_DEBUG_EDID_S;

static HDMI_DEBUG_EDID_S s_stDebugEdid = {0};

const static char *s_aEventStrTable[] = {
    "HPD",                      //HDMI_EVENT_HOTPLUG = 0x10,
    "HOTUNPLUG",                //HDMI_EVENT_HOTUNPLUG,
    "EDID_FAIL",                //HDMI_EVENT_EDID_FAIL,
    "HDCP_FAIL",                //HDMI_EVENT_HDCP_FAIL,
    "HDCP_SUCCESS",             //HDMI_EVENT_HDCP_SUCCESS,
    "RSEN_CONNECT",             //HDMI_EVENT_RSEN_CONNECT,
    "RSEN_DISCONNECT",          //HDMI_EVENT_RSEN_DISCONNECT,
    "HDCP_USERSETTING",         //HDMI_EVENT_HDCP_USERSETTING,
    "SCRAMBLE_FAIL",            //HDMI_EVENT_SCRAMBLE_FAIL,
    "SCRAMBLE_SUCCESS",         //HDMI_EVENT_SCRAMBLE_SUCCESS,
                                //HDMI_EVENT_BUTT
};

typedef struct
{
    HI_U32          u32DdcRegCfg;
    HI_U32          u32ApproximateValue;
    HI_CHAR         *pstReadValue;
}HDMI_DDC_FREQ_S;

HDMI_DDC_FREQ_S s_astDdcFreq[] = {

    {0x45,   20,  " 19.89"},
    {0x29,   30,  " 29.97"},
    {0x21,   40,  " 40.06"},
    {0x1a,   50,  " 49.90"},
    {0x15,   60,  " 60.53"},
    {0x12,   70,  " 69.42"},
    {0x0f,   80,  " 81.38"},
    {0x0d,   90,  " 91.87"},
    {0x0c,   100, " 98.11"},
    {0x0a,   110, "113.78"},
    {0x07,   150, "149.85"},
    {0x04,   220, "219.43"}

};

typedef struct file *PFILE;

typedef enum
{
    HDMI_DEBUG_BASE_OSD = 8 ,
    HDMI_DEBUG_BASE_DEC = 10,
    HDMI_DEBUG_BASE_HEX = 16,

}HDMI_DEBUG_BASE_E;


typedef struct{

    HDMI_DEVICE_ID_E    enHdmiId;
    HI_CHAR             *pcArgv[DEBUG_MAX_ARGV_NUM];
    HI_U32              u32Argc;
    HI_U32              u32RemainLen;

}HDMI_DEBUG_CMD_ARG_S;

typedef HI_S32 (*PFN_CMD_FUNC)(HDMI_DEBUG_CMD_ARG_S *pstCmdArg);

typedef struct{
    HI_CHAR         *pcName;
    HI_CHAR         *pcShortName;
    PFN_CMD_FUNC    pfnCmdFunc;
    HI_CHAR         *pCommentHelp;

}HDMI_DEBUG_CMD_INFO_S;

static HI_S32 DebugPrintHelp(HDMI_DEBUG_CMD_ARG_S *pstCmdArg);


/******************************************************************************
**
******************************************************************************/
HI_VOID DEBUG_EchoHelperVargs(HI_CHAR *buf, HI_U32 size, const HI_CHAR * fmt, HDMI_VA_LIST args)
{
#define DEFAULT_ECHO_DEVICE_HANDLE (0)

    struct kstat stat;
    HI_S32 ret;

    if (!buf || 0 == size)
        return;

    ret = vfs_fstat(DEFAULT_ECHO_DEVICE_HANDLE, &stat);
    if (ret)
    {
        HDMI_ERR("Default echo device handle(%u) invalid!\n", DEFAULT_ECHO_DEVICE_HANDLE);
        return;
    }

    HDMI_OSAL_Vsnprintf(buf, size, fmt, args);

    /* echo device must be chrdev and major number must be SERIAL_MAJOR or TTYAUX_MAJOR or UNIX98_PTY_SLAVE_MAJOR */
    if (S_ISCHR(stat.mode) && (MAJOR(stat.rdev) == SERIAL_MAJOR || MAJOR(stat.rdev) == TTYAUX_MAJOR || MAJOR(stat.rdev) == UNIX98_PTY_SLAVE_MAJOR))
    {
        struct file *file = fget(DEFAULT_ECHO_DEVICE_HANDLE);
        if (file)
        {
            /* file pos is invalid for chrdev */
            HDMI_OSAL_FileWrite(file, buf, HDMI_STRLEN(buf));
            fput(file);
        }
    }
    else
    {
        HDMI_ERR("Default echo device is invalid!\n");
    }
}


HI_VOID DEBUG_EchoHelper(const HI_CHAR *fmt, ...)
{
    HDMI_VA_LIST args;
    HI_CHAR *pucBuf = HI_NULL;

    if (!fmt)
    {
        HDMI_ERR("Invalid argument fmt!\n");
        return;
    }
    pucBuf = HDMI_VMALLOC(DEBUG_PROC_BUFFER_SIZE);
    if (HI_NULL == pucBuf)
    {
        HDMI_ERR("Memory allocate failed for proc\n");
        return;
    }

    HDMI_VA_START(args, fmt);
    DEBUG_EchoHelperVargs(pucBuf, DEBUG_PROC_BUFFER_SIZE, fmt, args);
    HDMI_VA_END(args);

    HDMI_VFREE(pucBuf);
}


static HI_BOOL IS_HEX_SPACE(HI_CHAR a)
{
    HI_BOOL bIsSpace = HI_FALSE;

    bIsSpace = ( a== DEBUG_CHAR_SPACE || a==DEBUG_CHAR_TAB || a==',' || a==';' || a=='\0' || a=='\n' || a=='\r' );

	return bIsSpace;
}

static HI_BOOL IS_HEX_CHAR(HI_CHAR a)
{
    HI_BOOL bIsChar = HI_FALSE;

    bIsChar = ( (a>='0' && a<='9') || (a>='a' && a<='f') || (a>='A' && a<='F') );

	return bIsChar;
}

static HI_CHAR HEX_VALUE_GET(HI_CHAR a)
{
	if ((a>='0' && a<='9'))
    {
    	return a - '0';
    }
	else if (a>='a' && a<='f')
    {
    	return a - 'a' + 0xa;
    }
	else if(a>='A' && a<='F')
    {
    	return a - 'A' + 0xa;
    }
	else
    {
    	return 0xff;
    }
}

static HI_BOOL IS_HEX_START(HI_CHAR *p,HI_CHAR **pcEnd)
{
    DEBUG_NULL_CHK(p);

	if (*p=='0' && (p[1]=='x' || p[1]=='X') )
    {
    	if (pcEnd)
        {
            *pcEnd = p+2;
        }

    	return HI_TRUE;
    }
	else if ( IS_HEX_CHAR(p[0])
            &&( IS_HEX_SPACE(p[1]) || (IS_HEX_CHAR(p[1]) && IS_HEX_SPACE(p[2]))) )
    {
    	if (pcEnd)
        {
            *pcEnd = p;
        }
    	return HI_TRUE;
    }
	else
    {
    	if (pcEnd)
        {
            *pcEnd = p;
        }
    	return HI_FALSE;
    }
}


static HI_S32 DebugStr2Hex(HI_CHAR *pcDest,HI_S32 s32Dlen,HI_CHAR *pcSrc,HI_U32 u32Slen)
{
	HI_U8 u8Result = 0;
	HI_CHAR *p = pcSrc;
	HI_S32  s32OldLen = s32Dlen;

	DEBUG_NULL_CHK(pcSrc);
	DEBUG_NULL_CHK(pcDest);

	while(p < (pcSrc+u32Slen) && s32Dlen)
    {
    	if (IS_HEX_START(p,&p))
        {
        	if(IS_HEX_CHAR(p[0]))
            {
            	u8Result = HEX_VALUE_GET(p[0]);
            	p++;
            	if (IS_HEX_CHAR(p[0]))
                {
                	u8Result <<= 4;
                	u8Result |= HEX_VALUE_GET(p[0]);
                	p++;
                }

            	if (pcDest)
                {
                    *pcDest++ = u8Result;
                	s32Dlen--;
                }
            }
        	else
            {
            	return HI_FAILURE;
            }
        }
    	else
        {
        	p++;
        }

    }

	return s32OldLen - s32Dlen;
}


static HDMI_DEBUG_BASE_E DebugBaseGet(const HI_CHAR *pcStr)
{
    if (pcStr[0] == '0')
    {
        if (TOLOWER(pcStr[1]) == 'x' )
        {
            return HDMI_DEBUG_BASE_HEX;
        }
        else
        {
            return HDMI_DEBUG_BASE_OSD;
        }
    }
    else
    {
        return HDMI_DEBUG_BASE_DEC;
    }
}

static HI_U32 DebugStrToU32(const HI_CHAR *pcStr, HI_CHAR **ppcEnd, HDMI_DEBUG_BASE_E enBase)
{
    HI_U32 u32Result = 0;

    DEBUG_NULL_CHK(pcStr);

    if (   HDMI_DEBUG_BASE_OSD != enBase
        && HDMI_DEBUG_BASE_DEC != enBase
        && HDMI_DEBUG_BASE_HEX != enBase)
    {
        enBase = DebugBaseGet(pcStr);
    }

    if (enBase == HDMI_DEBUG_BASE_HEX && pcStr[0] == '0' && TOLOWER(pcStr[1]) == 'x')
    {
        pcStr += 2;
    }

    while (*pcStr)
    {
        HI_U32 u32Value;

        u32Value = ((*pcStr >= '0') && (*pcStr <= '9')) ? *pcStr - '0' : TOLOWER(*pcStr) - 'a' + 10;
        if (u32Value >= enBase)
        {
            break;
        }
        u32Result = u32Result * enBase + u32Value;
        pcStr++;
    }

    if (ppcEnd)
    {
        *ppcEnd = (HI_CHAR *)pcStr;
    }

    return u32Result;
}

static struct file *Debugfopen(const char *filename, int flags, int mode)
{
    if (!filename)
    {
        return HI_NULL;
    }

    return HDMI_FILP_OPEN(filename, flags, mode);
}

static void Debugfclose(struct file *filp)
{
    if (filp)
    {
        HDMI_FILP_CLOSE(filp);
    }
}

static int Debugfread(char *buf, unsigned int len, struct file *filp)
{
    int readlen;

    DEBUG_NULL_CHK(buf);
    /* use osal public interface. */
    readlen = HDMI_FILP_READ(buf, len, filp);

    return readlen;
}

static HI_S32 DebugThread(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32          s32Ret = HI_FAILURE;
	HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       s32Ret = DRV_HDMI_ThreadStateSet(pstHdmiDev,HDMI_THREAD_STATE_STOP);
       HDMI_DBG_PRINT("\n thread set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       s32Ret = DRV_HDMI_ThreadStateSet(pstHdmiDev,HDMI_THREAD_STATE_RUN);
       HDMI_DBG_PRINT("\n thread set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo thread argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--thread off.\n"
                   "           1\t--thread on.\n");
    HDMI_DBG_PRINT("[example]: echo thread 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugOe(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
	HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HDMI_BLACK_FRAME_INFO_S stBlackInfo;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    stBlackInfo.inBitDepth = pstHdmiDev->stAttr.stVOAttr.enInBitDepth;
    stBlackInfo.inColorSpace = pstHdmiDev->stAttr.stVOAttr.enInColorSpace;
    stBlackInfo.inQuantization = (stBlackInfo.inColorSpace == HDMI_COLORSPACE_RGB) ? \
    pstHdmiDev->stAttr.stVOAttr.enRGBQuantization : pstHdmiDev->stAttr.stVOAttr.enYCCQuantization;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
       HDMI_DBG_PRINT("\n oe set OFF %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);
        HDMI_DBG_PRINT("\n oe set ON %s! \n\n", STR_SUCC );
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo oe argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--oe off.\n"
                   "           1\t--oe on.\n");
    HDMI_DBG_PRINT("[example]: echo oe 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugEvent(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
	HDMI_EVENT_E            enEvent = 0;
	HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
	HI_CHAR                 *pcStr = pstCmdArg->pcArgv[1];

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pcStr == HI_NULL)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    enEvent = (HDMI_EVENT_E)DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);

    if ( (enEvent >= HDMI_EVENT_HOTPLUG)
        && (enEvent < HDMI_EVENT_BUTT) )
    {
        s32Ret = DRV_HDMI_EventPoolWrite(pstCmdArg->enHdmiId, enEvent);
        if ((enEvent-HDMI_EVENT_HOTPLUG) < HDMI_ARRAY_SIZE(s_aEventStrTable))
        {
            HDMI_DBG_PRINT("hardware event %s simulate %s.\n",
                        s_aEventStrTable[enEvent-HDMI_EVENT_HOTPLUG],
                        s32Ret!=HI_SUCCESS ? STR_FAIL: STR_SUCC);
        }
    }
    else
    {
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo event argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: event type(DECMICAL) as follow\n");
    for (enEvent = HDMI_EVENT_HOTPLUG;
        enEvent < HDMI_EVENT_BUTT && ((enEvent-HDMI_EVENT_HOTPLUG) < HDMI_ARRAY_SIZE(s_aEventStrTable));
        enEvent++)
    {
        HDMI_DBG_PRINT("%-10s %d\t-- (0x%02x)%s\n","",enEvent,enEvent,
                        s_aEventStrTable[enEvent-HDMI_EVENT_HOTPLUG]);
    }
    HDMI_DBG_PRINT("[example]: echo event 16 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugEdidFromFile(HDMI_DEVICE_S *pstHdmiDev, HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32               s32Ret = HI_FAILURE;
    PFILE                pFile = HI_NULL;
    HI_U8               *pu8Buf = HI_NULL;
    HDMI_DEBUG_EDID_S   *pstDbgEdid = &s_stDebugEdid;
    HI_S32              s32Len = 0;

	DEBUG_NULL_CHK(pstHdmiDev);
	DEBUG_NULL_CHK(pstCmdArg);
    DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);

    pFile = Debugfopen(pstCmdArg->pcArgv[2], HDMI_O_RDWR, 0);
    if (pFile == HI_NULL)
    {
        HDMI_DBG_ERR("open file %s fail!\n",pstCmdArg->pcArgv[2]);
        return HI_FAILURE;
    }

    pu8Buf = (HI_U8 *)HDMI_VMALLOC(DEBUG_MAX_EDIDBUF_SIZE);
    if (pu8Buf)
    {
        HDMI_MEMSET(pstDbgEdid, 0, sizeof(HDMI_DEBUG_EDID_S));

        s32Len = Debugfread(pu8Buf, DEBUG_MAX_EDIDBUF_SIZE, pFile);
        if (s32Len <= 0)
        {
            HDMI_DBG_PRINT("read file size = %d!\n", s32Len);
        }
        else
        {
            s32Len = DebugStr2Hex(pstDbgEdid->au8Data, HDMI_EDID_TOTAL_SIZE, pu8Buf, (HI_U32)s32Len);
            if (s32Len < 0)
            {
                HDMI_DBG_ERR("string convert to hex error!\n");
            }
            else
            {
                pstDbgEdid->bDataValid = HI_TRUE;
                pstDbgEdid->s32Len     += s32Len;
                s32Ret = DRV_HDMI_EdidUpdate(&pstHdmiDev->stEdidInfo, HDMI_EDID_UPDATE_DEBUG);
            }
        }
        HDMI_VFREE(pu8Buf);
    }
    else
    {
        HDMI_DBG_ERR("vmalloc error!\n");
    }
    Debugfclose(pFile);

    if (s32Len < 0)
    {
        HDMI_DBG_ERR("error hex raw data format!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 DebugEdidFromCmd(HDMI_DEVICE_S *pstHdmiDev, HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32               s32Ret = HI_FAILURE;
    HDMI_DEBUG_EDID_S   *pstDbgEdid = &s_stDebugEdid;

	DEBUG_NULL_CHK(pstHdmiDev);
	DEBUG_NULL_CHK(pstCmdArg);
    DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);

    HDMI_DBG_ERR("pstDbgEdid->s32Len=%d !\n", pstDbgEdid->s32Len);
    s32Ret = DebugStr2Hex(pstDbgEdid->au8Data + pstDbgEdid->s32Len,
                            HDMI_EDID_TOTAL_SIZE-pstDbgEdid->s32Len,
                            pstCmdArg->pcArgv[2],
                            pstCmdArg->u32RemainLen);
    if (s32Ret < 0)
    {
        HDMI_DBG_ERR("error hex raw data format!\n");
        return HI_FAILURE;
    }
    else
    {
        pstDbgEdid->bDataValid = HI_FALSE;
        pstDbgEdid->s32Len     += s32Ret;
        HDMI_DBG_ERR("pstDbgEdid->s32Len=%d !\n", pstDbgEdid->s32Len);
    }

    return HI_SUCCESS;
}

static HI_S32 DebugEdid(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
	HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_S32              i = 0;
    HI_U8               *pu8Buf = HI_NULL;
    HDMI_DEBUG_EDID_S   *pstDbgEdid = &s_stDebugEdid;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 3)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);
    DEBUG_NULL_CHK(pstCmdArg->pcArgv[1]);

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"s")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        HDMI_MEMSET(pstDbgEdid,0,sizeof(HDMI_DEBUG_EDID_S));
        s32Ret = DRV_HDMI_EdidUpdate(&pstHdmiDev->stEdidInfo,HDMI_EDID_UPDATE_SINK);
        if (s32Ret != HI_SUCCESS)
        {
            HDMI_DBG_ERR("update edid from sink fail!Make sure cable connect!\n");
        }
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"l")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        s32Ret = DebugEdidFromCmd(pstHdmiDev, pstCmdArg);
        DEBUG_FAILURE_RET_CHK(s32Ret);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"e")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {

        s32Ret = DebugEdidFromCmd(pstHdmiDev, pstCmdArg);
        DEBUG_FAILURE_RET_CHK(s32Ret);
        s32Ret = DRV_HDMI_EdidUpdate(&pstHdmiDev->stEdidInfo,HDMI_EDID_UPDATE_DEBUG);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"f")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);
        s32Ret = DebugEdidFromFile(pstHdmiDev, pstCmdArg);
        DEBUG_FAILURE_RET_CHK(s32Ret);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_DBG_PRINT(" edid load %s! \n",s32Ret<0 ? STR_FAIL : STR_SUCC);
    HDMI_DBG_PRINT("[Edid Data]:");
    pu8Buf= (HI_U8 *)HDMI_VMALLOC(HDMI_EDID_TOTAL_SIZE);
    if (pu8Buf)
    {
        s32Ret = DRV_HDMI_EdidRawGet(&pstHdmiDev->stEdidInfo, pu8Buf, HDMI_EDID_TOTAL_SIZE);

        for (i = 0; (i < s32Ret) && (i < HDMI_EDID_TOTAL_SIZE); i++)
        {
            if (!(i%16)){HDMI_DBG_PRINT("\n");}
            HDMI_DBG_PRINT(" %02x",pu8Buf[i]);
        }

        HDMI_DBG_PRINT("\n\n");
        HDMI_VFREE(pu8Buf);
    }
    else
    {
        HDMI_DBG_ERR("vmalloc fail!\n");
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo edid argv1 argv2 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: edid operation mode as below\n");
    HDMI_DBG_PRINT("%10s 0(s)  --finish using debug edid and read from sink.\n","");
    HDMI_DBG_PRINT("%10s 1(l)  --read debug edid from argv2(a hex-string-line).\n","");
    HDMI_DBG_PRINT("%10s 2(el) --read debug edid from argv2(a hex-string-line),then finish reading.\n","");
    HDMI_DBG_PRINT("%10s 3(f)  --read debug edid from argv2(a hex-string-file-path).\n","");
    HDMI_DBG_PRINT("[argv2  ]: hex-data string/filepath.You have to use at least 1 charater of 'SPACE|TAB|,|0x' between 2 hex-bytes.\n");
    HDMI_DBG_PRINT("[example]: echo edid s > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo edid l 0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo edid f /mnt/edid_skyworth_300m.txt > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugAvmute(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
	HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       DRV_HDMI_AVMuteSet(pstHdmiDev, HI_FALSE);
       HDMI_DBG_PRINT("\n avmute set OFF %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       DRV_HDMI_AVMuteSet(pstHdmiDev, HI_TRUE);
       HDMI_DBG_PRINT("\n avmute set ON %s! \n\n", STR_SUCC );
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo avmute argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--avmute off.\n"
                   "           1\t--avmute on.\n");
    HDMI_DBG_PRINT("[example]: echo avmute 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugCbar(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
	HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HI_BOOL         bEnable = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       bEnable = HI_FALSE;
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_COLOR_BAR,&bEnable);
       HDMI_DBG_PRINT("\n ColorBar is OFF %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       bEnable = HI_TRUE;
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_COLOR_BAR,&bEnable);
       HDMI_DBG_PRINT("\n ColorBar is ON %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo cbar argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--colorbar off.\n"
                   "           1\t--colorbar on.\n");
    HDMI_DBG_PRINT("[example]: echo cbar 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

#ifdef HDMI_SCDC_SUPPORT
static HI_S32 DebugScdc(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
	HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_SCDC_STATUS_S  stScdcStatus = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);
    HDMI_MEMSET(&stScdcStatus, 0, sizeof(HDMI_SCDC_STATUS_S));

    if (pstCmdArg->u32Argc > 4 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       stScdcStatus.bSourceScrambleOn = HI_FALSE;
       stScdcStatus.bSinkScrambleOn = HI_FALSE;
       stScdcStatus.u8TmdsBitClkRatio = 10;
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
       HDMI_MSLEEP(90);
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);
       HDMI_MEMSET(&stScdcStatus,0,sizeof(stScdcStatus));

       HDMI_MSLEEP(3000);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
       HDMI_DBG_PRINT("\n scdc set OFF %s! \n\n",
                    (stScdcStatus.bSourceScrambleOn == HI_FALSE) &&
                    (stScdcStatus.bSinkScrambleOn == HI_FALSE) &&
                    (stScdcStatus.u8TmdsBitClkRatio == 10) ? STR_SUCC : STR_FAIL);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       stScdcStatus.bSourceScrambleOn = HI_TRUE;
       stScdcStatus.bSinkScrambleOn = HI_TRUE;
       stScdcStatus.u8TmdsBitClkRatio = 40;
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
       HDMI_MSLEEP(90);
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);

       HDMI_MEMSET(&stScdcStatus,0,sizeof(stScdcStatus));
       HDMI_MSLEEP(3000);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);

       HDMI_DBG_PRINT("\n scdc set ON %s! \n\n",
                    (stScdcStatus.bSourceScrambleOn == HI_TRUE) &&
                    (stScdcStatus.bSinkScrambleOn == HI_TRUE) &&
                    (stScdcStatus.u8TmdsBitClkRatio == 40) ? STR_SUCC : STR_FAIL);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
    }
#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        HI_CHAR *pcChar = HI_NULL;

        if (pstCmdArg->u32Argc < 4)
        {
            goto usage_error;
        }

        stScdcStatus.bSourceScrambleOn      = HI_TRUE;
        stScdcStatus.bSinkScrambleOn        = HI_TRUE;
        stScdcStatus.u8TmdsBitClkRatio      = 40;

        pcChar = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcChar);
        stScdcStatus.u32ScrambleInterval    = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);

        pcChar = pstCmdArg->pcArgv[3];
        DEBUG_NULL_CHK(pcChar);
        stScdcStatus.u32ScrambleTimeout     = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);
        stScdcStatus.bSinkReadQuest         = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);

    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4"))
    {
        HI_CHAR *pcChar = HI_NULL;

        if (pstCmdArg->u32Argc < 4)
        {
            goto usage_error;
        }

        stScdcStatus.bSourceScrambleOn      = HI_TRUE;
        stScdcStatus.bSinkScrambleOn        = HI_TRUE;
        stScdcStatus.u8TmdsBitClkRatio      = 10;

        pcChar = pstCmdArg->pcArgv[2];
        stScdcStatus.u32ScrambleInterval    = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);
        pcChar = pstCmdArg->pcArgv[3];
        stScdcStatus.u32ScrambleTimeout     = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);
        stScdcStatus.bSinkReadQuest         = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
    }
#endif
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }
    HDMI_DBG_PRINT("\n scdc get bSourceScrambleOn[%d] \n"
                       "            bSinkScrambleOn[%d] \n"
                       "          u8TmdsBitClkRatio[%d] \n\n",
                                    stScdcStatus.bSourceScrambleOn,
                                    stScdcStatus.bSinkScrambleOn,
                                    stScdcStatus.u8TmdsBitClkRatio);
    return HI_SUCCESS;

usage_error:
#if  defined (HDMI_SUPPORT_LOGIC_HISIV100)
    HDMI_DBG_PRINT("[Usage  ]: echo scdc argv1 [argv2] [argv3] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--scdc off.\n"
                   "           1\t--scdc on.\n"
                   "           2\t--scdc status get.\n"
                   "           3\t--scdc on,40x,cfg interval & timeout.\n"
                   "           4\t--scdc on.10x,cfg interval & timeout.\n");

    HDMI_DBG_PRINT("[argv2  ]: interval.optional,in ms,range[20,200].\n");
    HDMI_DBG_PRINT("[argv3  ]: timeout.optional,in ms,range[200,1000].\n");
    HDMI_DBG_PRINT("[example]: echo scdc 1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo scdc 3 25 300 > /proc/msp/hdmi0 \n");
#else
    HDMI_DBG_PRINT("[Usage  ]: echo scdc argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--scdc off.\n"
                   "           1\t--scdc on.\n"
                   "           2\t--scdc status get.\n");

    HDMI_DBG_PRINT("[example]: echo scdc 1 > /proc/msp/hdmi0 \n");
#endif
    return HI_FAILURE;
}
#endif

static HI_S32 DebugDdc(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{

    HI_U32          u32DdcFreq      = 0;
    HI_U32          i               = 0;
	HDMI_DEVICE_S   *pstHdmiDev     = HI_NULL;
    HI_CHAR         *pcStr          = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    pcStr = pstCmdArg->pcArgv[1];


    u32DdcFreq = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);

    if (u32DdcFreq >= HDMI_ARRAY_SIZE(s_astDdcFreq))
    {
        goto usage_error;
    }

    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DDC_FREQ,&s_astDdcFreq[u32DdcFreq].u32DdcRegCfg);
    HDMI_DBG_PRINT("\n ddc frequency set %s KHz %s! \n\n",s_astDdcFreq[u32DdcFreq].pstReadValue,STR_SUCC);


    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo ddc argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: ddc frequency [0,%u]\n",HDMI_ARRAY_SIZE(s_astDdcFreq)-1);
    for (i = 0;i < HDMI_ARRAY_SIZE(s_astDdcFreq);i++)
    {
        HDMI_DBG_PRINT("           %2u -- %3u KHz (real %s KHz,Reg=0x%02x)\n",
            i,
            s_astDdcFreq[i].u32ApproximateValue,
            s_astDdcFreq[i].pstReadValue,
            s_astDdcFreq[i].u32DdcRegCfg);
    }
    HDMI_DBG_PRINT("[example]: echo ddc 1 > /proc/msp/hdmi0\n");

    return HI_FAILURE;
}

static HI_S32 DebugHdmimode(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
	HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        HDMI_HAL_CALL(HAL_HDMI_TmdsModeSet, pstHdmiDev->pstHdmiHal,HDMI_TMDS_MODE_DVI);
        HDMI_DBG_PRINT("\n hdmi tmds mode set DVI %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        HDMI_HAL_CALL(HAL_HDMI_TmdsModeSet, pstHdmiDev->pstHdmiHal,HDMI_TMDS_MODE_HDMI_1_4);
        HDMI_DBG_PRINT("\n hdmi tmds mode set HDMI1.4 %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        HDMI_HAL_CALL(HAL_HDMI_TmdsModeSet, pstHdmiDev->pstHdmiHal,HDMI_TMDS_MODE_HDMI_2_0);
        HDMI_DBG_PRINT("\n hdmi tmds mode set HDMI2.0 %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo hdmimode argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--DVI.\n"
                   "           1\t--HDMI1.4.\n"
                   "           2\t--HDMI2.0.\n");
    HDMI_DBG_PRINT("[example]: echo hdmimode 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugOutclrspace(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
	HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    HI_U32              u32OldMode = 0;


    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAppAttr.enOutColorSpace;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_RGB;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_YCbCr422;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_YCbCr444;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_YCbCr420;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n output colorspace mode %d->%d %s! \n\n",
                    u32OldMode,
                    stAttr.stAppAttr.enOutColorSpace,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo outclrspace argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--RGB.\n"
                   "           1\t--YUV422.\n"
                   "           2\t--YUV444.\n"
                   "           3\t--YUV420.\n");
    HDMI_DBG_PRINT("[example]: echo outclrspace 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugDeepclr(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
	HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    HI_U32              u32OldMode = 0;


    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAppAttr.enDeepColorMode;

    if (stAttr.stAppAttr.enOutColorSpace == HDMI_COLORSPACE_YCbCr422)
    {
        HDMI_DBG_ERR("current output colorspace YUV422 not support deepcolor set!Force set\n");
        //return HI_FAILURE;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stAppAttr.enDeepColorMode = HDMI_DEEP_COLOR_24BIT;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stAppAttr.enDeepColorMode = HDMI_DEEP_COLOR_30BIT;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stAttr.stAppAttr.enDeepColorMode = HDMI_DEEP_COLOR_36BIT;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n deppcolor colorspace mode %d->%d %s! \n\n",
                    u32OldMode,
                    stAttr.stAppAttr.enDeepColorMode,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo deepclr argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--08 bit.\n"
                   "           1\t--10 bit.\n"
                   "           2\t--12 bit.\n");
    HDMI_DBG_PRINT("[example]: echo deepclr 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugDither(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
	HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_VIDEO_DITHER_E enDitherMode = HDMI_VIDEO_DITHER_DISALBE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    enDitherMode = HDMI_VIDEO_DITHER_DISALBE;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       enDitherMode = HDMI_VIDEO_DITHER_DISALBE;

       HDMI_DBG_PRINT("\n dither is disable %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        enDitherMode = HDMI_VIDEO_DITHER_10_8;
        HDMI_DBG_PRINT("\n dither is enable 10_08 %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        enDitherMode = HDMI_VIDEO_DITHER_12_8;
        HDMI_DBG_PRINT("\n dither is enable 12_08 %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        enDitherMode = HDMI_VIDEO_DITHER_12_10;
        HDMI_DBG_PRINT("\n dither is enable 12_10 %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DITHER,&enDitherMode);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo dither argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--dither disable.\n"
                   "           1\t--10_08.\n"
                   "           2\t--12_08.\n"
                   "           3\t--12_10.\n");
    HDMI_DBG_PRINT("[example]: echo dither 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugAuthenticate(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       pstHdmiDev->stAttr.stAppAttr.bAuthMode = HI_FALSE;
       HDMI_DBG_PRINT("\n aut disable %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       pstHdmiDev->stAttr.stAppAttr.bAuthMode = HI_TRUE;
       HDMI_DBG_PRINT("\n aut enable %s! \n\n", STR_SUCC );
    }
    else
    {
        HDMI_DBG_PRINT("\n aut status %d! \n\n", pstHdmiDev->stAttr.stAppAttr.bAuthMode);
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo aut argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--aut off.\n"
                   "           1\t--aut on.\n"
                   "           2\t--aut status get.\n");
    HDMI_DBG_PRINT("[example]: echo aut 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;

}

static HI_S32 DebugCmd(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_BLACK_FRAME_INFO_S stBlackInfo;
    HI_U32               u32Data    = 0;
    HI_CHAR             *pcStr      = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    stBlackInfo.inBitDepth = pstHdmiDev->stAttr.stVOAttr.enInBitDepth;
    stBlackInfo.inColorSpace = pstHdmiDev->stAttr.stVOAttr.enInColorSpace;
    stBlackInfo.inQuantization = (stBlackInfo.inColorSpace == HDMI_COLORSPACE_RGB) ? \
    pstHdmiDev->stAttr.stVOAttr.enRGBQuantization : pstHdmiDev->stAttr.stVOAttr.enYCCQuantization;

    if (   (pstCmdArg->u32Argc < 2)
        || (pstCmdArg->u32Argc > 3))
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "0"))
    {
        DRV_HDMI_Stop(pstHdmiDev);
        HDMI_DBG_PRINT("\n HDMI stop %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "1"))
    {
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT("\n HDMI start %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "2"))
    {
        stBlackInfo.bBlacEnable = HI_TRUE;
        HDMI_HAL_CALL(HAL_HDMI_BlackDataSet, pstHdmiDev->pstHdmiHal, &stBlackInfo);
        HDMI_DBG_PRINT("\n black frame enable %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "3"))
    {
        stBlackInfo.bBlacEnable = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_BlackDataSet, pstHdmiDev->pstHdmiHal, &stBlackInfo);
        HDMI_DBG_PRINT("\n black frame disable %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "4"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        pcStr   = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);
        u32Data = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
        HDMI_DBG_PRINT("\n PCB trace len old(%d)->new(%d)! \n\n", pstHdmiDev->stModParam.u32TraceLength, u32Data);

        pstHdmiDev->stModParam.u32TraceLength = u32Data;
    }
    else
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo cmd argv1 argv2(optional) > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--hdmi stop.\n"
                   "           1\t--hdmi start.\n"
                   "           2\t--black frame enable.\n"
                   "           3\t--black frame disable.\n"
                   "           4\t--PCB length set (must set argv2).\n");
    HDMI_DBG_PRINT("[example]: echo cmd 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

#ifdef HDMI_HDR_SUPPORT
static HI_S32 DebugHdr(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret      = HI_FAILURE;
	HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    HI_U32              u32OldMode  = 0;
    HDMI_HDR_ATTR_S     *pstHdrAttr = HI_NULL;
    HDMI_HDR_INFO_S     *pstHdrInfo = HI_NULL;
    HI_U32               u32Time    = 0;
    HI_CHAR             *pcStr      = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2 || pstCmdArg->pcArgv[1] == HI_NULL)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }
    pstHdrAttr = &(pstHdmiDev->stAttr.stHdrAttr);
    pstHdrInfo = &(pstHdmiDev->stHdrInfo);

    u32OldMode = pstHdrAttr->enUserHdrMode;

    if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "0"))
    {
        /* HDR mode set. */
        if (IS_STR_EQUAL(pstCmdArg->pcArgv[2], "1"))
        {
            pstHdrAttr->enUserHdrMode = HDMI_HDR_USERMODE_HDR10;
        }
        else if (IS_STR_EQUAL(pstCmdArg->pcArgv[2], "2"))
        {
            pstHdrAttr->enUserHdrMode = HDMI_HDR_USERMODE_DOLBY;
        }
        else
        {
            pstHdrAttr->enUserHdrMode = HDMI_HDR_USERMODE_SDR;
        }

        s32Ret = DRV_HDMI_AttrGet(pstHdmiDev, &stAttr);
        DEBUG_FAILURE_RET_CHK(s32Ret);

    	DRV_HDMI_Stop(pstHdmiDev);
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
    	DRV_HDMI_Start(pstHdmiDev);

        HDMI_DBG_PRINT("\n user hdr mode change %d->%d %s! \n\n",
                        u32OldMode,
                        stAttr.stHdrAttr.enUserHdrMode,
                        s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "1"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        if(IS_STR_EQUAL(pstCmdArg->pcArgv[2], "1"))
        {
            pstHdrInfo->enHdrDebugMode = HDMI_HDR_DEBUG_MODE_OE;
        }
        else if(IS_STR_EQUAL(pstCmdArg->pcArgv[2], "2"))
        {
            pstHdrInfo->enHdrDebugMode = HDMI_HDR_DEBUG_MODE_AVMUTE;
        }
        else
        {
            pstHdrInfo->enHdrDebugMode = HDMI_HDR_DEBUG_MODE_NONE;
        }

        HDMI_DBG_PRINT("\n debug mode set %d! \n\n", pstHdrInfo->enHdrDebugMode);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "2"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        pcStr   = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);

        u32Time = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
        if(1 > u32Time)
        {
            goto usage_error;
        }

        HDMI_DBG_PRINT("\n debug OE delay time change %d->%d! \n\n", pstHdrInfo->stHdrModeChnTimer.u32Time, u32Time);
        pstHdrInfo->stHdrModeChnTimer.u32Time = u32Time;
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "3"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        pcStr   = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);

        u32Time = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
        if(1 > u32Time)
        {
            goto usage_error;
        }
        HDMI_DBG_PRINT("\n debug Zero DRM Infoframe send time change %d->%d! \n\n", pstHdrInfo->stZeroDrmIfTimer.u32Time, u32Time);
        pstHdrInfo->stZeroDrmIfTimer.u32Time = u32Time;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo hdr argv1 argv2 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: HDR debug command.\n");
    HDMI_DBG_PRINT("           0\t--debug HDR mode set (argv2 = 0-SDR, 1-HDR10, 2-Dolby).\n"
                   "           1\t--debug mode set when the HDR mode change to HDR10 (argv2 = 0-debug disable, 1-OE, 2-AVMUTE).\n"
                   "           2\t--debug mode delay time(1~10000ms, default 100ms).\n"
                   "           3\t--Zero DRM Infoframe send time(1-10000ms, default 2000ms).\n");

    HDMI_DBG_PRINT("[argv2  ]: Command param.\n");
    HDMI_DBG_PRINT("[example]: echo hdr 0 1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo hdr 1 2 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo hdr 2 500 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo hdr 3 3000 > /proc/msp/hdmi0\n");

    return HI_FAILURE;
}

#endif


#ifdef HDMI_FRL_SUPPORT

#ifdef HDMI_SYS_NOHIGH_TIMERS
static HI_U32 u32TimerTest = 0;

HI_VOID DebugTimerIsr(HI_VOID *pParam)
{
    u32TimerTest++;

    if (u32TimerTest <= 10)
    {
        HAL_Timer_Start();
    }
    else
    {
        HAL_Timer_Stop();
    }

    return ;
}
#endif

extern HI_S32 FrlLMTableGet(HI_VOID);

static HI_S32 DebugFrl(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    TIMER_CONFIG_S       stConfig   = {0};
    HI_S32               s32Ret     = HI_SUCCESS;
    HDMI_FRL_INFO_S             *pstFrlInfo  = HI_NULL;
    HDMI_FRL_STATE_MACH_INFO_S  *pstMachInfo = HI_NULL;
    HI_U32                      u32Data      = 0;
    HI_CHAR                     *pcStr       = HI_NULL;
    HDMI_FRL_DEBUG_S            stDebug      = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);

    pstFrlInfo = &pstHdmiDev->stFrlInfo;
    pstMachInfo = &pstFrlInfo->stStateMachInfo;

    HDMI_MEMSET(&stConfig, 0, sizeof(stConfig));

    if (pstCmdArg->u32Argc < 3 || pstCmdArg->pcArgv[1] == HI_NULL)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    pcStr = pstCmdArg->pcArgv[2];
    DEBUG_NULL_CHK(pcStr);
    u32Data = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "0"))
    {
        if (u32Data > 1)
        {
            goto usage_error;
        }

        HDMI_DBG_PRINT("Set FRL machine old(%s)->new(%s).\n", \
                        (HI_TRUE == pstMachInfo->bStartMach) ? "start" : "stop", \
                        (1 == u32Data) ? "start" : "stop");

        pstMachInfo->bStartMach = (1 == u32Data) ? HI_TRUE : HI_FALSE;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "1"))
    {
        if(u32Data >= HDMI_FRL_RATE_SELECT_BUTT)
        {
            goto usage_error;
        }
        pstFrlInfo->enRateSelect = (HDMI_FRL_RATE_SELECT_E)u32Data;
        HDMI_DBG_PRINT("Set FRL rete strategy %s.\n", (HDMI_FRL_RATE_SELECT_BIG == u32Data) ? "BIG" : "LITTLE");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "2"))
    {
        if(u32Data >= HDMI_FRL_STRATEGY_MODE_BUTT)
        {
            goto usage_error;
        }

        pstFrlInfo->enStrategyMode = (HDMI_FRL_STRATEGY_MODE_E)u32Data;
        HDMI_DBG_PRINT("Set 2.1 strategy %d.\n", u32Data);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "3"))
    {
        if(u32Data == 0)
        {
            goto usage_error;
        }
        pstFrlInfo->u32MaxFailTimes = u32Data;
        HDMI_DBG_PRINT("Set max training fail times: %d.\n", u32Data);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "4"))
    {
        if(u32Data == 0)
        {
            goto usage_error;
        }
        pstMachInfo->u32WaitHandleMs = u32Data;
        HDMI_DBG_PRINT("Set wait handle time: %d.\n", u32Data);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "5"))
    {
        if(u32Data == 0)
        {
            goto usage_error;
        }
        pstMachInfo->u32WaitReadyMs = u32Data;
        HDMI_DBG_PRINT("Set wait ready time: %d.\n", u32Data);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "6"))
    {
        if(u32Data == 0)
        {
            goto usage_error;
        }
        pstMachInfo->u32WaitRetrainMs = u32Data;
        HDMI_DBG_PRINT("Set wait retrain time: %d.\n", u32Data);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "7"))
    {
        if(u32Data >= HDMI_FRL_TRAIN_SEL_BUTT)
        {
            goto usage_error;
        }
        pstFrlInfo->enTrainSel = (HDMI_FRL_TRAIN_SEL_E)u32Data;
        DRV_HDMI_Stop(pstHdmiDev);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT("Set training : %d.\n", (HDMI_FRL_TRAIN_SEL_SW == u32Data) ? "software" : "hardware");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "8"))
    {
        stDebug.enHdmiMode = (u32Data == 1) ? HDMI_FRL_MODE_FRL : HDMI_FRL_MODE_TMDS;
        if (stDebug.enHdmiMode == HDMI_FRL_MODE_FRL)
        {
            if (pstCmdArg->u32Argc < 4)
            {
                goto usage_error;
            }

            pcStr = pstCmdArg->pcArgv[3]; // RATE
            DEBUG_NULL_CHK(pcStr);
            u32Data = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
            stDebug.enRate = (u32Data >= FRL_WORK_MODE_4L12G) ? FRL_WORK_MODE_4L12G : u32Data;

            pcStr = pstCmdArg->pcArgv[4]; // SWDFM
            DEBUG_NULL_CHK(pcStr);
            u32Data = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
            stDebug.bSWDFM = (u32Data >= 1) ? HI_TRUE : HI_FALSE;
        }

        s32Ret = DRV_HDMI_FrlModeChange(pstHdmiDev->u32HdmiDevId, &stDebug);
        HDMI_DBG_PRINT("Frl debug: %s.\n", (HI_SUCCESS == s32Ret) ? STR_SUCC : STR_FAIL);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "9"))
    {
        pstFrlInfo->u32Bypass = (u32Data & 0x3);
        HDMI_DBG_PRINT("Bypass: 0x%x.\n", pstFrlInfo->u32Bypass);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "10"))
    {
        pstHdmiDev->stEdidInfo.stCapability.u8MaxFrlRate = (u32Data >= MAX_FRL_RATE) ? MAX_FRL_RATE : u32Data;
        HDMI_DBG_PRINT("Set sink caps max FRL rate: %d.\n", pstHdmiDev->stEdidInfo.stCapability.u8MaxFrlRate);
    }
#ifdef HDMI_SYS_NOHIGH_TIMERS
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "11"))
    {
        u32TimerTest = 0;
        stConfig.u32StartTime = HDMI_OSAL_GetTimeInMs();
        stConfig.pIsr         = DebugTimerIsr;
        stConfig.u32DelayMs   = 2;

        HAL_Timer_DeInit();
        HAL_Timer_Init(&stConfig);
        HAL_Timer_Start();

        HDMI_MSLEEP(50);
        HDMI_DBG_PRINT("Timer test: %s.\n", (u32TimerTest > 10) ? STR_SUCC : STR_FAIL);
    }
#endif
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "12"))
    {
        FrlLMTableGet();
        HDMI_DBG_PRINT("Get LM table success.\n");
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo frl argv1 argv2 argv3 argv4 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: FRL debug command.\n");
    HDMI_DBG_PRINT("           0\t--Train machine start [argv2: 0--stop, 1--start].\n"
                   "           1\t--FRL rate strategy   [argv2: 0--little, 1--big]\n"
                   "           2\t--HDMI2.1 strategy    [argv2: 0--(>600M), 1--(>340M), 2--(p-format)])\n");
    HDMI_DBG_PRINT("           3\t--Max train fail times[argv2: >0].\n"
                   "           4\t--Wait handle time    [argv2: >0]\n"
                   "           5\t--Wait ready time     [argv2: >0]\n"
                   "           6\t--Wait retrain time   [argv2: >0]\n"
                   "           7\t--Train select        [argv2: 0--software, 1--hardware]\n");
    HDMI_DBG_PRINT("           8\t--Mode change         [argv2:(TMDS/FRL) argv3:(Rate) argv4:(SWDFM)\n");
    HDMI_DBG_PRINT("           9\t--Train exception bp  [argv2: b0(readychk) b1(resultchk)]\n");
    HDMI_DBG_PRINT("          10\t--Sink max frl rate   [argv2: max frl rate(maximum 6)]\n");
#ifdef HDMI_SYS_NOHIGH_TIMERS
    HDMI_DBG_PRINT("          11\t--Timer test          [argv2: 0--unused]\n");
#endif
    HDMI_DBG_PRINT("          12\t--LM table get        [argv2: 0--unused]\n");

    return HI_FAILURE;
}

#endif

const static HDMI_DEBUG_CMD_INFO_S s_stCmdTable[] = {
    /***name**** short name *** func ************** help info **********************/
    {"help"     ,   "h",    DebugPrintHelp      ,  "print these help info."                             },
    {"thread"   ,   "t",    DebugThread         ,  "thread status set on/off."                          },
    {"oe"       ,   "o",    DebugOe             ,  "phyoutput enable(oe) set on/off."                   },
    {"event"    ,   "e" ,   DebugEvent          ,  "hardware event [16,25] simulate."                   },
    {"edid"     ,   "ed",   DebugEdid           ,  "edid raw data load."                                },
    {"avmute"   ,   "a",    DebugAvmute         ,  "audio & video mute set on/off."                     },
    {"cbar"     ,   "c",    DebugCbar           ,  "colorbar set on/off."                               },
#ifdef HDMI_SCDC_SUPPORT
    {"scdc"     ,   "sc",   DebugScdc           ,  "scdc set on/off."                                   },
#endif
    {"ddc"      ,   "dd",   DebugDdc            ,  "ddc frequency set in range [0,11]."                 },
    {"hdmimode" ,   "m" ,   DebugHdmimode       ,  "hdmi tmds mode set dvi/1.4/2.0."                    },
    {"outclrspace" ,"oc",   DebugOutclrspace    ,  "output colorspace mode set rgb/yuv422/yuv444/yuv420."},
    {"deepclr"  ,   "d",    DebugDeepclr        ,  "output color depth  set 08/10/12bit."               },
    {"dither"   ,   "di",   DebugDither         ,  "dither set on/off."                                 },
    {"aut"      ,   "au",   DebugAuthenticate   ,  "authentication mode set on/off."                    },
    {"cmd"      ,   "cmd",  DebugCmd            ,  "cmd set ."                                          },
#ifdef HDMI_HDR_SUPPORT
    {"hdr"      ,   "hm",   DebugHdr            ,  "hdr debug info set."                                },
#endif
#ifdef HDMI_FRL_SUPPORT
    {"frl"      ,   "fr",   DebugFrl            ,  "FRL Training test."                                 },
#endif
};

static HI_S32 DebugPrintHelp(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_U32 i = 0;

    DEBUG_NULL_CHK(pstCmdArg);

    for (i=0 ; i < HDMI_ARRAY_SIZE(s_stCmdTable) ; i++)
    {
        if (s_stCmdTable[i].pCommentHelp && s_stCmdTable[i].pcName)
        {
            HDMI_DBG_PRINT("    %02d. %-20s",i,s_stCmdTable[i].pcName);
            HDMI_DBG_PRINT("--[%-2s]%s\n",s_stCmdTable[i].pcShortName,s_stCmdTable[i].pCommentHelp);
        }
        else
        {
            HDMI_DBG_ERR("s_stCmdTable[%d].pCommentHelp or pcName is null!\n");
        }
    }

    HDMI_DBG_PRINT("\n");
    HDMI_DBG_PRINT("    You can use 'echo cmd argv... > /proc/msp/hdmi0' execute a debug command.\n"
                   "    You can use 'echo cmd > /proc/msp/hdmi0' for more details about each command.\n"
                   "    Here,'cmd' refers to NO./complete-name/short-name above.\n");
    return HI_SUCCESS;
}


static HI_S32 DebugCmdHandle(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_U32          i = 0,u32CmdNum = 0;
    HI_CHAR         *pcStr = pstCmdArg->pcArgv[0];

    DEBUG_NULL_CHK(pstCmdArg);

    if (pstCmdArg->u32Argc > 0)
    {
        u32CmdNum = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);

        for (i=0 ; i < HDMI_ARRAY_SIZE(s_stCmdTable) ; i++)
        {
            if ( s_stCmdTable[i].pcName )
            {
                if( ((u32CmdNum == i) && (*pcStr == '\0') )
                   || IS_STR_EQUAL(s_stCmdTable[i].pcName,pstCmdArg->pcArgv[0])
                   || IS_STR_EQUAL(s_stCmdTable[i].pcShortName,pstCmdArg->pcArgv[0]) )
                {

                    if (s_stCmdTable[i].pfnCmdFunc)
                    {
                        if(s_stCmdTable[i].pfnCmdFunc(pstCmdArg))
                        {
                            //goto error_help;
                        }
                    }
                    else
                    {
                        HDMI_DBG_ERR("s_stCmdTable[%d].pfnCmdFunc null\n",i);
                        goto error_help;
                    }
                    break;
                }

            }
            else
            {
                HDMI_DBG_ERR("s_stCmdTable[%d].pcName null\n",i);
                goto error_help;
            }

        }
    }

    if ( i == HDMI_ARRAY_SIZE(s_stCmdTable) )
    {
        goto error_help;
    }

    return HI_SUCCESS;

error_help:
    DebugPrintHelp(pstCmdArg);

    return HI_FAILURE;
}

static HI_S32 DebugCmdLineParse(HI_CHAR *pcCmdStr,HI_U32 u32Len,
                                HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
	HI_U32      i = 0;
	HI_U32      u32TmpArgc = 0;
	HI_CHAR     *pTmpStr = NULL;

	if (pcCmdStr == HI_NULL
        || pstCmdArg == HI_NULL
        || u32Len == 0
        || u32Len >= DEBUG_MAX_CMD_CHAR_NUM)
    {
        HDMI_DBG_ERR("invalid param!\n");
    	return HI_FAILURE;
    }
	else
    {
    	pTmpStr = pcCmdStr;
    }

	pstCmdArg->u32Argc = 0;
	for (i = 0; i < DEBUG_MAX_ARGV_NUM; i++)
    {
    	pstCmdArg->pcArgv[i] = HI_NULL;
    }

	if ( (*pTmpStr != DEBUG_CHAR_SPACE) && (*pTmpStr != DEBUG_CHAR_TAB) )
    {
    	pstCmdArg->pcArgv[u32TmpArgc] = pTmpStr;
    	u32TmpArgc++;
    	pTmpStr++;
    }

	for (i=0; i < u32Len; pTmpStr++,i++)
    {
    	if ( (*pTmpStr == DEBUG_CHAR_SPACE ) || (*pTmpStr == DEBUG_CHAR_TAB)  )
        {
            *pTmpStr = '\0';

        	if( (*(pTmpStr+1) != DEBUG_CHAR_SPACE) && (*(pTmpStr+1) != DEBUG_CHAR_TAB))
            {
            	pstCmdArg->pcArgv[u32TmpArgc] = pTmpStr + 1;
            	u32TmpArgc++;

            	if (u32TmpArgc == 3 )
                {
                    pstCmdArg->u32RemainLen = u32Len - i;
                    //break;
                }

            	if (u32TmpArgc >= DEBUG_MAX_ARGV_NUM)
                {
                    HDMI_DBG_PRINT(" too much argcs.max argc = %d\n",DEBUG_MAX_ARGV_NUM);
                    u32TmpArgc = DEBUG_MAX_ARGV_NUM;
                    break;
                }
            }

        }
    }

	pstCmdArg->u32Argc = u32TmpArgc;

	return HI_SUCCESS;
}


/********************** HDMI DEBUG public interface ************************************/

HI_S32 DRV_HDMI_DebugEdidRawRead(HDMI_EDID_UPDATE_MODE_E enMode,
                                        	HI_U8 *pau8Data,
                                        	HI_U32 u32Len)
{
    HDMI_DEBUG_EDID_S *pstDbgEdid = &s_stDebugEdid;

    if ( (HDMI_EDID_UPDATE_DEBUG != enMode)
        || (HI_FALSE == pstDbgEdid->bDataValid)
        || (HI_NULL == pau8Data)
        || (u32Len > HDMI_EDID_TOTAL_SIZE)    )
    {
        HDMI_ERR("Debug edid read fail,bDataValid=%d !\n",pstDbgEdid->bDataValid);
        return HI_FAILURE;
    }

    HDMI_MEMCPY(pau8Data,pstDbgEdid->au8Data,pstDbgEdid->s32Len);

    return pstDbgEdid->s32Len;
}

HI_S32 DRV_HDMI_DebugSourceWrite(HDMI_PROC_ENTRY *pFile, const char *pBuf,
                                                    HI_U32 u32Count,
                                                    HI_S64 *ps64Data)
{
    HI_S32                  s32Ret = HI_FAILURE;
	HI_U32                  u32Len = 0;
    HI_CHAR                 *pcTmpBuf = HI_NULL;
	HDMI_DEBUG_CMD_ARG_S    stCmdArg;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    HDMI_MEMSET(&stCmdArg, 0 , sizeof(HDMI_DEBUG_CMD_ARG_S));
    stCmdArg.enHdmiId  = HDMI_DEVICE_ID0;

    pstHdmiDev = GetHdmiDevice(stCmdArg.enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);

    pcTmpBuf = (HI_CHAR *)HDMI_VMALLOC(DEBUG_MAX_CMD_CHAR_NUM);
    if (!pcTmpBuf)
    {
        HDMI_DBG_ERR("kmalloc fail!\n");
        return EFAULT;
    }

    HDMI_MEMSET(pcTmpBuf, '\0' , DEBUG_MAX_CMD_CHAR_NUM);

	if(u32Count >= DEBUG_MAX_CMD_CHAR_NUM)
    {
        HDMI_DBG_ERR("\n Echo chars too long. u32Count=%lu,max cnt=%u\n", u32Count, DEBUG_MAX_CMD_CHAR_NUM);
    	goto error;
    }

    if(HDMI_COPY_FROM_USER(pcTmpBuf, pBuf, u32Count))
    {
        HDMI_DBG_ERR("\n copy from user failed. \n");
        goto error;
    }

    if (u32Count > 0)
    {
        /* end char '\n' set '\0' */
        pcTmpBuf[u32Count-1] = '\0';
        u32Len = u32Count - 1;
    }
    else
    {
        HDMI_DBG_ERR("ulCount=%d\n", u32Count);
        goto error;
    }

    s32Ret = DebugCmdLineParse(pcTmpBuf, u32Len, &stCmdArg);
    if (s32Ret != HI_SUCCESS)
    {
        HDMI_DBG_ERR("\n Cmd Parse fail! \n");
        goto error;
    }

    HDMI_MUTEX_LOCK(pstHdmiDev->stMutexProc);
    if(pstHdmiDev->u32UserCnt == 0 && pstHdmiDev->u32KernelCnt == 0)
    {
        HDMI_MUTEX_UNLOCK(pstHdmiDev->stMutexProc);
        HDMI_DBG_ERR("\n HDMI not open! \n");
        goto error;
    }

    s32Ret = DebugCmdHandle(&stCmdArg);
    HDMI_MUTEX_UNLOCK(pstHdmiDev->stMutexProc);

    if (s32Ret != HI_SUCCESS)
    {
        HDMI_DBG_ERR("\n Cmd handle error \n");
        goto error;
    }

    HDMI_VFREE(pcTmpBuf);
	return u32Count;

error:
    HDMI_VFREE(pcTmpBuf);
	return -EFAULT;

}

