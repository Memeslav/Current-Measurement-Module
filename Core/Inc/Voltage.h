#ifndef VOLTAGE_H_
#define VOLTAGE_H_

#include "stm32l053xx.h"

#define INTERNAL_REF 	1.224
#define ADC_MAX_LEVEL 	4096

extern volatile float VOLTS_PER_LEVEL;

#endif
