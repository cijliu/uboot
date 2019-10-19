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

#ifndef __REE_MPI_CIPHER_H__
#define __REE_MPI_CIPHER_H__

#include "cipher_osal.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

HI_S32 Cipher_HashMmzInit(HI_VOID);

HI_VOID Cipher_HashMmzDeInit(HI_VOID);

HI_S32 AES_Encrypt(HI_HANDLE hCipherHandle, HI_U8 *input, HI_U32 datalen, HI_U8 *output);

HI_S32 RSA_Private(HI_UNF_CIPHER_RSA_PRI_KEY_S *pstPriKey, HI_UNF_CIPHER_CA_TYPE_E enCaType,  HI_U8 *pu8In, HI_U8 *pu8Out);

HI_S32 RSA_Public(HI_UNF_CIPHER_RSA_PUB_KEY_S *pstPubKey, HI_U8 *pu8In, HI_U8 *pu8Out);

HI_S32 Mbedtls_GetRandomNumber(HI_VOID *param, HI_U8 *pu8Rand, size_t u32Size);

#ifdef __cplusplus
#if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __HI_MPI_CIPHER_H__ */

