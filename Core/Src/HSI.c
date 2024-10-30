#include "HSI.h"

HSI_STATUS HSI_Enable(void)
{
    uint32_t timeout = HSI_LAUNCH_TIMEOUT;

    RCC->CR |= RCC_CR_HSION;

    	while (((RCC->CR & RCC_CR_HSIRDY) == 0) && timeout--){}

    if (RCC->CR & RCC_CR_HSIRDY){return hsi_enabled;}
    else						{return hsi_failure;}
}

HSI_STATUS HSI_Disable(void)
{
    RCC->CR &= ~RCC_CR_HSION;

    if ((RCC->CR & RCC_CR_HSIRDY) == 0)	{return hsi_disabled;}
    else								{return hsi_failure;}
}

void Switch_MCU_to_HSI(void)
{
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |=  RCC_CFGR_SW_HSI;

	while((RCC->CFGR & RCC_CFGR_SWS_HSI) != RCC_CFGR_SWS_HSI){}
}

void Switch_MCU_to_MSI(void)
{
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |=  RCC_CFGR_SW_MSI;

	while((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_MSI){}
}
