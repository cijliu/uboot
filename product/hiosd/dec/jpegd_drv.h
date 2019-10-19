/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef __JPEGD_DRV_H__
#define __JPEGD_DRV_H__
#include "jpegd_reg.h"
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#ifdef CHIP_HI3559AV100
#define JPEGD_CRG_REG_ADDR    (0x1201013c)
#define JPEGD_REGS_ADDR       (0x11210000)
#endif

#ifdef CHIP_HI3519AV100
#define JPEGD_CRG_REG_ADDR    (0x0451013c)
#define JPEGD_REGS_ADDR       (0x04ac0000)
#endif

#ifdef CHIP_HI3516CV500
#define JPEGD_CRG_REG_ADDR    (0x120100c4)
#define JPEGD_REGS_ADDR       (0x11260000)
#endif

#define JPEGD_REGS_SIZE       0x6BF

#define JPEGD_IP_NUM          1

#define QUANT_TABLE_SIZE      64
#define HDC_TABLE_SIZE        12
#define HAC_MIN_TABLE_SIZE    8
#define HAC_BASE_TABLE_SIZE   8
#define HAC_SYMBOL_TABLE_SIZE 176

typedef struct tagJPEGD_VPU_STATUS_S {
    HI_BOOL bIntDecFinish;
    HI_BOOL bIntDecErr;
    HI_BOOL bIntOverTime;
    HI_BOOL bIntBsRes;
} JPEGD_VPU_STATUS_S;

typedef enum hiPIXEL_FORMAT_E {
    PIXEL_FORMAT_RGB_444 = 0,
    PIXEL_FORMAT_RGB_555,
    PIXEL_FORMAT_RGB_565,
    PIXEL_FORMAT_RGB_888,

    PIXEL_FORMAT_BGR_444,
    PIXEL_FORMAT_BGR_555,
    PIXEL_FORMAT_BGR_565,
    PIXEL_FORMAT_BGR_888,

    PIXEL_FORMAT_ARGB_1555,
    PIXEL_FORMAT_ARGB_4444,
    PIXEL_FORMAT_ARGB_8565,
    PIXEL_FORMAT_ARGB_8888,

    PIXEL_FORMAT_ABGR_1555,
    PIXEL_FORMAT_ABGR_4444,
    PIXEL_FORMAT_ABGR_8565,
    PIXEL_FORMAT_ABGR_8888,

    PIXEL_FORMAT_RGB_BAYER_8BPP,
    PIXEL_FORMAT_RGB_BAYER_10BPP,
    PIXEL_FORMAT_RGB_BAYER_12BPP,
    PIXEL_FORMAT_RGB_BAYER_14BPP,
    PIXEL_FORMAT_RGB_BAYER_16BPP,

    PIXEL_FORMAT_YUV_PLANAR_422,
    PIXEL_FORMAT_YUV_PLANAR_420,
    PIXEL_FORMAT_YUV_PLANAR_444,

    PIXEL_FORMAT_YVU_SEMIPLANAR_422,
    PIXEL_FORMAT_YVU_SEMIPLANAR_420,
    PIXEL_FORMAT_YVU_SEMIPLANAR_444,

    PIXEL_FORMAT_UYVY_PACKAGE_422,
    PIXEL_FORMAT_YUYV_PACKAGE_422,
    PIXEL_FORMAT_VYUY_PACKAGE_422,

    PIXEL_FORMAT_YUV_400,

    PIXEL_FORMAT_BUTT
} PIXEL_FORMAT_E;

typedef enum hiPICTURE_FORMAT_E {
    PICTURE_FORMAT_YUV420 = 0,
    PICTURE_FORMAT_YUV422 = 1, /* 422 2x1 */
    PICTURE_FORMAT_YUV444 = 2,
    PICTURE_FORMAT_YUV422v = 3, /* 422 1x2 */
    PICTURE_FORMAT_YUV400 = 4,
    PICTURE_FORMAT_BUTT
} PICTURE_FORMAT_E;

typedef struct tagJPEGD_VPU_CONFIG_S {
    int s32ChnID;
    PICTURE_FORMAT_E enPictureFormat;
    PIXEL_FORMAT_E enPixelFormat;
    HI_BOOL bOutYUV;
    unsigned char u8VFac;
    unsigned char u8UFac;
    unsigned char u8YFac;
    unsigned int u32Dri;
    unsigned int u32Width;
    unsigned int u32Height;
    unsigned int u32WidthInMcu;
    unsigned int u32HeightInMcu;
    unsigned int u32YStride;
    unsigned int u32CStride;
    unsigned int u32PicType;
    unsigned int u32RGBStride;
    unsigned int u32Alpha;

    HI_U64 u64YPhyAddr;
    HI_U64 u64CPhyAddr;
    HI_U64 u64PhyStrBufStart;
    HI_U64 u64PhyStrBufEnd;
    HI_U64 u64PhyStrStart;
    HI_U64 u64PhyStrEnd;
    HI_U64 u64PhyEmarBuffer0;
    HI_U64 u64PhyEmarBuffer1;

    unsigned int u32QuantTable[QUANT_TABLE_SIZE];
    unsigned int u32HuffmanTable[HDC_TABLE_SIZE];
    unsigned int u32HuffmanMinTable[HAC_MIN_TABLE_SIZE];
    unsigned int u32HuffmanBaseTable[HAC_BASE_TABLE_SIZE];
    unsigned int u32HuffmanSymbolTable[HAC_SYMBOL_TABLE_SIZE];
} JPEGD_VPU_CONFIG_S;

void JPEGD_DRV_WriteRegs(HI_VOID *pRegBase, JPEGD_VPU_CONFIG_S *pstVpuConfig);

void JPEGD_DRV_ReadRegs(HI_VOID *pRegBase, JPEGD_VPU_STATUS_S *pstVpuStatus);

void JPEGD_SetClockEn(int s32VpuId, HI_BOOL bRun);
void JPEGD_ResetSelect(int s32VpuId, HI_BOOL bRun);

HI_VOID JPEGD_SetOutstanding(int s32VpuId, int s32Outstanding);
HI_VOID *JPEGD_GetRegAddr(int s32VpuID);
unsigned int JPEGD_ReadInt(int s32VpuID);
void JPEGD_ClearInt(int s32VpuID);
void JPEGD_SetIntMask(int s32VpuID);
void JPEGD_Reset(int s32VpuId, HI_VOID *pInfo);
void JPEGD_StartVpu(int s32VpuId);
int JPEGD_SetTimeOut(int s32VpuID, int s32TimeOut);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of __JPEGD_DRV_H__ */


