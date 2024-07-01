#ifndef MEMORY_H_
#define MEMORY_H_

#include <string.h>
#include "stm32l053xx.h"

#define NUMBER_OF_REGISTERS	  32
#define IMPULSE_ARCHIVE_SIZE 128

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
	uint16_t lo;
	uint16_t hi;
}
UNIXTIME;
typedef struct
{
	int16_t max;
	int16_t ave;
	int16_t min;
}
CURRENTS;
typedef struct
{
	uint16_t global_counter_lo;
	uint16_t global_counter_hi;

	uint16_t last_readed_lo;
	uint16_t last_readed_hi;

	uint16_t show_pulse_num_lo;
	uint16_t show_pulse_num_hi;
}
CONTROLS;
typedef struct
{
	uint16_t num_lo;
	uint16_t num_hi;

	uint16_t start_time_lo;
	uint16_t start_time_hi;

	uint16_t duration_lo;
	uint16_t duration_hi;

	int16_t max_amp;
	int16_t ave_amp;
}
IMPULSE;
typedef struct
{
	uint16_t minimal_width_lo;
	uint16_t minimal_width_hi;

	uint16_t measure_period;

	int16_t  trigger_level;
	uint16_t hysteresis;
}
SETTINGS;
typedef struct
{
	uint16_t num_1;
	uint16_t num_2;
}
RESERVE;
typedef struct
{
	uint16_t value;
}
CALIBRATION;
typedef struct
{
	uint16_t lsi_freq;
	int16_t  mcu_temperature;
	uint16_t msi_freq_lo;
	uint16_t msi_freq_hi;
}
MCU_DATA;
typedef struct
{
	uint16_t info;
}
PO_VERSION;

typedef struct
{
	UNIXTIME 	unixtime;
	CURRENTS 	currents;
	CONTROLS 	controls;
	IMPULSE	 	impulse;
	SETTINGS 	settings;
	RESERVE		reserve;
	CALIBRATION	calibration;
	MCU_DATA	mcu_data;
	PO_VERSION	po_version;
}
REGISTERS;
typedef struct
{
	IMPULSE impulse[IMPULSE_ARCHIVE_SIZE];
}
IMPULSE_ARCHIVE;

extern volatile REGISTERS registers;
extern uint16_t* regs;

extern volatile IMPULSE_ARCHIVE impulse_archive;
extern uint16_t* impulses;

void MSI_set_max_frequency(void);
void MSI_set_min_frequency(void);

#endif
