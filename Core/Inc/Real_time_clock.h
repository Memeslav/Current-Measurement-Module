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
//Доступ к регистрам памяти
#include "Registers.h"

/*
    Модуль часов реального времени работает на:
    - низкочастотном LSI
    - часах реального времени RTC
    Использует для работы модули:
    - измерителя частот
    - сторожевого таймера

    Будильник A срабатывает через заданный период
    времени и инкрементирует счётчик секунд в регистрах,
    а также через определённый интервал времени проводит
    автокалибровку с измерением частоты LSI

    WakeUp таймер просыпается каждую секунду и
    включает АЦП для краткосрочных измерений
*/

//Интервал между калибровкой
#define INTERVAL_BETWEEN_CALIBRATIONS 60U

void RTC_Enable(void);

void RTC_Get_Time(struct tm* time);
void RTC_Set_Time(struct tm* time);

void RTC_Get_UNIXTIME(time_t* unixtime);
void RTC_Set_UNIXTIME(time_t* unixtime);

#endif
