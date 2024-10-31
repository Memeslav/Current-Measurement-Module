#include "CRC.hpp"

_CRC::_CRC(CRC_TypeDef* CRC_ID) : CRC_ID(CRC_ID)
{
    RCC->AHBENR |= RCC_AHBENR_CRCEN;

    CRC_ID->CR |= CRC_CR_RESET;
    CRC_ID->CR |= CRC_CR_REV_OUT;
    CRC_ID->CR |= CRC_CR_REV_IN_0;
    CRC_ID->CR |= CRC_CR_POLYSIZE_0;

    CRC_ID->POL = 0x8005;
    CRC_ID->INIT = 0xFFFF;
}

void _CRC::reset()
{
    CRC_ID->CR |= CRC_CR_RESET;
}
