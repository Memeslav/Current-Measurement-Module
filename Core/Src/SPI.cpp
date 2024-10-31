#include "SPI.hpp"

_SPI::_SPI(SPI_TypeDef* SPI_ID) : SPI_ID(SPI_ID)
{
    SPI_Init ();
    GPIO_Init();
}

void _SPI::SPI_Init()
{
    if (SPI_ID == SPI1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

			SPI1->CR2  = SPI_CR2_RXNEIE;
			SPI1->CR1  = SPI_CR1_CPHA | SPI_CR1_CPOL | SPI_CR1_DFF | SPI_CR1_SPE;

		NVIC_SetPriority(SPI1_IRQn, 0);
		NVIC_EnableIRQ(SPI1_IRQn);
    }
    else if (SPI_ID == SPI2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

			SPI_ID->CR2 = 0;
			SPI_ID->CR1 = SPI_CR1_MSTR | SPI_CR1_SPE | SPI_CR1_SSM | SPI_CR1_SSI;
    }
}

void _SPI::GPIO_Init()
{
    if (SPI_ID == SPI1)
    {
        RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

        GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk |
                          GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk);

        GPIOA->MODER |= (GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1 |
                         GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
    }
    else if (SPI_ID == SPI2)
    {
        RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

        GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk | GPIO_MODER_MODE13_Msk |
                          GPIO_MODER_MODE14_Msk | GPIO_MODER_MODE15_Msk);

        GPIOB->MODER |= (GPIO_MODER_MODE12_0 | GPIO_MODER_MODE13_1 |
                         GPIO_MODER_MODE14_1 | GPIO_MODER_MODE15_1);
    }
}

void _SPI::low_CS()	{if (SPI_ID == SPI2) {GPIOB->BSRR = GPIO_BSRR_BR_12;}}

void _SPI::hig_CS()	{if (SPI_ID == SPI2) {GPIOB->BSRR = GPIO_BSRR_BS_12;}}

uint8_t _SPI::transfer_Byte(uint8_t byte)
{
    uint32_t timeout = TIMEOUT_LIMIT;

    while (!(SPI_ID->SR & SPI_SR_TXE) && --timeout);
    if (timeout == 0) return 0xFF;
    SPI_ID->DR = byte;

    timeout = TIMEOUT_LIMIT;
    while (!(SPI_ID->SR & SPI_SR_RXNE) && --timeout);
    return timeout ? SPI_ID->DR : 0xFF;
}
