#include "Impulse_handler.h"

static Impulse_handler_settings_t 	settings 	= {0};
static Impulse_handler_buffer_t 	buffer 		= {0};

void Impulse_handler_settings_set(uint32_t minimal_duration, uint16_t trigger, uint16_t hysteresis)
{
	settings.minimal_impulse_duration = minimal_duration;
	Trigger_set(&settings.trigger, trigger, hysteresis);
}

