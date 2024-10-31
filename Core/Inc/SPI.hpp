#ifndef SPI_HPP_
#define SPI_HPP_

#include "stm32l053xx.h"

class _SPI
{
	private:

		SPI_TypeDef* SPI_ID;

	public:

		explicit _SPI(SPI_TypeDef* SPI_ID);

		void low_CS();
		void hig_CS();

		uint8_t transfer_Byte(uint8_t byte);
};

#endif
