#ifndef IMPULSE_H_
#define IMPULSE_H_

#include "ID.h"
#include "Unixtime.h"
#include "ADC_Level.h"

typedef struct	{	ID id;

					Unixtime_t start;
					Unixtime_t end;

					ADC_Level_t maximal;
					ADC_Level_t average;	}	Impulse_t;

static inline void Impulse_Clear (Impulse_t* impulse) {*impulse = (Impulse_t){0};}

#endif
