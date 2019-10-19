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
#ifndef __HDMI_OSAL_H__
#define __HDMI_OSAL_H__

#include "hi_type.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "hi_osal.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/******************************************************************************/
/* define type for hdmi                                                       */
/******************************************************************************/
typedef unsigned long                       HI_SIZE_T;

/******************************************************************************/
/* Data Structures                                                            */
/******************************************************************************/
/* file flags */
typedef enum{
    OSAL_RDONLY = 0,    /* read file only */
    OSAL_WRONLY,        /* write file only */
    OSAL_RDWR,          /* read and write file */
    OSAL_BUTT
} OSAL_FILE_FLAG_S;

/******************************************************************************/
/* Gloabl Data                                                                */
/******************************************************************************/

/******************************************************************************/
/* Public Interface                                                           */
/******************************************************************************/
#define IS_STR_EQUAL(p1,p2) ({\
    ( p1 && p2 && (HDMI_STRLEN(p1)==HDMI_STRLEN(p2)) && (HDMI_STRNCMP(p1,p2,HDMI_STRLEN(p1))==0) ) ? HI_TRUE : HI_FALSE;\
})

/** open a kernel file
**/
struct file* HDMI_OSAL_FileOpen(const HI_CHAR* pcFileName, OSAL_FILE_FLAG_S eFlags);
/** close a kernel file
**/
HI_VOID HDMI_OSAL_FileClose(struct file * pFile);
/** read a kernel file
**/
HI_S32 HDMI_OSAL_FileRead(struct file * pFile,  HI_CHAR* pcBuf, HI_U32 u32Len);
/** write a kernel file
**/
HI_S32 HDMI_OSAL_FileWrite(struct file* pFile, HI_CHAR* pcBuf, HI_U32 u32Len);

/** snprintf pszSrc
**/
HI_S32 HDMI_OSAL_Snprintf(HI_CHAR *pszStr, HI_SIZE_T ulLen, const HI_CHAR *pszFormat, ...);

/** get system time in Ms
**/
HI_U32 HDMI_OSAL_GetTimeInMs(HI_VOID);

/** get system time in Us
**/
HI_U64 HDMI_OSAL_GetTimeInUs(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif


