#include "LED.hpp"

LED::LED(LED_STATE initState, LED_COLOR color, uint32_t port, uint32_t pin) : state(initState), color(color), port(port), pin(pin)
{
	RCC->IOPENR |= port;

	if		(port == RCC_IOPENR_GPIOAEN) {GPIOA->MODER = (GPIOA->MODER & ~(3U << (pin * 2))) | (1U << (pin * 2));}
	else if (port == RCC_IOPENR_GPIOBEN) {GPIOB->MODER = (GPIOB->MODER & ~(3U << (pin * 2))) | (1U << (pin * 2));}
}

void LED::on(void)
{
    if		(port == RCC_IOPENR_GPIOAEN) {GPIOA->BSRR = (1U << pin);}
    else if (port == RCC_IOPENR_GPIOBEN) {GPIOB->BSRR = (1U << pin);}

    state = ON;
}

void LED::off()
{
	if		(port == RCC_IOPENR_GPIOAEN) {GPIOA->BSRR = (1U << (pin + 16));}
	else if (port == RCC_IOPENR_GPIOBEN) {GPIOB->BSRR = (1U << (pin + 16));}

	state = OFF;
}

void LED::toggle()
{
	if(state == OFF) {on(); }
	else			 {off();}
}

LED::LED_COLOR LED::get_color(void) {return color;}
LED::LED_STATE LED::get_state(void) {return state;}
