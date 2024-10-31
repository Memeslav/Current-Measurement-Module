#ifndef PKM_HPP_
#define PKM_HPP_

#include <string.h>

#include "MEM.hpp"
#include "SPI.hpp"
#include "CRC.hpp"

class PKM
{
public:

    enum PKM_COMMAND : uint8_t
    {
        READ  = 0,
        WRITE = 1,
    };

private:

    _SPI spi;
    _CRC crc;

	void EXTI_Init();

    static constexpr uint16_t UPDATE_DELAY = 30U;
    static constexpr uint16_t BUFFER_SIZE  = 32U;

    static constexpr uint16_t COMMAND_MASK  = 0x8000;
    static constexpr uint16_t ADDRESS_MASK  = 0x7FFF;

    struct Buffer
    {
        PKM_COMMAND command = READ;
        uint16_t register_count = 0;
        uint16_t index = 0;
        uint16_t start_address = 0;
        uint16_t data[BUFFER_SIZE] = {0};
    }
    buffer;

    inline void 	get_Command_and_Address(void);
    inline void 	get_Register_Count(void);

    void 	write_Data_from_PKM(void);
    void 	load_Data_to_PKM(void);

public:

    PKM(SPI_TypeDef* SPI_ID, CRC_TypeDef* CRC_ID);

    void EXTI_Handler(void);
    void SPI_Handler (void);
};

#endif
