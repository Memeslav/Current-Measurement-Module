#include "DMA.h"

#define CxS_ADC	0b0000U

void DMA1_Ch_1_Enable(volatile void* data_collector, uint8_t data_size)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_CSELR->CSELR |= (CxS_ADC << DMA_CSELR_C1S_Pos);

	DMA1_Channel1->CNDTR = data_size;
	DMA1_Channel1->CMAR  = (uint32_t)(data_collector);
	DMA1_Channel1->CPAR  = (uint32_t)(&(ADC1->DR));

	DMA1_Channel1->CCR   = DMA_CCR_MSIZE_0
						|  DMA_CCR_PSIZE_0
						|  DMA_CCR_PL_1
						|  DMA_CCR_MINC
						|  DMA_CCR_CIRC
						|  DMA_CCR_EN;
}
