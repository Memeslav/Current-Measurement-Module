#ifndef IMPULSE_H_
#define IMPULSE_H_

#include "stm32l053xx.h"

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

static	inline	void	Impulse_Clear	(IMPULSE* impulse)	{*impulse = (IMPULSE){0};}

#endif
