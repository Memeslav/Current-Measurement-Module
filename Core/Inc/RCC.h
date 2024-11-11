#ifndef RCC_H_
#define RCC_H_

#include "stm32l053xx.h"

#define LSI_DEFAULT_FREQUENCY	38000U
#define LSI_LAUNCH_TIMEOUT		10000U

#define LSE_DEFAULT_FREQUENCY	32768U
#define LSE_LAUNCH_TIMEOUT		10000U

void RCC_Enable(void);

#endif
