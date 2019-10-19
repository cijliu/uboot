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
#include "hdmi_product_define.h"
#include "drv_hdmi_intf.h"
#include "hdmi_hal_intf.h"
#include "hdmi_reg_timer.h"
#include "hdmi_hal_timer.h"

extern HI_S32   g_s32HdmiIrqTimer;

#define TIMER_11_SYS_CLK            0   /* set the clock of timer 11 3MHz */
#define HI3559AV100ES_TIMER11_CLK   (3000000)
#define HI3559AV100ES_TIMER11_UNIT  (1000)
#define HI3559AV100ES_TIMER11_NAME  "HdmiTrainTimer"

TIMER_CTX_S stTimerInfo;

#define CHECK_POINTER(p) \
do{                      \
    if(HI_NULL == p){\
        return HI_ERR_HDMI_NUL_PTR;\
    } \
}while(0)

#define CHECK_POINTER_NO_RET(p) \
do{                      \
    if(HI_NULL == p){\
        HDMI_ERR("The pointer is null\n");       \
        return; \
    } \
}while(0)


HI_S32 HAL_Timer_Isr(HI_VOID *pParam)
{
    CHECK_POINTER(pParam);
    CHECK_POINTER(stTimerInfo.pIsr);

    /* disable isr */
    HAL_Timer_Stop();

    stTimerInfo.pIsr(stTimerInfo.pParam);

    return HI_SUCCESS;
}

HI_S32 HAL_Timer_Init(TIMER_CONFIG_S *pstConfig)
{
    HI_S32 s32Ret = HI_SUCCESS;

    CHECK_POINTER(pstConfig);

    if (HI_TRUE == stTimerInfo.bRegister)
    {
        HDMI_ERR("timer registered, unregister first!\n");
        return HI_FAILURE;
    }

    HDMI_MEMSET(&stTimerInfo, 0, sizeof(stTimerInfo));

    s32Ret = osal_request_irq(g_s32HdmiIrqTimer, (HI_VOID *)HAL_Timer_Isr,
                    HI_NULL, HI3559AV100ES_TIMER11_NAME, (HI_VOID *)&stTimerInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HDMI_ERR("timer irq register failed!\n");
        return HI_FAILURE;
    }

    HDMI_REG_SC_CTRL_timerenbovSet(TIMER_11_SYS_CLK);
    stTimerInfo.bRegister = HI_TRUE;

    stTimerInfo.u32DelayMs   = pstConfig->u32DelayMs;
    stTimerInfo.u32StartTime = pstConfig->u32StartTime;
    stTimerInfo.pParam       = pstConfig->pParam;
    stTimerInfo.pIsr         = pstConfig->pIsr;

    return s32Ret;
}

HI_S32 HAL_Timer_DeInit(HI_VOID)
{
    if (HI_FALSE == stTimerInfo.bRegister)
    {
        HDMI_ERR("unregister, register first!\n");
        return HI_FAILURE;
    }

    HAL_Timer_Stop();

    osal_free_irq(g_s32HdmiIrqTimer, (HI_VOID *)&stTimerInfo);


    stTimerInfo.bRegister = HI_FALSE;
    HDMI_MEMSET(&stTimerInfo, 0, sizeof(stTimerInfo));

    return HI_SUCCESS;
}

HI_S32 HAL_Timer_Start(HI_VOID)
{
    HI_U32 u32DelayTime = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == stTimerInfo.bRegister)
    {
        u32DelayTime = ((HI3559AV100ES_TIMER11_CLK / HI3559AV100ES_TIMER11_UNIT) * stTimerInfo.u32DelayMs);
        /* set reg value */
        HDMI_REG_TIMER_11_loadSet(u32DelayTime);
        HDMI_REG_TIMER_11_bgload_bgloadSet(u32DelayTime);
        /* one time */
        HDMI_REG_TIMER_11_control_oneshotSet(HI_TRUE);
        /* 32 bit mode */
        HDMI_REG_TIMER_11_control_timersizeSet(HI_TRUE);
        /* no div */
        HDMI_REG_TIMER_11_control_timerpreSet(HI_FALSE);
        /* clear interrupt */
        HDMI_REG_TIMER_11_intclr_uintclrSet(HI_FALSE);
        /* enable interrupt */
        HDMI_REG_TIMER_11_control_intenableSet(HI_TRUE);
        /* start timer */
        HDMI_REG_TIMER_11_control_timerenSet(HI_TRUE);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 HAL_Timer_Stop(HI_VOID)
{
    HDMI_REG_TIMER_11_intclr_uintclrSet(HI_FALSE);
    HDMI_REG_TIMER_11_control_intenableSet(HI_FALSE);
    HDMI_REG_TIMER_11_control_timerenSet(HI_FALSE);

    return HI_SUCCESS;
}


