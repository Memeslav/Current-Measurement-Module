#ifndef LED_HPP_
#define LED_HPP_

#include "stm32l053xx.h"

class LED
{
	public:

		enum LED_STATE
		{
			OFF,
			 ON,
		};

		enum LED_COLOR
		{
			RED,
			BLU,
			GRN,
			YEL,
		};

	private:

		LED_STATE state;
		LED_COLOR color;

		uint32_t   port;
		uint32_t    pin;

	public:

		LED(LED_STATE state,
			LED_COLOR color,
			uint32_t  port,
			uint32_t  pin);

		LED_COLOR get_color(void);
		LED_STATE get_state(void);

		void on		(void);
		void off	(void);
		void toggle	(void);
};

#endif
