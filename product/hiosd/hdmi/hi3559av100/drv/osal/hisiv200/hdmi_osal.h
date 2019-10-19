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
#ifndef HDMI_PRODUCT_HI3559A
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#endif

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/******************************************************************************/
/* define type for hdmi                                                       */
/******************************************************************************/
#ifndef HDMI_PRODUCT_HI3559A
#define OSAL_INIT_LOCK(lock)                        spin_lock_init(&lock)
#define OSAL_LOCK(lock)                             spin_lock(&lock)
#define OSAL_UNLOCK(lock)                           spin_unlock(&lock)
#define OSAL_SPINLOCK_T                             spinlock_t
#define OSAL_VSPRINTF(dstr, len, fstr, arg)         vsnprintf(dstr, len, fstr, arg)
#define OSAL_DO_DIV(time,len)                       do_div(time, len)

#define OSAL_MEMSET(vir, data, size)                memset(vir, data, size)
#define OSAL_MEMCPY(dest, src, size)                memcpy(dest, src, size)
#define OSAL_STRNCAT(dest, src, size)               strncat(dest, src, size)

#define OSAL_STRLEN(vir)                            strlen(vir)
#define OSAL_STRSTR(vir, str)                       strstr(vir, str)
#define OSAL_SMSTRTOUL(str, end, base)              simple_strtoul(str, end, base)

#define HDMI_MUTEX                                  struct semaphore

#define OSAL_STRLEN(p)                              ({p ? strlen(p) : 0 ;})
#define OSAL_STRNCPY(p1,p2,size)                    if(p1 && p2 && size){strncpy(p1,p2,size);}

#else
#define OSAL_INIT_LOCK(lock)                        osal_spin_lock_init(&lock)
#define OSAL_LOCK(lock)                             osal_spin_lock(&lock)
#define OSAL_UNLOCK(lock)                           osal_spin_unlock(&lock)
#define OSAL_SPINLOCK_T                             osal_spinlock_t
#define OSAL_VSPRINTF(dstr, len, fstr, arg)         osal_vsnprintf(dstr, len, fstr, arg)
#define OSAL_DO_DIV(time,len)                       osal_do_div(time, len)

#define OSAL_STRNCAT(dest, src, size)               osal_strncat(dest, src, size)
#define OSAL_MEMSET(vir, data, size)                osal_memset(vir, data, size)
#define OSAL_MEMCPY(dest, src, size)                osal_memcpy(dest, src, size)
#define OSAL_STRLEN(vir)                            osal_strlen(vir)
#define OSAL_STRSTR(vir, str)                       osal_strstr(vir, str)
#define OSAL_SMSTRTOUL(str, end, base)              osal_simple_strtoul(str, end, base)

#define HDMI_MUTEX                                  osal_semaphore_t
#define OSAL_STRLEN(p)                              ({p ? osal_strlen(p) : 0 ;})
#define OSAL_STRNCPY(p1,p2,size)                    if(p1 && p2 && size){osal_strncpy(p1,p2,size);}

#endif



#ifndef HDMI_PRODUCT_HI3559A
#define HDMI_MUTEX_LOCK(a)  \
do{\
    HI_S32 s32Ret = down_interruptible(&(a));\
    if (0 != s32Ret)\
        {HDMI_ERR("down_interruptible failed! s32Ret=%d\n", s32Ret);}\
}while(0)


#define HDMI_MUTEX_UNLOCK(a)         	up(&(a))
#else
#define HDMI_MUTEX_LOCK(a)  \
do{\
    HI_S32 s32Ret = osal_down(&(a));\
    if (0 != s32Ret)\
        {HDMI_ERR("osal_down failed! s32Ret=%d\n", s32Ret);}\
}while(0)


#define HDMI_MUTEX_UNLOCK(a)         	osal_up(&(a))
#endif

#ifdef HDMI_DEBUG
#ifndef HI_ADVCA_FUNCTION_RELEASE
#ifndef HDMI_PRODUCT_HI3559A
#define OSAL_PRINTK(fmt, args...)        printk(fmt, ## args)
#else
#define OSAL_PRINTK(fmt, args...)        osal_printk(fmt, ## args)
#endif
#else
#define OSAL_PRINTK(fmt, args...)
#endif
#else
#define OSAL_PRINTK(fmt, args...)
#endif

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
    ( p1 && p2 && (strlen(p1)==strlen(p2)) && (strncmp(p1,p2,strlen(p1))==0) ) ? HI_TRUE : HI_FALSE;\
})

/** open a kernel file
**/
struct file* HDMI_OSAL_FileOpen(const HI_S8* ps8FileName, OSAL_FILE_FLAG_S eFlags);
/** close a kernel file
**/
HI_VOID HDMI_OSAL_FileClose(struct file * pFile);
/** read a kernel file
**/
HI_S32 HDMI_OSAL_FileRead(struct file * pFile,  HI_U8* ps8Buf, HI_U32 u32Len);
/** write a kernel file
**/
HI_S32 HDMI_OSAL_FileWrite(struct file* pFile, HI_S8* ps8Buf, HI_U32 u32Len);


/** copy str to pszDest from pszSrc
**/
HI_CHAR* HDMI_OSAL_Strncpy(HI_CHAR *pszDest, const HI_CHAR *pszSrc, HI_SIZE_T ulLen);
/** compare pszStr1 with pszStr2
**/
HI_S32 HDMI_OSAL_Strncmp(const HI_CHAR *pszStr1, const HI_CHAR *pszStr2, HI_SIZE_T ulLen);
/** casecompare pszStr1 with pszStr2
**/
HI_S32 HDMI_OSAL_Strncasecmp(const HI_CHAR *pszStr1, const HI_CHAR *pszStr2, HI_SIZE_T ulLen);
/** strncat pszSrc
**/
HI_CHAR* HDMI_OSAL_Strncat(HI_CHAR *pszDest, const HI_CHAR *pszSrc, HI_SIZE_T ulLen);
/** snprintf pszSrc
**/
HI_S32 HDMI_OSAL_Snprintf(HI_CHAR *pszStr, HI_SIZE_T ulLen, const HI_CHAR *pszFormat, ...);
/** vsnprintf pszSrc
**/
HI_S32 HDMI_OSAL_Vsnprintf(HI_CHAR *pszStr, HI_SIZE_T ulLen, const HI_CHAR *pszFormat, va_list stVAList);


/** get system time in Ms
**/
HI_U32 HDMI_OSAL_GetTimeInMs(HI_VOID);

/** get system time in Us
**/
HI_U32 HDMI_OSAL_GetTimeInUs(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

