#include "FRAM.h"

void FRAM_Enable(void)
{
	SPI2_Enable();
}

void FRAM_READ (uint16_t address,
				uint16_t data_size,
				uint8_t* data)
{
	SPI2_CS_LOW();
	SPI2_Transfer_Byte(READ);
	SPI2_Transfer_Byte((address >> 8) & 0xFF);
	SPI2_Transfer_Byte(address & 0xFF);

	DMA1_Ch_4((uint32_t*)data, data_size);
	/*
	for(uint16_t i = 0; i < data_size; i++)
	{
		data[i] = SPI2_Transfer_Byte(0x00);
	}
	*/

	SPI2_CS_HIGH();
}

void FRAM_WRITE(uint16_t address,
				uint16_t data_size,
				uint8_t* data)
{
	SPI2_CS_LOW();
	SPI2_Transfer_Byte(WREN);
	SPI2_CS_HIGH();

	SPI2_CS_LOW();

	SPI2_Transfer_Byte(WRITE);

	SPI2_Transfer_Byte((address >> 8) & 0xFF);
	SPI2_Transfer_Byte(address & 0xFF);

	DMA1_Ch_5((uint32_t*)data, data_size);
	/*
	for(uint16_t i = 0; i < data_size; i++)
	{
		SPI2_Transfer_Byte(data[i]);
	}
	 */

	SPI2_CS_HIGH();
}

void FRAM_Save_Settings(void)
{
	uint16_t address = FRAM_SIZE - sizeof(SETTINGS);
	FRAM_WRITE(address, sizeof(SETTINGS), (uint8_t*)&registers.settings);
}

void FRAM_Load_Settings(void)
{
	uint16_t address = FRAM_SIZE - sizeof(SETTINGS);
	FRAM_READ(address, sizeof(SETTINGS), (uint8_t*)&registers.settings);
}
