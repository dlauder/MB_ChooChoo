/*
 * LED_Driver.c
 *
 *  Created on: 22 maj 2016
 *      Author: Dave
 */


#include "LED_Driver.h"

struct LED_Driver * Init_Leds()
{
	LED_Driver_Instance = (struct LED_Driver *)_malloc(sizeof(struct LED_Driver));
	LED_Driver_Instance->LEDS = (XGpio *)_malloc(sizeof(XGpio));

	XGpio_Initialize(LED_Driver_Instance->LEDS, GPIO_DEVICE_ID);

	XGpio_SetDataDirection(LED_Driver_Instance->LEDS, LED_CHANNEL, ALL_OUTS);

	return(LED_Driver_Instance);
}

void Write_LEDS(int Value)
{
	XGpio_DiscreteWrite(LED_Driver_Instance->LEDS, LED_CHANNEL, Value);
}


