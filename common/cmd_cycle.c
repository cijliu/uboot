/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute  it and/or modify it
* under  the terms of  the GNU General Public License as published by the
* Free Software Foundation;  either version 2 of the  License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

/*
 * Command for compress.
 */

#include <common.h>

typedef unsigned char           HI_U8;
typedef unsigned char           HI_UCHAR;
typedef unsigned short          HI_U16;
typedef unsigned int            HI_U32;
typedef unsigned long           HI_UL;

typedef char                    HI_S8;
typedef short                   HI_S16;
typedef int                     HI_S32;

typedef char                    HI_CHAR;
typedef char*                   HI_PCHAR;


#define CYCLE_MAGIC_HEAD        (0x6379636c)

#define CYCLE_MAGIC_ITEM_START  (0x63796373)

#define CYCLE_MAGIC_ITEM_END    (0x63796365)

/** Cycle Head Infomation */
typedef struct hiCYCLE_HEAD_S {
    HI_U32 u32MagicHead;
    HI_U32 u32CycleFlashSize; /**<include cycle_head size */
    HI_U32 u32Compress: 2;
    HI_U32 u32WriteFlag: 3;
    HI_U32 u32Reserved: 27;
    HI_U32 u32AlignSize;
} HI_CYCLE_HEAD_S;

/** Cycle Item Infomation */
typedef struct hiCYCLE_ITEM_START_S {
    HI_U32 u32MagicItemStart;
    HI_U32 u32ItemLen;
    HI_U32 u32ItemAllLen;
    HI_U32 u32ItemOriginLen;
} HI_CYCLE_ITEM_START_S;

#define DIVIDE (3)
#define BYTE_ALIGN ((HI_U32)16)  /**<needed by decompress */

extern unsigned int hw_dec_type;
extern void hw_dec_init(void);
#if ((defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100) || (defined CONFIG_TARGET_HI3556AV100) || (defined CONFIG_TARGET_HI3519AV100))
extern int hw_dec_decompress(unsigned char *dst_h32, unsigned char *dst_l32,
                             int *dstlen,
                             unsigned char *src_h32, unsigned char *src_l32,
                             int srclen, void *unused);
#endif
#if ((defined CONFIG_TARGET_HI3559V200) || (defined CONFIG_TARGET_HI3556V200) || (defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300) || \
 (defined CONFIG_TARGET_HI3516CV500) || (defined CONFIG_TARGET_HI3516EV200) || (defined CONFIG_TARGET_HI3516EV300) || (defined CONFIG_TARGET_HI3518EV300) || \
 (defined CONFIG_TARGET_HI3516DV200))
extern int hw_dec_decompress(unsigned char *dst, int *dstlen,
                             unsigned char *src, int srclen,
                             void *unused);
#endif
extern void hw_dec_uinit(void);

#define CYCLE_ERR(fmt, args...) printf("ERR: <%s:%d> "fmt, __FUNCTION__, __LINE__, ##args)
#define CYCLE_DBG(fmt, args...) printf("DBG: <%s:%d> "fmt, __FUNCTION__, __LINE__, ##args)


static HI_S32 Cycle_Get_InitData(HI_UL ulSrc, HI_U32 u32SrcLen, HI_CYCLE_ITEM_START_S** ppstItem, HI_U32 *pu32Compress)
{
    HI_CYCLE_HEAD_S* pstHead = NULL;
    HI_CYCLE_ITEM_START_S* pstItem = NULL;
    HI_U32 u32ItemMagicEnd = 0;
    HI_UL ulBuffer = ulSrc;

    /* Cycle Head */
    pstHead = (HI_CYCLE_HEAD_S*)ulSrc;

    if ( (CYCLE_MAGIC_HEAD != pstHead->u32MagicHead)
            || (u32SrcLen < pstHead->u32CycleFlashSize)
            || (0 == pstHead->u32AlignSize) ) {
        CYCLE_ERR("pstHead->u32MagicHead: %#x\n", pstHead->u32MagicHead);
        CYCLE_ERR("SrcLen[%u] CycleFlashSize[%u]\n", u32SrcLen, pstHead->u32CycleFlashSize);
        return -1;
    }

    /* Compress Type */
    *pu32Compress = pstHead->u32Compress;
    CYCLE_DBG("Compress[%u]\n", *pu32Compress);

    /* First Item */
    ulBuffer += sizeof(HI_CYCLE_HEAD_S);
    ulBuffer = (ulBuffer + pstHead->u32AlignSize - 1) & ~(pstHead->u32AlignSize - 1);

    pstItem = (HI_CYCLE_ITEM_START_S*)ulBuffer;
    if ((0 == pstItem->u32ItemLen) || (0 != (pstItem->u32ItemLen % BYTE_ALIGN)) ) {
        CYCLE_ERR("pstItem->u32ItemLen: %#x\n", pstItem->u32ItemLen);
        return -1;
    }

    u32ItemMagicEnd = *(HI_U32*)(ulBuffer + (pstItem->u32ItemLen + sizeof(HI_CYCLE_ITEM_START_S)));

    if ((CYCLE_MAGIC_ITEM_START != pstItem->u32MagicItemStart)
            || (pstItem->u32ItemAllLen >= (pstHead->u32CycleFlashSize / DIVIDE))
            || (CYCLE_MAGIC_ITEM_END != u32ItemMagicEnd)) {
        CYCLE_ERR("Item MagicStart[%#x] Len[%u] MagicEnd[%#x] CycleFlashSize[%u]\n",
                  pstItem->u32MagicItemStart, pstItem->u32ItemLen, u32ItemMagicEnd, pstHead->u32CycleFlashSize);
        return -1;
    }

    while (1) {
        /* update item to last valid one */
        *ppstItem = (HI_CYCLE_ITEM_START_S*)ulBuffer;

        /* check next item valid or not */
        ulBuffer += pstItem->u32ItemAllLen;

        pstItem = (HI_CYCLE_ITEM_START_S*)ulBuffer;

        if (ulBuffer - ulSrc >= pstHead->u32CycleFlashSize) { /**<check buffer finish */
            return 0;
        }

        if (CYCLE_MAGIC_ITEM_START != pstItem->u32MagicItemStart) {
            if (pstItem->u32MagicItemStart == 0xffffffff) { /**<unused zone, use previous item */
                return 0;
            } else {
                CYCLE_ERR("pstItem->u32MagicItemStart(0x%x) wrong!\n", pstItem->u32MagicItemStart);
                return -1;
            }
        }

        u32ItemMagicEnd = *(HI_U32 *)(ulBuffer + (pstItem->u32ItemLen + sizeof(HI_CYCLE_ITEM_START_S)));

        if ((pstItem->u32ItemLen >= (pstHead->u32CycleFlashSize / DIVIDE) )
                || (CYCLE_MAGIC_ITEM_END != u32ItemMagicEnd)) { /**<item data damaged */
            CYCLE_ERR("\n");
            return -1;
        }
    }

    return -1;
}

static HI_S32 Cycle_Get_Data(HI_UL ulSrc, HI_U32 u32SrcLen, HI_UL ulDst)
{
    HI_S32 s32Ret = -1;

    HI_CYCLE_ITEM_START_S *pstItem = NULL;
    HI_UL  ulItemData = 0;
    HI_U32 nCompressed = 0;

    s32Ret = Cycle_Get_InitData(ulSrc, u32SrcLen, &pstItem, &nCompressed);

    if ((0 == s32Ret) && pstItem) {
        ulItemData += (HI_UL)pstItem + sizeof(HI_CYCLE_ITEM_START_S);

        if (nCompressed) {
            hw_dec_type = 0; /**<use direct address mode*/
            hw_dec_init(); /**<init hw decompress IP*/

            HI_S32 s32SizeCompressed = pstItem->u32ItemOriginLen;
#if ((defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100) || \
        (defined CONFIG_TARGET_HI3556AV100) || (defined CONFIG_TARGET_HI3519AV100))
            s32Ret = hw_dec_decompress(NULL, (HI_U8*)ulDst, &s32SizeCompressed,
                                       NULL, (HI_U8*)ulItemData, pstItem->u32ItemLen, NULL);
#endif
#if ((defined CONFIG_TARGET_HI3559V200) || (defined CONFIG_TARGET_HI3556V200) || \
    (defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300) || \
    (defined CONFIG_TARGET_HI3516CV500) || (defined CONFIG_TARGET_HI3516EV200) || \
    (defined CONFIG_TARGET_HI3516EV300) || (defined CONFIG_TARGET_HI3518EV300) || \
    (defined CONFIG_TARGET_HI3516DV200))
            s32Ret = hw_dec_decompress((HI_U8*)ulDst, &s32SizeCompressed,
                                       (HI_U8*)ulItemData, pstItem->u32ItemLen, NULL);
#endif

            if (s32Ret == 0 && s32SizeCompressed == pstItem->u32ItemOriginLen) {
                CYCLE_DBG("decompress ok!\n");
                s32Ret = 0;
            } else {
                memset((void*)ulDst, 0, 16);
                CYCLE_ERR("decompress fail[%#x]! uncompress size[%#x]\n", s32Ret, s32SizeCompressed);
                s32Ret = -1;
            }

            hw_dec_uinit(); /**<uinit hw decompress IP*/
        } else {
            memcpy((void*)ulDst, (void*)ulItemData, pstItem->u32ItemLen);
            s32Ret = 0;
        }
    } else {
        memset((void *)ulDst, 0, 16);
        CYCLE_ERR("Failed to get cycle data. dst: 0x%lx\n", ulDst);
        s32Ret = -1;
    }

    return s32Ret;
}

static HI_S32 GetCycleData(HI_UL ulSrc, HI_UL ulSrcBak, HI_U32 u32SrcLen, HI_UL ulDst)
{
    HI_S32 s32Ret = Cycle_Get_Data(ulSrc, u32SrcLen, ulDst);

    if (s32Ret == -1 && ulSrcBak != 0) {
        s32Ret = Cycle_Get_Data(ulSrcBak, u32SrcLen, ulDst);
    }

    return s32Ret;
}

static int do_cycle(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    HI_UL  ulSrc = 0, ulSrcBak = 0, ulDst = 0;
    HI_U32 u32SrcLen = 0;

    /* Check Input Args Count : four arguments needed */
    if (argc != 5) {
        goto usage;
    }

    ulSrc     = simple_strtoul(argv[1], NULL, 16);
    ulSrcBak  = simple_strtoul(argv[2], NULL, 16);
    u32SrcLen = simple_strtoul(argv[3], NULL, 16);
    ulDst     = simple_strtoul(argv[4], NULL, 16);

    if(ulSrc & 0XF) {
        printf("ERR:\n    src[0X%08lx] is not 16Byte-aligned!\n", ulSrc);
        return 1;
    }

    if(ulSrcBak & 0XF) {
        printf("ERR:\n    src_backup[0X%08lx] is not 16Byte-aligned!\n", ulSrcBak);
        return 1;
    }

    if(u32SrcLen & 0XFFFF) {
        printf("ERR:\n    src_len[0X%08x] is not 0x10000Byte-aligned!\n", u32SrcLen);
        return 1;
    }

    if(ulDst & 0XF) {
        printf("ERR:\n    dst[0X%08lx] is not 16Byte-aligned!\n", ulDst);
        return 1;
    }

    return GetCycleData(ulSrc, ulSrcBak, u32SrcLen, ulDst);

usage:
    cmd_usage(cmdtp);
    return 1;
}

U_BOOT_CMD(
    cread,  5,  1,  do_cycle,
    "get valid data from cycle_data buffer. 'cycle <src> <src_backup>  <src_len> <dst>'",
    "1. src_backup can be 0.  2. if src and src_backup are wrong, dst head (16 byte) will be set to 0.  3. src and dst must be 16Byte-aligned"
);

