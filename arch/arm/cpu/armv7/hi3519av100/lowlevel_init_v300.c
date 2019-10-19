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

#define HI_SYS_CTL_REG  SYS_CTRL_REG_BASE

#define OK 0
#define ERROR -1
#define DDR_CA0_OFST        0x88
#define DDR_CA1_OFST        0x8c
#define DDR_CA2_OFST        0x90
#define REG_BASE_DDRC           0x04600000

#define DDRC_CTRL_SREF_OFST     0x8000 + 0x0
#define DDRC_CFG_DDRMODE_OFST   0x8000 + 0X50
#define DDRC_CURR_FUNC_OFST     0x8000 + 0x294

#define DDRC1_CTRL_SREF_OFST    0x9000 + 0x0
#define DDRC1_CFG_DDRMODE_OFST  0x9000 + 0X50
#define DDRC1_CURR_FUNC_OFST    0x9000 + 0x294

#define DDRC2_CTRL_SREF_OFST    0xa000 + 0x0
#define DDRC2_CFG_DDRMODE_OFST  0xa000 + 0X50
#define DDRC2_CURR_FUNC_OFST    0xa000 + 0x294

#define DDRC3_CTRL_SREF_OFST    0xb000 + 0x0
#define DDRC3_CFG_DDRMODE_OFST  0xb000 + 0X50
#define DDRC3_CURR_FUNC_OFST    0xb000 + 0x294

#define DDRC_SELF_REFURBISH_MASK    (0x1)

/* [CUSTOM] DDR PHY0-PHY1 base register */
#define DDR_REG_BASE_PHY0       0x0460c000
//#define DDR_REG_BASE_PHY1       0x0460e000

/* [CUSTOM] DDR DMC0-DMC3 base register */
#define DDR_REG_BASE_DMC0       0x04608000
#define DDR_REG_BASE_DMC1       0x04609000

#ifdef DDR_REG_BASE_PHY1
#define DDR_REG_BASE_DMC2       0x0460a000
#define DDR_REG_BASE_DMC3       0x0460b000
#endif

#define DDR_PHY_DRAMCFG     0x2c    /* DRAM config register */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */
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

#ifdef DDR_SCRAMB_ENABLE

#define REG_BASE_MISC       0x04528000
#define MISC_CTRL88_OFST    0x88
#define MISC_CTRL8C_OFST    0x8c
#define MISC_CTRL90_OFST    0x90

#define REG_BASE_DDRC       DDRC0_REG_BASE
#define DDRC_0_CTRL_SREF_OFST   0x8000 + 0x0
#define DDRC_0_CURR_FUNC_OFST   0x8000 + 0x294
#define DDRC_1_CTRL_SREF_OFST   0x9000 + 0x0
#define DDRC_1_CURR_FUNC_OFST   0x9000 + 0x294

static void ddr_scramb_start(unsigned int random1, unsigned int random2)
{
    writel(random1, REG_BASE_MISC + MISC_CTRL88_OFST);
    writel(random2, REG_BASE_MISC + MISC_CTRL8C_OFST);
    writel(0, REG_BASE_MISC + MISC_CTRL90_OFST);
    writel(0x10, REG_BASE_MISC + MISC_CTRL90_OFST);

    delay(1000);

    writel(0, REG_BASE_MISC + MISC_CTRL88_OFST);
    writel(0, REG_BASE_MISC + MISC_CTRL8C_OFST);
}

#define REG_BASE_RNG_GEN        0x04090000
#define TRNG_DSTA_FIFO_DATA_OFST    0x204
#define TRNG_DATA_ST_OFST       0x208
#define HISEC_COM_TRNG_CTRL_OFST    0x200
#define REG_PERI_CRG101         0x0194

#define BIT_TRNG_FIFO_DATA_CNT      0x8
#define TRNG_FIFO_DATA_CNT_MASK     0xff
#define TRNG_CTRL_DEF_VAL       0xa

#define TRNG_CLK_ENABLE         (0x1 << 13)
#define TRNG_DO_SRST            (0x1 << 12)
#define TRNG_CLK_DISABLE        ~(0x1 << 13)
#define TRNG_UNDO_SRST          ~(0x1 << 12)

#undef reg_get
#define reg_get(addr) (*(volatile unsigned int *)((long)addr))

#undef reg_set
#define reg_set(addr, val) (*(volatile unsigned int *)((long)addr) = (val))

/* get random number */
int get_random_num(void)
{
    unsigned int reg_val = 0;

    do {
        reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DATA_ST_OFST);

    } while (!((reg_val >> BIT_TRNG_FIFO_DATA_CNT)
               & TRNG_FIFO_DATA_CNT_MASK));

    reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DSTA_FIFO_DATA_OFST);

    return reg_val;
}

void trng_init(void)
{
    unsigned int reg_val = 0;
    /* open rsa and trng clock */
    reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG101);
    reg_val |= TRNG_CLK_ENABLE;
    reg_set(CRG_REG_BASE + REG_PERI_CRG101, reg_val);

    /* set trng ctrl register */
    reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
            TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
    unsigned int reg_val = 0;

    /* close rsa and trng clock */
    reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG101);
    reg_val &= TRNG_CLK_DISABLE;
    reg_set(CRG_REG_BASE + REG_PERI_CRG101, reg_val);

}

static int ddr_scramb(void)
{
    unsigned int random_num1 = 0;
    unsigned int random_num2 = 0;
    unsigned int reg_val[2] = {0, 0};
    unsigned int ddrc_isvalid[2] = {0, 0};

    /* read ddrc_cfg_ddrmode register,
     * if value[3:0] is not 0x0 ,the channel is valid.
     */
    ddrc_isvalid[0] = (reg_get(REG_BASE_DDRC + DDRC_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;
    ddrc_isvalid[1] = (reg_get(REG_BASE_DDRC + DDRC1_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;

    /* set ddrc to do self-refurbish */
    if(ddrc_isvalid[0]) {
        reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, 0x1);
    }
    if(ddrc_isvalid[1]) {
        reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, 0x1);
    }

    /* wait the status of ddrc to be sef-refurbish */
    do {
        reg_val[0] = ddrc_isvalid[0] ? (reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & 0x1) : 1;
        reg_val[1] = ddrc_isvalid[1] ? (reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & 0x1) : 1;

    } while (!(reg_val[0] & reg_val[1]));

    trng_init();
    /* get random number */
    random_num1 = get_random_num();
    random_num2 = get_random_num();

    /* start ddr scrambling */
    ddr_scramb_start(random_num1, random_num2);

    /* clear random number */
    (void)get_random_num();
    (void)get_random_num();
    (void)get_random_num();
    (void)get_random_num();
    trng_deinit();

    /* set ddrc to exit self-refurbish */
    if(ddrc_isvalid[0]) {
        reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, (0x1 << 1));
    }
    if(ddrc_isvalid[1]) {
        reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, (0x1 << 1));
    }

    /* wait the status of ddrc to be normal */
    do {
        reg_val[0] = ddrc_isvalid[0] ? (reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & 0x1) : 0;
        reg_val[1] = ddrc_isvalid[1] ? (reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & 0x1) : 0;
    } while (reg_val[0] | reg_val[1]);

    return OK;
}

#endif /* DDR_SCRAMB_ENABLE */

#define SVB_VERSION 0x10

#define HI_PMC_CTL_REG      0x04528000
#define HPM_CORE_VOL_REG    (HI_PMC_CTL_REG + 0x60)
#define HPM_MDA_VOL_REG   (HI_PMC_CTL_REG + 0x68)
#define CYCLE_NUM       4
#define HPM_CPU_REG0    0x1208
#define HPM_CPU_REG1    0x120c
#define HPM_MDA_REG0    0x1228
#define HPM_MDA_REG1    0x122c
#define HPM_CORE_REG0   0x1218
#define HPM_CORE_REG1   0x121c

#define HMP_CLK_REG 0x0451019c

#define HPM_CHECK_REG 0x04520158
#define VERSION_REG 0x0452015c

#define OTP_HPM_CORE_REG    0x040b0028
#define OTP_HPM_MDA_REG 0x040b002c
#define OTP_HPM_CPU_REG 0x040b0034

#define TSENSOR_CTRL    0x70
#define TSENSOR_STATUS0 0X78

#define Vmin_core 840000
#define Vmax_core 940000

#define Vmin_mda 868000
#define Vmax_mda 973000

static unsigned hpm_value_avg(unsigned int* val)
{
    unsigned int i;
    unsigned tmp = 0;

    for (i = 0; i < 4; i++) {
        tmp += val[i] >> 2;
    }

    return tmp >> 2;
}

static void get_hpm_value(unsigned int* hpm_core, unsigned int* hpm_cpu, unsigned int* hpm_mda)
{
    int i;
    unsigned int temp;
    unsigned int core_value[4];
    unsigned int mda_value[4];
    unsigned int cpu_value[4];

    core_value[0] = 0;
    core_value[1] = 0;
    core_value[2] = 0;
    core_value[3] = 0;

    mda_value[0] = 0;
    mda_value[1] = 0;
    mda_value[2] = 0;
    mda_value[3] = 0;

    cpu_value[0] = 0;
    cpu_value[1] = 0;
    cpu_value[2] = 0;
    cpu_value[3] = 0;

    for (i = 0; i < CYCLE_NUM; i++) {
        delay(100);

        /* cpu */
        temp = readl(HI_PMC_CTL_REG + HPM_CPU_REG0);
        cpu_value[1] += (temp >> 16) & 0x3ff;
        cpu_value[0] += temp & 0x3ff;
        temp = readl(HI_PMC_CTL_REG + HPM_CPU_REG1);
        cpu_value[3] += (temp >> 16) & 0x3ff;
        cpu_value[2] += temp & 0x3ff;

        /* mda */
        temp = readl(HI_PMC_CTL_REG + HPM_MDA_REG0);
        mda_value[1] += (temp >> 16) & 0x3ff;
        mda_value[0] += temp & 0x3ff;
        temp = readl(HI_PMC_CTL_REG + HPM_MDA_REG1);
        mda_value[3] += (temp >> 16) & 0x3ff;
        mda_value[2] += temp & 0x3ff;

        /* core */
        temp = readl(HI_PMC_CTL_REG + HPM_CORE_REG0);
        core_value[1] += (temp >> 16) & 0x3ff;
        core_value[0] += temp & 0x3ff;
        temp = readl(HI_PMC_CTL_REG + HPM_CORE_REG1);
        core_value[3] += (temp >> 16) & 0x3ff;
        core_value[2] += temp & 0x3ff;
    }

    *hpm_core = hpm_value_avg(core_value);
    *hpm_mda = hpm_value_avg(mda_value);
    *hpm_cpu = hpm_value_avg(cpu_value);
}

static void start_hpm(unsigned int* hpm_core, unsigned int* hpm_cpu, unsigned int* hpm_mda)
{
    /* core */
    writel(0x60000201, HI_PMC_CTL_REG + 0x1210);
    /* mda  */
    writel(0x60000201, HI_PMC_CTL_REG + 0x1220);
    /* cpu  */
    writel(0x60000201, HI_PMC_CTL_REG + 0x1200);

    delay(500);

    get_hpm_value(hpm_core, hpm_cpu, hpm_mda);
}

static void set_hpm_core_volt(unsigned int hpm_core_value)
{
    unsigned long long mv1000;
    unsigned long long svb_value;

    mv1000 = 1377500 - 1250 * (unsigned long long)hpm_core_value;/* svb10 */
    if(mv1000 < Vmin_core) {
        mv1000 = Vmin_core;
    }
    if(mv1000 > Vmax_core) {
        mv1000 = Vmax_core;
    }

    svb_value = (((943000 - mv1000) * 80) & 0xffff0000) + 0x19f5;

    writel((unsigned int)svb_value, HPM_CORE_VOL_REG);
}

static void set_hpm_mda_volt(unsigned int hpm_mda_value)
{
    unsigned long long mv1000;
    unsigned long long svb_value;


    mv1000 = 1477000 - 1400 * (unsigned long long)hpm_mda_value; /*svb10*/
    if(mv1000 < Vmin_mda) {
        mv1000 = Vmin_mda;
    }
    if(mv1000 > Vmax_mda) {
        mv1000 = Vmax_mda;
    }

    svb_value = (((1000000 - mv1000) * 68) & 0xffff0000) + 0x19f5;

    writel((unsigned int)svb_value, HPM_MDA_VOL_REG);
}

static void hpm_check(unsigned int* hpm_core, unsigned int* hpm_cpu, unsigned int* hpm_mda, unsigned int hpm_from_otp)
{
    union {
        struct {
            unsigned int sys_hpm_mda : 9; /* [8..0]*/
            unsigned int sys_hpm_cpu : 9; /* [17..9]*/
            unsigned int sys_hpm_core : 9; /* [26..18]*/
            unsigned int from_otp : 1; /* [27]*/
            unsigned int hpm_mda_err : 1; /* [28]*/
            unsigned int hpm_cpu_err : 1; /* [29]*/
            unsigned int hpm_core_err : 1; /* [30]*/
            unsigned int reserved_0 : 1; /* [31]*/
        } bits;

        unsigned int u32;
    } sysboot10;
    sysboot10.u32 = 0;

    if(*hpm_core < 300) {
        *hpm_core = 300;
        sysboot10.bits.hpm_core_err = 1;
    }
    if(*hpm_core > 480) {
        *hpm_core = 480;
        sysboot10.bits.hpm_core_err = 1;
    }

    if(*hpm_cpu < 300) {
        *hpm_cpu = 300;
        sysboot10.bits.hpm_cpu_err = 1;
    }
    if(*hpm_cpu > 480) {
        *hpm_cpu = 480;
        sysboot10.bits.hpm_cpu_err = 1;
    }

    if(*hpm_mda < 300) {
        *hpm_mda = 300;
        sysboot10.bits.hpm_mda_err = 1;
    }
    if(*hpm_mda > 480) {
        *hpm_mda = 480;
        sysboot10.bits.hpm_mda_err = 1;
    }

    sysboot10.bits.sys_hpm_core = *hpm_core;
    sysboot10.bits.sys_hpm_cpu = *hpm_cpu;
    sysboot10.bits.sys_hpm_mda = *hpm_mda;
    sysboot10.bits.from_otp = hpm_from_otp;

    writel(sysboot10.u32, HPM_CHECK_REG);

}

static void adjust_hpm_by_temperature(unsigned int* hpm_core, unsigned int* hpm_cpu, unsigned int* hpm_mda, int temperature)
{
    int adjust_value;
    adjust_value = (4835 - 154 * temperature) >> 10;
    *hpm_core -= adjust_value;
    *hpm_cpu -= adjust_value;
    *hpm_mda -= adjust_value;
}
static void get_temperature(int *temperature)
{
    int value = 0;

    value = readl(HI_PMC_CTL_REG + TSENSOR_STATUS0);
    value = value & 0x3ff;

    *temperature = (((value - 116) * 210) >> 10 ) - 40;

    if(*temperature > 150) {
        *temperature = 150;
    }
    if(*temperature < -70) {
        *temperature = -70;
    }

}

static void start_svb(void)
{
    unsigned int hpm_core;
    unsigned int hpm_cpu;
    unsigned int hpm_mda;
    unsigned int hpm_from_otp;
    unsigned int svb_version;
    int temperature;

    svb_version = readl(VERSION_REG);
    svb_version &= 0xff00ffff;
    svb_version |= (SVB_VERSION << 16);
    writel(svb_version, VERSION_REG);

    hpm_core = (unsigned int)(short)((short)(readl(OTP_HPM_CORE_REG) & 0xffff)
                                     + (short)((readl(OTP_HPM_CORE_REG) >> 16) & 0xffff));
    hpm_mda  = (unsigned int)(short)((short)(readl(OTP_HPM_MDA_REG) & 0xffff)
                                     + (short)((readl(OTP_HPM_MDA_REG) >> 16) & 0xffff));
    hpm_cpu  = (unsigned int)(short)((short)(readl(OTP_HPM_CPU_REG) & 0xffff)
                                     + (short)((readl(OTP_HPM_CPU_REG) >> 16) & 0xffff));


    if ((!hpm_core) || (!hpm_mda) || (!hpm_cpu)) {
        /* open hmp clock */
        writel(0xfff0000, HMP_CLK_REG);
        start_hpm(&hpm_core, &hpm_cpu, &hpm_mda);
        get_temperature(&temperature);
        adjust_hpm_by_temperature(&hpm_core, &hpm_cpu, &hpm_mda, temperature);
        hpm_from_otp = 0;
    } else {
        /*ATE SVB transfer to board SVB*/
        hpm_core += 6;
        hpm_cpu  += 7;
        hpm_mda  += 7;
        hpm_from_otp = 1;
    }

    hpm_check(&hpm_core, &hpm_cpu, &hpm_mda, hpm_from_otp);

    set_hpm_core_volt(hpm_core);
    set_hpm_mda_volt(hpm_mda);
    /* delay 10ms do not delete */
    delay(280);
}

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
#ifdef DDR_SCRAMB_ENABLE
    /* enable ddr scramb */
    ddr_scramb();
#endif
}
