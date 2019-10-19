#include "util.h"
#include "higmac.h"
#include "ctrl.h"

void higmac_set_macif(struct higmac_netdev_local *ld, int mode, unsigned int speed)
{
    void __iomem *p = (void __iomem *)CRG_REG_BASE;
    unsigned long v;

    /* enable change: port_mode */
    higmac_writel_bits(ld, 1, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);
    if (speed == 2) { /* FIXME */
        speed = 5; /* 1000M */
    }
    higmac_writel_bits(ld, speed, PORT_MODE, BITS_PORT_MODE);
    /* disable change: port_mode */
    higmac_writel_bits(ld, 0, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);

    /* soft reset mac_if */
    v = readl(p + REG_ETH_CRG);
    if (ld->index) {
#if GMAC_AT_LEAST_2PORT
        v |= BIT_MACIF1_RST;
#endif
    } else {
        v |= BIT_MACIF0_RST;
    }
    writel(v, p + REG_ETH_CRG);

    /* config mac_if */
    if (ld->index) {
#if GMAC_AT_LEAST_2PORT
        writel(mode, HIGMAC_MACIF1_CTRL);
#endif
    } else {
        writel(mode, HIGMAC_MACIF0_CTRL);
    }

    v = readl(p + REG_ETH_CRG);
    if (ld->index) {
#if GMAC_AT_LEAST_2PORT
        v &= ~BIT_MACIF1_RST;
#endif
    } else {
        v &= ~BIT_MACIF0_RST;
    }
    writel(v, p + REG_ETH_CRG);
}

int higmac_hw_set_macaddress(struct higmac_netdev_local *ld, unsigned char *mac)
{
    unsigned long reg;

    reg = mac[1] | (mac[0] << 8);
    higmac_writel(ld, reg, STATION_ADDR_HIGH);

    reg = mac[5] | (mac[4] << 8) | (mac[3] << 16) | (mac[2] << 24);
    higmac_writel(ld, reg, STATION_ADDR_LOW);

    return 0;
}

int higmac_hw_get_macaddress(struct higmac_netdev_local *ld, unsigned char *mac)
{
    unsigned long reg;

    reg = higmac_readl(ld, STATION_ADDR_HIGH);
    mac[0] = (reg >> 8) & 0xff;
    mac[1] = reg & 0xff;

    reg = higmac_readl(ld, STATION_ADDR_LOW);
    mac[2] = (reg >> 24) & 0xff;
    mac[3] = (reg >> 16) & 0xff;
    mac[4] = (reg >> 8) & 0xff;
    mac[5] = reg & 0xff;

    return 0;
}

static inline int _higmac_read_irqstatus(struct higmac_netdev_local *ld)
{
    int status;

    status = higmac_readl(ld, STATUS_PMU_INT);

    return status;
}

int higmac_clear_irqstatus(struct higmac_netdev_local *ld, int irqs)
{
    int status;

    higmac_writel(ld, irqs, RAW_PMU_INT);
    status = _higmac_read_irqstatus(ld);

    return status;
}

/* FIXME */
int higmac_glb_preinit_dummy(struct higmac_netdev_local *ld)
{
    /* drop packet enable */
    higmac_writel(ld, 0x3F, REC_FILT_CONTROL);
    higmac_writel_bits(ld, 0, REC_FILT_CONTROL, BIT_BC_DROP_EN);

    /* clear all interrupt status */
    higmac_clear_irqstatus(ld, RAW_INT_ALL_MASK);

    /* disable interrupts */
    higmac_writel(ld, ~RAW_INT_ALL_MASK, ENA_PMU_INT);

    return 0;
}

void higmac_external_phy_reset(void)
{
    unsigned int v = 0;

#ifdef HIGAMC_USE_GPIO_RESET_PHY
    /* use GPIO0_1 to reset external phy */
    /* Set Direction output */
    v = readl(HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DIR_OFS);
    v |= HIGMAC_RESET_GPIO_DIR_OUT;
    writel(v, HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DIR_OFS);

    /* Set GPIO0_1=1 */
    writel(HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DATA_OFS);
    udelay(50000);
    /* Set GPIO0_1=0 to reset phy */
    writel(~HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DATA_OFS);
    udelay(200000);

    /* Set GPIO0_1=1 to cancel reset phy */
    writel(HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DATA_OFS);
    udelay(50000);
#else
    /* use CRG register to reset external phy */
    v = readl(CRG_REG_BASE + REG_ETH_CRG);
    v |= BIT_EXT_PHY0_RST; /* reset */
#if GMAC_AT_LEAST_2PORT
    v |= BIT_EXT_PHY1_RST;
#endif
    writel(v, CRG_REG_BASE + REG_ETH_CRG);

    udelay(50 * 1000); /* wait for phy reset time */

    v = readl(CRG_REG_BASE + REG_ETH_CRG);
    v &= ~BIT_EXT_PHY0_RST; /* undo reset */
#if GMAC_AT_LEAST_2PORT
    v &= ~BIT_EXT_PHY1_RST;
#endif
    writel(v, CRG_REG_BASE + REG_ETH_CRG);

    udelay(60 * 1000); /* wait for future MDIO operation */
#endif
}

void higmac_sys_init(void)
{
    unsigned long p = 0;
    volatile unsigned int v = 0;

    p = (unsigned long)(CRG_REG_BASE);

    v = readl(p + REG_ETH_CRG);

    /* phy clk select 25MHz */
    v &= ~BIT_EXT_PHY0_CLK_SELECT;
    v |= PHY0_CLK_25M;
#if GMAC_AT_LEAST_2PORT
    v &= ~BIT_EXT_PHY1_CLK_SELECT;
    v |= PHY1_CLK_25M;
#endif
    /* enable clk */
    v |= (BIT_GMAC0_CLK_EN | BIT_GMACIF0_CLK_EN);
#if GMAC_AT_LEAST_2PORT
    v |= BIT_GSF_PUB_CLK_EN;
    v |= (BIT_GMAC1_CLK_EN | BIT_GMACIF1_CLK_EN);
#endif

#ifdef CONFIG_HIGMAC_RMII0_CLK_USE_EXTERNAL_PAD
    if (higmac_board_info[0].phy_intf == interface_mode_rmii) {
        v |= BIT_RMII0_CLKSEL_PAD; /* rmii select pad clk */
    }
#endif
#if GMAC_AT_LEAST_2PORT
#ifdef CONFIG_HIGMAC_RMII1_CLK_USE_EXTERNAL_PAD
    if (higmac_board_info[1].phy_intf == interface_mode_rmii) {
        v |= BIT_RMII1_CLKSEL_PAD; /* rmii select pad clk */
    }
#endif
#endif

    writel(v, p + REG_ETH_CRG);

    /* soft reset */
    v = readl(p + REG_ETH_CRG);
    v |= BIT_GMAC0_RST;
#if GMAC_AT_LEAST_2PORT
    v |= BIT_GMAC1_RST;
#endif
    writel(v, p + REG_ETH_CRG);

    udelay(100);

    v = readl(p + REG_ETH_CRG);
    v &= ~BIT_GMAC0_RST;
#if GMAC_AT_LEAST_2PORT
    v &= ~BIT_GMAC1_RST;
#endif
    writel(v, p + REG_ETH_CRG);

    writel(0xe, HIGMAC_DUAL_MAC_CRF_ACK_TH);

    higmac_external_phy_reset();
}

void higmac_sys_exit(void)
{
}

void higmac_sys_allstop(void)
{
}

int higmac_set_hwq_depth(struct higmac_netdev_local *ld)
{
    if (HIGMAC_HWQ_RX_FQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
        BUG();
        return -1;
    }

    higmac_writel_bits(ld, 1, RX_FQ_REG_EN,
                       BITS_RX_FQ_DEPTH_EN);

    higmac_writel_bits(ld, HIGMAC_HWQ_RX_FQ_DEPTH << DESC_WORD_SHIFT,
                       RX_FQ_DEPTH, BITS_RX_FQ_DEPTH);

    higmac_writel_bits(ld, 0, RX_FQ_REG_EN,
                       BITS_RX_FQ_DEPTH_EN);

    if (HIGMAC_HWQ_RX_BQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
        BUG();
        return -1;
    }

    higmac_writel_bits(ld, 1, RX_BQ_REG_EN,
                       BITS_RX_BQ_DEPTH_EN);

    higmac_writel_bits(ld, HIGMAC_HWQ_RX_BQ_DEPTH << DESC_WORD_SHIFT,
                       RX_BQ_DEPTH, BITS_RX_BQ_DEPTH);

    higmac_writel_bits(ld, 0, RX_BQ_REG_EN,
                       BITS_RX_BQ_DEPTH_EN);

    if (HIGMAC_HWQ_TX_BQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
        BUG();
        return -1;
    }

    higmac_writel_bits(ld, 1, TX_BQ_REG_EN,
                       BITS_TX_BQ_DEPTH_EN);

    higmac_writel_bits(ld, HIGMAC_HWQ_TX_BQ_DEPTH << DESC_WORD_SHIFT,
                       TX_BQ_DEPTH, BITS_TX_BQ_DEPTH);

    higmac_writel_bits(ld, 0, TX_BQ_REG_EN,
                       BITS_TX_BQ_DEPTH_EN);

    if (HIGMAC_HWQ_TX_RQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
        BUG();
        return -1;
    }

    higmac_writel_bits(ld, 1, TX_RQ_REG_EN,
                       BITS_TX_RQ_DEPTH_EN);

    higmac_writel_bits(ld, HIGMAC_HWQ_TX_RQ_DEPTH << DESC_WORD_SHIFT,
                       TX_RQ_DEPTH, BITS_TX_RQ_DEPTH);

    higmac_writel_bits(ld, 0, TX_RQ_REG_EN,
                       BITS_TX_RQ_DEPTH_EN);

    return 0;
}

int higmac_set_rx_fq_hwq_addr(struct higmac_netdev_local *ld,
                              phys_addr_t phy_addr)
{
    higmac_writel_bits(ld, 1, RX_FQ_REG_EN,
                       BITS_RX_FQ_START_ADDR_EN);

    higmac_writel(ld, (u32)phy_addr, RX_FQ_START_ADDR);
#if defined(CONFIG_64BIT)
    higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), RX_FQ_DEPTH,
                       BITS_RX_FQ_ADDR_HI8);
#endif

    higmac_writel_bits(ld, 0, RX_FQ_REG_EN,
                       BITS_RX_FQ_START_ADDR_EN);

    return 0;
}

int higmac_set_rx_bq_hwq_addr(struct higmac_netdev_local *ld,
                              phys_addr_t phy_addr)
{
    higmac_writel_bits(ld, 1, RX_BQ_REG_EN,
                       BITS_RX_BQ_START_ADDR_EN);

    higmac_writel(ld, (u32)phy_addr, RX_BQ_START_ADDR);
#if defined(CONFIG_64BIT)
    higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), RX_BQ_DEPTH,
                       BITS_RX_BQ_ADDR_HI8);
#endif

    higmac_writel_bits(ld, 0, RX_BQ_REG_EN,
                       BITS_RX_BQ_START_ADDR_EN);

    return 0;
}

int higmac_set_tx_bq_hwq_addr(struct higmac_netdev_local *ld,
                              phys_addr_t phy_addr)
{
    higmac_writel_bits(ld, 1, TX_BQ_REG_EN,
                       BITS_TX_BQ_START_ADDR_EN);

    higmac_writel(ld, (u32)phy_addr, TX_BQ_START_ADDR);
#if defined(CONFIG_64BIT)
    higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), TX_BQ_DEPTH,
                       BITS_TX_BQ_ADDR_HI8);
#endif

    higmac_writel_bits(ld, 0, TX_BQ_REG_EN,
                       BITS_TX_BQ_START_ADDR_EN);

    return 0;
}

int higmac_set_tx_rq_hwq_addr(struct higmac_netdev_local *ld,
                              phys_addr_t phy_addr)
{
    higmac_writel_bits(ld, 1, TX_RQ_REG_EN,
                       BITS_TX_RQ_START_ADDR_EN);

    higmac_writel(ld, (u32)phy_addr, TX_RQ_START_ADDR);
#if defined(CONFIG_64BIT)
    higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), TX_RQ_DEPTH,
                       BITS_TX_RQ_ADDR_HI8);
#endif

    higmac_writel_bits(ld, 0, TX_RQ_REG_EN,
                       BITS_TX_RQ_START_ADDR_EN);

    return 0;
}

u32 higmac_desc_enable(struct higmac_netdev_local *ld, u32 desc_ena)
{
    u32 old;

    old = higmac_readl(ld, DESC_WR_RD_ENA);
    higmac_writel(ld, old | desc_ena, DESC_WR_RD_ENA);

    return old;
}

u32 higmac_desc_disable(struct higmac_netdev_local *ld, u32 desc_dis)
{
    u32 old;

    old = higmac_readl(ld, DESC_WR_RD_ENA);
    higmac_writel(ld, old & (~desc_dis), DESC_WR_RD_ENA);

    return old;
}

void higmac_desc_flush(struct higmac_netdev_local *ld)
{
    higmac_writel_bits(ld, 1, STOP_CMD, BITS_TX_STOP_EN);
    while (higmac_readl_bits(ld, FLUSH_CMD, BITS_TX_FLUSH_FLAG) != 1);
    higmac_writel_bits(ld, 1, FLUSH_CMD, BITS_TX_FLUSH_CMD);
    while (higmac_readl_bits(ld, FLUSH_CMD, BITS_TX_FLUSH_FLAG) != 0);
    higmac_writel_bits(ld, 0, FLUSH_CMD, BITS_TX_FLUSH_CMD);
    higmac_writel_bits(ld, 0, STOP_CMD, BITS_TX_STOP_EN);
    higmac_writel_bits(ld, 1, STOP_CMD, BITS_RX_STOP_EN);
    while (higmac_readl_bits(ld, FLUSH_CMD, BITS_RX_FLUSH_FLAG) != 1);
    higmac_writel_bits(ld, 1, FLUSH_CMD, BITS_RX_FLUSH_CMD);
    while (higmac_readl_bits(ld, FLUSH_CMD, BITS_RX_FLUSH_FLAG) != 0);
    higmac_writel_bits(ld, 0, FLUSH_CMD, BITS_RX_FLUSH_CMD);
    higmac_writel_bits(ld, 0, STOP_CMD, BITS_RX_STOP_EN);
}
