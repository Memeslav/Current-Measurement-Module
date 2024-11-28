#include "main.h"

int main(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

	GPIOB->MODER |= GPIO_MODER_MODE2_Msk;
	GPIOB->MODER &=~GPIO_MODER_MODE2_1;
	GPIOB->BSRR  |= GPIO_BSRR_BS_2;

	ADC_Enable();

    while (1)
    {
    	for(int i = 0; i < 100000; i++){}

    	ADC_Measure();
    }
}
