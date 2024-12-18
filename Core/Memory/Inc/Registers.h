#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <Impulse.h>
#include "Register.h"

#include "Currents.h"
#include "Controls.h"

#include "Settings.h"
#include "MCU_data.h"

typedef struct
{
	Register_32b_t	unixtime;

	Register_16b_t	maximal_current;
	Register_16b_t	average_current;
	Register_16b_t	minimal_current;

	Register_32b_t 	global_impulse_counter;
	Register_32b_t 	last_read_impulse_number;
	Register_32b_t 	show_impulse_number;

	Register_32b_t	impulse_number;
	Register_32b_t	impulse_time_start;
	Register_32b_t	impulse_duration;
	Register_16b_t	impulse_maximal_amplitude;
	Register_16b_t	impulse_average_amplitude;

	Register_32b_t	minimal_impulse_width;
	Register_16b_t	measure_period;
	Register_16b_t	trigger_level;
	Register_16b_t  hysteresis;

	Register_32b_t 	reserved;

	Register_16b_t	calibration;

	Register_16b_t	lsi_frequency;
	Register_16b_t	mcu_temperature;
	Register_32b_t 	msi_frequency;

	Register_16b_t	firmware_version;
}
REGISTERS;

#endif
