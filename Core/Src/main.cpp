#include "main.hpp"

LEDS Indicator;

MB85RS64PNF Fram(SPI2);

uint8_t suda[10] = {0};

int main(void)
{
	Fram.read(0x00, sizeof(suda), suda);

	Indicator.show_code(LEDS::LEDS_CODE::MEASURE_RAN);

    while(1)
    {

    }
}
