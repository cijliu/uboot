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

#include <linux/linkage.h>

ENTRY(memcpy_32)
memcpy:
	push {r3 - r10}
    cmp     r0, r1
    beq		copy_done
    add     r2, r0, r2
memcpy_loop:
    ldmia   r1!, {r3 - r10}
    stmia   r0!, {r3 - r10}
    cmp     r0, r2
    ble     memcpy_loop
copy_done:
	pop {r3 - r10}
    mov     pc, lr
ENDPROC(memcpy_32)
