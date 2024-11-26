#include "PWR.h"

void Disable_Backup_Write_Protection(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;
		PWR->CR  |=  PWR_CR_DBP;
}

void Enable_Backup_Write_Protection (void)
{
		PWR->CR  &= ~PWR_CR_DBP;
	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}
