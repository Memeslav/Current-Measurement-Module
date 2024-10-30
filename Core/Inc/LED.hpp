#ifndef LED_HPP_
#define LED_HPP_

#include "stm32l053xx.h"

class Led
{
	public:

	 	 enum class Color : uint8_t
		{
			RED = 0,
			BLU	= 1,
			GRN	= 2,
			YEL	= 3,
		};

	private:

		Color 			color;

	    GPIO_TypeDef* 	port;
	    uint32_t 		pin;

	public:

	    Led(Color color, GPIO_TypeDef* port, uint32_t pin);

	    Color 	get_Color() const;
	    bool 	get_State() const;

	    void 	on();
	    void 	off();
	    void 	toggle();
};

#endif
