#ifndef CURRENTS_HANDLER_H_
#define CURRENTS_HANDLER_H_

#include "stm32l053xx.h"

typedef struct	{	uint64_t number_of_measurements;
					uint64_t sum_of_all_measurements;

					uint16_t maximal;
					uint16_t minimal;	}	 Current_handler_buffer_t;

static inline void Current_handler_reset	(Current_handler_buffer_t *buffer)	{*buffer = (Current_handler_buffer_t){0};}

void Current_handler_update					(Current_handler_buffer_t *buffer, uint16_t signal);

static inline uint16_t Current_handler_get_maximal(const Current_handler_buffer_t *buffer)	{return buffer->maximal;}
static inline uint16_t Current_handler_get_minimal(const Current_handler_buffer_t *buffer)	{return buffer->minimal;}
static inline uint16_t Current_handler_get_average(const Current_handler_buffer_t *buffer)
{
	return buffer->number_of_measurements == 0 ? 0 : buffer->sum_of_all_measurements / buffer->number_of_measurements;
}

#endif
