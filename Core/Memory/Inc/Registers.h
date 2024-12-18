#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "Unixtime.h"
#include "Currents.h"
#include "Controls.h"
#include "Impulse.h"
#include "Settings.h"
#include "Reserve.h"
#include "Calibration.h"

#include "Register.h"

#include "MCU_data.h"

typedef struct
{
	Unixtime_t		unixtime;
	Currents_t 		currents;
	Controls_t 		controls;
	Impulse_t		impulse;
	Settings_t		settings;
	Reserve_t		reserve;
	Calibration_t	calibration;

	MCU_DATA 		mcu_data;

	Register_16b_t	po_version;
}
REGISTERS;

#endif
