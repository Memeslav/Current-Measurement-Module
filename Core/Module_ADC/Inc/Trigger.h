#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "stm32l053xx.h"

typedef struct
{
	int16_t 	upper_limit;
	int16_t  	lower_limit;
}
Trigger_t;

static inline void Trigger_set(Trigger_t *trigger, uint16_t level, uint16_t hysteresis)	{	trigger->upper_limit = level + hysteresis / 2;
																							trigger->lower_limit = level - hysteresis / 2;}

#endif
