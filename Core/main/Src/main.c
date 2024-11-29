#include "main.h"

int16_t data[4] = {0};
Celsius_t temp = 0;

Volt_t data_V[3] = {0};

ADC_Level_t levels[13] = {0};

int main(void)
{
	RCC->ICSCR &=~RCC_ICSCR_MSIRANGE_Msk;
	RCC->ICSCR |= RCC_ICSCR_MSIRANGE_6;

	ADC_Enable();

	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

	GPIOB->MODER |= GPIO_MODER_MODE2_Msk;
	GPIOB->MODER &=~GPIO_MODER_MODE2_1;
	GPIOB->BSRR  |= GPIO_BSRR_BS_2;

    while (1)
    {
    	for(int i = 0; i < 500000; i++){}

    	ADC_Measure();

    	while(ADC_Get_State() == IN_PROCESS){}

    	for(int i = 0; i < ADC_CHANNELS; i++)
    	{
    		data[i] = ADC_Get_Channel(i);
    	}

    	temp = Calculate_Temperature(ADC_Get_Channel(TEMPERC));

    	for(int i = 0; i < 3; i++)
    	{
    		data_V[i] = Calculate_Volt(ADC_Get_Channel(i));
    	}
    }
}
