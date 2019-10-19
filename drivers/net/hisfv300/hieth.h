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

#ifndef __HISILICON_ETH_H
#define __HISILICON_ETH_H

#include <config.h>
#include <common.h>
#include <command.h>

#include <linux/list.h>
#include <asm/io.h>

#include <malloc.h> /* malloc, free, realloc */

#include <net.h>
#include <miiphy.h>
#include <asm/arch/platform.h>

#define OSDRV_MODULE_VERSION_STRING "Hisilicon ETH net controler"

#ifndef BIT
#define BIT(nr) (1UL << (nr))
#endif
#define mdelay(n) udelay((n)*1000)
/* ***********************************************************
 *
 * Global varibles and defintions
 *
 *************************************************************
 */

/* configuerable values */

#ifdef HIETH_RX_QUEUE_MULTI_DESC
#define HIETH_HW_DESC_DEPTH 72
#endif

#define ETH_MDIO_FRQDIV 2

/* mdiobus device name, such as platform device name */
#define HIETH_MDIOBUS_NAME "hieth_mdiobus"

/* eth device name, such as platform device name */
#define HIETH_SFV300_NAME     "hieth_sfv300"
#define MAX_PHY_NAME_LEN      16
#define HIETH_MAX_QUEUE_DEPTH 64
#ifdef HIETH_RX_QUEUE_MULTI_DESC
#define HIETH_HW_RXQ_DEPTH 52 /* uboot */
#else
#define HIETH_HW_RXQ_DEPTH 1 /* uboot */
#endif
#define HIETH_HW_TXQ_DEPTH 1 /* uboot */

#define HIETH_MAX_FRAME_SIZE PKTSIZE_ALIGN /* 1536 */

#define hieth_dump_buf(buf, len)         \
    do {                                 \
        int i;                           \
        char *p = (void *)(buf);         \
        for (i = 0; i < (len); i++) {    \
            printf("0x%.2x ", *(p + i)); \
            if (!((i + 1) & 0x0F))       \
                printf("\n");            \
        }                                \
        printf("\n");                    \
    } while (0)

#define HIETH_TRACE_LEVEL          8
#define hieth_trace(level, msg...) \
    do {                                                       \
        if ((level) >= HIETH_TRACE_LEVEL) {                    \
            printf("hieth_trace:%s:%d: ", __FILE__, __LINE__); \
            printf(msg);                                       \
            printf("\n");                                      \
        }                                                      \
    } while (0)

#define hieth_error(s...)                            \
    do {                                             \
        printf("hieth:%s:%d: ", __FILE__, __LINE__); \
        printf(s);                                   \
        printf("\n");                                \
    } while (0)

#define hieth_assert(cond)                 \
    do {                                   \
        if (!(cond))                       \
            printf("Assert:hieth:%s:%d\n", \
                __FILE__,                  \
                __LINE__);                 \
    } while (0)

#define hil_vqueue_assert(cond)              hieth_assert(cond)
#define hil_vqueue_error(s...)               hieth_error(s)
#define hil_vqueue_trace_printf(level, s...) \
    do {                                     \
        if ((level) >= HIETH_TRACE_LEVEL)    \
            printf(s);                       \
    } while (0)

/* Error number */
#define HIETH_E_QUEUE (-1)
#define HIETH_E_BUSY  (-2)
#define HIETH_E_FULL  (-3)
#define HIETH_E_EMPTY (-4)

struct hieth_frame_desc {
    unsigned long frm_addr; /* required by the controler */
    unsigned int frm_len : 11; /* required by the controler */
};
#define hieth_fd_copy(newfd, fd) \
    do {                         \
        newfd = fd;              \
    } while (0)
#define HIETH_FD_INIT(fd) \
    do {                  \
        fd.frm_addr = 0;  \
        fd.frm_len = 0;   \
    } while (0)

#define hieth_trace_fd(level, fd) hieth_trace(level, \
    #fd "<%p>={ .frm_addr=%08lx, .frm_len=%d}",      \
    &(fd), (fd).frm_addr, (fd).frm_len)

/* port */
#define UP_PORT   0
#define DOWN_PORT 1

enum if_mode {
    INTERFACE_MODE_MII,
    INTERFACE_MODE_RMII
};

struct hieth_netdev_local {
    unsigned long iobase_phys; /* physical io addr */
    int port : 1; /* 0 => up port,    1 => down port */

#ifdef HIETH_RX_QUEUE_MULTI_DESC
    int desc_hw_offset; /* the offset where we feed hw */
    int desc_rec_offset; /* the offset where we receve the package */
    struct hieth_frame_desc *hieth_desc_head;
#endif

    u32 link_stat;
    char *mii_name;
    unsigned char phy_addr;
    enum if_mode phy_intf;

    /* mdio_bus freq-div, 1 for 1/100, 0 for 1/50 */
    u32 mdio_frqdiv;
};

/* ***********************************************************
 *
 * Only for internal used!
 *
 * ***********************************************************
 */

/* read/write IO */

#define _readl(c)     ({ u32 __v = le32_to_cpu(__raw_readl(c)); __v; })
#define _writel(v, c) __raw_writel(cpu_to_le32(v), c)

#define hieth_readl(ld, ofs) ({ u32 reg = _readl((ld)->iobase_phys + (ofs)); \
				hieth_trace(2, "_readl(0x%08X) = 0x%08X", \
				(u32)((ld)->iobase_phys + (ofs)), reg); \
				reg; })
#define hieth_writel(ld, v, ofs)                         \
    do {                                                 \
        _writel(v, (ld)->iobase_phys + (ofs));           \
        hieth_trace(2, "_writel(0x%08X) = 0x%08X",       \
           (u32)((ld)->iobase_phys + (ofs)), (u32)(v)); \
    } while (0)

#define MK_BITS(shift, nbits) ((((shift) & 0x1F) << 16) | ((nbits) & 0x1F))

#define hieth_writel_bits(ld, v, ofs, bits_desc)                                \
    do {                                                                        \
        u32 _bits_desc = bits_desc;                                             \
        u32 _shift = (_bits_desc) >> 16;                                        \
        u32 _reg = hieth_readl(ld, ofs);                                        \
        u32 _mask = ((1 << (_bits_desc & 0x1F)) - 1) << (_shift);               \
        hieth_writel(ld, (_reg & (~_mask)) | (((v) << (_shift)) & _mask), ofs); \
    } while (0)
#define hieth_readl_bits(ld, ofs, bits_desc) ({ \
		u32 _bits_desc = bits_desc; \
		u32 _shift = (_bits_desc)>>16; \
		u32 _mask = ((1 << (_bits_desc & 0x1F)) - 1) << (_shift); \
		(hieth_readl(ld, ofs) & _mask) >> (_shift); })

#define local_lock_init(ld)
#define local_lock_exit(ld)
#define local_lock(ld)
#define local_unlock(ld)

#define UD_REG_NAME(name) ((ld->port == UP_PORT) ? U_##name : D_##name)
#define UD_BIT_NAME(name) ((ld->port == UP_PORT) ? name##_U : name##_D)

#endif
