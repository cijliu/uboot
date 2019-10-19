/*
 * (C) Copyright 2015 Linaro
 * Peter Griffin <peter.griffin@linaro.org>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */
#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <spi_flash.h>
#include <linux/mtd/mtd.h>
#include <nand.h>
#include <netdev.h>
#include <mmc.h>
#include <sdhci.h>
#include <asm/armv8/mmu.h>
#include <command.h>

static struct mm_region hi3559av100_mem_map[] = {
    {
        .virt = 0x0UL,
        .phys = 0x0UL,
        .size = 0x40000000UL,
        .attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
        PTE_BLOCK_NON_SHARE
    }, {
        .virt = 0x40000000UL,
        .phys = 0x40000000UL,
        .size = 0x200000000,//PHYS_SDRAM_1_SIZE,
        .attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
        PTE_BLOCK_INNER_SHARE
    }, {
        /* List terminator */
        0,
    }
};

struct mm_region *mem_map = hi3559av100_mem_map;
static int boot_media = BOOT_MEDIA_UNKNOWN;

#if defined(CONFIG_SHOW_BOOT_PROGRESS)
void show_boot_progress(int progress)
{
    printf("Boot reached stage %d\n", progress);
}
#endif

#define COMP_MODE_ENABLE ((unsigned int)0x0000EAEF)

static inline void delay(unsigned long loops)
{
    __asm__ volatile ("1:\n"
                      "subs %0, %1, #1\n"
                      "bne 1b" : "=r" (loops) : "0" (loops));
}

/* get uboot start media. */
int get_boot_media(void)
{
    return boot_media;
}

int get_text_base(void)
{
    return CONFIG_SYS_TEXT_BASE;
}

static void boot_flag_init(void)
{
    unsigned int regval, boot_mode;

    /* get boot mode */
    regval = __raw_readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);
    boot_mode = GET_SYS_BOOT_MODE(regval);

    switch (boot_mode) {
        /* [5:4] 00b - boot from spi device */
        case BOOT_FROM_SPI:
            /* get SPI device type, (0: SPI nor | 1: SPI nand) */
            if (GET_SPI_DEVICE_TYPE(regval)) {
                boot_media = BOOT_MEDIA_NAND;
            } else {
                boot_media = BOOT_MEDIA_SPIFLASH;
            }
            break;
        /* [5:4] 01b - boot from Nand device */
        case BOOT_FROM_NAND:
            boot_media = BOOT_MEDIA_NAND;
            break;
        /* [5:4] 10b - boot from emmc */
        case BOOT_FROM_EMMC:
            boot_media = BOOT_MEDIA_EMMC;
            break;
        /* [5:4] 11b - boot from ufs */
        case BOOT_FROM_UFS:
            boot_media = BOOT_MEDIA_UFS;
            break;
        default:
            boot_media = BOOT_MEDIA_UNKNOWN;
            break;
    }
}

int board_early_init_f(void)
{
    return 0;
}

#define UBOOT_DATA_ADDR     (0x41000000)
#define UBOOT_DATA_SIZE     (0x80000)
int save_bootdata_to_flash(void)
{
    unsigned int sd_update_flag;
    void *buf;

    sd_update_flag = readl(REG_BASE_SCTL + REG_SC_GEN4);
    if (sd_update_flag == START_MAGIC) {
#if defined(CONFIG_HIFMC)
        static struct spi_flash *flash;
        unsigned int val;
        if (boot_media == BOOT_MEDIA_SPIFLASH) {
            flash = spi_flash_probe(0, 0, 1000000, 0x3);
            if (!flash) {
                printf("Failed to initialize SPI flash\n");
                return -1;
            }

            /* erase the address range. */
            printf("Spi flash erase...\n");
            val = flash->erase(flash, 0, UBOOT_DATA_SIZE);
            if (val) {
                printf("SPI flash sector erase failed\n");
                return 1;
            }

            buf = map_physmem((unsigned long)UBOOT_DATA_ADDR,
                              UBOOT_DATA_SIZE, MAP_WRBACK);
            if (!buf) {
                puts("Failed to map physical memory\n");
                return 1;
            }

            /* copy the data from RAM to FLASH */
            printf("Spi flash write...\n");
            val = flash->write(flash, 0, UBOOT_DATA_SIZE, buf);
            if (val) {
                printf("SPI flash write failed, return %d\n",
                       val);
                unmap_physmem(buf, UBOOT_DATA_SIZE);
                return 1;
            }

            unmap_physmem(buf, UBOOT_DATA_SIZE);
        }
        if (boot_media == BOOT_MEDIA_NAND) {
            struct mtd_info *nand_flash;
            size_t length = UBOOT_DATA_SIZE;

            nand_flash = nand_info[0];

            printf("Nand flash erase...\n");
            val = nand_erase(nand_flash, 0, UBOOT_DATA_SIZE);
            if (val) {
                printf("Nand flash erase failed\n");
                return 1;
            }

            buf = map_physmem((unsigned long)UBOOT_DATA_ADDR,
                              UBOOT_DATA_SIZE, MAP_WRBACK);
            if (!buf) {
                puts("Failed to map physical memory\n");
                return 1;
            }

            printf("Nand flash write...\n");
            val = nand_write(nand_flash, 0, &length, buf);
            if (val) {
                printf("Nand flash write failed, return %d\n",
                       val);
                unmap_physmem(buf, UBOOT_DATA_SIZE);
                return 1;
            }

            unmap_physmem(buf, UBOOT_DATA_SIZE);
        }
#endif
#if defined(CONFIG_MMC)
        if (boot_media == BOOT_MEDIA_EMMC) {
            struct mmc *mmc = find_mmc_device(0);

            if (!mmc) {
                return 1;
            }

            (void)mmc_init(mmc);

            buf = map_physmem((unsigned long)UBOOT_DATA_ADDR,
                              UBOOT_DATA_SIZE, MAP_WRBACK);
            if (!buf) {
                puts("Failed to map physical memory\n");
                return 1;
            }

            printf("MMC write...\n");
            blk_dwrite(mmc_get_blk_desc(mmc), 0, (UBOOT_DATA_SIZE >> 9), buf);
            unmap_physmem(buf, UBOOT_DATA_SIZE);
        }
#endif

        printf("update success!\n");
    }

    return 0;
}

int auto_update_flag = 0;
int bare_chip_program = 0;

#define REG_BASE_GPIO0          0x12140000
#define GPIO0_0_DATA_OFST       0x4
#define GPIO_DIR_OFST       0x400

int is_bare_program(void)
{
    return 1;
}

int is_auto_update(void)
{
#if (defined CONFIG_AUTO_SD_UPDATE) || (defined CONFIG_AUTO_USB_UPDATE)
    /* to add some judgement if neccessary */
    unsigned int  val[3];

    writel(REG_BASE_GPIO0 + GPIO_DIR_OFST, 0);

    val[0] = readl(REG_BASE_GPIO0 + GPIO0_0_DATA_OFST);
    if(val[0]) {
        return 0;
    }

    udelay(10000);
    val[1] = readl(REG_BASE_GPIO0 + GPIO0_0_DATA_OFST);
    udelay(10000);
    val[2] = readl(REG_BASE_GPIO0 + GPIO0_0_DATA_OFST);
    udelay(10000);

    if (val[0] == val[1] && val[1] == val[2] && val[0] == 0) {
        return 1;    /* update enable */
    } else {
        return 0;
    }

#else
    return 0;
#endif
}

void set_pcie_para_hi3559a(void)
{
    int val;
    val = readl(SYS_CTRL_REG_BASE + SYS_SATA);
    if((val & (0x3 << PCIE_MODE)) == 0) {

        /*X2 release phy reset*/
        val = readl(CRG_REG_BASE + PERI_CRG98);
        val &= ((~(0x1 << phy1_srs_req)) & (~(0x1 << phy0_srs_req)));
        writel(val, CRG_REG_BASE + PERI_CRG98);

        /*X2 select phy reset from crg*/
        val = readl(CRG_REG_BASE + PERI_CRG98);
        val |= (0x1 << phy1_srs_req_sel) | (0x1 << phy0_srs_req_sel);
        writel(val, CRG_REG_BASE + PERI_CRG98);
        mdelay(10);

        /*
         ** X2 seperate_rate=1
         **/
        writel(0x90f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x94f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x90f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x0, MISC_REG_BASE + MISC_CTRL5);
        writel(0x92f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x96f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x92f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x0, MISC_REG_BASE + MISC_CTRL5);
        mdelay(10);

        /*
         ** X2 split_cp_dis
         **/
        writel(0xd11, MISC_REG_BASE + MISC_CTRL5);
        writel(0xd51, MISC_REG_BASE + MISC_CTRL5);
        writel(0xd11, MISC_REG_BASE + MISC_CTRL5);
        writel(0x0, MISC_REG_BASE + MISC_CTRL5);
        writel(0xd31, MISC_REG_BASE + MISC_CTRL5);
        writel(0xd71, MISC_REG_BASE + MISC_CTRL5);
        writel(0xd31, MISC_REG_BASE + MISC_CTRL5);
        writel(0x0, MISC_REG_BASE + MISC_CTRL5);
        mdelay(10);
    } else {

        /*X1 release phy reset*/
        val = readl(CRG_REG_BASE + PERI_CRG98);
        val &= ~(0x1 << phy0_srs_req);
        writel(val, CRG_REG_BASE + PERI_CRG98);

        /*X1 select phy reset from crg*/
        val = readl(CRG_REG_BASE + PERI_CRG98);
        val |= (0x1 << phy0_srs_req_sel);
        writel(val, CRG_REG_BASE + PERI_CRG98);
        mdelay(10);

        /*
         ** X1 seperate_rate=1
         **/
        writel(0x90f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x94f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x90f, MISC_REG_BASE + MISC_CTRL5);
        writel(0x0, MISC_REG_BASE + MISC_CTRL5);
        mdelay(10);

        /*
         ** X1 split_cp_dis
         **/
        writel(0xd11, MISC_REG_BASE + MISC_CTRL5);
        writel(0xd51, MISC_REG_BASE + MISC_CTRL5);
        writel(0xd11, MISC_REG_BASE + MISC_CTRL5);
        writel(0x0, MISC_REG_BASE + MISC_CTRL5);
        mdelay(10);

    };
}

int misc_init_r(void)
{
#ifdef CONFIG_RANDOM_ETHADDR
    random_init_r();
#endif
    setenv("verify", "n");

#if (CONFIG_AUTO_UPDATE == 1)
    /* auto update flag */
    if(is_auto_update()) {
        auto_update_flag = 1;
    } else {
        auto_update_flag = 0;
    }

    /* bare chip program flag */
    if(is_bare_program()) {
        bare_chip_program = 1;
    } else {
        bare_chip_program = 0;
    }

#ifdef CFG_MMU_HANDLEOK
    dcache_stop();
#endif

#ifdef CFG_MMU_HANDLEOK
    dcache_start();
#endif

#endif /*CONFIG_AUTO_UPDATE*/

#if (CONFIG_AUTO_UPDATE == 1)
    extern int do_auto_update(void);
    if (auto_update_flag) {
        do_auto_update();
    }
    if (bare_chip_program && !auto_update_flag) {
        save_bootdata_to_flash();
    }
#endif /*CONFIG_AUTO_UPDATE*/
    set_pcie_para_hi3559a();
    return 0;
}

int board_init(void)
{
    DECLARE_GLOBAL_DATA_PTR;

    gd->bd->bi_arch_number = MACH_TYPE_HI3559AV100;
    gd->bd->bi_boot_params = CFG_BOOT_PARAMS;

    boot_flag_init();

    return 0;
}

int dram_init(void)
{
    DECLARE_GLOBAL_DATA_PTR;

    gd->ram_size = PHYS_SDRAM_1_SIZE;
    return 0;
}

void reset_cpu(ulong addr)
{
    writel(0x12345678, REG_BASE_SCTL + REG_SC_SYSRES);
    while(1);
}

int timer_init(void)
{
    /*
     *  *Under uboot, 0xffffffff is set to load register,
     *   * timer_clk = BUSCLK/2/256.
     *    * e.g. BUSCLK = 50M, it will roll back after 0xffffffff/timer_clk
     *     * = 43980s = 12hours
     *      */
    __raw_writel(0, CFG_TIMERBASE + REG_TIMER_CONTROL);
    __raw_writel(~0, CFG_TIMERBASE + REG_TIMER_RELOAD);

    /*32 bit, periodic*/
    __raw_writel(CFG_TIMER_CTRL, CFG_TIMERBASE + REG_TIMER_CONTROL);

    return 0;
}

int board_eth_init(bd_t *bis)
{
    int rc = 0;

#ifdef CONFIG_NET_HIGMACV300
    extern int higmac_initialize(bd_t * bis);
    rc = higmac_initialize(bis);
#endif
    return rc;
}

extern int hisi_sdhci_add_port(int index, u32 regbase, u32 freq);
extern int hisi_mmc_init(int index);

#ifdef CONFIG_GENERIC_MMC
extern int hisi_sdhci_add_port(int index, u32 regbase, u32 type);
extern int hisi_mmc_init(int dev_num);
#ifdef CONFIG_MMC_PHY
extern int mmc_phy_init(void);
#endif
int board_mmc_init(bd_t *bis)
{
    int ret = 0;
    int dev_num = 0;

#ifdef CONFIG_MMC_PHY
    mmc_phy_init();
#endif

#ifdef CONFIG_EMMC
    ret = hisi_sdhci_add_port(0, EMMC_BASE_REG, MMC_TYPE_MMC);
    if (!ret) {
        ret = hisi_mmc_init(dev_num);
        if (ret) {
            printf("No EMMC device found !\n");
        }
    }
    dev_num++;
#endif

#ifdef CONFIG_AUTO_SD_UPDATE
    if(is_auto_update()) {
        ret = hisi_sdhci_add_port(1, SDIO0_BASE_REG, MMC_TYPE_SD);
        if (ret) {
            return ret;
        }

        ret = hisi_mmc_init(dev_num);
        if (ret) {
            printf("No SD device found !\n");
        }
    }
#endif

    return ret;
}
#endif

#define PMC_REG_BASE     0x180c0000
#define SENSOR_HUB_CRG_0 0x18020000
#define SENSOR_HUB_CRG_1 0x18020004
#define SENSOR_HUB_CRG_2 0x18020008
#define SENSOR_HUB_CRG_3 0x1802000C
#define SENSOR_HUB_CRG_4 0x18020010
#define SENSOR_HUB_CRG_11 0x1802002c

static int start_m7(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    writel(0x5a5aabcd, PMC_REG_BASE + 0x58);
    writel(0x0, 0x180C005c);
    printf("cortex-M7 is running!\n");
    return 0;
}

static int config_m7(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    writel(0x069E36E3, SENSOR_HUB_CRG_2);
    writel(0x00810001, SENSOR_HUB_CRG_1);
    /* wait for pll lock */
    while(!(readl(SENSOR_HUB_CRG_3) & 0x1));
    writel(0x03, SENSOR_HUB_CRG_0);
    writel(0x1110, SENSOR_HUB_CRG_4);
    writel(0x01, SENSOR_HUB_CRG_11);
    printf("cortex-M7 is configed!\n");
    return 0;
}

U_BOOT_CMD(
    go_m7, CONFIG_SYS_MAXARGS, 1,   start_m7,
    "start cortex-M7",
    ""
    ""
);

U_BOOT_CMD(
    config_m7, CONFIG_SYS_MAXARGS, 1,   config_m7,
    "config cortex-M7 by default configs",
    ""
    ""
);

int start_a53up(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned long addr;

    if (argc < 2) {
        return CMD_RET_USAGE;
    }
    addr = simple_strtoul(argv[1], NULL, 16);
    printf ("## Starting A53UP at 0x%016lX ...\n", addr);

    writel(addr >> 2, REG_PERI_CPU_RVBARADDR_A53UP);

    /* start up a53 */
    {
        unsigned int reg;
        unsigned int jump_cmd = 0xea000004;
        unsigned int warm_reset_cmd[] = {
            0xe3a03000, 0xe3413d83, 0xf57ff06f, 0xf57ff04f,
            0xee1c3f50, 0xe3833003, 0xee0c3f50, 0xf57ff06f,
            0xe320f003, 0xeafffffe, 0x0
        };
        volatile uint32_t *p = (volatile uint32_t *)0x18;
        unsigned int *cmd = warm_reset_cmd;

        *((volatile uint32_t *)0) = jump_cmd;
        while (*cmd) {
            *p++ = *cmd++;
        }
        writel((addr >> 2) & 0xffffffff, REG_PERI_CPU_RVBARADDR_A53UP);
        flush_dcache_all();
        reg = readl(CRG_REG_BASE + REG_CRG51);
        reg |= CLUSTER2_GLB_CKEN;
        reg &= ~CLUSTER2_GLB_SRST_REQ;
        writel(reg, CRG_REG_BASE + REG_CRG51);
    }
    return 0;
}

U_BOOT_CMD(
    go_a53up, CONFIG_SYS_MAXARGS, 1,  start_a53up,
    "start a53-up at address 'addr'",
    "addr [arg ...]\n    - start a53 application at address 'addr'\n"
    "      passing 'arg' as arguments"
);

#define HEAD_SIZE   0X10
#define COMPRESSED_SIZE_OFFSET      0X0
#define UNCOMPRESSED_SIZE_OFFSET    0X4

#define HEAD_MAGIC_NUM0 0X70697A67/*'g''z''i''p'*/
#define HEAD_MAGIC_NUM0_OFFSET 0X8
#define HEAD_MAGIC_NUM1 0X64616568/*'h''e''a''d'*/
#define HEAD_MAGIC_NUM1_OFFSET 0XC

extern unsigned int hw_dec_type;
extern void hw_dec_init(void);
extern void hw_dec_uinit(void);

extern int hw_dec_decompress(unsigned int dst_h32, unsigned int dst_l32,
                             int *dstlen,
                             unsigned int src_h32, unsigned int src_l32,
                             int srclen, void *unused);

int do_ugzip(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned long src, dst;
    int size_comparessed, size_uncomparessed;
    unsigned int magic_num0, magic_num1;
    int ret = 0;
    /* need two arguments */
    if (argc != 3) {
        cmd_usage(cmdtp);
        return 0;
    }
    src = simple_strtoul(argv[1], NULL, 16);
    dst = simple_strtoul(argv[2], NULL, 16);

    if(src & 0XF) {
        printf("ERR:\n    src[0X%08lx] is not 16Byte-aligned!\n", src);
        return 0;
    }
    if(dst & 0XF) {
        printf("ERR:\n    dst[0X%08lx] is not 16Byte-aligned!\n", dst);
        return 0;
    }

    magic_num0 = *(unsigned int *)(src + HEAD_MAGIC_NUM0_OFFSET);
    magic_num1 = *(unsigned int *)(src + HEAD_MAGIC_NUM1_OFFSET);
    if((magic_num0 != HEAD_MAGIC_NUM0) || (magic_num1 != HEAD_MAGIC_NUM1)) {
        printf("ERR:\n    The magic numbers are not correct!\n"\
               "    Please check the source data!\n");
        return 0;
    }
    size_comparessed = *(int *)(src + COMPRESSED_SIZE_OFFSET);
    size_uncomparessed = *(int *)(src + UNCOMPRESSED_SIZE_OFFSET);
    /*use direct address mode*/
    hw_dec_type = 0;
    __asm_flush_dcache_all();
    __asm_flush_l3_dcache();
    /*init hw decompress IP*/
    hw_dec_init();

    /*start decompress*/
    ret = hw_dec_decompress((dst >> 32) & 0xffffffff, dst & 0xffffffff, &size_uncomparessed,
                            (src >> 32), (unsigned int)(src + HEAD_SIZE), size_comparessed, NULL);

    if(ret) {
        printf("ERR:\n    decompress fail!\n");
    } else {
        printf("decompress ok!\n");
    }

    /*uinit hw decompress IP*/
    hw_dec_uinit();

    return 0;
}

U_BOOT_CMD(
    ugzip, CONFIG_SYS_MAXARGS, 1,  do_ugzip,
    "Compress gzipfile with hardware IP",
    "ugzip <src> <dst>\n"
    "src and dst must be 16Byte-aligned"
);
