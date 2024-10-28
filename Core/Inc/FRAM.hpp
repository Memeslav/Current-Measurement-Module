#ifndef FRAM_HPP_
#define FRAM_HPP_

#include "stm32l053xx.h"

#include "SPI.hpp"

class MB85RS64PNF
{
	public:

		enum MB85RS64PNF_CODE
		{
			WREN	= 0x06,	// Set Write Enable Latch
			WRDI	= 0x04,	// Reset Write Enable Latch
			RDSR	= 0x05,	// Read Status Register
			WRSR	= 0x01,	// Write Status Register
			READ	= 0x03,	// Read Memory Code
			WRITE	= 0x02,	// Write Memory Code
		};

	private:

		_SPI spi;

	public:

		MB85RS64PNF(SPI_TypeDef* SPI_ID);

		void read (uint16_t address, uint16_t data_size, uint8_t* data);
		void write(uint16_t address, uint16_t data_size, uint8_t* data);
};

#endif
