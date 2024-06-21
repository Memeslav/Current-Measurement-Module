#ifndef FREQUENCY_METER_H_
#define FREQUENCY_METER_H_

//Стандартная библиотека STM
#include "stm32l053xx.h"

/*
    Измеритель частоты LSI работает на:
    - высокочастотном HSI
    - таймере TIM21
*/

//Справочные значения частоты
#define HSI_Typical_Frequency    16000000U
#define LSI_Typical_Frequency       38000U

//Количество выборок для расчёта
#define NUMBER_OF_SAMPLES               8U

//Измерение частоты
void Measure_frequency(float* frequency);

#endif
