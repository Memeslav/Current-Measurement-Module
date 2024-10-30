#include "LEDS.hpp"

LEDS::LEDS(void) : Leds
{
        {Led::Color::RED, GPIOA, 15},
        {Led::Color::BLU, GPIOB,  3},
        {Led::Color::YEL, GPIOB,  4},
        {Led::Color::GRN, GPIOB,  5},
}{}

void LEDS::turn_all_on(void)	{for (auto& led : Leds)	{led.on(); }}

void LEDS::turn_all_off(void)	{for (auto& led : Leds)	{led.off();}}

void LEDS::show_code(uint8_t code)
{
    turn_all_off();

    for (uint8_t i = 0; i < LEDS_COUNT; ++i)
    {
        if (code & (1U << i)) {Leds[i].on();}
    }
}
