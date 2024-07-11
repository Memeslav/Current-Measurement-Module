#include "Watchdog_timer.h"

//Ключи для работы с IWDG
#define IWDG_ENABLE_KEY     0x0000CCCC
#define IWDG_ACCESS_KEY     0x00005555
#define IWDG_UPDATE_KEY     0x0000AAAA

//Предделитель, зависит от IWDG->PR
#define IWDG_CLK_DIVIDE     256U

//Запуск сторожевого таймера
void Watchdog_Enable(float* LSI_frequency)
{
	IWDG->KR  =  IWDG_ENABLE_KEY;
	IWDG->KR  =  IWDG_ACCESS_KEY;

	IWDG->PR  = IWDG_PR_PR_Msk;

	IWDG->RLR = IWDG_TIMEOUT * ((*LSI_frequency/IWDG_CLK_DIVIDE));
    while(IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU)){}

	IWDG->KR  = IWDG_UPDATE_KEY;
}

//Обновить сторожевой таймер
void Watchdog_Update(void)
{
	IWDG->KR = IWDG_UPDATE_KEY;
}
