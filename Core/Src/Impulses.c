#include "Impulses.h"

IMPULSE_SETTINGS impulse_settings = {0};
IMPULSE_DATA impulse_data = {0};

static void Impulse_reset(void)
{
	memset(&impulse_data, 0, sizeof(impulse_data));
	impulse_data.impulse.max_amp = ADC_MINIMAL_LEVEL;
}

void Impulse_cut(IMPULSE* to)
{
	*to = impulse_data.impulse;
	Impulse_reset();
}

static void Impulse_start(void)
{
	impulse_data.impulse.start_time_lo = registers.unixtime.lo;
	impulse_data.impulse.start_time_hi = registers.unixtime.hi;
}

static void Impulse_record(void)
{
	impulse_data.number_of_measurements++;
	impulse_data.sum += adc_raw_data.signal;

	if (adc_raw_data.signal > impulse_data.impulse.max_amp)
	{
		impulse_data.impulse.max_amp = adc_raw_data.signal;
	}

	impulse_data.impulse.ave_amp  = impulse_data.sum / impulse_data.number_of_measurements;
}

int Impulse_filter(void)
{
	uint32_t impulse_duration = --impulse_data.number_of_measurements;

	impulse_data.impulse.duration_lo = (impulse_duration >>  0) & 0x00FF;
	impulse_data.impulse.duration_hi = (impulse_duration >> 16) & 0x00FF;

	if(impulse_duration <= impulse_settings.minimal_duration){return 0;}
	else {return 1;}
}

int Impulse_update(void)
{
	if(impulse_data.status == OUTSIDE_THE_IMPULSE)
	{
		if(adc_raw_data.signal >= impulse_settings.trigger.upper_limit)
		{
			if(LED_Check_Jumper() == 1){LED_YEL_ON();}

			impulse_data.status = INSIDE_THE_IMPULSE;

			Impulse_start();
			Impulse_record();

			LED_YEL_OFF();

			return INSIDE_THE_IMPULSE;
		}
		return OUTSIDE_THE_IMPULSE;
	}
	else
	{
		Impulse_record();

		if(adc_raw_data.signal < impulse_settings.trigger.down_limit)
		{
			impulse_data.status = OUTSIDE_THE_IMPULSE;

			if(Impulse_filter() == 1){return IMPULSE_IS_READY;}
			else{Impulse_reset();  return OUTSIDE_THE_IMPULSE;}
		}

		return INSIDE_THE_IMPULSE;
	}
}
