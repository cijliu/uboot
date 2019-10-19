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
#ifndef __HDMI_PRODUCT_DEFINE_H__
#define __HDMI_PRODUCT_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef HDMI_BUILD_IN_BOOT
#include "ubi_uboot.h"
#include "malloc.h"
#include "boot_hdmi_intf.h"
#else
#ifndef HDMI_LITEOS_SUPPORT
#include <linux/fs.h>
#endif

#include "hi_debug.h"
#include "dev_ext.h"
#include "mod_ext.h"
#include "hi_osal.h"
#include "drv_hdmi_log.h"
#endif

#include "hi_type.h"

/******************************************************************************/
/* Macro type for hdmi module                                                 */
/******************************************************************************/

#define HDMI_CHIP_HI3559AV100       0x3559a100

#define HDMI_CTRL_BASE_ADDR         0x11140000
#define HDMI_ADDR_BASE_IO_CFG       0x12040000
#define HDMI_ADDR_CRG               0x12010000      // CRG reg
#define BASE_ADDR_tx_dphy           0x11160000      // hdmi tx phy reg
#define HDMI_ADDR_SC                0x12020000      // system ctrol

#define HDMI_SYS_TIMER_ADDR         0x12000000      /* timer base addr */
#define HDMI_TIMER11_OFFSET         0x5020          /* timer11 offset addr */

/* No mux IO */

#define HDMI_COLOR_BAR_MASK         0x70000000
#define HDMI_COLOR_BAR_UPDATE_MASK  0x00000001
#define HDMI_COLOR_BAR_BASE         0x1110d000      // VDP

/* HDMI REG */
#define HDMI_TX_BASE_ADDR           0x11140000
#define HDMI_TX_REG_LEN             (0x30000)

#define HDMI_TX_BASE_ADDR_CTRL      0x0000
#define HDMI_TX_BASE_ADDR_AIDEO     0x0800
#define HDMI_TX_BASE_ADDR_AUDIO     0x1000
#define HDMI_TX_BASE_ADDR_HDMITX    0x1800
#define HDMI_TX_BASE_ADDR_HDCP1X    0x2000
#define HDMI_RX_BASE_ADDR_FRL       0x3000
#define HDMI_TX_BASE_ADDR_AON       0x4000
#define HDMI_TX_BASE_ADDR_CEC       0x4800
#define HDMI_TX_BASE_ADDR_MCU_PRAM  0x10000
#define HDMI_TX_BASE_ADDR_MCU_DRAM  0x18000
#define HDMI_TX_BASE_ADDR_MCU       0x1c000
#define HDMI_TX_BASE_ADDR_DPHY      0x20000

#define BASE_ADDR_tx_ctrl_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_CTRL)
#define BASE_ADDR_video_path_reg    (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_AIDEO)
#define BASE_ADDR_audio_path_reg    (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_AUDIO)
#define BASE_ADDR_tx_hdmi_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_HDMITX)
#define BASE_ADDR_tx_hdcp_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_HDCP1X)
#define BASE_ADDR_tx_aon_reg        (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_AON)
#define BASE_ADDR_tx_cec_reg        (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_CEC)
#define BASE_ADDR_mcu_cpu_reg       (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_MCU)
#define BASE_ADDR_mcu_pram          (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_MCU_PRAM)
#define BASE_ADDR_mcu_dram          (HDMI_TX_BASE_ADDR|HDMI_TX_BASE_ADDR_MCU_DRAM)
#define BASE_ADDR_frl_reg           (HDMI_TX_BASE_ADDR|HDMI_RX_BASE_ADDR_FRL)

/* when pixclk(VDP->HDMI) is less than 600M, HDMI is working on one clap one mode.
   Otherwise working on one clap two mode.*/
#define HDMI_ONE_BEAT_CLK           (600000)

/** pm disable */
//#define  CONFIG_GFX_COMM_PM_DISABLE
#ifdef HI_ADVCA_FUNCTION_RELEASE
/** PROC disable */
#define  CONFIG_HDMI_PROC_DISABLE
/** LOG disable */
#define  CONFIG_HDMI_DEBUG_DISABLE
#endif

#ifndef HDMI_BUILD_IN_BOOT

#define HDMI_SNPRINTF                       osal_snprintf
#define HDMI_VSNPRINTF(dstr, len, fstr, arg) osal_vsnprintf(dstr, len, fstr, arg)
#define HDMI_DOWN_INTERRUPTIBLE(a)          osal_down(a)
#define HDMI_UP(a)                          osal_up(a)
#define HDMI_WAKEUP(a)                      osal_wakeup(a)
#define HDMI_MEMSET                         osal_memset
#define HDMI_MEMCPY	                        osal_memcpy
#define HDMI_MEMCMP	                        osal_memcmp
#define HDMI_STRLEN(p)                      ({p ? osal_strlen(p) : 0 ;})
#define HDMI_STRNCPY(p1, p2, size)          osal_strncpy(p1,p2,size)
#define HDMI_STRNCMP(pdes, psrc, len)       osal_strncmp(pdes, psrc, len)
#define HDMI_STRSTR(vir, str)               osal_strstr(vir, str)
#define HDMI_STRNCASECMP(s1, s2, n)         osal_strncasecmp(s1, s2, n)
#define HDMI_STRNCAT(dest, src, count)      osal_strncat(dest, src, count)
#define HDMI_SMSTRTOUL(str, end, base)      osal_strtoull(str, end, base)
#define HDMI_SCHED_LOCK                     osal_sched_clock
#define HDMI_DO_DIV64(time,len)             osal_div_u64(time, len)
#define HDMI_DO_DIVU64(dividend, divisor)   osal_div64_u64(dividend, divisor)
#define HDMI_DO_DIVS64(dividend, divisor)   osal_div64_s64(dividend, divisor)
#define HDMI_DIVU64_REM(dividend, divisor)  osal_div_u64_rem(dividend, divisor)
#define HDMI_DIVS64_REM(dividend, divisor)  osal_div_s64_rem(dividend, divisor)
#define HDMI_GETTIMEOFDAY(tv)               osal_gettimeofday(tv)

#define HDMI_SPIN_LOCK_INIT(x)                 osal_spin_lock_init(&x)
#define HDMI_SPIN_LOCK(x)                    osal_spin_lock(&x)
#define HDMI_SPIN_UNLOCK(x)                    osal_spin_unlock(&x)
#define HDMI_SPIN_TRYLOCK(x)                osal_spin_trylock(&x)
#define HDMI_SPIN_DESTORY(x)                osal_spin_lock_destory(&x)
#define HDMI_WAIT_QUEUE                     osal_wait_t
#define HDMI_WAIT_QUEUE_INIT(x)             osal_wait_init(&x)
#define HDMI_WAIT_QUEUE_DESTORY(x)          osal_wait_destory(&x)
#define HDMI_INIT_MUTEX(x)                  osal_sema_init(&x, 1)
#define HDMI_DESTORY_MUTEX(x)               osal_sema_destory(&(x))
#define HDMI_DECLARE_MUTEX(x)               DEFINE_SEMAPHORE(x)

#define HDMI_MSLEEP(ms)                     osal_msleep((ms))
#define HDMI_MDELAY(ms)                     osal_mdelay((ms))
#define HDMI_UDELAY(us)                     osal_udelay((us))
#define HDMI_TIMEVAL_S                      osal_timeval_t

#define HDMI_OSAL_IOREMAP_NOCACHE(addr, len)      osal_ioremap_nocache((addr), (len))
#define HDMI_OSAL_IOUNMAP(addr)             osal_iounmap((addr))
#define HDMI_CONTAINER_OF                   osal_container_of
#define HDMI_LIST_HEAD                      struct osal_list_head
#define HDMI_LIST_EMPTY                     osal_list_empty
#define HDMI_LIST_FOR_EACH_SAFE             osal_list_for_each_safe
#define HDMI_LIST_ENTRY                     osal_list_entry
#define HDMI_LIST_DEL                       osal_list_del
#define HDMI_LIST_ADD_TAIL                  osal_list_add_tail
#define HDMI_ATOMIC_T                       osal_atomic_t
#define HDMI_SEMAPHORE                      osal_semaphore_t
#define HDMI_INIT_LIST_HEAD                 OSAL_INIT_LIST_HEAD
#define HDMI_COPY_FROM_USER                 osal_copy_from_user
#define HDMI_ATOMIC_INC_RETURN(x)           osal_atomic_inc_return(x)
#define HDMI_ATOMIC_DEC_ADN_TEST(x)         atomic_dec_and_test(x)
#define HDMI_ATOMIC_DEC_RETURN(x)           osal_atomic_dec_return(x)
#define HDMI_WAKE_UP                        osal_wakeup
#define HDMI_WAIT_EVENT_INTERRUPT(a, callback, param)     osal_wait_event(&(a), (callback), (HI_VOID *)param)
#define HDMI_VA_START(a, b)                 osal_va_start((a), (b))
#define HDMI_VA_END(a)                      osal_va_end(a)
#define HDMI_VA_LIST                        osal_va_list

#define HDMI_KTHREAD_RUN(a, b, c)           osal_kthread_create(a, b, c)
#define HDMI_KTHREAD_STOP(a, b)             osal_kthread_destory(a, b)
#define HDMI_TASK_T                         osal_task_t

#define HDMI_VMALLOC(size)                  osal_vmalloc(size)
#define HDMI_KMALLOC(size)                  osal_kmalloc(size, osal_gfp_kernel)
#define HDMI_KFREE(viraddr)                 osal_kfree(viraddr)
#define HDMI_VFREE(viraddr)                 osal_vfree(viraddr)

#define HDMI_FILP_OPEN(filename, flags, mode)   osal_klib_fopen(filename, flags, mode)
#define HDMI_FILP_CLOSE(flip)               osal_klib_fclose(flip)
#define HDMI_FILP_FWRITE(buf, len, flip)    osal_klib_fwrite(buf, len, flip)
#define HDMI_FILP_READ(buf, len, flip)      osal_klib_fread(buf, len, flip)

#define HDMI_O_ACCMODE                      OSAL_O_ACCMODE
#define HDMI_O_RDONLY                       OSAL_O_RDONLY
#define HDMI_O_WRONLY                       OSAL_O_WRONLY
#define HDMI_O_RDWR                         OSAL_O_RDWR
#define HDMI_O_CREAT                        OSAL_O_CREAT

/* (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) */
#define HDMI_FILE_MODE                      (0777)

#define PROC_PRINT(arg...)                  osal_seq_printf(arg)
#define VERSION_STRING                      ("[HDMI] Version:["MPP_VERSION"] Build Time:[")

#ifndef HDMI_LITEOS_SUPPORT
#define HDMI_THREAD_SHOULD_STOP             (kthread_should_stop())
#define HDMI_GET_CURRENT_ID                 (get_current()->tgid)
#else
/* thread id maybe is 0 */
#define HDMI_GET_CURRENT_ID                 (pthread_self() + 1)
#endif

#define DEVNAME_HDMI                        UMAP_DEVNAME_HDMI_BASE
#define DECLARE_HDMI_NODE(hdmi_name, hdmi_open, hdmi_release, hdmi_mmap, hdmi_ioctl, hdmi_suspend, hdmi_resume)

#define HI_TRACE_HDMI(level, fmt...) \
do{\
     HI_TRACE(level,HI_ID_HDMI,"[Func]:%s [Line]:%d [Info]:",__FUNCTION__, __LINE__); \
     HI_TRACE(level,HI_ID_HDMI,##fmt); \
} while(0)

#define HDMI_MUTEX_LOCK(a)  \
do{\
    HI_S32 s32Ret = osal_down((HDMI_SEMAPHORE *)&(a));\
    if (0 != s32Ret)\
        {HDMI_ERR("osal_down failed! s32Ret=%d\n", s32Ret);}\
}while(0)

#define HDMI_MUTEX_UNLOCK(a)                 osal_up((HDMI_SEMAPHORE *)&(a))


#ifdef HDMI_LOG_SUPPORT
#ifndef HI_ADVCA_FUNCTION_RELEASE
#define HDMI_PRINTK(fmt, args...)           osal_printk(fmt, ## args)
#else
#define HDMI_PRINTK(fmt, args...)
#endif
#else
#define HDMI_PRINTK(fmt, args...)
#endif

#ifdef CONFIG_HDMI_DEBUG_DISABLE
#define EDID_INFO(fmt...)
#define EDID_WARN(fmt...)
#define EDID_ERR(fmt...)
#define EDID_FATAL(fmt...)
#define HDMI_INFO(fmt...)
#define HDMI_WARN(fmt...)
#define HDMI_ERR(fmt...)
#define HDMI_FATAL(fmt...)

#elif defined(HDMI_LOG_SUPPORT)
#define EDID_INFO(fmt...)               //HI_INFO_PRINT   (HI_ID_HDMI, fmt)
#define EDID_WARN(fmt...)               //HI_WARN_PRINT   (HI_ID_HDMI, fmt)
#define EDID_ERR(fmt...)                //HI_ERR_PRINT    (HI_ID_HDMI, fmt)
#define EDID_FATAL(fmt...)              //HI_FATAL_PRINT  (HI_ID_HDMI, fmt)
#define HDMI_INFO(fmt...)               HI_TRACE_HDMI(HI_DBG_INFO, fmt);  HDMI_LOG_INFO(fmt)
#define HDMI_WARN(fmt...)               HI_TRACE_HDMI(HI_DBG_WARN, fmt);  HDMI_LOG_WARN(fmt)
#define HDMI_ERR(fmt...)                HI_TRACE_HDMI(HI_DBG_ERR, fmt);   HDMI_LOG_ERR(fmt)
#define HDMI_FATAL(fmt...)              HI_TRACE_HDMI(HI_DBG_EMERG, fmt); HDMI_LOG_FATAL(fmt)

#else
#define EDID_INFO(fmt...)               HI_TRACE_HDMI(HI_DBG_INFO, fmt)
#define EDID_WARN(fmt...)               HI_TRACE_HDMI(HI_DBG_WARN, fmt)
#define EDID_ERR(fmt...)                HI_TRACE_HDMI(HI_DBG_ERR, fmt)
#define EDID_FATAL(fmt...)              HI_TRACE_HDMI(HI_DBG_EMERG, fmt)
#define HDMI_FATAL(fmt...)              HI_TRACE_HDMI(HI_DBG_EMERG, fmt)
#define HDMI_ERR(fmt...)                HI_TRACE_HDMI(HI_DBG_ERR, fmt)
#define HDMI_WARN(fmt...)               HI_TRACE_HDMI(HI_DBG_WARN, fmt)
#define HDMI_INFO(fmt...)               HI_TRACE_HDMI(HI_DBG_INFO, fmt)

#endif

#define HDMI_IO_MAP(phys_addr, len)     (osal_ioremap_nocache(phys_addr, len))
#define HDMI_IO_UNMAP(virt_addr)        if(virt_addr){osal_iounmap((void *)virt_addr);}

typedef osal_proc_entry_t               HDMI_PROC_ENTRY;

/******************************************************************************/
/* Data Structures                                                            */
/******************************************************************************/
/** Structure of proc item */
typedef struct strHDMI_PROC_ITEM
{
    HI_S32 (*fnRead)(HDMI_PROC_ENTRY *pFile);
    HI_S32 (*fnWrite)(HDMI_PROC_ENTRY *pFile, const char *pBuf, HI_U32 u32Count, HI_S64 *ps64Data);
}HDMI_PROC_ITEM_S;

#else
#define HDMI_MSLEEP(ms)                 mdelay((ms))
#define HDMI_MDELAY(ms)                 mdelay((ms))
#define HDMI_UDELAY(us)                 udelay((us))
#define HDMI_SNPRINTF                   snprintf
#define HDMI_MEMSET                     memset
#define HDMI_MEMCPY	                    memcpy
#define HDMI_MEMCMP	                    memcmp
#define HDMI_VMALLOC(size)              vmalloc(size)
#define HDMI_KMALLOC(size)              kmalloc(size, GFP_KERNEL)
#define HDMI_KFREE(viraddr)             kfree(viraddr)
#define HDMI_VFREE(viraddr)             vfree(viraddr)

#define HDMI_IO_MAP(phys_addr, len)     (phys_addr)
#define HDMI_IO_UNMAP(virt_addr)

#define HDMI_DO_DIVU64(dividend, divisor)        div_u64(dividend, divisor)
#define HDMI_DO_DIVS64(dividend, divisor)        div_s64(dividend, divisor)
#define HDMI_DIVU64_REM(dividend, divisor, rem)  div_u64_rem(dividend, divisor, rem)
#define HDMI_DIVS64_REM(dividend, divisor, rem)  div_s64_rem(dividend, divisor, rem)

#endif

typedef struct
{
    HI_U32 u32SscBypassDiv;
    HI_U32 u32TmdsClkDiv;
}HDMI_CRG_CFG_S;

/******************************************************************************/
/* Public Interface                                                           */
/******************************************************************************/
HI_S32 HDMITXRegWrite(HI_U32 *pu32RegAddr, HI_U32 u32Value);
HI_U32 HDMITXRegRead(HI_U32 *pu32RegAddr);
HI_S32 HDMIRegWriteU32(HI_U32 u32RegAddr, HI_U32 u32Value);
HI_U32 HDMIRegReadU32 (HI_U32 u32RegAddr);
HI_S32 HDMITXRegWrite64(HI_U32 *pu32RegAddr, HI_U32 u32Value);
HI_U32 HDMITXRegRead64(HI_U32 *pu32RegAddr);

HI_VOID DRV_HDMI_ProdIoCfgSet(HI_VOID);
HI_VOID DRV_HDMI_ProdCrgAllResetSet(HI_BOOL bEnable);
HI_VOID DRV_HDMI_ProdCrgGateSet(HI_BOOL bEnable);
HI_VOID DRV_HDMI_ProdCrgDivSet(HDMI_CRG_CFG_S *pstCrgCfg);
HI_VOID DRV_HDMI_ProdCrgPhyResetSet(HI_BOOL bEnable);
HI_VOID DRV_HDMI_ProdCrgPhyResetGet(HI_BOOL *pbEnable);
HI_VOID DRV_HDMI_ProdCrgInit(HI_VOID);
HI_VOID DRV_HDMI_ProdCrgDeInit(HI_VOID);
HI_VOID DRV_HDMI_HardwareReset(HI_VOID);
HI_VOID DRV_HDMI_LowPowerSet(HI_BOOL bEnable);

#ifndef HDMI_BUILD_IN_BOOT
HI_S32 HI_HDMI_PROC_AddModule(HI_CHAR * pEntry_name, HDMI_PROC_ITEM_S *pProcItem, HI_VOID *pData);
HI_VOID HI_HDMI_PROC_RemoveModule(HI_CHAR *pEntry_name);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_PRODUCT_DEFINE_H__ */


