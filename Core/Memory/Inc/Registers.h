#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "Unixtime.h"
#include "Currents.h"
#include "Controls.h"
#include "Impulse.h"
#include "Settings.h"
#include "Reserve.h"
#include "Calibration.h"
#include "MCU_data.h"
#include "Firmware_version.h"

typedef enum
{
	UNIXTIME = 0,
	//============
	MAX_CURR = 2,
	AVE_CURR = 3,
	MIN_CURR = 4,
	//============
	GLBL_CNT = 5,
	LST_READ = 7,
	SHW_PULS = 9,
	//============
	PULS_NUM = 11,
	TIM_STRT = 13,
	CONTINIS = 15,
	MAX_AMPL = 17,
	AVE_AMPL = 18,
	//============
	MIN_WIDT = 19,
	MEAS_PER = 21,
	TRIG_LVL = 22,
	HSTERSIS = 23,
	//============
	RESERVED = 24,
	//============
	CALIB_PR = 26,
	//============
	LSI_FREQ = 27,
	MCU_TEMP = 28,
	MSI_FREQ = 29,
	//============
	PROG_VER = 31,
}
Register_address;

typedef struct
{
	Unixtime_t		unixtime;
	Currents_t 		currents;
	Controls_t 		controls;
	Impulse_t		impulse;
	Settings_t		settings;
	Reserve_t		reserve;
	Calibration_t	calibration;
	MCU_data_t		mcu_data;
	FM_version_t	version;
}
Register_map_t;

#endif
