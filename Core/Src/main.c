#include "main.h"


int main(void)
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

        GPIOA->MODER &= ~(GPIO_MODER_MODE9_Msk);
        GPIOA->MODER |=  (GPIO_MODER_MODE9_1);

        RCC->CFGR &= ~(RCC_CFGR_MCOSEL_Msk | RCC_CFGR_MCOPRE_Msk);
        RCC->CFGR |= RCC_CFGR_MCOSEL_0 | RCC_CFGR_MCOSEL_1;

    RCC->ICSCR &= ~RCC_ICSCR_MSIRANGE_Msk;

    RTC_Enable();

	for(;;)
	{

	}
}
