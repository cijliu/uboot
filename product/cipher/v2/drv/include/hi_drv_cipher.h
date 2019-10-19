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

#ifndef __HI_DRV_CIPHER_H__
#define __HI_DRV_CIPHER_H__

#include "hi_types.h"
#include "hi_unf_cipher.h"

#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus */

#define MAX_MULTI_PKG_NUM         (128)
#define CIPHER_SOFT_CHAN_NUM      8
#define CIPHER_INVALID_CHN        (0xffffffff)
#define CIPHER_MAX_NODE_BUF_SIZE  (0xFFFF0)   //1M-16
#define CIPHER_MAX_RSA_KEY_LEN    (512)
#define HASH_OUTPUT_SIZE_WORD     (1600/8/4)    //sha3 state

#define  HDCP_KEY_RAM_SIZE                      320
#define  HDCP_KEY_PRIME_SIZE                    320
#define  HDCP_KEY_TOOL_FILE_SIZE                384
#define  HDCP_KEY_CHIP_FILE_SIZE               (HDCP_KEY_RAM_SIZE + 12)

#define HASH_ALG_SHA2                           0x01
#define HASH_ALG_SHA3                           0x02
#define HASH_ALG_SM3                            0x03

#define HASH_MODE_RAW                           0x01
#define HASH_MODE_MAC                           0x02
#define HASH_MODE_SHAKE                         0x03

#define CPU_BIT_WIDTH_32            32
#define CPU_BIT_WIDTH_64            64
#define MY_CPU_BIT_WIDTH           sizeof(HI_SIZE_T)

typedef struct hiCIPHER_DATA_INFO_S
{
    HI_U32  u32src;
    HI_U32  u32dest;
    HI_U32  u32length;
    HI_BOOL bDecrypt;
    HI_U32  u32DataPkg[4];
}HI_DRV_CIPHER_DATA_INFO_S;

typedef enum hiHI_DRV_HASH_STEP
{
    HI_DRV_HASH_STEP_UPDATE = 0x0,
    HI_DRV_HASH_STEP_INIT = 0x01,
    HI_DRV_HASH_STEP_FINAL = 0x02,
}HI_DRV_HASH_STEP_E;

typedef struct  hiCIPHER_HANDLE_S
{
    HI_HANDLE hCIHandle;
    HI_UNF_CIPHER_ATTS_S stCipherAtts;
}CIPHER_HANDLE_S;

typedef struct  hiCIPHER_DATA_S
{
    HI_HANDLE CIHandle;
    HI_U32 ScrPhyAddr;
    HI_U32 ScrPhyAddrHigh;
    HI_U32 DestPhyAddr;
    HI_U32 DestPhyAddrHigh;
    HI_U32 u32DataLength;
}CIPHER_DATA_S;

typedef struct  hiCIPHER_PKG_S
{
    HI_HANDLE CIHandle;
    HI_U32 u32PkgNum;
    HI_U32 u32UserBitWidth;
    HI_UNF_CIPHER_DATA_S* pu8Pkg;
}CIPHER_PKG_S;

typedef struct hiCIPHER_Config_CTRL
{
    HI_HANDLE CIHandle;
    HI_UNF_CIPHER_CTRL_S CIpstCtrl;
}CIPHER_Config_CTRL;

typedef struct hiCIPHER_WAIT_DONE
{
    HI_HANDLE CIHandle;
    HI_U32    u32TimeOut;;
}CIPHER_WAIT_DONE_S;

typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 u32Key[12];                              /**< Key input, EK||AK||SK for SM1 */
    HI_U32 u32OddKey[8];                            /**< Key input, Old Key */
    HI_U32 u32IV[4];                                /**< Initialization vector (IV) */
    HI_BOOL bKeyByCA;                               /**< Encryption using advanced conditional access (CA) or decryption using keys */
    HI_UNF_CIPHER_CA_TYPE_E enCaType;               /**< Select keyladder type when using advanced CA */
    HI_UNF_CIPHER_ALG_E enAlg;                      /**< Cipher algorithm */
    HI_UNF_CIPHER_BIT_WIDTH_E enBitWidth;           /**< Bit width for encryption or decryption */
    HI_UNF_CIPHER_WORK_MODE_E enWorkMode;           /**< Operating mode */
    HI_UNF_CIPHER_KEY_LENGTH_E enKeyLen;            /**< Key length */
    HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S stChangeFlags; /**< control information exchange choices, we default all woulde be change except they have been in the choices */
    HI_UNF_CIPHER_SM1_ROUND_E enSm1Round;           /**< SM1 round number, should be 8, 10, 12 or 14*/
    HI_U32 u32IVLen;                                /**< IV lenght for CCM/GCM, which is an element of {4,6,8,10,12,14,16} for CCM, and is an element of [1-16] for GCM*/
    HI_U32 u32TagLen;                               /**< Tag lenght for CCM which is an element of {4,6,8,10,12,14,16}*/
    HI_U32 u32ALen;                                 /**< Associated data for CCM and GCM*/
    HI_U32 u32APhyAddr;
    HI_U32 u32APhyAddrHigh;                             /**< Physical address of Associated data for CCM and GCM*/
}CIPHER_CONFIG_CTRL_EX;

typedef struct
{
    HI_UNF_CIPHER_HASH_TYPE_E enShaType;
    HI_U32  u32HardChn;
    HI_U32  u32ShaVal[16];
    HI_U32  u32DataPhy;
    HI_U32  u32DataPhyHigh;
    HI_U32  u32DataLen;
}CIPHER_HASH_DATA_S;

typedef struct hiCIPHER_HASH_INIT_S
{
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
}CIPHER_HASH_INIT_S;

typedef struct hiCIPHER_HASH_UPDATE_S
{
    HI_HANDLE HashHandle;
    HI_U8 *pu8InputData;
    HI_U32 u32InputDataLen;
}CIPHER_HASH_UPDATE_S;

typedef struct hiCIPHER_HASH_FINISH_S
{
    HI_HANDLE HashHandle;
    HI_U8 *pu8OutputHash;
}CIPHER_HASH_FINISH_S;

typedef struct
{
    HI_U32 u32TimeOutUs;
    HI_U32 u32RNG;
}CIPHER_RNG_S;

typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 u32TagLen;
    HI_U32 u32Tag[4];
}CIPHER_TAG_S;

typedef struct hiCIPHER_RSA_DATA_S
{
    HI_U8  *pu8Input;
    HI_U8  *pu8Output;
    HI_U32  u32DataLen;
    HI_U8  *pu8N;
    HI_U8  *pu8K;
    HI_U16 u16NLen;
    HI_U16 u16KLen;
    HI_UNF_CIPHER_CA_TYPE_E enCaType;               /**< Select keyladder type when using advanced CA */
}CIPHER_RSA_DATA_S;

/** RSA private key struct */
typedef struct
{
    HI_U8 *pu8N;                      /*!<  public modulus    */
    HI_U8 *pu8E;                      /*!<  public exponent   */
    HI_U8 *pu8D;                      /*!<  private exponent  */
    HI_U8 *pu8P;                      /*!<  1st prime factor  */
    HI_U8 *pu8Q;                      /*!<  2nd prime factor  */
    HI_U8 *pu8DP;                     /*!<  D % (P - 1)       */
    HI_U8 *pu8DQ;                     /*!<  D % (Q - 1)       */
    HI_U8 *pu8QP;                     /*!<  1 / (Q % P)       */
    HI_U16 u16NLen;                   /**< length of public modulus */
    HI_U16 u16ELen;                   /**< length of public exponent */
    HI_U16 u16DLen;                   /**< length of private exponent */
    HI_U16 u16PLen;                   /**< length of 1st prime factor */
    HI_U16 u16QLen;                   /**< length of 2nd prime factor */
    HI_U16 u16DPLen;                  /**< length of D % (P - 1) */
    HI_U16 u16DQLen;                  /**< length of D % (Q - 1) */
    HI_U16 u16QPLen;                  /**< length of 1 / (Q % P) */
}CIPHER_RSA_PRI_KEY_S;

typedef struct hiCIPHER_RSA_KEY_S
{
    CIPHER_RSA_PRI_KEY_S stPriKey;
    HI_U32 u32NumBits;
    HI_U32 u32Exponent;
}CIPHER_RSA_KEY_S;

typedef enum
{
    CIPHER_TEST_PRINT_PHY = 0x01,
    CIPHER_TEST_PRINT_VIA,
    CIPHER_TEST_MEMSET,
    CIPHER_TEST_MEMCMP,
    CIPHER_TEST_MEMCPY,
    CIPHER_TEST_MEMCMP_PHY,
    CIPHER_TEST_READ_REG,
    CIPHER_TEST_WRITE_REG,
    CIPHER_TEST_AES  = 0x10,
    CIPHER_TEST_HMAC,
    CIPHER_TEST_RSA,
    CIPHER_TEST_HASH,
    CIPHER_TEST_DES,
    CIPHER_TEST_RSA_PRIM,
    CIPHER_TEST_RSA_KG,
    CIPHER_TEST_RND,
    CIPHER_TEST_BUTT,
}CIPHER_TEST;

#ifdef CONFIG_COMPAT
typedef struct  hiCIPHER_COMPAT_PKG_S
{
    HI_HANDLE CIHandle;
    HI_U32 u32PkgNum;
    HI_U32 u32PkgVia;
}CIPHER_COMPAT_PKG_S;

typedef struct hiCIPHER_COMPAT_RSA_DATA_S
{
    HI_U32  u32InputVia;
    HI_U32  u328OutputVia;
    HI_U32  u32DataLen;
    HI_U32  u328NVia;
    HI_U32  u328KVia;
    HI_U16 u16NLen;
    HI_U16 u16KLen;
}CIPHER_COMPAT_RSA_DATA_S;
#endif

typedef struct
{
    HI_UNF_CIPHER_CA_TYPE_E enRootKey;
    HI_UNF_CIPHER_KLAD_TARGET_E enTarget;
    HI_U32 u32CleanKey[4];
    HI_U32 u32EncryptKey[4];
    HI_U32 u32KeyLen;
}CIPHER_KLAD_KEY_S;

HI_S32 HI_DRV_CIPHER_CreateHandle(CIPHER_HANDLE_S *pstCIHandle, HI_VOID *file);
HI_S32 HI_DRV_CIPHER_ConfigChn(HI_U32 softChnId, HI_UNF_CIPHER_CTRL_S *pConfig);
HI_S32 HI_DRV_CIPHER_ConfigChnEx(HI_HANDLE hCIHandle, CIPHER_CONFIG_CTRL_EX *pConfig);
HI_S32 HI_DRV_CIPHER_GetHandleConfig(CIPHER_Config_CTRL *pstCipherConfig);
HI_S32 HI_DRV_CIPHER_GetHandleConfigEx(CIPHER_CONFIG_CTRL_EX *pstCipherConfig);
HI_S32 HI_DRV_CIPHER_GetIV(HI_U32 ChnId, HI_U32 u32IV[4]);
HI_S32 HI_DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn);
HI_S32 HI_DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData);
HI_S32 HI_DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData);
HI_S32 HI_DRV_CIPHER_EncryptMulti(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_DecryptMulti(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_EncryptMultiAsyn(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_DecryptMultiAsyn(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_WaitDone(CIPHER_WAIT_DONE_S *pstWaitDone);
HI_S32 HI_DRV_CIPHER_HashWaitDone(HI_HANDLE handle);
HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG);
HI_S32 HI_DRV_CIPHER_SoftReset(HI_VOID);
HI_S32 HI_DRV_CIPHER_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_GetTag(CIPHER_TAG_S *pstTag);
HI_S32 HI_DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData);
HI_S32 HI_DRV_CIPHER_KladEncryptKey(CIPHER_KLAD_KEY_S *pstKladKey);

HI_VOID HI_DRV_CIPHER_Suspend(HI_VOID);
HI_S32 HI_DRV_CIPHER_Resume(HI_VOID);

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#endif    /* End of #ifndef __HI_DRV_CIPHER_H__*/

