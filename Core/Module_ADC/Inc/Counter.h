#ifndef COUNTER_H_
#define COUNTER_H_

#include "stm32l053xx.h"

typedef struct	{	uint64_t quantity;
					uint64_t sum;		} Counter_t;

static inline void 		Counter_Clear		(Counter_t *buffer)					{  *buffer = (Counter_t){0};}

static inline void 		Counter_Update		(Counter_t *buffer, uint16_t value)	{	buffer->quantity++;
																					buffer->sum += value;}

static inline uint16_t 	Counter_get_average	(const Counter_t *buffer)			{return buffer->quantity == 0 ? 0 : buffer->sum / buffer->quantity;}

#endif
