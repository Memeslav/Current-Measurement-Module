#include "main.h"

#include "Impulse_handler.h"

int main(void)
{
	Memory_Init();

	Impulse_handler_settings_set(	Register_32b_Get(&registers.settings.minimal_impulse_duration),
									Register_16b_Get(&registers.settings.trigger_level),
									Register_16b_Get(&registers.settings.hysteresis));

    while (1)
    {

    }
}
