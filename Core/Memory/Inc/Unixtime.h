#ifndef UNIXTIME_H_
#define UNIXTIME_H_

#include "stm32l053xx.h"


typedef	union	{struct{uint16_t low; uint16_t high;}; uint32_t full;} Unixtime_t;

static	inline	uint32_t	Unixtime_32b_Get	(const Unixtime_t* unixtime)			{return unixtime->full;}
static	inline	void 		Unixtime_32b_Set	(Unixtime_t* unixtime, uint32_t value)	{unixtime->full = value;}

static	inline	void		Unixtime_32b_Increment	(Unixtime_t* unixtime) 	{unixtime->full++;}

#endif
