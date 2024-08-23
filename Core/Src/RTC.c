#include "RTC.h"


static void LSI_Enable(void)
{
	RCC->APB1ENR 	|=  RCC_APB1ENR_PWREN;
		PWR->CR  	|=  PWR_CR_DBP;

	RCC->CSR |= RCC_CSR_LSEON;
	while((RCC->CSR & RCC_CSR_LSERDY) != RCC_CSR_LSERDY){}

		PWR->CR  	&= ~PWR_CR_DBP;
	RCC->APB1RSTR	|=  RCC_APB1RSTR_PWRRST;
}

static void LSE_Enable(void)
{
	RCC->APB1ENR 	|=  RCC_APB1ENR_PWREN;
		PWR->CR  	|=  PWR_CR_DBP;

	RCC->CSR |= RCC_CSR_LSEON;
	while((RCC->CSR & RCC_CSR_LSERDY) != RCC_CSR_LSERDY){}

		PWR->CR  	&= ~PWR_CR_DBP;
	RCC->APB1RSTR	|=  RCC_APB1RSTR_PWRRST;
}

void RTC_Enable(void)
{
	LSE_Enable();
	//включить резонатор
}




time_t convert_to_unitime(struct tm *timeinfo)
{
    return mktime(timeinfo);
}

void convert_from_unitime(time_t unitime, struct tm *timeinfo)
{
    *timeinfo = *gmtime(&unitime);
}
