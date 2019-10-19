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
#include "hdmi_osal.h"
#include "drv_hdmi_edid.h"
#include "drv_hdmi_intf.h"
#include "drv_hdmi_frl.h"

#define DATAFLOW_METERING_THR   492

#define FLT_STEP_TIMEOUT        0x3d090
#define FLT_TIMEOUT             0x4c4b00
#define FLT_UPDATE_TIMEOUT      0x6100

#define FRL_CHECK_POINTER_NO_RET(p)\
do{	\
	if(HI_NULL == p){ \
		HDMI_ERR("%s %d null pointer!\n", __FUNCTION__, __LINE__);\
		return; \
	} \
}while(0)

#define FRL_CHECK_POINTER_RET(p)\
do{ \
    if(HI_NULL == p){ \
        HDMI_ERR("%s %d null pointer!\n", __FUNCTION__, __LINE__);\
        return HI_FALSE; \
    } \
}while(0)

#define FRL_CHECK_POINTER(p)\
    do{ \
        if(HI_NULL == p){ \
            HDMI_ERR("%s %d null pointer!\n", __FUNCTION__, __LINE__);\
            return HI_FAILURE; \
        } \
    }while(0)


#define GET_FRLRATE_INFO(FrlRate, FrlBitRate, FrlLaneNum) \
do \
{   \
    if (FrlRate == 1)\
    {\
        FrlBitRate = 3;\
        FrlLaneNum = 3;\
    }\
    else if (FrlRate == 2)\
    {\
        FrlBitRate = 6;\
        FrlLaneNum = 3;\
    }\
    else if (FrlRate == 3)\
    {\
        FrlBitRate = 6;\
        FrlLaneNum = 4;\
    }\
    else if (FrlRate == 4)\
    {\
        FrlBitRate = 8;\
        FrlLaneNum = 4;\
    }\
    else if (FrlRate == 5)\
    {\
        FrlBitRate = 10;\
        FrlLaneNum = 4;\
    }\
    else if (FrlRate == 6)\
    {\
        FrlBitRate = 12;\
        FrlLaneNum = 4;\
    }\
}while(0)

#define DEEPCOLOR_2_COLORDEPTH(DEEPCOLOR, ColorDepth) \
do  \
{    \
    if (DEEPCOLOR == HDMI_DEEP_COLOR_24BIT)\
    {\
         ColorDepth = 8;\
    }\
    else if (DEEPCOLOR == HDMI_DEEP_COLOR_30BIT)\
    {\
         ColorDepth = 10;\
    }\
    else if (DEEPCOLOR == HDMI_DEEP_COLOR_36BIT)\
    {\
         ColorDepth= 12;\
    }\
    else if (DEEPCOLOR == HDMI_DEEP_COLOR_48BIT)\
    {\
         ColorDepth = 16;\
    }\
    else\
    {\
         ColorDepth = 8;\
    }\
}while(0)

#define COLORSPACE_2_PIXELFORMAT(ColorSpace, PixelFormat)\
do  \
{    \
    if (ColorSpace == HDMI_COLORSPACE_RGB)\
    {\
        PixelFormat = 0;\
    }\
    else if (ColorSpace == HDMI_COLORSPACE_YCbCr420)\
    {\
        PixelFormat = 1;\
    }\
    else if (ColorSpace == HDMI_COLORSPACE_YCbCr422)\
    {\
        PixelFormat = 2;\
    }\
    else if (ColorSpace == HDMI_COLORSPACE_YCbCr444)\
    {\
        PixelFormat = 3;\
    }\
    else\
    {\
        PixelFormat = 0;\
    }\
}while(0)

#define SAMPLEFS_2_AUDIORATE(SampleFs, AudioRate)\
do \
{\
    if (SampleFs == HDMI_SAMPLE_RATE_8K)\
    {\
        AudioRate = 8000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_11K)\
    {\
        AudioRate = 11000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_12K)\
    {\
        AudioRate = 12000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_16K)\
    {\
        AudioRate = 16000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_22K)\
    {\
        AudioRate = 22000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_24K)\
    {\
        AudioRate = 24000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_32K)\
    {\
        AudioRate = 32000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_44K)\
    {\
        AudioRate = 44100;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_48K)\
    {\
        AudioRate = 48000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_88K)\
    {\
        AudioRate= 88000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_96K)\
    {\
        AudioRate = 96000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_176K)\
    {\
        AudioRate = 176000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_192K)\
    {\
        AudioRate = 192000;\
    }\
    else if (SampleFs == HDMI_SAMPLE_RATE_768K)\
    {\
        AudioRate = 768000;\
    }\
    else\
    {\
        AudioRate = 0;\
    }\
}while(0)


static HDMI_VIDEO_DEF_S *FrlGetFormatParam(HDMI_VIDEO_TIMING_E enTimming,
                                           HDMI_PICTURE_ASPECT enAspect, HI_BOOL b3DEnable)
{
    HDMI_VIDEO_DEF_S    *pstTmpFmt = HI_NULL;
    HDMI_VIDEO_CODE_E   enVic = 0;

    if (enTimming < HDMI_VIDEO_TIMING_VESA_DEFINE)
    {
        enVic = DRV_HDMI_VicSearch(enTimming, enAspect, b3DEnable);
        pstTmpFmt = DRV_HDMI_CommFormatParamGet(enVic);
    }
    else if (enTimming < HDMI_VIDEO_TIMING_USER_DEFINE)
    {
        pstTmpFmt = DRV_HDMI_VESAFormatParamGet(enTimming);
    }
    else
    {
        ;//USE Define
    }

    return pstTmpFmt;
}

static HI_S32 FrlTxFFESet(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_S32         s32Ret   = HI_SUCCESS;
    HDMI_PHY_CFG_S stPhyCfg = {0};

    FRL_CHECK_POINTER(pstHdmiDev);

    HDMI_MEMSET(&stPhyCfg, 0, sizeof(HDMI_PHY_CFG_S));

    // TODO: Read status_flags(which lane will change TxFFE)

    stPhyCfg.enModeCfg = HDMI_PHY_MODE_CFG_TXFFE;
    stPhyCfg.enRate = (FRL_WORK_MODE_E)pstHdmiDev->stFrlInfo.stRateInfo.u8CurRate;

#ifndef HDMI_FPGA_SUPPORT
    HDMI_HAL_CALL(HAL_HDMI_PhySet, &stPhyCfg);
#endif

    return s32Ret;
}

static HI_S32 FrlPhySet(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_S32             s32Ret      = HI_SUCCESS;
    HDMI_PHY_CFG_S     stPhyCfg    = {0};
    HDMI_APP_ATTR_S    *pstAppAttr = HI_NULL;
    HDMI_VO_ATTR_S     *pstVOAttr  = HI_NULL;

    FRL_CHECK_POINTER(pstHdmiDev);

    pstAppAttr = &pstHdmiDev->stAttr.stAppAttr;
    pstVOAttr  = &pstHdmiDev->stAttr.stVOAttr;

    HDMI_MEMSET(&stPhyCfg, 0, sizeof(HDMI_PHY_CFG_S));

    /* PHY config */
    stPhyCfg.bEmiEnable    = pstHdmiDev->bEmiEnable;
    stPhyCfg.u32PixelClk   = pstVOAttr->u32ClkFs;
    stPhyCfg.u32TmdsClk    = pstVOAttr->u32HdmiAdaptPixClk;
    stPhyCfg.enDeepColor   = pstAppAttr->enDeepColorMode;
    stPhyCfg.enColorSpace  = pstAppAttr->enOutColorSpace;
    stPhyCfg.enTraceLen    = pstHdmiDev->stModParam.enTraceLen;

    HDMI_INFO("start mode: %d\n", pstHdmiDev->stFrlInfo.enMode);
    if (HDMI_FRL_MODE_FRL == pstHdmiDev->stFrlInfo.enMode)
    {
        stPhyCfg.enModeCfg = HDMI_PHY_MODE_CFG_FRL;
        HDMI_MEMSET(stPhyCfg.aenTxFFE, FRL_TXFFE_MODE_0, sizeof(stPhyCfg.aenTxFFE));
        stPhyCfg.enRate = (FRL_WORK_MODE_E)pstHdmiDev->stFrlInfo.stRateInfo.u8CurRate;
    }

    HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, HI_FALSE);
    HDMI_HAL_CALL(HAL_HDMI_PhySet, &stPhyCfg);
    HAL_CALL_NOPARAM(HAL_HDMI_CtrlReset);
    HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, HI_TRUE);

    return s32Ret;
}


static HI_VOID FrlDFMConstruct(DFM_IN_S* pstDFM, HDMI_AO_ATTR_S* pstAoAttr,
                               HDMI_APP_ATTR_S* pstAppAttr, HDMI_VIDEO_DEF_S* pstVideoDef)
{
    FRL_CHECK_POINTER_NO_RET(pstDFM);
    FRL_CHECK_POINTER_NO_RET(pstAoAttr);
    FRL_CHECK_POINTER_NO_RET(pstAppAttr);
    FRL_CHECK_POINTER_NO_RET(pstVideoDef);

    pstDFM->s32Hactive = pstVideoDef->u32Hactive;
    pstDFM->s32Vactive = pstVideoDef->u32Vactive;
    pstDFM->s32Hblank = pstVideoDef->u32Hblank;
    pstDFM->s32Vblank = pstVideoDef->u32Vblank;
    pstDFM->s32Hfront = pstVideoDef->u32Hfront;
    pstDFM->s32Hsync = pstVideoDef->u32Hsync;
    pstDFM->s32Hback = pstVideoDef->u32Hback;
    pstDFM->s32Vfront = pstVideoDef->u32Vfront;
    pstDFM->s32Vsync = pstVideoDef->u32Vsync;
    pstDFM->s32Vback = pstVideoDef->u32Vback;
    pstDFM->s32VFreq = pstVideoDef->u32Rate;
    DEEPCOLOR_2_COLORDEPTH(pstAppAttr->enDeepColorMode, pstDFM->s32ColorDepth);
    COLORSPACE_2_PIXELFORMAT(pstAppAttr->enOutColorSpace, pstDFM->s32PixelFormat);
    SAMPLEFS_2_AUDIORATE(pstAoAttr->enSampleFs, pstDFM->s32AudioRate);

    pstDFM->s32Layout = (pstAoAttr->enChanels > HDMI_AUDIO_FORMAT_2CH) ? 1 : 0;
    /* ACAT PacketType */
    pstDFM->s32ACAT = 3;
    pstDFM->s32PacketType = 11;

    return;
}

HI_U8 FrlGetSinkVersion(HDMI_DEVICE_ID_E enHdmiID)
{
    HI_S32         s32Ret     = HI_SUCCESS;
    HI_U8          u8SinkVer  = 0;
    HDMI_DEVICE_S *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiID);

    s32Ret = HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_GET_SINK_VER, &u8SinkVer);

    u8SinkVer = (HI_SUCCESS != s32Ret) ? 0 : u8SinkVer;

    return u8SinkVer;
}

static HI_BOOL FrlGetFltUpdate(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_S32  s32Ret     = HI_SUCCESS;
    HI_BOOL bFltUpdate = HI_FALSE;

    s32Ret = HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_GET_FLT_UPDATE, &bFltUpdate);
    bFltUpdate = (HI_SUCCESS != s32Ret) ? HI_FALSE : bFltUpdate;

    return bFltUpdate;
}

static HI_VOID FrlSetFltUpdate(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bFltUpdate)
{
    HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_SET_FLT_UPDATE, &bFltUpdate);

    return;
}

static HI_BOOL FrlGetFltStart(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_BOOL bFltStart  = HI_FALSE;

    HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_GET_FLT_START, &bFltStart);

    return bFltStart;
}

static HI_VOID FrlSetFltStart(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bFltStart)
{
    HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_SET_FLT_START, &bFltStart);

    return;
}


static HI_VOID FrlGetTestConfig(HDMI_DEVICE_S* pstHdmiDev, SCDC_TEST_CONFIG_S* pstTestCfg)
{
    FRL_CHECK_POINTER_NO_RET(pstTestCfg);

    HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_GET_TEST_CONFIG, pstTestCfg);

    return;
}

static HI_VOID FrlSetConfig1(HDMI_DEVICE_S* pstHdmiDev, SCDC_CONFIG1_S* pstCfg)
{
    FRL_CHECK_POINTER_NO_RET(pstCfg);

    HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_SET_CONFIG1, pstCfg);

    return;
}

static HI_BOOL FrlGetFltReady(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_BOOL bFltReady = HI_FALSE;

    HAL_CALL(HAL_HDMI_ScdcProcess, SCDC_CMD_GET_FLT_READY, &bFltReady);

    return bFltReady;
}

static HI_BOOL FrlCheckCapability(HDMI_DEVICE_S* pstHdmiDev)
{
    HDMI_EDID_DATA_E        enEdidRet       = HDMI_EDID_DATA_INVALID;
    HDMI_TX_CAPABILITY_S    stTxCap;
    HDMI_SINK_CAPABILITY_S  *pstSinkCap     = HI_NULL;
    HDMI_FRL_INFO_S         *pstFrlInfo     = HI_NULL;
    HI_BOOL                 bRet            = HI_FALSE;
    HI_BOOL                 bSupportFrl     = HI_FALSE;
    HI_U32                  u32SinkScdcVer  = 0;
    HI_S32                  s32Ret          = HI_SUCCESS;

    FRL_CHECK_POINTER_RET(pstHdmiDev);

    pstFrlInfo = &pstHdmiDev->stFrlInfo;

    HDMI_MEMSET(&stTxCap, 0, sizeof(HDMI_TX_CAPABILITY_S));

    s32Ret = HAL_CALL(HAL_HDMI_TxCapabilityGet, &stTxCap);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FALSE;
    }

    enEdidRet = DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap);

    if (enEdidRet == HDMI_EDID_DATA_INVALID)
    {
        HDMI_WARN("Invalid EdidCapability from Sink!\n");
    }

    u32SinkScdcVer = FrlGetSinkVersion(pstHdmiDev->u32HdmiDevId);

    HDMI_INFO("bTxHdmi_21:%d, u8MaxFrlRate:%d, bSupportSCDC:%d, SCDCVersion:%d\n",
              stTxCap.bTxHdmi_21, pstSinkCap->u8MaxFrlRate, pstSinkCap->bSupportSCDC,
              u32SinkScdcVer);

    bSupportFrl = ((stTxCap.bTxHdmi_21) && (pstSinkCap->u8MaxFrlRate > 0)
                    && (pstSinkCap->bSupportSCDC) && (u32SinkScdcVer != 0))
                    ? HI_TRUE : HI_FALSE;

    if (bSupportFrl || pstHdmiDev->stAttr.stAppAttr.bAuthMode)
    {
        pstFrlInfo->stRateInfo.u8MaxRate = pstSinkCap->u8MaxFrlRate;
        bRet = HI_TRUE;
        HDMI_INFO("FrlCheckCapability success\n");
    }
    else
    {
        pstFrlInfo->stRateInfo.u8MaxRate = 0;
        bRet = HI_FALSE;
        HDMI_INFO("FrlCheckCapability fail\n");
    }

    pstFrlInfo->bSupportFFE = pstSinkCap->bSupportFFE;
    pstFrlInfo->bScdcPresent = pstSinkCap->bSupportSCDC;

    return bRet;
}

static HI_BOOL FrlCheckFormat(HDMI_FRL_INFO_S* pstFrlInfo, HDMI_ATTR_S* pstAttr)
{
    HI_U32                      i            = 0;
    HDMI_VO_ATTR_S              *pstVoAttr   = HI_NULL;
    HDMI_AO_ATTR_S              *pstAoAttr   = HI_NULL;
    HDMI_APP_ATTR_S             *pstAppAttr  = HI_NULL;
    HDMI_VIDEO_DEF_S            *pstVideoDef = HI_NULL;
    HI_BOOL                     b3DEnable    = HI_FALSE;
    DFM_IN_S                    stDFMIn      = {0};
    HI_U8                       u8MaxRate    = 0;
    HI_BOOL                     bCapable     = HI_FALSE;

    FRL_CHECK_POINTER_RET(pstFrlInfo);
    FRL_CHECK_POINTER_RET(pstAttr);

    pstVoAttr = &pstAttr->stVOAttr;
    pstAoAttr  = &pstAttr->stAOAttr;
    pstAppAttr = &pstAttr->stAppAttr;

    FRL_CHECK_POINTER_RET(pstVoAttr);
    FRL_CHECK_POINTER_RET(pstAoAttr);
    FRL_CHECK_POINTER_RET(pstAppAttr);

    u8MaxRate = pstFrlInfo->stRateInfo.u8MaxRate;

    HDMI_MEMSET(&stDFMIn, 0, sizeof(DFM_IN_S));

    b3DEnable = (HDMI_3D_BUTT == pstVoAttr->enStereoMode) ? HI_FALSE : HI_TRUE;

    pstVideoDef = FrlGetFormatParam(pstVoAttr->enVideoTiming,
                                    pstVoAttr->enPictureAspect, b3DEnable);
    if (HI_NULL == pstVideoDef)
    {
        HDMI_WARN("No this fmt's param, transmit by tmds.\n");
        return HI_FALSE;
    }

    HDMI_INFO("enVideoCode: %d\n", pstVideoDef->enVideoCode);
    pstFrlInfo->u32TmdsClk = pstVoAttr->u32HdmiAdaptPixClk;

    switch (pstFrlInfo->enStrategyMode)
    {
        case HDMI_FRL_STRATEGY_MODE_1:
        {
            if (pstVoAttr->u32HdmiAdaptPixClk <= HDMI_EDID_MAX_HDMI20_TMDS_RATE)
            {
                HDMI_INFO("u32HdmiAdaptPixClk(%d) < 600M\n", pstVoAttr->u32HdmiAdaptPixClk);
                bCapable = HI_FALSE;
                goto RET;
            }
            break;
        }
        case HDMI_FRL_STRATEGY_MODE_2:
        {
            if (pstVoAttr->u32HdmiAdaptPixClk <= HDMI_EDID_MAX_HDMI14_TMDS_RATE)
            {
                bCapable = HI_FALSE;
                goto RET;
            }
            break;
        }
        case HDMI_FRL_STRATEGY_MODE_3:
        {
            if (pstVideoDef->enPIType == HDMI_VIDEO_INTERLACE)
            {
                bCapable = HI_FALSE;
                goto RET;
            }
            break;
        }
        default:
            break;
    }

    FrlDFMConstruct(&stDFMIn, pstAoAttr, pstAppAttr, pstVideoDef);

    if (u8MaxRate > 6)
    {
        bCapable = HI_FALSE;
        goto RET;
    }

    for (i = u8MaxRate; i > 0; i--)
    {
        GET_FRLRATE_INFO(i, stDFMIn.s32BitRate, stDFMIn.s32LaneNum);
        if (DRV_HDMI_DFMFormatCanbeSupport(&stDFMIn) == HI_TRUE)
        {
            pstFrlInfo->stRateInfo.u8MinRate = i;
            HDMI_INFO("u8MinRate: %d\n", pstFrlInfo->stRateInfo.u8MinRate);
        }
        else
        {
            break;
        }
    }

    bCapable = (i == u8MaxRate) ? HI_FALSE : HI_TRUE;

RET:

    return bCapable;
}

static HI_VOID FrlSetTrainRate(HDMI_DEVICE_S* pstHdmiDev)
{
    HDMI_FRL_INFO_S *pstFrlInfo = HI_NULL;
    SCDC_CONFIG1_S   stCfg      = {0};

    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);

	pstFrlInfo = &pstHdmiDev->stFrlInfo;

    if (pstFrlInfo->enMode == HDMI_FRL_MODE_FRL)
    {
        stCfg.u8FfeLevels = (pstFrlInfo->bSupportFFE) ? 4 : 0;
        stCfg.u8FrlRate   = pstFrlInfo->stRateInfo.u8CurRate;
    }
    else
    {
        stCfg.u8FfeLevels = 0;
        stCfg.u8FrlRate = 0;
    }

    FrlSetConfig1(pstHdmiDev, &stCfg);

    return;
}

static HI_BOOL FrlIsCTSMode(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_BOOL  bRet = HI_FALSE;
    SCDC_TEST_CONFIG_S stTestCfg;

    if (pstHdmiDev == HI_NULL)
    {
        return HI_FALSE;
    }

    HDMI_MEMSET(&stTestCfg, 0, sizeof(SCDC_TEST_CONFIG_S));

    FrlGetTestConfig(pstHdmiDev, &stTestCfg);

    bRet = (   (stTestCfg.bFrlMax == 1 && stTestCfg.bDscFrlMax == 0)
            || (stTestCfg.bFrlMax == 0 && stTestCfg.bDscFrlMax == 1))
            ? HI_TRUE : HI_FALSE;

    return bRet;
}

static HI_S32 FrlGetCurRate(HDMI_FRL_INFO_S* pstFrlInfo)
{
    HI_S32       s32Ret       = HI_SUCCESS;
    HI_U8        u8CurFrlRate = 0;
    static HI_U8 u8PreRate    = 0;

    FRL_CHECK_POINTER(pstFrlInfo);

    u8CurFrlRate = pstFrlInfo->stRateInfo.u8CurRate;

    if (pstFrlInfo->bCTSMode == HI_TRUE)
    {
        u8PreRate = u8CurFrlRate;
        u8CurFrlRate = pstFrlInfo->stRateInfo.u8MaxRate;
    }
    else
    {
        if (u8PreRate != 0)
        {
            u8CurFrlRate = u8PreRate;
            u8PreRate = 0;
        }
        else
        {
            if (pstFrlInfo->enRateSelect == HDMI_FRL_RATE_SELECT_BIG)
            {
                u8CurFrlRate--;
            }
            else
            {
                u8CurFrlRate++;
            }

            if ((u8CurFrlRate > pstFrlInfo->stRateInfo.u8MaxRate)
                || (u8CurFrlRate < pstFrlInfo->stRateInfo.u8MinRate))
            {

                s32Ret = HI_FAILURE;
            }
        }
    }

    pstFrlInfo->stRateInfo.u8CurRate = u8CurFrlRate;

    return s32Ret;
}

static HI_VOID FrlTrainException(HDMI_DEVICE_S* pstHdmiDev)
{
    HDMI_FRL_INFO_S             *pstFrlInfo  = HI_NULL;
    HDMI_FRL_STATE_MACH_INFO_S  *pstMachInfo = HI_NULL;
    HDMI_PHY_CFG_S              stPhyCfg     = {0};
    HDMI_APP_ATTR_S             *pstAppAttr  = HI_NULL;
    HDMI_VO_ATTR_S              *pstVOAttr   = HI_NULL;
    HI_S32                       s32Ret      = HI_SUCCESS;

    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);

    pstFrlInfo  = &pstHdmiDev->stFrlInfo;
    pstMachInfo = &pstFrlInfo->stStateMachInfo;
    pstAppAttr  = &pstHdmiDev->stAttr.stAppAttr;
    pstVOAttr   = &pstHdmiDev->stAttr.stVOAttr;

    HDMI_ERR("FRL error!\n");

    /* Close PHY oe */
#ifndef HDMI_FPGA_SUPPORT
    s32Ret = HAL_CALL(HAL_HDMI_PhyOutputEnableSet, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }
#endif

    pstFrlInfo->enMode         = HDMI_FRL_MODE_TMDS;
    pstFrlInfo->bStart         = HI_FALSE;
    pstMachInfo->u64StartTime  = HDMI_OSAL_GetTimeInMs();
    pstMachInfo->enTrainStatus = HDMI_FRL_TRAIN_STEP_STOP;

    HDMI_MEMSET(&stPhyCfg, 0, sizeof(HDMI_PHY_CFG_S));

    /* PHY config */
    stPhyCfg.bEmiEnable    = pstHdmiDev->bEmiEnable;
    stPhyCfg.u32PixelClk   = pstVOAttr->u32ClkFs;
    stPhyCfg.u32TmdsClk    = pstVOAttr->u32HdmiAdaptPixClk;
    stPhyCfg.enDeepColor   = pstAppAttr->enDeepColorMode;
    stPhyCfg.enModeCfg     = HDMI_FRL_MODE_TMDS;
    stPhyCfg.enColorSpace  = pstAppAttr->enOutColorSpace;

    if (stPhyCfg.u32TmdsClk > HDMI_EDID_MAX_HDMI20_TMDS_RATE)
    {
        HDMI_ERR("TMDS Clk > 600M. Can't work TMDS mode. \n");
        // TODO: notify to user
        return;
    }

#ifndef HDMI_FPGA_SUPPORT
    s32Ret = HAL_CALL(HAL_HDMI_PhySet, &stPhyCfg);
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }
    /* HdmiModeStrategy and sw rst */
    HdmiModeStrategy(pstHdmiDev);
    s32Ret = HAL_CALL(HAL_HDMI_PhyOutputEnableSet, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }
#endif

    return;
}

static HI_VOID FrlConfigAndStartTrain(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_U32                  u8FrlRate = 0;
    HDMI_FRL_TRAIN_CONFIG_S stTrainConfig = {0};
    HDMI_FRL_INFO_S         *pstFrlInfo = HI_NULL;
    SCDC_TEST_CONFIG_S      stTestCfg;

    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);

    HDMI_MEMSET(&stTestCfg, 0, sizeof(SCDC_TEST_CONFIG_S));

    pstFrlInfo = &pstHdmiDev->stFrlInfo;
    u8FrlRate = pstFrlInfo->stRateInfo.u8CurRate;

    stTrainConfig.u8FrlRate = u8FrlRate;
    stTrainConfig.u8FFELevels = FRL_TXFFE_MODE_3;

    FrlGetTestConfig(pstHdmiDev, &stTestCfg);
    stTrainConfig.bFrlNoTimeOut = stTestCfg.bFltNoTimeout;

    stTrainConfig.stTimer.u32FltStepTimeOut = 0;
    stTrainConfig.stTimer.u32FltTimeOut = FLT_TIMEOUT;
    stTrainConfig.stTimer.u32FltUpdateTimeOut = FLT_UPDATE_TIMEOUT;
    stTrainConfig.stTimer.u32FltWaitConfigMs = 100;
    stTrainConfig.stTimer.u32FltWaitResultMs = 300;
    stTrainConfig.enTrainSel = pstFrlInfo->enTrainSel;

    HAL_CALL(HAL_HDMI_FrlTrainConfig, &stTrainConfig);
    HAL_CALL(HAL_HDMI_FrlEnable, HI_FALSE);
    HAL_CALL_NOPARAM(HAL_HDMI_FrlTrainStart);

    return;
}

static HI_VOID FrlGetTrainResult(HDMI_DEVICE_S* pstHdmiDev,
                                 HDMI_FRL_TRAIN_STATUS_S* pstTrainStatus)
{
    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);
    FRL_CHECK_POINTER_NO_RET(pstTrainStatus);

    HAL_CALL(HAL_HDMI_FrlGetTrainStatus, pstTrainStatus);

    return;
}

static HI_VOID FrlEnableOutput(HDMI_DEVICE_S* pstHdmiDev , HI_BOOL bEnable)
{
    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);

    HAL_CALL(HAL_HDMI_FrlEnable, bEnable);

    return;
}

HI_VOID DRV_HDMI_FrlMachInit(HDMI_DEVICE_ID_E enHdmiID)
{
    HDMI_DEVICE_S               *pstHdmiDev = HI_NULL;
    HDMI_FRL_INFO_S             *pstFrlInfo = HI_NULL;
    HDMI_FRL_STATE_MACH_INFO_S  *pstMachInfo = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiID);
    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);

    pstFrlInfo = &pstHdmiDev->stFrlInfo;
    pstMachInfo = &pstFrlInfo->stStateMachInfo;

    if (pstMachInfo->bStartMach != HI_TRUE)
    {
        pstMachInfo->bStartMach = HI_TRUE;
        pstMachInfo->u64StartTime = HDMI_OSAL_GetTimeInMs();
        pstMachInfo->u32WaitHandleMs = 100;
        pstMachInfo->u32WaitReadyMs = 20;
        pstMachInfo->u32WaitRetrainMs = 500;
        pstMachInfo->enTrainStatus = HDMI_FRL_TRAIN_STEP_BUTT;
        pstFrlInfo->enRateSelect = HDMI_FRL_RATE_SELECT_BIG;
        pstFrlInfo->u32MaxFailTimes = 3;
        pstFrlInfo->bWorkEn = HI_FALSE;
        pstFrlInfo->enTrainSel = HDMI_FRL_TRAIN_SEL_SW;
        HDMI_MEMSET(pstFrlInfo->aenCurTxFFE, FRL_TXFFE_MODE_0, sizeof(pstFrlInfo->aenCurTxFFE));
    }

    return ;
}

HI_VOID DRV_HDMI_FrlEnable(HDMI_DEVICE_ID_E enHdmiID, HI_BOOL bEnable)
{
    HDMI_DEVICE_S              *pstHdmiDev  = HI_NULL;
    HDMI_FRL_INFO_S            *pstFrlInfo  = HI_NULL;
    HDMI_FRL_STATE_MACH_INFO_S *pstMachInfo = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiID);
    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);

    pstFrlInfo  = &pstHdmiDev->stFrlInfo;
    pstMachInfo = &pstFrlInfo->stStateMachInfo;

    pstFrlInfo->bStart = bEnable;
    pstMachInfo->enTrainStatus = (HI_TRUE == bEnable) ?  \
        HDMI_FRL_TRAIN_STEP_READY_CHECK : HDMI_FRL_TRAIN_STEP_STOP;
    pstMachInfo->u64StartTime = HDMI_OSAL_GetTimeInMs();
    HDMI_INFO("enTrainStatus:%d, u64StartTime:%llu\n", pstMachInfo->enTrainStatus, pstMachInfo->u64StartTime);

    return;
}

HI_S32 DRV_HDMI_FrlModeStrategy(HDMI_DEVICE_ID_E enHdmiID)
{
    HDMI_DEVICE_S              *pstHdmiDev    = HI_NULL;
    HDMI_ATTR_S                *pstAttr       = HI_NULL;
    HDMI_FRL_INFO_S            *pstFrlInfo    = HI_NULL;
    HDMI_FRL_STATE_MACH_INFO_S *pstMachInfo   = HI_NULL;
    HI_U8                      *pu8CurFrlRate = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiID);
    FRL_CHECK_POINTER(pstHdmiDev);

    pstAttr       = &pstHdmiDev->stAttr;
    pstFrlInfo    = &pstHdmiDev->stFrlInfo;
    pstMachInfo   = &pstFrlInfo->stStateMachInfo;
    pu8CurFrlRate = &pstFrlInfo->stRateInfo.u8CurRate;

    if (HI_TRUE != FrlCheckCapability(pstHdmiDev))
    {
        HDMI_INFO("FrlCheckCapability fail, change to TMDS\n");
        pstFrlInfo->enMode = HDMI_FRL_MODE_TMDS;
    }
    else
    {
        if (HI_TRUE != FrlCheckFormat(pstFrlInfo, pstAttr))
        {
            HDMI_INFO("FrlCheckFormat fail, change to TMDS\n");
            pstFrlInfo->enMode = HDMI_FRL_MODE_TMDS;
        }
        else
        {
            HDMI_INFO("FrlCheckCapability success, FRL mode\n");
            pstFrlInfo->enMode = HDMI_FRL_MODE_FRL;
        }
    }

    if (pstFrlInfo->enMode == HDMI_FRL_MODE_TMDS)
    {
        if (pstAttr->stVOAttr.u32HdmiAdaptPixClk > HDMI_EDID_MAX_HDMI20_TMDS_RATE)
        {
            HDMI_ERR("This format not support!\n");
            return HI_FAILURE;
        }

        if (pstFrlInfo->bScdcPresent == HI_TRUE)
        {
            FrlSetTrainRate(pstHdmiDev);
        }
    }
    else
    {
        *pu8CurFrlRate =(pstFrlInfo->enRateSelect == HDMI_FRL_RATE_SELECT_BIG)
                        ? pstFrlInfo->stRateInfo.u8MaxRate
                        : pstFrlInfo->stRateInfo.u8MinRate;

        pstFrlInfo->bCTSMode = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_VOID DRV_HDMI_FrlTrainMach(HDMI_DEVICE_ID_E enHdmiID)
{
    HDMI_FRL_INFO_S            *pstFrlInfo     = HI_NULL;
    HDMI_DEVICE_S              *pstHdmiDev     = HI_NULL;
    HDMI_FRL_STATE_MACH_INFO_S *pstMachInfo    = HI_NULL;
    static HI_U32               u32TimeOut     = 0;
    HI_U64                      u64StartTime   = 0;
    HDMI_FRL_TRAIN_STEP_E       enTrainStatus  = HDMI_FRL_TRAIN_STEP_BUTT;
    HDMI_FRL_TRAIN_STATUS_S    *pstTrainStatus = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiID);
    FRL_CHECK_POINTER_NO_RET(pstHdmiDev);

    pstFrlInfo     = &pstHdmiDev->stFrlInfo;
    pstMachInfo    = &pstFrlInfo->stStateMachInfo;
    u64StartTime   = pstMachInfo->u64StartTime;
    enTrainStatus  = pstMachInfo->enTrainStatus;
    pstTrainStatus = &pstFrlInfo->stTrainStatus;

    switch (pstMachInfo->enTrainStatus)
    {
        case HDMI_FRL_TRAIN_STEP_READY_CHECK:
        {
            if ((HDMI_OSAL_GetTimeInMs() - u64StartTime) > pstMachInfo->u32WaitReadyMs)
            {
                if (HI_TRUE == FrlGetFltReady(pstHdmiDev))
                {
                    HDMI_INFO(">>>>>>>>>>>>>>>>>>start training\n");
                    FrlPhySet(pstHdmiDev);
                    FrlSetTrainRate(pstHdmiDev);
                    u32TimeOut = 0;
                    enTrainStatus = HDMI_FRL_TRAIN_STEP_TRAIN_START;
                }
                else
                {
                    u32TimeOut++;
                }
                u64StartTime = HDMI_OSAL_GetTimeInMs();
            }
            else
            {
                if(u32TimeOut >= 10)
                {
                    HDMI_INFO("FrlTrainException: %d\n", u32TimeOut);
                    u32TimeOut = 0;
                    if (pstFrlInfo->u32Bypass & FRL_BYPASS_READY_CHECK)
                    {
                        HDMI_INFO("READY_CHECK bypass, goto TRAIN_START!\n");
                        enTrainStatus = HDMI_FRL_TRAIN_STEP_TRAIN_START;
                        break;
                    }
                    FrlTrainException(pstHdmiDev);
                    return;
                }
            }
            break;
        }
        case HDMI_FRL_TRAIN_STEP_TRAIN_START:
        {
            HDMI_INFO("HDMI_FRL_TRAIN_STEP_TRAIN_START\n");
            FrlConfigAndStartTrain(pstHdmiDev);
            u64StartTime  = HDMI_OSAL_GetTimeInMs();
            enTrainStatus = HDMI_FRL_TRAIN_STEP_RESULT_CHECK;
            break;
        }
        case HDMI_FRL_TRAIN_STEP_RESULT_CHECK:
        {
            FrlGetTrainResult(pstHdmiDev, pstTrainStatus);
            if (pstTrainStatus->enFrlTrainStatus == HDMI_FRL_TRAIN_SUCCESS)
            {
                enTrainStatus = HDMI_FRL_TRAIN_STEP_RESULT_HANDLE;
                pstFrlInfo->u32FailCount = 0;
            }
            else
            {
                if (pstTrainStatus->enTrainFailRes == HDMI_FRL_TRAIN_FAIL_FFECHANGE)
                {
                    FrlTxFFESet(pstHdmiDev);
                    enTrainStatus = HDMI_FRL_TRAIN_STEP_TRAIN_START;
                    pstFrlInfo->u32FailCount = 0;
                }
                else if (pstTrainStatus->enTrainFailRes == HDMI_FRL_TRAIN_FAIL_RATECHANGE)
                {
                    enTrainStatus = HDMI_FRL_TRAIN_STEP_RATE_CHANGE;
                    pstFrlInfo->u32FailCount = 0;
                }
                else
                {
                    enTrainStatus = HDMI_FRL_TRAIN_STEP_TRAIN_START;
                    pstFrlInfo->u32FailCount++;
                    if(pstFrlInfo->u32MaxFailTimes <= pstFrlInfo->u32FailCount)
                    {
                        pstFrlInfo->u32FailCount = 0;
                        if (pstFrlInfo->u32Bypass & FRL_BYPASS_RESULT_CHECK)
                        {
                            HDMI_INFO("RESULT_CHECK bypass, goto RESULT_HANDLE!\n");
                            enTrainStatus = HDMI_FRL_TRAIN_STEP_RESULT_HANDLE;
                            break;
                        }
                        FrlTrainException(pstHdmiDev);
                    }
                }
            }

            u64StartTime  = HDMI_OSAL_GetTimeInMs();
            break;
        }
        case HDMI_FRL_TRAIN_STEP_RATE_CHANGE:
        {
            pstFrlInfo->bCTSMode = FrlIsCTSMode(pstHdmiDev);
            if (HI_SUCCESS != FrlGetCurRate(pstFrlInfo))
            {
                FrlTrainException(pstHdmiDev);
                return;
            }

            FrlPhySet(pstHdmiDev);
            FrlSetTrainRate(pstHdmiDev);

            enTrainStatus = HDMI_FRL_TRAIN_STEP_TRAIN_START;
            u64StartTime  = HDMI_OSAL_GetTimeInMs();
            break;
        }
        case HDMI_FRL_TRAIN_STEP_RESULT_HANDLE:
        {
            do
            {
                if (HI_TRUE == FrlGetFltStart(pstHdmiDev))
                {
                    if (pstFrlInfo->bStart)
                    {
                        pstFrlInfo->bWorkEn = HI_TRUE;
                        FrlEnableOutput(pstHdmiDev, pstFrlInfo->bWorkEn);
                        FrlSetFltStart(pstHdmiDev, HI_TRUE);

                        u32TimeOut = 0;
                        enTrainStatus = HDMI_FRL_TRAIN_STEP_RETRAIN_CHECK;
                        break;
                    }
                }
                else if (HI_TRUE == FrlGetFltUpdate(pstHdmiDev))
                {
                    u32TimeOut = 0;
                    FrlSetFltUpdate(pstHdmiDev, HI_TRUE);
                    enTrainStatus = HDMI_FRL_TRAIN_STEP_TRAIN_START;
                    break;
                }

                if ((HDMI_OSAL_GetTimeInMs() - u64StartTime) > pstMachInfo->u32WaitHandleMs)
                {
                    u32TimeOut++;
                    break;
                }

                HDMI_UDELAY(2000);
            }while(1);

            u64StartTime = HDMI_OSAL_GetTimeInMs();

            if (u32TimeOut >= 3)
            {
                HDMI_ERR("Training timeout!\n");
                u32TimeOut = 0;
                FrlTrainException(pstHdmiDev);
                return;
            }

            break;
        }
        case HDMI_FRL_TRAIN_STEP_RETRAIN_CHECK:
        {
            if ((HDMI_OSAL_GetTimeInMs() - u64StartTime) > pstMachInfo->u32WaitRetrainMs)
            {
                if (HI_TRUE == FrlGetFltUpdate(pstHdmiDev))
                {
                    FrlSetFltUpdate(pstHdmiDev, HI_TRUE);
                    pstFrlInfo->bWorkEn = HI_FALSE;
                    FrlEnableOutput(pstHdmiDev, pstFrlInfo->bWorkEn);
                    enTrainStatus = HDMI_FRL_TRAIN_STEP_TRAIN_START;
                    u64StartTime = HDMI_OSAL_GetTimeInMs();
                }
                else
                {
                    u64StartTime = HDMI_OSAL_GetTimeInMs();
                }
            }
            break;
        }
        case HDMI_FRL_TRAIN_STEP_STOP:
        {
            pstFrlInfo->bWorkEn = HI_FALSE;
            FrlEnableOutput(pstHdmiDev, pstFrlInfo->bWorkEn);
            u64StartTime  = HDMI_OSAL_GetTimeInMs();
            enTrainStatus = HDMI_FRL_TRAIN_STEP_BUTT;
            break;
        }
        case HDMI_FRL_TRAIN_STEP_BUTT:
        default:
            break;
    }

    pstMachInfo->u64StartTime  = u64StartTime;
    pstMachInfo->enTrainStatus = enTrainStatus;

    return;
}

HI_BOOL DFMCalculate(HDMI_FRL_INFO_S* pstFrlInfo, HDMI_ATTR_S* pstAttr)
{
    HDMI_VO_ATTR_S              *pstVoAttr   = HI_NULL;
    HDMI_AO_ATTR_S              *pstAoAttr   = HI_NULL;
    HDMI_APP_ATTR_S             *pstAppAttr  = HI_NULL;
    HDMI_VIDEO_DEF_S            *pstVideoDef = HI_NULL;
    HI_BOOL                     b3DEnable    = HI_FALSE;
    DFM_IN_S                    stDFMIn      = {0};
    HI_U8                       u8MaxRate    = 0;
    HI_BOOL                     bCapable     = HI_FALSE;

    FRL_CHECK_POINTER_RET(pstFrlInfo);
    FRL_CHECK_POINTER_RET(pstAttr);

    pstVoAttr = &pstAttr->stVOAttr;
    pstAoAttr  = &pstAttr->stAOAttr;
    pstAppAttr = &pstAttr->stAppAttr;
    u8MaxRate = pstFrlInfo->stRateInfo.u8MaxRate;

    b3DEnable = (HDMI_3D_BUTT == pstVoAttr->enStereoMode) ? HI_FALSE : HI_TRUE;

    pstVideoDef = FrlGetFormatParam(pstVoAttr->enVideoTiming,
                                    pstVoAttr->enPictureAspect, b3DEnable);

    FRL_CHECK_POINTER_RET(pstVideoDef);

    HDMI_MEMSET(&stDFMIn, 0, sizeof(DFM_IN_S));

    HDMI_INFO("enVideoCode: %d\n", pstVideoDef->enVideoCode);
    pstFrlInfo->u32TmdsClk = pstVoAttr->u32HdmiAdaptPixClk;

    FrlDFMConstruct(&stDFMIn, pstAoAttr, pstAppAttr, pstVideoDef);

    if (u8MaxRate > 6)
    {
        bCapable = HI_FALSE;
        goto RET;
    }

    GET_FRLRATE_INFO(pstFrlInfo->stRateInfo.u8CurRate, stDFMIn.s32BitRate, stDFMIn.s32LaneNum);

    if (DRV_HDMI_DFMFormatCanbeSupport(&stDFMIn) == HI_TRUE)
    {
        bCapable = HI_TRUE;
    }
    else
    {
        bCapable = HI_FALSE;
    }

    HDMI_ERR("This fmt can %s be trans\n", (bCapable == HI_TRUE) ? "" : "not");

RET:

    return bCapable;
}

HI_S32 DRV_HDMI_FrlModeChange(HDMI_DEVICE_ID_E enHdmiID, HDMI_FRL_DEBUG_S *pstDebug)
{
    HI_S32                   s32Ret         = HI_SUCCESS;
    HDMI_FRL_INFO_S         *pstFrlInfo     = HI_NULL;
    HDMI_DEVICE_S           *pstHdmiDev     = HI_NULL;
    HDMI_FRL_TRAIN_CONFIG_S  stTrainConfig  = {0};

    FRL_CHECK_POINTER_RET(pstDebug);

    pstHdmiDev = GetHdmiDevice(enHdmiID);
    FRL_CHECK_POINTER_RET(pstHdmiDev);
    pstFrlInfo = &pstHdmiDev->stFrlInfo;

    HDMI_MEMSET(&stTrainConfig, 0, sizeof(HDMI_FRL_TRAIN_CONFIG_S));

    pstHdmiDev->stFrlInfo.enMode = pstDebug->enHdmiMode;

    if (HDMI_FRL_MODE_FRL == pstDebug->enHdmiMode)
    {
        pstFrlInfo->stRateInfo.u8CurRate = pstDebug->enRate;

        /* DFM */
        pstFrlInfo->stRateInfo.u8MaxRate = FRL_WORK_MODE_4L12G;
        if (HI_FALSE == DFMCalculate(pstFrlInfo, &(pstHdmiDev->stAttr)))
        {
            HDMI_ERR("Can not trans\n");
            return HI_FAILURE;
        }

        stTrainConfig.u8FrlRate = pstDebug->enRate;
        stTrainConfig.u8FFELevels = FRL_TXFFE_MODE_3;
        stTrainConfig.bFrlNoTimeOut = HI_FALSE;

        stTrainConfig.stTimer.u32FltStepTimeOut = 0;
        stTrainConfig.stTimer.u32FltTimeOut = FLT_TIMEOUT;
        stTrainConfig.stTimer.u32FltUpdateTimeOut = FLT_UPDATE_TIMEOUT;
        stTrainConfig.stTimer.u32FltWaitConfigMs = 100;
        stTrainConfig.stTimer.u32FltWaitResultMs = 300;
        stTrainConfig.enTrainSel = pstFrlInfo->enTrainSel;

        HDMI_HAL_CALL(HAL_HDMI_FrlTrainConfig, &stTrainConfig);

        FrlPhySet(pstHdmiDev);  /* phy config */
        /* LM config & Channel config */
        HDMI_HAL_CALL(HAL_HDMI_Debug, HDMI_DEBUG_CMD_FRL, &stTrainConfig.u8FrlRate);
        HDMI_HAL_CALL(HAL_HDMI_FrlEnable,  HI_TRUE);/* enable worken */
    }
    else
    {
        /* TMDS mode */
        FrlPhySet(pstHdmiDev);
    }

    return s32Ret;
}

