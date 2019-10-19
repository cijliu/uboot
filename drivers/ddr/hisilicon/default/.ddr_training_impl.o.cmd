cmd_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.o := arm-himix100-linux-gcc -Wp,-MD,drivers/ddr/hisilicon/hi3516ev200/../default/.ddr_training_impl.o.d  -nostdinc -isystem /opt/hisi-linux/x86-arm/arm-himix100-linux/host_bin/../lib/gcc/arm-linux-uclibceabi/6.3.0/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -fstack-usage -Wno-format-nonliteral -Werror=date-time -Idrivers/ddr/hisilicon/default -Idrivers/ddr/hisilicon/hi3516ev200 -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -fno-pic -mno-unaligned-access -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv7-a -D__LINUX_ARM_ARCH__=7    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ddr_training_impl)"  -D"KBUILD_MODNAME=KBUILD_STR(ddr_training_impl)" -c -o drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.o drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.c

source_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.o := drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.c

deps_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.o := \
  drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.h \
  drivers/ddr/hisilicon/hi3516ev200/ddr_training_custom.h \
  drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_internal_config.h \
    $(wildcard include/config/h.h) \
  drivers/ddr/hisilicon/hi3516ev200/../default/ddr_ddrc_v520.h \
  drivers/ddr/hisilicon/hi3516ev200/../default/ddr_phy_t28.h \
  drivers/ddr/hisilicon/hi3516ev200/../default/ddr_ddrt_v2_0_shf0.h \
  drivers/ddr/hisilicon/hi3516ev200/../default/ddr_interface.h \

drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.o: $(deps_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.o)

$(deps_drivers/ddr/hisilicon/hi3516ev200/../default/ddr_training_impl.o):
