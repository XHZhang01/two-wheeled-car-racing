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
#include <hw_hsi2c.h>
#include <hw_cm_per.h>
#include <hw_control_AM335x.h>
#include "i2c.h"
#include <uartStdio.h>
#include "Motorsteuerung.h"
#include "IRSensors.h"

#define		ehrpwm1		6
#define		ehrpwm2		4

float pulse_width_M1 = 80;
float pulse_width_M2 = 80;

/* Motor 1: left; Motor 2: right */
unsigned int actiononzero_1a = EHRPWM_SET_OUTPUT_HIGH;
unsigned int actiononzero_1b = EHRPWM_SET_OUTPUT_LOW;
unsigned int actiononzero_2a = EHRPWM_SET_OUTPUT_LOW;
unsigned int actiononzero_2b = EHRPWM_SET_OUTPUT_HIGH;

unsigned int left_right = 0;

void set_motors(float pw1, float pw2)
{
	/* Motor 1 */
	if (pulse_width_M1 > 100)
	{
		pulse_width_M1 = 100;
	}
	else if (pulse_width_M1 < -80)
	{
		pulse_width_M1 = -80;
	}
	/* Motor 2 */
	if (pulse_width_M2 > 100)
	{
		pulse_width_M2 = 100;
	}
	else if (pulse_width_M2 < -80)
	{
		pulse_width_M2 = -80;
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
		actiononzero_2a = EHRPWM_SET_OUTPUT_LOW;
	    actiononzero_2b = EHRPWM_SET_OUTPUT_HIGH;

		MOTOR2_CONTROL((int)pulse_width_M2, actiononzero_2a, actiononzero_2b);
	}
	else
	{
		/* Backward */
		actiononzero_2a = EHRPWM_SET_OUTPUT_HIGH;
	    actiononzero_2b = EHRPWM_SET_OUTPUT_LOW;

		MOTOR2_CONTROL(-(int)pulse_width_M2, actiononzero_2a, actiononzero_2b);
	}

}

int main() {
	/* Initialization of motor */
	MUXING_INITIALIZATION();

	/* Initialzation of IRSensor */
	initialization ();

	/* Motor 1 */
	MOTOR1_CONTROL((int)pulse_width_M1, actiononzero_1a, actiononzero_1b);

	/* Motor 2 */
	MOTOR2_CONTROL((int)pulse_width_M2, actiononzero_2a, actiononzero_2b);

	while (1)
	{
		/* Grasp results of left, middle and right sensors */
		char sensor_data = read_isrsensor();
		unsigned int left_sensor_data = sensor_data & (1 << 6);
		UARTprintf("Left sensor data: ");
		UARTPutNum(left_sensor_data);
		UARTprintf("\r\n");
		unsigned int middle_sensor_data = sensor_data & (1 << 5);
		UARTprintf("Middle sensor data: ");
		UARTPutNum(middle_sensor_data);
		UARTprintf("\r\n");
		unsigned int right_sensor_data = sensor_data & (1 << 4);
		UARTprintf("Right sensor data: ");
		UARTPutNum(right_sensor_data);
		UARTprintf("\r\n");

		if (left_sensor_data == 0 && middle_sensor_data != 0 && right_sensor_data != 0)
		{
			/* Should turn right */
			pulse_width_M1 += 50;
			pulse_width_M2 -= 30;

			set_motors(pulse_width_M1, pulse_width_M2);
		}
		else if (left_sensor_data == 0 && middle_sensor_data == 0 && right_sensor_data != 0)
		{
			/* Should turn right */
			pulse_width_M1 += 60;
			pulse_width_M2 -= 40;

			set_motors(pulse_width_M1, pulse_width_M2);
		}
		else if (left_sensor_data != 0 && middle_sensor_data != 0 && right_sensor_data == 0)
		{
			/* Should turn left */
			pulse_width_M1 -= 30;
			pulse_width_M2 += 50;

			set_motors(pulse_width_M1, pulse_width_M2);
		}
		else if (left_sensor_data != 0 && middle_sensor_data == 0 && right_sensor_data == 0)
		{
			/* Should turn left */
			pulse_width_M1 -= 40;
			pulse_width_M2 += 60;

			set_motors(pulse_width_M1, pulse_width_M2);
		}
		else if (left_sensor_data == 0 && middle_sensor_data == 0 && right_sensor_data == 0)
		{
			/* Backward */
			pulse_width_M1 = 10;
            pulse_width_M2 = 10;

			set_motors(pulse_width_M1, pulse_width_M2);

			/* Backward */
			pulse_width_M1 = -60;
            pulse_width_M2 = -60;

			set_motors(pulse_width_M1, pulse_width_M2);
		}
		else
		{
			/* Should keep forward */
			pulse_width_M1 = 80;
			pulse_width_M2 = 80;

			set_motors(pulse_width_M1, pulse_width_M2);
		}

		/* Binary output to screen */
	    UARTprintf(BYTETOBINARYPATTERN, BYTETOBINARY(read_isrsensor()));

	    UARTprintf("\r\n");
	}
	return 0;
}
