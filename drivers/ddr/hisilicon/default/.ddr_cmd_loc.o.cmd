cmd_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.o := arm-himix100-linux-gcc -Wp,-MD,drivers/ddr/hisilicon/hi3516ev200/../default/.ddr_cmd_loc.o.d  -nostdinc -isystem /opt/hisi-linux/x86-arm/arm-himix100-linux/host_bin/../lib/gcc/arm-linux-uclibceabi/6.3.0/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -D__ASSEMBLY__ -g -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -fno-pic -mno-unaligned-access -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv7-a -D__LINUX_ARM_ARCH__=7   -c -o drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.o drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.S

source_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.o := drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.S

deps_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.o := \

drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.o: $(deps_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.o)

$(deps_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_cmd_loc.o):
