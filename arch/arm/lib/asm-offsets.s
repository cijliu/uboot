	.arch armv7-a
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 4	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 0	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
	.file	"asm-offsets.c"
@ GNU C11 (HC&C V100R002C00B032_20190114) version 6.3.0 (arm-linux-uclibceabi)
@	compiled by GNU C version 4.1.2 20080704 (Red Hat 4.1.2-44), GMP version 6.1.2, MPFR version 3.1.5, MPC version 1.0.3, isl version none
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed:  -nostdinc -I include -I ./arch/arm/include
@ -iprefix /opt/hisi-linux/x86-arm/arm-himix100-linux/host_bin/../lib/gcc/arm-linux-uclibceabi/6.3.0/
@ -isysroot /opt/hisi-linux/x86-arm/arm-himix100-linux/host_bin/../target
@ -D __KERNEL__ -D __UBOOT__ -D __ARM__ -D __LINUX_ARM_ARCH__=7
@ -D DO_DEPS_ONLY -D KBUILD_STR(s)=#s
@ -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
@ -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
@ -isystem /opt/hisi-linux/x86-arm/arm-himix100-linux/host_bin/../lib/gcc/arm-linux-uclibceabi/6.3.0/include
@ -include ./include/linux/kconfig.h -MD arch/arm/lib/.asm-offsets.s.d
@ arch/arm/lib/asm-offsets.c -marm -mno-thumb-interwork -mabi=aapcs-linux
@ -mword-relocations -mno-unaligned-access -mfloat-abi=soft -march=armv7-a
@ -mtls-dialect=gnu -auxbase-strip arch/arm/lib/asm-offsets.s -g -Os -Wall
@ -Wstrict-prototypes -Wno-format-security -Wno-format-nonliteral
@ -Werror=date-time -fno-builtin -ffreestanding -fno-stack-protector
@ -fno-delete-null-pointer-checks -fstack-usage -fno-pic
@ -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -fverbose-asm
@ options enabled:  -faggressive-loop-optimizations -falign-jumps
@ -falign-labels -falign-loops -fauto-inc-dec -fbranch-count-reg
@ -fcaller-saves -fchkp-check-incomplete-type -fchkp-check-read
@ -fchkp-check-write -fchkp-instrument-calls -fchkp-narrow-bounds
@ -fchkp-optimize -fchkp-store-bounds -fchkp-use-static-bounds
@ -fchkp-use-static-const-bounds -fchkp-use-wrappers
@ -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
@ -fcrossjumping -fcse-follow-jumps -fdata-sections -fdefer-pop
@ -fdevirtualize -fdevirtualize-speculatively -fdwarf2-cfi-asm
@ -fearly-inlining -feliminate-unused-debug-types -fexpensive-optimizations
@ -fforward-propagate -ffunction-cse -ffunction-sections -fgcse -fgcse-lm
@ -fgnu-runtime -fgnu-unique -fguess-branch-probability
@ -fhoist-adjacent-loads -fident -fif-conversion -fif-conversion2
@ -findirect-inlining -finline -finline-atomics -finline-functions
@ -finline-functions-called-once -finline-small-functions -fipa-cp
@ -fipa-cp-alignment -fipa-icf -fipa-icf-functions -fipa-icf-variables
@ -fipa-profile -fipa-pure-const -fipa-ra -fipa-reference -fipa-sra
@ -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
@ -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
@ -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
@ -fmath-errno -fmerge-constants -fmerge-debug-strings
@ -fmove-loop-invariants -fomit-frame-pointer -foptimize-sibling-calls
@ -fpartial-inlining -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays
@ -freg-struct-return -freorder-blocks -freorder-functions
@ -frerun-cse-after-loop -fsched-critical-path-heuristic
@ -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
@ -fsched-last-insn-heuristic -fsched-pressure -fsched-rank-heuristic
@ -fsched-spec -fsched-spec-insn-heuristic -fsched-stalled-insns-dep
@ -fschedule-insns2 -fsection-anchors -fsemantic-interposition
@ -fshow-column -fshrink-wrap -fsigned-zeros -fsplit-ivs-in-unroller
@ -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstdarg-opt
@ -fstrict-aliasing -fstrict-overflow -fstrict-volatile-bitfields
@ -fsync-libcalls -fthread-jumps -ftoplevel-reorder -ftrapping-math
@ -ftree-bit-ccp -ftree-builtin-call-dce -ftree-ccp -ftree-ch
@ -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim -ftree-dce
@ -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
@ -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
@ -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
@ -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr
@ -ftree-sra -ftree-switch-conversion -ftree-tail-merge -ftree-ter
@ -ftree-vrp -funit-at-a-time -fvar-tracking -fvar-tracking-assignments
@ -fverbose-asm -fzero-initialized-in-bss -marm -mlittle-endian
@ -mpic-data-is-text-relative -msched-prolog -muclibc
@ -mvectorize-with-neon-quad -mword-relocations

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup.main,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
.LFB192:
	.file 1 "arch/arm/lib/asm-offsets.c"
	.loc 1 24 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 202 0
	mov	r0, #0	@,
	bx	lr	@
	.cfi_endproc
.LFE192:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "include/common.h"
	.file 3 "./arch/arm/include/asm/types.h"
	.file 4 "include/linux/types.h"
	.file 5 "include/errno.h"
	.file 6 "include/linux/string.h"
	.file 7 "include/ide.h"
	.file 8 "include/part.h"
	.file 9 "include/efi.h"
	.file 10 "include/flash.h"
	.file 11 "include/lmb.h"
	.file 12 "include/asm-generic/u-boot.h"
	.file 13 "include/fdt.h"
	.file 14 "include/libfdt_env.h"
	.file 15 "include/image.h"
	.file 16 "./arch/arm/include/asm/mach-types.h"
	.file 17 "./arch/arm/include/asm/setup.h"
	.file 18 "./arch/arm/include/asm/u-boot-arm.h"
	.file 19 "include/net.h"
	.file 20 "include/environment.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xc86
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF195
	.byte	0xc
	.4byte	.LASF196
	.4byte	.LASF197
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF4
	.byte	0x2
	.byte	0xd
	.4byte	0x30
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x4
	.4byte	0x30
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x5
	.4byte	.LASF21
	.byte	0x5
	.byte	0xc
	.4byte	0x55
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3
	.uleb128 0x2
	.4byte	.LASF5
	.byte	0x3
	.byte	0xc
	.4byte	0x30
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.4byte	.LASF7
	.byte	0x3
	.byte	0x12
	.4byte	0x80
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x7
	.ascii	"u8\000"
	.byte	0x3
	.byte	0x1f
	.4byte	0x30
	.uleb128 0x4
	.4byte	0x95
	.uleb128 0x7
	.ascii	"u32\000"
	.byte	0x3
	.byte	0x25
	.4byte	0x80
	.uleb128 0x2
	.4byte	.LASF11
	.byte	0x3
	.byte	0x35
	.4byte	0x3c
	.uleb128 0x2
	.4byte	.LASF12
	.byte	0x3
	.byte	0x36
	.4byte	0x3c
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x8
	.byte	0x4
	.4byte	0xd9
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF14
	.uleb128 0x4
	.4byte	0xd2
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF15
	.uleb128 0x8
	.byte	0x4
	.4byte	0xd2
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x4
	.byte	0x57
	.4byte	0x43
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0x4
	.byte	0x59
	.4byte	0x3c
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x4
	.byte	0x67
	.4byte	0x63
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x4
	.byte	0x69
	.4byte	0x75
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x4
	.byte	0x95
	.4byte	0x75
	.uleb128 0x5
	.4byte	.LASF22
	.byte	0x6
	.byte	0xb
	.4byte	0xe5
	.uleb128 0x9
	.byte	0x4
	.uleb128 0xa
	.4byte	0xf6
	.4byte	0x13a
	.uleb128 0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF23
	.byte	0x7
	.byte	0x10
	.4byte	0x12f
	.uleb128 0xc
	.4byte	.LASF26
	.byte	0x8
	.byte	0x8
	.byte	0xd
	.4byte	0x16a
	.uleb128 0xd
	.4byte	.LASF24
	.byte	0x8
	.byte	0xe
	.4byte	0xe5
	.byte	0
	.uleb128 0xd
	.4byte	.LASF25
	.byte	0x8
	.byte	0xf
	.4byte	0x183
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	0x145
	.uleb128 0xe
	.4byte	0x55
	.4byte	0x183
	.uleb128 0xf
	.4byte	0x55
	.uleb128 0xf
	.4byte	0x55
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x16f
	.uleb128 0xa
	.4byte	0x16a
	.4byte	0x194
	.uleb128 0xb
	.byte	0
	.uleb128 0x4
	.4byte	0x189
	.uleb128 0x5
	.4byte	.LASF26
	.byte	0x8
	.byte	0xb6
	.4byte	0x194
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF27
	.uleb128 0xa
	.4byte	0xd2
	.4byte	0x1b6
	.uleb128 0xb
	.byte	0
	.uleb128 0x10
	.4byte	.LASF28
	.byte	0x9
	.2byte	0x121
	.4byte	0x1ab
	.uleb128 0x10
	.4byte	.LASF29
	.byte	0x9
	.2byte	0x124
	.4byte	0x1ab
	.uleb128 0x10
	.4byte	.LASF30
	.byte	0x9
	.2byte	0x124
	.4byte	0x1ab
	.uleb128 0x11
	.2byte	0xa0c
	.byte	0xa
	.byte	0x13
	.4byte	0x221
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xa
	.byte	0x14
	.4byte	0xf6
	.byte	0
	.uleb128 0xd
	.4byte	.LASF32
	.byte	0xa
	.byte	0x15
	.4byte	0xeb
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF33
	.byte	0xa
	.byte	0x16
	.4byte	0xf6
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF34
	.byte	0xa
	.byte	0x17
	.4byte	0x221
	.byte	0xc
	.uleb128 0x12
	.4byte	.LASF35
	.byte	0xa
	.byte	0x18
	.4byte	0x232
	.2byte	0x80c
	.byte	0
	.uleb128 0xa
	.4byte	0xf6
	.4byte	0x232
	.uleb128 0x13
	.4byte	0xc5
	.2byte	0x1ff
	.byte	0
	.uleb128 0xa
	.4byte	0x25
	.4byte	0x243
	.uleb128 0x13
	.4byte	0xc5
	.2byte	0x1ff
	.byte	0
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0xa
	.byte	0x32
	.4byte	0x1da
	.uleb128 0xa
	.4byte	0x243
	.4byte	0x259
	.uleb128 0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF37
	.byte	0xa
	.byte	0x34
	.4byte	0x24e
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	.LASF38
	.uleb128 0xc
	.4byte	.LASF39
	.byte	0x8
	.byte	0xb
	.byte	0x10
	.4byte	0x290
	.uleb128 0xd
	.4byte	.LASF40
	.byte	0xb
	.byte	0x11
	.4byte	0xaf
	.byte	0
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xb
	.byte	0x12
	.4byte	0xba
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.4byte	.LASF41
	.byte	0x50
	.byte	0xb
	.byte	0x15
	.4byte	0x2c1
	.uleb128 0x14
	.ascii	"cnt\000"
	.byte	0xb
	.byte	0x16
	.4byte	0x3c
	.byte	0
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xb
	.byte	0x17
	.4byte	0xba
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF42
	.byte	0xb
	.byte	0x18
	.4byte	0x2c1
	.byte	0x8
	.byte	0
	.uleb128 0xa
	.4byte	0x26b
	.4byte	0x2d1
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x8
	.byte	0
	.uleb128 0x16
	.ascii	"lmb\000"
	.byte	0xa0
	.byte	0xb
	.byte	0x1b
	.4byte	0x2f6
	.uleb128 0xd
	.4byte	.LASF43
	.byte	0xb
	.byte	0x1c
	.4byte	0x290
	.byte	0
	.uleb128 0xd
	.4byte	.LASF44
	.byte	0xb
	.byte	0x1d
	.4byte	0x290
	.byte	0x50
	.byte	0
	.uleb128 0x17
	.ascii	"lmb\000"
	.byte	0xb
	.byte	0x20
	.4byte	0x2d1
	.uleb128 0x18
	.byte	0x8
	.byte	0xc
	.byte	0x84
	.4byte	0x322
	.uleb128 0xd
	.4byte	.LASF34
	.byte	0xc
	.byte	0x85
	.4byte	0xaf
	.byte	0
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xc
	.byte	0x86
	.4byte	0xba
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.4byte	.LASF45
	.byte	0x50
	.byte	0xc
	.byte	0x1b
	.4byte	0x413
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0xc
	.byte	0x1c
	.4byte	0x3c
	.byte	0
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0xc
	.byte	0x1d
	.4byte	0xba
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF48
	.byte	0xc
	.byte	0x1e
	.4byte	0x3c
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF49
	.byte	0xc
	.byte	0x1f
	.4byte	0x3c
	.byte	0xc
	.uleb128 0xd
	.4byte	.LASF50
	.byte	0xc
	.byte	0x20
	.4byte	0x3c
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF51
	.byte	0xc
	.byte	0x21
	.4byte	0x3c
	.byte	0x14
	.uleb128 0xd
	.4byte	.LASF52
	.byte	0xc
	.byte	0x22
	.4byte	0x3c
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF53
	.byte	0xc
	.byte	0x28
	.4byte	0x3c
	.byte	0x1c
	.uleb128 0xd
	.4byte	.LASF54
	.byte	0xc
	.byte	0x29
	.4byte	0x3c
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF55
	.byte	0xc
	.byte	0x2a
	.4byte	0x3c
	.byte	0x24
	.uleb128 0xd
	.4byte	.LASF56
	.byte	0xc
	.byte	0x36
	.4byte	0x3c
	.byte	0x28
	.uleb128 0xd
	.4byte	.LASF57
	.byte	0xc
	.byte	0x37
	.4byte	0x3c
	.byte	0x2c
	.uleb128 0xd
	.4byte	.LASF58
	.byte	0xc
	.byte	0x38
	.4byte	0x413
	.byte	0x30
	.uleb128 0xd
	.4byte	.LASF59
	.byte	0xc
	.byte	0x39
	.4byte	0x43
	.byte	0x36
	.uleb128 0xd
	.4byte	.LASF60
	.byte	0xc
	.byte	0x3a
	.4byte	0x3c
	.byte	0x38
	.uleb128 0xd
	.4byte	.LASF61
	.byte	0xc
	.byte	0x3b
	.4byte	0x3c
	.byte	0x3c
	.uleb128 0xd
	.4byte	.LASF62
	.byte	0xc
	.byte	0x81
	.4byte	0xf6
	.byte	0x40
	.uleb128 0xd
	.4byte	.LASF63
	.byte	0xc
	.byte	0x82
	.4byte	0xf6
	.byte	0x44
	.uleb128 0xd
	.4byte	.LASF64
	.byte	0xc
	.byte	0x87
	.4byte	0x423
	.byte	0x48
	.byte	0
	.uleb128 0xa
	.4byte	0x30
	.4byte	0x423
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x5
	.byte	0
	.uleb128 0xa
	.4byte	0x301
	.4byte	0x433
	.uleb128 0x15
	.4byte	0xc5
	.byte	0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF65
	.byte	0xc
	.byte	0x89
	.4byte	0x322
	.uleb128 0xc
	.4byte	.LASF66
	.byte	0x28
	.byte	0xd
	.byte	0x39
	.4byte	0x4c3
	.uleb128 0xd
	.4byte	.LASF67
	.byte	0xd
	.byte	0x3a
	.4byte	0x4d4
	.byte	0
	.uleb128 0xd
	.4byte	.LASF68
	.byte	0xd
	.byte	0x3b
	.4byte	0x4d4
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF69
	.byte	0xd
	.byte	0x3c
	.4byte	0x4d4
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF70
	.byte	0xd
	.byte	0x3d
	.4byte	0x4d4
	.byte	0xc
	.uleb128 0xd
	.4byte	.LASF71
	.byte	0xd
	.byte	0x3e
	.4byte	0x4d4
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF72
	.byte	0xd
	.byte	0x3f
	.4byte	0x4d4
	.byte	0x14
	.uleb128 0xd
	.4byte	.LASF73
	.byte	0xd
	.byte	0x40
	.4byte	0x4d4
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF74
	.byte	0xd
	.byte	0x43
	.4byte	0x4d4
	.byte	0x1c
	.uleb128 0xd
	.4byte	.LASF75
	.byte	0xd
	.byte	0x46
	.4byte	0x4d4
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF76
	.byte	0xd
	.byte	0x49
	.4byte	0x4d4
	.byte	0x24
	.byte	0
	.uleb128 0x5
	.4byte	.LASF77
	.byte	0xe
	.byte	0xf
	.4byte	0x4ce
	.uleb128 0x8
	.byte	0x4
	.4byte	0x43e
	.uleb128 0x2
	.4byte	.LASF78
	.byte	0xe
	.byte	0x12
	.4byte	0x117
	.uleb128 0x19
	.4byte	.LASF79
	.byte	0x40
	.byte	0xf
	.2byte	0x13a
	.4byte	0x589
	.uleb128 0x1a
	.4byte	.LASF80
	.byte	0xf
	.2byte	0x13b
	.4byte	0x117
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF81
	.byte	0xf
	.2byte	0x13c
	.4byte	0x117
	.byte	0x4
	.uleb128 0x1a
	.4byte	.LASF82
	.byte	0xf
	.2byte	0x13d
	.4byte	0x117
	.byte	0x8
	.uleb128 0x1a
	.4byte	.LASF83
	.byte	0xf
	.2byte	0x13e
	.4byte	0x117
	.byte	0xc
	.uleb128 0x1a
	.4byte	.LASF84
	.byte	0xf
	.2byte	0x13f
	.4byte	0x117
	.byte	0x10
	.uleb128 0x1a
	.4byte	.LASF85
	.byte	0xf
	.2byte	0x140
	.4byte	0x117
	.byte	0x14
	.uleb128 0x1a
	.4byte	.LASF86
	.byte	0xf
	.2byte	0x141
	.4byte	0x117
	.byte	0x18
	.uleb128 0x1a
	.4byte	.LASF87
	.byte	0xf
	.2byte	0x142
	.4byte	0x101
	.byte	0x1c
	.uleb128 0x1a
	.4byte	.LASF88
	.byte	0xf
	.2byte	0x143
	.4byte	0x101
	.byte	0x1d
	.uleb128 0x1a
	.4byte	.LASF89
	.byte	0xf
	.2byte	0x144
	.4byte	0x101
	.byte	0x1e
	.uleb128 0x1a
	.4byte	.LASF90
	.byte	0xf
	.2byte	0x145
	.4byte	0x101
	.byte	0x1f
	.uleb128 0x1a
	.4byte	.LASF91
	.byte	0xf
	.2byte	0x146
	.4byte	0x589
	.byte	0x20
	.byte	0
	.uleb128 0xa
	.4byte	0x101
	.4byte	0x599
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x1f
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF92
	.byte	0xf
	.2byte	0x147
	.4byte	0x4df
	.uleb128 0x19
	.4byte	.LASF93
	.byte	0x18
	.byte	0xf
	.2byte	0x149
	.4byte	0x627
	.uleb128 0x1a
	.4byte	.LASF34
	.byte	0xf
	.2byte	0x14a
	.4byte	0xf6
	.byte	0
	.uleb128 0x1c
	.ascii	"end\000"
	.byte	0xf
	.2byte	0x14a
	.4byte	0xf6
	.byte	0x4
	.uleb128 0x1a
	.4byte	.LASF94
	.byte	0xf
	.2byte	0x14b
	.4byte	0xf6
	.byte	0x8
	.uleb128 0x1a
	.4byte	.LASF95
	.byte	0xf
	.2byte	0x14b
	.4byte	0xf6
	.byte	0xc
	.uleb128 0x1a
	.4byte	.LASF96
	.byte	0xf
	.2byte	0x14c
	.4byte	0xf6
	.byte	0x10
	.uleb128 0x1a
	.4byte	.LASF97
	.byte	0xf
	.2byte	0x14d
	.4byte	0x101
	.byte	0x14
	.uleb128 0x1a
	.4byte	.LASF98
	.byte	0xf
	.2byte	0x14d
	.4byte	0x101
	.byte	0x15
	.uleb128 0x1c
	.ascii	"os\000"
	.byte	0xf
	.2byte	0x14d
	.4byte	0x101
	.byte	0x16
	.uleb128 0x1a
	.4byte	.LASF99
	.byte	0xf
	.2byte	0x14e
	.4byte	0x101
	.byte	0x17
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF100
	.byte	0xf
	.2byte	0x14f
	.4byte	0x5a5
	.uleb128 0x1d
	.4byte	.LASF101
	.2byte	0x164
	.byte	0xf
	.2byte	0x155
	.4byte	0x7c6
	.uleb128 0x1a
	.4byte	.LASF102
	.byte	0xf
	.2byte	0x15b
	.4byte	0x7c6
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF103
	.byte	0xf
	.2byte	0x15c
	.4byte	0x599
	.byte	0x4
	.uleb128 0x1a
	.4byte	.LASF104
	.byte	0xf
	.2byte	0x15d
	.4byte	0xf6
	.byte	0x44
	.uleb128 0x1a
	.4byte	.LASF105
	.byte	0xf
	.2byte	0x160
	.4byte	0xcc
	.byte	0x48
	.uleb128 0x1a
	.4byte	.LASF106
	.byte	0xf
	.2byte	0x162
	.4byte	0x12d
	.byte	0x4c
	.uleb128 0x1a
	.4byte	.LASF107
	.byte	0xf
	.2byte	0x163
	.4byte	0xcc
	.byte	0x50
	.uleb128 0x1a
	.4byte	.LASF108
	.byte	0xf
	.2byte	0x164
	.4byte	0x55
	.byte	0x54
	.uleb128 0x1a
	.4byte	.LASF109
	.byte	0xf
	.2byte	0x166
	.4byte	0x12d
	.byte	0x58
	.uleb128 0x1a
	.4byte	.LASF110
	.byte	0xf
	.2byte	0x167
	.4byte	0xcc
	.byte	0x5c
	.uleb128 0x1a
	.4byte	.LASF111
	.byte	0xf
	.2byte	0x168
	.4byte	0x55
	.byte	0x60
	.uleb128 0x1a
	.4byte	.LASF112
	.byte	0xf
	.2byte	0x16a
	.4byte	0x12d
	.byte	0x64
	.uleb128 0x1a
	.4byte	.LASF113
	.byte	0xf
	.2byte	0x16b
	.4byte	0xcc
	.byte	0x68
	.uleb128 0x1a
	.4byte	.LASF114
	.byte	0xf
	.2byte	0x16c
	.4byte	0x55
	.byte	0x6c
	.uleb128 0x1a
	.4byte	.LASF115
	.byte	0xf
	.2byte	0x16e
	.4byte	0x12d
	.byte	0x70
	.uleb128 0x1a
	.4byte	.LASF116
	.byte	0xf
	.2byte	0x16f
	.4byte	0xcc
	.byte	0x74
	.uleb128 0x1a
	.4byte	.LASF117
	.byte	0xf
	.2byte	0x170
	.4byte	0x55
	.byte	0x78
	.uleb128 0x1c
	.ascii	"os\000"
	.byte	0xf
	.2byte	0x174
	.4byte	0x627
	.byte	0x7c
	.uleb128 0x1c
	.ascii	"ep\000"
	.byte	0xf
	.2byte	0x175
	.4byte	0xf6
	.byte	0x94
	.uleb128 0x1a
	.4byte	.LASF118
	.byte	0xf
	.2byte	0x177
	.4byte	0xf6
	.byte	0x98
	.uleb128 0x1a
	.4byte	.LASF119
	.byte	0xf
	.2byte	0x177
	.4byte	0xf6
	.byte	0x9c
	.uleb128 0x1a
	.4byte	.LASF120
	.byte	0xf
	.2byte	0x179
	.4byte	0xe5
	.byte	0xa0
	.uleb128 0x1a
	.4byte	.LASF121
	.byte	0xf
	.2byte	0x17a
	.4byte	0xf6
	.byte	0xa4
	.uleb128 0x1a
	.4byte	.LASF122
	.byte	0xf
	.2byte	0x17c
	.4byte	0xf6
	.byte	0xa8
	.uleb128 0x1a
	.4byte	.LASF123
	.byte	0xf
	.2byte	0x17d
	.4byte	0xf6
	.byte	0xac
	.uleb128 0x1a
	.4byte	.LASF124
	.byte	0xf
	.2byte	0x17e
	.4byte	0xf6
	.byte	0xb0
	.uleb128 0x1a
	.4byte	.LASF125
	.byte	0xf
	.2byte	0x17f
	.4byte	0xf6
	.byte	0xb4
	.uleb128 0x1c
	.ascii	"kbd\000"
	.byte	0xf
	.2byte	0x180
	.4byte	0x7cc
	.byte	0xb8
	.uleb128 0x1a
	.4byte	.LASF126
	.byte	0xf
	.2byte	0x183
	.4byte	0x55
	.byte	0xbc
	.uleb128 0x1a
	.4byte	.LASF127
	.byte	0xf
	.2byte	0x190
	.4byte	0x55
	.byte	0xc0
	.uleb128 0x1c
	.ascii	"lmb\000"
	.byte	0xf
	.2byte	0x193
	.4byte	0x2d1
	.byte	0xc4
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x599
	.uleb128 0x8
	.byte	0x4
	.4byte	0x433
	.uleb128 0x1b
	.4byte	.LASF128
	.byte	0xf
	.2byte	0x195
	.4byte	0x633
	.uleb128 0x10
	.4byte	.LASF129
	.byte	0xf
	.2byte	0x197
	.4byte	0x7d2
	.uleb128 0xa
	.4byte	0xd2
	.4byte	0x7fa
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x1f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF130
	.byte	0x2
	.2byte	0x115
	.4byte	0xf6
	.uleb128 0xa
	.4byte	0x95
	.4byte	0x811
	.uleb128 0xb
	.byte	0
	.uleb128 0x10
	.4byte	.LASF131
	.byte	0x2
	.2byte	0x117
	.4byte	0x806
	.uleb128 0x10
	.4byte	.LASF132
	.byte	0x2
	.2byte	0x15b
	.4byte	0xf6
	.uleb128 0x10
	.4byte	.LASF133
	.byte	0x2
	.2byte	0x15c
	.4byte	0xf6
	.uleb128 0x10
	.4byte	.LASF134
	.byte	0x2
	.2byte	0x15d
	.4byte	0xf6
	.uleb128 0x5
	.4byte	.LASF135
	.byte	0x10
	.byte	0xb
	.4byte	0x80
	.uleb128 0xa
	.4byte	0xd2
	.4byte	0x85d
	.uleb128 0x13
	.4byte	0xc5
	.2byte	0x3ff
	.byte	0
	.uleb128 0x1e
	.byte	0xc
	.byte	0x11
	.2byte	0x104
	.4byte	0x88e
	.uleb128 0x1a
	.4byte	.LASF34
	.byte	0x11
	.2byte	0x105
	.4byte	0x3c
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF31
	.byte	0x11
	.2byte	0x106
	.4byte	0x3c
	.byte	0x4
	.uleb128 0x1a
	.4byte	.LASF136
	.byte	0x11
	.2byte	0x107
	.4byte	0x55
	.byte	0x8
	.byte	0
	.uleb128 0x19
	.4byte	.LASF137
	.byte	0x68
	.byte	0x11
	.2byte	0x101
	.4byte	0x8c3
	.uleb128 0x1a
	.4byte	.LASF138
	.byte	0x11
	.2byte	0x102
	.4byte	0x55
	.byte	0
	.uleb128 0x1c
	.ascii	"end\000"
	.byte	0x11
	.2byte	0x103
	.4byte	0x3c
	.byte	0x4
	.uleb128 0x1a
	.4byte	.LASF139
	.byte	0x11
	.2byte	0x108
	.4byte	0x8c3
	.byte	0x8
	.byte	0
	.uleb128 0xa
	.4byte	0x85d
	.4byte	0x8d3
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x7
	.byte	0
	.uleb128 0x10
	.4byte	.LASF137
	.byte	0x11
	.2byte	0x10b
	.4byte	0x88e
	.uleb128 0x5
	.4byte	.LASF140
	.byte	0x12
	.byte	0x11
	.4byte	0xf6
	.uleb128 0x5
	.4byte	.LASF141
	.byte	0x12
	.byte	0x12
	.4byte	0xf6
	.uleb128 0x5
	.4byte	.LASF142
	.byte	0x12
	.byte	0x13
	.4byte	0xf6
	.uleb128 0x5
	.4byte	.LASF143
	.byte	0x12
	.byte	0x14
	.4byte	0xf6
	.uleb128 0x5
	.4byte	.LASF144
	.byte	0x12
	.byte	0x15
	.4byte	0xf6
	.uleb128 0x5
	.4byte	.LASF145
	.byte	0x12
	.byte	0x16
	.4byte	0xf6
	.uleb128 0x5
	.4byte	.LASF146
	.byte	0x12
	.byte	0x17
	.4byte	0xf6
	.uleb128 0xc
	.4byte	.LASF147
	.byte	0x4
	.byte	0x13
	.byte	0x2a
	.4byte	0x945
	.uleb128 0xd
	.4byte	.LASF148
	.byte	0x13
	.byte	0x2b
	.4byte	0x117
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x25
	.uleb128 0xc
	.4byte	.LASF149
	.byte	0x40
	.byte	0x13
	.byte	0xa2
	.4byte	0x9e8
	.uleb128 0xd
	.4byte	.LASF24
	.byte	0x13
	.byte	0xa3
	.4byte	0x9e8
	.byte	0
	.uleb128 0xd
	.4byte	.LASF150
	.byte	0x13
	.byte	0xa4
	.4byte	0x413
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF151
	.byte	0x13
	.byte	0xa5
	.4byte	0xaf
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF127
	.byte	0x13
	.byte	0xa6
	.4byte	0x55
	.byte	0x1c
	.uleb128 0xd
	.4byte	.LASF152
	.byte	0x13
	.byte	0xa8
	.4byte	0xa12
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF153
	.byte	0x13
	.byte	0xa9
	.4byte	0xa31
	.byte	0x24
	.uleb128 0xd
	.4byte	.LASF154
	.byte	0x13
	.byte	0xaa
	.4byte	0xa46
	.byte	0x28
	.uleb128 0xd
	.4byte	.LASF155
	.byte	0x13
	.byte	0xab
	.4byte	0xa57
	.byte	0x2c
	.uleb128 0xd
	.4byte	.LASF156
	.byte	0x13
	.byte	0xaf
	.4byte	0xa46
	.byte	0x30
	.uleb128 0xd
	.4byte	.LASF157
	.byte	0x13
	.byte	0xb0
	.4byte	0xa0c
	.byte	0x34
	.uleb128 0xd
	.4byte	.LASF158
	.byte	0x13
	.byte	0xb1
	.4byte	0x55
	.byte	0x38
	.uleb128 0xd
	.4byte	.LASF159
	.byte	0x13
	.byte	0xb2
	.4byte	0x12d
	.byte	0x3c
	.byte	0
	.uleb128 0xa
	.4byte	0xd2
	.4byte	0x9f8
	.uleb128 0x15
	.4byte	0xc5
	.byte	0xf
	.byte	0
	.uleb128 0xe
	.4byte	0x55
	.4byte	0xa0c
	.uleb128 0xf
	.4byte	0xa0c
	.uleb128 0xf
	.4byte	0x7cc
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x94b
	.uleb128 0x8
	.byte	0x4
	.4byte	0x9f8
	.uleb128 0xe
	.4byte	0x55
	.4byte	0xa31
	.uleb128 0xf
	.4byte	0xa0c
	.uleb128 0xf
	.4byte	0x12d
	.uleb128 0xf
	.4byte	0x55
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0xa18
	.uleb128 0xe
	.4byte	0x55
	.4byte	0xa46
	.uleb128 0xf
	.4byte	0xa0c
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0xa37
	.uleb128 0x1f
	.4byte	0xa57
	.uleb128 0xf
	.4byte	0xa0c
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0xa4c
	.uleb128 0x5
	.4byte	.LASF160
	.byte	0x13
	.byte	0xb8
	.4byte	0xa0c
	.uleb128 0xa
	.4byte	0x95
	.4byte	0xa78
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x5
	.byte	0
	.uleb128 0x10
	.4byte	.LASF161
	.byte	0x13
	.2byte	0x1f2
	.4byte	0x92c
	.uleb128 0x10
	.4byte	.LASF162
	.byte	0x13
	.2byte	0x1f3
	.4byte	0x92c
	.uleb128 0x10
	.4byte	.LASF163
	.byte	0x13
	.2byte	0x1f5
	.4byte	0x92c
	.uleb128 0x10
	.4byte	.LASF164
	.byte	0x13
	.2byte	0x1fa
	.4byte	0x7ea
	.uleb128 0x10
	.4byte	.LASF165
	.byte	0x13
	.2byte	0x1fb
	.4byte	0x7ea
	.uleb128 0xa
	.4byte	0xd2
	.4byte	0xac4
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x3f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF166
	.byte	0x13
	.2byte	0x1fc
	.4byte	0xab4
	.uleb128 0x10
	.4byte	.LASF167
	.byte	0x13
	.2byte	0x1fe
	.4byte	0xa68
	.uleb128 0x10
	.4byte	.LASF168
	.byte	0x13
	.2byte	0x1ff
	.4byte	0xa68
	.uleb128 0x10
	.4byte	.LASF169
	.byte	0x13
	.2byte	0x200
	.4byte	0x92c
	.uleb128 0x10
	.4byte	.LASF170
	.byte	0x13
	.2byte	0x201
	.4byte	0x92c
	.uleb128 0x10
	.4byte	.LASF171
	.byte	0x13
	.2byte	0x202
	.4byte	0x945
	.uleb128 0xa
	.4byte	0x945
	.4byte	0xb1c
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x3
	.byte	0
	.uleb128 0x10
	.4byte	.LASF172
	.byte	0x13
	.2byte	0x203
	.4byte	0xb0c
	.uleb128 0x10
	.4byte	.LASF173
	.byte	0x13
	.2byte	0x204
	.4byte	0x945
	.uleb128 0x10
	.4byte	.LASF174
	.byte	0x13
	.2byte	0x205
	.4byte	0x55
	.uleb128 0xa
	.4byte	0x9f
	.4byte	0xb50
	.uleb128 0x15
	.4byte	0xc5
	.byte	0x5
	.byte	0
	.uleb128 0x4
	.4byte	0xb40
	.uleb128 0x10
	.4byte	.LASF175
	.byte	0x13
	.2byte	0x206
	.4byte	0xb50
	.uleb128 0x10
	.4byte	.LASF176
	.byte	0x13
	.2byte	0x207
	.4byte	0xb50
	.uleb128 0x10
	.4byte	.LASF177
	.byte	0x13
	.2byte	0x20b
	.4byte	0xeb
	.uleb128 0x10
	.4byte	.LASF178
	.byte	0x13
	.2byte	0x20c
	.4byte	0xeb
	.uleb128 0x10
	.4byte	.LASF179
	.byte	0x13
	.2byte	0x20e
	.4byte	0x55
	.uleb128 0x10
	.4byte	.LASF180
	.byte	0x13
	.2byte	0x215
	.4byte	0x84c
	.uleb128 0x10
	.4byte	.LASF181
	.byte	0x13
	.2byte	0x217
	.4byte	0xa4
	.uleb128 0x10
	.4byte	.LASF182
	.byte	0x13
	.2byte	0x219
	.4byte	0xa4
	.uleb128 0x10
	.4byte	.LASF183
	.byte	0x13
	.2byte	0x221
	.4byte	0x92c
	.uleb128 0x20
	.4byte	.LASF198
	.byte	0x4
	.4byte	0x80
	.byte	0x13
	.2byte	0x277
	.4byte	0xbeb
	.uleb128 0x21
	.4byte	.LASF184
	.byte	0
	.uleb128 0x21
	.4byte	.LASF185
	.byte	0x1
	.uleb128 0x21
	.4byte	.LASF186
	.byte	0x2
	.uleb128 0x21
	.4byte	.LASF187
	.byte	0x3
	.byte	0
	.uleb128 0x10
	.4byte	.LASF188
	.byte	0x13
	.2byte	0x27d
	.4byte	0xbc1
	.uleb128 0x5
	.4byte	.LASF189
	.byte	0x14
	.byte	0x91
	.4byte	0xe5
	.uleb128 0x22
	.4byte	.LASF190
	.4byte	0x40000
	.byte	0x14
	.byte	0x9b
	.4byte	0xc2a
	.uleb128 0x14
	.ascii	"crc\000"
	.byte	0x14
	.byte	0x9c
	.4byte	0x10c
	.byte	0
	.uleb128 0xd
	.4byte	.LASF191
	.byte	0x14
	.byte	0xa0
	.4byte	0xc2a
	.byte	0x4
	.byte	0
	.uleb128 0xa
	.4byte	0x30
	.4byte	0xc3d
	.uleb128 0x23
	.4byte	0xc5
	.4byte	0x3fffb
	.byte	0
	.uleb128 0x2
	.4byte	.LASF192
	.byte	0x14
	.byte	0xa1
	.4byte	0xc02
	.uleb128 0xa
	.4byte	0x37
	.4byte	0xc53
	.uleb128 0xb
	.byte	0
	.uleb128 0x4
	.4byte	0xc48
	.uleb128 0x5
	.4byte	.LASF193
	.byte	0x14
	.byte	0xac
	.4byte	0xc53
	.uleb128 0x5
	.4byte	.LASF194
	.byte	0x14
	.byte	0xad
	.4byte	0xc6e
	.uleb128 0x8
	.byte	0x4
	.4byte	0xc3d
	.uleb128 0x24
	.4byte	.LASF199
	.byte	0x1
	.byte	0x17
	.4byte	0x55
	.4byte	.LFB192
	.4byte	.LFE192-.LFB192
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x6
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB192
	.4byte	.LFE192-.LFB192
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB192
	.4byte	.LFE192
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF105:
	.ascii	"fit_uname_cfg\000"
.LASF107:
	.ascii	"fit_uname_os\000"
.LASF17:
	.ascii	"ulong\000"
.LASF63:
	.ascii	"bi_boot_params\000"
.LASF161:
	.ascii	"net_gateway\000"
.LASF187:
	.ascii	"NETLOOP_FAIL\000"
.LASF47:
	.ascii	"bi_memsize\000"
.LASF108:
	.ascii	"fit_noffset_os\000"
.LASF84:
	.ascii	"ih_load\000"
.LASF185:
	.ascii	"NETLOOP_RESTART\000"
.LASF98:
	.ascii	"type\000"
.LASF97:
	.ascii	"comp\000"
.LASF25:
	.ascii	"select_hwpart\000"
.LASF141:
	.ascii	"FIQ_STACK_START\000"
.LASF68:
	.ascii	"totalsize\000"
.LASF176:
	.ascii	"net_null_ethaddr\000"
.LASF10:
	.ascii	"long long unsigned int\000"
.LASF150:
	.ascii	"enetaddr\000"
.LASF152:
	.ascii	"init\000"
.LASF73:
	.ascii	"last_comp_version\000"
.LASF157:
	.ascii	"next\000"
.LASF39:
	.ascii	"lmb_property\000"
.LASF165:
	.ascii	"net_hostname\000"
.LASF9:
	.ascii	"long long int\000"
.LASF3:
	.ascii	"signed char\000"
.LASF80:
	.ascii	"ih_magic\000"
.LASF62:
	.ascii	"bi_arch_number\000"
.LASF102:
	.ascii	"legacy_hdr_os\000"
.LASF123:
	.ascii	"initrd_end\000"
.LASF101:
	.ascii	"bootm_headers\000"
.LASF129:
	.ascii	"images\000"
.LASF127:
	.ascii	"state\000"
.LASF15:
	.ascii	"long int\000"
.LASF138:
	.ascii	"nr_banks\000"
.LASF20:
	.ascii	"__be32\000"
.LASF192:
	.ascii	"env_t\000"
.LASF113:
	.ascii	"fit_uname_fdt\000"
.LASF145:
	.ascii	"_datarelro_start_ofs\000"
.LASF23:
	.ascii	"ide_bus_offset\000"
.LASF100:
	.ascii	"image_info_t\000"
.LASF163:
	.ascii	"net_dns_server\000"
.LASF177:
	.ascii	"net_our_vlan\000"
.LASF28:
	.ascii	"image_base\000"
.LASF32:
	.ascii	"sector_count\000"
.LASF186:
	.ascii	"NETLOOP_SUCCESS\000"
.LASF174:
	.ascii	"net_rx_packet_len\000"
.LASF126:
	.ascii	"verify\000"
.LASF29:
	.ascii	"_binary_u_boot_bin_start\000"
.LASF106:
	.ascii	"fit_hdr_os\000"
.LASF182:
	.ascii	"net_boot_file_expected_size_in_blocks\000"
.LASF162:
	.ascii	"net_netmask\000"
.LASF196:
	.ascii	"arch/arm/lib/asm-offsets.c\000"
.LASF132:
	.ascii	"load_addr\000"
.LASF43:
	.ascii	"memory\000"
.LASF178:
	.ascii	"net_native_vlan\000"
.LASF146:
	.ascii	"IRQ_STACK_START_IN\000"
.LASF8:
	.ascii	"unsigned int\000"
.LASF89:
	.ascii	"ih_type\000"
.LASF85:
	.ascii	"ih_ep\000"
.LASF65:
	.ascii	"bd_t\000"
.LASF164:
	.ascii	"net_nis_domain\000"
.LASF120:
	.ascii	"ft_addr\000"
.LASF5:
	.ascii	"__u8\000"
.LASF1:
	.ascii	"long unsigned int\000"
.LASF7:
	.ascii	"__u32\000"
.LASF70:
	.ascii	"off_dt_strings\000"
.LASF61:
	.ascii	"bi_busfreq\000"
.LASF110:
	.ascii	"fit_uname_rd\000"
.LASF24:
	.ascii	"name\000"
.LASF86:
	.ascii	"ih_dcrc\000"
.LASF191:
	.ascii	"data\000"
.LASF56:
	.ascii	"bi_bootflags\000"
.LASF31:
	.ascii	"size\000"
.LASF2:
	.ascii	"short unsigned int\000"
.LASF140:
	.ascii	"IRQ_STACK_START\000"
.LASF111:
	.ascii	"fit_noffset_rd\000"
.LASF148:
	.ascii	"s_addr\000"
.LASF122:
	.ascii	"initrd_start\000"
.LASF99:
	.ascii	"arch\000"
.LASF78:
	.ascii	"fdt32_t\000"
.LASF197:
	.ascii	"/home/phoenix/uboot\000"
.LASF103:
	.ascii	"legacy_hdr_os_copy\000"
.LASF37:
	.ascii	"flash_info\000"
.LASF57:
	.ascii	"bi_ip_addr\000"
.LASF93:
	.ascii	"image_info\000"
.LASF58:
	.ascii	"bi_enetaddr\000"
.LASF198:
	.ascii	"net_loop_state\000"
.LASF21:
	.ascii	"errno\000"
.LASF96:
	.ascii	"load\000"
.LASF40:
	.ascii	"base\000"
.LASF76:
	.ascii	"size_dt_struct\000"
.LASF72:
	.ascii	"version\000"
.LASF175:
	.ascii	"net_bcast_ethaddr\000"
.LASF154:
	.ascii	"recv\000"
.LASF115:
	.ascii	"fit_hdr_setup\000"
.LASF13:
	.ascii	"sizetype\000"
.LASF116:
	.ascii	"fit_uname_setup\000"
.LASF134:
	.ascii	"save_size\000"
.LASF166:
	.ascii	"net_root_path\000"
.LASF87:
	.ascii	"ih_os\000"
.LASF133:
	.ascii	"save_addr\000"
.LASF53:
	.ascii	"bi_arm_freq\000"
.LASF153:
	.ascii	"send\000"
.LASF69:
	.ascii	"off_dt_struct\000"
.LASF190:
	.ascii	"environment_s\000"
.LASF45:
	.ascii	"bd_info\000"
.LASF16:
	.ascii	"ushort\000"
.LASF194:
	.ascii	"env_ptr\000"
.LASF92:
	.ascii	"image_header_t\000"
.LASF128:
	.ascii	"bootm_headers_t\000"
.LASF44:
	.ascii	"reserved\000"
.LASF4:
	.ascii	"uchar\000"
.LASF75:
	.ascii	"size_dt_strings\000"
.LASF159:
	.ascii	"priv\000"
.LASF112:
	.ascii	"fit_hdr_fdt\000"
.LASF22:
	.ascii	"___strtok\000"
.LASF48:
	.ascii	"bi_flashstart\000"
.LASF181:
	.ascii	"net_boot_file_size\000"
.LASF94:
	.ascii	"image_start\000"
.LASF41:
	.ascii	"lmb_region\000"
.LASF188:
	.ascii	"net_state\000"
.LASF90:
	.ascii	"ih_comp\000"
.LASF121:
	.ascii	"ft_len\000"
.LASF160:
	.ascii	"eth_current\000"
.LASF64:
	.ascii	"bi_dram\000"
.LASF27:
	.ascii	"_Bool\000"
.LASF151:
	.ascii	"iobase\000"
.LASF0:
	.ascii	"unsigned char\000"
.LASF83:
	.ascii	"ih_size\000"
.LASF170:
	.ascii	"net_server_ip\000"
.LASF118:
	.ascii	"rd_start\000"
.LASF136:
	.ascii	"node\000"
.LASF169:
	.ascii	"net_ip\000"
.LASF71:
	.ascii	"off_mem_rsvmap\000"
.LASF6:
	.ascii	"short int\000"
.LASF67:
	.ascii	"magic\000"
.LASF52:
	.ascii	"bi_sramsize\000"
.LASF119:
	.ascii	"rd_end\000"
.LASF104:
	.ascii	"legacy_hdr_valid\000"
.LASF156:
	.ascii	"write_hwaddr\000"
.LASF117:
	.ascii	"fit_noffset_setup\000"
.LASF173:
	.ascii	"net_rx_packet\000"
.LASF131:
	.ascii	"__dtb_dt_begin\000"
.LASF54:
	.ascii	"bi_dsp_freq\000"
.LASF130:
	.ascii	"monitor_flash_len\000"
.LASF168:
	.ascii	"net_server_ethaddr\000"
.LASF19:
	.ascii	"uint32_t\000"
.LASF143:
	.ascii	"_datarelrolocal_start_ofs\000"
.LASF142:
	.ascii	"_datarel_start_ofs\000"
.LASF38:
	.ascii	"long double\000"
.LASF14:
	.ascii	"char\000"
.LASF114:
	.ascii	"fit_noffset_fdt\000"
.LASF49:
	.ascii	"bi_flashsize\000"
.LASF79:
	.ascii	"image_header\000"
.LASF158:
	.ascii	"index\000"
.LASF193:
	.ascii	"default_environment\000"
.LASF11:
	.ascii	"phys_addr_t\000"
.LASF51:
	.ascii	"bi_sramstart\000"
.LASF137:
	.ascii	"meminfo\000"
.LASF95:
	.ascii	"image_len\000"
.LASF33:
	.ascii	"flash_id\000"
.LASF82:
	.ascii	"ih_time\000"
.LASF66:
	.ascii	"fdt_header\000"
.LASF167:
	.ascii	"net_ethaddr\000"
.LASF139:
	.ascii	"bank\000"
.LASF77:
	.ascii	"working_fdt\000"
.LASF59:
	.ascii	"bi_ethspeed\000"
.LASF195:
	.ascii	"GNU C11 6.3.0 -marm -mno-thumb-interwork -mabi=aapc"
	.ascii	"s-linux -mword-relocations -mno-unaligned-access -m"
	.ascii	"float-abi=soft -march=armv7-a -mtls-dialect=gnu -g "
	.ascii	"-Os -fno-builtin -ffreestanding -fno-stack-protecto"
	.ascii	"r -fno-delete-null-pointer-checks -fstack-usage -fn"
	.ascii	"o-pic -ffunction-sections -fdata-sections -fno-comm"
	.ascii	"on -ffixed-r9\000"
.LASF42:
	.ascii	"region\000"
.LASF179:
	.ascii	"net_restart_wrap\000"
.LASF184:
	.ascii	"NETLOOP_CONTINUE\000"
.LASF26:
	.ascii	"block_drvr\000"
.LASF60:
	.ascii	"bi_intfreq\000"
.LASF125:
	.ascii	"cmdline_end\000"
.LASF12:
	.ascii	"phys_size_t\000"
.LASF36:
	.ascii	"flash_info_t\000"
.LASF180:
	.ascii	"net_boot_file_name\000"
.LASF81:
	.ascii	"ih_hcrc\000"
.LASF189:
	.ascii	"env_name_spec\000"
.LASF18:
	.ascii	"uint8_t\000"
.LASF109:
	.ascii	"fit_hdr_rd\000"
.LASF74:
	.ascii	"boot_cpuid_phys\000"
.LASF35:
	.ascii	"protect\000"
.LASF183:
	.ascii	"net_ping_ip\000"
.LASF172:
	.ascii	"net_rx_packets\000"
.LASF155:
	.ascii	"halt\000"
.LASF91:
	.ascii	"ih_name\000"
.LASF55:
	.ascii	"bi_ddr_freq\000"
.LASF149:
	.ascii	"eth_device\000"
.LASF46:
	.ascii	"bi_memstart\000"
.LASF34:
	.ascii	"start\000"
.LASF199:
	.ascii	"main\000"
.LASF135:
	.ascii	"__machine_arch_type\000"
.LASF30:
	.ascii	"_binary_u_boot_bin_end\000"
.LASF88:
	.ascii	"ih_arch\000"
.LASF50:
	.ascii	"bi_flashoffset\000"
.LASF144:
	.ascii	"_datarellocal_start_ofs\000"
.LASF171:
	.ascii	"net_tx_packet\000"
.LASF124:
	.ascii	"cmdline_start\000"
.LASF147:
	.ascii	"in_addr\000"
	.ident	"GCC: (HC&C V100R002C00B032_20190114) 6.3.0"
	.section	.note.GNU-stack,"",%progbits
