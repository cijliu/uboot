/*
 * SVB driver:
 */

#include <asm/io.h>
#include <div64.h>
#include "hisvb.h"
#include <configs/hi3556av100.h>

#define SVB_VERSION 0x10

#define HI_PMC_CTL_REG          0x04528000
#define HPM_CORE_VOL_REG        (HI_PMC_CTL_REG + 0x60)
#define HPM_CPU_VOL_REG         (HI_PMC_CTL_REG + 0x64)
#define HPM_MDA_VOL_REG         (HI_PMC_CTL_REG + 0x68)
#define CYCLE_NUM               4
#define HPM_CPU_REG0            0x1208
#define HPM_CPU_REG1            0x120c
#define HPM_MDA_REG0            0x1228
#define HPM_MDA_REG1            0x122c
#define HPM_CORE_REG0           0x1218
#define HPM_CORE_REG1           0x121c

#define HMP_CLK_REG             0x0451019c

#define HPM_CHECK_REG           0x04520158
#define VERSION_REG             0x0452015c

#define OTP_HPM_CORE_REG        0x040b0028
#define OTP_HPM_MEDIA_REG   0x040b002c
#define OTP_HPM_CPU_REG         0x040b0034

#define TSENSOR_CTRL            0x70
#define TSENSOR_STATUS0         0X78

#define Vmin_core   750
#define Vmax_core   890

#define Vmin_cpu    740
#define Vmax_cpu    940

#define Vmin_media  670
#define Vmax_media  835

#define FREFIX_MEDIA_VOLTAGE    900 //900mV
#define FREFIX_CORE_VOLTAGE 900
#define FREFIX_CPU_VOLTAGE  900
#define FREFIX_DDR_IO_VOLTAGE   1100    //1100mv

static unsigned hpm_value_avg(unsigned int* val)
{
    unsigned int i;
    unsigned tmp = 0;

    for (i = 0; i < 4; i++) {
        tmp += val[i] >> 2;
    }

    return tmp >> 2;
}

static void get_hpm_value(unsigned int *hpm_core,
                          unsigned int *hpm_cpu, unsigned int *hpm_mda)
{
    int i;
    unsigned int temp;
    unsigned int core_value[4] = {0};
    unsigned int mda_value[4] = {0};
    unsigned int cpu_value[4] = {0};

    for (i = 0; i < CYCLE_NUM; i++) {
        delay_cycles(100);

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

static void start_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu, unsigned int *hpm_mda)
{
    /* core */
    writel(0x60000201, HI_PMC_CTL_REG + 0x1210);

    /* mda  */
    writel(0x60000201, HI_PMC_CTL_REG + 0x1220);

    /* cpu  */
    writel(0x60000201, HI_PMC_CTL_REG + 0x1200);

    delay_cycles(500);

    get_hpm_value(hpm_core, hpm_cpu, hpm_mda);

    *hpm_core = (unsigned int)(short)((short)(*hpm_core) + (short)((readl(OTP_HPM_CORE_REG) >> 16) & 0xffff));
    *hpm_mda  = (unsigned int)(short)((short)(*hpm_mda) + (short)((readl(OTP_HPM_MEDIA_REG) >> 16) & 0xffff));
    *hpm_cpu  = (unsigned int)(short)((short)(*hpm_cpu) + (short)((readl(OTP_HPM_CPU_REG) >> 16) & 0xffff));
}

/*
 * transfer form: voltage = 1307.5 - 1.25 * hpm  (mV)
 */
static unsigned int hpm_core_to_voltage(unsigned int hpm)
{
    unsigned int voltage = 1307500 - 1250 * hpm;

    voltage = voltage / 1000;
    if (voltage < Vmin_core) {
        voltage = Vmin_core;
    }
    if (voltage > Vmax_core) {
        voltage = Vmax_core;
    }

    return voltage;
}

/*
 * transfer form: voltage = 1070.77 - 0.842 * hpm  (mV)
 */
static unsigned int hpm_media_to_voltage(unsigned int hpm)
{
    unsigned int voltage = 1070770 - 842 * hpm;
    int avsp_on;
    unsigned int svb_version = readl(VERSION_REG);

    voltage = voltage / 1000;

    avsp_on = ((svb_version >> 30) & 0x1);
    if (avsp_on) {
        voltage += 50;
    }

    if (voltage < Vmin_media) {
        voltage = Vmin_media;
    }
    if (voltage > Vmax_media) {
        voltage = Vmax_media;
    }

    return voltage;
}

static unsigned int hpm_cpu_to_voltage(unsigned int hpm)
{
    unsigned int voltage = 1379000 - 1400 * hpm;
    int intacc_on;
    unsigned int svb_version = readl(VERSION_REG);

    voltage = voltage / 1000;

    intacc_on = (svb_version >> 31) & 0x1;
    if (intacc_on) {
        voltage += 40;
    }

    if (voltage < Vmin_cpu) {
        voltage = Vmin_media;
    }
    if (voltage > Vmax_cpu) {
        voltage = Vmax_cpu;
    }

    return voltage;
}

static void hpm_check(unsigned int *hpm_core, unsigned int *hpm_cpu,
                      unsigned int *hpm_mda, unsigned int hpm_from_otp)
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
            unsigned int svb_56a : 1; /* [31]*/
        } bits;

        unsigned int u32;
    } sysboot10;

    sysboot10.u32 = 0;

    if (*hpm_core < 300) {
        *hpm_core = 300;
        sysboot10.bits.hpm_core_err = 1;
    }

    if (*hpm_core > 480) {
        *hpm_core = 480;
        sysboot10.bits.hpm_core_err = 1;
    }

    if (*hpm_cpu < 300) {
        *hpm_cpu = 300;
        sysboot10.bits.hpm_cpu_err = 1;
    }

    if (*hpm_cpu > 480) {
        *hpm_cpu = 480;
        sysboot10.bits.hpm_cpu_err = 1;
    }

    if (*hpm_mda < 300) {
        *hpm_mda = 300;
        sysboot10.bits.hpm_mda_err = 1;
    }

    if (*hpm_mda > 480) {
        *hpm_mda = 480;
        sysboot10.bits.hpm_mda_err = 1;
    }

    sysboot10.bits.sys_hpm_core = *hpm_core;
    sysboot10.bits.sys_hpm_cpu = *hpm_cpu;
    sysboot10.bits.sys_hpm_mda = *hpm_mda;
    sysboot10.bits.from_otp = hpm_from_otp;

    sysboot10.bits.svb_56a = 1;
    writel(sysboot10.u32, HPM_CHECK_REG);
}

static void adjust_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu,
                       unsigned int *hpm_mda, int temperature)
{
    int adjust_value;

    adjust_value = (4835 - 154 * temperature) >> 10;

    *hpm_core -= adjust_value;
    *hpm_cpu -= adjust_value;
    *hpm_mda -= adjust_value;
}

static void get_chip_temperature(int *temperature)
{
    int value = 0;

    value = readl(HI_PMC_CTL_REG + TSENSOR_STATUS0);
    value = value & 0x3ff;

    *temperature = (((value - 116) * 210) >> 10 ) - 40;

    if (*temperature > 150) {
        *temperature = 150;
    }

    if (*temperature < -70) {
        *temperature = -70;
    }
}

/*
 * Note: the output voltages should be stable before this function returns.
 */
void svb_preset(void)
{
#define I2C_PMU_DEBUG 0
#if (I2C_PMU_DEBUG == 1)
    pmu_voltage_set(DOMAIN_MEDIA, FREFIX_MEDIA_VOLTAGE);
    pmu_voltage_set(DOMAIN_CORE, FREFIX_CORE_VOLTAGE);
    pmu_voltage_set(DOMAIN_CPU, FREFIX_CPU_VOLTAGE);
    pmu_voltage_set(DOMAIN_DDR, FREFIX_DDR_IO_VOLTAGE);
#endif
}

/*
 * Please make sure this function is called BEFORE DDR-training.
 */
void svb_start(void)
{
    unsigned int hpm_core;
    unsigned int hpm_cpu;
    unsigned int hpm_mda;
    unsigned int svb_version;
    int temperature;
    unsigned int value;

    unsigned int voltage;

    /* Set SVB software version to version-reg */
    svb_version = readl(VERSION_REG);
    svb_version &= 0xff00ffff;
    svb_version |= (SVB_VERSION << 16);
    writel(svb_version, VERSION_REG);



    /* hmp clock enable */
    writel(0xfff0000, HMP_CLK_REG);
    /* get hmp value from register */
    start_hpm(&hpm_core, &hpm_cpu, &hpm_mda);

    get_chip_temperature(&temperature);

    adjust_hpm(&hpm_core, &hpm_cpu, &hpm_mda, temperature);

    hpm_check(&hpm_core, &hpm_cpu, &hpm_mda, 0);

    /*
     * Start adjust the voltage of each domain.
     */
    voltage = hpm_core_to_voltage(hpm_core);
#ifdef I2C_PMU_ENABLE
    pmu_voltage_set(DOMAIN_CORE, voltage);
#else
    pwm_voltage_set(DOMAIN_CORE, voltage);
#endif

    voltage = hpm_media_to_voltage(hpm_mda);
#ifdef I2C_PMU_ENABLE
    pmu_voltage_set(DOMAIN_MEDIA, voltage);
#else
    pwm_voltage_set(DOMAIN_MEDIA, voltage);
#endif

    voltage = hpm_cpu_to_voltage(hpm_cpu);
#ifdef I2C_PMU_ENABLE
    pmu_voltage_set(DOMAIN_CPU, voltage);
#else
    pwm_voltage_set(DOMAIN_CPU, voltage);
#endif
    /*
     * Need to wait for a little while after voltage adjust!
     */
    delay_cycles(280);
}

