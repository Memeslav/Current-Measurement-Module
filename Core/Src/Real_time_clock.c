#include "Real_time_clock.h"

//Значения делителей для LSI = 38 кГц
#define     PREDIV_A_Default    128U
#define 	PREDIV_S_Default	297U
//Ключи для доступа к RTC
#define 	RTC_KEY_0 			0xCA
#define 	RTC_KEY_1 			0x53
#define 	RTC_KEY_OFF			0xFF
//Параметры для WakeUp Timer
#define 	WAKE_UP_DIV			16000U
#define 	WAKE_UP_MS_TO_SEC	1000U

//Частота работы LSI
float RTC_Frequence = LSI_Typical_Frequency;

volatile uint8_t MAIN_PROGRAM_STATE = RUN;
volatile uint8_t CURRENTS_UPDATE_TIMER = STOP;

//Работа с LSI
static void LSI_Enable(void)
{
    RCC->CSR |=  RCC_CSR_LSION;
	while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY){}   
}

//Калибровка RTC
static void RTC_Calibrate(void)
{
    Measure_frequency(LSI, &RTC_Frequence);

	uint16_t PREDIV_S =      PREDIV_S_Default;
	PREDIV_S = RTC_Frequence/PREDIV_A_Default;

	RTC->PRER =  RTC_PRER_PREDIV_A_Msk | PREDIV_S;
	RTC->PRER =  RTC_PRER_PREDIV_A_Msk | PREDIV_S;
}

//Установка Wake Up таймера
void RTC_Set_WakeUp_Timer(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

		PWR->CR |= PWR_CR_DBP;

		RTC->WPR  =  RTC_KEY_0;
		RTC->WPR  =  RTC_KEY_1;

		RTC->CR  &= ~RTC_CR_WUTE;
		RTC->ISR &= ~RTC_ISR_WUTF;

		RTC->WUTR = (RTC_Frequence / WAKE_UP_DIV) * registers.settings.measure_period * WAKE_UP_MS_TO_SEC;

		RTC->CR |=  RTC_CR_WUTE |
					RTC_CR_WUTIE;

		EXTI->RTSR |= EXTI_RTSR_RT20;
		EXTI->IMR  |= EXTI_IMR_IM20;

		RTC->WPR  = 0x00;

		RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

	NVIC_SetPriority(RTC_IRQn, 2);
	NVIC_EnableIRQ(RTC_IRQn);
}

//Включение часов реального времени
void Real_time_clock_enable(void)
{
    LSI_Enable();

    RTC_Calibrate();

    Watchdog_Enable(&RTC_Frequence);

    RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;

		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_LSI;
		RCC->CSR |=  RCC_CSR_RTCEN;

		PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

	RTC_Set_WakeUp_Timer();
}

//Прерывание для Wake Up таймера
void RTC_IRQHandler(void)
{
	if (RTC->ISR & RTC_ISR_WUTF)
	{
		Watchdog_Update();

	    if (++(registers.unixtime.lo) == 0){++(registers.unixtime.hi);}
	    if(registers.unixtime.lo % 60 == 0){RTC_Calibrate();}
	    if(CURRENTS_UPDATE_TIMER > 0){CURRENTS_UPDATE_TIMER--;}

	    MAIN_PROGRAM_STATE = RUN;

		RTC->ISR &= ~RTC_ISR_WUTF;
		EXTI->PR =   EXTI_PR_PIF20;
	}

	NVIC_ClearPendingIRQ(RTC_IRQn);
}
