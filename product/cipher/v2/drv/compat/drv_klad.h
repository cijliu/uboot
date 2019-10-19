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

#ifndef __DRV_KLAD_H_
#define __DRV_KLAD_H_

#include "hi_types.h"
#include "common.h"
#include "drv_cipher_ioctl.h"

HI_S32 HAL_Cipher_KladConfig(HI_U32 chnId,
                             HI_U32 u32OptId,
                             HI_UNF_CIPHER_KLAD_TARGET_E enTarget,
                             HI_BOOL bIsDecrypt);

HI_VOID HAL_Cipher_StartKlad(HI_VOID);
HI_VOID HAL_Cipher_SetKladData(HI_U32 *pu32DataIn);
HI_VOID HAL_Cipher_GetKladData(HI_U32 *pu32DataOut);
HI_S32 HAL_Cipher_WaitKladDone(HI_VOID);

HI_S32 DRV_KLAD_Init(HI_VOID);
HI_VOID DRV_KLAD_DeInit(HI_VOID);

HI_S32 DRV_Cipher_KladLoadKey(HI_U32 chnId,
                              HI_UNF_CIPHER_CA_TYPE_E enRootKey,
                              HI_UNF_CIPHER_KLAD_TARGET_E enTarget,
                              HI_U8 *pu8DataIn,
                              HI_U32 u32KeyLen);

HI_S32 DRV_Cipher_KladEncryptKey(HI_UNF_CIPHER_CA_TYPE_E enRootKey,
                                 HI_UNF_CIPHER_KLAD_TARGET_E target,
                                 HI_U32 u32CleanKey[4],
                                 HI_U32 u32EncryptKey[4]);

#endif