#ifndef CURRENTS_H_
#define CURRENTS_H_

#include "Memory.h"
#include "Driver_ADC.h"

typedef struct
{
	int64_t sum;
	int64_t number_of_measurements;
	CURRENTS currents;
}
CURRENTS_DATA;
extern CURRENTS_DATA currents_data;

void Currents_update(void);
void Currents_cut(CURRENTS* to);


#endif
