#ifndef CURRENTS_HANDLER_H_
#define CURRENTS_HANDLER_H_

#include "Currents.h"

typedef struct
{
	int64_t average_currents_sum;
	int64_t number_of_measurements;

	Currents_t currents;
}
Currents_buffer_t;

void Currents_handler_update	(int16_t 		signal_level);
void Currents_handler_cut		(Currents_t* 	data_destination);

#endif
