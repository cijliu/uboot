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
#include "hi_type.h"
#include "hdmi_reg_timer.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module tx_hdmi_reg */
volatile HDMI_REG_TIMER_11_S *gopsys_timer_11AllReg = NULL;
volatile HDMI_REG_SC_CTRL_S  *gopsc_ctrlAllReg = NULL;

int HDMI_REG_TIMER_11_S_Init(HI_CHAR *pcAddr)
{
#if 0
    if (HI_NULL == pcAddr)
    {
        HDMI_ERR("Input ptr is null!\n");
        return HI_FAILURE;
    }
#endif
    /* 0x12005020 */
//    gopsys_timer_11AllReg = (volatile HDMI_REG_TIMER_11_S *)(pcAddr + HDMI_SYS_TIMER_ADDR + HDMI_TIMER11_OFFSET);
    gopsys_timer_11AllReg = (volatile HDMI_REG_TIMER_11_S *)HDMI_IO_MAP(HDMI_SYS_TIMER_ADDR + HDMI_TIMER11_OFFSET, sizeof(HDMI_REG_TIMER_11_S));

    return HI_SUCCESS;
}

int HDMI_REG_TIMER_11_S_DeInit(void)
{
    if (gopsys_timer_11AllReg)
    {
        HDMI_IO_UNMAP(gopsys_timer_11AllReg);
        gopsys_timer_11AllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

int HDMI_REG_SC_CTRL_S_Init(HI_CHAR *pcAddr)
{
    if (HI_NULL != gopsc_ctrlAllReg)
    {
        HDMI_INFO("gopsc_ctrlAllReg map success!\n");
        return HI_SUCCESS;
    }

    gopsc_ctrlAllReg = (volatile HDMI_REG_SC_CTRL_S *)HDMI_IO_MAP(HDMI_ADDR_SC, 0x10000);

    return HI_SUCCESS;
}

int HDMI_REG_SC_CTRL_S_DeInit(void)
{
    if (gopsc_ctrlAllReg)
    {
        HDMI_IO_UNMAP(gopsc_ctrlAllReg);
        gopsc_ctrlAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_loadSet
//  Description : Set the value of the member U_TIMER_11_LOAD.load
//  Input       : unsigned int uload: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_loadSet(unsigned int uload)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_LOAD o_timer_11_load;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_LOAD.u32);
    o_timer_11_load.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_load.bits.load = uload;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_load.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_timer11_loadSet
//  Description : Set the value of the member U_TIMER_11_CONTROL.oneshot
//  Input       : unsigned int uoneshot: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_control_oneshotSet(unsigned int uoneshot)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_CONTROL o_timer_11_control;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_CONTROL.u32);
    o_timer_11_control.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_control.bits.oneshot = uoneshot;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_control.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_control_timersizeSet
//  Description : Set the value of the member U_TIMER_11_CONTROL.timersize
//  Input       : unsigned int utimersize: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_control_timersizeSet(unsigned int utimersize)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_CONTROL o_timer_11_control;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_CONTROL.u32);
    o_timer_11_control.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_control.bits.timersize = utimersize;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_control.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_control_timerpreSet
//  Description : Set the value of the member U_TIMER_11_CONTROL.timerpre
//  Input       : unsigned int utimerpre: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_control_timerpreSet(unsigned int utimerpre)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_CONTROL o_timer_11_control;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_CONTROL.u32);
    o_timer_11_control.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_control.bits.timerpre = utimerpre;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_control.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_control_intenableSet
//  Description : Set the value of the member U_TIMER_11_CONTROL.intenable
//  Input       : unsigned int uintenable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_control_intenableSet(unsigned int uintenable)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_CONTROL o_timer_11_control;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_CONTROL.u32);
    o_timer_11_control.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_control.bits.intenable = uintenable;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_control.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_control_timerenSet
//  Description : Set the value of the member U_TIMER_11_CONTROL.timeren
//  Input       : unsigned int utimermode: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_control_timerenSet(unsigned int utimeren)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_CONTROL o_timer_11_control;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_CONTROL.u32);
    o_timer_11_control.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_control.bits.timeren = utimeren;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_control.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_control_uintclrSet
//  Description : Set the value of the member U_TIMER_11_INTCLR.intclr
//  Input       : unsigned int uintclr: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_intclr_uintclrSet(unsigned int uintclr)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_INTCLR o_timer_11_intclr;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_INTCLR.u32);
    o_timer_11_intclr.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_intclr.bits.intclr = uintclr;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_intclr.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_TIMER_11_bgload_bgloadSet
//  Description : Set the value of the member U_TIMER_11_BGLOAD.bgload
//  Input       : unsigned int ubgload: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_TIMER_11_bgload_bgloadSet(unsigned int ubgload)
{
    HI_U32 *pu32RegAddr = NULL;
    U_TIMER_11_BGLOAD o_timer_11_bgload;
    pu32RegAddr = (HI_U32*)&(gopsys_timer_11AllReg->TIMER_11_BGLOAD.u32);
    o_timer_11_bgload.u32 = HDMITXRegRead(pu32RegAddr);
    o_timer_11_bgload.bits.bgload = ubgload;
    HDMITXRegWrite(pu32RegAddr, o_timer_11_bgload.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_REG_SC_CTRL_timerenbovSet
//  Description : Set the value of the member U_TIMER_11_BGLOAD.timerenbov
//  Input       : unsigned int utimerenbov: 32 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_REG_SC_CTRL_timerenbovSet(unsigned int utimerenbov)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SC_CTRL o_sc_ctrl;
    pu32RegAddr = (HI_U32*)&(gopsc_ctrlAllReg->SC_CTRL.u32);
    o_sc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_sc_ctrl.bits.timerenbov = utimerenbov;
    HDMITXRegWrite(pu32RegAddr, o_sc_ctrl.u32);

    return HI_SUCCESS;
}

