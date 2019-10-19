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
#ifndef __HDMI_HAL_INTF_H__
#define __HDMI_HAL_INTF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "drv_hdmi_common.h"
#include "hdmi_hal_ctrl.h"
#include "hdmi_hal_ddc.h"
#include "hdmi_hal_scdc.h"
#include "hdmi_hal_debug.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "drv_hdmi_compatibility.h"
#ifdef HDMI_HDCP_SUPPORT
#include "hdmi_hal_hdcp14.h"
#include "hdmi_hal_hdcp22.h"
#endif
#include "hdmi_hal_cec.h"
#endif



typedef struct
{
    HI_BOOL                 bInit;

    HDMI_TX_CAPABILITY_S    stTxCapability;
    HDMI_HDCP_MODE_E        enHdcpMode;
    HI_U32                  u32TmdsClk;

}HDMI_HAL_CFG_S;


typedef struct
{
    HMDI_CALLBACK           pfnEventCallback;
    HI_VOID                 *pstEventHandle;
}HDMI_HAL_EVENT_S;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif  /* __HDMI_HAL_INTF_H__ */

