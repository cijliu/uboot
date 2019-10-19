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

#ifndef __DRV_RNG_H__
#define __DRV_RNG_H__

/* add include here */
#include "hi_drv_cipher.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

HI_S32 DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG);
HI_U32 DRV_CIPHER_Rand(HI_VOID);
HI_S32 DRV_RNG_Init(HI_VOID);
HI_VOID DRV_RNG_DeInit(HI_VOID);

#ifdef __cplusplus
}
#endif
#endif /* __DRV_CIPHER_H__ */
