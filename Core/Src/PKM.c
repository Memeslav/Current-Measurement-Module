#include "PKM.h"


#define 	PKM_BUFFER_SIZE		32U
#define 	UPDATE_DELAY		30U

typedef struct
{
	uint16_t data[PKM_BUFFER_SIZE];

	uint16_t index;
	uint16_t command;
	uint16_t start_address;
	uint16_t register_count;
}
SPI_BUFFER;
SPI_BUFFER buffer = {{0}, 0, 0, 0, 0};

void PKM_Enable(void)
{
	CRC_Enable();
	SPI1_Enable();
}

void EXTI4_15_IRQHandler(void)
{
	if(EXTI->PR & EXTI_PR_PIF4)
	{
		if(!(GPIOA->IDR & GPIO_IDR_ID4))
		{
			GPIOA->MODER |=	 GPIO_MODER_MODE6_Msk;
			GPIOA->MODER &=	~GPIO_MODER_MODE6_0;

			memset(&buffer, 0, sizeof(buffer));
			CRC->CR |= CRC_CR_RESET;
		}
		else
		{
			GPIOA->MODER |=	 GPIO_MODER_MODE6_Msk;
			GPIOA->MODER &=	~GPIO_MODER_MODE6_1;
			GPIOA->BSRR |= GPIO_BSRR_BR_6;
		}

		EXTI->PR |= EXTI_PR_PIF4;
	}
	NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
}
void SPI1_IRQHandler(void)
{
	if(SPI1->SR & SPI_SR_RXNE)
	{
		buffer.data[buffer.index] = SPI1->DR;

		if(buffer.index == 0)
		{
			buffer.command 			= buffer.data[0] & 0x8000;
			buffer.start_address 	= buffer.data[0] & 0x7FFF;
		}

		if(buffer.index == 1)
		{
			buffer.register_count  = __REV16(buffer.data[1]);
		}

		if(buffer.command)
		{
			if(buffer.index == (2 + buffer.register_count))
			{
				for(uint8_t i = 0; i < buffer.index; i++)
				{
					*((__IO uint16_t *)&CRC->DR) = buffer.data[i];
				}

				if(__REV16(CRC->DR) == buffer.data[buffer.index])
				{
					uint8_t increment = 0;

					for(uint8_t i = buffer.start_address; i < (buffer.start_address + buffer.register_count); i++)
					{
						regs[i] = __REV16(buffer.data[2 + increment]);

						increment++;
					}
				}
			}
		}
		else
		{
			if		(buffer.index == 0)
	        {
				*((__IO uint16_t *)&CRC->DR) = buffer.start_address;
									SPI1->DR = buffer.start_address;
	        }
			else if	(buffer.index == 1)
	        {
				*((__IO uint16_t *)&CRC->DR) = __REV16(buffer.register_count);
									SPI1->DR = __REV16(buffer.register_count);
	        }
			else if	(buffer.index <  (2 + buffer.register_count))
	        {
				*((__IO uint16_t *)&CRC->DR) = __REV16(regs[buffer.start_address]);
									SPI1->DR = __REV16(regs[buffer.start_address]);
									buffer.start_address++;
	        }
			else if (buffer.index == (2 + buffer.register_count))
	        {
				SPI1->DR = __REV16(CRC->DR);
	        }
		}

		buffer.index++;
	}

	NVIC_ClearPendingIRQ(SPI1_IRQn);
}
