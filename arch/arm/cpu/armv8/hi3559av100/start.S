/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:    GPL-2.0+
 */

#include <asm-offsets.h>
#include <config.h>
#include <linux/linkage.h>
#include <asm/macro.h>
#include <asm/armv8/mmu.h>

/*************************************************************************
 *
 * Startup Code (reset vector)
 *
 *************************************************************************/
/*
 * Branch according to exception level
 */
.macro	switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, 0xc
	b.eq	\el3_label
	cmp	\xreg, 0x8
	b.eq	\el2_label
	cmp	\xreg, 0x4
	b.eq	\el1_label
.endm

/*
 * Enter Exception.
 * This will save the processor state that is ELR/X0~X30
 * to the stack frame.
 */
.macro	exception_entry
	stp	x29, x30, [sp, #-16]!
	stp	x27, x28, [sp, #-16]!
	stp	x25, x26, [sp, #-16]!
	stp	x23, x24, [sp, #-16]!
	stp	x21, x22, [sp, #-16]!
	stp	x19, x20, [sp, #-16]!
	stp	x17, x18, [sp, #-16]!
	stp	x15, x16, [sp, #-16]!
	stp	x13, x14, [sp, #-16]!
	stp	x11, x12, [sp, #-16]!
	stp	x9, x10, [sp, #-16]!
	stp	x7, x8, [sp, #-16]!
	stp	x5, x6, [sp, #-16]!
	stp	x3, x4, [sp, #-16]!
	stp	x1, x2, [sp, #-16]!

	/* Could be running at EL3/EL2/EL1 */
	switch_el x11, 3f, 2f, 1f
3:	mrs	x1, esr_el3
	mrs	x2, elr_el3
	b	0f
2:	mrs	x1, esr_el2
	mrs	x2, elr_el2
	b	0f
1:	mrs	x1, esr_el1
	mrs	x2, elr_el1
0:
	stp	x2, x0, [sp, #-16]!
	mov	x0, sp
.endm

.globl _start
_start:
    b reset

.balignl 64,0xdeadbeef
__blank_zone_start:
.fill 1024*10,1,0
__blank_zone_end:

.globl _blank_zone_start
_blank_zone_start:
.quad __blank_zone_start

.globl _blank_zone_end
_blank_zone_end:
.quad __blank_zone_end
.balignl 16,0xdeadbeef

.align 3

.globl _TEXT_BASE
_TEXT_BASE:
    .quad TEXT_BASE

/*
 * These are defined in the linker script.
 */
.globl _end_ofs
_end_ofs:
    .quad _end - _start

.globl _bss_start_ofs
_bss_start_ofs:
    .quad __bss_start - _start

.globl _bss_end_ofs
_bss_end_ofs:
    .quad __bss_end - _start

reset:
    /*
     * Could be EL3/EL2/EL1, Initial State:
     * Little Endian, MMU Disabled, i/dCache Disabled
     */
    adr    x0, vectors
    switch_el x1, 3f, 2f, 1f
3:  msr    vbar_el3, x0
    mrs    x0, scr_el3
    orr    x0, x0, #0xf             /* SCR_EL3.NS|IRQ|FIQ|EA */
    msr    scr_el3, x0
    msr    cptr_el3, xzr            /* Enable FP/SIMD */
#ifdef COUNTER_FREQUENCY
    ldr    x0, =COUNTER_FREQUENCY
    msr    cntfrq_el0, x0           /* Initialize CNTFRQ */
#endif
    b      0f
2:  msr    vbar_el2, x0
    mov    x0, #0x33ff
    msr    cptr_el2, x0             /* Enable FP/SIMD */
    b      0f
1:  msr    vbar_el1, x0
    mov    x0, #3 << 20
    msr    cpacr_el1, x0            /* Enable FP/SIMD */
0:

    /*
     * Cache/BPB/TLB Invalidate
     * i-cache is invalidated before enabled in icache_enable()
     * tlb is invalidated before mmu is enabled in dcache_enable()
     * d-cache is invalidated before enabled in dcache_enable()
     */

    /*
     *  read system register REG_SC_GEN2
     *  check if ziju flag
     */
    ldr    x0, =SYS_CTRL_REG_BASE
    ldr    w1, [x0, #REG_SC_GEN2]
    ldr    w2, =0x7a696a75         /* magic for "ziju" */
    cmp    w1, w2
    bne    normal_start_flow
    mov    x1, sp                  /* save sp */
    str    w1, [x0, #REG_SC_GEN2]  /* clear ziju flag */

ziju_flow:
    ldr    x2, =(STACK_TRAINING)
    bic    sp, x2, #0xf            /* 16-byte alignment for ABI compliance */
    ldr    x0, _blank_zone_start
    ldr    x1, _TEXT_BASE
    sub    x0, x0, x1
    adr    x1, _start
    add    x0, x0, x1
    mov    x1, #0x0                /* flags: 0->normal 1->pm */
    bl     init_registers          /* init PLL/DDRC/... */
    bl	   start_ddr_training      /* DDR training */

    ldr    x0, =SYS_CTRL_REG_BASE
    ldr    w1, [x0, #REG_SYSSTAT]
    lsr    w1, w1, #8
    and    w1, w1, #0x1
    cmp    w1, #1
    beq    pcie_slave_boot

return_to_bootrom:
    ldr    w1, [x0, #REG_SC_GEN2]
    mov    sp, x1                  /* restore sp */
    ldr    w1, [x0, #REG_SC_GEN3]
    mov    x30, x1
    ret                            /* return to bootrom */

pcie_slave_boot:
    ldr    w1, [x0, #REG_PERISTAT]
    and    w1, w1, #0x1
    cmp    w1, #1
    beq    return_to_bootrom        /* pcie secure boot*/

    ldr w1, =DDR_INIT_EXCUTE_OK_FLAG/* ddr init complete flag */
    str w1, [x0,#PCIE_SLAVE_BOOT_CTL_REG]

pcie_slave_hold:
    ldr x0, =SYS_CTRL_REG_BASE
    ldr w0, [x0, #PCIE_SLAVE_BOOT_CTL_REG]
    ldr w1, =UBOOT_DOWNLOAD_OK_FLAG/* uboot download complete flag */
    cmp w0, w1
    bne pcie_slave_hold
    ldr x30,=0x41000000
    ret

normal_start_flow:
    /* set stack for C code  */
    ldr    x0, =(CONFIG_SYS_INIT_SP_ADDR)
    bic    sp, x0, #0xf            /* 16-byte alignment for ABI compliance */

    bl      uart_early_init
    adr     x0, Str_SystemSartup
    bl      uart_early_puts
    /* enable I-Cache  */
    bl     icache_enable

running_addr_check:
    adr    x0,running_addr_check
    lsr    x0, x0, #28
    cmp    x0, #4
    bge    not_ddr_init

    /* read init table and config registers */
    ldr    x0, _blank_zone_start
    ldr    x1, _TEXT_BASE
    sub    x0, x0, x1
    adr    x1, _start
    add    x0, x0, x1
    mov    x1, #0                  /* flags: 0->normal 1->pm */
    bl     init_registers
    bl	   start_ddr_training
check_boot_mode:
    ldr    x0, =SYS_CTRL_REG_BASE
    ldr    w0, [x0, #REG_SYSSTAT]
    lsr    w6, w0, #4
    and    w6, w6, #0x3
    cmp    w6, #BOOT_FROM_EMMC
    bne    ufs_boot

#ifdef CONFIG_SDHCI
emmc_boot:
    ldr    x0, _TEXT_BASE
    ldr    x1, =__image_copy_start  /* x1 <- SRC &__image_copy_start */
    ldr    x2, =__bss_start         /* x2 <- SRC &__bss_start */
    sub    x1, x2, x1
    bl     emmc_boot_read
    b      jump_to_ddr
#endif

ufs_boot:
    cmp    w6, #BOOT_FROM_UFS
    bne    not_ddr_init
#ifdef CONFIG_UFS
    ldr    x0, _TEXT_BASE
    ldr    x1, =__image_copy_start    /* x1 <- SRC &__image_copy_start */
    ldr    x2, =__bss_start           /* x2 <- SRC &__bss_start*/
    sub    x1, x2, x1
    bl     ufs_boot_read
    b      jump_to_ddr
#endif

not_ddr_init:
master_cpu:
relocate:
    adr    x0, _start                 /*runing addr start*/
    ldr    x1, =__image_copy_start    /* x1 <- SRC &__image_copy_start */
    ldr    x2, =__bss_start           /* x2 <- SRC &__bss_start*/
    subs    x2, x2, x1
    b.eq   no_copy                    /* skip relocation */
    ldr    x1, _TEXT_BASE
    add    x2, x2, x1

copy_loop:
    ldp   x10, x11, [x0], #16        /* copy from source address [x0] */
    stp   x10, x11, [x1], #16        /* copy to   target address [x1] */
    cmp   x1, x2                     /* until source end address [x2] */
    b.lo  copy_loop
no_copy:
clear_remap:
    ldr    x1, =SYS_CTRL_REG_BASE
    ldr    w0, [x1]
    orr    w0, w0, #0x100
    str    w0, [x1]
jump_to_ddr:
    adr    x0, _start_armboot
    ldr    x30,[x0]
    ret
.align 3
_start_armboot: .quad start_armboot

/*-----------------------------------------------------------------------*/

/*
 * Exception vectors.
 */
	.align	3
	.globl	vectors
vectors:
	.align	3
	b	_do_bad_sync	/* Current EL Synchronous Thread */

	.align	3
	b	_do_bad_irq	/* Current EL IRQ Thread */

	.align	3
	b	_do_bad_fiq	/* Current EL FIQ Thread */

	.align	3
	b	_do_bad_error	/* Current EL Error Thread */

	.align	3
	b	_do_sync	/* Current EL Synchronous Handler */

	.align	3
	b	_do_irq		/* Current EL IRQ Handler */

	.align	3
	b	_do_fiq		/* Current EL FIQ Handler */

	.align	3
	b	_do_error	/* Current EL Error Handler */


_do_bad_sync:
	exception_entry
	bl	do_bad_sync
	b	exception_exit

_do_bad_irq:
	exception_entry
	bl	do_bad_irq
	b	exception_exit

_do_bad_fiq:
	exception_entry
	bl	do_bad_fiq
	b	exception_exit

_do_bad_error:
	exception_entry
	bl	do_bad_error
	b	exception_exit

_do_sync:
	exception_entry
	bl	do_sync
	b	exception_exit

_do_irq:
	exception_entry
	bl	do_irq
	b	exception_exit

_do_fiq:
	exception_entry
	bl	do_fiq
	b	exception_exit

_do_error:
	exception_entry
	bl	do_error
	b	exception_exit

exception_exit:
	ldp	x2, x0, [sp],#16
	switch_el x11, 3f, 2f, 1f
3:	msr	elr_el3, x2
	b	0f
2:	msr	elr_el2, x2
	b	0f
1:	msr	elr_el1, x2
0:
	ldp	x1, x2, [sp],#16
	ldp	x3, x4, [sp],#16
	ldp	x5, x6, [sp],#16
	ldp	x7, x8, [sp],#16
	ldp	x9, x10, [sp],#16
	ldp	x11, x12, [sp],#16
	ldp	x13, x14, [sp],#16
	ldp	x15, x16, [sp],#16
	ldp	x17, x18, [sp],#16
	ldp	x19, x20, [sp],#16
	ldp	x21, x22, [sp],#16
	ldp	x23, x24, [sp],#16
	ldp	x25, x26, [sp],#16
	ldp	x27, x28, [sp],#16
	ldp	x29, x30, [sp],#16
	eret

/*
 * void __asm_invalidate_icache_all(void)
 *
 * invalidate all tlb entries.
 */
ENTRY(__asm_invalidate_icache_all)
	ic	ialluis
	isb	sy
	ret
ENDPROC(__asm_invalidate_icache_all)

.align  3
Str_SystemSartup:
.ascii "\r\n\r\nSystem startup\r\n\0"
