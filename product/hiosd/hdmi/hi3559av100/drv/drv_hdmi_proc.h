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

#ifndef __DRV_HDMI_PROC_H__
#define __DRV_HDMI_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "hi_type.h"
#include "hdmi_product_define.h"

HI_S32 DRV_HDMI_ReadProc(HDMI_PROC_ENTRY *pFile);
HI_S32 DRV_HDMI_VOReadProc(HDMI_PROC_ENTRY *pFile);
HI_S32 DRV_HDMI_AOReadProc(HDMI_PROC_ENTRY *pFile);
HI_S32 DRV_HDMI_SinkReadProc(HDMI_PROC_ENTRY *pFile);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __DRV_HDMI_PROC_H__ */  


