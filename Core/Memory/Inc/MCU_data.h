#ifndef MCU_DATA_H_
#define MCU_DATA_H_

#include "stm32l053xx.h"

typedef struct
{
	Register_16b_t lsi_freq;
	Register_16b_t mcu_temperature;
	Register_32b_t msi_freq;
}
MCU_data_t;

static	inline	void	MCU_data_Clear	(MCU_data_t* mcu_data)	{*mcu_data = (MCU_data_t){0};}

#endif
