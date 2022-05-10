/*
 * EGR_DCMotor.c
 *
 *  Created on: 18.11.2013
 *      Author: Jonas
 */


#include "EGR_DCMotor.h"


/**
 * \brief  This API configures the action to be taken on A.
 * 		   This will determine the output waveform.
 *
 * \param	baseAddr			 baseAddr of EHRPWM
 * \param   ActionOnZero      	 Action to be taken when COUNTER == 0
 * \param   ActionOnCompMatch    Action to be taken when COUNTER == COMP_VALUE
 *
 *     Possible values for the actions are
 *	 	- EHRPWM_DO_NOTHING			0x0
 *	 	- EHRPWM_SET_OUTPUT_LOW		0x1
 *	 	- EHRPWM_SET_OUTPUT_HIGH	0x2
 *	 	- EHRPWM_OUTPUT_TOGGLE		0x3
 */
void configEHRPWM_A(unsigned int baseAddr,
					unsigned int ActionOnZero,
					unsigned int ActionOnCompMatch)
{
	HWREGH(baseAddr + EHRPWM_AQCTLA) = 	((ActionOnCompMatch << EHRPWM_AQCTLA_CAU_SHIFT) & EHRPWM_AQCTLA_CAU) |
										((ActionOnZero 		<< EHRPWM_AQCTLA_ZRO_SHIFT) & EHRPWM_AQCTLA_ZRO);
}


/**
 * \brief  This API configures the action to be taken on B.
 * 		   This will determine the output waveform.
 *
 * \param	baseAddr			 baseAddr of EHRPWM
 * \param   ActionOnZero      	 Action to be taken when COUNTER == 0
 * \param   ActionOnCompMatch    Action to be taken when COUNTER == COMP_VALUE
 *
 *     Possible values for the actions are
 *	 	- EHRPWM_DO_NOTHING			0x0
 *	 	- EHRPWM_SET_OUTPUT_LOW		0x1
 *	 	- EHRPWM_SET_OUTPUT_HIGH	0x2
 *	 	- EHRPWM_OUTPUT_TOGGLE		0x3
 */
void configEHRPWM_B(unsigned int baseAddr,
					unsigned int ActionOnZero,
					unsigned int ActionOnCompMatch)
{
	HWREGH(baseAddr + EHRPWM_AQCTLB) = 	((ActionOnCompMatch << EHRPWM_AQCTLA_CAU_SHIFT) & EHRPWM_AQCTLA_CAU) |
										((ActionOnZero 		<< EHRPWM_AQCTLA_ZRO_SHIFT) & EHRPWM_AQCTLA_ZRO);
}


/**
 * \brief  This API sets the DutyCycle of the PWM waveform,
 * 		   by loading the compare match value
 *
 * \param	baseAddr			 baseAddr of EHRPWM
 * \param   dutyCycle			 value of duty cycle in percent
 *
 *     Possible values for dutyCycle are [0 - 100]
 */
void EHRPWMsetDutyCycle (unsigned int baseAddr, unsigned short dutyCycle)
{
	// Load compare value to set the duty cycle
	// Attention! 16-Bit short register --> use HWREGH instead of HWREG !!
	HWREGH(baseAddr + EHRPWM_CMPA) = (dutyCycle * 10) & 0xFFFF;
}

/**
 *
 * \brief  This API initializes EHRPWM1 and EHRPWM2
 * 		   for use as DC motor control
 *
 *		   !! No Pin Muxing included !!
 */
void EHRPWMinitForDCMotor(){

	/******************************************************************************
	**      Enable the PWM Module in the clock management (CM_PER) registers
	*******************************************************************************/
	HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS1_CLKCTRL) |= 0x2;	// enable
	HWREG(SOC_PRCM_REGS + CM_PER_EPWMSS2_CLKCTRL) |= 0x2; 	// enable

	/******************************************************************************
	**     	Enable Timer Base Clock for PWM Module in the control module
	*******************************************************************************/
	HWREG(SOC_CONTROL_REGS + CONTROL_PWMSS_CTRL) |= (1 << 1); // Timebase Clock enable;
	HWREG(SOC_CONTROL_REGS + CONTROL_PWMSS_CTRL) |= (1 << 2); // Timebase Clock enable;

	/******************************************************************************
	**          Configure the clock frequency of the PWM Module with a Prescaler
	*******************************************************************************/
	// Clock Prescaler wird nicht zwingend benötigt
	// Attention! 16-Bit short register --> use HWREGH instead of HWREG !!
	HWREGH(SOC_EPWM_1_REGS + EHRPWM_TBCTL) = (HWREGH(SOC_EPWM_1_REGS + EHRPWM_TBCTL) &
			(~EHRPWM_TBCTL_HSPCLKDIV)) | ((PWM_CLOCK_PRESCALER/2 << EHRPWM_TBCTL_HSPCLKDIV_SHIFT) & EHRPWM_TBCTL_HSPCLKDIV);
	HWREGH(SOC_EPWM_2_REGS + EHRPWM_TBCTL) = (HWREGH(SOC_EPWM_1_REGS + EHRPWM_TBCTL) &
			(~EHRPWM_TBCTL_HSPCLKDIV)) | ((PWM_CLOCK_PRESCALER/2 << EHRPWM_TBCTL_HSPCLKDIV_SHIFT) & EHRPWM_TBCTL_HSPCLKDIV);


	/******************************************************************************
	**                     Configure the period of the output waveform
	*******************************************************************************/
	// Default mode is 0x3: Stop-freeze copunter !
	// --> must be set, to start counter
	// Attention! 16-Bit short register --> use HWREGH instead of HWREG !!
	HWREGH(SOC_EPWM_1_REGS + EHRPWM_TBCTL) &= (~EHRPWM_COUNTER_MODE_MASK);
	HWREGH(SOC_EPWM_1_REGS + EHRPWM_TBCTL) |= EHRPWM_TBCTL_CTRMODE_UP &  EHRPWM_COUNTER_MODE_MASK;
	HWREGH(SOC_EPWM_1_REGS + EHRPWM_TBPRD) = (unsigned short) 1000;
	HWREGH(SOC_EPWM_2_REGS + EHRPWM_TBCTL) &= (~EHRPWM_COUNTER_MODE_MASK);
	HWREGH(SOC_EPWM_2_REGS + EHRPWM_TBCTL) |= EHRPWM_TBCTL_CTRMODE_UP &  EHRPWM_COUNTER_MODE_MASK;
	HWREGH(SOC_EPWM_2_REGS + EHRPWM_TBPRD) = (unsigned short) 1000;


	/******************************************************************************
	**                     Configure Action qualifier
	*******************************************************************************/
	// Set Output HIGH, when CTR = 0
	// Set Output LOW,  when CTR = CMPA
	// Attention! 16-Bit short register --> use HWREGH instead of HWREG !!
	HWREGH(SOC_EPWM_1_REGS + EHRPWM_AQCTLB) = 	((EHRPWM_SET_OUTPUT_LOW  << EHRPWM_AQCTLA_CAU_SHIFT) & EHRPWM_AQCTLA_CAU) |
												((EHRPWM_SET_OUTPUT_HIGH << EHRPWM_AQCTLA_ZRO_SHIFT) & EHRPWM_AQCTLA_ZRO);
	HWREGH(SOC_EPWM_1_REGS + EHRPWM_AQCTLA) = 	((EHRPWM_DO_NOTHING  << EHRPWM_AQCTLA_CAU_SHIFT) & EHRPWM_AQCTLA_CAU) |
												((EHRPWM_DO_NOTHING  << EHRPWM_AQCTLA_ZRO_SHIFT) & EHRPWM_AQCTLA_ZRO);
	HWREGH(SOC_EPWM_2_REGS + EHRPWM_AQCTLA) = 	((EHRPWM_SET_OUTPUT_LOW  << EHRPWM_AQCTLA_CAU_SHIFT) & EHRPWM_AQCTLA_CAU) |
												((EHRPWM_SET_OUTPUT_HIGH << EHRPWM_AQCTLA_ZRO_SHIFT) & EHRPWM_AQCTLA_ZRO);
	HWREGH(SOC_EPWM_2_REGS + EHRPWM_AQCTLB) = 	((EHRPWM_DO_NOTHING  << EHRPWM_AQCTLA_CAU_SHIFT) & EHRPWM_AQCTLA_CAU) |
												((EHRPWM_DO_NOTHING  << EHRPWM_AQCTLA_ZRO_SHIFT) & EHRPWM_AQCTLA_ZRO);

	/******************************************************************************
	**  	            Configure Counter compare sub-module
	*******************************************************************************/
	/* Load Compare A value to set the duty cycle */
	// Attention! 16-Bit short register --> use HWREGH instead of HWREG !!
	HWREGH(SOC_EPWM_1_REGS + EHRPWM_CMPA) = 0;
	HWREGH(SOC_EPWM_2_REGS + EHRPWM_CMPA) = 0;

} //** End of EHRPWMinitForDCMotor() **
