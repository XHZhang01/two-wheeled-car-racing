
/*
 * Beispiel EGR
 *
 *  Created on: 08.09.2014
 *      Author: Coy, Pfeiffer
 */

#include "delay_ms.h"
#include <hw_types.h> //einbinden des HWREG Makros
#include <uartStdio.h>
//#define HWREG(x)     (*((volatile unsigned int *)(x)))

int main() {
	UARTprintf("   Hello World! Welcome to EGR Praktikum! \r\n   Sizeof(int): %d",sizeof(int));
	//Vorbereiten der pins
	HWREG(0x44e10000+0x854) &=~ (0x7); //l�schen des vorherigen Modes
	HWREG(0x44e10000+0x854) |= 0x7;	//setzen des neuen Modes

	HWREG(0x44e10000+0x858) &=~ (0x7); //l�schen des vorherigen Modes
	HWREG(0x44e10000+0x858) |= 0x7;	//setzen des neuen Modes

	HWREG(0x44e10000+0x85C) &=~ (0x7); //l�schen des vorherigen Modes
	HWREG(0x44e10000+0x85C) |= 0x7;	//setzen des neuen Modes

	HWREG(0x44e10000+0x860) &=~ (0x7); //l�schen des vorherigen Modes
	HWREG(0x44e10000+0x860) |= 0x7;	//setzen des neuen Modes

	//LED als output
	HWREG(0x4804C000 + 0x134) &= ~(1 << 21);
	HWREG(0x4804C000 + 0x134) &= ~(1 << 22);
	HWREG(0x4804C000 + 0x134) &= ~(1 << 23);
	HWREG(0x4804C000 + 0x134) &= ~(1 << 24);
	//LED an
	HWREG(0x4804C000 + 0x13C) &= ~(1 << 21);
	HWREG(0x4804C000 + 0x13C) &= ~(1 << 22);
	HWREG(0x4804C000 + 0x13C) &= ~(1 << 23);
	HWREG(0x4804C000 + 0x13C) &= ~(1 << 24);


	//unsigned int time =0;
	while (1)
	{

		//LED an
		HWREG(0x4804C000 + 0x13C) &= ~(1 << 21);
		HWREG(0x4804C000 + 0x13C) &= ~(1 << 22);
		HWREG(0x4804C000 + 0x13C) &= ~(1 << 23);
		HWREG(0x4804C000 + 0x13C) &= ~(1 << 24);

		delay_ms(200);

		//LED aus
		HWREG(0x4804C000 + 0x13C) |= (1 << 21);
		HWREG(0x4804C000 + 0x13C) |= (1 << 22);
		HWREG(0x4804C000 + 0x13C) |= (1 << 23);
		HWREG(0x4804C000 + 0x13C) |= (1 << 24);

		delay_ms(200);

	}
	return 0;
}
