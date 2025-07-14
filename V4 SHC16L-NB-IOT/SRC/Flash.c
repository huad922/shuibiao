#include "Flash.h"
uchar  g_write_value[48]={
			     0,0,0,0x05,0x18,0x00,0x00,//0-6 ���ַ
			     0x00,0x00,0x00,//7-9 �û�����ˮ��--����
			     0x00,0x00,0x00,//10-12 �û�����ˮ��--����
			     0x20,0x17,0x10,0x23,0x15,0x20,0x20,//13-19 ����ʱ��
				 //13   14   15   16   17   18   19
				 0x00,//20 �Ѷ�����������
				 0x06,//21 ���ݶ�����
			     0x00,0x00,0x00,//22-24 ��״̬
			     0x00,0x00,//25-26 ���Ŷ�������
			     0x02,//27 ���嵱��
			     //112,4,228,148,19,147,
				 115,28,226,179,23,173,//28-33 IP&PORT
			     0,//34 ���߼��
			     0x00,0x00,//35-36 ����ʱ��
			     0x00,//37 �û�״̬
			     0x00,//38 ��ص�ѹ
				 0x00,//39 �豸����
				 0x00,//40 �豸״̬
				 0x00,0x00,//41-42 SNRֵ 
				 0x00,0x00,0x00,//43-45
				 0x00,//46 ���ͱ�־
			     0x42//47 ����汾
				};  
uchar C_DATA[150];
uchar meter_data[360];// 
/******************************************
�豸����	g_write_value[39]
BIT7				BIT6 									BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
�Ƿ���� 1�� 0���� 	��� 1

�豸״̬	g_write_value[40]
BIT7		BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
 

*******************************************/
//��ر���
unsigned short mem_date=0;
unsigned char date;
unsigned char CDMA_time;//�����ȴ�ʱ��
unsigned char  showIP;
unsigned char  showdata[4]; 
 uchar z;    //����1���ռ��� 
unsigned char adc_flag;
unsigned char flagtype;
unsigned long consumed_water;   
unsigned char lowVoltageFlag;
unsigned char FDcycflag;
unsigned char FMflag;
  
unsigned char  returntime;
unsigned char  FDtime;
unsigned char  RX0_flag;

unsigned char pul_flag;
unsigned char FmForceFlag;
unsigned char FmOrder;
unsigned char key_time;
unsigned char time_Flag;
unsigned char count_time;
unsigned char doubletime;
unsigned char Nodoubletime;
/*******************************************************************************
* ��  ��  ��      : Delay
* ��      ��      : ��ʱ���� 1mS
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Delay(unsigned int i)
{
  unsigned int j,k;
  for(k=i;k>0;k--)
    for(j=0;j<615;j++);
}
/*******************************************************************************
* ��  ��  ��      : Flash_Read_Write
* ��      ��      : �����豸������Ϣ
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Flash_Read_Write(void)
{
	uchar i;
	for(i=0;i<48;i++)
	{
		g_write_value[i]=C_DATA[i];
	}
}
/*******************************************************************************
* ��  ��  ��      : Write_SegC
* ��      ��      : �Ȳ�����Ӧҳ��Ȼ�����д�����
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Write_SegC(void)
{
  unsigned char i;
  /******�������һҳ page63********/
  //�������һҳ
  Flash_PL = 0x5a;
  Flash_PL = 0xa5;
  EF_plock7 |= 0x80;    	       
  //�������һҳpage63 
  Flash_CTL = 0x02;
  *((volatile int *)0x00FF7E00) = 0x1234;	//���һҳ��ַFF7E00~FF7FFF
  while(Flash_CTL&0x10);						//�ȴ���������
   /******��ʼд��********/
  Flash_CTL =0x01;								//д���һҳFLASH
  for(i=0;i<48;i++)
  {
	*((volatile char *)(0xff7e00 + i)) = g_write_value[i];
  }
  while(Flash_CTL&0x10);
}
/*******************************************************************************
* ��  ��  ��      : Read_SegC
* ��      ��      : ��Flash
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Read_SegC(void)
{
  unsigned char i;
  Flash_CTL =0x00;								//�����һҳFLASH
  for(i=0;i<48;i++)
  {
	C_DATA[i]= *((volatile char *)(0xff7e00 + i));  //�����һҳ����ͨ�����ڷ���
  }
}
