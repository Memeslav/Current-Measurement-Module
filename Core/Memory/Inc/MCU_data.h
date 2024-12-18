#ifndef MCU_DATA_H_
#define MCU_DATA_H_

#include "stm32l053xx.h"

typedef struct
{
	Register_16b_t	lsi_freq;
	Register_16b_t	mcu_temperature;
	Register_32b_t	msi_freq;
}
MCU_DATA;

static	inline	void	MCU_data_Clear	(MCU_DATA* mcu_data)	{*mcu_data = (MCU_DATA){0};}

#endif
