#include <asm/io.h>
#include "hisvb.h"

#define HI_PMC_CTL_REG      0x04528000

#define PMC_VOLT_CORE_REG   (HI_PMC_CTL_REG + 0x60)
#define PMC_VOLT_CPU_REG    (HI_PMC_CTL_REG + 0x64)
#define PMC_VOLT_MEDIA_REG  (HI_PMC_CTL_REG + 0x68)

unsigned int core_voltage_to_svb_unit(unsigned int voltage)
{
    unsigned int value = (943000 - voltage * 1000) * 80;
    value &= 0xffff0000;
    value += 0x19f5;
    return value;
}

unsigned int cpu_voltage_to_svb_unit(unsigned int voltage)
{
    unsigned int value = (1000000 - voltage * 1000) * 68;
    value &= 0xffff0000;
    value += 0x19f5;
    return value;
}

unsigned int media_voltage_to_svb_unit(unsigned int voltage)
{
    unsigned int value = (943000 - voltage * 1000) * 80;
    value &= 0xffff0000;
    value += 0x19f5;
    return value;
}

void pwm_voltage_set(enum power_domain domain, unsigned int voltage)
{
    unsigned int value;

    switch (domain) {
        case DOMAIN_MEDIA:
            value = media_voltage_to_svb_unit(voltage);
            writel(value, PMC_VOLT_MEDIA_REG);
            break;
        case DOMAIN_CORE:
            value = core_voltage_to_svb_unit(voltage);
            writel(value, PMC_VOLT_CORE_REG);
            break;
        case DOMAIN_CPU:
            value = cpu_voltage_to_svb_unit(voltage);
            writel(value, PMC_VOLT_CPU_REG);
            break;
        case DOMAIN_DDR:
            break;
        case DOMAIN_GPU:
            break;
        default:
            break;
    }

    /* all done, need to wait? */
}
