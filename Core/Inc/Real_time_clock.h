#ifndef REAL_TIME_CLOCK_H_
#define REAL_TIME_CLOCK_H_

//Стандартная библиотека STM
#include "stm32l053xx.h"
//Библиотека для работы со временем
#include "time.h"

//Измеритель частоты
#include "Frequency_meter.h"
//Сторожевой таймер
#include "Watchdog_timer.h"

/*
    Модуль часов реального времени работает на:
    - низкочастотном LSI
    - часах реального времени RTC
    Использует для работы модули:
    - измерителя частот
    - сторожевого таймера

    Будильник A срабатывает каждую минуту и
    вызывает измерение частоты LSI для
    калибровки и авто-настройки часиков

    Будильник B отвечает за обновление UNIXTIME
    в регистрах памяти, срабатывает каждую секунду

    WakeUp таймер просыпается каждую секунду и
    включает АЦП для краткосрочных измерений
*/

void RTC_Enable(void);

void RTC_Get_Time(struct tm* time);
void RTC_Set_Time(struct tm* time);

void RTC_Get_UNIXTIME(time_t* unixtime);
void RTC_Set_UNIXTIME(time_t* unixtime);

#endif
