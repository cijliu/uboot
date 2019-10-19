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
#ifndef __HDMI_HAL_NCTS_H__
#define __HDMI_HAL_NCTS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hi_type.h"

typedef struct{
    HI_U32      u32AudioSmpRate;
    HI_U32      u32TmdsClk;
    HI_U32      u32NValue;
    HI_U32      u32CtsValue;
}HDMI_AUDIO_CTS_N_S;


HI_U32 HAL_HDMI_NValueGet(HI_U32 u32SampleRate,HI_U32 u32TmdsClk);

HI_U32 HAL_HDMI_CtsValueGet(HI_U32 u32SampleRate,HI_U32 u32TmdsClk);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_HAL_NCTS_H__ */


