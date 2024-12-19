#include "Module_FRAM.h"

void Module_FRAM_Enable(void)
{
	SPI2_Enable();
}

void FRAM_read (uint16_t address,
				uint16_t data_size,
				uint8_t* data)
{
	SPI2_CS_L();

	SPI2_Send_Byte(READ);
	SPI2_Send_Byte((address >> 8) & 0xFF);
	SPI2_Send_Byte(address & 0xFF);

	for(uint16_t i = 0; i < data_size; i++)
	{
		data[i] = SPI2_Send_Byte(0x00);
	}

	SPI2_CS_H();
}

void FRAM_write(uint16_t address,
				uint16_t data_size,
				uint8_t* data)
{
	SPI2_CS_L();
	SPI2_Send_Byte(WREN);
	SPI2_CS_H();

	SPI2_CS_L();

	SPI2_Send_Byte(WRITE);
	SPI2_Send_Byte((address >> 8) & 0xFF);
	SPI2_Send_Byte(address & 0xFF);

	for(uint16_t i = 0; i < data_size; i++)
	{
		SPI2_Send_Byte(data[i]);
	}

	SPI2_CS_H();
}
