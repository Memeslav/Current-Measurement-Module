#ifndef REAL_TIME_CLOCK_H_
#define REAL_TIME_CLOCK_H_

//Стандартная библиотека STM
#include "stm32l053xx.h"

//Память устройства
#include "Memory.h"
//Измеритель частоты
#include "Frequency_meter.h"
//Сторожевой таймер
#include "Watchdog_timer.h"
//Цифровой процессор
#include "Digital_processor.h"

/*
    Модуль часов реального времени работает на:
    - низкочастотном LSI
    - часах реального времени RTC
    Использует для работы модули:
    - измерителя частот
    - сторожевого таймера
*/

//Флаг для запуска и остановки выполнения кода
extern volatile uint8_t MAIN_PROGRAM_STATE;

typedef enum
{
	STOP,
	RUN,
}
PROGRAM_STATE;

void Real_time_clock_enable(void);
void RTC_Set_WakeUp_Timer(void);

#endif
