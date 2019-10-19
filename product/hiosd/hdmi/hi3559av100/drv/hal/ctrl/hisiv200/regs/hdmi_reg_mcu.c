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
#include "hdmi_reg_mcu.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module mcu_cpu_reg */
volatile S_mcu_cpu_reg_REGS_TYPE *gopmcu_cpu_regAllReg = NULL;

int HDMI_TX_S_mcu_cpu_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
{
#ifdef HDMI_BUILD_IN_BOOT
    pcAddr = (HI_CHAR *)HDMI_IO_MAP(HDMI_TX_BASE_ADDR, 4);
#else
    if (HI_NULL == pcAddr)
    {
        HDMI_ERR("pcAddr is NULL!\n");
        return HI_FAILURE;
    }
#endif

    gopmcu_cpu_regAllReg = (volatile S_mcu_cpu_reg_REGS_TYPE*)(pcAddr + (HDMI_TX_BASE_ADDR_MCU));

    return HI_SUCCESS;
}

int HDMI_TX_S_mcu_cpu_reg_REGS_TYPE_DeInit(void)
{
    if (gopmcu_cpu_regAllReg)
    {
        gopmcu_cpu_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_HW_VER_B0_hdcp2x_hw_ver_b0Set
//  Description : Set the value of the member HDCP2X_HW_VER_B0.hdcp2x_hw_ver_b0
//  Input       : unsigned int uhdcp2x_hw_ver_b0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_HW_VER_B0_hdcp2x_hw_ver_b0Set(unsigned int uhdcp2x_hw_ver_b0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_HW_VER_B0 o_hdcp2x_hw_ver_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_HW_VER_B0.u32);
    o_hdcp2x_hw_ver_b0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_hw_ver_b0.bits.hdcp2x_hw_ver_b0 = uhdcp2x_hw_ver_b0;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_hw_ver_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_HW_VER_B1_hdcp2x_hw_ver_b1Set
//  Description : Set the value of the member HDCP2X_HW_VER_B1.hdcp2x_hw_ver_b1
//  Input       : unsigned int uhdcp2x_hw_ver_b1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_HW_VER_B1_hdcp2x_hw_ver_b1Set(unsigned int uhdcp2x_hw_ver_b1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_HW_VER_B1 o_hdcp2x_hw_ver_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_HW_VER_B1.u32);
    o_hdcp2x_hw_ver_b1.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_hw_ver_b1.bits.hdcp2x_hw_ver_b1 = uhdcp2x_hw_ver_b1;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_hw_ver_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_HW_VER_B2_hdcp2x_hw_ver_b2Set
//  Description : Set the value of the member HDCP2X_HW_VER_B2.hdcp2x_hw_ver_b2
//  Input       : unsigned int uhdcp2x_hw_ver_b2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_HW_VER_B2_hdcp2x_hw_ver_b2Set(unsigned int uhdcp2x_hw_ver_b2)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_HW_VER_B2 o_hdcp2x_hw_ver_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_HW_VER_B2.u32);
    o_hdcp2x_hw_ver_b2.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_hw_ver_b2.bits.hdcp2x_hw_ver_b2 = uhdcp2x_hw_ver_b2;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_hw_ver_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_HW_VER_B3_hdcp2x_hw_ver_b3Set
//  Description : Set the value of the member HDCP2X_HW_VER_B3.hdcp2x_hw_ver_b3
//  Input       : unsigned int uhdcp2x_hw_ver_b3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_HW_VER_B3_hdcp2x_hw_ver_b3Set(unsigned int uhdcp2x_hw_ver_b3)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_HW_VER_B3 o_hdcp2x_hw_ver_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_HW_VER_B3.u32);
    o_hdcp2x_hw_ver_b3.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_hw_ver_b3.bits.hdcp2x_hw_ver_b3 = uhdcp2x_hw_ver_b3;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_hw_ver_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_SW_VER_B0_hdcp2x_sw_ver_b0Get
//  Description : Set the value of the member HDCP2X_SW_VER_B0.hdcp2x_sw_ver_b0
//  Input       : unsigned int uhdcp2x_sw_ver_b0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_SW_VER_B0_hdcp2x_sw_ver_b0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_SW_VER_B0 o_hdcp2x_sw_ver_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_SW_VER_B0.u32);
    o_hdcp2x_sw_ver_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_sw_ver_b0.bits.hdcp2x_sw_ver_b0;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_SW_VER_B1_hdcp2x_sw_ver_b1Get
//  Description : Set the value of the member HDCP2X_SW_VER_B1.hdcp2x_sw_ver_b1
//  Input       : unsigned int uhdcp2x_sw_ver_b1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_SW_VER_B1_hdcp2x_sw_ver_b1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_SW_VER_B1 o_hdcp2x_sw_ver_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_SW_VER_B1.u32);
    o_hdcp2x_sw_ver_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_sw_ver_b1.bits.hdcp2x_sw_ver_b1;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_SW_VER_B2_hdcp2x_sw_ver_b2Get
//  Description : Set the value of the member HDCP2X_SW_VER_B2.hdcp2x_sw_ver_b2
//  Input       : unsigned int uhdcp2x_sw_ver_b2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_SW_VER_B2_hdcp2x_sw_ver_b2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_SW_VER_B2 o_hdcp2x_sw_ver_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_SW_VER_B2.u32);
    o_hdcp2x_sw_ver_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_sw_ver_b2.bits.hdcp2x_sw_ver_b2;
}
//******************************************************************************
//  Function    : HDMI_HDCP2X_SW_VER_B3_hdcp2x_sw_ver_b3Get
//  Description : Set the value of the member HDCP2X_SW_VER_B3.hdcp2x_sw_ver_b3
//  Input       : unsigned int uhdcp2x_sw_ver_b3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_SW_VER_B3_hdcp2x_sw_ver_b3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_SW_VER_B3 o_hdcp2x_sw_ver_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_SW_VER_B3.u32);
    o_hdcp2x_sw_ver_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_sw_ver_b3.bits.hdcp2x_sw_ver_b3;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_AUTH_CTRL_mcu_auth_stopSet
//  Description : Set the value of the member HDCP2X_AUTH_CTRL.mcu_auth_stop
//  Input       : unsigned int umcu_auth_stop: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_AUTH_CTRL_mcu_auth_stopSet(unsigned int umcu_auth_stop)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_AUTH_CTRL o_hdcp2x_auth_ctrl;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_AUTH_CTRL.u32);
    o_hdcp2x_auth_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_auth_ctrl.bits.mcu_auth_stop = umcu_auth_stop;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_auth_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_AUTH_CTRL_mcu_auth_startSet
//  Description : Set the value of the member HDCP2X_AUTH_CTRL.mcu_auth_start
//  Input       : unsigned int umcu_auth_start: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_AUTH_CTRL_mcu_auth_startSet(unsigned int umcu_auth_start)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_AUTH_CTRL o_hdcp2x_auth_ctrl;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_AUTH_CTRL.u32);
    o_hdcp2x_auth_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_auth_ctrl.bits.mcu_auth_start = umcu_auth_start;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_auth_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr7Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr7
//  Input       : unsigned int uhdcp2x_mcu_intr7: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr7Set(unsigned int uhdcp2x_mcu_intr7)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr7 = uhdcp2x_mcu_intr7;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr7Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr7
//  Input       : unsigned int uhdcp2x_mcu_intr7: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr7Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr7;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr6Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr6
//  Input       : unsigned int uhdcp2x_mcu_intr6: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr6Set(unsigned int uhdcp2x_mcu_intr6)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr6 = uhdcp2x_mcu_intr6;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr6Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr6
//  Input       : unsigned int uhdcp2x_mcu_intr6: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr6Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr6;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr5Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr5
//  Input       : unsigned int uhdcp2x_mcu_intr5: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr5Set(unsigned int uhdcp2x_mcu_intr5)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr5 = uhdcp2x_mcu_intr5;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr5Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr5
//  Input       : unsigned int uhdcp2x_mcu_intr5: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr5Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr5;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr4Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr4
//  Input       : unsigned int uhdcp2x_mcu_intr4: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr4Set(unsigned int uhdcp2x_mcu_intr4)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr4 = uhdcp2x_mcu_intr4;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr4Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr4
//  Input       : unsigned int uhdcp2x_mcu_intr4: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr4Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr4;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr3Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr3
//  Input       : unsigned int uhdcp2x_mcu_intr3: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr3Set(unsigned int uhdcp2x_mcu_intr3)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr3 = uhdcp2x_mcu_intr3;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr3Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr3
//  Input       : unsigned int uhdcp2x_mcu_intr3: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr3;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr2Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr2
//  Input       : unsigned int uhdcp2x_mcu_intr2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr2Set(unsigned int uhdcp2x_mcu_intr2)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr2 = uhdcp2x_mcu_intr2;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr2Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr2
//  Input       : unsigned int uhdcp2x_mcu_intr2: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr2;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr1Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr1
//  Input       : unsigned int uhdcp2x_mcu_intr1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr1Set(unsigned int uhdcp2x_mcu_intr1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr1 = uhdcp2x_mcu_intr1;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr1Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr1
//  Input       : unsigned int uhdcp2x_mcu_intr1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr1;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr0Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr0
//  Input       : unsigned int uhdcp2x_mcu_intr0: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr0Set(unsigned int uhdcp2x_mcu_intr0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = 0;
    o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr0 = uhdcp2x_mcu_intr0;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr0Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B0.hdcp2x_mcu_intr0
//  Input       : unsigned int uhdcp2x_mcu_intr0: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B0_hdcp2x_mcu_intr0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B0 o_hdcp2x_mcu_intr_b0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B0.u32);
    o_hdcp2x_mcu_intr_b0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b0.bits.hdcp2x_mcu_intr0;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr15Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr15
//  Input       : unsigned int uhdcp2x_mcu_intr15: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr15Set(unsigned int uhdcp2x_mcu_intr15)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr15 = uhdcp2x_mcu_intr15;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr15Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr15
//  Input       : unsigned int uhdcp2x_mcu_intr15: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr15Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr15;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr14Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr14
//  Input       : unsigned int uhdcp2x_mcu_intr14: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr14Set(unsigned int uhdcp2x_mcu_intr14)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr14 = uhdcp2x_mcu_intr14;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr14Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr14
//  Input       : unsigned int uhdcp2x_mcu_intr14: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr14Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr14;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr13Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr13
//  Input       : unsigned int uhdcp2x_mcu_intr13: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr13Set(unsigned int uhdcp2x_mcu_intr13)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr13 = uhdcp2x_mcu_intr13;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr13Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr13
//  Input       : unsigned int uhdcp2x_mcu_intr13: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr13Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr13;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr12Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr12
//  Input       : unsigned int uhdcp2x_mcu_intr12: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr12Set(unsigned int uhdcp2x_mcu_intr12)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr12 = uhdcp2x_mcu_intr12;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr12Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr12
//  Input       : unsigned int uhdcp2x_mcu_intr12: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr12Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr12;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr11Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr11
//  Input       : unsigned int uhdcp2x_mcu_intr11: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr11Set(unsigned int uhdcp2x_mcu_intr11)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr11 = uhdcp2x_mcu_intr11;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr11Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr11
//  Input       : unsigned int uhdcp2x_mcu_intr11: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr11Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr11;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr10Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr10
//  Input       : unsigned int uhdcp2x_mcu_intr10: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr10Set(unsigned int uhdcp2x_mcu_intr10)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr10 = uhdcp2x_mcu_intr10;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr10Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr10
//  Input       : unsigned int uhdcp2x_mcu_intr10: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr10Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr10;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr9Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr9
//  Input       : unsigned int uhdcp2x_mcu_intr9: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr9Set(unsigned int uhdcp2x_mcu_intr9)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr9 = uhdcp2x_mcu_intr9;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr9Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr9
//  Input       : unsigned int uhdcp2x_mcu_intr9: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr9Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr9;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr8Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr8
//  Input       : unsigned int uhdcp2x_mcu_intr8: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr8Set(unsigned int uhdcp2x_mcu_intr8)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = 0;
    o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr8 = uhdcp2x_mcu_intr8;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr8Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B1.hdcp2x_mcu_intr8
//  Input       : unsigned int uhdcp2x_mcu_intr8: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B1_hdcp2x_mcu_intr8Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B1 o_hdcp2x_mcu_intr_b1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B1.u32);
    o_hdcp2x_mcu_intr_b1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b1.bits.hdcp2x_mcu_intr8;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr23Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr23
//  Input       : unsigned int uhdcp2x_mcu_intr23: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr23Set(unsigned int uhdcp2x_mcu_intr23)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr23 = uhdcp2x_mcu_intr23;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr23Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr23
//  Input       : unsigned int uhdcp2x_mcu_intr23: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr23Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr23;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr22Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr22
//  Input       : unsigned int uhdcp2x_mcu_intr22: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr22Set(unsigned int uhdcp2x_mcu_intr22)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr22 = uhdcp2x_mcu_intr22;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr22Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr22
//  Input       : unsigned int uhdcp2x_mcu_intr22: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr22Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr22;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr21Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr21
//  Input       : unsigned int uhdcp2x_mcu_intr21: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr21Set(unsigned int uhdcp2x_mcu_intr21)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr21 = uhdcp2x_mcu_intr21;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr21Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr21
//  Input       : unsigned int uhdcp2x_mcu_intr21: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr21Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr21;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr20Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr20
//  Input       : unsigned int uhdcp2x_mcu_intr20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr20Set(unsigned int uhdcp2x_mcu_intr20)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr20 = uhdcp2x_mcu_intr20;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr20Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr20
//  Input       : unsigned int uhdcp2x_mcu_intr20: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr20Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr20;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr19Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr19
//  Input       : unsigned int uhdcp2x_mcu_intr19: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr19Set(unsigned int uhdcp2x_mcu_intr19)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr19 = uhdcp2x_mcu_intr19;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr19Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr19
//  Input       : unsigned int uhdcp2x_mcu_intr19: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr19Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr19;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr18Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr18
//  Input       : unsigned int uhdcp2x_mcu_intr18: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr18Set(unsigned int uhdcp2x_mcu_intr18)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr18 = uhdcp2x_mcu_intr18;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr18Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr18
//  Input       : unsigned int uhdcp2x_mcu_intr18: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr18Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr18;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr17Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr17
//  Input       : unsigned int uhdcp2x_mcu_intr17: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr17Set(unsigned int uhdcp2x_mcu_intr17)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr17 = uhdcp2x_mcu_intr17;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr17Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr17
//  Input       : unsigned int uhdcp2x_mcu_intr17: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr17Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr17;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr16Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr16
//  Input       : unsigned int uhdcp2x_mcu_intr16: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr16Set(unsigned int uhdcp2x_mcu_intr16)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = 0;
    o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr16 = uhdcp2x_mcu_intr16;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr16Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B2.hdcp2x_mcu_intr16
//  Input       : unsigned int uhdcp2x_mcu_intr16: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B2_hdcp2x_mcu_intr16Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B2 o_hdcp2x_mcu_intr_b2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B2.u32);
    o_hdcp2x_mcu_intr_b2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b2.bits.hdcp2x_mcu_intr16;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr31Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr31
//  Input       : unsigned int uhdcp2x_mcu_intr31: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr31Set(unsigned int uhdcp2x_mcu_intr31)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr31 = uhdcp2x_mcu_intr31;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr31Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr31
//  Input       : unsigned int uhdcp2x_mcu_intr31: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr31Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr31;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr30Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr30
//  Input       : unsigned int uhdcp2x_mcu_intr30: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr30Set(unsigned int uhdcp2x_mcu_intr30)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr30 = uhdcp2x_mcu_intr30;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr30Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr30
//  Input       : unsigned int uhdcp2x_mcu_intr30: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr30Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr30;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr29Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr29
//  Input       : unsigned int uhdcp2x_mcu_intr29: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr29Set(unsigned int uhdcp2x_mcu_intr29)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr29 = uhdcp2x_mcu_intr29;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr29Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr29
//  Input       : unsigned int uhdcp2x_mcu_intr29: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr29Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr29;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr28Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr28
//  Input       : unsigned int uhdcp2x_mcu_intr28: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr28Set(unsigned int uhdcp2x_mcu_intr28)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr28 = uhdcp2x_mcu_intr28;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr28Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr28
//  Input       : unsigned int uhdcp2x_mcu_intr28: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr28Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr28;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr27Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr27
//  Input       : unsigned int uhdcp2x_mcu_intr27: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr27Set(unsigned int uhdcp2x_mcu_intr27)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr27 = uhdcp2x_mcu_intr27;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr27Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr27
//  Input       : unsigned int uhdcp2x_mcu_intr27: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr27Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr27;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr26Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr26
//  Input       : unsigned int uhdcp2x_mcu_intr26: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr26Set(unsigned int uhdcp2x_mcu_intr26)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr26 = uhdcp2x_mcu_intr26;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr26Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr26
//  Input       : unsigned int uhdcp2x_mcu_intr26: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr26Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr26;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr25Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr25
//  Input       : unsigned int uhdcp2x_mcu_intr25: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr25Set(unsigned int uhdcp2x_mcu_intr25)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr25 = uhdcp2x_mcu_intr25;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr25Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr25
//  Input       : unsigned int uhdcp2x_mcu_intr25: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr25Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr25;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr24Set
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr24
//  Input       : unsigned int uhdcp2x_mcu_intr24: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr24Set(unsigned int uhdcp2x_mcu_intr24)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = 0;
    o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr24 = uhdcp2x_mcu_intr24;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_mcu_intr_b3.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr24Get
//  Description : Set the value of the member HDCP2X_MCU_INTR_B3.hdcp2x_mcu_intr24
//  Input       : unsigned int uhdcp2x_mcu_intr24: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_MCU_INTR_B3_hdcp2x_mcu_intr24Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_MCU_INTR_B3 o_hdcp2x_mcu_intr_b3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_MCU_INTR_B3.u32);
    o_hdcp2x_mcu_intr_b3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_mcu_intr_b3.bits.hdcp2x_mcu_intr24;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_sks_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_send_sks_done
//  Input       : unsigned int uhdcp2x_send_sks_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_sks_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_send_sks_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_l_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_send_l_done
//  Input       : unsigned int uhdcp2x_send_l_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_l_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_send_l_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_lc_init_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_lc_init_done
//  Input       : unsigned int uhdcp2x_lc_init_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_lc_init_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_lc_init_done;
}
//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_pairing_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_pairing_done
//  Input       : unsigned int uhdcp2x_pairing_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_pairing_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_pairing_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_h_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_send_h_done
//  Input       : unsigned int uhdcp2x_send_h_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_h_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_send_h_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_km_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_km_done
//  Input       : unsigned int uhdcp2x_km_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_km_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_km_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_cert_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_send_cert_done
//  Input       : unsigned int uhdcp2x_send_cert_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_send_cert_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_send_cert_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_ake_init_doneGet
//  Description : Set the value of the member HDCP2X_RX_AUTH_STATE.hdcp2x_ake_init_done
//  Input       : unsigned int uhdcp2x_ake_init_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RX_AUTH_STATE_hdcp2x_ake_init_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RX_AUTH_STATE o_hdcp2x_rx_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RX_AUTH_STATE.u32);
    o_hdcp2x_rx_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rx_auth_state.bits.hdcp2x_ake_init_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_strm_rdy_doneGet
//  Description : Set the value of the member HDCP2X_RPT_AUTH_STATE.hdcp2x_strm_rdy_done
//  Input       : unsigned int uhdcp2x_strm_rdy_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_strm_rdy_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_AUTH_STATE o_hdcp2x_rpt_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_AUTH_STATE.u32);
    o_hdcp2x_rpt_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_auth_state.bits.hdcp2x_strm_rdy_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_strm_id_doneGet
//  Description : Set the value of the member HDCP2X_RPT_AUTH_STATE.hdcp2x_strm_id_done
//  Input       : unsigned int uhdcp2x_strm_id_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_strm_id_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_AUTH_STATE o_hdcp2x_rpt_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_AUTH_STATE.u32);
    o_hdcp2x_rpt_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_auth_state.bits.hdcp2x_strm_id_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_send_ack_doneGet
//  Description : Set the value of the member HDCP2X_RPT_AUTH_STATE.hdcp2x_send_ack_done
//  Input       : unsigned int uhdcp2x_send_ack_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_send_ack_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_AUTH_STATE o_hdcp2x_rpt_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_AUTH_STATE.u32);
    o_hdcp2x_rpt_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_auth_state.bits.hdcp2x_send_ack_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_id_list_doneGet
//  Description : Set the value of the member HDCP2X_RPT_AUTH_STATE.hdcp2x_id_list_done
//  Input       : unsigned int uhdcp2x_id_list_done: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_AUTH_STATE_hdcp2x_id_list_doneGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_AUTH_STATE o_hdcp2x_rpt_auth_state;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_AUTH_STATE.u32);
    o_hdcp2x_rpt_auth_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_auth_state.bits.hdcp2x_id_list_done;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_AUTH_STATE0_hdcp2x_auth_state0Get
//  Description : Set the value of the member HDCP2X_AUTH_STATE0.hdcp2x_auth_state0
//  Input       : unsigned int uhdcp2x_auth_state0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_AUTH_STATE0_hdcp2x_auth_state0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_AUTH_STATE0 o_hdcp2x_auth_state0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_AUTH_STATE0.u32);
    o_hdcp2x_auth_state0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_auth_state0.bits.hdcp2x_auth_state0;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_AUTH_STATE1_hdcp2x_auth_state1Get
//  Description : Set the value of the member HDCP2X_AUTH_STATE1.hdcp2x_auth_state1
//  Input       : unsigned int uhdcp2x_auth_state1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_AUTH_STATE1_hdcp2x_auth_state1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_AUTH_STATE1 o_hdcp2x_auth_state1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_AUTH_STATE1.u32);
    o_hdcp2x_auth_state1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_auth_state1.bits.hdcp2x_auth_state1;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_AUTH_STATE2_hdcp2x_auth_state2Get
//  Description : Set the value of the member HDCP2X_AUTH_STATE2.hdcp2x_auth_state2
//  Input       : unsigned int uhdcp2x_auth_state2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_AUTH_STATE2_hdcp2x_auth_state2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_AUTH_STATE2 o_hdcp2x_auth_state2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_AUTH_STATE2.u32);
    o_hdcp2x_auth_state2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_auth_state2.bits.hdcp2x_auth_state2;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_AUTH_STATE3_hdcp2x_auth_state3Get
//  Description : Set the value of the member HDCP2X_AUTH_STATE3.hdcp2x_auth_state3
//  Input       : unsigned int uhdcp2x_auth_state3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_AUTH_STATE3_hdcp2x_auth_state3Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_AUTH_STATE3 o_hdcp2x_auth_state3;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_AUTH_STATE3.u32);
    o_hdcp2x_auth_state3.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_auth_state3.bits.hdcp2x_auth_state3;
}
//******************************************************************************
//  Function    : HDMI_HDCP2X_CERT_INFO_hdcp2x_cert_rptGet
//  Description : Set the value of the member HDCP2X_CERT_INFO.hdcp2x_cert_rpt
//  Input       : unsigned int uhdcp2x_cert_rpt: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_CERT_INFO_hdcp2x_cert_rptGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_CERT_INFO o_hdcp2x_cert_info;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_CERT_INFO.u32);
    o_hdcp2x_cert_info.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_cert_info.bits.hdcp2x_cert_rpt;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_CERT_VER_hdcp2x_cert_verGet
//  Description : Set the value of the member HDCP2X_CERT_VER.hdcp2x_cert_ver
//  Input       : unsigned int uhdcp2x_cert_ver: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_CERT_VER_hdcp2x_cert_verGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_CERT_VER o_hdcp2x_cert_ver;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_CERT_VER.u32);
    o_hdcp2x_cert_ver.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_cert_ver.bits.hdcp2x_cert_ver;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_INFO_hdcp2x_rpt_dev_excGet
//  Description : Set the value of the member HDCP2X_RPT_INFO.hdcp2x_rpt_dev_exc
//  Input       : unsigned int uhdcp2x_rpt_dev_exc: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_INFO_hdcp2x_rpt_dev_excGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_INFO o_hdcp2x_rpt_info;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_INFO.u32);
    o_hdcp2x_rpt_info.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_info.bits.hdcp2x_rpt_dev_exc;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_INFO_hdcp2x_rpt_cas_excGet
//  Description : Set the value of the member HDCP2X_RPT_INFO.hdcp2x_rpt_cas_exc
//  Input       : unsigned int uhdcp2x_rpt_cas_exc: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_INFO_hdcp2x_rpt_cas_excGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_INFO o_hdcp2x_rpt_info;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_INFO.u32);
    o_hdcp2x_rpt_info.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_info.bits.hdcp2x_rpt_cas_exc;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_INFO_hdcp20_rpt_onGet
//  Description : Set the value of the member HDCP2X_RPT_INFO.hdcp20_rpt_on
//  Input       : unsigned int uhdcp20_rpt_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_INFO_hdcp20_rpt_onGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_INFO o_hdcp2x_rpt_info;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_INFO.u32);
    o_hdcp2x_rpt_info.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_info.bits.hdcp20_rpt_on;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_INFO_hdcp1x_dev_onGet
//  Description : Set the value of the member HDCP2X_RPT_INFO.hdcp1x_dev_on
//  Input       : unsigned int uhdcp1x_dev_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_INFO_hdcp1x_dev_onGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_INFO o_hdcp2x_rpt_info;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_INFO.u32);
    o_hdcp2x_rpt_info.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_info.bits.hdcp1x_dev_on;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_DEV_hdcp2x_rpt_dep_cntGet
//  Description : Set the value of the member HDCP2X_RPT_DEV.hdcp2x_rpt_dep_cnt
//  Input       : unsigned int uhdcp2x_rpt_dep_cnt: 3 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_DEV_hdcp2x_rpt_dep_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_DEV o_hdcp2x_rpt_dev;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_DEV.u32);
    o_hdcp2x_rpt_dev.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_dev.bits.hdcp2x_rpt_dep_cnt;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_DEV_hdcp2x_rpt_dev_cntGet
//  Description : Set the value of the member HDCP2X_RPT_DEV.hdcp2x_rpt_dev_cnt
//  Input       : unsigned int uhdcp2x_rpt_dev_cnt: 5 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_DEV_hdcp2x_rpt_dev_cntGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_DEV o_hdcp2x_rpt_dev;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_DEV.u32);
    o_hdcp2x_rpt_dev.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_dev.bits.hdcp2x_rpt_dev_cnt;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_V0_hdcp2x_rpt_v0Get
//  Description : Set the value of the member HDCP2X_RPT_V0.hdcp2x_rpt_v0
//  Input       : unsigned int uhdcp2x_rpt_v0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_V0_hdcp2x_rpt_v0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_V0 o_hdcp2x_rpt_v0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_V0.u32);
    o_hdcp2x_rpt_v0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_v0.bits.hdcp2x_rpt_v0;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_V1_hdcp2x_rpt_v1Get
//  Description : Set the value of the member HDCP2X_RPT_V1.hdcp2x_rpt_v1
//  Input       : unsigned int uhdcp2x_rpt_v1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_V1_hdcp2x_rpt_v1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_V1 o_hdcp2x_rpt_v1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_V1.u32);
    o_hdcp2x_rpt_v1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_v1.bits.hdcp2x_rpt_v1;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_V2_hdcp2x_rpt_v2Get
//  Description : Set the value of the member HDCP2X_RPT_V2.hdcp2x_rpt_v2
//  Input       : unsigned int uhdcp2x_rpt_v2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_V2_hdcp2x_rpt_v2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_V2 o_hdcp2x_rpt_v2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_V2.u32);
    o_hdcp2x_rpt_v2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_v2.bits.hdcp2x_rpt_v2;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_K0_hdcp2x_rpt_k0Set
//  Description : Set the value of the member HDCP2X_RPT_K0.hdcp2x_rpt_k0
//  Input       : unsigned int uhdcp2x_rpt_k0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_K0_hdcp2x_rpt_k0Set(unsigned int uhdcp2x_rpt_k0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_K0 o_hdcp2x_rpt_k0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_K0.u32);
    o_hdcp2x_rpt_k0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_rpt_k0.bits.hdcp2x_rpt_k0 = uhdcp2x_rpt_k0;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_rpt_k0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_K0_hdcp2x_rpt_k0Get
//  Description : Set the value of the member HDCP2X_RPT_K0.hdcp2x_rpt_k0
//  Input       : unsigned int uhdcp2x_rpt_k0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_K0_hdcp2x_rpt_k0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_K0 o_hdcp2x_rpt_k0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_K0.u32);
    o_hdcp2x_rpt_k0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_k0.bits.hdcp2x_rpt_k0;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_K1_hdcp2x_rpt_k1Set
//  Description : Set the value of the member HDCP2X_RPT_K1.hdcp2x_rpt_k1
//  Input       : unsigned int uhdcp2x_rpt_k1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_K1_hdcp2x_rpt_k1Set(unsigned int uhdcp2x_rpt_k1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_K1 o_hdcp2x_rpt_k1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_K1.u32);
    o_hdcp2x_rpt_k1.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_rpt_k1.bits.hdcp2x_rpt_k1 = uhdcp2x_rpt_k1;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_rpt_k1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_K1_hdcp2x_rpt_k1Get
//  Description : Set the value of the member HDCP2X_RPT_K1.hdcp2x_rpt_k1
//  Input       : unsigned int uhdcp2x_rpt_k1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_K1_hdcp2x_rpt_k1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_K1 o_hdcp2x_rpt_k1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_K1.u32);
    o_hdcp2x_rpt_k1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_k1.bits.hdcp2x_rpt_k1;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_M0_hdcp2x_rpt_m0Set
//  Description : Set the value of the member HDCP2X_RPT_M0.hdcp2x_rpt_m0
//  Input       : unsigned int uhdcp2x_rpt_m0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_M0_hdcp2x_rpt_m0Set(unsigned int uhdcp2x_rpt_m0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_M0 o_hdcp2x_rpt_m0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_M0.u32);
    o_hdcp2x_rpt_m0.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_rpt_m0.bits.hdcp2x_rpt_m0 = uhdcp2x_rpt_m0;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_rpt_m0.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_M0_hdcp2x_rpt_m0Get
//  Description : Set the value of the member HDCP2X_RPT_M0.hdcp2x_rpt_m0
//  Input       : unsigned int uhdcp2x_rpt_m0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_M0_hdcp2x_rpt_m0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_M0 o_hdcp2x_rpt_m0;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_M0.u32);
    o_hdcp2x_rpt_m0.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_m0.bits.hdcp2x_rpt_m0;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_M1_hdcp2x_rpt_m1Set
//  Description : Set the value of the member HDCP2X_RPT_M1.hdcp2x_rpt_m1
//  Input       : unsigned int uhdcp2x_rpt_m1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_M1_hdcp2x_rpt_m1Set(unsigned int uhdcp2x_rpt_m1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_M1 o_hdcp2x_rpt_m1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_M1.u32);
    o_hdcp2x_rpt_m1.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_rpt_m1.bits.hdcp2x_rpt_m1 = uhdcp2x_rpt_m1;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_rpt_m1.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_M1_hdcp2x_rpt_m1Get
//  Description : Set the value of the member HDCP2X_RPT_M1.hdcp2x_rpt_m1
//  Input       : unsigned int uhdcp2x_rpt_m1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_M1_hdcp2x_rpt_m1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_M1 o_hdcp2x_rpt_m1;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_M1.u32);
    o_hdcp2x_rpt_m1.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_m1.bits.hdcp2x_rpt_m1;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_M2_hdcp2x_rpt_m2Set
//  Description : Set the value of the member HDCP2X_RPT_M2.hdcp2x_rpt_m2
//  Input       : unsigned int uhdcp2x_rpt_m2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_M2_hdcp2x_rpt_m2Set(unsigned int uhdcp2x_rpt_m2)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_M2 o_hdcp2x_rpt_m2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_M2.u32);
    o_hdcp2x_rpt_m2.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_rpt_m2.bits.hdcp2x_rpt_m2 = uhdcp2x_rpt_m2;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_rpt_m2.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_M2_hdcp2x_rpt_m2Get
//  Description : Set the value of the member HDCP2X_RPT_M2.hdcp2x_rpt_m2
//  Input       : unsigned int uhdcp2x_rpt_m2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_M2_hdcp2x_rpt_m2Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_M2 o_hdcp2x_rpt_m2;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_M2.u32);
    o_hdcp2x_rpt_m2.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_m2.bits.hdcp2x_rpt_m2;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_STRM_ID_hdcp2x_rpt_strm_idSet
//  Description : Set the value of the member HDCP2X_RPT_STRM_ID.hdcp2x_rpt_strm_id
//  Input       : unsigned int uhdcp2x_rpt_strm_id: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_STRM_ID_hdcp2x_rpt_strm_idSet(unsigned int uhdcp2x_rpt_strm_id)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_STRM_ID o_hdcp2x_rpt_strm_id;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_STRM_ID.u32);
    o_hdcp2x_rpt_strm_id.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_rpt_strm_id.bits.hdcp2x_rpt_strm_id = uhdcp2x_rpt_strm_id;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_rpt_strm_id.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_STRM_ID_hdcp2x_rpt_strm_idGet
//  Description : Set the value of the member HDCP2X_RPT_STRM_ID.hdcp2x_rpt_strm_id
//  Input       : unsigned int uhdcp2x_rpt_strm_id: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_STRM_ID_hdcp2x_rpt_strm_idGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_STRM_ID o_hdcp2x_rpt_strm_id;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_STRM_ID.u32);
    o_hdcp2x_rpt_strm_id.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_strm_id.bits.hdcp2x_rpt_strm_id;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_STRM_TPYE_hdcp2x_rpt_strm_typeSet
//  Description : Set the value of the member HDCP2X_RPT_STRM_TPYE.hdcp2x_rpt_strm_type
//  Input       : unsigned int uhdcp2x_rpt_strm_type: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_STRM_TPYE_hdcp2x_rpt_strm_typeSet(unsigned int uhdcp2x_rpt_strm_type)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_STRM_TPYE o_hdcp2x_rpt_strm_tpye;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_STRM_TPYE.u32);
    o_hdcp2x_rpt_strm_tpye.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdcp2x_rpt_strm_tpye.bits.hdcp2x_rpt_strm_type = uhdcp2x_rpt_strm_type;
    HDMITXRegWrite(pu32RegAddr, o_hdcp2x_rpt_strm_tpye.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDCP2X_RPT_STRM_TPYE_hdcp2x_rpt_strm_typeGet
//  Description : Set the value of the member HDCP2X_RPT_STRM_TPYE.hdcp2x_rpt_strm_type
//  Input       : unsigned int uhdcp2x_rpt_strm_type: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDCP2X_RPT_STRM_TPYE_hdcp2x_rpt_strm_typeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HDCP2X_RPT_STRM_TPYE o_hdcp2x_rpt_strm_tpye;
    pu32RegAddr = (HI_U32*)&(gopmcu_cpu_regAllReg->HDCP2X_RPT_STRM_TPYE.u32);
    o_hdcp2x_rpt_strm_tpye.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdcp2x_rpt_strm_tpye.bits.hdcp2x_rpt_strm_type;
}

