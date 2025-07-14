#include "sys.h"
#include "Flash.h"
#include "AD.h"
#include <string.h>
#include "Uart.h"
#include "RTC.h"
#include "HT1621.h"
#include "intrins.h"
#include "Calculate.h"
//#include "LCD.h"

unsigned int j;    //���ͼ���
uchar y;    //����0���ռ���

uchar RX0[200];
//uchar RX1[50];
uchar TX[200];

unsigned int TX_Flag;//���ͱ�־λ
uint8_t Read_Flag;
uchar RX1_Flag=0;//����1���ձ�־
#define NB_Power_ON 	 P0 &=~BIT3
#define NB_Power_OFF     P0 |=BIT3
//CRCУ�鲿��
unsigned char ucCRCHi;
unsigned char ucCRCLo;
const unsigned char  aucCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40};
const unsigned char aucCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40};
void Uart1_Read_Data(void);
/*******************************************************************************
* ��  ��  ��      : Set_DCO
* ��      ��      : ����DCOʱ��4MHZ ʹ���ⲿ����
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Set_DCO(void)
{
  //ʱ�ӳ�ʼ��-------------------------------------									
  CLKC=0xC7;
  //CLKC2 |=BIT5;
  CLKC1 =(unsigned char)CAL0;					//��ȡ��ƵУ׼ֵ 4M
  while(!(CLKC2 & 0X80));						//�ȴ���Ƶ�ȶ�

}
/*******************************************************************************
* ��  ��  ��      : Uart_Init
* ��      ��      : ���ڳ�ʼ�� 2400bps żУ��
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Uart_Init(void)
{
/*	 //UART0��ʼ��
  P5_DIR  &= ~BIT1;								 //p5.1���TXD
  P5_DIR  |= BIT0;								 //p5.0����RXD
  P5_SEL0 &= ~(BIT0 +BIT1);						 //����P5.0  P5.1ΪUART0 RXD TXD 
  P5_SEL1 |= BIT0 +BIT1;
  PCON |= U0BRD;								 //�����ʷ���
  U0_TM =152;//230;//152;						//���ò����� 2400bps	
  U0_TMR &=~ UXTMR;    						     //���������ʷ�����
  SCON = 0;//UXSM_3 + UXREN;						 //���ô��ڹ�����ʽ
  */
  //UART1��ʼ��
  P1_DIR  &= ~BIT7;								 //p1.7���TXD
  P1_DIR  |= BIT6;								 //p1.6����RXD
  P1_SEL0 &= ~(BIT6 +BIT7);						 //����P1.6  P1.7ΪUART1 RXD TXD 
  P1_SEL1 |= BIT6 +BIT7;
  P1_SEL2 &= ~(BIT6 +BIT7);
  PCON |= U1BRD;								 //�����ʷ���
  U1_TM =230;//230;//230;						 //���ò�����9600
  U1_TMR |= UXTMR;    						     //���������ʷ�����
  SCON1 = UXSM_1 + UXREN;						 //���ô��ڹ�����ʽ
  IPH0 |=BIT4;
  IPL0 |=BIT4;
  ES = 1;										 //�򿪴����ж�
}
/*******************************************************************************
* ��  ��  ��      : Uart0_Init
* ��      ��      : ���ڳ�ʼ�� 2400bps żУ��
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void Uart0_Init(void)
{
//UART0��ʼ��
  P5_DIR  &= ~BIT1;								 //p5.1���TXD
  P5_DIR  |= BIT0;								 //p5.0����RXD
  P5_SEL0 &= ~(BIT0 +BIT1);						 //����P5.0  P5.1ΪUART0 RXD TXD 
  P5_SEL1 |= BIT0 +BIT1;
  PCON |= U0BRD;								 //�����ʷ���
  U0_TM =152;//230;//						//���ò����� 2400bps	
  U0_TMR |=UXTMR;    						     //���������ʷ�����
  SCON = UXSM_1 + UXREN;						 //���ô��ڹ�����ʽ
  IPH0 |=BIT4;
  IPL0 |=BIT4;
  ES = 1;										 //�򿪴����ж�
}
/*******************************************************************************
* ��  ��  ��      : usMBCRC16
* ��      ��      : CRCУ�麯��
* ��      ��      : ��.
* ��      ��      : ��.
*******************************************************************************/
void usMBCRC16( unsigned char * pucFrame, unsigned int usLen )
{
    unsigned int iIndex12;    
    ucCRCHi = 0xFF;
    ucCRCLo = 0xFF;
    while(usLen--)
    {
        iIndex12 = ucCRCLo ^ *( pucFrame++ );
	
        ucCRCLo = (unsigned char)( ucCRCHi ^ aucCRCHi[iIndex12] );
	
        ucCRCHi = aucCRCLo[iIndex12];
    }
}
/*******************************************************************************
* ��  ��  ��      : Clear_RX
* ��      ��      : ������ջ�����
* ��      ��      : 0�����RX0��1 ���RX1 
* ��      ��      : .
*******************************************************************************/
void Clear_RX(uchar n)
{
  uchar i;
  if(!n)
  for(i=0;i<150;i++)
  {
    RX0[i]=0x00;
  }
}
/*******************************************************************************
* ��  ��  ��      :  
* ��      ��      :  
* ��      ��      :     
* ��      ��      :  
*******************************************************************************/
char *strwu(const char *str1, const char *str2)
{
    char *cp = (char*)str1;
    char *s1, *s2;
 
    if (!*str2)
        return((char *)str1);
 
    while (*cp)
    {
        s1 = cp;
        s2 = (char *)str2;
 
        while (*s1 && *s2 && !(*s1 - *s2))
            s1++, s2++;
 
        if (!*s2)
            return(cp);
 
        cp++;
    }
    return(NULL);
}
/*******************************************************************************
* ��  ��  ��      : Check_cmd 
* ��      ��      : �ּ��������ַ����Ƿ������������
* ��      ��      : 0 ����Ƿ���RX0�У�1 ����Ƿ���RX1��   
* ��      ��      : λ����Ϣ
*******************************************************************************/
char* Check_cmd(uchar n,char*str)
{
	char *strx=0;
	if(n==0)
	strx=strwu((const char*)RX0,(const char*)str);
	return (char*)strx;
}
/*******************************************************************************
* ��  ��  ��      : Check_Str 
* ��      ��      : �������ַ��������е�һ�γ��ֵ�λ��
* ��      ��      : 0 ����Ƿ���RX0�У�1 ����Ƿ���RX1��   
* ��      ��      : �������г��ֵ�λ��
*******************************************************************************/
uchar Check_Str(char str)
{
 	unsigned char i;

	for(i=0;i<100;i++)
	{
		 if(str==RX0[i])
		 {
		 	break;
		 }
	}
 	return i;
}
/*******************************************************************************
* ��  ��  ��      : Uart0_TX
* ��      ��      : ����0���ʹ���
* ��      ��      : ��
* ��      ��      : ��.
*******************************************************************************/
void Uart0_TX(void)
{
      j = 0;
	  SBUF1=TX[j];
}
/*******************************************************************************
* ��  ��  ��      : NB_Close
* ��      ��      : ģ��ػ����Ͽ�NBģ�鲿�ֵ�Դ
* ��      ��      : �ӳ�ʱ��
* ��      ��      : NULL
*******************************************************************************/
void NB_Close(uchar time)
{
	P5_DIR  &= ~BIT1;		 		 
    P5_SEL0 &= ~BIT1; 
    P5_SEL1 &= ~BIT1;
	P1_DIR  &= ~BIT7;								 //p1.7���TXD
    P1_DIR  &= ~BIT6;								 //p1.6����RXD
    P1_SEL0 &= ~(BIT6 +BIT7);						 //����P1.6  P1.7ΪUART1 RXD TXD 
    P1_SEL1 &= ~(BIT6 +BIT7);
    P1_SEL2 &= ~(BIT6 +BIT7);
	P1 &=~(BIT6+BIT7);_nop_();
	P5 &=~BIT1;_nop_();_nop_(); 
	P0_DIR &=~BIT0;
	P0 |=BIT0;_nop_(); //AD����
	_nop_();_nop_();_nop_();_nop_();_nop_();
	Delay(5);
	NB_Power_OFF;	
	CDMA_time=time;
	while(CDMA_time);		
}
/*******************************************************************************
* ��  ��  ��      : NB_Open
* ��      ��      : NBģ���ϵ磬���ȴ���������
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
uchar NB_Open(uint8 time)
{
	uchar nb=0;
	NB_Power_ON; //CDMA_POWER
	CDMA_time=6;
	while(CDMA_time); //�ȴ�����ʱ��
	//while(1);
	strcpy((char*)TX,"AT\r\n");
    TX_Flag=4;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		Delay(30);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;	
	}
 	Clear_RX(0);
	nb=1;
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_CSQ
* ��      ��      : ��ѯ�ź�ֵ
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
uchar NB_CSQ(uchar time)
{
	uchar nb=0,qw; 
	strcpy((char*)TX,"AT+CSQ\r\n");
    TX_Flag=8;
	g_write_value[24]=66;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		CDMA_time=1;
		while(CDMA_time); 
		if(Check_cmd(0,"OK"))
		{
			nb=Check_Str(':');
			qw=Check_Str(',');
			if((qw-nb)==2)
					g_write_value[24]=RX0[nb+1]-0x30;
			else if((qw-nb)==3)
					g_write_value[24]=(RX0[nb+1]-0x30)*10+(RX0[nb+2]-0x30);
			if(g_write_value[24]<40 || g_write_value[24]==0)//�ź�ֵ��Ч
			{
				nb=0x01;
		   		break;//����ѭ��	
			}
			else
			{
				Clear_RX(0);
				TX_Flag=8;
				y=0;Uart0_TX();
				CDMA_time=2;
				while(TX_Flag)//�ȴ��������
				{
					if(CDMA_time==0)
						break;
				}
			}	
		}
		nb=0x00;
		if(time==0) break;	
	}
	//CDMA_time=1;
	//while(CDMA_time);
 	//Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_CGATT
* ��      ��      : ��ѯģ���Ƿ��ųɹ�
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
uchar NB_CGATT(uchar time)
{
	uchar nb=0; 
	strcpy((char*)TX,"AT+CGATT?\r\n");
    TX_Flag=11;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		CDMA_time=1;
		while(CDMA_time);
		if(Check_cmd(0,"OK"))
		{
			nb=Check_Str(':');
			nb=RX0[nb+1]-0x30;
			if(nb==1)//���ųɹ�
			{
				break;//����ѭ��	
			}
			else
			{
				if(Check_cmd(0,"TIND"))
				{
					nb=1;
					break;//����ѭ��
				}
				else Clear_RX(0);
				TX_Flag=11;
				y=0;Uart0_TX();
				CDMA_time=2;
				while(TX_Flag)//�ȴ��������
				{
					if(CDMA_time==0)
						break;
				}
			}	
		} 			
		/*if(Check_cmd(0,"TIND"))
		{
			nb=1;
			time=0;
			break;
		}*/		
		nb=0x00;
		if(time==0) break;	
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_CEREG
* ��      ��      : ��ѯģ������ע��״̬
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
 uchar NB_CEREG(uchar time)
{
	uchar nb=0; 
	strcpy((char*)TX,"AT+CGPADDR\r\n");
    TX_Flag=12;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		CDMA_time=1;
		while(CDMA_time);
		if(Check_cmd(0,"OK"))
		{
			nb=Check_Str(':');
			if(RX0[nb+3]+RX0[nb+4])
			{
		   		nb=1;
				break;//����ѭ��	
			}
			else
			{
				Clear_RX(0);
				TX_Flag=12;
				y=0;Uart0_TX();
				CDMA_time=2;
				while(TX_Flag)//�ȴ��������
				{
					if(CDMA_time==0)
						break;
				}
			}	
		}
		nb=0x00;
		if(time==0) break;	
	}
 	Clear_RX(0);
    return nb;
}  
/*******************************************************************************
* ��  ��  ��      : NB_CMEE
* ��      ��      : ���ô��󷵻�
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
AT+CMEE=1\r\n
*******************************************************************************/
uchar NB_CMEE(uint8 time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+MLWNMI=1\r\n");
    TX_Flag=13;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;	
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_CELL_RESELECTION
* ��      ��      : ����С����ѡ
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
AT+NCONFIG=CELL_RESELECTION,TRUE
*******************************************************************************/
/*uchar NB_CELL_RESELECTION(uint8 time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+CMEE=1\r\n");
    TX_Flag=11;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;	
	}
 	/*Clear_RX(0);
	strcpy((char*)TX,"AT+NEARFCN=0,0\r\n");
    TX_Flag=16;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;	
	}*/
/*	Clear_RX(0);
    return nb;

} */
/*******************************************************************************
* ��  ��  ��      : NB_CFUN
* ��      ��      : ��Ƶ���ܲ���
* ��      ��      : n 0 �ر���Ƶ 1  ����Ƶ time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
uchar NB_CFUN(uchar n,uchar time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+CFUN=");
	if(n) TX[8]=0x31;
	else  TX[8]=0x30;
	TX[9]=0x0D;
	TX[10]=0x0A;
    TX_Flag=11;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	CDMA_time=time;
	while(CDMA_time)//�ȴ�����ʱ��
	{
		Delay(4000);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		if(Check_cmd(0,"ERR"))
		{
			Clear_RX(0);
			TX_Flag=11;
			y=0;Uart0_TX();
			while(TX_Flag)//�ȴ��������
			{
				if(CDMA_time==0)
					break;
			}			
		}
		nb=0x00;
		if(CDMA_time==0) break;	
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_IoT_IP
* ��      ��      : IOTƽ̨��ַ
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
AT+NCDP=117.60.157.137,5683
AT+NCDP=180.101.147.115,5683
*******************************************************************************/
uchar NB_IoT_IP(uint8 time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+NCDP=117.60.157.137,5683\r\n");
    TX_Flag=29;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;		
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_IoT_123
* ��      ��      : ��ȡIOTƽ̨��ַ
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
AT+NCDP=117.60.157.137,5683
AT+NCDP=180.101.147.115,5683
*******************************************************************************/
uchar NB_IoT_123(uint8 time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+NCDP?\r\n");
    TX_Flag=10;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;		
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_IoT_124
* ��      ��      : AT ָ������ģ��
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
AT+NCDP=117.60.157.137,5683
AT+NCDP=180.101.147.115,5683
*******************************************************************************/
uchar NB_IoT_124(uchar time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+NRB\r\n");
    TX_Flag=8;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		CDMA_time=1;
		while(CDMA_time);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;		
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_CGA 
* ��      ��      : �����ն�����
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
/*uchar NB_CGA(uchar time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+CGATT=1\r\n");
    TX_Flag=12;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	CDMA_time=time;
	while(CDMA_time)//�ȴ�����ʱ��
	{
		CDMA_Wait=0;
		while(CDMA_Wait<1);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
	    if(Check_cmd(0,"ERR"))
		{
			Clear_RX(0);
			TX_Flag=12;
			y=0;Uart0_TX();
			while(TX_Flag)//�ȴ��������
			{
				if(CDMA_time==0)
					break;
			}			
		}
		nb=0x00;
		if(CDMA_time==0) break;		
	}
 	Clear_RX(0);
    return nb;
} */
/*******************************************************************************
* ��  ��  ��      : NB_NUESTATS 
* ��      ��      : ��ѯģ��״̬
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : 1 һ��  0 ��һ��
+NCDP:117.60.157.137,5683

*******************************************************************************/
uchar NB_NUESTATS(uint8 time)
 {
 	uchar nb=0,i,a;
	strcpy((char*)TX,"AT+NUESTATS\r\n");
    TX_Flag=13;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	CDMA_time=time;
	while(CDMA_time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"RSRQ"))
		{
			//SNR
			for(i=0;i<200;i++)
			{
				if(RX0[i]=='R' && RX0[i+1]==':')
				{
					break;
				}
			}
			a=i+2;
			if(RX0[a]>0x39 || RX0[a]<0x30)//�ź�ֵ�쳣
			{
				C_DATA[49]=0XFF;
				C_DATA[50]=0XFF;	
			}
			else//�ź�ֵ��Ϊ��
			{
				for(i=0;i<10;i++)
				{
					if(RX0[i+a]==0x0D) break;//��ѯ������
				}
				if(i==1)
				{
					C_DATA[49]=0x00;
					C_DATA[50]=RX0[a]-0x30;
				}
				else if(i==2)
				{
					C_DATA[49]=0x00;
					C_DATA[50]=(RX0[a]-0x30)*16+RX0[a+1]-0x30;
				}
				else if(i==3)
				{
					C_DATA[49]=RX0[a]-0x30;
					C_DATA[50]=(RX0[a+1]-0x30)*16+RX0[a+2]-0x30;	
				}					
			}
			//PCI
			for(i=0;i<200;i++)
			{
				if(RX0[i]=='P' && RX0[i+1]=='C' && RX0[i+2]=='I' && RX0[i+3]==':' )
				{
					break;
				}
			}
			a=i+4;
			for(i=0;i<10;i++)
			{
				if(RX0[i+a]==0x0D) break;//��ѯ������
			}
			if(i==1)
			{
				C_DATA[51]=0x00;
				C_DATA[52]=RX0[a]-0x30;
			}
			else if(i==2)
			{
				C_DATA[51]=0x00;
				C_DATA[52]=(RX0[a]-0x30)*16+RX0[a+1]-0x30;
			}
			else if(i==3)
			{
				C_DATA[51]=RX0[a]-0x30;
				C_DATA[52]=(RX0[a+1]-0x30)*16+RX0[a+2]-0x30;	
			}					
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(CDMA_time==0) break;		
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_CIMI 
* ��      ��      : ��ѯģ��״̬
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : 1 һ��  0 ��һ��
+NCDP:117.60.157.137,5683

*******************************************************************************/
uchar NB_CIMI(uint8 time)
 {
 	uchar nb=0,i,a;
	strcpy((char*)TX,"AT+CIMI\r\n");
    TX_Flag=9;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	CDMA_time=time;
	while(CDMA_time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			for(i=0;i<200;i++)
			{
				if(RX0[i]==0x4F && RX0[i+1]==0x4B)
				{
					break;
				}
			}
			a=i-19;
			for(i=0;i<15;i++)
			{
				C_DATA[34+i]=RX0[a+i];
			}					
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(CDMA_time==0) break;		
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_NMGS 
* ��      ��      : ȷ���ն˿��Խ������ݷ���
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
uchar NB_NMGS(uchar time)
{
	uchar nb=0;
	//����һ������ ��֤�Ƿ�����ƽ̨�ɹ�
	strcpy((char*)TX,"AT+MLWULDATA=4,AAAA0000\r\n");
    TX_Flag=25;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	//CDMA_time=time;
	while(--time)//�ȴ�����ʱ��
	{
		CDMA_time=1;
		while(CDMA_time);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		if(Check_cmd(0,"ERR"))
		{
			Clear_RX(0);
		    TX_Flag=25;
			y=0;Uart0_TX();
			while(TX_Flag)//�ȴ��������
			{
				if(CDMA_time==0)
					break;
			}			
		}
		nb=0x00;
		if(time==0) break;		
	}
 	Clear_RX(0);
	if(nb)//��ѯ�Ƿ��ڷ���״̬
	{
		strcpy((char*)TX,"AT+MLWMSTATUS?\r\n");
	    TX_Flag=16;
		y=0;Uart0_TX();
		CDMA_time=2;
		while(TX_Flag)//�ȴ��������
		{
			if(CDMA_time==0)
				break;
		}
		time=500;
		while(--time)//�ȴ�����ʱ��
		{
			Delay(15);
			if(Check_cmd(0,"ENABLED"))
			{
				nb=0x01;
		   		break;
			}
			nb=0x00;
			if(time==0) break;		
		}	
	}
	 Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_eDRX 
* ��      ��      : �ر�eDRX
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
/*uchar NB_eDRX(uchar time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+CEDRXS=0,5,");
	TX[14]=0x22;
	TX[15]=0x30;
	TX[16]=0x31;
	TX[17]=0x30;
	TX[18]=0x31;
	TX[19]=0x22;
	TX[20]=0x0D;
	TX[21]=0x0A;
    TX_Flag=22;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	CDMA_time=time;
	while(CDMA_time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(CDMA_time==0) break;		
	}
 	Clear_RX(0);
    return nb;
}*/
/*******************************************************************************
* ��  ��  ��      : NB_PSM 
* ��      ��      : �ر�PSM
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
/*uchar NB_PSM(uchar time)
{
	uchar nb=0;
	strcpy((char*)TX,"AT+CPSMS=0\r\n");
    TX_Flag=12;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	while(--time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(time==0) break;		
	}
 	Clear_RX(0);
    return nb;
}*/
/*******************************************************************************
* ��  ��  ��      : NB_NCSEARFCN
* ��      ��      : ��Ƶ
* ��      ��      : time �ȴ����ص�ʱ�� ��λ��  
* ��      ��      : ״ֵ̬��1 ok  0 err
*******************************************************************************/
uchar NB_NCSEARFCN(uchar time)
 {
 	uchar nb=0;
	strcpy((char*)TX,"AT+NCSEARFCN\r\n");
    TX_Flag=14;
	y=0;Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	CDMA_time=time;
	while(CDMA_time)//�ȴ�����ʱ��
	{
		Delay(50);
		if(Check_cmd(0,"OK"))
		{	
			nb=0x01;
	   		break;
		}
		nb=0x00;
		if(CDMA_time==0) break;	
	}
 	Clear_RX(0);
    return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_IoT
* ��      ��      : ����ƽ̨���Ӳ���
* ��      ��      : qwe ��Ҫ���͵�������ʼ��ַ��n ���͵�����λ����time �ȴ����ص�ʱ�� ��λ��  
* ��      ��      : ״ֵ̬��1 ok  0 err
*******************************************************************************/
uchar NB_IoT(void)
{
	uchar nb=0;
	//NB_CELL_RESELECTION(500);
	/*	if(NB_CFUN(0,20))//�ر���Ƶ
		 {		 	
		 	NB_IoT_IP(600);
		  	CDMA_time=2;
			while(CDMA_time);//�ȴ�����ʱ��
			*/
			NB_IoT_123(500);
		 	CDMA_time=1;
			while(CDMA_time);//�ȴ�����ʱ��
			NB_CMEE(500);
		 	CDMA_time=1;
			while(CDMA_time);//�ȴ�����ʱ��
		/*NB_CELL_RESELECTION(500);
			//if(NB_eDRX(10))//�ر�eDRX
			//{
				//NB_PSM(500);//�ر�PSM
				//CDMA_time=1;
				//while(CDMA_time);//�ȴ�����ʱ��
				//if(NB_IoT_IP(600))//����IoT IP
				//{	
				//	CDMA_time=3;
			//		while(CDMA_time);//�ȴ�����ʱ��
				//	if(NB_CFUN(1,20))//����Ƶ
				//	{					
				//		if(NB_CGA(20))//�����ն�����
				//		{ 
				//			CDMA_time=2;
				//			while(CDMA_time);//�ȴ�����ʱ��
				*/			
							nb=1;	
					//	}
				//	}
				//}				
			//}	*/

		 //}		
	//else nb=1;
	return nb;
}
/*******************************************************************************
* ��  ��  ��      : NB_NSOST
* ��      ��      : ��������
* ��      ��      : qwe ��Ҫ���͵�������ʼ��ַ��n ���͵�����λ����time �ȴ����ص�ʱ�� ��λ��  
* ��      ��      : ״ֵ̬��1 ok  0 err
AT+NMGS=5,00012E1F63
*******************************************************************************/
uchar NB_NSOST(uchar* qwe,unsigned short n,uchar time)
{
	uchar nb=0,s,a,b;//c,d,e,f;
	//NB_NSOCR(1);
	strcpy((char*)TX,"AT+MLWULDATA=");_nop_();
	if(n>99)
	{
		TX[13]=n/100+0x30;
		TX[14]=(n%100)/10+0x30;
		TX[15]=n%10+0x30;
		nb=16;	
	}
	else if(n>9)
	{
		TX[13]=n/10+0x30;
		TX[14]=n%10+0x30;
		nb=15;
	}
	else 
	{
		TX[13]=n+0x30;
		nb=14;
	}
	TX[nb]=0x2C;
	//Э����أ�������
	for(s=0;s<n;s++)
	{
	    a=qwe[s]/16;
		b=qwe[s]%16;
		if(a>9)
		{
			if(a==10) a=0x41;
			if(a==11) a=0x42;
			if(a==12) a=0x43;
			if(a==13) a=0x44;
			if(a==14) a=0x45;
			if(a==15) a=0x46;
		}
		else a=a+0x30;
		if(b>9)
		{
		if(b==10) b=0x41;
		if(b==11) b=0x42;
		if(b==12) b=0x43;
		if(b==13) b=0x44;
		if(b==14) b=0x45;
		if(b==15) b=0x46;
		}
		else b=b+0x30;
		TX[nb+1+2*s]=a;
		TX[nb+2+2*s]=b;
	}
	TX[nb+1+2*n]=0x0D;
	TX[nb+2+2*n]=0x0A;
	TX_Flag=nb+3+2*n;
	Uart0_TX();
	CDMA_time=2;
	while(TX_Flag)//�ȴ��������
	{
		if(CDMA_time==0)
			break;
	}
	y=0;
	CDMA_time=time;
	while(--time)//�ȴ�����ʱ��
	{
		CDMA_time=1;
		while(CDMA_time);
		if(Check_cmd(0,"OK")) 
		{
		    nb=0x01;
		    break;
		}
		else if(Check_cmd(0,"ERR"))
		{
			TX_Flag=nb+3+2*n;
			y=0;Uart0_TX();
			while(TX_Flag);//�ȴ��������			
		}
		else nb=0x00;
		if(CDMA_time==0) break;	
	}
	Clear_RX(0);
    return nb;	
}
/*******************************************************************************
* ��  ��  ��      : Data_deal
* ��      ��      : NBģ���ϵ磬���ȴ���������
* ��      ��      : cs Э����룬num ������������  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
void Data_deal(uint8_t cs,unsigned short num)
{
    unsigned short i;
	C_DATA[0]=0x1B;
	C_DATA[1]=0x06;
	C_DATA[2]=0x66;//g_write_value[0];
	C_DATA[3]=0x66;//g_write_value[1];
    C_DATA[4]=0x66;//g_write_value[2];
	C_DATA[5]=0x66;//g_write_value[3];
        switch(cs)
	{
	case 0://������
		C_DATA[6]=0xA1;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		C_DATA[15]=0x00;
		usMBCRC16(&C_DATA[2],14);
		C_DATA[16]=ucCRCLo;
		C_DATA[17]=ucCRCHi;
		C_DATA[18]=0x68;
		C_DATA[19]=0x16;
		break;
	case 1://�����ϴ�
		//��ѹ�ɼ�
		ADC_Read();
		//�ź�ǿ�Ȳɼ�
		g_write_value[23] =(g_write_value[23]&0xE0)+(g_write_value[24]&0x1F);
		C_DATA[6]=0xA2;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		C_DATA[15]=0x25;
		//�û�����ˮ��
		C_DATA[16]=g_write_value[7];
		C_DATA[17]=g_write_value[8];
		C_DATA[18]=g_write_value[9];
		//����ʱ��
		C_DATA[19]=g_write_value[13];
		C_DATA[20]=g_write_value[14];
		C_DATA[21]=g_write_value[15];
		C_DATA[22]=g_write_value[16];
		C_DATA[23]=g_write_value[17];
		C_DATA[24]=g_write_value[18];
		C_DATA[25]=g_write_value[19];
		//�ϴ����
		C_DATA[26]=g_write_value[34];
		//�ϴ�ʱ��
		C_DATA[27]=g_write_value[35];//g_write_value[120];
		C_DATA[28]=g_write_value[36];//g_write_value[121];
		//���嵱��
		C_DATA[29]=g_write_value[27];
		//��ص�ѹ
		C_DATA[30]=g_write_value[38];
		//��״̬
		C_DATA[31]=g_write_value[22];
		C_DATA[32]=g_write_value[23];
		//�Ѷ�����������
		C_DATA[33]=g_write_value[20];
		//IMSI�� 15�ֽ� 48
		//NB_CIMI(2);
		//SNR ֵ 2�ֽ� 50
		//NB_NUESTATS(2);
		//PCI ֵ 2�ֽ� 51 52

		//У��λ
		usMBCRC16(&C_DATA[2],51);
		C_DATA[53]=ucCRCLo;
		C_DATA[54]=ucCRCHi;
		//��β
		C_DATA[55]=0X68;
		C_DATA[56]=0X16;
		break;
	case 3://дָ���
		C_DATA[6]=TX_Flag;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		C_DATA[15]=0x01;
		C_DATA[16]=Read_Flag;
		usMBCRC16(&C_DATA[2],15);
		C_DATA[17]=ucCRCLo;
		C_DATA[18]=ucCRCHi;
		C_DATA[19]=0X68;
		C_DATA[20]=0X16;
		break;
	case 4://������ȡ
		C_DATA[6]=0xA6;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		C_DATA[15]=0x02;
		C_DATA[16]=g_write_value[22]&0x80;
		C_DATA[17]=g_write_value[27];
		usMBCRC16(&C_DATA[2],16);
		C_DATA[18]=ucCRCLo;
		C_DATA[19]=ucCRCHi;
		C_DATA[20]=0X68;
		C_DATA[21]=0X16;
		break;
	case 6://IP���˿ڶ�ȡ
		C_DATA[6]=0xAB;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		C_DATA[15]=0x09;
		
		C_DATA[16] =g_write_value[28];
		C_DATA[17]=g_write_value[29];
		C_DATA[18]=g_write_value[30];
		C_DATA[19]=g_write_value[31];
		C_DATA[20]=g_write_value[32];
		C_DATA[21]=g_write_value[33];

		C_DATA[22]=g_write_value[34];
		
		C_DATA[23]=g_write_value[35];
		C_DATA[24]=g_write_value[36];
		
		usMBCRC16(&C_DATA[2],24);
		C_DATA[25]=ucCRCLo;
		C_DATA[27]=ucCRCHi;
		C_DATA[28]=0x68;
		C_DATA[29]=0x16;
		break;
	case 7://���������ϴ� ǰ10��  1-10
		C_DATA[6]=0xAF;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		if(g_write_value[20]>10) C_DATA[15]=70;
		else C_DATA[15]=g_write_value[20]*7;
		for(i=0;i<C_DATA[15];i++)//��������ת��
		C_DATA[i+16]=meter_data[i];
		C_DATA[15]=C_DATA[15]+1;
		C_DATA[15+C_DATA[15]]=g_write_value[27];
		//У��λ
		usMBCRC16(&C_DATA[2],14+C_DATA[15]);
		C_DATA[16+C_DATA[15]]=ucCRCLo;
		C_DATA[17+C_DATA[15]]=ucCRCHi;
		//��β
		C_DATA[18+C_DATA[15]]=0X68;
		C_DATA[19+C_DATA[15]]=0X16;
		break;
	case 8://���������ϴ� �ڶ���10�� 11-20
		C_DATA[6]=0xAF;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		if(g_write_value[20]>20) C_DATA[15]=70;
		else C_DATA[15]=(g_write_value[20]-10)*7;
		for(i=0;i<C_DATA[15];i++)//��������ת��
		C_DATA[16+i]=meter_data[i+70];//i-9+70
		C_DATA[15]=C_DATA[15]+1;
		C_DATA[15+C_DATA[15]]=g_write_value[27];
		//У��λ
		usMBCRC16(&C_DATA[2],14+C_DATA[15]);
		C_DATA[16+C_DATA[15]]=ucCRCLo;
		C_DATA[17+C_DATA[15]]=ucCRCHi;
		//��β
		C_DATA[18+C_DATA[15]]=0X68;
		C_DATA[19+C_DATA[15]]=0X16;
		break;
	case 9://���������ϴ� ������10��  21-30
		C_DATA[6]=0xAF;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		if(g_write_value[20]>30) C_DATA[15]=70;
		else C_DATA[15]=(g_write_value[20]-20)*7;
		for(i=0;i<C_DATA[15];i++)//��������ת��
		C_DATA[16+i]=meter_data[i+140];//i-9+70
		C_DATA[15]=C_DATA[15]+1;
		C_DATA[15+C_DATA[15]]=g_write_value[27];
		//У��λ
		usMBCRC16(&C_DATA[2],14+C_DATA[15]);
		C_DATA[16+C_DATA[15]]=ucCRCLo;
		C_DATA[17+C_DATA[15]]=ucCRCHi;
		//��β
		C_DATA[18+C_DATA[15]]=0X68;
		C_DATA[19+C_DATA[15]]=0X16;
		break;
	case 10://���������ϴ� ���ĸ�10�� 31-40
		C_DATA[6]=0xAF;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		if(g_write_value[20]>40) C_DATA[15]=70;
		else C_DATA[15]=(g_write_value[20]-30)*7;
		for(i=0;i<C_DATA[15];i++)//��������ת��
		C_DATA[16+i]=meter_data[i+210];//i-9+70
		C_DATA[15]=C_DATA[15]+1;
		C_DATA[15+C_DATA[15]]=g_write_value[27];
		//У��λ
		usMBCRC16(&C_DATA[2],14+C_DATA[15]);
		C_DATA[16+C_DATA[15]]=ucCRCLo;
		C_DATA[17+C_DATA[15]]=ucCRCHi;
		//��β
		C_DATA[18+C_DATA[15]]=0X68;
		C_DATA[19+C_DATA[15]]=0X16;
		break;
	case 11://���������ϴ� �����10�� 41-48
		C_DATA[6]=0xAF;
		C_DATA[7]=g_write_value[0];
		C_DATA[8]=g_write_value[1];
		C_DATA[9]=g_write_value[2];
		C_DATA[10]=g_write_value[3];
		C_DATA[11]=g_write_value[4];
		C_DATA[12]=g_write_value[5];
		C_DATA[13]=g_write_value[6];
		C_DATA[14]=0x00;
		if(g_write_value[20]>50) C_DATA[15]=70;
		else C_DATA[15]=(g_write_value[20]-40)*7;
		for(i=0;i<C_DATA[15];i++)//��������ת��
		C_DATA[16+i]=meter_data[i+280];//i-9+70
		C_DATA[15]=C_DATA[15]+1;
		C_DATA[15+C_DATA[15]]=g_write_value[27];
		//У��λ
		usMBCRC16(&C_DATA[2],14+C_DATA[15]);
		C_DATA[16+C_DATA[15]]=ucCRCLo;
		C_DATA[17+C_DATA[15]]=ucCRCHi;
		//��β
		C_DATA[18+C_DATA[15]]=0X68;
		C_DATA[19+C_DATA[15]]=0X16;
		break;		
	}
	if(RX0_flag==1)  {TX_Flag=num;j=0;SBUF=C_DATA[j];while(TX_Flag);} 
	else NB_NSOST(C_DATA,num,5);
}
/*******************************************************************************
* ��  ��  ��      : RX_Judge
* ��      ��      : Э�鴦��
* ��      ��      : NULL 
* ��      ��      : NULL
*******************************************************************************/
void RX_Judge(void)
{
	uint8_t i;
        if(C_DATA[0]==0x1B && C_DATA[1]==0x06 && ((C_DATA[2]==g_write_value[0] && C_DATA[3]==g_write_value[1] && C_DATA[4]==g_write_value[2] && C_DATA[5]==g_write_value[3]
		 && C_DATA[6]==g_write_value[4] && C_DATA[7]==g_write_value[5] && C_DATA[8]==g_write_value[6])
	|| (C_DATA[2]==0xAA && C_DATA[3]==0xAA && C_DATA[4]==0xAA && C_DATA[5]==0XAA && C_DATA[6]==0XAA && C_DATA[7]==0XAA && C_DATA[8]==0XAA))) //��ַʶ��
	{
		if(C_DATA[9]==0x41 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x00)//����ָ��
		{
			usMBCRC16(&C_DATA[2],12);
			if(C_DATA[14]==ucCRCLo && C_DATA[15]==ucCRCHi)
		    {	
			Data_deal(0,20);
			CDMA_Wait=100;
			}
		}
		if(C_DATA[9]==0x42 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x00)//�����ϴ�ָ��
		{
			usMBCRC16(&C_DATA[2],12);
			if(C_DATA[14]==ucCRCLo && C_DATA[15]==ucCRCHi)
			{
			Data_deal(1,57);
			}
		}
		if(C_DATA[9]==0x4C && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x07)//д����ʱ��
		{
			usMBCRC16(&C_DATA[2],19);
			if(C_DATA[21]==ucCRCLo && C_DATA[22]==ucCRCHi)
			{
				g_write_value[13]=C_DATA[14];
				g_write_value[14]=C_DATA[15];
				g_write_value[15]=C_DATA[16];
				g_write_value[16]=C_DATA[17];
				g_write_value[17]=C_DATA[18];
				g_write_value[18]=C_DATA[19];
				g_write_value[19]=C_DATA[20];
				RTCSet();
				Read_Flag=0x00;
				TX_Flag=0xAC;
				Data_deal(3,21);	
			}
		}
		if(C_DATA[9]==0x43 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x01)//���ſ���ָ��
		{
			usMBCRC16(&C_DATA[2],13);
			if(C_DATA[15]==ucCRCLo && C_DATA[16]==ucCRCHi)
			{
				 Read_Flag=0x11;
				 TX_Flag=0xA3;				 	                    
			     Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x44 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x02)//��������
		{
			usMBCRC16(&C_DATA[2],14);
			if(C_DATA[16]==ucCRCLo && C_DATA[17]==ucCRCHi)
			{
				if(C_DATA[14]==0x00)
				{
					 if((g_write_value[22]>>7)==0)
					 {
					 	 g_write_value[27]=C_DATA[15];
						 Read_Flag=0x00;
					 }
					 else
					 {
					 	Read_Flag=0x11;
					 }
				}
				else if(C_DATA[14]==0x80)
				{
					  g_write_value[22] |=C_DATA[15];
					  g_write_value[27]=C_DATA[16];
					  Read_Flag=0x00;
				}
				else if(C_DATA[14]==0x88)//�ָ�����
				{
					  g_write_value[22] &=~0x80;
					  g_write_value[7]=0x00;//��ˮ������
					  g_write_value[8]=0x00;
					  g_write_value[9]=0x00;
					  Read_Flag=0x22;
				}
				//���ݴ洢
				Write_SegC();
				TX_Flag=0xA4;
				Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x46 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x00)//������ 
		{
			usMBCRC16(&C_DATA[2],12);
			if(C_DATA[14]==ucCRCLo && C_DATA[15]==ucCRCHi)
			{
				Data_deal(4,22);
			}
		}
		if(C_DATA[9]==0x47 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x00)//������汾
		{
			usMBCRC16(&C_DATA[2],12);
			if(C_DATA[14]==ucCRCLo && C_DATA[15]==ucCRCHi)
			{
				 Read_Flag=g_write_value[47];
			 	 TX_Flag=0xA7;
			     Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x48 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x00)//�����ַ
		{
			usMBCRC16(&C_DATA[2],12);
			if(C_DATA[14]==ucCRCLo && C_DATA[15]==ucCRCHi)
			{
				 Read_Flag=0x00;
			 	 TX_Flag=0xA8;
			         Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x49 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x07)//д���ַ
		{
			usMBCRC16(&C_DATA[2],19);
			if(C_DATA[21]==ucCRCLo && C_DATA[22]==ucCRCHi)
			{
				g_write_value[0]=C_DATA[14];
				g_write_value[1]=C_DATA[15];
				g_write_value[2]=C_DATA[16];
				g_write_value[3]=C_DATA[17];
				g_write_value[4]=C_DATA[18];
				g_write_value[5]=C_DATA[19];
				g_write_value[6]=C_DATA[20];
				//���ݴ洢
				Write_SegC();
 				Read_Flag=0x00;
				TX_Flag=0xA9;
				Data_deal(3,21);
			}
		} 
		if(C_DATA[9]==0x4A && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x06)//����IP&Port
		{
			usMBCRC16(&C_DATA[2],18);
			if(C_DATA[20]==ucCRCLo && C_DATA[21]==ucCRCHi)
			{	//IP��Ϣ
				g_write_value[28]=C_DATA[14];
				g_write_value[29]=C_DATA[15];
				g_write_value[30]=C_DATA[16];
				g_write_value[31]=C_DATA[17];
				g_write_value[32]=C_DATA[18];
				g_write_value[33]=C_DATA[19];
				//���ݴ洢
				Write_SegC(); 
				Read_Flag=0x00;
				TX_Flag=0xAA;
				Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x4B && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x00)//��IP���˿�
		{
			usMBCRC16(&C_DATA[2],12);
			if(C_DATA[14]==ucCRCLo && C_DATA[15]==ucCRCHi)//CDMA
			{
				 Data_deal(6,37);
			}
		}
		if(C_DATA[9]==0x4D && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x01 && C_DATA[14]==0x11)//����λ���
		{
			usMBCRC16(&C_DATA[2],13);
			if(C_DATA[15]==ucCRCLo && C_DATA[16]==ucCRCHi)
			{
				g_write_value[22]&=0x83;//�������λ
				g_write_value[23]&=~0xE0;
				//���ݴ洢
				Write_SegC();          
			    FDcycflag=1;  
				flagtype &=~0x80; 
			    flagtype &=~0x0C;       
			    flagtype |= 0x02;      
 
				//���Һ����ʾ    
			    //LCDRAM13 &=~(BIT1+BIT2+BIT6); 
				//LCDRAM12 &=~BIT5;  
				Read_Flag=0x00;
				TX_Flag=0xAD;
				Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x4E && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x03)//�����ϱ����ں�ʱ��
		{
			usMBCRC16(&C_DATA[2],15);
			if(C_DATA[17]==ucCRCLo && C_DATA[18]==ucCRCHi)
			{
			    //�ϴ���� hex
				g_write_value[34]=C_DATA[14];
				//��ʱ�ϴ�ʱ�� ʱ ��  BCD��	   
				g_write_value[35]=C_DATA[15];
				g_write_value[36]=C_DATA[16];
				date=mem_date=0;
				RNG_Time();
				Write_SegC();
				Read_Flag=0x00;
				TX_Flag=0xAE;
				Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x4F && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x00)//ȷ�϶�ȡ�������ݳɹ�
		{
			usMBCRC16(&C_DATA[2],12);
			if(C_DATA[14]==ucCRCLo && C_DATA[15]==ucCRCHi)
			{
				 g_write_value[46]=2;
				 g_write_value[20]=0; 
				 Write_SegC();
				 Read_Flag=0x22;
			 	 TX_Flag=0xB0;
			     Data_deal(3,21);
			}
		}
		if(C_DATA[9]==0x45 && C_DATA[10]==0x10 && C_DATA[11]==0x00 && C_DATA[12]==0x00 && C_DATA[13]==0x03)//д�����
		{
			usMBCRC16(&C_DATA[2],15);
			if(C_DATA[17]==ucCRCLo && C_DATA[18]==ucCRCHi)
			{
				g_write_value[7]=C_DATA[14];   
				g_write_value[8]=C_DATA[15];
				g_write_value[9]=C_DATA[16];
				Write_SegC();
				Read_Flag=0x00;
				TX_Flag=0xA5;
				Data_deal(3,21);
			}
		}
		for(i=0;i<100;i++)
		{
			C_DATA[i]=0;
		}
		Clear_RX(0);
		y=0;
	}
	InitData();
}
/*******************************************************************************
* ��  ��  ��      : NB_RX
* ��      ��      : NBģ��������ݴ���
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
+NNMI:4,AAAA0000
*******************************************************************************/
void NB_RX(void)
{
	uint8_t i,n,a,b,temp,num;
	for(i=0;i<50;i++)
	if(RX0[i]=='A' && RX0[i+1]=='T' && RX0[i+2]=='A' && RX0[i+3]==':')//��ѯ�Ƿ��н��յ�����
	{
		CDMA_time=1;
		while(CDMA_time);
		temp=1;
		break;
	}		
     if(temp)//���յ�����
	{
		temp=0;
		a=Check_Str(',');//�ҵ�����λ��
		b=Check_Str(':');
		n=a-b-1;
		if(n==1)
		{
			num=RX0[a-1]-0x30;
		}
		else if(n==2)
		{
			num=RX0[a-1]-0x30;
			num=(RX0[a-2]-0x30)*10+num;
		}
		else if(n==3)
		{
			num=RX0[a-1]-0x30;
			num=(RX0[a-2]-0x30)*10+num;
			num=num+(RX0[a-3]-0x30)*100; //num���յ��ֽ���
		}
		n=a;
		//Э��ת��
			for(i=0;i<num;i++)
			{
				a=RX0[n+1+i*2];
			    b=RX0[n+2+i*2];
				if(a>0x40)
				{		   
					if(a==0x41) a=10;
					if(a==0x42) a=11;
					if(a==0x43) a=12;
					if(a==0x44) a=13;
					if(a==0x45) a=14;
					if(a==0x46) a=15;
				}
				else a=a-0x30;
				if(b>0x40)
				{
					if(b==0x41) b=10;
					if(b==0x42) b=11;
					if(b==0x43) b=12;
					if(b==0x44) b=13;
					if(b==0x45) b=14;
					if(b==0x46) b=15;
				}
				else b=b-0x30;
				C_DATA[i]=a*16+b;
			}
			RX_Judge();	//Э���ж�		
	}
	else
	{
		if(RX0[99]!=0)
		{
			 Clear_RX(0);
			 y=0;
		}
	}
}
/*******************************************************************************
* ��  ��  ��      : NB_Send
* ��      ��      : NBģ���ϵ磬���ȴ���������
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
void NB_Send(void)
{
	Uart_Init();_nop_();_nop_();
    z=1;
	if(NB_Open(500))//�����ɹ�
	{	
		if(NB_IoT())
		{	
			if(NB_CSQ(50))//�ȴ��ź��ȶ�
			{	 
			 	if(NB_CGATT(60))//�Ƿ��ųɹ�
			 	{	
					if(NB_CEREG(3))
					{  	
				 		if(NB_NMGS(10))//����һ�����ݣ�����ģ������
						{
							CDMA_time=1;
							while(CDMA_time);//�ȴ��ر�
							//IMSI�� 15�ֽ� 48
							NB_CIMI(2);
							//SNR ֵ 2�ֽ� 50
							NB_NUESTATS(2);
							//PCI ֵ 2�ֽ� 51 52
							Data_deal(1,57);//����ʵʱ����
							CDMA_time=1;
							while(CDMA_time);//�ȴ��ر�
							Read_Flag=0x22;
				 	 		TX_Flag=0xB0;
				         	Data_deal(3,21);// ���ͱ�־λ 
							CDMA_Wait=0;
							y=0;
							while(CDMA_Wait<40) //���ߵȴ�25��
							{								
								NB_RX();//�ȴ����ݽ���	
							}
						 	NB_CFUN(0,15);							
						}
						else
						{
							if(NB_CFUN(0,20))//�ر���Ƶ
							{
								NB_NCSEARFCN(2);
								CDMA_time=1;
								while(CDMA_time);//�ȴ��ر�	
							}		
						}
						
 					 } 
			 	}
				else
				{
					if(NB_CFUN(0,20))//�ر���Ƶ
					{
						NB_NCSEARFCN(2);
						CDMA_time=1;
						while(CDMA_time);//�ȴ��ر�	
					}
					
				}
			}
			else
			{
				if(NB_CFUN(0,20))//�ر���Ƶ
				{
					NB_NCSEARFCN(2);
					CDMA_time=1;
					while(CDMA_time);//�ȴ��ر�	
				}
				
			}	
		} 
	}
	NB_Close(1);
    z=0; 
}
/*******************************************************************************
* ��  ��  ��      : NB_Send2
* ��      ��      : NB ���� ���ò���
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
void NB_Send2(void)
{
	Uart_Init();_nop_();_nop_();
    z=1;
	if(NB_Open(500))//�����ɹ�
	{	 
		if(NB_CFUN(0,20))//�ر���Ƶ
		 {		 	
			if(NB_IoT_IP(600))//����IoT IP
			{	
				NB_IoT_123(500);
				NB_IoT_124(8);
			}	

		 }		
	}
	NB_Close(1);
    z=0; 
}
/*******************************************************************************
* ��  ��  ��      : Data_UP
* ��      ��      : NB��ʱ�ϴ�
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
void Data_UP(void)
{
	unsigned char send_num=0;
	//���������ϱ�
	if(g_write_value[20]==0)
	{
		Read_Flag=0x00;		
	}
	else if(g_write_value[20]<11)
	{
		send_num=g_write_value[20]*7+21;
		Data_deal(7,send_num);//1-10�� 
		Read_Flag=0x11;	
	}
	else if(g_write_value[20]<21)
	{
		send_num=(g_write_value[20]-10)*7+21;
		Data_deal(7,91);//ǰ10��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(8,send_num);//11-20��	
		Read_Flag=0x11;
	}
	else if(g_write_value[20]<31)
	{
		send_num=(g_write_value[20]-20)*7+21;
		Data_deal(7,91);//ǰ10��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(8,91);//ǰ20��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(9,send_num);//21-30��	
		Read_Flag=0x11;							
	}
	else if(g_write_value[20]<41)
	{
		send_num=(g_write_value[20]-30)*7+21;
		Data_deal(7,91);//ǰ10��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(8,91);//ǰ20��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(9,91);//ǰ30��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(10,send_num);//31-40��
		Read_Flag=0x11;								
	}
	else if(g_write_value[20]<51)
	{
		send_num=(g_write_value[20]-40)*7+21;
		Data_deal(7,91);//ǰ10��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(8,91);//ǰ20��
		CDMA_time=2;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(9,91);//ǰ30��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(10,91);//ǰ40��
		CDMA_time=1;
		while(CDMA_time);//�ȴ��ر�	
		Data_deal(11,send_num);//41-50��
		Read_Flag=0x11;								
	}
	TX_Flag=0xB0;
	Data_deal(3,21);	
}
/*******************************************************************************
* ��  ��  ��      : NB_Timing_Send
* ��      ��      : NB��ʱ�ϴ�
* ��      ��      : time �ȴ����ص�ʱ��  
* ��      ��      : ִ�н�� 1 OK  0 err
*******************************************************************************/
void NB_Timing_Send(void)
{
	Uart_Init();_nop_();_nop_();
    z=1;
	if(NB_Open(500))//�����ɹ�
	{	 
		if(NB_IoT())
		{
			if(NB_CSQ(50))//�ȴ��ź��ȶ�
			{	 
			 	if(NB_CGATT(50))//�Ƿ��ųɹ�
			 	{	
					if(NB_CEREG(3))
					{
						if(NB_NMGS(10))//����һ�����ݣ�����ģ������
						{
							CDMA_time=1;
							while(CDMA_time);//�ȴ��ر�	
							//IMSI�� 15�ֽ� 48
							NB_CIMI(2);
							//SNR ֵ 2�ֽ� 50
							NB_NUESTATS(2);
							//PCI ֵ 2�ֽ� 51 52
							//ʵʱ�����ϱ�
							Data_deal(1,57);
							CDMA_time=1;
							while(CDMA_time);
							//���������ϱ�
							Data_UP();
							g_write_value[46]=1;//���ݷ��ͱ�־
							//�ȴ�����
							CDMA_Wait=0;
							y=0;
							while(CDMA_Wait<30)
							{								
								NB_RX();//�ȴ����ݽ���	
							}
							if(g_write_value[46]==1)//���߳ɹ�  ����û�н��յ�ƽָ̨����·�һ��
							{
								//IMSI�� 15�ֽ� 48
								NB_CIMI(2);
								//SNR ֵ 2�ֽ� 50
								NB_NUESTATS(2);
								//PCI ֵ 2�ֽ� 51 52
								//ʵʱ�����ϱ�
								Data_deal(1,57);
								CDMA_time=1;
								while(CDMA_time);
								//���������ϱ�
								Data_UP();
								CDMA_Wait=0;
								y=0;
								while(CDMA_Wait<30)
								{								
									NB_RX();//�ȴ����ݽ���	
								}
							}
						 	NB_CFUN(0,15);							
						}
						else
						{
							if(NB_CFUN(0,20))//�ر���Ƶ
							{
								NB_NCSEARFCN(2);
								CDMA_time=1;
								while(CDMA_time);//�ȴ��ر�	
							}							
						}
						
					}	
			 	}
				else
				{
					if(NB_CFUN(0,20))//�ر���Ƶ
					{
						NB_NCSEARFCN(2);
						CDMA_time=1;
						while(CDMA_time);//�ȴ��ر�	
					}
				}
			}
			else
			{
				if(NB_CFUN(0,20))//�ر���Ƶ
				{
					NB_NCSEARFCN(2);
					CDMA_time=1;
					while(CDMA_time);//�ȴ��ر�	
				}
			}	
		}
	}
	NB_Close(1);
    z=0;
}
/*******************************************************************************
* ��  ��  ��      : RX0_read
* ��      ��      : �������ò�����ȡ
* ��      ��      : ��  
* ��      ��      : ��
*******************************************************************************/
void RX0_read(void)
{
	uchar i;
	RX0_flag=0;z=0;
	Uart0_Init();
	CDMA_time=1;
	while(CDMA_time);//�ȴ�����ʱ��	if(RX1_flag)
	if(RX0_flag==1)
	{		
		for(i=0;i<40;i++) C_DATA[i]=RX0[i];
		RX_Judge();
		for(i=0;i<40;i++) RX0[i]=0;
		RX0_flag=0;z=0;
	}
	showIP=0;
	NB_Close(1);
}
//================================================
//UART�ж�	 ���ڵ���żУ��������ʵ��
//================================================
void INTERRUPT_UART(void) interrupt 4
{
//------------------------------------------------
	if(SCON & U0RI)						   		 //�����U0�����ж�	
	{
	    SCON &= ~U0RI; 							 //��������жϱ�־
		RX0[z]=SBUF;
		if(RX0[0]==0x1B)
		{
			z++;
			if(z==(RX0[13]+16)) 
			RX0_flag=1;
			if(z>40) z=0;			
		}
	}
//------------------------------------------------
	if(SCON & U0TI)								 //�����U0�����ж�
	{
		SCON &= ~U0TI;	//�巢������жϱ�־
		j++;							                 
	    if (j < TX_Flag)  SBUF =C_DATA[j];             
	    else TX_Flag=0;//��ʾ������� 
	}
//================================================
//UART1�ж�	 ���ڵ���żУ��������ʵ��
//================================================
	//------------------------------------------------
	if(SCON1 & U1RI)								 //�����U1�����ж�
	{
		SCON1 &= ~U1RI;
		RX0[y]=SBUF1;
		y++;
		if(y>150) y=0;
	}
//------------------------------------------------
	if(SCON1 & U1TI)								 //�����U1�����ж�
	{	
	  	SCON1 &= ~U1TI;
		j++;							                 
	    if (j < TX_Flag)  SBUF1 =TX[j];             
	    else TX_Flag=0;//��ʾ������� 
	}

}