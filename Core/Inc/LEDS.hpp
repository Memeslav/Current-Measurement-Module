#ifndef LEDS_CONTROLLER_HPP_
#define LEDS_CONTROLLER_HPP_

#include "LED.hpp"

#define LEDS_COUNT 4U

class LEDS
{
	public:

		LEDS(void);

		enum LEDS_CODE : uint8_t
		{
			MEASURE_RAN         = 0b1000,
			IMPULSE_DETECTED    = 0b0100,
			DATA_EXCHANGE       = 0b0010,
			QUARTZ_LAUNCHING    = 0b0001,
		};

		Led Leds[LEDS_COUNT];

		void turn_all_on (void);
		void turn_all_off(void);

		void show_code(uint8_t code);
};


#endif
