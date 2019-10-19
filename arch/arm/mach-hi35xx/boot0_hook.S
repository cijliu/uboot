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

HI35XX_BOOT0_HOOK

    .globl _blank_zone_start
_blank_zone_start:  .word __blank_zone_start
ENTRY(get_blank_start)
	ldr r0, _blank_zone_start
	ldr r1, =__image_copy_start
	sub r0, r0, r1
	adrl r1, _start
	add r0, r0, r1
	mov pc, lr
ENDPROC(get_blank_start)

ENTRY(get_code_start)
	adrl r0, _start
	mov pc, lr
ENDPROC(get_code_start)
