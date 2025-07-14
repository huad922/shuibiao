#ifndef _RTC_H_
#define _RTC_H_

#include "sys.h"

extern unsigned char CDMA_time;//开机等待时间
extern unsigned char CDMA_Wait;//数据接收等待时间
extern void RTCInit(void);
extern void RTCSet(void);

#endif