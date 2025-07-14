#include "Flash.h"
#include "Calculate.h"
//#include "LCD.h"
//===============================================
//宏定义
//===============================================
#define RNGTESTTIMES           (5)
#define RNGCTRLPWRON           (0x01)
#define RNGCTRLRUN             (0x02)

#define RNGMODECNTOFFSERT      (2)
#define RNGMODEFDBKOFFSERT     (1)
#define RNGMODELOADOFFSERT     (0)
#define RNGMODECNT0            (0)
#define RNGMODECNT8            (1)
#define RNGMODECNT16           (2)
#define RNGMODECNT32           (3)
#define RNGMODECNT64           (4)
#define RNGMODECNT128          (5)
#define RNGMODECNT256          (6)
#define RNGMODEXORON           (1)
#define RNGMODEXOROFF          (0)
#define RNGMODELOADNEW     	   (1)
#define RNGMODELOADOLD     	   (0)
/*******************************************************************************
* 函  数  名      : InitData
* 描      述      : 数据初始化
* 输      入      : 无.
* 返      回      : 无.
*******************************************************************************/
void InitData(void)    
{
  consumed_water=(unsigned long)g_write_value[9]*65536+(unsigned long)g_write_value[8]*256+(unsigned long)g_write_value[7];
  showIP=0;
}

/*******************************************************************************
* 函  数  名      : calculate
* 描      述      : 数据计算，后显示
* 输      入      : 无
* 返      回      : 无.
*******************************************************************************/
void calculate(void)
{
	
 if(pul_flag==1)
    {
      pul_flag=0;                                                
      consumed_water++; 
      g_write_value[9]=(uint8_t)(consumed_water/65536);
      g_write_value[8]=(uint8_t)(consumed_water/256%256);
      g_write_value[7]=(uint8_t)(consumed_water%256);
      showIP=0;
    }
}
/*******************************************************************************
* 函  数  名      : RNG_Time
* 描      述      : 产生随机时间
* 输      入      : 无
* 返      回      : 无.
设置的上报时间后两个小时内随机
*******************************************************************************/
void RNG_Time(void)
{
unsigned char tmpReg;
unsigned char rngdata;
unsigned char time_temp,time_hour,time_min;
	time_min=(g_write_value[36]/16)*10+g_write_value[36]%16;
	time_hour=(g_write_value[35]/16)*10+g_write_value[35]%16;
	 //1. Enable the RNG power
    tmpReg = RNGCtrlReg;
    RNGCtrlReg = tmpReg | RNGCTRLPWRON;
    //2. Set the mode
    RNGModeReg = (RNGMODECNT0 << RNGMODECNTOFFSERT)     // 
	           | (RNGMODEXORON << RNGMODEFDBKOFFSERT) 	//
			   | (RNGMODELOADNEW << RNGMODELOADOFFSERT);
    tmpReg = RNGCtrlReg;
    //3. Generate the RNG data
    RNGCtrlReg = tmpReg | RNGCTRLRUN;
    //4. Read the RNG data
    while(0 != (RNGCtrlReg & RNGCTRLRUN))
    {
    }
    rngdata = RNGData0Reg3;
    /*rngdata[2] = RNGData0Reg2;
    rngdata[3] = RNGData0Reg3;
    rngdata[4] = RNGData1Reg0;
    rngdata[5] = RNGData1Reg1;
    rngdata[6] = RNGData1Reg2;
    rngdata[7] = RNGData1Reg3;*/
    //5. Disable the RNG
    RNGCtrlReg = 0x00;
	time_temp=(rngdata*15)/32;
	time_min=time_min+time_temp;
	time_min=time_temp%60;
	time_hour=time_hour+time_temp/60;
	if(time_hour>23)time_hour=time_hour-24;;
	g_write_value[36]=(time_min/10)*16+time_min%10;
	g_write_value[35]=(time_hour/10)*16+time_hour%10;

}