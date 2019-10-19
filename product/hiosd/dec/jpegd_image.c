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
#include "jpegd_image.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

static const unsigned char DefaultHuffmanTable[418] = { 0x01, 0xA2,
    // Table K.3 Table for luminance DC coefficient differences
    0x00,
    0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0A, 0x0B,

    // Table K.4 Table for chrominance DC coefficient differences
    0x01,
    0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0A, 0x0B,

    // Table K.5 Table for luminance AC coefficients
    0x10,
    0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7D,
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
    0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5,
    0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
    0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA,

    // Table K.6 Table for chrominance AC coefficients
    0x11,
    0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77,
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0,
    0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26,
    0x27, 0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5,
    0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3,
    0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA,
    0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA,
};

static const unsigned char DefaultQuantTable[160] = { 0x00, 0x84,
    // Table K.1 Luminance quantization table
    0x00,
    16,  11,  12,  14,  12,  10,  16,  14,  13,  14,  18,  17,  16,  19,  24,  40,
    26,  24,  22,  22,  24,  49,  35,  37,  29,  40,  58,  51,  61,  60,  57,  51,
    56,  55,  64,  72,  92,  78,  64,  68,  87,  69,  55,  56,  80, 109,  81,  87,
    95,  98, 103, 104, 103,  62,  77, 113, 121, 112, 100, 120,  92, 101, 103,  99,

    // Table K.2 Chrominance quantization table
    0x01,
    17, 18, 18, 24, 21, 24, 47, 26, 26, 47, 99, 66, 56, 66, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
};

int DecodeDHT(MotionJpegObj *mjpeg, const unsigned char *stream, unsigned int len)
{
    HuffmanTab *huffman = &mjpeg->HuffmanTmp;
    int ErrorFlag = 0;
    int i, ptr[16], tab_len;
    int k = 2;
    int Lh;
    unsigned char code, tc, th;
    int ii = 0;
    int jj;

    Lh = (stream[0] << 8) + stream[1];
    stream += 2;

    while (k < Lh) {
        int max_code = 0;
        code = *stream++;
        tc = (code >> 4) & 0x1;
        th = code & 0x1;
        ErrorFlag |= (code & 0xEE);
        if (ErrorFlag != 0) {
            return HI_JPEG_DEC_DHT_ERR;
        }

        for (i = 0, tab_len = 0; i < 16; i++) {
            ptr[i] = *stream++;

            if (ptr[i]) {
                huffman->MinCode[i] = (max_code) << 1;
                huffman->MaxCode[i] = huffman->MinCode[i] + ptr[i] - 1;
                huffman->MaxCode16[i] = ((huffman->MaxCode[i] + 1) << (15 - i)) - 1;
                huffman->Len[i] = ptr[i];
                huffman->HuffmanValPtr[i] = tab_len;
                max_code = huffman->MaxCode[i] + 1;
                ErrorFlag |= ((huffman->MaxCode[i] + 1) > (1 << (i + 1)));
            } else {
                huffman->MinCode[i] = max_code << 1;
                huffman->MaxCode[i] = -1;
                huffman->MaxCode16[i] = -1;
                huffman->Len[i] = 0;
                huffman->HuffmanValPtr[i] = tab_len;
                max_code <<= 1;
            }
            tab_len += ptr[i];
        }
        huffman->MaxCode16[15] = 0x0000ffff;
        huffman->MaxCode[15] = huffman->MinCode[15] + ptr[15] - 1;
        k += 17 + tab_len;
        ErrorFlag |= (tab_len > 255);

        if ((k > Lh) || ErrorFlag) {
            return HI_JPEG_DEC_DHT_ERR;
        }

        memset(&huffman->HuffmanVal[0], 0, sizeof(huffman->HuffmanVal));
        for (i = 0; (i < tab_len) && (i < 256); i++) {
            huffman->HuffmanVal[i] = *stream++;
        }

        for (i = 0, jj = 0; i < 8; i++) {
            for (ii = 0; ii < ptr[i]; ii++) {
                int count = 1 << (7 - i);
                unsigned char huffmancode = huffman->HuffmanVal[huffman->HuffmanValPtr[i] + ii];
                while (count--) {
                    huffman->FastHuffmanLen[jj] = i + 1;
                    huffman->FastHuffmanCode[jj++] = huffmancode;
                }
            }
        }
        huffman->uCode32 = (jj - 1) << 24;
        mjpeg->hTab[(tc << 1) + th] = *huffman;
    }

    return HI_JPEG_DEC_OK;
}

int DecodeSOF0(MotionJpegObj *mjpeg, const unsigned char *stream, unsigned int len)  // 0xFF C0
{
    int ErrorFlag = 0;
    FrameHeader header = {0};
    int Ls;

    Ls = (stream[0] << 8) + stream[1];
    header.Colordepth = stream[2];
    header.yHeight = (stream[3] << 8) + stream[4];
    header.yWidth = (stream[5] << 8) + stream[6];
    header.Nf = stream[7];
    stream += 8;

    ErrorFlag |= (header.Colordepth != 8);
    ErrorFlag |= (Ls != (header.Nf * 3 + 8));
    ErrorFlag |= (header.yHeight > mjpeg->MaxHeight);
    ErrorFlag |= (header.yWidth > mjpeg->MaxWidth);
    ErrorFlag |= (header.yWidth == 0);
    ErrorFlag |= (header.yHeight == 0);
    ErrorFlag |= ((header.Nf != 1) && (header.Nf != 3));

    if (header.Colordepth != 8) {
        return HI_ERR_NOT_BASELINE;
    }

    if (Ls != (header.Nf * 3 + 8)) {
        return HI_ERR_FRAME_HEADER;
    }

    if ((header.yHeight > mjpeg->MaxHeight) || (header.yHeight == 0)) {
        return HI_UNSUPPORT_PIC_SIZE;
    }

    if ((header.yWidth > mjpeg->MaxWidth) || (header.yWidth == 0)) {
        return HI_UNSUPPORT_PIC_SIZE;
    }
    if ((header.Nf != 3) && (header.Nf != 1)) {
        return HI_UNSUPPORT_PIC_STRUCT;
    }

    if (header.Nf == 1) {
        header.Ci[0] = stream[0];
        header.H[0] = stream[1];
        header.H[1] = 0;
        header.H[2] = 0;
        header.Tq[0] = stream[2];
        header.Tq[1] = header.Tq[0];
        header.Tq[2] = header.Tq[0];
        ErrorFlag |= (header.H[0] != 0x11);  // only support H = V = 1;
        ErrorFlag |= (header.Tq[0] & 0xfc);  // Tq = (0 ~ 3), inclusive
        if (ErrorFlag != 0) {
            return HI_UNSUPPORT_PIC_STRUCT;
        }
        mjpeg->WidthInMCU = (header.yWidth + 7) >> 3;
        mjpeg->HeightInMCU = (header.yHeight + 7) >> 3;
        mjpeg->yStride = mjpeg->WidthInMCU << 3;
        mjpeg->enPictureFormat = PICTURE_FORMAT_YUV400;  // YUV100
    }

    if (header.Nf == 3) {
        header.Ci[0] = stream[0];
        header.H[0] = stream[1];
        header.Tq[0] = stream[2];
        header.Ci[1] = stream[3];
        header.H[1] = stream[4];
        header.Tq[1] = stream[5];
        header.Ci[2] = stream[6];
        header.H[2] = stream[7];
        header.Tq[2] = stream[8];

        ErrorFlag |= (header.H[1] != 0x11);  // only support H = V = 1;
        ErrorFlag |= (header.H[2] != 0x11);  // only support H = V = 1;
        ErrorFlag |= (header.Tq[0] & 0xfc);  // Tq = (0 ~ 3), inclusive
        ErrorFlag |= (header.Tq[1] & 0xfc);  // Tq = (0 ~ 3), inclusive
        ErrorFlag |= (header.Tq[2] & 0xfc);  // Tq = (0 ~ 3), inclusive

        if ((header.Tq[0] & 0xfc) || (header.Tq[1] & 0xfc) || (header.Tq[2] & 0xfc)) {
            return HI_ERR_NOT_BASELINE;
        }

        if ((header.H[0] == 0x41) || (header.H[0] == 0x14)) {
            return HI_UNSUPPORT_YUV411;
        }

        if ((header.H[1] != 0x11) || (header.H[2] != 0x11)) {
            return HI_UNSUPPORT_PIC_STRUCT;
        }

        if (header.H[0] == 0x11) {
            mjpeg->WidthInMCU = (header.yWidth + 7) >> 3;
            mjpeg->HeightInMCU = (header.yHeight + 7) >> 3;
            mjpeg->yStride = mjpeg->WidthInMCU << 3;
            mjpeg->cStride = mjpeg->WidthInMCU << 3;
            mjpeg->enPictureFormat = PICTURE_FORMAT_YUV444;  // YUV111
        } else if (header.H[0] == 0x22) {
            mjpeg->WidthInMCU = (header.yWidth + 15) >> 4;
            mjpeg->HeightInMCU = (header.yHeight + 15) >> 4;
            mjpeg->yStride = mjpeg->WidthInMCU << 4;
            mjpeg->cStride = mjpeg->WidthInMCU << 3;
            mjpeg->enPictureFormat = PICTURE_FORMAT_YUV420;  // YUV420
        } else if (header.H[0] == 0x21) {
            mjpeg->WidthInMCU = (header.yWidth + 15) >> 4;
            mjpeg->HeightInMCU = (header.yHeight + 7) >> 3;
            mjpeg->yStride = mjpeg->WidthInMCU << 4;
            mjpeg->cStride = mjpeg->WidthInMCU << 3;
            mjpeg->enPictureFormat = PICTURE_FORMAT_YUV422;  // YUV422
        } else if (header.H[0] == 0x12) {
            mjpeg->WidthInMCU = (header.yWidth + 7) >> 3;
            mjpeg->HeightInMCU = (header.yHeight + 15) >> 4;
            mjpeg->yStride = mjpeg->WidthInMCU << 3;
            mjpeg->cStride = mjpeg->WidthInMCU << 3;
            mjpeg->enPictureFormat = PICTURE_FORMAT_YUV422v;
        } else {
            mjpeg->enPictureFormat = PICTURE_FORMAT_BUTT;  // do not support
            return HI_UNSUPPORT_PIC_STRUCT;
        }
    }

    header.MaxMCUNumber = mjpeg->WidthInMCU * mjpeg->HeightInMCU;
    header.RestartIntervalLogic = mjpeg->Frame.RestartInterval;
    header.RestartInterval = (mjpeg->Frame.RestartInterval != 0) ? mjpeg->Frame.RestartInterval : header.MaxMCUNumber;
    mjpeg->Frame = header;
    return HI_JPEG_DEC_OK;
}

int DecodeSOS(MotionJpegObj *mjpeg, unsigned char *stream, unsigned int len)  // 0xFF DA
{
    int ErrorFlag = 0;
    ScanHeader scan;
    int i, code;
    FrameHeader *fh = &mjpeg->Frame;
    int Ls = (stream[0] << 8) + stream[1];
    int Ns = stream[2];
    stream += 3;

    ErrorFlag |= (Ns != fh->Nf);  // Ns should be equal to Nf in frame header
    ErrorFlag |= (Ls != (Ns * 2 + 6));

    if (ErrorFlag) {
        return HI_ERR_SCAN_HEADER;
    }

    for (i = 0; (i < Ns) && (ErrorFlag == 0); i++) {
        scan.Cs[i] = *stream++;
        code = *stream++;
        scan.Td[i] = code >> 4;
        scan.Ta[i] = code & 0xf;
        mjpeg->qTabComponents[i] = &mjpeg->qTab[(3 & fh->Tq[i])];
        mjpeg->hTabComponentsDC[i] = &mjpeg->hTab[(1 & scan.Td[i])];
        mjpeg->hTabComponentsAC[i] = &mjpeg->hTab[2 + (1 & scan.Ta[i])];

        ErrorFlag |= (scan.Cs[i] != fh->Ci[i]);
        ErrorFlag |= (scan.Td[i] > 1);  // baseline: Td  = (0 ~ 1), inclusive
        ErrorFlag |= (scan.Ta[i] > 1);  // baseline: Ta  = (0 ~ 1), inclusive

        if ((scan.Td[i] > 1) || (scan.Ta[i] > 1)) {
            return HI_ERR_NOT_BASELINE;
        }

        if (scan.Cs[i] != fh->Ci[i]) {
            return HI_ERR_SCAN_HEADER;
        }
    }
    scan.Ns = Ns;
    scan.Ss = *stream++;
    scan.Se = *stream++;
    code = *stream++;
    scan.Ah = code >> 4;
    scan.Al = code & 0xf;

    if ((scan.Ss != 0) || (scan.Se != 63) || (scan.Ah != 0) || (scan.Al != 0)) {
        return HI_ERR_NOT_BASELINE;
    }

    if (ErrorFlag == 0) {
        mjpeg->Scan = scan;
        return HI_JPEG_DEC_OK;
    } else {
        return HI_JPEG_DEC_SCAN_ERR;
    }
}

int DecodeDRI(MotionJpegObj *mjpeg, const unsigned char *stream, unsigned int len)
{
    int Lr = (stream[0] << 8) + stream[1];
    int Ri = (stream[2] << 8) + stream[3];

    if (Lr != 4) {
        return 1;
    }

    mjpeg->Frame.RestartInterval = Ri;
    mjpeg->Frame.RestartIntervalLogic = Ri;

    if (mjpeg->Frame.MaxMCUNumber == 0) {
        mjpeg->Frame.RestartInterval = Ri;
    } else {
        mjpeg->Frame.RestartInterval = (Ri == 0) ? mjpeg->Frame.MaxMCUNumber : Ri;
    }

    return 0;
}

int DecodeDQT(MotionJpegObj *mjpeg, const unsigned char *stream, unsigned int len)
{
    int ErrorFlag = 0;
    unsigned char *pQuant;
    int i, code, Pq, Tq;
    int k = 2;
    int Lq = (stream[0] << 8) + stream[1];
    stream += 2;

    while ((k < Lq) && (ErrorFlag == 0)) {
        k += 65;
        code = *stream++;
        Pq = code >> 4;
        Tq = code & 0xf;
        ErrorFlag |= (Pq != 0);  // Pq must be 0 in baseline
        ErrorFlag |= (Tq > 3);  // Tq should be (0 ~ 3), inclusive
        ErrorFlag |= (k > Lq);
        if (ErrorFlag) {
            return ErrorFlag;
        }

        pQuant = mjpeg->qTab[Tq & 3].Quant;
        for (i = 0; i < 64; i++) {
            pQuant[i] = *stream++;
        }
    }
    return ErrorFlag;
}

void InitDefaultHuffmanTable(MotionJpegObj *mjpeg)
{
    int ret;
    ret = DecodeDHT(mjpeg, DefaultHuffmanTable, 0x01A2);
    if (ret != HI_JPEG_DEC_OK) {
        HI_TRACE("jpeg decode DHT error!\n");
    }
}

void InitDefaultQuantTable(MotionJpegObj *mjpeg)
{
    int ret;
    ret = DecodeDQT(mjpeg, DefaultQuantTable, 0x0084);
    if (ret != 0) {
        HI_TRACE("jpeg decode DQT error!\n");
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */



