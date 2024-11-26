#include "main.h"

void get_TimeData(time_t unixtime, struct tm* timedata)
{
    struct tm* temp = gmtime(&unixtime);
    if (temp != NULL) {*timedata = *temp;}
}

int main(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;
		PWR->CR  |=  PWR_CR_DBP;
		RCC->CSR |=	 RCC_CSR_LSEON;
		PWR->CR  &= ~PWR_CR_DBP;
	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

	RTC_Enable();

    while (1)
    {

    }
}
