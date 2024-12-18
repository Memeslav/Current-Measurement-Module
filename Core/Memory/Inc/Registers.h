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

	CURRENTS 		currents;
	CONTROLS 		controls;
	IMPULSE			impulse;
	SETTINGS		settings;

	Register_32b_t	reserved;
	Register_16b_t	calibration;

	MCU_DATA 		mcu_data;

	Register_16b_t	po_version;
}
REGISTERS;

#endif
