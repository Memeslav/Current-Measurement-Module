#include "Driver_RTC.h"

#define 	RTC_KEY_0 			0xCA
#define 	RTC_KEY_1 			0x53
#define 	RTC_KEY_OFF			0xFF
#define 	RTC_COUNT_SHIFT		0x01

static void RTC_Init(void)
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

void Driver_RTC_Enable(void)
{
	RTC_Init();
}

void Driver_RTC_Set_WakeUp_Timer(uint16_t period_s)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

		PWR->CR |= PWR_CR_DBP;

		RTC->WPR  =  RTC_KEY_0;
		RTC->WPR  =  RTC_KEY_1;

		RTC->CR  &= ~RTC_CR_WUTE;
		RTC->CR  &= ~RTC_CR_WUCKSEL_Msk;
		RTC->CR  |=  RTC_CR_WUCKSEL_2;
		RTC->ISR &= ~RTC_ISR_WUTF;

		RTC->WUTR = period_s - RTC_COUNT_SHIFT;

		RTC->CR |=  RTC_CR_WUTE | RTC_CR_WUTIE;

		EXTI->RTSR |= EXTI_RTSR_RT20;
		EXTI->IMR  |= EXTI_IMR_IM20;

		RTC->WPR  = RTC_KEY_OFF;

		RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

	NVIC_SetPriority(RTC_IRQn, 0);
	NVIC_EnableIRQ(RTC_IRQn);
}

void RTC_IRQHandler(void)
{
	if (RTC->ISR & RTC_ISR_WUTF)
	{
		GPIOA->ODR ^= GPIO_ODR_OD8;

		RTC->ISR &= ~RTC_ISR_WUTF;
		EXTI->PR =   EXTI_PR_PIF20;
	}

	NVIC_ClearPendingIRQ(RTC_IRQn);
}
