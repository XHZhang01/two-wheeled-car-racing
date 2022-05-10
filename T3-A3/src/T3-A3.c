/* EGR */

#include <hw_types.h>
#include"Conf_mod.h"
#include"delay_ms.h"
#include"EGR_Cape.h"
#include"GPIO.h"
#include<interrupt.h>
#include<soc_AM335x.h>
#include"EGR_DCMotor.h"
#include<hw_gpio_v2.h>
#include<hw_dmtimer.h>
#include<uartStdio.h>
#include<hw_tsc_adc_ss.h>
#include"Motorsteuerung.h"

#define		ehrpwm1		6
#define		ehrpwm2		4

float pulse_width_M1 = -50;
float pulse_width_M2 = 50;

unsigned int actiononzero_1a = EHRPWM_SET_OUTPUT_HIGH;
unsigned int actiononzero_1b = EHRPWM_SET_OUTPUT_LOW;
unsigned int actiononzero_2a = EHRPWM_SET_OUTPUT_HIGH;
unsigned int actiononzero_2b = EHRPWM_SET_OUTPUT_LOW;

int main() {

	/* Joysticker */

	/* Activate ADC */
	HWREG(SOC_CM_WKUP_REGS + (0Xbc)) &= ~(0x3);
	HWREG(SOC_CM_WKUP_REGS + (0Xbc)) |= (0x2);

	/* Deactivate WriteProtect */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 2);

	/* Choose Steps */

	/* Port 1 (AIN1): Step 1 and FIFO */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPENABLE) |= (1 << 1);

	/* Mode */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 0)|(1 << 1));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 0);

	/* Analog pins */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 19)|(1 << 20)|(1 << 21)|(1 << 22));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 19);

	/* Positive reference voltage: VDDA */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 12)|(1 << 14));

	/* FIFO */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~(1 << 26);

	/* 16 samples avergae */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 2)|(1 << 3)|(1 << 4));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 4);

	/* Port 2 (AIN3): Step 2 and FIFO1 */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPENABLE) |= (1 << 2);

	/* Mode */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~((1 << 0)|(1 << 1));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 0);

	/* Analog pins */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~((1 << 19)|(1 << 20)|(1 << 21)|(1 << 22));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (0x3 << 19);

	/* Positive reference voltage: VDDA */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~((1 << 12)|(1 << 14));

	/* FIFO1 */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 26);

	/* 16 samples avergae */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~((1 << 2)|(1 << 3)|(1 << 4));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 4);

	/* Start */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 0);

	/* Motors */

	/* Pin-muxing and initialization of motors */
	MUXING_INITIALIZATION();

	/* Motor 1 */
	MOTOR1_CONTROL((int)pulse_width_M1, actiononzero_1a, actiononzero_1b);

	/* Motor 2 */
	MOTOR2_CONTROL((int)pulse_width_M2, actiononzero_2a, actiononzero_2b);


	while (1)
	{
		/*
		 * Port 1 (right 350 to left 3540); Port 2 (back 200 to forward 3900)
		 * Mapping: Port 2 (Backward or Forward), [200, 3900] to [-100, 100]: -100 + 200/(3900 - 200)*(myadcvalue_p2 - 200);
		 *          Port 1 (Right or Left), Left [350, 3540] to [50, -50] ;Right [350, 3540] to [-50, 50]
		 */

		/* Read ADC value of Port 1 */
		unsigned int myadcvalue_p1;
		myadcvalue_p1 = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(0));

		/* Output ADC value of Port 1 to computer screen */
		UARTprintf("Current ADC value of Port 1: ");
		UARTPutNum(myadcvalue_p1);
		UARTprintf("\r\n");

		/* Read ADC value of Port 2 */
		unsigned int myadcvalue_p2;
		myadcvalue_p2 = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(1));

		/* Output ADC value of Port 2 to computer screen */
		UARTprintf("Current ADC value of Port 2: ");
		UARTPutNum(myadcvalue_p2);
		UARTprintf("\r\n");

		/* Mapping */
//		pulse_width_M1 = -((-100.0 + 200.0/(3900.0 - 200.0)*(myadcvalue_p2 - 200.0)) - (-50.0 + 100.0/(3540.0 - 350.0)*(myadcvalue_p1 - 350.0)));
//		pulse_width_M2 = (-100.0 + 200.0/(3900.0 - 200.0)*(myadcvalue_p2 - 200.0)) + (-50.0 + 100.0/(3540.0 - 350.0)*(myadcvalue_p1 - 350.0));

		/* Port 2: forward or backward */
		pulse_width_M1 = -100.0 + 200.0/(3900.0 - 200.0)*(myadcvalue_p2 - 200.0);
		pulse_width_M2 = -100.0 + 200.0/(3900.0 - 200.0)*(myadcvalue_p2 - 200.0);
		if (pulse_width_M1 > 0 )
		{
			/* Forward */
			/* Port 1: left or right */
			pulse_width_M1 += -50.0 + 100.0/(3540.0 - 350.0)*(myadcvalue_p1 - 350.0);
			pulse_width_M2 -= -50.0 + 100.0/(3540.0 - 350.0)*(myadcvalue_p1 - 350.0);
		}

		if (pulse_width_M1 < 0 )
		{
			/* Backward */
			/* Port 1: left or right */
			pulse_width_M1 -= -50.0 + 100.0/(3540.0 - 350.0)*(myadcvalue_p1 - 350.0);
			pulse_width_M2 += -50.0 + 100.0/(3540.0 - 350.0)*(myadcvalue_p1 - 350.0);
		}
		pulse_width_M1 = -pulse_width_M1;

		/* Maximal value 100 and minimal value -100 */
		/* Motor 1 */
		if (pulse_width_M1 > 100)
		{
			pulse_width_M1 = 100;
		}
		else if (pulse_width_M1 < -100)
		{
			pulse_width_M1 = -100;
		}
		/* Motor 2 */
		if (pulse_width_M2 > 100)
		{
			pulse_width_M2 = 100;
		}
		else if (pulse_width_M2 < -100)
		{
			pulse_width_M2 = -100;
		}

		/* Motor 1 */
		if (pulse_width_M1 > 0)
		{
			/* Forward */
			actiononzero_1a = EHRPWM_SET_OUTPUT_HIGH;
		    actiononzero_1b = EHRPWM_SET_OUTPUT_LOW;

			MOTOR1_CONTROL((int)pulse_width_M1, actiononzero_1a, actiononzero_1b);
		}
		else
		{
			/* Backward */
			actiononzero_1a = EHRPWM_SET_OUTPUT_LOW;
		    actiononzero_1b = EHRPWM_SET_OUTPUT_HIGH;

			MOTOR1_CONTROL(-(int)pulse_width_M1, actiononzero_1a, actiononzero_1b);
		}

		/* Motor 2 */
		if (pulse_width_M2 > 0)
		{
			/* Forward */
			actiononzero_2a = EHRPWM_SET_OUTPUT_HIGH;
		    actiononzero_2b = EHRPWM_SET_OUTPUT_LOW;

			MOTOR2_CONTROL((int)pulse_width_M2, actiononzero_2a, actiononzero_2b);
		}
		else
		{
			/* Backward */
			actiononzero_2a = EHRPWM_SET_OUTPUT_LOW;
		    actiononzero_2b = EHRPWM_SET_OUTPUT_HIGH;

			MOTOR2_CONTROL(-(int)pulse_width_M2, actiononzero_2a, actiononzero_2b);
		}

		/* Output pulse width */
		UARTprintf("Pulse width of motor 1: ");
		UARTPutNum((int)pulse_width_M1);
		UARTprintf("\r\n");
		UARTprintf("Pulse width of motor 2: ");
		UARTPutNum((int)pulse_width_M2);
		UARTprintf("\r\n");
	}
	return 0;
}
