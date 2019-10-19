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
#ifndef __HDMI_PLATFORM_H__
#define __HDMI_PLATFORM_H__
#include "hi_type.h"
#ifdef CONFIG_HDMI_STB_SDK
#include "hi_module.h"
#include "hi_debug.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "hi_drv_mem.h"
#include <asm/io.h>
#endif

#ifdef HI_MINIBOOT_SUPPORT
#include <malloc.h>
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/******************************************************************************/
/* Macro type for hdmi module                                                 */
/******************************************************************************/
#define HDMI_CTRL_BASE_ADDR             0x13010000

#define PERI_HDMITX_CTRL_ADDR           0x12120150
#define HDMI_AUDIO_SOURCE_SPDIF 	   (0x1<<6)
#define HDMI_AUDIO_SOURCE_I2S 		   (0x1<<7)
#define HDMI_AUDIO_SOURCE_DSD 		   (0x1<<8)
#define HDMI_AUDIO_SOURCE_HBRA 		   (0x1<<9)
#define HDMI_AUDIO_SOURCE_PARALLEL 	   (0x1<<10)

#define HDMI_CRG_BASE_ADDR  			0x1204003c
#define HDMITX_CTRL_PIXELNX_CKSEL		(0x1<<28)
#define HDMITX_CTRL_ID_CKSEL			(0x1<<24)
#define HDMITX_CTRL_ASCLK_SEL			(0x1<<18)
#define HDMITX_CTRL_OSCLK_SEL			(0x1<<17)
#define HDMITX_CTRL_SRST_REQ			(0x1<<13)
#define HDMITX_CTRL_BUS_SRST_REQ		(0x1<<12)
#define HDMITX_CTRL_PIXELNX_CKEN		(0x1<<8) 
#define HDMITX_CTRL_XCLK_CKEN  		    (0x1<<7)  
#define HDMITX_CTRL_PIXEL_CKEN			(0x1<<6) 
#define HDMITX_CTRL_AS_CKEN			    (0x1<<5)
#define HDMITX_CTRL_OS_CKEN			    (0x1<<4)
#define HDMITX_CTRL_MHL_CKEN			(0x1<<3)
#define HDMITX_CTRL_ID_CKEN			    (0x1<<2)
#define HDMITX_CTRL_CEC_CKEN			(0x1<<1)
#define HDMITX_CTRL_BUS_CKEN			(0x1<<0)
#define HDMI_COLOR_BAR_MASK             0x70000000
#define HDMI_COLOR_BAR_UPDATE_MASK      0x00000001
#define HDMI_COLOR_BAR_BASE             0x1302c000

#define  HDMI_ADDR_CRG                  0xf8a22000

/* Pin Multiplex, HDMITX IO CONFIG,see Hi3798MV200T SI RFQ.xlsm */
#define HDMI_ADDR_BASE_IO_CFG           0xf8a21000
#define HDMI_ADDR_IO_CFG_HOTPLUG        (HDMI_ADDR_BASE_IO_CFG + 0xb4)
#define HDMI_ADDR_IO_CFG_SDA            (HDMI_ADDR_BASE_IO_CFG + 0xb8)
#define HDMI_ADDR_IO_CFG_SCL            (HDMI_ADDR_BASE_IO_CFG + 0xbc)
#define HDMI_ADDR_IO_CFG_CEC            (HDMI_ADDR_BASE_IO_CFG + 0xc0)

#define HDMI_VMALLOC(size)              vmalloc(size, GFP_KERNEL)
#define HDMI_KMALLOC(size)              kmalloc(size, GFP_KERNEL)

#define HDMI_KFREE(viraddr)             kfree(viraddr)
#define HDMI_VFREE(viraddr)             vfree(viraddr)

#define HDMI_IO_MAP(phys_addr, len)     (phys_addr)
#define HDMI_IO_UNMAP(virt_addr)    


#endif

/******************************************************************************/
/* Data Structures                                                            */
/******************************************************************************/

/******************************************************************************/
/* Gloabl Data                                                                */
/******************************************************************************/

/******************************************************************************/
/* Public Interface                                                           */
/******************************************************************************/
#define DECLARE_HDMI_NODE(hdmi_name, hdmi_open, hdmi_release, hdmi_mmap, hdmi_ioctl, hdmi_suspend, hdmi_resume) \
static struct file_operations s_stHdmiFileOps =\
{\
    .owner   = THIS_MODULE,      \
    .unlocked_ioctl = hdmi_ioctl,\
    .open    = hdmi_open,        \
    .release = hdmi_release,     \
    .mmap    = hdmi_mmap         \
};\
static PM_BASEOPS_S s_stHdmiDrvOps = \
{\
    .suspend      = hdmi_suspend,\
    .resume       = hdmi_resume  \
};\
static UMAP_DEVICE_S s_stHdmiDev = \
{\
    .minor      = UMAP_MIN_MINOR_HDMI,\
    .owner      = THIS_MODULE,\
    .fops       = &s_stHdmiFileOps,\
    .drvops     = &s_stHdmiDrvOps \
};


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

