#include "FRAM.hpp"

void MB85RS64PNF::read(uint16_t address, uint16_t data_size, uint8_t* data)
{
    EnableCS();
    spi.transfer_byte(static_cast<uint8_t>(MB85RS64PNF::MB85RS64PNF_CODE::READ));
    spi.transfer_byte(address >> 8);
    spi.transfer_byte(address & 0xFF);

    for (uint16_t i = 0; i < data_size; i++)
    {
        data[i] = spi.transfer_byte(0x00);
    }

    DisableCS();
}

void MB85RS64PNF::write(uint16_t address, uint16_t data_size, uint8_t* data)
{
    EnableCS();
    spi.transfer_byte(static_cast<uint8_t>(MB85RS64PNF::MB85RS64PNF_CODE::WREN));
    DisableCS();

    EnableCS();
    spi.transfer_byte(static_cast<uint8_t>(MB85RS64PNF::MB85RS64PNF_CODE::WRITE));
    spi.transfer_byte(address >> 8);
    spi.transfer_byte(address & 0xFF);

    for (uint16_t i = 0; i < data_size; i++)
    {
        spi.transfer_byte(data[i]);
    }

    DisableCS();
}
