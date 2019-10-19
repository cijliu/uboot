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
#ifndef __HDMI_HAL_PHY_H__
#define __HDMI_HAL_PHY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hdmi_hal_intf.h"

typedef enum
{
    PHY_RPRE_50,
    PHY_RPRE_56,
    PHY_RPRE_71,
    PHY_RPRE_83,
    PHY_RPRE_100,
    PHY_RPRE_125,
    PHY_RPRE_250,
    PHY_RPRE_500,
    PHY_RPRE_BUTT
} PHY_RPRE_E;

typedef enum
{
    PHY_RTERM_MODE_SINGLE,
    PHY_RTERM_MODE_SOURCE,
    PHY_RTERM_MODE_LOAD,
    PHY_RTERM_MODE_BUTT
} PHY_RTERM_MODE_E;

typedef enum
{
    PHY_LINK_MODE_HI = 0x0,
    PHY_LINK_MODE_FRL
} PHY_LINK_MODE_E;
typedef enum
{
    PHY_FCON_MODE_AUTO = 0x0,
    PHY_FCON_MODE_MANUAL
} PHY_FCON_MODE_E;
/* ssc struct */
typedef struct
{
    HI_U32              u32SscAmptd; // 1/1M ppm
    HI_U32              u32SscFreq;  // 1Hz
} PHY_SSC_CFG_S;

typedef struct
{
    HI_BOOL             bSscEnable;
    HI_BOOL             bSscDebugEn;
    PHY_SSC_CFG_S       stPhySscCfg;
}HDMI_PHY_SSC_S;

typedef struct
{
    HI_U32              u32PixClk;      /* Pixel colck,in KHz */
    HI_U32              u32TmdsClk;     /* TMDS colck,in KHz */
    HDMI_DEEP_COLOR_E   enDeepColor;    /* Deep color(color depth)  */
    HDMI_PHY_SSC_S      stHDMIPhySsc;   /* Spread Spectrum ctrl(ssc) para */
}HDMI_PHY_SSC_CFG_S;

/* HW spec struct */
typedef struct
{
    HI_U32              u32IMainClk;
    HI_U32              u32IMainD0;
    HI_U32              u32IMainD1;
    HI_U32              u32IMainD2;
    HI_U32              u32IPreClk;
    HI_U32              u32IPreD0;
    HI_U32              u32IPreD1;
    HI_U32              u32IPreD2;
    PHY_RPRE_E          enRPreClk;
    PHY_RPRE_E          enRPreD0;
    PHY_RPRE_E          enRPreD1;
    PHY_RPRE_E          enRPreD2;
    PHY_RTERM_MODE_E    enRTermModeClk;
    HI_U32              u32RTermClk;
    PHY_RTERM_MODE_E    enRTermModeD0;
    HI_U32              u32RTermD0;
    PHY_RTERM_MODE_E    enRTermModeD1;
    HI_U32              u32RTermD1;
    PHY_RTERM_MODE_E    enRTermModeD2;
    HI_U32              u32RTermD2;

}PHY_HWSPEC_CFG_S;

typedef struct
{
    HI_BOOL             bHWSpecDebugEn;
    PHY_HWSPEC_CFG_S    stPhyHWSpecCfg;
}HDMI_PHY_HWSPEC_S;

typedef struct
{
    HI_U32              u32TmdsClk;     /* TMDS colck,in KHz */
    HDMI_PHY_HWSPEC_S   stHDMIPhySpec;  /* phy specification para */
}HDMI_PHY_HWSPEC_CFG_S;

/* public struct */
typedef struct
{
    HI_U32              u32PixelClk;
    HI_U32              u32TmdsClk;     /* TMDS colck,in KHz */
    HI_BOOL             bEmiEnable;
    HDMI_DEEP_COLOR_E   enDeepColor;    /* Deep color(color depth)  */
    HDMI_PHY_MODE_CFG_E enModeCfg;      /* TMDS/FRL/TxFFE */
    HDMI_TRACE_LEN_E    enTraceLen;
}HDMI_PHY_TMDS_CFG_S;

typedef struct
{
    HI_BOOL             bInit;
    HI_BOOL             bPowerEnable;
    HI_BOOL             bOeEnable;
    HDMI_PHY_TMDS_CFG_S stTmdsCfg;
    HDMI_PHY_SSC_S      stSscCfg;
    PHY_HWSPEC_CFG_S    stHWSpecCfg;
}HDMI_PHY_INFO_S;

HI_S32 HAL_HDMI_PhyInit(HDMI_HAL_INIT_S *pstHalInit);
HI_S32 HAL_HDMI_PhyDeInit(HI_VOID);

HI_S32 HAL_HDMI_PhyPowerGet(HI_BOOL *pbEnable);
HI_S32 HAL_HDMI_PhyPowerSet(HI_BOOL bEnable);

HI_S32 HAL_HDMI_PhyOeSet(HI_BOOL bEnable);
HI_S32 HAL_HDMI_PhyOeGet(HI_BOOL *pbEnable);

HI_S32 HAL_HDMI_PhyTmdsSet(HDMI_PHY_TMDS_CFG_S *pstTmdsCfg);

HI_S32 HAL_HDMI_PhySpecSet(HDMI_PHY_HWSPEC_CFG_S * pstHdmiSpecCfg);

HI_S32 HAL_HDMI_PhyInfoGet(HDMI_PHY_INFO_S *pstPhyStatus);

HI_S32 HAL_HDMI_PhySscSet(HDMI_PHY_SSC_CFG_S * pstHdmiSscCfg);
HI_S32 HAL_HDMI_PhySscGet(HI_BOOL * pbEnable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_HAL_PHY_H__ */





