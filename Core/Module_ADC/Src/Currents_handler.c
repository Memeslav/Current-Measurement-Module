#include "Currents_handler.h"

Currents_buffer_t data = {0};

static inline void Currents_handler_reset_buffer(void)	{data = (Currents_buffer_t){0};}

void Currents_handler_update	(int16_t signal_level)
{
	if(data.number_of_measurements == 0)	{	data.currents.max = signal_level;
												data.currents.ave = signal_level;
												data.currents.min = signal_level;}

	data.number_of_measurements++;
	data.average_currents_sum += signal_level;

	if		(signal_level < data.currents.min)	{data.currents.min = signal_level;}
	else if	(signal_level > data.currents.max)	{data.currents.max = signal_level;}

	data.currents.ave = data.average_currents_sum/data.number_of_measurements;
}

void Currents_handler_cut		(Currents_t* data_destination)
{
	data_destination->max = data.currents.max;
	data_destination->ave = data.currents.ave;
	data_destination->min = data.currents.min;
}
