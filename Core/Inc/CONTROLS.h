#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "stm32l053xx.h"

typedef struct
{
	uint16_t global_counter_lo;
	uint16_t global_counter_hi;

	uint16_t last_readed_lo;
	uint16_t last_readed_hi;

	uint16_t show_pulse_num_lo;
	uint16_t show_pulse_num_hi;
}
CONTROLS;

void Global_Counter_Increment(volatile CONTROLS* controls);

#endif
