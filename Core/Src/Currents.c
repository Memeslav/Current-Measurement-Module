#include "Currents.h"

CURRENTS_DATA currents_data = {0};

void Currents_update(void)
{
	currents_data.number_of_measurements++;
	currents_data.sum += adc_raw_data.signal;

	if(adc_raw_data.signal < currents_data.currents.min)
	{
		currents_data.currents.min = adc_raw_data.signal;
	}
	else if(adc_raw_data.signal > currents_data.currents.max)
	{
		currents_data.currents.max = adc_raw_data.signal;
	}

	currents_data.currents.ave = currents_data.sum/currents_data.number_of_measurements;
}

static void Currents_reset(void)
{
	currents_data.sum = 0;
	currents_data.number_of_measurements = 0;

	currents_data.currents.max = adc_raw_data.signal; //-4095
	currents_data.currents.ave = adc_raw_data.signal; //0
	currents_data.currents.min = adc_raw_data.signal; //4095
}

void Currents_cut(CURRENTS* to)
{
	to->max = currents_data.currents.max;
	to->ave = currents_data.currents.ave;
	to->min = currents_data.currents.min;

	Currents_reset();
}
