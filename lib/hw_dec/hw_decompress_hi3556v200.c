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

#include <asm/io.h>
#include <config.h>

#define PERI_CRG100 0x190

#define GZIP_OFFSET PERI_CRG100
#define GZIP_CLKEN (0x7<<0)

#ifndef GZIP_REG_BASE
#define GZIP_REG_BASE   0x11200000
#endif

#define HW_DEC_REG_BASE_ADDR  (GZIP_REG_BASE)

static void disable_decompress_clock(void)
{
    unsigned int regval;

    regval = readl(CRG_REG_BASE + GZIP_OFFSET);
    regval &= ~GZIP_CLKEN;
    writel(regval, CRG_REG_BASE + GZIP_OFFSET);
}

static void enable_decompress_clock(void)
{
    unsigned int regval;

    regval = readl(CRG_REG_BASE + GZIP_OFFSET);
    regval |= GZIP_CLKEN;
    writel(regval, CRG_REG_BASE + GZIP_OFFSET);
}
