#include "FRAM.hpp"

MB85RS64PNF::MB85RS64PNF(SPI_TypeDef* SPI_ID) : spi(SPI_ID) {}

void MB85RS64PNF::read (uint16_t address, uint16_t data_size, uint8_t* data)
{
	spi.low_CS();
	spi.transfer_byte(READ);
	spi.transfer_byte((address >> 8) & 0xFF);
	spi.transfer_byte(address & 0xFF);

	for (uint16_t i = 0; i < data_size; i++) {data[i] = spi.transfer_byte(0x00);}
	spi.hig_CS();
}

void MB85RS64PNF::write(uint16_t address, uint16_t data_size, uint8_t* data)
{
    spi.low_CS();
    spi.transfer_byte(WREN);
    spi.hig_CS();

    spi.low_CS();
	spi.transfer_byte(WRITE);
	spi.transfer_byte((address >> 8) & 0xFF);
	spi.transfer_byte(address & 0xFF);

	for (uint16_t i = 0; i < data_size; i++) {spi.transfer_byte(data[i]);}
	spi.hig_CS();
}

