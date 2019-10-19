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

#define HASH_MAX_BLOCK_SIZE         (256)
#define SHA1_RESULT_SIZE            (20)
#define SHA224_RESULT_SIZE          (28)
#define SHA256_RESULT_SIZE          (32)
#define SHA384_RESULT_SIZE          (48)
#define SHA512_RESULT_SIZE          (64)

#define SPACC_HASH_CHN               1
#define HASH_CHANNAL_MAX_NUM         (8)

#define SHA1_H0     0x67452301
#define SHA1_H1     0xefcdab89
#define SHA1_H2     0x98badcfe
#define SHA1_H3     0x10325476
#define SHA1_H4     0xc3d2e1f0

#define SHA224_H0    0xc1059ed8
#define SHA224_H1    0x367cd507
#define SHA224_H2    0x3070dd17
#define SHA224_H3    0xf70e5939
#define SHA224_H4    0xffc00b31
#define SHA224_H5    0x68581511
#define SHA224_H6    0x64f98fa7
#define SHA224_H7    0xbefa4fa4

#define SHA256_H0    0x6a09e667
#define SHA256_H1    0xbb67ae85
#define SHA256_H2    0x3c6ef372
#define SHA256_H3    0xa54ff53a
#define SHA256_H4    0x510e527f
#define SHA256_H5    0x9b05688c
#define SHA256_H6    0x1f83d9ab
#define SHA256_H7    0x5be0cd19

#define SHA384_H0    0xcbbb9d5dc1059ed8ULL
#define SHA384_H1    0x629a292a367cd507ULL
#define SHA384_H2    0x9159015a3070dd17ULL
#define SHA384_H3    0x152fecd8f70e5939ULL
#define SHA384_H4    0x67332667ffc00b31ULL
#define SHA384_H5    0x8eb44a8768581511ULL
#define SHA384_H6    0xdb0c2e0d64f98fa7ULL
#define SHA384_H7    0x47b5481dbefa4fa4ULL

#define SHA512_H0    0x6a09e667f3bcc908ULL
#define SHA512_H1    0xbb67ae8584caa73bULL
#define SHA512_H2    0x3c6ef372fe94f82bULL
#define SHA512_H3    0xa54ff53a5f1d36f1ULL
#define SHA512_H4    0x510e527fade682d1ULL
#define SHA512_H5    0x9b05688c2b3e6c1fULL
#define SHA512_H6    0x1f83d9abfb41bd6bULL
#define SHA512_H7    0x5be0cd19137e2179ULL

#define SM3_H0    0x7380166F
#define SM3_H1    0x4914B2B9
#define SM3_H2    0x172442D7
#define SM3_H3    0xDA8A0600
#define SM3_H4    0xA96F30BC
#define SM3_H5    0x163138AA
#define SM3_H6    0xE38DEE4D
#define SM3_H7    0xB0FB0E4E


typedef struct hiHASH_INFO_S
{
    HI_HANDLE hHandle;
    HI_UNF_CIPHER_HASH_TYPE_E enShaType;

    HI_U8 bIsUsed;
    HI_U8 u8BlockSize;
    HI_U8 u8ShaLen;
    HI_U8 u8LastBlockSize;

    HI_U32 u32TotalDataLen;
    HI_U32 u32ShaVal[HASH_RESULT_MAX_LEN_IN_WORD];
    HI_U8  u8LastBlock[HASH_MAX_BLOCK_SIZE];
    HI_U8  u8Mac[HASH_MAX_BLOCK_SIZE];
}HASH_INFO_S;

#define HI_ID_HASH              101
static HASH_INFO_S g_stCipherHashData[HASH_CHANNAL_MAX_NUM];

#define HASH_CHECK_HANDLE(hHashHandle)   \
do \
{ \
    if ((HI_ID_HASH != HI_HANDLE_GET_MODID(hHashHandle)) \
        || (0 != HI_HANDLE_GET_PriDATA(hHashHandle)))\
    { \
        HI_ERR_CIPHER("invalid cipher handle 0x%x\n", hHashHandle); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
    if (HASH_CHANNAL_MAX_NUM <= HI_HANDLE_GET_CHNID(hHashHandle)) \
    { \
        HI_ERR_CIPHER("chan %d is too large, max: %d\n", HI_HANDLE_GET_CHNID(hHashHandle), HASH_CHANNAL_MAX_NUM); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
    if (HI_FALSE == g_stCipherHashData[HI_HANDLE_GET_CHNID(hHashHandle)].bIsUsed) \
    { \
        HI_ERR_CIPHER("chan %d is not open\n", HI_HANDLE_GET_CHNID(hHashHandle)); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
} while (0)

static HI_U32 HashMsgPadding(HI_U8 *pu8Msg, HI_U32 u32ByteLen, HI_U32 u32TotalLen, HI_U32 u8BlockSize)
{
    HI_U32 u32Tmp = 0;
    HI_U32 u32PaddingLen;

    if (u8BlockSize == 0)
    {
        HI_ERR_CIPHER("Bloc size is zero !\n");
        return HI_FAILURE;
    }

    u32Tmp = u32TotalLen % u8BlockSize;
    if (u8BlockSize == 64)
    {
        u32PaddingLen = (u32Tmp < 56) ? (56 - u32Tmp) : (120 - u32Tmp);
        u32PaddingLen += 8;
    }
    else
    {
        u32PaddingLen = (u32Tmp < 112) ? (112 - u32Tmp) : (240 - u32Tmp);
        u32PaddingLen += 16;
    }

    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    pu8Msg[u32ByteLen++] = 0x80;
    cipher_memset_s(&pu8Msg[u32ByteLen], HASH_BLOCK_SIZE * 2, 0, u32PaddingLen - 1 - 8);
    u32ByteLen+=u32PaddingLen - 1 - 8;

    /* write 8 bytes fix data length */
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 29)&0x07);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 21)&0xff);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 13)&0xff);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 5)&0xff);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen << 3)&0xff);

    return u32ByteLen;
}

static HI_S32 CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S stHashData;
    HI_U32 u32SoftId;
    HASH_INFO_S *pstHashInfo;
    HI_U64 u64H;

    for(u32SoftId=0; u32SoftId<HASH_CHANNAL_MAX_NUM; u32SoftId++)
    {
        if (!g_stCipherHashData[u32SoftId].bIsUsed)
        {
            break;
        }
    }

    if(u32SoftId >= HASH_CHANNAL_MAX_NUM)
    {
        HI_ERR_CIPHER("Hash module is busy!\n");
        return HI_FAILURE;
    }

    pstHashInfo = &g_stCipherHashData[u32SoftId];
    cipher_memset_s(pstHashInfo, sizeof(HASH_INFO_S), 0, sizeof(HASH_INFO_S));
    cipher_memset_s(&stHashData, sizeof(stHashData), 0, sizeof(CIPHER_HASH_DATA_S));
    pstHashInfo->enShaType = pstHashAttr->eShaType;

    switch(pstHashAttr->eShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1:
        stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
        pstHashInfo->u8ShaLen = SHA1_RESULT_SIZE;
        pstHashInfo->u8BlockSize = 64;
        pstHashInfo->u32ShaVal[0] = CPU_TO_BE32(SHA1_H0);
        pstHashInfo->u32ShaVal[1] = CPU_TO_BE32(SHA1_H1);
        pstHashInfo->u32ShaVal[2] = CPU_TO_BE32(SHA1_H2);
        pstHashInfo->u32ShaVal[3] = CPU_TO_BE32(SHA1_H3);
        pstHashInfo->u32ShaVal[4] = CPU_TO_BE32(SHA1_H4);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA224:
        stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA224;
        pstHashInfo->u8ShaLen = SHA224_RESULT_SIZE;
        pstHashInfo->u8BlockSize = 64;
        pstHashInfo->u32ShaVal[0] = CPU_TO_BE32(SHA224_H0);
        pstHashInfo->u32ShaVal[1] = CPU_TO_BE32(SHA224_H1);
        pstHashInfo->u32ShaVal[2] = CPU_TO_BE32(SHA224_H2);
        pstHashInfo->u32ShaVal[3] = CPU_TO_BE32(SHA224_H3);
        pstHashInfo->u32ShaVal[4] = CPU_TO_BE32(SHA224_H4);
        pstHashInfo->u32ShaVal[5] = CPU_TO_BE32(SHA224_H5);
        pstHashInfo->u32ShaVal[6] = CPU_TO_BE32(SHA224_H6);
        pstHashInfo->u32ShaVal[7] = CPU_TO_BE32(SHA224_H7);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256:
        stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
        pstHashInfo->u8ShaLen = SHA256_RESULT_SIZE;
        pstHashInfo->u8BlockSize = 64;
        pstHashInfo->u32ShaVal[0] = CPU_TO_BE32(SHA256_H0);
        pstHashInfo->u32ShaVal[1] = CPU_TO_BE32(SHA256_H1);
        pstHashInfo->u32ShaVal[2] = CPU_TO_BE32(SHA256_H2);
        pstHashInfo->u32ShaVal[3] = CPU_TO_BE32(SHA256_H3);
        pstHashInfo->u32ShaVal[4] = CPU_TO_BE32(SHA256_H4);
        pstHashInfo->u32ShaVal[5] = CPU_TO_BE32(SHA256_H5);
        pstHashInfo->u32ShaVal[6] = CPU_TO_BE32(SHA256_H6);
        pstHashInfo->u32ShaVal[7] = CPU_TO_BE32(SHA256_H7);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384:
        stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA384;
        pstHashInfo->u8ShaLen = SHA384_RESULT_SIZE;
        pstHashInfo->u8BlockSize = 128;
        u64H = CPU_TO_BE64(SHA384_H0);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[0], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA384_H1);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[2], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA384_H2);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[4], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA384_H3);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[6], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA384_H4);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[8], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA384_H5);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[10], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA384_H6);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[12], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA384_H7);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[14], 8, &u64H, 8);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA512:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA512:
        stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA512;
        pstHashInfo->u8ShaLen = SHA512_RESULT_SIZE;
        pstHashInfo->u8BlockSize = 128;
        u64H = CPU_TO_BE64(SHA512_H0);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[0], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA512_H1);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[2], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA512_H2);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[4], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA512_H3);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[6], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA512_H4);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[8], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA512_H5);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[10], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA512_H6);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[12], 8, &u64H, 8);
        u64H = CPU_TO_BE64(SHA512_H7);
        cipher_memcpy_s(&pstHashInfo->u32ShaVal[14], 8, &u64H, 8);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SM3:
        stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SM3;
        pstHashInfo->u8ShaLen = SHA256_RESULT_SIZE;
        pstHashInfo->u8BlockSize = 64;
        pstHashInfo->u32ShaVal[0] = CPU_TO_BE32(SM3_H0);
        pstHashInfo->u32ShaVal[1] = CPU_TO_BE32(SM3_H1);
        pstHashInfo->u32ShaVal[2] = CPU_TO_BE32(SM3_H2);
        pstHashInfo->u32ShaVal[3] = CPU_TO_BE32(SM3_H3);
        pstHashInfo->u32ShaVal[4] = CPU_TO_BE32(SM3_H4);
        pstHashInfo->u32ShaVal[5] = CPU_TO_BE32(SM3_H5);
        pstHashInfo->u32ShaVal[6] = CPU_TO_BE32(SM3_H6);
        pstHashInfo->u32ShaVal[7] = CPU_TO_BE32(SM3_H7);
        break;
    default:
        HI_ERR_CIPHER("Invaid sha type %d\n", pstHashAttr->eShaType);
        break;
    }

    stHashData.u32HardChn = SPACC_HASH_CHN;

    ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHINIT, &stHashData);
    if (ret == HI_SUCCESS)
    {
        pstHashInfo->bIsUsed = HI_TRUE;
        *pHashHandle = HI_HANDLE_MAKEHANDLE(HI_ID_HASH, 0, u32SoftId);
    }

    return ret;
}

static HI_S32 CIPHER_HashUpdateBlock(HASH_INFO_S *pstHashInfo, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_FAILURE;
    CIPHER_HASH_DATA_S stHashData;

    cipher_memset_s(&stHashData, sizeof(stHashData), 0, sizeof(stHashData));
    stHashData.enShaType = pstHashInfo->enShaType;
    stHashData.u32HardChn = SPACC_HASH_CHN;
    cipher_memcpy_s(&stHashData.u32ShaVal, sizeof(stHashData.u32ShaVal),
        pstHashInfo->u32ShaVal, sizeof(pstHashInfo->u32ShaVal));

    stHashData.u32DataLen = u32InputDataLen;
    stHashData.u32DataPhy = GET_ULONG_LOW((HI_SIZE_T)pu8InputData);
    stHashData.u32DataPhyHigh = GET_ULONG_HIGH((HI_SIZE_T)pu8InputData);
    ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHUPDATE, &stHashData);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return ret;
    }

    cipher_memcpy_s(pstHashInfo->u32ShaVal, sizeof(pstHashInfo->u32ShaVal),
        &stHashData.u32ShaVal, sizeof(stHashData.u32ShaVal));

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HashUpdate(HI_HANDLE hCIHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo = HI_NULL;
    HI_U32 u32Size = 0;
    HI_U8 *u8DataPhy = HI_NULL;
    HI_U32 hHashHandle = 0;

    if (NULL == pu8InputData)
    {
        HI_ERR_CIPHER("Invalid point!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (0 == u32InputDataLen)
    {
        return HI_SUCCESS;
    }

    HASH_CHECK_HANDLE(hCIHashHandle);
    hHashHandle = HI_HANDLE_GET_CHNID(hCIHashHandle);
    pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[hHashHandle];

    u8DataPhy = (HI_U8*)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (HI_NULL == u8DataPhy)
    {
        HI_ERR_CIPHER("Error, memalign for u8DataPhy failed!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return HI_FAILURE;
    }

    cipher_memset_s(u8DataPhy, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);

    if ((u32InputDataLen + pstHashInfo->u32TotalDataLen < u32InputDataLen)
        || (u32InputDataLen + pstHashInfo->u8LastBlockSize < u32InputDataLen))
    {
        HI_ERR_CIPHER("Error, input len is too large!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        free(u8DataPhy);
        u8DataPhy = HI_NULL;
        return HI_FAILURE;
    }

    pstHashInfo->u32TotalDataLen += u32InputDataLen;
    u32Size = pstHashInfo->u8LastBlockSize + u32InputDataLen;
    if( u32Size < pstHashInfo->u8BlockSize )
    {
        cipher_memcpy_s(pstHashInfo->u8LastBlock+pstHashInfo->u8LastBlockSize, HASH_BLOCK_SIZE,
            pu8InputData, u32InputDataLen);
        pstHashInfo->u8LastBlockSize+=u32InputDataLen;
        free(u8DataPhy);
        u8DataPhy = HI_NULL;
        return HI_SUCCESS;
    }

    /* process the tail of last update */
    if ( 0 < pstHashInfo->u8LastBlockSize )
    {
        cipher_memcpy_s(pstHashInfo->u8LastBlock + pstHashInfo->u8LastBlockSize, HASH_BLOCK_SIZE,
            pu8InputData, pstHashInfo->u8BlockSize - pstHashInfo->u8LastBlockSize);
        cipher_memcpy_s(u8DataPhy, pstHashInfo->u8BlockSize, pstHashInfo->u8LastBlock, pstHashInfo->u8BlockSize);
        ret = CIPHER_HashUpdateBlock(pstHashInfo, u8DataPhy, pstHashInfo->u8BlockSize);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
            pstHashInfo->bIsUsed = HI_FALSE;
            free(u8DataPhy);
            u8DataPhy = HI_NULL;
            return ret;
        }
        u32InputDataLen -= pstHashInfo->u8BlockSize - pstHashInfo->u8LastBlockSize;
        pu8InputData += pstHashInfo->u8BlockSize - pstHashInfo->u8LastBlockSize;
    }

    if (u32InputDataLen >= pstHashInfo->u8BlockSize)
    {
        u32Size = u32InputDataLen - (u32InputDataLen % pstHashInfo->u8BlockSize);
        ret = CIPHER_HashUpdateBlock(pstHashInfo, pu8InputData, u32Size);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
            pstHashInfo->bIsUsed = HI_FALSE;
            free(u8DataPhy);
            u8DataPhy = HI_NULL;
            return ret;
        }
        u32InputDataLen -= u32Size;
        pu8InputData += u32Size;
    }

    /* save tail data */
    cipher_memset_s(pstHashInfo->u8LastBlock, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);
    pstHashInfo->u8LastBlockSize = u32InputDataLen;
    cipher_memcpy_s(pstHashInfo->u8LastBlock, HASH_BLOCK_SIZE, pu8InputData, u32InputDataLen);

    free(u8DataPhy);
    u8DataPhy = HI_NULL;

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HashFinal(HI_HANDLE hCIHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo = HI_NULL;
    CIPHER_HASH_DATA_S stHashData;
    HI_U32 u32Tmp = 0;
    HI_U8 *u8DataPhy = HI_NULL;
    HI_U32 hHashHandle = 0;

    if (NULL == pu8OutputHash)
    {
        HI_ERR_CIPHER("Invalid point!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    HASH_CHECK_HANDLE(hCIHashHandle);
    hHashHandle = HI_HANDLE_GET_CHNID(hCIHashHandle);
    pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[hHashHandle];

    u8DataPhy = (HI_U8*)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (NULL == u8DataPhy)
    {
        HI_ERR_CIPHER("memalign for data phy failed!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return HI_ERR_CIPHER_INVALID_POINT;
    }
    cipher_memset_s(u8DataPhy, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);

    cipher_memset_s(&stHashData, sizeof(CIPHER_HASH_DATA_S), 0, sizeof(CIPHER_HASH_DATA_S));

    u32Tmp = HashMsgPadding(pstHashInfo->u8LastBlock, pstHashInfo->u8LastBlockSize,
        pstHashInfo->u32TotalDataLen, pstHashInfo->u8BlockSize);

    cipher_memcpy_s(u8DataPhy, u32Tmp, pstHashInfo->u8LastBlock, u32Tmp);

    stHashData.enShaType = pstHashInfo->enShaType;
    stHashData.u32DataLen = u32Tmp;
    stHashData.u32DataPhy = GET_ULONG_LOW((HI_SIZE_T)(u8DataPhy));
    stHashData.u32DataPhyHigh = GET_ULONG_HIGH((HI_SIZE_T)(u8DataPhy));
    cipher_memcpy_s(stHashData.u32ShaVal, sizeof(stHashData.u32ShaVal),
        pstHashInfo->u32ShaVal, sizeof(pstHashInfo->u32ShaVal));
    stHashData.u32HardChn = SPACC_HASH_CHN;

    ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHFINAL, &stHashData);
    cipher_memcpy_s(pu8OutputHash, HASH_RESULT_MAX_LEN,
        stHashData.u32ShaVal, pstHashInfo->u8ShaLen);
    pstHashInfo->bIsUsed = HI_FALSE;

    free(u8DataPhy);
    u8DataPhy = HI_NULL;

    return ret;
}

static HI_S32 CIPHER_HmacKeyInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_U8 au8Hmackey[HASH_MAX_BLOCK_SIZE])
{
    HI_HANDLE hHash = 0;

    if ((pstHashAttr->eShaType == HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384)
        || (pstHashAttr->eShaType == HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA512))
    {
        /*key length is less than 128bytes, copy directly*/
        if(pstHashAttr->u32HMACKeyLen <= 128)
        {
            cipher_memcpy_s(au8Hmackey, HASH_MAX_BLOCK_SIZE, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
            return HI_SUCCESS;
        }
    }
    else
    {
        /*key length is less than 64bytes, copy directly*/
        if(pstHashAttr->u32HMACKeyLen <= 64)
        {
            cipher_memcpy_s(au8Hmackey, HASH_MAX_BLOCK_SIZE, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
            return HI_SUCCESS;
        }
    }

    /*key length more than 64bytes, calcute the hash result*/
    return CIPHER_HashInit(pstHashAttr, &hHash)
          || CIPHER_HashUpdate(hHash, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen)
          || CIPHER_HashFinal(hHash,au8Hmackey);
}

static HI_S32 CIPHER_HmacInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8* key_pad = HI_NULL;
    HASH_INFO_S *pstHashInfo;
    HI_U32 i = 0;
    HI_U32 u32SoftId = 0;

    INLET_PARAM_CHECK_POINT_NULL(pstHashAttr->pu8HMACKey);
    INLET_PARAM_CHECK_U32_ZERO(pstHashAttr->u32HMACKeyLen);

    key_pad = (HI_U8*)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (HI_NULL == key_pad)
    {
        HI_ERR_CIPHER("memalign for key_pad failed!\n");
        return HI_FAILURE;
    }

    memset(key_pad, 0, HASH_MAX_BLOCK_SIZE);

    /* Init hmac key */
    ret = CIPHER_HmacKeyInit(pstHashAttr, key_pad);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Hmac key initial failed!\n");
        free(key_pad);
        key_pad = HI_NULL;
        return HI_FAILURE;
    }

    /* hash i_key_pad and message start */
    ret = CIPHER_HashInit(pstHashAttr, pHashHandle);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("hash i_key_pad and message start failed!\n");
        free(key_pad);
        key_pad = HI_NULL;
        return HI_FAILURE;
    }
    u32SoftId = HI_HANDLE_GET_CHNID(*pHashHandle);
    pstHashInfo = (HASH_INFO_S *)&g_stCipherHashData[u32SoftId];
    cipher_memcpy_s(pstHashInfo->u8Mac, sizeof(pstHashInfo->u8Mac), key_pad, pstHashInfo->u8BlockSize);

    /* generate i_key_pad */
    for(i=0; i < pstHashInfo->u8BlockSize; i++)
    {
        key_pad[i] ^= 0x36;
    }

    /* hash i_key_pad update */
    ret = CIPHER_HashUpdate(*pHashHandle, key_pad, pstHashInfo->u8BlockSize);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("cipher hash update failed!\n");
        free(key_pad);
        key_pad = HI_NULL;
        return ret;
    }

    free(key_pad);
    key_pad = HI_NULL;

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HmacUpdate(HI_HANDLE hCIHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    return CIPHER_HashUpdate(hCIHashHandle, pu8InputData, u32InputDataLen);
}

static HI_S32 CIPHER_HmacFinal(HI_HANDLE hCIHashHandle, HI_U8 *pu8Output)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo;
    HI_HANDLE hHash = HI_INVALID_HANDLE;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8* hash_sum_1 = HI_NULL;
    HI_U8* key_pad = HI_NULL;
    HI_U32 u32ShaSize = 0;
    HI_U32 i;
    HI_U32 hHashHandle = 0;

    HASH_CHECK_HANDLE(hCIHashHandle);
    hHashHandle = HI_HANDLE_GET_CHNID(hCIHashHandle);
    pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[hHashHandle];

    key_pad = (HI_U8*)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (HI_NULL == key_pad)
    {
        HI_ERR_CIPHER("memalign for key_pad failed!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return HI_FAILURE;
    }
    hash_sum_1 = (HI_U8*)memalign(ARCH_DMA_MINALIGN, HASH_RESULT_MAX_LEN);
    if (HI_NULL == hash_sum_1)
    {
        HI_ERR_CIPHER("memalign for key_pad failed!\n");
        free(key_pad);
        key_pad = HI_NULL;
        pstHashInfo->bIsUsed = HI_FALSE;
        return HI_FAILURE;
    }

    cipher_memset_s(key_pad, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);
    cipher_memset_s(hash_sum_1, HASH_RESULT_MAX_LEN, 0, HASH_RESULT_MAX_LEN);
    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = pstHashInfo->enShaType;
    cipher_memcpy_s(key_pad, HASH_MAX_BLOCK_SIZE, pstHashInfo->u8Mac, pstHashInfo->u8BlockSize);

    /* hash i_key_pad+message finished */
    ret = CIPHER_HashFinal(hCIHashHandle, hash_sum_1);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final i_key_pad+message failure, ret=%d\n", ret);
        free(key_pad);
        key_pad = HI_NULL;
        free(hash_sum_1);
        hash_sum_1 = HI_NULL;
        return HI_FAILURE;
    }

    /* generate o_key_pad */
    for(i=0; i < pstHashInfo->u8BlockSize; i++)
    {
        key_pad[i] ^= 0x5c;
    }

    if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA224 == stHashAttr.eShaType )
    {
        u32ShaSize = SHA224_RESULT_SIZE;
    }
    else if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384 == stHashAttr.eShaType )
    {
        u32ShaSize = SHA384_RESULT_SIZE;
    }
    else
    {
        u32ShaSize = pstHashInfo->u8ShaLen;
    }

    /* hash o_key_pad+hash_sum_1 start */
    ret = CIPHER_HashInit(&stHashAttr, &hHash)
          || CIPHER_HashUpdate(hHash, key_pad, pstHashInfo->u8BlockSize)
          || CIPHER_HashUpdate(hHash, hash_sum_1, u32ShaSize)
          || CIPHER_HashFinal(hHash, pu8Output);
    free(key_pad);
    key_pad = HI_NULL;
    free(hash_sum_1);
    hash_sum_1 = HI_NULL;

    return ret;
}

HI_S32 HI_MPI_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_FAILURE;

    if((NULL == pstHashAttr) || (NULL == pHashHandle))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    switch(pstHashAttr->eShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
    case HI_UNF_CIPHER_HASH_TYPE_SHA512:
    case HI_UNF_CIPHER_HASH_TYPE_SM3:
    {
        ret = CIPHER_HashInit(pstHashAttr, pHashHandle);
        break;
    }
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA512:
    {
        ret = CIPHER_HmacInit(pstHashAttr, pHashHandle);
        break;
    }
    default:
        HI_ERR_CIPHER("Invalid sha type %d!\n", pstHashAttr->eShaType);
        break;
    }

    return ret;
}

HI_S32 HI_MPI_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32SoftId = 0;
    HASH_INFO_S *pstHashInfo = HI_NULL;

    if (NULL == pu8InputData)
    {
        HI_ERR_CIPHER("Invalid point!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    HASH_CHECK_HANDLE(hHashHandle);
    u32SoftId = HI_HANDLE_GET_CHNID(hHashHandle);
    pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[u32SoftId];

    switch(pstHashInfo->enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
    case HI_UNF_CIPHER_HASH_TYPE_SHA512:
    case HI_UNF_CIPHER_HASH_TYPE_SM3:
    {
        ret = CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
        break;
    }
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA512:
    {
        ret = CIPHER_HmacUpdate(hHashHandle, pu8InputData, u32InputDataLen);
        break;
    }
    default:
        HI_ERR_CIPHER("Invalid sha type %d!\n", pstHashInfo->enShaType);
        break;
    }

    return ret;
}

HI_S32 HI_MPI_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32SoftId = 0;
    HASH_INFO_S *pstHashInfo = HI_NULL;

    if (NULL == pu8OutputHash)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    HASH_CHECK_HANDLE(hHashHandle);
    u32SoftId = HI_HANDLE_GET_CHNID(hHashHandle);
    pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[u32SoftId];

    switch(pstHashInfo->enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
    case HI_UNF_CIPHER_HASH_TYPE_SHA512:
    case HI_UNF_CIPHER_HASH_TYPE_SM3:
    {
        ret = CIPHER_HashFinal(hHashHandle, pu8OutputHash);
        break;
    }
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA512:
    {
        ret = CIPHER_HmacFinal(hHashHandle, pu8OutputHash);
        break;
    }
    default:
        HI_ERR_CIPHER("Invalid sha type %d!\n", pstHashInfo->enShaType);
        break;
    }

    return ret;
}


