#include "RTC.h"

void RTC_Enable(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

			PWR->CR  |=  PWR_CR_DBP;

			RCC->CSR |=  RCC_CSR_RTCRST_Msk;
			RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

			RCC->CSR |=	 RCC_CSR_LSEON;
			while((RCC->CSR & RCC_CSR_LSERDY) != RCC_CSR_LSERDY){}

			RCC->CSR |=  RCC_CSR_RTCSEL_0;
			RCC->CSR |=  RCC_CSR_RTCEN;

			PWR->CR  &= ~PWR_CR_DBP;

		RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}

void RTC_IRQHandler(void)
{
	if (RTC->ISR & RTC_ISR_WUTF)
	{
		Unixtime_Increment(&registers.unixtime);
	}
}
