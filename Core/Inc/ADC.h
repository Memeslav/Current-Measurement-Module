#ifndef ADC_H_
#define ADC_H_

#include "stm32l053xx.h"

#define ADC_CHANNELS 	4
#define ADC_MAX 		4095

typedef enum	{	DATA_READY = 0,
					IN_PROCESS = 1,		}	ADC_STATES;

typedef struct	{	int16_t  INA333S;
					int16_t  TPR3312;
					int16_t  INT_REF;
					int16_t  TEMPERC;
					int16_t  CLR_SIG;	}	ADC_RAW_DATA;

void ADC_Enable (void);
void ADC_Measure(void);

extern	ADC_STATES		ADC_STATE;
extern	ADC_RAW_DATA	ADC_RAW;

#endif
