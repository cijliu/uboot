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

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32 CIPHER_Ioctl(HI_U32 cmd, HI_VOID * argp, HI_VOID *private_data)
{
    HI_S32 ret = HI_SUCCESS;

    if (argp == HI_NULL)
    {
        HI_ERR_CIPHER("Error, argp is NULL!\n");
        return HI_FAILURE;
    }

    switch(cmd)
    {
        case CMD_CIPHER_CREATEHANDLE:
        {
            CIPHER_HANDLE_S *pstCIHandle = (CIPHER_HANDLE_S *)argp;
            ret = HI_DRV_CIPHER_CreateHandle(pstCIHandle,  private_data);
            break;
        }
        case CMD_CIPHER_DESTROYHANDLE:
        {
            HI_HANDLE hCipherChn = *(HI_HANDLE *)argp;
            ret = HI_DRV_CIPHER_DestroyHandle(hCipherChn);
            break;
        }
        case CMD_CIPHER_CONFIGHANDLE_EX:
        {
            CIPHER_CONFIG_CTRL_EX stCIConfig = *(CIPHER_CONFIG_CTRL_EX *)argp;
            ret = HI_DRV_CIPHER_ConfigChnEx(stCIConfig.CIHandle, &stCIConfig);
            break;
        }
        case CMD_CIPHER_ENCRYPT:
        {
            CIPHER_DATA_S *pstCIData = (CIPHER_DATA_S *)argp;
            ret = HI_DRV_CIPHER_Encrypt(pstCIData);
            break;
        }
        case CMD_CIPHER_DECRYPT:
        {
            CIPHER_DATA_S *pstCIData = (CIPHER_DATA_S *)argp;
            ret = HI_DRV_CIPHER_Decrypt(pstCIData);
            break;
        }
        case CMD_CIPHER_ENCRYPTMULTI:
        {
            CIPHER_PKG_S *pstPkg = (CIPHER_PKG_S *)argp;
            ret = HI_DRV_CIPHER_EncryptMulti(pstPkg);
            break;
        }
        case CMD_CIPHER_DECRYPTMULTI:
        {
            CIPHER_PKG_S *pstPkg = (CIPHER_PKG_S *)argp;
            ret = HI_DRV_CIPHER_DecryptMulti(pstPkg);
            break;
        }
#ifdef CIPHER_KLAD_SUPPORT
         case CMD_CIPHER_KLAD_KEY:
        {
            CIPHER_KLAD_KEY_S *pstKladData = (CIPHER_KLAD_KEY_S *)argp;
            ret = HI_DRV_CIPHER_KladEncryptKey(pstKladData);
            break;
        }
#endif
        case CMD_CIPHER_GETTAG:
        {
            CIPHER_TAG_S *pstTag = (CIPHER_TAG_S *)argp;
            ret = HI_DRV_CIPHER_GetTag(pstTag);
            break;
        }
        case CMD_CIPHER_GETRANDOMNUMBER:
        {
            CIPHER_RNG_S *pstRNG  = (CIPHER_RNG_S *)argp;
            ret = HI_DRV_CIPHER_GetRandomNumber(pstRNG);
            break;
        }
        case CMD_CIPHER_GETHANDLECONFIG_EX:
        {
            CIPHER_CONFIG_CTRL_EX *pstCIData = (CIPHER_CONFIG_CTRL_EX *)argp;
            ret = HI_DRV_CIPHER_GetHandleConfigEx(pstCIData);
            break;
        }
        case CMD_CIPHER_CALCHASHINIT:
        {
            CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S*)argp;
            ret = HI_DRV_CIPHER_CalcHashInit(pstCipherHashData);
            break;
        }
        case CMD_CIPHER_CALCHASHUPDATE:
        {
            CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S*)argp;
            ret = HI_DRV_CIPHER_CalcHashUpdate(pstCipherHashData);
            break;
        }
        case CMD_CIPHER_CALCHASHFINAL:
        {
            CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S*)argp;
               ret = HI_DRV_CIPHER_CalcHashFinal(pstCipherHashData);
            break;
        }
        case CMD_CIPHER_CALCRSA:
        {
            CIPHER_RSA_DATA_S *pCipherRsaData = (CIPHER_RSA_DATA_S*)argp;
            ret = HI_DRV_CIPHER_CalcRsa(pCipherRsaData);
            break;
        }
#ifdef CONFIG_COMPAT
#ifdef CONFIG_RSA_HARDWARE_SUPPORT
        case CMD_CIPHER_COMPAT_CALCRSA:
        {
            CIPHER_COMPAT_RSA_DATA_S *pCipherCompatRsaData = (CIPHER_COMPAT_RSA_DATA_S*)argp;
            CIPHER_RSA_DATA_S stCipherRsaData;

            stCipherRsaData.pu8Input = U32_TO_POINT(pCipherCompatRsaData->u32InputVia);
            stCipherRsaData.pu8Output = U32_TO_POINT(pCipherCompatRsaData->u328OutputVia);
            stCipherRsaData.pu8K = U32_TO_POINT(pCipherCompatRsaData->u328KVia);
            stCipherRsaData.pu8N = U32_TO_POINT(pCipherCompatRsaData->u328NVia);
            stCipherRsaData.u16KLen = pCipherCompatRsaData->u16KLen;
            stCipherRsaData.u16NLen = pCipherCompatRsaData->u16NLen;
            stCipherRsaData.u32DataLen = pCipherCompatRsaData->u32DataLen;

            ret = HI_DRV_CIPHER_CalcRsa(&stCipherRsaData);
            break;
        }
#endif
        case CMD_CIPHER_COMPAT_ENCRYPTMULTI:
        {
            CIPHER_COMPAT_PKG_S *pstPkg = (CIPHER_COMPAT_PKG_S *)argp;
            CIPHER_PKG_S stPkg;

            stPkg.CIHandle = pstPkg->CIHandle;
            stPkg.u32PkgNum = pstPkg->u32PkgNum;
            stPkg.pu8Pkg = U32_TO_POINT(pstPkg->u32PkgVia);

            ret = HI_DRV_CIPHER_EncryptMulti(&stPkg);
            break;
        }
        case CMD_CIPHER_COMPAT_DECRYPTMULTI:
        {
            CIPHER_COMPAT_PKG_S *pstPkg = (CIPHER_COMPAT_PKG_S *)argp;
            CIPHER_PKG_S stPkg;

            stPkg.CIHandle = pstPkg->CIHandle;
            stPkg.u32PkgNum = pstPkg->u32PkgNum;
            stPkg.pu8Pkg = U32_TO_POINT(pstPkg->u32PkgVia);

            ret = HI_DRV_CIPHER_DecryptMulti(&stPkg);
            break;
        }
#endif
        default:
        {
            HI_ERR_CIPHER("Unsupport cmd, MOD_ID=0x%02X, NR=0x%02x, SIZE=0x%02x!\n", REE_CIPHER_IOC_TYPE (cmd), REE_CIPHER_IOC_NR (cmd), REE_CIPHER_IOC_SIZE(cmd));
            ret = HI_FAILURE;
            break;
        }
    }

    return ret;
}

HI_S32 CIPHER_MODULE_Init(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    ret = DRV_CIPHER_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret = DRV_RNG_Init();
    if (HI_SUCCESS != ret)
    {
        (HI_VOID)DRV_CIPHER_DeInit();
        return ret;
    }

#ifdef CIPHER_KLAD_SUPPORT
    ret = hi_drv_compat_init();
    if (HI_SUCCESS != ret)
    {
        (HI_VOID)DRV_CIPHER_DeInit();
        (HI_VOID)DRV_RNG_DeInit();
        return ret;
    }
#endif

    ret = DRV_RSA_Init();
    if (HI_SUCCESS != ret)
    {
        (HI_VOID)DRV_CIPHER_DeInit();
        (HI_VOID)DRV_RNG_DeInit();
#ifdef CIPHER_KLAD_SUPPORT
        (HI_VOID)hi_drv_compat_deinit();
#endif
        return ret;
    }

    return HI_SUCCESS;
}

HI_VOID CIPHER_MODULE_Exit(HI_VOID)
{
    (HI_VOID)DRV_CIPHER_DeInit();
    (HI_VOID)DRV_RNG_DeInit();
    (HI_VOID)DRV_RSA_DeInit();

#ifdef CIPHER_KLAD_SUPPORT
    (HI_VOID)hi_drv_compat_deinit();
#endif
    return ;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
