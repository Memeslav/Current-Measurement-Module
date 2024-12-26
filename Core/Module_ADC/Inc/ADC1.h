#ifndef ADC_H_
#define ADC_H_

#include "DMA1.h"

#define ADC1_CHANNELS	4U

typedef enum	{	INA333S = 0,
					TPR3312 = 1,
					INT_REF	= 2,
					TEMPERC = 3		} 	ADC1_Channel;

typedef enum	{	Measure_is_Complete = 0,
					Measure_in_Progress = 1		}	ADC_STATE;

extern volatile ADC_STATE	ADC1_STATE;
extern volatile uint16_t	ADC1_DATA[ADC1_CHANNELS];

void ADC1_Enable	(void);
void ADC1_Measure	(void);

#endif
