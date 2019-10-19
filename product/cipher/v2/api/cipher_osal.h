/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute  it and/or modify it
* under  the terms of  the GNU General Public License as published by the
* Free Software Foundation;  either version 2 of the  License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef __CIPHER_OSAL_H__
#define __CIPHER_OSAL_H__

#ifndef HI_MINIBOOT_SUPPORT
#include <common.h>
#else
#include "string.h"
#include "stdio.h"
#endif
#include "common.h"
#include "malloc.h"
#include "hi_types.h"
#include "hi_unf_cipher.h"
#include "hi_drv_cipher.h"
#include "drv_cipher_ioctl.h"
#include "hi_mpi_cipher.h"
#include "ree_mpi_cipher.h"
#define CIPHER_KLAD_SUPPORT
#define HASH_BLOCK_SIZE                  (128)
#define HASH_RESULT_MAX_LEN              (64)
#define HASH_RESULT_MAX_LEN_IN_WORD      (16)
#define HI_INVALID_HANDLE                (0xffffffff)

#define  HI_ERR_CIPHER_NOT_INIT                     (HI_S32)(0x804D0001)
#define  HI_ERR_CIPHER_INVALID_HANDLE               (HI_S32)(0x804D0002)
#define  HI_ERR_CIPHER_INVALID_POINT                (HI_S32)(0x804D0003)
#define  HI_ERR_CIPHER_INVALID_PARA                 (HI_S32)(0x804D0004)
#define  HI_ERR_CIPHER_FAILED_INIT                  (HI_S32)(0x804D0005)
#define  HI_ERR_CIPHER_FAILED_GETHANDLE             (HI_S32)(0x804D0006)
#define  HI_ERR_CIPHER_FAILED_RELEASEHANDLE         (HI_S32)(0x804D0007)
#define  HI_ERR_CIPHER_FAILED_CONFIGAES             (HI_S32)(0x804D0008)
#define  HI_ERR_CIPHER_FAILED_CONFIGDES             (HI_S32)(0x804D0009)
#define  HI_ERR_CIPHER_FAILED_ENCRYPT               (HI_S32)(0x804D000A)
#define  HI_ERR_CIPHER_FAILED_DECRYPT               (HI_S32)(0x804D000B)
#define  HI_ERR_CIPHER_BUSY                         (HI_S32)(0x804D000C)
#define  HI_ERR_CIPHER_NO_AVAILABLE_RNG             (HI_S32)(0x804D000D)

#define CPU_TO_BE16(v) (((v)<< 8) | ((v)>>8))
#define CPU_TO_BE32(v) ((((HI_U32)(v))>>24) | ((((HI_U32)(v))>>8)&0xff00) | ((((HI_U32)(v))<<8)&0xff0000) | (((HI_U32)(v))<<24))
#define CPU_TO_BE64(x) ((HI_U64)(                         \
        (((HI_U64)(x) & (HI_U64)0x00000000000000ffULL) << 56) |   \
        (((HI_U64)(x) & (HI_U64)0x000000000000ff00ULL) << 40) |   \
        (((HI_U64)(x) & (HI_U64)0x0000000000ff0000ULL) << 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00000000ff000000ULL) <<  8) |   \
        (((HI_U64)(x) & (HI_U64)0x000000ff00000000ULL) >>  8) |   \
        (((HI_U64)(x) & (HI_U64)0x0000ff0000000000ULL) >> 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00ff000000000000ULL) >> 40) |   \
        (((HI_U64)(x) & (HI_U64)0xff00000000000000ULL) >> 56)))

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define UMAP_DEVNAME_CIPHER       "cipher"
#define UMAP_CIPHER_MINOR_BASE    50

#define HI_INVALID_HANDLE   (0xffffffff)

#define GET_ULONG_LOW(dw)       (unsigned int)(dw)
#define GET_ULONG_HIGH(dw)      0
#define MAKE_ULONG(low, high)   (low)

typedef unsigned long             HI_SIZE_T;

#define HI_PRINT                 printf
#define HI_ERR_CIPHER(fmt...)    HI_PRINT(fmt)
#define HI_INFO_CIPHER(fmt...)   //HI_PRINT(fmt)

/**************************** debug api ***********************/
#if 1
void PrintData(const char*pbName, HI_U8 *pbData, HI_U32 u32Size);

#define HI_PRINT_HEX(name, str, len) PrintData(name, str, len)
#else
#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_U32 _val; \
    HI_U8 *_str = (HI_U8*)str;\
    if (_str != HI_NULL) \
    {\
        HI_PRINT("[%s]:\n", name);\
        for ( _i = 0 ; _i < (len); _i+=4 )\
        {\
            _val  = *((_str)+_i+3);\
            _val |= *((_str)+_i+2) << 8;\
            _val |= *((_str)+_i+1) << 16;\
            _val |= *((_str)+_i+0) << 24;\
            HI_PRINT("%x\n", _val);\
        }\
        HI_PRINT("\n");\
    }\
}
#endif

/************************** params check api *********************/
#define INLET_PARAM_CHECK_U32_MAX(val, max) \
do{\
    if ((val) > (max))\
    {\
        HI_ERR_CIPHER("inlet param " #val " = 0x%x overflow, must less than" #max "(0x%x).\n", val, max);\
        return HI_ERR_CIPHER_INVALID_PARA;\
    }\
}while(0)

#define INLET_PARAM_CHECK_U32_ZERO(val) \
do{\
    if ((val) == 0)\
    {\
        HI_ERR_CIPHER("inlet param " #val " is zero\n");\
        return HI_ERR_CIPHER_INVALID_PARA;\
    }\
}while(0)

#define INLET_PARAM_CHECK_POINT_NULL(p) \
do{\
    if ((p) == HI_NULL)\
    {\
        HI_ERR_CIPHER("inlet param " #p " is null\n");\
        return HI_ERR_CIPHER_INVALID_POINT;\
    }\
}while(0)

#define cipher_mutex                             HI_VOID *
#define cipher_mutex_init(x)
#define cipher_mutex_lock(x)
#define cipher_mutex_unlock(x)
#define cipher_mutex_destroy(x)

#define cipher_open(a, b, c)			(CIPHER_MODULE_Init(), 1)
#define cipher_close(x)				(CIPHER_MODULE_Exit())
#define cipher_ioctl(dev, cmd, argp)		CIPHER_Ioctl(cmd, argp, NULL)

#define cipher_malloc(x)             malloc(x)
#define cipher_free(x)               free(x)

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len);
int   cipher_memcmp_s(const void *a, const void *b, unsigned len);
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len);

extern HI_S32 g_CipherDevFd;

typedef struct
{
    HI_VOID *pu8StartVirAddr;
    HI_SIZE_T szStartPhyAddr;
    HI_U32 u32Size;
}cipher_mmz_buf_t;

HI_S32 CIPHER_Maloc(cipher_mmz_buf_t *pstMem, HI_CHAR *name);
HI_S32 CIPHER_Free(cipher_mmz_buf_t *pstMem);

#endif

