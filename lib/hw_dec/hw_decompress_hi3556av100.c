#include <asm/io.h>
#include <config.h>

#define PERI_CRG82 0x148
#define GZIP_CLKEN (1<<1)

#ifndef GZIP_REG_BASE
#define GZIP_REG_BASE   0x04790000
#endif

#define HW_DEC_REG_BASE_ADDR  (GZIP_REG_BASE)

static void disable_decompress_clock(void)
{
    unsigned int regval;

    regval = readl(CRG_REG_BASE + PERI_CRG82);
    regval &= ~GZIP_CLKEN;
    writel(regval, CRG_REG_BASE + PERI_CRG82);
}

static void enable_decompress_clock(void)
{
    unsigned int regval;

    regval = readl(CRG_REG_BASE + PERI_CRG82);
    regval |= GZIP_CLKEN;
    writel(regval, CRG_REG_BASE + PERI_CRG82);
}
