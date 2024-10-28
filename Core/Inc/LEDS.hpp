#ifndef LEDS_CONTROLLER_HPP_
#define LEDS_CONTROLLER_HPP_

#include "stm32l053xx.h"

#include "LED.hpp"

#define LEDS_COUNT	4U

class LEDS_CONTROLLER
{
	private:

		LED LEDS[LEDS_COUNT];

	public:

		LEDS_CONTROLLER();

		void turn_all_on (void);
		void turn_all_off(void);

		void toggle_all  (void);
};

#endif
