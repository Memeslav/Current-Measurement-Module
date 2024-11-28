#include "main.h"

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
    	for(int i = 0; i < 50000; i++){}

    	DPU_Measure();
    }
}
