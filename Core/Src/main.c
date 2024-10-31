#include "main.h"

LED led_1 = {RED, 15, GPIOA};
LED led_2 = {BLU,  3, GPIOB};
LED led_3 = {YEL,  4, GPIOB};
LED led_4 = {GRN,  5, GPIOB};

int main(void)
{
	LED_Init(&led_1);
	LED_Init(&led_2);
	LED_Init(&led_3);
	LED_Init(&led_4);

	LED_Enable(&led_1);
	LED_Enable(&led_2);
	LED_Enable(&led_3);
	LED_Enable(&led_4);

    while (1)
    {

    }
}
