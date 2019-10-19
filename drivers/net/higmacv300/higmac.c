#include <console.h>
#include "util.h"
#include "higmac.h"
#include "ctrl.h"
#include "mdio.h"

#define INVALID_PHY_ADDR 0xFF

typedef enum {
    GSF0_PORT0,
#if GMAC_AT_LEAST_2PORT
    GSF0_PORT1,
#endif
#if GMAC_AT_LEAST_3PORT
    GSF1_PORT0,
#endif
    MAX_PORT_NUM,
} port_id_t;

static int mac_iobase[MAX_PORT_NUM] = {
    HIGMAC0_IOBASE,
#if GMAC_AT_LEAST_2PORT
    HIGMAC1_IOBASE,
#endif
#if GMAC_AT_LEAST_3PORT
    HIGMAC2_IOBASE,
#endif
};

/* suppose higmac_board_info[i] was initialed! */
#define for_each_gmac_netdev_local_priv(ld, i) \
    for (i = 0; i < CONFIG_GMAC_NUMS &&        \
                ({ld = &higmac_board_info[i].higmac_ld; 1; });                         \
         i++)

/* this driver only support GMAC_NUMS = 2 or 1 */
#define MDIO_BUS_NUMS (2)
struct higmac_board_info higmac_board_info[CONFIG_GMAC_NUMS] = {
    {
        {
            .index = GSF0_PORT0,
            .iobase = HIGMAC0_IOBASE,
            .iobase_phys = HIGMAC0_IOBASE,
        },
        .mii_name = "mdio0",
        .phy_intf = CONFIG_HIGMAC_PHY0_INTERFACE_MODE,
        .phy_addr = CONFIG_HIGMAC_PHY0_ADDR,
    },
#if GMAC_AT_LEAST_2PORT
    {
        {
            .index = GSF0_PORT1,
            .iobase = HIGMAC1_IOBASE,
            .iobase_phys = HIGMAC1_IOBASE,
        },
        .mii_name = "mdio1",
        .phy_intf = CONFIG_HIGMAC_PHY1_INTERFACE_MODE,
        .phy_addr = CONFIG_HIGMAC_PHY1_ADDR,
    }
#endif
};

static int phy_link_times;
static int gmac_debug;

static char *phy_intf_str[interface_mode_butt] = {
    "mii",
    "rmii",
    "rgmii",
};
static char *mdio_bus[CONFIG_GMAC_NUMS] = {
    "mdio0",
#if GMAC_AT_LEAST_2PORT
    "mdio1",
#endif
#if GMAC_AT_LEAST_3PORT
    "mdio2"
#endif
};

#if defined(CONFIG_MACH_GODEYES)
/*
 *  * 3516(godeyes) port mode def.
 *   * port_mode_butt means not support this mode.
 *    */
static int g_speed_portmode_table[speed_mode_butt][interface_mode_butt] = {
    { port_mode_10_mii,  port_mode_butt, port_mode_10_rgmii },
    { port_mode_100_mii, port_mode_butt, port_mode_100_rgmii },
    { port_mode_butt,    port_mode_butt, port_mode_1000_rgmii }
};
#else
static int g_speed_portmode_table[speed_mode_butt][interface_mode_butt] = {
    { port_mode_10_mii,  port_mode_10_rmii,  port_mode_10_rgmii },
    { port_mode_100_mii, port_mode_100_rmii, port_mode_100_rgmii },
    { port_mode_butt,    port_mode_butt,     port_mode_1000_rgmii }
};
#endif

static int calculate_port_mode(enum speed_mode speed, enum if_mode if_mode,
                               int is_duplex_half)
{
    if (speed < speed_mode_butt && if_mode < interface_mode_butt) {
        int ret = g_speed_portmode_table[speed][if_mode];

        if (is_duplex_half) {
            ret &= ~BIT(4); /* see mac_if reg def. */
        }
        return ret;
    }

    printf("Invalid speed(%d) & interface(%d) mode.\n", speed, if_mode);
    printf("Please assign which mode our eth will correctly work at.\n"
           "It may support 10M/100M MII, 10M/100M RMII, "
           "10M/100M/1000M RGMII interface.\n"
           "eg. if your board have two NICs, connecting each phy using "
           "mii and rgmii interface, you can use the module param "
           "'port_mode=mii,rgmii' to tell the driver.\n");
    BUG();

    /* can't reach here */
    return -1;
}

/* module parameter
 * 1) phy_intf=mii,rgmii if eth0=mii, eth1=rgmii
 *    phy_intf=mii if eth0=mii, eth1=mii;
 * 2) use_internal_phy=1 if eth1 use internal phy;
 * 3) phy0_addr=1, phy1_addr=2
 * 4) gmac_debug=1
 */
static void parse_module_parameters(void)
{
    unsigned long tmp;
    int gmac = 0;
    char *s, *e;

    s = getenv("gmac_debug");
    if (s) {
        gmac_debug = simple_strtoul(s, 0, 0); /* debug on */
    } else {
        gmac_debug = 0;
    }

    s = getenv("phy_link_times");
    if (s) {
        phy_link_times = simple_strtoul(s, 0, 0);
    } else {
        phy_link_times = DEFAULT_PHY_LINK_TIMES;
    }

    /* phy_intf = {mii | rgmii | rmii} [,{mii | rgmii | rmii}] */
    s = getenv("mdio_intf");
next_mii:
    if (s) {
        enum if_mode if_mode;

        while (*s == ' ' || *s == ',') {
            s++;
        }

        if (!strncmp(s, "mii", 3)) {
            if_mode = interface_mode_mii;
        } else if (!strncmp(s, "rmii", 4)) {
            if_mode = interface_mode_rmii;
        } else if (!strncmp(s, "rgmii", 5)) {
            if_mode = interface_mode_rgmii;
        } else {
            printf("Invalid phy_intf(mii, rmii, or rgmii)."
                   "Set ETH%d default to mii.\n",
                   gmac);
            if_mode = interface_mode_mii;
        }

        if (!gmac) { /* first time */
            gmac = 1;
            higmac_board_info[0].phy_intf = if_mode;
            /* in case phy_intf=mii */
#if GMAC_AT_LEAST_2PORT
            higmac_board_info[1].phy_intf = if_mode;
#endif
            s = strchr(s, ',');
            goto next_mii;
        } else {
#if GMAC_AT_LEAST_2PORT
            higmac_board_info[1].phy_intf = if_mode;
#endif
        }
    }
#if GMAC_AT_LEAST_2PORT
    /* use_mdio=0 or use_mdio=1 or use_mdio=0,1 or ... */
    gmac = 0;
    s = getenv("use_mdio");
next_mdio:
    if (s) {
        while (*s == ' ' || *s == ',') {
            s++;
        }

        tmp = simple_strtoul(s, &e, 10);
        if (tmp >= MDIO_BUS_NUMS) {
            printf("Invalid use_mdio, Set GMAC%d use mdio%d.\n",
                   gmac, gmac);
            tmp = gmac;
        }

        if (!gmac) { /* first time */
            higmac_board_info[0].mii_name = mdio_bus[tmp];
            higmac_board_info[1].mii_name = mdio_bus[tmp];
            gmac++;
            s = e;
            s = strchr(s, ',');
            goto next_mdio;
        } else {
            higmac_board_info[1].mii_name = mdio_bus[tmp];
        }
    }
#endif

    /* get phy addr */
    gmac = 0;
    s = getenv("phy_addr");
next_phyaddr:
    if (s) {
        while (*s == ' ' || *s == ',') {
            s++;
        }

        tmp = simple_strtoul(s, &e, 10);
        if (tmp == 0) {
            printf("Dectected gmac%d phyaddr set to 0, "
                   "is it right?\n",
                   gmac);
        } else if (tmp >= 32) {
            printf("Dectected gmac%d phyaddr "
                   "set to val(%lu) >= 32."
                   "This may not correct, "
                   "use default phyaddr=%d\n",
                   gmac, tmp,
                   higmac_board_info[gmac].phy_addr);

            tmp = higmac_board_info[gmac].phy_addr;
        }
        if (!gmac) { /* gmac0 */
            higmac_board_info[gmac].phy_addr = tmp;
            gmac++;
            s = e;
            s = strchr(s, ',');
            goto next_phyaddr;
        } else { /* gmac1 */
#if GMAC_AT_LEAST_2PORT
            higmac_board_info[gmac].phy_addr = tmp;
#endif
        }
    }

    if (gmac_debug) {
        printf("phy_link_times=%d\n", phy_link_times);
        for (gmac = 0; gmac < CONFIG_GMAC_NUMS; gmac++) {
            printf("ETH%d: port_mode=%s, "
                   "mii_name=%s, phy_addr=%d\n",
                   gmac,
                   phy_intf_str[higmac_board_info[gmac].phy_intf],
                   higmac_board_info[gmac].mii_name,
                   higmac_board_info[gmac].phy_addr);
        }
        printf("\n");
    }
}

static unsigned long rstate = 1;
/* trivial congruential random generators. from glibc. */
void srandom(unsigned long seed)
{
    rstate = seed ? seed : 1; /* dont allow a 0 seed */
}

unsigned long random(void)
{
    unsigned int next = rstate;
    int result;

    next *= 1103515245;
    next += 12345;
    result = (unsigned int)(next / 65536) % 2048;

    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int)(next / 65536) % 1024;

    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int)(next / 65536) % 1024;

    rstate = next;

    return result;
}

void random_ether_addr(unsigned char *mac)
{
    unsigned long ethaddr_low, ethaddr_high;

    srandom(get_timer(0));
    /*
     * setting the 2nd LSB in the most significant byte of
     * the address makes it a locally administered ethernet
     * address
     */
    ethaddr_high = (random() & 0xfeff) | 0x0200;
    ethaddr_low = random();

    mac[0] = ethaddr_high >> 8;
    mac[1] = ethaddr_high & 0xff;
    mac[2] = ethaddr_low >> 24;
    mac[3] = (ethaddr_low >> 16) & 0xff;
    mac[4] = (ethaddr_low >> 8) & 0xff;
    mac[5] = ethaddr_low & 0xff;

    mac[0] &= 0xfe; /* clear multicast bit */
    mac[0] |= 0x02; /* set local assignment bit (IEEE802) */
}

static int higmac_net_set_mac_address(struct eth_device *dev)
{
    struct higmac_netdev_local *ld = (struct higmac_netdev_local *)dev->priv;
    unsigned char mac[MAC_LEN] = { 0 };
    int ret;

    ret = eth_getenv_enetaddr("ethaddr", mac);
    if (!ret) {
        unsigned char ethaddr[20] = { 0 };

        random_ether_addr(mac);

        snprintf((char *)ethaddr, sizeof(ethaddr), "%02X:%02X:%02X:%02X:%02X:%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        ethaddr[sizeof(ethaddr) - 1] = '\0';
        setenv("ethaddr", (char *)ethaddr);
    }

    higmac_hw_set_macaddress(ld, mac);
    memcpy(dev->enetaddr, mac, MAC_LEN);
    print_mac(dev->enetaddr);

    return 0;
}

static int higmac_init_hw_desc_queue(struct higmac_netdev_local *ld)
{
    higmac_desc *queue_phy_addr = NULL;
    int queue_count = 0;

    /* init rx fq */
    queue_count = HIGMAC_HWQ_RX_FQ_DEPTH;

    queue_phy_addr = (higmac_desc *)memalign(ARCH_DMA_MINALIGN, queue_count * sizeof(higmac_desc));
    if (queue_phy_addr == NULL) {
        printf("alloc rx fq error!\n");
        goto _error_alloc_rx_fq;
    }

    memset((void *)queue_phy_addr, 0, queue_count * sizeof(higmac_desc));
#ifndef CONFIG_SYS_DCACHE_OFF
    flush_cache((unsigned long)queue_phy_addr,
                ALIGN(queue_count * sizeof(higmac_desc), ARCH_DMA_MINALIGN));
#endif
    ld->rx_fq_addr = queue_phy_addr;
    higmac_set_rx_fq_hwq_addr(ld, (phys_addr_t)queue_phy_addr);

    /* init rx bq */
    queue_count = HIGMAC_HWQ_RX_BQ_DEPTH;

    queue_phy_addr = (higmac_desc *)memalign(ARCH_DMA_MINALIGN, queue_count * sizeof(higmac_desc));
    if (queue_phy_addr == NULL) {
        printf("alloc rx bq error!\n");
        goto _error_alloc_rx_bq;
    }

    memset((void *)queue_phy_addr, 0, queue_count * sizeof(higmac_desc));
#ifndef CONFIG_SYS_DCACHE_OFF
    flush_cache((unsigned long)queue_phy_addr,
                ALIGN(queue_count * sizeof(higmac_desc), ARCH_DMA_MINALIGN));
#endif
    ld->rx_bq_addr = queue_phy_addr;
    higmac_set_rx_bq_hwq_addr(ld, (phys_addr_t)queue_phy_addr);

    /* init tx bq */
    queue_count = HIGMAC_HWQ_TX_BQ_DEPTH;

    queue_phy_addr = (higmac_desc *)memalign(ARCH_DMA_MINALIGN, queue_count * sizeof(higmac_desc));
    if (queue_phy_addr == NULL) {
        printf("alloc tx bq error!\n");
        goto _error_alloc_tx_bq;
    }

    memset((void *)queue_phy_addr, 0, queue_count * sizeof(higmac_desc));
#ifndef CONFIG_SYS_DCACHE_OFF
    flush_cache((unsigned long)queue_phy_addr,
                ALIGN(queue_count * sizeof(higmac_desc), ARCH_DMA_MINALIGN));
#endif
    ld->tx_bq_addr = queue_phy_addr;
    higmac_set_tx_bq_hwq_addr(ld, (phys_addr_t)queue_phy_addr);

    /* init tx rq */
    queue_count = HIGMAC_HWQ_TX_RQ_DEPTH;

    queue_phy_addr = (higmac_desc *)memalign(ARCH_DMA_MINALIGN, queue_count * sizeof(higmac_desc));
    if (queue_phy_addr == NULL) {
        printf("alloc tx rq error!\n");
        goto _error_alloc_tx_rq;
    }

    memset((void *)queue_phy_addr, 0, queue_count * sizeof(higmac_desc));
#ifndef CONFIG_SYS_DCACHE_OFF
    flush_cache((unsigned long)queue_phy_addr,
                ALIGN(queue_count * sizeof(higmac_desc), ARCH_DMA_MINALIGN));
#endif
    ld->tx_rq_addr = queue_phy_addr;
    higmac_set_tx_rq_hwq_addr(ld, (phys_addr_t)queue_phy_addr);

    return 0;

_error_alloc_tx_rq:
    free(ld->tx_bq_addr);
    ld->tx_bq_addr = NULL;

_error_alloc_tx_bq:
    free(ld->rx_bq_addr);
    ld->rx_bq_addr = NULL;

_error_alloc_rx_bq:
    free(ld->rx_fq_addr);
    ld->rx_fq_addr = NULL;

_error_alloc_rx_fq:
    return -1;
}

#if 0
static void higmac_destroy_hw_desc_queue(struct higmac_netdev_local *ld)
{
    free(ld->rx_fq_addr);
    free(ld->rx_bq_addr);
    free(ld->tx_bq_addr);
    free(ld->tx_rq_addr);

    ld->rx_fq_addr = NULL;
    ld->rx_bq_addr = NULL;
    ld->tx_bq_addr = NULL;
    ld->tx_rq_addr = NULL;
}
#endif

#define PHY_ID_KSZ8051 0x00221550
#define PHY_ID_KSZ8081 0x00221560
#define PHY_ID_KSZ9031 0x00221620
#define PHY_ID_MASK    0xFFFFFFF0

/* MMD: MDIO Manageable Device */
#define MACR  0x0D
#define MAADR 0x0E
static void phy_mmd_read(char *devname, u32 phyaddr,
                         u32 mmd_device, u32 regnum, u32 *val)
{
    int ret = 0;

    miiphy_write(devname, phyaddr, MACR, mmd_device);
    miiphy_write(devname, phyaddr, MAADR, regnum);
    miiphy_write(devname, phyaddr, MACR, 0x4000 | mmd_device);

    ret = miiphy_read(devname, phyaddr, MAADR, (unsigned short *)val);
    if (ret)
        printf("%s mmd read phy %d dev %d reg 0x%x failed\n",
               devname, phyaddr, mmd_device, regnum);
}

static void phy_mmd_write(char *devname, u32 phyaddr,
                          u32 mmd_device, u32 regnum, u32 val)
{
    miiphy_write(devname, phyaddr, MACR, mmd_device);
    miiphy_write(devname, phyaddr, MAADR, regnum);
    miiphy_write(devname, phyaddr, MACR, 0x4000 | mmd_device);

    miiphy_write(devname, phyaddr, MAADR, val);
}

static int phy_detected(char *devname, unsigned int phyaddr)
{
    u32 phy_id = 0;
    u16 id1 = 0, id2 = 0;

    if (miiphy_read(devname, phyaddr, MII_PHYSID1, &id1) != 0) {
        printf("PHY IDR1 read failed\n");
        return 0;
    };
    if (miiphy_read(devname, phyaddr, MII_PHYSID2, &id2) != 0) {
        printf("PHY IDR2 read failed\n");
        return 0;
    };

    phy_id = (id1 & 0xffff) << 16;
    phy_id |= (id2 & 0xffff);

    /* If the phy_id is all Fs, there is no device there */
    if (0xffffffff == phy_id || 0 == phy_id ||
        phy_id == 0xFFFF || phy_id == 0xFFFF0000) {
        return 0;
    }

    return 1;
}

static int phy_fixup(char *devname, unsigned int phyaddr, enum if_mode phymode)
{
    u32 phy_id;
    u16 id1 = 0, id2 = 0;

    if (miiphy_read(devname, phyaddr, MII_PHYSID1, &id1) != 0) {
        printf("PHY IDR1 read failed\n");
        return -1;
    };
    if (miiphy_read(devname, phyaddr, MII_PHYSID2, &id2) != 0) {
        printf("PHY IDR2 read failed\n");
        return -1;
    };

    phy_id = (id1 & 0xffff) << 16;
    phy_id |= (id2 & 0xffff);

    /* If the phy_id is all Fs, there is no device there */
    if (0xffffffff == phy_id || 0 == phy_id ||
        phy_id == 0xFFFF || phy_id == 0xFFFF0000) {
        return -1;
    }

    /* PHY-KSZ8051 */
    if (((phy_id & PHY_ID_MASK) == PHY_ID_KSZ8051) &&
        (phymode == interface_mode_rmii)) {
        unsigned int val = 0;

        if (miiphy_read(devname, phyaddr, 0x1F,
                        (unsigned short *)&val) != 0) {
            printf("PHY reg read failed\n");
            return -1;
        };
        val |= BIT(7); /* set phy RMII 50MHz clk; */
        if (miiphy_write(devname, phyaddr, 0x1F, val) != 0) {
            return -1;
        }

        if (miiphy_read(devname, phyaddr, 0x16,
                        (unsigned short *)&val) != 0) {
            printf("PHY reg read failed\n");
            return -1;
        };
        val |= BIT(1); /* set phy RMII override; */
        if (miiphy_write(devname, phyaddr, 0x16, val) != 0) {
            return -1;
        }
    }

    /* PHY-KSZ8081 */
    if (((phy_id & PHY_ID_MASK) == PHY_ID_KSZ8081) &&
        (phymode == interface_mode_rmii)) {
        unsigned int val = 0;

        if (miiphy_read(devname, phyaddr, 0x1F,
                        (unsigned short *)&val) != 0) {
            printf("PHY IDR1 read failed\n");
            return -1;
        };
        val |= BIT(7); /* set phy RMII 50MHz clk; */
        if (miiphy_write(devname, phyaddr, 0x1F, val) != 0) {
            return -1;
        }
    }

    /* PHY-KSZ9031 */
    if ((phy_id & PHY_ID_MASK) == PHY_ID_KSZ9031) {
        unsigned int val = 0;

        /* RX_CLK Pad Skew: 1_1101(+0.84) */
        phy_mmd_read(devname, phyaddr, 0x2, 0x8, &val);
        val = (val & ~0x1F) | 0x1D;
        phy_mmd_write(devname, phyaddr, 0x2, 0x8, val);
    }

    return 0;
}

static int higmac_net_adjust_link(struct higmac_netdev_local *ld)
{
    char *mii_name = higmac_board_info[ld->index].mii_name;
    int phy_addr = higmac_board_info[ld->index].phy_addr;
    enum if_mode phy_mode = higmac_board_info[ld->index].phy_intf;
    int stat = 0, speed = 0, is_duplex_half = 1, port_mode, phy_duplex;
    enum speed_mode speed_mode = speed_mode_100M;

    if (phy_addr == INVALID_PHY_ADDR) {
        return stat;
    }

    phy_fixup(mii_name, phy_addr, phy_mode);

    if (!phy_detected(mii_name, phy_addr)) {
        return stat;
    }

    stat |= miiphy_link(mii_name, phy_addr) ? HIGMAC_LINKED : 0;

    phy_duplex = miiphy_duplex(mii_name, phy_addr);
    if (phy_duplex == FULL) {
        stat |= HIGMAC_DUP_FULL;
        is_duplex_half = 0;
    }

    speed = miiphy_speed(mii_name, phy_addr);
    switch (speed) {
        case _10BASET:
            stat |= HIGMAC_SPD_10M;
            speed_mode = speed_mode_10M;
            break;
        default:
            printf("wired, phy speed!\n");
            break;
        case _100BASET:
            stat |= HIGMAC_SPD_100M;
            speed_mode = speed_mode_100M;
            break;
        case _1000BASET:
            stat |= HIGMAC_SPD_1000M;
            speed_mode = speed_mode_1000M;
            break;
    }

    if (ld->link_stat != stat) {
        if (stat & HIGMAC_LINKED) {
            port_mode = calculate_port_mode(speed_mode,
                                            higmac_board_info[ld->index].phy_intf,
                                            is_duplex_half);

            higmac_set_macif(ld, port_mode, speed_mode);

            if (is_duplex_half) {
                higmac_writel(ld, 0x0, MAC_DUPLEX_HALF_CTRL);
            } else {
                higmac_writel(ld, 0x1, MAC_DUPLEX_HALF_CTRL);
            }
        }
        ld->link_stat = stat;
    }

    return stat;
}

static int select_current_linked_phy(struct higmac_netdev_local *ld)
{
    int count = phy_link_times ?: DEFAULT_PHY_LINK_TIMES;
    int status;

    for (; count > 0; count--) {
        if (ctrlc()) {
            puts("\nAbort\n");
            goto link_failed;
        }

        status = higmac_net_adjust_link(ld);
        if (status & HIGMAC_LINKED) {
            goto link_on;
        }
        mdelay(100);
    }

link_failed:
    printf("ETH%d: PHY(%s, phyaddr=%d, %s) not link!\n",
           ld->index, higmac_board_info[ld->index].mii_name,
           higmac_board_info[ld->index].phy_addr,
           phy_intf_str[higmac_board_info[ld->index].phy_intf]);

    return -1;

link_on:
    printf("ETH%d: PHY(phyaddr=%d, %s) link UP: DUPLEX=%s : SPEED=%s\n",
           ld->index, higmac_board_info[ld->index].phy_addr,
           phy_intf_str[higmac_board_info[ld->index].phy_intf],
           (status & HIGMAC_DUP_FULL) ? "FULL" : "HALF",
           (status & HIGMAC_SPD_100M) ? "100M" : ((status & HIGMAC_SPD_10M) ? "10M" : "1000M"));

    miiphy_set_current_dev(higmac_board_info[ld->index].mii_name);

    return 0;
}

#define NET_IP_ALIGN 2
static int higmac_recv(struct eth_device *dev)
{
    struct higmac_netdev_local *ld = (struct higmac_netdev_local *)dev->priv;
    int timeout_us = 100000;
    u32 rx_fq_wr_offset = 0;
    u32 rx_fq_rd_offset = 0;
    u32 rx_bq_wr_offset = 0;
    u32 rx_bq_rd_offset = 0;
    int len = 0;
    int wr_rd_dist;
    int i;
    higmac_desc *rx_fq_desc = ld->rx_fq_addr;
    higmac_desc *rx_bq_desc = ld->rx_bq_addr;
    phys_addr_t addr = 0;

    rx_fq_wr_offset = higmac_readl_bits(ld, RX_FQ_WR_ADDR,
                                        BITS_RX_FQ_WR_ADDR);
    rx_fq_rd_offset = higmac_readl_bits(ld, RX_FQ_RD_ADDR,
                                        BITS_RX_FQ_RD_ADDR);

    if (rx_fq_wr_offset >= rx_fq_rd_offset) {
        wr_rd_dist = (HIGMAC_HWQ_RX_FQ_DEPTH << DESC_BYTE_SHIFT) - (rx_fq_wr_offset - rx_fq_rd_offset);
    } else {
        wr_rd_dist = rx_fq_rd_offset - rx_fq_wr_offset;
    }

    /* offset was counted on bytes, desc size = 2^5 */
    wr_rd_dist >>= DESC_BYTE_SHIFT;

    /* wr_rd_dist - 1 for logic reason.
     * Logic think the desc pool is full filled, ...?
     */
    for (i = 0; i < wr_rd_dist - 1; i++) {
        rx_fq_desc = ld->rx_fq_addr +
                     (rx_fq_wr_offset >> DESC_BYTE_SHIFT);
        addr = (phys_addr_t)memalign(ARCH_DMA_MINALIGN, HIETH_BUFFER_SIZE);
        if (!addr) {
            break;
        }
#ifndef CONFIG_SYS_DCACHE_OFF
        invalidate_dcache_range(addr,
                                ALIGN(addr + HIETH_BUFFER_SIZE, ARCH_DMA_MINALIGN));
#endif
        addr += NET_IP_ALIGN;
        rx_fq_desc->data_buff_addr = (u32)addr;
#if defined(CONFIG_64BIT)
        rx_fq_desc->reserve4 = ((u64)addr >> REG_BIT_WIDTH) << Q_ADDR_HI8_OFFSET;
#endif
        rx_fq_desc->descvid = DESC_VLD_FREE;
        rx_fq_desc->buffer_len = (HIETH_MAX_FRAME_SIZE - 1);
        rx_fq_desc->data_len = 8;
#ifndef CONFIG_SYS_DCACHE_OFF
        flush_cache((unsigned long)rx_fq_desc & ~(ARCH_DMA_MINALIGN - 1),
                    ALIGN(sizeof(*rx_fq_desc), ARCH_DMA_MINALIGN));
#endif

        rx_fq_wr_offset += DESC_SIZE;
        if (rx_fq_wr_offset >=
            (HIGMAC_HWQ_RX_FQ_DEPTH << DESC_BYTE_SHIFT)) {
            rx_fq_wr_offset = 0;
        }
        higmac_writel_bits(ld, rx_fq_wr_offset, RX_FQ_WR_ADDR,
                           BITS_RX_FQ_WR_ADDR);
    }

    /* enable Rx */
    /*
       higmac_desc_enable(ld, RX_OUTCFF_WR_DESC_ENA|RX_CFF_RD_DESC_ENA);
       higmac_writel_bits(ld, 1, PORT_EN, BITS_RX_EN);
    */
    rx_bq_wr_offset = higmac_readl_bits(ld, RX_BQ_WR_ADDR,
                                        BITS_RX_BQ_WR_ADDR);
    rx_bq_rd_offset = higmac_readl_bits(ld, RX_BQ_RD_ADDR,
                                        BITS_RX_BQ_RD_ADDR);
    rx_bq_desc += (rx_bq_rd_offset >> DESC_BYTE_SHIFT);

    while (--timeout_us && (rx_bq_wr_offset == rx_bq_rd_offset)) {
        udelay(1);
        rx_bq_wr_offset = higmac_readl_bits(ld,
                                            RX_BQ_WR_ADDR, BITS_RX_BQ_WR_ADDR);
    }

    if (!timeout_us) {
        /* printf("rx time out!\n"); */
        return -1;
    }

    rx_bq_rd_offset += DESC_SIZE;
    if (rx_bq_rd_offset >= (HIGMAC_HWQ_RX_BQ_DEPTH << DESC_BYTE_SHIFT)) {
        rx_bq_rd_offset = 0;
    }

#ifndef CONFIG_SYS_DCACHE_OFF
    invalidate_dcache_range((unsigned long)rx_bq_desc & ~(ARCH_DMA_MINALIGN - 1),
                            ALIGN((unsigned long)rx_bq_desc + sizeof(*rx_bq_desc), ARCH_DMA_MINALIGN));
#endif
    addr = rx_bq_desc->data_buff_addr;
#if defined(CONFIG_64BIT)
    addr |= (u64)(rx_bq_desc->reserve4 >> Q_ADDR_HI8_OFFSET) << REG_BIT_WIDTH;
#endif
    len = rx_bq_desc->data_len;
    if (HIGMAC_INVALID_RXPKG_LEN(len)) {
        higmac_writel_bits(ld, rx_bq_rd_offset, RX_BQ_RD_ADDR,
                           BITS_RX_BQ_RD_ADDR);
        addr -= NET_IP_ALIGN;
        free((void *)addr);
        addr = 0;
        return -1;
    }
    if (gmac_debug) {
        printf("got packet!\n");
    }

    if (gmac_debug) {
        char *buf = (char *)addr;
        int i;

        printf("[%s:%d]Packet length = %#4x\n", __FUNCTION__, __LINE__, len);
        for (i = 0; i < len; i++) {
            if (i % 16 == 0) {
                printf("%#4.4x", i);
            }
            if (i % 2 == 0) {
                printf(" ");
            }
            printf("%2.2x", ((unsigned char *)buf)[i]);
            if (i % 16 == 15) {
                printf("\n");
            }
        }
        printf("\n\n\n\n");
    }

#ifndef CONFIG_SYS_DCACHE_OFF
    invalidate_dcache_range(addr - NET_IP_ALIGN, ALIGN(addr + len, ARCH_DMA_MINALIGN));
#endif
    memcpy((void *)net_rx_packets[0],
           (const void *)addr, len);
    addr -= NET_IP_ALIGN;
    free((void *)addr);
    addr = 0;

    higmac_writel_bits(ld, rx_bq_rd_offset, RX_BQ_RD_ADDR,
                       BITS_RX_BQ_RD_ADDR);

    /* NetRecive */
    net_process_received_packet(net_rx_packets[0], len);

    /* disable Rx */
    /*
       higmac_writel_bits(ld, 0, PORT_EN, BITS_RX_EN);
       higmac_desc_disable(ld, RX_OUTCFF_WR_DESC_ENA|RX_CFF_RD_DESC_ENA);
    */
    return 0;
}

static int higmac_send(struct eth_device *dev, void *packet, int length)
{
    struct higmac_netdev_local *ld = (struct higmac_netdev_local *)dev->priv;
    int timeout_us = 1000;
    u32 tx_bq_wr_offset = 0;
    u32 tx_bq_rd_offset = 0;
    u32 tx_rq_wr_offset = 0;
    u32 tx_rq_rd_offset = 0;
    unsigned int tso_ver = 0;
    higmac_desc *tx_bq_desc = ld->tx_bq_addr;
    phys_addr_t addr = 0;

    tx_bq_wr_offset = higmac_readl_bits(ld,
                                        TX_BQ_WR_ADDR, BITS_TX_BQ_WR_ADDR);
    tx_bq_rd_offset = higmac_readl_bits(ld,
                                        TX_BQ_RD_ADDR, BITS_TX_BQ_RD_ADDR);

    if (tx_bq_rd_offset != tx_bq_wr_offset) {
        higmac_writel_bits(ld, tx_bq_rd_offset,
                           TX_BQ_WR_ADDR, BITS_TX_BQ_WR_ADDR);
        /* printf("tx bq is error!\n"); */
        return -1;
    }

    tso_ver = higmac_readl_bits(ld, CRF_MIN_PACKET, BIT_TSO_VERSION);

    tx_bq_desc += (tx_bq_wr_offset >> DESC_BYTE_SHIFT);
    addr = (phys_addr_t)packet;
    tx_bq_desc->data_buff_addr = (u32)addr;
#if defined(CONFIG_64BIT)
    tx_bq_desc->reserve3 = ((u64)addr >> REG_BIT_WIDTH) & TX_DESC_HI8_MASK;
#endif
    tx_bq_desc->descvid = DESC_VLD_BUSY;

    if (tso_ver) {
        tx_bq_desc->fl = 0;
    } else {
        tx_bq_desc->fl = DESC_FL_FULL;
    }

    tx_bq_desc->reserve1 = 0;
    tx_bq_desc->data_len = length;
    tx_bq_desc->buffer_len = HIETH_MAX_FRAME_SIZE - 1;
#ifndef CONFIG_SYS_DCACHE_OFF
    flush_cache((unsigned long)packet, ALIGN(length, ARCH_DMA_MINALIGN));
    flush_cache((unsigned long)tx_bq_desc & ~(ARCH_DMA_MINALIGN - 1),
                ALIGN(sizeof(*tx_bq_desc), ARCH_DMA_MINALIGN));
#endif

    tx_bq_wr_offset += DESC_SIZE;
    if (tx_bq_wr_offset >= (HIGMAC_HWQ_TX_BQ_DEPTH << DESC_BYTE_SHIFT)) {
        tx_bq_wr_offset = 0;
    }

    higmac_writel_bits(ld, tx_bq_wr_offset,
                       TX_BQ_WR_ADDR, BITS_TX_BQ_WR_ADDR);

    /* enable tx */
    /*
       higmac_writel_bits(ld, 1, PORT_EN, BITS_TX_EN);
       higmac_desc_enable(ld, TX_OUTCFF_WR_DESC_ENA|TX_CFF_RD_DESC_ENA);
    */
    tx_rq_wr_offset = higmac_readl_bits(ld,
                                        TX_RQ_WR_ADDR, BITS_TX_RQ_WR_ADDR);
    tx_rq_rd_offset = higmac_readl_bits(ld,
                                        TX_RQ_RD_ADDR, BITS_TX_RQ_RD_ADDR);

    tx_rq_rd_offset += DESC_SIZE;
    if (tx_rq_rd_offset >= (HIGMAC_HWQ_TX_RQ_DEPTH << DESC_BYTE_SHIFT)) {
        tx_rq_rd_offset = 0;
    }

    while (--timeout_us && (tx_rq_rd_offset != tx_rq_wr_offset)) {
        udelay(1);
        tx_rq_wr_offset = higmac_readl_bits(ld,
                                            TX_RQ_WR_ADDR, BITS_TX_RQ_WR_ADDR);
    }

    if (!timeout_us) {
        /* printf("send time out!\n"); */
        return -1;
    }

    higmac_writel_bits(ld, tx_rq_rd_offset,
                       TX_RQ_RD_ADDR, BITS_TX_RQ_RD_ADDR);
    if (gmac_debug) {
        printf("send packet!\n");
    }
    /* disable tx */
    /*
       higmac_desc_disable(ld, TX_OUTCFF_WR_DESC_ENA|TX_CFF_RD_DESC_ENA);
       higmac_writel_bits(ld, 0, PORT_EN, BITS_TX_EN);
    */
    return 0;
}

static int gmac_hw_inited;
static void higmac_hw_init(void)
{
    /* init once to save time */
    if (!gmac_hw_inited) {
        higmac_sys_init();

        gmac_hw_inited = 1;
    }
}

static int higmac_init(struct eth_device *dev, bd_t *bd)
{
    struct higmac_netdev_local *ld = (struct higmac_netdev_local *)dev->priv;
    char *mii_devname = higmac_board_info[ld->index].mii_name;
    int phy_addr = higmac_board_info[ld->index].phy_addr;
    enum if_mode phy_intf = higmac_board_info[ld->index].phy_intf;
    int ret = 0;

    higmac_hw_init();

    /* init once to save time */
    if (!ld->initalized) {
        if (!phy_detected(mii_devname, phy_addr)) {
            return -1;
        }

        miiphy_reset(mii_devname, phy_addr);

        if (phy_intf != interface_mode_rgmii) {
            unsigned short val = 0;
            if (!miiphy_read(mii_devname, phy_addr, MII_CTRL1000, &val)) {
                val &= ~(PHY_1000BTCR_1000FD | PHY_1000BTCR_1000HD);
                miiphy_write(mii_devname, phy_addr, MII_CTRL1000, val);
            }
        }

        higmac_glb_preinit_dummy(ld);

        ret = higmac_set_hwq_depth(ld);
        if (ret) {
            printf("init eth%d hw desc queue depth fail!\n", ld->index);
            return ret;
        }

        ret = higmac_init_hw_desc_queue(ld);
        if (ret) {
            printf("init eth%d hw desc queue fail!\n", ld->index);
            return ret;
        }
        ld->initalized = 1;
    }

    ret = select_current_linked_phy(ld);
    if (ret) {
        return ret;
    }

    higmac_net_set_mac_address(dev);
    higmac_desc_enable(ld, RX_OUTCFF_WR_DESC_ENA | RX_CFF_RD_DESC_ENA);
    higmac_writel_bits(ld, 1, PORT_EN, BITS_RX_EN);

    higmac_writel_bits(ld, 1, PORT_EN, BITS_TX_EN);
    higmac_desc_enable(ld, TX_OUTCFF_WR_DESC_ENA | TX_CFF_RD_DESC_ENA);

    return 0;
}

static void higmac_halt(struct eth_device *dev)
{
    struct higmac_netdev_local *ld = (struct higmac_netdev_local *)dev->priv;

    higmac_writel_bits(ld, 0, PORT_EN, BITS_RX_EN);
    higmac_desc_disable(ld, RX_OUTCFF_WR_DESC_ENA | RX_CFF_RD_DESC_ENA);

    higmac_desc_disable(ld, TX_OUTCFF_WR_DESC_ENA | TX_CFF_RD_DESC_ENA);
    higmac_writel_bits(ld, 0, PORT_EN, BITS_TX_EN);

    /* higmac_glb_preinit_dummy(current_ld); */
#if 0
    higmac_destroy_hw_desc_queue(current_ld);
    higmac_mdiobus_driver_exit();
    higmac_sys_exit();
#endif
}

static int higmac_register_dev(port_id_t port_id)
{
    struct eth_device *dev;

    dev = malloc(sizeof(*dev));
    if (dev == NULL) {
        return -1;
    }
    memset(dev, 0, sizeof(*dev));

    dev->iobase = mac_iobase[port_id];
    dev->init = higmac_init;
    dev->halt = higmac_halt;
    dev->send = higmac_send;
    dev->recv = higmac_recv;
    dev->priv = &higmac_board_info[port_id].higmac_ld;
    snprintf(dev->name, sizeof(dev->name) - 1, "gmac%d", port_id);

    eth_register(dev);

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
    struct mii_dev *bus = mdio_alloc();

    if (!bus) {
        free(dev);
        debug("Failed to allocate MDIO bus\n");
        return -ENOMEM;
    }

    bus->read = higmac_mdiobus_read;
    bus->write = higmac_mdiobus_write;
    snprintf(bus->name, sizeof(bus->name), mdio_bus[port_id]);

    if (mdio_register(bus)) {
        mdio_free(bus);
        free(dev);
        return -1;
    }
#endif

    return 0;
}

int higmac_initialize(bd_t *bis)
{
    int ret;

    parse_module_parameters();

    ret = higmac_register_dev(GSF0_PORT0);
    if (ret) {
        return ret;
    }

#if GMAC_AT_LEAST_2PORT
    ret = higmac_register_dev(GSF0_PORT1);
    if (ret) {
        return ret;
    }
#endif

#if GMAC_AT_LEAST_3PORT
    ret = higmac_register_dev(GSF1_PORT0);
    if (ret) {
        return ret;
    }
#endif

    return 0;
}
