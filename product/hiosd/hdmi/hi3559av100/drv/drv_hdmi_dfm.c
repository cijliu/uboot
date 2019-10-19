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

#define IDEAL_DFM_SCALE_FACTOR_TMDS      (1)
#define BLANK_DFM_SCALE_FACTOR_FRL       (1)
#define BLANK_RC_RATIO                   (8)
#define AV_DFM_SCALE_FACTOR_FRL          (2) //x3
#define CFRL_TOLERANCE                   (492)
#define LINE_START_TOLERANCE             (8)
#define CFRL_SB_PAYLOAD                  (2008)
#define CFRL_PKT_PAYLOAD                 (1020)
#define CFRL_PKT_AVERAGE                 (1004)
#define FIX_ERR3                         (1)
#define FSM_TOLERANCE                    (12)

#define GETK420(pixelformat) (((pixelformat) == 1) ? 2 : 1)
#define GETKCD(pixelformat, colorspace) (((pixelformat) == 2) ? 8 : (colorspace))

static DFM_INFO_S s_stDFMInfo;
static DFM_BASE_PARAS_S s_stBaseParas;
static HI_S64 DoDiv(HI_S64 s64DivA, HI_S64 s64DivB)
{
	HI_S64 s64DivResult = 0;
	s64DivResult = HDMI_DO_DIVS64(s64DivA, s64DivB);
	return s64DivResult;
}

static DFM_BASE_PARAS_S *GetDFMBaseParas(HI_VOID)
{
    return &s_stBaseParas;
}

static DFM_INFO_S *GetDFMInfo(HI_VOID)
{
    return &s_stDFMInfo;
}

static HI_S32 DFMGetAudioAP(DFM_IN_S *pstDFMIn)//x100
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
    else if (pstDFMIn->s32PacketType == 0x9 || pstDFMIn->s32PacketType == 0xE
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

    pstDFMInfo->s64MinPixelClk = DoDiv(pstDFMInfo->s64PixelClk*
                                 (1000 - PIXELCLK_TOLERANCE),1000);

    pstDFMInfo->s32MaxTimeLine = DoDiv(pstDFMInfo->s32Htotal*1000000000000,
                                 pstDFMInfo->s64MinPixelClk);//x1000000000000

    pstDFMInfo->s32MinTimeLine = DoDiv(pstDFMInfo->s32Htotal*1000000000000,
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

    pstDFMInfo->s32AudioAP = DFMGetAudioAP(pstDFMIn);//step1.12

    pstDFMInfo->s32AudioRAP = (HI_S32)DoDiv((HI_S64)pstDFMIn->s32AudioRate
                               *(1000 + AUDIOCLK_TOLERANCE)
                               *pstDFMInfo->s32AudioAP,100000);//step1.13

    pstDFMInfo->s32AvgAudioPackets = (HI_S32)DoDiv((HI_S64)pstDFMInfo->s32AudioRAP
                                      *pstDFMInfo->s32MinTimeLine, 1000000000);//step1.14  x1000

    pstDFMInfo->s32AudioPackets = (pstDFMInfo->s32AvgAudioPackets + 1000 -1)/1000;//step1.15

    pstDFMInfo->s32BlankAudioMin = 64 + 32*pstDFMInfo->s32AudioPackets;//step1.16

    pstDFMInfo->s32CFrlFree = MAX(pstDFMIn->s32Hblank*s32Kcd/s32K420/8
                              - 32*(1 + pstDFMInfo->s32AudioPackets) -7, 0);//step1.17

    pstDFMInfo->s32CFrlRCMargin = 4;//step1.18

    pstDFMInfo->s32CFrlRCSavings = MAX((7*pstDFMInfo->s32CFrlFree/8
                                   - pstDFMInfo->s32CFrlRCMargin), 0);//step1.19

    pstDFMInfo->s32Bpp = 24*s32Kcd/s32K420/8;//step1.20

    pstDFMInfo->s32ActiveBytesPerLine = pstDFMInfo->s32Bpp*pstDFMIn->s32Hactive/8;//step1.21

    pstDFMInfo->s32ActiveTBPerLine = (pstDFMInfo->s32ActiveBytesPerLine + 3 -1)/3;//step1.22

    pstDFMInfo->s32BlankTBPerLine = (pstDFMIn->s32Hblank*s32Kcd/s32K420 + 8 - 1)/8;//step1.23

    pstDFMInfo->bAudioSupport = (pstDFMInfo->s32BlankTBPerLine
                                 >= pstDFMInfo->s32BlankAudioMin)
                                 ? HI_TRUE : HI_FALSE;//step1.24

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

    pstDFMInfo->s32ActiveTimeMin = DoDiv(pstDFMInfo->s32ActiveTBPerLine*3*100000000000000,
                                   DoDiv(2*pstDFMIn->s32LaneNum*pstDFMInfo->s64MinFrlCharRate
                                   *(100000 - pstDFMInfo->s32OverheadMax), 1000)); //step1.28  x1000000000000

    pstDFMInfo->s32BlankTimeMin = DoDiv(pstDFMInfo->s32BlankTBPerLine*100000000000000,
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

static HI_VOID DFMBaseParasCalc(DFM_IN_S *pstDFMIn, DFM_BASE_PARAS_S * pstBaseParas)
{
    HI_BOOL bDeepColor = HI_FALSE;
    HI_BOOL bHactiveDiv4 = HI_FALSE;
    HI_BOOL bHactiveDiv8 = HI_FALSE;
    HI_S32 s32DeltaFRLCharNumPerLine = 0;
    HI_S32 s32ActualBlank1AndAvTime = 0;
    HI_S32 s32IdealBlank1AndAvTime = 0;
    HI_S64 s64K5MaxActualBlank = 0;
    HI_S32 s32Temp = 0;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    if (pstDFMIn == HI_NULL || pstBaseParas == HI_NULL)
    {
        return;
    }

    pstDFMInfo = GetDFMInfo();

    bDeepColor = ((pstDFMIn->s32PixelFormat == 1 || pstDFMIn->s32PixelFormat == 3)
                 && (pstDFMIn->s32ColorDepth == 10 || pstDFMIn->s32ColorDepth == 12))
                 ? HI_TRUE : HI_FALSE;

    bHactiveDiv4 = ((pstDFMIn->s32Hactive%4) == 0) ? HI_TRUE : HI_FALSE;
    bHactiveDiv8 = ((pstDFMIn->s32Hactive%8) == 0) ? HI_TRUE : HI_FALSE;

    pstBaseParas->s32BlankLineMaxTriByte = (pstDFMInfo->s32Htotal
                                            *pstDFMInfo->s32Bpp + 24 - 1)/24;

    if (bDeepColor == HI_TRUE)
    {
        if (pstDFMIn->s32PixelFormat == 3)
        {
            pstBaseParas->s32AvLineMaxTriByte = ((bHactiveDiv4 == HI_TRUE)
                                                ? (pstDFMIn->s32Hactive
                                                  *pstDFMIn->s32ColorDepth/8 + 1)
                                                : ((pstDFMIn->s32Hactive
                                                  *pstDFMIn->s32ColorDepth + 8 - 1)
                                                  /8 + 1)) + 2;

            pstBaseParas->s32AvLineMinTriByte = ((bHactiveDiv4 == HI_TRUE)
                                                ? (pstDFMIn->s32Hactive
                                                  *pstDFMIn->s32ColorDepth/8)
                                                : ((pstDFMIn->s32Hactive
                                                   *pstDFMIn->s32ColorDepth
                                                   + 8 - 1)/8)) + 2;
        }
        else
        {
            pstBaseParas->s32AvLineMaxTriByte = ((bHactiveDiv8 == HI_TRUE)
                                                ? (pstDFMIn->s32Hactive/2
                                                  *pstDFMIn->s32ColorDepth/8 + 1)
                                                : ((pstDFMIn->s32Hactive/2
                                                   *pstDFMIn->s32ColorDepth
                                                   + 8 - 1)/8 + 1)) + 2;

            pstBaseParas->s32AvLineMinTriByte = ((bHactiveDiv4 == HI_TRUE)
                                                ? (pstDFMIn->s32Hactive/2
                                                  *pstDFMIn->s32ColorDepth/8)
                                                : ((pstDFMIn->s32Hactive
                                                   *pstDFMIn->s32ColorDepth
                                                   + 8 - 1)/8)) + 2;
        }
    }
    else
    {
        pstBaseParas->s32AvLineMaxTriByte = pstDFMIn->s32Hactive
                                            *pstDFMInfo->s32Bpp/24 + 2;

        pstBaseParas->s32AvLineMinTriByte = pstDFMIn->s32Hactive
                                            *pstDFMInfo->s32Bpp/24 + 2;
    }

    pstBaseParas->s32BlankLineMinTriByte = pstDFMInfo->s32Htotal
                                           *pstDFMInfo->s32Bpp/24;

    s32DeltaFRLCharNumPerLine = pstDFMInfo->s32MaxFrlCharsPerLine
                                - pstDFMInfo->s32MinFrlCharsPerLine;

    pstBaseParas->s32ClkTolerancePerLine =  DoDiv(s32DeltaFRLCharNumPerLine
                                            *pstDFMInfo->s64MinPixelClk
                                            *(pstDFMInfo->s32Bpp*10000/24),
                                            pstDFMIn->s32LaneNum
                                            *pstDFMInfo->s64MaxFrlCharRate); // x10000

    s32ActualBlank1AndAvTime = DoDiv((HI_S64)pstDFMInfo->s32MinTimeLine
                               *(pstDFMInfo->s32Htotal - pstDFMIn->s32Hfront),
                               pstDFMInfo->s32Htotal); // x1000

    s32IdealBlank1AndAvTime = DoDiv((HI_S64)pstDFMInfo->s32MaxTimeLine
                              *(pstDFMInfo->s32Htotal - pstDFMIn->s32Hfront),
                              pstDFMInfo->s32Htotal); // x1000

    s32Temp = DoDiv((HI_S64)(s32IdealBlank1AndAvTime - s32ActualBlank1AndAvTime)*10000
                    *pstBaseParas->s32AvLineMinTriByte*pstDFMInfo->s32Htotal,
                     (HI_S64)pstDFMInfo->s32MaxTimeLine*pstDFMIn->s32Hactive);

    pstBaseParas->s32ActualBlank1AndAvEndCdiff = s32Temp; //x10000

    pstBaseParas->s64K1MaxIdealTMDS = DoDiv(pstDFMInfo->s64MaxPixelClk
                                            *IDEAL_DFM_SCALE_FACTOR_TMDS
                                            *pstDFMInfo->s32Bpp, 24);

    pstBaseParas->s64K1MinIdealTMDS = DoDiv(pstDFMInfo->s64MinPixelClk
                                            *IDEAL_DFM_SCALE_FACTOR_TMDS
                                            *pstDFMInfo->s32Bpp, 24);

    s64K5MaxActualBlank = DoDiv(pstDFMInfo->s64MaxBitRate*pstDFMIn->s32LaneNum
                                *BLANK_DFM_SCALE_FACTOR_FRL, 18);

    pstBaseParas->s64K5MinActualBlank = DoDiv(pstDFMInfo->s64MinBitRate
                                              *pstDFMIn->s32LaneNum
                                              *BLANK_DFM_SCALE_FACTOR_FRL, 18);

    pstBaseParas->s64K6MaxActualBlank = s64K5MaxActualBlank*BLANK_RC_RATIO;

    pstBaseParas->s64K6MinActualAv = DoDiv(pstDFMInfo->s64MinBitRate
                                           *pstDFMIn->s32LaneNum
                                           *AV_DFM_SCALE_FACTOR_FRL, 18*3);

    pstBaseParas->s64K6MaxActualAv = DoDiv(pstDFMInfo->s64MaxBitRate
                                           *pstDFMIn->s32LaneNum
                                           *AV_DFM_SCALE_FACTOR_FRL, 18*3);

    pstBaseParas->s32Blank1LenMin = (pstDFMIn->s32Hsync + pstDFMIn->s32Hback)
                                     *pstDFMInfo->s32Bpp/24 - 2;
    pstBaseParas->s32Blank1LenMax = ((pstDFMIn->s32Hsync + pstDFMIn->s32Hback)
                                     *pstDFMInfo->s32Bpp + 24 - 1)/24 - 2;
    pstBaseParas->s32Blank2LenMin = pstDFMIn->s32Hfront*pstDFMInfo->s32Bpp/24;
    pstBaseParas->s32Blank2LenMax = (pstDFMIn->s32Hfront*pstDFMInfo->s32Bpp + 24 - 1)/24;
#ifdef DEBUG
    HDMI_INFO("bDeepColor = %s\n", (bDeepColor ? "true" : "false"));
    HDMI_INFO("bHactiveDiv4 = %s\n", (bHactiveDiv4 ? "true" : "false"));
    HDMI_INFO("bHactiveDiv8 = %s\n", (bHactiveDiv8 ? "true" : "false"));
    HDMI_INFO("s32BlankLineMaxTriByte = %d\n", pstBaseParas->s32BlankLineMaxTriByte);
    HDMI_INFO("s32AvLineMaxTriByte = %d\n", pstBaseParas->s32AvLineMaxTriByte);
    HDMI_INFO("s32AvLineMinTriByte = %d\n", pstBaseParas->s32AvLineMinTriByte);
    HDMI_INFO("s32BlankLineMinTriByte = %d\n", pstBaseParas->s32BlankLineMinTriByte);
    HDMI_INFO("s32DeltaFRLCharNumPerLine = %d\n", s32DeltaFRLCharNumPerLine);
    HDMI_INFO("s32ClkTolerancePerLine = %d\n", pstBaseParas->s32ClkTolerancePerLine);
    HDMI_INFO("s32ActualBlank1AndAvTime = %d\n", s32ActualBlank1AndAvTime);
    HDMI_INFO("s32IdealBlank1AndAvTime = %d\n", s32IdealBlank1AndAvTime);
    HDMI_INFO("s32ActualBlank1AndAvEndCdiff = %d\n", pstBaseParas->s32ActualBlank1AndAvEndCdiff);
    HDMI_INFO("s64K1MaxIdealTMDS = %lld\n", pstBaseParas->s64K1MaxIdealTMDS);
    HDMI_INFO("s64K1MinIdealTMDS = %lld\n", pstBaseParas->s64K1MinIdealTMDS);
    HDMI_INFO("s64K5MaxActualBlank = %lld\n", s64K5MaxActualBlank);
    HDMI_INFO("s64K5MinActualBlank = %lld\n", pstBaseParas->s64K5MinActualBlank);
    HDMI_INFO("s64K6MaxActualBlank = %lld\n", pstBaseParas->s64K6MaxActualBlank);
    HDMI_INFO("s64K6MinActualAv = %lld\n", pstBaseParas->s64K6MinActualAv);
    HDMI_INFO("s64K6MaxActualAv = %lld\n", pstBaseParas->s64K6MaxActualAv);
    HDMI_INFO("s32Blank1LenMin = %d\n", pstBaseParas->s32Blank1LenMin);
    HDMI_INFO("s32Blank1LenMax = %d\n", pstBaseParas->s32Blank1LenMax);
    HDMI_INFO("s32Blank2LenMin = %d\n", pstBaseParas->s32Blank2LenMin);
    HDMI_INFO("s32Blank2LenMax = %d\n", pstBaseParas->s32Blank2LenMax);
#endif
    return;
}

static HI_S32 DFMBlankParasCalc(DFM_IN_S *pstDFMIn, HI_S32 s32PreSetBlank)
{
    HI_S32 s32CFRLTolSubMarginBlank = 0;
    HI_S32 s32BlankGapLenStp1 = 0;
    HI_S32 s32BlankGapLenStp2 = 0;
    HI_S32 s32Blank2SliceNumMin = 0;
    HI_S32 s32BlankSliceDiff = 0;
    HI_S32 s32Temp = 0;
    DFM_INFO_S *pstDFMInfo = HI_NULL;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;

    if (pstDFMIn == HI_NULL)
    {
        return HI_FAILURE;
    }

    pstDFMInfo = GetDFMInfo();
    pstBaseParas = GetDFMBaseParas();

    s32Temp = ((pstDFMInfo->bIsExtraMode == HI_TRUE)
               ? pstBaseParas->s32ClkTolerancePerLine
               : MAX(pstBaseParas->s32ClkTolerancePerLine,
               pstBaseParas->s32ActualBlank1AndAvEndCdiff))
               + (LINE_START_TOLERANCE + s32PreSetBlank)*10000;

    pstBaseParas->s32FRLCharDeltaIdealBlank = s32Temp; // x10000

    s32CFRLTolSubMarginBlank = CFRL_TOLERANCE*10000
                               - pstBaseParas->s32FRLCharDeltaIdealBlank; //x10000

    s32Temp = DoDiv(s32CFRLTolSubMarginBlank
              *DoDiv(pstBaseParas->s64K6MaxActualBlank*1000000,
              pstBaseParas->s64K6MaxActualBlank
              - pstBaseParas->s64K1MinIdealTMDS), 4*10000000000);

    pstBaseParas->s32BlankMaxLen = s32Temp*4;

    if (pstBaseParas->s32BlankMaxLen == 0)
    {
        return HI_FAILURE;
    }

    s32BlankGapLenStp1 = DoDiv(pstBaseParas->s64K5MinActualBlank
                         *pstBaseParas->s32BlankMaxLen*10000,
                         pstBaseParas->s64K1MaxIdealTMDS)
                         - pstBaseParas->s32BlankMaxLen*10000; //x10000

    s32BlankGapLenStp2 = s32BlankGapLenStp1 - DoDiv((HI_S64)(s32BlankGapLenStp1
                         + (HI_S64)pstBaseParas->s32BlankMaxLen*10000)
                         *(pstDFMInfo->s32CFrlSB - CFRL_SB_PAYLOAD),
                         pstDFMInfo->s32CFrlSB) + (HI_S64)pstBaseParas->s32BlankMaxLen*10000
                         / CFRL_PKT_AVERAGE; //x10000

    pstBaseParas->s32BlankGapLen = (s32BlankGapLenStp2 + 10000 - 1)/10000;

    s32BlankSliceDiff = pstBaseParas->s32BlankMaxLen*IDEAL_DFM_SCALE_FACTOR_TMDS*1000
                        - DoDiv((pstBaseParas->s32BlankMaxLen + pstBaseParas->s32BlankGapLen)
                        *pstBaseParas->s64K1MaxIdealTMDS*pstDFMInfo->s32CFrlSB*1000,
                        pstBaseParas->s64K5MinActualBlank*CFRL_SB_PAYLOAD); // x1000

    pstBaseParas->s32BlankLineDiffDelt = (pstDFMInfo->s32Htotal*pstDFMInfo->s32Bpp
                                          /pstBaseParas->s32BlankMaxLen + 24 -1)/24
                                          *s32BlankSliceDiff; // x1000

    pstBaseParas->bShouldBeRCCompress = (((HI_S64)pstBaseParas->s32AvLineMaxTriByte*15*100000/10
                                         + (HI_S64)pstDFMIn->s32Hblank*pstDFMInfo->s32Bpp*100000/24)
                                         > (HI_S64)pstDFMInfo->s32MinFrlCharsPerLine
                                         *(100000 - pstDFMInfo->s32OverheadMax))
                                         ? HI_TRUE : HI_FALSE;

    s32Blank2SliceNumMin = (pstBaseParas->s32Blank2LenMin*10000
                            /pstBaseParas->s32BlankMaxLen + 10000 - 1)/10000;

    s32Temp = pstBaseParas->s32Blank2LenMin
              - (s32Blank2SliceNumMin - 1)
              *pstBaseParas->s32BlankMaxLen;

    pstBaseParas->s32Blank2LastSliceSizeMin = s32Temp;

    s32Temp = (pstBaseParas->s32BlankLineMinTriByte*10000
              /pstBaseParas->s32BlankMaxLen + 10000 - 1)/10000;

    pstBaseParas->s32BlankSliceNumMin = s32Temp;

    s32Temp = pstBaseParas->s32BlankLineMinTriByte
              - (pstBaseParas->s32BlankSliceNumMin - 1)
              *pstBaseParas->s32BlankMaxLen;

    pstBaseParas->s32BlankLastSliceSizeMin = s32Temp;

#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaIdealBlank = %d\n", pstBaseParas->s32FRLCharDeltaIdealBlank);
    HDMI_INFO("s32CFRLTolSubMarginBlank = %d\n", s32CFRLTolSubMarginBlank);
    HDMI_INFO("s32BlankMaxLen = %d\n", pstBaseParas->s32BlankMaxLen);
    HDMI_INFO("s32BlankGapLenStp1 = %d\n", s32BlankGapLenStp1);
    HDMI_INFO("s32BlankGapLenStp2 = %d\n", s32BlankGapLenStp2);
    HDMI_INFO("s32BlankGapLen = %d\n", pstBaseParas->s32BlankGapLen);
    HDMI_INFO("s32BlankSliceDiff = %d\n", s32BlankSliceDiff);
    HDMI_INFO("s32BlankLineDiffDelt = %d\n", pstBaseParas->s32BlankLineDiffDelt);
    HDMI_INFO("s32Blank2SliceNumMin = %d\n", s32Blank2SliceNumMin);
    HDMI_INFO("s32BlankSliceNumMin = %d\n", pstBaseParas->s32BlankSliceNumMin);
    HDMI_INFO("bShouldBeRCCompress = %s\n", pstBaseParas->bShouldBeRCCompress ? "true" : "false");
#endif
    return HI_SUCCESS;
}

static HI_S32 DFMAvParasCalc(DFM_IN_S *pstDFMIn, HI_S32 s32PreSetActive)
{
    HI_S32 s32CFRLTolSubMarginAv = 0;
    HI_S32 s32AvMaxLenC = 0;
    HI_S32 s32AvGapLenStp1 = 0;
    HI_S32 s32Temp = 0;
    HI_S32 s32AvSliceNumMin = 0;
    DFM_INFO_S *pstDFMInfo = HI_NULL;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;

    if (pstDFMIn == HI_NULL)
    {
        return HI_FAILURE;
    }

    pstDFMInfo = GetDFMInfo();
    pstBaseParas = GetDFMBaseParas();

    pstBaseParas->s32FRLCharDeltaAv = pstBaseParas->s32ClkTolerancePerLine
                                      + (LINE_START_TOLERANCE + s32PreSetActive)*10000;

    s32CFRLTolSubMarginAv = CFRL_TOLERANCE*10000 - pstBaseParas->s32FRLCharDeltaAv;

    s32Temp = DoDiv(DoDiv(s32CFRLTolSubMarginAv*pstBaseParas->s64K6MaxActualAv,
              pstBaseParas->s64K6MaxActualAv - pstBaseParas->s64K1MaxIdealTMDS),
              6*10000);

    s32AvMaxLenC = s32Temp*6;

    if (s32AvMaxLenC == 0)
    {
        return HI_FAILURE;
    }

    pstBaseParas->s32AvMaxLenP = s32AvMaxLenC*2/3;


    s32AvGapLenStp1 = (DoDiv(pstBaseParas->s64K6MaxActualAv*1000000,
                      pstBaseParas->s64K1MaxIdealTMDS) - 1000000)* s32AvMaxLenC/1000000;

    s32Temp =  DoDiv(DoDiv((((HI_S64)s32AvGapLenStp1 + s32AvMaxLenC)
               *((HI_S64)pstDFMInfo->s32CFrlSB - CFRL_SB_PAYLOAD)*CFRL_PKT_AVERAGE
               + (HI_S64)s32AvMaxLenC*pstDFMInfo->s32CFrlSB)*10000, CFRL_PKT_AVERAGE
               * (HI_S64)pstDFMInfo->s32CFrlSB) + 10000 - 1, 10000);

    pstBaseParas->s32AvGapLenStp2 = s32AvGapLenStp1 - s32Temp;

    pstBaseParas->s32AvGapLen = pstBaseParas->s32AvGapLenStp2;

    pstBaseParas->s32AvDiff = s32AvMaxLenC*10000 - DoDiv(DoDiv((s32AvMaxLenC
                              + pstBaseParas->s32AvGapLen)*10000
                              *pstBaseParas->s64K1MaxIdealTMDS,
                              pstBaseParas->s64K6MinActualAv)*pstDFMInfo->s32CFrlSB,
                              CFRL_SB_PAYLOAD); //x10000

    pstBaseParas->s32AvCDiff = DoDiv(DoDiv((HI_S64)pstDFMIn->s32Hactive
                               *pstDFMInfo->s32Bpp*10000,24*s32AvMaxLenC)
                               + 10000 - 1, 10000)*(pstBaseParas->s32AvDiff/10); //x1000


    s32AvSliceNumMin = (pstBaseParas->s32AvLineMinTriByte*10000
                       /pstBaseParas->s32AvMaxLenP + 10000 - 1)/10000;

    s32Temp = pstBaseParas->s32AvLineMinTriByte
              - (s32AvSliceNumMin - 1)
              *pstBaseParas->s32AvMaxLenP;

    pstBaseParas->s32AvLastSliceSizeMin = s32Temp;
#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaAv = %d\n", pstBaseParas->s32FRLCharDeltaAv);
    HDMI_INFO("s32CFRLTolSubMarginAv = %d\n", s32CFRLTolSubMarginAv);
    HDMI_INFO("s32AvMaxLenC = %d\n", s32AvMaxLenC);
    HDMI_INFO("s32AvMaxLenP = %d\n", pstBaseParas->s32AvMaxLenP);
    HDMI_INFO("s32AvGapLenStp1 = %d\n", s32AvGapLenStp1);
    HDMI_INFO("s32AvGapLenStp2 = %d\n", pstBaseParas->s32AvGapLenStp2);
    HDMI_INFO("s32AvGapLen = %d\n", pstBaseParas->s32AvGapLen);
    HDMI_INFO("s32AvDiff = %d\n", pstBaseParas->s32AvDiff);
    HDMI_INFO("s32AvCDiff = %d\n", pstBaseParas->s32AvCDiff);
    HDMI_INFO("s32AvSliceNumMin = %d\n", s32AvSliceNumMin);
#endif
    return HI_SUCCESS;
}

static HI_S32 DFMExtBlankParasCalc(DFM_IN_S *pstDFMIn, HI_S32 s32PreSetExtBlank)
{
    HI_S32 s32CFRLToleranceSubMargin = 0;
    HI_S32 s32TBlankActual = 0;
    HI_S32 s32RatioExtraBlank = 0;
    HI_S64 s64K8ExtraBlankActualMax = 0;
    HI_S64 s64K8ExtraBlankActualMin = 0;
    HI_S32 s32Blank1EndCfrlDiff = 0;
    HI_S32 s32AvEndCfrlDiff = 0;
    HI_S32 s32ExtraBlank1GapLenStp1 = 0;
    HI_S32 s32ExtraBlank1GapLenStp2 = 0;
    HI_S32 s32ExtraBlank2MaxLen = 0;
    HI_S32 s32ExtraBlank2GapLenStp1 = 0;
    HI_S32 s32ExtraBlank2GapLenStp2 = 0;
    HI_S32 s32Temp = 0;
    HI_S64 s64Temp = 0;
    HI_S64 s64Temp1 = 0;
    DFM_INFO_S *pstDFMInfo = HI_NULL;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;

    if (pstDFMIn == HI_NULL)
    {
        return HI_FAILURE;
    }

    pstDFMInfo = GetDFMInfo();
    pstBaseParas = GetDFMBaseParas();

    s32Temp = MAX(pstBaseParas->s32ClkTolerancePerLine,
              pstBaseParas->s32ActualBlank1AndAvEndCdiff)
              + (LINE_START_TOLERANCE*2 + s32PreSetExtBlank)*10000;

    pstBaseParas->s32FRLCharDeltaIdealExtBlank2 = s32Temp; //X10000

    s32CFRLToleranceSubMargin = CFRL_TOLERANCE*10000
                                - pstBaseParas->s32FRLCharDeltaIdealExtBlank2; //X10000

    s32TBlankActual = pstDFMInfo->s32BlankTimeRef - pstDFMInfo->s32TBorrow; // x1000000000000

    s32RatioExtraBlank = DoDiv((HI_S64)s32TBlankActual*100000,
                         pstDFMInfo->s32BlankTimeRef); // x100000

    s64K8ExtraBlankActualMax = DoDiv(pstBaseParas->s64K1MaxIdealTMDS*100000,
                               s32RatioExtraBlank);

    s64K8ExtraBlankActualMin = DoDiv(pstBaseParas->s64K1MinIdealTMDS*100000,
                               s32RatioExtraBlank);

    s32Blank1EndCfrlDiff = 100*(pstDFMIn->s32Hsync + pstDFMIn->s32Hback)
                            *pstDFMInfo->s32TBBorrow/pstDFMIn->s32Hblank;// x100

    s32AvEndCfrlDiff = s32Blank1EndCfrlDiff - 100*pstDFMInfo->s32TBBorrow;// x100



    s64Temp = DoDiv((pstDFMIn->s32Hsync + pstDFMIn->s32Hback)
              *pstDFMInfo->s32Bpp*10/24*DoDiv(1000000*(s64K8ExtraBlankActualMin
              - pstBaseParas->s64K1MaxIdealTMDS), s64K8ExtraBlankActualMin), 1000);

    s64Temp1 = DoDiv(1000000*pstBaseParas->s64K6MaxActualBlank,
                     pstBaseParas->s64K6MaxActualBlank - s64K8ExtraBlankActualMin);

    s32Temp = (HI_S32)DoDiv(DoDiv((s32CFRLToleranceSubMargin - s64Temp)
              *s64Temp1, 4), 10000000000);

    pstBaseParas->s32ExtraBlank1MaxLen = s32Temp*4;

    s32ExtraBlank1GapLenStp1 = DoDiv(pstBaseParas->s64K5MinActualBlank
                               *pstBaseParas->s32ExtraBlank1MaxLen,
                               s64K8ExtraBlankActualMax)
                               - pstBaseParas->s32ExtraBlank1MaxLen;

    s32Temp = DoDiv(DoDiv((HI_S64)(s32ExtraBlank1GapLenStp1
              + pstBaseParas->s32ExtraBlank1MaxLen)*(pstDFMInfo->s32CFrlSB
              - CFRL_SB_PAYLOAD)*10000, pstDFMInfo->s32CFrlSB)
              + DoDiv((HI_S64)pstBaseParas->s32ExtraBlank1MaxLen*10000,
              CFRL_PKT_AVERAGE) + 10000 - 1,10000);

    s32ExtraBlank1GapLenStp2 = s32ExtraBlank1GapLenStp1 - s32Temp;


    s64Temp = DoDiv(pstDFMIn->s32Hfront*pstDFMInfo->s32Bpp*10/24*DoDiv(1000000
              *(s64K8ExtraBlankActualMin - pstBaseParas->s64K1MaxIdealTMDS),
              s64K8ExtraBlankActualMin), 1000);

    s64Temp1 = DoDiv(1000000*pstBaseParas->s64K6MaxActualBlank,
                    pstBaseParas->s64K6MaxActualBlank - s64K8ExtraBlankActualMin);

    s32Temp = (HI_S32)DoDiv(DoDiv((s32CFRLToleranceSubMargin
               - 100*s32AvEndCfrlDiff - s64Temp)*s64Temp1, 4), 10000000000);

    s32ExtraBlank2MaxLen = s32Temp*4;

    s32ExtraBlank2GapLenStp1 = DoDiv(pstBaseParas->s64K5MinActualBlank
                               *s32ExtraBlank2MaxLen, s64K8ExtraBlankActualMax)
                               - s32ExtraBlank2MaxLen;

    s32Temp = DoDiv(DoDiv((HI_S64)(s32ExtraBlank2GapLenStp1 + s32ExtraBlank2MaxLen)
              *(pstDFMInfo->s32CFrlSB - CFRL_SB_PAYLOAD)*10000,
              pstDFMInfo->s32CFrlSB) + DoDiv((HI_S64)s32ExtraBlank2MaxLen*10000,
              CFRL_PKT_AVERAGE) + 10000 - 1, 10000);

    s32ExtraBlank2GapLenStp2 = s32ExtraBlank2GapLenStp1 - s32Temp;

    pstBaseParas->s32ExtraBlankMaxLen = (pstBaseParas->s32ExtraBlank1MaxLen
                                         < s32ExtraBlank2MaxLen)
                                         ? pstBaseParas->s32ExtraBlank1MaxLen
                                         : s32ExtraBlank2MaxLen;

    pstBaseParas->s32ExtraBlankGapMaxLen = (pstBaseParas->s32ExtraBlank1MaxLen
                                            < s32ExtraBlank2MaxLen)
                                            ? s32ExtraBlank1GapLenStp2
                                            : s32ExtraBlank2GapLenStp2;

    if (pstBaseParas->s32ExtraBlankMaxLen == 0
        || pstBaseParas->s32ExtraBlankGapMaxLen == 0 )
    {
        return HI_FAILURE;
    }
#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaIdealExtBlank2 = %d\n", pstBaseParas->s32FRLCharDeltaIdealExtBlank2);
    HDMI_INFO("s32CFRLToleranceSubMargin = %d\n", s32CFRLToleranceSubMargin);
    HDMI_INFO("s32TBlankActual = %d\n", s32TBlankActual);
    HDMI_INFO("s32RatioExtraBlank = %d\n", s32RatioExtraBlank);
    HDMI_INFO("s64K8ExtraBlankActualMax = %lld\n", s64K8ExtraBlankActualMax);
    HDMI_INFO("s64K8ExtraBlankActualMin = %lld\n", s64K8ExtraBlankActualMin);
    HDMI_INFO("s32AvEndCfrlDiff = %d\n", s32AvEndCfrlDiff);
    HDMI_INFO("s32Blank1EndCfrlDiff = %d\n", s32Blank1EndCfrlDiff);
    HDMI_INFO("s32ExtraBlank1MaxLen = %d\n", pstBaseParas->s32ExtraBlank1MaxLen);
    HDMI_INFO("s32ExtraBlank1GapLenStp1 = %d\n", s32ExtraBlank1GapLenStp1);
    HDMI_INFO("s32ExtraBlank1GapLenStp2 = %d\n", s32ExtraBlank1GapLenStp2);
    HDMI_INFO("s32ExtraBlank2MaxLen = %d\n", s32ExtraBlank2MaxLen);
    HDMI_INFO("s32ExtraBlank2GapLenStp1 = %d\n", s32ExtraBlank2GapLenStp1);
    HDMI_INFO("s32ExtraBlank2GapLenStp2 = %d\n", s32ExtraBlank2GapLenStp2);
    HDMI_INFO("s32ExtraBlankMaxLen = %d\n", pstBaseParas->s32ExtraBlankMaxLen);
    HDMI_INFO("s32ExtraBlankGapMaxLen = %d\n", pstBaseParas->s32ExtraBlankGapMaxLen);
#endif
    return HI_SUCCESS;

}


static HI_S32 DFMExtAvParasCalc(DFM_IN_S *pstDFMIn)
{
    HI_S32 s32Blank1NoGapAndAvMinRatio = 0;
    HI_S32 s32Blank1NoGapAndAvEndCIdeal = 0;
    HI_S32 s32Blank1NoGapAndAvEndCActual = 0;
    HI_S32 s32Blank1NoGapAndAvEndCDiff = 0;
    HI_S32 s32AvLineNoGapEndTimeRatio = 0;
    HI_S32 s32AvLineNoGapEndTBIdeal = 0;
    HI_S32 s32AvLineNoGapEndTBActual = 0;
    HI_S32 s32AvLineEndNoGapCDiffMax = 0;
    HI_S32 s32AVLineNoAddGapBlank21sliceRatio = 0;
    HI_S32 s32AVLineNoAddGapBlank22sliceRatio = 0;
    HI_S32 s32HalfOfBlank1 = 0;
    HI_S32 s32Blank1AndAvMinRatio = 0;
    HI_S32 s32Blank1AndAvEndCideal = 0;
    HI_S32 s32Blank1AndAvEndCActual = 0;
    HI_S32 s32AvLineEndTimeRatio = 0;
    HI_S32 s32AvLineEndTBIdeal = 0;
    HI_S32 s32AvLineNoAddGapMargin = 0;
    HI_S32 s32Temp = 0;
    HI_S32 s32Temp1 = 0;
    HI_BOOL bTemp = HI_FALSE;
    DFM_INFO_S *pstDFMInfo = HI_NULL;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;

    if (pstDFMIn == HI_NULL)
    {
        return HI_FAILURE;
    }

    pstDFMInfo = GetDFMInfo();
    pstBaseParas = GetDFMBaseParas();

    pstBaseParas->s32AvMaxLenPExtra = (pstDFMInfo->s32Bpp*pstDFMIn->s32Hactive
                                       + 24 - 1)/24 + 3;

    pstBaseParas->s32AvGapLenExtra = 0;

    s32Temp = DoDiv((HI_S64)(pstBaseParas->s32Blank1LenMax + 8 -1)/8
              *pstBaseParas->s32BlankLineMaxTriByte*100000,
              (HI_S64)pstDFMInfo->s32MinFrlCharsPerLine
              *(100000 - pstDFMInfo->s32OverheadMax));

    pstBaseParas->s32Blank1NoGapWillOK = pstBaseParas->s32Blank1LenMax - s32Temp;

    s32Temp = DoDiv(((HI_S64)(pstBaseParas->s32Blank1LenMax + 8 -1)/8*10
              + pstBaseParas->s32AvLineMaxTriByte*15)*1000000000,
              (HI_S64)pstDFMInfo->s32MinFrlCharsPerLine
              *(100000 - pstDFMInfo->s32OverheadMax));

    s32Blank1NoGapAndAvMinRatio = s32Temp;   //X100000

    s32Blank1NoGapAndAvEndCIdeal = s32Blank1NoGapAndAvMinRatio
                                   *pstBaseParas->s32BlankLineMaxTriByte/100000;

    s32Blank1NoGapAndAvEndCActual = pstBaseParas->s32AvLineMaxTriByte
                                    + pstBaseParas->s32Blank1LenMax;

    s32Blank1NoGapAndAvEndCDiff = s32Blank1NoGapAndAvEndCActual
                                  - s32Blank1NoGapAndAvEndCIdeal;

    s32Temp = DoDiv(((HI_S64)(pstBaseParas->s32Blank2LenMax
              + pstBaseParas->s32Blank1LenMax + 8 - 1)/8*10
              + pstBaseParas->s32AvLineMaxTriByte*15)*1000000000,
              (HI_S64)pstDFMInfo->s32MinFrlCharsPerLine
              *(100000 - pstDFMInfo->s32OverheadMax));

    s32AvLineNoGapEndTimeRatio = s32Temp; //X100000

    s32AvLineNoGapEndTBIdeal = s32AvLineNoGapEndTimeRatio
                               *pstBaseParas->s32BlankLineMaxTriByte/100000;

    s32AvLineNoGapEndTBActual = pstBaseParas->s32AvLineMaxTriByte
                                + pstBaseParas->s32Blank1LenMax
                                + pstBaseParas->s32Blank2LenMax;

    s32AvLineEndNoGapCDiffMax = s32AvLineNoGapEndTBActual - s32AvLineNoGapEndTBIdeal;

    bTemp = (pstBaseParas->s32Blank1NoGapWillOK <= CFRL_TOLERANCE
             && s32Blank1NoGapAndAvEndCDiff <= CFRL_TOLERANCE
             && s32AvLineEndNoGapCDiffMax <= CFRL_TOLERANCE)
             ? HI_TRUE : HI_FALSE;

    pstBaseParas->bExtraNoGapWillOK = bTemp;

    s32HalfOfBlank1 = (pstBaseParas->s32Blank1LenMax/2 + 4 - 1)/4*4;

    s32Temp = MIN(s32HalfOfBlank1, (pstBaseParas->s32Blank2LenMax + 8 - 1)/8*4);

    pstBaseParas->s32HalfOfMinBlank1AndBlank2 = s32Temp;

    s32Temp = pstBaseParas->s32Blank1LenMax - DoDiv((HI_S64)(s32HalfOfBlank1
              + (pstBaseParas->s32Blank1LenMax - s32HalfOfBlank1 + 8 -1)/8)
              *pstBaseParas->s32BlankLineMaxTriByte*100000,
              (HI_S64)pstDFMInfo->s32MinFrlCharsPerLine
              *(100000 - pstDFMInfo->s32OverheadMax));


    pstBaseParas->bBlank1TwoSliceNoAddGapWillOK = (s32Temp < CFRL_TOLERANCE)
                                                   ? HI_TRUE : HI_FALSE;

    s32Temp = DoDiv((pstBaseParas->s32Blank1LenMax*80
               + pstBaseParas->s32Blank2LenMax*10
               + pstBaseParas->s32AvLineMaxTriByte*15*8)*10000000000,
               (HI_S64)80*pstDFMInfo->s32MaxFrlCharsPerLine
               *(100000 - pstDFMInfo->s32OverheadMax));

    s32AVLineNoAddGapBlank21sliceRatio = s32Temp;  //X100000

    pstBaseParas->s32AvLineEndTBActual = pstBaseParas->s32AvLineMaxTriByte
                                         + pstBaseParas->s32Blank1LenMax
                                         + pstBaseParas->s32Blank2LenMax;

    s32Temp = s32AVLineNoAddGapBlank21sliceRatio
              *pstBaseParas->s32BlankLineMaxTriByte/100000
              - pstBaseParas->s32AvLineEndTBActual;

    pstBaseParas->bAVLineNoAddGapBlank21sliceWillOK = (s32Temp < CFRL_TOLERANCE)
                                                      ? HI_TRUE : HI_FALSE;

    s32Temp = DoDiv((pstBaseParas->s32Blank1LenMax*80
               + pstBaseParas->s32HalfOfMinBlank1AndBlank2*80
               + (pstBaseParas->s32Blank2LenMax
               - pstBaseParas->s32HalfOfMinBlank1AndBlank2)*10
               + pstBaseParas->s32AvLineMaxTriByte*15*8)*10000000000,
               (HI_S64)80*pstDFMInfo->s32MaxFrlCharsPerLine
               *(100000 - pstDFMInfo->s32OverheadMax));

    s32AVLineNoAddGapBlank22sliceRatio = s32Temp; //X100000

    s32Temp = s32AVLineNoAddGapBlank22sliceRatio
              *pstBaseParas->s32BlankLineMaxTriByte/100000
              - pstBaseParas->s32AvLineEndTBActual;

    pstBaseParas->bAVLineNoGapBlank22sliceWillOK = (s32Temp < CFRL_TOLERANCE)
                                                    ? HI_TRUE : HI_FALSE;

    s32Temp = DoDiv((HI_S64)pstDFMInfo->s32TBBorrow*pstBaseParas->s32Blank1LenMax
              *pstDFMInfo->s32MinFrlCharsPerLine*24,
              (HI_S64)(pstBaseParas->s32Blank2LenMax + pstBaseParas->s32Blank1LenMax)
              *pstDFMInfo->s32Htotal*pstDFMInfo->s32Bpp);

    pstBaseParas->s32HBlank1TakeByAvFRL = s32Temp;

    s32Blank1AndAvMinRatio = DoDiv((pstBaseParas->s32Blank1LenMax*10
                             + pstBaseParas->s32AvLineMaxTriByte*15)*10000000000,
                             (HI_S64)10*pstDFMInfo->s32MaxFrlCharsPerLine
                             *(100000 - pstDFMInfo->s32OverheadMax)); //x100000

    s32Blank1AndAvEndCideal = s32Blank1AndAvMinRatio
                              *pstBaseParas->s32BlankLineMaxTriByte/100000;

    s32Blank1AndAvEndCActual = pstBaseParas->s32AvLineMaxTriByte
                               + pstBaseParas->s32Blank1LenMax;

    pstBaseParas->s32Blank1AndAvEndCDiff = s32Blank1AndAvEndCActual
                                           - s32Blank1AndAvEndCideal;

    s32Temp = (pstDFMInfo->bIsExtraMode && pstBaseParas->s32ExtraBlankGapMaxLen >= 0)
               ? pstBaseParas->s32ExtraBlankMaxLen
               : MAX(pstBaseParas->s32Blank1LenMax, pstBaseParas->s32Blank2LenMax);

    pstBaseParas->s32ExtraBlankMaxLenFinal = s32Temp;

    if (pstBaseParas->s32ExtraBlankMaxLenFinal == 0)
    {
        return HI_FAILURE;
    }

    pstBaseParas->s32ExtBlank2SliceNumMin = (pstBaseParas->s32Blank2LenMin*10000
                                            /pstBaseParas->s32ExtraBlankMaxLenFinal
                                            + 10000 - 1)/10000;

    s32Temp = pstBaseParas->s32Blank2LenMin
              - (pstBaseParas->s32ExtBlank2SliceNumMin - 1)
              *pstBaseParas->s32ExtraBlankMaxLenFinal;

    pstBaseParas->s32ExtBlank2LastSliceSizeMin = s32Temp;

    s32AvLineEndTimeRatio = DoDiv((pstBaseParas->s32Blank2LenMax*80
                             + pstBaseParas->s32Blank1LenMax*80
                             - pstBaseParas->s32ExtBlank2LastSliceSizeMin*7*10
                             + pstBaseParas->s32AvLineMaxTriByte*15*8)*10000000000,
                             (HI_S64)80*pstDFMInfo->s32MaxFrlCharsPerLine
                             *(100000 - pstDFMInfo->s32OverheadMax)); // x100000

    s32AvLineEndTBIdeal = s32AvLineEndTimeRatio
                          *pstBaseParas->s32BlankLineMaxTriByte/100000;

    pstBaseParas->s32AvLineEndCDiffMax = pstBaseParas->s32AvLineEndTBActual
                                         - s32AvLineEndTBIdeal;

    s32Temp = DoDiv((HI_S64)pstDFMInfo->s32MinFrlCharsPerLine
              *pstDFMIn->s32Hblank*pstBaseParas->s32Blank1LenMax,
              (HI_S64)pstDFMInfo->s32Htotal*(pstBaseParas->s32Blank2LenMax
              + pstBaseParas->s32Blank1LenMax));

    pstBaseParas->s32HBlank1ActualFRLAbility = s32Temp;

    s32AvLineNoAddGapMargin = DoDiv((HI_S64)pstDFMInfo->s32MinFrlCharsPerLine
                              *(100000 - pstDFMInfo->s32OverheadMax)
                              - (HI_S64)((HI_S64)pstBaseParas->s32AvLineMaxTriByte*15
                              + (HI_S64)pstBaseParas->s32Blank1LenMax*10
                              + (HI_S64)pstBaseParas->s32Blank2LenMax*10)*10000, 100000);


    s32Temp = DoDiv((HI_S64)(pstBaseParas->s32Blank2LenMax*80
               + (HI_S64)pstBaseParas->s32Blank1LenMax*80
               - (HI_S64)pstBaseParas->s32ExtraBlank1MaxLen*7*10
               + (HI_S64)pstBaseParas->s32AvLineMaxTriByte*15*8)
               * (HI_S64)pstBaseParas->s32BlankLineMaxTriByte*100000,
               (HI_S64)80*pstDFMInfo->s32MaxFrlCharsPerLine
               *(100000 - pstDFMInfo->s32OverheadMax));

    s32Temp1 = pstBaseParas->s32AvLineMaxTriByte
               + pstBaseParas->s32Blank1LenMax
               + pstBaseParas->s32Blank2LenMax
               - pstBaseParas->s32ExtBlank2LastSliceSizeMin
               - s32Temp;

    pstBaseParas->s32AvLineNoAddGapBlank2DFMMax = s32Temp1;

    bTemp = ((pstBaseParas->s32Blank1AndAvEndCDiff <= CFRL_TOLERANCE)
             && (pstBaseParas->s32AvLineEndCDiffMax <= CFRL_TOLERANCE)
             && (pstBaseParas->s32AvLineNoAddGapBlank2DFMMax
             < (s32AvLineNoAddGapMargin + CFRL_TOLERANCE)))
             ? HI_TRUE : HI_FALSE;

    pstBaseParas->bBlank1AndAvEndCDiff = bTemp;


    pstBaseParas->s32AvGapLenExtraFinal = (pstDFMInfo->bIsExtraMode
                                           && pstBaseParas->s32ExtraBlankGapMaxLen >= 0)
                                           ? pstBaseParas->s32ExtraBlankGapMaxLen : 0;

    pstBaseParas->s32ExtBlank1SliceNumMin = (pstBaseParas->s32Blank1LenMin*10000
                                            /pstBaseParas->s32ExtraBlankMaxLenFinal
                                            + 10000 - 1)/10000;
#ifdef DEBUG
    HDMI_INFO("s32AvMaxLenPExtra = %d\n", pstBaseParas->s32AvMaxLenPExtra);
    HDMI_INFO("s32AvGapLenExtra = %d\n", pstBaseParas->s32AvGapLenExtra);
    HDMI_INFO("s32Blank1NoGapWillOK = %d\n", pstBaseParas->s32Blank1NoGapWillOK);
    HDMI_INFO("s32Blank1NoGapAndAvMinRatio = %d\n", s32Blank1NoGapAndAvMinRatio);
    HDMI_INFO("s32Blank1NoGapAndAvEndCIdeal = %d\n", s32Blank1NoGapAndAvEndCIdeal);
    HDMI_INFO("s32Blank1NoGapAndAvEndCActual = %d\n", s32Blank1NoGapAndAvEndCActual);
    HDMI_INFO("s32Blank1NoGapAndAvEndCDiff = %d\n", s32Blank1NoGapAndAvEndCDiff);
    HDMI_INFO("s32AvLineNoGapEndTimeRatio = %d\n", s32AvLineNoGapEndTimeRatio);
    HDMI_INFO("s32AvLineNoGapEndTBIdeal = %d\n", s32AvLineNoGapEndTBIdeal);
    HDMI_INFO("s32AvLineNoGapEndTBActual = %d\n", s32AvLineNoGapEndTBActual);
    HDMI_INFO("s32AvLineEndNoGapCDiffMax = %d\n", s32AvLineEndNoGapCDiffMax);
    HDMI_INFO("bExtraNoGapWillOK = %s\n", pstBaseParas->bExtraNoGapWillOK ? "true" : "false");
    HDMI_INFO("s32HalfOfBlank1 = %d\n", s32HalfOfBlank1);
    HDMI_INFO("s32HalfOfMinBlank1AndBlank2 = %d\n", pstBaseParas->s32HalfOfMinBlank1AndBlank2);
    HDMI_INFO("bBlank1TwoSliceNoAddGapWillOK = %s\n", pstBaseParas->bBlank1TwoSliceNoAddGapWillOK ? "true" : "false");
    HDMI_INFO("s32AVLineNoAddGapBlank21sliceRatio = %d\n", s32AVLineNoAddGapBlank21sliceRatio);
    HDMI_INFO("s32AvLineEndTBActual = %d\n", pstBaseParas->s32AvLineEndTBActual);
    HDMI_INFO("bAVLineNoAddGapBlank21sliceWillOK = %s\n", pstBaseParas->bAVLineNoAddGapBlank21sliceWillOK ? "true" : "false");
    HDMI_INFO("s32AVLineNoAddGapBlank22sliceRatio = %d\n", s32AVLineNoAddGapBlank22sliceRatio);
    HDMI_INFO("bAVLineNoGapBlank22sliceWillOK = %s\n", pstBaseParas->bAVLineNoGapBlank22sliceWillOK ? "true" : "false");
    HDMI_INFO("s32HBlank1TakeByAvFRL = %d\n", pstBaseParas->s32HBlank1TakeByAvFRL);
    HDMI_INFO("s32Blank1AndAvMinRatio = %d\n", s32Blank1AndAvMinRatio);
    HDMI_INFO("s32Blank1AndAvEndCideal = %d\n", s32Blank1AndAvEndCideal);
    HDMI_INFO("s32Blank1AndAvEndCActual = %d\n", s32Blank1AndAvEndCActual);
    HDMI_INFO("s32Blank1AndAvEndCDiff = %d\n", pstBaseParas->s32Blank1AndAvEndCDiff);
    HDMI_INFO("s32ExtraBlankMaxLenFinal = %d\n", pstBaseParas->s32ExtraBlankMaxLenFinal);
    HDMI_INFO("s32ExtBlank2SliceNumMin = %d\n", pstBaseParas->s32ExtBlank2SliceNumMin);
    HDMI_INFO("s32ExtBlank2LastSliceSizeMin = %d\n", pstBaseParas->s32ExtBlank2LastSliceSizeMin);
    HDMI_INFO("s32AvLineEndTimeRatio = %d\n", s32AvLineEndTimeRatio);
    HDMI_INFO("s32AvLineEndTBIdeal = %d\n", s32AvLineEndTBIdeal);
    HDMI_INFO("s32AvLineEndCDiffMax = %d\n", pstBaseParas->s32AvLineEndCDiffMax);
    HDMI_INFO("s32HBlank1ActualFRLAbility = %d\n", pstBaseParas->s32HBlank1ActualFRLAbility);
    HDMI_INFO("s32AvLineNoAddGapMargin = %d\n", s32AvLineNoAddGapMargin);
    HDMI_INFO("s32AvLineNoAddGapBlank2DFMMax = %d\n", pstBaseParas->s32AvLineNoAddGapBlank2DFMMax);
    HDMI_INFO("bBlank1AndAvEndCDiff = %s\n", pstBaseParas->bBlank1AndAvEndCDiff ? "true" : "false");
    HDMI_INFO("s32AvGapLenExtraFinal = %d\n", pstBaseParas->s32AvGapLenExtraFinal);
#endif
    return HI_SUCCESS;
}

static HI_VOID DFMAvLineCanbeSendCalc(HI_VOID)
{
    HI_BOOL bTemp = HI_FALSE;
    HI_S32 s32CharDeltaAvEnd = 0;
    HI_S32 s32CharDeltaLineEnd = 0;
    HI_S32 s32Temp = 0;
    HI_S32 s32Temp1 = 0;
    HI_BOOL bAvEndNoGapWithBlank2DFMOk = HI_FALSE;
    HI_BOOL bAvEndNoGapWithBlank2GAPOk = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    pstBaseParas->s32GapDeltaIAvLine = (LINE_START_TOLERANCE*2
                                       + FIX_ERR3*((pstDFMInfo->bIsExtraMode)
                                       ? pstBaseParas->s32ExtBlank1SliceNumMin
                                       : pstBaseParas->s32BlankSliceNumMin))*100; // x100

    s32Temp = DoDiv(((HI_S64)pstBaseParas->s32ExtBlank2LastSliceSizeMin
              *pstBaseParas->s32AvGapLenExtraFinal*100*8
              + (HI_S64)MAX(pstBaseParas->s32ExtBlank2LastSliceSizeMin
              - pstDFMInfo->s32BlankAudioMin, 0)*7*100
              *pstBaseParas->s32ExtraBlankMaxLenFinal),
              (8 * (HI_S64)pstBaseParas->s32ExtraBlankMaxLenFinal));

    s32Temp1 = DoDiv(((HI_S64)pstBaseParas->s32Blank2LastSliceSizeMin
               *pstBaseParas->s32BlankGapLen*100*8
               + (HI_S64)MAX(pstBaseParas->s32Blank2LastSliceSizeMin
               - pstDFMInfo->s32BlankAudioMin, 0)*7*100
               *pstBaseParas->s32BlankMaxLen),
               (8 * (HI_S64)pstBaseParas->s32BlankMaxLen));

    pstBaseParas->s32GapLineLastSlice = (pstDFMInfo->bIsExtraMode)
                                        ? s32Temp : s32Temp1;  //x100

    s32Temp = MAX(pstBaseParas->s32ClkTolerancePerLine,
              pstBaseParas->s32ActualBlank1AndAvEndCdiff)
              + DoDiv(pstBaseParas->s32AvLastSliceSizeMin
              *(pstBaseParas->s64K6MaxActualAv
              - pstBaseParas->s64K1MinIdealTMDS)*10000,
              pstBaseParas->s64K6MaxActualAv);

    s32CharDeltaAvEnd = (pstDFMInfo->bIsExtraMode)
                        ? pstBaseParas->s32ClkTolerancePerLine : s32Temp; //x10000

    s32CharDeltaLineEnd = pstBaseParas->s32Blank2LenMin
                          *(pstBaseParas->s64K6MaxActualBlank
                          - pstBaseParas->s64K1MinIdealTMDS)
                          /pstBaseParas->s64K6MaxActualBlank
                          + s32CharDeltaAvEnd/10000;

    bAvEndNoGapWithBlank2DFMOk = (s32CharDeltaLineEnd < CFRL_TOLERANCE)
                                  ? HI_TRUE : HI_FALSE;

    s32Temp = (pstDFMInfo->bIsExtraMode) ? (100*pstBaseParas->s32ExtBlank2LastSliceSizeMin
              *pstBaseParas->s32AvGapLenExtraFinal/pstBaseParas->s32ExtraBlankMaxLenFinal)
              : DoDiv((HI_S64)100*pstBaseParas->s32Blank2LastSliceSizeMin*pstBaseParas->s32BlankGapLen
              *pstBaseParas->s32AvMaxLenP + (HI_S64)100*pstBaseParas->s32AvLastSliceSizeMin
              *pstBaseParas->s32AvGapLen*pstBaseParas->s32BlankMaxLen,
              (HI_S64)pstBaseParas->s32AvMaxLenP*pstBaseParas->s32BlankMaxLen); //x100


    bAvEndNoGapWithBlank2GAPOk = (s32Temp > pstBaseParas->s32GapDeltaIAvLine)
                                  ? HI_TRUE : HI_FALSE;

    bTemp = ((!pstBaseParas->bShouldBeRCCompress)
              &&(pstBaseParas->s32GapLineLastSlice
              > pstBaseParas->s32GapDeltaIAvLine))
              ? HI_TRUE : HI_FALSE;

    pstBaseParas->bAvLineNoRCCanBeSend = bTemp;

    bTemp = (pstBaseParas->bShouldBeRCCompress)
             ? HI_FALSE : pstBaseParas->bBlank1AndAvEndCDiff;

    pstBaseParas->bAvLineNoRCNoGapAddCanBeSend = bTemp;

    bTemp = (pstBaseParas->bShouldBeRCCompress)
             ? pstBaseParas->bExtraNoGapWillOK : HI_FALSE;

    pstBaseParas->bAvLineShouldRCNoGapCanBeSend = bTemp;

    bTemp = (bAvEndNoGapWithBlank2DFMOk && bAvEndNoGapWithBlank2GAPOk)
             ? HI_TRUE : HI_FALSE;

    pstBaseParas->bAvEndNoGapCanBeSend = bTemp;

    bTemp = (pstBaseParas->s32Blank1NoGapWillOK < CFRL_TOLERANCE
            && pstDFMInfo->bIsExtraMode
            && pstBaseParas->s32Blank1AndAvEndCDiff <= CFRL_TOLERANCE
            && pstBaseParas->s32AvLineEndCDiffMax <= CFRL_TOLERANCE
            && pstBaseParas->bAVLineNoAddGapBlank21sliceWillOK)
            ? HI_TRUE : HI_FALSE;

    pstBaseParas->bNoGapAddBlank22SliceCanOK = bTemp;

    bTemp = (pstBaseParas->s32Blank1NoGapWillOK > CFRL_TOLERANCE
            && pstDFMInfo->bIsExtraMode
            && pstBaseParas->bBlank1AndAvEndCDiff
            && pstBaseParas->bBlank1TwoSliceNoAddGapWillOK)
            ? HI_TRUE : HI_FALSE;

    pstBaseParas->bNoGapAddBlank12SliceCanOK = bTemp;
#ifdef DEBUG
    HDMI_INFO("s32CharDeltaAvEnd = %d\n", s32CharDeltaAvEnd);
    HDMI_INFO("s32CharDeltaLineEnd = %d\n", s32CharDeltaLineEnd);
    HDMI_INFO("bAvEndNoGapWithBlank2DFMOk = %s\n", bAvEndNoGapWithBlank2DFMOk ? "true" : "false");
    HDMI_INFO("bAvEndNoGapWithBlank2GAPOk = %s\n", bAvEndNoGapWithBlank2GAPOk ? "true" : "false");
    HDMI_INFO("bAvLineNoRCCanBeSend = %s\n", pstBaseParas->bAvLineNoRCCanBeSend ? "true" : "false");
    HDMI_INFO("bAvLineNoRCNoGapAddCanBeSend = %s\n", pstBaseParas->bAvLineNoRCNoGapAddCanBeSend ? "true" : "false");
    HDMI_INFO("bAvLineShouldRCNoGapCanBeSend = %s\n", pstBaseParas->bAvLineShouldRCNoGapCanBeSend ? "true" : "false");
    HDMI_INFO("bAvEndNoGapCanBeSend = %s\n", pstBaseParas->bAvEndNoGapCanBeSend ? "true" : "false");
    HDMI_INFO("bNoGapAddBlank22SliceCanOK = %s\n", pstBaseParas->bNoGapAddBlank22SliceCanOK ? "true" : "false");
    HDMI_INFO("bNoGapAddBlank12SliceCanOK = %s\n", pstBaseParas->bNoGapAddBlank12SliceCanOK ? "true" : "false");
#endif
    return;
}

//ERR1
static HI_BOOL DFMBlank1LastSliceSizeIsOk(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32Blank1SliceNumMin = 0;
    HI_S32 s32Blank1LastSliceSizeMin = 0;
    HI_S32 s32Blank1SliceNumMax = 0;
    HI_S32 s32Blank1LastSliceSizeMax = 0;
    HI_BOOL bTemp = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32Blank1SliceNumMin = (pstBaseParas->s32Blank1LenMin*10000
                            /pstBaseParas->s32BlankMaxLen + 10000 - 1)/10000;

    s32Blank1LastSliceSizeMin = pstBaseParas->s32Blank1LenMin
                                - (s32Blank1SliceNumMin - 1)
                                *pstBaseParas->s32BlankMaxLen;

    s32Blank1SliceNumMax = (pstBaseParas->s32Blank1LenMax*10000
                            /pstBaseParas->s32BlankMaxLen + 10000 - 1)/10000;

    s32Blank1LastSliceSizeMax = pstBaseParas->s32Blank1LenMin
                                 - (s32Blank1SliceNumMax - 1)
                                 *pstBaseParas->s32BlankMaxLen;

    bTemp = (s32Blank1LastSliceSizeMin > 8 && s32Blank1LastSliceSizeMax > 8
            && s32Blank1LastSliceSizeMin <= pstBaseParas->s32BlankMaxLen
            && s32Blank1LastSliceSizeMax <= pstBaseParas->s32BlankMaxLen)
            ? HI_TRUE : HI_FALSE;

    bRet = (pstDFMInfo->bIsExtraMode) ? HI_TRUE : bTemp;
#ifdef DEBUG
    HDMI_INFO("s32Blank1SliceNumMin = %d\n", s32Blank1SliceNumMin);
    HDMI_INFO("s32Blank1LastSliceSizeMin = %d\n", s32Blank1LastSliceSizeMin);
    HDMI_INFO("s32Blank1SliceNumMax = %d\n", s32Blank1SliceNumMax);
    HDMI_INFO("s32Blank1LastSliceSizeMax = %d\n", s32Blank1LastSliceSizeMax);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMBlank2LastSliceSizeIsOk(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32Blank2LastSliceSizeMin = 0;
    HI_S32 s32Blank2SliceNumMax = 0;
    HI_S32 s32Blank2LastSliceSizeMax = 0;
    HI_BOOL bTemp = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32Blank2LastSliceSizeMin = pstBaseParas->s32Blank2LastSliceSizeMin;

    s32Blank2SliceNumMax = (pstBaseParas->s32Blank2LenMax*10000
                            /pstBaseParas->s32BlankMaxLen + 10000 - 1)/10000;

    s32Blank2LastSliceSizeMax = pstBaseParas->s32Blank2LenMax
                                - (s32Blank2SliceNumMax - 1)
                                *pstBaseParas->s32BlankMaxLen;

    bTemp = (s32Blank2LastSliceSizeMin > 8 && s32Blank2LastSliceSizeMax > 8
            && s32Blank2LastSliceSizeMin <= pstBaseParas->s32BlankMaxLen
            && s32Blank2LastSliceSizeMax <= pstBaseParas->s32BlankMaxLen)
            ? HI_TRUE : HI_FALSE;

    bRet = (pstBaseParas->s32Blank2LenMin <= 8)
           ? HI_TRUE : ((pstDFMInfo->bIsExtraMode) ? HI_TRUE : bTemp);
#ifdef DEBUG
    HDMI_INFO("s32Blank2LastSliceSizeMin = %d\n", s32Blank2LastSliceSizeMin);
    HDMI_INFO("s32Blank2SliceNumMax = %d\n", s32Blank2SliceNumMax);
    HDMI_INFO("s32Blank2LastSliceSizeMax = %d\n", s32Blank2LastSliceSizeMax);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMBlankSliceLenIsOk(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32BlankLastSliceSizeMin = 0;
    HI_S32 s32BlankSliceNumMax = 0;
    HI_S32 s32BlankLastSliceSizeMax = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32BlankLastSliceSizeMin = pstBaseParas->s32BlankLastSliceSizeMin;

    s32BlankSliceNumMax = (pstBaseParas->s32BlankLineMaxTriByte*10000
                           /pstBaseParas->s32BlankMaxLen + 10000 - 1)/10000;

    s32BlankLastSliceSizeMax = pstBaseParas->s32BlankLineMaxTriByte
                               - (s32BlankSliceNumMax - 1)
                               *pstBaseParas->s32BlankMaxLen;

    bRet = (s32BlankLastSliceSizeMin > 8 && s32BlankLastSliceSizeMax > 8
           && s32BlankLastSliceSizeMin <= pstBaseParas->s32BlankMaxLen
           && s32BlankLastSliceSizeMax <= pstBaseParas->s32BlankMaxLen)
           ? HI_TRUE : HI_FALSE;
#ifdef DEBUG
    HDMI_INFO("s32BlankLastSliceSizeMin = %d\n", s32BlankLastSliceSizeMin);
    HDMI_INFO("s32BlankSliceNumMax = %d\n", s32BlankSliceNumMax);
    HDMI_INFO("s32BlankLastSliceSizeMax = %d\n", s32BlankLastSliceSizeMax);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMAvLineBlankCdiffIsOk(HI_S32 s32PreSetBlank)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32FRLCharDeltaIdealBlank2 = 0;
    HI_S32 s32FRLCharDeltaActualBlank2 = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32FRLCharDeltaIdealBlank2 = MAX(pstBaseParas->s32ClkTolerancePerLine,
                                 pstBaseParas->s32ActualBlank1AndAvEndCdiff)
                                 + (LINE_START_TOLERANCE*2 + s32PreSetBlank)*10000;//x10000

    s32FRLCharDeltaActualBlank2 = MAX(pstBaseParas->s32ClkTolerancePerLine,
                                  pstBaseParas->s32ActualBlank1AndAvEndCdiff)
                                  + LINE_START_TOLERANCE*2*10000;//x10000

    bRet = (pstDFMInfo->bIsExtraMode) ? HI_TRUE
            : ((s32FRLCharDeltaIdealBlank2 >= s32FRLCharDeltaActualBlank2)
            ? HI_TRUE : HI_FALSE);
#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaIdealBlank2 = %d\n", s32FRLCharDeltaIdealBlank2);
    HDMI_INFO("s32FRLCharDeltaActualBlank2 = %d\n", s32FRLCharDeltaActualBlank2);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMBlankLineDFMIsOk(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32FRLCharDeltaActualBlank = 0;
    HI_S32 s32Temp = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32Temp = (pstDFMInfo->bIsExtraMode)
               ? pstBaseParas->s32ClkTolerancePerLine
               : MAX(pstBaseParas->s32ClkTolerancePerLine,
               pstBaseParas->s32ActualBlank1AndAvEndCdiff);

    s32FRLCharDeltaActualBlank = s32Temp + LINE_START_TOLERANCE*10000
                                 + pstBaseParas->s32BlankLineDiffDelt*10;

    bRet = (pstBaseParas->s32FRLCharDeltaIdealBlank >= s32FRLCharDeltaActualBlank)
           ? HI_TRUE : HI_FALSE;
#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaActualBlank = %d\n", s32FRLCharDeltaActualBlank);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMBlankLineCanBeSend(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32FRLCharDeltaGapMax = 0;
    HI_S32 s32BlankLineLastSliceGap = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32FRLCharDeltaGapMax = LINE_START_TOLERANCE
                            + FIX_ERR3*pstBaseParas->s32BlankSliceNumMin
                            + FSM_TOLERANCE;

    s32BlankLineLastSliceGap = pstBaseParas->s32BlankLastSliceSizeMin
                               *pstBaseParas->s32BlankGapLen
                               /pstBaseParas->s32BlankMaxLen;

    bRet = (s32BlankLineLastSliceGap >= s32FRLCharDeltaGapMax) ? HI_TRUE : HI_FALSE;
#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaGapMax = %d\n", s32FRLCharDeltaGapMax);
    HDMI_INFO("s32BlankLineLastSliceGap = %d\n", s32BlankLineLastSliceGap);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMBlankGapLenExtend(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;

    pstBaseParas = GetDFMBaseParas();

    bRet = (pstBaseParas->s32BlankGapLen < 65500) ? HI_TRUE : HI_FALSE;

#ifdef DEBUG
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMAvLineBlankCanBeSend(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_BOOL bTemp = HI_FALSE;
    HI_S32 s32GapLineLastSlice = 0;
    HI_S32 s32GapDeltaIAvLine = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32GapLineLastSlice = DoDiv(((HI_S64)pstBaseParas->s32Blank2LastSliceSizeMin
                          *pstBaseParas->s32BlankGapLen*8
                          + (HI_S64)MAX(pstBaseParas->s32Blank2LastSliceSizeMin
                          - pstDFMInfo->s32BlankAudioMin, 0)*7
                          *pstBaseParas->s32BlankMaxLen)*100,
                          (8*(HI_S64)pstBaseParas->s32BlankMaxLen)); //x100

    s32GapDeltaIAvLine = (LINE_START_TOLERANCE*2
                         + FIX_ERR3*pstBaseParas->s32BlankSliceNumMin)*100;

    bTemp = (s32GapLineLastSlice > s32GapDeltaIAvLine)
             ? HI_TRUE : HI_FALSE;

    bRet = (pstDFMInfo->bIsExtraMode) ? HI_TRUE : bTemp;

#ifdef DEBUG
    HDMI_INFO("s32GapLineLastSlice = %d\n", s32GapLineLastSlice);
    HDMI_INFO("s32GapDeltaIAvLine = %d\n", s32GapDeltaIAvLine);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

//ERR2
static HI_BOOL DFMAvLineAvDFMIsOk(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32FRLCharDeltaAv = 0;
    HI_S32 s32FRLCharDeltaActualAv = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;

    pstBaseParas = GetDFMBaseParas();

    s32FRLCharDeltaAv = pstBaseParas->s32FRLCharDeltaAv; //x10000

    s32FRLCharDeltaActualAv = pstBaseParas->s32ClkTolerancePerLine
                              + LINE_START_TOLERANCE*10000
                              + pstBaseParas->s32AvCDiff*10; //x10000

    bRet = (s32FRLCharDeltaAv > s32FRLCharDeltaActualAv) ? HI_TRUE : HI_FALSE;

#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaAv = %d\n", s32FRLCharDeltaAv);
    HDMI_INFO("s32FRLCharDeltaActualAv = %d\n", s32FRLCharDeltaActualAv);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMAvSliceLenIsOK(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32AvLastSliceSizeMin = 0;
    HI_S32 s32AvSliceNumMax = 0;
    HI_S32 s32AvLastSliceSizeMax = 0;
    HI_BOOL bTemp = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32AvLastSliceSizeMin = pstBaseParas->s32AvLastSliceSizeMin;

    s32AvSliceNumMax = (pstBaseParas->s32AvLineMaxTriByte*10000
                        /pstBaseParas->s32AvMaxLenP + 10000 - 1)/10000;

    s32AvLastSliceSizeMax = pstBaseParas->s32AvLineMaxTriByte
                            - (s32AvSliceNumMax - 1)*pstBaseParas->s32AvMaxLenP;

    bTemp = (s32AvLastSliceSizeMin > 8 && s32AvLastSliceSizeMax > 8
            && s32AvLastSliceSizeMin <= pstBaseParas->s32AvMaxLenP
            && s32AvLastSliceSizeMax <= pstBaseParas->s32AvMaxLenP)
            ? HI_TRUE : HI_FALSE;


    bRet = (pstDFMInfo->bIsExtraMode) ? HI_TRUE : bTemp;
#ifdef DEBUG
    HDMI_INFO("s32AvLastSliceSizeMin = %d\n", s32AvLastSliceSizeMin);
    HDMI_INFO("s32AvSliceNumMax = %d\n", s32AvSliceNumMax);
    HDMI_INFO("s32AvLastSliceSizeMax = %d\n", s32AvLastSliceSizeMax);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMAvGapLenExtend(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;

    pstBaseParas = GetDFMBaseParas();

    bRet = (pstBaseParas->s32AvGapLenStp2 < 65500) ? HI_TRUE : HI_FALSE;
#ifdef DEBUG
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

//ERR3
static HI_BOOL DFMExtBlank1LastSliceSizeIsOK(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_BOOL bTemp = HI_FALSE;
    HI_S32 s32ExtBlank1LastSliceSizeMin = 0;
    HI_S32 s32ExtBlank1SliceNumMax = 0;
    HI_S32 s32ExtBlank1SliceSizeMax = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32ExtBlank1LastSliceSizeMin = pstBaseParas->s32Blank1LenMin
                                   - (pstBaseParas->s32ExtBlank1SliceNumMin - 1)
                                   *pstBaseParas->s32ExtraBlankMaxLenFinal;

    s32ExtBlank1SliceNumMax = (pstBaseParas->s32Blank1LenMax*10000
                               /pstBaseParas->s32ExtraBlankMaxLenFinal
                               + 10000 - 1)/10000;

    s32ExtBlank1SliceSizeMax = pstBaseParas->s32Blank1LenMax
                               - (s32ExtBlank1SliceNumMax - 1)
                               *pstBaseParas->s32ExtraBlankMaxLenFinal;

    bTemp = (s32ExtBlank1LastSliceSizeMin > 8 && s32ExtBlank1SliceSizeMax > 8
            && s32ExtBlank1LastSliceSizeMin <= pstBaseParas->s32ExtraBlankMaxLenFinal
            && s32ExtBlank1SliceSizeMax <= pstBaseParas->s32ExtraBlankMaxLenFinal)
            ? HI_TRUE : HI_FALSE;

    bRet = (pstDFMInfo->bIsExtraMode) ?  bTemp : HI_TRUE;

#ifdef DEBUG
    HDMI_INFO("s32ExtBlank1SliceNumMin = %d\n", pstBaseParas->s32ExtBlank1SliceNumMin);
    HDMI_INFO("s32ExtBlank1LastSliceSizeMin = %d\n", s32ExtBlank1LastSliceSizeMin);
    HDMI_INFO("s32ExtBlank1SliceNumMax = %d\n", s32ExtBlank1SliceNumMax);
    HDMI_INFO("s32ExtBlank1SliceSizeMax = %d\n", s32ExtBlank1SliceSizeMax);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMExtBlank2LastSliceSizeIsOK(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_BOOL bTemp = HI_FALSE;
    HI_BOOL bTemp1 = HI_FALSE;
    HI_S32 s32ExtBlank2SliceNumMax = 0;
    HI_S32 s32ExtBlank2SliceSizeMax= 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32ExtBlank2SliceNumMax = (pstBaseParas->s32Blank2LenMax*10000
                               /pstBaseParas->s32ExtraBlankMaxLenFinal
                               + 10000 - 1)/10000;

    pstBaseParas->s32ExtBlank2SliceNumMax = s32ExtBlank2SliceNumMax;

    s32ExtBlank2SliceSizeMax = pstBaseParas->s32Blank2LenMax
                               - (s32ExtBlank2SliceNumMax - 1)
                               *pstBaseParas->s32ExtraBlankMaxLenFinal;

    pstBaseParas->s32ExtBlank2SliceSizeMax = s32ExtBlank2SliceSizeMax;

    bTemp1 = (pstBaseParas->s32ExtBlank2LastSliceSizeMin > 8
              && s32ExtBlank2SliceSizeMax > 8
              && pstBaseParas->s32ExtBlank2LastSliceSizeMin
              <= pstBaseParas->s32ExtraBlankMaxLenFinal
              && s32ExtBlank2SliceSizeMax
              <= pstBaseParas->s32ExtraBlankMaxLenFinal)
              ? HI_TRUE : HI_FALSE;

    bTemp = (pstDFMInfo->bIsExtraMode) ? bTemp1 : HI_TRUE;

    bRet = (pstBaseParas->s32Blank2LenMin <= 8)? HI_TRUE : bTemp;
#ifdef DEBUG
    HDMI_INFO("s32ExtBlank2SliceNumMax = %d\n", s32ExtBlank2SliceNumMax);
    HDMI_INFO("s32ExtBlank2SliceNumMax = %d\n", pstBaseParas->s32ExtBlank2SliceNumMax);
    HDMI_INFO("s32ExtBlank2SliceSizeMax = %d\n", s32ExtBlank2SliceSizeMax);
    HDMI_INFO("s32ExtBlank2SliceSizeMax = %d\n", pstBaseParas->s32ExtBlank2SliceSizeMax);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMExtraAvLineBlankCdiffIsOk(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_BOOL bTemp = HI_FALSE;
    HI_S32 s32FRLCharDeltaActualExtBlank2 = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32FRLCharDeltaActualExtBlank2 = MAX(pstBaseParas->s32ClkTolerancePerLine,
                                     pstBaseParas->s32ActualBlank1AndAvEndCdiff)
                                     + LINE_START_TOLERANCE*2*10000; //x10000

    bTemp = (pstBaseParas->s32FRLCharDeltaIdealExtBlank2 >= s32FRLCharDeltaActualExtBlank2)
             ? HI_TRUE : HI_FALSE;

    bRet = (pstDFMInfo->bIsExtraMode) ? bTemp : HI_TRUE;
#ifdef DEBUG
    HDMI_INFO("s32FRLCharDeltaActualExtBlank2 = %d\n", s32FRLCharDeltaActualExtBlank2);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMExtraAvLineBlankCanBeSend(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_BOOL bTemp = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    bTemp = (pstBaseParas->s32GapLineLastSlice > pstBaseParas->s32GapDeltaIAvLine)
            ? HI_TRUE : HI_FALSE;

    bRet = (pstDFMInfo->bIsExtraMode) ? bTemp : HI_TRUE;
#ifdef DEBUG
    HDMI_INFO("s32GapDeltaIAvLine = %d\n", pstBaseParas->s32GapDeltaIAvLine);
    HDMI_INFO("s32GapLineLastSlice = %d\n", pstBaseParas->s32GapLineLastSlice);
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_BOOL DFMAvLineCanBeSend(HI_VOID)
{
    HI_BOOL bRet = HI_FALSE;
    HI_BOOL bTemp = HI_FALSE;
    HI_BOOL bTemp1 = HI_FALSE;
    HI_BOOL bTemp2 = HI_FALSE;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    bTemp2 = (pstBaseParas->s32ExtBlank2SliceSizeMax
             > (pstBaseParas->s32Blank2LenMax
             /pstBaseParas->s32ExtBlank2SliceNumMax)) ? HI_TRUE : HI_FALSE;

    bTemp1 = (pstDFMInfo->bIsExtraMode) ? bTemp2 : HI_TRUE;

    bTemp =  (pstBaseParas->s32ExtraBlankGapMaxLen >= 0)
             ? (pstBaseParas->bAvLineNoRCCanBeSend
             || pstBaseParas->bAvLineNoRCNoGapAddCanBeSend)
             : pstBaseParas->bExtraNoGapWillOK;

    bRet = (bTemp1 || bTemp || pstBaseParas->bAvEndNoGapCanBeSend)
            ? HI_TRUE : HI_FALSE;
#ifdef DEBUG
    HDMI_INFO("bRet = %s\n", bRet ? "true" : "false");
#endif
    return bRet;
}

static HI_VOID DFMOutParasCalc(DFM_IN_S *pstDFMIn, DFM_OUT_S* pstDFMOut)
{
    HI_S32 s32HactiveTimeNoGapAdd = 0;
    HI_S32 s32HBlankActualAbility = 0;
    HI_S32 s32AvCyclesNotExtra = 0;
    HI_S32 s32HactiveTime = 0;
    HI_S32 s32Temp = 0;
    HI_S32 s32Temp1 = 0;
    HI_S32 s32Temp2 = 0;
    DFM_BASE_PARAS_S *pstBaseParas = HI_NULL;
    DFM_INFO_S *pstDFMInfo = HI_NULL;

    if (pstDFMIn == HI_NULL || pstDFMOut == HI_NULL)
    {
        return;
    }

    pstBaseParas = GetDFMBaseParas();
    pstDFMInfo = GetDFMInfo();

    s32Temp = (pstBaseParas->s32AvLineEndCDiffMax < CFRL_TOLERANCE)
               ? (pstBaseParas->s32Blank1LenMax
               + (pstBaseParas->s32AvLineNoAddGapBlank2DFMMax - CFRL_TOLERANCE - 16))
               : (pstBaseParas->s32HBlank1ActualFRLAbility
               - (pstBaseParas->s32AvLineEndCDiffMax - CFRL_TOLERANCE)
               *pstDFMInfo->s32MaxFrlCharsPerLine/pstBaseParas->s32AvLineEndTBActual);

    s32HactiveTimeNoGapAdd = (s32Temp*10000/pstDFMIn->s32LaneNum + 10000 - 1)/10000;

    s32Temp1 = (pstDFMInfo->bIsExtraMode)
               ? (pstBaseParas->s32HBlank1ActualFRLAbility
               - pstBaseParas->s32HBlank1TakeByAvFRL)
               : pstBaseParas->s32HBlank1ActualFRLAbility;

    s32Temp = s32Temp1/pstDFMIn->s32LaneNum;

    s32HBlankActualAbility = (!pstBaseParas->bAvLineNoRCCanBeSend
                              && pstBaseParas->bAvLineNoRCNoGapAddCanBeSend)
                              ? s32HactiveTimeNoGapAdd : s32Temp;

    s32AvCyclesNotExtra = pstDFMInfo->s32MinFrlCharsPerLine*pstDFMIn->s32Hactive
                          /pstDFMInfo->s32Htotal/pstDFMIn->s32LaneNum;

    s32HactiveTime = (pstDFMInfo->bIsExtraMode) ? 0 : s32AvCyclesNotExtra;

    pstDFMOut->s32AvMaxLen = (pstDFMInfo->bIsExtraMode)
                              ? pstBaseParas->s32AvMaxLenPExtra
                              : pstBaseParas->s32AvMaxLenP;

    pstDFMOut->s32AvGapLen = (pstDFMInfo->bIsExtraMode)
                              ? pstBaseParas->s32AvGapLenExtra
                              : pstBaseParas->s32AvGapLen;

    pstDFMOut->s32BlankMaxLen = pstBaseParas->s32BlankMaxLen;

    pstDFMOut->s32BlankGapLen = pstBaseParas->s32BlankGapLen;

    pstDFMOut->s32HblankCycles = (!pstBaseParas->bAvLineNoRCCanBeSend
                                  && !pstBaseParas->bAvLineNoRCNoGapAddCanBeSend
                                  && (pstBaseParas->bAvLineShouldRCNoGapCanBeSend
                                  || !pstBaseParas->bAvEndNoGapCanBeSend))
                                  ? 0 : s32HBlankActualAbility;

    pstDFMOut->s32HactiveTime = (!pstBaseParas->bAvLineNoRCCanBeSend
                                 && !pstBaseParas->bAvLineNoRCNoGapAddCanBeSend)
                                 ? 0 : s32HactiveTime;

    s32Temp1 = (pstBaseParas->bNoGapAddBlank12SliceCanOK)
                ? (pstBaseParas->s32Blank1LenMax/2 + 4 - 1)/4*4
                : pstBaseParas->s32HalfOfMinBlank1AndBlank2;

    s32Temp2 = (pstBaseParas->bNoGapAddBlank22SliceCanOK)
                ? MAX(pstBaseParas->s32Blank1LenMax,
                (pstBaseParas->s32Blank2LenMax/2 + 4 - 1)/4*4) : s32Temp1;

    s32Temp = (pstBaseParas->bAvLineShouldRCNoGapCanBeSend)
               ? MAX(pstBaseParas->s32Blank1LenMax, pstBaseParas->s32Blank2LenMax)
               :((pstBaseParas->bAvEndNoGapCanBeSend)
               ? pstBaseParas->s32ExtraBlankMaxLen : s32Temp2);

    pstDFMOut->s32ExtraBlankMaxLen = (pstBaseParas->bAvLineNoRCCanBeSend
                                      || pstBaseParas->bAvLineNoRCNoGapAddCanBeSend)
                                      ? pstBaseParas->s32ExtraBlankMaxLen : s32Temp;

    s32Temp = (!pstBaseParas->bAvLineNoRCCanBeSend
               && (pstBaseParas->bAvLineNoRCNoGapAddCanBeSend
               || pstBaseParas->bAvLineShouldRCNoGapCanBeSend
               || (!pstBaseParas->bAvLineNoRCNoGapAddCanBeSend
               && !pstBaseParas->bAvLineShouldRCNoGapCanBeSend)))
               ? 0 : pstBaseParas->s32ExtraBlankGapMaxLen;


    pstDFMOut->s32ExtraBlankGapLen = (pstDFMInfo->bIsExtraMode
                                      && pstBaseParas->bAvLineNoRCCanBeSend)
                                      ? pstBaseParas->s32ExtraBlankGapMaxLen : s32Temp;


    pstDFMOut->s32Vactive = pstDFMIn->s32Vactive;

    pstDFMOut->s32Vblank1Lines = pstDFMIn->s32Vsync + pstDFMIn->s32Vback;

    pstDFMOut->bExtraNoGapFlags = (!pstBaseParas->bAvLineNoRCCanBeSend
                                   && !pstBaseParas->bAvLineNoRCNoGapAddCanBeSend
                                   && pstBaseParas->bAvLineShouldRCNoGapCanBeSend)
                                   ? HI_TRUE : HI_FALSE;

    pstDFMOut->bIsExtraMode = pstDFMInfo->bIsExtraMode;

#ifdef DEBUG
    HDMI_INFO("s32HactiveTimeNoGapAdd = %d\n", s32HactiveTimeNoGapAdd);
    HDMI_INFO("s32HBlankActualAbility = %d\n", s32HBlankActualAbility);
    HDMI_INFO("s32AvCyclesNotExtra = %d\n", s32AvCyclesNotExtra);
    HDMI_INFO("11s32HactiveTime = %d\n", s32HactiveTime);
    HDMI_INFO("s32AvMaxLen = %d\n", pstDFMOut->s32AvMaxLen);
    HDMI_INFO("s32AvGapLen = %d\n", pstDFMOut->s32AvGapLen);
    HDMI_INFO("s32BlankMaxLens = %d\n", pstDFMOut->s32BlankMaxLen);
    HDMI_INFO("s32BlankGapLen = %d\n", pstDFMOut->s32BlankGapLen);
    HDMI_INFO("s32HblankCycles = %d\n", pstDFMOut->s32HblankCycles);
    HDMI_INFO("22s32HactiveTime = %d\n", pstDFMOut->s32HactiveTime);
    HDMI_INFO("s32ExtraBlankMaxLen = %d\n", pstDFMOut->s32ExtraBlankMaxLen);
    HDMI_INFO("s32ExtraBlankGapLen = %d\n", pstDFMOut->s32ExtraBlankGapLen);
    HDMI_INFO("s32Vactive = %d\n", pstDFMOut->s32Vactive);
    HDMI_INFO("s32Vblank1Lines = %d\n", pstDFMOut->s32Vblank1Lines);
    HDMI_INFO("bExtraNoGapFlags = %s\n", pstDFMOut->bExtraNoGapFlags ? "true" : "false");
    HDMI_INFO("bIsExtraMode = %s\n", pstDFMOut->bIsExtraMode ? "true" : "false");
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

    DFMInfoInit(pstDFMIn, pstDFMInfo);

    bRet = (pstDFMInfo->bAudioSupport && pstDFMInfo->bVideoSupport
            && pstDFMInfo->bUncompressSupport) ? HI_TRUE : HI_FALSE;

    return bRet;
}

HI_S32 DRV_HDMI_DFMGetData(DFM_IN_S *pstDFMIn, DFM_OUT_S* pstDFMOut)
{
    HI_S32 s32PreSetActive = 1;
    HI_S32 s32PreSetBlank = 1;
    HI_S32 s32PreSetExtBlank = 1;
    DFM_BASE_PARAS_S * pstBaseParas = HI_NULL;

    if (pstDFMIn == HI_NULL || pstDFMOut == HI_NULL)
    {
        return HI_FAILURE;
    }

    pstBaseParas = GetDFMBaseParas();

    DFMBaseParasCalc(pstDFMIn, pstBaseParas);


    for (s32PreSetBlank = 1; s32PreSetBlank <= CFRL_TOLERANCE; s32PreSetBlank++)
    {
        if (HI_FAILURE == DFMBlankParasCalc(pstDFMIn, s32PreSetBlank))
        {
            s32PreSetBlank = 493;
            break;
        }

        if (HI_FALSE == DFMBlank1LastSliceSizeIsOk())
        {
            continue;
        }

        if (HI_FALSE == DFMBlank2LastSliceSizeIsOk())
        {
            continue;
        }

        if (HI_FALSE == DFMBlankSliceLenIsOk())
        {
            continue;
        }

        if (HI_FALSE == DFMAvLineBlankCdiffIsOk(s32PreSetBlank))
        {
            continue;
        }

        if (HI_FALSE == DFMBlankLineDFMIsOk())
        {
            continue;
        }

        if (HI_FALSE == DFMBlankLineCanBeSend())
        {
            continue;
        }

        if (HI_FALSE == DFMBlankGapLenExtend())
        {
            continue;
        }

        if (HI_FALSE == DFMAvLineBlankCanBeSend())
        {
            continue;
        }

        break;
    }

    if (s32PreSetBlank > CFRL_TOLERANCE)
    {
        s32PreSetBlank = 1;
        DFMBlankParasCalc(pstDFMIn, s32PreSetBlank);
    }

    for (s32PreSetActive = 1; s32PreSetActive <= CFRL_TOLERANCE; s32PreSetActive++)
    {
        if (HI_FAILURE == DFMAvParasCalc(pstDFMIn, s32PreSetActive))
        {
            s32PreSetActive = 493;
            break;
        }

        if (HI_FALSE == DFMAvLineAvDFMIsOk())
        {
            continue;
        }

        if (HI_FALSE == DFMAvSliceLenIsOK())
        {
            continue;
        }


        if (HI_FALSE == DFMAvGapLenExtend())
        {
            continue;
        }

        break;
    }

    if (s32PreSetActive > CFRL_TOLERANCE)
    {
        s32PreSetActive = 1;
        DFMAvParasCalc(pstDFMIn, s32PreSetActive);
    }

    for (s32PreSetExtBlank = 1; s32PreSetExtBlank <= CFRL_TOLERANCE; s32PreSetExtBlank++)
    {
        if (HI_FAILURE == DFMExtBlankParasCalc(pstDFMIn, s32PreSetExtBlank))
        {
            s32PreSetExtBlank = 493;
            break;
        }

        if (HI_FAILURE == DFMExtAvParasCalc(pstDFMIn))
        {
            s32PreSetExtBlank = 493;
            break;
        }

        DFMAvLineCanbeSendCalc();

        if (HI_FALSE == DFMExtBlank1LastSliceSizeIsOK())
        {
            continue;
        }

        if (HI_FALSE == DFMExtBlank2LastSliceSizeIsOK())
        {
            continue;
        }

        if (HI_FALSE == DFMExtraAvLineBlankCdiffIsOk())
        {
            continue;
        }

        if (HI_FALSE == DFMExtraAvLineBlankCanBeSend())
        {
           continue;
        }

        if (HI_FALSE == DFMAvLineCanBeSend())
        {
           continue;
        }

        break;
    }


    if (s32PreSetExtBlank > CFRL_TOLERANCE)
    {
        s32PreSetExtBlank = 1;
        DFMExtBlankParasCalc(pstDFMIn, s32PreSetExtBlank);
        DFMExtAvParasCalc(pstDFMIn);
        DFMAvLineCanbeSendCalc();
    }

    DFMOutParasCalc(pstDFMIn, pstDFMOut);

#ifdef DEBUG
    HDMI_INFO("s32PreSetBlank=%d\n", s32PreSetBlank);
    HDMI_INFO("s32PreSetActive=%d\n", s32PreSetActive);
    HDMI_INFO("s32PreSetExtBlank=%d\n", s32PreSetExtBlank);
#endif
    return HI_SUCCESS;
}

