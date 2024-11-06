#include "RTC.h"

static void RTC_LSI_Init(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;
		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_1;
		RCC->CSR |=  RCC_CSR_RTCEN;
		PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}

static void RTC_LSE_Init(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;
		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_0;
		RCC->CSR |=  RCC_CSR_RTCEN;
		PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}

static void RTC_Check_Clock_Source(void)
{

}

void RTC_Enable(void)
{
	if(LSE_Enable() == lse_enabled)	{RTC_LSE_Init();}
	else							{RTC_LSI_Init();}


}

/*
void RTC_IRQHandler(void)
{
	if (RTC->ISR & RTC_ISR_WUTF)
	{
    	Unixtime_Increment(&registers.unixtime);
	}
}
*/
