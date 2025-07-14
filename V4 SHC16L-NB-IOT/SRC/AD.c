#include "Flash.h"
#include "intrins.h"
unsigned long adc_result;
/*******************************************************************************
* 函  数  名      : ADC_Read
* 描      述      : 开始AD转换
* 输      入      : 无.
* 返      回      : 无.
*******************************************************************************/
void ADC_Read(void)
{
  adc_flag=1;
  BGRC |= BGREN;								//打开BGR 基准电压发生器
  ADC1 = ADCVREF_2P5 +0x06+ ADCEN+ADCCH_0;  		    //选择2.5V基准电压， 采样时钟不分频 ADC使能 
  P0_SEL0 |=BIT0;
  ADC3 = CAL3&0x38;									//读入2.5V基准电压出厂校准值
  ADC3 |= ADCTSEN;  							
  ADC2 =  ADCBUF +0xc0 +ADCMODE_S + ADCALIGN_R;		//打开VIN BUF 连单次采样模式 结果右对齐
  Delay(10);									//等待AD启动稳定
  ADC2 |= ADCSTART;								//启动转换
  AIE |= BIT5;
  while(adc_flag);
  ADC2 &=~ADCSTART;
  BGRC &=~BGREN;Delay(1);
  P0_SEL0 &=~BIT0;
  ADC1=ADC2=ADC3=0x00;
}
//===============================================
//ADC  中断
//===============================================
void INTERRUPT_ADC(void) interrupt 13
{
	adc_result=ADCH;
	adc_result=adc_result<<8;
	adc_result=adc_result+ADCL;
	adc_result=(adc_result*125)/2048;
	g_write_value[38]=adc_result;//(adc_result*25)/232;
	adc_flag=0;
	AIF &= ~BIT5;								 //清AD转换中断标志
}
