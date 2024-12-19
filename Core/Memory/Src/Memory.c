#include "Memory.h"

volatile	Register_map_t 		registers 		= {0};
volatile 	Impulse_archive_t 	impulse_archive = {0};

void Memory_Init(void)
{
	registers 		= (Register_map_t)		{0};
	impulse_archive = (Impulse_archive_t)	{0};

	Register_32b_Set(&registers.settings.minimal_impulse_duration, 	DEFAULT_SETTINGS_MIN_WIDT);
	Register_16b_Set(&registers.settings.measure_period, 			DEFAULT_SETTINGS_MEAS_PER);
	Register_16b_Set(&registers.settings.trigger_level, 			DEFAULT_SETTINGS_TRIG_LVL);
	Register_16b_Set(&registers.settings.hysteresis, 				DEFAULT_SETTINGS_HSTERSIS);

	Register_16b_Set(&registers.calibration, 						DEFAULT_CALIBRATION_VALUE);
}
