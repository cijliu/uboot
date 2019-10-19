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
#ifndef __DRV_HDMI_EDID_TEST_H__
#define __DRV_HDMI_EDID_TEST_H__

#include "hi_type.h"
#include "drv_hdmi_edid.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef CONFIG_HDMI_STB_SDK  
/* BVT not support debug now */
#define HDMI_EDID_RAW_TEST				1 
#endif

#ifdef HDMI_EDID_RAW_TEST

/**
\brief	read EDID TEST raw data
\param[in]    @enMode   		see HDMI_EDID_UPDATE_MODE_E
\param[in]	@u32Len		length in bytes[0~512]
\param[out]  @pau8Data		pointer to a destination data buffer
\retval  read length[0~512] / HI_FALURE
*/
HI_S32 DRV_HDMI_EdidTestRawRead(HDMI_EDID_UPDATE_MODE_E enMode,
											HI_U8 *pau8Data,
											HI_U32 u32Len);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __DRV_HDMI_EDID_TEST_H__ */  


