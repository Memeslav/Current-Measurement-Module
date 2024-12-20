#ifndef ADC_H_
#define ADC_H_

#include "stm32l053xx.h"

#define ADC_CHANNELS	4
#define ADC_MAX_LEVEL	4095

typedef int16_t	ADC_Level_t;

typedef enum	{	INA333S = 0,
					TPR3312 = 1,
					INT_REF	= 2,
					TEMPERC	= 3,	}	ADC_Channel;

typedef enum	{	IN_PROCESS = 0,
					DATA_READY = 1,	}	ADC_STATE;

ADC_Level_t	Driver_ADC_Get_Channel		(ADC_Channel channel);
ADC_STATE 	Driver_ADC_Get_State		(void);
void Driver_ADC_Get_All_Channels		(ADC_Level_t *data);
void Driver_ADC_Enable					(void);
void Driver_ADC_Measure					(void);

#endif
