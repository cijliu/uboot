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
#include "hdmi_reg_aon.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module tx_aon_reg */
volatile S_tx_aon_reg_REGS_TYPE *goptx_aon_regAllReg = NULL;

int HDMI_TX_S_tx_aon_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
{
#ifdef HDMI_BUILD_IN_BOOT
    pcAddr = (HI_CHAR *)HDMI_IO_MAP(HDMI_TX_BASE_ADDR, 4);
#else
    if (HI_NULL == pcAddr)
    {
        HDMI_ERR("pcAddr is NULL! \n");
        return HI_FAILURE;
    }
#endif

    goptx_aon_regAllReg = (volatile S_tx_aon_reg_REGS_TYPE *)(pcAddr + (HDMI_TX_BASE_ADDR_AON));

    return HI_SUCCESS;
}

int HDMI_TX_S_tx_aon_reg_REGS_TYPE_DeInit(void)
{
    if (goptx_aon_regAllReg)
    {
        goptx_aon_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

#ifndef HDMI_BUILD_IN_BOOT
#ifdef HDMI_CEC_SUPPORT
//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask13Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask13
//  Input       : unsigned int uaon_intr_mask13: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask13Set(unsigned int uaon_intr_mask13)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask13 = uaon_intr_mask13;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask12Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask12
//  Input       : unsigned int uaon_intr_mask12: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask12Set(unsigned int uaon_intr_mask12)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask12 = uaon_intr_mask12;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask11Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask11
//  Input       : unsigned int uaon_intr_mask11: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask11Set(unsigned int uaon_intr_mask11)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask11 = uaon_intr_mask11;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask10Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask10
//  Input       : unsigned int uaon_intr_mask10: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask10Set(unsigned int uaon_intr_mask10)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask10 = uaon_intr_mask10;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask9Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask9
//  Input       : unsigned int uaon_intr_mask9: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask9Set(unsigned int uaon_intr_mask9)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask9 = uaon_intr_mask9;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask8Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask8
//  Input       : unsigned int uaon_intr_mask8: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask8Set(unsigned int uaon_intr_mask8)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask8 = uaon_intr_mask8;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask7Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask7
//  Input       : unsigned int uaon_intr_mask7: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask7Set(unsigned int uaon_intr_mask7)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask7 = uaon_intr_mask7;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask6Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask6
//  Input       : unsigned int uaon_intr_mask6: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask6Set(unsigned int uaon_intr_mask6)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask6 = uaon_intr_mask6;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask5Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask5
//  Input       : unsigned int uaon_intr_mask5: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask5Set(unsigned int uaon_intr_mask5)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask5 = uaon_intr_mask5;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask4Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask4
//  Input       : unsigned int uaon_intr_mask4: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask4Set(unsigned int uaon_intr_mask4)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask4 = uaon_intr_mask4;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}
#endif

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_MASK_aon_intr_mask0Set
//  Description : Set the value of the member TX_AON_INTR_MASK.aon_intr_mask0
//  Input       : unsigned int uaon_intr_mask0: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_MASK_aon_intr_mask0Set(unsigned int uaon_intr_mask0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_MASK o_tx_aon_intr_mask;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_MASK.u32);
    o_tx_aon_intr_mask.u32 = HDMITXRegRead(pu32RegAddr);
    o_tx_aon_intr_mask.bits.aon_intr_mask0 = uaon_intr_mask0;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_mask.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat13Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat13
//  Input       : unsigned int uaon_intr_stat13: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************

#ifdef HDMI_CEC_SUPPORT
int HDMI_TX_AON_INTR_STATE_aon_intr_stat13Set(unsigned int uaon_intr_stat13)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat13 = uaon_intr_stat13;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat12Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat12
//  Input       : unsigned int uaon_intr_stat12: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat12Set(unsigned int uaon_intr_stat12)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat12 = uaon_intr_stat12;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat11
//  Input       : unsigned int uaon_intr_stat11: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set(unsigned int uaon_intr_stat11)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat11 = uaon_intr_stat11;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat10Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat10
//  Input       : unsigned int uaon_intr_stat10: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat10Set(unsigned int uaon_intr_stat10)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat10 = uaon_intr_stat10;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat9Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat9
//  Input       : unsigned int uaon_intr_stat9: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat9Set(unsigned int uaon_intr_stat9)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat9 = uaon_intr_stat9;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat8Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat8
//  Input       : unsigned int uaon_intr_stat8: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat8Set(unsigned int uaon_intr_stat8)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat8 = uaon_intr_stat8;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat7Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat7
//  Input       : unsigned int uaon_intr_stat7: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat7Set(unsigned int uaon_intr_stat7)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat7 = uaon_intr_stat7;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat6Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat6
//  Input       : unsigned int uaon_intr_stat6: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat6Set(unsigned int uaon_intr_stat6)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat6 = uaon_intr_stat6;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat5Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat5
//  Input       : unsigned int uaon_intr_stat5: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat5Set(unsigned int uaon_intr_stat5)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat5 = uaon_intr_stat5;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat4Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat4
//  Input       : unsigned int uaon_intr_stat4: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat4Set(unsigned int uaon_intr_stat4)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat4 = uaon_intr_stat4;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}
#endif

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat1Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat1
//  Input       : unsigned int uaon_intr_stat1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat1Set(unsigned int uaon_intr_stat1)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat1 = uaon_intr_stat1;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat0Set
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat0
//  Input       : unsigned int uaon_intr_stat0: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat0Set(unsigned int uaon_intr_stat0)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = 0;
    o_tx_aon_intr_state.bits.aon_intr_stat0 = uaon_intr_stat0;
    HDMITXRegWrite(pu32RegAddr, o_tx_aon_intr_state.u32);

    return HI_SUCCESS;
}
#endif

//******************************************************************************
//  Function    : HDMI_DDC_MST_CTRL_dcc_man_enSet
//  Description : Set the value of the member DDC_MST_CTRL.dcc_man_en
//  Input       : unsigned int udcc_man_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MST_CTRL_dcc_man_enSet(unsigned int udcc_man_en)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DDC_MST_CTRL o_ddc_mst_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MST_CTRL.u32);
    o_ddc_mst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_ddc_mst_ctrl.bits.dcc_man_en = udcc_man_en;
    HDMITXRegWrite(pu32RegAddr, o_ddc_mst_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DDC_MAN_CTRL_ddc_sda_oenSet
//  Description : Set the value of the member DDC_MAN_CTRL.ddc_sda_oen
//  Input       : unsigned int uddc_sda_oen: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MAN_CTRL_ddc_sda_oenSet(unsigned int uddc_sda_oen)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DDC_MAN_CTRL o_ddc_man_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MAN_CTRL.u32);
    o_ddc_man_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_ddc_man_ctrl.bits.ddc_sda_oen = uddc_sda_oen;
    HDMITXRegWrite(pu32RegAddr, o_ddc_man_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DDC_MAN_CTRL_ddc_scl_oenSet
//  Description : Set the value of the member DDC_MAN_CTRL.ddc_scl_oen
//  Input       : unsigned int uddc_scl_oen: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MAN_CTRL_ddc_scl_oenSet(unsigned int uddc_scl_oen)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DDC_MAN_CTRL o_ddc_man_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MAN_CTRL.u32);
    o_ddc_man_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_ddc_man_ctrl.bits.ddc_scl_oen = uddc_scl_oen;
    HDMITXRegWrite(pu32RegAddr, o_ddc_man_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_DDC_MST_STATE_ddc_i2c_no_ackGet
//  Description : Set the value of the member DDC_MST_STATE.ddc_i2c_no_ack
//  Input       : unsigned int uddc_i2c_no_ack: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MST_STATE_ddc_i2c_no_ackGet(void)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DDC_MST_STATE o_ddc_mst_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MST_STATE.u32);
    o_ddc_mst_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_ddc_mst_state.bits.ddc_i2c_no_ack;
}

//******************************************************************************
//  Function    : HDMI_DDC_MST_STATE_ddc_i2c_bus_lowGet
//  Description : Set the value of the member DDC_MST_STATE.ddc_i2c_bus_low
//  Input       : unsigned int uddc_i2c_bus_low: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MST_STATE_ddc_i2c_bus_lowGet(void)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DDC_MST_STATE o_ddc_mst_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MST_STATE.u32);
    o_ddc_mst_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_ddc_mst_state.bits.ddc_i2c_bus_low;
}

#ifndef HDMI_BUILD_IN_BOOT
//******************************************************************************
//  Function    : HDMI_HOTPLUG_ST_CFG_hpd_polarity_ctlGet
//  Description : Set the value of the member HOTPLUG_ST_CFG.hpd_polarity_ctl
//  Input       : unsigned int uhpd_polarity_ctl: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HOTPLUG_ST_CFG_hpd_polarity_ctlGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_HOTPLUG_ST_CFG o_hotplug_st_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->HOTPLUG_ST_CFG.u32);
    o_hotplug_st_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hotplug_st_cfg.bits.hpd_polarity_ctl;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_STATE_phy_rx_senseGet
//  Description : Set the value of the member TX_AON_STATE.phy_rx_sense
//  Input       : unsigned int uphy_rx_sense: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_STATE_phy_rx_senseGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_STATE o_tx_aon_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_STATE.u32);
    o_tx_aon_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_state.bits.phy_rx_sense;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_STATE_hotplug_stateGet
//  Description : Set the value of the member TX_AON_STATE.hotplug_state
//  Input       : unsigned int uhotplug_state: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_STATE_hotplug_stateGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_STATE o_tx_aon_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_STATE.u32);
    o_tx_aon_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_state.bits.hotplug_state;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat12Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat12
//  Input       : unsigned int uaon_intr_stat12: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
#ifdef HDMI_CEC_SUPPORT
int HDMI_TX_AON_INTR_STATE_aon_intr_stat12Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat12;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat11Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat11
//  Input       : unsigned int uaon_intr_stat11: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat11Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat11;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat9Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat9
//  Input       : unsigned int uaon_intr_stat9: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat9Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat9;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat8Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat8
//  Input       : unsigned int uaon_intr_stat8: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat8Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat8;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat7Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat7
//  Input       : unsigned int uaon_intr_stat7: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat7Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat7;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat6Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat6
//  Input       : unsigned int uaon_intr_stat6: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat6Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat6;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat5Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat5
//  Input       : unsigned int uaon_intr_stat5: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat5Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat5;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat4Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat4
//  Input       : unsigned int uaon_intr_stat4: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat4Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat4;
}
#endif

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat1Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat1
//  Input       : unsigned int uaon_intr_stat1: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat1Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat1;
}

//******************************************************************************
//  Function    : HDMI_TX_AON_INTR_STATE_aon_intr_stat0Get
//  Description : Set the value of the member TX_AON_INTR_STATE.aon_intr_stat0
//  Input       : unsigned int uaon_intr_stat0: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_TX_AON_INTR_STATE_aon_intr_stat0Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_TX_AON_INTR_STATE o_tx_aon_intr_state;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->TX_AON_INTR_STATE.u32);
    o_tx_aon_intr_state.u32 = HDMITXRegRead(pu32RegAddr);
    return o_tx_aon_intr_state.bits.aon_intr_stat0;
}
#endif

//******************************************************************************
//  Function    : HDMI_DDC_MAN_CTRL_ddc_sda_stGet
//  Description : Set the value of the member DDC_MAN_CTRL.ddc_sda_st
//  Input       : unsigned int uddc_sda_st: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MAN_CTRL_ddc_sda_stGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DDC_MAN_CTRL o_ddc_man_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MAN_CTRL.u32);
    o_ddc_man_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_ddc_man_ctrl.bits.ddc_sda_st;
}

//******************************************************************************
//  Function    : HDMI_DDC_MAN_CTRL_ddc_scl_stGet
//  Description : Set the value of the member DDC_MAN_CTRL.ddc_scl_st
//  Input       : unsigned int uddc_scl_st: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_DDC_MAN_CTRL_ddc_scl_stGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    U_DDC_MAN_CTRL o_ddc_man_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MAN_CTRL.u32);
    o_ddc_man_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_ddc_man_ctrl.bits.ddc_scl_st;
}

int HDMI_DDC_MST_CTRL_ddc_speed_cntSet(unsigned int uddc_speed_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_DDC_MST_CTRL o_ddc_mst_ctrl;

    pu32RegAddr = (HI_U32*)&(goptx_aon_regAllReg->DDC_MST_CTRL.u32);
    o_ddc_mst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_ddc_mst_ctrl.bits.ddc_speed_cnt = uddc_speed_cnt;
    HDMITXRegWrite(pu32RegAddr, o_ddc_mst_ctrl.u32);

    return HI_SUCCESS;
}


