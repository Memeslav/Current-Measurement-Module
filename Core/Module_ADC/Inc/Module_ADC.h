#ifndef MODULE_ADC_H_
#define MODULE_ADC_H_

#include "Driver_ADC.h"
#include "Current_handler.h"
#include "Impulse_handler.h"
#include "Circuit_switcher.h"

typedef struct
{
	Impulse_handler_t impulse_handler;
	Current_handler_t current_handler;

}
Module_ADC_t;

void Module_ADC_Enable			(void);
void Module_ADC_Measure			(void);

void Module_ADC_Data_Processing	(void);

#endif
