/*
 * i2c.h
 *
 *  Created on: 13.12.2013
 *      Author: Coy
 *		Copyright: TUM MiMed 2013
 *		beaglebone EGR
 *		Version: 1.0
 */

#ifndef I2C_H_
#define I2C_H_
#include <hw_types.h>
#include <hw_hsi2c.h>
#include <soc_AM335x.h>
#include <interrupt.h>
#include <hw_cm_per.h>
#include <hw_control_AM335x.h>
#include "delay_ms.h"

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

//void
//Delay_us(unsigned int us);
//
//void
//Delay(unsigned int ms);

void
initi2c();

void
writetoi2c(unsigned int sla_address, unsigned char*data, unsigned char count,
    char stp);

void
readfromi2c(unsigned int sla_address, char*data, unsigned char count, char stp);

void
I2CIsr(void);

void
CleanUpInterrupts(void);

#endif /* I2C_H_ */
