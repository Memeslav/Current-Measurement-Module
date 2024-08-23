#include "LSE_Driver.h"

void LSE_Enable (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR  |= PWR_CR_DBP;

	RCC->CSR |= RCC_CSR_LSEON;
		while((RCC->CSR & RCC_CSR_LSERDY) != RCC_CSR_LSERDY){}

		PWR->CR  &= ~PWR_CR_DBP;
	RCC->APB1ENR |= ~RCC_APB1ENR_PWREN;
}
