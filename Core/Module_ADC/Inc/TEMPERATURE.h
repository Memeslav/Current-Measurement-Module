#ifndef TEMP_H_
#define TEMP_H_

#include "DRIVER_ADC.h"

typedef	float	Celsius_t;

Celsius_t Calculate_Temperature(ADC_Level_t level);

#endif