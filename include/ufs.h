#ifndef __UFS_H__
#define __UFS_H__

#include <common.h>
#include <linux/io.h>

typedef u32 ULONG;
typedef u16 USHORT;
typedef u8 UCHAR;
typedef u32 BOOL;
typedef u32 UINT;
typedef signed int s32;

#define UFS_DEBUG
/*#define UFS_MEM_DEBUG*/

/*#define UFS_FPGA */
#define COMBO_PHY_V120

/*-----------------------------------------------------------------
 * FMC register
------------------------------------------------------------------ */
#define FMC_MEM_CTRL		0x100000b4

/*-----------------------------------------------------------------
 *serial base address and clock
------------------------------------------------------------------ */

#ifndef UFS_FPGA
#define REG_BASE_UFS_ADDRESS 0x10010000
#else
#define REG_BASE_UFS_ADDRESS 0x113a0000
#endif

#ifdef UFS_FPGA
#define REG_BASE_FPGA2_APB_IF_ADDRESS 0x113f7000
#define UFS_SRST_REQ	(0x1 << 0)
#define UFS_RST			(0x1 << 31)
#endif

#define TRUE    1
#define FALSE   0


#define MAX_DEVICE  64

#define SUCCESS 0
#define ERROR   (-1)

#define UFS_ERROR -1
#define UFS_OK   0
#define UFS_DATA_DIFF 0x2
#define UFS_GLITCH_BYPASS 0x3

/* use the below MACRO to define pressure test characteristc */
/*#define PRESSURE_REINIT*/
#define PRESSURE_PMC
#define PRESSURE_RW
/*#define PRESSURE_H8*/
#define CLOSE_CLK_GATING
/*#define USE_GPIO_TO_CAPTURE*/

#define H8_DELAY 1

/*#define OCS_5_WORKAROUND*/
#if defined(OCS_5_WORKAROUND)
#define NOISE_PROOF
#endif

#define CONTROLLER_OFFSET_TO_SRAM  (0xE0000000)
#define SRAM_PHY_BASE_ADDR  0

#define UPIU_TOTAL_PACK_SIZE  ( \
	1024/*UTR_1k*/ +  1024 /*align*/ +  \
	1024/*UTMR_1k*/ + 1024 /*align*/ +  \
	36864/*UTMR_36k*/ + 128 /*align*/ + \
	2304/*LRB_2k256b*/) /*total 0xa980*/

#define SRAM_TOTAL_SIZE UPIU_TOTAL_PACK_SIZE

#define BLK_SIZE_ALIGN_DOWN(x)  ((x) & ~(LOGICAL_BLK_SIZE - 1))
#define BLK_SIZE_ALIGN(x) \
		((x + LOGICAL_BLK_SIZE - 1) & ~(LOGICAL_BLK_SIZE - 1))
#define BYTES_ALIGN_4(x)  ((x + 4 - 1) & ~(4 - 1))
#define BYTES_ALIGN_128(x)  ((x + 128 - 1) & ~(128 - 1))
#define BYTES_ALIGN_1024(x)  ((x + 1024 - 1) & ~(1024 - 1))
#define COMBO_PHY_V110
/* use the st board's ufs controller */
#define USE_AXI_EXP
#if defined(COMBO_PHY_V100)
	#define TX_SLEEP_CONTROL  0x00c50000
	#define RX_SLEEP_CONTROL  0x00c70000
	#define REF_CLK_DIV_EN   0x00d00000
	#define RG_PLL_CP    0x00ce0000
#elif defined(COMBO_PHY_V110)
	#define TX_SLEEP_CONTROL  0x00c80000
	#define RX_SLEEP_CONTROL  0x00c60000
#endif

#define ADDR_MAP_PC_2_SRAM(x)   (x)

#ifndef CONFIG_SYS_DCACHE_OFF
#define memcpy_pc_2_sram(a, b, sz) \
		flush_dcache_range((unsigned long)(a), \
			(unsigned long)((b) + (sz)))
#define memcpy_sram_2_pc(a, b, sz) \
		invalidate_dcache_range((unsigned long)(a), \
			(unsigned long)((b) + (sz)))
#else
#define memcpy_pc_2_sram(a, b, sz)
#define memcpy_sram_2_pc(a, b, sz)
#endif


#define UFS_USE_HISI_MPHY_TC

/*#define CHIP_STATUS_SLOW*/
#define UFSHC_CLK_GATE_BYPASS
/*#define UFS_INIT_RATE_B*/
/*#define UFS_AUTO_H8_ENABLE*/
/*#define UFS_UNIPRO_SCRAMBLING*/
/*#define TX_EQUALIZER_0DB*/
#define TX_EQUALIZER_35DB
/*#define TX_EQUALIZER_60DB*/
#define UFS_UNIPRO_TERMINATION
/*#define UFS_HS_GEAR_1*/

#define UFS_SYS_PSW_POWER_CTRL		(REG_BASE_UFS_SYS + 0x04)
#define UFS_SYS_PHY_ISO_EN		(REG_BASE_UFS_SYS + 0x08)
#define UFS_SYS_HC_LP_CTRL		(REG_BASE_UFS_SYS + 0x0C)
#define UFS_SYS_PHY_CLK_CTRL		(REG_BASE_UFS_SYS + 0x10)
#define UFS_SYS_PSW_CLK_CTRL		(REG_BASE_UFS_SYS + 0x14)
#define UFS_SYS_CLOCK_GATE_BYPASS	(REG_BASE_UFS_SYS + 0x18)
#define UFS_SYS_RESET_CTRL_EN		(REG_BASE_UFS_SYS + 0x1C)
#define UFS_SYS_MONITOR_HH		(REG_BASE_UFS_SYS + 0x3C)
#define UFS_SYS_UFS_SYSCTRL		(REG_BASE_UFS_SYS + 0x5C)
#define UFS_SYS_UFS_DEVICE_RESET_CTRL	(REG_BASE_UFS_SYS + 0x60)

#define AO_IOC_IOCG_001			(REG_BASE_AO_IOC + 0x804)
#define GPIODIR				(0x400)

#define BIT_UFS_PSW_ISO_CTRL		(1 << 16)
#define BIT_UFS_PSW_MTCMOS_EN		(1)
#define BIT_UFS_REFCLK_ISO_EN		(1 << 16)
#define BIT_UFS_PHY_ISO_CTRL		(1)
#define BIT_SYSCTRL_LP_ISOL_EN		(1 << 16)
#define BIT_SYSCTRL_PWR_READY		(1 << 8)
#define BIT_SYSCTRL_REF_CLOCK_EN	(1 << 24)
#define MASK_SYSCTRL_REF_CLOCK_SEL	(0x3 << 8)
#define MASK_SYSCTRL_CFG_CLOCK_FREQ	(0xFF)
#ifdef CHIP_STATUS_SLOW
#define UFS_FREQ_CFG_CLK		(0x14)
#else
#define UFS_FREQ_CFG_CLK                (0x39)
#endif
#define BIT_SYSCTRL_PSW_CLK_EN		(1 << 4)
#define MASK_UFS_CLK_GATE_BYPASS	(0x3F)
#define BIT_SYSCTRL_LP_RESET_N		(1)
#define BIT_UFS_REFCLK_SRC_SEl		(1)
#define MASK_UFS_SYSCRTL_BYPASS		(0x3F << 16)
#define MASK_UFS_DEVICE_RESET		(0x1 << 6)
#define MASK_UFS_HCE_RESET		(0x7)
#define BIT_UFS_DEVICE_RESET		(0x1)

/* sysctrl ufs clk bit */
#define BIT_SYS_UFS_CLK_TYPE_OFF	(0x6)
#define BIT_SYS_UFS_CLK_TYPE_MASK	(0x3 << BIT_SYS_UFS_CLK_TYPE_OFF)

#define HOST_64BIT

/* FIXME: Fix this when partition table is ready */
#define PARTITION_TABLE_UNIT	512
#define UFS_RPMB_BUF_SIZE (256)

#define RETRY_CNT              2000
#define TIMEOUT_CNT            5000
/* Versions of UFSHCI specification that
the controller implementation supports */
#define DWC_UFS_HC_VERSION_1_1	0x00010100
#define DWC_UFS_HC_VERSION_2_0	0x00000200

/* UFS DEVICE Spec Versions */
#define UFS_DEVICE_SPEC_1_1	0x0110
#define UFS_DEVICE_SPEC_2_0	0x0200

/* UFSHCD Registers Offsets */
#define UFS_CAP_OFF             0x00
#define UFS_VER_OFF             0x08
#define UFS_HCPID_OFF           0x10
#define UFS_HCMID_OFF           0x14
#define UFS_AHIT_OFF            0x18
#define UFS_IS_OFF              0x20
#define UFS_IE_OFF              0x24
#define UFS_HCS_OFF             0x30
#define UFS_HCE_OFF             0x34
#define UFS_UECPA_OFF           0x38
#define UFS_UECDL_OFF           0x3C
#define UFS_UECN_OFF            0x40
#define UFS_UECT_OFF            0x44
#define UFS_UECDME_OFF          0x48
#define UFS_UTRIACR_OFF         0x4C
#define UFS_UTRLBA_OFF          0x50
#define UFS_UTRLBAU_OFF         0x54
#define UFS_UTRLDBR_OFF         0x58
#define UFS_UTRLCLR_OFF         0x5C
#define UFS_UTRLRSR_OFF         0x60
#define UFS_UTMRLBA_OFF         0x70
#define UFS_UTMRLBAU_OFF        0x74
#define UFS_UTMRLDBR_OFF        0x78
#define UFS_UTMRLCLR_OFF        0x7C
#define UFS_UTMRLRSR_OFF        0x80
#define UFS_UICCMD_OFF          0x90
#define UFS_UICCMDARG1_OFF      0x94
#define UFS_UICCMDARG2_OFF      0x98
#define UFS_UICCMDARG3_OFF      0x9C
#define UFS_BUSTHRTL_OFF        0xC0
#define UFS_OOCPR_OFF           0xC4
#define UFS_FEIE_OFF            0xC8
#define UFS_CDACFG_OFF          0xD0
#define UFS_CDATX1_OFF          0xD4
#define UFS_CDATX2_OFF          0xD8
#define UFS_CDARX1_OFF          0xDC
#define UFS_CDARX2_OFF          0xE0
#define UFS_CDASTA_OFF          0xE4
#define UFS_LBMCFG_OFF          0xF0
#define UFS_LBMSTA_OFF          0xF4
#define UFS_DBG_OFF             0xF8
#define UFS_HCLKDIV_OFF         0xFC

/* Controller capability masks and shift value */
#define DWC_UFS_NUTRS_MASK                  0x0000001f
#define DWC_UFS_NPRTTS_MASK                 0x0000ff00
#define DWC_UFS_NPRTTS_SHIFT                8
#define DWC_UFS_NUTMRS_MASK                 0x00070000
#define DWC_UFS_NUTMRS_SHIFT                16
#define DWC_UFS_AUTOH8                      0x00800000
#define DWC_UFS_AUTOH8_SHIFT                23
#define DWC_UFS_64AS                        0x01000000
#define DWC_UFS_64AS_SHIFT                  24
#define DWC_UFS_OODDS                       0x02000000
#define DWC_UFS_OODDS_SHIFT                 25
#define DWC_UFS_UICDMETMS                   0x04000000
#define DWC_UFS_UICDMETMS_SHIFT             26

/* DWC_UFS_REG_IE Bitfields */
#define DWC_UFS_UTRCE                       0x00000001
#define DWC_UFS_UDEPRIE                     0x00000002
#define DWC_UFS_UEE                         0x00000004
#define DWC_UFS_UTMSE                       0x00000008
#define DWC_UFS_UPMSE                       0x00000010
#define DWC_UFS_UHXSE                       0x00000020
#define DWC_UFS_UHESE                       0x00000040
#define DWC_UFS_ULLSE                       0x00000080
#define DWC_UFS_ULSSE                       0x00000100
#define DWC_UFS_UTMRCE                      0x00000200
#define DWC_UFS_UCCE                        0x00000400
#define DWC_UFS_DFEE                        0x00000800
#define DWC_UFS_UTPEE                       0x00001000
#define DWC_UFS_HCFEE                       0x00010000
#define DWC_UFS_SBFEE                       0x00020000

/* DWC_UFS_REG_UTRIACR Bitfields and masks and shift value */
#define DWC_UFS_IAEN                        0x80000000
#define DWC_UFS_IAPWEN                      0x01000000
#define DWC_UFS_IASB                        0x00100000
#define DWC_UFS_CTR                         0x00010000
#define DWC_UFS_IACTH_MASK                  0x00001f00
#define DWC_UFS_IACTH_SH                    8
#define DWC_UFS_IATOVAL_MASK                0x000000ff


#define MTX_L0	0x0000	/*GenSelectorIndex for TX lane 0*/
#define MTX_L1	0x0001	/*GenSelectorIndex for TX lane 1*/
#define MRX_L0	0x0004  /*GenSelectorIndex for RX lane 0*/
#define MRX_L1	0x0005  /*GenSelectorIndex for RX lane 1*/

#define ATTR_M_SHIFT			16
#define ATTR_UNIPRO_SHIFT		ATTR_M_SHIFT

#define ATTR_MTX0(x)	((x << ATTR_M_SHIFT) | MTX_L0)
#define ATTR_MTX1(x)	((x << ATTR_M_SHIFT) | MTX_L1)
#define ATTR_MRX0(x)	((x << ATTR_M_SHIFT) | MRX_L0)
#define ATTR_MRX1(x)	((x << ATTR_M_SHIFT) | MRX_L1)
#define ATTR_MCB(x)		((u32)((u16)(x) << ATTR_M_SHIFT))
#define ATTR_UNIPRO(x)	((u32)((u16)(x) << ATTR_UNIPRO_SHIFT))
/*SYNOPSYS UniPro register*/
#define UNIPRO_DME_RESET		0xD010
#define UNIPRO_DME_LAYBER_ENABLE	0xD000
/*MPHY registers addr*/
/*RX*/
#define AD_DIF_P_LS_TIMEOUT_VAL		0x0003
#define PWM_PREPARE_TO			0x00000080
#define SKP_DET_SEL			0x0009
#define SKP_DET_SEL_EN			0x00000001

#define MRX_EN				0x00F0
#define MRX_ENABLE			(0x01 << 0)
#define RX_SQ_VREF			0x00F1
#define RX_SQ_VREF_175mv		0x00000002
#define VCO_AUTO_CHG			0x00DF
#define VCO_AUTO_CHG_EN			(0x01 << 0)
#define VCO_FORCE_ON_EN			(0x01 << 1)

#define RG_PLL_PRE_DIV			0x00C2
#define RG_PLL_PRE_DIV_1		0x00
#define RG_PLL_PRE_DIV_2		0x01
#define RG_PLL_PRE_DIV_4		0x02
#define RG_PLL_PRE_DIV_8		0x03

#define RG_PLL_FBK_P			0x00C3
#define RG_PLL_FBK_S			0x00C4

#define RG_PLL_SWC_EN			0x00C9
#define PG_PLL_SWC_ENABLE		0x01

#define RG_PLL_RXHSGR			0x00CD
#define RG_PLL_RXLSGR			0x00CE
#define RG_PLL_TXHSGR			0x00CF
#define HS_R_A_FBK_P			0x41
#define HS_R_B_FBK_P			0x4C
#define HS_G_1_TXRXHSGR			0x02
#define HS_G_2_TXRXHSGR			0x01
#define HS_G_3_TXRXHSGR			0x00

#define RG_PLL_TXLSGR			0x00D0

/*PHY CB*/
#define RG_PLL_TXHS_EN			0x00C7
#define RG_PLL_TXHS_ENANBLE		(0x01 << 0)
#define RG_PLL_TXHS_EN_CONTROL		(0x01 << 1)

#define RG_PLL_TXLS_EN			0x00C8
#define RG_PLL_TXLS_ENABLE		(0x01 << 0)
#define RG_PLL_TXLS_EN_CONTROL		(0x01 << 1)

struct pllChkInfo {
	uint32_t	reg_addr;
	int		bit_mask;
	int		expect_val;
	char	*string;
};


enum {
	RG_PLL_PRE_DIV_INDEX = 0,
	RG_PLL_SWC_EN_INDEX,
	RG_PLL_FBK_S_INDEX,
	RG_PLL_FBK_P_INDEX,
	RG_PLL_TXHSGR_INDEX,
	RG_PLL_RXHSGR_INDEX,
	RG_PLL_END_INDEX
};

/* Interrupt configuration options */
enum {
	DWC_UFS_HCD_INTR_DISABLE = 0,
	DWC_UFS_HCD_INTR_ENABLE = 1,
};

/* Interrupt aggregation options */
enum {
	INTR_AGGR_RESET,
	INTR_AGGR_CONFIG,
	INTR_AGGR_DISABLE
};

#define DWC_INTR_AGGR_COUNTER_THRESHOLD_VALUE	(0x1F)
#define DWC_INTR_AGGR_TIMEOUT_VALUE		(0xFF)
#define BAD_SLOT  0x55
enum tm_task_resp {
	TM_COMPLETE = 0x00,
	TM_NOT_SUPPORT = 0x04,
	TM_FAILED = 0x05,
	TM_SUCCESS = 0x08,
	TM_BAD_LUN = 0x09
};

/* TX_FSM_STATE */
enum {
	M_TX_IDLE = 0x0,
	M_TX_DISABLE = 0x0,
	M_TX_HIBERN8 = 0x1,
	M_TX_HIBERN8_EXIT = 0x1,
	M_TX_Sleep = 0x2,
	M_TX_STALL = 0x3,
	M_TX_LS_BURST = 0x4,
	M_TX_HS_BURST = 0x5,
	M_TX_LINE_CFG = 0x6,
	M_TX_LINE_RESET = 0x7
};

#define HIBERNATE_TIMER_VALUE_MASK (~(BIT(9)))
#define HIBERNATE_TIMER_SCALE_SHIFT (10)
#define CGE   (BIT(12))
#define LP_AH8_PGE   (BIT(17))
#define LP_PGE	(BIT(16))
#define ULP_ULP_CTRLMODE (BIT(3))
/*
 * Register Fields
 */
#define UFS_AUTO_HIBERNATE_BIT	BIT(23)
#define UFS_CAPS_64AS_BIT		BIT(24)
#define UFS_HCE_RESET_BIT		BIT(0)
#define UFS_HCS_DP_BIT			BIT(0)
#define UFS_HCS_UCRDY_BIT		BIT(3)
#define UFS_HCS_UPMCRS_OFF		(8)
#define UFS_HCS_UPMCRS_MASK		(0x3 << UFS_HCS_UPMCRS_OFF)
#define UFS_IS_UE_BIT			BIT(2)
#define UFS_IS_UPMS_BIT			BIT(4)
#define UFS_IS_UHXS_BIT			BIT(5)
#define UFS_IS_UHES_BIT			BIT(6)
#define UFS_IS_ULSS_BIT			BIT(8)
#define UFS_IS_UCCS_BIT			BIT(10)
#define UFS_UTP_RUN_BIT			BIT(0)
#define UFS_LBMCFG_DEFAULT_VALUE	0xb01
#define UFS_HCLKDIV_NORMAL_VALUE	0xFA
#define UFS_HCLKDIV_SLOW_VALUE		0x14
#define UFS_HCLKDIV_FPGA_VALUE		0x28

#define UFS_AHIT_AH8ITV_MASK		(0x3FF)
#define UFS_AHIT_AUTOH8_TIMER		(0x1001)

#define UIC_LINK_STARTUP_CMD		0x16
#define NOP_TRANS_TYPE			0x20

#define LOWER_32_BITS(x)	((uint32_t)((uint64_t)(x) & 0xFFFFFFFFUL))
#define UPPER_32_BITS(x)	((uint32_t)((uint64_t)(x) >> 32))

#define CMD_DESC_ALIGNMENT     128
#define ALIGN_SIZE             1024
#define PRDT_BUFFER_SIZE       0x40000
#define CAPCITY_ADJ_FACTOR     1
#define UNIT_DESCS_COUNT       8
#define SENSE_KEY_INDEX        36
#define RPMB_DATA_SIZE         256
#define RPMB_FRAME_SIZE        512
#define LOGICAL_BLK_SIZE       4096


#define TM_TASK_TEST_NUM       7

#define QUERY_DESC_MANUFACTURER_NAME_MAX_SIZE 0x12
#define QUERY_DESC_PRODUCT_NAME_MAX_SIZE 0x22

/* Data structure sizes in bytes */
enum {
	DWC_UFS_BASIC_UPIU_SIZE = 32,
	DWC_UFS_UTRD_SIZE = 32,
	DWC_UFS_TSF_SIZE = 16,
	DWC_UFS_PRD_SIZE = 16,

	DWC_UFSHCD_MAX_PRD_SIZE = 8,	/* 128 (Linux) */

	DWC_MAX_QUERY_DATA = 256,
	DWC_UFS_CDB_SIZE = 16,
	DWC_UFS_SENSE_DATA_SIZE = 18,

	DWC_UFS_UTMRD_HDR_SIZE = 16,
};

/* Alignment Requirement in bytes */
enum {
	DWC_UTRL_BASE_ALIGN = 1024,
	DWC_UCD_ALIGN = 512,
};

#define FAST_MAX_GEAR 4
#define SLOW_MAX_GEAR 2
#define FAST_MAX_RATE 3
#define SLOW_MAX_RATE 2

/* Rate */
enum UFS_RATE {
	UFS_RATE_A = 1,
	UFS_RATE_B = 2
};

/* POWER mode */
enum POWER_MODE {
	FAST_MODE = 0x11,
	SLOW_MODE = 0x22,
	FASTAUTO_MODE = 0x44,
	SLOWAUTO_MODE = 0x55,
	INVALID_MODE = 0xFF
};

enum ufs_pwm_gear_tag {
	UFS_PWM_DONT_CHANGE,/* Don't change Gear */
	UFS_PWM_G1,/* PWM Gear 1 (default for reset) */
	UFS_PWM_G2,/* PWM Gear 2 */
	UFS_PWM_G3,/* PWM Gear 3 */
	UFS_PWM_G4,/* PWM Gear 4 */
	UFS_PWM_G5,/* PWM Gear 5 */
	UFS_PWM_G6,/* PWM Gear 6 */
	UFS_PWM_G7,/* PWM Gear 7 */
};

enum ufs_hs_gear_tag {
	UFS_HS_DONT_CHANGE,/* Don't change Gear */
	UFS_HS_G1,/* HS Gear 1 (default for reset) */
	UFS_HS_G2,/* HS Gear 2 */
	UFS_HS_G3,/* HS Gear 3 */
};

enum unit_desc_type{
	UNIT_DESC_0 = 0X00,
	UNIT_DESC_1,
	UNIT_DESC_2,
	UNIT_DESC_3,
	UNIT_DESC_4,
	UNIT_DESC_5,
	UNIT_DESC_6,
	UNIT_DESC_7,
	UNIT_DESC_MAX,
};
/* power mode specific define */
struct pwrModeParams {
	uint8_t txGear;
	uint8_t rxGear;
	uint8_t hsSeries;
	uint8_t txLanes;
	uint8_t rxLanes;
	uint8_t pwrMode;
};

struct st_register_dump {
	uint16_t offset;
	char *name;
};

//#define DEFAULT_POWER_MODE	FAST_MODE
#define DEFAULT_POWER_MODE	SLOW_MODE
//#define DEFAULT_GEAR			UFS_HS_G1
#define DEFAULT_GEAR			UFS_PWM_G4
#define DEFAULT_RATE			UFS_RATE_A
#define DEFAULT_LANE			(1)
#define DEFAULT_ACTIVE_LUN	(3)
#define DEFAULT_BOOT_LUN	(0)
#pragma pack(push)
#pragma pack(1)

/*
 * Command UPIU Structure
 */
struct dwc_ufs_cmd_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;	/* Only LS nibble is valid. Others Reserved */
	uint8_t reserved_1_0;
	uint8_t reserved_1_1;
	uint8_t reserved_1_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_2;
	uint16_t data_seg_len;
	uint32_t exp_data_xfer_len;
	uint8_t cdb[16];	/* UFS/SCSI command descriptor block */
};

/*
 * Query UPIU Structure
 */
struct dwc_ufs_query_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint8_t reserved_2;
	uint8_t query_func;
	uint8_t query_resp; /* valid only wen used for response */
	uint8_t reserved_3;
	uint8_t tot_ehs_len;
	uint8_t reserved_4;
	uint16_t data_seg_len;
	uint8_t tsf[16];
	uint32_t reserved_5;
};

/*
 * NOP OUT UPIU Structure
 */
struct dwc_ufs_nop_req_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint32_t reserved_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint8_t reserved_4[20];
};

/*
 * NOP IN UPIU Structure
 */
struct dwc_ufs_nop_resp_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint8_t reserved_2_0;
	uint8_t reserved_2_1;
	uint8_t response;
	uint8_t reserved_3;
	uint8_t tot_ehs_len;
	uint8_t device_info;
	uint16_t data_seg_len;
	uint8_t reserved_4[20];
};

/*
 * Transfer Response UPIU Structure
 */
struct dwc_ufs_resp_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;	/* Only LS nibble is valid. Others Reserved */
	uint8_t reserved_1;
	uint8_t response;
	uint8_t status;		/* This is SCSI status */
	uint8_t tot_ehs_len;
	uint8_t device_info;
	uint16_t data_seg_len;
	uint32_t residual_xfer_count;
	uint32_t reserved_2;
	uint32_t reserved_3;
	uint32_t reserved_4;
	uint32_t reserved_5;
	uint16_t sense_data_len;
	uint8_t sense_data[18];
};

struct dwc_ufs_prd {
	uint32_t base_addr;
	uint32_t upper_addr;
	uint32_t reserved1;
	uint32_t size;
};

/**
 * dwc_ufs_ucd
 * UTP Command Descriptor (UCD) structure.
 * Every UTRD contains a pointer for this data structure
 * This structure logically consists of 3 parts
 *	1. "Transfer Request" or "Command UPIU" (SCSI, Native UFS & DM)
 *	2. "Transfer Response" or "Response UPIU"
 *	3. "Physical Region Description Table"(PRDT).
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space.
 * "Transfer Request" and "Transfer Response" are in BIG ENDIAN Format
 * "PRDT" is in LITTLE ENDIAN Format
 */
struct dwc_ufs_ucd {
	u8 cmd_upiu[DWC_UCD_ALIGN];
	u8 resp_upiu[DWC_UCD_ALIGN];
	struct dwc_ufs_prd prdt[DWC_UFSHCD_MAX_PRD_SIZE];
};

struct dwc_ufs_utrd {
	uint8_t reserved_1_0:8;
	uint8_t reserved_1_1:8;
	uint8_t reserved_1_2:8;
	uint8_t ct_and_flags:8;
	uint32_t reserved_2:32;
	uint8_t ocs:8;
	uint8_t reserved_3_0:8;
	uint8_t reserved_3_1:8;
	uint8_t reserved_3_2:8;
	uint32_t reserved_4:32;

	/* Only bits 31:7 are valid; 128B Aligned addr */
	uint32_t ucdba:32;
	uint32_t ucdbau:32;
	uint16_t resp_upiu_length:16;
	uint16_t resp_upiu_offset:16;

	uint16_t prdt_length:16;
	uint16_t prdt_offset:16;
};

/**
 * dwc_ufs_tm_req_upiu
 * Task Management Request UPIU structure
 * Size of this structure is 32 bytes
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space. This structure is in BIG ENDINA Format
 */
struct dwc_ufs_tm_req_upiu {	/* BIG ENDINA */
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t reserved_1;
	uint8_t tm_fn;
	uint8_t reserved_2_0;
	uint8_t reserved_2_1;
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint32_t input_param_1;
	uint32_t input_param_2;
	uint32_t input_param_3;
	uint32_t reserved_4;
	uint32_t reserved_5;
};

/**
 * dwc_ufs_tm_resp_upiu
 * Task Management Response UPIU structure
 * Size of this structure is 32 bytes
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space. This structure is in BIG ENDINA Format
 */
struct dwc_ufs_tm_resp_upiu {	/* BIG ENDINA */
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t reserved_1_0;
	uint8_t reserved_1_1;
	uint8_t response;
	uint8_t reserved_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint32_t output_param_1;
	uint32_t output_param_2;
	uint32_t reserved_4;
	uint32_t reserved_5;
	uint32_t reserved_6;
};

struct dwc_ufs_utmrd {
	uint8_t reserved_1_0:8;
	uint8_t reserved_1_1:8;
	uint8_t reserved_1_2:8;
	uint8_t intr_flag:8;	/* only one bit is valid */
	uint32_t reserved_2:32;
	uint8_t ocs:8;
	uint8_t reserved_3_0:8;
	uint8_t reserved_3_1:8;
	uint8_t reserved_3_2:8;
	uint32_t reserved_4:32;

	struct dwc_ufs_tm_req_upiu tm_req_upiu;
	struct dwc_ufs_tm_resp_upiu tm_resp_upiu;
};

#pragma pack(pop)
struct para_with_enable {
	uint32_t enable;
	uint32_t value;
};

struct ufs_mode_page_para {
	struct para_with_enable tst;
	struct para_with_enable swp;
	struct para_with_enable busy_timeout_period;
	struct para_with_enable read_retry_count;
	struct para_with_enable write_retry_count;
	struct para_with_enable recovery_time_limit;
	struct para_with_enable wce;
	struct para_with_enable rcd;
};

#define CONTROL_MODE_PAGE_CODE				0x0A
#define CONTROL_MODE_PAGE_SIZE				20
#define READ_WRITE_ERROR_RECOVERY_MODE_PAGE_CODE	0x01
#define READ_WRITE_ERROR_RECOVERY_MODE_PAGE_SIZE	20
#define CACHING_MODE_PAGE_CODE				0x08
#define CACHING_MODE_PAGE_SIZE				28
#define MAX_MODE_PAGE_SIZE				28

struct partitionDesc {
	uint8_t bootLunId;
	uint8_t writeProtect;
	uint8_t memoryType;
	uint8_t dataReliability;
	uint8_t blockSize; /* bLogicalBlocksize Def: 4096 */
	uint8_t provType; /* Fully provisioning or Thin provisioning */
	uint16_t wContextCapabilities;
	/* Capacity of LUN for provisioning in Mega bytes */
	uint32_t lu_capacity;
#define UFS_MAX_LU_CAP		0xFFFFFFFF
	uint32_t dNumAllocUnits;      /* Used internally by driver */
};

struct configuration_header {
	uint8_t bBootEnable;
	uint8_t bDescrAccessEn;
	uint8_t bInitPowerMode;
	uint8_t bHighPriorityLUN;
	uint8_t bSecureRemovalType;
	uint8_t bInitActiveICCLevel;
	uint16_t wPeriodicRTCUpdate;
};

struct partitionDescTable {
	uint8_t bNumberLU;            /* Used internally by driver */
	uint8_t bAllocationUnitSize;  /* Used internally by driver */
	uint32_t dSegmentSize;        /* used internally by driver */
	uint64_t qTotalRawDeviceCapacity;
	uint8_t bDataOrdering;
	uint8_t bMaxContexIDNumber;
	uint16_t wSupportedMemoryTypes;
	uint32_t dSystemCodeMaxNAllocU;
	uint16_t wSystemCodeCapAdjFac;
	uint32_t dNonPersistMaxNAllocU;
	uint16_t wNonPersistCapAdjFac;
	uint32_t dEnhanced1MaxNAllocU;
	uint16_t wEnhanced1CapAdjFac;
	uint32_t dEnhanced2MaxNAllocU;
	uint16_t wEnhanced2CapAdjFac;
	uint32_t dEnhanced3MaxNAllocU;
	uint16_t wEnhanced3CapAdjFac;
	uint32_t dEnhanced4MaxNAllocU;
	uint16_t wEnhanced4CapAdjFac;
	struct configuration_header *p_conf_header;
	struct partitionDesc *partitionDescPtr[8];
};

struct desc_params {
	void                 *req_upiu;
	struct configuration_header *conf_head;
	struct partitionDesc **part_desc;
	uint8_t              opcode;
	uint8_t              desc_idn;
	uint8_t              desc_index;
	uint16_t             length;
};

/* UFS: Device descriptor */
struct ufs_device_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint8_t bDevice ;/*Device*/
	uint8_t bDeviceClass ;/*00h 00h: Mass Storage*/
	uint8_t bDeviceSubClass ;/*00h 00h: Embedded Bootable*/
	uint8_t bProtocol ;/*00h 00h: SCSI*/
	uint8_t bNumberLU; /*User Conf. Number of Logical Units (Default: 00h)*/
	uint8_t bNumberWLU; /*04h 04h: 4 Well known logical units exist*/
	uint8_t bBootEnable; /*User Conf. 00h: Boot feature disabled (Default) 01h: Bootable feature enabled*/
	uint8_t bDescrAccessEn; /*User Conf. 00h: Device Descriptor access disabled (Default) 01h: Device Descriptor access enabled*/
	uint8_t bInitPowerMode; /*User Conf. 00h: UFS-Sleep Mode 01h: Active Mode (Default)*/
	uint8_t bHighPriorityLUN; /*User Conf. 00h-07h: Configured LUN has high priority 7Fh: All logical units have the same priority (Default)*/
	uint8_t bSecureRemovalType;
	uint8_t bSecurityLU; /*01h 01h: RPMB*/
	uint8_t bBackgroundOpsTermLat;
	uint8_t bInitActiveICCLevel;
	uint16_t wSpecVersion; /*0210h Specification version 2.10*/
	uint16_t wManufactureDate; /*Device Specific Manufacturing Date ex: 0515h = May 2015 Rev 1.2 / Aug. 2016 33 OFFSET SIZE NAME VALUE Description*/
	uint8_t iManufacturerName; /*01h Index to Manufacturer Name String*/
	uint8_t iProductName; /*02h Index to Product Name String*/
	uint8_t iSerialNumber; /*03h Index to Serial Number String*/
	uint8_t iOemID; /*04h Index to OEM ID String*/
	uint16_t wManufacturerID; /*1ADh Manufacturer ID*/
	uint8_t bUD0BaseOffset; /*10h Unit Descriptor 0 Base Offset*/
	uint8_t bUDConfigPLength;
	uint8_t bDeviceRTTCap;
	uint16_t wPeriodicRTCUpdate; /*User Conf. Frequency and method of Real-Time Clock update (Default 000h)*/
	uint8_t bUFSFeatureSupport; /*01h 01h: Field Firmware Update (FFU) supported*/
	uint8_t bFFUTimeout; /*03h Field Firmware Update Timeout. The maximum time is expressed in unitsof seconds.*/
	uint8_t bQueueDepth; /*00h 0: The device implements the per-LU queueing architecture.22h 2 wDeviceVersion 00h Device version*/
	uint16_t wDeviceVersion;
	uint8_t bNumSecureWPArea; /*20h Number of Secure Write Protect Areas*/
	uint32_t dPSAMaxDataSize; /*00h PSA Maximum Data Size*/
	uint8_t bPSAStateTimeout; /*00h PSA State Timeout*/
	uint8_t iProductRevisionLevel; /*05h Index to the string which contains the Product Revision Level*/
	uint8_t Reserved[5]; /*00h Reserved*/
	uint8_t ReservedUME[16]; /*00h Reserved for Unified Memory Extension standard*/
}__attribute__ ((packed));
/* UFS: Device descriptor */
struct ufs_geometry_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bMediaTechnology;
	uint8_t Reserved;
	uint64_t qTotalRawDeviceCapacity;
	uint8_t bMaxNumberLU;
	uint32_t dSegmentSize;
	uint8_t bAllocationUnitSize;
	uint8_t bMinAddrBlockSize;
	uint8_t bOptimalReadBlockSize;
	uint8_t bOptimalWriteBlockSize;
	uint8_t bMaxInBufferSize;
	uint8_t bMaxOutBufferSize;
	uint8_t bRPMB_ReadWriteSize;
	uint8_t bDynamicCapacityResourcePolicy;
	uint8_t bDataOrdering;
	uint8_t bMaxContexIDNumber;
	uint8_t bSysDataTagUnitSize;
	uint8_t bSysDataTagResSize;
	uint8_t bSupportedSecRTypes;
	uint16_t wSupportedMemoryTypes;
	uint32_t dSystemCodeMaxNAllocU;
	uint16_t wSystemCodeCapAdjFac;
	uint32_t dNonPersistMaxNAllocU;
	uint16_t wNonPersistCapAdjFac;
	uint32_t dEnhanced1MaxNAllocU;
	uint16_t wEnhanced1CapAdjFac;
	uint32_t dEnhanced2MaxNAllocU;
	uint16_t wEnhanced2CapAdjFac;
	uint32_t dEnhanced3MaxNAllocU;
	uint16_t wEnhanced3CapAdjFac;
	uint32_t dEnhanced4MaxNAllocU;
	uint16_t wEnhanced4CapAdjFac;
	uint32_t dOptimalLogicalBlockSize;
}__attribute__ ((packed));
/* UFS: String descriptor */
struct ufs_string_descriptor {
	char manufacturer_name[QUERY_DESC_MANUFACTURER_NAME_MAX_SIZE];
	char product_name[QUERY_DESC_PRODUCT_NAME_MAX_SIZE];
};
/* UFS: Health descriptor */
struct ufs_health_descriptor{
	uint8_t bLength;
	uint8_t bDescriptorIDN;
	uint8_t bPreEOLInfo;
	uint8_t bDeviceLifeTimeEstA;
	uint8_t bDeviceLifeTimeEstB;
	uint8_t Reserved[32];
}__attribute__ ((packed));
struct ufs_unit_index_descriptror{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bUnitIndex;
	uint8_t bLUEnable;
	uint8_t bBootLunID;
	uint8_t bLUWriteProtect;
	uint8_t bLUQueueDepth;
	uint8_t bPSASensitive;
	uint8_t bMemoryType;
	uint8_t bDataReliability;
	uint8_t bLogicalBlockSize;
	uint64_t qLogicalBlockCount;
	uint32_t dEraseBlockSize;
	uint8_t bProvisioningType;
	uint64_t qPhyMemResourceCount;
	uint16_t wContextCapabilities;
	uint8_t bLargeUnitGranularity_Muint8_t;
}__attribute__ ((packed));
struct ufs_unit_RPMB_descriptror{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bUnitIndex;
	uint8_t bLUEnable;
	uint8_t bBootLunID;
	uint8_t bLUWriteProtect;
	uint8_t bLUQueueDepth;
	uint8_t bPSASensitive;
	uint8_t bMemoryType;
	uint8_t Reserved1;
	uint8_t bLogicalBlockSize;
	uint64_t qLogicalBlockCount;
	uint32_t dEraseBlockSize;
	uint8_t bProvisioningType;
	uint64_t qPhyMemResourceCount;
	uint8_t Reserved2[3];
}__attribute__ ((packed));

struct ufs_unit_descriptor{
	struct ufs_unit_index_descriptror unit_index_desc[UNIT_DESC_MAX];
	struct ufs_unit_RPMB_descriptror unit_RPMB_desc;
}__attribute__ ((packed));
struct ufs_dev_desc_configuration_param{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bConfDescContinue;
	uint8_t bBootEnable;
	uint8_t bDescrAccessEn;
	uint8_t bInitPowerMode;
	uint8_t bHighPriorityLUN;
	uint8_t bSecureRemovalType;
	uint8_t bInitActiveICCLevel;
	uint16_t wPeriodicRTCUpdate;
	uint8_t Reserved[5];
}__attribute__ ((packed));
struct ufs_unit_desc_configuration_param{
	uint8_t bLUEnable;
	uint8_t bBootLunID;
	uint8_t bLUWriteProtect;
	uint8_t bMemoryType;
	uint32_t dNumAllocUnits;
	uint8_t bDataReliability;
	uint8_t bLogicalBlockSize;
	uint8_t bProvisioningType;
	uint16_t wContextCapabilities;
	uint8_t Reserved[3];
}__attribute__ ((packed));
struct ufs_configuration_descriptor{
	struct ufs_dev_desc_configuration_param dev_desc_conf_param;
	struct ufs_unit_desc_configuration_param unit_desc_conf_param[UNIT_DESC_MAX];
}__attribute__ ((packed));
struct ufs_descriptor{
	BOOL desc_is_init;
	struct ufs_device_descriptor dev_desc;
	struct ufs_string_descriptor str_desc;
	struct ufs_geometry_descriptor geo_desc;
	struct ufs_unit_descriptor unit_desc;
	struct ufs_configuration_descriptor conf_desc;
	struct ufs_health_descriptor heal_desc;
};
/**
 * struct dwc_ufs_hcd_lrb
 * Local Reference Block for application commands (eg:scsi)
 * Maintained for every utrd slot
 * @command_type: Maintained to abstract the application layer out of core
 * @data_direction: whether command is a read/write or no-data command
 * @ocs: ocs from utrd is read and kept here for future analysis
 * @xfer_command_status: holds the response from response-upiu(eg: Scsi status)
 * @transfer_size: total size of transfer in bytes
 * @task_tag: task_tag
 * @lun: lun
 * @scmd: scsi command; should be null if its not a scsi command
 * @utrd: transfer descriptor address pointer
 * @cmd_upiu: address of command upiu
 * @resp_upiu: address of response upiu
 * @prdt: base address of prd table
 * @sense_buffer_len: sense buffer length in bytes
 * @snese_buffer: pointer to sense buffer for the command
 */
struct dwc_ufs_hcd_lrb {
	/* Understood */
	u8 command_type;	/* UFS, SCSI or Device Management */
	u8 data_direction;
	u8 read_write_flags;
	u8 ocs;
	u8 xfer_command_status;

	u32 transfer_size;
	u32 task_tag;
	u32 lun;

	struct dwc_ufs_utrd *utrd;
	struct dwc_ufs_cmd_upiu *cmd_upiu;
	struct dwc_ufs_resp_upiu *resp_upiu;
	struct dwc_ufs_prd *prdt;

	u16 sense_buffer_len;
	u8 *sense_buffer;
};

/**
 * struct dwc_ufshcd_dm_lrb
 * Local Reference Block for Device management commands (eg: nopout, query ..)
 * Maintained one per driver instance
 * @trans_type: Transaction Type (query/nopout ..)
 * @flags:flags indicating Read/Write
 * @lun: lun to be addressed through this command
 * @query_fn: query_function
 * @tot_ehs_len: total ehs length
 * @data_seg_len: data segment length for this command
 * @tsf: transaction specific field for this command
 * @dm_cmd_results: Device management function result updated after
 * post processing
 */
struct dwc_ufshcd_dm_lrb {
	u8 trans_type;
	u8 flags;
	u8 lun;
	/* We cant fix task tag; it is dynamically set */
	u8 query_fn;
	u8 tot_ehs_len;
	u16 data_seg_len;
	u8 tsf[DWC_UFS_TSF_SIZE];

	s32 dm_cmd_results;
};

/**
 * struct uic_command - UIC command structure
 * @command: UIC command
 * @argument1: UIC command argument 1
 * @argument2: UIC command argument 2
 * @argument3: UIC command argument 3
 * @cmd_active: Indicate if UIC command is outstanding. the same variable
 * as condition variable to wake up dme wait queue
 */
struct dwc_ufs_dme_sap_cmd {
	u32 command;
	u32 argument1;
	u32 argument2;
	u32 argument3;
	int cmd_active;
};

/**
 * struct dwc_ufs_hba
 * Private structure of the host bus adapter
 * @mmio_base: DWC UFS HCI base register address
 * @irq: Irq no to be used for ISR registration
 * @gdev: Generic device structure for pci/platform device abstraction
 * @shost: scsi host structure for scsi mid layer
 * @caps: DWC UFS HC capabilities stored here for reference
 * @ufs_version: UFS version read adn kept here
 * @nutrs: Transfer Request Queue depth supported by DWC UFS HC
 * @nutmrs: Task Management Queue depth supported by DWC UFS HC
 * @utrl_base_addr: UTP Transfer Request Descriptor List base address (virtual)
 * @utmrl_base_addr: UTP Task Management Descriptor List base address (virtual)
 * @ucdl_base_addr: UFS Command Descriptor List Base Address (virtual)
 * @utrl_dma_addr: UTRDL DMA address List Base Address (DMA/Physical)
 * @utmrl_dma_addr: UTMRDL DMA address List Base Address (DMA/Physical)
 * @ucdl_dma_addr: UFS Command Descriptor List Base Address (DMA/Physical)
 * @lrb: pointer to local reference block list
 * @dm_lrb: local reference block device management commands
 * @dme_completion_handler_type: work queue type or wait queue type
 * @tm_completion_handler_type: work queue type or wait queue type
 * @dm_completion_handler_type: work queue type or wait queue type
 * @fatal_error_handler_type: work queue type or wait queue type
 * @dme_sap_workq: work quue for DME/UIO commands
 * @active_dme_cmd: Active dme command is kept in this structure
 * @intr_enable_mask: Enable mask for the interrupts
 * @intr_aggr_cntr_thr: Interrupt aggregatin counter threshold
 * @intr_aggr_timout_val: Interrupt aggregation timeout value
 * @outstanding_xfer_reqs: outstanding transfer requests to be processed
 * @outstanding_dm_requests: outstanding DM requests to be processes
 * (Only One as of now)
 * @outstanding_tm_tasks: outstanding TM tasks to be processed
 * @dwc_ufshcd_tm_wait_queue: wait queue head to keep tm task commands
 * @dwc_ufshcd_dm_wait_queue: wait queue head to keep dm commands
 * @dwc_ufshcd_dme_wait_queue: wait queue head to keep dme commands
 * @dwc_ufshcd_tm_condition: condition variable to wake up tm wait queue
 * @dwc_ufshcd_dm_condition: condition variable to wake up dm wiet queue
 * @fatal_error_handler_workq: work queue for handling Fatal errors
 * @dwc_ufshcd_state: state of the driver/hardware
 * @dwc_ufshcd_interrupts: keeps the snapshot of interrupt status register
 */
struct dwc_ufs_hba {
	/* Understood */
	/*the mmio_base in fastboot is just the HCI's physical address,
		no use here */
	void *mmio_base;
#if 0
	int irq;
	struct device *gdev;
	struct Scsi_Host *shost;
#endif

	u32 caps;

	u8 nutrs;
	u8 nprtts;
	u8 nutmrs;
	u8 autoh8;
	u8 as64;
	u8 oodds;
	u8 uicdmetms;

	u8 active_lun;		/* Active Lun to be used for transfer      */
	u8 lu_request_sense_sent[UNIT_DESCS_COUNT];
	u8 unit_offset;		/* Offset of first Unit Configuration Desc */
	u8 unit_length;		/* Length Of Configuration Unit Descriptor */
	uint16_t manufacturer_id;
	uint16_t manufacturer_data;
#define UFS_MANUFACTURER_ID_TOSHIBA	0x0198
#define UFS_MANUFACTURER_ID_HYNIX	0x01AD
#define UFS_MANUFACTURER_ID_SUMSANG	0x01CE
#define UFS_MANUFACTURER_ID_SANDISK	0x0145
	u8 manufacturer_name;
	u8 product_name;
	u8 oem_id;
	u8 serial_number;
	u16 dev_spec_version;	/* Device Specification version */

	/* Virtual memory reference for driver */
	uint64_t  mem_pool;
	void  *write_read_buf;
	struct dwc_ufs_utrd *utrl_base_addr;
	struct dwc_ufs_utmrd *utmrl_base_addr;
	struct dwc_ufs_ucd *ucdl_base_addr;

	/* DMA memory reference for above mentioned virtual memory
	 * for Host Controller reference */
	/*In fastboot, the Virtual memoery is the same as the DMA memory */
#if 0
	dma_addr_t utrl_dma_addr;
	dma_addr_t utmrl_dma_addr;
	dma_addr_t ucdl_dma_addr;
#endif

	struct dwc_ufs_hcd_lrb *lrb;
	struct dwc_ufshcd_dm_lrb dm_lrb;
#if 0
	u32 dme_completion_handler_type;
	u32 tm_completion_handler_type;
	u32 dm_completion_handler_type;
	u32 fatal_error_handler_type;

	/* Work to handle dme operation */
	struct work_struct dme_sap_workq;
#endif
	struct dwc_ufs_dme_sap_cmd active_dme_cmd;

	/* Interrupt aggregation parameters */
	u32 intr_enable_mask;
	u8 intr_aggr_cntr_thr;
	u8 intr_aggr_timout_val;

	/* Outstanding requests Xfer: 32 Max, dm: 1, tm:8 ,
		 xfer and dm share the UTRL */
	unsigned long outstanding_xfer_reqs;
	unsigned long outstanding_dm_requests;
	unsigned long outstanding_tm_tasks;

	unsigned long dwc_ufshcd_tm_condition;
	unsigned long dwc_ufshcd_dm_condition;

	/* DWC UFS HC state */
	u32 dwc_ufshcd_state;

	/* HBA interrupts */
	u32 dwc_ufshcd_interrupts;

	/* Read Write Statistics */
	u32 debug_mode;

	u8 is_init;
};

#ifdef UFS_DEBUG
#define UFS_PRINT printf
#define PRINT_ERROR printf
#define PRINT_DEBUG  UFS_PRINT
#define PRINT_WARNING  UFS_PRINT
#define PRINT_INFO  UFS_PRINT
#define POS()	UFS_PRINT("%s:%d: HERE\n", __func__, __LINE__)
#define FUNC_ENTER()
#define FUNC_EXIT()
#else
#define POS()
#define FUNC_ENTER()
#define FUNC_EXIT()
#define PRINT_WARNING(s...)
#define UFS_PRINT(s...)
#define PRINT_ERROR(s...)
#endif


#ifdef UFS_MEM_DEBUG
#define UFS_MEM printf
#else
#define UFS_MEM(s...)
#endif

/* Byte swap u16*/
static inline uint16_t swap_16(uint16_t val)
{
	return (uint16_t)((val << 8) | (val >> 8));
}

/* Byte swap unsigned int */
static inline uint32_t swap_32(uint32_t val)
{

	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

static inline uint32_t to_bigendian32(uint32_t val)
{
#ifdef HOST_BIG_ENDIAN
	return val;
#else
	return swap_32(val);
#endif
}

static inline uint32_t to_littleendian32(uint32_t val)
{
#ifdef HOST_BIG_ENDIAN
	return swap_32(val);
#else
	return val;
#endif
}

static inline uint16_t to_bigendian16(uint16_t val)
{
#ifdef HOST_BIG_ENDIAN
	return val;
#else
	return swap_16(val);
#endif
}

static inline uint16_t to_littleendian16(uint16_t val)
{
#ifdef HOST_BIG_ENDIAN
	return swap_16(val);
#else
	return val;
#endif
}

static inline uint32_t bigtolittleendian32(uint32_t val)
{
	return ((val>>24)&0xff) | ((val<<8)&0xff0000) |
		((val>>8)&0xff00) | ((val<<24)&0xff000000);
}

static inline void ufs_waitms(uint32_t delay)
{
	while (delay--)
		udelay(1000);
}

static inline void dwc_ufs_write_reg(UINT reg_offset, UINT value)
{
	writel(value, ((void *)REG_BASE_UFS_ADDRESS + reg_offset));
}

static inline UINT dwc_ufs_read_reg(UINT reg_offset)
{
	UINT value;

	value = readl((void *)REG_BASE_UFS_ADDRESS + reg_offset);
	return value;
}

#define find_device_index() (0)

/* UFS Command Opcodes */
#define READ_DESC_OPCODE   0x1
#define WRITE_DESC_OPCODE  0x2
#define READ_ATTR_OPCODE   0x3
#define WRITE_ATTR_OPCODE  0x4
#define READ_FLAG_OPCODE   0x5
#define SET_FLAG_OPCODE    0x6
#define CLEAR_FLAG_OPCODE  0x7
#define TOGGLE_FLAG_OPCODE 0x8

/* Descriptor Idn's */
#define DEVICE_DESC        0x00
#define CONFIGURATION_DESC 0x01
#define UNIT_DESC          0x02
#define GEOMETRY_DESC      0x07
#define INTERCONNECT_DESC  0x04
#define STRING_DESC        0x05
#define POWER_DESC         0x08
#define HEALTH_DESC        0x09

#define QUERY_RESPONSE_HEAD_OFFSET (32)
#define QUERY_RESPONSE_DATA_OFFSET (2)
#define DEVICE_LUN 0xD0

#define DEVICE_DESC_LENGTH 0x40
#define UNIT_DESC_LENGTH   0x23
#define GEOMETRY_DESC_LENGTH 0x44
#define CONFIGURATION_DESC_LENGTH 0x90
#define INTERCONNECT_DESC_LENGTH 0x06
#define STRING_DESC_LENGTH 0xfe
#define POWER_DESC_LENGTH 0x62
#define HEALTH_DESC_LENGTH 0x25

#define STANDARD_RD_REQ 0x01
#define STANDARD_WR_REQ 0x81

enum info_show_type{
	UFS_INFO_SHOW_DEVICE_DESC = 0x00,
	UFS_INFO_SHOW_CONFIGURATION_DESC =  0x01,
	UFS_INFO_SHOW_UNIT_DESC= 0x02,
	UFS_INFO_SHOW_STRING_DESC = 0x05,
	UFS_INFO_SHOW_GEOMETRY_DESC = 0x07,
	UFS_INFO_SHOW_HEALTH_DESC = 0x09,
	UFS_INFO_SHOW_ALL = 0X10,
	UFS_INFO_SHOW_BASIC = 0XFF,
};

#define WELL_BOOT_LU_A  0x01
#define WELL_BOOT_LU_B  0x02

/*
 * UFSStatus/Error Macros used as return values for all functions
 */
enum {
	UFS_SUCCESS			=  0x00,
	UFS_LINK_STARTUP_FAIL		= -0x02,
	UFS_UTRD_DOORBELL_TIMEOUT	= -0x03,
	UFS_NOP_RESP_FAIL		= -0x04,
	UFS_INVALID_NOP_IN		= -0x05,
	UFS_UTMRD_DOORBELL_TIMEOUT	= -0x06,
	UFS_FDEVICE_INIT_FAIL		= -0x07,

	UFS_SOFTWARE_ERROR		= -0x0F,

	/* response upiu status error */
	RESP_STAT_CONDITION_MET		= -0x14,
	RESP_STAT_BUSY			= -0x15,
	RESP_STAT_RESERVATION_CONFLICT	= -0x16,
	RESP_STAT_TASK_SET_FULL		= -0x17,
	RESP_STAT_ACA_ACTIVE		= -0x18,
	RESP_STAT_TASK_ABORTED		= -0x19,
	RESP_STAT_UNKNOWN		= -0x1F,

#define RET_SENSE_KEY_OFF			(0x20)
	/* sense key */
	NO_SENSE                        = -0x20,
	RECOVERED_ERROR                 = -0x21,
	NOT_READY                       = -0x22,
	MEDIUM_ERROR                    = -0x23,
	HARDWARE_ERROR                  = -0x24,
	ILLEGAL_REQUEST                 = -0x25,
	UNIT_ATTENTION                  = -0x26,
	DATA_PROTECT                    = -0x27,
	BLANK_CHECK                     = -0x28,
	VENDOR_SPECIFIC                 = -0x29,
	ABORTED_COMMAND                 = -0x2B,
	VOLUME_OVERFLOW                 = -0x2D,
	MISCOMPARE                      = -0x2E,

	/* RPMB Operation Results */
	UFS_RPMB_GENERAL_FAILURE        = -0x31,
	UFS_AUTHENTICATION_FAILURE      = -0x32,
	UFS_COUNTER_FAILURE             = -0x33,
	UFS_ADDRESS_FAILURE             = -0x34,
	UFS_WRITE_FAILURE               = -0x35,
	UFS_READ_FAILURE                = -0x36,
	UFS_AUTH_KEY_NOT_PROGRAMMED     = -0x37,
	UFS_RPMB_WR_COUNTER_EXPIRED     = -0x38,
	UFS_NONCE_MISMATCH              = -0x39,
	UFS_MAC_MISMATCH                = -0x3a,

#define RET_UIC_CONFIG_ERROR_OFF		(0xA0)
	/* UIC Config Result Error */
	UFS_UIC_TIMEOUT			= -0xA0,
	INVALID_MIB_ATTRIBUTE		= -0xA1,
	INVALID_MIB_ATTRIBUTE_VALUE	= -0xA2,
	READ_ONLY_MIB_ATTRIBUTE		= -0xA3,
	WRITE_ONLY_MIB_ATTRIBUTE	= -0xA4,
	BAD_INDEX			= -0xA5,
	LOCKED_MIB_ATTRIBUTE		= -0xA6,
	BAD_TEST_FEATURE_INDEX		= -0xA7,
	PEER_COMMUNICATION_FAILURE	= -0xA8,
	BUSY				= -0xA9,
	DME_FAILURE			= -0xAA,

#define RET_UTRD_OCS_ERROR_OFF			(0xB0)
	/* utrd ocs error */
	INVALID_COMMAND_TABLE_ATTRIBUTES = -0xB1,
	INVALID_PRDT_ATTRIBUTES          = -0xB2,
	MISMATCH_DATA_BUFFER_SIZE        = -0xB3,
	MISMATCH_RESPONSE_UPIU_SIZE      = -0xB4,
	COMMUNICATION_FAILURE            = -0xB5,
	ABORTED                          = -0xB6,
	FATAL_ERROR                      = -0xB7,
	INVALID_OCS_VALUE                = -0xBF,

	/* Query response code */
	QUERY_PARAMETER_NOT_READABLE	= -0xF6,
	QUERY_PARAMETER_NOT_WRITEABLE	= -0xF7,
	QUERY_PARAMETER_ALREADY_WRITTEN	= -0xF8,
	QUERY_INVALID_LENGTH		= -0xF9,
	QUERY_INVALID_VALUE		= -0xFA,
	QUERY_INVALID_SELECTOR		= -0xFB,
	QUERY_INVALID_INDEX		= -0xFC,
	QUERY_INVALID_IDN		= -0xFD,
	QUERY_INVALID_OPCODE		= -0xFE,
	QUERY_GENERAL_FAILURE		= -0xFF
};

/* DME Commands */
enum {
	DWC_UFS_DME_GET = 0x01,
	DWC_UFS_DME_SET = 0x02,
	DWC_UFS_DME_PEER_GET = 0x03,
	DWC_UFS_DME_PEER_SET = 0x04,
	DWC_UFS_DME_POWERON = 0x10,
	DWC_UFS_DME_POWEROFF = 0x11,
	DWC_UFS_DME_ENABLE = 0x12,
	DWC_UFS_DME_RESET = 0x14,
	DWC_UFS_DME_ENDPOINTRESET = 0x15,
	DWC_UFS_DME_LINKSTARTUP = 0x16,
	DWC_UFS_DME_HIBERNATE_ENTER = 0x17,
	DWC_UFS_DME_HIBERNATE_EXIT = 0x18,
	DWC_UFS_DME_TEST_MODE = 0x1A,
};
/* DME Result Codes */
enum {
	DWC_UFS_DME_SUCCESS = 0x00,
	DWC_UFS_DME_INV_MIB_ATTR = 0x01,
	DWC_UFS_DME_INV_MIB_ATTR_VAL = 0x02,
	DWC_UFS_DME_READ_ONLY_MIB_ATTR = 0x03,
	DWC_UFS_DME_WRITE_ONLY_MIB_ATTR = 0x04,
	DWC_UFS_DME_BAD_INDEX = 0x05,
	DWC_UFS_DME_LOCKED_MIB_ATTR = 0x06,
	DWC_UFS_DME_BAD_TEST_FEAT_INDEX = 0x07,
	DWC_UFS_DME_PEER_COMM_FAILURE = 0x08,
	DWC_UFS_DME_BUSY = 0x09,
	DWC_UFS_DME_FAILURE = 0x0a,

	DWC_UFS_DME_RESULT_CODE_MASK = 0xff,
};
/* DME Reset type */
enum {
	DWC_UFS_DME_RESET_LEVEL_COLD = 0,
	DWC_UFS_DME_RESET_LEVEL_WARM = 1,
};
/* DME attribute whether normal or static */
enum {
	DWC_UFS_DME_ATTR_SET_TYPE_NORMAL = 0,
	DWC_UFS_DME_ATTR_SET_TYPE_STATIC = 1,
};

/* UTP Transfer Request Data Direction (DD) */
enum {
	UTP_NO_DATA_TRANSFER = 0x00,
	UTP_HOST_TO_DEVICE = 0x02,
	UTP_DEVICE_TO_HOST = 0x04
};

/* UPIU Read/Write flags */
enum {
	UPIU_CMD_FLAGS_NONE = 0x00,
	UPIU_CMD_FLAGS_WRITE = 0x20,
	UPIU_CMD_FLAGS_READ = 0x40
};

enum {
	UTP_SCSI_COMMAND = 0x00,
	UTP_NATIVE_UFS_COMMAND = (1 << 4),
	UTP_DEVICE_MANAGEMENT_FUNCTION = (2 << 4)
};

enum {
	UTP_UFS_STORAGE_COMMAND = (1 << 4)
};

enum flags_id {
	FDEVICE_INIT = 0x1,
	FPERMANANT_WPEN = 0x2,
	FPOWERON_WPEN = 0x3,
	FBG_OPSEN = 0x4,
	FPURGE_OPSEN = 0x6,
	FPHYRES_REMOVAL = 0x8,
	FBUSY_RTC = 0x9
};

enum tm_task_type {
	ABORT_TASK = 0x1,
	ABORT_TASK_SET = 0x2,
	CLEAR_TASK_SET = 0x4,
	LUN_RESET = 0x8,
	QUERY_TASK = 0x80,
	QUERY_TASK_SET = 0x81
};

 /*bCurrent PowerMode */
enum {
	CURRENT_POWER_MODE_IDLE = 0x00,
	CURRENT_POWER_MODE_PRE_ACTIVE = 0x10,
	CURRENT_POWER_MODE_ACTIVE = 0x11,
	CURRENT_POWER_MODE_PRE_SLEEP = 0x20,
	CURRENT_POWER_MODE_SLEEP = 0x22,
	CURRENT_POWER_MODE_PRE_POWERDOWN = 0x30,
	CURRENT_POWER_MODE_POWERDOWN = 0x33
};
/*use for unipro & M-PHY 's configuration and control*/
enum uic_dme_type {
	/*Configuration */
	DME_GET = 0x01,
	DME_SET = 0x02,
	DME_PEER_GET = 0x03,
	DME_PEER_SET = 0x04,
	/*Control */
	DME_POWERON = 0x10,
	DME_POWEROFF = 0x11,
	DME_ENABLE = 0x12,

	DME_Reserve_1 = 0x13,
	DME_RESET = 0x14,
	DME_ENDPOINTRESET = 0x15,
	DME_LINKSTARTUP = 0x16,
	DME_HIBERNATE_ENTER = 0x17,
	DME_HIBERNATE_EXIT = 0x18,
	DME_Reserve_2 = 0x19,
	DME_TEST_MODE = 0x1A,
};

enum attr_id {
	B_BOOT_LUNEN = 0x0,
	B_CURRENT_PM = 0x2,
	B_ACTIV_ICC_LEVEL = 0x3,
	B_OUT_OF_ORDER_DATAEN = 0x4,
	B_BCKGND_OPS_STATUS = 0x5,
	B_PURGE_STATUS = 0x6,
	B_MAX_DATA_IN_SIZE = 0x7,
	B_MAX_DATA_OUT_SIZE = 0x8,
	D_DYN_CAP_NEEDED = 0x9,
	B_REFCLK_FREQ = 0xA,
	B_CONFIG_DESC_LOCK = 0xB,
	B_MAX_NUM_OF_RTT = 0xC,
	W_EXCEPTION_EVENT_CONTROL = 0xD,
	W_EXCEPTION_EVENT_STATUS = 0xE,
	D_SECONDS_PASSED = 0xF,
	W_CONTEXT_CONF = 0x10,
	D_CORR_PRG_BLKNUM = 0x11
};

/* Operation Type for RPMB tasks */
enum opn_type {
	WRITE_COUNTER_READ = 0x00,
	WRITE_RPMB_DATA = 0x01,
	READ_RPMB_DATA = 0x02,
	RESULT_REGISTER_READ = 0x03,
	AUTH_KEY_DATA = 0x04
};

struct tm_task_request {
	enum tm_task_type tm_function;
	enum tm_task_resp expect_result;
	u8 lun;
	u8 operate_task_tag;
};

static inline void set_bits(unsigned int  mask, unsigned long int addr)
{
	(*(volatile unsigned int *) (addr)) |= mask;
}

#define GET_LOCAL_DWC_HOST() \
	int index = find_device_index(); \
	struct dwc_ufs_hba *dwc_host = &g_dwc_host[index];

int ufs_format_unit(void);
int ufs_set_bootlun(uint8_t lun);
int ufs_set_active_lun(uint8_t lun);

int ufs_read_boot_storage(uint64_t dest_addr, uint64_t src_offset,
						  uint32_t size);
int ufs_write_boot_storage(uint64_t dest_addr, uint64_t src_offset,
	uint32_t size);
int ufs_read_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size);
int ufs_write_storage(uint64_t src_addr, uint64_t dest_offset, uint32_t size);
void send_uic_command(uint32_t command, uint32_t arg1, uint32_t arg2,
		      uint32_t arg3);
int ufs_unmap(uint64_t start_lba, uint32_t blk_cnt);
int ufs_set_mode_page(uint32_t page, const struct ufs_mode_page_para *para,
		      uint32_t save_pages);
int ufs_get_max_lba(uint32_t *max_addr);
int ufs_set_flag(enum flags_id idn, uint8_t *flags_ret);
int ufs_read_flag(enum flags_id idn, uint8_t *flags_ret);
int ufs_clear_flag(enum flags_id idn, uint8_t *flags_ret);
int ufs_toggle_flag(enum flags_id idn, uint8_t *flags_ret);

int read_descriptor(const void *req_upiu, void **resp_upiu);
int write_descriptor(const void *req_upiu);
void modify_desc_upiu(const struct desc_params *params);

int read_attribute(enum attr_id idn, uint8_t indexx, uint8_t selector,
		uint32_t *ret_value);
int write_attribute(enum attr_id idn, uint8_t indexx, uint8_t selector,
		uint32_t *value);

int dwc_ufshcd_drv_init(struct dwc_ufs_hba *hba);
int pressure_multi_slot_write(uint8_t simultaneouts,
		uint8_t observe);
int pressure_multi_slot_read(uint8_t simultaneouts,
		uint8_t observe);
int pressure_multi_slot_mix(uint8_t simultaneouts,
		uint8_t observe);
uint8_t dwc_ufshcd_get_xfer_req_free_slot(struct dwc_ufs_hba *hba);
int wait_for_cmd_completion(uint32_t slot_mask);
int wait_for_cmd_completion_async(uint32_t doorbell, uint32_t slot_mask);
int dwc_ufshcd_initialize_hba_desc_pointers(const struct dwc_ufs_hba *hba);
int wait_for_utrl_doorbell_clean(uint32_t slot_mask);
int wait_for_utmrl_doorbell_clean(uint32_t slot_mask);
void create_tm_req(enum tm_task_type tm_func, uint32_t lun, uint32_t task_tag,
		uint8_t free_slot);
int wait_for_tm_completion(uint32_t slot_mask);
int handle_tm_completion(uint32_t *output);
void dwc_ufshcd_config_intr_aggregation(const struct dwc_ufs_hba *hba,
		int option);
void dwc_ufshcd_configure_interrupt(const struct dwc_ufs_hba *hba,
		u32 option);
uint8_t dwc_ufshcd_get_tm_req_free_slot(struct dwc_ufs_hba *hba);
int ufs_read_config_description(void);
int GetWriteCounterValue(uint8_t *counter, const uint8_t *nonce_val);
void get_rpmb_dataframes(uint8_t *rpmb_buf, enum opn_type opn,
		const uint8_t counter[4], const uint8_t *src_addr,
		uint16_t rpmb_blk_addr, uint16_t size, const uint8_t key[32],
		const uint8_t *nonce_val);
int ReadRPMBData(uint8_t *destAddr, uint16_t srcAddr, uint32_t size,
		const uint8_t *nonce_val, const uint8_t key[]);
int ufs_lu_init(void);
void ufs_reg_dump(void);

int ufs_init(enum POWER_MODE mode, int hs_gear, int rate, int lane,
			 int scramble, int termination);

int ufs_storage_init(void);
int ufs_read_storage(uint64_t src_addr, uint64_t dest_offset, uint32_t size);
int ufs_write_storage(uint64_t src_addr, uint64_t dest_offset, uint32_t size);
int ufs_hibernate_exit(int psw);
int ufs_hibernate_enter(int psw);
void ufs_readreg_all(void);
void ufs_reg_param(int argc,char *const argv[]);
int ufs_show_desc_info(enum info_show_type type);
#endif

