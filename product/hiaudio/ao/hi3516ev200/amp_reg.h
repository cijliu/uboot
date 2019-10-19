/*
 * Copyright (c) 2019 HiSilicon Technologies Co., Ltd.
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

#ifndef __AMP_REG_H__
#define __AMP_REG_H__

#define GPIO_REGS_ADDR            (0x120b0000)
#define IOCFG_CORE_REGS_ADDR      (0x120c0000)

// 16ev200demo,16ev300demo
#define IOCFG_AHB_GPIO1_0_ADDR    (0x0000 + IOCFG_CORE_REGS_ADDR)

// 18ev300demo
#define IOCFG_AHB_GPIO1_5_ADDR    (0x0014 + IOCFG_CORE_REGS_ADDR)

#endif

