#include "main.h"

uint8_t test[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

uint8_t suda_1[10] = {0};
uint8_t suda_2[10] = {0};

int main(void)
{
	DMA1_Init();

	SPI2_Enable();

	FRAM_READ(0x00, sizeof(suda_1), suda_1);

	FRAM_WRITE(0x00, sizeof(suda_1), suda_1);

	FRAM_READ(0x00, sizeof(suda_2), suda_2);

    while (1)
    {

    }
}
