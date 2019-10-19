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
#include <common.h>
#include "jpegd_drv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* Begin of #ifdef __cplusplus */

#define osal_readl(x) (*((volatile int*)(x)))
#define osal_writel(v, x) (*((volatile int*)(x)) = (v))

__inline static unsigned int GetLowAddr(HI_U64 u64Phyaddr)
{
    return (unsigned int)u64Phyaddr;
}

__inline static unsigned int GetHighAddr(HI_U64 u64Phyaddr)
{
    return (unsigned int)(u64Phyaddr >> 32);
}

void JPEGD_SetClockEn(int s32VpuId, HI_BOOL bRun)
{
    unsigned long t, mask;
    unsigned int offset = 1;
    mask = 1 << offset;
    t = osal_readl((const volatile void *)JPEGD_CRG_REG_ADDR);
    t &= ~mask;
    t |= (bRun << offset) & mask;
    osal_writel(t, (volatile void *)JPEGD_CRG_REG_ADDR);

    return;
}

void JPEGD_ResetSelect(int s32VpuId, HI_BOOL bRun)
{
    int i;
    volatile U_JPEG_DEC_START D32;
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_GetRegAddr(s32VpuId);

    if (bRun == HI_FALSE) {
        for (i = 0; i < 1000; i++) {
            D32.u32 = pJpegdReg->JPEG_DEC_START.u32;
            if (D32.bits.rst_busy == 0) {
                break;
            }
            udelay(10);
        }
        if (i >= 1000) {
            printf("JPEGD reset error!\n");
            return;
        }
    }

    {
        unsigned long t, mask;
        unsigned int offset = 0;
        mask = 1 << offset;
        t = osal_readl((const volatile void *)JPEGD_CRG_REG_ADDR);
        t &= ~mask;
        t |= (bRun << offset) & mask;
        osal_writel(t, (volatile void *)JPEGD_CRG_REG_ADDR);
    }

    return;
}

HI_VOID JPEGD_SetOutstanding(int s32VpuId, int s32Outstanding)
{
    U_FREQ_SCALE D32;
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_GetRegAddr(s32VpuId);

    D32.u32 = pJpegdReg->FREQ_SCALE.u32;
    D32.bits.outstanding = s32Outstanding;
    pJpegdReg->FREQ_SCALE.u32 = D32.u32;
    return;
}

HI_VOID *JPEGD_GetRegAddr(int s32VpuID)
{
    S_JPGD_REGS_TYPE *pJpegdReg = HI_NULL;

    pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_REGS_ADDR;

    return pJpegdReg;
}

unsigned int JPEGD_ReadInt(int s32VpuID)
{
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_GetRegAddr(s32VpuID);

    return pJpegdReg->JPEG_INT.u32;
}

void JPEGD_ClearInt(int s32VpuID)
{
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_GetRegAddr(s32VpuID);
    /* check if it's frame end */
    pJpegdReg->JPEG_INT.u32 = 0xFFFFFFFF;

    return;
}

void JPEGD_SetIntMask(int s32VpuID)
{
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_GetRegAddr(s32VpuID);

    pJpegdReg->INT_MASK.u32 = 0x0;

    return;
}

void JPEGD_Reset(int s32VpuId, HI_VOID *pInfo)
{
    JPEGD_ResetSelect(s32VpuId, HI_TRUE);
    JPEGD_ResetSelect(s32VpuId, HI_FALSE);
    JPEGD_SetIntMask(s32VpuId);
    JPEGD_SetOutstanding(s32VpuId, 0x3);

    return;
}

void JPEGD_StartVpu(int s32VpuId)
{
    U_JPEG_DEC_START D32;
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_GetRegAddr(s32VpuId);

    D32.u32 = pJpegdReg->JPEG_DEC_START.u32;
    D32.bits.jpeg_dec_start = 1;
    pJpegdReg->JPEG_DEC_START.u32 = D32.u32;

    return;
}

int JPEGD_SetTimeOut(int s32VpuID, int s32TimeOut)
{
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)JPEGD_GetRegAddr(s32VpuID);

    pJpegdReg->OVER_TIME_THD = (unsigned int)s32TimeOut;

    return HI_SUCCESS;
}

void JPEGD_DRV_WriteRegs(HI_VOID *pRegBase, JPEGD_VPU_CONFIG_S *pstConfig)
{
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)pRegBase;

    /*  1. JPEG_RESUME_START */
    {
        U_JPEG_RESUME_START D32;

        D32.u32 = 0;

        D32.bits.jpeg_resume_start = 0;
        D32.bits.last_resume_in_pic = 1;

        pJpegdReg->JPEG_RESUME_START.u32 = D32.u32;
    }

    /*  2. JPEG_STRIDE */
    {
        U_JPEG_STRIDE D32;

        D32.u32 = 0;

        D32.bits.y_stride = pstConfig->u32YStride;
        D32.bits.uv_stride = pstConfig->u32CStride;

        pJpegdReg->JPEG_STRIDE.u32 = D32.u32;
    }

    /*  3. PICTURE_SIZE */
    {
        U_PICTURE_SIZE D32;

        D32.u32 = 0;

        D32.bits.pic_width_in_mcu = pstConfig->u32WidthInMcu;
        D32.bits.pic_height_in_mcu = pstConfig->u32HeightInMcu;

        pJpegdReg->PICTURE_SIZE.u32 = D32.u32;
    }

    /*  4. PICTURE_TYPE */
    {
        U_PICTURE_TYPE D32;

        D32.u32 = 0;

        D32.bits.pic_type = pstConfig->u32PicType;

        pJpegdReg->PICTURE_TYPE.u32 = D32.u32;
    }

    /*  . RGB_OUT_STRIDE */
    {
        U_RGB_OUT_STRIDE D32;

        D32.u32 = 0;

        D32.bits.jcfg2jdo_out_stride = pstConfig->u32RGBStride;

        pJpegdReg->RGB_OUT_STRIDE.u32 = D32.u32;
    }

    /*  5. BITBUFFER_STADDR */
    {
        pJpegdReg->BITBUFFER_STADDR_LSB = GetLowAddr(pstConfig->u64PhyStrBufStart);

        pJpegdReg->BITBUFFER_STADDR_MSB.u32 = GetHighAddr(pstConfig->u64PhyStrBufStart);
    }

    /*  6. BITBUFFER_ENDADDR */
    {
        pJpegdReg->BITBUFFER_ENDADDR_LSB = GetLowAddr(pstConfig->u64PhyStrBufEnd);

        pJpegdReg->BITBUFFER_ENDADDR_MSB.u32 = GetHighAddr(pstConfig->u64PhyStrBufEnd);
    }

    /*  7. BITSTREAMS_STADDR */
    {
        pJpegdReg->BITSTREAMS_STADDR_LSB = GetLowAddr(pstConfig->u64PhyStrStart);

        pJpegdReg->BITSTREAMS_STADDR_MSB.u32 = GetHighAddr(pstConfig->u64PhyStrStart);
    }

    /*  8. BITSTREAMS_ENDADDR */
    {
        pJpegdReg->BITSTREAMS_ENDADDR_LSB = GetLowAddr(pstConfig->u64PhyStrEnd);

        pJpegdReg->BITSTREAMS_ENDADDR_MSB.u32 = GetHighAddr(pstConfig->u64PhyStrEnd);
    }

    /*  9. PICTURE_YSTADDR */
    {
        pJpegdReg->PICTURE_YSTADDR_LSB = GetLowAddr(pstConfig->u64YPhyAddr);

        pJpegdReg->PICTURE_YSTADDR_MSB.u32 = GetHighAddr(pstConfig->u64YPhyAddr);
    }

    /*  10. PICTURE_UVSTADDR */
    if (pstConfig->bOutYUV == HI_TRUE) {
        pJpegdReg->PICTURE_UVSTADDR_LSB = GetLowAddr(pstConfig->u64CPhyAddr);

        pJpegdReg->PICTURE_UVSTADDR_MSB.u32 = GetHighAddr(pstConfig->u64CPhyAddr);
    }

    /*  11. FREQ_SCALE */
    {
        U_FREQ_SCALE D32;
        D32.u32 = pJpegdReg->FREQ_SCALE.u32;

        D32.bits.freq_scale = 0;
        D32.bits.ck_gt_en = 0;
        D32.bits.outstanding = 3;
        D32.bits.axi_id = 0;
        if (pstConfig->bOutYUV == HI_TRUE) {
            D32.bits.jidct_emar_en = 1;
        } else {
            D32.bits.jidct_emar_en = 0;
        }
        pJpegdReg->FREQ_SCALE.u32 = D32.u32;
    }

    /*  12. OUT_TYPE */
    {
        U_OUT_TYPE D32;

        D32.u32 = 0;

        if (pstConfig->bOutYUV == HI_TRUE) {
            if (pstConfig->enPictureFormat == PICTURE_FORMAT_YUV400) {
                D32.bits.jidct_yuv420_en = 0;
            } else {
                D32.bits.jidct_yuv420_en = 1;
            }
        } else {
            D32.bits.jidct_yuv420_en = 0;
            D32.bits.hor_med_en = 1;
            D32.bits.ver_med_en = 1;
            D32.bits.dither_en = 1;

            D32.bits.hor_med_en = 0;
            D32.bits.ver_med_en = 0;
            D32.bits.dither_en = 0;
            if (pstConfig->enPixelFormat == PIXEL_FORMAT_ARGB_8888) {
                D32.bits.out_rgb_type = 0;
            } else if (pstConfig->enPixelFormat == PIXEL_FORMAT_ABGR_8888) {
                D32.bits.out_rgb_type = 1;
            } else if (pstConfig->enPixelFormat == PIXEL_FORMAT_ARGB_1555) {
                D32.bits.out_rgb_type = 2;
            } else if (pstConfig->enPixelFormat == PIXEL_FORMAT_ABGR_1555) {
                D32.bits.out_rgb_type = 3;
            } else if (pstConfig->enPixelFormat == PIXEL_FORMAT_RGB_565) {
                D32.bits.out_rgb_type = 4;
            } else if (pstConfig->enPixelFormat == PIXEL_FORMAT_BGR_565) {
                D32.bits.out_rgb_type = 5;
            } else if (pstConfig->enPixelFormat == PIXEL_FORMAT_RGB_888) {
                D32.bits.out_rgb_type = 6;
            } else if (pstConfig->enPixelFormat == PIXEL_FORMAT_BGR_888) {
                D32.bits.out_rgb_type = 7;
            }
        }

        pJpegdReg->OUT_TYPE.u32 = D32.u32;
    }

    /*  . JPGD_ALPHA */
    if (pstConfig->bOutYUV == HI_FALSE) {
        U_JPGD_ALPHA D32;

        D32.u32 = 0;

        D32.bits.jpgd_a = pstConfig->u32Alpha;
        pJpegdReg->JPGD_ALPHA.u32 = D32.u32;
    }

    {
        unsigned int i;

        for (i = 0; i < JPEGD_IP_NUM; i++) {
            pJpegdReg->MTN_ADDRESS0_LSB = GetLowAddr(pstConfig->u64PhyEmarBuffer0);
            pJpegdReg->MTN_ADDRESS0_MSB.u32 = GetHighAddr(pstConfig->u64PhyEmarBuffer0);

            pJpegdReg->MTN_ADDRESS1_LSB = GetLowAddr(pstConfig->u64PhyEmarBuffer1);
            pJpegdReg->MTN_ADDRESS1_MSB.u32 = GetHighAddr(pstConfig->u64PhyEmarBuffer1);
        }
    }

    /*  PICCUT_STARTPOS     U_PICCUT_ENDPOS */
    if (pstConfig->bOutYUV == HI_FALSE) {
        {
            U_PICCUT_STARTPOS D32;

            D32.u32 = 0;

            D32.bits.jcfg2jytr_pic_startx = 0;
            D32.bits.jcfg2jytr_pic_starty = 0;
            pJpegdReg->PICCUT_STARTPOS.u32 = D32.u32;
        }

        {
            U_PICCUT_ENDPOS D32;

            D32.u32 = 0;

            D32.bits.jcfg2jytr_pic_endx = pstConfig->u32Width - 1;
            D32.bits.jcfg2jytr_pic_endy = pstConfig->u32Height - 1;
            pJpegdReg->PICCUT_ENDPOS.u32 = D32.u32;
        }
    }

    {
        U_SAMPLING_FACTOR D32;

        D32.u32 = 0;

        D32.bits.v_fac = pstConfig->u8VFac;
        D32.bits.u_fac = pstConfig->u8UFac;
        D32.bits.y_fac = pstConfig->u8YFac;

        pJpegdReg->SAMPLING_FACTOR.u32 = D32.u32;
    }

    /*  13. DRI */
    {
        U_DRI D32;

        D32.u32 = 0;

        D32.bits.jcfg2jvld_ri = pstConfig->u32Dri;

        pJpegdReg->DRI.u32 = D32.u32;
    }

    {
        unsigned int i;
        for (i = 0; i < QUANT_TABLE_SIZE; i++) {
            pJpegdReg->QUANT_TABLE[i].u32 = pstConfig->u32QuantTable[i];
        }
    }

    {
        unsigned int i;
        for (i = 0; i < HDC_TABLE_SIZE; i++) {
            pJpegdReg->HDC_TABLE[i].u32 = pstConfig->u32HuffmanTable[i];
        }
    }

    {
        unsigned int i;
        for (i = 0; i < HAC_MIN_TABLE_SIZE; i++) {
            pJpegdReg->HAC_MIN_TABLE[i].u32 = pstConfig->u32HuffmanMinTable[i];
        }
    }

    {
        unsigned int i;
        for (i = 0; i < HAC_BASE_TABLE_SIZE; i++) {
            pJpegdReg->HAC_BASE_TABLE[i].u32 = pstConfig->u32HuffmanBaseTable[i];
        }
    }

    {
        unsigned int i;
        for (i = 0; i < HAC_SYMBOL_TABLE_SIZE; i++) {
            pJpegdReg->HAC_SYMBOL_TABLE[i] = pstConfig->u32HuffmanSymbolTable[i];
        }
    }

    return;
}

void JPEGD_DRV_ReadRegs(HI_VOID *pRegBase, JPEGD_VPU_STATUS_S *pstJpegdVpuStatus)
{
    S_JPGD_REGS_TYPE *pJpegdReg = (S_JPGD_REGS_TYPE *)pRegBase;

    pstJpegdVpuStatus->bIntDecFinish = pJpegdReg->JPEG_INT.bits.int_dec_fnsh;
    pstJpegdVpuStatus->bIntDecErr = pJpegdReg->JPEG_INT.bits.int_dec_err;
    pstJpegdVpuStatus->bIntOverTime = pJpegdReg->JPEG_INT.bits.int_over_time;
    pstJpegdVpuStatus->bIntBsRes = pJpegdReg->JPEG_INT.bits.int_bs_res;
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


