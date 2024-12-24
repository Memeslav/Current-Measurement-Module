#include "DMA1.h"

void DMA_Enable(volatile uint32_t* from, volatile uint32_t* to, uint8_t size)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel1->CMAR		 = (uint32_t)(to);
		DMA1_Channel1->CPAR		 = (uint32_t)(from);
		DMA1_Channel1->CNDTR	 = 	size;
		DMA1_Channel1->CCR		|=	DMA_CCR_MSIZE_0
								|	DMA_CCR_PSIZE_0
								|	DMA_CCR_PL_Msk
								| 	DMA_CCR_MINC
								|	DMA_CCR_CIRC
								|	DMA_CCR_EN;
}
