/*
 * Copyright (c) 2017 HiSilicon Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <asm/arch-hi3559av100/platform.h>
#include <dm.h>
#include "../../usb/host/xhci.h"

#define SYS_STAT	0x8c
#define PCIE_USB3_MODE		(0x3<<0)
#define PCIE_X2				0x0

#define USB_PORT0   0x38
#define P0_U3_PORT_DISABLE  (0x1<<3)
#define USB_PORT1   0x3c
#define P1_U3_PORT_DISABLE  (0x1<<3)

static long base = 0;

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	if (index == 0)
		base = USB3_CTRL_REG_BASE;
	if (index == 1)
		base = USB3_CTRL_REG_BASE_1;

	*hccr = (struct xhci_hccr *)(base);
	*hcor = (struct xhci_hcor *)((long) *hccr
			+ HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void usb3_eye_config(void)
{
	int reg;

	/* Port0 usb2 phy0 misc ctrl */
	reg = readl(MISC_REG_BASE + USB2_PHY0_CTRL);
	reg &= ~(0xf << 4);
	reg |= USB2_PHY_VREF;	/* [7:4] -> (eye vref = 4%) */
	reg |= USB2_PHY_PRE;	/* [13:12] -> (pre electric = 3x) */
	writel(reg, MISC_REG_BASE + USB2_PHY0_CTRL);
	udelay(50);

	/* Port1 usb2 phy1 misc ctrl */
	reg = readl(MISC_REG_BASE + USB2_PHY1_CTRL);
	reg &= ~(0xf << 4);
	reg |= USB2_PHY_VREF;	/* [7:4] -> (eye vref = 4%) */
	reg |= USB2_PHY_PRE;	/* [13:12] -> (pre electric = 3x) */
	writel(reg, MISC_REG_BASE + USB2_PHY1_CTRL);
	udelay(50);

	/* Port0 TX swing comp => 0x1101 */
	writel(P0_TX_SWING_COMP_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_SWING_COMP_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_SWING_COMP_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(50);

	/* Port0 termination trim => 0x0000 */
	writel(P0_TX_TERMINATION_TRIM_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_TERMINATION_TRIM_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_TERMINATION_TRIM_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(50);

	/* Port1 TX swing comp => 0x1101 */
	writel(P1_TX_SWING_COMP_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_SWING_COMP_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_SWING_COMP_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(50);

	/* Port1 termination trim => 0x0000 */
	writel(P1_TX_TERMINATION_TRIM_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_TERMINATION_TRIM_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_TERMINATION_TRIM_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(50);
}

void phy_hiusb_init(int index)
{
	unsigned long flags, usb2_offset, usb3_offset;
	unsigned int reg, cbp_mode;

	local_irq_save(flags);

	if (index == 0){
		base = USB3_CTRL_REG_BASE;
		usb2_offset = 1;
		usb3_offset = 16;
	}
	if (index == 1){
		base = USB3_CTRL_REG_BASE_1;
		usb2_offset = 0;
		usb3_offset = 0;
	}

	/*judgement pcie usb3 mode*/
	cbp_mode = readl(SYS_CTRL_REG_BASE + SYS_STAT);
	cbp_mode = cbp_mode >> 12;
	cbp_mode &= PCIE_USB3_MODE;

	/*USB3 VCC reset*/
	reg = readl(USB3_CTRL_CFG);
	reg |= (USB3_VCC_SRST_REQ << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(500);

	/*combphy reset */
	reg = readl(USB3_COMBPHY_CFG);
	reg |= (COMBPHY_SRST_REQ >> usb3_offset);
	writel(reg, USB3_COMBPHY_CFG);
	udelay(100);

	/*disable port0 ss*/
	reg = readl(MISC_REG_BASE + USB_PORT0);
	reg |= P0_U3_PORT_DISABLE;
	writel(reg, MISC_REG_BASE + USB_PORT0);
	/*disable port1 ss*/
	reg = readl(MISC_REG_BASE + USB_PORT1);
	reg |= P1_U3_PORT_DISABLE;
	writel(reg, MISC_REG_BASE + USB_PORT1);

	/*release TPOR default release*/
	reg = readl(USB2_PHY_CFG);
	reg &= ~(USB2_PHY_PORT_TREQ << usb2_offset);
	writel(reg, USB2_PHY_CFG);
	udelay(200);

	/*utmi clock sel*/
	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB3_UTMI_CKSEL << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(200);

	/*open phy ref clk default open*/
	reg = readl(USB2_PHY_CFG);
	reg |= (USB2_PHY_CKEN << usb2_offset);
	writel(reg, USB2_PHY_CFG);
	udelay(200);

	/*U2 phy reset release*/
	reg = readl(USB2_PHY_CFG);
	reg &= ~(USB2_PHY_REQ << usb2_offset);
	writel(reg, USB2_PHY_CFG);
	udelay(200);

	/*usb3 occ pclk sel*/
	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB3_PCLK_OCC_SEL << usb3_offset);
	writel(reg, USB3_CTRL_CFG);

	/*in pcie X2 mode, config USB3_1 PCLK*/
	if (cbp_mode == PCIE_X2) {
		reg = readl(USB3_CTRL_CFG);
		reg |= USB3_PCLK_OCC_SEL;
		writel(reg, USB3_CTRL_CFG);
	}

	/*open ref CKEN*/
	reg = readl(USB3_COMBPHY_CFG);
	reg |= (COMBPHY_REF_CKEN >> usb3_offset);
	writel(reg, USB3_COMBPHY_CFG);
	udelay(100);

	/*U3 PHY reset release*/
	reg = readl(USB3_COMBPHY_CFG);
	reg &= ~(COMBPHY_SRST_REQ >> usb3_offset);
	writel(reg, USB3_COMBPHY_CFG);
	udelay(100);

	/*config U3 Controller USB3_0 PHY OUTPUT*/
	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB3_VCC_SRST_REQ << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(500);

	reg = readl(base + REG_GUSB3PIPECTL0);
	reg |= PCS_SSP_SOFT_RESET;
	writel(reg, base + REG_GUSB3PIPECTL0);
	udelay(200);
	reg = readl(base + REG_GCTL);
	reg &= ~(0x3<<12);
	reg |= (0x1<<12); /*[13:12] 01: Host; 10: Device; 11: OTG*/
	writel(reg, base + REG_GCTL);
	udelay(20);

	reg = readl(base + REG_GUSB3PIPECTL0);
	reg &= ~PCS_SSP_SOFT_RESET;
	reg &= ~(1<<17);       /* disable suspend */
	writel(reg, base + REG_GUSB3PIPECTL0);
	udelay(20);

	reg &= CLEAN_USB3_GTXTHRCFG;
	reg |= USB_TXPKT_CNT_SEL;
	reg |= USB_TXPKT_CNT;
	reg |= USB_MAXTX_BURST_SIZE;
	writel(reg, base + GTXTHRCFG);
	udelay(20);
	writel(reg, base + GRXTHRCFG);
	udelay(20);

	usb3_eye_config();

	local_irq_restore(flags);
}

void xhci_hcd_stop(int index)
{
	unsigned long usb3_offset;
	unsigned int reg;

	if (index == 0){
		usb3_offset = 16;
	}
	if (index == 1){
		usb3_offset = 0;
	}

	reg = readl(USB3_COMBPHY_CFG);
	reg &= ~(COMBPHY_SRST_REQ >> usb3_offset);
	writel(reg, USB3_COMBPHY_CFG);
	udelay(100);

	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB3_VCC_SRST_REQ << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(500);
}
