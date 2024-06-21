#include "main.h"

int main(void)
{
	RCC->ICSCR &= ~RCC_ICSCR_MSIRANGE_Msk;

	RTC_Enable();
	Module_PKM_Enable();

    while(1)
    {

    }
}
