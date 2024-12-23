#include "Impulse_handler.h"

static inline void Impulse_Recording		(Impulse_handler_t* buffer, ADC_Level_t signal)
{
	Counter_Update(&buffer->counter, signal);
	buffer->impulse.maximal = (signal > buffer->impulse.maximal) ? signal : buffer->impulse.maximal;
}
static inline void Impulse_Start			(Impulse_handler_t* buffer, ADC_Level_t signal, Unixtime_t unixtime)
{
	buffer->state = IMPULSE_RECORDING;
	buffer->impulse.start = unixtime;
	Impulse_Recording(buffer, signal);
}
static inline void Impulse_End				(Impulse_handler_t* buffer, ADC_Level_t signal, Unixtime_t unixtime)
{
	buffer->impulse.end = unixtime;
	Unixtime_t duration = buffer->impulse.end - buffer->impulse.start;
	if		(Filter_Check(&buffer->filter, duration) == APPROVED) 	{buffer->state = IMPULSE_RECORDED;}
	else if	(Filter_Check(&buffer->filter, duration) == DENIED)		{buffer->state = IMPULSE_NOT_DETECTED;}
}
Impulse_handler_state Impulse_Handler_Update(Impulse_handler_t* buffer, ADC_Level_t signal, Unixtime_t unixtime)
{
	switch(buffer->state)
	{
		case IMPULSE_NOT_DETECTED:
			if(signal > buffer->trigger.upper_limit)
			{Impulse_Start(buffer, signal, unixtime);}
			break;

		case IMPULSE_RECORDING:
			if(signal < buffer->trigger.lower_limit)
			{Impulse_End(buffer, signal, unixtime);}
			else{Impulse_Recording(buffer, signal);}
			break;

		default:
			break;
	}
	return buffer->state;
}
