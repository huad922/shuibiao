#ifndef CALCULATE_H
#define CALCULATE_H

extern void calculate(void);
/*#define FOflag (P1&BIT4) 
#define FCflag (P1&BIT3) 
#define FOflagH 0x20
#define FCflagH 0x10
#define FOpen  P1 |=BIT1; P1 &=~BIT0  
#define FClose P1 &=~BIT1; P1 |=BIT0  
#define FStop  P1 &=~(BIT1+BIT0) 
extern void FCyc(void);
extern void FCtrol(unsigned char order);
*/
extern void InitData(void);
extern void RNG_Time(void);

#endif