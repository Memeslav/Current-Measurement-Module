#include "Module_PKM.h"

uint16_t* regs = (uint16_t*)&registers;

static PKM_buffer_t buffer = {0, {0}, 0, 0, 0};

void EXTI4_15_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PIF4)
    {
        if (!(GPIOA->IDR & GPIO_IDR_ID4))
        {
        	SPI1_MISO_Reset();
			buffer = (PKM_buffer_t){0};
            CRC_Reset();
        }
        else
        {
        	SPI1_MISO_Set();
        }

        EXTI->PR |= EXTI_PR_PIF4;
    }

    NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
}

static inline void Get_Command_and_Address(void)
{
	buffer.command = (PKM_command)((buffer.data[0] >> 15) & PKM_COMMAND_MASK);
    buffer.start_address = buffer.data[0] & PKM_ADDRESS_MASK;
}

static inline void Get_Register_Count(void)
{
    buffer.register_count = __REV16(buffer.data[1]);
}

static void WriteDataFromPKM(void)
{
    if (buffer.index != (2 + buffer.register_count)) return;

    for (uint8_t i = 0; i < buffer.index; i++)
    {
    	CRC_Load(buffer.data[i]);
    }

    if (__REV16(CRC_Get_Result()) == buffer.data[buffer.index])
    {
        for (uint8_t i = 0; i < buffer.register_count; i++)
        {
            regs[buffer.start_address + i] = __REV16(buffer.data[2 + i]);
        }
    }
}

static void LoadDataToPKM(void)
{
    switch (buffer.index)
    {
        case 0:
        	CRC_Load(buffer.start_address);
        	SPI1_Send_16b_frame(buffer.start_address);
            break;

        case 1:
        	CRC_Load(__REV16(buffer.register_count));
        	SPI1_Send_16b_frame(__REV16(buffer.register_count));
            break;

        default:
            if (buffer.index < (2 + buffer.register_count))
            {
                CRC_Load(__REV16(regs[buffer.start_address]));
                SPI1_Send_16b_frame(__REV16(regs[buffer.start_address]));
                buffer.start_address++;
            }
            else if (buffer.index == (2 + buffer.register_count))
            {
            	SPI1_Send_16b_frame(__REV16(CRC_Get_Result()));
            }
            break;
    }
}

void SPI1_IRQHandler(void)
{
    if (SPI1->SR & SPI_SR_RXNE)
    {
        buffer.data[buffer.index] = SPI1->DR;

        if (buffer.index == 0) Get_Command_and_Address();
        if (buffer.index == 1) Get_Register_Count();

        if (buffer.command == TRANSMIT_DATA)	{WriteDataFromPKM();}
        else									{LoadDataToPKM();}

        buffer.index++;
    }

    NVIC_ClearPendingIRQ(SPI1_IRQn);
}
