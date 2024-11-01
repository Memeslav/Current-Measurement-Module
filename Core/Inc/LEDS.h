#ifndef LEDS_H_
#define LEDS_H_

#include "stm32l053xx.h"
#include "LED.h"

#define LEDS_COUNT	4

typedef enum	{	CODE_0	= 0b0000,
					CODE_1	= 0b0001,
					CODE_2  = 0b0010,
					CODE_3	= 0b0011,
					CODE_4  = 0b0100,
					CODE_5	= 0b0101,
					CODE_6  = 0b0110,
					CODE_7	= 0b0111,
					CODE_8  = 0b1000,
					CODE_9	= 0b1001,
					CODE_10 = 0b1010,
					CODE_11	= 0b1011,
					CODE_12 = 0b1100,
					CODE_13	= 0b1101,
					CODE_14 = 0b1110,
					CODE_15	= 0b1111,	}
LEDS_CODE;

typedef struct	{	LED* array[LEDS_COUNT];}
LEDS_CONTROLLER;

void LEDS_CONTROLLER_Init(LEDS_CONTROLLER *LEDS);
void LEDS_Show_Code(LEDS_CODE code);
void LEDS_Enable_All(void);
void LEDS_Disable_All(void);

extern LEDS_CONTROLLER LEDS;

#endif
