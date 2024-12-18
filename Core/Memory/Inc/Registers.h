#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "Unixtime.h"
#include "Currents.h"
#include "Controls.h"


#include "Impulse.h"
#include "Register.h"



#include "Settings.h"
#include "MCU_data.h"

typedef struct
{
	Unixtime_t	unixtime;
	Currents_t 	currents;
	Controls_t 	controls;

	IMPULSE			impulse;
	SETTINGS		settings;

	Register_32b_t	reserved;
	Register_16b_t	calibration;

	MCU_DATA 		mcu_data;

	Register_16b_t	po_version;
}
REGISTERS;

#endif
