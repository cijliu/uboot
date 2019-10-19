/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute  it and/or modify it
* under  the terms of  the GNU General Public License as published by the
* Free Software Foundation;  either version 2 of the  License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "hi_types.h"
#include "cipher_adapt.h"

#ifdef OTP_SUPPORT

HI_VOID *g_u32EfuseOtpRegBase = HI_NULL;

/* OTP init */
HI_S32 HAL_Efuse_OTP_Init(HI_VOID)
{
    HI_U32 CrgValue = 0;
    HI_U32 *u32SysAddr = HI_NULL;

    u32SysAddr = cipher_ioremap_nocache(REG_SYS_OTP_CLK_ADDR_PHY, 0x100);
    if (u32SysAddr == HI_NULL)
    {
        HI_ERR_CIPHER("ERROR: u32SysAddr ioremap with nocache failed!!\n");
        return HI_FAILURE;
    }

    HAL_CIPHER_ReadReg(u32SysAddr, &CrgValue);
#ifdef OTP_CRG_RESET_SUPPORT
    CrgValue |= OTP_CRG_RESET_BIT;   /* reset */
    CrgValue |= OTP_CRG_CLOCK_BIT;   /* set the bit 0, clock opened */
    HAL_CIPHER_WriteReg(u32SysAddr, CrgValue);

    /* clock select and cancel reset 0x30100*/
    CrgValue &= (~OTP_CRG_RESET_BIT); /* cancel reset */
#endif
    CrgValue |= OTP_CRG_CLOCK_BIT;   /* set the bit 0, clock opened */
    HAL_CIPHER_WriteReg(u32SysAddr, CrgValue);

    cipher_iounmap(u32SysAddr);
    u32SysAddr = HI_NULL;

    g_u32EfuseOtpRegBase = cipher_ioremap_nocache(CIPHER_OTP_REG_BASE_ADDR_PHY, 0x100);
    if (g_u32EfuseOtpRegBase == HI_NULL)
    {
        HI_ERR_CIPHER("ERROR: osal_ioremap_nocache for OTP failed!!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_OTP_WaitFree(HI_VOID)
{
    HI_U32 u32TimeOutCnt = 0;
    HI_U32 u32RegValue = 0;

    while(1)
    {
        HAL_CIPHER_ReadReg(OTP_USER_CTRL_STA, &u32RegValue);
        if((u32RegValue&0x1)==0)//bit0:otp_op_busy 0:idle, 1:busy
        {
            return HI_SUCCESS;
        }

        u32TimeOutCnt++;
        if(u32TimeOutCnt >= 10000)
        {
            HI_ERR_CIPHER("OTP_WaitFree TimeOut!\n");
            break;
        }
    }
    return HI_FAILURE;
}

HI_S32 HAL_OTP_SetMode(OTP_USER_WORK_MODE_E enOtpMode)
{
    HI_U32 u32RegValue = enOtpMode;

    if(enOtpMode >= OTP_UNKOOWN_MODE)
    {
        HI_ERR_CIPHER("Mode Unknown!\n");
        return  HI_FAILURE;
    }

    (HI_VOID)HAL_CIPHER_WriteReg(OTP_USER_WORK_MODE, u32RegValue);
    return HI_SUCCESS;
}

HI_VOID HAL_OTP_OP_Start(HI_VOID)
{
    HI_U32 u32RegValue = 0x1acce551;
    (HI_VOID)HAL_CIPHER_WriteReg(OTP_USER_OP_START, u32RegValue);
}

HI_S32 HAL_OTP_Wait_OP_done(HI_VOID)
{
    HI_U32 u32TimeOutCnt = 0;
    HI_U32 u32RegValue = 0;

    while(1)
    {
        HAL_CIPHER_ReadReg(OTP_USER_CTRL_STA, &u32RegValue);
        if(u32RegValue & 0x2)
        {
            return HI_SUCCESS;
        }

        u32TimeOutCnt++;
        if(u32TimeOutCnt >= 10000)
        {
            HI_ERR_CIPHER("OTP_Wait_OP_done TimeOut!\n");
            break;
        }
    }
    return HI_FAILURE;
}

HI_VOID HAL_CHOOSE_OTP_key(OTP_USER_KEY_INDEX_E enWhichKey)
{
    HI_U32 RegValue = 0;

    RegValue = enWhichKey;
    (HI_VOID)HAL_CIPHER_WriteReg(OTP_USER_KEY_INDEX, RegValue);
}

/* set otp key to klad */
HI_S32 HAL_Efuse_OTP_LoadCipherKey(HI_U32 chn_id, HI_U32 opt_id)
{
    if(opt_id > OTP_USER_KEY3)
    {
        opt_id = OTP_USER_KEY0;
    }

    if(HI_FAILURE == HAL_OTP_WaitFree())
    {
        return HI_FAILURE;
    }
    HAL_CHOOSE_OTP_key(opt_id);

    if(HAL_OTP_SetMode(OTP_LOCK_CIPHER_KEY_MODE))
    {
        return HI_FAILURE;
    }

    HAL_OTP_OP_Start();

    if(HI_FAILURE == HAL_OTP_Wait_OP_done())
    {
        return HI_FAILURE;
    }

    return  HI_SUCCESS;
}
#endif

