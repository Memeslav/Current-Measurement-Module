#include "LEDS.h"

void Set_Pin(uint16_t pin, GPIO_TypeDef *port, LED_STATUS state)
{
    if (state == on) {port->BSRR |= pin;}
    else 			 {port->BSRR |= (pin << 16);}
}

void LED_Init(LED *led, LED_COLOUR color)
{
    led->color = color;
    led->status = off;

    switch (color)
    {
        case RED:
            led->port = GPIOA;
            led->pin = GPIO_BSRR_BS_15;
            RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
            break;

        case BLU:
            led->port = GPIOB;
            led->pin = GPIO_BSRR_BS_3;
            RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
            break;

        case YEL:
            led->port = GPIOB;
            led->pin = GPIO_BSRR_BS_4;
            RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
            break;

        case GRN:
            led->port = GPIOB;
            led->pin = GPIO_BSRR_BS_5;
            RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
            break;
    }

    led->port->MODER &= ~(3 << (led->pin * 2));
    led->port->MODER |= (1 << (led->pin * 2));

    led->set = Set_Pin;
}


void LED_Set(LED *led, LED_STATUS state)
{
    if (led->status != state)
    {
        led->set(led->pin, led->port, state);
        led->status = state;
    }
}

void LED_Toggle(LED *led)
{
    LED_Set(led, led->status == off ? on : off);
}
