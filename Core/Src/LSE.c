#include "LSE.h"

LSE_STATUS LSE_Enable(void)
{
    uint32_t timeout = LSE_LAUNCH_TIMEOUT;

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

		PWR->CR |= PWR_CR_DBP;

	RCC->CSR |=	 RCC_CSR_LSEON;
	while(((RCC->CSR & RCC_CSR_LSERDY) != RCC_CSR_LSERDY) && timeout--){}

    	PWR->CR &= ~PWR_CR_DBP;

    RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

    return (RCC->CSR & RCC_CSR_LSERDY) ? lse_enabled : lse_failure;
}
