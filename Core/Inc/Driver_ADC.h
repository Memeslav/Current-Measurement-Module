#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

#include "stm32l053xx.h"

#define NUMBER_OF_ADC_CHANNELS 	4
#define SUPPLY_VOLTAGE_LEVEL 	4095

#define ADC_MAXIMAL_LEVEL		4095
#define ADC_MINIMAL_LEVEL  	   -4095

#define ADC_INPUT_OFFSET_LEVEL	5

typedef enum
{
	FREE = 0,
	BUSY = 1,
}
ADC_STATE;

typedef struct
{
	int16_t  ina333_output;
	int16_t  tpr3312_output;

	int16_t  internal_ref;
	int16_t  temperature;

	int16_t  power_supply;
	int16_t  signal;
}
ADC_RAW_DATA;

extern volatile ADC_RAW_DATA adc_raw_data;
extern volatile ADC_STATE adc_state;

void Driver_ADC_enable	   (void);
void Run_single_measurement(void);

#endif
