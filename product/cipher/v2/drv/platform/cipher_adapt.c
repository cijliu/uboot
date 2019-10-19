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

HI_S32  cipher_mmz_alloc_remap(HI_CHAR *name, cipher_mmz_buf_t *pstMmz)
{

    if(pstMmz->u32Size == 0)
    {
        HI_ERR_CIPHER("Error: length of malloc is invalid!\n");
        return HI_FAILURE;
    }

    pstMmz->szStartPhyAddr = (HI_SIZE_T)memalign(ARCH_DMA_MINALIGN, pstMmz->u32Size);

    if (0 == pstMmz->szStartPhyAddr)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for cipher input failed!\n");
        return HI_FAILURE;
    }
    pstMmz->pu8StartVirAddr = (HI_U8*)pstMmz->szStartPhyAddr;

    return HI_SUCCESS;
}

HI_VOID cipher_mmz_release_unmap(cipher_mmz_buf_t *pstMmz)
{
    if (pstMmz->szStartPhyAddr > 0)
    {
        free(pstMmz->pu8StartVirAddr);
        pstMmz->szStartPhyAddr = 0;
        pstMmz->pu8StartVirAddr = NULL;
    }
}

HI_S32  cipher_mmz_map(cipher_mmz_buf_t *pstMmz)
{
    pstMmz->pu8StartVirAddr = (HI_U8*)pstMmz->szStartPhyAddr;

    return HI_SUCCESS;
}

HI_VOID cipher_mmz_unmap(cipher_mmz_buf_t *pstMmz)
{

}

HI_S32 cipher_waitdone_callback(HI_VOID *pParam)
{
    HI_BOOL *pbDone = pParam;

    pbDone = pParam;

    return  *pbDone != HI_FALSE;
}

/************************* SYSTEM API ************************/
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len)
{
    if ((dst == NULL) || (src == NULL) || (dstlen < len))
    {
        HI_ERR_CIPHER("Error: cipher call %s with invalid parameter.\n", __FUNCTION__);
        return NULL;
    }

    return memcpy(dst, src, len);
}

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len)
{
    if ((dst == NULL) || (dlen < len))
    {
        HI_ERR_CIPHER("Error: cipher call %s with invalid parameter.\n", __FUNCTION__);
        return NULL;
    }

    return memset(dst, val, len);
}

int cipher_memcmp_s(const void *a, const void *b, unsigned int len)
{
    if ((a == NULL) || (b == NULL))
    {
        HI_ERR_CIPHER("Error: cipher call %s with invalid parameter, point is null.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    if (a == b)
    {
        HI_ERR_CIPHER("Error: cipher call %s with invalid parameter, comparing with the same address.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    return memcmp(a, b, len);
}

void HEX2STR(char buf[2], HI_U8 val)
{
    HI_U8 high, low;

    high = (val >> 4) & 0x0F;
    low =  val & 0x0F;

    if(high <= 9)
    {
        buf[0] = high + '0';
    }
    else
    {
        buf[0] = (high - 0x0A) + 'A';
    }

    if(low <= 9)
    {
        buf[1] = low + '0';
    }
    else
    {
        buf[1] = (low - 0x0A) + 'A';
    }

}

void PrintData(const char*pbName, HI_U8 *pbData, HI_U32 u32Size)
{
    HI_U32 i;
    char buf[2];

    if (pbName != HI_NULL)
    {
        HI_PRINT("[%s-%p]:\n", pbName, pbData);
    }
    for (i=0; i<u32Size; i++)
    {
        HEX2STR(buf, pbData[i]);
        HI_PRINT("%c%c ", buf[0], buf[1]);
        if(((i+1) % 16) == 0)
            HI_PRINT("\n");
    }
    if (( i % 16) != 0)
    {
        HI_PRINT("\n");
    }
}

