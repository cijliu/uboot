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

#include <asm/arch-hi3559v200/platform.h>
#include <dm.h>
#include "../../usb/host/xhci.h"

/* offset 0x140 */
#define USB2_UTMI_PCTRL			(0x1 << 15)
#define USB2_PHY_TEST_SRST_REQ	(0x1 << 14)
#define USB2_UTMI_CKSEL			(0x1 << 13)
#define USB2_UTMI_CKEN			(0x1 << 12)
#define USB2_REF_CKEN			(0x1 << 9)
#define USB2_BUS_CKEN			(0x1 << 8)
#define USB2_VCC_SRST_REQ		(0x1 << 3)
#define USB2_PHY_CKEN			(0x1 << 2)
#define USB2_PHY_PORT_TREQ		(0x1 << 1)
#define USB2_PHY_REQ			(0x1 << 0)

#define REG_GUSB3PIPECTL0		0xc2c0
#define PCS_SSP_SOFT_RESET		(0x1 << 31)
#define PORT_DISABLE_SUSPEND	(0x1 << 17)

#define REG_GCTL				0xc110
#define PORT_CAP_DIR			(0x3 << 12)
#define PORT_SET_HOST			(0x1 << 12)

#define GTXTHRCFG				0xc108
#define	USB2_G_TXTHRCFG			0x23100000

#define GRXTHRCFG				0xc10c
#define	USB2_G_RXTHRCFG			0x23100000

#define USB2_INNO_PHY_BASE_REG	0x10110000
#define	USB2_PHY_CLK_OUTPUT_REG	0x18
#define	USB2_PHY_CLK_OUTPUT_VAL	0x0c

#define	USB2_VBUS_IO_BASE_REG	0x10ff0000
#define	USB2_VBUS_IO_OFFSET		0x40
#define	USB2_VBUS_IO_VAL		0x431

#define	HS_HIGH_HEIGHT_TUNING_OFFSET	0x8
#define HS_HIGH_HEIGHT_TUNING_MASK	(0x7 << 4)
#define HS_HIGH_HEIGHT_TUNING_VAL	0x5 << 4

#define PRE_EMPHASIS_TUNING_OFFSET	0x0
#define PRE_EMPHASIS_TUNING_MASK	(0x7 << 0)
#define	PRE_EMPHASIS_TUNING_VAL		0x7 << 0

#define PRE_EMPHASIS_STRENGTH_OFFSET	0x14
#define PRE_EMPHASIS_STRENGTH_MASK	(0x7 << 2)
#define PRE_EMPHASIS_STRENGTH_VAL	0x3 << 2

#define HS_SLEW_RATE_TUNING_OFFSET	0x74
#define HS_SLEW_RATE_TUNING_MASK	(0x7 << 1)
#define HS_SLEW_RATE_TUNING_VAL		0x7 << 1

#define DISCONNECT_TRIGGER_OFFSET	0x10
#define DISCONNECT_TRIGGER_MASK		(0xf << 4)
#define DISCONNECT_TRIGGER_VAL		0xd << 4

static long base = 0;

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	base = USB3_CTRL_REG_BASE;

	*hccr = (struct xhci_hccr *)(base);
	*hcor = (struct xhci_hcor *)((long) *hccr
			+ HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void usb2_eye_config(void)
{
	int reg;

	/* HS eye height tuning */
	reg = readl(USB2_INNO_PHY_BASE_REG + HS_HIGH_HEIGHT_TUNING_OFFSET);
	reg &= ~HS_HIGH_HEIGHT_TUNING_MASK;
	reg |= HS_HIGH_HEIGHT_TUNING_VAL;
	writel(reg, USB2_INNO_PHY_BASE_REG + HS_HIGH_HEIGHT_TUNING_OFFSET);

	/* Pre-emphasis tuning */
	reg = readl(USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_TUNING_OFFSET);
	reg &= ~PRE_EMPHASIS_TUNING_MASK;
	reg |= PRE_EMPHASIS_TUNING_VAL;
	writel(reg, USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_TUNING_OFFSET);

	/* Pre-emphasis strength */
	reg = readl(USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_STRENGTH_OFFSET);
	reg &= ~PRE_EMPHASIS_STRENGTH_MASK;
	reg |= PRE_EMPHASIS_STRENGTH_VAL;
	writel(reg, USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_STRENGTH_OFFSET);

	/* HS driver slew rate tunning */
	reg = readl(USB2_INNO_PHY_BASE_REG + HS_SLEW_RATE_TUNING_OFFSET);
	reg &= ~HS_SLEW_RATE_TUNING_MASK;
	reg |= HS_SLEW_RATE_TUNING_VAL;
	writel(reg, USB2_INNO_PHY_BASE_REG + HS_SLEW_RATE_TUNING_OFFSET);

	/* HOST disconnects detection trigger point */
	reg = readl(USB2_INNO_PHY_BASE_REG + DISCONNECT_TRIGGER_OFFSET);
	reg &= ~DISCONNECT_TRIGGER_MASK;
	reg |= DISCONNECT_TRIGGER_VAL;
	writel(reg, USB2_INNO_PHY_BASE_REG + DISCONNECT_TRIGGER_OFFSET);

}

void phy_hiusb_init(int index)
{
	int reg;

	/* usb phy reset */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg |= USB2_PHY_TEST_SRST_REQ;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(100);

	/* cancel usb phy srst */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg &= ~USB2_PHY_TEST_SRST_REQ;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(20);

	/* usb2 vcc reset */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg |= USB2_VCC_SRST_REQ;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(200);

	/* set inno phy output clock */
	writel(USB2_PHY_CLK_OUTPUT_VAL, USB2_INNO_PHY_BASE_REG +
			USB2_PHY_CLK_OUTPUT_REG);
	udelay(10);

	/* TODO:usb2 eye diagram */

	/* open phy ref cken */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg |= USB2_PHY_CKEN;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(10);

	/* open utmi pctrl */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg &= ~USB2_UTMI_PCTRL;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(10);

	/* open utmi cksel */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg &= ~USB2_UTMI_CKSEL;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(10);

	/* open utmi cken */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg |= USB2_UTMI_CKEN;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(10);

	/* open controller ref cken */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg |= USB2_REF_CKEN;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(10);

	/* open bus cken */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg |= USB2_BUS_CKEN;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(200);

	/* cancel POR reset */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg &= ~USB2_PHY_REQ;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(200);

	/* cancel TPOR reset */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg &= ~USB2_PHY_PORT_TREQ;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(200);

	/* cancel vcc reset */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg &= ~USB2_VCC_SRST_REQ;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(200);

	/* usb2 test vbus using gpio */
	writel(USB2_VBUS_IO_VAL, USB2_VBUS_IO_BASE_REG + USB2_VBUS_IO_OFFSET);
	udelay(20);

	/*
	 * USB2 Controller configs
	 */
	reg = readl(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	reg |= PCS_SSP_SOFT_RESET;
	writel(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	udelay(20);

	reg = readl(USB3_CTRL_REG_BASE + REG_GCTL);
	reg &= ~PORT_CAP_DIR;
	reg |= PORT_SET_HOST; /*[13:12] 01: Host; 10: Device; 11: OTG*/
	writel(reg, USB3_CTRL_REG_BASE + REG_GCTL);
	udelay(20);

	reg = readl(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	reg &= ~PCS_SSP_SOFT_RESET;
	reg &= ~PORT_DISABLE_SUSPEND;       //disable suspend
	writel(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	udelay(20);

	writel(USB2_G_TXTHRCFG, USB3_CTRL_REG_BASE + GTXTHRCFG);
	writel(USB2_G_RXTHRCFG, USB3_CTRL_REG_BASE + GRXTHRCFG);
	udelay(20);

	/*
	 * USB2 eye config
	 */
	usb2_eye_config();
}
EXPORT_SYMBOL(phy_hiusb_init);

void xhci_hcd_stop(int index)
{
	int reg;

	/* usb2 vcc reset */
	reg = readl(CRG_REG_BASE + REG_CRG80);
	reg |= USB2_VCC_SRST_REQ;
	writel(reg, CRG_REG_BASE + REG_CRG80);
	udelay(200);
}
EXPORT_SYMBOL(xhci_hcd_stop);
