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

#define HIETH_SFV300

#include "hieth.h"
#include "ctrl.h"

static inline u32 _hieth_irq_enable(struct hieth_netdev_local *ld, u32 irqs)
{
    u32 old;

    old = hieth_readl(ld, GLB_RW_IRQ_ENA);

    hieth_writel(ld, old | irqs, GLB_RW_IRQ_ENA);

    return old;
}

static inline u32 _hieth_irq_disable(struct hieth_netdev_local *ld, u32 irqs)
{
    u32 old;

    old = hieth_readl(ld, GLB_RW_IRQ_ENA);

    hieth_writel(ld, old & (~irqs), GLB_RW_IRQ_ENA);

    return old;
}

static inline u32 _hieth_read_irqstatus(struct hieth_netdev_local *ld)
{
    u32 status;

    status = hieth_readl(ld, GLB_RO_IRQ_STAT);

    return status;
}

static inline int _test_xmit_queue_ready(struct hieth_netdev_local *ld)
{
    return hieth_readl_bits(ld, UD_REG_NAME(GLB_RO_QUEUE_STAT),
                            BITS_XMITQ_RDY);
}

static inline int _test_recv_queue_ready(struct hieth_netdev_local *ld)
{
    return hieth_readl_bits(ld, UD_REG_NAME(GLB_RO_QUEUE_STAT),
                            BITS_RECVQ_RDY);
}

u32 hieth_irq_enable(struct hieth_netdev_local *ld, u32 irqs)
{
    u32 old;

    local_lock(ld);
    old = _hieth_irq_enable(ld, irqs);
    local_unlock(ld);

    return old;
}

u32 hieth_irq_disable(struct hieth_netdev_local *ld, u32 irqs)
{
    u32 old;

    local_lock(ld);
    old = _hieth_irq_disable(ld, irqs);
    local_unlock(ld);

    return old;
}

u32 hieth_read_irqstatus(struct hieth_netdev_local *ld)
{
    u32 status;

    local_lock(ld);
    status = _hieth_read_irqstatus(ld);
    local_unlock(ld);

    return status;
}

u32 hieth_read_raw_irqstatus(struct hieth_netdev_local *ld)
{
    u32 status;

    local_lock(ld);
    status = hieth_readl(ld, GLB_RO_IRQ_STAT);
    local_unlock(ld);

    return status;
}

u32 hieth_clear_irqstatus(struct hieth_netdev_local *ld, u32 irqs)
{
    u32 status;

    local_lock(ld);
    hieth_writel(ld, irqs, GLB_RW_IRQ_RAW);
    status = _hieth_read_irqstatus(ld);
    local_unlock(ld);

    return status;
}

u32 hieth_set_endian_mode(struct hieth_netdev_local *ld, u32 mode)
{
    u32 old;

    local_lock(ld);
    old = hieth_readl_bits(ld, GLB_ENDIAN_MOD, BITS_ENDIAN);
    hieth_writel_bits(ld, mode, GLB_ENDIAN_MOD, BITS_ENDIAN);
    local_unlock(ld);

    return old;
}
