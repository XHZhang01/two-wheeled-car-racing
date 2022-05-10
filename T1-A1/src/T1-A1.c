/* EGR */

#include <hw_types.h>

int main() {

    /* GPIO for Port 1 Pin 2: Reset all bits and set 0b111 (0x7) */
	HWREG(0x44e10000 + 0x8b8) &=~ ((1<<0)|(1<<1)|(1<<2));
	HWREG(0x44e10000 + 0x8b8) |= 0x7;

	/* Enable output for LED */
	HWREG(0x481ac000 + 0x134) &=~ (1 << 12);

	/* Dataout as 0V */
	HWREG(0x481ac000 + 0x13c) &=~ (1 << 12);

	while (1)
	{
		/* Place main loop code here */
	}
	return 0;
}
