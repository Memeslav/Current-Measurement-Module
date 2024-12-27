#ifndef SRC_TEMPERATURE_H_
#define SRC_TEMPERATURE_H_

#define TEMP130_CAL_ADDR 	((uint16_t*)((uint32_t)0x1FF8007E))
#define TEMP30_CAL_ADDR  	((uint16_t*)((uint32_t)0x1FF8007A))
#define VDD_CALIB 			((uint16_t)(300))
#define VDD_APPLI 			((uint16_t)(330))

static inline float Calculate_Temperature(uint16_t adc_level)
{
    float vdd_scaled = adc_level * (float)VDD_APPLI / VDD_CALIB;
    return 30.0f + (vdd_scaled - *TEMP30_CAL_ADDR) * 100.0f / (*TEMP130_CAL_ADDR - *TEMP30_CAL_ADDR);
}

#endif
