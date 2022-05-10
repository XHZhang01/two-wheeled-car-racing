/*
 * delay.h
 *
 *  Created on: 28.10.2013
 *      Author: Jonas Pfeiffer
 *
 *
 *     Anmerkung: 	Diese delay_ms() funktioniert mit der Rev. C des Beaglebone Black!!
 *     				�ltere Revisions ben�tigen nur 2450 "nop" cycles f�r 1 ms delay!!
 */

#ifndef DELAY_MS_H_
#define DELAY_MS_H_


extern void delay_ms(unsigned int ms);
extern void delay_us(unsigned int us);


#endif /* DELAY_H_ */
