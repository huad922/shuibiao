#include "Flash.h"
#include "intrins.h"
unsigned long adc_result;
/*******************************************************************************
* ��  ��  ��      : ADC_Read
* ��      ��      : ��ʼADת��
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void ADC_Read(void)
{
  adc_flag=1;
  BGRC |= BGREN;								//��BGR ��׼��ѹ������
  ADC1 = ADCVREF_2P5 +0x06+ ADCEN+ADCCH_0;  		    //ѡ��2.5V��׼��ѹ�� ����ʱ�Ӳ���Ƶ ADCʹ�� 
  P0_SEL0 |=BIT0;
  ADC3 = CAL3&0x38;									//����2.5V��׼��ѹ����У׼ֵ
  ADC3 |= ADCTSEN;  							
  ADC2 =  ADCBUF +0xc0 +ADCMODE_S + ADCALIGN_R;		//��VIN BUF �����β���ģʽ ����Ҷ���
  Delay(10);									//�ȴ�AD�����ȶ�
  ADC2 |= ADCSTART;								//����ת��
  AIE |= BIT5;
  while(adc_flag);
  ADC2 &=~ADCSTART;
  BGRC &=~BGREN;Delay(1);
  P0_SEL0 &=~BIT0;
  ADC1=ADC2=ADC3=0x00;
}
//===============================================
//ADC  �ж�
//===============================================
void INTERRUPT_ADC(void) interrupt 13
{
	adc_result=ADCH;
	adc_result=adc_result<<8;
	adc_result=adc_result+ADCL;
	adc_result=(adc_result*125)/2048;
	g_write_value[38]=adc_result;//(adc_result*25)/232;
	adc_flag=0;
	AIF &= ~BIT5;								 //��ADת���жϱ�־
}
