#ifndef IMPULSE_HANDLER_H_
#define IMPULSE_HANDLER_H_

#include "Impulse.h"
#include "Trigger.h"
#include "Counter.h"

typedef enum	{	IMPULSE_NOT_DETECTED 	= 0,
					IMPULSE_RECORDING		= 1,
					IMPULSE_RECORDED		= 2,}	Impulse_handler_state;

typedef struct	{	Trigger_t trigger;
					Impulse_t impulse;
					Counter_t counter;
					Impulse_handler_state state;}	Impulse_handler_t;

static inline void Impulse_handler_clear		(	Impulse_handler_t*	buffer)		{	buffer->state = IMPULSE_NOT_DETECTED;
																						Impulse_Clear(&buffer->impulse);
																						Counter_Clear(&buffer->counter);}

static inline void Impulse_handler_set_trigger	(	Impulse_handler_t* 	buffer,
													ADC_Level_t 		trigger,
													ADC_Level_t 		hysteresis)	{	Trigger_set(&buffer->trigger, trigger, hysteresis);}



#endif
