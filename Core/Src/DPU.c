#include "DPU.h"

#define TEMP130_CAL_ADDR 	((uint16_t*)((uint32_t)0x1FF8007E))
#define TEMP30_CAL_ADDR  	((uint16_t*)((uint32_t)0x1FF8007A))
#define VDD_CALIB 			((uint16_t)(300))
#define VDD_APPLI 			((uint16_t)(330))

DPU_RAW_DATA DPU_RAW = {0};

static void Сalculate_PWR_SPL(void)
{
	DPU_RAW.PWR_SPL = INTERNAL_REF * ADC_MAX;
	DPU_RAW.PWR_SPL /= ADC_RAW.INT_REF;
}

static void Сalculate_TEMPERC(void)
{
	float temperature;

	float vdd_appli_scaled  = ADC_RAW.TEMPERC * VDD_APPLI / VDD_CALIB;
	float temp30_cal_value  = (float)(*TEMP30_CAL_ADDR);
	float temp130_cal_value = (float)(*TEMP130_CAL_ADDR);

    temperature = vdd_appli_scaled - temp30_cal_value;
    temperature = temperature * (130 - 30);
    temperature = temperature / (temp130_cal_value - temp30_cal_value);
    temperature = temperature + 30;

    DPU_RAW.TEMPERC = temperature;
}

static void Сalculate_INA333S(void)
{
	DPU_RAW.INA333S = ((ADC_RAW.INA333S * (DPU_RAW.PWR_SPL/ADC_MAX)) / 12);
}

static float Level_to_Volts(int adc_data)
{
	return adc_data * (DPU_RAW.PWR_SPL/ADC_MAX);
}

void DPU_Enable	(void)
{
	ADC_Enable();
}

void DPU_Measure(void)
{
	ADC_Measure();

	while(ADC_STATE == IN_PROCESS){}

	Сalculate_PWR_SPL();
	Сalculate_TEMPERC();

	DPU_RAW.INA333S = Level_to_Volts(ADC_RAW.INA333S);
	DPU_RAW.INT_REF = Level_to_Volts(ADC_RAW.INT_REF);
	DPU_RAW.TPR3312 = Level_to_Volts(ADC_RAW.TPR3312);
}
