#ifndef CALCULATE_H
#define CALCULATE_H

extern void calculate(void);
extern void InitData(void);
extern void RNG_Time(void);
#define FOflag (P1&BIT3) 
#define FCflag (P1&BIT4) 
#define FOflagH BIT3
#define FCflagH BIT4
#define FClose  P1 |=BIT1; P1 &=~BIT2  
#define FOpen P1 &=~BIT1; P1 |=BIT2  
#define FStop  P1 &=~(BIT1+BIT2) 
extern void FCyc(void);
extern void FCtrol(unsigned char order);

#endif