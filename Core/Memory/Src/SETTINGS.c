#include "SETTINGS.h"

void Settings_Reset_to_Default(SETTINGS* settings)
{
	settings->minimal_width_lo	= 5;
	settings->minimal_width_hi	= 0;

	settings->measure_period	= 1;

	settings->trigger_level		= 2000;
	settings->hysteresis		= 200;
}
