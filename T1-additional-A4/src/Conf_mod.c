// Diese Datei wird nur verlinkt. D.h. ihr editiert ueber alle Projekte hinweg die selbe (diese) Datei.

/*
 * Control_Module.c
 *
 *  Created on: 12.10.2014
 *      Author: Andi
 */

#include "Conf_mod.h"
#include <hw_types.h>


void PinMuxing(unsigned int OffsetAddr,
        	   unsigned int Pull_EnableDisable,
        	   unsigned int PullDirection,
			   unsigned int MuxMode)
{
	if (MuxMode > 0x7)
		MuxMode = 7;

    // Pinmuxing
	HWREG(0x44e10000 + OffsetAddr) &=~ (0x7); //l�schen des vorherigen Modes
	HWREG(0x44e10000 + OffsetAddr) |= MuxMode;	//setzen des neuen Modes

	if (Pull_EnableDisable)
		HWREG(0x44e10000 + OffsetAddr) |=  (1<< 3); // Disable Pull-Up-Down
	else
		HWREG(0x44e10000 + OffsetAddr) &=~ (1<< 3); // Enable Pull-Up-Down

	if (PullDirection)
		HWREG(0x44e10000 + OffsetAddr) |=  (1<< 4); // Set Pull-Up
	else
		HWREG(0x44e10000 + OffsetAddr) &=~ (1<< 4); // Set Pull-Down
}
