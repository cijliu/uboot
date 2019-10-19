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

#include "hdmi_osal.h"
#include "hi_osal.h"
#include "hdmi_product_define.h"
/******************************************************************************/
/* operation functinos of kernel file                                         */
/******************************************************************************/

/** open a kernel file
**/
struct file* HDMI_OSAL_FileOpen(const HI_CHAR* pcFileName, OSAL_FILE_FLAG_S eFlags)
{
    struct file *pFile = NULL;

	if (HI_NULL == pcFileName)
	{
		return HI_NULL;
	}

    eFlags = HDMI_O_RDWR | HDMI_O_CREAT;

    pFile = HDMI_FILP_OPEN(pcFileName, eFlags, HDMI_FILE_MODE);

    return pFile;
}

/** close a kernel file
**/
HI_VOID HDMI_OSAL_FileClose(struct file * pFile)
{
    if (HI_NULL != pFile)
    {
        HDMI_FILP_CLOSE(pFile);
    }

	return;
}

/** read a kernel file
**/
HI_S32 HDMI_OSAL_FileRead(struct file * pFile,  HI_CHAR* pcBuf, HI_U32 u32Len)
{
	HI_S32 s32ReadLen = 0;

    if(HI_NULL == pcBuf)
    {
        return 0;
    }

    s32ReadLen = HDMI_FILP_READ(pcBuf, u32Len, pFile);

    return s32ReadLen;
}

/** write a kernel file
**/
HI_S32 HDMI_OSAL_FileWrite(struct file* pFile, HI_CHAR* pcBuf, HI_U32 u32Len)
{
    HI_S32 s32WriteLen = 0;

    if(HI_NULL == pcBuf)
    {
        return 0;
    }

    s32WriteLen = HDMI_FILP_FWRITE(pcBuf, u32Len, pFile);

    return s32WriteLen;
}

/******************************************************************************/
/* operation functinos of stream                                              */
/******************************************************************************/

/** snprintf pszSrc
**/
HI_S32 HDMI_OSAL_Snprintf(HI_CHAR *pszStr, HI_SIZE_T ulLen, const HI_CHAR *pszFormat, ...)
{
    HI_S32 s32Len;
    HDMI_VA_LIST stArgs = {0};

    HDMI_VA_START(stArgs, pszFormat);
    s32Len = HDMI_VSNPRINTF(pszStr, ulLen, pszFormat, stArgs);
    HDMI_VA_END(stArgs);

    return s32Len;
}

/******************************************************************************/
/* operation functinos of get system time                                     */
/******************************************************************************/
/** get system time in Ms
**/
HI_U32 HDMI_OSAL_GetTimeInMs(HI_VOID)
{
	HI_U64 u64SysTime = 0;

    u64SysTime = HDMI_DO_DIV64(HDMI_SCHED_LOCK(), 1000000);

    return (HI_U32)u64SysTime;
}

/** get system time in Us
**/
HI_U64 HDMI_OSAL_GetTimeInUs(HI_VOID)
{
	HI_U64 u64CurrUs = 0;
    HDMI_TIMEVAL_S CurrentTime;

    HDMI_GETTIMEOFDAY(&CurrentTime);
    u64CurrUs = ((HI_U64)CurrentTime.tv_sec*1000000 + CurrentTime.tv_usec);

	return u64CurrUs;
}

/******************************************************************************/
/* Gloabl Data                                                                */
/******************************************************************************/

/******************************************************************************/
/* Public Interface                                                           */
/******************************************************************************/


