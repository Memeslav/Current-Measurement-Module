#ifndef IMPULSE_HANDLER_H_
#define IMPULSE_HANDLER_H_

#include "Average_value_handler.h"

typedef enum	{	IMPULSE_NOT_DETECTED 	= 0,
					IMPULSE_RECORDING		= 1,
					IMPULSE_RECORDED		= 2,	}	Impulse_handler_state;

typedef struct	{	Average_value_handler_t counter;

					uint16_t maximal;
					uint16_t minimal;	}	 Impulse_handler_buffer_t;

#endif
