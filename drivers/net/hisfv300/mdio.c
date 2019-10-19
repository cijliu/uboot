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
#include "mdio.h"

static int wait_mdio_ready(struct hieth_netdev_local *ld)
{
    int timeout_us = 5000;

    while (--timeout_us && !test_mdio_ready(ld)) {
        udelay(50);
    }

    return timeout_us;
}

int hieth_mdio_read(struct hieth_netdev_local *ld, int phy_addr, int regnum)
{
    int val = 0;
    hieth_assert((!(phy_addr & (~0x1F))) && (!(regnum & (~0x1F))));

    local_lock(ld);

    if (!wait_mdio_ready(ld)) {
        hieth_error("mdio busy");
        goto error_exit;
    }

    mdio_start_phyread(ld, phy_addr, regnum);

    if (wait_mdio_ready(ld)) {
        val = mdio_get_phyread_val(ld);
    } else {
        hieth_error("read timeout");
    }

error_exit:

    local_unlock(ld);

    hieth_trace(4, "phy_addr = %d, regnum = %d, val = 0x%04x", phy_addr,
                regnum, val);

    return val;
}

int hieth_mdio_write(struct hieth_netdev_local *ld, int phy_addr, int regnum,
                     int val)
{
    hieth_assert((!(phy_addr & (~0x1F))) && (!(regnum & (~0x1F))));

    hieth_trace(4, "phy_addr = %d, regnum = %d", phy_addr, regnum);

    local_lock(ld);

    if (!wait_mdio_ready(ld)) {
        hieth_error("mdio busy");
        val = -1;
        goto error_exit;
    }

    mdio_phywrite(ld, phy_addr, regnum, val);

error_exit:

    local_unlock(ld);

    return val;
}

int hieth_mdio_reset(struct hieth_netdev_local *ld)
{
    mdio_reg_reset(ld);

    return 0;
}

int hieth_mdio_init(struct hieth_netdev_local *ld)
{
    local_lock_init(ld);

    hieth_mdio_reset(ld);

    return 0;
}

void hieth_mdio_exit(struct hieth_netdev_local *ld)
{
    local_lock_exit(ld);
}
