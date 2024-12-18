#include "main.h"

uint16_t* 	regs 		= (uint16_t*)&registers;

uint16_t size = 0;

uint16_t test = 0;

int main(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODE2_Msk;
	GPIOB->MODER &=~GPIO_MODER_MODE2_1;
	GPIOB->BSRR  |= GPIO_BSRR_BS_2;

    Memory_Init();

    size = sizeof(registers);

    for(int i = 0; i < 32; i++)
	{
		regs[i] = i;
	}

    for(int i = 0; i < 32; i++)
    {
    	test = regs[i];
    }

    while (1)
    {
    }
}
