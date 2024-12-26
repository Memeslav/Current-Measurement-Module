#include "../../Module_ADC/Inc/TEMPERATURE.h"

#define TEMP130_CAL_ADDR 	((uint16_t*)((uint32_t)0x1FF8007E))
#define TEMP30_CAL_ADDR  	((uint16_t*)((uint32_t)0x1FF8007A))
#define VDD_CALIB 			((uint16_t)(300))
#define VDD_APPLI 			((uint16_t)(330))

/*
Celsius_t Calculate_Temperature(ADC_Level_t level)
{
	float temperature;

	float vdd_appli_scaled  = level * VDD_APPLI / VDD_CALIB;

	float temp30_cal_value  = (float)(*TEMP30_CAL_ADDR);
	float temp130_cal_value = (float)(*TEMP130_CAL_ADDR);

    temperature = vdd_appli_scaled - temp30_cal_value;
    temperature = temperature * (130 - 30);
    temperature = temperature / (temp130_cal_value - temp30_cal_value);
    temperature = temperature + 30;

    return temperature;
}
*/
