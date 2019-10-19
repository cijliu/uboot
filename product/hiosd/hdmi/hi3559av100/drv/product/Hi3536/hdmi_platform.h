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
#ifndef HDMI_BUILD_IN_BOOT
#include "hi_debug.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/******************************************************************************/
/* Macro type for hdmi module                                                 */
/******************************************************************************/
#define HDMI_CHIP_HI3536  0x35360100 

#define HDMI_CTRL_BASE_ADDR 0x13010000

#define HDMI_VMALLOC(size)     vmalloc(size, GFP_KERNEL)
#define HDMI_KMALLOC(size)     kmalloc(size, GFP_KERNEL)

#define HDMI_KFREE(viraddr)    kfree(viraddr)
#define HDMI_VFREE(viraddr)    vfree(viraddr)

/******************************************************************************/
/* Data Structures                                                            */
/******************************************************************************/

/******************************************************************************/
/* Gloabl Data                                                                */
/******************************************************************************/

/******************************************************************************/
/* Public Interface                                                           */
/******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

