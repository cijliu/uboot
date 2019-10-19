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
#ifndef __HDMI_HAL_PLATFORM_H__
#define __HDMI_HAL_PLATFORM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#if 0
typedef enum
{
    HDMI_CLK_TYPE_CRG,
    HDMI_CLK_TYPE_PHY,
}HDMI_CLK_TYPE_E;
#endif

typedef enum
{
    HDMITX_CTRL_ID_DIV_2X,
    HDMITX_CTRL_ID_DIV_4X,
    HDMITX_CTRL_ID_DIV_6X,
    HDMITX_CTRL_ID_DIV_8X,
    
}HDMI_CTRL_ID_DIV_E;



typedef enum
{
    HDMITX_CTRL_PIXEL_DIV_2X,
    HDMITX_CTRL_PIXEL_DIV_4X,
    HDMITX_CTRL_PIXEL_DIV_6X,
    HDMITX_CTRL_PIXEL_DIV_8X,

}HDMI_CTRL_PIXEL_DIV_E;


typedef struct 
{
    HDMI_CTRL_ID_DIV_E      enIdDiv;
    HDMI_CTRL_PIXEL_DIV_E   enPixelDiv;
}HDMI_CTRL_DIV_S;



HI_S32 HAL_HDMI_PlatformHwReset(HI_BOOL bReset);
HI_S32 HAL_HDMI_PlatformSwReset(HI_BOOL bReset);
HI_S32 HAL_HDMI_PlatformClkGet(HDMI_CTRL_DIV_S *pstCtrlDiv,HDMI_CTRL_PIXEL_DIV_E *penPixDiv);
HI_S32 HAL_HDMI_PlatformClkCfg(HDMI_CLK_TYPE_E enClkType);
HI_S32 HAL_HDMI_PlatformClkDiv(HDMI_CTRL_DIV_S *pstClkDiv);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_HAL_PLATFORM_H__ */   

