#ifndef LEDS_H_
#define LEDS_H_

#include "stm32l053xx.h"

typedef enum
{
	RED = 0,
	BLU = 1,
	YEL = 2,
	GRN = 3,
}
LED_COLOUR;

void LED_Enable 	(LED_COLOUR led_colour);
void LED_Disable	(LED_COLOUR led_colour);
void LED_Toggle		(LED_COLOUR led_colour);

#endif
