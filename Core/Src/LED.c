#include <LED.h>

LED RED = {15, GPIOA};	LED BLU = { 3, GPIOB};
LED YEL = { 4, GPIOB};	LED GRN = { 5, GPIOB};

void LED_Init		(LED *led)
{
    if (led->port == GPIOA) {RCC->IOPENR |= RCC_IOPENR_GPIOAEN;}
    else					{RCC->IOPENR |= RCC_IOPENR_GPIOBEN;}

    led->port->MODER &= ~(3U << (led->pin * 2));
    led->port->MODER |=  (1U << (led->pin * 2));
}

void LED_Enable		(LED *led)	{led->port->BSRR = (1U << led->pin);}
void LED_Disable	(LED *led)	{led->port->BSRR = (1U << (led->pin + 16));}
void LED_Toggle		(LED *led)	{led->port->ODR ^= (1U << led->pin);}
bool LED_Is_Work	(LED *led)	{return (led->port->IDR & (1U << led->pin));}
