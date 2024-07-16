#include "Module_PKM.h"

typedef struct
{
	uint16_t data[SPI_BUFFER_SIZE];

	uint16_t index;
	uint16_t command;
	uint16_t start_address;
	uint16_t register_count;
}
SPI_BUFFER;
SPI_BUFFER buffer = {{0}, 0, 0, 0, 0};

static void CRC_Enable(void)
{
	RCC->AHBENR |= RCC_AHBENR_CRCEN;

		CRC->CR |= CRC_CR_RESET;
		CRC->CR |= CRC_CR_REV_OUT;
		CRC->CR |= CRC_CR_REV_IN_0;
		CRC->CR |= CRC_CR_POLYSIZE_0;

		CRC->POL  = 0x8005;
		CRC->INIT = 0xFFFF;
}

static void SPI1_Enable (void)
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

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

    RCC->APB2ENR  |= RCC_APB2ENR_SPI1EN;

    	SPI1->CR2  = SPI_CR2_RXNEIE;

		SPI1->CR1  = SPI_CR1_CPHA
				  |  SPI_CR1_CPOL
				  |  SPI_CR1_DFF
				  |  SPI_CR1_SPE;

	NVIC_SetPriority(SPI1_IRQn, 0);
	NVIC_EnableIRQ(SPI1_IRQn);
}

void Module_PKM_Enable(void)
{
	CRC_Enable();
	SPI1_Enable();
}

void Show_impulse_in_window(void)
{
	uint32_t impulse_num = (uint32_t)(registers.controls.show_pulse_num_hi << 16)|registers.controls.show_pulse_num_lo;

	registers.impulse = impulse_archive.impulse[impulse_num % 128];
}

void EXTI4_15_IRQHandler(void)
{
	if(EXTI->PR & EXTI_PR_PIF4)
	{
		if(!(GPIOA->IDR & GPIO_IDR_ID4))
		{
			MSI_set_max_frequency();

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

			MSI_set_min_frequency();
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

						if((i == MIN_WIDT_L) ||
						   (i == MIN_WIDT_H) ||
						   (i == TRIG_LVL)   ||
						   (i == HSTERSIS))
						{
							Update_impulse_settings();
							LOAD_REGISTERS_TO_FRAM();
						}
						else if(i == SHW_PULS_L)
						{
							Show_impulse_in_window();
							LOAD_REGISTERS_TO_FRAM();
						}
						else if(i == MEAS_PER)
						{
							RTC_Set_WakeUp_Timer();
							LOAD_REGISTERS_TO_FRAM();
						}

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
				if(buffer.start_address == UNIXTIME_L)
				{Load_currents_into_registers();}

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
