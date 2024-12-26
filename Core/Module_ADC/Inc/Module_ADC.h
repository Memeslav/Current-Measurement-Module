#ifndef MODULE_ADC_H_
#define MODULE_ADC_H_

#include "ADC1.h"
#include "Switch.h"

extern volatile int16_t SIGNAL;

void Module_ADC_Enable(void);
void Module_ADC_Update(void);

#endif
