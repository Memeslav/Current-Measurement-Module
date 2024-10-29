#ifndef CUR_H_
#define CUR_H_

#include "stm32l053xx.h"

typedef struct
{
	int16_t max;
	int16_t ave;
	int16_t min;
}
CURRENTS;

void Clear_Currents(CURRENTS* currents);

#endif
