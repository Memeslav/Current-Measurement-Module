#include "Module_ADC.h"

static void Measure(Module_ADC_t* Module_ADC)
{
	Circuit_Switcher_On();
	for(int i = 0; i < 1000; i++);

	Module_ADC->adc.measure();

	Circuit_Switcher_Off();
}

void Module_ADC_Init(Module_ADC_t* Module_ADC)
{
	ADC_Init(&Module_ADC->adc);

	Module_ADC->signal = 0;

	Current_Handler_Clear(&Module_ADC->current_handler);
	Impulse_Handler_Clear(&Module_ADC->impulse_handler);

	Module_ADC->measure = Measure;
}

