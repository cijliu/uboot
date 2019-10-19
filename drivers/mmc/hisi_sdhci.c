/*
 * (C) Copyright 2015 Linaro
 * peter.griffin <peter.griffin@linaro.org>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <common.h>
#include <malloc.h>
#include <sdhci.h>
#include "mmc_private.h"

#define MIN_FREQ 400000
#define NOT_FOUND -1
#define PHASE_SCALE 32

static void hisi_enable_sample(struct sdhci_host *host);
static void hisi_set_drv_phase(struct sdhci_host *host,	unsigned int phase);
static void hisi_set_sampl_phase(struct sdhci_host *host, unsigned int phase);


#if defined(CONFIG_TARGET_HI3556AV100) || defined(CONFIG_TARGET_HI3519AV100)
#include <asm/arch-hi3556av100/platform.h>
#include "hisi_hi3556av100.c"
#endif

#ifdef CONFIG_TARGET_HI3559AV100
#include <asm/arch-hi3559av100/platform.h>
#include "hisi_hi3559av100.c"
#endif

#ifdef CONFIG_TARGET_HI3516EV200
#include <asm/arch-hi3516ev200/platform.h>
#include "hisi_hi3516ev200.c"
#endif

#ifdef CONFIG_TARGET_HI3516EV300
#include <asm/arch-hi3516ev300/platform.h>
#include "hisi_hi3516ev300.c"
#endif

#ifdef CONFIG_TARGET_HI3518EV300
#include <asm/arch-hi3518ev300/platform.h>
#include "hisi_hi3518ev300.c"
#endif

#ifdef CONFIG_TARGET_HI3516DV200
#include <asm/arch-hi3516dv200/platform.h>
#include "hisi_hi3516dv200.c"
#endif

static void hisi_enable_sample(struct sdhci_host *host)
{
	unsigned int reg;

	reg = sdhci_readl(host, SDHCI_AT_CTRL);
	reg |= SDHCI_SAMPLE_EN;
	sdhci_writel(host, reg, SDHCI_AT_CTRL);
}

static void hisi_set_drv_phase(struct sdhci_host *host,
		unsigned int phase)
{
	unsigned long crg_addr;
	unsigned int reg;

	crg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_DRV_DLL_CTRL : REG_SDIO0_DRV_DLL_CTRL;
	reg = readl(crg_addr);
	reg &= ~SDIO_DRV_PHASE_SEL_MASK;
	reg |= SDIO_DRV_SEL(phase);
	writel(reg, crg_addr);
}

static void hisi_set_sampl_phase(struct sdhci_host *host,
		unsigned int phase)
{
	unsigned int reg;

	reg = sdhci_readl(host, SDHCI_AT_STAT);
	reg &= ~SDHCI_PHASE_SEL_MASK;
	reg |= phase;
	sdhci_writel(host, reg, SDHCI_AT_STAT);
}

static void hisi_wait_drv_dll_lock(struct sdhci_host *host)
{
	unsigned int reg, timeout = 20;
	unsigned long reg_addr;

	reg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_DRV_DLL_STATUS : REG_SDIO0_DRV_DLL_STATUS;
	do {
		reg = readl(reg_addr);
		if (reg & SDIO_DRV_DLL_LOCK)
			return;

		udelay(1000);
		timeout--;
	} while (timeout > 0);

	printf("DRV DLL master not locked.\n");
}

static void hisi_enable_sampl_dll_slave(struct sdhci_host *host)
{
	unsigned int reg;
	unsigned long reg_addr;

	reg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_SAMPL_DLL_CTRL : REG_SDIO0_SAMPL_DLL_CTRL;
	reg = readl(reg_addr);
	reg |= SDIO_SAMPL_DLL_SLAVE_EN;
	writel(reg, reg_addr);
}

static void hisi_wait_sampl_dll_slave_ready(struct sdhci_host *host)
{
	unsigned int reg, timeout = 20;
	unsigned long reg_addr;

	reg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_SAMPL_DLL_STATUS : REG_SDIO0_SAMPL_DLL_STATUS;
	do {
		reg = readl(reg_addr);
		if (reg & SDIO_SAMPL_DLL_SLAVE_READY)
			return;

		udelay(1000);
		timeout--;
	} while (timeout > 0);

	printf("SAMPL DLL slave not ready.\n");
}

static int hisi_mmc_set_clk(struct sdhci_host *host, unsigned int clk)
{
	unsigned short ctrl, timeout;

	hisi_dll_reset_assert(host);
	udelay(25);
	hisi_set_crg(host, clk);
	hisi_set_phase(host);
	udelay(25);

	if (clk > MMC_HIGH_52_MAX_DTR) {
		hisi_enable_sampl_dll_slave(host);
		hisi_dll_reset_deassert(host);
	}

	ctrl = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	ctrl |= SDHCI_CLOCK_INT_EN | SDHCI_CLOCK_PLL_EN;
	sdhci_writew(host, ctrl, SDHCI_CLOCK_CONTROL);
	/* Wait max 20 ms */
	timeout = 20;
	while (!((ctrl = sdhci_readw(host, SDHCI_CLOCK_CONTROL))
				& SDHCI_CLOCK_INT_STABLE)) {
		if (timeout == 0) {
			printf("%s: Internal clock never stabilised.\n",
					__func__);
			return -EBUSY;;
		}
		timeout--;
		udelay(1000);
	}

	if (clk > MMC_HIGH_52_MAX_DTR) {
		hisi_wait_drv_dll_lock(host);
		hisi_wait_sampl_dll_slave_ready(host);
		hisi_wait_ds180_dll_ready();
	}

	ctrl |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, ctrl, SDHCI_CLOCK_CONTROL);
	udelay(100);

	if (host->mmc->timing == MMC_TIMING_MMC_HS400 &&
			clk > MMC_HIGH_52_MAX_DTR) {
		hisi_wait_ds_dll_lock();
		hisi_set_ds_dll_delay();
	}
	return 0;
}

static void hisi_enable_edge_tuning(struct sdhci_host *host)
{
	unsigned int reg;

	reg = readl(REG_EMMC_SAMPLB_DLL_CTRL);
	reg &= ~SDIO_SAMPLB_DLL_CLK_MASK;
	reg |= SDIO_SAMPLB_SEL(8);
	writel(reg, REG_EMMC_SAMPLB_DLL_CTRL);

	reg = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	reg |= SDHCI_EDGE_DETECT_EN;
	sdhci_writel(host, reg, SDHCI_MULTI_CYCLE);
}

static void hisi_disable_edge_tuning(struct sdhci_host *host)
{
	unsigned int reg;

	reg = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	reg &= ~SDHCI_EDGE_DETECT_EN;
	sdhci_writel(host, reg, SDHCI_MULTI_CYCLE);
}

static void hisi_disable_card_clk(struct sdhci_host *host)
{
	u16 clk;

	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	clk &= ~SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}

static void hisi_enable_card_clk(struct sdhci_host *host)
{
	u16 clk;

	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}

static void hisi_select_sampl_phase(struct sdhci_host *host,
		unsigned int phase)
{
	hisi_disable_card_clk(host);
	hisi_set_sampl_phase(host, phase);
	hisi_wait_sampl_dll_slave_ready(host);
	hisi_enable_card_clk(host);
	udelay(1);
}

static int hisi_send_tuning(struct sdhci_host *host, u32 opcode)
{
	int count, err, tuning_num = 1;

	count = 0;
	do {
		err = mmc_send_tuning(host->mmc, opcode);
		if (err)
			break;

		count++;
	} while (count < tuning_num);

	return err;
}

static int hisi_mmc_exec_tuning(struct sdhci_host *host,
		unsigned int opcode)
{
	unsigned int index, val;
	unsigned int found = 0, prev_found = 0;
	unsigned int edge_p2f, edge_f2p, start, end;
	unsigned int phase, fall = NOT_FOUND, rise = NOT_FOUND;
	unsigned int fall_updat_flag = 0;
	int err, prev_err = 0;
	unsigned short ctrl;

	hisi_wait_drv_dll_lock(host);
	hisi_enable_sampl_dll_slave(host);
	hisi_enable_sample(host);
	hisi_enable_edge_tuning(host);
	host->is_tuning = 1;

	start = 0;
	end = PHASE_SCALE / 4;

	edge_p2f = start;
	edge_f2p = end;
	for (index = 0; index <= end; index++) {
		hisi_select_sampl_phase(host, index * 4);

		err = mmc_send_tuning(host->mmc, opcode);
		if (!err) {
			val = sdhci_readl(host, SDHCI_MULTI_CYCLE);
			found = val & SDHCI_FOUND_EDGE;
		} else
			found = 1;

		if (prev_found && !found)
			edge_f2p = index;
		else if (!prev_found && found)
			edge_p2f = index;

		if ((edge_p2f != start) && (edge_f2p != end))
			break;

		prev_found = found;
		found = 0;
	}

	if ((edge_p2f == start) && (edge_f2p == end)) {
		printf("tuning failed! can not found edge!\n");
		return -1;
	}

	hisi_disable_edge_tuning(host);

	start = edge_p2f * 4;
	end = edge_f2p * 4;
	if (end <= start)
		end += PHASE_SCALE;

	fall = start;
	rise = end;
	fall_updat_flag = 0;
	for (index = start; index <= end; index++) {
		hisi_select_sampl_phase(host, index % PHASE_SCALE);

		err = hisi_send_tuning(host, opcode);
		if (err)
		{
			debug("send tuning CMD%u fail! phase:%u err:%d\n", opcode, index, err);
		}

		if (err && index == start) {
			if (!fall_updat_flag) {
				fall_updat_flag = 1;
				fall = start;
			}
		} else {
			if (!prev_err && err) {
				if (!fall_updat_flag) {
					fall_updat_flag = 1;
					fall = index;
				}
			}
		}

		if (prev_err && !err) {
			rise = index;
		}

		if (err && index == end)
			rise = end;

		prev_err = err;
	}

	phase = ((fall + rise) / 2 + 16) % PHASE_SCALE;

	printf("tuning done! valid phase shift [%u, %u] Final Phase:%u\n",
			rise % PHASE_SCALE, fall % PHASE_SCALE, phase);

	host->tuning_phase = phase;
	hisi_select_sampl_phase(host, phase);

	ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	ctrl |= SDHCI_CTRL_TUNED_CLK;
	sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);
	host->is_tuning = 0;

	return 0;
}

int hisi_sdhci_add_port(int index, u32 regbase, u32 type)
{
	struct sdhci_host *host = NULL;

	if (type == MMC_TYPE_MMC)
		emmc_hardware_init();
	else
		sd_hardware_init();

	host = calloc(1, sizeof(struct sdhci_host));
	if (!host) {
		puts("sdhci_host malloc fail!\n");
		return -ENOMEM;
	}

	host->name = "hisi-sdhci";
	host->index = index;
	host->type = type;
	host->ioaddr = (void *)(unsigned long)regbase;
	host->quirks = 0;
	if (type == MMC_TYPE_MMC)
#if defined(CONFIG_TARGET_HI3516EV200)  || defined(CONFIG_TARGET_HI3518EV300)
		host->host_caps = MMC_MODE_HS | MMC_MODE_HS_52MHz |
			MMC_MODE_HS200_1_8V;
#else
		host->host_caps = MMC_MODE_HS400ES |
			MMC_MODE_HS400_1_8V | MMC_MODE_HS200_1_8V | MMC_MODE_HS;
#endif
	host->set_clock = hisi_mmc_set_clk;
	host->priv_init = hisi_mmc_priv_init;
	host->set_control_reg = hisi_mmc_set_ioconfig;
	host->execute_tuning = hisi_mmc_exec_tuning;

#ifdef CONFIG_SDHCI_ADMA
	host->max_segs = 512;
	host->max_seg_size = 65536;
#ifdef CONFIG_TARGET_HI3559AV100
	host->desc_sz = sizeof(struct sdhci_adma2_64_desc);
#else
	host->desc_sz = sizeof(struct sdhci_adma2_32_desc);
#endif
	host->adma_table_sz = (host->max_segs + 2) * host->desc_sz;
	host->adma_table = malloc(ALIGN(host->adma_table_sz, CONFIG_SYS_CACHELINE_SIZE));
	host->adma_table += CONFIG_SYS_CACHELINE_SIZE - ((unsigned long)host->adma_table & (CONFIG_SYS_CACHELINE_SIZE - 1));
	if (!host->adma_table) {
		puts("adma table malloc fail!\n");
		free(host);
		return -ENOMEM;
	}
#endif

	add_sdhci(host, CONFIG_HISI_SDHCI_MAX_FREQ, MIN_FREQ);

	return 0;
}

static void print_mmcinfo(struct mmc *mmc)
{
	printf("MMC/SD Card:\n");
	printf("    MID:         0x%x\n", mmc->cid[0] >> 24);
	printf("    Read Block:  %d Bytes\n", mmc->read_bl_len);
	printf("    Write Block: %d Bytes\n", mmc->write_bl_len);
	printf("    Chip Size:   %s Bytes (%s)\n",
			ultohstr(mmc->capacity),
			mmc->high_capacity ? "High Capacity" : "Low Capacity");
	printf("    Name:        \"%c%c%c%c%c\"\n",
			mmc->cid[0] & 0xff,
			(mmc->cid[1] >> 24),
			(mmc->cid[1] >> 16) & 0xff,
			(mmc->cid[1] >> 8) & 0xff,
			mmc->cid[1] & 0xff);

	printf("    Chip Type:   %s\n"
			"    Version:     %d.%d\n",
			IS_SD(mmc) ? "SD" : "MMC",
			EXTRACT_SDMMC_MAJOR_VERSION(mmc->version),
			EXTRACT_SDMMC_MINOR_VERSION(mmc->version));

	printf("    Speed:       %sHz\n", ultohstr(mmc->clock));
	printf("    Bus Width:   %dbit\n", mmc->bus_width);
	printf("    Mode:        %s\n", mmc->strobe_enhanced ? "HS400ES" :
			mmc->timing == MMC_TIMING_MMC_HS400 ? "HS400" :
			mmc->timing == MMC_TIMING_MMC_HS200 ? "HS200" : "HS");
}

int hisi_mmc_init(int dev_num)
{
	struct mmc *mmc = find_mmc_device(dev_num);
	int ret;

	if (!mmc) {
		printf("mmc device not found!!\n");
		return -EINVAL;
	}

	ret = mmc_init(mmc);
	if (ret)
		return ret;

	if (!IS_SD(mmc))
	{
		print_mmcinfo(mmc);
		return mmc_set_boot_config(mmc);
	}

	return 0;
}

void printf_mmc(int dev_num)
{
	struct mmc *mmc = find_mmc_device(dev_num);

	if (mmc)
		print_mmcinfo(mmc);
}
