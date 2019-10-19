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

#include <asm/arch/platform.h>
#include <config.h>
#include <ddr_interface.h>

static inline void delay(unsigned int num)
{
    volatile unsigned int i;

    for (i = 0; i < (100 * num); i++) {
        __asm__ __volatile__("nop");
    }
}

extern void reset_cpu(unsigned long addr);

static inline void DWB(void) /* drain write buffer */
{
}

static inline unsigned int readl(unsigned addr)
{
    unsigned int val;

    val = (*(volatile unsigned int *)(addr));
    return val;
}

static inline void writel(unsigned val, unsigned addr)
{
    DWB();
    (*(volatile unsigned *) (addr)) = (val);
    DWB();
}

#define REG_BASE_RNG_GEN            0x10090000
#define TRNG_DSTA_FIFO_DATA_OFST    0x204
#define TRNG_DATA_ST_OFST           0x208
#define BIT_TRNG_FIFO_DATA_CNT      0x8
#define TRNG_FIFO_DATA_CNT_MASK     0xff
#define REG_PERI_CRG104             0x1a0
#define TRNG_CLK_ENABLE             (0x1<<3)
#define TRNG_CLK_DISABLE            ~(0x1<<3)
#define TRNG_CTRL_DEF_VAL           0xa
#define HISEC_COM_TRNG_CTRL_OFST    0x200

#define REG_BASE_MISC               0x12030000
#define DDR_CA0_OFST                0x28
#define DDR_CA1_OFST                0x2C
#define DDR_CA2_OFST                0x30

#define REG_BASE_DDRC               0x12060000
#define DDRC_CTRL_SREF_OFST         (0x8000 + 0x0)
#define DDRC_CFG_DDRMODE_OFST       (0x8000 + 0x50)
#define DDRC_CURR_FUNC_OFST         (0x8000 + 0x294)

#define DDRC_CHANNEL_VALID_MASK     (0xf)
#define DDRC_SELF_REFURBISH_MASK    (0x1)

#define DDRC_SELF_REFURBISH_EN      0x1
#define DDRC_SELF_REFURBISH_EXIT    (0x1 << 1)

#undef reg_get
#undef reg_set
#define reg_get(addr) readl(addr)
#define reg_set(addr, val) writel(val, (unsigned int)addr)

void trng_init(void)
{
    unsigned int reg_val = 0;
    /* open rsa and trng clock */
    reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG104);
    reg_val |= TRNG_CLK_ENABLE;
    reg_set(CRG_REG_BASE + REG_PERI_CRG104, reg_val);

    /* set trng ctrl register */
    reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
            TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
    unsigned int reg_val = 0;

    /* close rsa and trng clock */
    reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG104);
    reg_val &= TRNG_CLK_DISABLE;
    reg_set(CRG_REG_BASE + REG_PERI_CRG104, reg_val);

}
/* get random number */
static int get_random_num(void)
{
    unsigned int reg_val = 0;

    do {
        reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DATA_ST_OFST);

    } while (!((reg_val >> BIT_TRNG_FIFO_DATA_CNT)
               & TRNG_FIFO_DATA_CNT_MASK));

    reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DSTA_FIFO_DATA_OFST);

    return reg_val;
}

/* start ddr cramb */
static void ddr_scramb_start(unsigned int random1, unsigned int random2)
{
    reg_set(REG_BASE_MISC + DDR_CA0_OFST, random1);
    reg_set(REG_BASE_MISC + DDR_CA1_OFST, random2);
    reg_set(REG_BASE_MISC + DDR_CA2_OFST, 0);
    reg_set(REG_BASE_MISC + DDR_CA2_OFST, 0x10);
    delay(1000);
    reg_set(REG_BASE_MISC + DDR_CA0_OFST, 0);
    reg_set(REG_BASE_MISC + DDR_CA1_OFST, 0);
}

/* execute ddr scramb */
static void ddr_scramb(void)
{
    unsigned int random_num1 = 0;
    unsigned int random_num2 = 0;
    unsigned int reg_val = 0;
    unsigned int ddrc_isvalid = 0;

    /* read ddrc_cfg_ddrmode register,
     * if value[3:0] is not 0x0 ,the channel is valid.
     */
    ddrc_isvalid = (reg_get(REG_BASE_DDRC + DDRC_CFG_DDRMODE_OFST) & DDRC_CHANNEL_VALID_MASK) ? 1 : 0;

    /* set ddrc to do self-refurbish */
    if(ddrc_isvalid) {
        reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, DDRC_SELF_REFURBISH_EN);
    }

    /* wait the status of ddrc to be sef-refurbish */
    do {
        reg_val = ddrc_isvalid ? (reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK) : 1;

    } while (!reg_val);

    trng_init();
    /* get random number */
    random_num1 = get_random_num();
    random_num2 = get_random_num();

    /* start ddr scrambling */
    ddr_scramb_start(random_num1, random_num2);

    /* clear random number */
    random_num1 = get_random_num();
    random_num2 = get_random_num();
    random_num1 = get_random_num();
    random_num2 = get_random_num();

    trng_deinit();

    /* set ddrc to exit self-refurbish */
    if(ddrc_isvalid) {
        reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, DDRC_SELF_REFURBISH_EXIT);
    }

    /* wait the status of ddrc to be normal */
    do {
        reg_val = ddrc_isvalid ? (reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK) : 0;

    } while (reg_val);
}

void start_svb(void)
{
//TODO:
#define SVB_VER_REG         0x120200ac
#define SVB_VER             0x00

    /* add SVB VER*/
    int tmp_reg = readl(SVB_VER_REG);
    tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER << 16);
    writel(tmp_reg, SVB_VER_REG);
}

/* [CUSTOM] DDR PHY0-PHY1 base register */
#define DDR_REG_BASE_PHY0       0x1206c000

/* [CUSTOM] DDR DMC0-DMC3 base register */
#define DDR_REG_BASE_DMC0       0x12068000
#define DDR_REG_BASE_DMC1       0x12069000

#ifdef DDR_REG_BASE_PHY1
#define DDR_REG_BASE_DMC2       0x1206a000
#define DDR_REG_BASE_DMC3       0x1206b000
#endif

#define DDR_PHY_DRAMCFG     0x2c    /* DRAM config register */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */

void start_ddr_training(unsigned int base)
{
    start_svb();

    /* ddr hw training */
    ddr_hw_training_if(0);
    extern void ddr_cmd_site_save(void);
    ddr_cmd_site_save();
    /* ddr sw training */
    ddr_sw_training_if(0);
    extern void ddr_cmd_site_restore(void);
    ddr_cmd_site_restore();
    /*the value should config after trainning, or
      it will cause chip compatibility problems*/
    if ((readl(DDR_REG_BASE_PHY0 + DDR_PHY_DRAMCFG)
            & PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
        writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
        writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
    } else {
        writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
    }
#ifdef DDR_REG_BASE_PHY1
    if ((readl(DDR_REG_BASE_PHY1 + DDR_PHY_DRAMCFG)
            & PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
        writel(0x401, DDR_REG_BASE_DMC2 + 0x28);
        writel(0x401, DDR_REG_BASE_DMC3 + 0x28);
    } else {
        writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
    }
#endif
    /* enable ddr scramb */
    ddr_scramb();
}
