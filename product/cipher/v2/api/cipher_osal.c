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

#include "cipher_osal.h"

HI_S32 CIPHER_Maloc(cipher_mmz_buf_t *pstMem, HI_CHAR *name)
{
    if(pstMem->u32Size == 0)
    {
        HI_ERR_CIPHER("Error: length of malloc is invalid!\n");
        return HI_FAILURE;
    }

    pstMem->szStartPhyAddr = (HI_SIZE_T)memalign(ARCH_DMA_MINALIGN, pstMem->u32Size);
    if (0 == pstMem->szStartPhyAddr)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for hash input failed!\n");
        return HI_FAILURE;
    }
    pstMem->pu8StartVirAddr = (HI_U8*)pstMem->szStartPhyAddr;

    return HI_SUCCESS;
}

HI_S32 CIPHER_Free(cipher_mmz_buf_t *pstMem)
{
    if (pstMem->szStartPhyAddr > 0)
    {
        free(pstMem->pu8StartVirAddr);
        pstMem->szStartPhyAddr = 0;
        pstMem->pu8StartVirAddr = NULL;
    }

    return HI_SUCCESS;
}

