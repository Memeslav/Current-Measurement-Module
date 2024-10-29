#include "main.h"

#define     PREDIV_A_Default    0x7F
#define 	PREDIV_S_Default	0xFF
//Ключи для доступа к RTC
#define 	RTC_KEY_0 			0xCA
#define 	RTC_KEY_1 			0x53
#define 	RTC_KEY_OFF			0xFF
//Параметры для WakeUp Timer
#define 	WAKE_UP_DIV			32U
#define 	WAKE_UP_MS_TO_SEC	1000U

float RTC_Frequence = 32768;

uint8_t meme = 0;

void Real_time_clock_enable(void)
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

void RTC_Set_WakeUp_Timer(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

		PWR->CR |= PWR_CR_DBP;

		RTC->WPR  =  RTC_KEY_0;
		RTC->WPR  =  RTC_KEY_1;

		RTC->CR  &= ~RTC_CR_WUTE;
		RTC->CR  &= ~RTC_CR_WUCKSEL_Msk;
		RTC->CR  |=  RTC_CR_WUCKSEL_2;
		RTC->ISR &= ~RTC_ISR_WUTF;

		RTC->WUTR = 2;

		RTC->CR |=  RTC_CR_WUTE |
					RTC_CR_WUTIE;

		EXTI->RTSR |= EXTI_RTSR_RT20;
		EXTI->IMR  |= EXTI_IMR_IM20;

		RTC->WPR  = 0x00;

		RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

	NVIC_SetPriority(RTC_IRQn, 2);
	NVIC_EnableIRQ(RTC_IRQn);
}

void RTC_IRQHandler(void)
{
	if (RTC->ISR & RTC_ISR_WUTF)
	{
		RTC->ISR &= ~RTC_ISR_WUTF;
		EXTI->PR =   EXTI_PR_PIF20;

		if(meme%2 == 0)
		{
			RCC->IOPENR  |=   RCC_IOPENR_GPIOAEN;
			GPIOA->MODER &= ~(GPIO_MODER_MODE15_Msk);
			GPIOA->MODER |=  GPIO_MODER_MODE15_0;
			GPIOA->BSRR  |=   GPIO_BSRR_BS_15;
		}
		else
		{
			GPIOA->BSRR  |=   GPIO_BSRR_BR_15;
		}

		meme++;
	}

	NVIC_ClearPendingIRQ(RTC_IRQn);
}

void sleeper(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR  &= ~PWR_CR_PDDS;
		PWR->CSR &= ~PWR_CSR_WUF;

		EXTI->PR = 0;

		SCB->SCR |= 1 << SCB_SCR_SLEEPDEEP_Pos;

		__WFE();
}

int main(void)
{
	Real_time_clock_enable();

	RTC_Set_WakeUp_Timer();

    while (1)
    {
    	sleeper();
    }
}
