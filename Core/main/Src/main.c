#include "main.h"

int main(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

		GPIOA->MODER &= ~GPIO_MODER_MODE8_Msk;
		GPIOA->MODER |= GPIO_MODER_MODE8_0;

    Memory_Init();

    Module_RTC_Enable();
    Module_RTC_Periodic_WakeUp(Register_16b_Get(&registers.settings.measure_period));

    Module_PKM_Enable();

    while (1)
    {
    	//ждём разрешение на начало измерений

    	Watchdog_Update();

    	Module_RTC_Watchdog_Update();

    	//Register_32b_Increment(&registers.unixtime);

    	//Если ножка зажата, то в режим сна не уходим
    }
}
