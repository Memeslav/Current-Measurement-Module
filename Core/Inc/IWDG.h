#ifndef IWDG_H_
#define IWDG_H_

#include "stm32l053xx.h"
#include "LSI.h"

#define IWDG_ENABLE_KEY     0x0000CCCC
#define IWDG_ACCESS_KEY     0x00005555
#define IWDG_UPDATE_KEY     0x0000AAAA
#define IWDG_CLK_DIVIDE     256U

void IWDG_Enable(void);
void IWDG_Update(void);

#endif
