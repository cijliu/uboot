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

#ifndef __CIPHER_ADAPT_H_
#define __CIPHER_ADAPT_H_

#ifndef HI_MINIBOOT_SUPPORT
#include <common.h>
#else
#include "delay.h"
#include "malloc.h"
#include "string.h"
#include "stdio.h"
#endif
//#include "hi_common.h"
#include "malloc.h"

#include "hi_types.h"
#include "drv_cipher_ioctl.h"
#include "hi_drv_cipher.h"
#include "cipher_config.h"
#include "spacc_intf.h"
#include "drv_rng.h"
#include "drv_rsa.h"
#include "drv_klad.h"
#include "../../../hiotp/hal_otp.h"
#include "hi_drv_compat.h"

/**************************** M A C R O ****************************/
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

#define HI_ID_CIPHER            100

#define HI_HANDLE_MAKEHANDLE(mod, privatedata, chnid)  (HI_HANDLE)( (((mod)& 0xffff) << 16) | ((((privatedata)& 0xff) << 8) ) | (((chnid) & 0xff)) )
#define HI_HANDLE_GET_MODID(handle)     (((handle) >> 16) & 0xffff)
#define HI_HANDLE_GET_PriDATA(handle)   (((handle) >> 8) & 0xff)
#define HI_HANDLE_GET_CHNID(handle)     (((handle)) & 0xff)

#define CIPHER_IOR             _IOWR
#define CIPHER_IOW            _IOW
#define CIPHER_IOWR            _IOWR

#define CIPHER_IOC_DIR        _IOC_DIR
#define CIPHER_IOC_TYPE        _IOC_TYPE
#define CIPHER_IOC_NR        _IOC_NR
#define CIPHER_IOC_SIZE        _IOC_SIZE
#define U32_TO_POINT(addr)                  ((HI_VOID*)((HI_SIZE_T)(addr)))
#define POINT_TO_U32(addr)                  ((HI_U32)((HI_SIZE_T)(addr)))

#define HAL_CIPHER_ReadReg(addr, result)    (*(result) = *(volatile unsigned int *)(addr))
#define HAL_CIPHER_WriteReg(addr,result)    (*(volatile unsigned int *)(addr) = (result))

#define HAL_SET_BIT(src, bit)               ((src) |= (1<<bit))
#define HAL_CLEAR_BIT(src,bit)              ((src) &= ~(1<<bit))

#define CPU_TO_BE16(v) (((v)<< 8) | ((v)>>8))
#define CPU_TO_BE32(v) (((v)>>24) | (((v)>>8)&0xff00) | (((v)<<8)&0xff0000) | ((v)<<24))
#define CPU_TO_BE64(x) ((HI_U64)(                         \
        (((HI_U64)(x) & (HI_U64)0x00000000000000ffULL) << 56) |   \
        (((HI_U64)(x) & (HI_U64)0x000000000000ff00ULL) << 40) |   \
        (((HI_U64)(x) & (HI_U64)0x0000000000ff0000ULL) << 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00000000ff000000ULL) <<  8) |   \
        (((HI_U64)(x) & (HI_U64)0x000000ff00000000ULL) >>  8) |   \
        (((HI_U64)(x) & (HI_U64)0x0000ff0000000000ULL) >> 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00ff000000000000ULL) >> 40) |   \
        (((HI_U64)(x) & (HI_U64)0xff00000000000000ULL) >> 56)))

/**************************** S T D L I B ****************************/
#define cipher_ioremap_nocache(addr, size)  (HI_VOID*)(addr)
#define cipher_iounmap(x)

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len);
int  cipher_memcmp_s(const void *a, const void *b, unsigned len);
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len);
HI_S32 cipher_waitdone_callback(HI_VOID *pParam);

#define cipher_mutex                        HI_VOID *
#define cipher_mutex_init(x)
#define cipher_mutex_lock(x)                0
#define cipher_mutex_unlock(x)

#define cipher_queue_head                   HI_VOID *
#define cipher_queue_init(x)
#define cipher_queue_wait_up(x)
#define cipher_queue_wait_timeout(head, con, time)

#define cipher_request_irq(irq, func, name)
#define cipher_free_irq(irq, name)
#define cipher_irqreturn_t                          int
#define CIPHER_IRQ_HANDLED                          1

#define cipher_copy_from_user(s, d, l)       (memcpy(s, d, l), 0)
#define cipher_copy_to_user(s, d, l)         (memcpy(s, d, l), 0)

#define cipher_malloc(x)                     malloc(x)
#define cipher_free(x)                       free(x)

#define cipher_msleep(msec)                  udelay(1000)
#define HI_PRINT                             printf
#define HI_ERR_CIPHER(fmt...)                HI_PRINT(fmt)
#define HI_INFO_CIPHER(fmt...)               //HI_PRINT(fmt)
#define cipher_proc_printf                   //osal_seq_printf

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void HEX2STR(char buf[2], HI_U8 val);

#if 0
#define HI_PRINT_HEX(name, str, len) PrintData(name, str, len)
#else
#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_U8 *_str; \
    _str = (HI_U8*)str; \
    HI_PRINT("[%s]:\n", name);\
    for ( _i = 0 ; _i < (len); _i++ )\
    {\
        if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
        HI_PRINT("\\x%02x", *((_str)+_i));\
    }\
    HI_PRINT("\n");\
}
#endif

/**************************** P R I V A T E ****************************/
typedef struct
{
    HI_VOID *pu8StartVirAddr;
        HI_SIZE_T szStartPhyAddr;
        HI_U32 u32MMZAddr;
    HI_U32 u32Size;
}cipher_mmz_buf_t;

HI_S32  cipher_mmz_alloc_remap(HI_CHAR *name, cipher_mmz_buf_t *pstMmz);
HI_VOID cipher_mmz_release_unmap(cipher_mmz_buf_t *pstMmz);
HI_S32  cipher_mmz_map(cipher_mmz_buf_t *pstMmz);
HI_VOID cipher_mmz_unmap(cipher_mmz_buf_t *pstMmz);

#endif

