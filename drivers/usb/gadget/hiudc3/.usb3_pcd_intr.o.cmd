cmd_drivers/usb/gadget/hiudc3/usb3_pcd_intr.o := arm-himix100-linux-gcc -Wp,-MD,drivers/usb/gadget/hiudc3/.usb3_pcd_intr.o.d  -nostdinc -isystem /opt/hisi-linux/x86-arm/arm-himix100-linux/host_bin/../lib/gcc/arm-linux-uclibceabi/6.3.0/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -fstack-usage -Wno-format-nonliteral -Werror=date-time -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -fno-pic -mno-unaligned-access -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv7-a -D__LINUX_ARM_ARCH__=7    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(usb3_pcd_intr)"  -D"KBUILD_MODNAME=KBUILD_STR(usb3_pcd_intr)" -c -o drivers/usb/gadget/hiudc3/usb3_pcd_intr.o drivers/usb/gadget/hiudc3/usb3_pcd_intr.c

source_drivers/usb/gadget/hiudc3/usb3_pcd_intr.o := drivers/usb/gadget/hiudc3/usb3_pcd_intr.c

deps_drivers/usb/gadget/hiudc3/usb3_pcd_intr.o := \
  drivers/usb/gadget/hiudc3/usb3_drv.h \
  drivers/usb/gadget/hiudc3/sys.h \
  drivers/usb/gadget/hiudc3/types.h \
  drivers/usb/gadget/hiudc3/usb3.h \
    $(wildcard include/config/value.h) \
    $(wildcard include/config/att/one.h) \
    $(wildcard include/config/vbus/draw.h) \
  arch/arm/include/asm/types.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/phys/64bit.h) \
    $(wildcard include/config/dma/addr/t/64bit.h) \
  drivers/usb/gadget/hiudc3/usb3_hw.h \
  drivers/usb/gadget/hiudc3/debug.h \
    $(wildcard include/config/pl011/clock.h) \
    $(wildcard include/config/pl01x/ports.h) \
    $(wildcard include/config/cons/index.h) \
    $(wildcard include/config/baudrate.h) \
  drivers/usb/gadget/hiudc3/platform.h \
  /opt/hisi-linux/x86-arm/arm-himix100-linux/lib/gcc/arm-linux-uclibceabi/6.3.0/include/stdarg.h \
  drivers/usb/gadget/hiudc3/usb3_pcd.h \

drivers/usb/gadget/hiudc3/usb3_pcd_intr.o: $(deps_drivers/usb/gadget/hiudc3/usb3_pcd_intr.o)

$(deps_drivers/usb/gadget/hiudc3/usb3_pcd_intr.o):
