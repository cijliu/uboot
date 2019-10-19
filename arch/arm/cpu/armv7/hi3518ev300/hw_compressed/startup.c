/*
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
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

#include <config.h>
#include <linux/kconfig.h>
#include <asm/io.h>

/******************************************************************************/
extern void uart_early_init(void);
extern void uart_early_puts(const char *ss);
extern void reset_cpu(unsigned long addr);
/******************************************************************************/
const unsigned long IMAGE_ENTRY = (CONFIG_SYS_TEXT_BASE);

extern unsigned char input_data[];
extern unsigned char input_data_end[];
extern unsigned long _armboot_start;

/******************************************************************************/
#define error(_s)               uart_early_puts(_s)
#define putstr(_s)              uart_early_puts(_s)

#include "hw_decompress.c"
#define GZIP_SIZE_OFFSET 0x4
extern unsigned int hw_dec_type;

#ifndef CONFIG_SYS_ICACHE_OFF
/* Invalidate entire I-cache and branch predictor array */
static void invalidate_icache_all(void)
{
    /*
     * Invalidate all instruction caches to PoU.
     * Also flushes branch target cache.
     */
    asm volatile ("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));

    /* Invalidate entire branch predictor array */
    asm volatile ("mcr p15, 0, %0, c7, c5, 6" : : "r" (0));

    /* Full system DSB - make sure that the invalidation is complete */
    dsb();

    /* ISB - make sure the instruction stream sees it */
    isb();
}
#else
static void invalidate_icache_all(void)
{
}
#endif

#ifdef CONFIG_MINI_BOOT

#ifndef BIT
#define BIT(x) (1 << (x))
#endif

#define TIME2_CLK_SEL  BIT(18)

int timer_init(void)
{
    /*
     **Under uboot, 0xffffffff is set to load register,
     ** timer_clk = BUSCLK/2/256.
     ** e.g. BUSCLK = 50M, it will roll back after 0xffffffff/timer_clk
     ** = 43980s = 12hours
     **/
    __raw_writel(0, CFG_TIMERBASE + REG_TIMER_CONTROL);
    __raw_writel(~0, CFG_TIMERBASE + REG_TIMER_RELOAD);

    /*32 bit, periodic*/
    __raw_writel(CFG_TIMER_CTRL, CFG_TIMERBASE + REG_TIMER_CONTROL);


    /*start timer2 with mode below*/
    unsigned int reg = 0;

    reg = __raw_readl(SYS_CTRL_REG_BASE + REG_SC_CTRL);
    //for timer2,use sys BUS clk
    reg |= TIME2_CLK_SEL;
    __raw_writel(reg, SYS_CTRL_REG_BASE + REG_SC_CTRL);

    //disable timer2
    __raw_writel(0, TIMER2_REG_BASE + REG_TIMER_CONTROL);
    //timer2 load
    __raw_writel(~0, TIMER2_REG_BASE + REG_TIMER_RELOAD);

    /*
     * Timing mode: 32bits [bit 1 set as 1]
     * ticking with 1/256 clock frequency [bit 3 set as 1, bit 2 set as 0]
     * timing circulary [bit 6 set as 1]
     * timer enabled [bit 7 set as 1]
     */
    reg = (1 << 7) | (1 << 6) | (1 << 3) | (1 << 1);
    __raw_writel(reg, TIMER2_REG_BASE + REG_TIMER_CONTROL);

    return 0;
}

#define TIME_STAMP_CNT      0x12020138
#define TIME_STAMP_VALUE    0x04010050
#define CONFIG_TIME_STAMP_ENABLE

void time_stamp(const char *strFunc, int nLine, int type)
{
#ifdef CONFIG_TIME_STAMP_ENABLE
    static int init_flag = 0;
    unsigned int cnt;
    unsigned int stamp;
    unsigned int *addr;

    if (!init_flag) {
        init_flag = 1;
        *(unsigned int *)TIME_STAMP_CNT = 0;
    }

    cnt = *(unsigned int *)TIME_STAMP_CNT;
    stamp = *(unsigned int *)(TIMER2_REG_BASE + REG_TIMER_VALUE);
    addr = (unsigned int *)(TIME_STAMP_VALUE + cnt * 16);

    *addr = ~stamp;
    addr++;
    *addr = (unsigned int)strFunc;
    addr++;
    *addr = nLine;
    addr++;
    *addr = type;
    cnt++;
    *(unsigned int *)TIME_STAMP_CNT = cnt;
#endif
}
#endif


/******************************************************************************/
void start_armboot(void)
{
    unsigned char *pdst_l32 = NULL;
    unsigned int image_data_len;
    int pdst_len;
    int ret;
    int i;
    char *p = NULL;
    char *q = NULL;

#ifndef CONFIG_MINI_BOOT
    uart_early_init();
    uart_early_puts("\r\nUncompress ");
#endif

    /*use direct address mode*/
    hw_dec_type = 0;
    /*init hw decompress IP*/
    hw_dec_init();

    /*start decompress*/
    pdst_l32 = (unsigned char *)IMAGE_ENTRY;
    image_data_len = input_data_end - input_data;

    /*get dets length from compress image*/
    p = (char *)&pdst_len;
    q = (char *)(input_data_end - GZIP_SIZE_OFFSET);
    for (i = 0; i < sizeof(int); i++) {
        p[i] = q[i];
    }

    ret = hw_dec_decompress(pdst_l32, &pdst_len, input_data, image_data_len, NULL);
    if (!ret) {
#ifndef CONFIG_MINI_BOOT
        uart_early_puts("Ok!");
#endif
    } else {
#ifndef CONFIG_MINI_BOOT
        uart_early_puts("Fail!");
#endif
        while(1);
    }

    /*uinit hw decompress IP*/
    hw_dec_uinit();
    void (*uboot)(void);
    uboot = (void (*))CONFIG_SYS_TEXT_BASE;
    invalidate_icache_all();
    uboot();
}

/******************************************************************************/
void hang(void)
{
    uart_early_puts("### ERROR ### Please RESET the board ###\n");
    for (;;) { } ;
}


void do_bad_sync(void)
{
    uart_early_puts("bad sync abort\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}

void do_sync(void)
{
    uart_early_puts("sync abort\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}

void do_bad_error(void)
{
    uart_early_puts("bad error\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}

void do_error(void)
{
    uart_early_puts("error\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}

void do_bad_fiq(void)
{
    uart_early_puts("bad fast interrupt request\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}

void do_bad_irq(void)
{
    uart_early_puts("bad interrupt request\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}

void do_fiq(void)
{
    uart_early_puts("fast interrupt request\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}

void do_irq(void)
{
    uart_early_puts("interrupt request\r\n");
    uart_early_puts("Resetting CPU ...\r\n");
    reset_cpu(0);
}
