#include "Flash.h"
#include "sys.h"
//#include "LCD.h"
#include "Calculate.h"
#include "intrins.h"

/*******************************************************************************
* ��  ��  ��      : Port_Init
* ��      ��      : ��ʼ��1621״̬
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Port_Init(void)
{
	//�������
	P0_DIR &=~BIT3;
	P1_DIR &=~(BIT0+BIT1+BIT2+BIT5+BIT3+BIT4); 
	P2_DIR=P3_DIR=0x00;//P2/P3  ��ΪLCD����
	P4_DIR &=~(BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT7);
	//��������
	P0_DIR |=(BIT1+BIT2+BIT4+BIT5+BIT6);
	P4_DIR |=BIT6;
	//64Pin ����������
    P5_DIR &=~(BIT2+BIT3+BIT4);
	P6_DIR =P7_DIR =P8_DIR =0x00;
	P5 &=~(BIT2+BIT3+BIT4);
	P6=P7=P8=0x00; 
	//Ԥ������--����͵�ƽ
	P1 &=~(BIT0+BIT1+BIT2+BIT5+BIT3+BIT4);
	P2=P3=0;
	P4 &=~(BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT7);
	_nop_();_nop_();
	_nop_();_nop_();
	//������ų�ʼ��
	P0 |=BIT3;//NB_Power
	_nop_();_nop_();
	_nop_();_nop_();
	//����--����
    P0_INT_SEL=0x00;//P0�� ���ش���
	P0_EDGE_SEL=0X00;//P0�� �½��ش���
	P0_IE |=(BIT6+BIT5+BIT4+BIT1+BIT2);
    P4_INT_SEL=0x00;//P4�� ���ش���
	P4_EDGE_SEL=0X00;//P4�� �½��ش���
	P4_IE |=BIT6;//P4��
    //P5_INT_SEL=0x00;//P4�� ���ش���
	//P5_EDGE_SEL=0X00;//P4�� �½��ش���
	//P5_IE |=BIT0;//P4��
	AIE	|=PTE; 
}
/*******************************************************************************
�����жϺ���
*******************************************************************************/
void INTERRUPT_PORT(void) interrupt 8
{
	 if(P0_IFG & BIT2)//KEY
	  {			
	  	  returntime=0;
		  showIP++;
		  if(showIP>4) showIP=0;
		  //if(!z && (g_write_value[39]&BIT7)) Show();
	  }
	  if(P0_IFG & BIT5)//S2
	  {			
	  	  calculate();
	  }
	  if(P0_IFG & BIT4)//S1
	  {			
	  	 pul_flag=1;
	  }
	  if(P0_IFG & BIT6)//S3
	  {			
	  	 
	  }
	  if(P0_IFG & BIT1)//RX�ж�
	  {			
	  	  RX0_flag=2;
	  }
	  if(P4_IFG & BIT6)//Ƿѹ
	  {			
	  	
	  }
	 P0_IFG =0x00;
	 P4_IFG =0x00;
}
