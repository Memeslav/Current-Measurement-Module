#ifndef LEDS_CONTROLLER_HPP_
#define LEDS_CONTROLLER_HPP_

#include "stm32l053xx.h"

#include "LED.hpp"

#define LEDS_COUNT	4U

class LEDS_CONTROLLER
{
	public:

		enum LEDS_CODE
		{
			MEASURE_RAN			= 0b1000,
			IMPULSE_DETECTED	= 0b0100,
			DATA_EXCHANGE		= 0b0010,
			QUARTZ_LAUNCHING	= 0b0001,
		};

	private:

		LED LEDS[LEDS_COUNT];

	public:

		LEDS_CONTROLLER();

		void turn_all_on (void);
		void turn_all_off(void);

		void toggle_all  (void);

		void show_code	 (uint8_t code);
};

#endif
