#ifndef MODULE_ADC_H_
#define MODULE_ADC_H_

#include "VOLTAGE.h"
#include "DRIVER_ADC.h"
#include "TEMPERATURE.h"

typedef struct
{
	m_Volt_t SIGNAL;

	Volt_t INA333S;
	Volt_t TPR3312;
	Volt_t INT_REF;
	Volt_t PWR_SPL;

	Celsius_t TEMPERC;
}
ADC_RESULT;

ADC_RESULT Module_ADC_Enable(void);
ADC_RESULT Module_ADC_Measure(void);

#endif
