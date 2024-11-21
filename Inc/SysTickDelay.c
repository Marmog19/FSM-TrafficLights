/*
 * SysTickDelay.c
 *
 */

#include "SysTickDelay.h"

void SysTick_Init(void) {
	STK_CTRL = 0;          // 0. Turn off SysTick during initialization
	STK_LOAD = 0x00FFFFFF; // 1. Program reload value (max value)
	STK_VAL = 0;           // 2. Clear current value
	STK_CTRL = 0x00000005; // 3. Enable SysTick (bit 1) with core clock (bit 2)
}

void SysTick_Delay(unsigned long d) {
	STK_LOAD = d-1;	// number of counts to wait
	// any value clears the current value to 0
	// and also clears the COUNTFLAG bit in the STK_CTRL register to 0
	STK_VAL = 0;
	while (!(STK_CTRL & (1 << 16))) {} // wait for COUNTFLAG
}

void SysTick_Delay10ms(unsigned long d) {
	unsigned long i;
	for(i=0; i<d; i++){
		// To find the right value (X) to get 10ms we use
		// the Clock frequency (from the variable SystemCoreClock=SCC)
		// and the following equation:
		// X*(1/SCC)s = 10ms => X = SCC*(10*10^-3) = SCC / 100
	    SysTick_Delay(SystemCoreClock / 100);
	  }
}
