#ifndef ADC_H_
#define ADC_H_

#include "stm32l053xx.h"
#include "DMA.h"

#define NUMBER_OF_ADC_CHANNELS	4U

typedef struct
{
	int16_t  ina333_output;
	int16_t  tpr3312_output;

	int16_t  internal_ref;
	int16_t  temperature;
}
ADC_RAW_DATA;

void ADC_Enable(void);

extern volatile ADC_RAW_DATA ADC_DATA;

#endif
