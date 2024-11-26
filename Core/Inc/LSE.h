#ifndef LSE_H_
#define LSE_H_

#include <stdbool.h>

#include "stm32l053xx.h"

#include "PWR.h"

#define LSE_DEFAULT_FREQUENCY	32768U
#define LSE_LAUNCH_TIMEOUT		10000U

bool LSE_Enable(void);

#endif
