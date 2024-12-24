#ifndef DPU_H_
#define DPU_H_

#include <ADC.h>

typedef float	Volt_t;
typedef float	m_Volt_t;

m_Volt_t 	Calculate_m_Volt	(ADC_Level_t level);
Volt_t		Calculate_Volt		(ADC_Level_t level);

ADC_Level_t	Calculate_Level_from_Volt		(Volt_t volt);
ADC_Level_t Calculate_Level_from_m_Volt		(m_Volt_t mvolt);

#endif
