/*
 * The Flash Memory Controller v100 Device Driver for hisilicon
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
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

#include <common.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <hifmc_common.h>

#include "hifmc_spi_ids.h"

#define REG_IO_BASE 0x100c0000
static void hi3518ev300_io_config_spi_sfc(void)
{
    /* set pad ctrl reg for spi */
    writel(0x401, REG_IO_BASE + 0x14);    /* sfc_clk */
    writel(0x461, REG_IO_BASE + 0x18);    /* sfc_hold_io0 */
    writel(0x461, REG_IO_BASE + 0x1c);    /* sfc_miso_io1 */
    writel(0x461, REG_IO_BASE + 0x20);    /* sfc_wp_io2 */
    writel(0x461, REG_IO_BASE + 0x24);    /* sfc_mosi_io3 */
    writel(0x461, REG_IO_BASE + 0x28);   /* sfc_csn */
}

static void hi3518ev300_io_config_spi_sdio(void)
{
    /* set pad ctrl reg for spi */
    writel(0x461, REG_IO_BASE + 0x60);    /* SDIO1_CCLK_OUT */
    writel(0x561, REG_IO_BASE + 0x64);    /* SDIO1_CCMD */
    writel(0x461, REG_IO_BASE + 0x68);    /* SDIO1_CDATA0 */
    writel(0x561, REG_IO_BASE + 0x6c);    /* SDIO1_CDATA1 */
    writel(0x531, REG_IO_BASE + 0x70);    /* SDIO1_CDATA2 */
    writel(0x461, REG_IO_BASE + 0x74);   /* SDIO1_CDATA3 */

}
/*****************************************************************************/
void hifmc_set_fmc_system_clock(struct spi_op *op, int clk_en)
{
    unsigned int old_val, regval, sysstat_val;

    sysstat_val = readl(REG_BASE_SCTL + REG_SC_SYSSTAT);

    old_val = regval = readl(CRG_REG_BASE + REG_FMC_CRG);

    regval &= ~FMC_CLK_SEL_MASK;

    if (op && op->clock) {
        regval |= op->clock & FMC_CLK_SEL_MASK;
        FMC_PR(DTR_DB, "\t|||*-get the setting clock value: %#x\n",
               op->clock);
    } else {
        regval |= FMC_CLK_SEL(FMC_CLK_24M); /* Default Clock */
        if(SPI_INPUT_SLE(sysstat_val)) {
            hi3518ev300_io_config_spi_sdio();
        } else {
            hi3518ev300_io_config_spi_sfc();
        }
    }
    if (clk_en) {
        regval |= FMC_CLK_ENABLE;
    } else {
        regval &= ~FMC_CLK_ENABLE;
    }

    if (regval != old_val) {
        FMC_PR(DTR_DB, "\t|||*-setting system clock [%#x]%#x\n",
               REG_FMC_CRG, regval);
        writel(regval, (CRG_REG_BASE + REG_FMC_CRG));
    }
}

/*****************************************************************************/
void hifmc_get_fmc_best_2x_clock(unsigned int *clock)
{
    int ix;
    int clk_reg, clk_type;
    const char *str[] = {"12", "50", "75", "100"};

#define CLK_2X(_clk)    (((_clk) + 1) >> 1)
    unsigned int sys_2X_clk[] = {
        CLK_2X(24), FMC_CLK_SEL(FMC_CLK_24M),
        CLK_2X(100),    FMC_CLK_SEL(FMC_CLK_100M),
        CLK_2X(150),    FMC_CLK_SEL(FMC_CLK_150M),
        CLK_2X(200),    FMC_CLK_SEL(FMC_CLK_200M),
        0,      0,
    };
#undef CLK_2X

    clk_type = FMC_CLK_24M;
    clk_reg = FMC_CLK_SEL(clk_type);
    FMC_PR(QE_DBG, "\t|||*-matching flash clock %d\n", *clock);
    for (ix = 0; sys_2X_clk[ix]; ix += 2) {
        if (*clock < sys_2X_clk[ix]) {
            break;
        }
        clk_reg = sys_2X_clk[ix + 1];
        clk_type = GET_FMC_CLK_TYPE(clk_reg);
        FMC_PR(QE_DBG, "\t||||-select system clock: %sMHz\n",
               str[clk_type]);
    }
#ifdef CONFIG_DTR_MODE_SUPPORT
    FMC_PR(DTR_DB, "best system clock for SDR.\n");
#endif
    FMC_PR(QE_DBG, "\t|||*-matched best system clock: %sMHz\n",
           str[clk_type]);
    *clock = clk_reg;
}

#ifdef CONFIG_DTR_MODE_SUPPORT
/*****************************************************************************/
void hifmc_get_fmc_best_4x_clock(unsigned int *clock)
{
    int ix;
    int clk_reg, clk_type;
    char *const str[] = {"6", "25", "37.5", "50", "75", "90"};

#define CLK_4X(_clk)    (((_clk) + 1) >> 2)
    unsigned int sys_4X_clk[] = {
        CLK_4X(24), FMC_CLK_SEL(FMC_CLK_24M),
        CLK_4X(100),    FMC_CLK_SEL(FMC_CLK_100M),
        CLK_4X(150),    FMC_CLK_SEL(FMC_CLK_150M),
        CLK_4X(200),    FMC_CLK_SEL(FMC_CLK_200M),
        CLK_4X(300),    FMC_CLK_SEL(FMC_CLK_300M),
        CLK_4X(360),    FMC_CLK_SEL(FMC_CLK_360M),
        0,      0,
    };
#undef CLK_4X
    clk_type = FMC_CLK_24M;
    clk_reg = FMC_CLK_SEL(clk_type);
    FMC_PR(DTR_DB, "\t|||*-matching flash clock %d\n", *clock);
    for (ix = 0; sys_4X_clk[ix]; ix += 2) {
        if (*clock < sys_4X_clk[ix]) {
            break;
        }
        clk_reg = sys_4X_clk[ix + 1];
        clk_type = GET_FMC_CLK_TYPE(clk_reg);
        FMC_PR(DTR_DB, "\t||||-select system clock: %sMHz\n",
               str[clk_type]);
    }
    FMC_PR(DTR_DB, "best system clock for DTR.\n");
    FMC_PR(DTR_DB, "\t|||*-matched best system clock: %sMHz\n",
           str[clk_type]);
    *clock = clk_reg;
}
/*****************************************************************************/
#endif/* CONFIG_DTR_MODE_SUPPORT */
