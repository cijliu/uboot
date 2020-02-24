cmd_tools/envcrc.o := cc -Wp,-MD,tools/.envcrc.o.d -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer    -include ./include/libfdt_env.h -idirafterinclude -idirafter./arch/arm/include -I./lib/libfdt -I./tools -DCONFIG_SYS_TEXT_BASE=0x40800000 -DUSE_HOSTCC -D__KERNEL_STRICT_NAMES -D_GNU_SOURCE  -c -o tools/envcrc.o tools/envcrc.c

source_tools/envcrc.o := tools/envcrc.c

deps_tools/envcrc.o := \
    $(wildcard include/config/env/is/in/flash.h) \
    $(wildcard include/config/env/addr.h) \
    $(wildcard include/config/sys/flash/base.h) \
    $(wildcard include/config/env/offset.h) \
    $(wildcard include/config/env/addr/redund.h) \
    $(wildcard include/config/env/offset/redund.h) \
    $(wildcard include/config/env/size.h) \
    $(wildcard include/config/env/sect/size.h) \
    $(wildcard include/config/env/size/redund.h) \
    $(wildcard include/config/sys/monitor/base.h) \
    $(wildcard include/config/sys/monitor/len.h) \
    $(wildcard include/config/sys/redundand/environment.h) \
    $(wildcard include/config/build/envcrc.h) \
  include/libfdt_env.h \
  include/compiler.h \
    $(wildcard include/config/use/stdint.h) \
  /usr/lib/gcc/x86_64-linux-gnu/4.6/include/stddef.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.6/include/stdint.h \
  /usr/include/stdint.h \
  /usr/include/features.h \
  /usr/include/x86_64-linux-gnu/bits/predefs.h \
  /usr/include/x86_64-linux-gnu/sys/cdefs.h \
  /usr/include/x86_64-linux-gnu/bits/wordsize.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
  /usr/include/x86_64-linux-gnu/bits/wchar.h \
  /usr/include/errno.h \
  /usr/include/x86_64-linux-gnu/bits/errno.h \
  /usr/include/linux/errno.h \
  /usr/include/x86_64-linux-gnu/asm/errno.h \
  /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h \
  /usr/include/stdlib.h \
  /usr/include/x86_64-linux-gnu/bits/waitflags.h \
  /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
  /usr/include/endian.h \
  /usr/include/x86_64-linux-gnu/bits/endian.h \
  /usr/include/x86_64-linux-gnu/bits/byteswap.h \
  /usr/include/xlocale.h \
  /usr/include/x86_64-linux-gnu/sys/types.h \
  /usr/include/x86_64-linux-gnu/bits/types.h \
  /usr/include/x86_64-linux-gnu/bits/typesizes.h \
  /usr/include/time.h \
  /usr/include/x86_64-linux-gnu/sys/select.h \
  /usr/include/x86_64-linux-gnu/bits/select.h \
  /usr/include/x86_64-linux-gnu/bits/sigset.h \
  /usr/include/x86_64-linux-gnu/bits/time.h \
  /usr/include/x86_64-linux-gnu/bits/select2.h \
  /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
  /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/alloca.h \
  /usr/include/x86_64-linux-gnu/bits/stdlib.h \
  /usr/include/stdio.h \
  /usr/include/libio.h \
  /usr/include/_G_config.h \
  /usr/include/wchar.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.6/include/stdarg.h \
  /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
  /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
  /usr/include/x86_64-linux-gnu/bits/stdio.h \
  /usr/include/x86_64-linux-gnu/bits/stdio2.h \
  /usr/include/string.h \
  /usr/include/x86_64-linux-gnu/bits/string.h \
  /usr/include/x86_64-linux-gnu/bits/string2.h \
  /usr/include/x86_64-linux-gnu/bits/string3.h \
  /usr/include/x86_64-linux-gnu/sys/mman.h \
  /usr/include/x86_64-linux-gnu/bits/mman.h \
  /usr/include/fcntl.h \
  /usr/include/x86_64-linux-gnu/bits/fcntl.h \
  /usr/include/x86_64-linux-gnu/bits/uio.h \
  /usr/include/x86_64-linux-gnu/bits/stat.h \
  /usr/include/x86_64-linux-gnu/bits/fcntl2.h \
  /usr/include/byteswap.h \
  /usr/include/x86_64-linux-gnu/bits/timex.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
  /usr/include/linux/posix_types.h \
  /usr/include/linux/stddef.h \
  /usr/include/x86_64-linux-gnu/asm/posix_types.h \
  /usr/include/x86_64-linux-gnu/asm/posix_types_64.h \
  /usr/include/x86_64-linux-gnu/asm/types.h \
  /usr/include/asm-generic/types.h \
  /usr/include/asm-generic/int-ll64.h \
  /usr/include/x86_64-linux-gnu/asm/bitsperlong.h \
  /usr/include/asm-generic/bitsperlong.h \
    $(wildcard include/config/64bit.h) \
  /usr/lib/gcc/x86_64-linux-gnu/4.6/include/stdbool.h \
  /usr/include/unistd.h \
  /usr/include/x86_64-linux-gnu/bits/posix_opt.h \
  /usr/include/x86_64-linux-gnu/bits/environments.h \
  /usr/include/x86_64-linux-gnu/bits/confname.h \
  /usr/include/getopt.h \
  /usr/include/x86_64-linux-gnu/bits/unistd.h \
  include/config.h \
    $(wildcard include/config/boarddir.h) \
  include/config_defaults.h \
    $(wildcard include/config/defaults/h/.h) \
    $(wildcard include/config/bootm/linux.h) \
    $(wildcard include/config/mini/boot.h) \
    $(wildcard include/config/bootm/netbsd.h) \
    $(wildcard include/config/bootm/plan9.h) \
    $(wildcard include/config/bootm/rtems.h) \
    $(wildcard include/config/bootm/vxworks.h) \
    $(wildcard include/config/gzip.h) \
    $(wildcard include/config/zlib.h) \
    $(wildcard include/config/partitions.h) \
  include/config_uncmd_spl.h \
    $(wildcard include/config/uncmd/spl/h//.h) \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/spl/dm.h) \
    $(wildcard include/config/dm/serial.h) \
    $(wildcard include/config/dm/gpio.h) \
    $(wildcard include/config/dm/i2c.h) \
    $(wildcard include/config/dm/spi.h) \
    $(wildcard include/config/dm/warn.h) \
    $(wildcard include/config/dm/stdio.h) \
  include/configs/hi3516ev200.h \
    $(wildcard include/config/sys/cacheline/size.h) \
    $(wildcard include/config/remake/elf.h) \
    $(wildcard include/config/support/raw/initrd.h) \
    $(wildcard include/config/board/early/init/f.h) \
    $(wildcard include/config/sys/text/base.h) \
    $(wildcard include/config/sys/text/base/ori.h) \
    $(wildcard include/config/nr/dram/banks.h) \
    $(wildcard include/config/sys/sdram/base.h) \
    $(wildcard include/config/sys/init/sp/addr.h) \
    $(wildcard include/config/sys/load/addr.h) \
    $(wildcard include/config/sys/gbl/data/size.h) \
    $(wildcard include/config/sys/timer/rate.h) \
    $(wildcard include/config/sys/timer/counter.h) \
    $(wildcard include/config/sys/timer/counts/down.h) \
    $(wildcard include/config/sys/malloc/len.h) \
    $(wildcard include/config/baudrate.h) \
    $(wildcard include/config/cons/index.h) \
    $(wildcard include/config/pl01x/serial.h) \
    $(wildcard include/config/pl011/serial.h) \
    $(wildcard include/config/pl011/clock.h) \
    $(wildcard include/config/pl01x/ports.h) \
    $(wildcard include/config/cur/uart/base.h) \
    $(wildcard include/config/hifmc.h) \
    $(wildcard include/config/hifmc/reg/base.h) \
    $(wildcard include/config/hifmc/buffer/base.h) \
    $(wildcard include/config/hifmc/max/cs/num.h) \
    $(wildcard include/config/hifmc/spi/nor.h) \
    $(wildcard include/config/cmd/sf.h) \
    $(wildcard include/config/env/is/in/spi/flash.h) \
    $(wildcard include/config/spi/nor/max/chip/num.h) \
    $(wildcard include/config/spi/nor/quiet/test.h) \
    $(wildcard include/config/hifmc/spi/nand.h) \
    $(wildcard include/config/cmd/nand.h) \
    $(wildcard include/config/env/is/in/nand.h) \
    $(wildcard include/config/spi/nand/max/chip/num.h) \
    $(wildcard include/config/sys/max/nand/device.h) \
    $(wildcard include/config/sys/nand/max/chips.h) \
    $(wildcard include/config/sys/nand/base.h) \
    $(wildcard include/config/hifmc/nand.h) \
    $(wildcard include/config/nand/edo/mode.h) \
    $(wildcard include/config/nand/max/chip/num.h) \
    $(wildcard include/config/sys/fault/echo/link/down.h) \
    $(wildcard include/config/net/hisfv300.h) \
    $(wildcard include/config/mmc.h) \
    $(wildcard include/config/support/emmc/boot.h) \
    $(wildcard include/config/generic/mmc.h) \
    $(wildcard include/config/cmd/mmc.h) \
    $(wildcard include/config/env/is/in/mmc.h) \
    $(wildcard include/config/sys/mmc/env/dev.h) \
    $(wildcard include/config/ext4/sparse.h) \
    $(wildcard include/config/sdhci.h) \
    $(wildcard include/config/hisi/sdhci.h) \
    $(wildcard include/config/hisi/sdhci/max/freq.h) \
    $(wildcard include/config/bounce/buffer.h) \
    $(wildcard include/config/fs/ext4.h) \
    $(wildcard include/config/sdhci/adma.h) \
    $(wildcard include/config/himci.h) \
    $(wildcard include/config/himci/max/freq.h) \
    $(wildcard include/config/mmc/power/off/timeout.h) \
    $(wildcard include/config/mmc/power/on/timerout.h) \
    $(wildcard include/config/mmc/reset/low/timeout.h) \
    $(wildcard include/config/mmc/reset/high/timerout.h) \
    $(wildcard include/config/misc/init/r.h) \
    $(wildcard include/config/menu.h) \
    $(wildcard include/config/cmd/unzip.h) \
    $(wildcard include/config/cmd/env.h) \
    $(wildcard include/config/mtd/partitions.h) \
    $(wildcard include/config/bootp/bootfilesize.h) \
    $(wildcard include/config/bootargs.h) \
    $(wildcard include/config/bootcommand.h) \
    $(wildcard include/config/bootdelay.h) \
    $(wildcard include/config/sys/usb/xhci/max/root/ports.h) \
    $(wildcard include/config/env/overwrite.h) \
    $(wildcard include/config/command/history.h) \
    $(wildcard include/config/env/vars/uboot/config.h) \
    $(wildcard include/config/sys/cbsize.h) \
    $(wildcard include/config/sys/pbsize.h) \
    $(wildcard include/config/sys/prompt.h) \
    $(wildcard include/config/sys/bargsize.h) \
    $(wildcard include/config/sys/longhelp.h) \
    $(wildcard include/config/cmdline/editing.h) \
    $(wildcard include/config/sys/maxargs.h) \
    $(wildcard include/config/sys/no/flash.h) \
    $(wildcard include/config/ddr/training/v2.h) \
    $(wildcard include/config/productname.h) \
    $(wildcard include/config/auto/update.h) \
    $(wildcard include/config/auto/update/adaptation.h) \
    $(wildcard include/config/auto/sd/update.h) \
    $(wildcard include/config/auto/usb/update.h) \
    $(wildcard include/config/cmd/fat.h) \
    $(wildcard include/config/skip/lowlevel/init.h) \
    $(wildcard include/config/cmdline/tag.h) \
    $(wildcard include/config/osd/enable.h) \
    $(wildcard include/config/cmd/ugzip.h) \
    $(wildcard include/config/audio/enable.h) \
  include/linux/sizes.h \
  arch/arm/include/asm/arch/platform.h \
    $(wildcard include/config/reg/base.h) \
  include/configs/dopi.h \
  include/config_distro_defaults.h \
    $(wildcard include/config/cmd/distro/defaults/h.h) \
    $(wildcard include/config/bootp/bootpath.h) \
    $(wildcard include/config/bootp/dns.h) \
    $(wildcard include/config/bootp/gateway.h) \
    $(wildcard include/config/bootp/hostname.h) \
    $(wildcard include/config/bootp/pxe.h) \
    $(wildcard include/config/bootp/subnetmask.h) \
    $(wildcard include/config/cmd/pxe.h) \
    $(wildcard include/config/auto/complete.h) \
    $(wildcard include/config/dos/partition.h) \
    $(wildcard include/config/efi/partition.h) \
    $(wildcard include/config/iso/partition.h) \
  include/config_distro_bootcmd.h \
    $(wildcard include/config/cmd/distro/bootcmd/h.h) \
    $(wildcard include/config/partition/uuids.h) \
    $(wildcard include/config/cmd/part.h) \
    $(wildcard include/config/sandbox.h) \
    $(wildcard include/config/cmd/ubifs.h) \
    $(wildcard include/config/efi/loader.h) \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/arm.h) \
    $(wildcard include/config/cmd/sata.h) \
    $(wildcard include/config/scsi.h) \
    $(wildcard include/config/cmd/ide.h) \
    $(wildcard include/config/cmd/pci/enum.h) \
    $(wildcard include/config/dm/pci.h) \
    $(wildcard include/config/cmd/usb.h) \
    $(wildcard include/config/cmd/dhcp.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/cmd/dhcp/or/pxe.h) \
  arch/arm/include/asm/config.h \
    $(wildcard include/config/h/.h) \
    $(wildcard include/config/lmb.h) \
    $(wildcard include/config/sys/boot/ramdisk/high.h) \
    $(wildcard include/config/static/rela.h) \
    $(wildcard include/config/ls102xa.h) \
    $(wildcard include/config/cpu/pxa27x.h) \
    $(wildcard include/config/cpu/monahans.h) \
    $(wildcard include/config/cpu/pxa25x.h) \
    $(wildcard include/config/fsl/layerscape.h) \
  include/config_fallbacks.h \
    $(wildcard include/config/fallbacks/h.h) \
    $(wildcard include/config/spl.h) \
    $(wildcard include/config/spl/pad/to.h) \
    $(wildcard include/config/spl/max/size.h) \
    $(wildcard include/config/sys/baudrate/table.h) \
    $(wildcard include/config/fs/fat.h) \
    $(wildcard include/config/cmd/ext4.h) \
    $(wildcard include/config/cmd/ext2.h) \
    $(wildcard include/config/cmd/ext4/write.h) \
    $(wildcard include/config/ext4/write.h) \
    $(wildcard include/config/cmd/gpt.h) \
    $(wildcard include/config/systemace.h) \
    $(wildcard include/config/random/uuid.h) \
    $(wildcard include/config/cmd/uuid.h) \
    $(wildcard include/config/lib/uuid.h) \
    $(wildcard include/config/lib/rand.h) \
    $(wildcard include/config/lib/hw/rand.h) \
    $(wildcard include/config/api.h) \
    $(wildcard include/config/lcd.h) \
    $(wildcard include/config/cmd/bmp.h) \
    $(wildcard include/config/fit/signature.h) \
    $(wildcard include/config/image/format/legacy.h) \
    $(wildcard include/config/disable/image/legacy.h) \
    $(wildcard include/config/sys/i2c.h) \
    $(wildcard include/config/cmdline.h) \

tools/envcrc.o: $(deps_tools/envcrc.o)

$(deps_tools/envcrc.o):
