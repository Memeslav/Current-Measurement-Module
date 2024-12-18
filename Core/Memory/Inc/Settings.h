#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "Register.h"

typedef struct
{
	Register_32b_t minimal_impulse_duration;

	Register_16b_t measure_period;
	Register_16b_t trigger_level;
	Register_16b_t hysteresis;
}
Settings_t;

#endif
