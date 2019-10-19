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
#ifndef __HDMI_HAL_TIMER_H__
#define __HDMI_HAL_TIMER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hi_type.h"
#include "drv_hdmi_common.h"
#include "hdmi_hal_scdc.h"
#include "hdmi_hal_ddc.h"
#include "hdmi_product_define.h"

typedef HI_VOID (*TIMERCALL)(HI_VOID*);

typedef struct
{
    HI_U32      u32StartTime;
    HI_U32      u32DelayMs;    /* unit: ms */
    TIMERCALL   pIsr;
    HI_VOID     *pParam;
}TIMER_CONFIG_S;

typedef struct
{
    HI_U32      u32StartTime;
    HI_U32      u32DelayMs;    /* unit: ms */
    TIMERCALL   pIsr;
    HI_VOID     *pParam;
    HI_BOOL     bRegister;
}TIMER_CTX_S;


HI_S32 HAL_Timer_Init(TIMER_CONFIG_S *pstConfig);
HI_S32 HAL_Timer_DeInit(HI_VOID);
HI_S32 HAL_Timer_Start(HI_VOID);
HI_S32 HAL_Timer_Stop(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_HAL_TIMER_H__ */

