#ifndef DMA_CH1_H_
#define DMA_CH1_H_

#include "stm32l053xx.h"

typedef enum	{	DMA_STATUS_IDLE 	= 0,
    				DMA_STATUS_BUSY		= 1,
					DMA_STATUS_COMPLETE	= 2,
					DMA_STATUS_ERROR	= 3,}	DMA_Status_t;

typedef struct	{	DMA_Status_t 	status;
					uint32_t 		from;
					uint32_t		to;
					uint8_t 		data_size;}	DMA_Channel_t;

static inline void DMA_Init	(	DMA_Channel_t* 	DMA_Channel,
								uint32_t 		from,
								uint32_t 		to,
								uint32_t 		data_size)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel1->CMAR		 = (uint32_t)(&to);
		DMA1_Channel1->CPAR		 = (uint32_t)(&from);
		DMA1_Channel1->CNDTR	 = 	data_size;
		DMA1_Channel1->CCR		|=	DMA_CCR_HTIE | DMA_CCR_MSIZE_0 	| DMA_CCR_PSIZE_0 | DMA_CCR_PL_Msk
								| 	DMA_CCR_MINC | DMA_CCR_CIRC 	| DMA_CCR_EN;

	NVIC_SetPriority(DMA1_Channel1_IRQn, 0);	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

void DMA1_Channel1_IRQHandler(void)
{
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        DMA1->IFCR |= DMA_IFCR_CHTIF1;
    }
    NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
}

#endif
