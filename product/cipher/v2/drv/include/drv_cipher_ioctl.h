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

#ifndef __REE_DRV_CIPHER_IOCTL_H__
#define __REE_DRV_CIPHER_IOCTL_H__

#include "hi_types.h"
#include "hi_unf_cipher.h"

HI_S32 CIPHER_MODULE_Init(HI_VOID);
HI_VOID CIPHER_MODULE_Exit(HI_VOID);
HI_S32 CIPHER_Ioctl(HI_U32 cmd, HI_VOID * argp, HI_VOID *private_data);


typedef struct
{
    HI_U32 u32ChnId;
    HI_CHAR *ps8Openstatus;
    HI_CHAR *ps8Alg;
    HI_CHAR *ps8Mode;
    HI_U32 u32KeyLen;
    HI_CHAR *ps8KeyFrom;
    HI_BOOL bIsDecrypt;
    HI_U32 u32DataInSize;
    HI_U32 u32DataInAddr;
    HI_U32 u32DataOutSize;
    HI_U32 u32DataOutAddr;
    HI_BOOL bInINTAllEn;
    HI_BOOL bInINTEn;
    HI_BOOL bInINTRaw;
    HI_BOOL bOutINTEn;
    HI_BOOL bOutINTRaw;
    HI_U32 u32OutINTCount;      //CHANn_INT_OCNTCFG
    char  u8IVString[33];
}CIPHER_CHN_STATUS_S;

#define REE_CIPHER_IOC_NA        0U
#define REE_CIPHER_IOC_W        1U
#define REE_CIPHER_IOC_R        2U
#define REE_CIPHER_IOC_RW        3U

#define REE_CIPHER_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define REE_CIPHER_IOR(type,nr,size)            REE_CIPHER_IOC(REE_CIPHER_IOC_R,(type),(nr), sizeof(size))
#define REE_CIPHER_IOW(type,nr,size)            REE_CIPHER_IOC(REE_CIPHER_IOC_W,(type),(nr), sizeof(size))
#define REE_CIPHER_IOWR(type,nr,size)     REE_CIPHER_IOC(REE_CIPHER_IOC_RW,(type),(nr),sizeof(size))

#define REE_CIPHER_IOC_DIR(nr)        (((nr) >> 30) & 0x03)
#define REE_CIPHER_IOC_TYPE(nr)        (((nr) >> 8) & 0xFF)
#define REE_CIPHER_IOC_NR(nr)        (((nr) >> 0) & 0xFF)
#define REE_CIPHER_IOC_SIZE(nr)        (((nr) >> 16) & 0x3FFF)

#define HI_ID_CIPHER 100

HI_S32 REE_CIPHER_Ioctl(HI_U32 cmd, HI_VOID *argp);


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#define    CMD_CIPHER_CREATEHANDLE           REE_CIPHER_IOWR(HI_ID_CIPHER,  0x1,  CIPHER_HANDLE_S)
#define    CMD_CIPHER_DESTROYHANDLE          REE_CIPHER_IOW(HI_ID_CIPHER,  0x2,  HI_U32)
#define    CMD_CIPHER_CONFIGHANDLE           REE_CIPHER_IOW(HI_ID_CIPHER,  0x3,  CIPHER_Config_CTRL)
#define    CMD_CIPHER_ENCRYPT                REE_CIPHER_IOW(HI_ID_CIPHER,  0x4,  CIPHER_DATA_S)
#define    CMD_CIPHER_DECRYPT                REE_CIPHER_IOW(HI_ID_CIPHER,  0x5,  CIPHER_DATA_S)
#define    CMD_CIPHER_DECRYPTMULTI           REE_CIPHER_IOW(HI_ID_CIPHER,  0x6,  CIPHER_PKG_S)
#define    CMD_CIPHER_ENCRYPTMULTI           REE_CIPHER_IOW(HI_ID_CIPHER,  0x7,  CIPHER_PKG_S)
#define    CMD_CIPHER_GETRANDOMNUMBER        REE_CIPHER_IOWR(HI_ID_CIPHER,  0x8,  CIPHER_RNG_S)
#define    CMD_CIPHER_GETHANDLECONFIG        REE_CIPHER_IOWR(HI_ID_CIPHER,  0x9,  CIPHER_Config_CTRL)
#define    CMD_CIPHER_CALCHASHINIT           REE_CIPHER_IOWR(HI_ID_CIPHER,  0xa,  CIPHER_HASH_DATA_S)
#define    CMD_CIPHER_CALCHASHUPDATE         REE_CIPHER_IOWR(HI_ID_CIPHER,  0xb,  CIPHER_HASH_DATA_S)
#define    CMD_CIPHER_CALCHASHFINAL          REE_CIPHER_IOWR(HI_ID_CIPHER, 0xc,  CIPHER_HASH_DATA_S)
#define    CMD_CIPHER_CALCRSA                REE_CIPHER_IOWR(HI_ID_CIPHER, 0x10, CIPHER_RSA_DATA_S)
#define    CMD_CIPHER_GETTAG                 REE_CIPHER_IOWR(HI_ID_CIPHER, 0x11, CIPHER_TAG_S)
#define    CMD_CIPHER_CONFIGHANDLE_EX        REE_CIPHER_IOWR(HI_ID_CIPHER,  0x23, CIPHER_CONFIG_CTRL_EX)
#define    CMD_CIPHER_GETHANDLECONFIG_EX     REE_CIPHER_IOWR(HI_ID_CIPHER,  0x24, CIPHER_CONFIG_CTRL_EX)
#define    CMD_CIPHER_KLAD_KEY               REE_CIPHER_IOWR(HI_ID_CIPHER, 0x12, CIPHER_KLAD_KEY_S)

#ifdef CONFIG_COMPAT
#define    CMD_CIPHER_COMPAT_DECRYPTMULTI    REE_CIPHER_IOW(HI_ID_CIPHER,  0x6, CIPHER_COMPAT_PKG_S)
#define    CMD_CIPHER_COMPAT_ENCRYPTMULTI    REE_CIPHER_IOW(HI_ID_CIPHER,  0x7, CIPHER_COMPAT_PKG_S)
#define    CMD_CIPHER_COMPAT_CALCRSA         REE_CIPHER_IOWR(HI_ID_CIPHER, 0x10, CIPHER_COMPAT_RSA_DATA_S)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_CIPHER_IOCTL_H__*/
