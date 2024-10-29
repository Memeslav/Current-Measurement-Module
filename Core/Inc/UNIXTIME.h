#ifndef UNIXTIME_H_
#define UNIXTIME_H_

#include "stm32l053xx.h"

typedef struct
{
	uint16_t lo;
	uint16_t hi;
}
UNIXTIME;

void Unixtime_Increment(UNIXTIME* unixtime);

#endif
