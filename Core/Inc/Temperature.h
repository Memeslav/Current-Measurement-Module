#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "Memory.h"
#include "Driver_ADC.h"

#define TEMP130_CAL_ADDR 	((uint16_t*)((uint32_t)0x1FF8007E))
#define TEMP30_CAL_ADDR  	((uint16_t*)((uint32_t)0x1FF8007A))
#define VDD_CALIB 			((uint16_t)(300))
#define VDD_APPLI 			((uint16_t)(330))

void Temperature_calculation(float* save_result_to);

#endif
