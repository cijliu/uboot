/**
 * cmd_entry.S
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 */

.section .text
.type _start, %function
.globl _start
_start:
	stp     x29, x30, [sp, #-16]!
	stp     x27, x28, [sp, #-16]!
	stp     x25, x26, [sp, #-16]!
	stp     x23, x24, [sp, #-16]!
	stp     x21, x22, [sp, #-16]!
	stp     x19, x20, [sp, #-16]!
	stp     x17, x18, [sp, #-16]!
	stp     x15, x16, [sp, #-16]!
	stp     x13, x14, [sp, #-16]!
	stp     x11, x12, [sp, #-16]!
	stp     x9, x10, [sp, #-16]!
	stp     x7, x8, [sp, #-16]!
	stp     x5, x6, [sp, #-16]!
	stp     x3, x4, [sp, #-16]!
	stp     x1, x2, [sp, #-16]!

	b	real_start

_STACK_POINT:
	.quad STACK_POINT

.globl _bss_start
_bss_start: .quad __bss_start
.globl _bss_end
_bss_end:   .quad _end

_real_start:
	.quad real_start
real_start:
	ldr	x3, _bss_start
	ldr	x1, _bss_end
	mov	x2, #0x00000000

clear_bss_loop:
	str	x2, [x3]
	cmp	x3, x1
	add	x3, x3, #4
	bne	clear_bss_loop

	ldr	x4, =_x30
	str	x30, [x4]          /* x30 is lr, save lr */

	ldp     x1, x2, [sp],#16
	ldp     x3, x4, [sp],#16
	ldp     x5, x6, [sp],#16
	ldp     x7, x8, [sp],#16
	ldp     x9, x10, [sp],#16
	ldp     x11, x12, [sp],#16
	ldp     x13, x14, [sp],#16
	ldp     x15, x16, [sp],#16
	ldp     x17, x18, [sp],#16
	ldp     x19, x20, [sp],#16
	ldp     x21, x22, [sp],#16
	ldp     x23, x24, [sp],#16
	ldp     x25, x26, [sp],#16
	ldp     x27, x28, [sp],#16
	ldp     x29, x30, [sp],#16

	ldr	x30, =_sp
	mov     x29, sp
	str     x29, [x30]    /* save sp */
	ldr	x29, _STACK_POINT
	mov	sp, x29

	bl	ddr_training_cmd_entry

	ldr	x30, =_sp   /* restore sp */
	ldr	x28, [x30]
	mov	sp, x28

	ldr	x28, =_x30
	ldr	x30, [x28]  /* restore lr */
	ret

.section .data
_x30:	.quad 0
_sp:	.quad 0
