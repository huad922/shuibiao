/****************************** (C) COPYRIGHT 2017 ************************
* ��  ��  ��      : main.C
* ��      ��      : ���³�
*                   QQ:741470274      TEL��15298612531        
* ��      ��      : V1.0
* ��      ��      : 2016/01/16	
* ��      ��      : ������
      
V4.2:
	�Ż�CSQ��CGAIT ��ѯ�߼�

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
//����������ɾ��
//===============================================
unsigned char code reserved_trap[6] _at_ 0x7A;
unsigned char code flashlockbit_reserve[8] _at_ 0x86= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};            
unsigned int code password_reserve[0x08] _at_ 0x90={0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};

/*******************************************************************************
* ��  ��  ��      : calculate
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
			if(g_write_value[19]==0 && g_write_value[17]==g_write_value[35]  && g_write_value[18]==g_write_value[36])//�������õ�ʱ��
			{
				//g_write_value[46]: 0 ��ʼ�������ݴ��� 1 ��������û�յ�ƽ̨ȷ�� 2 �������ݳɹ� 
					g_write_value[46]=0;
					NB_Timing_Send(); //��һ�η���
					if(g_write_value[46]==0)//����ʧ�� �ط�һ��
					{
						NB_Timing_Send();//�ڶ��η���
					}		
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
	  	if(showIP==3)
		{
			showIP=0;
			NB_Send();//�����ϴ�
		}
/************************* �ɻɸ�˫���Ϲ��ϼ�� ******************************/
	  if(((P0&BIT4)==0)&&((P0&BIT5)==0)) //˫����                        
	  { 
		    Nodoubletime=0;
		    doubletime++;
		    if((doubletime>20)&&((flagtype&0x08)==0x00))//˫����      
		    { 
			  flagtype |=0x08;//     
		      g_write_value[23]|=0x80;
			  NB_Send();//˫���ͱ���
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
		      flagtype &=~0x04;//���˫���ϱ�ʶ             
		      flagtype &=~0x08;//����˫����                   
		    }
	  }
//*********************** 20�� �ص���ʼ���� *******************************/
	  returntime++;
	  if(returntime==10)
	  {
		  returntime=0;
		  showIP=0;
	  }
//*********************** ÿ��洢һ������ *******************************/
	if(g_write_value[17]==0 && g_write_value[18]==0 && g_write_value[19]==0)	
	{
		 Write_SegC(); 
		 _nop_();_nop_();_nop_();_nop_();	
	}

}
//************������***********//
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
	WDTCLKIRC;    ////WDTCLKX32;WDTʱ��Դѡ���ڲ�32K	
    WDTCON = WDT_8S; //WDTѡ��8�븴λ 		
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

