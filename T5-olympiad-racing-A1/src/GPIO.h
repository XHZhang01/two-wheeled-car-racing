// Diese Datei wird nur verlinkt. D.h. ihr editiert ueber alle Projekte hinweg die selbe (diese) Datei.

/*
 * EGR_GPIO.h
 *
 *  Created on: 24.01.2014
 *      Author: Jonas Pfeiffer, Johannes Coy
 *   Copyright: TUM MiMed
 * Last Change: 28.10.2014
 */


#include <hw_types.h>



#ifndef GPIO_H_
#define GPIO_H_

// Pin Values
#define 	PIN_HIGH 		1
#define 	PIN_LOW 		0

// Input or Output
#define 	GPIO_OUTPUT		0
#define 	GPIO_INPUT		1

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GPIO Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern void EGR_GPIODirSet(unsigned int gpio_base_addr,
						   unsigned int pinNumber,
						   unsigned int pinDirection);

extern void EGR_PinWrite  (unsigned int gpio_base_addr,
						   unsigned int pinNumber,
						   unsigned int pinValue);

extern unsigned int EGR_PinRead (unsigned int gpio_base_addr,
						  	  	 unsigned int pinNumber);

#endif /* GPIO_H_ */
