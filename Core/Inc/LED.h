#ifndef LEDS_H_
#define LEDS_H_

#include "stdbool.h"
#include "stm32l053xx.h"

typedef enum
{
	RED = 0,
	BLU = 1,
	YEL = 2,
	GRN = 3,
}
LED_COLOUR;

typedef struct
{
	LED_COLOUR		color;

	uint16_t 		pin;
	GPIO_TypeDef	*port;
}
LED;

void LED_Init		(LED *led);

void LED_Enable		(LED *led);
void LED_Disable	(LED *led);
void LED_Toggle		(LED *led);

bool LED_Is_Work	(LED *led);

#endif
