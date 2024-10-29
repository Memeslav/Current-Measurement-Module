#include "MEM.h"

volatile REGISTERS registers =
{
	.unixtime 		= 	{
							0			// unitime
						},
	//---------------------------------------------------------------
	.currents 		= 	{
							0			// currents
						},
	//---------------------------------------------------------------
	.controls 		= 	{
							0			// counters and parameters
						},
	//---------------------------------------------------------------
	.impulse		= 	{
							0			// "window" to show impulse
						},
	//---------------------------------------------------------------
	.settings		= 	{
							5,			// minimal_width_lo, seconds
							0, 			// minimal_width_hi, seconds
							1, 			// measure_period, seconds
							2000, 		// trigger_level, mV*100
							200			// hysteresis, mV*100
						},
	//---------------------------------------------------------------
	.reserve		= 	{
							0			//for additional functions
						},
	//---------------------------------------------------------------
	.calibration	= 	{
							1208		// calibration parameter
						},
	//---------------------------------------------------------------
	.mcu_data		= 	{
							38000,		// lsi frequency, hertz
							20,			// temperature, celsius
							0x0000,		// msi frequency, hertz
							0x0000		// msi frequency, hertz
						},
	//---------------------------------------------------------------
	.po_version		= 	{
							108			// po version
						},
};

uint16_t* regs = (uint16_t*)&registers;
