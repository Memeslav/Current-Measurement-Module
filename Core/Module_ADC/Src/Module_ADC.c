#include "Module_ADC.h"

struct { ADC_Level_t data[4]; } adc_raw = {0};

Impulse_handler_t impulse_handler = (Impulse_handler_t) {0};
Current_handler_t current_handler = (Current_handler_t) {0};

void Module_ADC_Enable(void)
{
	Current_Handler_Clear(&current_handler);
	Impulse_Handler_Clear(&impulse_handler);

	//Driver_ADC_Enable();
}

void Module_ADC_Measure(void)
{
	Circuit_Switcher_On();
	for(int i = 0; i < 1000; i++);
	//Driver_ADC_Measure();
	Circuit_Switcher_Off();
}

void Module_ADC_Data_Processing(void)
{
	//Driver_ADC_Get_All_Channels(adc_raw.data);

	ADC_Level_t signal = adc_raw.data[INA333S] - adc_raw.data[TPR3312];

	Current_Handler_Update(&current_handler, signal);
	Impulse_Handler_Update(&impulse_handler, signal, 0);
}
