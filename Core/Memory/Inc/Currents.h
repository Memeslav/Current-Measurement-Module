#ifndef CURRENTS_H_
#define CURRENTS_H_

#include "stm32l053xx.h"

typedef struct
{
	int16_t max;
	int16_t ave;
	int16_t min;
}
Currents_t;

static inline void Currents_Clear (Currents_t* currents)
{
	*currents = (Currents_t){0};
}

#endif
