#include "Memory.h"

volatile REGISTERS registers =
{
    .unixtime		=	{	.full = 0	},

    .currents 		= 	{	.max = 0,
    						.ave = 0,
							.min = 0,	},

    .controls 		= 	{	.global_counter = { .full = 0 },
    						.last_readed    = { .full = 0 },
							.show_pulse     = { .full = 0 }},

    .impulse 		= 	{	.num       	= { .full = 0 },
    						.start_time = { .full = 0 },
							.duration   = { .full = 0 },
							.max_amp    = 0,
							.ave_amp    = 0,},

    .settings 		= 	{	.minimal_width 	= { .full = 5 },
    						.measure_period = 1,
							.trigger_level 	= 2000,
							.hysteresis 	= 200,},

    .reserved 		= 	{ 	.full = 0,	},

    .calibration 	= 		1208,

    .mcu_data 		= 	{.lsi_freq = 38000,	.mcu_temperature = 20,	.msi_freq = 0x0000,},

    .po_version 	= 	110,
};
