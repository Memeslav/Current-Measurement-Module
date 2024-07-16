#ifndef WATCHDOG_TIMER_H_
#define WATCHDOG_TIMER_H_

//Стандартная библиотека STM
#include "stm32l053xx.h"

/*  
    Сторожевой таймер работает на:
    - низкочастотном LSI
    - таймере IWDG
*/

//Значение для таймера в секундах
#define IWDG_TIMEOUT    10U

//Запуск сторожевого таймера
void Watchdog_Enable(float* LSI_frequency);
//Обновить сторожевой таймер
void Watchdog_Update(void);

#endif
