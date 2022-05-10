/*
 * IRSensor.c
 * Created on 30.08.2021
 * Author: Xuhui Zhang
 */

#include <hw_types.h>
#include <hw_hsi2c.h>
#include <soc_AM335x.h>
#include <interrupt.h>
#include <hw_cm_per.h>
#include <hw_control_AM335x.h>
#include "delay_ms.h"
#include "i2c.h"
#include <uartStdio.h>

/* Slave address */
unsigned int sla_address = 0x38;

/* Count: number of Bytes */
unsigned char count1 = 1;
unsigned char count2 = 2;

/* Register 3: configuaration */
unsigned char data3[2];

/* Register 1: Output */
unsigned char datat1[2];

/* Register 1: Input */
unsigned char datarw1[1];
char datarr1[1];

/* Stop condition */
char stp;

extern void initialization ()
{
	initi2c();

	data3[0] = 3;
	/* Pin 0-6: Input and Pin 7: Output, 0b01111111 */
	data3[1] = 127;

	stp = 1;

	writetoi2c(sla_address, &data3[0], count2, stp);

	/* Transmit data */

	datat1[0] = 1;

	/* Receive data */

	datarw1[0] = 0;
	datarr1[0] = 0;
}

extern char read_isrsensor()
{
	/* Pin 0-6: Input and Pin 7: Output, 0b10000000 */
	datat1[1] = 128;

	/* Send data: Write to i2c */
	stp = 1;
	writetoi2c(sla_address, &datat1[0], count2, stp);

	/* Receive data: Read from i2c */
	stp = 0;
	writetoi2c(sla_address, &datarw1[0], count1, stp);
	stp = 1;
	readfromi2c(sla_address, &datarr1[0], count1, stp);

	/* Pin 0-6: Input and Pin 7: Output, 0b00000000 */
	datat1[1] = 0;

	/* Send data: Write to i2c */
	stp = 1;
	writetoi2c(sla_address, &datat1[0], count2, stp);

	delay_ms(10);

    return datarr1[0];
}

