#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "Register.h"

typedef enum
{
	UNIXTIME,
	//=========
	MAX_CURR,
	AVE_CURR,
	MIN_CURR,
	//=========
	GLBL_CNT,
	LST_READ,
	SHW_PULS,
	//=========
	PULS_NUM,
	TIM_STRT,
	CONTINIS,
	MAX_AMPL,
	AVE_AMPL,
	//=========
	MIN_WIDT,
	MEAS_PER,
	TRIG_LVL,
	HSTERSIS,
	//=========
	RESERVED_0,
	RESERVED_1,
	//=========
	CALIB_PR,
	//=========
	LSI_FREQ,
	MCU_TEMP,
	//=========
	MSI_FREQ,
	//=========
	PROG_VER,
}
REGISTER_ADDRESS;

typedef struct
{
	Register_32b_t unixtime;
}
REGISTERS;

/*
typedef struct
{
	UNIXTIME 		unixtime;
	CURRENTS 		currents;
	CONTROLS 		controls;
	IMPULSE	 		impulse;
	SETTINGS 		settings;
	RESERVE			reserve;
	CALIBRATION		calibration;
	MCU_DATA		mcu_data;
	PO_VERSION		po_version;
}
REGISTERS;

extern volatile REGISTERS registers;
extern uint16_t* regs;
*/


#endif
