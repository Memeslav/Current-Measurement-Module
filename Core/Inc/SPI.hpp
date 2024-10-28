#ifndef SPI_HPP_
#define SPI_HPP_

#include "stm32l053xx.h"

class _SPI
{
	private:

		SPI_TypeDef* SPI_ID;

	public:

		_SPI(SPI_TypeDef* SPI_ID);

		void low_CS(void);
		void hig_CS(void);

		uint8_t transfer_byte(uint8_t byte);
};

#endif
