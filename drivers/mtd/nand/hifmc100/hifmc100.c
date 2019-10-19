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
#include <nand.h>
#include <asm/io.h>
#include <errno.h>
#include <malloc.h>
#include <match_table.h>
#include <asm/arch/platform.h>

#include <hifmc_common.h>
#include <hinfc_common.h>
#include "../../hifmc_spi_ids.h"
#include "hifmc100.h"

/*****************************************************************************/
void hifmc100_ecc0_switch(struct hifmc_host *host, unsigned char op)
{
    unsigned int config;
#if EC_DBG
    unsigned int cmp_cfg;

    config = hifmc_read(host, FMC_CFG);
    FMC_PR(EC_DBG, "\t *-Get CFG[%#x]%#x\n", FMC_CFG, config);

    if (op) {
        cmp_cfg = host->fmc_cfg;
    } else {
        cmp_cfg = host->fmc_cfg_ecc0;
    }

    if (cmp_cfg != config)
        DB_MSG("Warning: FMC config[%#x] is different.\n",
               cmp_cfg);
#endif

    if (op == ENABLE) {
        config = host->fmc_cfg_ecc0;
    } else if (op == DISABLE) {
        config = host->fmc_cfg;
    } else {
        DB_MSG("Error: Invalid opcode: %d\n", op);
        return;
    }

    hifmc_write(host, FMC_CFG, config);
    FMC_PR(EC_DBG, "\t *-Set CFG[%#x]%#x\n", FMC_CFG, config);
}

/*****************************************************************************/
static void hifmc100_send_cmd_pageprog(struct hifmc_host *host)
{
    unsigned char pages_per_block_shift;
    unsigned int reg, block_num, block_num_h, page_num;
    struct hifmc_spi *spi = host->spi;
    struct nand_chip *chip = host->chip;
    const char *op = "Dma";
#ifndef CONFIG_SYS_DCACHE_OFF
    unsigned int dma_align_mask = CONFIG_SYS_CACHELINE_SIZE - 1;
    unsigned int dma_align_len;
#endif

    if (WR_DBG) {
        printf("\n");
    }
    FMC_PR(WR_DBG, "*-Enter %s page program!\n", op);

    if (hifmc_ip_user) {
        printf("Warning: Hifmc IP is busy, Please try again.\n");
        udelay(1);
        return;
    } else {
        hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
        hifmc_ip_user++;
    }

    reg = spi->driver->write_enable(spi);
    if (reg) {
        DB_MSG("Error: %s program write enable failed! reg: %#x\n",
               op, reg);
        goto end;
    }

    host->set_system_clock(spi->write, ENABLE);

    if (ecc0_flag == 1) {
        hifmc100_ecc0_switch(host, ENABLE);
        hifmc_write(host, FMC_DMA_LEN, oobsize_real);
    }

    reg = FMC_INT_CLR_ALL;
    hifmc_write(host, FMC_INT_CLR, reg);
    FMC_PR(WR_DBG, "|-Set INT_CLR[%#x]%#x\n", FMC_INT_CLR, reg);

    reg = OP_CFG_FM_CS(host->cmd_op.cs)
          | OP_CFG_OEN_EN
          | OP_CFG_MEM_IF_TYPE(spi->write->iftype);
    hifmc_write(host, FMC_OP_CFG, reg);
    FMC_PR(WR_DBG, "|-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

    pages_per_block_shift = chip->phys_erase_shift - chip->page_shift;
    block_num = host->addr_value[1] >> pages_per_block_shift;
    block_num_h = block_num >> REG_CNT_HIGH_BLOCK_NUM_SHIFT;
    reg = FMC_ADDRH_SET(block_num_h);
    hifmc_write(host, FMC_ADDRH, reg);
    FMC_PR(WR_DBG, "|-Set ADDRH[%#x]%#x\n", FMC_ADDRH, reg);

    page_num = host->addr_value[1] - (block_num << pages_per_block_shift);
    reg = ((block_num & REG_CNT_BLOCK_NUM_MASK) << REG_CNT_BLOCK_NUM_SHIFT)
          | ((page_num & REG_CNT_PAGE_NUM_MASK) << REG_CNT_PAGE_NUM_SHIFT);
    hifmc_write(host, FMC_ADDRL, reg);
    FMC_PR(WR_DBG, "|-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

    if (ecc0_flag != 1) {
        *host->epm = 0x0000;
    }

#ifndef CONFIG_SYS_DCACHE_OFF
    dma_align_len = ((host->pagesize + host->oobsize + dma_align_mask)
                     & ~dma_align_mask);
    flush_dcache_range(host->dma_buffer, host->dma_buffer + dma_align_len);
#endif

    reg = host->dma_buffer;
    hifmc_write(host, FMC_DMA_SADDR_D0, reg);
    FMC_PR(WR_DBG, "|-Set DMA_SADDR_D[0x40]%#x\n", reg);
    reg = (host->dma_buffer & FMC_DMA_SADDRH_MASK) >> 32;
    hifmc_write(host, FMC_DMA_SADDRH_D0, reg);
    FMC_PR(WR_DBG, "\t|-Set DMA_SADDRH_D0[%#x]%#x\n", FMC_DMA_SADDRH_D0, reg);

    reg = host->dma_oob;
    hifmc_write(host, FMC_DMA_SADDR_OOB, reg);
    FMC_PR(WR_DBG, "|-Set DMA_SADDR_OOB[%#x]%#x\n", FMC_DMA_SADDR_OOB, reg);
    reg = (host->dma_oob & FMC_DMA_SADDRH_MASK) >> 32;
    hifmc_write(host, FMC_DMA_SADDRH_OOB, reg);
    FMC_PR(WR_DBG, "\t|-Set DMA_SADDRH_OOB[%#x]%#x\n", FMC_DMA_SADDRH_OOB,
           reg);

    reg = OP_CTRL_WR_OPCODE(spi->write->cmd)
          | OP_CTRL_DMA_OP(OP_TYPE_DMA)
          | OP_CTRL_RW_OP(RW_OP_WRITE)
          | OP_CTRL_DMA_OP_READY;
    hifmc_write(host, FMC_OP_CTRL, reg);
    FMC_PR(WR_DBG, "|-Set OP_CTRL[%#x]%#x\n", FMC_OP_CTRL, reg);

    FMC_DMA_WAIT_INT_FINISH(host);

    if (ecc0_flag == 1) {
        hifmc100_ecc0_switch(host, DISABLE);
    }

    reg = spi->driver->wait_ready(spi);
    if (reg) {
        DB_MSG("Error: %s program wait ready failed! status: %#x\n",
               op, reg);
	}

end:
    hifmc_ip_user--;

    FMC_PR(WR_DBG, "*-End %s page program!\n", op);
}

/*****************************************************************************/
static void hifmc100_send_cmd_readstart(struct hifmc_host *host)
{
    unsigned char pages_per_block_shift;
    unsigned char only_oob = 0;
    unsigned short wrap = 0;
    unsigned int reg, block_num, block_num_h, page_num;
	unsigned int addr_of = 0;
    struct hifmc_spi *spi = host->spi;
    struct nand_chip *chip = host->chip;
    char *op = "Dma";
#ifndef CONFIG_SYS_DCACHE_OFF
    unsigned int dma_align_mask = CONFIG_SYS_CACHELINE_SIZE - 1;
    unsigned int dma_align_len;
#endif

    if (RD_DBG) {
        printf("\n");
    }
    FMC_PR(RD_DBG, "\t*-Start %s page read\n", op);

    if (hifmc_ip_user) {
        printf("Warning: Hifmc IP is busy, Please try again.\n");
        udelay(1);
        return;
    } else {
        hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
        hifmc_ip_user++;
    }

    host->set_system_clock(spi->read, ENABLE);

    if (ecc0_flag == 1 && (host->cmd_op.l_cmd != NAND_CMD_READOOB)) {
        hifmc100_ecc0_switch(host, ENABLE);
        hifmc_write(host, FMC_DMA_LEN, oobsize_real);
    }

    reg = FMC_INT_CLR_ALL;
    hifmc_write(host, FMC_INT_CLR, reg);
    FMC_PR(RD_DBG, "\t|-Set INT_CLR[%#x]%#x\n", FMC_INT_CLR, reg);

    if (host->cmd_op.l_cmd == NAND_CMD_READOOB) {
        only_oob = 1;
        host->cmd_op.op_cfg = OP_CTRL_RD_OP_SEL(RD_OP_READ_OOB);
    } else {
        host->cmd_op.op_cfg = OP_CTRL_RD_OP_SEL(RD_OP_READ_ALL_PAGE);
    }

    reg = OP_CFG_FM_CS(host->cmd_op.cs)
          | OP_CFG_OEN_EN
          | OP_CFG_MEM_IF_TYPE(spi->read->iftype)
          | OP_CFG_DUMMY_NUM(spi->read->dummy);
    hifmc_write(host, FMC_OP_CFG, reg);
    FMC_PR(RD_DBG, "\t|-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

    pages_per_block_shift = chip->phys_erase_shift - chip->page_shift;
    block_num = host->addr_value[1] >> pages_per_block_shift;
    block_num_h = block_num >> REG_CNT_HIGH_BLOCK_NUM_SHIFT;

    reg = FMC_ADDRH_SET(block_num_h);
    hifmc_write(host, FMC_ADDRH, reg);
    FMC_PR(RD_DBG, "\t|-Set ADDRH[%#x]%#x\n", FMC_ADDRH, reg);

    page_num = host->addr_value[1] - (block_num << pages_per_block_shift);
    if (only_oob)
        switch (host->ecctype) {
            case NAND_ECC_8BIT:
                addr_of = REG_CNT_ECC_8BIT_OFFSET;
                break;
            case NAND_ECC_16BIT:
                addr_of = REG_CNT_ECC_16BIT_OFFSET;
                break;
            case NAND_ECC_24BIT:
                addr_of = REG_CNT_ECC_24BIT_OFFSET;
                break;
            case NAND_ECC_0BIT:
            default:
                break;
        }

    reg = ((block_num & REG_CNT_BLOCK_NUM_MASK) << REG_CNT_BLOCK_NUM_SHIFT)
          | ((page_num & REG_CNT_PAGE_NUM_MASK) << REG_CNT_PAGE_NUM_SHIFT)
          | ((wrap & REG_CNT_WRAP_MASK) << REG_CNT_WRAP_SHIFT)
          | (addr_of & REG_CNT_ECC_OFFSET_MASK);
    hifmc_write(host, FMC_ADDRL, reg);
    FMC_PR(RD_DBG, "\t|-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

#ifndef CONFIG_SYS_DCACHE_OFF
    dma_align_len = ((host->pagesize + host->oobsize + dma_align_mask)
                     & ~dma_align_mask);
    invalidate_dcache_range(host->dma_buffer, host->dma_buffer + dma_align_len);
#endif

    reg = host->dma_buffer;
    hifmc_write(host, FMC_DMA_SADDR_D0, reg);
    FMC_PR(RD_DBG, "\t|-Set DMA_SADDR_D0[%#x]%#x\n", FMC_DMA_SADDR_D0, reg);

    reg = (host->dma_buffer & FMC_DMA_SADDRH_MASK) >> 32;
    hifmc_write(host, FMC_DMA_SADDRH_D0, reg);
    FMC_PR(RD_DBG, "\t|-Set DMA_SADDRH_D0[%#x]%#x\n", FMC_DMA_SADDRH_D0, reg);

    reg = host->dma_oob;
    hifmc_write(host, FMC_DMA_SADDR_OOB, reg);
    FMC_PR(RD_DBG, "\t|-Set DMA_SADDR_OOB[%#x]%#x\n", FMC_DMA_SADDR_OOB,
           reg);
    reg = (host->dma_oob & FMC_DMA_SADDRH_MASK) >> 32;
    hifmc_write(host, FMC_DMA_SADDRH_OOB, reg);
    FMC_PR(RD_DBG, "\t|-Set DMA_SADDRH_OOB[%#x]%#x\n", FMC_DMA_SADDRH_OOB,
           reg);

    reg = OP_CTRL_RD_OPCODE(spi->read->cmd) | host->cmd_op.op_cfg
          | OP_CTRL_DMA_OP(OP_TYPE_DMA)
          | OP_CTRL_RW_OP(RW_OP_READ) | OP_CTRL_DMA_OP_READY;
    hifmc_write(host, FMC_OP_CTRL, reg);
    FMC_PR(RD_DBG, "\t|-Set OP_CTRL[%#x]%#x\n", FMC_OP_CTRL, reg);

    FMC_DMA_WAIT_INT_FINISH(host);

    if (ecc0_flag == 1 && (host->cmd_op.l_cmd != NAND_CMD_READOOB)) {
        hifmc100_ecc0_switch(host, DISABLE);
    }

#ifndef CONFIG_SYS_DCACHE_OFF
    invalidate_dcache_range(host->dma_buffer, host->dma_buffer + dma_align_len);
#endif

    hifmc_ip_user--;

    FMC_PR(RD_DBG, "\t*-End %s page read\n", op);
}

/*****************************************************************************/
static void hifmc100_send_cmd_erase(struct hifmc_host *host)
{
    unsigned int reg;
    struct hifmc_spi *spi = host->spi;

    if (ER_DBG) {
        printf("\n");
    }
    FMC_PR(ER_DBG, "\t*-Start send cmd erase!\n");

    if (hifmc_ip_user) {
        printf("Warning: Hifmc IP is busy, Please try again.\n");
        udelay(1);
        return;
    } else {
        hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
        hifmc_ip_user++;
    }

    reg = spi->driver->write_enable(spi);
    if (reg) {
        DB_MSG("Error: Erase write enable failed! reg: %#x\n", reg);
        goto end;
    }

    host->set_system_clock(spi->erase, ENABLE);

    reg = FMC_INT_CLR_ALL;
    hifmc_write(host, FMC_INT_CLR, reg);
    FMC_PR(ER_DBG, "\t|-Set INT_CLR[%#x]%#x\n", FMC_INT_CLR, reg);

    reg = spi->erase->cmd;
    hifmc_write(host, FMC_CMD, FMC_CMD_CMD1(reg));
    FMC_PR(ER_DBG, "\t|-Set CMD[%#x]%#x\n", FMC_CMD, reg);

    reg = FMC_ADDRL_BLOCK_H_MASK(host->addr_value[1])
          | FMC_ADDRL_BLOCK_L_MASK(host->addr_value[0]);
    hifmc_write(host, FMC_ADDRL, reg);
    FMC_PR(ER_DBG, "\t|-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

    reg = OP_CFG_FM_CS(host->cmd_op.cs)
          | OP_CFG_OEN_EN
          | OP_CFG_MEM_IF_TYPE(spi->erase->iftype)
          | OP_CFG_ADDR_NUM(STD_OP_ADDR_NUM)
          | OP_CFG_DUMMY_NUM(spi->erase->dummy);
    hifmc_write(host, FMC_OP_CFG, reg);
    FMC_PR(ER_DBG, "\t|-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

    reg = FMC_OP_CMD1_EN(ENABLE)
          | FMC_OP_ADDR_EN(ENABLE)
          | FMC_OP_REG_OP_START;
    hifmc_write(host, FMC_OP, reg);
    FMC_PR(ER_DBG, "\t|-Set OP[%#x]%#x\n", FMC_OP, reg);

    FMC_CMD_WAIT_CPU_FINISH(host);

    reg = spi->driver->wait_ready(spi);
    FMC_PR(ER_DBG, "\t|-Erase wait ready, reg: %#x\n", reg);
    if (reg) {
        DB_MSG("Error: Erase wait ready fail! status: %#x\n", reg);
    }

end:
    hifmc_ip_user--;

    FMC_PR(ER_DBG, "\t*-End send cmd erase!\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_status(struct hifmc_host *host)
{
    unsigned char status;
	unsigned char addr = STATUS_ADDR;
    struct hifmc_spi *spi = host->spi;

    if (hifmc_ip_user) {
        printf("Warning: Hifmc IP is busy, Please try again.\n");
        udelay(1);
        return;
    } else {
        hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
        hifmc_ip_user++;
    }

    if (host->cmd_op.l_cmd == NAND_CMD_GET_FEATURES) {
        addr = PROTECT_ADDR;
    }

    status = spi_nand_feature_op(spi, GET_OP, addr, 0);
    FMC_PR((ER_DBG || WR_DBG), "\t*-Get status[%#x]: %#x\n", addr, status);

    hifmc_ip_user--;
}

/*****************************************************************************/
static void hifmc100_send_cmd_readid(struct hifmc_host *host)
{
    unsigned int reg;

    FMC_PR(BT_DBG, "\t|*-Start send cmd read ID\n");

    hifmc100_ecc0_switch(host, ENABLE);

    reg = FMC_CMD_CMD1(SPI_CMD_RDID);
    hifmc_write(host, FMC_CMD, reg);
    FMC_PR(BT_DBG, "\t||-Set CMD[%#x]%#x\n", FMC_CMD, reg);

    reg = READ_ID_ADDR;
    hifmc_write(host, FMC_ADDRL, reg);
    FMC_PR(BT_DBG, "\t||-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

    reg = OP_CFG_FM_CS(host->cmd_op.cs)
          | OP_CFG_OEN_EN
          | OP_CFG_ADDR_NUM(READ_ID_ADDR_NUM);
    hifmc_write(host, FMC_OP_CFG, reg);
    FMC_PR(BT_DBG, "\t||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

    reg = FMC_DATA_NUM_CNT(MAX_SPI_NAND_ID_LEN);
    hifmc_write(host, FMC_DATA_NUM, reg);
    FMC_PR(BT_DBG, "\t||-Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, reg);

    reg = FMC_OP_CMD1_EN(ENABLE)
          | FMC_OP_ADDR_EN(ENABLE)
          | FMC_OP_READ_DATA_EN(ENABLE)
          | FMC_OP_REG_OP_START;
    hifmc_write(host, FMC_OP, reg);
    FMC_PR(BT_DBG, "\t||-Set OP[%#x]%#x\n", FMC_OP, reg);

    host->addr_cycle = 0x0;

    FMC_CMD_WAIT_CPU_FINISH(host);

    hifmc100_ecc0_switch(host, DISABLE);

    FMC_PR(BT_DBG, "\t|*-End read flash ID\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_reset(struct hifmc_host *host)
{
    unsigned int reg;

    FMC_PR(BT_DBG, "\t|*-Start send cmd reset\n");

    reg = FMC_CMD_CMD1(SPI_CMD_RESET);
    hifmc_write(host, FMC_CMD, reg);
    FMC_PR(BT_DBG, "\t||-Set CMD[%#x]%#x\n", FMC_CMD, reg);

    reg = OP_CFG_FM_CS(host->cmd_op.cs) | OP_CFG_OEN_EN;
    hifmc_write(host, FMC_OP_CFG, reg);
    FMC_PR(BT_DBG, "\t||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

    reg = FMC_OP_CMD1_EN(ENABLE) | FMC_OP_REG_OP_START;
    hifmc_write(host, FMC_OP, reg);
    FMC_PR(BT_DBG, "\t||-Set OP[%#x]%#x\n", FMC_OP, reg);

    FMC_CMD_WAIT_CPU_FINISH(host);

    FMC_PR(BT_DBG, "\t|*-End send cmd reset\n");
}

/*****************************************************************************/
static unsigned char hifmc100_read_byte(struct mtd_info *mtd)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;
    unsigned char value; 
	unsigned char ret_val = 0;

    if (host->cmd_op.l_cmd == NAND_CMD_READID) {
        value = readb(host->iobase + host->offset);
        host->offset++;
        if (host->cmd_op.data_no == host->offset) {
            host->cmd_op.l_cmd = 0;
        }
        return value;
    }

    if (host->cmd_op.cmd == NAND_CMD_STATUS) {
        value = hifmc_read(host, FMC_STATUS);
        if (host->cmd_op.l_cmd == NAND_CMD_GET_FEATURES) {
            FMC_PR((ER_DBG || WR_DBG), "\t\tRead BP status: %#x\n",
                   value);
            if (ANY_BP_ENABLE(value)) {
                ret_val |= NAND_STATUS_WP;
            }

            host->cmd_op.l_cmd = NAND_CMD_STATUS;
        }

        if (!(value & STATUS_OIP_MASK)) {
            ret_val |= NAND_STATUS_READY;
        }

        if ((chip->state == FL_ERASING)
                && (value & STATUS_E_FAIL_MASK)) {
            FMC_PR(ER_DBG, "\t\tGet erase status: %#x\n", value);
            ret_val |= NAND_STATUS_FAIL;
        }

        if ((chip->state == FL_WRITING)
                && (value & STATUS_P_FAIL_MASK)) {
            FMC_PR(WR_DBG, "\t\tGet write status: %#x\n", value);
            ret_val |= NAND_STATUS_FAIL;
        }

        return ret_val;
    }

    if (host->cmd_op.l_cmd == NAND_CMD_READOOB) {
        value = readb((unsigned char *)((unsigned char *)host->dma_oob + host->offset));
        host->offset++;
        return value;
    }

    host->offset++;

    return readb(host->buffer + host->column + host->offset - 1);
}

/*****************************************************************************/
static unsigned short hifmc100_read_word(struct mtd_info *mtd)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;

    host->offset += 2;
    return readw(host->buffer + host->column + host->offset - 2);
}

/*****************************************************************************/
static void hifmc100_write_buf(struct mtd_info *mtd,
                               const u_char *buf, int len)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;

    if (buf == chip->oob_poi) {
        memcpy((unsigned char *)host->dma_oob, buf, len);
    } else {
        memset((unsigned char *)(host->dma_buffer + host->pagesize), 0xff, host->oobsize);
        memcpy((unsigned char *)host->dma_buffer, buf, len);
    }
    return;
}

/*****************************************************************************/
static void hifmc100_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;

    if (buf == chip->oob_poi) {
        memcpy(buf, (unsigned char *)host->dma_oob, len);
    } else {
        memcpy(buf, (unsigned char *)host->dma_buffer, len);
    }
    return;
}

/*****************************************************************************/
static void hifmc100_select_chip(struct mtd_info *mtd, int chipselect)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;

    if (chipselect < 0) {
        return;
    }

    if (chipselect > CONFIG_SPI_NAND_MAX_CHIP_NUM) {
        DB_BUG("Error: Invalid chipselect: %d\n", chipselect);
    }

    if (host->mtd != mtd) {
        host->mtd = mtd;
    }

    if (!(chip->options & NAND_BROKEN_XD)) {
        if ((chip->state == FL_ERASING) || (chip->state == FL_WRITING)) {
            host->cmd_op.l_cmd = NAND_CMD_GET_FEATURES;
        }
    }
}

/******************************************************************************/
static void hifmc100_cmdfunc(struct mtd_info *mtd, unsigned int command,
                             int column, int page_addr)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;

    switch (command) {
        case NAND_CMD_RESET:
            host->send_cmd_reset(host);
            chip->dev_ready(mtd);
            break;
        case NAND_CMD_READID:
            host->offset = 0;
            host->cmd_op.l_cmd = command & 0xff;
            memset((u_char *)(host->iobase), 0,
                   MAX_SPI_NAND_ID_LEN);
            host->cmd_op.data_no = MAX_SPI_NAND_ID_LEN;
            host->send_cmd_readid(host);
            break;
        case NAND_CMD_GET_FEATURES:
        case NAND_CMD_STATUS:
            host->cmd_op.l_cmd = command & 0xff;
            host->cmd_op.cmd = NAND_CMD_STATUS;
            host->send_cmd_status(host);
            break;
        case NAND_CMD_READOOB:
            host->offset = 0;
            host->cmd_op.l_cmd = command & 0xff;
            host->cmd_op.cmd = command & 0xff;
        case NAND_CMD_READ0:
            if (command == NAND_CMD_READ0) {
                host->cmd_op.l_cmd = command & 0xff;
            }
            host->addr_value[1] = page_addr;
            host->send_cmd_readstart(host);
            break;
        case NAND_CMD_SEQIN:
            host->addr_value[1] = page_addr;
            break;
        case NAND_CMD_PAGEPROG:
            host->offset = 0;
            host->send_cmd_pageprog(host);
            break;
        case NAND_CMD_ERASE1:
            host->cmd_op.l_cmd = command & 0xff;
            host->addr_value[0] = page_addr;
            host->addr_value[1] = page_addr >> 16;
            host->send_cmd_erase(host);
            break;
        case NAND_CMD_ERASE2:
        case NAND_CMD_READSTART:
            break;
        default:
            printf("%s not support command 0x%08x:\n", mtd->name, command);
            break;
    }
}

/*****************************************************************************/
static int hifmc100_dev_ready(struct mtd_info *mtd)
{
    unsigned int reg;
    unsigned long deadline = 1 << 12;
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;

    do {
        reg = OP_CFG_FM_CS(host->cmd_op.cs) | OP_CFG_OEN_EN;
        hifmc_write(host, FMC_OP_CFG, reg);

        reg = FMC_OP_READ_STATUS_EN(ENABLE) | FMC_OP_REG_OP_START;
        hifmc_write(host, FMC_OP, reg);

        FMC_CMD_WAIT_CPU_FINISH(host);

        reg = hifmc_read(host, FMC_STATUS);
        if (!(reg & STATUS_OIP_MASK)) {
            return 1;
        }

        udelay(1);

    } while (deadline--);

#ifndef CONFIG_SYS_NAND_QUIET_TEST
    printf("Warning: Wait SPI nand ready timeout, status: %#x\n", reg);
#endif

    return 0;
}

/*****************************************************************************/
/*
 * 'host->epm' only use the first oobfree[0] field, it looks very simple, But...
 */
static struct nand_ecclayout nand_ecc_default = {
    .oobfree = {{2, 30} }
};

#ifdef CONFIG_FS_MAY_NOT_YAFFS2
static struct nand_ecclayout nand_ecc_2k16bit = {
    .oobfree = {{2, 6} }
};

static struct nand_ecclayout nand_ecc_4k16bit = {
    .oobfree = {{2, 14} }
};
#endif

/*****************************************************************************/
static struct nand_config_info hifmc_spi_nand_config_table[] = {
    {NAND_PAGE_4K,  NAND_ECC_24BIT, 200,    &nand_ecc_default},
#ifdef CONFIG_FS_MAY_NOT_YAFFS2
    {NAND_PAGE_4K,  NAND_ECC_16BIT, 128,    &nand_ecc_4k16bit},
#endif
    {NAND_PAGE_4K,  NAND_ECC_8BIT,  128,    &nand_ecc_default},
    {NAND_PAGE_4K,  NAND_ECC_0BIT,  32,     &nand_ecc_default},

    {NAND_PAGE_2K,  NAND_ECC_24BIT, 128,    &nand_ecc_default},
#ifdef CONFIG_FS_MAY_NOT_YAFFS2
    {NAND_PAGE_2K,  NAND_ECC_16BIT, 64,     &nand_ecc_2k16bit},
#endif
    {NAND_PAGE_2K,  NAND_ECC_8BIT,  64,     &nand_ecc_default},
    {NAND_PAGE_2K,  NAND_ECC_0BIT,  32,     &nand_ecc_default},

    {0,     0,      0,  NULL},
};

/*
 * Auto-sensed the page size and ecc type value. driver will try each of page
 * size and ecc type one by one till flash can be read and wrote accurately.
 * so the page size and ecc type is match adaptively without switch on the board
 */
static struct nand_config_info *hifmc100_get_config_type_info(struct mtd_info *mtd)
{
    struct nand_config_info *best = NULL;
    struct nand_config_info *info = hifmc_spi_nand_config_table;
    struct nand_chip *chip = mtd_to_nand(mtd);
    for (; info->layout; info++) {
        if (match_page_type_to_size(info->pagetype) != mtd->writesize) {
            continue;
        }

        if (mtd->oobsize < info->oobsize) {
            continue;
        }

        if (!best || (best->ecctype < info->ecctype)) {
            best = info;
        }
    }
    /* All SPI NAND are small-page,SLC */
    chip->bits_per_cell = 1;
    return best;
}

/*****************************************************************************/
static void hifmc100_set_oob_info(struct mtd_info *mtd,
                                  struct nand_config_info *info)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;

    /* oobsize_real for ecc0 read and write */
    oobsize_real = mtd->oobsize;

    if (info->ecctype != NAND_ECC_0BIT) {
        mtd->oobsize = info->oobsize;
    }

    host->oobsize = mtd->oobsize;
    host->dma_oob = host->dma_buffer + host->pagesize;
    host->bbm = (u_char *)(host->buffer + host->pagesize
                           + HIFMC_BAD_BLOCK_POS);

    chip->ecc.layout = info->layout;

    /* EB bits locate in the bottom two of CTRL(30) */
    host->epm = (u_short *)(host->buffer + host->pagesize
                            + chip->ecc.layout->oobfree[0].offset + 28);

#ifdef CONFIG_FS_MAY_NOT_YAFFS2
    if (best->ecctype == NAND_ECC_16BIT) {
        if (host->pagesize == _2K) {
            /* EB bits locate in the bottom two of CTRL(4) */
            host->epm = (u_short *)(host->buffer + host->pagesize
                                    + chip->ecc.layout->oobfree[0].offset + 4);
        } else if (host->pagesize == _4K) {
            /* EB bit locate in the bottom two of CTRL(14) */
            host->epm = (u_short *)(host->buffer + host->pagesize
                                    + chip->ecc.layout->oobfree[0].offset + 12);
        }
    }
#endif
}

/*****************************************************************************/
static unsigned int hifmc100_get_ecc_reg(struct hifmc_host *host,
                                         struct nand_config_info *info)
{
    host->ecctype = info->ecctype;

    return FMC_CFG_ECC_TYPE(match_ecc_type_to_reg(info->ecctype));
}

/*****************************************************************************/
static unsigned int hifmc100_get_page_reg(struct hifmc_host *host,
                                          struct nand_config_info *info)
{
    host->pagesize = match_page_type_to_size(info->pagetype);

    return FMC_CFG_PAGE_SIZE(match_page_type_to_reg(info->pagetype));
}

/*****************************************************************************/
static unsigned int hifmc100_get_block_reg(struct hifmc_host *host,
                                           struct nand_config_info *info)
{
    unsigned int block_reg = 0;
	unsigned int page_per_block;
    struct mtd_info *mtd = host->mtd;

    host->block_page_mask = ((mtd->erasesize / mtd->writesize) - 1);
    page_per_block = mtd->erasesize / match_page_type_to_size(info->pagetype);
    switch (page_per_block) {
        case 64:
            block_reg = BLOCK_SIZE_64_PAGE;
            break;
        case 128:
            block_reg = BLOCK_SIZE_128_PAGE;
            break;
        case 256:
            block_reg = BLOCK_SIZE_256_PAGE;
            break;
        case 512:
            block_reg = BLOCK_SIZE_512_PAGE;
            break;
        default:
            DB_MSG("Can't support block %#x and page %#x size\n",
                   mtd->erasesize, mtd->writesize);
    }

    return FMC_CFG_BLOCK_SIZE(block_reg);
}

/*****************************************************************************/
static void hifmc100_set_fmc_cfg_reg(struct mtd_info *mtd,
                                     struct nand_config_info *type_info)
{
    struct nand_chip *chip = mtd_to_nand(mtd);
    struct hifmc_host *host = chip->priv;
    unsigned int page_reg, ecc_reg, block_reg, reg_fmc_cfg;

    ecc_reg = hifmc100_get_ecc_reg(host, type_info);
    page_reg = hifmc100_get_page_reg(host, type_info);
    block_reg = hifmc100_get_block_reg(host, type_info);

    reg_fmc_cfg = hifmc_read(host, FMC_CFG);
    reg_fmc_cfg &= ~(PAGE_SIZE_MASK | ECC_TYPE_MASK | BLOCK_SIZE_MASK);
    reg_fmc_cfg |= ecc_reg | page_reg | block_reg;
    hifmc_write(host, FMC_CFG, reg_fmc_cfg);

    /* max number of correctible bit errors per ecc step */
    mtd->ecc_strength = host->ecctype;

    /* Save value of FMC_CFG and FMC_CFG_ECC0 to turn on/off ECC */
    host->fmc_cfg = reg_fmc_cfg;
    host->fmc_cfg_ecc0 = (host->fmc_cfg & ~ECC_TYPE_MASK) | ECC_TYPE_0BIT;
    FMC_PR(BT_DBG, "\t|-Save FMC_CFG[%#x]: %#x and FMC_CFG_ECC0: %#x\n",
           FMC_CFG, host->fmc_cfg, host->fmc_cfg_ecc0);
}

/*****************************************************************************/
static int hifmc100_set_config_info(struct mtd_info *mtd)
{
    struct nand_config_info *type_info = NULL;

    FMC_PR(BT_DBG, "\t*-Start match PageSize and EccType\n");

    type_info = hifmc100_get_config_type_info(mtd);
    if (!type_info)
        DB_BUG(ERR_STR_DRIVER "pagesize: %d and oobsize: %d.\n",
               mtd->writesize, mtd->oobsize);

    /* Set the page_size, ecc_type, block_size of FMC_CFG[0x0] register */
    hifmc100_set_fmc_cfg_reg(mtd, type_info);

    FMC_PR(BT_DBG, "\t|- PageSize %s EccType %s OOB Size %d\n",
           nand_page_name(type_info->pagetype),
           nand_ecc_name(type_info->ecctype), type_info->oobsize);

    hifmc100_set_oob_info(mtd, type_info);

    FMC_PR(BT_DBG, "\t*-End match PageSize and EccType\n");

    return 0;
}

/*****************************************************************************/
static void hifmc100_chip_init(struct nand_chip *chip)
{
    if (!chip->IO_ADDR_R) {
        chip->IO_ADDR_R = (void __iomem *)CONFIG_HIFMC_BUFFER_BASE;
    }
    chip->IO_ADDR_W = chip->IO_ADDR_R;
    memset((char *)chip->IO_ADDR_R, 0xff, HIFMC100_BUFFER_LEN);

    chip->read_byte = hifmc100_read_byte;
    chip->read_word = hifmc100_read_word;
    chip->write_buf = hifmc100_write_buf;
    chip->read_buf = hifmc100_read_buf;

    chip->select_chip = hifmc100_select_chip;

    chip->cmdfunc = hifmc100_cmdfunc;
    chip->dev_ready = hifmc100_dev_ready;

    chip->chip_delay = FMC_CHIP_DELAY;

    chip->options = NAND_BBT_SCANNED | NAND_BROKEN_XD;

    chip->ecc.layout = NULL;
    chip->ecc.mode = NAND_ECC_NONE;
}

/*****************************************************************************/
int hifmc100_host_init(struct hifmc_host *host)
{
    unsigned int reg, flash_type;
    long align_mask;

    FMC_PR(BT_DBG, "\t||*-Start SPI Nand host init\n");

    host->iobase = (void __iomem *)CONFIG_HIFMC_BUFFER_BASE;
    host->regbase = (void __iomem *)CONFIG_HIFMC_REG_BASE;

    reg = hifmc_read(host, FMC_CFG);
    flash_type = (reg & FLASH_SEL_MASK) >> FLASH_SEL_SHIFT;
    if (flash_type != FLASH_TYPE_SPI_NAND) {
        DB_MSG("Error: Flash type isn't SPI Nand. reg: %#x\n", reg);
        return -ENODEV;
    }

    if ((reg & OP_MODE_MASK) == OP_MODE_BOOT) {
        reg |= FMC_CFG_OP_MODE(OP_MODE_NORMAL);
        hifmc_write(host, FMC_CFG, reg);
        FMC_PR(BT_DBG, "\t|||-Set CFG[%#x]%#x\n", FMC_CFG, reg);
    }

    host->fmc_cfg = reg;
    host->fmc_cfg_ecc0 = (reg & ~ECC_TYPE_MASK) | ECC_TYPE_0BIT;

    reg = hifmc_read(host, FMC_GLOBAL_CFG);
    if (reg & FMC_GLOBAL_CFG_WP_ENABLE) {
        reg &= ~FMC_GLOBAL_CFG_WP_ENABLE;
        hifmc_write(host, FMC_GLOBAL_CFG, reg);
    }

    host->addr_cycle = 0;
    host->addr_value[0] = 0;
    host->addr_value[1] = 0;
    host->cache_addr_value[0] = ~0;
    host->cache_addr_value[1] = ~0;

    /* ecc0_flag for ecc0 read/write */
    ecc0_flag = 0;

    FMC_PR(BT_DBG, "\t|||-Malloc memory for dma buffer\n");
    host->buforg = kmalloc((HIFMC100_BUFFER_LEN + FMC_DMA_ALIGN),
                           GFP_KERNEL);
    if (!host->buforg) {
        DB_MSG("Error: Can't malloc memory for SPI Nand driver.\n");
        return -ENOMEM;
    }

    /* DMA need 32 bytes alignment */
    align_mask = FMC_DMA_ALIGN - 1;
    host->dma_buffer = (long)(host->buforg + align_mask) & ~align_mask;

    host->buffer = (char *)host->dma_buffer;
    memset(host->buffer, 0xff, HIFMC100_BUFFER_LEN);

    host->send_cmd_pageprog = hifmc100_send_cmd_pageprog;
    host->send_cmd_status = hifmc100_send_cmd_status;
    host->send_cmd_readstart = hifmc100_send_cmd_readstart;
    host->send_cmd_erase = hifmc100_send_cmd_erase;
    host->send_cmd_readid = hifmc100_send_cmd_readid;
    host->send_cmd_reset = hifmc100_send_cmd_reset;
    host->set_system_clock = hifmc_set_fmc_system_clock;

    reg = TIMING_CFG_TCSH(CS_HOLD_TIME)
          | TIMING_CFG_TCSS(CS_SETUP_TIME)
          | TIMING_CFG_TSHSL(CS_DESELECT_TIME);
    hifmc_write(host, FMC_SPI_TIMING_CFG, reg);
    FMC_PR(BT_DBG, "\t|||-Set TIMING[%#x]%#x\n", FMC_SPI_TIMING_CFG, reg);

    reg = ALL_BURST_ENABLE;
    hifmc_write(host, FMC_DMA_AHB_CTRL, reg);
    FMC_PR(BT_DBG, "\t|||-Set DMA_AHB[%#x]%#x\n", FMC_DMA_AHB_CTRL, reg);

    FMC_PR(BT_DBG, "\t|||-Register SPI Nand ID table and ecc probe\n");
    hifmc_spi_nand_ids_register();
    nand_oob_resize = hifmc100_set_config_info;

    FMC_PR(BT_DBG, "\t||*-End SPI Nand host init\n");

    return 0;
}

/*****************************************************************************/
void hifmc100_spi_nand_init(struct hifmc_host *host)
{
    struct nand_chip *chip = host->chip;

    FMC_PR(BT_DBG, "\t|*-Start hifmc100 SPI Nand init\n");

    /* Set system clock and enable controller */
    FMC_PR(BT_DBG, "\t||-Set system clock and Enable Controller\n");
    if (host->set_system_clock) {
        host->set_system_clock(NULL, ENABLE);
    }

    /* Hifmc nand_chip struct init */
    FMC_PR(BT_DBG, "\t||-Hifmc100 struct nand_chip init\n");
    chip->priv = host;
    hifmc100_chip_init(chip);

    FMC_PR(BT_DBG, "\t|*-End hifmc100 SPI Nand init\n");
}

