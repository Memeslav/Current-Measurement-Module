#include "main.h"


int main(void)
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    RCC->ICSCR &= ~RCC_ICSCR_MSIRANGE_Msk;

    RTC_Enable();

	for(;;)
	{

	}
}
