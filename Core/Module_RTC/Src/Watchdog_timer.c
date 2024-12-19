#include "Watchdog_timer.h"

#define IWDG_ENABLE_KEY     0x0000CCCC
#define IWDG_ACCESS_KEY     0x00005555
#define IWDG_UPDATE_KEY     0x0000AAAA

#define IWDG_CLK_DIVIDE     255U
#define IWDG_TIMEOUT_S		10U
#define IWDG_LSI_HERTZ		38000U

void Watchdog_Enable(void)
{
    RCC->CSR |=  RCC_CSR_LSION;
	while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY){}

	IWDG->KR  =  IWDG_ENABLE_KEY;
	IWDG->KR  =  IWDG_ACCESS_KEY;

	IWDG->PR  = IWDG_PR_PR_Msk;

	IWDG->RLR = IWDG_TIMEOUT_S * ((IWDG_LSI_HERTZ/IWDG_CLK_DIVIDE));
    while(IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU)){}

	IWDG->KR  = IWDG_UPDATE_KEY;
}

void Watchdog_Update(void)
{
	IWDG->KR = IWDG_UPDATE_KEY;
}
