#include "Temperature.h"

void Temperature_calculation(float* save_result_to)
{
	float temperature;

	float vdd_appli_scaled  = adc_raw_data.temperature * VDD_APPLI / VDD_CALIB;
	float temp30_cal_value  = (float)(*TEMP30_CAL_ADDR);
	float temp130_cal_value = (float)(*TEMP130_CAL_ADDR);

    temperature = vdd_appli_scaled - temp30_cal_value;
    temperature = temperature * (130 - 30);
    temperature = temperature / (temp130_cal_value - temp30_cal_value);
    temperature = temperature + 30;

    *save_result_to = temperature;

    registers.mcu_data.mcu_temperature = (int16_t)temperature;
}
