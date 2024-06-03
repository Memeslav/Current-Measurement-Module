#include "Frequency_meter.h"

//Буфер данных для работы измерителя
struct Clock_Measure
{
    uint8_t is_called;

	uint16_t buffer[NUMBER_OF_SAMPLES];
	uint16_t index;
	uint16_t timestep;

    float    Frequency;
};
struct Clock_Measure Time_Data = {0, {0}, 0, 0, 0};

//Работа с HSI
static void HSI_Enable (void)
{
    RCC->CR |=  RCC_CR_HSION;
    while((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY){}

	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |=  RCC_CFGR_SW_HSI;

	while((RCC->CFGR & RCC_CFGR_SWS_HSI) != RCC_CFGR_SWS_HSI){}
}
static void HSI_Disable(void)
{
    RCC->CFGR &= ~RCC_CFGR_SW_Msk;
    RCC->CFGR |=  RCC_CFGR_SW_MSI;

    while((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_MSI){}

    RCC->CR &= ~RCC_CR_HSION;
    while((RCC->CR & RCC_CR_HSIRDY) == RCC_CR_HSIRDY){}
}

//Работа с TIM21
static void TIM21_Enable (Clock_source source)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;
    while((RCC->APB2ENR & RCC_APB2ENR_TIM21EN) != RCC_APB2ENR_TIM21EN){}

            TIM21->PSC = 0;
            TIM21->CNT = 0;
            TIM21->ARR = UINT16_MAX;

            TIM21->OR &= ~TIM21_OR_TI1_RMP_Msk;

            if(source == LSI)
            {
                TIM21->OR |=  (TIM21_OR_TI1_RMP_0 |
                               TIM21_OR_TI1_RMP_2);
            }
            else if(source == MSI)
            {
                TIM21->OR |=  (TIM21_OR_TI1_RMP_0 |
                               TIM21_OR_TI1_RMP_1);
            }

            TIM21->CCER  &= ~(TIM_CCER_CC1NP_Msk|
                              TIM_CCER_CC1P_Msk);

            TIM21->CCMR1 &=  ~TIM_CCMR1_IC1PSC_Msk;

            TIM21->CCR1  &=  ~TIM_CCR1_CCR1_Msk;

            TIM21->CCMR1 |=   TIM_CCMR1_CC1S_0;

            TIM21->DIER  |=   TIM_DIER_CC1IE;

            TIM21->CCER  |=   TIM_CCER_CC1E;

            TIM21->CR1   |=   TIM_CR1_CEN;

    NVIC_SetPriority(TIM21_IRQn, 0);
    NVIC_EnableIRQ(TIM21_IRQn);    
}
static void TIM21_Disable(void)
{
    NVIC_DisableIRQ(TIM21_IRQn);
    
    RCC->APB2ENR &= ~RCC_APB2ENR_TIM21EN;
    while((RCC->APB2ENR & RCC_APB2ENR_TIM21EN) == RCC_APB2ENR_TIM21EN){}
}

//Прерывание для сбора временных меток
void TIM21_IRQHandler(void)
{
	if(TIM21->SR & TIM_SR_CC1IF)
	{
		Time_Data.buffer[Time_Data.index] = TIM21->CCR1;

		if(Time_Data.index < NUMBER_OF_SAMPLES)
		{
			Time_Data.index++;
		}
		else
		{
            for(int i = 1; i < NUMBER_OF_SAMPLES; i++)
            {
                Time_Data.timestep += ((Time_Data.buffer[i] - Time_Data.buffer[i - 1]));
            }

            Time_Data.timestep /= (NUMBER_OF_SAMPLES - 1);

            Time_Data.Frequency = 1.0/(Time_Data.timestep * (1.0/HSI_Typical_Frequency));

            TIM21_Disable();
            HSI_Disable();

            Time_Data.is_called = 0;
            Time_Data.timestep = 0;
            Time_Data.index = 0;
		}

		TIM21->SR &= ~TIM_SR_CC1IF;
	}

	NVIC_ClearPendingIRQ(TIM21_IRQn);
}

//Измерение частоты
void Measure_frequency(Clock_source source, float* frequency)
{
    if(Time_Data.is_called){return;}
    else  {Time_Data.is_called = 1;};

    HSI_Enable();
    TIM21_Enable(source);

    while(Time_Data.is_called)
    {
    	Time_Data.is_called++;
    }
    *frequency = Time_Data.Frequency;
}
