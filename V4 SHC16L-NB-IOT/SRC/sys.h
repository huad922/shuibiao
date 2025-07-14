#include "REG251S_user.h"
#include "4802_reg_user.h"
#define uchar unsigned char
#define uint8 unsigned int
#define uint8_t unsigned char
/*************************************************
加载要测试的IP
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
标准位定义
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
中断使能
*************************************************/
//AIE
#define		RTCE	BIT6						 //RTC中断
#define		ADCE	BIT5						 //ADC中断
#define		VCE		BIT4						 //VC中断
#define		LVD		BIT3						 //LVD中断
#define		ISOE	BIT2						 //7816中断
#define		I2CE	BIT1						 //I2C中断
#define		PTE		BIT0						 //端口中断

/*************************************************
SYS
*************************************************/
//LPM
#define 	LPMIN	LPM|=0X01;LPM|=0X02			 //进入低功耗模式

//PCON
#define		IDLE	BIT0
#define		IDLEIN	PCON |= IDLE				 //进入空闲模式

/*************************************************
CLK
*************************************************/
//CLKC
#define		LCDCLK		BIT7					 //LCD时钟选择
#define		LCDCLKX32	CLKC &= ~LCDCLK			 //外部
#define		LCDCLKIRC	CLKC |= LCDCLK			 //内部

#define		WDTCLK		BIT6					 //WDT时钟选择
#define		WDTCLKX32	CLKC &= ~WDTCLK			 //外部
#define		WDTCLKIRC	CLKC |= WDTCLK			 //内部

#define		RTCCLK		BIT5					 //RTC时钟选择
#define		RTCCLKX32	CLKC &= ~RTCCLK			 //外部
#define		RTCCLKIRC	CLKC |= RTCCLK			 //内部

#define		SYSDS1		BIT4					 //系统时钟从主频时钟分频选择1
#define 	SYSDS0		BIT3					 //系统时钟从主频时钟分频选择0
#define 	SYSDS_0		0x00					 //系统时钟为主频时钟
#define 	SYSDS_1		SYSDS0					 //系统时钟为主频时钟2分频
#define 	SYSDS_2		SYSDS1					 //系统时钟为主频时钟4分频
#define 	SYSDS_3		SYSDS0 + SYSDS1		 	 //系统时钟为主频时钟8分频

#define		X32KEN		BIT2					 //外部32K使能

#define		IRCEN		BIT1					 //内部RC使能

#define		SYSCLK		BIT0					 //系统时钟选择

//CLKC1
#define 	CLKFS1		BIT7					 //主频时钟频率选择1
#define 	CLKFS0		BIT6					 //主频时钟频率选择0
#define		CLKF_2M		0X00					 //主频时钟频率2M
#define		CLKF_4M		CLKFS0					 //主频时钟频率4M
#define		CLKF_8M		CLKFS1					 //主频时钟频率8M
#define		CLKF_16M	CLKFS0 + CLKFS1			 //主频时钟频率16M

//CLKC2
#define		X32STB		BIT7					 //外部32K稳定标志位
#define		IRCSTB		BIT6					 //内部16M稳定标志位

//PERICLK0
#define		VCCLKEN		BIT4					 //外围模块时钟允许
#define		LVDCLKEN	BIT3		
#define		BGRCLKEN	BIT2
#define		ADCCLKEN	BIT1
#define		LCDCLKEN	BIT0

//PERICLK1
#define		SPICLKEN	BIT6
#define		DESCLKEN	BIT5
#define		RNGCLKEN	BIT4					 //外围模块时钟允许
#define		CRCCLKEN	BIT3		
#define		DMACLKEN	BIT2
#define		RTCCLKEN	BIT1
#define		FLASHCLKEN	BIT0

//PERICLK2
#define		X7816CLKEN	BIT7
#define		I2CCLKEN	BIT6
#define		UART0CLKEN	BIT5
#define		UART1CLKEN	BIT4					 //外围模块时钟允许
#define		TIMERCLKEN	BIT3		
#define		PCACLKEN	BIT2
#define		WDTCLKEN	BIT1
#define		PORTCLKEN	BIT0


/*************************************************
LCD
*************************************************/
//LCDRC0
#define 	LCDDUTY1	BIT7					 //LCDDUTY模式
#define 	LCDDUTY0	BIT6
#define		LCDDUTY_1	0X00				     //LCD静态显示模式
#define		LCDDUTY_2	LCDDUTY0				 //LCD1/2段码显示
#define		LCDDUTY_3	LCDDUTY1				 //LCD1/3段码显示
#define		LCDDUTY_4	LCDDUTY0 + LCDDUTY1		 //LCD1/4段码显示

#define		LCDBIAS		BIT5					 //LCD偏压模式
#define		LCDBIAS_2	LCDBIAS					 //LCD1/2偏压			  	
#define		LCDBIAS_3	0X00					 //LCD1/3偏压

#define		LCDFRQ1		BIT4				     //LCD电荷泵时钟频率选择
#define		LCDFRQ0		BIT3
#define		LCDFRQ_2K  	0X00					 //LCD电荷泵时钟频率选择2K
#define		LCDFRQ_4K	LCDFRQ0					 //LCD电荷泵时钟频率选择4K
#define		LCDFRQ_8K	LCDFRQ1					 //LCD电荷泵时钟频率选择8K
#define		LCDFRQ_16K	LCDFRQ0 + LCDFRQ1		 //LCD电荷泵时钟频率选择16K


#define 	LCDFRA1		BIT2					 //LCD帧刷新频率选择
#define		LCDFRA0		BIT1
#define		LCDFRA_64	0X00					 //默认
#define		LCDFRA_128	LCDFRA0					 //128/4 = 32K
#define		LCDFRA_256	LCDFRA1					 //
#define		LCDFRA_512	LCDFRA0 + LCDFRA1		 //

#define 	LCDEN		BIT0					 //LCD使能

//LCDRC1
#define		LCDBUF1		BIT6					 //LCD驱动能力选择
#define		LCDBUF0		BIT5
#define		LCDBUF_0	0X00					 //最弱（推荐值）	
#define		LCDBUF_1	LCDBUF0					 //	 ~
#define		LCDBUF_2	LCDBUF1					 //	 ~
#define		LCDBUF_3	LCDBUF0 + LCDBUF1		 //最强

#define		LCDCPEN		BIT0					 //LCD电荷泵使能
/*************************************************
UART
*************************************************/
//SCON SCON1
#define		UXSM0		BIT7					 //串口工作模式位选择
#define		UXSM1		BIT6
#define		UXSM_0		0X00					 //串口工作模式0 移位寄存器
#define     UXSM_1		UXSM1					 //串口工作模式1 8位传输 波特率可调
#define		UXSM_2		UXSM0					 //串口工作模式2 9位传输 CLK/32 CLK/64
#define		UXSM_3		UXSM0 + UXSM1			 //串口工作模式3 9位传输 波特率可调

#define		UXSM2		BIT5					 //多级通信及地址匹配
#define     UXREN		BIT4			    	 //启动接收模式
#define		UXTB8		BIT3				     //模式2或3下的第9位数据											 		
#define		UXRB8		BIT2				 	 //模式2或3下接收的第9位数据

//SCON
#define		U0TI		BIT1					 //UART0 发送标志
#define		U0RI		BIT0					 //UART0 接收标志

//SCON1
#define		U1TI		BIT1					 //UART1 发送标志
#define		U1RI		BIT0					 //UART1 接收标志

//U0_TMR U1_TMR
#define		UXTMR		BIT0				 	 //启动UART波特率发生器

//PCON
#define		U0BRD		BIT7				 	 //U0波特率翻倍
#define		U0FE7		BIT6				     //U0SM0功能选择 1:FE(帧错误检测)		 
#define		U1BRD		BIT3				 	 //U1波特率翻倍				
#define		U1FE7		BIT2					 //U1SM0功能选择 1:FE(帧错误检测)

//波特率计数初值
#define		BPS9600		243

/*************************************************
TIMER
*************************************************/
//TMOD
#define 	T1GATE		BIT7	  				 //T1门控
#define 	T1CT		BIT6					 //T1计数定时选择
												 //0定时 主频1/12
												 //1计数 （P1.1或P2.1 下降沿计数）

#define 	T1MS1		BIT5					 //T1工作方式
#define 	T1MS0		BIT4
#define		T1MS_0		0X00					 //方式0 13位计数定时器
#define		T1MS_1		T1MS0					 //方式1 16位计数定时器
#define		T1MS_2		T1MS1					 //方式2 8位自动重装载
#define		T1MS_3		T1MS0 + T1MS1			 //定时器1停止运行

#define 	T0GATE		BIT3					 //T0门控
#define 	T0CT		BIT2					 //T0计数定时选择
												 //0定时 主频1/12
												 //1计数 （P1.1或P2.1 下降沿计数）

#define 	T0MS1		BIT1					 //T0工作方式
#define 	T0MS0		BIT0
#define		T0MS_0		0X00					 //方式0 13位计数定时器
#define		T0MS_1		T0MS0					 //方式1 16位计数定时器
#define		T0MS_2		T0MS1					 //方式2 8位自动重装载
#define		T0MS_3		T0MS0 + T0MS1			 //方式3 两个8位定时计数器

//TCON2
#define		T3MS		BIT3					 //方式0 16位计数定时器  方式1 8位自动重装载					 
#define		T2MS		BIT1

/*************************************************
PCA
*************************************************/
//CCON
#define		CR			BIT6					 //PCA启动
#define		CCF4		BIT4					 //捕获器4中断标志
#define		CCF3		BIT3					 //捕获器3中断标志
#define		CCF2		BIT2					 //捕获器2中断标志	
#define		CCF1		BIT1					 //捕获器1中断标志
#define		CCF0		BIT0					 //捕获器0中断标志


//CMOD
#define		CWDT		BIT6					 //PCA看门狗功能使能

#define		CCPS0		BIT1					 //PCA时钟输入选择
#define		CCPS1		BIT2					 //
#define		CCPS_0		0X00					 //PCA时钟输入 系统时钟12分频	
#define		CCPS_1		CCPS0					 //PCA时钟输入 系统时钟4分频
#define		CCPS_2		CCPS1					 //PCA时钟输入 TIMER0溢出
#define		CCPS_3		CCPS0 + CCPS1			 //PCA时钟输入 外部引脚ECI（最高系统时钟8分频）
#define		EPCA		BIT0					 //PCA计数定时中断使能

//CCAPMX
#define		ECOM		BIT6					 //允许比较功能（包括软件计数，WDT,PWM,高速输出功能）
#define		CAPP		BIT5					 //允许上升沿捕获
#define		CAPN		BIT4					 //允许下降沿捕获
#define		CAPPN		CAPP + CAPN				 //上升沿下降沿都捕获
#define		CMAT		BIT3					 //允许匹配控制位
#define		CTOG		BIT2					 //高速输出模式 允许引脚翻转
#define		CPWM		BIT1					 //PWM模式 允许引脚作为PWM输出
#define		ECCF		BIT0					 //PCA比较捕获中断使能	

/*************************************************
I2C
*************************************************/
//I2CADR
#define 	I2CGC		BIT0					 //是否响应通用调用地址

//I2CSTAT

//I2CCON
#define		I2CENS		BIT6					 //I2C接口使能
#define		I2CSTR		BIT5					 //起始标志位
#define		I2CSTO		BIT4					 //停止标志位
#define		I2CSI		BIT3					 //I2C中断标志
#define		I2CAA		BIT2					 //应答标志位

//I2C波特率
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
#define		I2CBPS_BLK	 I2CCR2 + I2CCR1 +I2CCR0 //根据timer计数初值决定BPS
//I2CTM
//I2CTMR
/*************************************************
SPI
*************************************************/
//SPICTR
#define		SPIFCLR		BIT2					 //置位此位将FIFO清空
#define		SPIM1		BIT1					 //工作模式控制1
#define		SPIM0		BIT0					 //工作模式控制0
#define		SPIM_NO		0X00					 //SPI禁止
#define		SPIM_S		SPIM0					 //SPI发送模式
#define		SPIM_R		SPIM1					 //SPI接收模式
#define		SPIM_SR		SPIM0 + SPIM1			 //SPI全双工

//SPICON
#define		SPIMASTER	BIT7					 //SPI主从设置，置位为MASTER 复位为SLAVE	

#define		SPIFLEN2	BIT6					 //帧数据长度控制  只在MASTER下有效
#define		SPIFLEN1	BIT5
#define		SPIFLEN0	BIT4
#define		SPIFLEN_4	SPIFLEN0 + SPIFLEN1
#define		SPIFLEN_5	SPIFLEN2
#define		SPIFLEN_6	SPIFLEN2 + SPIFLEN0
#define		SPIFLEN_7	SPIFLEN2 + SPIFLEN1
#define		SPIFLEN_8	SPIFLEN2 + SPIFLEN1 + SPIFLEN0 
												 
#define		SPICPHA1	BIT3					 //时钟沿选择
#define		SPICPHA0	BIT2
#define		SPICPHA_0   0X00					 //奇数收 偶数发
#define		SPICPHA_1  	SPICPHA0				 //偶数收 奇数发
#define		SPICPHA_2   SPICPHA1				 //奇数收 奇数发
#define		SPICPHA_3	SPICPHA0 + SPICPHA1		 //偶数收 偶数发

#define		SPICPOL		BIT1					 //同步时钟极性

#define		SPILSBF		BIT0					 //先传控制位 1低位先传 0高位先传

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

#define		ADCVREF_EX		ADCVREF1			 //外部基准
#define		ADCVREF_1P5		ADCVREF0			 //1.5V基准
#define		ADCVREF_2P5		0X00				 //2.5V基准

#define		ADCCH2			BIT5
#define		ADCCH1			BIT4
#define		ADCCH0			BIT3

#define		ADCCH_0			0X00				 //采样通道选择
#define		ADCCH_1			ADCCH0
#define		ADCCH_2			ADCCH1
#define		ADCCH_3			ADCCH0 + ADCCH1
#define		ADCCH_4			ADCCH2
#define		ADCCH_5			ADCCH0 + ADCCH2
#define		ADCCH_6			ADCCH1 + ADCCH2
#define		ADCCH_TS		ADCCH0 + ADCCH1 + ADCCH2

#define		ADCCLKSEL1		BIT2				 //时钟选择 系统时钟分频数
#define		ADCCLKSEL0		BIT1

#define		ADCCLKDIV_1		0X00
#define		ADCCLKDIV_2		ADCCLKSEL0
#define		ADCCLKDIV_4		ADCCLKSEL1
#define		ADCCLKDIV_8		ADCCLKSEL1 + ADCCLKSEL0

#define		ADCEN			BIT0				 //ADC使能

//ADC2
#define		ADCBUF			BIT5				 //ADC BUF 使能

#define		ADCMODE_C		0x00				 //连续转换模式
#define		ADCMODE_S		BIT3				 //单次转换模式

#define		ADCALIGN_L		0X00				 //转换结果数据左对齐
#define		ADCALIGN_R		BIT2				 //转换结果数据右对齐

#define		ADCSTART		BIT0				 //启动转换

//ADC3
#define		ADCTSEN			BIT0				 //TS使能

	
/*************************************************
函数声明
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
变量声明 （系统变量定义参见app.h）
*************************************************/
//------------------------------------------------
extern unsigned char sys_s;						 //系统状态
extern unsigned char sys_timer;					 //系统计时所用的timer
extern unsigned char sys_cmd[20];				 //命令存储数组

#define		Ssta		sys_cmd[0]				 //数据包起始字节
#define		Smod		sys_cmd[1]				 //指令对象
#define		Scp1		sys_cmd[2]				 //操作指令1
#define		Scp2		sys_cmd[3]				 //操作指令2
#define 	Slen		sys_cmd[4]				 //数据包第4个数据为数据长度
#define 	Sdata(x)	sys_cmd[5+x]			 //数据包第5个开始为数据

//------------------------------------------------
//接收
extern unsigned char u0_ri;					     //缓存计数
extern unsigned char u0_rt;						 //接收计时
extern unsigned char u0_rbuf[20];				 //串行通信缓存
extern unsigned char u0_err;					 //接收到的命令错误标志
//0：没有错误
//1~N:命令有误

//发送
#define		Tsta		u0_tbuf[0]				 //数据包起始字节
#define		Tmod		u0_tbuf[1]				 //指令对象
#define		Tcp1		u0_tbuf[2]				 //操作指令1
#define		Tcp2		u0_tbuf[3]				 //操作指令2
#define 	Tlen		u0_tbuf[4]				 //数据包第4个数据为数据长度
#define 	Tdata(x)	u0_tbuf[5+x]			 //数据包第5个开始为数据

extern unsigned char u0_tbuf[30];				 //串行通信缓存
extern unsigned char u0_ti;					     //缓存计数
extern unsigned char u0_ts;						 //发送标志 等于1时发送缓存中数据
extern unsigned char u0_tf;						 //一帧发送完成标志 等于1时可以发送下一帧
#define		Tsen		u0_ts					 //					

extern unsigned char i;