#include "main.h"

int main(void)
{
	LED_Init();

	Real_time_clock_enable();
	LOAD_REGISTERS_FROM_FRAM();
	RTC_Set_WakeUp_Timer();

	Digital_processor_enable();
	Module_PKM_Enable();

    while(1)
    {
    	if(MAIN_PROGRAM_STATE == RUN)
    	{
    	    MSI_set_max_frequency();
    	    Update_data_from_ADC();
    	    MSI_set_min_frequency();

    	    MAIN_PROGRAM_STATE = STOP;
    	}
    }
}
