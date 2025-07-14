#include "RTC.h"
#include "Flash.h"

unsigned char CDMA_Wait;//数据接收等待时间

//===============================================
//初始化RTC
//===============================================
void RTCInit(void)
{  
  RTC_HOLD = 0x00;								  //打开RTC  

  INTERVAL  = 0X41;							  //一秒中断一次
  
  YEAR_L 	= g_write_value[14];								  //设置初始时间
  YEAR_H 	= g_write_value[13];
  MONTH 	= g_write_value[15];
  DAY 		= g_write_value[16];
  HOUR 		= g_write_value[17];
  MINUTE 	= g_write_value[18];
  SECOND 	= g_write_value[19];
  AIE	   |= RTCE;								  //打开RTC中断
}
//===============================================
//修改实时时间
//===============================================
void RTCSet(void)
{  
  AIE	   &= ~RTCE;
  YEAR_L 	= g_write_value[14];								  //设置初始时间
  YEAR_H 	= g_write_value[13];
  MONTH 	= g_write_value[15];
  DAY 		= g_write_value[16];
  HOUR 		= g_write_value[17];
  MINUTE 	= g_write_value[18];
  SECOND 	= g_write_value[19];
   AIE	   |= RTCE;								  //打开RTC中断
}
//===============================================
//RTC 中断
//===============================================
void INTERRUPT_RTC(void) interrupt 14
{
  WDTEAT;
  AIF &= ~BIT6; 								 //清RTC中断标志
  CDMA_time--;
  if(CDMA_time>0xF0) CDMA_time=0;
  CDMA_Wait++;
  count_time++;
  time_Flag++;
  if(time_Flag%2==0 && FDtime>0) FDtime--;

  g_write_value[14] = YEAR_L_DIS;
  g_write_value[15] = MONTH_DIS;
  g_write_value[16] = DAY_DIS;
  g_write_value[17] = HOUR_DIS;
  g_write_value[18] = MINUTE_DIS;
  g_write_value[19] = SECOND_DIS;
}
