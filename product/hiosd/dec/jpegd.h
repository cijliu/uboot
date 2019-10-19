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

#ifndef __JPEGD_H__
#define __JPEGD_H__
#include "hi_type.h"
#include "jpegd_drv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define ALIGN_UP(x, a) (((x) + ((a)-1)) & (~((a)-1)))

#define HI_JPEG_DEC_OK        0
#define HI_JPEG_DEC_FRAME_ERR 1
#define HI_JPEG_DEC_SCAN_ERR  2
#define HI_JPEG_DEC_MCU_ERR   3
#define HI_JPEG_DEC_DRI_ERR   4
#define HI_JPEG_DEC_DHT_ERR   5
#define HI_JPEG_DEC_DQT_ERR   6

#define JPEGD_MAX_WIDTH       8192
#define JPEGD_MAX_HEIGHT      8192
#define JPEGD_MIN_WIDTH       8
#define JPEGD_MIN_HEIGHT      8

#define ONE_EMAR_BUF_SIZE     (128 * ((JPEGD_MAX_WIDTH + 7) >> 3))

#define BASELINE              0xC0  // baseline frame header
#define PROGRESSIVE           0xC2  // progressive frame header
#define DHT                   0xC4
#define RST0                  0xD0
#define RST1                  0xD1
#define RST2                  0xD2
#define RST3                  0xD3
#define RST4                  0xD4
#define RST5                  0xD5
#define RST6                  0xD6
#define RST7                  0xD7
#define SOI                   0xD8
#define EOI                   0xD9
#define SOS                   0xDA
#define DQT                   0xDB
#define DNL                   0xDC
#define DRI                   0xDD

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define HI_MJPEG_DEC_OK       0
#define HI_MJPEG_NO_PICTURE   (-1)
#define HI_MJPEG_ERR_HANDLE   (-2)

#define JPEGD_MAX_HANDLE_NUM  3

#define JPEGD_ALLOC_BUFF_CACHED

typedef void *JPEGD_HANDLE;

typedef enum hiJPEGD_STATE {
    STATE_IDLE = 0,
    STATE_BUSY = 1,
    STATE_BUTT
} JPEGD_STATE_E;

typedef struct {
    int MaxCode[16];
    int MaxCode16[16];
    int MinCode[16];
    int Len[16];
    unsigned short HuffmanValPtr[16];
    unsigned char HuffmanVal[256];

    unsigned char FastHuffmanCode[256];
    unsigned char FastHuffmanLen[256];
    unsigned int uCode32;
} HuffmanTab;

typedef struct {
    unsigned char Quant[64];
} QuantTab;

typedef struct {
    unsigned int Nf;
    unsigned int Colordepth;
    unsigned int yWidth;
    unsigned int yHeight;
    unsigned char Ci[4];
    unsigned char H[4];
    unsigned char V[4];
    unsigned char Tq[4];
    unsigned int RestartInterval;
    unsigned int RestartIntervalLogic;
    unsigned int MaxMCUNumber;
} FrameHeader;

typedef struct {
    unsigned int Ns;
    unsigned char Cs[4];
    unsigned char Td[4];
    unsigned char Ta[4];
    unsigned char Ss;
    unsigned char Se;
    unsigned char Ah;
    unsigned char Al;
} ScanHeader;

typedef struct {
    unsigned char *pBuffer;
    unsigned int BitLen;
    unsigned int BitOffset;
} Bitstream;

typedef struct {
    unsigned char *pu8VirAddr;
    HI_U64 u64PhyAddr;
    unsigned int u32Len;
    unsigned int u64PTS;
} JPEGD_STREAM_S;

typedef struct {
    unsigned char *StreamBuffer;
    unsigned char *PicBuffer;
    unsigned int u32StreamOffest;
    JPEGD_STREAM_S stStream;
    Bitstream Bits;
    FrameHeader Frame;
    ScanHeader Scan;
    HuffmanTab hTab[4];
    QuantTab qTab[4];

    unsigned char *pY[2];
    unsigned char *pU[2];
    unsigned char *pV[2];
    unsigned int ValidFrame;
    unsigned int MaxWidth;
    unsigned int MaxHeight;
    unsigned int BufSize;
    unsigned int FirstMCU;
    short JpegDCPred[4];  // 0 for Y;  1 for U;   2 for V;  3 reserved

    unsigned int HeightInMCU;
    unsigned int WidthInMCU;
    unsigned int yStride;
    unsigned int cStride;
    PICTURE_FORMAT_E enPictureFormat;

    QuantTab *qTabComponents[3];
    HuffmanTab *hTabComponentsDC[3];
    HuffmanTab *hTabComponentsAC[3];
    HuffmanTab HuffmanTmp;

    unsigned int u32Profile; /* 0: baseline; 1:progressive; other:unsupport; */
    JPEGD_STATE_E enState;
    JPEGD_VPU_CONFIG_S stVpuConfig;
    JPEGD_VPU_STATUS_S stVpuStatus;
} MotionJpegObj;

typedef struct hiMJPEG_USERDATA_S {
    unsigned int uUserDataType;  // Type of userdata
    unsigned int uUserDataSize;  // Length of userdata in byte
    unsigned char *pData;  // Buffer contains userdata stuff
    struct hiMJPEG_USERDATA_S *pNext;  // Pointer to next userdata
} MJPEG_USERDATA_S;

typedef struct hiMJPEG_DEC_FRAME_S {
    unsigned char *pY;
    unsigned char *pU;
    unsigned char *pV;
    unsigned int uWidth;
    unsigned int uHeight;
    unsigned int uYStride;
    unsigned int uCStride;
    int uPictureFormat;  // 0: YUV420;
    // 1: YUV422;
    // 2: YUV444;
    // 3: YUV422V;
    // 4: YUV400;
    // >=5: reserved
    int bError;  // 0: No error
    // 1: MCU error
    HI_U64 ullPTS;  // time stamp
    unsigned int reserved;
    int ErrorCode;
    MJPEG_USERDATA_S *pUserData;  // Pointer to the first userdata
} MJPEG_DEC_FRAME_S;

JPEGD_HANDLE JPEGD_GetHandle(HI_VOID);
int JPEGD_DecFrame(JPEGD_HANDLE Handle, unsigned int uFlags);
int JPEGD_StartOneFrame(JPEGD_HANDLE Handle, unsigned int uFlags);
void JPEGD_WriteRegs(JPEGD_HANDLE Handle, HI_VOID *pRegBase);
void JPEGD_ReadRegs(JPEGD_HANDLE Handle, HI_VOID *pRegBase);
int JPEGD_StartDecoding(JPEGD_HANDLE Handle);
HI_VOID JPEGD_FinishDecoding(JPEGD_HANDLE Handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* _JPEGD_H_ */

