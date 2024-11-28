#ifndef DPU_H_
#define DPU_H_

#include "stm32l053xx.h"

#include "ADC.h"

#define	INTERNAL_REF	1.224

typedef struct
{
	float	PWR_SPL;

	float	INA333S;
	float	TPR3312;
	float	INT_REF;

	float	TEMPERC;
}
DPU_RAW_DATA;

void DPU_Enable	(void);
void DPU_Measure(void);

extern DPU_RAW_DATA DPU_RAW;

#endif
