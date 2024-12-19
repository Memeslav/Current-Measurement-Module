#include "Watchdog_timer.h"

void Watchdog_Enable(void)
{
	IWDG->KR  =  IWDG_ENABLE_KEY;
	IWDG->KR  =  IWDG_ACCESS_KEY;

	IWDG->PR  = IWDG_PR_PR_Msk;

	IWDG->RLR = IWDG_TIMEOUT_S * ((IWDG_LSI_HERTZ/IWDG_CLK_DIVIDE));
    while(IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU)){}

	IWDG->KR  = IWDG_UPDATE_KEY;

    RCC->CSR |=  RCC_CSR_LSION;
	while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY){}
}
