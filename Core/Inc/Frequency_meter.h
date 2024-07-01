#ifndef FREQUENCY_METER_H_
#define FREQUENCY_METER_H_

//Стандартная библиотека STM
#include "stm32l053xx.h"

#include "Memory.h"

/*  
    Измеритель частот работает на:
    - высокочастотном HSI
    - таймере TIM21
*/

//Измеряемый источник
typedef enum
{
    LSI = 0,
    MSI = 1,
}
Clock_source;

//Справочные значения частоты
#define HSI_Typical_Frequency    16000000U
#define LSI_Typical_Frequency       38000U

//Количество выборок для расчёта
#define NUMBER_OF_SAMPLES               8U

//Измерение частоты
void Measure_frequency(Clock_source source, float* frequency);

#endif
