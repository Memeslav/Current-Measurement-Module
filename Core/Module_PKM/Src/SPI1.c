#include "SPI1.h"

void SPI1_Enable (void)
{
    RCC->IOPENR   |= RCC_IOPENR_GPIOAEN;

    	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk
				  	 |    GPIO_MODER_MODE5_Msk
					 |    GPIO_MODER_MODE6_Msk
					 |    GPIO_MODER_MODE7_Msk);

		GPIOA->MODER |=	  GPIO_MODER_MODE4_1
					 |	  GPIO_MODER_MODE5_1
					 |    GPIO_MODER_MODE6_1
					 |    GPIO_MODER_MODE7_1;

		EXTI->IMR 	 |=   EXTI_IMR_IM4;
		EXTI->RTSR   |=   EXTI_RTSR_RT4;
		EXTI->FTSR   |=   EXTI_FTSR_FT4;

	NVIC_SetPriority(EXTI4_15_IRQn, 2);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

    RCC->APB2ENR  |= RCC_APB2ENR_SPI1EN;

    	SPI1->CR2  = SPI_CR2_RXNEIE;

		SPI1->CR1  = SPI_CR1_CPHA
				  |  SPI_CR1_CPOL
				  |  SPI_CR1_DFF
				  |  SPI_CR1_SPE;

	NVIC_SetPriority(SPI1_IRQn, 3);
	NVIC_EnableIRQ(SPI1_IRQn);
}
