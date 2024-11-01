#include "LEDS.h"

LEDS_CONTROLLER LEDS = {{&RED, &BLU, &YEL, &GRN}};

void LEDS_CONTROLLER_Init(LEDS_CONTROLLER *LEDS)	{for(uint8_t i = 0; i < LEDS_COUNT; i++){LED_Init(LEDS->array[i]);}}

void LEDS_Enable_All(void)	{for (int i = 0; i < LEDS_COUNT; i++) {LED_Enable( LEDS.array[i]);}}
void LEDS_Disable_All(void)	{for (int i = 0; i < LEDS_COUNT; i++) {LED_Disable(LEDS.array[i]);}}

void LEDS_Show_Code(LEDS_CODE code)
{
    for (int i = 0; i < LEDS_COUNT; i++)
    {
        if (code & (1 << (LEDS_COUNT - 1 - i)))	{LED_Enable (LEDS.array[i]);}
        else									{LED_Disable(LEDS.array[i]);}
    }
}
