#include "Module_PKM.h"
#include <string.h>

uint16_t* regs = (uint16_t*)&registers;

#define PKM_BUFFER_SIZE  32U
#define UPDATE_DELAY     30U

typedef struct
{
    uint16_t data[PKM_BUFFER_SIZE];
    uint16_t index;
    uint16_t command;
    uint16_t start_address;
    uint16_t register_count;
}
PKM_BUFFER;

static PKM_BUFFER buffer = {{0}, 0, 0, 0, 0};

void Module_PKM_Enable(void)
{
    CRC_Enable();
    SPI1_Enable();
};

void EXTI4_15_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PIF4)
    {
        if (!(GPIOA->IDR & GPIO_IDR_ID4))
        {
        	GPIOA->MODER |=	 GPIO_MODER_MODE6_Msk;
			GPIOA->MODER &=	~GPIO_MODER_MODE6_0;

        	memset(&buffer, 0, sizeof(buffer));
            CRC_Reset();
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


static inline void Get_Command_and_Address(void)
{
    buffer.command       = buffer.data[0] & 0x8000;
    buffer.start_address = buffer.data[0] & 0x7FFF;
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
            SPI1->DR = buffer.start_address;
            break;

        case 1:

        	CRC_Load(__REV16(buffer.register_count));
            SPI1->DR = __REV16(buffer.register_count);
            break;

        default:

            if (buffer.index < (2 + buffer.register_count))
            {
                CRC_Load(__REV16(regs[buffer.start_address]));
                SPI1->DR = __REV16(regs[buffer.start_address]);
                buffer.start_address++;
            }
            else if (buffer.index == (2 + buffer.register_count))
            {
                SPI1->DR = __REV16(CRC_Get_Result());
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
}
