#ifndef MCU_DATA_H_
#define MCU_DATA_H_

#include "stm32l053xx.h"

typedef struct
{
	uint16_t lsi_freq;
	int16_t  mcu_temperature;
	uint16_t msi_freq_lo;
	uint16_t msi_freq_hi;
}
MCU_DATA;

static	inline	void	MCU_data_Clear	(MCU_DATA* mcu_data)	{*mcu_data = (MCU_DATA){0};}

#endif
