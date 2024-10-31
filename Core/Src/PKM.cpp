#include "PKM.hpp"

PKM::PKM(SPI_TypeDef* SPI_ID, CRC_TypeDef* CRC_ID) : spi(SPI_ID), crc(CRC_ID)
{
	EXTI_Init();
}

void PKM::EXTI_Init(void)
{
	EXTI->IMR 	 |=   EXTI_IMR_IM4;
	EXTI->RTSR   |=   EXTI_RTSR_RT4;
	EXTI->FTSR   |=   EXTI_FTSR_FT4;

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

inline void PKM::get_Command_and_Address(void)
{
    buffer.command       = static_cast<PKM::PKM_COMMAND>(buffer.data[0] & COMMAND_MASK);
    buffer.start_address = 								(buffer.data[0] & ADDRESS_MASK);
}
inline void PKM::get_Register_Count(void)
{
	buffer.register_count = __REV16(buffer.data[1]);
}


void PKM::EXTI_Handler(void)
{
    if (EXTI->PR & EXTI_PR_PIF4)
    {
        if (!(GPIOA->IDR & GPIO_IDR_ID4))
        {
            //memset(&buffer, 0, sizeof(buffer));
            //CRC_ID.reset();
        }

        EXTI->PR |= EXTI_PR_PIF4;
    }

    NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
}

extern "C" {void EXTI4_15_IRQHandler(void);}

extern "C" {void EXTI4_15_IRQHandler(void)
{
	//pkm.EXTI_Handler();
	//PKM::EXTI_Handler();
}

extern "C" void SPI1_IRQHandler(void)
{
	/*
	if (SPI1->SR & SPI_SR_RXNE)
	    {
	        buffer.data[buffer.index] = SPI1->DR;

	        if (buffer.index == 0) Get_Command_and_Address();
	        if (buffer.index == 1) Get_Register_Count();

	        if (buffer.command)
	        {
	            WriteDataFromPKM();
	        }
	        else
	        {
	            LoadDataToPKM();
	        }

	        buffer.index++;
	    }

	    NVIC_ClearPendingIRQ(SPI1_IRQn);
	*/
}


