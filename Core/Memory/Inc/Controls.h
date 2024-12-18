#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "stm32l053xx.h"

typedef	union	{struct{uint16_t low; uint16_t high;}; uint32_t full;} Counter_t;

static	inline	uint32_t	Counter_32b_Get			(const Counter_t* counter) 				{return counter->full;}
static	inline	void 		Counter_32b_Set			(Counter_t* counter, uint32_t value) 	{counter->full = value;}
static	inline	void		Counter_32b_Increment	(Counter_t* counter) 					{counter->full++;}

typedef struct
{
	Counter_t global_counter;
	Counter_t last_read;
	Counter_t show_pulse_num;
}
Controls_t;

#endif
