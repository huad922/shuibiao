/****************************** (C) COPYRIGHT 2017 ************************
* 文  件  名      : main.C
* 作      者      : 吴新辰
*                   QQ:741470274      TEL：15298612531        
* 版      本      : V1.0
* 日      期      : 2016/01/16	
* 描      述      : 主程序
      
V4.2:
	优化CSQ及CGAIT 查询逻辑

*******************************************************************************/
#include "sys.h"
#include "Uart.h"
#include "Flash.h"
#include "AD.h"
#include "sys.h"
#include "HT1621.h"
//#include "LCD.h"
#include "intrins.h"
#include "Calculate.h"
 
//===============================================
//保留区域（勿删）
//===============================================
unsigned char code reserved_trap[6] _at_ 0x7A;
unsigned char code flashlockbit_reserve[8] _at_ 0x86= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};            
unsigned int code password_reserve[0x08] _at_ 0x90={0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};

/*******************************************************************************
* 函  数  名      : calculate
* 描      述      : 数据计算，后显示
* 输      入      : 无
* 返      回      : 无.
*******************************************************************************/
void Meter_Time(void)
{
//*************************数据冻结***********************************/
/********************一小时一次、最多48条****************************/
 	 if(g_write_value[19]==0 && g_write_value[18]%16==0)//十分钟
	{
		mem_date++;	
		if(mem_date%g_write_value[21]==0)//到达数据存储间隔 
		{		 
			 meter_data[g_write_value[20]*7+0]=g_write_value[7];//总用水量3字节
			 meter_data[g_write_value[20]*7+1]=g_write_value[8];
			 meter_data[g_write_value[20]*7+2]=g_write_value[9];
			 meter_data[g_write_value[20]*7+3]=g_write_value[15];//月
			 meter_data[g_write_value[20]*7+4]=g_write_value[16];//日
			 meter_data[g_write_value[20]*7+5]=g_write_value[17];//时
			 meter_data[g_write_value[20]*7+6]=g_write_value[18];//分
			 g_write_value[20]++;//已冻结条数
			 if(g_write_value[20]>47) g_write_value[20]=0;
		}
		if(mem_date==289)  mem_date=0;
	}
	//*************************上传间隔***********************************/
		if(g_write_value[34]==0)//间隔为0  每天上传
		{
			if(g_write_value[19]==0 && g_write_value[17]==g_write_value[35]  && g_write_value[18]==g_write_value[36])//到达设置的时间
			{
				//g_write_value[46]: 0 开始进行数据传输 1 发送数据没收到平台确认 2 发送数据成功 
					g_write_value[46]=0;
					NB_Timing_Send(); //第一次发送
					if(g_write_value[46]==0)//上线失败 重发一次
					{
						NB_Timing_Send();//第二次发送
					}		
			}					
		}
		else//间隔不为零
		{
			if(g_write_value[19]==0 && g_write_value[18]==0)// 一小时
			{
				date++;	
				if((date%g_write_value[34])==0)//达到间隔时间,且上次发送失败
				{
					if(g_write_value[20]>0)  
					{	//g_write_value[46]: 0 开始进行数据传输 1 发送数据没收到平台确认 2 发送数据成功 
						g_write_value[46]=0;
						NB_Timing_Send();//第一次发送
						if(g_write_value[46]==0)//上线失败 重发一次
						{
							NB_Timing_Send();//第二次发送
						}		
					} 
					else NB_Send();
				}
				if(date==24) date=0; 
			}	
		}
//********************** 欠压标志 **************************//
/*  if((P0&BIT1)==0)//P01 低压检测
  { 
    LCDRAM13 |=0x01; 
    lowVoltageTime++;
    if((lowVoltageTime>50)&&((lowVoltageFlag&0x02)==0x00)) 
    { 
      lowVoltageTime=60;
      lowVoltageFlag |= 0x01;//低压标识允许显示 
      g_write_value[174] |= 0x04;
    }
  } 
  else 
  { 
    if((g_write_value[174]&0x04)==0x04){ LCDRAM13 |=0x01;   }   
    else { LCDRAM13 &=~0x01;  }                      
    lowVoltageTime=0;
  }*/
//********************** 实时上传 **************************//
	  	if(showIP==3)
		{
			showIP=0;
			NB_Send();//数据上传
		}
/************************* 干簧干双吸合故障检测 ******************************/
	  if(((P0&BIT4)==0)&&((P0&BIT5)==0)) //双吸合                        
	  { 
		    Nodoubletime=0;
		    doubletime++;
		    if((doubletime>20)&&((flagtype&0x08)==0x00))//双吸和      
		    { 
			  flagtype |=0x08;//     
		      g_write_value[23]|=0x80;
			  NB_Send();//双吸和报警
			  doubletime=0;          
		    }  
	  }
	  else 
	  {
		    doubletime=0;
		    Nodoubletime++;
		    if((Nodoubletime>60)&&((flagtype&0x08)==0x08))   
		    { 
		      g_write_value[23] &=~0x80;
		      flagtype &=~0x04;//清除双吸合标识             
		      flagtype &=~0x08;//允许双吸合                   
		    }
	  }
//*********************** 20秒 回到初始界面 *******************************/
	  returntime++;
	  if(returntime==10)
	  {
		  returntime=0;
		  showIP=0;
	  }
//*********************** 每天存储一次数据 *******************************/
	if(g_write_value[17]==0 && g_write_value[18]==0 && g_write_value[19]==0)	
	{
		 Write_SegC(); 
		 _nop_();_nop_();_nop_();_nop_();	
	}

}
//************主函数***********//
void main(void)
{
    Set_DCO();
	Port_Init();
	RNG_Time();
	//LCD_Init();	
	Read_SegC();
	if(g_write_value[47]!=C_DATA[47])
	{
	     Write_SegC();
	}
	else Flash_Read_Write(); 
    RTCInit();
	InitData();
	EA = 1;
 	ADC_Read();
    NB_Close(2);
	InitData();
	WDTCLKIRC;    ////WDTCLKX32;WDT时钟源选择内部32K	
    WDTCON = WDT_8S; //WDT选择8秒复位 		
    WDTEAT;
 	NB_Send2();
	while(1)
	{ 
	  //NB_Send();
	  Meter_Time();
	  if(RX0_flag==2) RX0_read();
	  LPMIN;				   
	  _nop_();_nop_();
	  _nop_();_nop_();	   
	}
}

