#include "main.h"

float MSI_FREQU = 0;
float LSI_FREQU = 0;

int main(void)
{
    RCC->CSR |=  RCC_CSR_LSION;
	while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY){}

    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

        GPIOA->MODER &= ~(GPIO_MODER_MODE9_Msk);
        GPIOA->MODER |=  (GPIO_MODER_MODE9_1);

        RCC->CFGR &= ~(RCC_CFGR_MCOSEL_Msk | RCC_CFGR_MCOPRE_Msk);
        RCC->CFGR |= RCC_CFGR_MCOSEL_0 | RCC_CFGR_MCOSEL_1;

    RCC->ICSCR &= ~RCC_ICSCR_MSIRANGE_Msk;

	for(;;)
	{
		Measure_frequency(LSI, &LSI_FREQU);
		Measure_frequency(MSI, &MSI_FREQU);
	}
}
