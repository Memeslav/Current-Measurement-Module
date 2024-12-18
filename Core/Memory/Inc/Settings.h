#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "stm32l053xx.h"

typedef struct
{
	uint16_t minimal_width_lo;
	uint16_t minimal_width_hi;

	uint16_t measure_period;

	int16_t  trigger_level;
	uint16_t hysteresis;
}
Settings_t;

static inline uint32_t Minimal_Width_32b_Get(const Settings_t* settings)
{
    return ((uint32_t)settings->minimal_width_hi << 16) | settings->minimal_width_lo;
}

static inline void Settings_Reset_To_Default(Settings_t* settings)
{
    settings->minimal_width_lo = 5;
    settings->minimal_width_hi = 0;
    settings->measure_period = 1;
    settings->trigger_level = 2000;
    settings->hysteresis = 200;
}

#endif
