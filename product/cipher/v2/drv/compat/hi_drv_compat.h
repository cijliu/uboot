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

#ifndef _HI_DRV_CPMPAT_H_
#define _HI_DRV_CPMPAT_H_

s32 hi_drv_compat_init(void);
s32 hi_drv_compat_deinit(void);
s32 klad_load_hard_key(u32 handle, u32 catype, u8 *key);
s32 klad_encrypt_key(u32 keysel, u32 target, u32 clear[4], u32 encrypt[4]);

#endif

