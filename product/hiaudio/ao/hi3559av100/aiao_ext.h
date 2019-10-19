/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : aio_ext.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/5/5
  Description   :
  History       :
  1.Date        : 2009/5/5
    Author      : p00123320
    Modification: Created file
******************************************************************************/


#ifndef __AIAO_EXT_H__
#define __AIAO_EXT_H__

typedef struct hiAIO_DRV_DEV_CTX_S
{
    struct
    {
        HI_U32          u32BufSize;         
        HI_U32          u32PhyAddr;         
        HI_U8*          pu8VirAddr;         

        HI_U32          u32RptrOffSet;         
        HI_U32          u32WptrOffSet;         

    } stCirBuf;

    AIO_ATTR_S          stAioAttr;
    HI_BOOL             bEnable;

    HI_U64              u64LastPts;         
    HI_U32              u32FrmTime;         
    HI_U32              u32MaxFrmTime;      
    HI_U32              u32IsrTime;         
    HI_U32              u32MaxIsrTime;      
    HI_U32              u32AioFifoLen;      
    HI_U32              u32FifoLenBase;     
    HI_U32              u32FifoShift;       
    HI_U32              u32TransLen;        

    HI_S32              as32ChnIndex[AIO_MAX_CHN_NUM];

    HI_U32              u32IntCnt;
    HI_U32              u32fifoIntCnt;          
    HI_U32              u32buffIntCnt;          
    AUDIO_TRACK_MODE_E  enTrackMode;
    HI_BOOL             bMute;
    AUDIO_FADE_S        stFade;
    HI_S32              s32Volume;
    HI_BOOL             bMicInl;
    HI_BOOL             bMicInr;
}AIO_DRV_DEV_CTX_S;

#endif
