#ifndef ADC_H_
#define ADC_H_

#include "DMA.h"
#include "ADC_Level.h"

#define ADC_CHANNELS 4U

typedef enum 	{Measure_is_Complete = 0, Measure_in_Progress = 1}		ADC_State_e;
typedef enum 	{INA333S = 0, TPR3312 = 1, INT_REF = 2, TEMPERC = 3}	ADC_Channel_e;

typedef struct	{ADC_State_e* state;
				 ADC_Level_t* channels;

				 ADC_State_e (*get_state)		 (void);
				 ADC_Level_t (*get_channel)		 (ADC_Channel_e);
				 void 		 (*get_all_channels) (ADC_Level_t*);
				 void 		 (*measure)			 (void);} ADC_t;

void ADC_Init(ADC_t *adc);

#endif
