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
#ifndef __DRV_HDMI_DEBUG_H__
#define __DRV_HDMI_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hi_type.h"
#include "hdmi_product_define.h"
#include "drv_hdmi_edid.h"

HI_S32 DRV_HDMI_DebugSourceWrite(HDMI_PROC_ENTRY *pFile, const char *buf,
                                                    HI_U32 u32Count,
                                                    HI_S64 *ps64Data);

HI_S32 DRV_HDMI_DebugEdidRawRead(HDMI_EDID_UPDATE_MODE_E enMode,
                                        	HI_U8 *pau8Data,
                                        	HI_U32 u32Len);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __DRV_HDMI_DEBUG_H__ */


