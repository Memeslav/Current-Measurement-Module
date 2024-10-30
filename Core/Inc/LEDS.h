#ifndef LEDS_H_
#define LEDS_H_

#include "stm32l053xx.h"

#define LEDS_COUNT 4U

typedef enum
{
	RED = 0,
	BLU = 1,
	YEL = 2,
	GRN = 3,
}
LED_COLOUR;

typedef enum
{
	off		= 0,
	on		= 1,
}
LED_STATUS;

typedef struct
{
	uint16_t 		pin;
	GPIO_TypeDef	*port;

	LED_COLOUR		color;
	LED_STATUS		status;

    void (*set)		(uint16_t, GPIO_TypeDef*, LED_STATUS);
}
LED;

void LED_Init(LED *led, LED_COLOUR color);
void LED_Set(LED *led, LED_STATUS state);
void LED_Toggle(LED *led);

#endif
