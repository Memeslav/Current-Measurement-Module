#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "stm32l053xx.h"

typedef struct
{
	uint16_t global_counter_lo;
	uint16_t global_counter_hi;

	uint16_t last_readed_lo;
	uint16_t last_readed_hi;

	uint16_t show_pulse_num_lo;
	uint16_t show_pulse_num_hi;
}
Controls_t;

static inline uint32_t Global_Counter_32b_Get(const Controls_t* controls)
{
    return ((uint32_t)controls->global_counter_hi << 16) | controls->global_counter_lo;
}
static inline void Global_Counter_32b_Set(Controls_t* controls, uint32_t value)
{
    controls->global_counter_lo = (uint16_t)(value & 0xFFFF);
    controls->global_counter_hi = (uint16_t)((value >> 16) & 0xFFFF);
}
static inline void Global_Counter_32b_Increment(Controls_t* controls)
{
    uint32_t value = Global_Counter_32b_Get(controls);
    value++;
    Global_Counter_32b_Set(controls, value);
}

static inline uint32_t Last_Readed_32b_Get(const Controls_t* controls)
{
    return ((uint32_t)controls->last_readed_hi << 16) | controls->last_readed_lo;
}
static inline uint32_t Show_Pulse_Num_32b_Get(const Controls_t* controls)
{
    return ((uint32_t)controls->show_pulse_num_hi << 16) | controls->show_pulse_num_lo;
}

#endif
