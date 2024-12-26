#include "Module_ADC.h"

volatile int16_t SIGNAL = 0;

void Module_ADC_Enable(void)
{
	RCC->IOPENR  |=   RCC_IOPENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE15_Msk);
	GPIOA->MODER |=  GPIO_MODER_MODE15_0;

	GPIOA->BSRR  |=   GPIO_BSRR_BR_15;

	Switch_Init();
	ADC1_Enable();
}

void Module_ADC_Update(void)
{
	Switch_On();

	for(int i = 0; i < 5; i++)
	{
		GPIOA->BSRR  |=   GPIO_BSRR_BS_15;ADC1_Measure();
		ADC1_Measure();
		GPIOA->BSRR  |=   GPIO_BSRR_BR_15;
	}

	Switch_Off();

	SIGNAL = ADC1_DATA[INA333S] - ADC1_DATA[TPR3312];

	//PCB_Info_Update()
	//Currents_Update()
	//Impulse_Update()
}
