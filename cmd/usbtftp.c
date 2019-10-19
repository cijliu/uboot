/*
* Copyright (c) 2019 HiSilicon Technologies Co., Ltd.
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
#include "../drivers/usb/gadget/hiudc3/usb3_drv.h"
#include "common.h"

#include <common.h>
#include <malloc.h>
#include <command.h>


static unsigned int usb_open_flag = 0;
static char strCommand[256] = {0};

extern int get_eventbuf_count(usb3_device_t *dev);
extern void dcache_disable(void);
extern void usb3_common_init(usb3_device_t *dev, volatile uint8_t *base);
extern void phy_hiusb_init(int index);
extern void usb3_init(usb3_device_t *dev);
extern void dcache_enable(void);
extern int usb_stop(void);
extern void usb3_handle_event(usb3_device_t *dev);

static int udc_request(void)
{
    dcache_disable();

    usb3_device_t *usb3_dev;
    struct usb_device_descriptor *usb3_dev_desc;

    usb3_dev = (usb3_device_t *)malloc(sizeof(usb3_device_t));
    if (NULL == usb3_dev) {
        debug("usb3_dev: out of memory\n");
        return -ENOMEM;
    }
    usb3_memset((void *)usb3_dev, 0, sizeof(usb3_device_t));
    usb3_dev_desc = (usb_device_descriptor_t *)malloc(sizeof(struct usb_device_descriptor));
    usb3_pcd_t *pcd = &usb3_dev->pcd;
    usb3_pcd_ep_t *ep = &pcd->in_ep;
    usb3_pcd_req_t *req = &ep->req;
    req->bufdma = (uint8_t *)malloc(512);
    usb_info("size of usb3_dev %d\n", sizeof(*usb3_dev));
    usb3_dev->base = (volatile uint8_t *)USB3_CTRL_REG_BASE;

    uint8_t string_manu[]= {'H',0,'i',0,'s',0,'l',0,'i',0,'c',0,'o',0,'n',0};
    uint8_t string_prod[]= {'H',0,'i',0,'U',0,'S',0,'B',0,'B',0,'u',0,'r',0,'n',0};
    usb3_dev->string_manu_len = sizeof(string_manu);
    usb3_dev->string_prod_len = sizeof(string_prod);
    usb3_dev->dev_desc = usb3_dev_desc;
    memcpy(usb3_dev->string_manu, string_manu, usb3_dev->string_manu_len);
    memcpy(usb3_dev->string_prod, string_prod, usb3_dev->string_prod_len);
    usb3_dev->pcd.ep0_setup_desc = (usb3_dma_desc_t *)
                ((phys_addr_t)(usb3_dev->pcd.ep0_setup + 15) & (uint32_t)(~15));
    usb3_dev->pcd.ep0_in_desc = (usb3_dma_desc_t *)
                ((phys_addr_t)(usb3_dev->pcd.ep0_in + 15) & (uint32_t)(~15));
    usb3_dev->pcd.ep0_out_desc = (usb3_dma_desc_t *)
                ((phys_addr_t)(usb3_dev->pcd.ep0_out + 15) & (uint32_t)(~15));
    usb3_dev->pcd.in_ep.ep_desc = (usb3_dma_desc_t *)
                ((phys_addr_t)(usb3_dev->pcd.in_ep.epx_desc + 15) & (uint32_t)(~15));
    usb3_dev->pcd.out_ep.ep_desc = (usb3_dma_desc_t *)
                ((phys_addr_t)(usb3_dev->pcd.out_ep.epx_desc + 15) & (uint32_t)(~15));

    /* Release usb3.0 controller */

    phy_hiusb_init(0);

    /* Get usb3.0 version number */
    usb3_dev->snpsid = usb3_rd32((volatile uint32_t *)
        (usb3_dev->base + USB3_CORE_REG_BASE + USB3_CORE_GSNPSID_REG_OFFSET));

    /* Initialize usb3.0 core */
    usb3_common_init(usb3_dev, usb3_dev->base + USB3_CORE_REG_BASE);

    /* Initialize usb3.0 pcd */
    usb3_init(usb3_dev);

    usb_info("usb init done\n");

    ulong time_start = get_timer(0);

    /* inital the send buffer */
    extern char tx_state[200];
    memset(tx_state, 0, sizeof(tx_state));

    while (usb_open_flag) {
        usb3_handle_event(usb3_dev);
        
        if (0 != get_eventbuf_count(usb3_dev)) {
            time_start = get_timer(0);
            continue;
        } 

        if (get_timer(time_start) > 5000) {
            printf("the USB has no data for about 5s, stop the USB Device\n");
            break;
        }
    }

    usb_open_flag = 0;

    phy_hiusb_init(0);

    usb_stop();

    if (NULL != req->bufdma) {
        free(req->bufdma);
        req->bufdma = NULL;
    }

    if (NULL != usb3_dev_desc) {
        free(usb3_dev_desc);
        usb3_dev_desc = NULL;
    }

    if (NULL != usb3_dev) {
        free(usb3_dev);
        usb3_dev = NULL;
    }

    dcache_enable();

    return 0;
}


static int do_usbtftp(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    if (strncmp(argv[1], "start", 5) == 0) {
        if (0 == usb_open_flag) {
            return CMD_RET_USAGE;
        }

        printf(" %s\n", strCommand);
        return 0;
    }

    if (strncmp(argv[1], "error", 5) == 0) {
        if (0 == usb_open_flag) {
            return CMD_RET_USAGE;
        }

        usb_open_flag = 0;
        memset(strCommand, 0, sizeof(strCommand));
        printf("usbtftp error\n");
        return 0;
    }
    
    if (strncmp(argv[1], "end", 3) == 0) {
        if (0 == usb_open_flag) {
            return CMD_RET_USAGE;
        }
        
        usb_open_flag = 0;
        memset(strCommand, 0, sizeof(strCommand));
        printf("usbtftp end\n");
        return 0;
    }

    if (3 == argc) {
        if ( strlen(argv[1]) + strlen(argv[2]) + 15 >= 256 ) {
            return CMD_RET_USAGE;
        }
        
        char *endp = NULL;
        (void)simple_strtoul(argv[1], &endp, 16);
        if (*argv[1] == 0 || *endp != 0) {
            return CMD_RET_USAGE;
        }

        memset(strCommand, 0, sizeof(strCommand));

        sprintf(strCommand, "usbtftp %s %s", argv[1], argv[2]);    
        usb_open_flag = 1;

        (void)udc_request();

        return 0;
    }


    /* not support now */
    if (4 == argc) {
        return 0;

    }

    return CMD_RET_USAGE;
}

U_BOOT_CMD(
    usbtftp, 4, 0, do_usbtftp,
    "download or upload image using USB protocol",
    "command to download or upload image using USB protocol\n"
    "usbtftp addr file len - request to upload memory content from addr to file\n"
    "usbtftp addr file     - request to doonload file to addr\n"
    "usbtftp start         - start the usbtftp task\n"
    "                        only support when usb is opened\n"
    "usbtftp error         - usbtftp error\n"
    "                        only support when usb is opened\n"
    "usbtftp end           - stop the usbtftp task\n"
    "                        only support when usb is opened\n"
);


