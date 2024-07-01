#ifndef IMPULSES_H_
#define IMPULSES_H_

#include "Memory.h"
#include "Driver_ADC.h"

typedef struct
{
	int16_t upper_limit;
	int16_t  down_limit;
}
TRIGGER;

typedef struct
{
	uint32_t minimal_duration;
	uint16_t hysteresis;

	TRIGGER  trigger;
}
IMPULSE_SETTINGS;
extern IMPULSE_SETTINGS impulse_settings;

typedef enum
{
	OUTSIDE_THE_IMPULSE,
	INSIDE_THE_IMPULSE,
	IMPULSE_IS_READY,
}
IMPULSE_STATUS;

typedef struct
{
	int64_t sum;
	int64_t number_of_measurements;
	IMPULSE impulse;

	IMPULSE_STATUS status;
}
IMPULSE_DATA;
extern IMPULSE_DATA impulse_data;

int Impulse_update(void);
void Impulse_cut(IMPULSE* to);

#endif
