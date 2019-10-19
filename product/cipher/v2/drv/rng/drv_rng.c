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

#include "cipher_adapt.h"

#define  REG_RNG_BASE_ADDR                   g_u32RngRegBase
#define  HISEC_COM_TRNG_CTRL                 (REG_RNG_BASE_ADDR + 0x200)
#define  HISEC_COM_TRNG_FIFO_DATA            (REG_RNG_BASE_ADDR + 0x204)
#define  HISEC_COM_TRNG_DATA_ST              (REG_RNG_BASE_ADDR + 0x208)

HI_VOID *g_u32RngRegBase;

HI_S32 DRV_RNG_Init(HI_VOID)
{
    HI_U32 u32RngStat = 0;

    g_u32RngRegBase = cipher_ioremap_nocache(CIPHER_RNG_REG_BASE_ADDR_PHY, 0x1000);
    if (g_u32RngRegBase == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache sha2 Reg failed\n");
        return HI_FAILURE;
    }

    HAL_CIPHER_ReadReg(CIPHER_RNG_CRG_ADDR_PHY, &u32RngStat);
    u32RngStat |= RNG_CRG_CLOCK_BIT;
    u32RngStat &= ~RNG_CRG_RESET_BIT;
    HAL_CIPHER_WriteReg(CIPHER_RNG_CRG_ADDR_PHY, u32RngStat);

    return HI_SUCCESS;
}

HI_VOID DRV_RNG_DeInit(HI_VOID)
{
    cipher_iounmap(g_u32RngRegBase);
}

HI_S32 DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
    HI_U32 u32RngStat = 0;
    HI_U32 u32TimeOut = 0;

    if(NULL == pstRNG)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if(0 == pstRNG->u32TimeOutUs)
    {
        /* low 3bit(RNG_data_count[2:0]), indicate how many RNGs in the fifo is available now */
        HAL_CIPHER_ReadReg(HISEC_COM_TRNG_DATA_ST, &u32RngStat);
        if(((u32RngStat >> 8) & 0x3F) <= 0)
        {
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
        }
    }
    else
    {
        while(u32TimeOut ++ < pstRNG->u32TimeOutUs)
        {
            /* low 3bit(RNG_data_count[2:0]), indicate how many RNGs in the fifo is available now */
            HAL_CIPHER_ReadReg(HISEC_COM_TRNG_DATA_ST, &u32RngStat);
            if(((u32RngStat >> 8) & 0x3F) > 0)
            {
                break;
            }
        }
        if (u32TimeOut >= pstRNG->u32TimeOutUs)
        {
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
        }
    }

    HAL_CIPHER_ReadReg(HISEC_COM_TRNG_FIFO_DATA, &pstRNG->u32RNG);

    return HI_SUCCESS;
}

HI_U32 DRV_CIPHER_Rand(HI_VOID)
{
    CIPHER_RNG_S stRNG;

    stRNG.u32TimeOutUs = - 1;
    DRV_CIPHER_GetRandomNumber(&stRNG);

    return stRNG.u32RNG;
}

HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
    HI_S32 ret = HI_SUCCESS;

    if(NULL == pstRNG)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    ret = DRV_CIPHER_GetRandomNumber(pstRNG);

    return ret;
}

