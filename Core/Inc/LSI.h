#ifndef LSI_H_
#define LSI_H_

#include "stm32l053xx.h"

#define LSI_DEFAULT_FREQUENCY	38000U
#define LSI_LAUNCH_TIMEOUT		10000U

typedef enum
{
	lsi_failure		= 0,
	lsi_enabled  	= 1,
}
LSI_STATUS;

LSI_STATUS LSI_Enable (void);

#endif
