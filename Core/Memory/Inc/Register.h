#ifndef REGISTER_H_
#define REGISTER_H_

#include "stm32l053xx.h"

typedef uint16_t Register_16b_t;

typedef struct {Register_16b_t low;	Register_16b_t high;} Register_32b_t;

static inline uint32_t Register_32b_Get(const volatile Register_32b_t* reg)			{	return ((uint32_t)reg->high << 16) | reg->low;}

static inline void Register_32b_Set(volatile Register_32b_t* reg, uint32_t value)	{	reg->low  = (Register_16b_t)(value & 0xFFFF);
																						reg->high = (Register_16b_t)((value >> 16) & 0xFFFF);}

static inline void Register_32b_Increment(volatile Register_32b_t* reg)				{	uint32_t value = Register_32b_Get(reg);
    																					value++; Register_32b_Set(reg, value);}

#endif
