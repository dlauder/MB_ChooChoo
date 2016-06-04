/*
 * SWI_Driver.c
 *
 *  Created on: 22 maj 2016
 *      Author: Dave
 */

#include "SWI_Driver.h"

struct SWI_Driver * Init_Switches()
{
	SWI_Driver_Instance = (struct SWI_Driver *)_malloc(sizeof(struct SWI_Driver));
	SWI_Driver_Instance->Switches = (XGpio *)_malloc(sizeof(XGpio));

	XGpio_Initialize(SWI_Driver_Instance->Switches, SWI_DEVICE_ID);

	XGpio_SetDataDirection(SWI_Driver_Instance->Switches, SWITCH_CHANNEL, ALL_INS);

	return(SWI_Driver_Instance);

}

int Read_Switches()
{
	return XGpio_DiscreteRead(SWI_Driver_Instance->Switches, SWITCH_CHANNEL);
}

