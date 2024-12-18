#ifndef UNIXTIME_H_
#define UNIXTIME_H_

#include "stm32l053xx.h"

typedef	struct	{uint16_t lo; uint16_t hi;}	Unixtime_t;

static inline uint32_t Unixtime_32b_Get (const Unixtime_t* unixtime)
{
	return ((uint32_t)unixtime->hi << 16) | unixtime->lo;
}

static inline void Unixtime_32b_Set (Unixtime_t* unixtime, uint32_t value)
{
	unixtime->lo = (uint16_t)(value & 0xFFFF);
	unixtime->hi = (uint16_t)((value >> 16) & 0xFFFF);
}

static inline void Unixtime_32b_Increment (Unixtime_t* unixtime)
{
	uint32_t value = Unixtime_32b_Get(unixtime);
	value++; Unixtime_32b_Set(unixtime, value);
}

#endif
