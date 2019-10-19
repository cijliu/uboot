#
# (C) Copyright 2000-2007
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

ifneq (,$(findstring y,$(CONFIG_MTD_DEVICE)$(CONFIG_CMD_NAND)$(CONFIG_CMD_ONENAND)$(CONFIG_CMD_SF)))
obj-y += mtdcore.o mtd_uboot.o
endif
obj-$(CONFIG_MTD) += mtd-uclass.o
obj-$(CONFIG_MTD_PARTITIONS) += mtdpart.o
obj-$(CONFIG_MTD_CONCAT) += mtdconcat.o
obj-$(CONFIG_ALTERA_QSPI) += altera_qspi.o
obj-$(CONFIG_HAS_DATAFLASH) += at45.o
obj-$(CONFIG_FLASH_CFI_DRIVER) += cfi_flash.o
obj-$(CONFIG_FLASH_CFI_MTD) += cfi_mtd.o
obj-$(CONFIG_HAS_DATAFLASH) += dataflash.o
obj-$(CONFIG_FTSMC020) += ftsmc020.o
obj-$(CONFIG_FLASH_CFI_LEGACY) += jedec_flash.o
obj-$(CONFIG_MW_EEPROM) += mw_eeprom.o
obj-$(CONFIG_FLASH_PIC32) += pic32_flash.o
obj-$(CONFIG_ST_SMI) += st_smi.o
obj-$(CONFIG_STM32_FLASH) += stm32_flash.o
obj-$(CONFIG_HIFMC) += hifmc_common.o
obj-$(CONFIG_TARGET_HI3559AV100) += hifmc_hi3559av100.o
obj-$(CONFIG_TARGET_HI3556AV100) += hifmc_hi3556av100.o
obj-$(CONFIG_TARGET_HI3519AV100) += hifmc_hi3519av100.o
obj-$(CONFIG_TARGET_HI3516CV500) += hifmc_hi3516cv500.o
obj-$(CONFIG_TARGET_HI3556V200) += hifmc_hi3556v200.o
obj-$(CONFIG_TARGET_HI3559V200) += hifmc_hi3559v200.o
obj-$(CONFIG_TARGET_HI3516DV300) += hifmc_hi3516dv300.o
obj-$(CONFIG_TARGET_HI3516AV300) += hifmc_hi3516av300.o
obj-$(CONFIG_TARGET_HI3516EV200) += hifmc_hi3516ev200.o
obj-$(CONFIG_TARGET_HI3516EV300) += hifmc_hi3516ev300.o
obj-$(CONFIG_TARGET_HI3518EV300) += hifmc_hi3518ev300.o
obj-$(CONFIG_TARGET_HI3516DV200) += hifmc_hi3516dv200.o
