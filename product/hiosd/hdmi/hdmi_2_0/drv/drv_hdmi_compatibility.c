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

#include "drv_hdmi_compatibility.h"
#include "hdmi_osal.h"

#define DEF_FILE_NAMELENGTH 32

#define COMPAT_NULL_CHK(p)  do{\
    if(HI_NULL==p)\
    {HDMI_ERR("NULL pionter!\n");return HI_FAILURE;}\
}while(0);


typedef struct{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HI_U64                       u64MsUnder340M;
    HI_U64                       u64MsOver340M;
}COMPAT_HDCP_MS_S;

typedef struct{
    HDMI_EDID_MANUFACTURE_INFO_S    stEdid;
    HDMI_VIDEO_TIMING_E             enTimming;      /* note: HDMI_VIDEO_TIMING_BUTT indicate that for all timiming compatibility config is needed to the TV.*/
    HDMI_AVMUTE_CFG_S               stAvmuteCfg;
}COMPAT_SINK_AVMUTE_S;

typedef struct
{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HDMI_VIDEO_TIMING_E          enTimming;
    HI_U32                       u32FmtDelay;
    HI_U32                       u32MuteDelay;
}COMPAT_SINK_DELAY_S;

typedef struct
{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HI_U32                       u32StopDelay;
}COMPAT_SINK_STOPDELAY_S;

static HDMI_EDID_MANUFACTURE_INFO_S s_astSinkCecUnsupport[] =
{
    /* Name[4],ProdCode,SerialNO,Week,Year */
    {   "000" ,       0,       0,   0,   0,},
};

static COMPAT_HDCP_MS_S s_astSinkHdcpMs[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},  Under340  Over340 */
    {   {"SNY" ,    51203,16843009,   1, 2015},   500,    2100},        //sony KD-65X9300D
    {   {"MEI" ,    41622,16843009,   0, 2014},  2000,    3000},        //panasonic TH-58AX800C
    {   {"GSM" ,        1,16843009,   1, 2016},   500,    6000},        //LG OLED 65B6P-C
};

static COMPAT_SINK_AVMUTE_S s_astSinkAvmute[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},                   timming,           mutePkgEn,Set(no use), bMuteClr, bMuteRpt,u32RptCnt */
    {   {"DEF" ,        0,       0,   0,    0},  HDMI_VIDEO_TIMING_BUTT             , {  HI_TRUE,  HI_TRUE,  HI_TRUE,  HI_TRUE,    17} },        //default config for all other TV have no problem.
    {   {"HEC" ,       48,       1,  35, 2010},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        // skyworth LED49EC520UA
    {   {"SAM" ,     3140,16777217,  42, 2014},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        // samsung UA48JU5900CXXZ
    {   {"SHP" ,     4452,       0, 255, 2016},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        // sharp LCD-60TX85A
    {   {"MST" ,       48,       1,   0, 2007},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },
    {   {"GSM" ,        1,16843009,   1, 2016},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },
    {   {"CHD" ,    36897,       1,  32, 2008},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        //changhong LT19629
    {   {"HEC" ,       48,       1,  28, 2016},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        //Hisense LED55EC680US
    {   {"SHP" ,    17446,       0,  255,2015},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        //SHARP LCD-60DS7008A
    {   {"SKY" ,        1,16843009,  34, 2017},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        //skywork 43M9
    {   {"HRE" ,     1691,       1,  51, 2010},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        // hair 40DH6000 skyworth 166 13F-B 127
    {   {"SKY" ,        1,16843009,   2, 2016},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        //skyworth 50M5
};

static HDMI_EDID_MANUFACTURE_INFO_S s_astSinkScdcPos[] =

{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},     */
    {"GSM" ,        1,16843009,   1, 2016},             //LG OLED 65B6P-C
};

static COMPAT_SINK_DELAY_S s_astSinkDelay[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},                   timming,          fmtDelay, muteDelay */
    //{   {"DEF" ,        0,       0,   0,    0},  HDMI_VIDEO_TIMING_BUTT             ,   500,    120},        //default config for all other TV have no problem.
    {   {"SKW" ,       48,       1,   1, 2008},  HDMI_VIDEO_TIMING_BUTT              ,   500,    900},        // SKY 24E60HR
    {   {"SKY" ,       48,       1,  10, 2010},  HDMI_VIDEO_TIMING_BUTT              ,   200,      0},
    {   {"TCL" ,        0,       0,  20, 2013},  HDMI_VIDEO_TIMING_BUTT              ,   500,    500},
};

static COMPAT_SINK_STOPDELAY_S s_astSinkStopDelay[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year}, u32StopDelay */
    //{   {"DEF" ,        0,       0,   0,    0},        0},
    {   {"SKW" ,      48,       1,          1, 2008},     1000},
    {   {"GSM" ,       1,       16843009,   1, 2011},     1000},
    {   {"LTV" ,      48,       1,          6, 2014},     1000},        // LeTV x50air
};

static HI_BOOL CompatEdidMatchChk(HDMI_EDID_MANUFACTURE_INFO_S *pstTmpManuInfo,
                            HDMI_EDID_MANUFACTURE_INFO_S *pstSinkManuInfo)
{
    HI_BOOL bMatch = HI_FALSE;

    if (  (HI_NULL == pstTmpManuInfo)
        ||(HI_NULL == pstSinkManuInfo) )
    {
        return HI_FALSE;
    }

    bMatch =  (pstTmpManuInfo->cMfrsName[0] == pstSinkManuInfo->cMfrsName[0])
                && (pstTmpManuInfo->cMfrsName[1] == pstSinkManuInfo->cMfrsName[1])
                && (pstTmpManuInfo->cMfrsName[2] == pstSinkManuInfo->cMfrsName[2])
                && (pstTmpManuInfo->cMfrsName[3] == pstSinkManuInfo->cMfrsName[3])
                && (pstTmpManuInfo->u32ProductCode == pstSinkManuInfo->u32ProductCode)
                && (pstTmpManuInfo->u32SerialNumber == pstSinkManuInfo->u32SerialNumber)
                && (pstTmpManuInfo->u32Week == pstSinkManuInfo->u32Week)
                && (pstTmpManuInfo->u32Year == pstSinkManuInfo->u32Year) ;

    return bMatch;
}

HI_BOOL DRV_HDMI_CompatCecValidCheck(HDMI_DEVICE_S *pstHdmiDev)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i=0, pstTmpManuInfo = &s_astSinkCecUnsupport[0];
            pstTmpManuInfo && pstSinkManuInfo && (i < HDMI_ARRAY_SIZE(s_astSinkCecUnsupport));
            pstTmpManuInfo++,i++)
        {
            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                HDMI_WARN("error CEC PHY ADDR,not support.\n");
                return HI_FALSE;
            }
        }
    }

    return HI_TRUE;
}


HI_S32  DRV_HDMI_CompatHdcpMsGet(HDMI_DEVICE_ID_E enHdmiId,HI_U64 *pu64WaitMs)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_HDCP_MS_S                *pstHdcpMs = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pu64WaitMs);

    /* default value */
    *pu64WaitMs = 500;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i=0, pstHdcpMs = &s_astSinkHdcpMs[0];
            pstHdcpMs && (i < HDMI_ARRAY_SIZE(s_astSinkHdcpMs));
            pstHdcpMs++, i++)
        {
            pstTmpManuInfo = &pstHdcpMs->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                *pu64WaitMs = pstHdmiDev->stAttr.stVOAttr.u32HdmiAdaptPixClk >= FMT_PIX_CLK_340000 ?
                                pstHdcpMs->u64MsOver340M : pstHdcpMs->u64MsUnder340M;
                break;
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32  DRV_HDMI_CompatAvmuteGet(HDMI_DEVICE_ID_E enHdmiId,HI_BOOL bAvmute,HDMI_AVMUTE_CFG_S *pstAvmuteCfg)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_SINK_AVMUTE_S            *pstSinkAvmute = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pstAvmuteCfg);

    /* default value */
    pstSinkAvmute = &s_astSinkAvmute[0];
    pstAvmuteCfg->bMutePkgEn    = pstSinkAvmute->stAvmuteCfg.bMutePkgEn;
    pstAvmuteCfg->bMuteSet      = bAvmute;
    pstAvmuteCfg->bMuteClr      = (!bAvmute) && pstSinkAvmute->stAvmuteCfg.bMuteClr;
    pstAvmuteCfg->bMuteRptEn    = (!bAvmute);
    pstAvmuteCfg->u32RptCnt     = pstSinkAvmute->stAvmuteCfg.u32RptCnt;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 1, pstSinkAvmute = &s_astSinkAvmute[1];
            pstSinkAvmute && (i < HDMI_ARRAY_SIZE(s_astSinkAvmute));
            pstSinkAvmute++, i++)
        {
            pstTmpManuInfo = &pstSinkAvmute->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                if ((pstHdmiDev->stAttr.stVOAttr.enVideoTiming == pstSinkAvmute->enTimming)
                    || (HDMI_VIDEO_TIMING_BUTT == pstSinkAvmute->enTimming)) //HDMI_VIDEO_TIMING_BUTT meants all timming use the same config to the TV.
                {
                    pstAvmuteCfg->bMutePkgEn    = pstSinkAvmute->stAvmuteCfg.bMutePkgEn;
                    pstAvmuteCfg->bMuteSet      = bAvmute;
                    pstAvmuteCfg->bMuteClr      = (!bAvmute) && pstSinkAvmute->stAvmuteCfg.bMuteClr;
                    pstAvmuteCfg->bMuteRptEn    = pstSinkAvmute->stAvmuteCfg.bMuteRptEn;
                    pstAvmuteCfg->u32RptCnt     = pstSinkAvmute->stAvmuteCfg.u32RptCnt;
                    break;
                }
            }
        }
    }

    return HI_SUCCESS;
}

HI_BOOL DRV_HDMI_CompatScdcInStartGet(HDMI_DEVICE_ID_E enHdmiId)
{
    HI_U32                          i = 0;
    HI_BOOL                         bInStart = HI_FALSE;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);

    /* default value */
    bInStart = HI_FALSE;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        //return HI_FALSE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 0, pstTmpManuInfo = &s_astSinkScdcPos[0];
            pstTmpManuInfo && (i < HDMI_ARRAY_SIZE(s_astSinkScdcPos));
            pstTmpManuInfo++, i++)
        {
            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                bInStart = HI_TRUE;
                break;
            }
        }
    }

    return bInStart;
}

HI_S32  DRV_HDMI_CompatDelayGet(HDMI_DEVICE_ID_E enHdmiId, HDMI_DELAY_S *pstDelay)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_SINK_DELAY_S             *pstSinkDelay = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pstDelay);

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 0, pstSinkDelay = &s_astSinkDelay[0];
            pstSinkDelay && (i < HDMI_ARRAY_SIZE(s_astSinkDelay));
            pstSinkDelay++, i++)
        {
            pstTmpManuInfo = &pstSinkDelay->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                if ((pstHdmiDev->stAttr.stVOAttr.enVideoTiming == pstSinkDelay->enTimming)
                    || (HDMI_VIDEO_TIMING_BUTT == pstSinkDelay->enTimming)) //HDMI_VIDEO_TIMING_BUTT meants all timming use the same config to the TV.
                {
                    pstDelay->u32FmtDelay  = pstSinkDelay->u32FmtDelay;
                    pstDelay->u32MuteDelay = pstSinkDelay->u32MuteDelay;
                    break;
                }
            }
        }
    }

    return HI_SUCCESS;

}

HI_S32  DRV_HDMI_CompatStopDelay(HDMI_DEVICE_ID_E enHdmiId)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_SINK_STOPDELAY_S         *pstSinkStopDelay = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 0, pstSinkStopDelay = &s_astSinkStopDelay[0];
            pstSinkStopDelay && (i < HDMI_ARRAY_SIZE(s_astSinkStopDelay));
            pstSinkStopDelay++, i++)
        {
            pstTmpManuInfo = &pstSinkStopDelay->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                HDMI_INFO("set stop delay = %dms.\n", pstSinkStopDelay->u32StopDelay);
                HDMI_MSLEEP(pstSinkStopDelay->u32StopDelay);
                break;
            }
        }
    }

    return HI_SUCCESS;

}

