#include "main.h"

int main(void)
{
	RCC_Enable();	//Запуск LSI и LSE

	IWDG_Enable();	//Запуск Watch Dog Timer'а

	FRAM_Enable();	//Запуск внешней FRAM-памяти

	FRAM_Load_Settings();	//Загрузка последних настроек из внешней FRAM-памяти

	DPU_Enable();	//Запуск АЦП и обработчика измерений

	RTC_Enable();	//Запуск часов реального времени

    while (1)
    {
    	IWDG_Update();
    }
}
