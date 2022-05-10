/*
 * Motorsteuerung.c
 *
 * Created on 27.08.2021
 * Author: Xuhui Zhang
 *
 * Notation: This program is for initialization and signal setting of DC-motor
 *
 */

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


void MUXING_INITIALIZATION()
{
    /* Motor 1 (Out 1 Pin 2): ehrpwm*/
	PinMuxing(CONF_H_BRUECKE_MOTOR1_2, PULL_DISABLE, PULL_UP, ehrpwm1);

    /* Motor 1 (Out 2 Pin 1): ehrpwm*/
	PinMuxing(CONF_H_BRUECKE_MOTOR1_1, PULL_DISABLE, PULL_UP, ehrpwm1);

    /* Motor 2 (Out 1 Pin 2): ehrpwm*/
	PinMuxing(CONF_H_BRUECKE_MOTOR2_2, PULL_DISABLE, PULL_UP, ehrpwm2);

    /* Motor 2 (Out 2 Pin 1): ehrpwm*/
	PinMuxing(CONF_H_BRUECKE_MOTOR2_1, PULL_DISABLE, PULL_UP, ehrpwm2);

	EHRPWMinitForDCMotor();
}

extern void MOTOR1_CONTROL(int duty_cycle, unsigned int actiononzero_1a, unsigned int actiononzero_1b)
{
	/* Motor 1 */
	EHRPWMsetDutyCycle (SOC_EPWM_1_REGS, duty_cycle);

	/* Set mode */
	configEHRPWM_A (SOC_EPWM_1_REGS, actiononzero_1a, EHRPWM_SET_OUTPUT_LOW);
	configEHRPWM_B (SOC_EPWM_1_REGS, actiononzero_1b, EHRPWM_SET_OUTPUT_LOW);
}

extern void MOTOR2_CONTROL(int duty_cycle, unsigned int actiononzero_2a, unsigned int actiononzero_2b)
{
	/* Motor 2 */
	EHRPWMsetDutyCycle (SOC_EPWM_2_REGS, duty_cycle);

	/* Set mode */
	configEHRPWM_A (SOC_EPWM_2_REGS, actiononzero_2a, EHRPWM_SET_OUTPUT_LOW);
	configEHRPWM_B (SOC_EPWM_2_REGS, actiononzero_2b, EHRPWM_SET_OUTPUT_LOW);
}


