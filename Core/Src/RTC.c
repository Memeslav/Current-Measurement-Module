#include "RTC.h"

struct 	tm 			time_and_data;
		time_t 		unixtime;

static void RTC_in_LSE_Mode_Init(void)
{
	Disable_Backup_Write_Protection();

		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_0;
		RCC->CSR |=  RCC_CSR_RTCEN;

	Enable_Backup_Write_Protection();
}

static void RTC_in_LSI_Mode_Init(void)
{
	Disable_Backup_Write_Protection();

		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_1;
		RCC->CSR |=  RCC_CSR_RTCEN;

	Enable_Backup_Write_Protection();
}

void RTC_Enable(void)
{
	if(LSE_Enable() == true)
	{
		RTC_in_LSE_Mode_Init();
	}
	else
	{
		RTC_in_LSI_Mode_Init();
	}
}

void RTC_IRQHandler(void)
{
	if (RTC->ISR & RTC_ISR_WUTF)
	{
		RTC->ISR &= ~RTC_ISR_WUTF;
		EXTI->PR =   EXTI_PR_PIF20;
	}

	NVIC_ClearPendingIRQ(RTC_IRQn);
}
