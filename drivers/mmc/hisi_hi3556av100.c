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

#define MIN_FREQ 400000
#define NOT_FOUND -1
#define PHASE_SCALE 32

#define EMMC_PHY_INIT_CTRL      (EMMC_PHY_BASE + 0x4)
#define PHY_INIT_EN             BIT(0)
#define PHY_DLYMEAS_EN          BIT(2)
#define PHY_ZCAL_EN             BIT(3)

#define EMMC_PHY_DLY_CTL1       (EMMC_PHY_BASE + 0x254)
#define PHY_INV_CLK             BIT(31)

#define EMMC_PHY_IOCTL_PUPD     (EMMC_PHY_BASE + 0x260)
#define RG_EMMC_PUPD_EN         0x7ff
#define RG_EMMC_PULL_UP         0x2ff

#define EMMC_PHY_IOCTL_RONSEL_1_0   (EMMC_PHY_BASE + 0x264)
#define RG_EMMC_RONSEL1             0x7ff
#define RG_EMMC_RONSEL0             0x7ff
#define EMMC_PHY_IOCTL_OD_RONSEL_2  (EMMC_PHY_BASE + 0x268)

#define EMMC_PHY_IOCTL_IOE      (EMMC_PHY_BASE + 0x26c)
#define DA_EMMC_IE              0x7ff
#define DA_EMMC_E               0x6ff

#define EMMC_RSTN_PULL_UP_EN	BIT(8)
#define PIN_SEL_EMMC_FUNC	0x1
#define PIN_SEL_EMMC_POWER_EN	0x2

#define REG_PERI_STAT	(SYS_CTRL_REG_BASE + 0x30)
#define EMMC_PULL_UP_DISABLE    BIT(13)

#define REG_MISC_CTRL17         (MISC_REG_BASE + MISC_CTRL17)
#define REG_MISC_CTRL18         (MISC_REG_BASE + MISC_CTRL18)
#define SDIO0_PWRSW_SEL_1V8		BIT(5)
#define SDIO0_PWR_EN			BIT(4)
#define SDIO0_IO_MODE_SEL_1V8	BIT(1)
#define SDIO0_PWR_CTRL_BY_MISC  BIT(0)

#define SDIO_SAMPL_DLL_SRST_REQ	(0x1 << 30)
#define SDIO_DRV_DLL_SRST_REQ	(0x1 << 29)
#define SDIO_CLK_EN		(0x1 << 28)
#define SDIO_SRST_REQ	(0x1 << 27)

#define REG_EMMC_DRV_DLL_CTRL	(CRG_REG_BASE + 0x1b0)
#define REG_SDIO0_DRV_DLL_CTRL  (CRG_REG_BASE + 0x1d4)
#define SDIO_DRV_PHASE_SEL_MASK (0x1f << 24)
#define SDIO_DRV_SEL(phase)     ((phase) << 24)

#define REG_EMMC_DS_DLL_CTRL		(CRG_REG_BASE + 0x1b4)
#define EMMC_DS_DLL_MODE_SSEL       BIT(13)
#define EMMC_DS_DLL_SSEL_MASK       (0x1fff)
#define REG_EMMC_DS180_DLL_CTRL     (CRG_REG_BASE + 0x1b8)
#define EMMC_DS180_DLL_BYPASS       BIT(15)
#define REG_EMMC_DS_DLL_STATUS      (CRG_REG_BASE + 0x1c8)
#define EMMC_DS_DLL_LOCK            BIT(15)
#define EMMC_DS_DLL_MDLY_TAP_MASK   (0x1fff)

#define REG_EMMC_DRV_DLL_STATUS     (CRG_REG_BASE + 0x1c4)
#define REG_SDIO0_DRV_DLL_STATUS    (CRG_REG_BASE + 0x1e8)
#define SDIO_DRV_DLL_LOCK           BIT(15)

#define REG_EMMC_SAMPL_DLL_CTRL     (CRG_REG_BASE + 0x1a8)
#define REG_SDIO0_SAMPL_DLL_CTRL    (CRG_REG_BASE + 0x1ec)
#define SDIO_SAMPL_DLL_SLAVE_EN     BIT(16)

#define REG_EMMC_SAMPL_DLL_STATUS   (CRG_REG_BASE + 0x1bc)
#define REG_SDIO0_SAMPL_DLL_STATUS  (CRG_REG_BASE + 0x1e0)
#define SDIO_SAMPL_DLL_SLAVE_READY  BIT(14)

#define REG_EMMC_SAMPLB_DLL_CTRL    0x1ac
#define SDIO_SAMPLB_DLL_CLK_MASK    (0x1f << 24)
#define SDIO_SAMPLB_SEL(phase)      ((phase) << 24)

#define REG_IO_CFG_0_BASE		0x04058000
#define EMMC_MUXCTRL_REG_START  0x8c    /* iocfg_reg35 */
#define EMMC_MUXCTRL_REG_END    0xbc    /* iocfg_reg47 */

#define IO_CFG_REG46            0xb8
#define IO_CFG_REG47            0xbc

#define REG_BASE_MISC			0x04528000
#define DRV50_VAL				0x000
#define BIT_RG_EMMC_LHEN_IN		(0x3f << 17)
#define BIT_EMMC_ISO_EN			(0x1 << 16)
#define DRV50_NO_OD_val			0xfff

#define PERI_CRG_EMMC			0x1a8
#define MMC_CLK_SEL_SHIFT      	24
#define MMC_RST					(0x1 << 27)
#define MMC_CLK_EN				(0x1 << 28)
#define MMC_DRV_DLL_RST			(0x1 << 29)
#define MMC_SAM_DLL_RST			(0x1 << 30)
#define MMC_DRV_PHASE_MASK		(0x1f << 24)
#define SW_TUNING_EN			(0x1 << 4)
#define MMC_CLK_50M				0x2
#define SW_TUNING_45			0x4
#define SW_TUNING_0				0x0

#define PERI_EMMC_DRV_DLL		0x1c4

static void hisi_dll_reset_assert(struct sdhci_host *host)
{
	unsigned long crg_addr;
	unsigned int reg;

	crg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_CRG : REG_SDIO0_CRG;
	reg = readl(crg_addr);
	reg |= SDIO_DRV_DLL_SRST_REQ | SDIO_SAMPL_DLL_SRST_REQ;
	writel(reg, crg_addr);
}

static void hisi_dll_reset_deassert(struct sdhci_host *host)
{
	unsigned long crg_addr;
	unsigned int reg;

	crg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_CRG : REG_SDIO0_CRG;
	reg = readl(crg_addr);
	reg &= ~(SDIO_DRV_DLL_SRST_REQ | SDIO_SAMPL_DLL_SRST_REQ);
	writel(reg, crg_addr);
}

static void hisi_set_crg(struct sdhci_host *host, unsigned int clk)
{
	unsigned long crg_addr;
	unsigned int sel, reg;
	unsigned int clk_mux[8] = {100000, 25000000, 49500000,
		99000000, 187500000, 150000000, 198000000, 400000};

	crg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_CRG : REG_SDIO0_CRG;
	reg = readl(crg_addr);
	reg &= ~MMC_CLK_SEL_MASK;

	if (clk <= MIN_FREQ)
		sel = 7;
	else {
		for (sel = 6; sel > 0; sel--) {
			if (clk >= clk_mux[sel])
				break;
		}
	}

	reg |= MMC_CLK_SEL(sel);
	writel(reg, crg_addr);
}

static void hisi_wait_ds180_dll_ready(void)
{
	//Do nothing
	return;
}

static void hisi_wait_ds_dll_lock(void)
{
	unsigned int reg, timeout = 20;

	do {
		reg = readl(REG_EMMC_DS_DLL_STATUS);
		if (reg & EMMC_DS_DLL_LOCK)
			return;

		udelay(1000);
		timeout--;
	} while (timeout > 0);

	printf("DS DLL master not locked.\n");
}

static void hisi_set_ds_dll_delay(void)
{
	//Do nothing
	return;
}

static void hisi_mmc_priv_init(struct sdhci_host *host)
{
	unsigned short ctrl;
	unsigned int reg;

	ctrl = sdhci_readw(host, SDHCI_MSHC_CTRL);
	ctrl &= ~SDHCI_CMD_CONFLIT_CHECK;
	sdhci_writew(host, ctrl, SDHCI_MSHC_CTRL);

	reg = sdhci_readl(host, SDHCI_AXI_MBIIU_CTRL);
	reg |= SDHCI_GM_WR_OSRC_LMT | SDHCI_GM_RD_OSRC_LMT;
	sdhci_writel(host, reg, SDHCI_AXI_MBIIU_CTRL);

	reg  = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	reg |= SDHCI_EDGE_DETECT_EN | SDHCI_DOUT_EN_F_EDGE;
	sdhci_writel(host, reg, SDHCI_MULTI_CYCLE);
}

void mmc_muxctrl_config(void)
{
	unsigned int offt;
	unsigned int val;

	/* set emmc multiplexing */
	for (offt = EMMC_MUXCTRL_REG_START;
			offt <= EMMC_MUXCTRL_REG_END;
			offt += 4) {
		val = readl(REG_IO_CFG_0_BASE + offt);
		val &= ~0xf;
		writel(val, REG_IO_CFG_0_BASE + offt);
	}

	val = readl(REG_IO_CFG_0_BASE + IO_CFG_REG46);
	val |= (0x1 << 10);
	writel(val, REG_IO_CFG_0_BASE + IO_CFG_REG46);

	val = readl(REG_IO_CFG_0_BASE + IO_CFG_REG47);
	val |= (0x1 << 10);
	writel(val, REG_IO_CFG_0_BASE + IO_CFG_REG47);
}

static void sd_hardware_init(void)
{
	unsigned int reg, ctrl;

	/* clk enable */
	reg = readl(REG_SDIO0_CRG);
	reg |= SDIO_CLK_EN;
	writel(reg, REG_SDIO0_CRG);

	/* reset assert*/
	reg = readl(REG_SDIO0_CRG);
	reg |= SDIO_SRST_REQ | SDIO_DRV_DLL_SRST_REQ
		| SDIO_SAMPL_DLL_SRST_REQ;
	writel(reg, REG_SDIO0_CRG);
	udelay(25);

	/* reset deassert */
	reg &= ~SDIO_SRST_REQ;
	writel(reg, REG_SDIO0_CRG);
	udelay(1);

	ctrl = readl(REG_MISC_CTRL18);
	ctrl |= SDIO0_PWR_EN | SDIO0_PWR_CTRL_BY_MISC;
	ctrl &= ~(SDIO0_IO_MODE_SEL_1V8 | SDIO0_PWRSW_SEL_1V8);
	writel(ctrl, REG_MISC_CTRL18);

	udelay(5000);
}

static int emmc_hardware_init(void)
{
	unsigned int reg = 0;
	unsigned int timeout = 10;

	mmc_muxctrl_config();

	/* emmc phy config */
	reg = readl(REG_BASE_MISC + MISC_CTRL17);
	reg &= ~(BIT_RG_EMMC_LHEN_IN | BIT_EMMC_ISO_EN);
	writel(reg, REG_BASE_MISC + MISC_CTRL17);

	/*enable phy init*/
	reg = readl(EMMC_PHY_INIT_CTRL);
	reg |= (PHY_INIT_EN | PHY_ZCAL_EN);
	reg &= ~PHY_DLYMEAS_EN;
	writel(reg, EMMC_PHY_INIT_CTRL);

	/*wait phy init and zcal done*/
	for(;;) {
		reg = readl(EMMC_PHY_INIT_CTRL);
		if (!(reg & (PHY_INIT_EN | PHY_ZCAL_EN)))
			break;
		udelay(100);
		if (timeout-- == 0) {
			printf("wait mmc phy cal done time out\n");
			return -1;
		}
	}

	/* DRV50 */
	writel(DRV50_VAL, EMMC_PHY_IOCTL_RONSEL_1_0);
	/* DRV50, OD = 0 */
	writel(DRV50_NO_OD_val, EMMC_PHY_IOCTL_OD_RONSEL_2);

	/* invert the TXCLK */
	reg = readl(EMMC_PHY_DLY_CTL1);
	reg &= ~PHY_INV_CLK;
	writel(reg, EMMC_PHY_DLY_CTL1);

	/*enable pull up*/
	reg = readl(REG_BASE_SCTL + REG_PERI_STAT);
	if (reg & EMMC_PULL_UP_DISABLE)
		/* no pull-up */
		writel(RG_EMMC_PULL_UP << 16, EMMC_PHY_IOCTL_PUPD);
	else
		/* pull-up */
		writel((RG_EMMC_PULL_UP << 16) | RG_EMMC_PUPD_EN, EMMC_PHY_IOCTL_PUPD);

	writel((DA_EMMC_IE << 16) | DA_EMMC_E, EMMC_PHY_IOCTL_IOE);

	/* enable ck_en */
	reg = readl(CRG_REG_BASE + PERI_CRG_EMMC);
	reg |= MMC_CLK_EN;
	writel(reg, CRG_REG_BASE + PERI_CRG_EMMC);

	/* eMMC reset assert*/
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_SRST_REQ | SDIO_DRV_DLL_SRST_REQ
		| SDIO_SAMPL_DLL_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(25);

	/* eMMC reset deassert */
	reg &= ~SDIO_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(1);

	return 0;
}

static void hisi_mmc_set_ioconfig(struct sdhci_host *host)
{
	unsigned int reg;

	if (host->type == MMC_TYPE_MMC) {
		if (host->mmc->timing == MMC_TIMING_MMC_HS200
				|| host->mmc->timing == MMC_TIMING_MMC_HS400
				|| host->mmc->timing == MMC_TIMING_MMC_HS) {
			reg = sdhci_readw(host, SDHCI_EMMC_CTRL);
			reg |= SDHCI_CARD_IS_EMMC;
			sdhci_writew(host, reg, SDHCI_EMMC_CTRL);

			/* set drv strength to 50ohm */
			writel(0x6ff, EMMC_PHY_IOCTL_RONSEL_1_0);
			writel(0x6ff, EMMC_PHY_IOCTL_OD_RONSEL_2);
		}
	}
}

static void hisi_set_phase(struct sdhci_host *host)
{
	unsigned int drv_phase, sample_phase;

	if (host->mmc->timing == MMC_TIMING_MMC_HS400) {
		drv_phase = 9;	/*101.25 degree*/
		sample_phase = host->tuning_phase;
	} else if (host->mmc->timing == MMC_TIMING_MMC_HS200) {
		drv_phase = 20;	/*225 degree*/
		sample_phase = host->tuning_phase;
	} else if (host->mmc->timing == MMC_TIMING_UHS_SDR104) {
		drv_phase = 20;	/*225 degree*/
		sample_phase = host->tuning_phase;

	} else if (host->mmc->timing == MMC_TIMING_SD_HS
			|| host->mmc->timing == MMC_TIMING_UHS_SDR25
			|| host->mmc->timing == MMC_TIMING_UHS_DDR50
			|| host->mmc->timing == MMC_TIMING_MMC_HS) {
		drv_phase = 16; /* 180 degree */
		sample_phase = 4; /* 45 degreee*/

	} else {
		drv_phase = 16; /* 180 degree */
		sample_phase = 0;
	}

	hisi_set_drv_phase(host, drv_phase);
	hisi_enable_sample(host);
	hisi_set_sampl_phase(host, sample_phase);

	udelay(25);
}
