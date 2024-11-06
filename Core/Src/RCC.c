#include "RCC.h"

static void LSI_Enable(void)
{
	RCC->CSR |= RCC_CSR_LSION;
}

static void LSE_Enable(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;
		RCC->CSR |=  RCC_CSR_LSEDRV_Msk;
		RCC->CSR |=  RCC_CSR_LSEON;
		PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}

static void RTC_LSI_Select(void)
{
	RCC->CIER |= RCC_CIER_LSIRDYIE;
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;
		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_1;
		PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}

static void RTC_LSE_Select(void)
{
	RCC->CIER |= RCC_CIER_LSERDYIE;
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;
		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_0;
		PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}

void CSS_LSE_Enable(void)
{
	RCC->CIER |= RCC_CIER_CSSLSE;
	RCC->CSR |= RCC_CSR_LSECSSON;
}

void RCC_Enable(void)
{
	NVIC_SetPriority(RTC_IRQn, 0);
	NVIC_EnableIRQ(RTC_IRQn);

	LSI_Enable();
	LSE_Enable();

	RTC_LSE_Select();
	CSS_LSE_Enable();
}

void RTC_IRQHandler(void)
{
	if(RCC_CIFR_CSSLSEF)
	{
		RCC->CICR = RCC_CICR_CSSLSEC;
		RTC_LSI_Select();
	}
	else if(RCC_CIFR_LSERDYF)
	{
		RCC->CICR = RCC_CICR_LSERDYC;
	}
	else if(RCC_CIFR_LSIRDYF)
	{
		RCC->CICR = RCC_CICR_LSIRDYC;
	}

	NVIC_ClearPendingIRQ(RTC_IRQn);
}
