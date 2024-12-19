#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "Register.h"

#define DEFAULT_SETTINGS_MIN_WIDT	5U
#define DEFAULT_SETTINGS_MEAS_PER	1U
#define DEFAULT_SETTINGS_TRIG_LVL	2000U
#define DEFAULT_SETTINGS_HSTERSIS	200U

typedef struct
{
	Register_32b_t minimal_impulse_duration;

	Register_16b_t measure_period;
	Register_16b_t trigger_level;
	Register_16b_t hysteresis;
}
Settings_t;

#endif
