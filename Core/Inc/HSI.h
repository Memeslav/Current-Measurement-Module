#ifndef HSI_H_
#define HSI_H_

#include "stm32l053xx.h"

#define HSI_DEFAULT_FREQUENCY	16000000U
#define HSI_LAUNCH_TIMEOUT		10000U

typedef enum
{
	hsi_disabled	= 0,
	hsi_enabled  	= 1,
	hsi_failure		= 2,
}
HSI_STATUS;

HSI_STATUS HSI_Enable (void);
HSI_STATUS HSI_Disable(void);

void Switch_MCU_to_HSI(void);
void Switch_MCU_to_MSI(void);

#endif
