#ifndef FMU_H_
#define FMU_H_

#include "HSI.h"
#include "TIM.h"

#define FMU_PROCESS_TIMEOUT	10000000U

typedef enum
{
	LSI	= 0,
	LSE	= 1,
}
TARGET_CLOCK_SOURCE;

uint32_t Measure_Frequency(TARGET_CLOCK_SOURCE source);

#endif
