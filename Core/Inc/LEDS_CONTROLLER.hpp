#ifndef LEDS_CONTROLLER_HPP_
#define LEDS_CONTROLLER_HPP_

#include "stm32l053xx.h"

#include "LED.hpp"

class LEDS_CONTROLLER
{
	private:

		LED* LEDS;
		uint8_t LEDS_COUNT;

	public:

		LEDS_CONTROLLER(LED* LEDS, uint8_t LEDS_COUNT);

		void turn_all_on (void);
		void turn_all_off(void);

		void toggle_all  (void);
};

#endif
