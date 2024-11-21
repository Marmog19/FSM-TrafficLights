/*
 * SysTickDelay.h
 *
 */
#ifndef SYSTICKDELAY_H_
#define SYSTICKDELAY_H_

#include <stm32f4xx.h>

// defines addresses for SysTick
#define STK_CTRL      (*((volatile unsigned long *)0xE000E010))
#define STK_LOAD    (*((volatile unsigned long *)0xE000E014))
#define STK_VAL   (*((volatile unsigned long *)0xE000E018))


// initializes SysTick
void SysTick_Init(void);

// delays with the SysTick count
void SysTick_Delay(unsigned long);

// wait 10ms
void SysTick_Delay10ms(unsigned long);

#endif /* SYSTICKDELAY_H_ */
