// Diese Datei wird nur verlinkt. D.h. ihr editiert ueber alle Projekte hinweg die selbe (diese) Datei.

/*
 * Control_Module.h
 *
 *  Created on: 12.10.2014
 *      Author: Andi
 */

#ifndef CONTROL_MODULE_H_
#define CONTROL_MODULE_H_

// Basis Adresse des Control Module
#define		BASE_ADDR_CONTROL   0x44E10000

// Pull Enable/Disable und Up/Down
#define 	PULL_ENABLE 	0
#define 	PULL_DISABLE	1
#define 	PULL_DOWN		0
#define 	PULL_UP			1

#define		GPIO_MODE		7

// Pinmux Funktion
extern void PinMuxing(unsigned int OffsetAddr,
        		   	  unsigned int Pull_EnableDisable,
        		      unsigned int PullDirection,
					  unsigned int MuxMode);

#endif /* CONTROL_MODULE_H_ */
