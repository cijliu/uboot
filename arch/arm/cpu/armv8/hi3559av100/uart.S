/*
 * Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General Public License as published by the
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


#include <config.h>

//******************************************************************************
//
//  void uart_early_init(void);
//
.text
.align	4
.global	uart_early_init
.type	uart_early_init, %function
uart_early_init:
	ldr	x4, io_base_addr_L0
	ldr	w3, =0x1D01
	str	w3, [x4, #0XD4]
	ldr	w3, =0x0401
	str	w3, [x4, #0XD8]

    ldr	x4, uart_base_addr_L0
	mov	w3, #0
	/* Disable UART */
	str	w3, [x4, #48]
	/* Set baud rate to 115200, uart clock:24M */
	add	w3, w3, #13
	str	w3, [x4, #36]
	mov	w3, #1
	str	w3, [x4, #40]
	/* Set the UART to be 8 bits, 1 stop bit, no parity, fifo enabled. */
	ldr	w3, =112
	str	w3, [x4, #44]
	/* Enable UART */
	ldr	w3, =769
	str	w3, [x4, #48]
	ret
.align	4
uart_base_addr_L0:
	.quad CONFIG_CUR_UART_BASE
io_base_addr_L0:
	.quad 0x1f000000

//******************************************************************************
//
//  void uart_early_puts(const char *ss);
//
.align	4
.global	uart_early_puts
.type	uart_early_puts, %function
uart_early_puts:
#if !defined(CONFIG_SUPPORT_CA_RELEASE)
	ldr	x2, uart_base_addr_L1
	b	next_char
output:
	ldr	w4, [x2, #24]
	tst	w4, #32
	bne	output
	str	w3, [x2, #0]
	add	x0, x0, #1
next_char:
	ldrb	w3, [x0]
	cmp	w3, #0
	bne	output
#endif /* CONFIG_SUPPORT_CA_RELEASE */
	ret
.align	4
uart_base_addr_L1:
	.quad CONFIG_CUR_UART_BASE

//******************************************************************************
//
//  void uart_early_putc(int chr);
//
//  call example:
//    mov	w0, #'A'
//    bl	uart_early_putc
//
.align	4
.global	uart_early_putc
.type	uart_early_putc, %function
uart_early_putc:
#if !defined(CONFIG_SUPPORT_CA_RELEASE)
	ldr	x2, uart_base_addr_L3
wait3:
	ldr	w4, [x2, #24]
	tst	w4, #32
	bne	wait3
	str	w0, [x2, #0]

#endif /* CONFIG_SUPPORT_CA_RELEASE */
	ret
.align	4
uart_base_addr_L3:
	.quad CONFIG_CUR_UART_BASE
