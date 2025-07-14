/*--------------------------------------------------------------------------
REG251S.H

Header file for 8xC251SA/SB/SQ/SP
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __REG251S_H__
#define __REG251S_H__

/*  BYTE Registers  */
sfr P0          = 0x80;
sfr SP          = 0x81;
sfr DPL         = 0x82;
sfr DPH         = 0x83;
sfr DPXL        = 0x84;
sfr LockSFR     = 0x85;
sfr PCON        = 0x87;

sfr TCON        = 0x88;
sfr TMOD        = 0x89;
sfr TL0         = 0x8A;
sfr TL1         = 0x8B;
sfr TH0         = 0x8C;
sfr TH1         = 0x8D;
sfr CCMCON      = 0x8E;
sfr CCMVAL      = 0x8F;

sfr P1          = 0x90;
sfr Flash_CTL   = 0x91;
sfr CLKC        = 0x92;
sfr CLKC1       = 0x93;
sfr CLKC2       = 0x94;
sfr LPM         = 0x95;
sfr MMCON       = 0x97;

sfr SCON        = 0x98;
sfr SBUF        = 0x99;
sfr BGRC        = 0x9A;
sfr ADC1        = 0x9B;
sfr ADC2        = 0x9C;
sfr ADC3        = 0x9D;
sfr ADCH        = 0x9E;
sfr ADCL        = 0x9F;

sfr P2          = 0xA0;
sfr MPAGE       = 0xA1;
sfr Buzz_CTL    = 0xA2;
sfr Buzz_CNT    = 0xA3;
sfr Reset_flag  = 0xA4;
sfr WDTCON      = 0xA5;
sfr WDTRST      = 0xA6;
sfr Boot_Info   = 0xA7;

sfr IE0         = 0xA8;
sfr SADDR       = 0xA9;
sfr SCON1       = 0xAA;
sfr SBUF1       = 0xAB;
sfr P0_DIR      = 0xAC;
sfr P1_DIR      = 0xAD;
sfr P2_DIR      = 0xAE;
sfr P3_DIR      = 0xAF;

sfr P3          = 0xB0;
sfr Flash_PL    = 0xB1; 
sfr PERI_CLK0   = 0xB3;
sfr PERI_CLK1   = 0xB4;
sfr PERI_CLK2   = 0xB5;
sfr LVDC1       = 0xB6;
sfr IPH0        = 0xB7;

sfr IPL0        = 0xB8;
sfr SADEN       = 0xB9;
sfr SADDR1      = 0xBA;
sfr SADEN1      = 0xBB;
sfr VC1         = 0xBC;
sfr VC2         = 0xBD;
sfr SPH         = 0xBE;
sfr LVDC2       = 0xBF;

sfr AIF         = 0xC0;
sfr TCON2       = 0xC3;
sfr TL2         = 0xC4;
sfr TH2         = 0xC5;
sfr TL3         = 0xC6;
sfr TH3         = 0xC7;

sfr U0_TMR      = 0xC8;
sfr U0_TM       = 0xC9;
sfr U1_TMR      = 0xCA;
sfr U1_TM       = 0xCB;
sfr VC3         = 0xCC;
sfr X32K_CTL    = 0xCF;

sfr PSW         = 0xD0;
sfr PSW1        = 0xD1;
sfr I2C_RUN     = 0xD2;
sfr I2C_TM      = 0xD3;
sfr	I2CCON	    = 0xD4;
sfr	I2CDAT		= 0xD5;
sfr	I2CADR		= 0xD6;
sfr I2CSTA      = 0xD7;

sfr CCON        = 0xD8;
sfr CMOD        = 0xD9;
sfr CCAPM0      = 0xDA;
sfr CCAPM1      = 0xDB;
sfr CCAPM2      = 0xDC;
sfr CCAPM3      = 0xDD;
sfr CCAPM4      = 0xDE;
sfr CCAPO       = 0xDF;

sfr ACC         = 0xE0;
sfr P4          = 0xE2;
sfr P5          = 0xE3;
sfr P6          = 0xE4;
sfr P7          = 0xE5;
sfr P8          = 0xE6;

sfr AIE         = 0xE8;
sfr CL          = 0xE9;
sfr CCAP0L      = 0xEA;
sfr CCAP1L      = 0xEB;
sfr CCAP2L      = 0xEC;
sfr CCAP3L      = 0xED;
sfr CCAP4L      = 0xEE;

sfr B           = 0xF0;
sfr P4_DIR      = 0xF2;
sfr P5_DIR      = 0xF3;
sfr P6_DIR      = 0xF4;
sfr P7_DIR      = 0xF5;
sfr P8_DIR      = 0xF6;
sfr AIPH        = 0xF7;

sfr AIPL        = 0xF8;
sfr CH          = 0xF9;
sfr CCAP0H      = 0xFA;
sfr CCAP1H      = 0xFB;
sfr CCAP2H      = 0xFC;
sfr CCAP3H      = 0xFD;
sfr CCAP4H      = 0xFE;

/*  BIT Registers  */

/*  TCON  */
sbit TR1    = TCON^6;
sbit TR0    = TCON^4;
sbit IE1_   = TCON^3;
sbit IT1    = TCON^2;
sbit IE0_   = TCON^1;
sbit IT0    = TCON^0;

/*  TCON2 */
sbit TM3_OVF= TCON2^7;
sbit TM2_OVF= TCON2^6;
sbit TM1_OVF= TCON2^5;
sbit TM0_OVF= TCON2^4;
sbit TMM3   = TCON2^3;
sbit TR3    = TCON2^2;
sbit TMM2   = TCON2^1;
sbit TR2    = TCON2^0;

/*  IE0   */
sbit EA     = IE0^7;
sbit EC     = IE0^6;
sbit ET2    = IE0^5;
sbit ES     = IE0^4;
sbit ET1    = IE0^3;
sbit EX1    = IE0^2;
sbit ET0    = IE0^1;
sbit EX0    = IE0^0;

/*  SCON  */
sbit FE     = SCON^7;
sbit SM0    = SCON^7;
sbit SM1    = SCON^6;
sbit SM2    = SCON^5;
sbit REN    = SCON^4;
sbit TB8    = SCON^3;
sbit RB8    = SCON^2;
sbit TI     = SCON^1;
sbit RI     = SCON^0;

/*  AIF  */
sbit AIF6   = AIF^6;
sbit AIF5   = AIF^5;
sbit AIF4   = AIF^4;
sbit AIF3   = AIF^3;
sbit AIF2   = AIF^2;
sbit AIF1   = AIF^1;
sbit AIF0   = AIF^0;

/*  CCON  */
sbit CF     = CCON^7;
sbit CR     = CCON^6;
sbit CCF4   = CCON^4;
sbit CCF3   = CCON^3;
sbit CCF2   = CCON^2;
sbit CCF1   = CCON^1;
sbit CCF0   = CCON^0;

/*  AIE  */
sbit AIE6   = AIE^6;
sbit AIE5   = AIE^5;
sbit AIE4   = AIE^4;
sbit AIE3   = AIE^3;
sbit AIE2   = AIE^2;
sbit AIE1   = AIE^1;
sbit AIE0   = AIE^0;

/*  PSW  */ 
sbit CY   = PSW^7;
sbit AC   = PSW^6;
sbit F0   = PSW^5;
sbit RS1  = PSW^4;
sbit RS0  = PSW^3;
sbit OV   = PSW^2;
sbit UD   = PSW^1;
sbit P    = PSW^0;

#endif