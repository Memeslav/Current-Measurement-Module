#include "Memory.h"

volatile	REGISTERS 	registers 	= {0};
			uint16_t* 	regs 		= (uint16_t*)&registers;

volatile 	IMPULSE_ARCHIVE 	impulse_archive = {0};
			uint16_t* 			impulses 		= (uint16_t*)&impulse_archive;

void Memory_Init(void)
{
	//------------------------------------------------
	registers.unixtime.full 				=       0;
	//------------------------------------------------
//	registers.currents.max 					=       0;
//	registers.currents.ave 					=       0;
//	registers.currents.min 					=       0;
	//------------------------------------------------
//	registers.controls.global_counter.full 	=       0;
//	registers.controls.last_readed.full 	=       0;
//	registers.controls.show_pulse.full 		=       0;
	//------------------------------------------------
//	registers.impulse.num.full 				=       0;
//	registers.impulse.start_time.full		=       0;
//	registers.impulse.duration.full 		=       0;
//	registers.impulse.max_amp 				=       0;
//	registers.impulse.ave_amp 				=       0;
	//------------------------------------------------
//	registers.settings.minimal_width.full	=       5;
//	registers.settings.measure_period 		=       1;
//	registers.settings.trigger_level 		=    2000;
//	registers.settings.hysteresis 			=     200;
	//------------------------------------------------
	registers.reserved.full 				=       0;
	//------------------------------------------------
	registers.calibration 					=    1208;
	//------------------------------------------------
//	registers.mcu_data.lsi_freq 			=   38000;
//	registers.mcu_data.mcu_temperature		= 	   20;
//	registers.mcu_data.msi_freq.full 		= 2097152;
	//------------------------------------------------
	registers.firmware_version 				= 	  110;
	//------------------------------------------------
}
