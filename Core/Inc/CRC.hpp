#ifndef CRC_HPP_
#define CRC_HPP_

#include "stm32l053xx.h"

class _CRC
{
	private:

		CRC_TypeDef* CRC_ID;

	public:

		explicit _CRC(CRC_TypeDef* CRC_ID);

		void reset();
};

#endif
