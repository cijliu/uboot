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
#include "drv_hdmi_dfm.h"
#include "hdmi_product_define.h"

#define FRLCHAR_PER_CB_NUM      (510)
#define RS_PER_CB_NUM           (8)
#define CB_PER_SB_NUM           (4)
#define PIXELCLK_TOLERANCE      (5)
#define AUDIOCLK_TOLERANCE      (1)
#define BITRATE_TOLERANCE       (3)
#define TB_BORROW_MAX           (400)

#define GETK420(pixelformat)            (((pixelformat) == 1) ? 2 : 1)
#define GETKCD(pixelformat, colorspace) (((pixelformat) == 2) ? 8 : (colorspace))

#define DFM_CHK_ZERO(x) \
{ \
    if (x == 0) \
    { \
        HDMI_ERR("x is zero!\n"); \
        return; \
    } \
}

static DFM_INFO_S s_stDFMInfo;

static HI_S64 DoDiv(HI_S64 s64DivA, HI_S64 s64DivB)
{
    HI_S64 s64DivResult = 0;

    s64DivResult = HDMI_DO_DIVS64(s64DivA, s64DivB);

    return s64DivResult;
}

static DFM_INFO_S *GetDFMInfo(HI_VOID)
{
    return &s_stDFMInfo;
}

static HI_S32 DFMGetAudioAP(DFM_IN_S *pstDFMIn)
{
    HI_S32 s32AudioAP = 0;

    if (pstDFMIn == HI_NULL)
    {
        return 0;
    }

    if (pstDFMIn->s32PacketType == 0x2 || pstDFMIn->s32PacketType == 0x7)
    {
        if (pstDFMIn->s32Layout == 0)
        {
            s32AudioAP = 25;
        }
        else
        {
            s32AudioAP = 100;
        }
    }
    else if (pstDFMIn->s32PacketType == 0x8)
    {
         s32AudioAP = 100;
    }
    else if (  pstDFMIn->s32PacketType == 0x9
            || pstDFMIn->s32PacketType == 0xE
            || pstDFMIn->s32PacketType == 0xF)
    {
        s32AudioAP = 100;
    }
    else if (pstDFMIn->s32PacketType == 0xB || pstDFMIn->s32PacketType == 0xC)
    {
        if (pstDFMIn->s32ACAT == 1)
        {
            s32AudioAP = 200;
        }
        else if (pstDFMIn->s32ACAT == 2)
        {
            s32AudioAP = 300;
        }
        else if (pstDFMIn->s32ACAT == 3)
        {
            s32AudioAP = 400;
        }
    }

    return s32AudioAP;
}

static HI_VOID DFMInfoInit(DFM_IN_S *pstDFMIn,  DFM_INFO_S *pstDFMInfo)
{
    HI_S32 s32Kcd = 0;
    HI_S32 s32K420 = 0;

    if (pstDFMIn == HI_NULL || pstDFMInfo == HI_NULL)
    {
        return;
    }

    s32Kcd = GETKCD(pstDFMIn->s32PixelFormat, pstDFMIn->s32ColorDepth);
    s32K420 = GETK420(pstDFMIn->s32PixelFormat);

    pstDFMInfo->s32Htotal = pstDFMIn->s32Hactive + pstDFMIn->s32Hblank;

    pstDFMInfo->s32Vtotal = pstDFMIn->s32Vactive + pstDFMIn->s32Vblank;

    pstDFMInfo->s64PixelClk = DoDiv((HI_S64)pstDFMInfo->s32Htotal
                                    *pstDFMInfo->s32Vtotal*pstDFMIn->s32VFreq, 1000);

    pstDFMInfo->s32CFrlSB = FRLCHAR_PER_CB_NUM*4 + pstDFMIn->s32LaneNum;
    DFM_CHK_ZERO(pstDFMInfo->s32CFrlSB);

    pstDFMInfo->s32OverheadSB = pstDFMIn->s32LaneNum*100000
                                /pstDFMInfo->s32CFrlSB;//step1.01 x100000

    pstDFMInfo->s32OverheadRS = RS_PER_CB_NUM*CB_PER_SB_NUM*100000
                                /pstDFMInfo->s32CFrlSB;//step1.02   x100000

    pstDFMInfo->s32OverheadMap = 25*10000/pstDFMInfo->s32CFrlSB;//step1.03   x100000

    pstDFMInfo->s32OverheadMin = pstDFMInfo->s32OverheadSB + pstDFMInfo->s32OverheadRS
                                 + pstDFMInfo->s32OverheadMap;//step1.04   x100000

    pstDFMInfo->s32OverheadM = 300;//step1.05  x100000

    pstDFMInfo->s32OverheadMax = pstDFMInfo->s32OverheadMin + pstDFMInfo->s32OverheadM;//step1.06  x100000

    pstDFMInfo->s64MaxPixelClk = DoDiv(pstDFMInfo->s64PixelClk*
                                 (1000 + PIXELCLK_TOLERANCE),1000);//step1.07
    DFM_CHK_ZERO(pstDFMInfo->s64MaxPixelClk);

    pstDFMInfo->s64MinPixelClk = DoDiv(pstDFMInfo->s64PixelClk*
                                 (1000 - PIXELCLK_TOLERANCE),1000);
    DFM_CHK_ZERO(pstDFMInfo->s64MinPixelClk);

    pstDFMInfo->s32MaxTimeLine = DoDiv((HI_S64)pstDFMInfo->s32Htotal*1000000000000,
                                 pstDFMInfo->s64MinPixelClk);//x1000000000000

    pstDFMInfo->s32MinTimeLine = DoDiv((HI_S64)pstDFMInfo->s32Htotal*1000000000000,
                                 pstDFMInfo->s64MaxPixelClk);//step1.08   x1000000000000

    pstDFMInfo->s64MinBitRate = DoDiv((HI_S64)pstDFMIn->s32BitRate*1000000000
                                *(10000 - BITRATE_TOLERANCE), 10000);//step1.09

    pstDFMInfo->s64MaxBitRate = DoDiv((HI_S64)pstDFMIn->s32BitRate*1000000000
                                *(10000 + BITRATE_TOLERANCE), 10000);

    pstDFMInfo->s64MaxFrlCharRate = DoDiv(pstDFMInfo->s64MaxBitRate, 18);

    pstDFMInfo->s64MinFrlCharRate = DoDiv(pstDFMInfo->s64MinBitRate, 18);//step1.10

    pstDFMInfo->s32MaxFrlCharsPerLine = (HI_S32)DoDiv(pstDFMInfo->s32MaxTimeLine
                                     *pstDFMInfo->s64MaxFrlCharRate
                                     *pstDFMIn->s32LaneNum, 1000000000000);

    pstDFMInfo->s32MinFrlCharsPerLine = (HI_S32)DoDiv(pstDFMInfo->s32MinTimeLine
                                     *pstDFMInfo->s64MinFrlCharRate
                                     *pstDFMIn->s32LaneNum, 1000000000000);//step1.11
    DFM_CHK_ZERO(pstDFMInfo->s32MinFrlCharsPerLine);

    pstDFMInfo->s32AudioAP = DFMGetAudioAP(pstDFMIn);//step1.12

    pstDFMInfo->s32AudioRAP = (HI_S32)DoDiv((HI_S64)pstDFMIn->s32AudioRate
                               *(1000 + AUDIOCLK_TOLERANCE)
                               *pstDFMInfo->s32AudioAP,100000);//step1.13

    pstDFMInfo->s32AvgAudioPackets = (HI_S32)DoDiv((HI_S64)pstDFMInfo->s32AudioRAP
                                      *pstDFMInfo->s32MinTimeLine, 1000000000);//step1.14  x1000

    pstDFMInfo->s32AudioPackets = (pstDFMInfo->s32AvgAudioPackets + 1000 -1)/1000;//step1.15

    pstDFMInfo->s32BlankAudioMin = 64 + 32*pstDFMInfo->s32AudioPackets;//step1.16

    pstDFMInfo->s32CFrlFree = MAX(((pstDFMIn->s32Hblank*s32Kcd)/s32K420)/8
                              - 32*(1 + pstDFMInfo->s32AudioPackets) -7, 0);//step1.17

    pstDFMInfo->s32CFrlRCMargin = 4;//step1.18

    pstDFMInfo->s32CFrlRCSavings = MAX((7*pstDFMInfo->s32CFrlFree/8
                                   - pstDFMInfo->s32CFrlRCMargin), 0);//step1.19

    pstDFMInfo->s32Bpp = ((24*s32Kcd)/s32K420)/8;//step1.20

    pstDFMInfo->s32ActiveBytesPerLine = pstDFMInfo->s32Bpp*pstDFMIn->s32Hactive/8;//step1.21

    pstDFMInfo->s32ActiveTBPerLine = (pstDFMInfo->s32ActiveBytesPerLine + 3 -1)/3;//step1.22

    pstDFMInfo->s32BlankTBPerLine = (pstDFMIn->s32Hblank*s32Kcd/s32K420 + 8 - 1)/8;//step1.23

    pstDFMInfo->bAudioSupport = (pstDFMInfo->s32BlankTBPerLine
                                 >= pstDFMInfo->s32BlankAudioMin)
                                 ? HI_TRUE : HI_FALSE;//step1.24

    DFM_CHK_ZERO(pstDFMInfo->s32Htotal);
    pstDFMInfo->s64AvgTBRate = DoDiv(pstDFMInfo->s64MaxPixelClk
                               *(pstDFMInfo->s32ActiveTBPerLine
                               + pstDFMInfo->s32BlankTBPerLine),
                               pstDFMInfo->s32Htotal);//step1.25

    pstDFMInfo->s32ActiveTimeRef = DoDiv((HI_S64)pstDFMInfo->s32MinTimeLine
                                   *pstDFMIn->s32Hactive,
                                   pstDFMInfo->s32Htotal);//step1.26  x1000000000000

    pstDFMInfo->s32BlankTimeRef = DoDiv((HI_S64)pstDFMInfo->s32MinTimeLine
                                  *pstDFMIn->s32Hblank,
                                  pstDFMInfo->s32Htotal);//step1.27  x1000000000000

    pstDFMInfo->s32ActiveTimeMin = DoDiv((HI_S64)pstDFMInfo->s32ActiveTBPerLine*3*100000000000000,
                                   DoDiv(2*pstDFMIn->s32LaneNum*pstDFMInfo->s64MinFrlCharRate
                                   *(100000 - pstDFMInfo->s32OverheadMax), 1000)); //step1.28  x1000000000000

    pstDFMInfo->s32BlankTimeMin = DoDiv((HI_S64)pstDFMInfo->s32BlankTBPerLine*100000000000000,
                                  DoDiv(pstDFMIn->s32LaneNum*pstDFMInfo->s64MinFrlCharRate
                                  *(100000 - pstDFMInfo->s32OverheadMax), 1000)); //step1.29   x1000000000000

    if (pstDFMInfo->s32ActiveTimeRef >= pstDFMInfo->s32ActiveTimeMin
        && pstDFMInfo->s32BlankTimeRef >= pstDFMInfo->s32BlankTimeMin)
    {
        pstDFMInfo->s32TBorrow = 0;//step1.30
    }
    else if (pstDFMInfo->s32ActiveTimeRef < pstDFMInfo->s32ActiveTimeMin
        && pstDFMInfo->s32BlankTimeRef >= pstDFMInfo->s32BlankTimeMin)
    {
        pstDFMInfo->s32TBorrow = pstDFMInfo->s32ActiveTimeMin
                               - pstDFMInfo->s32ActiveTimeRef;//step1.31
    }
    else
    {
        pstDFMInfo->s32TBorrow = -1;
    }

    if (pstDFMInfo->s32TBorrow == -1)
    {
        pstDFMInfo->s32TBBorrow = -1;
    }
    else
    {
        pstDFMInfo->s32TBBorrow = ((HI_S32)DoDiv(pstDFMInfo->s32TBorrow
                                  *pstDFMInfo->s64AvgTBRate, 100000000000)
                                  + 10 - 1)/10;//step1.32
    }

    if (pstDFMInfo->s32TBBorrow == -1)
    {
        pstDFMInfo->bVideoSupport = HI_FALSE;
    }
    else
    {
        pstDFMInfo->bVideoSupport = (pstDFMInfo->s32TBBorrow <= TB_BORROW_MAX)
                                    ? HI_TRUE : HI_FALSE;//step1.33
    }

    pstDFMInfo->s32CFrlActualPayload = (3*pstDFMInfo->s32ActiveTBPerLine + 2 - 1)/2
                                        + pstDFMInfo->s32BlankTBPerLine
                                        - pstDFMInfo->s32CFrlRCSavings;//step1.34

    pstDFMInfo->s32Utilization = DoDiv((HI_S64)pstDFMInfo->s32CFrlActualPayload*100000,
                                       (HI_S64)pstDFMInfo->s32MinFrlCharsPerLine); //step1.35  x100000

    pstDFMInfo->s32Margin = 100000 - (pstDFMInfo->s32Utilization
                            + pstDFMInfo->s32OverheadMax);//step1.36    x100000

    pstDFMInfo->bUncompressSupport = (pstDFMInfo->s32Margin >= 0)
                                     ? HI_TRUE : HI_FALSE;//step1.37

    pstDFMInfo->bCanbeTrans = (pstDFMInfo->bAudioSupport && pstDFMInfo->bVideoSupport
                               && pstDFMInfo->bUncompressSupport) ? HI_TRUE : HI_FALSE;

    pstDFMInfo->bIsExtraMode = (pstDFMInfo->bCanbeTrans && (pstDFMInfo->s32TBBorrow > 0))
                                ? HI_TRUE : HI_FALSE;

#ifdef DEBUG
    HDMI_INFO("start\n");
    HDMI_INFO("s32Htotal = %d\n",pstDFMInfo->s32Htotal);
    HDMI_INFO("s32Vtotal = %d\n",pstDFMInfo->s32Vtotal);
    HDMI_INFO("s64PixelClk = %lld\n",pstDFMInfo->s64PixelClk);
    HDMI_INFO("s32Bpp = %d\n",pstDFMInfo->s32Bpp);
    HDMI_INFO("s32CFrlSB = %d\n",pstDFMInfo->s32CFrlSB);
    HDMI_INFO("s32OverheadSB = %d\n",pstDFMInfo->s32OverheadSB);
    HDMI_INFO("s32OverheadRS = %d\n",pstDFMInfo->s32OverheadRS);
    HDMI_INFO("s32OverheadMap = %d\n",pstDFMInfo->s32OverheadMap);
    HDMI_INFO("s32OverheadMin = %d\n",pstDFMInfo->s32OverheadMin);
    HDMI_INFO("s32OverheadM = %d\n",pstDFMInfo->s32OverheadM);
    HDMI_INFO("s32OverheadMax = %d\n",pstDFMInfo->s32OverheadMax);
    HDMI_INFO("s64MaxPixelClk = %lld\n",pstDFMInfo->s64MaxPixelClk);
    HDMI_INFO("s64MinPixelClk = %lld\n",pstDFMInfo->s64MinPixelClk);
    HDMI_INFO("s32MaxTimeLine = %d\n",pstDFMInfo->s32MaxTimeLine);
    HDMI_INFO("s32MinTimeLine = %d\n",pstDFMInfo->s32MinTimeLine);
    HDMI_INFO("s64MaxBitRate = %lld\n",pstDFMInfo->s64MaxBitRate);
    HDMI_INFO("s64MinBitRate = %lld\n",pstDFMInfo->s64MinBitRate);
    HDMI_INFO("s64MaxFrlCharRate = %lld\n",pstDFMInfo->s64MaxFrlCharRate);
    HDMI_INFO("s64MinFrlCharRate = %lld\n",pstDFMInfo->s64MinFrlCharRate);
    HDMI_INFO("s32MaxFrlCharsPerLine = %d\n",pstDFMInfo->s32MaxFrlCharsPerLine);
    HDMI_INFO("s32MinFrlCharsPerLine = %d\n",pstDFMInfo->s32MinFrlCharsPerLine);
    HDMI_INFO("s32AudioAP = %d\n",pstDFMInfo->s32AudioAP);
    HDMI_INFO("s32AudioRAP = %d\n",pstDFMInfo->s32AudioRAP);
    HDMI_INFO("s32AvgAudioPackets = %d\n",pstDFMInfo->s32AvgAudioPackets);
    HDMI_INFO("s32AudioPackets = %d\n",pstDFMInfo->s32AudioPackets);
    HDMI_INFO("s32BlankAudioMin = %d\n",pstDFMInfo->s32BlankAudioMin);
    HDMI_INFO("s32CFrlFree = %d\n",pstDFMInfo->s32CFrlFree);
    HDMI_INFO("s32CFrlRCMargin = %d\n",pstDFMInfo->s32CFrlRCMargin);
    HDMI_INFO("s32CFrlRCSavings = %d\n",pstDFMInfo->s32CFrlRCSavings);
    HDMI_INFO("s32ActiveBytesPerLine = %d\n",pstDFMInfo->s32ActiveBytesPerLine);
    HDMI_INFO("s32ActiveTBPerLine = %d\n",pstDFMInfo->s32ActiveTBPerLine);
    HDMI_INFO("s32BlankTBPerLine = %d\n",pstDFMInfo->s32BlankTBPerLine);
    HDMI_INFO("bAudioSupport = %s\n",pstDFMInfo->bAudioSupport ? "TRUE" : "FALSE");
    HDMI_INFO("s64AvgTBRate = %lld\n",pstDFMInfo->s64AvgTBRate);
    HDMI_INFO("s32ActiveTimeRef = %d\n",pstDFMInfo->s32ActiveTimeRef);
    HDMI_INFO("s32BlankTimeRef = %d\n",pstDFMInfo->s32BlankTimeRef);
    HDMI_INFO("s32ActiveTimeMin = %d\n",pstDFMInfo->s32ActiveTimeMin);
    HDMI_INFO("s32BlankTimeMin = %d\n",pstDFMInfo->s32BlankTimeMin);
    HDMI_INFO("s32TBorrow = %d\n",pstDFMInfo->s32TBorrow);
    HDMI_INFO("s32TBBorrow = %d\n",pstDFMInfo->s32TBBorrow);
    HDMI_INFO("bVideoSupport = %s\n",pstDFMInfo->bVideoSupport ? "TRUE" : "FALSE");
    HDMI_INFO("s32CFrlActualPayload = %d\n",pstDFMInfo->s32CFrlActualPayload);
    HDMI_INFO("s32Utilization = %d\n",pstDFMInfo->s32Utilization);
    HDMI_INFO("s32Margin = %d\n",pstDFMInfo->s32Margin);
    HDMI_INFO("bUncompressSupport = %s\n",pstDFMInfo->bUncompressSupport ? "TRUE" : "FALSE");
    HDMI_INFO("bCanbeTrans = %s\n",pstDFMInfo->bCanbeTrans ? "TRUE" : "FALSE");
    HDMI_INFO("bIsExtraMode = %s\n",pstDFMInfo->bIsExtraMode ? "TRUE" : "FALSE");
#endif

    return;
}

HI_BOOL DRV_HDMI_DFMFormatCanbeSupport(DFM_IN_S *pstDFMIn)
{
    HI_BOOL bRet = HI_FALSE;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    if (pstDFMIn == HI_NULL)
    {
        return HI_FALSE;
    }

    pstDFMInfo = GetDFMInfo();
    if (pstDFMInfo == HI_NULL)
    {
        return HI_FALSE;
    }

    DFMInfoInit(pstDFMIn, pstDFMInfo);

    bRet = (pstDFMInfo->bAudioSupport && pstDFMInfo->bVideoSupport
            && pstDFMInfo->bUncompressSupport) ? HI_TRUE : HI_FALSE;

    return bRet;
}

