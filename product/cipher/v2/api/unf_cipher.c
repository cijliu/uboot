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

#define HI_CIPHER_LOCK()
#define HI_CIPHER_UNLOCK()
#define HI_HASH_LOCK()
#define HI_HASH_UNLOCK()
HI_S32 g_CipherDevFd = -1;
static HI_S32 g_CipherInitCounter = -1;

#define CHECK_CIPHER_OPEN()\
do{\
    if (g_CipherInitCounter < 0)\
    {\
        HI_ERR_CIPHER("CIPHER is not open.\n");\
        return HI_ERR_CIPHER_NOT_INIT;\
    }\
}while(0)

HI_S32 HI_UNF_CIPHER_Init(HI_VOID)
{
    HI_CIPHER_LOCK();

    if (g_CipherInitCounter > 0)
    {
        g_CipherInitCounter++;
        HI_CIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    g_CipherDevFd = cipher_open("/dev/"UMAP_DEVNAME_CIPHER, O_RDWR, 0);
    if (g_CipherDevFd < 0)
    {
        HI_ERR_CIPHER("Open CIPHER err.\n");
        HI_CIPHER_UNLOCK();
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    g_CipherInitCounter = 1;
    HI_CIPHER_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_UNF_CIPHER_DeInit(HI_VOID)
{
    HI_CIPHER_LOCK();

    if(g_CipherInitCounter > 0)
    {
        g_CipherInitCounter--;
    }

    if(g_CipherInitCounter != 0)
    {
        HI_CIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    cipher_close(g_CipherDevFd);

    g_CipherInitCounter = -1;

    HI_CIPHER_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_UNF_CIPHER_CreateHandle(HI_HANDLE* phCipher, HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_CreateHandle(phCipher, pstCipherAttr);
}

HI_S32 HI_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_DestroyHandle(hCipher);
}

HI_S32 HI_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_ConfigHandle(hCipher, pstCtrl);
}

HI_S32 HI_UNF_CIPHER_ConfigHandleEx(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_EX_S* pstExCtrl)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_ConfigHandleEx(hCipher, pstExCtrl);
}

HI_S32 HI_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_SIZE_T szSrcPhyAddr, HI_SIZE_T szDestPhyAddr, HI_U32 u32ByteLength)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Encrypt(hCipher, szSrcPhyAddr, szDestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_SIZE_T szSrcPhyAddr, HI_SIZE_T szDestPhyAddr, HI_U32 u32ByteLength)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Decrypt(hCipher, szSrcPhyAddr, szDestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_EncryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 HI_UNF_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_DecryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 HI_UNF_CIPHER_GetTag(HI_HANDLE hCipher, HI_U8 *pu8Tag, HI_U32 *pu32TagLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_GetTag(hCipher, pu8Tag, pu32TagLen);
}

HI_S32 HI_UNF_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, pstCtrl);
}

#ifdef CIPHER_KLAD_SUPPORT
HI_S32 HI_UNF_CIPHER_KladEncryptKey(HI_UNF_CIPHER_CA_TYPE_E enRootKey,
                                    HI_UNF_CIPHER_KLAD_TARGET_E enTarget,
                                    HI_U8 *pu8CleanKey, HI_U8* pu8EcnryptKey,
                                    HI_U32 u32KeyLen)
{
    return HI_MPI_CIPHER_KladEncryptKey(enRootKey, enTarget, pu8CleanKey, pu8EcnryptKey, u32KeyLen);
}
#endif

HI_S32 HI_UNF_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_GetRandomNumber(pu32RandomNumber, 0);
}

HI_S32 HI_UNF_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    ret =  HI_MPI_CIPHER_HashInit(pstHashAttr, pHashHandle);

    HI_HASH_UNLOCK();

    return ret;
}

HI_S32 HI_UNF_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    ret = HI_MPI_CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);

    HI_HASH_UNLOCK();

    return ret;
}

HI_S32 HI_UNF_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    ret = HI_MPI_CIPHER_HashFinal(hHashHandle, pu8OutputHash);

    HI_HASH_UNLOCK();

    return ret;
}

HI_S32 HI_UNF_CIPHER_RsaPublicEncrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaEnc,
                                  HI_U8 *pu8Input, HI_U32 u32InLen,
                                  HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPublicEncrypt(pstRsaEnc, pu8Input, u32InLen, pu8Output, pu32OutLen);
}

HI_S32 HI_UNF_CIPHER_RsaPrivateDecrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaDec,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPrivateDecrypt(pstRsaDec, pu8Input, u32InLen, pu8Output, pu32OutLen);
}

HI_S32 HI_UNF_CIPHER_RsaSign(HI_UNF_CIPHER_RSA_SIGN_S *pstRsaSign,
                             HI_U8 *pu8InData, HI_U32 u32InDataLen,
                             HI_U8 *pu8HashData,
                             HI_U8 *pu8OutSign, HI_U32 *pu32OutSignLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaSign(pstRsaSign, pu8InData, u32InDataLen, pu8HashData,
        pu8OutSign, pu32OutSignLen);
}

HI_S32 HI_UNF_CIPHER_RsaVerify(HI_UNF_CIPHER_RSA_VERIFY_S *pstRsaVerify,
                               HI_U8 *pu8InData, HI_U32 u32InDataLen,
                               HI_U8 *pu8HashData,
                               HI_U8 *pu8InSign, HI_U32 u32InSignLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaVerify(pstRsaVerify, pu8InData, u32InDataLen, pu8HashData,
        pu8InSign, u32InSignLen);
}

HI_S32 HI_UNF_CIPHER_RsaPrivateEncrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaEnc,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPrivateEncrypt(pstRsaEnc, pu8Input, u32InLen, pu8Output, pu32OutLen);
}

HI_S32 HI_UNF_CIPHER_RsaPublicDecrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaDec,
                               HI_U8 *pu8Input, HI_U32 u32InLen,
                               HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPublicDecrypt(pstRsaDec, pu8Input, u32InLen, pu8Output,pu32OutLen);
}


