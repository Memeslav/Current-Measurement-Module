#include "Real_time_clock.h"

//Значения делителей для LSI = 38 кГц
#define     PREDIV_A_Default     128U
#define 	PREDIV_S_Default	 297U
//Ключи для доступа к RTC
#define 	RTC_KEY_0 			 0xCA
#define 	RTC_KEY_1 			 0x53
//Смещение времени при чтении
#define     GET_YEAR_OFFSET 	 100U
#define     GET_MONTH_OFFSET  	   1U
#define     GET_DAY_OFFSET    	   7U
//Смещение времени при записи
#define     SET_YEAR_OFFSET 	 100U
#define     SET_MONTH_OFFSET  	   1U
#define     SET_DAY_OFFSET    	   1U

float RTC_Frequence = LSI_Typical_Frequency;

//Работа с LSI
static void LSI_Enable(void)
{
    RCC->CSR |=  RCC_CSR_LSION;
	while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY){}   
}

//Работа с RTC
static void RTC_Init_Mode_Enter(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;

        RTC->WPR  =  RTC_KEY_0;
		RTC->WPR  =  RTC_KEY_1;

		RTC->ISR |=  RTC_ISR_INIT;
		while((RTC->ISR & RTC_ISR_INITF) != RTC_ISR_INITF);
}
static void RTC_Init_Mode_Exit (void)
{
		RTC->ISR &= ~RTC_ISR_INIT;
        while((RTC->ISR & RTC_ISR_INITF) == RTC_ISR_INITF){}

		RTC->WPR  = 0x00;
	
        PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}
static void RTC_Calibrate(void)
{
    Measure_frequency(LSI, &RTC_Frequence);

	RTC_Init_Mode_Enter();

        uint16_t PREDIV_S =      PREDIV_S_Default;
        PREDIV_S = RTC_Frequence/PREDIV_A_Default;

		RTC->PRER =  RTC_PRER_PREDIV_A_Msk | PREDIV_S;
		RTC->PRER =  RTC_PRER_PREDIV_A_Msk | PREDIV_S;

	RTC_Init_Mode_Exit();
}
static void RTC_Set_WakeUp_Timer(uint32_t period_ms)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

		PWR->CR |= PWR_CR_DBP;

        RTC->WPR  =  RTC_KEY_0;
		RTC->WPR  =  RTC_KEY_1;

	    RTC->CR  &= ~RTC_CR_WUTE;
	    RTC->ISR &= ~RTC_ISR_WUTF;

		RTC->WUTR = (RTC_Frequence / 16000) * period_ms;

	    RTC->CR |=  RTC_CR_WUTE |
	    			RTC_CR_WUTIE;

	    EXTI->RTSR |= EXTI_RTSR_RT20;
	    EXTI->IMR  |= EXTI_IMR_IM20;

	    RTC->WPR  = 0x00;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

	NVIC_SetPriority(RTC_IRQn, 0);
	NVIC_EnableIRQ(RTC_IRQn);
}
static void RTC_Set_Alarm_A(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

		PWR->CR |= PWR_CR_DBP;

        RTC->WPR  =  RTC_KEY_0;
		RTC->WPR  =  RTC_KEY_1;

        RTC->CR  &= ~RTC_CR_ALRAE;
        RTC->ISR &= ~RTC_ISR_ALRAF;
        while ((RTC->ISR & RTC_ISR_ALRAWF) != RTC_ISR_ALRAWF); 

        RTC->ISR &= ~RTC_ISR_ALRAF;

        RTC->ALRMAR = RTC_ALRMAR_MSK1 | 
                      RTC_ALRMAR_MSK2 | 
                      RTC_ALRMAR_MSK3 | 
                      RTC_ALRMAR_MSK4;

        RTC->CR |= RTC_CR_ALRAE | 
                   RTC_CR_ALRAIE;

        EXTI->RTSR |= EXTI_RTSR_RT17;
        EXTI->IMR  |= EXTI_IMR_IM17;

	    RTC->WPR  = 0x00;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
}
static void RTC_Set_Alarm_B(void)
{
    RTC_Init_Mode_Enter();

        RTC->CR  &= ~RTC_CR_ALRBE;
        RTC->ISR &= ~RTC_ISR_ALRBF;
        while ((RTC->ISR & RTC_ISR_ALRBWF) != RTC_ISR_ALRBWF); 

        RTC->ISR &= ~RTC_ISR_ALRBF;

        RTC->ALRMBR = RTC_ALRMBR_MSK1 | 
                      RTC_ALRMBR_MSK2 | 
                      RTC_ALRMBR_MSK3 | 
                      RTC_ALRMBR_MSK4;

        RTC->CR |= RTC_CR_ALRBE | 
                   RTC_CR_ALRBIE;

        EXTI->RTSR |= EXTI_RTSR_RT17;
        EXTI->IMR  |= EXTI_IMR_IM17;

	RTC_Init_Mode_Exit();
}

void RTC_Get_Time(struct tm* time)
{
    time->tm_isdst = 0;
	time->tm_wday  = ((RTC->DR & RTC_DR_WDU_Msk) >> RTC_DR_WDU_Pos) % GET_DAY_OFFSET;
	time->tm_year  = ((RTC->DR & RTC_DR_YT_Msk ) >> RTC_DR_YT_Pos ) * 10 + ((RTC->DR & RTC_DR_YU_Msk ) >> RTC_DR_YU_Pos ) + GET_YEAR_OFFSET ;
	time->tm_mon   = ((RTC->DR & RTC_DR_MT_Msk ) >> RTC_DR_MT_Pos ) * 10 + ((RTC->DR & RTC_DR_MU_Msk ) >> RTC_DR_MU_Pos ) - GET_MONTH_OFFSET;
	time->tm_mday  = ((RTC->DR & RTC_DR_DT_Msk ) >> RTC_DR_DT_Pos ) * 10 + ((RTC->DR & RTC_DR_DU_Msk ) >> RTC_DR_DU_Pos ) ;
	time->tm_hour  = ((RTC->TR & RTC_TR_HT_Msk ) >> RTC_TR_HT_Pos ) * 10 + ((RTC->TR & RTC_TR_HU_Msk ) >> RTC_TR_HU_Pos ) ;
	time->tm_min   = ((RTC->TR & RTC_TR_MNT_Msk) >> RTC_TR_MNT_Pos) * 10 + ((RTC->TR & RTC_TR_MNU_Msk) >> RTC_TR_MNU_Pos) ;
	time->tm_sec   = ((RTC->TR & RTC_TR_ST_Msk ) >> RTC_TR_ST_Pos ) * 10 + ((RTC->TR & RTC_TR_SU_Msk ) >> RTC_TR_SU_Pos)  ;
}
void RTC_Set_Time(struct tm* time)
{
	RTC_Init_Mode_Enter();

		RTC->DR = ( time->tm_wday 	    << RTC_DR_WDU_Pos)|
				  ((time->tm_year / 10) << RTC_DR_YT_Pos )|
				  ((time->tm_year % 10) << RTC_DR_YU_Pos )|
				  ((time->tm_mon  / 10) << RTC_DR_MT_Pos )|
				  ((time->tm_mon  % 10) << RTC_DR_MU_Pos )|
				  ((time->tm_mday / 10) << RTC_DR_DT_Pos )|
				  ((time->tm_mday % 10) << RTC_DR_DU_Pos );

		RTC->TR = ((time->tm_hour / 10) << RTC_TR_HT_Pos )|
				  ((time->tm_hour % 10) << RTC_TR_HU_Pos )|
				  ((time->tm_min  / 10) << RTC_TR_MNT_Pos)|
				  ((time->tm_min  % 10) << RTC_TR_MNU_Pos)|
				  ((time->tm_sec  / 10) << RTC_TR_ST_Pos )|
				  ((time->tm_sec  % 10) << RTC_TR_SU_Pos );

	RTC_Init_Mode_Exit();
}

void RTC_Get_UNIXTIME(time_t* unixtime)
{
    struct tm dt =  
	{
		.tm_isdst = 0,
		.tm_wday  = ((RTC->DR & RTC_DR_WDU_Msk) >> RTC_DR_WDU_Pos) % GET_DAY_OFFSET,
		.tm_year  = ((RTC->DR & RTC_DR_YT_Msk ) >> RTC_DR_YT_Pos ) * 10 + ((RTC->DR & RTC_DR_YU_Msk ) >> RTC_DR_YU_Pos) + GET_YEAR_OFFSET ,
		.tm_mon   = ((RTC->DR & RTC_DR_MT_Msk ) >> RTC_DR_MT_Pos ) * 10 + ((RTC->DR & RTC_DR_MU_Msk ) >> RTC_DR_MU_Pos) - GET_MONTH_OFFSET,
		.tm_mday  = ((RTC->DR & RTC_DR_DT_Msk ) >> RTC_DR_DT_Pos ) * 10 + ((RTC->DR & RTC_DR_DU_Msk ) >> RTC_DR_DU_Pos) ,
		.tm_hour  = ((RTC->TR & RTC_TR_HT_Msk ) >> RTC_TR_HT_Pos ) * 10 + ((RTC->TR & RTC_TR_HU_Msk ) >> RTC_TR_HU_Pos) ,
		.tm_min   = ((RTC->TR & RTC_TR_MNT_Msk) >> RTC_TR_MNT_Pos) * 10 + ((RTC->TR & RTC_TR_MNU_Msk) >> RTC_TR_MNU_Pos),
		.tm_sec   = ((RTC->TR & RTC_TR_ST_Msk ) >> RTC_TR_ST_Pos ) * 10 + ((RTC->TR & RTC_TR_SU_Msk ) >> RTC_TR_SU_Pos) ,
	};
    
    *unixtime = mktime(&dt);
}
void RTC_Set_UNIXTIME(time_t* unixtime)
{
	struct tm dt = {0};

	gmtime_r(unixtime, &dt);

	dt.tm_wday += SET_DAY_OFFSET;
	dt.tm_mon  += SET_MONTH_OFFSET;
	dt.tm_year -= SET_YEAR_OFFSET;

	RTC_Init_Mode_Enter();

		uint16_t PREDIV_S = PREDIV_S_Default;
        PREDIV_S = RTC_Frequence/PREDIV_A_Default;

		RTC->PRER =  RTC_PRER_PREDIV_A_Msk | PREDIV_S;

		RTC->DR = ( dt.tm_wday 	     << RTC_DR_WDU_Pos)|
				  ((dt.tm_year / 10) << RTC_DR_YT_Pos )|
				  ((dt.tm_year % 10) << RTC_DR_YU_Pos )|
				  ((dt.tm_mon  / 10) << RTC_DR_MT_Pos )|
				  ((dt.tm_mon  % 10) << RTC_DR_MU_Pos )|
				  ((dt.tm_mday / 10) << RTC_DR_DT_Pos )|
				  ((dt.tm_mday % 10) << RTC_DR_DU_Pos );

		RTC->TR = ((dt.tm_hour / 10) << RTC_TR_HT_Pos )|
				  ((dt.tm_hour % 10) << RTC_TR_HU_Pos )|
				  ((dt.tm_min  / 10) << RTC_TR_MNT_Pos)|
				  ((dt.tm_min  % 10) << RTC_TR_MNU_Pos)|
				  ((dt.tm_sec  / 10) << RTC_TR_ST_Pos )|
				  ((dt.tm_sec  % 10) << RTC_TR_SU_Pos );

	RTC_Init_Mode_Exit();
}

void RTC_Enable (void)
{
    LSI_Enable();

    RCC->APB1ENR |=  RCC_APB1ENR_PWREN;

		PWR->CR  |=  PWR_CR_DBP;

		RCC->CSR |=  RCC_CSR_RTCRST_Msk;
		RCC->CSR &= ~RCC_CSR_RTCRST_Msk;

		RCC->CSR |=  RCC_CSR_RTCSEL_1;
		RCC->CSR |=  RCC_CSR_RTCEN;

		PWR->CR  &= ~PWR_CR_DBP;

	RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;

    NVIC_SetPriority(RTC_IRQn, 1);
    NVIC_EnableIRQ(RTC_IRQn);

    RTC_Calibrate();

    //RTC_Set_WakeUp_Timer(1000);
    RTC_Set_Alarm_A();
    //RTC_Set_Alarm_B();

    //Watchdog_Enable(&RTC_Frequence);
}

static void WakeUp_Handler (void)
{
	RTC->ISR &= ~RTC_ISR_WUTF;
	EXTI->PR =   EXTI_PR_PIF20;
}
static void Alarm_A_Handler(void)
{
	RTC_Calibrate();
	RTC_Set_Alarm_A();
	RTC->ISR &= ~RTC_ISR_ALRAF;
	EXTI->PR =   EXTI_PR_PIF17;
}
static void Alarm_B_Handler(void)
{
	RTC->ISR &= ~RTC_ISR_ALRBF;
	EXTI->PR =   EXTI_PR_PIF17;
}

void RTC_IRQHandler(void)
{
	if		(RTC->ISR & RTC_ISR_WUTF ){ WakeUp_Handler();}
	else if	(RTC->ISR & RTC_ISR_ALRAF){Alarm_A_Handler();}
	else if	(RTC->ISR & RTC_ISR_ALRBF){Alarm_B_Handler();}

	NVIC_ClearPendingIRQ(RTC_IRQn);
}
