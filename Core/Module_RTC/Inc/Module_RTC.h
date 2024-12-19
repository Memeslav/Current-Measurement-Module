#ifndef MODULE_RTC_H_
#define MODULE_RTC_H_

#include "Driver_RTC.h"
#include "Watchdog_timer.h"

static inline void Module_RTC_Enable			(void)				{Watchdog_Enable();	Driver_RTC_Enable();}
static inline void Module_RTC_Periodic_WakeUp	(uint16_t period_s)	{Driver_RTC_Set_WakeUp_Timer(period_s);}
static inline void Module_RTC_Watchdog_Update	(void)				{Watchdog_Update();}

#endif
