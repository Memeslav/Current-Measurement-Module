#include "../../Module_ADC/Inc/VOLTAGE.h"

#define INTERNAL_REF 1.224

Volt_t	Calculate_Volt	(ADC_Level_t level)
{
	Volt_t internal_ref = INTERNAL_REF / Driver_ADC_Get_Channel(INT_REF);

	return level * internal_ref;
}
ADC_Level_t	Calculate_Volt_m_Volt(ADC_Level_t level)
{
	Volt_t internal_ref = INTERNAL_REF / Driver_ADC_Get_Channel(INT_REF);
	return (m_Volt_t)(level * internal_ref * 1000);
}

ADC_Level_t	Calculate_Level_from_Volt		(Volt_t volt)
{
    Volt_t internal_ref = INTERNAL_REF / Driver_ADC_Get_Channel(INT_REF);
    return (volt / internal_ref);
}
ADC_Level_t Calculate_Level_from_m_Volt		(m_Volt_t mvolt)
{
	Volt_t internal_ref = INTERNAL_REF / Driver_ADC_Get_Channel(INT_REF);
	return (ADC_Level_t)(mvolt / (internal_ref * 1000));
}
