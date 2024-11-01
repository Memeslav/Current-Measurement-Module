#include "DMA.h"

void DMA1_Init(void)
{

}

void DMA1_Ch_1(uint32_t* src_address, uint32_t* dest_address, uint32_t num_data)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel1->CNDTR = num_data;

    DMA1_Channel1->CPAR = (uint32_t)src_address;
    DMA1_Channel1->CMAR = (uint32_t)dest_address;

    DMA1_Channel1->CCR =  DMA_CCR_MSIZE_0 |
                          DMA_CCR_PSIZE_0 |
                          DMA_CCR_CIRC    |
                          DMA_CCR_MINC    |
                          DMA_CCR_PL_1    |
                          DMA_CCR_EN;
}
