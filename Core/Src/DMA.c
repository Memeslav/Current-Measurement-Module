#include "DMA.h"

uint8_t FILLER = 0xFF;


void DMA1_Init(void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    	DMA1_CSELR->CSELR |= (CxS_ADC  << DMA_CSELR_C1S_Pos)|	//ADC
    						 (CxS_SPI2 << DMA_CSELR_C4S_Pos)|	//SPI1_RX
							 (CxS_SPI2 << DMA_CSELR_C5S_Pos);	//SPI1_TX
}

void DMA1_Ch_4(uint32_t* data_target, uint32_t size)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel4->CNDTR = size;

		DMA1_Channel4->CPAR = (uint32_t)(&(SPI2->DR));
		DMA1_Channel4->CMAR = (uint32_t)(data_target);

		DMA1_Channel4->CCR =  DMA_CCR_PL_Msk | DMA_CCR_MINC | DMA_CCR_EN;
}

void DMA1_Ch_5(uint32_t* data_source, uint32_t size)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel5->CNDTR = size;

		DMA1_Channel5->CPAR = (uint32_t)(&(SPI2->DR));
		DMA1_Channel5->CMAR = (uint32_t)(data_source);

		DMA1_Channel5->CCR =  DMA_CCR_PL_Msk | DMA_CCR_MINC |
							  DMA_CCR_DIR 	 | DMA_CCR_EN;
}

void DMA1_Channel2_3_IRQHandler(void)
{
	if(DMA1->ISR & DMA_ISR_TCIF2)
	{

	}
	if(DMA1->ISR & DMA_ISR_TCIF3)
	{

	}
}
