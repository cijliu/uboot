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
#include "hdmi_osal.h"
#include "hdmi_hal_frl.h"
#include "hdmi_reg_frl.h"
#include "hdmi_reg_aon.h"
#include "hdmi_reg_ctrl.h"
#include "hdmi_hal_ddc.h"
#include "hdmi_hal_machine.h"
#include "hdmi_product_define.h"
#include "hdmi_hal_scdc.h"
#include "hdmi_hal_phy.h"

#ifdef HDMI_SYS_NOHIGH_TIMERS
#include "hdmi_hal_timer.h"
#include "hdmi_reg_timer.h"
#endif
/******************************************************************************/
/******************************Macro define************************************/
/******************************************************************************/
#define HW_TRAINING

#define FRL_NULL_CHECK(p)\
do\
{\
    if(HI_NULL == p)\
    {\
        HDMI_WARN("%s is null pointer!return fail.\n",#p);\
        return HI_FAILURE;\
    }\
}while(0)

#define FRL_NULL_CHECK_NO_RET(p)\
do\
{\
    if(HI_NULL == p)\
    {\
        HDMI_WARN("%s is null pointer!return fail.\n",#p);\
        return;\
    }\
}while(0)

#define FRL_INT_NULL_CHECK(p)\
do\
{\
    if(HI_NULL == p)\
    {\
        return;\
    }\
}while(0)

/******************************************************************************/
/*****************************Private data            *************************/
/******************************************************************************/

typedef struct
{
	HI_U32 u32RamAddr;
	HI_U32 u32WrData;
	HI_U8  u89Bor7B;
}LM_TABLE_CONFIG_S;

/******************************************************************************/
/*****************************Global Data            **************************/
/******************************************************************************/

static FRL_INFO_S s_stFrlInfo[HDMI_DEVICE_ID_BUTT];

/*FRL 9B10B coding table */
const static HI_U32 s_aLm9B10B[512] = {
 0x34B2D2, 0x8B1D32, 0x52AB52, 0xC18F92, 0x62A752, 0xA19792, 0x61A792, 0xE087D2,
 0x32B352, 0x919B92, 0x51AB92, 0xD08BD2, 0x31B392, 0xB093D2, 0x722372, 0xD10BB2,
 0x8D1CB2, 0x899D92, 0x49AD92, 0xC88DD2, 0x29B592, 0xA895D2, 0x64A6D2, 0xE87A10,
 0x19B992, 0x9899D2, 0x58A9D2, 0xD87610, 0x38B1D2, 0xB86E10, 0x785E10, 0xD20B72,
 0x8C9CD2, 0x859E92, 0x45AE92, 0xC40EF4, 0x25B692, 0xA416F4, 0x6426F4, 0xE47910,
 0x15BA92, 0x941AF4, 0x542AF4, 0xD47510, 0x3432F4, 0xB46D10, 0x745D10, 0xBFD00 ,
 0x2E3472, 0x8C1CF4, 0x4C2CF4, 0xCC7310, 0x2C34F4, 0xAC6B10, 0x6C5B10, 0x13FB00,
 0x1C38F4, 0x9C6710, 0x5C5710, 0x23F700, 0x3C4F10, 0x43EF00, 0x83DF00, 0x70A3D2,
 0x4E2C72, 0x961A72, 0x562A72, 0xC20F74, 0x363272, 0xA21774, 0x622774, 0xE27890,
 0x532B32, 0x921B74, 0x522B74, 0xD27490, 0x323374, 0xB26C90, 0x725C90, 0xDFC80 ,
 0xCA0D72, 0x8A1D74, 0x4A2D74, 0xCA7290, 0x2A3574, 0xAA6A90, 0x6A5A90, 0xEA3A80,
 0x1A3974, 0x9A6690, 0x5A5690, 0xDA3680, 0x3A4E90, 0xBA2E80, 0x7A1E80, 0x6A2572,
 0xC60E72, 0x861E74, 0x462E74, 0xC67190, 0x263674, 0xA66990, 0x665990, 0xE63980,
 0x163A74, 0x966590, 0x565590, 0xD63580, 0x364D90, 0xB62D80, 0x761D80, 0xA61672,
 0xE3C74 , 0x8E6390, 0x4E5390, 0xCE3380, 0x2E4B90, 0xAE2B80, 0x6E1B80, 0x11FB82,
 0x1E4790, 0x9E2780, 0x5E1780, 0x21F782, 0x3E0F80, 0x41EF82, 0x81DF82, 0x9A1972,
 0x4D2CB2, 0x871E32, 0x472E32, 0xC10FB4, 0x273632, 0xA117B4, 0x6127B4, 0xE17850,
 0x173A32, 0x911BB4, 0x512BB4, 0xD17450, 0x3133B4, 0xB16C50, 0x715C50, 0xEFC40 ,
 0xC90DB2, 0x891DB4, 0x492DB4, 0xC97250, 0x2935B4, 0xA96A50, 0x695A50, 0xE93A40,
 0x1939B4, 0x996650, 0x595650, 0xD93640, 0x394E50, 0xB92E40, 0x791E40, 0x6925B2,
 0xC50EB2, 0x851EB4, 0x452EB4, 0xC57150, 0x2536B4, 0xA56950, 0x655950, 0xE53940,
 0x153AB4, 0x956550, 0x555550, 0xD53540, 0x354D50, 0xB52D40, 0x751D40, 0xA516B2,
 0xD3CB4 , 0x8D6350, 0x4D5350, 0xCD3340, 0x2D4B50, 0xAD2B40, 0x6D1B40, 0x12FB42,
 0x1D4750, 0x9D2740, 0x5D1740, 0x22F742, 0x3D0F40, 0x42EF42, 0x82DF42, 0x9919B2,
 0xC30F32, 0x831F34, 0x432F34, 0xC370D0, 0x233734, 0xA368D0, 0x6358D0, 0xE338C0,
 0x133B34, 0x9364D0, 0x5354D0, 0xD334C0, 0x334CD0, 0xB32CC0, 0x731CC0, 0xA31732,
 0xB3D34 , 0x8B62D0, 0x4B52D0, 0xCB32C0, 0x2B4AD0, 0xAB2AC0, 0x6B1AC0, 0x14FAC2,
 0x1B46D0, 0x9B26C0, 0x5B16C0, 0x24F6C2, 0x3B0EC0, 0x44EEC2, 0x84DEC2, 0x931B32,
 0x2B3532, 0x8761D0, 0x4751D0, 0xC731C0, 0x2749D0, 0xA729C0, 0x6719C0, 0x18F9C2,
 0x1745D0, 0x9725C0, 0x5715C0, 0x28F5C2, 0x370DC0, 0x48EDC2, 0x88DDC2, 0x333332,
 0x1CB8D2, 0x8F23C0, 0x4F13C0, 0x30F3C2, 0x2F0BC0, 0x50EBC2, 0x90DBC2, 0x10FBC4,
 0x1F07C0, 0x60E7C2, 0xA0D7C2, 0x20F7C4, 0xC0CFC2, 0x40EFC4, 0x80DFC4, 0xA915B2,
 0x2AB552, 0x869E52, 0x46AE52, 0xC08FD4, 0x26B652, 0xA097D4, 0x60A7D4, 0xE0F830,
 0x16BA52, 0x909BD4, 0x50ABD4, 0xD0F430, 0x30B3D4, 0xB0EC30, 0x70DC30, 0xF7C20 ,
 0x8A9D52, 0x889DD4, 0x48ADD4, 0xC8F230, 0x28B5D4, 0xA8EA30, 0x68DA30, 0xE8BA20,
 0x18B9D4, 0x98E630, 0x58D630, 0xD8B620, 0x38CE30, 0xB8AE20, 0x789E20, 0x68A5D2,
 0xC48ED2, 0x849ED4, 0x44AED4, 0xC4F130, 0x24B6D4, 0xA4E930, 0x64D930, 0xE4B920,
 0x14BAD4, 0x94E530, 0x54D530, 0xD4B520, 0x34CD30, 0xB4AD20, 0x749D20, 0xA496D2,
 0xCBCD4 , 0x8CE330, 0x4CD330, 0xCCB320, 0x2CCB30, 0xACAB20, 0x6C9B20, 0x137B22,
 0x1CC730, 0x9CA720, 0x5C9720, 0x237722, 0x3C8F20, 0x436F22, 0x835F22, 0x949AD2,
 0xC28F52, 0x829F54, 0x42AF54, 0xC2F0B0, 0x22B754, 0xA2E8B0, 0x62D8B0, 0xE2B8A0,
 0x12BB54, 0x92E4B0, 0x52D4B0, 0xD2B4A0, 0x32CCB0, 0xB2ACA0, 0x729CA0, 0xE20772,
 0xABD54 , 0x8AE2B0, 0x4AD2B0, 0xCAB2A0, 0x2ACAB0, 0xAAAAA0, 0x6A9AA0, 0x157AA2,
 0x1AC6B0, 0x9AA6A0, 0x5A96A0, 0x2576A2, 0x3A8EA0, 0x456EA2, 0x855EA2, 0x929B52,
 0xA29752, 0x86E1B0, 0x46D1B0, 0xC6B1A0, 0x26C9B0, 0xA6A9A0, 0x6699A0, 0x1979A2,
 0x16C5B0, 0x96A5A0, 0x5695A0, 0x2975A2, 0x368DA0, 0x496DA2, 0x895DA2, 0x97DA4 ,
 0x1E3872, 0x8EA3A0, 0x4E93A0, 0x3173A2, 0x2E8BA0, 0x516BA2, 0x915BA2, 0x117BA4,
 0x1E87A0, 0x6167A2, 0xA157A2, 0x2177A4, 0xC14FA2, 0x416FA4, 0x815FA4, 0xAA1572,
 0x54AAD2, 0x819F94, 0x41AF94, 0xC1F070, 0x21B794, 0xA1E870, 0x61D870, 0xE1B860,
 0x11BB94, 0x91E470, 0x51D470, 0xD1B460, 0x31CC70, 0xB1AC60, 0x719C60, 0xE107B2,
 0x9BD94 , 0x89E270, 0x49D270, 0xC9B260, 0x29CA70, 0xA9AA60, 0x699A60, 0x167A62,
 0x19C670, 0x99A660, 0x599660, 0x267662, 0x398E60, 0x466E62, 0x865E62, 0x3931B2,
 0x951AB2, 0x85E170, 0x45D170, 0xC5B160, 0x25C970, 0xA5A960, 0x659960, 0x1A7962,
 0x15C570, 0x95A560, 0x559560, 0x2A7562, 0x358D60, 0x4A6D62, 0x8A5D62, 0xA7D64 ,
 0x1D38B2, 0x8DA360, 0x4D9360, 0x327362, 0x2D8B60, 0x526B62, 0x925B62, 0x127B64,
 0x1D8760, 0x626762, 0xA25762, 0x227764, 0xC24F62, 0x426F64, 0x825F64, 0x7123B2,
 0x1AB952, 0x839F12, 0x43AF12, 0xC3B0E0, 0x23B712, 0xA3A8E0, 0x6398E0, 0x1C78E2,
 0x13BB12, 0x93A4E0, 0x5394E0, 0x2C74E2, 0x338CE0, 0x4C6CE2, 0x8C5CE2, 0xC7CE4 ,
 0x1B3932, 0x8BA2E0, 0x4B92E0, 0x3472E2, 0x2B8AE0, 0x546AE2, 0x945AE2, 0x147AE4,
 0x1B86E0, 0x6466E2, 0xA456E2, 0x2476E4, 0xC44EE2, 0x446EE4, 0x845EE4, 0xB21372,
 0x8E1C72, 0x87A1E0, 0x4791E0, 0x3871E2, 0x2789E0, 0x5869E2, 0x9859E2, 0x1879E4,
 0x1785E0, 0x6865E2, 0xA855E2, 0x2875E4, 0xC84DE2, 0x486DE4, 0x885DE4, 0x3532B2,
 0xFBC10 , 0x7063E2, 0xB053E2, 0x3073E4, 0xD04BE2, 0x506BE4, 0x905BE4, 0x4AAD52,
 0xE047E2, 0x6067E4, 0xA057E4, 0x4CACD2, 0x3A3172, 0x2CB4D2, 0x2D34B2, 0x5A2972,
};

/*FRL 7B8B coding table */
const static HI_U32 s_aLm7B8B[128] = {
    0x946B2, 0x8C732, 0x4CB32, 0xC8372, 0x2CD32, 0xA8572, 0x68972, 0xE1E10,
    0x926D2, 0x98672, 0x58A72, 0xD1D10, 0x38C72, 0xB1B10, 0x71710, 0xFF00 ,
    0x8A752, 0x88774, 0x48B74, 0xC9C90, 0x28D74, 0xA9A90, 0x69690, 0xE8E80,
    0x18E74, 0x99990, 0x59590, 0xD8D80, 0x39390, 0xB8B80, 0x78780, 0x16E92,
    0x54AB2, 0x847B4, 0x44BB4, 0xC5C50, 0x24DB4, 0xA5A50, 0x65650, 0xE4E40,
    0x14EB4, 0x95950, 0x55550, 0xD4D40, 0x35350, 0xB4B40, 0x74740, 0x1AE52,
    0xC43B2, 0x8D8D0, 0x4D4D0, 0xCCCC0, 0x2D2D0, 0xACAC0, 0x6C6C0, 0x13EC2,
    0x1D1D0, 0x9C9C0, 0x5C5C0, 0x23DC2, 0x3C3C0, 0x43BC2, 0x837C2, 0x34CB2,
    0x52AD2, 0x827D4, 0x42BD4, 0xC3C30, 0x22DD4, 0xA3A30, 0x63630, 0xE2E20,
    0x12ED4, 0x93930, 0x53530, 0xD2D20, 0x33330, 0xB2B20, 0x72720, 0x1CE32,
    0xC23D2, 0x8B8B0, 0x4B4B0, 0xCACA0, 0x2B2B0, 0xAAAA0, 0x6A6A0, 0x15EA2,
    0x1B1B0, 0x9A9A0, 0x5A5A0, 0x25DA2, 0x3A3A0, 0x45BA2, 0x857A2, 0x629D2,
    0x26D92, 0x87870, 0x47470, 0xC6C60, 0x27270, 0xA6A60, 0x66660, 0x19E62,
    0x17170, 0x96960, 0x56560, 0x29D62, 0x36360, 0x49B62, 0x89762, 0x32CD2,
    0x4AB52, 0x8E8E0, 0x4E4E0, 0x31CE2, 0x2E2E0, 0x51AE2, 0x916E2, 0x2AD52,
    0x1E1E0, 0x619E2, 0xA15E2, 0x86792, 0xC13E2, 0xA45B2, 0x649B2, 0xA25D2,
};

/******************************************************************************/
/*****************************private  interface         **********************/
/******************************************************************************/
static FRL_INFO_S* FrlInfoPtrGet(HDMI_DEVICE_ID_E enHdmi)
{

	if (enHdmi < HDMI_DEVICE_ID_BUTT)
	{
		return &s_stFrlInfo[enHdmi];
	}

	return HI_NULL;
}

HI_S32 FrlGetLtpReq(HDMI_DEVICE_ID_E enHdmi, HI_U8 *pu8Ltp)
{
    HI_U32 i = 0;
    SCDC_LTP_REQ_S stLtpReq = {0};

    for (i = 0;  i < 4; i++)
    {
        FRL_NULL_CHECK(&pu8Ltp[i]);
    }

    HAL_HDMI_ScdcCtrl(enHdmi, SCDC_CMD_GET_LTP_REQ, &stLtpReq);

    pu8Ltp[0] = stLtpReq.u8Ln0Ltp;
    pu8Ltp[1] = stLtpReq.u8Ln1Ltp;
    pu8Ltp[2] = stLtpReq.u8Ln2Ltp;
    pu8Ltp[3] = stLtpReq.u8Ln3Ltp;

    return HI_SUCCESS;
}


HI_S32 FrlSetFrlNoTimeOut(HI_BOOL bNoTimeOut)
{
    HDMI_CPU_CFG_SEL_flt_no_timeoutSet(bNoTimeOut);
    return HI_SUCCESS;
}

HI_S32 FrlHwVersionGet(FRL_VERSION_INFO_S *pstVersionInfo)
{
    FRL_NULL_CHECK(pstVersionInfo);

    pstVersionInfo->u32Year = HDMI_TX_FRL_VERSION_frl_tx_hw_yearGet();
	pstVersionInfo->u32Month = HDMI_TX_FRL_VERSION_frl_tx_hw_monthGet();
	pstVersionInfo->u32Day = HDMI_TX_FRL_VERSION_frl_tx_hw_dayGet();

    return HI_SUCCESS;
}

HI_S32 FrlLMRfdInitSet(HI_U32 u32LaneIdx, HI_U32 u32Value)
{
    switch(u32LaneIdx)
    {
        case FRL_LANE_IDX_0:
            HDMI_LM_CODE_RFD_code_rfd_init0Set(u32Value);
            break;
        case FRL_LANE_IDX_1:
            HDMI_LM_CODE_RFD_code_rfd_init1Set(u32Value);
            break;
        case FRL_LANE_IDX_2:
            HDMI_LM_CODE_RFD_code_rfd_init2Set(u32Value);
            break;
        case FRL_LANE_IDX_3:
            HDMI_LM_CODE_RFD_code_rfd_init3Set(u32Value);
            break;
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 FrlLMScrInitSet(HI_U32 u32LaneIdx, HI_U32 u32Value)
{
    switch(u32LaneIdx)
    {
        case FRL_LANE_IDX_0:
            HDMI_LM_SRC_INIT0_lane0_init_valueSet(u32Value);
            break;
        case FRL_LANE_IDX_1:
            HDMI_LM_SRC_INIT0_lane1_init_valueSet(u32Value);
            break;
        case FRL_LANE_IDX_2:
            HDMI_LM_SRC_INIT1_lane2_init_valueSet(u32Value);
            break;
        case FRL_LANE_IDX_3:
            HDMI_LM_SRC_INIT1_lane3_init_valueSet(u32Value);
            break;
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 FrlScrambleEnble(HI_BOOL bEnable)
{
    HDMI_LM_SRC_EN_scram_enSet(bEnable);

    return HI_SUCCESS;
}

HI_S32 FrlLineStartHsyncEnable(HI_BOOL bEnable)
{
    HDMI_LINE_START_HSYNC_EN_line_start_hsync_enSet(bEnable);

    return HI_SUCCESS;
}

HI_S32 FrlScdcConfigInSet(HI_U32 u32Value)
{
    HDMI_SCDCS_CONFIG_scdcs_config_inSet(u32Value);

    return HI_SUCCESS;
}

HI_S32 FrlTimerInfoSet(FRL_TIMER_INFO_S stTimerInfo)
{
    /*0x3414 UPDATE_FLAG_TIMER*/
	HDMI_UPDATE_FLAG_TIMER_update_flag_timerSet(stTimerInfo.u32FltUpdateTimeOut);
	/*0x3418 FLT_STEP_TIMER*/
	HDMI_FLT_STEP_TIMER_step_timeout_timerSet(stTimerInfo.u32FltStepTimeOut);
	/*0x341c FLT_TIMEOUT_TIMER*/
	HDMI_FLT_TIMEOUT_TIMER_flt_timeout_timerSet(stTimerInfo.u32FltTimeOut);

    return HI_SUCCESS;
}

HI_S32 FrlWorkEnSet(HI_BOOL bEnable)
{
    HDMI_WORK_EN_work_enSet(bEnable);

    return HI_SUCCESS;
}

HI_S32 FrlChannelModeSet(HI_U8 u8ChannelMode)
{
    HDMI_CPU_SET_RES_soft_train_okSet(u8ChannelMode);

    return HI_SUCCESS;
}

HI_S32 FrlTrainingEnable(HI_BOOL bEnable)
{
    HDMI_FLT_START_flt_startSet(bEnable);
    HDMI_UDELAY(1);
    HDMI_FLT_START_flt_startSet(!bEnable);

    return HI_SUCCESS;
}

HI_S32 FrlReset(HI_VOID)
{
    HDMI_TX_PWD_RST_CTRL_frl_soft_arst_reqSet(1);
    HDMI_UDELAY(1);
    HDMI_TX_PWD_RST_CTRL_frl_soft_arst_reqSet(0);

    return HI_SUCCESS;
}

HI_S32 FrlTrainingPatternSet(HI_U8 u8LaneIdx, HI_U8 u8Pattern)
{
    switch (u8LaneIdx)
    {
        case FRL_LANE_IDX_0:
            HDMI_CPU_SET_PATTERN_lane0_train_ptnSet(u8Pattern);
            break;
        case FRL_LANE_IDX_1:
            HDMI_CPU_SET_PATTERN_lane1_train_ptnSet(u8Pattern);
            break;
        case FRL_LANE_IDX_2:
            HDMI_CPU_SET_PATTERN_lane2_train_ptnSet(u8Pattern);
            break;
        case FRL_LANE_IDX_3:
            HDMI_CPU_SET_PATTERN_lane3_train_ptnSet(u8Pattern);
            break;
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 FrlLaneLoop(HI_U8 *pu8Ltp, HI_U8 u8LaneNum, HI_BOOL bFrlNoTimeout, HDMI_PHY_TMDS_CFG_S *pstTmdsCfg)
{
    HI_U8 u8LaneIdx = 0;
    HI_BOOL bChangePtn = HI_FALSE;
    HI_BOOL bFFESet = HI_FALSE;

    FRL_NULL_CHECK(pu8Ltp);
    FRL_NULL_CHECK(pstTmdsCfg);

    if (u8LaneNum > 4)
    {
        return HI_FAILURE;
    }

    for (u8LaneIdx = 0; u8LaneIdx < u8LaneNum; u8LaneIdx++)
    {
        bChangePtn = ((pu8Ltp[u8LaneIdx] > 0 && pu8Ltp[u8LaneIdx] < 3)
                      || (pu8Ltp[u8LaneIdx] > 3 && pu8Ltp[u8LaneIdx] < 9)
                      || (pu8Ltp[u8LaneIdx] == 3 && bFrlNoTimeout))
                      ? HI_TRUE : HI_FALSE;
        bFFESet = (pu8Ltp[u8LaneIdx] == 0xE) ? HI_TRUE : HI_FALSE;;

        if (bFFESet)
        {
            /* PHY FFE Setting */
            pstTmdsCfg->aenTxFFE[u8LaneIdx] = (pstTmdsCfg->aenTxFFE[u8LaneIdx] >= FRL_TXFFE_MODE_3) ? \
                                                   FRL_TXFFE_MODE_3 : (pstTmdsCfg->aenTxFFE[u8LaneIdx] + 1);
            pstTmdsCfg->enModeCfg = HDMI_PHY_MODE_CFG_TXFFE;
            HAL_HDMI_PhyTmdsSet(pstTmdsCfg);
//            HDMI_INFO("TxFFE change, Lan:%d\n", u8LaneIdx);
        }
        else if (bChangePtn)
        {
//            HDMI_INFO("Pattern change, Lan%d, %d\n", u8LaneIdx, pu8Ltp[u8LaneIdx]);
            FrlTrainingPatternSet(u8LaneIdx, pu8Ltp[u8LaneIdx]);
        }
        else
        {
//            HDMI_INFO("Sink Lane(%d) LTP req = LTP%d \r\n", u8LaneIdx, pu8Ltp[u8LaneIdx]);
        }
    }

    return HI_SUCCESS;
}

#ifdef HDMI_SYS_NOHIGH_TIMERS
/* use timer11 to delay 2ms */
typedef struct FrlTimerParam_s
{
    HI_U8               u8LaneNum;
    FRL_INFO_S          *pstInfo;
    HDMI_PHY_TMDS_CFG_S *pstTmdsCfg;
    HI_U64              u64StartTime;
    HI_U32              u32FrlTimeOut;
}FRL_TIMER_PARAM_S;

HI_VOID FrlTraningInterrupt(HI_VOID *pParam)
{
    HI_U8    au8Ltp[4]              = {0};
    HI_BOOL  bUpdate                = HI_FALSE;
    HI_BOOL  bClrUpdate             = HI_FALSE;
    HI_BOOL  bTrainSuccess          = HI_FALSE;
    HI_BOOL  bChangeRate            = HI_FALSE;
    HI_U8    u8LaneNum              = 0;
    HI_BOOL  bFrlNoTimeout          = HI_FALSE;
    HI_U32   u32FrlTimeOut          = 0;
    FRL_INFO_S          *pstInfo    = HI_NULL;
    FRL_TRAIN_RESULT_S  *pstResult  = HI_NULL;
    HDMI_PHY_TMDS_CFG_S *pstTmdsCfg = HI_NULL;
    FRL_TIMER_PARAM_S   *pstParam   = HI_NULL;

    FRL_INT_NULL_CHECK(pParam);

    pstParam = (FRL_TIMER_PARAM_S *)pParam;
    u8LaneNum = pstParam->u8LaneNum;

    pstInfo = pstParam->pstInfo;
    FRL_INT_NULL_CHECK(pstInfo);

    pstResult = &pstInfo->stStatus.stTrainInfo.stResult;
    FRL_INT_NULL_CHECK(pstResult);

    pstTmdsCfg = pstParam->pstTmdsCfg;
    FRL_INT_NULL_CHECK(pstTmdsCfg);

    bFrlNoTimeout = pstInfo->stCFG.bFrlNoTimeout;
    u32FrlTimeOut = pstParam->u32FrlTimeOut;

    if ((HAL_HDMI_MachMsGet() - pstParam->u64StartTime > u32FrlTimeOut) && !bFrlNoTimeout)
    {
        /*Time out,Training Fail;*/
        pstResult->enTrainStatus = FRL_TRAIN_FAIL;
        pstResult->enFailRes = FRL_TRAIN_FAIL_RES_FLTTIMEOUT;
        return ;
    }

    HAL_HDMI_ScdcCtrl(pstInfo->enHdmiId, SCDC_CMD_GET_FLT_UPDATE_TRIM, &bUpdate);

    if (bUpdate)
    {
        FrlGetLtpReq(pstInfo->enHdmiId, au8Ltp);
        bClrUpdate = HI_TRUE;
        HAL_HDMI_ScdcCtrl(pstInfo->enHdmiId, SCDC_CMD_SET_FLT_UPDATE_TRIM, &bClrUpdate);

        if (u8LaneNum == 3)
        {
             bTrainSuccess = ((au8Ltp[0] == 0) && (au8Ltp[1] == 0) && (au8Ltp[2] == 0))
                                ? HI_TRUE : HI_FALSE;
             bChangeRate = ((au8Ltp[0] == 0xF) && (au8Ltp[1] == 0xF) && (au8Ltp[2] == 0xF))
                                ? HI_TRUE : HI_FALSE;
        }
        else
        {
             bTrainSuccess = ((au8Ltp[0] == 0) && (au8Ltp[1] == 0) && (au8Ltp[2] == 0) && (au8Ltp[3] == 0))
                                ? HI_TRUE : HI_FALSE;
             bChangeRate = ((au8Ltp[0] == 0xF) && (au8Ltp[1] == 0xF) && (au8Ltp[2] == 0xF) && (au8Ltp[3] == 0xF))
                                ? HI_TRUE : HI_FALSE;
        }

        if (bTrainSuccess)
        {
            /*Training success;*/
            pstResult->enTrainStatus = FRL_TRAIN_SUCCESS;
            pstResult->enFailRes = FRL_TRAIN_FAIL_RES_NORMAL;
            FrlChannelModeSet(1);
            return ;
        }
        else if (bChangeRate)
        {
            /*Training need reduce Rate;*/
            pstResult->enTrainStatus = FRL_TRAIN_FAIL;
            pstResult->enFailRes = FRL_TRAIN_FAIL_RES_RATECHANGE;
            return ;
        }
        else
        {
            FrlLaneLoop(au8Ltp, u8LaneNum, bFrlNoTimeout, pstTmdsCfg);
        }
    }

    if (   FRL_TRAIN_SUCCESS != pstResult->enTrainStatus
        && FRL_TRAIN_FAIL != pstResult->enTrainStatus)
    {
        HAL_Timer_Start();
    }

    return ;
}

HI_S32 FrlTrainingStart(FRL_INFO_S *pstInfo)
{
    HI_BOOL  bFrlNoTimeout          = HI_FALSE;
    HI_U64   u64StartTime           = 0;
    HI_U64   u64CurrentTime         = 0;
    HI_U32   u32FrlTimeOut          = 0;
    FRL_TRAIN_RESULT_S *pstResult   = HI_NULL;
    TIMER_CONFIG_S      stConfig    = {0};
    FRL_TIMER_PARAM_S   stTimerParam= {0};
    HDMI_PHY_TMDS_CFG_S stHdmiCfg   = {0};

    FRL_NULL_CHECK(pstInfo);

    pstResult = &pstInfo->stStatus.stTrainInfo.stResult;
    u32FrlTimeOut = pstInfo->stCFG.stTimer.u32FltTimeOut / 25000;

    HDMI_MEMSET(&stHdmiCfg, 0, sizeof(HDMI_PHY_TMDS_CFG_S));
    stHdmiCfg.enModeCfg = HDMI_PHY_MODE_CFG_TXFFE;

    u64StartTime = HAL_HDMI_MachMsGet();
    stTimerParam.u64StartTime = u64StartTime;
    stTimerParam.pstInfo = pstInfo;
    stTimerParam.pstTmdsCfg = &stHdmiCfg;
    stTimerParam.u32FrlTimeOut = u32FrlTimeOut;

    stConfig.pIsr = FrlTraningInterrupt;
    stConfig.pParam = &stTimerParam;
    stConfig.u32DelayMs = 1;

    /* set software train rate */
    HDMI_CPU_SET_RES_soft_train_rateSet(pstInfo->stCFG.u8FrlRate);
    HDMI_CPU_SET_RES_software_train_setSet(HI_TRUE);
    HDMI_CPU_SET_RES_flt_skipSet(HI_FALSE);

    if (HI_SUCCESS != HAL_Timer_Init(&stConfig))
    {
        pstResult->enTrainStatus = FRL_TRAIN_FAIL;
        pstResult->enFailRes = FRL_TRAIN_FAIL_RES_FLTTIMEOUT;
        return HI_FAILURE;
    }

    HAL_Timer_Start();

    do
    {
        HDMI_MSLEEP(10);
        u64CurrentTime = HAL_HDMI_MachMsGet();
        /* Exit and return when training success or failed.
           If timeout break and return when sink permits timeout. */
        if (   FRL_TRAIN_SUCCESS == pstResult->enTrainStatus
            || FRL_TRAIN_FAIL == pstResult->enTrainStatus
            || (((u64CurrentTime - u64StartTime) >= (u32FrlTimeOut + 100)) && (!bFrlNoTimeout)))
        {
            break;
        }
    }while(1);

    HAL_Timer_Stop();
    HAL_Timer_DeInit();

    return HI_SUCCESS;
}
#else
HI_S32 FrlTrainingStart(FRL_INFO_S *pstInfo)
{
    HI_U8    au8Ltp[4] = {0};
    HI_BOOL  bUpdate = HI_FALSE;
    HI_BOOL  bClrUpdate = HI_FALSE;
    HI_BOOL  bTrainSuccess = HI_FALSE;
    HI_BOOL  bChangeRate = HI_FALSE;
    HI_U64   u64StartTime = 0;
    HI_U8    u8LaneNum = 0;
    HI_BOOL  bFrlNoTimeout = HI_FALSE;
	HI_U32   u32FrlTimeOut = 0;
    FRL_TRAIN_RESULT_S *pstResult = HI_NULL;
    HDMI_PHY_TMDS_CFG_S stHdmiTmdsCfg = {0};
    FRL_NULL_CHECK(pstInfo);

    u8LaneNum = (pstInfo->stCFG.u8FrlRate > 2) ? 4 : 3;
    u64StartTime = HAL_HDMI_MachMsGet();
    bFrlNoTimeout = pstInfo->stCFG.bFrlNoTimeout;
    pstResult = &pstInfo->stStatus.stTrainInfo.stResult;
    FRL_NULL_CHECK(pstResult);
    u32FrlTimeOut = pstInfo->stCFG.stTimer.u32FltTimeOut/25000;

    HDMI_MEMSET(&stHdmiTmdsCfg, 0, sizeof(HDMI_PHY_TMDS_CFG_S));
    stHdmiTmdsCfg.enModeCfg = HDMI_PHY_MODE_CFG_TXFFE;

    /* set software train rate */
    HDMI_CPU_SET_RES_soft_train_rateSet(pstInfo->stCFG.u8FrlRate);
    HDMI_CPU_SET_RES_software_train_setSet(HI_TRUE);
    HDMI_CPU_SET_RES_flt_skipSet(HI_FALSE);

    do
    {
        HAL_HDMI_ScdcCtrl(pstInfo->enHdmiId, SCDC_CMD_GET_FLT_UPDATE_TRIM, &bUpdate);
        if (bUpdate)
        {
            FrlGetLtpReq(pstInfo->enHdmiId, au8Ltp);
            bClrUpdate = HI_TRUE;
            HAL_HDMI_ScdcCtrl(pstInfo->enHdmiId, SCDC_CMD_SET_FLT_UPDATE_TRIM, &bClrUpdate);

            if (u8LaneNum == 3)
            {
                 bTrainSuccess = ((au8Ltp[0] == 0) && (au8Ltp[1] == 0) && (au8Ltp[2] == 0))
                                  ? HI_TRUE : HI_FALSE;
                 bChangeRate = ((au8Ltp[0] == 0xF) && (au8Ltp[1] == 0xF) && (au8Ltp[2] == 0xF))
                                ? HI_TRUE : HI_FALSE;
            }
            else
            {
                 bTrainSuccess = ((au8Ltp[0] == 0) && (au8Ltp[1] == 0) && (au8Ltp[2] == 0) && (au8Ltp[3] == 0))
                                 ? HI_TRUE : HI_FALSE;
                 bChangeRate = ((au8Ltp[0] == 0xF) && (au8Ltp[1] == 0xF) && (au8Ltp[2] == 0xF) && (au8Ltp[3] == 0xF))
                                ? HI_TRUE : HI_FALSE;
            }

            if (bTrainSuccess)
            {
                /*Training success;*/
                pstResult->enTrainStatus = FRL_TRAIN_SUCCESS;
                pstResult->enFailRes = FRL_TRAIN_FAIL_RES_NORMAL;
                FrlChannelModeSet(1);
                HDMI_INFO("Source training success!\n");
                break;
            }
            else if (bChangeRate)
            {
                /*Training need reduce Rate;*/
                pstResult->enTrainStatus = FRL_TRAIN_FAIL;
                pstResult->enFailRes = FRL_TRAIN_FAIL_RES_RATECHANGE;
                HDMI_INFO("Source training rate change!\n");
                break;
            }
            else
            {
                FrlLaneLoop(au8Ltp, u8LaneNum, bFrlNoTimeout, &stHdmiTmdsCfg);
            }
        }

        if ((HAL_HDMI_MachMsGet() - u64StartTime > u32FrlTimeOut) && !bFrlNoTimeout)
        {
            /*Time out,Training Fail;*/
            pstResult->enTrainStatus = FRL_TRAIN_FAIL;
            pstResult->enFailRes = FRL_TRAIN_FAIL_RES_FLTTIMEOUT;
            HDMI_ERR("FRL training timeout!\n");
            break;
        }

        HDMI_MSLEEP(1);
    }while(1);

    return HI_SUCCESS;
}
#endif

static HI_S32 FrlLMDataSet(LM_TABLE_CONFIG_S *LM_TableConfig)
{
    FRL_NULL_CHECK(LM_TableConfig);

	/*step1: RegAddr 0x320c,  coding table write data*/
	HDMI_LM_IN_AC0_WDATA_in_ac0_wdataSet(LM_TableConfig->u32WrData);
	HDMI_UDELAY(1);

    /*step2: RegAddr 0x3200,  bit[31] = 1,9b RAM; bit[31] = 0,7B RAM;
    bit[24:16] = RAM addr;bit[15:8] = channel number,read used;bit[7:4]=0xa*/
	HDMI_LM_IN_AC0_CMD_commandSet(0);
	HDMI_LM_IN_AC0_CMD_protect_numberSet(0xa);
	HDMI_LM_IN_AC0_CMD_in_ac0_numberSet(0);
	HDMI_LM_IN_AC0_CMD_in_ac0_addrSet(LM_TableConfig->u89Bor7B<<15
                                      | LM_TableConfig->u32RamAddr);
	HDMI_UDELAY(1);

	/*step3: RegAddr 0x321c=1 enable command*/
	HDMI_LM_COMMAND_EN_command_enSet(1);
	HDMI_UDELAY(1);
	/*step4: RegAddr 0x321c=0 clear command*/
	HDMI_LM_COMMAND_EN_command_enSet(0);
	HDMI_UDELAY(1);

	return HI_SUCCESS;
}

static HI_U32 FrlLMDataGet(LM_TABLE_CONFIG_S *LM_TableConfig)
{
    HI_U32 u32Data = 0;

    FRL_NULL_CHECK(LM_TableConfig);

    /*step1: RegAddr 0x3200,  bit[31] = 1,9b RAM; bit[31] = 0,7B RAM;
    bit[24:16] = RAM addr;bit[15:8] = channel number,read used;bit[7:4]=0xa*/
	HDMI_LM_IN_AC0_CMD_commandSet(1);
	HDMI_LM_IN_AC0_CMD_protect_numberSet(0xa);
	HDMI_LM_IN_AC0_CMD_in_ac0_numberSet(0);
	HDMI_LM_IN_AC0_CMD_in_ac0_addrSet(LM_TableConfig->u89Bor7B<<15
                                      | LM_TableConfig->u32RamAddr);
	HDMI_UDELAY(1);

	/*step2: RegAddr 0x321c=1 enable command*/
	HDMI_LM_COMMAND_EN_command_enSet(1);
	HDMI_UDELAY(1);
	/*step3: RegAddr 0x321c=0 clear command*/
	HDMI_LM_COMMAND_EN_command_enSet(0);
	HDMI_UDELAY(1);

    /*step4: RegAddr 0x320c,  coding table write data*/
	u32Data = HDMI_LM_IN_AC0_RDATA_in_ac0_rdataGet();

    osal_printk("read:addr(0x%x), 0x%x \n", HDMI_TX_CTRL_read(0x3200), HDMI_TX_CTRL_read(0x3208));

	return u32Data;
}

HI_S32 FrlLMTableGet(HI_VOID)
{
	HI_U32 u32RamAddr = 0;

	LM_TABLE_CONFIG_S stLM_TableConfig;

    HDMI_MEMSET(&stLM_TableConfig,0,sizeof(stLM_TableConfig));

	/*step1:0x3210=0x3  */
	HDMI_LM_SRC_EN_ram_config_enSet(1);

    /*step2:7B8B coding table write operation*/
	stLM_TableConfig.u89Bor7B = 0;
	for (u32RamAddr = 0; u32RamAddr < 128; u32RamAddr++)
	{
		stLM_TableConfig.u32RamAddr = u32RamAddr;
        FrlLMDataGet(&stLM_TableConfig);
	}

    /*step3:9B10B coding table write operation*/
	stLM_TableConfig.u89Bor7B = 1;
	for (u32RamAddr = 0; u32RamAddr < 512; u32RamAddr++)
	{
		stLM_TableConfig.u32RamAddr = u32RamAddr;
        FrlLMDataGet(&stLM_TableConfig);
	}

    /*step4:when Soure write operation is done,Source clear operation \
    enable register 0x3210*/
    HDMI_UDELAY(1);
    HDMI_LM_SRC_EN_ram_config_enSet(0);

	return HI_SUCCESS;
}

static HI_S32 FrlLMTableSet(HI_VOID)
{
	HI_U32 u32RamAddr = 0;
	LM_TABLE_CONFIG_S stLM_TableConfig;

    HDMI_MEMSET(&stLM_TableConfig,0,sizeof(stLM_TableConfig));

	/*step1:0x3210=0x3  */
	HDMI_LM_SRC_EN_ram_config_enSet(1);

    /*step2:7B8B coding table write operation*/
	stLM_TableConfig.u89Bor7B = 0;
	for (u32RamAddr = 0; u32RamAddr < 128; u32RamAddr++)
	{
		stLM_TableConfig.u32RamAddr = u32RamAddr;
        stLM_TableConfig.u32WrData = (s_aLm7B8B[u32RamAddr]);
		if (HI_SUCCESS != FrlLMDataSet(&stLM_TableConfig))
		{
			HDMI_ERR("ramaddr 7b8b write operate fail!\r\n");
			return HI_FAILURE;
		}
	}

    /*step3:9B10B coding table write operation*/
	stLM_TableConfig.u89Bor7B = 1;
	for (u32RamAddr = 0; u32RamAddr < 512; u32RamAddr++)
	{
		stLM_TableConfig.u32RamAddr = u32RamAddr;
		stLM_TableConfig.u32WrData = s_aLm9B10B[u32RamAddr];
		if (HI_SUCCESS != FrlLMDataSet(&stLM_TableConfig))
		{
			HDMI_ERR("ramaddr = 9b10b write operate fail!\r\n");
			return HI_FAILURE;
		}
	}

    /*step4:when Soure write operation is done,Source clear operation \
    enable register 0x3210*/
    HDMI_UDELAY(1);
    HDMI_LM_SRC_EN_ram_config_enSet(0);

	return HI_SUCCESS;
}

#ifdef HW_TRAINING
static HI_S32 FrlFltStatusInfoGet(HDMI_DEVICE_ID_E enHdmi)
{
	FRL_INFO_S *pstFrlInfo = HI_NULL;
	HI_U32 u32FltLtp       = 0;
    HI_U32 u32FrlModeAct   = 0;
    FRL_TRAIN_RUN_STATUS_S stRunStatus = {0};

    HDMI_MEMSET(&stRunStatus, 0, sizeof(FRL_TRAIN_RUN_STATUS_S));

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK(pstFrlInfo);

	stRunStatus.u32FrlCurFsm = HDMI_FLT_FSM_STATUS_flt_fsm_currGet();

	if (HDMI_FLT_FSM_STATUS_work_lane_numGet())
	{
		stRunStatus.enWorkLaneNum = FRL_WORK_LANE_NUM_3L;
	}
	else
	{
		stRunStatus.enWorkLaneNum = FRL_WORK_LANE_NUM_4L;
	}
	if (HDMI_FLT_FSM_STATUS_work_channelGet())
	{
		stRunStatus.enWorkChannel = FRL_WORK_CHANNEL_NORMAL;
	}
	else
	{
		stRunStatus.enWorkChannel = FRL_WORK_CHANNEL_TRAIN;
	}

	/*Reg addr 0x3434*/
	u32FltLtp = HDMI_FLT_LTP_ltp_patternGet();
	stRunStatus.enPattern[0] = u32FltLtp & 0xf;
	stRunStatus.enPattern[1] = (u32FltLtp >> 4) & 0xf;
	stRunStatus.enPattern[2] = (u32FltLtp >> 8) & 0xf;
	stRunStatus.enPattern[3] = (u32FltLtp >> 12) & 0xf;

	/*Reg addr 0x3438*/
	u32FrlModeAct = HDMI_FRL_MODE_ACT_frl_mode_actGet();
    stRunStatus.enTrainMode = (FRL_WORK_MODE_E)u32FrlModeAct;

    stRunStatus.bStart = HDMI_FLT_START_flt_startGet();

    HDMI_MEMCPY(&pstFrlInfo->stStatus.stTrainInfo.stRunStatus,\
                &stRunStatus, sizeof(stRunStatus));

    HDMI_INFO("Train Run status Start= %d\n", stRunStatus.bStart);
    HDMI_INFO("Train Run status Pattern[0]=%d\n", stRunStatus.enPattern[0]);
    HDMI_INFO("Train Run status Pattern[1]=%d\n", stRunStatus.enPattern[1]);
    HDMI_INFO("Train Run status Pattern[2]=%d\n", stRunStatus.enPattern[2]);
    HDMI_INFO("Train Run status Pattern[3]=%d\n", stRunStatus.enPattern[3]);
    HDMI_INFO("Train Run status TrainMode=%d\n", stRunStatus.enTrainMode);
    HDMI_INFO("Train run status WorkChannel=%d\n", stRunStatus.enWorkChannel);
    HDMI_INFO("Train run status WorkLaneNum=%d\n", stRunStatus.enWorkLaneNum);
    HDMI_INFO("Train run status FrlCurFsm = %d\n", stRunStatus.u32FrlCurFsm);

    return HI_SUCCESS;
}

static HI_S32 FrlFltWaitDone(HDMI_DEVICE_ID_E enHdmi)
{
    HI_BOOL bFltUpdate = HI_FALSE;
    HI_U32 u32FrlWorkMode = 0,u32FailResGet = 0;
	FRL_INFO_S *pstFrlInfo = HI_NULL;
    FRL_TRAIN_RESULT_S stResult;
    HI_U32 u32TimeCur = 0;
    HI_U32 u32TimeOri = 0;

    HDMI_MEMSET(&stResult,0,sizeof(stResult));

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK(pstFrlInfo);

    u32TimeCur = HDMI_OSAL_GetTimeInMs();
    u32TimeOri = u32TimeCur;

	do
	{
        u32TimeCur = HDMI_OSAL_GetTimeInMs();

        /*Source gets FLT's status informations via the register of 0x3430,\
        0x3434 and 0x3438*/
		FrlFltStatusInfoGet(enHdmi);
        /*Source gets FLT's the information of result via the register of \
        0x343c*/
		if (1 == HDMI_FLT_RESULT_train_successGet())
		{
			stResult.enTrainStatus = FRL_TRAIN_SUCCESS;
            u32FrlWorkMode = HDMI_FLT_RESULT_frl_work_modeGet();
            stResult.enWorkMode = (FRL_WORK_MODE_E)u32FrlWorkMode;

            /*When train is success,source channel switch to normal*/
            HDMI_CPU_SET_RES_soft_train_okSet(1);

            HAL_HDMI_ScdcCtrl(enHdmi, SCDC_CMD_GET_FLT_UPDATE, &bFltUpdate);
            if (HI_TRUE == bFltUpdate)
            {
                bFltUpdate = HI_TRUE;
                HAL_HDMI_ScdcCtrl(enHdmi, SCDC_CMD_SET_FLT_UPDATE, &bFltUpdate);
            }

            HDMI_INFO("The source train success\n");
            break;
		}

		if (1 == HDMI_FLT_RESULT_train_failGet())
		{
			stResult.enTrainStatus = FRL_TRAIN_FAIL;
            u32FailResGet = HDMI_FLT_RESULT_train_fail_resGet();
            stResult.enFailFsm = (FRL_TRAIN_FAIL_FSM_E)(u32FailResGet & 0x3);
            stResult.enFailRes = (FRL_TRAIN_FAIL_RES_E)(u32FailResGet >> 2 & 0x3);

            if (1 == HDMI_FLT_RESULT_sink_ffe_reqGet())
            {
                pstFrlInfo->bNoReset = HI_TRUE;
                stResult.enFailRes = FRL_TRAIN_FAIL_RES_FFECHANGE;
            }

            HAL_HDMI_ScdcCtrl(enHdmi, SCDC_CMD_GET_FLT_UPDATE, &bFltUpdate);
            if (HI_TRUE == bFltUpdate)
            {
                bFltUpdate = HI_TRUE;
                HAL_HDMI_ScdcCtrl(enHdmi, SCDC_CMD_SET_FLT_UPDATE, &bFltUpdate);
            }

            HDMI_ERR("The source train fail: %d\r\n", stResult.enFailRes);
            break;
		}

		if (1 == HDMI_FLT_RESULT_train_busyGet())
		{
			stResult.enTrainStatus = FRL_TRAIN_BUSY;

            HDMI_INFO("The source train is busy\r\n");
		}

		stResult.u32FltCounter = HDMI_FLT_RESULT_flt_cntGet();
        HDMI_INFO("Hdmi training get result counter = %d\n",\
                   stResult.u32FltCounter);

		if ((u32TimeCur - u32TimeOri) > pstFrlInfo->stCFG.stTimer.u32FltWaitResultMs)
		{
            HDMI_ERR("The Source waits result timeout\n");
			break;
		}

        HDMI_MSLEEP(20);
	}while(1);

    HDMI_MEMCPY(&pstFrlInfo->stStatus.stTrainInfo.stResult, &stResult,\
                    sizeof(stResult));

	return HI_SUCCESS;
}
#endif
/******************************************************************************/
/***************************public  interface**********************************/
/******************************************************************************/

//------------------------------------------------------------------------------
// Function:        HAL_HDMI_FrlInit
// Description:     Source init FRL
// Parameters:      enHdmi:    HDMI_DEVICE_ID0
// Returns:         HI_SUCCESS
//                  HI_FAILURE
//------------------------------------------------------------------------------

HI_S32 HAL_HDMI_FrlInit(HDMI_DEVICE_ID_E enHdmi, HDMI_HAL_INIT_S *pstHalInit)
{
	FRL_INFO_S *pstFrlInfo = HI_NULL;
    FRL_VERSION_INFO_S	 stVersionInfo;

    FRL_NULL_CHECK(pstHalInit);
    HDMI_MEMSET(&stVersionInfo,0,sizeof(stVersionInfo));

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK(pstFrlInfo);

    if (HI_TRUE == pstFrlInfo->bInit)
    {
        return HI_SUCCESS;
    }

    HDMI_MEMSET(pstFrlInfo,0,sizeof(FRL_INFO_S));

	/*reg addr map*/
	HDMI_HDMITX_FRL_reg_Init(pstHalInit->pcBaseAddr);

#ifdef HDMI_SYS_NOHIGH_TIMERS
    HDMI_REG_TIMER_11_S_Init(HI_NULL);
    HDMI_REG_SC_CTRL_S_Init(HI_NULL);
#endif

	/*frl  static reg config*/
	FrlLMRfdInitSet(0, 1);
    FrlLMRfdInitSet(1, 1);
    FrlLMRfdInitSet(2, 1);
    FrlLMRfdInitSet(3, 1);

    FrlLMScrInitSet(0, 0xFFFF);
    FrlLMScrInitSet(1, 0xFFFE);
    FrlLMScrInitSet(2, 0xFFFD);
    FrlLMScrInitSet(3, 0xFFFC);

    FrlScrambleEnble(HI_TRUE);

	/*frl struct init*/
	pstFrlInfo->bInit = HI_TRUE;
	pstFrlInfo->enHdmiId = enHdmi;
	pstFrlInfo->stStatus.bLmLoad = HI_FALSE;
	pstFrlInfo->stStatus.bWorkEn = HI_FALSE;
    pstFrlInfo->bNoReset = HI_FALSE;

    HDMI_LM_CODE_RFD_lm_ptn_rsv_enSet(HI_TRUE);

    FrlHwVersionGet(&stVersionInfo);

    HDMI_MEMCPY(&pstFrlInfo->stStatus.stVersionInfo,\
                &stVersionInfo, sizeof(FRL_VERSION_INFO_S));
    HDMI_INFO("Frl init get logic version updata time:%d,%d,%d.\n",\
              stVersionInfo.u32Year,stVersionInfo.u32Month,stVersionInfo.u32Day);

	return HI_SUCCESS;
}

//------------------------------------------------------------------------------
// Function:        HAL_HDMI_FrlDeInit
// Description:     Source deinit FRL
// Parameters:      enHdmi:     HDMI_DEVICE_ID0
// Returns:         None
//------------------------------------------------------------------------------
HI_VOID HAL_HDMI_FrlDeInit(HDMI_DEVICE_ID_E enHdmi)
{
	FRL_INFO_S *pstFrlInfo = HI_NULL;

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK_NO_RET(pstFrlInfo);

	/*frl struct clear*/
	pstFrlInfo->bInit = HI_FALSE;
	pstFrlInfo->enHdmiId = enHdmi;
	pstFrlInfo->stStatus.bLmLoad = HI_FALSE;
	pstFrlInfo->stStatus.bWorkEn = HI_FALSE;
    pstFrlInfo->bNoReset = HI_FALSE;

	/*reg addr unmap*/
	HDMI_HDMITX_FRL_reg_DeInit();

#ifdef HDMI_SYS_NOHIGH_TIMERS
    HDMI_REG_TIMER_11_S_DeInit();
    HDMI_REG_SC_CTRL_S_DeInit();
#endif

	return;
}

//------------------------------------------------------------------------------
// Function:        HAL_HDMI_FrlConfig
// Description:     FRL's paramter config
// Parameters:      enHdmi:    HDMI_DEVICE_ID0
//                  pstCfg:    input param
// Returns:         HI_SUCCESS
//                  HI_FAILURE
//------------------------------------------------------------------------------

HI_S32 HAL_HDMI_FrlConfig(HDMI_DEVICE_ID_E enHdmi, FRL_CFG_S *pstCfg)
{
	HI_U32 u32ScdcsConf = 0;
	HI_U8  u8WriteByte = 0;
	FRL_INFO_S *pstFrlInfo = HI_NULL;

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK(pstFrlInfo);
	FRL_NULL_CHECK(pstCfg);

    HDMI_MEMCPY(&pstFrlInfo->stCFG, pstCfg, sizeof(FRL_CFG_S));

    HDMI_TX_CHANNEL_SEL_flbk_selSet(HI_FALSE);

    FrlLineStartHsyncEnable(HI_TRUE);

	u8WriteByte = pstCfg->u8FrlRate | (pstCfg->u8FFELevels << 4);

    u32ScdcsConf = u8WriteByte;
	u32ScdcsConf = u32ScdcsConf << 8;
    FrlScdcConfigInSet(u32ScdcsConf);
    HDMI_INFO("HAL_HDMI_FrlConfig config scdcs = %x\r\n",u32ScdcsConf);

    FrlTimerInfoSet(pstCfg->stTimer);
    FrlSetFrlNoTimeOut(pstCfg->bFrlNoTimeout);

    return HI_SUCCESS;
}

//------------------------------------------------------------------------------
// Function:        HAL_HDMI_FrlEnableWorkEn
// Description:     Source set the signal that open worken or close worken
// Parameters:      enHdmi:    HDMI_DEVICE_ID0
//                  bEnable:   HI_TRUE  open worken
//                             HI_FALSE close worken
//
// Returns:         HI_SUCCESS
//                  HI_FAILURE
//------------------------------------------------------------------------------

HI_S32 HAL_HDMI_FrlEnableWorkEn(HDMI_DEVICE_ID_E enHdmi, HI_BOOL bEnable)
{
	FRL_INFO_S *pstFrlInfo = HI_NULL;

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK(pstFrlInfo);

    FrlWorkEnSet(bEnable);
    pstFrlInfo->stStatus.bWorkEn = bEnable;

	return HI_SUCCESS;
}

//------------------------------------------------------------------------------
// Function:        HAL_HDMI_FrlStartTraining
// Description:     Start FLT training config
// Parameters:      enHdmi:    HDMI_DEVICE_ID0
// Returns:         HI_SUCCESS
//                  HI_FAILURE
//------------------------------------------------------------------------------

HI_S32 HAL_HDMI_FrlStartTraining(HDMI_DEVICE_ID_E enHdmi)
{
	FRL_INFO_S *pstFrlInfo = HI_NULL;

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK(pstFrlInfo);

	if (pstFrlInfo->stStatus.bLmLoad == HI_FALSE)
	{
		FrlLMTableSet();
		pstFrlInfo->stStatus.bLmLoad = HI_TRUE;
	}

    if (HDMI_FRL_TRAIN_SEL_SW == pstFrlInfo->stCFG.enTrainSel)
    {
        FrlChannelModeSet(0);
        FrlReset();
        FrlTrainingStart(pstFrlInfo);
    }
    else
    {
    	/*step1:Training start*/
        FrlChannelModeSet(0);

        if (pstFrlInfo->bNoReset)
        {
            pstFrlInfo->bNoReset = HI_FALSE;
        }
        else
        {
            FrlReset();
        }

    	/*step2:FLT Start*/
        FrlTrainingEnable(HI_TRUE);
    	pstFrlInfo->stStatus.stTrainInfo.stRunStatus.bStart = HI_TRUE;

    	/*step3:FLT Wait Done*/
    	FrlFltWaitDone(enHdmi);
    }

	return HI_SUCCESS;
}

//------------------------------------------------------------------------------
// Function:        HAL_HDMI_FrlGetStatus
// Description:     Get FRL's status informations
// Parameters:      enHdmi:    HDMI_DEVICE_ID0
//                  pstStatus: output param
//
// Returns:         HI_SUCCESS
//                  HI_FAILURE
//------------------------------------------------------------------------------

HI_S32 HAL_HDMI_FrlGetStatus(HDMI_DEVICE_ID_E enHdmi, FRL_STATUS_S *pstStatus)
{
	FRL_INFO_S *pstFrlInfo = HI_NULL;

	pstFrlInfo = FrlInfoPtrGet(enHdmi);
    FRL_NULL_CHECK(pstFrlInfo);
	FRL_NULL_CHECK(pstStatus);

    /*Get status scdcs info*/
    HDMI_MEMCPY(pstStatus,&pstFrlInfo->stStatus,\
                sizeof(pstFrlInfo->stStatus));

	return HI_SUCCESS;

}

HI_S32 HAL_HDMI_FrlDebug(FRL_DEBUG_S *pstDebug)
{
    FRL_NULL_CHECK(pstDebug);

    FrlLMTableSet();
    HDMI_CPU_SET_RES_flt_skipSet(HI_TRUE);
    if (pstDebug->u8Rate > 2)
    {
        // 4 LANE
        HDMI_CPU_SET_RES_frl_lane_sel_setSet(HI_FALSE);
    }
    else
    {
        // 3 LANE
        HDMI_CPU_SET_RES_frl_lane_sel_setSet(HI_TRUE);
    }

    FrlReset();
    FrlChannelModeSet(1);

    return HI_SUCCESS;
}

