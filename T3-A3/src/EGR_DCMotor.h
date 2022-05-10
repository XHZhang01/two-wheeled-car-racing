/*
 * EGR_DCMotor.h
 *
 *  Created on: 14.11.2013
 *      Author: Jonas Pfeiffer
 */

#ifndef EGR_DCMOTOR_H_
#define EGR_DCMOTOR_H_

/******************************************************************************
**                    		INCLUDES
*******************************************************************************/
#include <soc_AM335x.h>
#include <hw_types.h>
#include <hw_control_AM335x.h>
#include <hw_cm_per.h>
#include <ehrpwm.h>

/******************************************************************************
**                      MACRO DEFINITIONS
*******************************************************************************/
#define PWM_CLOCK_PRESCALER			10

#define EHRPWM_DO_NOTHING			0x0
#define EHRPWM_SET_OUTPUT_LOW		0x1
#define EHRPWM_SET_OUTPUT_HIGH		0x2
#define EHRPWM_OUTPUT_TOGGLE		0x3

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
void EHRPWMinitForDCMotor();
void EHRPWMsetDutyCycle (unsigned int baseAddr, unsigned short dutyCycle);
void configEHRPWM_A		(unsigned int baseAddr, unsigned int ActionOnZero, unsigned int ActionOnCompMatch);
void configEHRPWM_B		(unsigned int baseAddr, unsigned int ActionOnZero, unsigned int ActionOnCompMatch);

#endif /* EGR_DCMOTOR_H_ */
