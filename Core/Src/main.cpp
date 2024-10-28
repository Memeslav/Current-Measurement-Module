#include "main.hpp"

LEDS_CONTROLLER LEDS;

int main(void)
{
	LEDS.turn_all_on();

    while(1)
    {
    	for(uint8_t code = 0; code < 16; code++)
    	{
    		LEDS.show_code(code);
    		for(int i = 0; i < 50000; i++);
    	}
    }
}
