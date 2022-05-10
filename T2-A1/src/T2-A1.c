/* EGR */

#include <hw_types.h>
#include"Conf_mod.h"
#include"delay_ms.h"
#include"EGR_Cape.h"
#include"GPIO.h"
#include<interrupt.h>
#include<soc_AM335x.h>
#include<hw_gpio_v2.h>
#include<hw_dmtimer.h>

unsigned int counter = 0;

void myGPIO2Isr() {

	/* Read input of Switch 3 */
	if (EGR_PinRead(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6) == 0)
	{
		/* Turn off all LEDS*/
		EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_HIGH);
		EGR_PinWrite(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, PIN_HIGH);
		EGR_PinWrite(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, PIN_HIGH);
		EGR_PinWrite(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, PIN_HIGH);

//		delay_ms(800);
		counter++;
	}
}

int main() {

    /* GPIO for Switch 1 (Port 1 Pin 2): Input*/
	PinMuxing(CONF_PORT1_PIN2, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2, GPIO_INPUT);

    /* GPIO for Switch 2 (Port 1 Pin 4): Input*/
	PinMuxing(CONF_PORT1_PIN4, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4, GPIO_INPUT);

    /* GPIO for Switch 3 (Port 1 Pin 6): Input*/
	PinMuxing(CONF_PORT1_PIN6, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6, GPIO_INPUT);

    /* GPIO for LED 1 (Port 2 Pin 2): Output*/
	PinMuxing(CONF_PORT2_PIN2, PULL_DISABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, GPIO_OUTPUT);

    /* GPIO for LED 2 (Port 2 Pin 4): Output*/
	PinMuxing(CONF_PORT2_PIN4, PULL_DISABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, GPIO_OUTPUT);

    /* GPIO for LED 3 (Port 2 Pin 6): Output*/
	PinMuxing(CONF_PORT2_PIN6, PULL_DISABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, GPIO_OUTPUT);

    /* GPIO for LED 4 (Port 2 Pin 8): Output*/
	PinMuxing(CONF_PORT2_PIN8, PULL_DISABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, GPIO_OUTPUT);

	/* Initialization: turn off all LEDs*/

	EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_HIGH);
	EGR_PinWrite(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, PIN_HIGH);
	EGR_PinWrite(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, PIN_HIGH);
	EGR_PinWrite(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, PIN_HIGH);

	unsigned int delay_time = 1500;

	IntMasterIRQEnable();
	IntAINTCInit();
	IntSystemEnable(SYS_INT_GPIOINT2A);
	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_SET(0)) |= (1 << GPIO_PORT1_PIN6);
	HWREG(SOC_GPIO_2_REGS + GPIO_FALLINGDETECT) |= (1 << GPIO_PORT1_PIN6);
	IntRegister(SYS_INT_GPIOINT2A, myGPIO2Isr);

	while (1)
	{
		/* Read input of Switch 1 */
		if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0)
		{
			delay_ms(800);
			counter++;
		}

		/* LED1 */
		if (counter%2 == 1)
		{
			/* Turn on LED 1 for delay time and then turn if off*/
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_LOW);
			delay_ms(delay_time);
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_HIGH);
		}
		else
		{
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_HIGH);
		}

		/* Read input of Switch 1 */
	    if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0)
		{
			delay_ms(800);
			counter++;
		}

		/* Read input of Switch 2 */
		if (EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4) == 0)
		{
			delay_ms(200);
			delay_time = delay_time - 50;
		}


		/* LED2 */
		if (counter%2 == 1)
		{
			/* Turn on LED 2 for delay time and then turn if off*/
			EGR_PinWrite(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, PIN_LOW);
			delay_ms(delay_time);
			EGR_PinWrite(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, PIN_HIGH);
		}
		else
		{
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_HIGH);
		}

		/* Read input of Switch 1 */
		if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0)
		{
			delay_ms(800);
			counter++;
		}

		/* Read input of Switch 2 */
		if (EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4) == 0)
		{
			delay_ms(200);
			delay_time = delay_time - 50;
		}

		/* LED3 */
		if (counter%2 == 1)
		{
			/* Turn on LED 3 for delay time and then turn if off*/
			EGR_PinWrite(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, PIN_LOW);
			delay_ms(delay_time);
			EGR_PinWrite(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, PIN_HIGH);
		}
		else
		{
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_HIGH);
		}

		/* Read input of Switch 1 */
		if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0)
		{
			delay_ms(800);
			counter++;
		}

		/* Read input of Switch 2 */
		if (EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4) == 0)
		{
			delay_ms(200);
			delay_time = delay_time - 50;
		}

		/* LED4 */
		if (counter%2 == 1)
		{
			/* Turn on LED 4 for delay time and then turn if off*/
			EGR_PinWrite(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, PIN_LOW);
			delay_ms(delay_time);
			EGR_PinWrite(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, PIN_HIGH);
		}
		else
		{
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, PIN_HIGH);
		}

		/* Read input of Switch 1 */
		if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0)
		{
			delay_ms(800);
			counter++;
		}

		/* Read input of Switch 2 */
		if (EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4) == 0)
		{
			delay_ms(200);
			delay_time = delay_time - 50;
		}

	}
	return 0;

}
