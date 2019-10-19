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
#include <ddr_training_impl.h>

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

#define REG_BASE_DDRC               0x120d0000
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
void ddr_scramb(void)
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

//svb
#define SVB_VER_16EV300             0x10

#define CYCLE_NUM 4
#define  HPM_CORE_REG0 0x120280d8
#define  HPM_CORE_REG1 0x120280dc

#define SVB_PWM_REG 0X120280b0

#define SVB_VER_REG         0x12020168
#define  HPM_CHECK_REG 0x1202015c
#define SYS_CTRL_VOLT_REG 0x12020158

#define TSENSOR_STATUS0 0x120280bc
#define OTP_HPM_CORE_REG 0x100a002c

static unsigned hpm_value_avg(unsigned int* val)
{
    unsigned int i = 0;
    unsigned tmp = 0;

    for (i = 0; i < 4; i++) {
        tmp += val[i] >> 2;
    }

    return tmp >> 2;
}

static void get_hpm_value(unsigned int* hpm_core)
{
    int i = 0;
    unsigned int temp = 0;
    unsigned int core_value[4];

    core_value[0] = 0;
    core_value[1] = 0;
    core_value[2] = 0;
    core_value[3] = 0;

    for (i = 0; i < CYCLE_NUM; i++) {
        delay(10);

        temp = readl(HPM_CORE_REG0);
        core_value[1] += (temp >> 16) & 0x3ff;
        core_value[0] += temp & 0x3ff;
        temp = readl(HPM_CORE_REG1);
        core_value[3] += (temp >> 16) & 0x3ff;
        core_value[2] += temp & 0x3ff;
    }

    *hpm_core = hpm_value_avg(core_value);
}

static void start_hpm(unsigned int* hpm_core)
{
    get_hpm_value(hpm_core);
}

static void hpm_check(unsigned int* hpm_core)
{
    union {
        struct {
            unsigned int reserved_0 : 16; /* [15..0]*/
            unsigned int sys_hpm_core : 9; /* [24..16]*/
            unsigned int reserved_1 : 1; /* [25]*/
            unsigned int hpm_core_err : 1; /* [26]*/
            unsigned int reserved_2 : 5; /* [27..31]*/
        } bits;

        unsigned int u32;
    } sysboot10;
    sysboot10.u32 = readl(HPM_CHECK_REG);
    sysboot10.bits.sys_hpm_core = 0;
    sysboot10.bits.hpm_core_err = 0;

    if(*hpm_core < 150) {
        *hpm_core = 150;
        sysboot10.bits.hpm_core_err = 1;
    }
    if(*hpm_core > 350) {
        *hpm_core = 350;
        sysboot10.bits.hpm_core_err = 1;
    }

    sysboot10.bits.sys_hpm_core = *hpm_core;

    writel(sysboot10.u32, HPM_CHECK_REG);

}

static void get_temperature(unsigned int *temperature)
{
    unsigned int value = 0;

    value = readl(TSENSOR_STATUS0);
    value = value & 0x3ff;

    if (value <= 117) {
        *temperature = -40;
    } else if (value >= 841) {
        *temperature = 110;
    } else {
        *temperature = (((value - 117) * 212) >> 10) - 40;
    }
}

static void adjust_hpm(unsigned int *hpm_core, unsigned int temperature)
{

    if ((*hpm_core >= 283) && (temperature >= 70)) {
        *hpm_core = *hpm_core + 4 + (((temperature - 70) * 205) >> 10);
    } else if ((*hpm_core <= 222) && (temperature >= 70)) {
        *hpm_core = *hpm_core - 4;
    } else {
    }
}

//max: 1099 min:654
//y = 1006 , x <= 190
//y = -1.4786x + 1287, 190<x<310
//y = 829, x >= 310
static void set_hpm_core_volt(unsigned int hpm_core_value)
{
    unsigned int volt;
    unsigned int duty;
    unsigned int otp_vmin_core = readl(OTP_HPM_CORE_REG);

    if (hpm_core_value <= 190) {
        volt = 1006;
    } else if(hpm_core_value >= 310) {
        volt = 829;
    } else {
        volt = 1287 - ((1514 * hpm_core_value) >> 10);
    }
    volt = volt + (int)((short int)(otp_vmin_core >> 16));

    writel(volt, SYS_CTRL_VOLT_REG);
    duty = ((unsigned int)((1099 - volt) * 460) >> 10)  - 1;

    writel((  ((duty << 16) & 0XFFFF0000) + 0x0c75), SVB_PWM_REG);

}

void start_svb(void)
{
    unsigned int hpm_core = 0;
    unsigned int temperature = 0;

    unsigned int tmp_reg = readl(SVB_VER_REG);
    tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER_16EV300 << 16);
    writel(tmp_reg, SVB_VER_REG);

    get_temperature(&temperature);
    start_hpm(&hpm_core);
    adjust_hpm(&hpm_core, temperature);
    hpm_check(&hpm_core);

    set_hpm_core_volt(hpm_core);
    delay(200);
}


/* [CUSTOM] DDR PHY0-PHY1 base register */
#define DDR_REG_BASE_PHY0       0x120dc000

/* [CUSTOM] DDR DMC0-DMC3 base register */
#define DDR_REG_BASE_DMC0       0x120d8000
#define DDR_REG_BASE_DMC1       0x120d8000

#ifdef DDR_REG_BASE_PHY1
#define DDR_REG_BASE_DMC2       0x120d9000
#define DDR_REG_BASE_DMC3       0x120d9000
#endif

#define CRG_REG_BASE            0x12010000
#define PERI_CRG_DDRT           0x198

#define DDR_REG_BASE_SYSCTRL    0x12020000
/* [SYSCTRL]RAM Retention control register 0 */
#define SYSCTRL_MISC_CTRL4      0x8010

#define DDR_PHY_DRAMCFG         0x2c    /* DRAM config register */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */

#define BYTE_NUM  2

/**
 * ddr_boot_prepare
 * @void
 *
 * Do some prepare before ddr training.
 * Keep empty when nothing to do.
 */
static void ddr_boot_prepare(struct tr_relate_reg *reg)
{
    /* select ddrt bus path */
    reg->custom.ive_ddrt_mst_sel = readl(DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);
    writel(reg->custom.ive_ddrt_mst_sel & 0xffffffdf, DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);

    /* turn on ddrt clock */
    reg->custom.ddrt_clk_reg = readl(CRG_REG_BASE + PERI_CRG_DDRT);
    /* enable ddrt0 clock */
    writel(reg->custom.ddrt_clk_reg | (0x1 << 1), CRG_REG_BASE + PERI_CRG_DDRT);
    __asm__ __volatile__("nop");
    /* disable ddrt0 soft reset */
    writel(readl(CRG_REG_BASE + PERI_CRG_DDRT) & (~(0x1 << 0)), CRG_REG_BASE + PERI_CRG_DDRT);

    /* disable rdqs anti-aging */
    reg->custom.phy0_age_compst_en = readl(DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
    writel((reg->custom.phy0_age_compst_en & 0x7fffffff), DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
    reg->custom.phy1_age_compst_en = readl(DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
    writel((reg->custom.phy1_age_compst_en & 0x7fffffff), DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

/**
 * ddr_boot_restore
 * @void
 *
 * Restore register config after ddr training.
 * Keep empty when nothing to do.
 */
static void ddr_boot_restore(struct tr_relate_reg *reg)
{
    /* restore ddrt bus path */
    writel(reg->custom.ive_ddrt_mst_sel, DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);

    /* restore ddrt clock */
    writel(reg->custom.ddrt_clk_reg, CRG_REG_BASE + PERI_CRG_DDRT);

    /* restore rdqs anti-aging */
    writel(reg->custom.phy0_age_compst_en, DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
    writel(reg->custom.phy1_age_compst_en, DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

/**
 * ddr_rdqs_bdl_adj
 * @void
 *
 * Adjust rdqs/rdq/rdm bdl to avoid problem cause by ddr anti-aging.
 */
static void ddr_rdqs_bdl_adj(void)
{
    int i;
    unsigned int rdqs;
    unsigned int rdq03, rdq47;
    unsigned int rdm;
    unsigned int tmp;

    for (i = 0; i < BYTE_NUM; i++) {
        rdqs = readl(DDR_REG_BASE_PHY0 + 0x22c + i * 0x80);
        rdq03 = readl(DDR_REG_BASE_PHY0 + 0x21c + i * 0x80);
        rdq47 = readl(DDR_REG_BASE_PHY0 + 0x220 + i * 0x80);
        rdm = readl(DDR_REG_BASE_PHY0 + 0x224 + i * 0x80);

        /* rdqs bdl lower two bit shoud be 0x11 */
        while ((rdqs & 0x3) < 0x3) {
            /* rdqs/rdq/rdm bdl + 1 */
            rdqs = rdqs + 0x1;
            rdq03 = rdq03 + 0x01010101;
            rdq47 = rdq47 + 0x01010101;
            rdm = rdm + 0x1;

            writel(rdqs, DDR_REG_BASE_PHY0 + 0x22c + i * 0x80);
            writel(rdq03, DDR_REG_BASE_PHY0 + 0x21c + i * 0x80);
            writel(rdq47, DDR_REG_BASE_PHY0 + 0x220 + i * 0x80);
            writel(rdm, DDR_REG_BASE_PHY0 + 0x224 + i * 0x80);
        }

    }

    tmp = readl(DDR_REG_BASE_PHY0 + DDR_PHY_MISC);
    tmp |= (1 << PHY_MISC_UPDATE_BIT);
    /* update new config to PHY */
    writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_MISC);
    tmp &= ~(1 << PHY_MISC_UPDATE_BIT);
    writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_MISC);
    tmp = readl(DDR_REG_BASE_PHY0 + DDR_PHY_PHYINITCTRL);
    /* set 1 to issue PHY counter reset signal */
    tmp |= (1 << PHY_PHYCONN_RST_BIT);
    writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_PHYINITCTRL);
    /* set 0 to end the reset signal */
    tmp &= ~(1 << PHY_PHYCONN_RST_BIT);
    writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_PHYINITCTRL);
}

void start_ddr_training(unsigned int base)
{
    struct tr_relate_reg relate_reg;
    struct tr_relate_reg *reg = &relate_reg;

    start_svb();

    ddr_boot_prepare(reg);

    /* ddr pcode training */
    ddr_pcode_training_if(0);
    /* ddr hw training */
    ddr_hw_training_if(0);
    /* ddr sw training */
    ddr_sw_training_if(0);

    ddr_rdqs_bdl_adj();

    ddr_boot_restore(reg);

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
//  ddr_scramb();
}
