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
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <version.h>
#include <net.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <config.h>
#include "jpegd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

const char g_hilogo_magic_str[] = "HISILICON LOGO MAGIC";

unsigned long g_hilogo = 0;
unsigned long g_jpeg_size = 0;
unsigned long g_video_data_base = 0;
unsigned long g_jpegd_emar_buf = 0;
unsigned int g_output_format = 0;

extern void dcache_enable(void);
extern void dcache_disable(void);
extern int dcache_status(void);
extern void flush_dcache_range(unsigned long start, unsigned long stop);

int jpeg_decode(unsigned int format)
{
    JPEGD_HANDLE Handle;
    int s32Ret;

    g_output_format = format;
    if (dcache_status()) {
        flush_dcache_range(g_hilogo, g_hilogo + g_jpeg_size);
    }

    Handle = JPEGD_GetHandle();

    s32Ret = JPEGD_StartDecoding(Handle);
    if (s32Ret != HI_SUCCESS) {
        printf("decoding error!");
        return -1;
    }

    JPEGD_FinishDecoding(Handle);

    return 0;
}

int load_jpeg(void)
{
    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;
    char *str4 = NULL;
    long u = 0;
    unsigned int u32Len;
    unsigned long ulInterval;

    printf("jpeg decoding ...\n");

 /* get vo buffer address */
    str1 = getenv("vobuf");
    if (str1) {
        g_video_data_base = simple_strtol(str1, NULL, 0);
    } else {
        printf("Invalid vobuf address!\n");
        return 1;
    }
    if (g_video_data_base == 0) {
        printf("Invalid VOU buffer address 0x%08lX\n", g_video_data_base);
        return -1;
    }

    /* get emar buffer address for jpegd */
    str2 = getenv("jpeg_emar_buf");
    if (str2) {
        g_jpegd_emar_buf = simple_strtol(str2, NULL, 0);
    } else {
        printf("Invalid jpeg_emar_buf address!\n");
        return 1;
    }
    if (g_jpegd_emar_buf == 0) {
        printf("Invalid jpeg_emar_buf address 0x%08lX\n", g_jpegd_emar_buf);
        return -1;
    }

    /* jpeg decoder need 2 emar buffer */
    u32Len = ONE_EMAR_BUF_SIZE * 2;
    if (g_video_data_base > g_jpegd_emar_buf) {
        ulInterval = g_video_data_base - g_jpegd_emar_buf;
    } else {
        ulInterval = g_jpegd_emar_buf - g_video_data_base;
    }
    if (ulInterval < u32Len) {
        printf("vobuf and jpeg_emar_buf is overlapping! Their ulInterval len must larger than %u\n", u32Len);
        return -1;
    }

    /* get jpeg stream address */
    str3 = getenv("jpeg_size");
    if (str3) {
        g_jpeg_size = simple_strtol(str3, NULL, 0);
    } else {
        printf("you should set jpeg stream address!\n");
        return -1;
    }
    if (g_jpeg_size == 0) {
        printf("Invalid jpeg_size 0x%08lX\n", g_jpeg_size);
        return -1;
    }

    str4 = getenv("jpeg_addr");
    if (str4) {
        g_hilogo = simple_strtol(str4, NULL, 0);
    } else {
        printf("you should set jpeg picture's address!\n");
        return -1;
    }
    if (g_hilogo == 0) {
        printf("Invalid jpeg_addr 0x%08lX\n", g_hilogo);
        return -1;
    }

    printf("<<addr=%#lx, size=%#lx, jpeg_emar_buf=%#lx, vobuf=%#lx>>\n", g_hilogo, g_jpeg_size, g_jpegd_emar_buf,
           g_video_data_base);
    if ((g_hilogo & 0x7f) != 0) {
        printf("jpeg_addr:%#lx should be align to 128bytes!\n", g_hilogo);
        return -1;
    }
    if ((*(unsigned char *)g_hilogo != 0xFF) || (*(unsigned char *)(g_hilogo + 1) != 0xD8)) {
        printf("addr:%#lx,size:%ld,logoaddr:%#lx,:%2x,%2x\n", g_hilogo, g_jpeg_size, u, *(unsigned char *)g_hilogo,
               *(unsigned char *)(g_hilogo + 1));
        return -1;
    }

    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */




