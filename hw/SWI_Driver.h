/*
 * SWI_Driver.h
 *
 *  Created on: 22 maj 2016
 *      Author: Dave
 */

#ifndef SRC_HW_SWI_DRIVER_H_
#define SRC_HW_SWI_DRIVER_H_

#include "xgpio.h"
#include "..\memory\heap.h"

#define SWI_DEVICE_ID	0
#define SWITCH_CHANNEL	1
#define ALL_INS			0xFFFFFFFF

struct SWI_Driver
{
	XGpio * Switches;

};

struct SWI_Driver * SWI_Driver_Instance;

struct SWI_Driver * Init_Switches();
int Read_Switches();

#endif /* SRC_HW_SWI_DRIVER_H_ */
