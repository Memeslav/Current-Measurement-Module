#include "LEDS_CONTROLLER.hpp"

LEDS_CONTROLLER::LEDS_CONTROLLER(LED* LEDS, uint8_t LEDS_COUNT) : LEDS(LEDS), LEDS_COUNT(LEDS_COUNT) {}

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
