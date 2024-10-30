#ifndef LSE_H_
#define LSE_H_

#include "stm32l053xx.h"

#define LSE_DEFAULT_FREQUENCY	32768U
#define LSE_LAUNCH_TIMEOUT		10000U

typedef enum
{
	lse_disabled	= 0,
	lse_enabled  	= 1,
	lse_failure		= 2,
}
LSE_STATUS;

LSE_STATUS LSE_Enable (void);

#endif
