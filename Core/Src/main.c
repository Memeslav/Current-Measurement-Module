#include "main.h"

LED leds[LEDS_COUNT];

int main(void)
{
	LED_Init(&leds[RED], RED);
	LED_Init(&leds[BLU], BLU);
	LED_Init(&leds[YEL], YEL);
	LED_Init(&leds[GRN], GRN);

    while (1)
    {
        LED_Toggle(&leds[RED]);
    	for(int i = 0; i < 100000; i++);
        LED_Toggle(&leds[BLU]);
    	for(int i = 0; i < 100000; i++);
        LED_Toggle(&leds[YEL]);
    	for(int i = 0; i < 100000; i++);
        LED_Toggle(&leds[GRN]);
    	for(int i = 0; i < 100000; i++);
    }
}
