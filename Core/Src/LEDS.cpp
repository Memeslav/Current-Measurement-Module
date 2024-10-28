#include "LEDS.hpp"

LEDS_CONTROLLER::LEDS_CONTROLLER() : LEDS  {LED(LED::OFF, LED::RED, RCC_IOPENR_GPIOAEN, 15),
    										LED(LED::OFF, LED::BLU, RCC_IOPENR_GPIOBEN,  3),
											LED(LED::OFF, LED::YEL, RCC_IOPENR_GPIOBEN,  4),
											LED(LED::OFF, LED::GRN, RCC_IOPENR_GPIOBEN,  5)} {}

void LEDS_CONTROLLER::turn_all_on(void)
{
    for (uint8_t i = 0; i < LEDS_COUNT; ++i) {LEDS[i].on();}
}

void LEDS_CONTROLLER::turn_all_off(void)
{
    for (uint8_t i = 0; i < LEDS_COUNT; ++i) {LEDS[i].off();}
}

void LEDS_CONTROLLER::toggle_all(void)
{
    for (uint8_t i = 0; i < LEDS_COUNT; ++i) {LEDS[i].toggle();}
}
