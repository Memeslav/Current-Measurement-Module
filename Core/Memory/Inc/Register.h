#ifndef REGISTER_H_
#define REGISTER_H_

#include "stm32l053xx.h"

typedef uint16_t Register_16b_t;

typedef	union	{struct{Register_16b_t low;	Register_16b_t high;};	uint32_t full;}	Register_32b_t;

static	inline	uint32_t	Register_32b_Get		(const Register_32b_t* reg)				{return reg->full;}
static	inline	void 		Register_32b_Set		(Register_32b_t* reg, uint32_t value)	{reg->full = value;}

static	inline	void		Register_32b_Increment	(Register_32b_t* reg) 					{reg->full++;}
static	inline	void		Register_32b_Decrement	(Register_32b_t* reg) 					{reg->full--;}

#endif
