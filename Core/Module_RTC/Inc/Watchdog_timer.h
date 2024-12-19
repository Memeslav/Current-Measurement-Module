#ifndef WATCHDOG_TIMER_H_
#define WATCHDOG_TIMER_H_

#include "stm32l053xx.h"

#define IWDG_ENABLE_KEY     0x0000CCCC
#define IWDG_ACCESS_KEY     0x00005555
#define IWDG_UPDATE_KEY     0x0000AAAA

#define IWDG_CLK_DIVIDE     256U
#define IWDG_TIMEOUT_S		10U
#define IWDG_LSI_HERTZ		38000U

void Watchdog_Enable(void);
static inline void Watchdog_Update	(void)	{IWDG->KR = IWDG_UPDATE_KEY;}

#endif
