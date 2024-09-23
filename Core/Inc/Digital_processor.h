#ifndef DIGITAL_PROCESSOR_H_
#define DIGITAL_PROCESSOR_H_

#include "Memory.h"
#include "Driver_ADC.h"

#include "Temperature.h"
#include "Currents.h"
#include "Impulses.h"

#include "LEDS.h"

#define INTERNAL_REFERENCE_VOLTAGE 1.224

typedef struct
{
	float power_supply_V;
	float temperature_C;
	float ina333_gain;
}
PCB_INFO;
extern PCB_INFO pcb_info;

void Digital_processor_enable(void);

void Update_data_from_ADC(void);

void Load_currents_into_registers(void);

void Update_impulse_settings(void);

#endif
