/*******************************************************************
 *
 *  Copyright (C), 2001-2015, Hisilicon Tech. Co., Ltd.
 *
 * *****************************************************************
 * File Name     : acodec.c
 * Version       : Initial Draft
 * Author        : Hisilicon multimedia software group
 * Created       : 2015/01/14
 * Description   : 
 * History       :
 * 1.Date        : 2015/01/14
 * Author      : x00307967
 * Modification: Created file
 *
 * *****************************************************************
 */

#include <common.h>
#include <command.h>
#include <version.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
//#include <asm/sizes.h>
#include <config.h>

#include "hi_audio_ao.h"
#include "acodec_def.h"
#include "acodec.h"

#define IO_ADDRESS(x) (x)

void *g_acodec_crg_reg = NULL;

static unsigned long ulAcodecBase;

unsigned int ACODEC_HAL_ReadReg(unsigned int u32Offset)
{
    return (*(volatile unsigned int*)((unsigned long)ulAcodecBase + (unsigned int)u32Offset));
}

void ACODEC_HAL_WriteReg(unsigned int u32Offset, unsigned int u32Value)
{
    *(volatile unsigned int*)((unsigned long)(ulAcodecBase) + (unsigned int)(u32Offset)) = u32Value;
}

void ACODEC_HAL_DUMP(unsigned int u32Offset)
{
    printf("addr: %8lx  value: %x\n",((unsigned long)ulAcodecBase + (unsigned int)u32Offset),\
        ACODEC_HAL_ReadReg( u32Offset));
}


static inline void acodec_RegWrite32(unsigned long value, unsigned long mask,
    unsigned long addr)
{
	unsigned long t;

	t = readl((const volatile void *)addr);
	t &= ~mask;
	t |= value & mask;
	writel(t, (volatile void *)addr);
}

static inline void HI_RegRead(unsigned long *pvalue, unsigned long addr)
{
	*pvalue = readl((const volatile void *)addr);
}

//static ACODEC_REGS_S *g_pstAcodecReg = NULL;
static void acodec_ana_init(void)
{
	U_AUDIO_ANA_CTRL_0 	acodec_anareg0;
    U_AUDIO_ANA_CTRL_1  acodec_anareg1;
	U_AUDIO_ANA_CTRL_2 	acodec_anareg2;
	unsigned int u32Value;

	acodec_anareg0.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG0_ADDR);
    acodec_anareg1.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG1_ADDR);
    acodec_anareg2.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG2_ADDR);
	
	/* acodec_anareg0.bits.pd_rctune   1 -> 0 */
	acodec_anareg0.bits.pd_rctune = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);

	/* acodec_anareg1.bits.adc_rctune_en   0 -> 1 */
	acodec_anareg1.bits.adc_rctune_en = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);


	udelay(50);

	u32Value = ACODEC_HAL_ReadReg(ACODEC_ANAREG6_ADDR);

	/*bits[5] == 1, RC tune code(bits[4:0]) ok*/
	if ((u32Value & 0x20) == 0x20)
	{
		acodec_anareg1.bits.adc_tune_int1_code = u32Value & 0x1f;
		acodec_anareg1.bits.adc_tune_int2_code = u32Value & 0x1f;
		ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);

		acodec_anareg2.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG2_ADDR);
		acodec_anareg2.bits.adc_tune_int3_code = u32Value & 0x1f;
		ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);
	}
	else
	{
		/*default RC value on hifonev500:0xC, never reach this branch in theory*/
		acodec_anareg1.bits.adc_tune_int1_code = 0xC;
		acodec_anareg1.bits.adc_tune_int2_code = 0xC;
		ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);

		acodec_anareg2.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG2_ADDR);
		acodec_anareg2.bits.adc_tune_int3_code = 0xC;
		ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);
	}

	/* acodec_anareg1.bits.adc_rctune_en   1 -> 0 */
	acodec_anareg1.bits.adc_rctune_en = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);

	/* acodec_anareg0.bits.pd_rctune   0 -> 1 */
	acodec_anareg0.bits.pd_rctune = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);

	/* acodec_anareg1.bits.adc_tune_sel set to 0 */
	acodec_anareg1.bits.adc_tune_sel = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);

}

static void acodec_ana_power_on(void)
{
	U_AUDIO_ANA_CTRL_0 	acodec_anareg0;
    U_AUDIO_ANA_CTRL_1  acodec_anareg1;
	U_AUDIO_ANA_CTRL_2 	acodec_anareg2;
    U_AUDIO_ANA_CTRL_3  acodec_anareg3;
	//U_AUDIO_DAC_REG_1   acodec_dacreg1;


	acodec_anareg0.u32 = 0x0000dcff;
    acodec_anareg1.u32 = 0x00c00000;
    acodec_anareg2.u32 = 0x40000004;
    acodec_anareg3.u32 = 0x35848000;
	
	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);

	acodec_anareg3.bits.rst = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);
	udelay(10*1000);

	acodec_anareg2.bits.pop_spd_cfg = 0x0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);
	acodec_anareg3.bits.pop_pdm_dly_cfg_08 = 0x0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);

	acodec_anareg3.bits.ibadj_micbias = 1;
	acodec_anareg3.bits.ibadj_ctcm = 0x1;
	acodec_anareg3.bits.ibadj_dac = 0x1;
	acodec_anareg3.bits.ibadj_adc = 0x1;
	acodec_anareg3.bits.ibadj_linein = 0x1;
	acodec_anareg3.bits.ibadj_dac_vref = 0x1;
	acodec_anareg3.bits.micbias_adj = 0x3;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);
	
	acodec_anareg0.bits.pd_ctcm_rx = 0;
	acodec_anareg0.bits.pd_bias = 0;
	acodec_anareg0.bits.pd_ctcm = 0;
	acodec_anareg0.bits.pdb_ctcm_ibias = 1;
	acodec_anareg0.bits.pd_dac_vref = 0;
	acodec_anareg0.bits.pd_dacl = 0;
	acodec_anareg0.bits.pd_dacr = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);

	acodec_anareg1.bits.mute_dacl = 1;
	acodec_anareg1.bits.mute_dacr = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
	acodec_anareg2.bits.pop_lineout_pull_en = 1;
	acodec_anareg2.bits.pd_ctcm_tx = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);
	udelay(10*1000);

	acodec_anareg1.bits.pu_pop_pullb_reg = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
	udelay(10*1000);

	acodec_anareg0.bits.pd_vref = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);
	udelay(500*1000);

	acodec_anareg3.bits.rst_pop_08 = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);
	udelay(10*1000);

	/* acodec_anareg3 LINEOUT_PD_ORG_08=0 */
	acodec_anareg3.bits.lineoutl_pd_org_08 = 0;
	acodec_anareg3.bits.lineoutr_pd_org_08 = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);
	udelay(100*1000);

	acodec_anareg2.bits.pop_lineout_pull_en = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);

	acodec_anareg1.bits.mute_dacl = 0;
	acodec_anareg1.bits.mute_dacr = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
}

static inline void acodec_regsetbit(
        unsigned long value,
        unsigned long offset,
        unsigned long addr)
{
    unsigned long t, mask;

    mask = 1 << offset;
    t = readl(addr);
    t &= ~mask;
    t |= (value << offset) & mask;
    writel(t, addr);
}

static int acodec_soft_reset(void)
{
    U_AUDIO_CTRL_REG_1 	acodec_digctrl1; 
    U_AUDIO_DAC_REG_0  	acodec_digdacreg0;
    U_AUDIO_DAC_REG_1   acodec_digdacreg1;
    U_AUDIO_ADC_REG_0   acodec_digadcreg0;

    U_AUDIO_ANA_CTRL_0 	acodec_anareg0;
    U_AUDIO_ANA_CTRL_1  acodec_anareg1;
    U_AUDIO_ANA_CTRL_2 	acodec_anareg2;
    U_AUDIO_ANA_CTRL_3  acodec_anareg3;

	unsigned int acodec_tunecode; //Tune Code

    if (0 == ulAcodecBase) {
        printf("Haven't ioremap acodec regs!");
        return -1;
    }

	acodec_anareg1.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG1_ADDR);
	acodec_tunecode = acodec_anareg1.bits.adc_tune_int1_code;
	
    acodec_anareg0.u32 = 0x00002000;
    acodec_anareg1.u32 = 0xac2c2911;
    acodec_anareg2.u32 = 0x00550060;
    acodec_anareg3.u32 = 0x00843555;

	acodec_anareg1.bits.adc_tune_int1_code = acodec_tunecode;
	acodec_anareg1.bits.adc_tune_int2_code = acodec_tunecode;
	acodec_anareg2.bits.adc_tune_int3_code = acodec_tunecode;
	
	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);

	acodec_digctrl1.u32   = 0x00035a00;
    ACODEC_HAL_WriteReg(ACODEC_CTRLREG1_ADDR, acodec_digctrl1.u32);
    acodec_digctrl1.u32   = 0xff035a00;
    ACODEC_HAL_WriteReg(ACODEC_CTRLREG1_ADDR, acodec_digctrl1.u32);

	
    acodec_digdacreg0.u32 = 0x08000001;
    ACODEC_HAL_WriteReg(ACODEC_DACREG0_ADDR, acodec_digdacreg0.u32);
    
    acodec_digdacreg1.u32 = 0x06062424;
    ACODEC_HAL_WriteReg(ACODEC_DACREG1_ADDR, acodec_digdacreg1.u32);
    
    acodec_digadcreg0.u32 = 0x1e1ec001;
    ACODEC_HAL_WriteReg(ACODEC_ADCREG0_ADDR, acodec_digadcreg0.u32);

    return 0;
}
int acodec_i2s_set(AUDIO_SAMPLE_RATE_E enSample)
{
    unsigned int i2s_fs_sel = 0;
    U_AUDIO_CTRL_REG_1   unDigctrlReg1;

    if ((AUDIO_SAMPLE_RATE_8000 == enSample)
        || (AUDIO_SAMPLE_RATE_11025 == enSample)
        || (AUDIO_SAMPLE_RATE_12000 == enSample)) 
    {
        i2s_fs_sel = 0x18;
    } 
    else if ((AUDIO_SAMPLE_RATE_16000 == enSample)
        || (AUDIO_SAMPLE_RATE_22050 == enSample)
        || (AUDIO_SAMPLE_RATE_24000 == enSample)) 
    {
        i2s_fs_sel = 0x19;
    } 
    else if ((AUDIO_SAMPLE_RATE_32000 == enSample)
        || (AUDIO_SAMPLE_RATE_44100 == enSample)
        || (AUDIO_SAMPLE_RATE_48000 == enSample)) 
    {
        i2s_fs_sel = 0x1a;
    } 
    else 
    {
        printf("%s: not support enSample:%d\n", __FUNCTION__, enSample);
        return -1;
    }

	unDigctrlReg1.u32 = ACODEC_HAL_ReadReg(ACODEC_CTRLREG1_ADDR);
    unDigctrlReg1.bits.i2s1_fs_sel = i2s_fs_sel;
    ACODEC_HAL_WriteReg(ACODEC_CTRLREG1_ADDR, unDigctrlReg1.u32);

    return 0;
}

int acodec_device_init(void)
{
    U_AUDIO_CTRL_REG_1  acodec_digctrl1; 
    U_AUDIO_DAC_REG_0	acodec_digdacreg0;
    U_AUDIO_DAC_REG_1   acodec_digdacreg1;
	U_AUDIO_REG_1		acodec_audio_reg;

    unsigned int aiao_crg = 0;
    unsigned int aiao_cfg = 0;
    
    ulAcodecBase = (unsigned int)IO_ADDRESS(ACODEC_REGS_BASE);
    if ( 0 == ulAcodecBase) {
        printf("could not ioremap acodec regs!");
        return -1;
    }

    g_acodec_crg_reg = (void *)IO_ADDRESS(ACODEC_REGS_CRG);
    if (NULL == g_acodec_crg_reg) {
        printf("could not ioremap acodec regs!");
        return -1;
    }

	acodec_audio_reg.u32 = 0xf;
	ACODEC_HAL_WriteReg(ACODEC_AUDIO_REG, acodec_audio_reg.u32);
	
	acodec_RegWrite32(0x2 << 30, 0x3 << 30, (unsigned long)g_acodec_crg_reg);
	acodec_regsetbit(1 , 29, (unsigned long)g_acodec_crg_reg);
    acodec_regsetbit(0 , 28, (unsigned long)g_acodec_crg_reg);

    aiao_crg = (unsigned int)IO_ADDRESS(AIAO_CLK_TX0_CRG);
    *(volatile unsigned int*)((unsigned long)(aiao_crg)) = 0x00152EF0;
    aiao_cfg = (unsigned int)IO_ADDRESS(AIAO_CLK_TX0_CFG);
    *(volatile unsigned int*)((unsigned long)(aiao_cfg)) = 0x00000115;
    udelay(50*1000);

    acodec_digctrl1.u32   = 0xff035a00;
    ACODEC_HAL_WriteReg(ACODEC_CTRLREG1_ADDR, acodec_digctrl1.u32);
    //osal_printk("step1 acodec_digctrl0:0x%x\n", acodec_digctrl0.u32);

	acodec_digdacreg1.u32 = 0x7e7e2424;
    ACODEC_HAL_WriteReg(ACODEC_DACREG1_ADDR, acodec_digdacreg1.u32);
    //osal_printk("step3 acodec_digctrl2:0x%x\n", acodec_digctrl2.u32);

    acodec_digdacreg0.u32 = 0x08000001;
    ACODEC_HAL_WriteReg(ACODEC_DACREG0_ADDR, acodec_digdacreg0.u32);
    //osal_printk("step2 acodec_digctrl1:0x%x\n", acodec_digctrl1.u32);

	acodec_ana_power_on();
	acodec_ana_init();
    acodec_soft_reset();

    printf("acodec inited!\n");
    
    return 0;
}       
       
int acodec_device_exit(void)
{  
    U_AUDIO_ANA_CTRL_0 	acodec_anareg0;
    U_AUDIO_ANA_CTRL_1  acodec_anareg1;
	U_AUDIO_ANA_CTRL_2 	acodec_anareg2;
    U_AUDIO_ANA_CTRL_3  acodec_anareg3;

	U_AUDIO_DAC_REG_1 acodec_dacreg1;

    unsigned int aiao_crg = 0;
    unsigned int aiao_cfg = 0;
     
    //VALG_TimerDelete(&g_AcodecTimer);
    
    acodec_regsetbit(0 , 0, (unsigned long)g_acodec_crg_reg);
	
    acodec_dacreg1.u32 = 0x7f7f2424;
    ACODEC_HAL_WriteReg(ACODEC_DACREG1_ADDR, acodec_dacreg1.u32);

    aiao_crg = (unsigned int)IO_ADDRESS(AIAO_CLK_TX0_CRG);
    *(volatile unsigned int*)((unsigned long)(aiao_crg)) = 0x00152EF0;
    aiao_cfg = (unsigned int)IO_ADDRESS(AIAO_CLK_TX0_CFG);
    *(volatile unsigned int*)((unsigned long)(aiao_cfg)) = 0x00000115;
    udelay(50*1000);

	acodec_anareg0.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG0_ADDR);
    acodec_anareg1.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG1_ADDR);
    acodec_anareg2.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG2_ADDR);
    acodec_anareg3.u32 = ACODEC_HAL_ReadReg(ACODEC_ANAREG3_ADDR);

	/*============ step 1 ==============*/

	acodec_anareg1.bits.mute_dacl = 1;
	acodec_anareg1.bits.mute_dacr = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
	/*============ step 2 ==============*/
	/* acodec_anareg0 PD_MICBAIS1=1,PD_MICBAIS2=1*/

	/*============ step 3 ==============*/
	/* acodec_anareg2 POP_LINEOUT_PULL_EN=0 */
	acodec_anareg2.bits.pop_lineout_pull_en = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);

	acodec_anareg3.bits.rst_pop_08 = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);
	udelay(10);
	acodec_anareg3.bits.rst_pop_08 = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);

	/*============ step 4 ==============*/
	/* acodec_anareg3 LINEOUT_PD_ORG_08=1*/
	acodec_anareg3.bits.lineoutl_pd_org_08 = 1;
	acodec_anareg3.bits.lineoutr_pd_org_08 = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);
	udelay(150*1000);
	
	acodec_anareg3.bits.rst_pop_08 = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);

	/*============ step 6 ==============*/
	/* acodec_anareg0 PD_VREF = 1 */
	acodec_anareg0.bits.pd_vref = 1;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);
	udelay(500*1000);

	/*============ step 7 ==============*/
	/* acodec_anareg1 PU_POP_PULLB_REG=0 */
	acodec_anareg1.bits.pu_pop_pullb_reg = 0;
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
	udelay(10*1000);

	/*============ step 8 ==============*/
	/*reset to default value*/
	acodec_anareg0.u32 = 0x0000dcff;
    acodec_anareg1.u32 = 0x00c00000;
    acodec_anareg2.u32 = 0x40000004;
    acodec_anareg3.u32 = 0x35848000;

	ACODEC_HAL_WriteReg(ACODEC_ANAREG0_ADDR, acodec_anareg0.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG1_ADDR, acodec_anareg1.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG2_ADDR, acodec_anareg2.u32);
	ACODEC_HAL_WriteReg(ACODEC_ANAREG3_ADDR, acodec_anareg3.u32);

    printf("acodec exited!\n");
    return 0;
}


