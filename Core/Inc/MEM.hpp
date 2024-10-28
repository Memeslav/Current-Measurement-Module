#ifndef MEM_HPP_
#define MEM_HPP_

#include "stm32l053xx.h"

#define NUMBER_OF_REGISTERS	  32U

class MEMORY
{
	public:

		enum REGISTER_ADDRESS
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
		};

		struct UNIXTIME
		{
			uint16_t lo = 0;
			uint16_t hi = 0;
		};

		struct CURRENTS
		{
			int16_t max = 0;
			int16_t ave = 0;
			int16_t min = 0;
		};

		struct CONTROLS
		{
			uint16_t global_counter_lo 	= 0;
			uint16_t global_counter_hi 	= 0;
			uint16_t last_readed_lo 	= 0;
			uint16_t last_readed_hi 	= 0;
			uint16_t show_pulse_num_lo 	= 0;
			uint16_t show_pulse_num_hi 	= 0;
		};

		struct IMPULSE
		{
			uint16_t num_lo 		= 0;
			uint16_t num_hi 		= 0;
			uint16_t start_time_lo 	= 0;
			uint16_t start_time_hi 	= 0;
			uint16_t duration_lo 	= 0;
			uint16_t duration_hi 	= 0;
			int16_t max_amp 		= 0;
			int16_t ave_amp 		= 0;
		};

		struct SETTINGS
		{
			uint16_t minimal_width_lo 	= 5;
			uint16_t minimal_width_hi 	= 0;
			uint16_t measure_period 	= 1;
			int16_t trigger_level 		= 2000;
			uint16_t hysteresis 		= 200;
		};

		struct RESERVE
		{
			uint16_t num_1 	= 0;
			uint16_t num_2 	= 0;
		};

		struct CALIBRATION
		{
			uint16_t value 	= 1208;
		};

		struct MCU_DATA
		{
			uint16_t lsi_freq 		= 38000;
			int16_t mcu_temperature = 20;
			uint16_t msi_freq_lo 	= 0x0000;
			uint16_t msi_freq_hi 	= 0x0000;
		};

		struct PO_VERSION
		{
			uint16_t info 	= 108;
		};

		struct REGISTERS
		{
			UNIXTIME unixtime;
			CURRENTS currents;
			CONTROLS controls;
			IMPULSE impulse;
			SETTINGS settings;
			RESERVE reserve;
			CALIBRATION calibration;
			MCU_DATA mcu_data;
			PO_VERSION po_version;
		};
};

#endif
