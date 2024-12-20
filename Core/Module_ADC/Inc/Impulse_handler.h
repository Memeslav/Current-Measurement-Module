#ifndef IMPULSE_HANDLER_H_
#define IMPULSE_HANDLER_H_

#include "Impulse.h"
#include "Trigger.h"

typedef struct
{
	Trigger_t 	trigger;
	uint32_t 	minimal_impulse_duration;
}
Impulse_handler_settings_t;

void Impulse_handler_settings_set(uint32_t minimal_duration, uint16_t trigger, uint16_t hysteresis);

typedef enum
{
	OUTSIDE_THE_IMPULSE,
	INSIDE_THE_IMPULSE,
	IMPULSE_IS_READY,
}
Impulse_measure_status;

typedef struct
{
	Impulse_measure_status status;

	int64_t average_currents_sum;
	int64_t number_of_measurements;

	Impulse_t impulse;
}
Impulse_handler_buffer_t;

static inline void Impulse_handler_buffer_clear(Impulse_handler_buffer_t* buffer) {*buffer = (Impulse_handler_buffer_t){0};}



#endif
