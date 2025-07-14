#include "LCD.h"
#include "sys.h"
#include "Flash.h"

//�궨��  Һ�����ζ�Ӧ�ı���
#define a 0x08
#define b 0x80
#define c 0x20
#define d 0x10
#define e 0x02
#define f 0x04
#define g 0x40
///#define p 0x10
//�Զ����ɶ����
const char LCD_Tab[]={
    a+b+c+d+e+f,    //0
    b+c,            //1
    a+b+g+e+d,      //2
    a+b+g+c+d,      //3
    f+g+b+c,        //4
    a+f+g+c+d,      //5
    a+f+g+c+d+e,    //6
    a+b+c,          //7
    a+b+c+d+e+f+g,  //8
    a+b+f+g+c+d,    //9
    f+g+e+c+d,      //b 10
    a+f+e+d,        //C	11
    b+c+d+e+g,      //d	12
    a+f+g+e+d,      //E	13
	a+b+e+f+g,      //P 14
	a+b+c+e+f,      //n 15
	d+e+f,          //L 16
	b+c+d+e+f,      //U 17
	b+c+e+f+g,      //H 18
    0x00,             //�հ� 19
	0x40
};
#undef a
#undef b
#undef c
#undef d
#undef e
#undef f
#undef g 
/*
LCDRAM2:��1������+�춨��
LCDRAM3:��2������+���ۣ�
LCDRAM4:��3������+��1��С����~~~LCDRAM7:��6������+��4��С���㣻
LCDRAM10����7������+��5��С���㣻
LCDRAM11:0x01-M;0x02-k;0x04-h;0x08-W;0x10-/h;0x20-m3��0x40-Ԫ��0x80-��
LCDRAM12:0x01-������0x02-������0x04-����; 0x80-��ˮ; 0x10-һ��-; 0x20-��ˮ��0x40-����; 0x80-����
LCDRAM13:0x01-Ƿѹ��0x02-����; 0x04-ʣ����; 0x08-��������0x10-�ѹ�����0x20-���ֵ��0x40-
*/
/*******************************************************************************
* ��  ��  ��      : Showopen
* ��      ��      : ������ʾ
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void ShowOpen(unsigned char time)
{
	LCDRAM2=LCD_Tab[0];	//O
	LCDRAM3=LCD_Tab[14]; //P
	LCDRAM4=LCD_Tab[13]; //E
	LCDRAM5=LCD_Tab[15]; //n
	LCDRAM6=LCD_Tab[19];
	LCDRAM7=LCD_Tab[19];
	LCDRAM10=LCD_Tab[time];
}
/*******************************************************************************
* ��  ��  ��      : ShowClose
* ��      ��      : ������ʾ
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void ShowClose(unsigned char time)
{
	LCDRAM2=LCD_Tab[11];	//C
	LCDRAM3=LCD_Tab[16]; //L
	LCDRAM4=LCD_Tab[0]; //O
	LCDRAM5=LCD_Tab[5]; //S
	LCDRAM6=LCD_Tab[13]; //E
	LCDRAM7=LCD_Tab[19];
	LCDRAM10=LCD_Tab[time];
}
/*******************************************************************************
* ��  ��  ��      : LCD_Clera
* ��      ��      : ȫ����ʾ������
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
 void LCD_Clear(unsigned char j)
{
  LCDRAM2=LCDRAM3=LCDRAM4=LCDRAM5=LCDRAM6=LCDRAM7=
  LCDRAM10=LCDRAM11=LCDRAM12=LCDRAM13=j;  
}
/*******************************************************************************
* ��  ��  ��      : Lcd_DisNum
* ��      ��      : ������ʾ
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Lcd_DisNum(unsigned char pos,unsigned char num)
{
	switch(pos)
	{
		case 0:
			LCDRAM2 |=LCD_Tab[num];
		break;
		case 1:
			LCDRAM3 |=LCD_Tab[num];
		break;
		case 2:
			LCDRAM4 |=LCD_Tab[num];
		break;
		case 3:
		 	LCDRAM5 |=LCD_Tab[num];
		break;
		case 4:
		 	LCDRAM6 |=LCD_Tab[num];
		break;
		case 5:
		 	LCDRAM7 |=LCD_Tab[num];
		break;
		case 6:
		 	LCDRAM10 |=LCD_Tab[num];
		break;
	}
}
/*******************************************************************************
* ��  ��  ��      : Lcd_DisTag
* ��      ��      : Һ��״̬��ʾ
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Lcd_DisTag(unsigned char pos)
{
	switch(pos)
	{
		case 0: //// ��5С����
			LCDRAM4 |=0x01;
		break;
		case 1://  ��4С����
			LCDRAM5 |=0x01;
		break;
		case 2://  ��3С����
			LCDRAM6 |=0x01;
		break;
		case 3://  ��2С����
			LCDRAM7 |=0x01;
		break;
		case 4://  ��1С����
			LCDRAM10 |=0x01;
		break;
		case 5:// ʣ����
			LCDRAM13 =0x04;
		break;
		case 6:// ������
			LCDRAM13 =0x08;
		break;
		case 7://�ѹ���
			LCDRAM13 =0x10;
		break;
		case 8://���ֵ
			LCDRAM13 |=0x20;
		break;
		case 17:// ����
			LCDRAM12 =0x40;
		break;
		case 18:// ����
			LCDRAM12 =0x80;
		break;
		case 19:// Ƿѹ
			LCDRAM13 |=0x01;
		break;
		case 20:// ����
			LCDRAM13 |=0x02;
		break;
		case 21:// ����
			LCDRAM3 =0x01;
		break;
		case 22:// �춨
			LCDRAM2 =0x01;
		break;
		case 28://  m3
			LCDRAM11 =0x20;
		break;
		case 29://  yuan
			LCDRAM11 =0x40;
		break;
	}
}
/*******************************************************************************
* ��  ��  ��      : Show
* ��      ��      : ��ʾ�������
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Show(void)
{	 
	 unsigned char i=0,j=0;    //NO.(j)display
     unsigned char k=0;        //
	 unsigned char h=0;
	 unsigned long mid;
	 LCD_Clear(0X00);//����
	 //״̬��ʾ
	 switch(showIP)
	{
		case 0:  //����ˮ��
		    mid=consumed_water;
		    Lcd_DisTag(FMflag);
		    Lcd_DisTag(28);
		    Lcd_DisTag(6);
		    Lcd_DisTag(4);
		    k=5;
		break;
		case 1://����ʱ��
		    Lcd_DisTag(1);
		    Lcd_DisTag(3);
		    Lcd_DisTag(10);
		    for(i=0;i<3;i++){showdata[i]=(g_write_value[14-i]/16)*10+g_write_value[14-i]%16;}  showdata[3]=0x00;
		    k=1;
		    j=0;
		break;
		case 2://���
		    for(i=0;i<4;i++){showdata[i]=g_write_value[126+i];} 
		break;
 		case 3://��ص�ѹ
		    mid=g_write_value[38]*2;
	        Lcd_DisTag(3);
			LCDRAM2=LCD_Tab[17];
		    k=4;
 		break;
		case 4://��״̬
		    LCDRAM2 =LCD_Tab[14];
			LCDRAM3 =LCD_Tab[18];
		    showdata[3]=0x00;
		    showdata[2]=g_write_value[22]/128;
		    showdata[1]=g_write_value[23]/128*10;
		    showdata[0]=g_write_value[23]%32;
		    j=2;
		break;
	}
	//������ʾ
	 if((showIP<1) || showIP==3){ for(i=0;i<4;i++){showdata[i]=(uint8_t)(mid%100);mid=mid/100;} }
	      
	  i=showdata[3-(j+1)/2]%10;
	  if(i!=0)k=0;
	  if(i!=0|j>=k){ Lcd_DisNum(j,i); h++;}
	  j++;
	 
	  while(j<7)
	  {
	    i=showdata[3-(j+1)/2]/10;
	    if(i!=0)k=0;
	    if(i!=0|j>=k){ Lcd_DisNum(j,i); h++;}
	    j++;
	    
	    i=showdata[3-(j+1)/2]%10;
	    if(i!=0)k=0;
	    if(i!=0|j>=k){ Lcd_DisNum(j,i); h++;}
	    j++;
	  }	 
}
/*******************************************************************************
* ��  ��  ��      : LCD_Init
* ��      ��      : ��ʼ��Һ����ʾ
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void LCD_Init(void)
{  
  LCD_Clear(0X00);		//LCD����
  //LCD�����˿�����Ϊ���
  P2_DIR	= 0x00;
  P3_DIR	= 0x00;
  P4_DIR &=~(BIT0+BIT1+BIT2+BIT3);  
  //�˿�����ΪLCD��������
  P2_SEL0	= 0xFF;
  P3_SEL0	= 0xFF;	
  P4_SEL0	|=(BIT0+BIT1+BIT2+BIT3);
  //�Ĵ�������
  LCDCR0 	= LCDDUTY_4 + LCDBIAS_3 + LCDFRQ_16K + LCDFRA_128 + LCDEN;
  LCDCR1	= LCDBUF_0 + LCDCPEN; //LCD ��С������������ɱ�ʹ��
}


