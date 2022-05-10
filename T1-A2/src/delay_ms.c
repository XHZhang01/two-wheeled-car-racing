/*
 * delay_ms.c
 *
 *  Created on: 23.09.2015
 *      Author: egr
 */
#include "delay_ms.h"

void delay_ms(unsigned int ms)
{
	volatile unsigned int cycles= ms*2450;	// Von Hand kalibriert

	while(cycles--)
			asm("nop");

}

void delay_us(unsigned int us) {
        volatile unsigned int cycles = us * 3;  // Von Hand kalibriert

        while (cycles--)
                asm("nop");

}
