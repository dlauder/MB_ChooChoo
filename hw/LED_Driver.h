/*
 * LED_Driver.h
 *
 *  Created on: 22 maj 2016
 *      Author: Dave
 */
#ifndef SRC_HW_LED_DRIVER_H_
#define SRC_HW_LED_DRIVER_H_

#include "xparameters.h"
#include "xgpio.h"
#include "..\memory\heap.h"

#define GPIO_DEVICE_ID	XPAR_GPIO_0_DEVICE_ID
#define LED_CHANNEL		2
#define ALL_OUTS 		0x00000000

struct LED_Driver
{
	XGpio * LEDS;

};

struct LED_Driver * LED_Driver_Instance;

struct LED_Driver * Init_Leds();
void Write_LEDS(int Value);

#endif /* SRC_HW_LED_DRIVER_H_ */
