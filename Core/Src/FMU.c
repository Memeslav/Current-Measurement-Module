#include "FMU.h"


#define	NUMBER_OF_SAMPLES 64U


typedef enum
{
	INACTIVE = 0,
	ACTIVE   = 1,
}
MEASURE_STATUS;
MEASURE_STATUS measure_status = INACTIVE;

struct Clock_Measure
{
    float frequency;

	uint16_t index;
	float timestep;
	uint16_t buffer[NUMBER_OF_SAMPLES];
};
struct Clock_Measure Time_Data = {0, 0, 0, {0}};


static void inline TIM21_Target_Set(TARGET_CLOCK_SOURCE source)
{
    TIM21->OR &= ~TIM21_OR_TI1_RMP_Msk;

	switch (source)
	{
		case LSI:

			TIM21->OR |=  (TIM21_OR_TI1_RMP_0 | TIM21_OR_TI1_RMP_2);
			break;

		case LSE:

			TIM21->OR |=  (TIM21_OR_TI1_RMP_2);
			break;
	}
}


uint32_t Measure_Frequency(TARGET_CLOCK_SOURCE source)
{
    if (measure_status == ACTIVE) return 0;

    measure_status = ACTIVE;
    Time_Data.index = 0;
    Time_Data.timestep = 0;

    TIM21_Init();
    TIM21_Target_Set(source);
    TIM21_Enable();

    uint32_t timeout = FMU_PROCESS_TIMEOUT;
    while (measure_status == ACTIVE && --timeout);

    return (measure_status == INACTIVE) ? Time_Data.frequency : 0;
}

void TIM21_IRQHandler(void)
{
    if (TIM21->SR & TIM_SR_CC1IF)
    {
        uint32_t current_capture = TIM21->CCR1;

        if (Time_Data.index > 0)
        {
            Time_Data.timestep += current_capture - Time_Data.buffer[Time_Data.index - 1];
        }

        Time_Data.buffer[Time_Data.index++] = current_capture;

        if (Time_Data.index >= NUMBER_OF_SAMPLES)
        {
            Time_Data.frequency = (HSI_DEFAULT_FREQUENCY * (NUMBER_OF_SAMPLES - 1)) / Time_Data.timestep;

            measure_status = INACTIVE;
            TIM21_Disable();
        }

        TIM21->SR &= ~TIM_SR_CC1IF;
    }

    NVIC_ClearPendingIRQ(TIM21_IRQn);
}
