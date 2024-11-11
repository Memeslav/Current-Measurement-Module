#include "IWDG.h"

void IWDG_Enable(void)
{
	IWDG->KR  =  IWDG_ENABLE_KEY;
	IWDG->KR  =  IWDG_ACCESS_KEY;

	IWDG->PR  =  IWDG_PR_PR_Msk;

	IWDG->RLR =  IWDG_RLR_RL_Msk;
	while(IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU)){}

	IWDG->KR  =  IWDG_UPDATE_KEY;
}

void IWDG_Update(void)
{
	IWDG->KR = IWDG_UPDATE_KEY;
}
