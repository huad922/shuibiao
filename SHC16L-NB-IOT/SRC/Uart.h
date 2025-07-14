#ifndef _UART_H_
#define _UART_H_

#include "Flash.h"

#define R 0x00;
#define T 0x01;

#define uchar    unsigned char 
#define uint8    unsigned int
#define uint16_t   unsigned short
//extern uchar RX[23];
extern void Set_DCO(void);
extern void Uart_Init(void);
extern void NB_Send(void);
extern void NB_Close(uchar time);
extern void NB_Timing_Send(void);
extern void RX0_read(void);
extern void NB_Send2(void);



#endif