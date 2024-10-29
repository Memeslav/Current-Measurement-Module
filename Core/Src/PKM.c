#include "PKM.h"
#include <string.h>

#define PKM_BUFFER_SIZE  32U
#define UPDATE_DELAY     30U

typedef struct {
    uint16_t data[PKM_BUFFER_SIZE];
    uint16_t index;
    uint16_t command;
    uint16_t start_address;
    uint16_t register_count;
} SPI_BUFFER;

static SPI_BUFFER buffer = {{0}, 0, 0, 0, 0};

// Включаем необходимые периферийные модули
void PKM_Enable(void) {
    CRC_Enable();
    SPI1_Enable();
};

// Сброс и очистка буфера при прерывании на внешней линии
void EXTI4_15_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PIF4) {
        if (!(GPIOA->IDR & GPIO_IDR_ID4)) {
            memset(&buffer, 0, sizeof(buffer));
            CRC->CR |= CRC_CR_RESET; // Сброс модуля CRC
        }
        EXTI->PR |= EXTI_PR_PIF4;
    }
    NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
}

// Извлечение команды и начального адреса из первого элемента буфера данных
static inline void ParseCommandAndAddress(void) {
    buffer.command       = buffer.data[0] & 0x8000;
    buffer.start_address = buffer.data[0] & 0x7FFF;
}

// Извлечение количества регистров из второго элемента буфера данных
static inline void ParseRegisterCount(void) {
    buffer.register_count = __REV16(buffer.data[1]);
}

// Запись данных из буфера в регистры, если CRC совпадает
static void WriteDataFromPKM(void) {
    if (buffer.index != (2 + buffer.register_count)) return;

    // Проверка CRC данных
    for (uint8_t i = 0; i < buffer.index; i++) {
        *((__IO uint16_t *)&CRC->DR) = buffer.data[i];
    }

    if (__REV16(CRC->DR) == buffer.data[buffer.index]) {
        // Обновление регистров
        for (uint8_t i = 0; i < buffer.register_count; i++) {
            regs[buffer.start_address + i] = __REV16(buffer.data[2 + i]);
        }
    }
}

// Загрузка данных в SPI с CRC-контролем
static void LoadDataToPKM(void) {
    switch (buffer.index) {
        case 0:
            *((__IO uint16_t *)&CRC->DR) = buffer.start_address;
            SPI1->DR = buffer.start_address;
            break;
        case 1:
            *((__IO uint16_t *)&CRC->DR) = __REV16(buffer.register_count);
            SPI1->DR = __REV16(buffer.register_count);
            break;
        default:
            if (buffer.index < (2 + buffer.register_count)) {
                *((__IO uint16_t *)&CRC->DR) = __REV16(regs[buffer.start_address]);
                SPI1->DR = __REV16(regs[buffer.start_address]);
                buffer.start_address++;
            } else if (buffer.index == (2 + buffer.register_count)) {
                SPI1->DR = __REV16(CRC->DR);
            }
            break;
    }
}

// Обработчик прерывания SPI1
void SPI1_IRQHandler(void) {
    if (SPI1->SR & SPI_SR_RXNE) {
        buffer.data[buffer.index] = SPI1->DR;

        // Парсинг команды и регистра только на первых шагах
        if (buffer.index == 0) ParseCommandAndAddress();
        if (buffer.index == 1) ParseRegisterCount();

        // Выбор операции в зависимости от команды
        if (buffer.command) {
            WriteDataFromPKM();
        } else {
            LoadDataToPKM();
        }

        buffer.index++;
    }
    NVIC_ClearPendingIRQ(SPI1_IRQn);
}
