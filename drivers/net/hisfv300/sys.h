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

#ifndef __HISILICON_ETHV100_SYS_H
#define __HISILICON_ETHV100_SYS_H

void hieth_sys_init(void);
void hieth_sys_exit(void);

void hieth_set_crg_phy_mode(unsigned char is_rmii_mode);
void set_inner_phy_addr(u32 phyaddr);
void set_efuse_unread(void);

void hieth_sys_startup(void);
void hieth_sys_allstop(void);

void set_phy_valtage(void);
#endif
