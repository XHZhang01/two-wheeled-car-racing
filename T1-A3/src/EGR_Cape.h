// Diese Datei wird nur verlinkt. D.h. ihr editiert ueber alle Projekte hinweg die selbe (diese) Datei.

/*

 * EGR_Cape.h
 *
 *  Created on: 12.10.2014
 *  	Author: Andreas Hutter, Johannes Coy
 *   Copyright: TUM MiMed
 * Last Change: 28.10.2014
 */

#ifndef EGR_CAPE_H_
#define EGR_CAPE_H_

/*
 * ===================================
 *  Pinbelegung des BeagleCape
 * ===================================
 * Modul-	  | Pin-Name   | GPIO-Pin
 * Steckplatz |	(Std.)	   |
 * ===================================
 * 	USR0	  | GPMC_A5    | GPIO1_21
 * 	USR1	  | GPMC_A6    | GPIO1_22
 * 	USR2	  | GPMC_A7    | GPIO1_23
 * 	USR3	  | GPMC_A8    | GPIO1_24
 * ===================================
 * 	Port1	  | LCD_DATA6  | GPIO2_12
 *       	  | LCD_DATA4  | GPIO2_10
 *		      | LCD_DATA2  | GPIO2_8
 *      	  | LCD_DATA0  | GPIO2_6
 * ===================================
 * 	Port2 	  | LCD_DATA14 | GPIO0_10
 *       	  | LCD_DATA13 | GPIO0_9
 *        	  | LCD_DATA12 | GPIO0_8
 *       	  | LCD_DATA8  | GPIO2_14
 * ===================================
 * 	Port3  	  | GPMC_AD4   | GPIO1_4
 *       	  | GPMC_AD0   | GPIO1_0
 *        	  | LCD_VSYNC  | GPIO2_22
 *       	  | LCD_HSYNC  | GPIO2_23
 * ===================================
 * 	H-Bruecke | GPMC_A2    | GPIO1_18
 *  (MOtor)   | GPMC_A3    | GPIO1_19
 *        	  | GPMC_AD8   | GPIO0_22
 *       	  | GPMC_AD9   | GPIO0_23
 * ===================================
 * 	I2C SCL   | spi0_cs0   | GPIO0_5
 *      SDA   | spi0_d1    | GPIO0_4
 *       	  |            |
 * =================================== *
 *
 *
 */

// Zuordnung der Portpins zu den GPIO Modulen

//USRLEDs
	// Pinnummer des Portpins
#define 	GPIO_USRLED0		21
#define 	GPIO_USRLED1		22
#define 	GPIO_USRLED2		23
#define 	GPIO_USRLED3		24

	// GPIO-Modul-Basisadresse des Portpins
#define 	GPIO_USRLED0_MODUL	0x4804C000
#define 	GPIO_USRLED1_MODUL	0x4804C000
#define 	GPIO_USRLED2_MODUL	0x4804C000
#define 	GPIO_USRLED3_MODUL	0x4804C000

// Port 1
	// Pinnummer des Portpins
#define 	GPIO_PORT1_PIN2		12 
#define 	GPIO_PORT1_PIN4		10
#define 	GPIO_PORT1_PIN6		8
#define 	GPIO_PORT1_PIN8		6

	// GPIO-Modul-Basisadresse des Portpins
#define 	GPIO_PORT1_PIN2_MODUL	0x481AC000
#define 	GPIO_PORT1_PIN4_MODUL	0x481AC000
#define 	GPIO_PORT1_PIN6_MODUL	0x481AC000
#define 	GPIO_PORT1_PIN8_MODUL	0x481AC000

// Port 2
	// Pinnummer des Portpins
#define 	GPIO_PORT2_PIN2		10
#define 	GPIO_PORT2_PIN4		9
#define 	GPIO_PORT2_PIN6		8
#define 	GPIO_PORT2_PIN8		14

	// GPIO-Modul-Basisadresse des Portpins
#define 	GPIO_PORT2_PIN2_MODUL	0x44E07000
#define 	GPIO_PORT2_PIN4_MODUL	0x44E07000
#define 	GPIO_PORT2_PIN6_MODUL	0x44E07000
#define 	GPIO_PORT2_PIN8_MODUL	0x481AC000

// Port 3
	// Pinnummer des Portpins
#define 	GPIO_PORT3_PIN2		4
#define 	GPIO_PORT3_PIN4		0
#define 	GPIO_PORT3_PIN6		22
#define 	GPIO_PORT3_PIN8		23

	// GPIO-Modul-Basisadresse des Portpins
#define 	GPIO_PORT3_PIN2_MODUL	0x4804C000
#define 	GPIO_PORT3_PIN4_MODUL	0x4804C000
#define 	GPIO_PORT3_PIN6_MODUL	0x481AC000
#define 	GPIO_PORT3_PIN8_MODUL	0x481AC000

//H-Bruecke als GPIO-Pins
	// Pinnummer des Portpins
#define		GPIO_H_BRUECKE_MOTOR1_1	18
#define		GPIO_H_BRUECKE_MOTOR1_2	19
#define		GPIO_H_BRUECKE_MOTOR2_1	22
#define		GPIO_H_BRUECKE_MOTOR2_2	23

	// GPIO-Modul-Basisadresse des Portpins
#define		GPIO_H_BRUECKE_MOTOR1_1_MODUL	0x4804C000
#define		GPIO_H_BRUECKE_MOTOR1_2_MODUL	0x4804C000
#define		GPIO_H_BRUECKE_MOTOR2_1_MODUL	0x44E07000
#define		GPIO_H_BRUECKE_MOTOR2_2_MODUL	0x44E07000


//Offsetadresse des Portpins im Controlmodul zum Pinmuxing
//USRLEDS
#define 	CONF_USRLED0		0x854
#define 	CONF_USRLED1		0x858
#define 	CONF_USRLED2		0x85C
#define 	CONF_USRLED3		0x860
// Port 1
#define  	CONF_PORT1_PIN2		0x8b8
#define  	CONF_PORT1_PIN4		0x8b0
#define  	CONF_PORT1_PIN6		0x8a8
#define  	CONF_PORT1_PIN8		0x8a0
// Port 2
#define  	CONF_PORT2_PIN2		0x8d8
#define  	CONF_PORT2_PIN4		0x8b4
#define  	CONF_PORT2_PIN6		0x8a0
#define  	CONF_PORT2_PIN8		0x8c0
// Port 3
#define  	CONF_PORT3_PIN2		0x810
#define  	CONF_PORT3_PIN4		0x800
#define  	CONF_PORT3_PIN6		0x8e0
#define  	CONF_PORT3_PIN8		0x8e4
// H-Bruecke werden erst in Termin 2 ben�tigt
#define		CONF_H_BRUECKE_MOTOR1_1     0x848
#define		CONF_H_BRUECKE_MOTOR1_2     0x84c
#define		CONF_H_BRUECKE_MOTOR2_1     0x820
#define		CONF_H_BRUECKE_MOTOR2_2     0x824

//I2C Pins werden erst in Termin 4 ben�tigt
#define		CONF_I2C_SCL
#define		CONF_I2C_SDA


#endif /* EGR_CAPE_H_ */
