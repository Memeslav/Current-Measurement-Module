#include "Memory.h"

volatile REGISTERS registers =
{
	.unixtime 		= 	{0},
	.currents 		= 	{0},
	.controls 		= 	{0},
	.impulse		= 	{0},

	.settings		= 	{5,			// minimal_width_lo, seconds
						0, 			// minimal_width_hi, seconds
						1, 			// measure_period, seconds
						2000, 		// trigger_level, mV*100
						200},		// hysteresis, mV*100

	.reserve		= 	{0},

	.calibration	= 	{1208},		// calibration parameter

	.mcu_data		= 	{38000,		// lsi frequency, hertz
						20,			// temperature, celsius
						0x0000,		// msi frequency, hertz
						0x0000},	// msi frequency, hertz

	.po_version		= 	{109},
};
uint16_t* regs = (uint16_t*)&registers;

volatile IMPULSE_ARCHIVE impulse_archive = {0};
uint16_t* impulses = (uint16_t*)&impulse_archive;

//Переключение тактовой частоты на минимальную
void MSI_set_min_frequency(void)
{
	RCC->ICSCR &=~RCC_ICSCR_MSIRANGE_Msk;
	RCC->ICSCR |= RCC_ICSCR_MSIRANGE_0;
}

//Переключение тактовой частоты на максимальную
void MSI_set_max_frequency(void)
{
	RCC->ICSCR &=~RCC_ICSCR_MSIRANGE_Msk;
	RCC->ICSCR |= RCC_ICSCR_MSIRANGE_6;
}
