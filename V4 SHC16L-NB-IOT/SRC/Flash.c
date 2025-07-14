#include "Flash.h"
uchar  g_write_value[48]={
			     0,0,0,0x05,0x18,0x00,0x00,//0-6 表地址
			     0x00,0x00,0x00,//7-9 用户总用水量--正向
			     0x00,0x00,0x00,//10-12 用户总用水量--反向
			     0x20,0x17,0x10,0x23,0x15,0x20,0x20,//13-19 表上时间
				 //13   14   15   16   17   18   19
				 0x00,//20 已冻结数据条数
				 0x06,//21 数据冻结间隔
			     0x00,0x00,0x00,//22-24 表状态
			     0x00,0x00,//25-26 阀门动作次数
			     0x02,//27 脉冲当量
			     //112,4,228,148,19,147,
				 115,28,226,179,23,173,//28-33 IP&PORT
			     0,//34 上线间隔
			     0x00,0x00,//35-36 上线时间
			     0x00,//37 用户状态
			     0x00,//38 电池电压
				 0x00,//39 设备参数
				 0x00,//40 设备状态
				 0x00,0x00,//41-42 SNR值 
				 0x00,0x00,0x00,//43-45
				 0x00,//46 发送标志
			     0x42//47 程序版本
				};  
uchar C_DATA[150];
uchar meter_data[360];// 
/******************************************
设备参数	g_write_value[39]
BIT7				BIT6 									BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
是否带阀 1带 0不带 	外壳 1

设备状态	g_write_value[40]
BIT7		BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
 

*******************************************/
//相关变量
unsigned short mem_date=0;
unsigned char date;
unsigned char CDMA_time;//开机等待时间
unsigned char  showIP;
unsigned char  showdata[4]; 
 uchar z;    //串口1接收计数 
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
* 函  数  名      : Delay
* 描      述      : 延时函数 1mS
* 输      入      : 无.
* 返      回      : 无.
*******************************************************************************/
void Delay(unsigned int i)
{
  unsigned int j,k;
  for(k=i;k>0;k--)
    for(j=0;j<615;j++);
}
/*******************************************************************************
* 函  数  名      : Flash_Read_Write
* 描      述      : 交换设备参数信息
* 输      入      : 无.
* 返      回      : 无.
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
* 函  数  名      : Write_SegC
* 描      述      : 先擦除相应页，然后进行写入操作
* 输      入      : 无.
* 返      回      : 无.
*******************************************************************************/
void Write_SegC(void)
{
  unsigned char i;
  /******擦除最后一页 page63********/
  //解锁最后一页
  Flash_PL = 0x5a;
  Flash_PL = 0xa5;
  EF_plock7 |= 0x80;    	       
  //擦除最后一页page63 
  Flash_CTL = 0x02;
  *((volatile int *)0x00FF7E00) = 0x1234;	//最后一页地址FF7E00~FF7FFF
  while(Flash_CTL&0x10);						//等待擦除结束
   /******开始写入********/
  Flash_CTL =0x01;								//写最后一页FLASH
  for(i=0;i<48;i++)
  {
	*((volatile char *)(0xff7e00 + i)) = g_write_value[i];
  }
  while(Flash_CTL&0x10);
}
/*******************************************************************************
* 函  数  名      : Read_SegC
* 描      述      : 读Flash
* 输      入      : 无.
* 返      回      : 无.
*******************************************************************************/
void Read_SegC(void)
{
  unsigned char i;
  Flash_CTL =0x00;								//读最后一页FLASH
  for(i=0;i<48;i++)
  {
	C_DATA[i]= *((volatile char *)(0xff7e00 + i));  //将最后一页数据通过串口发送
  }
}
