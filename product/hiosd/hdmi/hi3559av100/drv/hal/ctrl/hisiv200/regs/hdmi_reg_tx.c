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
#include "hi_type.h"
#include "hdmi_reg_tx.h"
#include "hdmi_product_define.h"

/* Define the struct pointor of the module tx_hdmi_reg */
volatile S_tx_hdmi_reg_REGS_TYPE *goptx_hdmi_regAllReg = NULL;


int HDMI_TX_S_tx_hdmi_reg_REGS_TYPE_Init(HI_CHAR *pcAddr)
{
#ifdef HDMI_BUILD_IN_BOOT
    pcAddr = (HI_CHAR *)HDMI_IO_MAP(HDMI_TX_BASE_ADDR, 4);
#else
    if (HI_NULL == pcAddr)
    {
        HDMI_ERR("pcAddr is NULL!\n");
        return HI_FAILURE;
    }
#endif

    goptx_hdmi_regAllReg = (volatile S_tx_hdmi_reg_REGS_TYPE *)(pcAddr + HDMI_TX_BASE_ADDR_HDMITX);

    return HI_SUCCESS;
}

int HDMI_TX_S_tx_hdmi_reg_REGS_TYPE_DeInit(void)
{
    if (goptx_hdmi_regAllReg)
    {
        goptx_hdmi_regAllReg = HI_NULL;
    }

    return HI_SUCCESS;
}

int HDMI_AVI_PKT_HEADER_hbSet(unsigned int uhb0,unsigned int uhb1,unsigned int uhb2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_PKT_HEADER o_avi_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_PKT_HEADER.u32);
    o_avi_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_pkt_header.bits.avi_pkt_hb2 = uhb2;
    o_avi_pkt_header.bits.avi_pkt_hb1 = uhb1;
    o_avi_pkt_header.bits.avi_pkt_hb0 = uhb0;
    HDMITXRegWrite(pu32RegAddr, o_avi_pkt_header.u32);
    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT0_L_avi_pkt0_pbSet(unsigned int uavi_pkt0_pb0,unsigned int uavi_pkt0_pb1,unsigned int uavi_pkt0_pb2,unsigned int uavi_pkt0_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT0_L o_avi_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT0_L.u32);
    o_avi_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb3 = uavi_pkt0_pb3;
    o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb2 = uavi_pkt0_pb2;
    o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb1 = uavi_pkt0_pb1;
    o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb0 = uavi_pkt0_pb0;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt0_l.u32);

    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT0_H_avi_pkt0_pbSet(unsigned int uavi_pkt0_pb4,unsigned int uavi_pkt0_pb5,unsigned int uavi_pkt0_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT0_H o_avi_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT0_H.u32);
    o_avi_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt0_h.bits.avi_sub_pkt0_pb6 = uavi_pkt0_pb6;
    o_avi_sub_pkt0_h.bits.avi_sub_pkt0_pb5 = uavi_pkt0_pb5;
    o_avi_sub_pkt0_h.bits.avi_sub_pkt0_pb4 = uavi_pkt0_pb4;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt0_h.u32);

    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT1_L_avi_pkt1_pbSet(unsigned int uavi_pkt1_pb0,unsigned int uavi_pkt1_pb1,unsigned int uavi_pkt1_pb2,unsigned int uavi_pkt1_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT1_L o_avi_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT1_L.u32);
    o_avi_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb3 = uavi_pkt1_pb3;
    o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb2 = uavi_pkt1_pb2;
    o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb1 = uavi_pkt1_pb1;
    o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb0 = uavi_pkt1_pb0;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt1_l.u32);

    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT1_H_avi_pkt1_pbSet(unsigned int uavi_pkt1_pb4,unsigned int uavi_pkt1_pb5,unsigned int uavi_pkt1_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT1_H o_avi_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT1_H.u32);
    o_avi_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt1_h.bits.avi_sub_pkt1_pb6 = uavi_pkt1_pb6;
    o_avi_sub_pkt1_h.bits.avi_sub_pkt1_pb5 = uavi_pkt1_pb5;
    o_avi_sub_pkt1_h.bits.avi_sub_pkt1_pb4 = uavi_pkt1_pb4;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt1_h.u32);

    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT2_L_avi_pkt2_pbSet(unsigned int uavi_pkt2_pb0,unsigned int uavi_pkt2_pb1,unsigned int uavi_pkt2_pb2,unsigned int uavi_pkt2_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT2_L o_avi_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT2_L.u32);
    o_avi_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb3 = uavi_pkt2_pb3;
    o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb2 = uavi_pkt2_pb2;
    o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb1 = uavi_pkt2_pb1;
    o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb0 = uavi_pkt2_pb0;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt2_l.u32);

    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT2_H_avi_pkt2_pbSet(unsigned int uavi_pkt2_pb4,unsigned int uavi_pkt2_pb5,unsigned int uavi_pkt2_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT2_H o_avi_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT2_H.u32);
    o_avi_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt2_h.bits.avi_sub_pkt2_pb6 = uavi_pkt2_pb6;
    o_avi_sub_pkt2_h.bits.avi_sub_pkt2_pb5 = uavi_pkt2_pb5;
    o_avi_sub_pkt2_h.bits.avi_sub_pkt2_pb4 = uavi_pkt2_pb4;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt2_h.u32);

    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT3_L_avi_pkt3_pbSet(unsigned int uavi_pkt3_pb0,unsigned int uavi_pkt3_pb1,unsigned int uavi_pkt3_pb2,unsigned int uavi_pkt3_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT3_L o_avi_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT3_L.u32);
    o_avi_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb3 = uavi_pkt3_pb3;
    o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb2 = uavi_pkt3_pb2;
    o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb1 = uavi_pkt3_pb1;
    o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb0 = uavi_pkt3_pb0;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt3_l.u32);

    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT3_H_avi_pkt3_pbSet(unsigned int uavi_pkt3_pb4,unsigned int uavi_pkt3_pb5,unsigned int uavi_pkt3_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT3_H o_avi_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT3_H.u32);
    o_avi_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_avi_sub_pkt3_h.bits.avi_sub_pkt3_pb6 = uavi_pkt3_pb6;
    o_avi_sub_pkt3_h.bits.avi_sub_pkt3_pb5 = uavi_pkt3_pb5;
    o_avi_sub_pkt3_h.bits.avi_sub_pkt3_pb4 = uavi_pkt3_pb4;
    HDMITXRegWrite(pu32RegAddr, o_avi_sub_pkt3_h.u32);

    return HI_SUCCESS;
}
#ifndef HDMI_BUILD_IN_BOOT

//*************************************************************************************//
//********************************** Avi Infoframe Get ********************************//
//*************************************************************************************//
int HDMI_AVI_PKT_HEADER_hbGet(U_AVI_PKT_HEADER* u_avi_pkt_header)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_PKT_HEADER o_avi_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_PKT_HEADER.u32);
    o_avi_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_pkt_header->bits.avi_pkt_hb2 = o_avi_pkt_header.bits.avi_pkt_hb2;
    u_avi_pkt_header->bits.avi_pkt_hb1 = o_avi_pkt_header.bits.avi_pkt_hb1;
    u_avi_pkt_header->bits.avi_pkt_hb0 = o_avi_pkt_header.bits.avi_pkt_hb0;
    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT0_L_avi_pkt0_pbGet(U_AVI_SUB_PKT0_L* u_avi_sub_pkt0_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT0_L o_avi_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT0_L.u32);
    o_avi_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt0_l->bits.avi_sub_pkt0_pb3 = o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb3;
    u_avi_sub_pkt0_l->bits.avi_sub_pkt0_pb2 = o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb2;
    u_avi_sub_pkt0_l->bits.avi_sub_pkt0_pb1 = o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb1;
    u_avi_sub_pkt0_l->bits.avi_sub_pkt0_pb0 = o_avi_sub_pkt0_l.bits.avi_sub_pkt0_pb0;
	return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT0_H_avi_pkt0_pbGet(U_AVI_SUB_PKT0_H* u_avi_sub_pkt0_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT0_H o_avi_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT0_H.u32);
    o_avi_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt0_h->bits.avi_sub_pkt0_pb6 = o_avi_sub_pkt0_h.bits.avi_sub_pkt0_pb6;
    u_avi_sub_pkt0_h->bits.avi_sub_pkt0_pb5 = o_avi_sub_pkt0_h.bits.avi_sub_pkt0_pb5;
    u_avi_sub_pkt0_h->bits.avi_sub_pkt0_pb4 = o_avi_sub_pkt0_h.bits.avi_sub_pkt0_pb4;

	return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT1_L_avi_pkt1_pbGet(U_AVI_SUB_PKT1_L* u_avi_sub_pkt1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT1_L o_avi_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT1_L.u32);
    o_avi_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt1_l->bits.avi_sub_pkt1_pb3 = o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb3;
    u_avi_sub_pkt1_l->bits.avi_sub_pkt1_pb2 = o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb2;
    u_avi_sub_pkt1_l->bits.avi_sub_pkt1_pb1 = o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb1;
    u_avi_sub_pkt1_l->bits.avi_sub_pkt1_pb0 = o_avi_sub_pkt1_l.bits.avi_sub_pkt1_pb0;

	return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT1_H_avi_pkt1_pbGet(U_AVI_SUB_PKT1_H* u_avi_sub_pkt1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT1_H o_avi_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT1_H.u32);
    o_avi_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt1_h->bits.avi_sub_pkt1_pb6 = o_avi_sub_pkt1_h.bits.avi_sub_pkt1_pb6;
    u_avi_sub_pkt1_h->bits.avi_sub_pkt1_pb5 = o_avi_sub_pkt1_h.bits.avi_sub_pkt1_pb5;
    u_avi_sub_pkt1_h->bits.avi_sub_pkt1_pb4 = o_avi_sub_pkt1_h.bits.avi_sub_pkt1_pb4;

	return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT2_L_avi_pkt2_pbGet(U_AVI_SUB_PKT2_L* u_avi_sub_pkt2_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT2_L o_avi_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT2_L.u32);
    o_avi_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt2_l->bits.avi_sub_pkt2_pb3 = o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb3;
    u_avi_sub_pkt2_l->bits.avi_sub_pkt2_pb2 = o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb2;
    u_avi_sub_pkt2_l->bits.avi_sub_pkt2_pb1 = o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb1;
    u_avi_sub_pkt2_l->bits.avi_sub_pkt2_pb0 = o_avi_sub_pkt2_l.bits.avi_sub_pkt2_pb0;

	return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT2_H_avi_pkt2_pbGet(U_AVI_SUB_PKT2_H* u_avi_sub_pkt2_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT2_H o_avi_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT2_H.u32);
    o_avi_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt2_h->bits.avi_sub_pkt2_pb6 = o_avi_sub_pkt2_h.bits.avi_sub_pkt2_pb6;
    u_avi_sub_pkt2_h->bits.avi_sub_pkt2_pb5 = o_avi_sub_pkt2_h.bits.avi_sub_pkt2_pb5;
    u_avi_sub_pkt2_h->bits.avi_sub_pkt2_pb4 = o_avi_sub_pkt2_h.bits.avi_sub_pkt2_pb4;
	return HI_SUCCESS;

}

int HDMI_AVI_SUB_PKT3_L_avi_pkt3_pbGet(U_AVI_SUB_PKT3_L* u_avi_sub_pkt3_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT3_L o_avi_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT3_L.u32);
    o_avi_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt3_l->bits.avi_sub_pkt3_pb3 = o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb3;
    u_avi_sub_pkt3_l->bits.avi_sub_pkt3_pb2 = o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb2;
    u_avi_sub_pkt3_l->bits.avi_sub_pkt3_pb1 = o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb1;
    u_avi_sub_pkt3_l->bits.avi_sub_pkt3_pb0 = o_avi_sub_pkt3_l.bits.avi_sub_pkt3_pb0;
    return HI_SUCCESS;
}

int HDMI_AVI_SUB_PKT3_H_avi_pkt3_pbGet(U_AVI_SUB_PKT3_H* u_avi_sub_pkt3_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVI_SUB_PKT3_H o_avi_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVI_SUB_PKT3_H.u32);
    o_avi_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_avi_sub_pkt3_h->bits.avi_sub_pkt3_pb6 = o_avi_sub_pkt3_h.bits.avi_sub_pkt3_pb6;
    u_avi_sub_pkt3_h->bits.avi_sub_pkt3_pb5 = o_avi_sub_pkt3_h.bits.avi_sub_pkt3_pb5;
    u_avi_sub_pkt3_h->bits.avi_sub_pkt3_pb4 = o_avi_sub_pkt3_h.bits.avi_sub_pkt3_pb4;
    return HI_SUCCESS;
}

//*************************************************************************************//
//******************************** Audio Infoframe set ********************************//
//*************************************************************************************//



int HDMI_AUDIO_PKT_HEADER_hbSet(unsigned int uhb0,unsigned int uhb1,unsigned int uhb2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_PKT_HEADER o_audio_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_PKT_HEADER.u32);
    o_audio_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_pkt_header.bits.aif_pkt_hb2= uhb2;
    o_audio_pkt_header.bits.aif_pkt_hb1= uhb1;
    o_audio_pkt_header.bits.aif_pkt_hb0= uhb0;
    HDMITXRegWrite(pu32RegAddr, o_audio_pkt_header.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT0_L_audio_pkt0_pbSet(unsigned int uaudio_pkt0_pb0,unsigned int uaudio_pkt0_pb1,unsigned int uaudio_pkt0_pb2,unsigned int uaudio_pkt0_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT0_L o_audio_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT0_L.u32);
    o_audio_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt0_l.bits.aif_sub_pkt0_pb3 = uaudio_pkt0_pb3;
    o_audio_sub_pkt0_l.bits.aif_sub_pkt0_pb2 = uaudio_pkt0_pb2;
    o_audio_sub_pkt0_l.bits.aif_sub_pkt0_pb1 = uaudio_pkt0_pb1;
    o_audio_sub_pkt0_l.bits.aif_sub_pkt0_pb0 = uaudio_pkt0_pb0;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt0_l.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT0_H_audio_pkt0_pbSet(unsigned int uaudio_pkt0_pb4,unsigned int uaudio_pkt0_pb5,unsigned int uaudio_pkt0_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT0_H o_audio_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT0_H.u32);
    o_audio_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt0_h.bits.aif_sub_pkt0_pb6 = uaudio_pkt0_pb6;
    o_audio_sub_pkt0_h.bits.aif_sub_pkt0_pb5 = uaudio_pkt0_pb5;
    o_audio_sub_pkt0_h.bits.aif_sub_pkt0_pb4 = uaudio_pkt0_pb4;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt0_h.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT1_L_audio_pkt1_pbSet(unsigned int uaudio_pkt1_pb0,unsigned int uaudio_pkt1_pb1,unsigned int uaudio_pkt1_pb2,unsigned int uaudio_pkt1_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT1_L o_audio_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT1_L.u32);
    o_audio_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt1_l.bits.aif_sub_pkt1_pb3 = uaudio_pkt1_pb3;
    o_audio_sub_pkt1_l.bits.aif_sub_pkt1_pb2 = uaudio_pkt1_pb2;
    o_audio_sub_pkt1_l.bits.aif_sub_pkt1_pb1 = uaudio_pkt1_pb1;
    o_audio_sub_pkt1_l.bits.aif_sub_pkt1_pb0 = uaudio_pkt1_pb0;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt1_l.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT1_H_audio_pkt1_pbSet(unsigned int uaudio_pkt1_pb4,unsigned int uaudio_pkt1_pb5,unsigned int uaudio_pkt1_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT1_H o_audio_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT1_H.u32);
    o_audio_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt1_h.bits.aif_sub_pkt1_pb6 = uaudio_pkt1_pb6;
    o_audio_sub_pkt1_h.bits.aif_sub_pkt1_pb5 = uaudio_pkt1_pb5;
    o_audio_sub_pkt1_h.bits.aif_sub_pkt1_pb4 = uaudio_pkt1_pb4;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt1_h.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT2_L_audio_pkt2_pbSet(unsigned int uaudio_pkt2_pb0,unsigned int uaudio_pkt2_pb1,unsigned int uaudio_pkt2_pb2,unsigned int uaudio_pkt2_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT2_L o_audio_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT2_L.u32);
    o_audio_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt2_l.bits.aif_sub_pkt2_pb3 = uaudio_pkt2_pb3;
    o_audio_sub_pkt2_l.bits.aif_sub_pkt2_pb2 = uaudio_pkt2_pb2;
    o_audio_sub_pkt2_l.bits.aif_sub_pkt2_pb1 = uaudio_pkt2_pb1;
    o_audio_sub_pkt2_l.bits.aif_sub_pkt2_pb0 = uaudio_pkt2_pb0;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt2_l.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT2_H_audio_pkt2_pbSet(unsigned int uaudio_pkt2_pb4,unsigned int uaudio_pkt2_pb5,unsigned int uaudio_pkt2_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT2_H o_audio_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT2_H.u32);
    o_audio_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt2_h.bits.aif_sub_pkt2_pb6 = uaudio_pkt2_pb6;
    o_audio_sub_pkt2_h.bits.aif_sub_pkt2_pb5 = uaudio_pkt2_pb5;
    o_audio_sub_pkt2_h.bits.aif_sub_pkt2_pb4 = uaudio_pkt2_pb4;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt2_h.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT3_L_audio_pkt3_pbSet(unsigned int uaudio_pkt3_pb0,unsigned int uaudio_pkt3_pb1,unsigned int uaudio_pkt3_pb2,unsigned int uaudio_pkt3_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT3_L o_audio_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT3_L.u32);
    o_audio_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt3_l.bits.aif_sub_pkt3_pb3 = uaudio_pkt3_pb3;
    o_audio_sub_pkt3_l.bits.aif_sub_pkt3_pb2 = uaudio_pkt3_pb2;
    o_audio_sub_pkt3_l.bits.aif_sub_pkt3_pb1 = uaudio_pkt3_pb1;
    o_audio_sub_pkt3_l.bits.aif_sub_pkt3_pb0 = uaudio_pkt3_pb0;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt3_l.u32);

    return HI_SUCCESS;
}

int HDMI_AUDIO_SUB_PKT3_H_audio_pkt3_pbSet(unsigned int uaudio_pkt3_pb4,unsigned int uaudio_pkt3_pb5,unsigned int uaudio_pkt3_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT3_H o_audio_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT3_H.u32);
    o_audio_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_audio_sub_pkt3_h.bits.aif_sub_pkt3_pb6 = uaudio_pkt3_pb6;
    o_audio_sub_pkt3_h.bits.aif_sub_pkt3_pb5 = uaudio_pkt3_pb5;
    o_audio_sub_pkt3_h.bits.aif_sub_pkt3_pb4 = uaudio_pkt3_pb4;
    HDMITXRegWrite(pu32RegAddr, o_audio_sub_pkt3_h.u32);

    return HI_SUCCESS;
}


//*************************************************************************************//
//******************************** Audio Infoframe Get ********************************//
//*************************************************************************************//
int HDMI_AIF_PKT_HEADER_hbGet(U_AIF_PKT_HEADER* u_aif_pkt_header)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_PKT_HEADER o_aif_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_PKT_HEADER.u32);
    o_aif_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_pkt_header->bits.aif_pkt_hb2 = o_aif_pkt_header.bits.aif_pkt_hb2;
    u_aif_pkt_header->bits.aif_pkt_hb1 = o_aif_pkt_header.bits.aif_pkt_hb1;
    u_aif_pkt_header->bits.aif_pkt_hb0 = o_aif_pkt_header.bits.aif_pkt_hb0;
    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT0_L_aif_pkt0_pbGet(U_AIF_SUB_PKT0_L* u_aif_sub_pkt0_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT0_L o_aif_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT0_L.u32);
    o_aif_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt0_l->bits.aif_sub_pkt0_pb3 = o_aif_sub_pkt0_l.bits.aif_sub_pkt0_pb3;
    u_aif_sub_pkt0_l->bits.aif_sub_pkt0_pb2 = o_aif_sub_pkt0_l.bits.aif_sub_pkt0_pb2;
    u_aif_sub_pkt0_l->bits.aif_sub_pkt0_pb1 = o_aif_sub_pkt0_l.bits.aif_sub_pkt0_pb1;
    u_aif_sub_pkt0_l->bits.aif_sub_pkt0_pb0 = o_aif_sub_pkt0_l.bits.aif_sub_pkt0_pb0;

    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT0_H_aif_pkt0_pbGet(U_AIF_SUB_PKT0_H* u_aif_sub_pkt0_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT0_H o_aif_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT0_H.u32);
    o_aif_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt0_h->bits.aif_sub_pkt0_pb6 = o_aif_sub_pkt0_h.bits.aif_sub_pkt0_pb6;
    u_aif_sub_pkt0_h->bits.aif_sub_pkt0_pb5 = o_aif_sub_pkt0_h.bits.aif_sub_pkt0_pb5;
    u_aif_sub_pkt0_h->bits.aif_sub_pkt0_pb4 = o_aif_sub_pkt0_h.bits.aif_sub_pkt0_pb4;

    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT1_L_aif_pkt1_pbGet(U_AIF_SUB_PKT1_L* u_aif_sub_pkt1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT1_L o_aif_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT1_L.u32);
    o_aif_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt1_l->bits.aif_sub_pkt1_pb3 = o_aif_sub_pkt1_l.bits.aif_sub_pkt1_pb3;
    u_aif_sub_pkt1_l->bits.aif_sub_pkt1_pb2 = o_aif_sub_pkt1_l.bits.aif_sub_pkt1_pb2;
    u_aif_sub_pkt1_l->bits.aif_sub_pkt1_pb1 = o_aif_sub_pkt1_l.bits.aif_sub_pkt1_pb1;
    u_aif_sub_pkt1_l->bits.aif_sub_pkt1_pb0 = o_aif_sub_pkt1_l.bits.aif_sub_pkt1_pb0;

    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT1_H_aif_pkt1_pbGet(U_AIF_SUB_PKT1_H* u_aif_sub_pkt1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT1_H o_aif_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT1_H.u32);
    o_aif_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt1_h->bits.aif_sub_pkt1_pb6 = o_aif_sub_pkt1_h.bits.aif_sub_pkt1_pb6;
    u_aif_sub_pkt1_h->bits.aif_sub_pkt1_pb5 = o_aif_sub_pkt1_h.bits.aif_sub_pkt1_pb5;
    u_aif_sub_pkt1_h->bits.aif_sub_pkt1_pb4 = o_aif_sub_pkt1_h.bits.aif_sub_pkt1_pb4;

    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT2_L_aif_pkt2_pbGet(U_AIF_SUB_PKT2_L* u_aif_sub_pkt2_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT2_L o_aif_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT2_L.u32);
    o_aif_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt2_l->bits.aif_sub_pkt2_pb3 = o_aif_sub_pkt2_l.bits.aif_sub_pkt2_pb3;
    u_aif_sub_pkt2_l->bits.aif_sub_pkt2_pb2 = o_aif_sub_pkt2_l.bits.aif_sub_pkt2_pb2;
    u_aif_sub_pkt2_l->bits.aif_sub_pkt2_pb1 = o_aif_sub_pkt2_l.bits.aif_sub_pkt2_pb1;
    u_aif_sub_pkt2_l->bits.aif_sub_pkt2_pb0 = o_aif_sub_pkt2_l.bits.aif_sub_pkt2_pb0;

    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT2_H_aif_pkt2_pbGet(U_AIF_SUB_PKT2_H* u_aif_sub_pkt2_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT2_H o_aif_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT2_H.u32);
    o_aif_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt2_h->bits.aif_sub_pkt2_pb6 = o_aif_sub_pkt2_h.bits.aif_sub_pkt2_pb6;
    u_aif_sub_pkt2_h->bits.aif_sub_pkt2_pb5 = o_aif_sub_pkt2_h.bits.aif_sub_pkt2_pb5;
    u_aif_sub_pkt2_h->bits.aif_sub_pkt2_pb4 = o_aif_sub_pkt2_h.bits.aif_sub_pkt2_pb4;
    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT3_L_aif_pkt3_pbGet(U_AIF_SUB_PKT3_L* u_aif_sub_pkt3_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT3_L o_aif_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT3_L.u32);
    o_aif_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt3_l->bits.aif_sub_pkt3_pb3 = o_aif_sub_pkt3_l.bits.aif_sub_pkt3_pb3;
    u_aif_sub_pkt3_l->bits.aif_sub_pkt3_pb2 = o_aif_sub_pkt3_l.bits.aif_sub_pkt3_pb2;
    u_aif_sub_pkt3_l->bits.aif_sub_pkt3_pb1 = o_aif_sub_pkt3_l.bits.aif_sub_pkt3_pb1;
    u_aif_sub_pkt3_l->bits.aif_sub_pkt3_pb0 = o_aif_sub_pkt3_l.bits.aif_sub_pkt3_pb0;
    return HI_SUCCESS;
}

int HDMI_AIF_SUB_PKT3_H_aif_pkt3_pbGet(U_AIF_SUB_PKT3_H* u_aif_sub_pkt3_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AIF_SUB_PKT3_H o_aif_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AIF_SUB_PKT3_H.u32);
    o_aif_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_aif_sub_pkt3_h->bits.aif_sub_pkt3_pb6 = o_aif_sub_pkt3_h.bits.aif_sub_pkt3_pb6;
    u_aif_sub_pkt3_h->bits.aif_sub_pkt3_pb5 = o_aif_sub_pkt3_h.bits.aif_sub_pkt3_pb5;
    u_aif_sub_pkt3_h->bits.aif_sub_pkt3_pb4 = o_aif_sub_pkt3_h.bits.aif_sub_pkt3_pb4;
    return HI_SUCCESS;
}

//*************************************************************************************//
//******************************** Spif Infoframe set *********************************//
//*************************************************************************************//

#ifndef CONFIG_HDMI_BVT_SDK
int HDMI_SPIF_PKT_HEADER_hbSet(unsigned int uhb0,unsigned int uhb1,unsigned int uhb2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_PKT_HEADER o_spif_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_PKT_HEADER.u32);
    o_spif_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_pkt_header.bits.spd_pkt_hb2= uhb2;
    o_spif_pkt_header.bits.spd_pkt_hb1= uhb1;
    o_spif_pkt_header.bits.spd_pkt_hb0= uhb0;
    HDMITXRegWrite(pu32RegAddr, o_spif_pkt_header.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT0_L_spif_pkt0_pbSet(unsigned int uspif_pkt0_pb0,unsigned int uspif_pkt0_pb1,unsigned int uspif_pkt0_pb2,unsigned int uspif_pkt0_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT0_L o_spif_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT0_L.u32);
    o_spif_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb3 = uspif_pkt0_pb3;
    o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb2 = uspif_pkt0_pb2;
    o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb1 = uspif_pkt0_pb1;
    o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb0 = uspif_pkt0_pb0;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt0_l.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT0_H_spif_pkt0_pbSet(unsigned int uspif_pkt0_pb4,unsigned int uspif_pkt0_pb5,unsigned int uspif_pkt0_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT0_H o_spif_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT0_H.u32);
    o_spif_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt0_h.bits.spd_sub_pkt0_pb6 = uspif_pkt0_pb6;
    o_spif_sub_pkt0_h.bits.spd_sub_pkt0_pb5 = uspif_pkt0_pb5;
    o_spif_sub_pkt0_h.bits.spd_sub_pkt0_pb4 = uspif_pkt0_pb4;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt0_h.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT1_L_spif_pkt1_pbSet(unsigned int uspif_pkt1_pb0,unsigned int uspif_pkt1_pb1,unsigned int uspif_pkt1_pb2,unsigned int uspif_pkt1_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT1_L o_spif_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT1_L.u32);
    o_spif_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb3 = uspif_pkt1_pb3;
    o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb2 = uspif_pkt1_pb2;
    o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb1 = uspif_pkt1_pb1;
    o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb0 = uspif_pkt1_pb0;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt1_l.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT1_H_spif_pkt1_pbSet(unsigned int uspif_pkt1_pb4,unsigned int uspif_pkt1_pb5,unsigned int uspif_pkt1_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT1_H o_spif_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT1_H.u32);
    o_spif_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt1_h.bits.spd_sub_pkt1_pb6 = uspif_pkt1_pb6;
    o_spif_sub_pkt1_h.bits.spd_sub_pkt1_pb5 = uspif_pkt1_pb5;
    o_spif_sub_pkt1_h.bits.spd_sub_pkt1_pb4 = uspif_pkt1_pb4;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt1_h.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT2_L_spif_pkt2_pbSet(unsigned int uspif_pkt2_pb0,unsigned int uspif_pkt2_pb1,unsigned int uspif_pkt2_pb2,unsigned int uspif_pkt2_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT2_L o_spif_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT2_L.u32);
    o_spif_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb3 = uspif_pkt2_pb3;
    o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb2 = uspif_pkt2_pb2;
    o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb1 = uspif_pkt2_pb1;
    o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb0 = uspif_pkt2_pb0;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt2_l.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT2_H_spif_pkt2_pbSet(unsigned int uspif_pkt2_pb4,unsigned int uspif_pkt2_pb5,unsigned int uspif_pkt2_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT2_H o_spif_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT2_H.u32);
    o_spif_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt2_h.bits.spd_sub_pkt2_pb6 = uspif_pkt2_pb6;
    o_spif_sub_pkt2_h.bits.spd_sub_pkt2_pb5 = uspif_pkt2_pb5;
    o_spif_sub_pkt2_h.bits.spd_sub_pkt2_pb4 = uspif_pkt2_pb4;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt2_h.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT3_L_spif_pkt3_pbSet(unsigned int uspif_pkt3_pb0,unsigned int uspif_pkt3_pb1,unsigned int uspif_pkt3_pb2,unsigned int uspif_pkt3_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT3_L o_spif_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT3_L.u32);
    o_spif_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb3 = uspif_pkt3_pb3;
    o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb2 = uspif_pkt3_pb2;
    o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb1 = uspif_pkt3_pb1;
    o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb0 = uspif_pkt3_pb0;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt3_l.u32);

    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT3_H_spif_pkt3_pbSet(unsigned int uspif_pkt3_pb4,unsigned int uspif_pkt3_pb5,unsigned int uspif_pkt3_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT3_H o_spif_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT3_H.u32);
    o_spif_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_spif_sub_pkt3_h.bits.spd_sub_pkt3_pb6 = uspif_pkt3_pb6;
    o_spif_sub_pkt3_h.bits.spd_sub_pkt3_pb5 = uspif_pkt3_pb5;
    o_spif_sub_pkt3_h.bits.spd_sub_pkt3_pb4 = uspif_pkt3_pb4;
    HDMITXRegWrite(pu32RegAddr, o_spif_sub_pkt3_h.u32);

    return HI_SUCCESS;
}

//*************************************************************************************//
//******************************** Spd Infoframe Get **********************************//
//*************************************************************************************//
int HDMI_SPIF_PKT_HEADER_hbGet(U_SPIF_PKT_HEADER* u_spif_pkt_header)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_PKT_HEADER o_spif_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_PKT_HEADER.u32);
    o_spif_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_pkt_header->bits.spd_pkt_hb2 = o_spif_pkt_header.bits.spd_pkt_hb2;
    u_spif_pkt_header->bits.spd_pkt_hb1 = o_spif_pkt_header.bits.spd_pkt_hb1;
    u_spif_pkt_header->bits.spd_pkt_hb0 = o_spif_pkt_header.bits.spd_pkt_hb0;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT0_L_spif_pkt0_pbGet(U_SPIF_SUB_PKT0_L* u_spif_sub_pkt0_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT0_L o_spif_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT0_L.u32);
    o_spif_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt0_l->bits.spd_sub_pkt0_pb3 = o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb3;
    u_spif_sub_pkt0_l->bits.spd_sub_pkt0_pb2 = o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb2;
    u_spif_sub_pkt0_l->bits.spd_sub_pkt0_pb1 = o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb1;
    u_spif_sub_pkt0_l->bits.spd_sub_pkt0_pb0 = o_spif_sub_pkt0_l.bits.spd_sub_pkt0_pb0;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT0_H_spif_pkt0_pbGet(U_SPIF_SUB_PKT0_H* u_spif_sub_pkt0_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT0_H o_spif_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT0_H.u32);
    o_spif_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt0_h->bits.spd_sub_pkt0_pb6 = o_spif_sub_pkt0_h.bits.spd_sub_pkt0_pb6;
    u_spif_sub_pkt0_h->bits.spd_sub_pkt0_pb5 = o_spif_sub_pkt0_h.bits.spd_sub_pkt0_pb5;
    u_spif_sub_pkt0_h->bits.spd_sub_pkt0_pb4 = o_spif_sub_pkt0_h.bits.spd_sub_pkt0_pb4;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT1_L_spif_pkt1_pbGet(U_SPIF_SUB_PKT1_L* u_spif_sub_pkt1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT1_L o_spif_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT1_L.u32);
    o_spif_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt1_l->bits.spd_sub_pkt1_pb3 = o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb3;
    u_spif_sub_pkt1_l->bits.spd_sub_pkt1_pb2 = o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb2;
    u_spif_sub_pkt1_l->bits.spd_sub_pkt1_pb1 = o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb1;
    u_spif_sub_pkt1_l->bits.spd_sub_pkt1_pb0 = o_spif_sub_pkt1_l.bits.spd_sub_pkt1_pb0;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT1_H_spif_pkt1_pbGet(U_SPIF_SUB_PKT1_H* u_spif_sub_pkt1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT1_H o_spif_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT1_H.u32);
    o_spif_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt1_h->bits.spd_sub_pkt1_pb6 = o_spif_sub_pkt1_h.bits.spd_sub_pkt1_pb6;
    u_spif_sub_pkt1_h->bits.spd_sub_pkt1_pb5 = o_spif_sub_pkt1_h.bits.spd_sub_pkt1_pb5;
    u_spif_sub_pkt1_h->bits.spd_sub_pkt1_pb4 = o_spif_sub_pkt1_h.bits.spd_sub_pkt1_pb4;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT2_L_spif_pkt2_pbGet(U_SPIF_SUB_PKT2_L* u_spif_sub_pkt2_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT2_L o_spif_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT2_L.u32);
    o_spif_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt2_l->bits.spd_sub_pkt2_pb3 = o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb3;
    u_spif_sub_pkt2_l->bits.spd_sub_pkt2_pb2 = o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb2;
    u_spif_sub_pkt2_l->bits.spd_sub_pkt2_pb1 = o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb1;
    u_spif_sub_pkt2_l->bits.spd_sub_pkt2_pb0 = o_spif_sub_pkt2_l.bits.spd_sub_pkt2_pb0;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT2_H_spif_pkt2_pbGet(U_SPIF_SUB_PKT2_H* u_spif_sub_pkt2_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT2_H o_spif_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT2_H.u32);
    o_spif_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt2_h->bits.spd_sub_pkt2_pb6 = o_spif_sub_pkt2_h.bits.spd_sub_pkt2_pb6;
    u_spif_sub_pkt2_h->bits.spd_sub_pkt2_pb5 = o_spif_sub_pkt2_h.bits.spd_sub_pkt2_pb5;
    u_spif_sub_pkt2_h->bits.spd_sub_pkt2_pb4 = o_spif_sub_pkt2_h.bits.spd_sub_pkt2_pb4;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT3_L_spif_pkt3_pbGet(U_SPIF_SUB_PKT3_L* u_spif_sub_pkt3_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT3_L o_spif_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT3_L.u32);
    o_spif_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt3_l->bits.spd_sub_pkt3_pb3 = o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb3;
    u_spif_sub_pkt3_l->bits.spd_sub_pkt3_pb2 = o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb2;
    u_spif_sub_pkt3_l->bits.spd_sub_pkt3_pb1 = o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb1;
    u_spif_sub_pkt3_l->bits.spd_sub_pkt3_pb0 = o_spif_sub_pkt3_l.bits.spd_sub_pkt3_pb0;
    return HI_SUCCESS;
}

int HDMI_SPIF_SUB_PKT3_H_spif_pkt3_pbGet(U_SPIF_SUB_PKT3_H* u_spif_sub_pkt3_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_SPIF_SUB_PKT3_H o_spif_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->SPIF_SUB_PKT3_H.u32);
    o_spif_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_spif_sub_pkt3_h->bits.spd_sub_pkt3_pb6 = o_spif_sub_pkt3_h.bits.spd_sub_pkt3_pb6;
    u_spif_sub_pkt3_h->bits.spd_sub_pkt3_pb5 = o_spif_sub_pkt3_h.bits.spd_sub_pkt3_pb5;
    u_spif_sub_pkt3_h->bits.spd_sub_pkt3_pb4 = o_spif_sub_pkt3_h.bits.spd_sub_pkt3_pb4;
    return HI_SUCCESS;
}

//*************************************************************************************//
//******************************** Mpeg Infoframe Get *********************************//
//*************************************************************************************//
int HDMI_MPEG_PKT_HEADER_hbSet(unsigned int uhb0,unsigned int uhb1,unsigned int uhb2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_PKT_HEADER o_mpeg_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_PKT_HEADER.u32);
    o_mpeg_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_pkt_header.bits.mpeg_pkt_hb2= uhb2;
    o_mpeg_pkt_header.bits.mpeg_pkt_hb1= uhb1;
    o_mpeg_pkt_header.bits.mpeg_pkt_hb0= uhb0;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_pkt_header.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT0_L_mpeg_pkt0_pbSet(unsigned int umpeg_pkt0_pb0,unsigned int umpeg_pkt0_pb1,unsigned int umpeg_pkt0_pb2,unsigned int umpeg_pkt0_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT0_L o_mpeg_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT0_L.u32);
    o_mpeg_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb3 = umpeg_pkt0_pb3;
    o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb2 = umpeg_pkt0_pb2;
    o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb1 = umpeg_pkt0_pb1;
    o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb0 = umpeg_pkt0_pb0;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt0_l.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT0_H_mpeg_pkt0_pbSet(unsigned int umpeg_pkt0_pb4,unsigned int umpeg_pkt0_pb5,unsigned int umpeg_pkt0_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT0_H o_mpeg_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT0_H.u32);
    o_mpeg_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt0_h.bits.mpeg_sub_pkt0_pb6 = umpeg_pkt0_pb6;
    o_mpeg_sub_pkt0_h.bits.mpeg_sub_pkt0_pb5 = umpeg_pkt0_pb5;
    o_mpeg_sub_pkt0_h.bits.mpeg_sub_pkt0_pb4 = umpeg_pkt0_pb4;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt0_h.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT1_L_mpeg_pkt1_pbSet(unsigned int umpeg_pkt1_pb0,unsigned int umpeg_pkt1_pb1,unsigned int umpeg_pkt1_pb2,unsigned int umpeg_pkt1_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT1_L o_mpeg_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT1_L.u32);
    o_mpeg_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb3 = umpeg_pkt1_pb3;
    o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb2 = umpeg_pkt1_pb2;
    o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb1 = umpeg_pkt1_pb1;
    o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb0 = umpeg_pkt1_pb0;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt1_l.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT1_H_mpeg_pkt1_pbSet(unsigned int umpeg_pkt1_pb4,unsigned int umpeg_pkt1_pb5,unsigned int umpeg_pkt1_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT1_H o_mpeg_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT1_H.u32);
    o_mpeg_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt1_h.bits.mpeg_sub_pkt1_pb6 = umpeg_pkt1_pb6;
    o_mpeg_sub_pkt1_h.bits.mpeg_sub_pkt1_pb5 = umpeg_pkt1_pb5;
    o_mpeg_sub_pkt1_h.bits.mpeg_sub_pkt1_pb4 = umpeg_pkt1_pb4;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt1_h.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT2_L_mpeg_pkt2_pbSet(unsigned int umpeg_pkt2_pb0,unsigned int umpeg_pkt2_pb1,unsigned int umpeg_pkt2_pb2,unsigned int umpeg_pkt2_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT2_L o_mpeg_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT2_L.u32);
    o_mpeg_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb3 = umpeg_pkt2_pb3;
    o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb2 = umpeg_pkt2_pb2;
    o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb1 = umpeg_pkt2_pb1;
    o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb0 = umpeg_pkt2_pb0;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt2_l.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT2_H_mpeg_pkt2_pbSet(unsigned int umpeg_pkt2_pb4,unsigned int umpeg_pkt2_pb5,unsigned int umpeg_pkt2_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT2_H o_mpeg_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT2_H.u32);
    o_mpeg_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt2_h.bits.mpeg_sub_pkt2_pb6 = umpeg_pkt2_pb6;
    o_mpeg_sub_pkt2_h.bits.mpeg_sub_pkt2_pb5 = umpeg_pkt2_pb5;
    o_mpeg_sub_pkt2_h.bits.mpeg_sub_pkt2_pb4 = umpeg_pkt2_pb4;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt2_h.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT3_L_mpeg_pkt3_pbSet(unsigned int umpeg_pkt3_pb0,unsigned int umpeg_pkt3_pb1,unsigned int umpeg_pkt3_pb2,unsigned int umpeg_pkt3_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT3_L o_mpeg_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT3_L.u32);
    o_mpeg_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb3 = umpeg_pkt3_pb3;
    o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb2 = umpeg_pkt3_pb2;
    o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb1 = umpeg_pkt3_pb1;
    o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb0 = umpeg_pkt3_pb0;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt3_l.u32);

    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT3_H_mpeg_pkt3_pbSet(unsigned int umpeg_pkt3_pb4,unsigned int umpeg_pkt3_pb5,unsigned int umpeg_pkt3_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT3_H o_mpeg_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT3_H.u32);
    o_mpeg_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_mpeg_sub_pkt3_h.bits.mpeg_sub_pkt3_pb6 = umpeg_pkt3_pb6;
    o_mpeg_sub_pkt3_h.bits.mpeg_sub_pkt3_pb5 = umpeg_pkt3_pb5;
    o_mpeg_sub_pkt3_h.bits.mpeg_sub_pkt3_pb4 = umpeg_pkt3_pb4;
    HDMITXRegWrite(pu32RegAddr, o_mpeg_sub_pkt3_h.u32);

    return HI_SUCCESS;
}

//*************************************************************************************//
//******************************** Avi Infoframe set **********************************//
//*************************************************************************************//
int HDMI_MPEG_PKT_HEADER_hbGet(U_MPEG_PKT_HEADER* u_mpeg_pkt_header)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_PKT_HEADER o_mpeg_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_PKT_HEADER.u32);
    o_mpeg_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_pkt_header->bits.mpeg_pkt_hb2 = o_mpeg_pkt_header.bits.mpeg_pkt_hb2;
    u_mpeg_pkt_header->bits.mpeg_pkt_hb1 = o_mpeg_pkt_header.bits.mpeg_pkt_hb1;
    u_mpeg_pkt_header->bits.mpeg_pkt_hb0 = o_mpeg_pkt_header.bits.mpeg_pkt_hb0;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT0_L_mpeg_pkt0_pbGet(U_MPEG_SUB_PKT0_L* u_mpeg_sub_pkt0_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT0_L o_mpeg_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT0_L.u32);
    o_mpeg_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt0_l->bits.mpeg_sub_pkt0_pb3 = o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb3;
    u_mpeg_sub_pkt0_l->bits.mpeg_sub_pkt0_pb2 = o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb2;
    u_mpeg_sub_pkt0_l->bits.mpeg_sub_pkt0_pb1 = o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb1;
    u_mpeg_sub_pkt0_l->bits.mpeg_sub_pkt0_pb0 = o_mpeg_sub_pkt0_l.bits.mpeg_sub_pkt0_pb0;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT0_H_mpeg_pkt0_pbGet(U_MPEG_SUB_PKT0_H* u_mpeg_sub_pkt0_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT0_H o_mpeg_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT0_H.u32);
    o_mpeg_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt0_h->bits.mpeg_sub_pkt0_pb6 = o_mpeg_sub_pkt0_h.bits.mpeg_sub_pkt0_pb6;
    u_mpeg_sub_pkt0_h->bits.mpeg_sub_pkt0_pb5 = o_mpeg_sub_pkt0_h.bits.mpeg_sub_pkt0_pb5;
    u_mpeg_sub_pkt0_h->bits.mpeg_sub_pkt0_pb4 = o_mpeg_sub_pkt0_h.bits.mpeg_sub_pkt0_pb4;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT1_L_mpeg_pkt1_pbGet(U_MPEG_SUB_PKT1_L* u_mpeg_sub_pkt1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT1_L o_mpeg_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT1_L.u32);
    o_mpeg_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt1_l->bits.mpeg_sub_pkt1_pb3 = o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb3;
    u_mpeg_sub_pkt1_l->bits.mpeg_sub_pkt1_pb2 = o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb2;
    u_mpeg_sub_pkt1_l->bits.mpeg_sub_pkt1_pb1 = o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb1;
    u_mpeg_sub_pkt1_l->bits.mpeg_sub_pkt1_pb0 = o_mpeg_sub_pkt1_l.bits.mpeg_sub_pkt1_pb0;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT1_H_mpeg_pkt1_pbGet(U_MPEG_SUB_PKT1_H* u_mpeg_sub_pkt1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT1_H o_mpeg_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT1_H.u32);
    o_mpeg_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt1_h->bits.mpeg_sub_pkt1_pb6 = o_mpeg_sub_pkt1_h.bits.mpeg_sub_pkt1_pb6;
    u_mpeg_sub_pkt1_h->bits.mpeg_sub_pkt1_pb5 = o_mpeg_sub_pkt1_h.bits.mpeg_sub_pkt1_pb5;
    u_mpeg_sub_pkt1_h->bits.mpeg_sub_pkt1_pb4 = o_mpeg_sub_pkt1_h.bits.mpeg_sub_pkt1_pb4;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT2_L_mpeg_pkt2_pbGet(U_MPEG_SUB_PKT2_L* u_mpeg_sub_pkt2_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT2_L o_mpeg_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT2_L.u32);
    o_mpeg_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt2_l->bits.mpeg_sub_pkt2_pb3 = o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb3;
    u_mpeg_sub_pkt2_l->bits.mpeg_sub_pkt2_pb2 = o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb2;
    u_mpeg_sub_pkt2_l->bits.mpeg_sub_pkt2_pb1 = o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb1;
    u_mpeg_sub_pkt2_l->bits.mpeg_sub_pkt2_pb0 = o_mpeg_sub_pkt2_l.bits.mpeg_sub_pkt2_pb0;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT2_H_mpeg_pkt2_pbGet(U_MPEG_SUB_PKT2_H* u_mpeg_sub_pkt2_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT2_H o_mpeg_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT2_H.u32);
    o_mpeg_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt2_h->bits.mpeg_sub_pkt2_pb6 = o_mpeg_sub_pkt2_h.bits.mpeg_sub_pkt2_pb6;
    u_mpeg_sub_pkt2_h->bits.mpeg_sub_pkt2_pb5 = o_mpeg_sub_pkt2_h.bits.mpeg_sub_pkt2_pb5;
    u_mpeg_sub_pkt2_h->bits.mpeg_sub_pkt2_pb4 = o_mpeg_sub_pkt2_h.bits.mpeg_sub_pkt2_pb4;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT3_L_mpeg_pkt3_pbGet(U_MPEG_SUB_PKT3_L* u_mpeg_sub_pkt3_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT3_L o_mpeg_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT3_L.u32);
    o_mpeg_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt3_l->bits.mpeg_sub_pkt3_pb3 = o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb3;
    u_mpeg_sub_pkt3_l->bits.mpeg_sub_pkt3_pb2 = o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb2;
    u_mpeg_sub_pkt3_l->bits.mpeg_sub_pkt3_pb1 = o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb1;
    u_mpeg_sub_pkt3_l->bits.mpeg_sub_pkt3_pb0 = o_mpeg_sub_pkt3_l.bits.mpeg_sub_pkt3_pb0;
    return HI_SUCCESS;
}

int HDMI_MPEG_SUB_PKT3_H_mpeg_pkt3_pbGet(U_MPEG_SUB_PKT3_H* u_mpeg_sub_pkt3_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_MPEG_SUB_PKT3_H o_mpeg_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->MPEG_SUB_PKT3_H.u32);
    o_mpeg_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_mpeg_sub_pkt3_h->bits.mpeg_sub_pkt3_pb6 = o_mpeg_sub_pkt3_h.bits.mpeg_sub_pkt3_pb6;
    u_mpeg_sub_pkt3_h->bits.mpeg_sub_pkt3_pb5 = o_mpeg_sub_pkt3_h.bits.mpeg_sub_pkt3_pb5;
    u_mpeg_sub_pkt3_h->bits.mpeg_sub_pkt3_pb4 = o_mpeg_sub_pkt3_h.bits.mpeg_sub_pkt3_pb4;
    return HI_SUCCESS;
}
#endif

//*************************************************************************************//
//********************************  Gen  Infoframe set ********************************//
//*************************************************************************************//
int HDMI_GEN_PKT_HEADER_hbSet(unsigned int uhb0,unsigned int uhb1,unsigned int uhb2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_PKT_HEADER o_gen_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_PKT_HEADER.u32);
    o_gen_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_pkt_header.bits.gen_pkt_hb2= uhb2;
    o_gen_pkt_header.bits.gen_pkt_hb1= uhb1;
    o_gen_pkt_header.bits.gen_pkt_hb0= uhb0;
    HDMITXRegWrite(pu32RegAddr, o_gen_pkt_header.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT0_L_gen_pkt0_pbSet(unsigned int ugen_pkt0_pb0,unsigned int ugen_pkt0_pb1,unsigned int ugen_pkt0_pb2,unsigned int ugen_pkt0_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT0_L o_gen_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT0_L.u32);
    o_gen_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb3 = ugen_pkt0_pb3;
    o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb2 = ugen_pkt0_pb2;
    o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb1 = ugen_pkt0_pb1;
    o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb0 = ugen_pkt0_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt0_l.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT0_H_gen_pkt0_pbSet(unsigned int ugen_pkt0_pb4,unsigned int ugen_pkt0_pb5,unsigned int ugen_pkt0_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT0_H o_gen_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT0_H.u32);
    o_gen_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt0_h.bits.gen_sub_pkt0_pb6 = ugen_pkt0_pb6;
    o_gen_sub_pkt0_h.bits.gen_sub_pkt0_pb5 = ugen_pkt0_pb5;
    o_gen_sub_pkt0_h.bits.gen_sub_pkt0_pb4 = ugen_pkt0_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt0_h.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT1_L_gen_pkt1_pbSet(unsigned int ugen_pkt1_pb0,unsigned int ugen_pkt1_pb1,unsigned int ugen_pkt1_pb2,unsigned int ugen_pkt1_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT1_L o_gen_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT1_L.u32);
    o_gen_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb3 = ugen_pkt1_pb3;
    o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb2 = ugen_pkt1_pb2;
    o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb1 = ugen_pkt1_pb1;
    o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb0 = ugen_pkt1_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt1_l.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT1_H_gen_pkt1_pbSet(unsigned int ugen_pkt1_pb4,unsigned int ugen_pkt1_pb5,unsigned int ugen_pkt1_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT1_H o_gen_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT1_H.u32);
    o_gen_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt1_h.bits.gen_sub_pkt1_pb6 = ugen_pkt1_pb6;
    o_gen_sub_pkt1_h.bits.gen_sub_pkt1_pb5 = ugen_pkt1_pb5;
    o_gen_sub_pkt1_h.bits.gen_sub_pkt1_pb4 = ugen_pkt1_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt1_h.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT2_L_gen_pkt2_pbSet(unsigned int ugen_pkt2_pb0,unsigned int ugen_pkt2_pb1,unsigned int ugen_pkt2_pb2,unsigned int ugen_pkt2_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT2_L o_gen_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT2_L.u32);
    o_gen_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb3 = ugen_pkt2_pb3;
    o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb2 = ugen_pkt2_pb2;
    o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb1 = ugen_pkt2_pb1;
    o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb0 = ugen_pkt2_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt2_l.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT2_H_gen_pkt2_pbSet(unsigned int ugen_pkt2_pb4,unsigned int ugen_pkt2_pb5,unsigned int ugen_pkt2_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT2_H o_gen_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT2_H.u32);
    o_gen_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt2_h.bits.gen_sub_pkt2_pb6 = ugen_pkt2_pb6;
    o_gen_sub_pkt2_h.bits.gen_sub_pkt2_pb5 = ugen_pkt2_pb5;
    o_gen_sub_pkt2_h.bits.gen_sub_pkt2_pb4 = ugen_pkt2_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt2_h.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT3_L_gen_pkt3_pbSet(unsigned int ugen_pkt3_pb0,unsigned int ugen_pkt3_pb1,unsigned int ugen_pkt3_pb2,unsigned int ugen_pkt3_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT3_L o_gen_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT3_L.u32);
    o_gen_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb3 = ugen_pkt3_pb3;
    o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb2 = ugen_pkt3_pb2;
    o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb1 = ugen_pkt3_pb1;
    o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb0 = ugen_pkt3_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt3_l.u32);

    return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT3_H_gen_pkt3_pbSet(unsigned int ugen_pkt3_pb4,unsigned int ugen_pkt3_pb5,unsigned int ugen_pkt3_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT3_H o_gen_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT3_H.u32);
    o_gen_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gen_sub_pkt3_h.bits.gen_sub_pkt3_pb6 = ugen_pkt3_pb6;
    o_gen_sub_pkt3_h.bits.gen_sub_pkt3_pb5 = ugen_pkt3_pb5;
    o_gen_sub_pkt3_h.bits.gen_sub_pkt3_pb4 = ugen_pkt3_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gen_sub_pkt3_h.u32);

    return HI_SUCCESS;
}


//*************************************************************************************//
//********************************  Gen Infoframe Get *********************************//
//*************************************************************************************//
int HDMI_GEN_PKT_HEADER_hbGet(U_GEN_PKT_HEADER* u_gen_pkt_header)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_PKT_HEADER o_gen_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_PKT_HEADER.u32);
    o_gen_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_pkt_header->bits.gen_pkt_hb2 = o_gen_pkt_header.bits.gen_pkt_hb2;
    u_gen_pkt_header->bits.gen_pkt_hb1 = o_gen_pkt_header.bits.gen_pkt_hb1;
    u_gen_pkt_header->bits.gen_pkt_hb0 = o_gen_pkt_header.bits.gen_pkt_hb0;
	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT0_L_gen_pkt0_pbGet(U_GEN_SUB_PKT0_L* u_gen_sub_pkt0_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT0_L o_gen_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT0_L.u32);
    o_gen_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt0_l->bits.gen_sub_pkt0_pb3 = o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb3;
    u_gen_sub_pkt0_l->bits.gen_sub_pkt0_pb2 = o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb2;
    u_gen_sub_pkt0_l->bits.gen_sub_pkt0_pb1 = o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb1;
    u_gen_sub_pkt0_l->bits.gen_sub_pkt0_pb0 = o_gen_sub_pkt0_l.bits.gen_sub_pkt0_pb0;
	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT0_H_gen_pkt0_pbGet(U_GEN_SUB_PKT0_H* u_gen_sub_pkt0_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT0_H o_gen_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT0_H.u32);
    o_gen_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt0_h->bits.gen_sub_pkt0_pb6 = o_gen_sub_pkt0_h.bits.gen_sub_pkt0_pb6;
    u_gen_sub_pkt0_h->bits.gen_sub_pkt0_pb5 = o_gen_sub_pkt0_h.bits.gen_sub_pkt0_pb5;
    u_gen_sub_pkt0_h->bits.gen_sub_pkt0_pb4 = o_gen_sub_pkt0_h.bits.gen_sub_pkt0_pb4;

	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT1_L_gen_pkt1_pbGet(U_GEN_SUB_PKT1_L* u_gen_sub_pkt1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT1_L o_gen_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT1_L.u32);
    o_gen_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt1_l->bits.gen_sub_pkt1_pb3 = o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb3;
    u_gen_sub_pkt1_l->bits.gen_sub_pkt1_pb2 = o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb2;
    u_gen_sub_pkt1_l->bits.gen_sub_pkt1_pb1 = o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb1;
    u_gen_sub_pkt1_l->bits.gen_sub_pkt1_pb0 = o_gen_sub_pkt1_l.bits.gen_sub_pkt1_pb0;

	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT1_H_gen_pkt1_pbGet(U_GEN_SUB_PKT1_H* u_gen_sub_pkt1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT1_H o_gen_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT1_H.u32);
    o_gen_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt1_h->bits.gen_sub_pkt1_pb6 = o_gen_sub_pkt1_h.bits.gen_sub_pkt1_pb6;
    u_gen_sub_pkt1_h->bits.gen_sub_pkt1_pb5 = o_gen_sub_pkt1_h.bits.gen_sub_pkt1_pb5;
    u_gen_sub_pkt1_h->bits.gen_sub_pkt1_pb4 = o_gen_sub_pkt1_h.bits.gen_sub_pkt1_pb4;

	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT2_L_gen_pkt2_pbGet(U_GEN_SUB_PKT2_L* u_gen_sub_pkt2_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT2_L o_gen_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT2_L.u32);
    o_gen_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt2_l->bits.gen_sub_pkt2_pb3 = o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb3;
    u_gen_sub_pkt2_l->bits.gen_sub_pkt2_pb2 = o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb2;
    u_gen_sub_pkt2_l->bits.gen_sub_pkt2_pb1 = o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb1;
    u_gen_sub_pkt2_l->bits.gen_sub_pkt2_pb0 = o_gen_sub_pkt2_l.bits.gen_sub_pkt2_pb0;

	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT2_H_gen_pkt2_pbGet(U_GEN_SUB_PKT2_H* u_gen_sub_pkt2_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT2_H o_gen_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT2_H.u32);
    o_gen_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt2_h->bits.gen_sub_pkt2_pb6 = o_gen_sub_pkt2_h.bits.gen_sub_pkt2_pb6;
    u_gen_sub_pkt2_h->bits.gen_sub_pkt2_pb5 = o_gen_sub_pkt2_h.bits.gen_sub_pkt2_pb5;
    u_gen_sub_pkt2_h->bits.gen_sub_pkt2_pb4 = o_gen_sub_pkt2_h.bits.gen_sub_pkt2_pb4;

	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT3_L_gen_pkt3_pbGet(U_GEN_SUB_PKT3_L* u_gen_sub_pkt3_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT3_L o_gen_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT3_L.u32);
    o_gen_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt3_l->bits.gen_sub_pkt3_pb3 = o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb3;
    u_gen_sub_pkt3_l->bits.gen_sub_pkt3_pb2 = o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb2;
    u_gen_sub_pkt3_l->bits.gen_sub_pkt3_pb1 = o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb1;
    u_gen_sub_pkt3_l->bits.gen_sub_pkt3_pb0 = o_gen_sub_pkt3_l.bits.gen_sub_pkt3_pb0;

	return HI_SUCCESS;
}

int HDMI_GEN_SUB_PKT3_H_gen_pkt3_pbGet(U_GEN_SUB_PKT3_H* u_gen_sub_pkt3_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GEN_SUB_PKT3_H o_gen_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GEN_SUB_PKT3_H.u32);
    o_gen_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gen_sub_pkt3_h->bits.gen_sub_pkt3_pb6 = o_gen_sub_pkt3_h.bits.gen_sub_pkt3_pb6;
    u_gen_sub_pkt3_h->bits.gen_sub_pkt3_pb5 = o_gen_sub_pkt3_h.bits.gen_sub_pkt3_pb5;
    u_gen_sub_pkt3_h->bits.gen_sub_pkt3_pb4 = o_gen_sub_pkt3_h.bits.gen_sub_pkt3_pb4;

	return HI_SUCCESS;
}
//*************************************************************************************//
//********************************  Gamut Infoframe set *******************************//
//*************************************************************************************//
#ifndef CONFIG_HDMI_BVT_SDK
int HDMI_GAMUT_PKT_HEADER_hbSet(unsigned int uhb0,unsigned int uhb1,unsigned int uhb2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_PKT_HEADER o_gamut_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_PKT_HEADER.u32);
    o_gamut_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_pkt_header.bits.gamut_pkt_hb2= uhb2;
    o_gamut_pkt_header.bits.gamut_pkt_hb1= uhb1;
    o_gamut_pkt_header.bits.gamut_pkt_hb0= uhb0;
    HDMITXRegWrite(pu32RegAddr, o_gamut_pkt_header.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT0_L_gamut_pkt0_pbSet(unsigned int ugamut_pkt0_pb0,unsigned int ugamut_pkt0_pb1,unsigned int ugamut_pkt0_pb2,unsigned int ugamut_pkt0_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT0_L o_gamut_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT0_L.u32);
    o_gamut_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb3 = ugamut_pkt0_pb3;
    o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb2 = ugamut_pkt0_pb2;
    o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb1 = ugamut_pkt0_pb1;
    o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb0 = ugamut_pkt0_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt0_l.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT0_H_gamut_pkt0_pbSet(unsigned int ugamut_pkt0_pb4,unsigned int ugamut_pkt0_pb5,unsigned int ugamut_pkt0_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT0_H o_gamut_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT0_H.u32);
    o_gamut_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt0_h.bits.gamut_sub_pkt0_pb6 = ugamut_pkt0_pb6;
    o_gamut_sub_pkt0_h.bits.gamut_sub_pkt0_pb5 = ugamut_pkt0_pb5;
    o_gamut_sub_pkt0_h.bits.gamut_sub_pkt0_pb4 = ugamut_pkt0_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt0_h.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT1_L_gamut_pkt1_pbSet(unsigned int ugamut_pkt1_pb0,unsigned int ugamut_pkt1_pb1,unsigned int ugamut_pkt1_pb2,unsigned int ugamut_pkt1_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT1_L o_gamut_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT1_L.u32);
    o_gamut_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb3 = ugamut_pkt1_pb3;
    o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb2 = ugamut_pkt1_pb2;
    o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb1 = ugamut_pkt1_pb1;
    o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb0 = ugamut_pkt1_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt1_l.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT1_H_gamut_pkt1_pbSet(unsigned int ugamut_pkt1_pb4,unsigned int ugamut_pkt1_pb5,unsigned int ugamut_pkt1_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT1_H o_gamut_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT1_H.u32);
    o_gamut_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt1_h.bits.gamut_sub_pkt1_pb6 = ugamut_pkt1_pb6;
    o_gamut_sub_pkt1_h.bits.gamut_sub_pkt1_pb5 = ugamut_pkt1_pb5;
    o_gamut_sub_pkt1_h.bits.gamut_sub_pkt1_pb4 = ugamut_pkt1_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt1_h.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT2_L_gamut_pkt2_pbSet(unsigned int ugamut_pkt2_pb0,unsigned int ugamut_pkt2_pb1,unsigned int ugamut_pkt2_pb2,unsigned int ugamut_pkt2_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT2_L o_gamut_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT2_L.u32);
    o_gamut_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb3 = ugamut_pkt2_pb3;
    o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb2 = ugamut_pkt2_pb2;
    o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb1 = ugamut_pkt2_pb1;
    o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb0 = ugamut_pkt2_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt2_l.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT2_H_gamut_pkt2_pbSet(unsigned int ugamut_pkt2_pb4,unsigned int ugamut_pkt2_pb5,unsigned int ugamut_pkt2_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT2_H o_gamut_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT2_H.u32);
    o_gamut_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt2_h.bits.gamut_sub_pkt2_pb6 = ugamut_pkt2_pb6;
    o_gamut_sub_pkt2_h.bits.gamut_sub_pkt2_pb5 = ugamut_pkt2_pb5;
    o_gamut_sub_pkt2_h.bits.gamut_sub_pkt2_pb4 = ugamut_pkt2_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt2_h.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT3_L_gamut_pkt3_pbSet(unsigned int ugamut_pkt3_pb0,unsigned int ugamut_pkt3_pb1,unsigned int ugamut_pkt3_pb2,unsigned int ugamut_pkt3_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT3_L o_gamut_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT3_L.u32);
    o_gamut_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb3 = ugamut_pkt3_pb3;
    o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb2 = ugamut_pkt3_pb2;
    o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb1 = ugamut_pkt3_pb1;
    o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb0 = ugamut_pkt3_pb0;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt3_l.u32);

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT3_H_gamut_pkt3_pbSet(unsigned int ugamut_pkt3_pb4,unsigned int ugamut_pkt3_pb5,unsigned int ugamut_pkt3_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT3_H o_gamut_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT3_H.u32);
    o_gamut_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_gamut_sub_pkt3_h.bits.gamut_sub_pkt3_pb6 = ugamut_pkt3_pb6;
    o_gamut_sub_pkt3_h.bits.gamut_sub_pkt3_pb5 = ugamut_pkt3_pb5;
    o_gamut_sub_pkt3_h.bits.gamut_sub_pkt3_pb4 = ugamut_pkt3_pb4;
    HDMITXRegWrite(pu32RegAddr, o_gamut_sub_pkt3_h.u32);

    return HI_SUCCESS;
}
#endif

//*************************************************************************************//
//********************************  Gamut Infoframe Get *******************************//
//*************************************************************************************//
int HDMI_GAMUT_PKT_HEADER_hbGet(U_GAMUT_PKT_HEADER* u_gamut_pkt_header)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_PKT_HEADER o_gamut_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_PKT_HEADER.u32);
    o_gamut_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_pkt_header->bits.gamut_pkt_hb2 = o_gamut_pkt_header.bits.gamut_pkt_hb2;
    u_gamut_pkt_header->bits.gamut_pkt_hb1 = o_gamut_pkt_header.bits.gamut_pkt_hb1;
    u_gamut_pkt_header->bits.gamut_pkt_hb0 = o_gamut_pkt_header.bits.gamut_pkt_hb0;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT0_L_gamut_pkt0_pbGet(U_GAMUT_SUB_PKT0_L* u_gamut_sub_pkt0_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT0_L o_gamut_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT0_L.u32);
    o_gamut_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt0_l->bits.gamut_sub_pkt0_pb3 = o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb3;
    u_gamut_sub_pkt0_l->bits.gamut_sub_pkt0_pb2 = o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb2;
    u_gamut_sub_pkt0_l->bits.gamut_sub_pkt0_pb1 = o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb1;
    u_gamut_sub_pkt0_l->bits.gamut_sub_pkt0_pb0 = o_gamut_sub_pkt0_l.bits.gamut_sub_pkt0_pb0;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT0_H_gamut_pkt0_pbGet(U_GAMUT_SUB_PKT0_H* u_gamut_sub_pkt0_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT0_H o_gamut_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT0_H.u32);
    o_gamut_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt0_h->bits.gamut_sub_pkt0_pb6 = o_gamut_sub_pkt0_h.bits.gamut_sub_pkt0_pb6;
    u_gamut_sub_pkt0_h->bits.gamut_sub_pkt0_pb5 = o_gamut_sub_pkt0_h.bits.gamut_sub_pkt0_pb5;
    u_gamut_sub_pkt0_h->bits.gamut_sub_pkt0_pb4 = o_gamut_sub_pkt0_h.bits.gamut_sub_pkt0_pb4;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT1_L_gamut_pkt1_pbGet(U_GAMUT_SUB_PKT1_L* u_gamut_sub_pkt1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT1_L o_gamut_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT1_L.u32);
    o_gamut_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt1_l->bits.gamut_sub_pkt1_pb3 = o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb3;
    u_gamut_sub_pkt1_l->bits.gamut_sub_pkt1_pb2 = o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb2;
    u_gamut_sub_pkt1_l->bits.gamut_sub_pkt1_pb1 = o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb1;
    u_gamut_sub_pkt1_l->bits.gamut_sub_pkt1_pb0 = o_gamut_sub_pkt1_l.bits.gamut_sub_pkt1_pb0;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT1_H_gamut_pkt1_pbGet(U_GAMUT_SUB_PKT1_H* u_gamut_sub_pkt1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT1_H o_gamut_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT1_H.u32);
    o_gamut_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt1_h->bits.gamut_sub_pkt1_pb6 = o_gamut_sub_pkt1_h.bits.gamut_sub_pkt1_pb6;
    u_gamut_sub_pkt1_h->bits.gamut_sub_pkt1_pb5 = o_gamut_sub_pkt1_h.bits.gamut_sub_pkt1_pb5;
    u_gamut_sub_pkt1_h->bits.gamut_sub_pkt1_pb4 = o_gamut_sub_pkt1_h.bits.gamut_sub_pkt1_pb4;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT2_L_gamut_pkt2_pbGet(U_GAMUT_SUB_PKT2_L* u_gamut_sub_pkt2_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT2_L o_gamut_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT2_L.u32);
    o_gamut_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt2_l->bits.gamut_sub_pkt2_pb3 = o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb3;
    u_gamut_sub_pkt2_l->bits.gamut_sub_pkt2_pb2 = o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb2;
    u_gamut_sub_pkt2_l->bits.gamut_sub_pkt2_pb1 = o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb1;
    u_gamut_sub_pkt2_l->bits.gamut_sub_pkt2_pb0 = o_gamut_sub_pkt2_l.bits.gamut_sub_pkt2_pb0;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT2_H_gamut_pkt2_pbGet(U_GAMUT_SUB_PKT2_H* u_gamut_sub_pkt2_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT2_H o_gamut_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT2_H.u32);
    o_gamut_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt2_h->bits.gamut_sub_pkt2_pb6 = o_gamut_sub_pkt2_h.bits.gamut_sub_pkt2_pb6;
    u_gamut_sub_pkt2_h->bits.gamut_sub_pkt2_pb5 = o_gamut_sub_pkt2_h.bits.gamut_sub_pkt2_pb5;
    u_gamut_sub_pkt2_h->bits.gamut_sub_pkt2_pb4 = o_gamut_sub_pkt2_h.bits.gamut_sub_pkt2_pb4;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT3_L_gamut_pkt3_pbGet(U_GAMUT_SUB_PKT3_L* u_gamut_sub_pkt3_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT3_L o_gamut_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT3_L.u32);
    o_gamut_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt3_l->bits.gamut_sub_pkt3_pb3 = o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb3;
    u_gamut_sub_pkt3_l->bits.gamut_sub_pkt3_pb2 = o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb2;
    u_gamut_sub_pkt3_l->bits.gamut_sub_pkt3_pb1 = o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb1;
    u_gamut_sub_pkt3_l->bits.gamut_sub_pkt3_pb0 = o_gamut_sub_pkt3_l.bits.gamut_sub_pkt3_pb0;

    return HI_SUCCESS;
}

int HDMI_GAMUT_SUB_PKT3_H_gamut_pkt3_pbGet(U_GAMUT_SUB_PKT3_H* u_gamut_sub_pkt3_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_GAMUT_SUB_PKT3_H o_gamut_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->GAMUT_SUB_PKT3_H.u32);
    o_gamut_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_gamut_sub_pkt3_h->bits.gamut_sub_pkt3_pb6 = o_gamut_sub_pkt3_h.bits.gamut_sub_pkt3_pb6;
    u_gamut_sub_pkt3_h->bits.gamut_sub_pkt3_pb5 = o_gamut_sub_pkt3_h.bits.gamut_sub_pkt3_pb5;
    u_gamut_sub_pkt3_h->bits.gamut_sub_pkt3_pb4 = o_gamut_sub_pkt3_h.bits.gamut_sub_pkt3_pb4;

    return HI_SUCCESS;
}
#endif

//*************************************************************************************//
//********************************  Vsif Infoframe set ********************************//
//*************************************************************************************//
int HDMI_VSIF_PKT_HEADER_hbSet(unsigned int uhb0,unsigned int uhb1,unsigned int uhb2)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_PKT_HEADER o_vsif_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_PKT_HEADER.u32);
    o_vsif_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_pkt_header.bits.vsif_pkt_hb2= uhb2;
    o_vsif_pkt_header.bits.vsif_pkt_hb1= uhb1;
    o_vsif_pkt_header.bits.vsif_pkt_hb0= uhb0;
    HDMITXRegWrite(pu32RegAddr, o_vsif_pkt_header.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT0_L_vsif_pkt0_pbSet(unsigned int uvsif_pkt0_pb0,unsigned int uvsif_pkt0_pb1,unsigned int uvsif_pkt0_pb2,unsigned int uvsif_pkt0_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT0_L o_vsif_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT0_L.u32);
    o_vsif_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb3 = uvsif_pkt0_pb3;
    o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb2 = uvsif_pkt0_pb2;
    o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb1 = uvsif_pkt0_pb1;
    o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb0 = uvsif_pkt0_pb0;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt0_l.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT0_H_vsif_pkt0_pbSet(unsigned int uvsif_pkt0_pb4,unsigned int uvsif_pkt0_pb5,unsigned int uvsif_pkt0_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT0_H o_vsif_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT0_H.u32);
    o_vsif_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt0_h.bits.vsif_sub_pkt0_pb6 = uvsif_pkt0_pb6;
    o_vsif_sub_pkt0_h.bits.vsif_sub_pkt0_pb5 = uvsif_pkt0_pb5;
    o_vsif_sub_pkt0_h.bits.vsif_sub_pkt0_pb4 = uvsif_pkt0_pb4;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt0_h.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT1_L_vsif_pkt1_pbSet(unsigned int uvsif_pkt1_pb0,unsigned int uvsif_pkt1_pb1,unsigned int uvsif_pkt1_pb2,unsigned int uvsif_pkt1_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT1_L o_vsif_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT1_L.u32);
    o_vsif_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb3 = uvsif_pkt1_pb3;
    o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb2 = uvsif_pkt1_pb2;
    o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb1 = uvsif_pkt1_pb1;
    o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb0 = uvsif_pkt1_pb0;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt1_l.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT1_H_vsif_pkt1_pbSet(unsigned int uvsif_pkt1_pb4,unsigned int uvsif_pkt1_pb5,unsigned int uvsif_pkt1_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT1_H o_vsif_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT1_H.u32);
    o_vsif_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt1_h.bits.vsif_sub_pkt1_pb6 = uvsif_pkt1_pb6;
    o_vsif_sub_pkt1_h.bits.vsif_sub_pkt1_pb5 = uvsif_pkt1_pb5;
    o_vsif_sub_pkt1_h.bits.vsif_sub_pkt1_pb4 = uvsif_pkt1_pb4;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt1_h.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT2_L_vsif_pkt2_pbSet(unsigned int uvsif_pkt2_pb0,unsigned int uvsif_pkt2_pb1,unsigned int uvsif_pkt2_pb2,unsigned int uvsif_pkt2_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT2_L o_vsif_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT2_L.u32);
    o_vsif_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb3 = uvsif_pkt2_pb3;
    o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb2 = uvsif_pkt2_pb2;
    o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb1 = uvsif_pkt2_pb1;
    o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb0 = uvsif_pkt2_pb0;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt2_l.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT2_H_vsif_pkt2_pbSet(unsigned int uvsif_pkt2_pb4,unsigned int uvsif_pkt2_pb5,unsigned int uvsif_pkt2_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT2_H o_vsif_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT2_H.u32);
    o_vsif_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt2_h.bits.vsif_sub_pkt2_pb6 = uvsif_pkt2_pb6;
    o_vsif_sub_pkt2_h.bits.vsif_sub_pkt2_pb5 = uvsif_pkt2_pb5;
    o_vsif_sub_pkt2_h.bits.vsif_sub_pkt2_pb4 = uvsif_pkt2_pb4;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt2_h.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT3_L_vsif_pkt3_pbSet(unsigned int uvsif_pkt3_pb0,unsigned int uvsif_pkt3_pb1,unsigned int uvsif_pkt3_pb2,unsigned int uvsif_pkt3_pb3)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT3_L o_vsif_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT3_L.u32);
    o_vsif_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb3 = uvsif_pkt3_pb3;
    o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb2 = uvsif_pkt3_pb2;
    o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb1 = uvsif_pkt3_pb1;
    o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb0 = uvsif_pkt3_pb0;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt3_l.u32);

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT3_H_vsif_pkt3_pbSet(unsigned int uvsif_pkt3_pb4,unsigned int uvsif_pkt3_pb5,unsigned int uvsif_pkt3_pb6)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT3_H o_vsif_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT3_H.u32);
    o_vsif_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    o_vsif_sub_pkt3_h.bits.vsif_sub_pkt3_pb6 = uvsif_pkt3_pb6;
    o_vsif_sub_pkt3_h.bits.vsif_sub_pkt3_pb5 = uvsif_pkt3_pb5;
    o_vsif_sub_pkt3_h.bits.vsif_sub_pkt3_pb4 = uvsif_pkt3_pb4;
    HDMITXRegWrite(pu32RegAddr, o_vsif_sub_pkt3_h.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_AVI_CFG_cea_avi_rpt_enSet
//  Description : Set the value of the member CEA_AVI_CFG.cea_avi_rpt_en
//  Input       : unsigned int ucea_avi_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_AVI_CFG_cea_avi_rpt_enSet(unsigned int ucea_avi_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_AVI_CFG o_cea_avi_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_AVI_CFG.u32);
    o_cea_avi_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_avi_cfg.bits.cea_avi_rpt_en = ucea_avi_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_avi_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_AVI_CFG_cea_avi_enSet
//  Description : Set the value of the member CEA_AVI_CFG.cea_avi_en
//  Input       : unsigned int ucea_avi_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_AVI_CFG_cea_avi_enSet(unsigned int ucea_avi_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_AVI_CFG o_cea_avi_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_AVI_CFG.u32);
    o_cea_avi_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_avi_cfg.bits.cea_avi_en = ucea_avi_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_avi_cfg.u32);

    return HI_SUCCESS;
}


#ifndef HDMI_BUILD_IN_BOOT

//*************************************************************************************//
//********************************  Vsif Infoframe Get ********************************//
//*************************************************************************************//
int HDMI_VSIF_PKT_HEADER_hbGet(U_VSIF_PKT_HEADER* u_vsif_pkt_header)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_PKT_HEADER o_vsif_pkt_header;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_PKT_HEADER.u32);
    o_vsif_pkt_header.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_pkt_header->bits.vsif_pkt_hb2 = o_vsif_pkt_header.bits.vsif_pkt_hb2;
    u_vsif_pkt_header->bits.vsif_pkt_hb1 = o_vsif_pkt_header.bits.vsif_pkt_hb1;
    u_vsif_pkt_header->bits.vsif_pkt_hb0 = o_vsif_pkt_header.bits.vsif_pkt_hb0;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT0_L_vsif_pkt0_pbGet(U_VSIF_SUB_PKT0_L* u_vsif_sub_pkt0_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT0_L o_vsif_sub_pkt0_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT0_L.u32);
    o_vsif_sub_pkt0_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt0_l->bits.vsif_sub_pkt0_pb3 = o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb3;
    u_vsif_sub_pkt0_l->bits.vsif_sub_pkt0_pb2 = o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb2;
    u_vsif_sub_pkt0_l->bits.vsif_sub_pkt0_pb1 = o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb1;
    u_vsif_sub_pkt0_l->bits.vsif_sub_pkt0_pb0 = o_vsif_sub_pkt0_l.bits.vsif_sub_pkt0_pb0;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT0_H_vsif_pkt0_pbGet(U_VSIF_SUB_PKT0_H* u_vsif_sub_pkt0_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT0_H o_vsif_sub_pkt0_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT0_H.u32);
    o_vsif_sub_pkt0_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt0_h->bits.vsif_sub_pkt0_pb6 = o_vsif_sub_pkt0_h.bits.vsif_sub_pkt0_pb6;
    u_vsif_sub_pkt0_h->bits.vsif_sub_pkt0_pb5 = o_vsif_sub_pkt0_h.bits.vsif_sub_pkt0_pb5;
    u_vsif_sub_pkt0_h->bits.vsif_sub_pkt0_pb4 = o_vsif_sub_pkt0_h.bits.vsif_sub_pkt0_pb4;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT1_L_vsif_pkt1_pbGet(U_VSIF_SUB_PKT1_L* u_vsif_sub_pkt1_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT1_L o_vsif_sub_pkt1_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT1_L.u32);
    o_vsif_sub_pkt1_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt1_l->bits.vsif_sub_pkt1_pb3 = o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb3;
    u_vsif_sub_pkt1_l->bits.vsif_sub_pkt1_pb2 = o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb2;
    u_vsif_sub_pkt1_l->bits.vsif_sub_pkt1_pb1 = o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb1;
    u_vsif_sub_pkt1_l->bits.vsif_sub_pkt1_pb0 = o_vsif_sub_pkt1_l.bits.vsif_sub_pkt1_pb0;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT1_H_vsif_pkt1_pbGet(U_VSIF_SUB_PKT1_H* u_vsif_sub_pkt1_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT1_H o_vsif_sub_pkt1_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT1_H.u32);
    o_vsif_sub_pkt1_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt1_h->bits.vsif_sub_pkt1_pb6 = o_vsif_sub_pkt1_h.bits.vsif_sub_pkt1_pb6;
    u_vsif_sub_pkt1_h->bits.vsif_sub_pkt1_pb5 = o_vsif_sub_pkt1_h.bits.vsif_sub_pkt1_pb5;
    u_vsif_sub_pkt1_h->bits.vsif_sub_pkt1_pb4 = o_vsif_sub_pkt1_h.bits.vsif_sub_pkt1_pb4;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT2_L_vsif_pkt2_pbGet(U_VSIF_SUB_PKT2_L* u_vsif_sub_pkt2_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT2_L o_vsif_sub_pkt2_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT2_L.u32);
    o_vsif_sub_pkt2_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt2_l->bits.vsif_sub_pkt2_pb3 = o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb3;
    u_vsif_sub_pkt2_l->bits.vsif_sub_pkt2_pb2 = o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb2;
    u_vsif_sub_pkt2_l->bits.vsif_sub_pkt2_pb1 = o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb1;
    u_vsif_sub_pkt2_l->bits.vsif_sub_pkt2_pb0 = o_vsif_sub_pkt2_l.bits.vsif_sub_pkt2_pb0;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT2_H_vsif_pkt2_pbGet(U_VSIF_SUB_PKT2_H* u_vsif_sub_pkt2_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT2_H o_vsif_sub_pkt2_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT2_H.u32);
    o_vsif_sub_pkt2_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt2_h->bits.vsif_sub_pkt2_pb6 = o_vsif_sub_pkt2_h.bits.vsif_sub_pkt2_pb6;
    u_vsif_sub_pkt2_h->bits.vsif_sub_pkt2_pb5 = o_vsif_sub_pkt2_h.bits.vsif_sub_pkt2_pb5;
    u_vsif_sub_pkt2_h->bits.vsif_sub_pkt2_pb4 = o_vsif_sub_pkt2_h.bits.vsif_sub_pkt2_pb4;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT3_L_vsif_pkt3_pbGet(U_VSIF_SUB_PKT3_L* u_vsif_sub_pkt3_l)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT3_L o_vsif_sub_pkt3_l;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT3_L.u32);
    o_vsif_sub_pkt3_l.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt3_l->bits.vsif_sub_pkt3_pb3 = o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb3;
    u_vsif_sub_pkt3_l->bits.vsif_sub_pkt3_pb2 = o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb2;
    u_vsif_sub_pkt3_l->bits.vsif_sub_pkt3_pb1 = o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb1;
    u_vsif_sub_pkt3_l->bits.vsif_sub_pkt3_pb0 = o_vsif_sub_pkt3_l.bits.vsif_sub_pkt3_pb0;

    return HI_SUCCESS;
}

int HDMI_VSIF_SUB_PKT3_H_vsif_pkt3_pbGet(U_VSIF_SUB_PKT3_H* u_vsif_sub_pkt3_h)
{
    HI_U32 *pu32RegAddr = NULL;
    U_VSIF_SUB_PKT3_H o_vsif_sub_pkt3_h;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->VSIF_SUB_PKT3_H.u32);
    o_vsif_sub_pkt3_h.u32 = HDMITXRegRead(pu32RegAddr);
    u_vsif_sub_pkt3_h->bits.vsif_sub_pkt3_pb6 = o_vsif_sub_pkt3_h.bits.vsif_sub_pkt3_pb6;
    u_vsif_sub_pkt3_h->bits.vsif_sub_pkt3_pb5 = o_vsif_sub_pkt3_h.bits.vsif_sub_pkt3_pb5;
    u_vsif_sub_pkt3_h->bits.vsif_sub_pkt3_pb4 = o_vsif_sub_pkt3_h.bits.vsif_sub_pkt3_pb4;

    return HI_SUCCESS;
}








//******************************************************************************
//  Function    : HDMI_CEA_SPF_CFG_cea_spf_rpt_enSet
//  Description : Set the value of the member CEA_SPF_CFG.cea_spf_rpt_en
//  Input       : unsigned int ucea_spf_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
#ifndef CONFIG_HDMI_BVT_SDK
int HDMI_CEA_SPF_CFG_cea_spf_rpt_enSet(unsigned int ucea_spf_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_SPF_CFG o_cea_spf_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_SPF_CFG.u32);
    o_cea_spf_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_spf_cfg.bits.cea_spf_rpt_en = ucea_spf_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_spf_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_SPF_CFG_cea_spf_enSet
//  Description : Set the value of the member CEA_SPF_CFG.cea_spf_en
//  Input       : unsigned int ucea_spf_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_SPF_CFG_cea_spf_enSet(unsigned int ucea_spf_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_SPF_CFG o_cea_spf_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_SPF_CFG.u32);
    o_cea_spf_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_spf_cfg.bits.cea_spf_en = ucea_spf_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_spf_cfg.u32);

    return HI_SUCCESS;
}
#endif

//******************************************************************************
//  Function    : HDMI_CEA_AUD_CFG_cea_aud_rpt_enSet
//  Description : Set the value of the member CEA_AUD_CFG.cea_aud_rpt_en
//  Input       : unsigned int ucea_aud_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_AUD_CFG_cea_aud_rpt_enSet(unsigned int ucea_aud_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_AUD_CFG o_cea_aud_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_AUD_CFG.u32);
    o_cea_aud_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_aud_cfg.bits.cea_aud_rpt_en = ucea_aud_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_aud_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_AUD_CFG_cea_aud_enSet
//  Description : Set the value of the member CEA_AUD_CFG.cea_aud_en
//  Input       : unsigned int ucea_aud_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_AUD_CFG_cea_aud_enSet(unsigned int ucea_aud_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_AUD_CFG o_cea_aud_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_AUD_CFG.u32);
    o_cea_aud_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_aud_cfg.bits.cea_aud_en = ucea_aud_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_aud_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_MPEG_CFG_cea_mpeg_rpt_enSet
//  Description : Set the value of the member CEA_MPEG_CFG.cea_mpeg_rpt_en
//  Input       : unsigned int ucea_mpeg_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
#ifndef CONFIG_HDMI_BVT_SDK
int HDMI_CEA_MPEG_CFG_cea_mpeg_rpt_enSet(unsigned int ucea_mpeg_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_MPEG_CFG o_cea_mpeg_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_MPEG_CFG.u32);
    o_cea_mpeg_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_mpeg_cfg.bits.cea_mpeg_rpt_en = ucea_mpeg_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_mpeg_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_MPEG_CFG_cea_mpeg_enSet
//  Description : Set the value of the member CEA_MPEG_CFG.cea_mpeg_en
//  Input       : unsigned int ucea_mpeg_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_MPEG_CFG_cea_mpeg_enSet(unsigned int ucea_mpeg_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_MPEG_CFG o_cea_mpeg_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_MPEG_CFG.u32);
    o_cea_mpeg_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_mpeg_cfg.bits.cea_mpeg_en = ucea_mpeg_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_mpeg_cfg.u32);

    return HI_SUCCESS;
}
#endif

//******************************************************************************
//  Function    : HDMI_CEA_GEN_CFG_cea_gen_rpt_enSet
//  Description : Set the value of the member CEA_GEN_CFG.cea_gen_rpt_en
//  Input       : unsigned int ucea_gen_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_GEN_CFG_cea_gen_rpt_enSet(unsigned int ucea_gen_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_GEN_CFG o_cea_gen_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_GEN_CFG.u32);
    o_cea_gen_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_gen_cfg.bits.cea_gen_rpt_en = ucea_gen_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_gen_cfg.u32);

    return HI_SUCCESS;
}
#endif
//******************************************************************************
//  Function    : HDMI_CEA_GEN_CFG_cea_gen_enSet
//  Description : Set the value of the member CEA_GEN_CFG.cea_gen_en
//  Input       : unsigned int ucea_gen_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_GEN_CFG_cea_gen_enSet(unsigned int ucea_gen_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_GEN_CFG o_cea_gen_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_GEN_CFG.u32);
    o_cea_gen_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_gen_cfg.bits.cea_gen_en = ucea_gen_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_gen_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_CP_CFG_cea_cp_rpt_cntSet
//  Description : Set the value of the member CEA_CP_CFG.cea_cp_rpt_en
//  Input       : unsigned int cea_cp_rpt_cnt: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_CP_CFG_cea_cp_rpt_cntSet(unsigned int ucea_cp_rpt_cnt)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_CP_CFG o_cea_cp_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_CP_CFG.u32);
    o_cea_cp_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_cp_cfg.bits.cea_cp_rpt_cnt = ucea_cp_rpt_cnt;
    HDMITXRegWrite(pu32RegAddr, o_cea_cp_cfg.u32);

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : HDMI_CEA_CP_CFG_cea_cp_rpt_enSet
//  Description : Set the value of the member CEA_CP_CFG.cea_cp_rpt_en
//  Input       : unsigned int ucea_cp_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_CP_CFG_cea_cp_rpt_enSet(unsigned int ucea_cp_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_CP_CFG o_cea_cp_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_CP_CFG.u32);
    o_cea_cp_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_cp_cfg.bits.cea_cp_rpt_en = ucea_cp_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_cp_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_CP_CFG_cea_cp_enSet
//  Description : Set the value of the member CEA_CP_CFG.cea_cp_en
//  Input       : unsigned int ucea_cp_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_CP_CFG_cea_cp_enSet(unsigned int ucea_cp_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_CP_CFG o_cea_cp_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_CP_CFG.u32);
    o_cea_cp_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_cp_cfg.bits.cea_cp_en = ucea_cp_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_cp_cfg.u32);

    return HI_SUCCESS;
}

#ifndef HDMI_BUILD_IN_BOOT

//******************************************************************************
//  Function    : HDMI_CEA_GAMUT_CFG_cea_gamut_rpt_enSet
//  Description : Set the value of the member CEA_GAMUT_CFG.cea_gamut_rpt_en
//  Input       : unsigned int ucea_gamut_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_GAMUT_CFG_cea_gamut_rpt_enSet(unsigned int ucea_gamut_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_GAMUT_CFG o_cea_gamut_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_GAMUT_CFG.u32);
    o_cea_gamut_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_gamut_cfg.bits.cea_gamut_rpt_en = ucea_gamut_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_gamut_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_GAMUT_CFG_cea_gamut_enSet
//  Description : Set the value of the member CEA_GAMUT_CFG.cea_gamut_en
//  Input       : unsigned int ucea_gamut_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_GAMUT_CFG_cea_gamut_enSet(unsigned int ucea_gamut_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_GAMUT_CFG o_cea_gamut_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_GAMUT_CFG.u32);
    o_cea_gamut_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_gamut_cfg.bits.cea_gamut_en = ucea_gamut_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_gamut_cfg.u32);

    return HI_SUCCESS;
}
#endif
//******************************************************************************
//  Function    : HDMI_CEA_VSIF_CFG_cea_vsif_rpt_enSet
//  Description : Set the value of the member CEA_VSIF_CFG.cea_vsif_rpt_en
//  Input       : unsigned int ucea_vsif_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_VSIF_CFG_cea_vsif_rpt_enSet(unsigned int ucea_vsif_rpt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_VSIF_CFG o_cea_vsif_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_VSIF_CFG.u32);
    o_cea_vsif_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_vsif_cfg.bits.cea_vsif_rpt_en = ucea_vsif_rpt_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_vsif_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_VSIF_CFG_cea_vsif_enSet
//  Description : Set the value of the member CEA_VSIF_CFG.cea_vsif_en
//  Input       : unsigned int ucea_vsif_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_VSIF_CFG_cea_vsif_enSet(unsigned int ucea_vsif_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_VSIF_CFG o_cea_vsif_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_VSIF_CFG.u32);
    o_cea_vsif_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    o_cea_vsif_cfg.bits.cea_vsif_en = ucea_vsif_en;
    HDMITXRegWrite(pu32RegAddr, o_cea_vsif_cfg.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AVMIXER_CONFIG_dc_pkt_enSet
//  Description : Set the value of the member AVMIXER_CONFIG.dc_pkt_en
//  Input       : unsigned int udc_pkt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AVMIXER_CONFIG_dc_pkt_enSet(unsigned int udc_pkt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVMIXER_CONFIG o_avmixer_config;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVMIXER_CONFIG.u32);
    o_avmixer_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_avmixer_config.bits.dc_pkt_en = udc_pkt_en;
    HDMITXRegWrite(pu32RegAddr, o_avmixer_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_AVMIXER_CONFIG_hdmi_modeSet
//  Description : Set the value of the member AVMIXER_CONFIG.hdmi_mode
//  Input       : unsigned int uhdmi_mode: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AVMIXER_CONFIG_hdmi_modeSet(unsigned int uhdmi_mode)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVMIXER_CONFIG o_avmixer_config;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVMIXER_CONFIG.u32);
    o_avmixer_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_avmixer_config.bits.hdmi_mode = uhdmi_mode;
    HDMITXRegWrite(pu32RegAddr, o_avmixer_config.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CP_PKT_AVMUTE_cp_clr_avmuteSet
//  Description : Set the value of the member CP_PKT_AVMUTE.cp_clr_avmute
//  Input       : unsigned int ucp_clr_avmute: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CP_PKT_AVMUTE_cp_clr_avmuteSet(unsigned int ucp_clr_avmute)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CP_PKT_AVMUTE o_cp_pkt_avmute;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CP_PKT_AVMUTE.u32);
    o_cp_pkt_avmute.u32 = HDMITXRegRead(pu32RegAddr);
    o_cp_pkt_avmute.bits.cp_clr_avmute = ucp_clr_avmute;
    HDMITXRegWrite(pu32RegAddr, o_cp_pkt_avmute.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CP_PKT_AVMUTE_cp_set_avmuteSet
//  Description : Set the value of the member CP_PKT_AVMUTE.cp_set_avmute
//  Input       : unsigned int ucp_set_avmute: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CP_PKT_AVMUTE_cp_set_avmuteSet(unsigned int ucp_set_avmute)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CP_PKT_AVMUTE o_cp_pkt_avmute;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CP_PKT_AVMUTE.u32);
    o_cp_pkt_avmute.u32 = HDMITXRegRead(pu32RegAddr);
    o_cp_pkt_avmute.bits.cp_set_avmute = ucp_set_avmute;
    HDMITXRegWrite(pu32RegAddr, o_cp_pkt_avmute.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDMI_ENC_CTRL_enc_bypassSet
//  Description : Set the value of the member HDMI_ENC_CTRL.enc_bypass
//  Input       : unsigned int uenc_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDMI_ENC_CTRL_enc_bypassSet(unsigned int uenc_bypass)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HDMI_ENC_CTRL o_hdmi_enc_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->HDMI_ENC_CTRL.u32);
    o_hdmi_enc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_enc_ctrl.bits.enc_bypass = uenc_bypass;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_enc_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDMI_ENC_CTRL_enc_scr_onSet
//  Description : Set the value of the member HDMI_ENC_CTRL.enc_scr_on
//  Input       : unsigned int uenc_scr_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDMI_ENC_CTRL_enc_scr_onSet(unsigned int uenc_scr_on)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HDMI_ENC_CTRL o_hdmi_enc_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->HDMI_ENC_CTRL.u32);
    o_hdmi_enc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_enc_ctrl.bits.enc_scr_on = uenc_scr_on;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_enc_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_HDMI_ENC_CTRL_enc_hdmi2_onSet
//  Description : Set the value of the member HDMI_ENC_CTRL.enc_hdmi2_on
//  Input       : unsigned int uenc_hdmi2_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDMI_ENC_CTRL_enc_hdmi2_onSet(unsigned int uenc_hdmi2_on)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HDMI_ENC_CTRL o_hdmi_enc_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->HDMI_ENC_CTRL.u32);
    o_hdmi_enc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_enc_ctrl.bits.enc_hdmi2_on = uenc_hdmi2_on;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_enc_ctrl.u32);

    return HI_SUCCESS;
}

//******************************************************************************
//  Function    : HDMI_CEA_AVI_CFG_cea_avi_enGet
//  Description : Set the value of the member CEA_AVI_CFG.cea_avi_en
//  Input       : unsigned int ucea_avi_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_AVI_CFG_cea_avi_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_AVI_CFG o_cea_avi_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_AVI_CFG.u32);
    o_cea_avi_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_avi_cfg.bits.cea_avi_en;
}


#ifndef HDMI_BUILD_IN_BOOT
//******************************************************************************
//  Function    : HDMI_CEA_SPF_CFG_cea_spf_enGet
//  Description : Set the value of the member CEA_SPF_CFG.cea_spf_en
//  Input       : unsigned int ucea_spf_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
#ifndef CONFIG_HDMI_BVT_SDK
int HDMI_CEA_SPF_CFG_cea_spf_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_SPF_CFG o_cea_spf_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_SPF_CFG.u32);
    o_cea_spf_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_spf_cfg.bits.cea_spf_en;
}
#endif

//******************************************************************************
//  Function    : HDMI_CEA_AUD_CFG_cea_aud_enGet
//  Description : Set the value of the member CEA_AUD_CFG.cea_aud_en
//  Input       : unsigned int ucea_aud_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_AUD_CFG_cea_aud_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_AUD_CFG o_cea_aud_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_AUD_CFG.u32);
    o_cea_aud_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_aud_cfg.bits.cea_aud_en;
}

//******************************************************************************
//  Function    : HDMI_CEA_MPEG_CFG_cea_mpeg_enGet
//  Description : Set the value of the member CEA_MPEG_CFG.cea_mpeg_en
//  Input       : unsigned int ucea_mpeg_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
#ifndef CONFIG_HDMI_BVT_SDK
int HDMI_CEA_MPEG_CFG_cea_mpeg_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_MPEG_CFG o_cea_mpeg_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_MPEG_CFG.u32);
    o_cea_mpeg_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_mpeg_cfg.bits.cea_mpeg_en;
}
#endif

//******************************************************************************
//  Function    : HDMI_CEA_GEN_CFG_cea_gen_enGet
//  Description : Set the value of the member CEA_GEN_CFG.cea_gen_en
//  Input       : unsigned int ucea_gen_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_GEN_CFG_cea_gen_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_GEN_CFG o_cea_gen_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_GEN_CFG.u32);
    o_cea_gen_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_gen_cfg.bits.cea_gen_en;
}
#endif


//******************************************************************************
//  Function    : HDMI_CEA_CP_CFG_cea_cp_rpt_enGet
//  Description : Set the value of the member CEA_CP_CFG.cea_cp_rpt_en
//  Input       : unsigned int ucea_cp_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_CP_CFG_cea_cp_rpt_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_CP_CFG o_cea_cp_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_CP_CFG.u32);
    o_cea_cp_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_cp_cfg.bits.cea_cp_rpt_en;
}

#ifndef HDMI_BUILD_IN_BOOT
//******************************************************************************
//  Function    : HDMI_CEA_GAMUT_CFG_cea_gamut_enGet
//  Description : Set the value of the member CEA_GAMUT_CFG.cea_gamut_en
//  Input       : unsigned int ucea_gamut_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_GAMUT_CFG_cea_gamut_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_GAMUT_CFG o_cea_gamut_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_GAMUT_CFG.u32);
    o_cea_gamut_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_gamut_cfg.bits.cea_gamut_en;
}

//******************************************************************************
//  Function    : HDMI_CEA_VSIF_CFG_cea_vsif_rpt_enGet
//  Description : Set the value of the member CEA_VSIF_CFG.cea_vsif_rpt_en
//  Input       : unsigned int ucea_vsif_rpt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CEA_VSIF_CFG_cea_vsif_rpt_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CEA_VSIF_CFG o_cea_vsif_cfg;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CEA_VSIF_CFG.u32);
    o_cea_vsif_cfg.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cea_vsif_cfg.bits.cea_vsif_rpt_en;
}

//******************************************************************************
//  Function    : HDMI_AVMIXER_CONFIG_dc_pkt_enGet
//  Description : Set the value of the member AVMIXER_CONFIG.dc_pkt_en
//  Input       : unsigned int udc_pkt_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AVMIXER_CONFIG_dc_pkt_enGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVMIXER_CONFIG o_avmixer_config;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVMIXER_CONFIG.u32);
    o_avmixer_config.u32 = HDMITXRegRead(pu32RegAddr);
    return o_avmixer_config.bits.dc_pkt_en;
}

#endif

//******************************************************************************
//  Function    : HDMI_AVMIXER_CONFIG_null_pkt_enSet
//  Description : Set the value of the member AVMIXER_CONFIG.null_pkt_en
//  Input       : unsigned int unull_pkt_en_vs_high: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AVMIXER_CONFIG_null_pkt_enSet(unsigned int unull_pkt_en)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVMIXER_CONFIG o_avmixer_config;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVMIXER_CONFIG.u32);
    o_avmixer_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_avmixer_config.bits.null_pkt_en = unull_pkt_en;
    HDMITXRegWrite(pu32RegAddr, o_avmixer_config.u32);

    return HI_SUCCESS;
}


//******************************************************************************
//  Function    : HDMI_AVMIXER_CONFIG_hdmi_modeGet
//  Description : Set the value of the member AVMIXER_CONFIG.hdmi_mode
//  Input       : unsigned int uhdmi_mode: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_AVMIXER_CONFIG_hdmi_modeGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_AVMIXER_CONFIG o_avmixer_config;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->AVMIXER_CONFIG.u32);
    o_avmixer_config.u32 = HDMITXRegRead(pu32RegAddr);
    return o_avmixer_config.bits.hdmi_mode;
}

//******************************************************************************
//  Function    : HDMI_CP_PKT_AVMUTE_cp_set_avmuteGet
//  Description : Set the value of the member CP_PKT_AVMUTE.cp_set_avmute
//  Input       : unsigned int ucp_set_avmute: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CP_PKT_AVMUTE_cp_set_avmuteGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CP_PKT_AVMUTE o_cp_pkt_avmute;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CP_PKT_AVMUTE.u32);
    o_cp_pkt_avmute.u32 = HDMITXRegRead(pu32RegAddr);
    return o_cp_pkt_avmute.bits.cp_set_avmute;
}

//******************************************************************************
//  Function    : HDMI_HDMI_ENC_CTRL_enc_scr_onGet
//  Description : Set the value of the member HDMI_ENC_CTRL.enc_scr_on
//  Input       : unsigned int uenc_scr_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDMI_ENC_CTRL_enc_scr_onGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HDMI_ENC_CTRL o_hdmi_enc_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->HDMI_ENC_CTRL.u32);
    o_hdmi_enc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_enc_ctrl.bits.enc_scr_on;
}

//******************************************************************************
//  Function    : HDMI_CTL_TYPE_CONFIG_ctl_type_configSet
//  Description : Set the value of the member CTL_TYPE_CONFIG.ctl_type_config
//  Input       : unsigned int uctl_type_config: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_CTL_TYPE_CONFIG_ctl_type_configSet(unsigned int uctl_type_config)
{
    HI_U32 *pu32RegAddr = NULL;
    U_CTL_TYPE_CONFIG o_ctl_type_config;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->CTL_TYPE_CONFIG.u32);
    o_ctl_type_config.u32 = HDMITXRegRead(pu32RegAddr);
    o_ctl_type_config.bits.ctl_type_config = uctl_type_config;
    HDMITXRegWrite(pu32RegAddr, o_ctl_type_config.u32);

    return HI_SUCCESS;
}

#ifndef HDMI_BUILD_IN_BOOT
//******************************************************************************
//  Function    : HDMI_HDMI_ENC_CTRL_enc_hdmi2_onGet
//  Description : Set the value of the member HDMI_ENC_CTRL.enc_hdmi2_on
//  Input       : unsigned int uenc_hdmi2_on: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HDMI_ENC_CTRL_enc_hdmi2_onGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HDMI_ENC_CTRL o_hdmi_enc_ctrl;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->HDMI_ENC_CTRL.u32);
    o_hdmi_enc_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_enc_ctrl.bits.enc_hdmi2_on;
}

#endif

//******************************************************************************
//  Function    : HDMI_HTOTAL_HW_htotal_hwGet
//  Description : Set the value of the member HTOTAL_HW_.htotal_hw
//  Input       : unsigned int uhtotal_hw: 15 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int HDMI_HTOTAL_HW_htotal_hwGet(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    U_HTOTAL_HW o_htotal_hw;
    pu32RegAddr = (HI_U32*)&(goptx_hdmi_regAllReg->HTOTAL_HW.u32);
    o_htotal_hw.u32 = HDMITXRegRead(pu32RegAddr);
    return o_htotal_hw.bits.htotal_hw;
}


