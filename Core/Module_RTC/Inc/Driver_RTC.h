#ifndef DRIVER_RTC_H_
#define DRIVER_RTC_H_

#include "stm32l053xx.h"

void Driver_RTC_Enable(void);
void Driver_RTC_Set_WakeUp_Timer(uint16_t period_s);

#endif
