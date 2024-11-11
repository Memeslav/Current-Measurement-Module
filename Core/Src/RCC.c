#include "RCC.h"

static void Disable_Backup_Write_Protection(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;
		PWR->CR  |=  PWR_CR_DBP;
}

static void Enable_Backup_Write_Protection (void)
{
		PWR->CR  &= ~PWR_CR_DBP;
	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}

static void LSI_Enable(void)
{
    uint32_t timeout = LSI_LAUNCH_TIMEOUT;

    RCC->CSR |= RCC_CSR_LSION;
    while(!(RCC->CSR & RCC_CSR_LSIRDY) && timeout--){}
}

static void LSE_Enable(void)
{
    uint32_t timeout = LSE_LAUNCH_TIMEOUT;

	RCC->CSR |=	 RCC_CSR_LSEON;
	while(!(RCC->CSR & RCC_CSR_LSERDY) && timeout--){}
}

void RCC_Enable(void)
{
	LSI_Enable();

    Disable_Backup_Write_Protection();

    LSE_Enable();

    Enable_Backup_Write_Protection();
}
