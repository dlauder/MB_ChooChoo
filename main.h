/*
 * main.h
 *
 *  Created on: 21 maj 2016
 *      Author: Dave
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <stdio.h>

#include "platform\platform.h"
#include "xil_printf.h"

//#include "xparameters.h"
//#include "xgpio.h"

#include "memory\heap.h"
#include "hw\LED_Driver.h"
#include "hw\SWI_Driver.h"

struct thisPlatform
{
	XGpio * SWI_Driver;
	struct LED_Driver * LED_Driver;
};

//#define GPIO_DEVICE_ID	XPAR_GPIO_0_DEVICE_ID
//#define SWITCH_CHANNEL	1
//#define LED_CHANNEL		2

//#define ALL_OUTS 		0x00000000
//#define ALL_INS			0xFFFFFFFF

struct thisPlatform * me;

//void Init_Switches(XGpio * );
//void Init_Leds(XGpio *);
//int Read_Switches(XGpio * SWI_Driver);
//void Write_LEDS(XGpio * LED_Driver, int Value);

#endif /* SRC_MAIN_H_ */
