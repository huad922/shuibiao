#ifndef _Flash_H_
#define _Flash_H_

#include "sys.h"
extern uchar g_write_value[48];
extern uchar C_DATA[150];
extern uchar meter_data[360]; 
extern void Write_SegC(void);
extern void Read_SegC(void);
extern void Flash_Read_Write(void);
//extern void Delay(unsigned int i);
extern unsigned long consumed_water; 

extern unsigned short mem_date;
extern unsigned char date;
extern unsigned char CDMA_time;//开机等待时间
extern unsigned char  CardKey; 
extern unsigned char keytyp;
extern unsigned char  FMflag; 
extern unsigned char  showIP;
extern unsigned char  showdata[4]; 
extern uchar z;    //串口1接收计数 
extern unsigned char  RX0_flag;
extern unsigned char adc_flag;
extern unsigned char flagtype;

extern unsigned char  returntime;
extern unsigned char  FDtime;

extern unsigned char pul_flag;
extern unsigned char FmForceFlag;
extern unsigned char FmOrder;
extern unsigned char FDcycflag;
extern unsigned char FMflag;

extern void GetTime(void);
extern unsigned char time_Flag;
extern unsigned char count_time;
extern unsigned char doubletime;
extern unsigned char Nodoubletime;
extern unsigned char key_time;


#endif