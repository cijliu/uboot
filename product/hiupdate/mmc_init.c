/*
* Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
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


static int mmc_stor_init(void)
{
    struct mmc *mmc;
    int dev_num = 0;
#ifdef CONFIG_EMMC
    extern int target_dev;
    dev_num = target_dev;
#else
    dev_num = 0;
#endif
    mmc = find_mmc_device(dev_num);
    if (mmc == NULL) {
        printf("No mmc driver found!\n");
        return -1;
    }

    if (((unsigned long)mmc->block_dev.vendor[0] == 0)
            || ((unsigned long)mmc->block_dev.product[0] == 0)) {
        printf("*No SD card found!\n");
        return -1;
    }

    return 0;
}

static void mmc_stor_exit(void)
{
}
