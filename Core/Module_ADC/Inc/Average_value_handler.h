#ifndef AVERAGE_VALUE_HANDLER_H_
#define AVERAGE_VALUE_HANDLER_H_

#include "stm32l053xx.h"

typedef struct	{	uint64_t number_of_measurements;
					uint64_t sum_of_all_measurements;	} Average_value_handler_t;

static inline void 		Average_handler_reset		(Average_value_handler_t *buffer)					{  *buffer = (Average_handler_buffer_t){0};}

static inline void 		Average_handler_update		(Average_value_handler_t *buffer, uint16_t value)	{	buffer->number_of_measurements++;
																											buffer->sum_of_all_measurements += value;}

static inline uint16_t 	Average_handler_get_average	(const Average_handler_buffer_t *buffer)
{
	return buffer->number_of_measurements == 0 ? 0 : buffer->sum_of_all_measurements / buffer->number_of_measurements;
}

#endif
