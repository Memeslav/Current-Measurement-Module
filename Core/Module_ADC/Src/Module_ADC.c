#include "Module_ADC.h"

struct { ADC_Level_t data[4]; } adc_raw = {0};

static void Module_ADC_Circuit_Enable(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
		GPIOB->MODER |= GPIO_MODER_MODE2_Msk;
		GPIOB->MODER &=~GPIO_MODER_MODE2_1;
		GPIOB->BSRR  |= GPIO_BSRR_BS_2;
}

static void Module_ADC_Circuit_Disable(void)
{
		GPIOB->BSRR |= GPIO_BSRR_BR_2;
	RCC->IOPENR &=~RCC_IOPENR_GPIOBEN;
}

void Module_ADC_Enable(void)
{
	Driver_ADC_Enable();
}

void Module_ADC_Measure(void)
{
	Module_ADC_Circuit_Enable();

	for(int i = 0; i < 500; i++);

	Driver_ADC_Measure();
	Module_ADC_Circuit_Disable();
}

void Module_ADC_Data_Processing(void)
{
	Driver_ADC_Get_All_Channels(adc_raw.data);

	/*
	ADC_Level_t INA333S_l = Driver_ADC_Get_Channel(INA333S);
	ADC_Level_t TPR3312_l = Driver_ADC_Get_Channel(TPR3312);
	ADC_Level_t INT_REF_l = Driver_ADC_Get_Channel(INT_REF);
	ADC_Level_t TEMPERC_l = Driver_ADC_Get_Channel(TEMPERC);

	ADC_Level_t SIGNAL_l = INA333S_l - TPR3312_l;
	*/

}
