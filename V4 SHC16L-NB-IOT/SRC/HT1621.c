#include "Flash.h"
#include "sys.h"
//#include "LCD.h"
#include "Calculate.h"
#include "intrins.h"

/*******************************************************************************
* 函  数  名      : Port_Init
* 描      述      : 初始化1621状态
* 输      入      : 无.
* 返      回      : 无.
*******************************************************************************/
void Port_Init(void)
{
	//输出引脚
	P0_DIR &=~BIT3;
	P1_DIR &=~(BIT0+BIT1+BIT2+BIT5+BIT3+BIT4); 
	P2_DIR=P3_DIR=0x00;//P2/P3  作为LCD引脚
	P4_DIR &=~(BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT7);
	//输入引脚
	P0_DIR |=(BIT1+BIT2+BIT4+BIT5+BIT6);
	P4_DIR |=BIT6;
	//64Pin 无以下引脚
    P5_DIR &=~(BIT2+BIT3+BIT4);
	P6_DIR =P7_DIR =P8_DIR =0x00;
	P5 &=~(BIT2+BIT3+BIT4);
	P6=P7=P8=0x00; 
	//预留引脚--输出低电平
	P1 &=~(BIT0+BIT1+BIT2+BIT5+BIT3+BIT4);
	P2=P3=0;
	P4 &=~(BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT7);
	_nop_();_nop_();
	_nop_();_nop_();
	//相关引脚初始化
	P0 |=BIT3;//NB_Power
	_nop_();_nop_();
	_nop_();_nop_();
	//按键--输入
    P0_INT_SEL=0x00;//P0脚 边沿触发
	P0_EDGE_SEL=0X00;//P0脚 下降沿触发
	P0_IE |=(BIT6+BIT5+BIT4+BIT1+BIT2);
    P4_INT_SEL=0x00;//P4脚 边沿触发
	P4_EDGE_SEL=0X00;//P4脚 下降沿触发
	P4_IE |=BIT6;//P4脚
    //P5_INT_SEL=0x00;//P4脚 边沿触发
	//P5_EDGE_SEL=0X00;//P4脚 下降沿触发
	//P5_IE |=BIT0;//P4脚
	AIE	|=PTE; 
}
/*******************************************************************************
按键中断函数
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
	  if(P0_IFG & BIT1)//RX中断
	  {			
	  	  RX0_flag=2;
	  }
	  if(P4_IFG & BIT6)//欠压
	  {			
	  	
	  }
	 P0_IFG =0x00;
	 P4_IFG =0x00;
}
