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

#define OVF_IT_FLAG 1
#define MAT_IT_FLAG 0

void myTimer2Isr() {

	if ((HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) & (1 << OVF_IT_FLAG)) != 0)
	{
		HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) = (1 << OVF_IT_FLAG);

		EGR_PinWrite(GPIO_PORT3_PIN2_MODUL, GPIO_PORT3_PIN2, PIN_HIGH);
	}

	else if ((HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) & (1 << MAT_IT_FLAG)) != 0)
	{
		HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) = (1 << MAT_IT_FLAG);

		EGR_PinWrite(GPIO_PORT3_PIN2_MODUL, GPIO_PORT3_PIN2, PIN_LOW);
	}


}

int main() {

    /* GPIO for Servo-motor (Port 3 Pin 2): Output*/
	PinMuxing(CONF_PORT3_PIN2, PULL_DISABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT3_PIN2_MODUL, GPIO_PORT3_PIN2, GPIO_OUTPUT);

	EGR_PinWrite(GPIO_PORT3_PIN2_MODUL, GPIO_PORT3_PIN2, PIN_HIGH);

    /* GPIO for Switch 1 (Port 1 Pin 2): Input*/
	PinMuxing(CONF_PORT1_PIN2, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2, GPIO_INPUT);

    /* GPIO for Switch 2 (Port 1 Pin 4): Input*/
	PinMuxing(CONF_PORT1_PIN4, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4, GPIO_INPUT);

    /* GPIO for Switch 3 (Port 1 Pin 6): Input*/
	PinMuxing(CONF_PORT1_PIN6, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6, GPIO_INPUT);

	IntMasterIRQEnable();
	IntAINTCInit();
	IntSystemEnable(SYS_INT_TINT2);
	IntRegister(SYS_INT_TINT2, myTimer2Isr);

	/* TIMER */
	unsigned int pulse_width = 48000; /* 48000 (2ms: right); 36000 (1.5ms: middle); 24000 (1ms: left) */
	/* AR mode*/
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1 << 1);
	/* Disable prescaler*/
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) &=~ (1 << 5);
	/* Enable compare mode*/
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1 << 6);
	/* Compare value xms * 24*10^3 */
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = 0xFFFFFFFF - 480000 + pulse_width;
	/* Start time 0xFFFFFFFF - 20ms */
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCRR) = 0xFFFFFFFF - 480000;
	/* Load value 0xFFFFFFFF - 20ms */
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TLDR) = 0xFFFFFFFF - 480000;

	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_SET) |= ((1 << 0) | (1 << 1));

	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1 << 0);

	while (1)
	{
		if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0)
		{
			/* Switch 1: 2ms, right */
			delay_ms(200);
			pulse_width += 800;
			HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = 0xFFFFFFFF - 480000 + pulse_width;

			/* Maximal 2ms */
			if (pulse_width > 48000)
			{
				pulse_width = 48000;
			}
		}
		else if (EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4) == 0)
		{
			/* Switch 2: 1ms, left */
			delay_ms(200);
			pulse_width -= 800;
			HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = 0xFFFFFFFF - 480000 + pulse_width;

			/* Minimal 2ms */
			if (pulse_width < 24000)
			{
				pulse_width = 24000;
			}
		}
		else if (EGR_PinRead(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6) == 0)
		{
			/* Switch 3: 1.5ms, middle */
			pulse_width = 36000;
			HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = 0xFFFFFFFF - 480000 + pulse_width;
		}
	}
	return 0;
}
