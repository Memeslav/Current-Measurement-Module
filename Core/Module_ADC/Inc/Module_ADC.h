#ifndef MODULE_ADC_H_
#define MODULE_ADC_H_

#include "ADC.h"
#include "Current_handler.h"
#include "Impulse_handler.h"
#include "Circuit_switcher.h"

typedef struct
{
	ADC_t 		adc;
	ADC_Level_t signal;

	Impulse_handler_t impulse_handler;
	Current_handler_t current_handler;

	void (*measure) (struct Module_ADC_t* Module_ADC);

}
Module_ADC_t;

void Module_ADC_Init(Module_ADC_t* Module_ADC);

#endif
