/* EGR */

#include <hw_types.h>

int main() {

    /* GPIO for Port 1 Pin 2: Reset all bits and set 0b111 (0x7) */
	HWREG(0x44e10000 + 0x8b8) &=~ ((1<<0)|(1<<1)|(1<<2));
	HWREG(0x44e10000 + 0x8b8) |= 0x7;

    /* GPIO for Port 1 Pin 4: Reset all bits and set 0b111 (0x7) */
	HWREG(0x44e10000 + 0x8b0) &=~ ((1<<0)|(1<<1)|(1<<2));
	HWREG(0x44e10000 + 0x8b0) |= 0x7;

	/* Enable input for Pin 2 */
	HWREG(0x481ac000 + 0x134) |= (1 << 12);

	/* Enable input for Pin 4 */
	HWREG(0x481ac000 + 0x134) |= (1 << 10);

    /* GPIO for Port 2 Pin 2: Reset all bits and set 0b111 (0x7) */
	HWREG(0x44e10000 + 0x8d8) &=~ ((1<<0)|(1<<1)|(1<<2));
	HWREG(0x44e10000 + 0x8d8) |= 0x7;

    /* GPIO for Port 2 Pin 4: Reset all bits and set 0b111 (0x7) */
	HWREG(0x44e10000 + 0x8d4) &=~ ((1<<0)|(1<<1)|(1<<2));
	HWREG(0x44e10000 + 0x8d4) |= 0x7;

	/* Enable output for Pin 2 */
	HWREG(0x44e07000 + 0x134) &=~ (1 << 10);

	/* Enable output for Pin 4 */
	HWREG(0x44e07000 + 0x134) &=~ (1 << 9);

	/* Set pullups for Switch 1*/
	HWREG(0x44e10000 + 0x8b8) &=~ (1 << 3);
	HWREG(0x44e10000 + 0x8b8) |= (1 << 4);

	/* Set pullups for Switch 2*/
	HWREG(0x44e10000 + 0x8b0) &=~ (1 << 3);
	HWREG(0x44e10000 + 0x8b0) |= (1 << 4);

	while (1)
	{
		/* Set value of Switch as Dataout for Pin 2 and Pin 4*/
		if ((HWREG(0x481ac000 + 0x138) & (1 << 12)) == (1 << 12))
		{
			HWREG(0x44e07000 + 0x13c) |= (1 << 10);

		}
		else
		{
			HWREG(0x44e07000 + 0x13c) &=~ (1 << 10);
		}

		if ((HWREG(0x481ac000 + 0x138) & (1 << 10)) == (1 << 10))
		{
			HWREG(0x44e07000 + 0x13c) |= (1 << 9);
		}
		else
		{
			HWREG(0x44e07000 + 0x13c) &=~ (1 << 9);
		}
	}

	return 0;
}
