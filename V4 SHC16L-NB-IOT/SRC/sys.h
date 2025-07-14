#include "REG251S_user.h"
#include "4802_reg_user.h"
#define uchar unsigned char
#define uint8 unsigned int
#define uint8_t unsigned char
/*************************************************
����Ҫ���Ե�IP
*************************************************/
#define		START	 0X00
#define		CLK	 	 0X01
//#define 	LCD		 0X10
#define		RTC		 0X11
#define		TIMER	 0X20
#define		PCA		 0X21
#define		SPI		 0X30
//#define	UART	 0X31
#define		I2C		 0X70
#define		I2CA	 0X71
#define		WDT		 0X80
#define		GPIO	 0X90

/*************************************************
��׼λ����
*************************************************/
#define		BIT0	0X01
#define		BIT1	0X02
#define		BIT2	0X04
#define		BIT3	0X08
#define		BIT4	0X10
#define		BIT5	0X20
#define		BIT6	0X40
#define		BIT7	0X80
/*************************************************
�ж�ʹ��
*************************************************/
//AIE
#define		RTCE	BIT6						 //RTC�ж�
#define		ADCE	BIT5						 //ADC�ж�
#define		VCE		BIT4						 //VC�ж�
#define		LVD		BIT3						 //LVD�ж�
#define		ISOE	BIT2						 //7816�ж�
#define		I2CE	BIT1						 //I2C�ж�
#define		PTE		BIT0						 //�˿��ж�

/*************************************************
SYS
*************************************************/
//LPM
#define 	LPMIN	LPM|=0X01;LPM|=0X02			 //����͹���ģʽ

//PCON
#define		IDLE	BIT0
#define		IDLEIN	PCON |= IDLE				 //�������ģʽ

/*************************************************
CLK
*************************************************/
//CLKC
#define		LCDCLK		BIT7					 //LCDʱ��ѡ��
#define		LCDCLKX32	CLKC &= ~LCDCLK			 //�ⲿ
#define		LCDCLKIRC	CLKC |= LCDCLK			 //�ڲ�

#define		WDTCLK		BIT6					 //WDTʱ��ѡ��
#define		WDTCLKX32	CLKC &= ~WDTCLK			 //�ⲿ
#define		WDTCLKIRC	CLKC |= WDTCLK			 //�ڲ�

#define		RTCCLK		BIT5					 //RTCʱ��ѡ��
#define		RTCCLKX32	CLKC &= ~RTCCLK			 //�ⲿ
#define		RTCCLKIRC	CLKC |= RTCCLK			 //�ڲ�

#define		SYSDS1		BIT4					 //ϵͳʱ�Ӵ���Ƶʱ�ӷ�Ƶѡ��1
#define 	SYSDS0		BIT3					 //ϵͳʱ�Ӵ���Ƶʱ�ӷ�Ƶѡ��0
#define 	SYSDS_0		0x00					 //ϵͳʱ��Ϊ��Ƶʱ��
#define 	SYSDS_1		SYSDS0					 //ϵͳʱ��Ϊ��Ƶʱ��2��Ƶ
#define 	SYSDS_2		SYSDS1					 //ϵͳʱ��Ϊ��Ƶʱ��4��Ƶ
#define 	SYSDS_3		SYSDS0 + SYSDS1		 	 //ϵͳʱ��Ϊ��Ƶʱ��8��Ƶ

#define		X32KEN		BIT2					 //�ⲿ32Kʹ��

#define		IRCEN		BIT1					 //�ڲ�RCʹ��

#define		SYSCLK		BIT0					 //ϵͳʱ��ѡ��

//CLKC1
#define 	CLKFS1		BIT7					 //��Ƶʱ��Ƶ��ѡ��1
#define 	CLKFS0		BIT6					 //��Ƶʱ��Ƶ��ѡ��0
#define		CLKF_2M		0X00					 //��Ƶʱ��Ƶ��2M
#define		CLKF_4M		CLKFS0					 //��Ƶʱ��Ƶ��4M
#define		CLKF_8M		CLKFS1					 //��Ƶʱ��Ƶ��8M
#define		CLKF_16M	CLKFS0 + CLKFS1			 //��Ƶʱ��Ƶ��16M

//CLKC2
#define		X32STB		BIT7					 //�ⲿ32K�ȶ���־λ
#define		IRCSTB		BIT6					 //�ڲ�16M�ȶ���־λ

//PERICLK0
#define		VCCLKEN		BIT4					 //��Χģ��ʱ������
#define		LVDCLKEN	BIT3		
#define		BGRCLKEN	BIT2
#define		ADCCLKEN	BIT1
#define		LCDCLKEN	BIT0

//PERICLK1
#define		SPICLKEN	BIT6
#define		DESCLKEN	BIT5
#define		RNGCLKEN	BIT4					 //��Χģ��ʱ������
#define		CRCCLKEN	BIT3		
#define		DMACLKEN	BIT2
#define		RTCCLKEN	BIT1
#define		FLASHCLKEN	BIT0

//PERICLK2
#define		X7816CLKEN	BIT7
#define		I2CCLKEN	BIT6
#define		UART0CLKEN	BIT5
#define		UART1CLKEN	BIT4					 //��Χģ��ʱ������
#define		TIMERCLKEN	BIT3		
#define		PCACLKEN	BIT2
#define		WDTCLKEN	BIT1
#define		PORTCLKEN	BIT0


/*************************************************
LCD
*************************************************/
//LCDRC0
#define 	LCDDUTY1	BIT7					 //LCDDUTYģʽ
#define 	LCDDUTY0	BIT6
#define		LCDDUTY_1	0X00				     //LCD��̬��ʾģʽ
#define		LCDDUTY_2	LCDDUTY0				 //LCD1/2������ʾ
#define		LCDDUTY_3	LCDDUTY1				 //LCD1/3������ʾ
#define		LCDDUTY_4	LCDDUTY0 + LCDDUTY1		 //LCD1/4������ʾ

#define		LCDBIAS		BIT5					 //LCDƫѹģʽ
#define		LCDBIAS_2	LCDBIAS					 //LCD1/2ƫѹ			  	
#define		LCDBIAS_3	0X00					 //LCD1/3ƫѹ

#define		LCDFRQ1		BIT4				     //LCD��ɱ�ʱ��Ƶ��ѡ��
#define		LCDFRQ0		BIT3
#define		LCDFRQ_2K  	0X00					 //LCD��ɱ�ʱ��Ƶ��ѡ��2K
#define		LCDFRQ_4K	LCDFRQ0					 //LCD��ɱ�ʱ��Ƶ��ѡ��4K
#define		LCDFRQ_8K	LCDFRQ1					 //LCD��ɱ�ʱ��Ƶ��ѡ��8K
#define		LCDFRQ_16K	LCDFRQ0 + LCDFRQ1		 //LCD��ɱ�ʱ��Ƶ��ѡ��16K


#define 	LCDFRA1		BIT2					 //LCD֡ˢ��Ƶ��ѡ��
#define		LCDFRA0		BIT1
#define		LCDFRA_64	0X00					 //Ĭ��
#define		LCDFRA_128	LCDFRA0					 //128/4 = 32K
#define		LCDFRA_256	LCDFRA1					 //
#define		LCDFRA_512	LCDFRA0 + LCDFRA1		 //

#define 	LCDEN		BIT0					 //LCDʹ��

//LCDRC1
#define		LCDBUF1		BIT6					 //LCD��������ѡ��
#define		LCDBUF0		BIT5
#define		LCDBUF_0	0X00					 //�������Ƽ�ֵ��	
#define		LCDBUF_1	LCDBUF0					 //	 ~
#define		LCDBUF_2	LCDBUF1					 //	 ~
#define		LCDBUF_3	LCDBUF0 + LCDBUF1		 //��ǿ

#define		LCDCPEN		BIT0					 //LCD��ɱ�ʹ��
/*************************************************
UART
*************************************************/
//SCON SCON1
#define		UXSM0		BIT7					 //���ڹ���ģʽλѡ��
#define		UXSM1		BIT6
#define		UXSM_0		0X00					 //���ڹ���ģʽ0 ��λ�Ĵ���
#define     UXSM_1		UXSM1					 //���ڹ���ģʽ1 8λ���� �����ʿɵ�
#define		UXSM_2		UXSM0					 //���ڹ���ģʽ2 9λ���� CLK/32 CLK/64
#define		UXSM_3		UXSM0 + UXSM1			 //���ڹ���ģʽ3 9λ���� �����ʿɵ�

#define		UXSM2		BIT5					 //�༶ͨ�ż���ַƥ��
#define     UXREN		BIT4			    	 //��������ģʽ
#define		UXTB8		BIT3				     //ģʽ2��3�µĵ�9λ����											 		
#define		UXRB8		BIT2				 	 //ģʽ2��3�½��յĵ�9λ����

//SCON
#define		U0TI		BIT1					 //UART0 ���ͱ�־
#define		U0RI		BIT0					 //UART0 ���ձ�־

//SCON1
#define		U1TI		BIT1					 //UART1 ���ͱ�־
#define		U1RI		BIT0					 //UART1 ���ձ�־

//U0_TMR U1_TMR
#define		UXTMR		BIT0				 	 //����UART�����ʷ�����

//PCON
#define		U0BRD		BIT7				 	 //U0�����ʷ���
#define		U0FE7		BIT6				     //U0SM0����ѡ�� 1:FE(֡������)		 
#define		U1BRD		BIT3				 	 //U1�����ʷ���				
#define		U1FE7		BIT2					 //U1SM0����ѡ�� 1:FE(֡������)

//�����ʼ�����ֵ
#define		BPS9600		243

/*************************************************
TIMER
*************************************************/
//TMOD
#define 	T1GATE		BIT7	  				 //T1�ſ�
#define 	T1CT		BIT6					 //T1������ʱѡ��
												 //0��ʱ ��Ƶ1/12
												 //1���� ��P1.1��P2.1 �½��ؼ�����

#define 	T1MS1		BIT5					 //T1������ʽ
#define 	T1MS0		BIT4
#define		T1MS_0		0X00					 //��ʽ0 13λ������ʱ��
#define		T1MS_1		T1MS0					 //��ʽ1 16λ������ʱ��
#define		T1MS_2		T1MS1					 //��ʽ2 8λ�Զ���װ��
#define		T1MS_3		T1MS0 + T1MS1			 //��ʱ��1ֹͣ����

#define 	T0GATE		BIT3					 //T0�ſ�
#define 	T0CT		BIT2					 //T0������ʱѡ��
												 //0��ʱ ��Ƶ1/12
												 //1���� ��P1.1��P2.1 �½��ؼ�����

#define 	T0MS1		BIT1					 //T0������ʽ
#define 	T0MS0		BIT0
#define		T0MS_0		0X00					 //��ʽ0 13λ������ʱ��
#define		T0MS_1		T0MS0					 //��ʽ1 16λ������ʱ��
#define		T0MS_2		T0MS1					 //��ʽ2 8λ�Զ���װ��
#define		T0MS_3		T0MS0 + T0MS1			 //��ʽ3 ����8λ��ʱ������

//TCON2
#define		T3MS		BIT3					 //��ʽ0 16λ������ʱ��  ��ʽ1 8λ�Զ���װ��					 
#define		T2MS		BIT1

/*************************************************
PCA
*************************************************/
//CCON
#define		CR			BIT6					 //PCA����
#define		CCF4		BIT4					 //������4�жϱ�־
#define		CCF3		BIT3					 //������3�жϱ�־
#define		CCF2		BIT2					 //������2�жϱ�־	
#define		CCF1		BIT1					 //������1�жϱ�־
#define		CCF0		BIT0					 //������0�жϱ�־


//CMOD
#define		CWDT		BIT6					 //PCA���Ź�����ʹ��

#define		CCPS0		BIT1					 //PCAʱ������ѡ��
#define		CCPS1		BIT2					 //
#define		CCPS_0		0X00					 //PCAʱ������ ϵͳʱ��12��Ƶ	
#define		CCPS_1		CCPS0					 //PCAʱ������ ϵͳʱ��4��Ƶ
#define		CCPS_2		CCPS1					 //PCAʱ������ TIMER0���
#define		CCPS_3		CCPS0 + CCPS1			 //PCAʱ������ �ⲿ����ECI�����ϵͳʱ��8��Ƶ��
#define		EPCA		BIT0					 //PCA������ʱ�ж�ʹ��

//CCAPMX
#define		ECOM		BIT6					 //����ȽϹ��ܣ��������������WDT,PWM,����������ܣ�
#define		CAPP		BIT5					 //���������ز���
#define		CAPN		BIT4					 //�����½��ز���
#define		CAPPN		CAPP + CAPN				 //�������½��ض�����
#define		CMAT		BIT3					 //����ƥ�����λ
#define		CTOG		BIT2					 //�������ģʽ �������ŷ�ת
#define		CPWM		BIT1					 //PWMģʽ ����������ΪPWM���
#define		ECCF		BIT0					 //PCA�Ƚϲ����ж�ʹ��	

/*************************************************
I2C
*************************************************/
//I2CADR
#define 	I2CGC		BIT0					 //�Ƿ���Ӧͨ�õ��õ�ַ

//I2CSTAT

//I2CCON
#define		I2CENS		BIT6					 //I2C�ӿ�ʹ��
#define		I2CSTR		BIT5					 //��ʼ��־λ
#define		I2CSTO		BIT4					 //ֹͣ��־λ
#define		I2CSI		BIT3					 //I2C�жϱ�־
#define		I2CAA		BIT2					 //Ӧ���־λ

//I2C������
#define 	I2CCR2		BIT7
#define		I2CCR1		BIT1
#define		I2CCR0		BIT0

#define		I2CBPS_256	 0X00
#define		I2CBPS_224	 I2CCR0
#define		I2CBPS_198	 I2CCR1
#define		I2CBPS_170	 I2CCR1 + I2CCR0
#define		I2CBPS_960	 I2CCR2
#define		I2CBPS_150	 I2CCR2 + I2CCR0
#define		I2CBPS_90	 I2CCR2 + I2CCR1
#define		I2CBPS_BLK	 I2CCR2 + I2CCR1 +I2CCR0 //����timer������ֵ����BPS
//I2CTM
//I2CTMR
/*************************************************
SPI
*************************************************/
//SPICTR
#define		SPIFCLR		BIT2					 //��λ��λ��FIFO���
#define		SPIM1		BIT1					 //����ģʽ����1
#define		SPIM0		BIT0					 //����ģʽ����0
#define		SPIM_NO		0X00					 //SPI��ֹ
#define		SPIM_S		SPIM0					 //SPI����ģʽ
#define		SPIM_R		SPIM1					 //SPI����ģʽ
#define		SPIM_SR		SPIM0 + SPIM1			 //SPIȫ˫��

//SPICON
#define		SPIMASTER	BIT7					 //SPI�������ã���λΪMASTER ��λΪSLAVE	

#define		SPIFLEN2	BIT6					 //֡���ݳ��ȿ���  ֻ��MASTER����Ч
#define		SPIFLEN1	BIT5
#define		SPIFLEN0	BIT4
#define		SPIFLEN_4	SPIFLEN0 + SPIFLEN1
#define		SPIFLEN_5	SPIFLEN2
#define		SPIFLEN_6	SPIFLEN2 + SPIFLEN0
#define		SPIFLEN_7	SPIFLEN2 + SPIFLEN1
#define		SPIFLEN_8	SPIFLEN2 + SPIFLEN1 + SPIFLEN0 
												 
#define		SPICPHA1	BIT3					 //ʱ����ѡ��
#define		SPICPHA0	BIT2
#define		SPICPHA_0   0X00					 //������ ż����
#define		SPICPHA_1  	SPICPHA0				 //ż���� ������
#define		SPICPHA_2   SPICPHA1				 //������ ������
#define		SPICPHA_3	SPICPHA0 + SPICPHA1		 //ż���� ż����

#define		SPICPOL		BIT1					 //ͬ��ʱ�Ӽ���

#define		SPILSBF		BIT0					 //�ȴ�����λ 1��λ�ȴ� 0��λ�ȴ�

//SPILEN
//SPIBPS
//SPISTA1
#define		SPIRFNE		BIT3
#define		SPISFNF		BIT2
#define		SPIREND		BIT1
#define		SPISEND		BIT0

//SPISTA2
#define		SPISOV		BIT5
#define		SPIROV		BIT4
#define		SPIAERR		BIT3
#define		SPIQERR		BIT2
#define		SPITRDY		BIT1
#define		SPIRRDY		BIT0

/*************************************************
WDT
*************************************************/
//WDTRST
#define		WDTEAT		WDTRST = 0X1E;WDTRST = 0XE1	

//WDTCON
#define		WDTWOV2		BIT2
#define		WDTWOV1		BIT1
#define		WDTWOV0		BIT0		

#define		WDT_250MS	0X00
#define		WDT_500MS	WDTWOV0
#define		WDT_1S		WDTWOV1
#define		WDT_2S		WDTWOV0 + WDTWOV1
#define		WDT_4S		WDTWOV2
#define		WDT_8S		WDTWOV2	+ WDTWOV0
#define		WDT_16S		WDTWOV2 + WDTWOV1
#define		WDT_32S		WDTWOV2 + WDTWOV1 + WDTWOV0

/*************************************************
BGRC
*************************************************/
//BGRC
#define		BGREN			BIT0

/*************************************************
ADC
*************************************************/
//ADC1
#define		ADCVREF1		BIT7
#define		ADCVREF0		BIT6

#define		ADCVREF_EX		ADCVREF1			 //�ⲿ��׼
#define		ADCVREF_1P5		ADCVREF0			 //1.5V��׼
#define		ADCVREF_2P5		0X00				 //2.5V��׼

#define		ADCCH2			BIT5
#define		ADCCH1			BIT4
#define		ADCCH0			BIT3

#define		ADCCH_0			0X00				 //����ͨ��ѡ��
#define		ADCCH_1			ADCCH0
#define		ADCCH_2			ADCCH1
#define		ADCCH_3			ADCCH0 + ADCCH1
#define		ADCCH_4			ADCCH2
#define		ADCCH_5			ADCCH0 + ADCCH2
#define		ADCCH_6			ADCCH1 + ADCCH2
#define		ADCCH_TS		ADCCH0 + ADCCH1 + ADCCH2

#define		ADCCLKSEL1		BIT2				 //ʱ��ѡ�� ϵͳʱ�ӷ�Ƶ��
#define		ADCCLKSEL0		BIT1

#define		ADCCLKDIV_1		0X00
#define		ADCCLKDIV_2		ADCCLKSEL0
#define		ADCCLKDIV_4		ADCCLKSEL1
#define		ADCCLKDIV_8		ADCCLKSEL1 + ADCCLKSEL0

#define		ADCEN			BIT0				 //ADCʹ��

//ADC2
#define		ADCBUF			BIT5				 //ADC BUF ʹ��

#define		ADCMODE_C		0x00				 //����ת��ģʽ
#define		ADCMODE_S		BIT3				 //����ת��ģʽ

#define		ADCALIGN_L		0X00				 //ת��������������
#define		ADCALIGN_R		BIT2				 //ת����������Ҷ���

#define		ADCSTART		BIT0				 //����ת��

//ADC3
#define		ADCTSEN			BIT0				 //TSʹ��

	
/*************************************************
��������
*************************************************/
//SYS*********************************************
void SystemInit(void);
void Delay(unsigned int i);
void SystemTimerChange(void);
void SystemClkChange(unsigned char clk);

//CLK*********************************************
void ClkInit(void);

//LCD*********************************************
void LcdInit(void);
void LcdWhat(void);

//RTC*********************************************
void RTCInit(void);
void TestRtc(void);

//WDT*********************************************
void WdtInit(unsigned char clk,unsigned char wov);
void TestWdt(void);

//UART********************************************
void Uart0Init(unsigned char scon,unsigned char br,unsigned char brd);
void Uart1Init(unsigned char scon,unsigned char br,unsigned char brd);
void Uart0SendData(void);

//TIMER*******************************************
void Timer0Init(unsigned char tmod,unsigned char th0,unsigned char tl0);
void Timer1Init(unsigned char tmod,unsigned char th1,unsigned char tl1);
void Timer2Init(unsigned char tcon2,unsigned char th,unsigned char tl2);
void Timer3Init(unsigned char tcon2,unsigned char th3,unsigned char tl3);
void TestTimer(void);

//PCA*********************************************
void PcaTimerInit(unsigned char cmod, unsigned char ch, unsigned char cl);
void PcaCapInit(unsigned char mod);
void PcaMatInit(unsigned char ch, unsigned char cl);
void PcaHsoInit(unsigned char ch, unsigned char cl);
void PcaPwmInit(unsigned char ch, unsigned char cl);
void PcaWdtInit(unsigned char ch, unsigned char cl);
void TestPca(void);

//SPI*********************************************
void SpiInit(unsigned char con,unsigned bps);
void SpiSend(unsigned char spi_sbuf[],unsigned char len);
void SpiRecive(unsigned char spi_rbuf[],unsigned char len);
void SpiSendRecive(unsigned char spi_sbuf[],unsigned char spi_rbuf[],unsigned char len);
void TestSpi(void);

//I2C*********************************************
void I2cInit(unsigned char adr,unsigned char bps,unsigned char tm);
unsigned char I2cWrite(unsigned char e2adr,unsigned char adr);
unsigned char I2cRead(unsigned char e2adr,unsigned char adr);
void TestI2c(void);

//I2CA********************************************
void I2caInit(void);
unsigned char I2caWrite(unsigned char adr);
unsigned char I2caRead(unsigned char adr);
void TestI2ca(void);

//GPIO********************************************
void GpioDriverInit(unsigned char level,unsigned char driver);
void TestGpio(void);

//LCD*********************************************
void LCDInit(void);
void LCDClear(unsigned char *p , unsigned char j);
void LCDRefresh(void);
void LCDTSADR(void);
/*************************************************
�������� ��ϵͳ��������μ�app.h��
*************************************************/
//------------------------------------------------
extern unsigned char sys_s;						 //ϵͳ״̬
extern unsigned char sys_timer;					 //ϵͳ��ʱ���õ�timer
extern unsigned char sys_cmd[20];				 //����洢����

#define		Ssta		sys_cmd[0]				 //���ݰ���ʼ�ֽ�
#define		Smod		sys_cmd[1]				 //ָ�����
#define		Scp1		sys_cmd[2]				 //����ָ��1
#define		Scp2		sys_cmd[3]				 //����ָ��2
#define 	Slen		sys_cmd[4]				 //���ݰ���4������Ϊ���ݳ���
#define 	Sdata(x)	sys_cmd[5+x]			 //���ݰ���5����ʼΪ����

//------------------------------------------------
//����
extern unsigned char u0_ri;					     //�������
extern unsigned char u0_rt;						 //���ռ�ʱ
extern unsigned char u0_rbuf[20];				 //����ͨ�Ż���
extern unsigned char u0_err;					 //���յ�����������־
//0��û�д���
//1~N:��������

//����
#define		Tsta		u0_tbuf[0]				 //���ݰ���ʼ�ֽ�
#define		Tmod		u0_tbuf[1]				 //ָ�����
#define		Tcp1		u0_tbuf[2]				 //����ָ��1
#define		Tcp2		u0_tbuf[3]				 //����ָ��2
#define 	Tlen		u0_tbuf[4]				 //���ݰ���4������Ϊ���ݳ���
#define 	Tdata(x)	u0_tbuf[5+x]			 //���ݰ���5����ʼΪ����

extern unsigned char u0_tbuf[30];				 //����ͨ�Ż���
extern unsigned char u0_ti;					     //�������
extern unsigned char u0_ts;						 //���ͱ�־ ����1ʱ���ͻ���������
extern unsigned char u0_tf;						 //һ֡������ɱ�־ ����1ʱ���Է�����һ֡
#define		Tsen		u0_ts					 //					

extern unsigned char i;