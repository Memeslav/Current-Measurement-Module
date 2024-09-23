#include <LEDS.h>

uint16_t led_delay = 1000;

void LED_Init(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE9);
	GPIOA->MODER &= ~(GPIO_MODER_MODE10);

	GPIOA->PUPDR |= GPIO_PUPDR_PUPD9_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD10_0;
}

uint8_t LED_Check_Jumper(void)
{
    if (!(GPIOA->IDR & GPIO_IDR_ID9) || !(GPIOA->IDR & GPIO_IDR_ID10))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void LED_RED_ON (void)
{
	RCC->IOPENR  |=   RCC_IOPENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE15_Msk);
	GPIOA->MODER |=  GPIO_MODER_MODE15_0;

	GPIOA->BSRR  |=   GPIO_BSRR_BS_15;
}
void LED_RED_OFF(void)
{
	GPIOA->BSRR  |=   GPIO_BSRR_BR_15;
}

void LED_RED_TOGGLE(void)
{
	LED_RED_ON();

	for(int i = 0; i <= led_delay; i++){}

	LED_RED_OFF();
}

void LED_BLU_ON (void)
{
	RCC->IOPENR  |=   RCC_IOPENR_GPIOBEN;

	GPIOB->MODER &= ~(GPIO_MODER_MODE3_Msk);
	GPIOB->MODER |=  GPIO_MODER_MODE3_0;

	GPIOB->BSRR  |=   GPIO_BSRR_BS_3;
}
void LED_BLU_OFF(void)
{
	GPIOB->BSRR  |=   GPIO_BSRR_BR_3;
}

void LED_BLU_TOGGLE(void)
{
	LED_BLU_ON();

	for(int i = 0; i <= led_delay; i++){}

	LED_BLU_OFF();
}

void LED_YEL_ON (void)
{
	RCC->IOPENR  |=   RCC_IOPENR_GPIOBEN;

	GPIOB->MODER &= ~(GPIO_MODER_MODE4_Msk);
	GPIOB->MODER |=  GPIO_MODER_MODE4_0;

	GPIOB->BSRR  |=   GPIO_BSRR_BS_4;
}
void LED_YEL_OFF(void)
{
	GPIOB->BSRR  |=   GPIO_BSRR_BR_4;
}

void LED_YEL_TOGGLE(void)
{
	LED_YEL_ON();

	for(int i = 0; i <= led_delay; i++){}

	LED_YEL_OFF();
}

void LED_GRN_ON (void)
{
	RCC->IOPENR  |=   RCC_IOPENR_GPIOBEN;

	GPIOB->MODER &= ~(GPIO_MODER_MODE5_Msk);
	GPIOB->MODER |=  GPIO_MODER_MODE5_0;

	GPIOB->BSRR  |=   GPIO_BSRR_BS_5;
}
void LED_GRN_OFF(void)
{
	GPIOB->BSRR  |=   GPIO_BSRR_BR_5;
}

void LED_GRN_TOGGLE(void)
{
	LED_GRN_ON();

	for(int i = 0; i <= led_delay; i++){}

	LED_GRN_OFF();
}
