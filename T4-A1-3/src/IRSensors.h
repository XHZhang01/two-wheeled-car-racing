/*
 * IRSensor.h
 * Created on 30.08.2021
 * Author: Xuhui Zhang
 */

#ifndef IRSensor_H_
#define IRSensor_H_

#include <hw_types.h>
#include <hw_hsi2c.h>
#include <soc_AM335x.h>
#include <interrupt.h>
#include <hw_cm_per.h>
#include <hw_control_AM335x.h>
#include "delay_ms.h"
#include "i2c.h"
#include <uartStdio.h>

extern void initialization ();

extern char read_isrsensor();

#endif IRSensor_H_
