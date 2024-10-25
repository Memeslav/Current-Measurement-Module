#include "main.hpp"

LED LEDS[4] =
{
    LED(LED::OFF, LED::RED, RCC_IOPENR_GPIOAEN, 15),
    LED(LED::OFF, LED::BLU, RCC_IOPENR_GPIOBEN,  3),
    LED(LED::OFF, LED::YEL, RCC_IOPENR_GPIOBEN,  4),
    LED(LED::OFF, LED::GRN, RCC_IOPENR_GPIOBEN,  5)
};

int main(void)
{
    while(1)
    {

    }
}
