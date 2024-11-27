#include "RTC.h"

void RTC_Enable(void)
{

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
