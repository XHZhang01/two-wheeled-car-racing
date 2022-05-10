/*
 * Motorsteuerung.h
 *
 * Created on 27.08.2021
 * Author: Xuhui Zhang
 *
 * Notation: This program is for initialization and signal setting of DC-motor
 *
 */

#ifndef MOTOR_STEUERUNG_H_
#define MOTOR_STEUERUNG_H_

#define		ehrpwm1		6
#define		ehrpwm2		4

extern void MUXING_INITIALIZATION();
extern void MOTOR1_CONTROL(int duty_cycle, unsigned int actiononzero_1a, unsigned int actiononzero_1b);
extern void MOTOR2_CONTROL(int duty_cycle, unsigned int actiononzero_2a, unsigned int actiononzero_2b);

/*
 * MODE for DC-motor, 0: Forward; 1: Reverse; 2: Brake; 3: Standby
 */

#endif /*MOTOR_STEUERUNG_H_*/
