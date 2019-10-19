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

HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber, HI_U32 u32TimeOutUs)
{
    HI_S32 Ret = HI_FAILURE;
    CIPHER_RNG_S stRNG;

    INLET_PARAM_CHECK_POINT_NULL(pu32RandomNumber);

    stRNG.u32RNG = 0;
    stRNG.u32TimeOutUs = u32TimeOutUs;
    Ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_GETRANDOMNUMBER, &stRNG);

    if (Ret == HI_SUCCESS)
    {
        *pu32RandomNumber = stRNG.u32RNG;
    }

    return Ret;
}

