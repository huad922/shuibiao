/****************************** (C) COPYRIGHT 2017 ************************
* ��  ��  ��      : main.C
* ��      ��      : ���³�
*                   QQ:741470274      TEL��15298612531        
* ��      ��      : V1.0
* ��      ��      : 2016/01/16	
* ��      ��      : ������
              ����AD�ɼ����տڵ�ѹֵ���жϹ��ĵ�ͨ�����
ʵ�ֹ����У� 

*******************************************************************************/
#include "sys.h"
#include "Uart.h"
#include "Flash.h"
#include "AD.h"
#include "sys.h"
#include "HT1621.h"
#include "LCD.h"
#include "intrins.h"
#include "Calculate.h"
 
//===============================================
//����������ɾ��
//===============================================
unsigned char code reserved_trap[6] _at_ 0x7A;
unsigned char code flashlockbit_reserve[8] _at_ 0x86= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};            
unsigned int code password_reserve[0x08] _at_ 0x90={0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};

/*******************************************************************************
* ��  ��  ��      : Meter_Time
* ��      ��      : ���ݼ��㣬����ʾ
* ��      ��      : ��
* ��      ��      : ��.
*******************************************************************************/
void Meter_Time(void)
{
//*************************���ݶ���***********************************/
/********************һСʱһ�Ρ����48��****************************/
 	 if(g_write_value[19]==0 && g_write_value[18]%16==0)//ʮ����
	{
		mem_date++;	
		if(mem_date%g_write_value[21]==0)//�������ݴ洢��� 
		{		 
			 meter_data[g_write_value[20]*7+0]=g_write_value[7];//����ˮ��3�ֽ�
			 meter_data[g_write_value[20]*7+1]=g_write_value[8];
			 meter_data[g_write_value[20]*7+2]=g_write_value[9];
			 meter_data[g_write_value[20]*7+3]=g_write_value[15];//��
			 meter_data[g_write_value[20]*7+4]=g_write_value[16];//��
			 meter_data[g_write_value[20]*7+5]=g_write_value[17];//ʱ
			 meter_data[g_write_value[20]*7+6]=g_write_value[18];//��
			 g_write_value[20]++;//�Ѷ�������
			 if(g_write_value[20]>47) g_write_value[20]=0;
		}
		if(mem_date==289)  mem_date=0;
	}
//*************************�ϴ����***********************************/
			if(g_write_value[34]==0)//���Ϊ0  ÿ���ϴ�
			{
				if(g_write_value[17]==g_write_value[35]  && g_write_value[18]==g_write_value[36] && g_write_value[19]==0)//�������õ�ʱ��
				{
					if(g_write_value[20]>0)  
					{	//g_write_value[46]: 0 ��ʼ�������ݴ��� 1 ��������û�յ�ƽ̨ȷ�� 2 �������ݳɹ� 
						g_write_value[46]=0;
						NB_Timing_Send(); //��һ�η���
						if(g_write_value[46]==0)//����ʧ�� �ط�һ��
						{
							NB_Timing_Send();//�ڶ��η���
						}		
					} 
					else NB_Send();	
				}					
			}
			else//�����Ϊ��
			{
				if(g_write_value[19]==0 && g_write_value[18]==0)// һСʱ
				{
					date++;	
					if((date%g_write_value[34])==0)//�ﵽ���ʱ��,���ϴη���ʧ��
					{
						if(g_write_value[20]>0)  
						{	//g_write_value[46]: 0 ��ʼ�������ݴ��� 1 ��������û�յ�ƽ̨ȷ�� 2 �������ݳɹ� 
							g_write_value[46]=0;
							NB_Timing_Send();//��һ�η���
							if(g_write_value[46]==0)//����ʧ�� �ط�һ��
							{
								NB_Timing_Send();//�ڶ��η���
							}		
						} 
						else NB_Send();
					}
					if(date==24) date=0; 
				}	
			}
//********************** Ƿѹ��־ **************************//
/*  if((P0&BIT1)==0)//P01 ��ѹ���
  { 
    LCDRAM13 |=0x01; 
    lowVoltageTime++;
    if((lowVoltageTime>50)&&((lowVoltageFlag&0x02)==0x00)) 
    { 
      lowVoltageTime=60;
      lowVoltageFlag |= 0x01;//��ѹ��ʶ������ʾ 
      g_write_value[174] |= 0x04;
    }
  } 
  else 
  { 
    if((g_write_value[174]&0x04)==0x04){ LCDRAM13 |=0x01;   }   
    else { LCDRAM13 &=~0x01;  }                      
    lowVoltageTime=0;
  }*/
//********************** ʵʱ�ϴ� **************************//
		  if((P0&BIT2)==0 && (showIP==0x00 || showIP==0x01))	
		  {
		  	key_time++;
			if(key_time>15) key_time=10;
			if(key_time==5)//���뼰ʱ
			{		
				LCD_Clear(0X00);
				NB_Send();//�����ϴ�
			}			  
		  }
		  else
		  {
		  	key_time=0;
		  }
/************************* �ɻɸ�˫���Ϲ��ϼ�� ******************************/
	  if(((P0&BIT4)==0)&&((P0&BIT5)==0) && flagtype==0) //˫����                        
	  { 
		    Nodoubletime=0;
		    doubletime++;
		    if(doubletime>20)//˫����      
		    {     
		      flagtype=1;
			  g_write_value[23]|=0x80;
			  NB_Send();//˫���ͱ���
			  doubletime=0;          
		    }  
	  }
	  else 
	  {
			doubletime=0;
		    Nodoubletime++;
		    if(Nodoubletime>60)   
		    { 
			  flagtype=0;
			  g_write_value[23] &=~0x80;                
		    }
	  }
//*********************** Ƿѹ�ط�  *******************************/
	if((P4&BIT6)==0 && lowVoltageFlag==0)
	{
		lowVoltage++;
		nolowVoltage=0;
		if(lowVoltage>5)
		{
			P0 &=~BIT0;
			FCtrol(1);
			g_write_value[22] |=BIT2;
			NB_Send();
			lowVoltageFlag=1;	
		}	
	}
	else if((P4&BIT6) && lowVoltageFlag)
	{
		lowVoltage=0;
		nolowVoltage++;
		if(nolowVoltage>10 && lowVoltageFlag)
		{
			P0 |=BIT0;
			lowVoltageFlag=0;
			g_write_value[22] &=~BIT2;
			FCtrol(0);
			ADC_Read();
		}			
	}
	
//*********************** 20�� �ص���ʼ���� *******************************/
	  returntime++;
	  if(returntime==10)
	  {
		  returntime=0;
		  showIP=0;
		  Show();
	  }
//*********************** ÿ��洢һ������ *******************************/
	if(g_write_value[17]==0 && g_write_value[18]==0 && g_write_value[19]==0)	
	{
		 Write_SegC(); 
		 _nop_();_nop_();_nop_();_nop_();	
	}
//*********************** ÿ�·������� *******************************/
	if(g_write_value[17]==0x10 && g_write_value[18]==0x10 && g_write_value[19]==0x10 && (g_write_value[16]==0x05 || g_write_value[16]==0x15 || g_write_value[16]==0x25))
	{
		FCtrol(0);
		FCtrol(1);
		FCtrol(0);		
	}
}
//************������***********//
void main(void)
{
    Set_DCO();
	Port_Init();
	RNG_Time();
	LCD_Init();	
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
	WDTCLKIRC;    ////WDTCLKX32;WDTʱ��Դѡ���ڲ�32K	
    WDTCON = WDT_8S; //WDTѡ��8�븴λ 		
    WDTEAT;
	LCD_Clear(0XFF);//����
    CDMA_time=2;
	while(CDMA_time);//�ȴ�2��
 	FCtrol(0);
	FCtrol(1);
	FCtrol(0);	
	LCDRAM3=LCDRAM5=LCDRAM7=0x40;
	NB_Send2();
	Show();
	while(1)
	{ 
	  Meter_Time();
	  if(RX0_flag==2) RX0_read();
	  LPMIN;					   
	  _nop_();_nop_();
	  _nop_();_nop_();	   
	}
}

