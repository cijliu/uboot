/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef __MIPI_TX_HAL_H__
#define __MIPI_TX_HAL_H__

#include "hi_mipi_tx.h"

void mipi_tx_drv_set_phy_cfg(combo_dev_cfg_t *dev_cfg);
void mipi_tx_drv_set_controller_cfg(combo_dev_cfg_t *dev_cfg);

void mipi_tx_drv_set_cmd_info(cmd_info_t *cmd_info);

void mipi_tx_drv_enable_input(output_mode_t output_mode);

int mipi_tx_drv_init(void);
void mipi_tx_drv_exit(void);

#endif
