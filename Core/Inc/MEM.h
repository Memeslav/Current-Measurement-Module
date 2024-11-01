#ifndef MEMORY_H_
#define MEMORY_H_

#include "stm32l053xx.h"

#include "UNIXTIME.h"
#include "CUR.h"
#include "CONTROLS.h"
#include "IMP.h"
#include "SETTINGS.h"
#include "RESERVE.h"
#include "CALIBRATION.h"
#include "MCU_DATA.h"
#include "PO_VERSION.h"

#include "IMP_ARCHIVE.h"

#define NUMBER_OF_REGISTERS	  32


typedef enum
{
	UNIXTIME_L,
	UNIXTIME_H,
	//=========
	MAX_CURR,
	AVE_CURR,
	MIN_CURR,
	//=========
	GLBL_CNT_L,
	GLBL_CNT_H,
	LST_READ_L,
	LST_READ_H,
	SHW_PULS_L,
	SHW_PULS_H,
	//=========
	PULS_NUM_L,
	PULS_NUM_H,
	TIM_STRT_L,
	TIM_STRT_H,
	CONTINIS_L,
	CONTINIS_H,
	MAX_AMPL,
	AVE_AMPL,
	//=========
	MIN_WIDT_L,
	MIN_WIDT_H,
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
	MSI_FREQ_L,
	MSI_FREQ_H,
	//=========
	PROG_VER,
}
REGISTER_ADDRESS;

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

#endif
