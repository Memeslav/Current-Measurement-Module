#include "LED.hpp"

Led::Led(Color color, GPIO_TypeDef* port, uint32_t pin) : color(color), port(port), pin(pin)
{
    if (port == GPIOA)	{RCC->IOPENR |= RCC_IOPENR_GPIOAEN;}
    else				{RCC->IOPENR |= RCC_IOPENR_GPIOBEN;}

    port->MODER = (port->MODER & ~(3U << (pin * 2))) | (1U << (pin * 2));
}

Led::Color Led::get_Color() const	{return color;}

bool Led::get_State() 		const	{return (port->ODR & (1U << pin)) != 0;}

void Led::on()		{port->BSRR = (1U << pin);}

void Led::off()		{port->BSRR = (1U << (pin + 16));}

void Led::toggle()	{port->ODR ^= (1U << pin);}
