ccflags-y += -Idrivers/ddr/hisilicon/default -Idrivers/ddr/hisilicon/$(SOC)

ifndef CONFIG_MINI_BOOT
obj-y += ddr_cmd_loc.o ddr_cmd_ctl.o cmd_ddr_training_v2.o
else
obj-y += ddr_cmd_ctl.o cmd_ddr_training_v2.o
endif

extra-y += ddr_training_impl.o ddr_training_ctl.o ddr_training_boot.o ddr_training_console.o

ifndef CONFIG_MINI_BOOT
$(obj)/ddr_cmd_loc.S: ddr_training_cmd_bin

ddr_training_cmd_bin:
ifdef CONFIG_ARM64
	$(MAKE) -C drivers/ddr/hisilicon/default/cmd_bin TOPDIR=$(CURDIR) CROSS_COMPILE=$(CROSS_COMPILE) CPU=$(CPU) SOC=$(SOC) CONFIG_ARM64=$(CONFIG_ARM64) clean
	$(MAKE) -C drivers/ddr/hisilicon/default/cmd_bin TOPDIR=$(CURDIR) CROSS_COMPILE=$(CROSS_COMPILE) CPU=$(CPU) SOC=$(SOC) CONFIG_ARM64=$(CONFIG_ARM64)

else
	$(MAKE) -C drivers/ddr/hisilicon/default/cmd_bin TOPDIR=$(CURDIR) CROSS_COMPILE=$(CROSS_COMPILE) CPU=$(CPU) SOC=$(SOC) clean
	$(MAKE) -C drivers/ddr/hisilicon/default/cmd_bin TOPDIR=$(CURDIR) CROSS_COMPILE=$(CROSS_COMPILE) CPU=$(CPU) SOC=$(SOC)
endif
endif
