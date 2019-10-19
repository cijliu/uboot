/*
* Copyright (c) 2017 HiSilicon Technologies Co., Ltd.
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
static int usb_stor_init(void)
{
    int ret = -1;

try_again:
    if (usb_stop() < 0) {
        debug("usb_stop failed\n");
        return ret;
    }

    mdelay(1000);
    ret = usb_init();
    if (ret == -3) {
        goto try_again;
    }

    if (ret < 0) {
        debug("usb_init failed!\n");
        return ret;
    }

    /*
     * check whether a storage device is attached (assume that it's
     * a USB memory stick, since nothing else should be attached).
     */
    ret = usb_stor_scan(0);
    if (-1 == ret) {
        debug("No USB device found. Not initialized!\n");
    }

    return ret;
}

static void usb_stor_exit(void)
{
    usb_stop();
}

