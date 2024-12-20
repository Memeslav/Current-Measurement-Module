#ifndef IMPULSE_HANDLER_H_
#define IMPULSE_HANDLER_H_

#include "stm32l053xx.h"

typedef enum	{	IMPULSE_NOT_DETECTED 	= 0,
					IMPULSE_RECORDING		= 1,
					IMPULSE_RECORDED		= 2,	}	Impulse_handler_state;

typedef struct	{	uint64_t number_of_measurements;
					uint64_t sum_of_all_measurements;

					uint16_t maximal;
					uint16_t minimal;	}	 Impulse_handler_buffer_t;

#endif
