#ifndef LED_H_
#define LED_H_

#include "stdbool.h"
#include "stm32l053xx.h"

typedef struct	{	uint16_t 		pin;
					GPIO_TypeDef	*port;	}
LED;

void LED_Init		(LED *led);
void LED_Enable		(LED *led);
void LED_Disable	(LED *led);
void LED_Toggle		(LED *led);
bool LED_Is_Work	(LED *led);

extern LED RED;	extern LED BLU;
extern LED YEL;	extern LED GRN;

#endif
