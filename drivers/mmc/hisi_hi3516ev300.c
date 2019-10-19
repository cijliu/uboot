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

#define SDIO_DRV_DLL_SRST_REQ		(0x1 << 29)
#define SDIO_CLK_EN			(0x1 << 28)
#define SDIO_SRST_REQ			(0x1 << 27)
#define SDIO_CLK_SEL			(0x7 << 24)

#define REG_EMMC_DRV_DLL_STATUS		(CRG_REG_BASE + 0x210)
#define REG_SDIO0_DRV_DLL_STATUS	REG_EMMC_DRV_DLL_STATUS
#define REG_SDIO1_DRV_DLL_STATUS	(CRG_REG_BASE + 0x228)
#define SDIO_DRV_DLL_LOCK		BIT(15)
#define SDIO_DRV_DLL_READY		BIT(14)

#define REG_EMMC_SAMPL_DLL_STATUS	(CRG_REG_BASE + 0x208)
#define REG_SDIO0_SAMPL_DLL_STATUS	REG_EMMC_SAMPL_DLL_STATUS
#define REG_SDIO1_SAMPL_DLL_STATUS	(CRG_REG_BASE + 0x224)
#define SDIO_SAMPL_DLL_SLAVE_READY	BIT(0)

#define REG_EMMC_SAMPL_DLL_CTRL		(CRG_REG_BASE + 0x1f4)
#define REG_SDIO0_SAMPL_DLL_CTRL	REG_EMMC_SAMPL_DLL_CTRL
#define REG_SDIO1_SAMPL_DLL_CTRL	(CRG_REG_BASE + 0x22c)
#define SDIO_SAMPL_DLL_SLAVE_EN		BIT(16)

#define REG_EMMC_SAMPLB_DLL_CTRL	(CRG_REG_BASE + 0x1f8)
#define REG_SDIO0_SAMPLB_DLL_CTRL	REG_EMMC_SAMPLB_DLL_CTRL
#define REG_SDIO1_SAMPLB_DLL_CTRL	(CRG_REG_BASE + 0x21c)
#define SDIO_SAMPLB_DLL_CLK_MASK	(0x1f << 0)
#define SDIO_SAMPLB_SEL(phase)		((phase) << 0)

#define REG_EMMC_DRV_DLL_CTRL		(CRG_REG_BASE + 0x1fc)
#define REG_SDIO0_DRV_DLL_CTRL		REG_EMMC_DRV_DLL_CTRL;
#define REG_SDIO1_DRV_DLL_CTRL		(CRG_REG_BASE + 0x220)
#define SDIO_DRV_PHASE_SEL_MASK		(0x1f << 24)
#define SDIO_DRV_SEL(phase)		((phase) << 24)

#define REG_EMMC_DS_DLL_CTRL		(CRG_REG_BASE + 0x200)
#define EMMC_DS_DLL_MODE_SSEL		BIT(13)
#define EMMC_DS_DLL_SSEL_MASK		(0x7f)

#define REG_EMMC_DS180_DLL_CTRL		(CRG_REG_BASE + 0x204)
#define EMMC_DS180_DLL_BYPASS		BIT(15)
#define REG_EMMC_DS180_DLL_STATUS	(CRG_REG_BASE + 0x218)
#define EMMC_DS180_DLL_READY		BIT(0)

#define IO_CFG_SR			BIT(10)
#define IO_CFG_PULL_DOWN		BIT(9)
#define IO_CFG_PULL_UP			BIT(8)
#define IO_CFG_DRV_STR_MASK		(0xf << 4)
#define IO_CFG_DRV_STR_SEL(str)		((str) << 4)

#define REG_IO_CFG_BASE			0x100C0000
/* EMMC_IOCFG */
#define IO_CFG_EMMC_DATA_LINE_COUNT	8
#define REG_CTRL_EMMC_CLK		0x0014
#define REG_CTRL_EMMC_CMD		0x0018
#define REG_CTRL_EMMC_DATA0		0x001c
#define REG_CTRL_EMMC_DATA1		0x0028
#define REG_CTRL_EMMC_DATA2		0x0024
#define REG_CTRL_EMMC_DATA3		0x0020
#define REG_CTRL_EMMC_DATA4		0x0030
#define REG_CTRL_EMMC_DATA5		0x0034
#define REG_CTRL_EMMC_DATA6		0x0038
#define REG_CTRL_EMMC_DATA7		0x003c
#define REG_CTRL_EMMC_DS		0x0058
#define REG_CTRL_EMMC_RST		0x005c
static unsigned int io_emmc_data_reg[IO_CFG_EMMC_DATA_LINE_COUNT] = {REG_CTRL_EMMC_DATA0, REG_CTRL_EMMC_DATA1,
			REG_CTRL_EMMC_DATA2, REG_CTRL_EMMC_DATA3,
			REG_CTRL_EMMC_DATA4, REG_CTRL_EMMC_DATA5,
			REG_CTRL_EMMC_DATA6, REG_CTRL_EMMC_DATA7};

#define IO_CFG_SDIO0_DATA_LINE_COUNT	4
#define REG_CTRL_SDIO0_CLK		0x0040
#define REG_CTRL_SDIO0_CMD		0x0044
#define REG_CTRL_SDIO0_DATA0		0x0048
#define REG_CTRL_SDIO0_DATA1		0x004C
#define REG_CTRL_SDIO0_DATA2		0x0050
#define REG_CTRL_SDIO0_DATA3		0x0054
static unsigned int io_sdio0_data_reg[IO_CFG_SDIO0_DATA_LINE_COUNT] = {REG_CTRL_SDIO0_DATA0, REG_CTRL_SDIO0_DATA1,
			REG_CTRL_SDIO0_DATA2, REG_CTRL_SDIO0_DATA3};

static void hisi_dll_reset_assert(struct sdhci_host *host)
{
	unsigned long crg_addr;
	unsigned int reg;

	crg_addr = REG_EMMC_CRG;
	reg = readl(crg_addr);
	reg |= SDIO_DRV_DLL_SRST_REQ;
	writel(reg, crg_addr);
}

static void hisi_dll_reset_deassert(struct sdhci_host *host)
{
	unsigned long crg_addr;
	unsigned int reg;

	crg_addr = REG_EMMC_CRG;
	reg = readl(crg_addr);
	reg &= ~SDIO_DRV_DLL_SRST_REQ;
	writel(reg, crg_addr);
}

static void hisi_set_crg(struct sdhci_host *host, unsigned int clk)
{
	unsigned long crg_addr;
	unsigned int sel, reg;
	unsigned int clk_mux[8] = {100000, 400000, 25000000,
	50000000, 90000000, 112000000, 150000000, 198000000};

	crg_addr = REG_EMMC_CRG;
	reg = readl(crg_addr);
	reg &= ~MMC_CLK_SEL_MASK;

	if (clk <= MIN_FREQ)
		sel = 1;
	else {
		for (sel = 6; sel > 0; sel--) {
			if (clk >= clk_mux[sel])
				break;
		}
	}

	reg |= MMC_CLK_SEL(sel);
	writel(reg, crg_addr);
}

static void hisi_wait_ds_dll_lock(void)
{
	//Do nothing
	return;
}

static void hisi_set_ds_dll_delay(void)
{
	//Do nothing
	return;
}

static void hisi_wait_ds180_dll_ready(void)
{
	unsigned int reg, timeout = 20;

	do {
		reg = readl(REG_EMMC_DS180_DLL_STATUS);
		if (reg & EMMC_DS180_DLL_READY)
			return;

		udelay(1000);
		timeout--;
	} while (timeout > 0);

	printf("DS180 DLL master not ready.\n");
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
	reg &= ~SDHCI_UNDEFL_INCR_EN;
	sdhci_writel(host, reg, SDHCI_AXI_MBIIU_CTRL);

	reg  = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	reg &= ~SDHCI_CMD_DLY_EN;
	reg |= SDHCI_EDGE_DETECT_EN | SDHCI_DATA_DLY_EN;
	sdhci_writel(host, reg, SDHCI_MULTI_CYCLE);
}

static void hisi_set_drv_str(unsigned int offset, unsigned int pull_up, unsigned int pull_down,
	unsigned int sr, unsigned int drv_str)
{
	unsigned int reg;

	reg = readl(REG_IO_CFG_BASE + offset);
	reg &= ~(IO_CFG_PULL_UP | IO_CFG_PULL_DOWN | IO_CFG_DRV_STR_MASK | IO_CFG_SR);
	reg |= (pull_up ? IO_CFG_PULL_UP: 0);
	reg |= (pull_down ? IO_CFG_PULL_DOWN: 0);
	reg |= (sr ? IO_CFG_SR: 0);
	reg |= IO_CFG_DRV_STR_SEL(drv_str);
	writel(reg, REG_IO_CFG_BASE + offset);
}

static int sd_hardware_init(void)
{
	unsigned int reg = 0;

	/* The same CRG registers is used for both eMMC and SD card on this platform. */
	/* clk enable */
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_CLK_EN;
	writel(reg, REG_EMMC_CRG);

	/* reset assert*/
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_SRST_REQ | SDIO_DRV_DLL_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(25);

	/* reset deassert */
	reg &= ~SDIO_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(1);

	udelay(5000);

	return 0;
}

static int emmc_hardware_init(void)
{
	unsigned int reg = 0;

	/* eMMC clk enable */
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_CLK_EN;
	writel(reg, REG_EMMC_CRG);

	/* eMMC reset assert*/
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_SRST_REQ | SDIO_DRV_DLL_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(25);

	reg = readl(REG_EMMC_CRG);
	reg &= ~SDIO_CLK_SEL;
	reg |= (0x1 << 24); //select 400K clk
	writel(reg, REG_EMMC_CRG);
	udelay(25);

	/* eMMC reset deassert */
	reg = readl(REG_EMMC_CRG);
	reg &= ~SDIO_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(1);

	return 0;
}

static void hisi_mmc_set_ioconfig(struct sdhci_host *host)
{
	unsigned int reg;
	int i;

	if (host->type == MMC_TYPE_MMC) {
		reg = sdhci_readw(host, SDHCI_EMMC_CTRL);
		reg |= SDHCI_CARD_IS_EMMC;
		sdhci_writew(host, reg, SDHCI_EMMC_CTRL);

		switch(host->mmc->timing) {
		case MMC_TIMING_MMC_HS400:
			hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 0, 0x3);
			hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 0, 0x4);

			for(i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			{
				hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 0, 0x4);
			}
			hisi_set_drv_str(REG_CTRL_EMMC_DS, 0, 1, 1, 0x3);
			hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);
			break;
		case MMC_TIMING_MMC_HS200:
			hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 0, 0x2);
			hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 1, 0x4);
			for(i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			{
				hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 1, 0x4);
			}
			hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);
			break;
		case MMC_TIMING_MMC_HS:
			hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 1, 0x4);
			hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 1, 0x6);
			for(i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			{
				hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 1, 0x6);
			}
			hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);
			break;
		case MMC_TIMING_LEGACY:
		default:
			hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 1, 0x5);
			hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 1, 0x6);
			for(i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			{
				hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 1, 0x6);
			}
			hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);
			break;
		}
	}else {
		switch(host->mmc->timing) {
		case MMC_TIMING_SD_HS:
			hisi_set_drv_str(REG_CTRL_SDIO0_CLK, 0, 1, 1, 0x5);
			hisi_set_drv_str(REG_CTRL_SDIO0_CMD, 1, 0, 1, 0x7);
			for(i = 0; i < IO_CFG_SDIO0_DATA_LINE_COUNT; i++)
			{
				hisi_set_drv_str(io_sdio0_data_reg[i], 1, 0, 1, 0x7);
			}
			break;
		case MMC_TIMING_LEGACY:
		default:
			hisi_set_drv_str(REG_CTRL_SDIO0_CLK, 0, 1, 1, 0x7);
			hisi_set_drv_str(REG_CTRL_SDIO0_CMD, 1, 0, 1, 0x7);
			for(i = 0; i < IO_CFG_SDIO0_DATA_LINE_COUNT; i++)
			{
				hisi_set_drv_str(io_sdio0_data_reg[i], 1, 0, 1, 0x7);
			}
			break;
		}
	}
}

static void hisi_set_phase(struct sdhci_host *host)
{
	unsigned int drv_phase, sample_phase;

	if (host->mmc->timing == MMC_TIMING_MMC_HS400) {
		drv_phase = 10;	/* 112.5 degree */
		sample_phase = host->tuning_phase;
	} else if (host->mmc->timing == MMC_TIMING_MMC_HS200) {
		drv_phase = 23;	/* 258.75 degree */
		sample_phase = host->tuning_phase;
	} else if (host->mmc->timing == MMC_TIMING_MMC_HS) {
		drv_phase = 16;	/* 180 degree */
		sample_phase = 4;
	} else if (host->mmc->timing == MMC_TIMING_SD_HS) {
		drv_phase = 20;	/* 225 degree */
		sample_phase = 4;
	} else if (host->mmc->timing == MMC_TIMING_LEGACY) {
		drv_phase = 16;	/* 180 degree */
		sample_phase = 0;
	} else {
		drv_phase = 16; /* 180 degree */
		sample_phase = 4;
	}

	hisi_set_drv_phase(host, drv_phase);
	hisi_enable_sample(host);
	hisi_set_sampl_phase(host, sample_phase);

	udelay(25);
}
