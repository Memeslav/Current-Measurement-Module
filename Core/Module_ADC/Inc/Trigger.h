#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "ADC_Level.h"

typedef struct
{
	ADC_Level_t	upper_limit;
	ADC_Level_t	lower_limit;
}
Trigger_t;

static inline void Trigger_Set	(	Trigger_t *trigger,
									ADC_Level_t value,
									ADC_Level_t hysteresis)	{	trigger->upper_limit = value + hysteresis / 2;
																trigger->lower_limit = value - hysteresis / 2;}

#endif
