#include "main.hpp"

LEDS_CONTROLLER LEDS;

int main(void)
{
	LEDS.show_code(LEDS_CONTROLLER::MEASURE_RAN);
	LEDS.show_code(LEDS_CONTROLLER::IMPULSE_DETECTED);
	LEDS.show_code(LEDS_CONTROLLER::DATA_EXCHANGE);
	LEDS.show_code(LEDS_CONTROLLER::QUARTZ_LAUNCHING);

    while(1)
    {

    }
}
