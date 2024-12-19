#include "main.h"

void deep_sleep(void)
{
    // Включаем питание для периферийных устройств
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;  // Включаем питание для Power Control (PWR)

    // Разрешаем доступ к регистрам PWR для настройки сна
    PWR->CR |= PWR_CR_DBP;  // Разрешаем доступ к регистрам PWR

    // Убираем флаг пробуждения
    PWR->CSR &= ~PWR_CSR_WUF;

    // Переводим контроллер в режим Standby
    PWR->CR |= PWR_CR_PDDS;  // Включаем режим Standby (глубокий сон)
    PWR->CR |= PWR_CR_CWUF;  // Убираем флаг пробуждения

    // Устанавливаем флаг SLEEPDEEP для перехода в глубокий режим сна
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // Ожидание события, что приводит к пробуждению (например, прерывание)
    __SEV();   // Генерация события
    __WFE();   // Ожидание события
    __WFE();

    // Контроллер "спит" в этом месте до тех пор, пока не произойдёт событие пробуждения
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
		GPIOA->ODR ^= GPIO_ODR_OD8;

		for(int i = 0; i < 1000; i++);

		deep_sleep();
    }
}
