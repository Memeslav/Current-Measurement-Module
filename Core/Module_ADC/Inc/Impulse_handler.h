#ifndef IMPULSE_HANDLER_H_
#define IMPULSE_HANDLER_H_

#include "Filter.h"
#include "Impulse.h"
#include "Trigger.h"
#include "Counter.h"
#include "Unixtime.h"

typedef enum	{	IMPULSE_NOT_DETECTED 	= 0,
					IMPULSE_RECORDING		= 1,
					IMPULSE_RECORDED		= 2,	}	Impulse_handler_state;

typedef struct	{	Filter_t				filter;
					Trigger_t 				trigger;
					Impulse_t 				impulse;
					Counter_t 				counter;
					Impulse_handler_state	state;}		Impulse_handler_t;

Impulse_handler_state 	Impulse_Handler_Update		(	Impulse_handler_t*	buffer,
														ADC_Level_t 		signal,
														Unixtime_t 			unixtime);

static inline void 		Impulse_Handler_Clear		(	Impulse_handler_t*	buffer)		{	buffer->state = IMPULSE_NOT_DETECTED;
																							Impulse_Clear(&buffer->impulse);
																							Counter_Clear(&buffer->counter);}

static inline void 		Impulse_Handler_Set_Trigger	(	Impulse_handler_t* 	buffer,
														ADC_Level_t 		trigger,
														ADC_Level_t 		hysteresis)	{	Trigger_Set(&buffer->trigger, trigger, hysteresis);}

static inline void		Impulse_Handler_Set_Filter	(	Impulse_handler_t* 	buffer,
														Unixtime_t			duration)	{	Filter_Set(&buffer->filter, duration);}

static inline Impulse_t Impulse_Handler_Get_Impulse (	Impulse_handler_t* 	buffer)		{	buffer->impulse.average = Counter_Get_Average(&buffer->counter);
																							return buffer->impulse;}

#endif
