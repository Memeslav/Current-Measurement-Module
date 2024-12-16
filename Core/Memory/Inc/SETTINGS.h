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
SETTINGS;

void Settings_Reset_to_Default(SETTINGS* settings);

#endif
