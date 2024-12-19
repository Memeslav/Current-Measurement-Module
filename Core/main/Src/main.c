#include "main.h"

void sleeper(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR  &= ~PWR_CR_PDDS;
		PWR->CSR &= ~PWR_CSR_WUF;

		EXTI->PR = 0;

		SCB->SCR |= 1 << SCB_SCR_SLEEPDEEP_Pos;

		__WFE();
}

int main(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

		GPIOA->MODER &= ~GPIO_MODER_MODE8_Msk;
		GPIOA->MODER |= GPIO_MODER_MODE8_0;

    Memory_Init();

    Driver_RTC_Enable();
    Driver_RTC_Set_WakeUp_Timer(1);

    while (1)
    {
    	sleeper();
    }
}
