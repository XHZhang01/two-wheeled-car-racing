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

#define		ehrpwm1		6
#define		ehrpwm2		4

unsigned int step_size = 10;
int pulse_width = 5;

unsigned int actiononzero_1a = EHRPWM_SET_OUTPUT_HIGH;
unsigned int actiononzero_1b = EHRPWM_SET_OUTPUT_LOW;
unsigned int actiononzero_2a = EHRPWM_SET_OUTPUT_HIGH;
unsigned int actiononzero_2b = EHRPWM_SET_OUTPUT_LOW;

int main() {

//    /* Motor 1 (Out 1 Pin 2): ehrpwm*/
//	PinMuxing(CONF_H_BRUECKE_MOTOR1_2, PULL_DISABLE, PULL_UP, ehrpwm1);
//
//    /* Motor 1 (Out 2 Pin 1): ehrpwm*/
//	PinMuxing(CONF_H_BRUECKE_MOTOR1_1, PULL_DISABLE, PULL_UP, ehrpwm1);
//
//    /* Motor 2 (Out 1 Pin 2): ehrpwm*/
//	PinMuxing(CONF_H_BRUECKE_MOTOR2_2, PULL_DISABLE, PULL_UP, ehrpwm2);
//
//    /* Motor 2 (Out 2 Pin 1): ehrpwm*/
//	PinMuxing(CONF_H_BRUECKE_MOTOR2_1, PULL_DISABLE, PULL_UP, ehrpwm2);
//
//	EHRPWMinitForDCMotor();

	MUXING_INITIALIZATION();

	/* Motor 1*/
//	EHRPWMsetDutyCycle (SOC_EPWM_1_REGS, pulse_width);
//	configEHRPWM_A (SOC_EPWM_1_REGS, actiononzero_1a, EHRPWM_SET_OUTPUT_LOW);
//	configEHRPWM_B (SOC_EPWM_1_REGS, actiononzero_1b, EHRPWM_SET_OUTPUT_LOW);
	MOTOR1_CONTROL(pulse_width, actiononzero_1a, actiononzero_1b);


	/* Motor 2*/
//	EHRPWMsetDutyCycle (SOC_EPWM_2_REGS, pulse_width);
//	configEHRPWM_A (SOC_EPWM_2_REGS, actiononzero_2a, EHRPWM_SET_OUTPUT_LOW);
//	configEHRPWM_B (SOC_EPWM_2_REGS, actiononzero_2b, EHRPWM_SET_OUTPUT_LOW);
	MOTOR2_CONTROL(pulse_width, actiononzero_2a, actiononzero_2b);


    /* GPIO for Switch 1 (Port 1 Pin 2): Input*/
	PinMuxing(CONF_PORT1_PIN2, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2, GPIO_INPUT);

    /* GPIO for Switch 2 (Port 1 Pin 4): Input*/
	PinMuxing(CONF_PORT1_PIN4, PULL_ENABLE, PULL_UP, GPIO_MODE);
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4, GPIO_INPUT);

	while (1)
	{
		if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0)
		{
			/* Switch 1: Acceleration with step size 10 */
			delay_ms(200);
			pulse_width += step_size;

			/* pulse width <= 100 */
			if (pulse_width > 100)
			{
				pulse_width = 100;
			}

			if (pulse_width > 0)
			{
				/* In postive direction */
				actiononzero_1a = EHRPWM_SET_OUTPUT_HIGH;
				actiononzero_1b = EHRPWM_SET_OUTPUT_LOW;
				actiononzero_2a = EHRPWM_SET_OUTPUT_HIGH;
				actiononzero_2b = EHRPWM_SET_OUTPUT_LOW;

				/* Motor 1*/
//				EHRPWMsetDutyCycle (SOC_EPWM_1_REGS, pulse_width);
//				configEHRPWM_A (SOC_EPWM_1_REGS, actiononzero_1a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_1_REGS, actiononzero_1b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR1_CONTROL(pulse_width, actiononzero_1a, actiononzero_1b);

				/* Motor 2*/
//				EHRPWMsetDutyCycle (SOC_EPWM_2_REGS, pulse_width);
//				configEHRPWM_A (SOC_EPWM_2_REGS, actiononzero_2a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_2_REGS, actiononzero_2b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR2_CONTROL(pulse_width, actiononzero_2a, actiononzero_2b);
			}
			else
			{
				/* In negative direction */
				actiononzero_1a = EHRPWM_SET_OUTPUT_LOW;
				actiononzero_1b = EHRPWM_SET_OUTPUT_HIGH;
				actiononzero_2a = EHRPWM_SET_OUTPUT_LOW;
				actiononzero_2b = EHRPWM_SET_OUTPUT_HIGH;

				/* Motor 1*/
//				EHRPWMsetDutyCycle (SOC_EPWM_1_REGS, -pulse_width);
//				configEHRPWM_A (SOC_EPWM_1_REGS, actiononzero_1a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_1_REGS, actiononzero_1b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR1_CONTROL(-pulse_width, actiononzero_1a, actiononzero_1b);

				/* Motor 2*/
//				EHRPWMsetDutyCycle (SOC_EPWM_2_REGS, -pulse_width);
//				configEHRPWM_A (SOC_EPWM_2_REGS, actiononzero_2a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_2_REGS, actiononzero_2b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR2_CONTROL(-pulse_width, actiononzero_2a, actiononzero_2b);
			}
		}

		if (EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4) == 0)
		{
			/* Switch 2: Decceleration with step size 10 */
			delay_ms(200);
			pulse_width -= step_size;

			/* pulse width >= -100 */
			if (pulse_width < -100)
			{
				pulse_width = -100;
			}

			if (pulse_width > 0)
			{
				/* In postive direction */
				actiononzero_1a = EHRPWM_SET_OUTPUT_HIGH;
				actiononzero_1b = EHRPWM_SET_OUTPUT_LOW;
				actiononzero_2a = EHRPWM_SET_OUTPUT_HIGH;
				actiononzero_2b = EHRPWM_SET_OUTPUT_LOW;

				/* Motor 1*/
//				EHRPWMsetDutyCycle (SOC_EPWM_1_REGS, pulse_width);
//				configEHRPWM_A (SOC_EPWM_1_REGS, actiononzero_1a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_1_REGS, actiononzero_1b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR1_CONTROL(pulse_width, actiononzero_1a, actiononzero_1b);

				/* Motor 2*/
//				EHRPWMsetDutyCycle (SOC_EPWM_2_REGS, pulse_width);
//				configEHRPWM_A (SOC_EPWM_2_REGS, actiononzero_2a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_2_REGS, actiononzero_2b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR2_CONTROL(pulse_width, actiononzero_2a, actiononzero_2b);
			}
			else
			{
				/* In negative direction */
				actiononzero_1a = EHRPWM_SET_OUTPUT_LOW;
				actiononzero_1b = EHRPWM_SET_OUTPUT_HIGH;
				actiononzero_2a = EHRPWM_SET_OUTPUT_LOW;
				actiononzero_2b = EHRPWM_SET_OUTPUT_HIGH;

				/* Motor 1*/
//				EHRPWMsetDutyCycle (SOC_EPWM_1_REGS, -pulse_width);
//				configEHRPWM_A (SOC_EPWM_1_REGS, actiononzero_1a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_1_REGS, actiononzero_1b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR1_CONTROL(-pulse_width, actiononzero_1a, actiononzero_1b);

				/* Motor 2*/
//				EHRPWMsetDutyCycle (SOC_EPWM_2_REGS, -pulse_width);
//				configEHRPWM_A (SOC_EPWM_2_REGS, actiononzero_2a, EHRPWM_SET_OUTPUT_LOW);
//				configEHRPWM_B (SOC_EPWM_2_REGS, actiononzero_2b, EHRPWM_SET_OUTPUT_LOW);
				MOTOR2_CONTROL(-pulse_width, actiononzero_2a, actiononzero_2b);
			}
		}
	}
	return 0;
}
