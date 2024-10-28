#ifndef DMA_HPP_
#define DMA_HPP_

#include "stm32l053xx.h"

class _DMA
{
	private:

		DMA_TypeDef* DMA_ID;

	public:

		_DMA(DMA_TypeDef* DMA_ID);
};

#endif
