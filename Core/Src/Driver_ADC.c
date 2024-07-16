#include "Driver_ADC.h"

volatile ADC_RAW_DATA adc_raw_data = {0, 0, 0, 0, SUPPLY_VOLTAGE_LEVEL, 0};
volatile ADC_STATE adc_state = {0};

static void Cycle_Delay(void)
{
	for(int i = 0; i < 5000; i++);
}

static void Enable_DMA (void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_Channel1->CNDTR = NUMBER_OF_ADC_CHANNELS;
	DMA1_Channel1->CMAR  = (uint32_t)(&adc_raw_data);
	DMA1_Channel1->CPAR  = (uint32_t)(&(ADC1->DR));

	DMA1_Channel1->CCR   = DMA_CCR_MSIZE_0
						|  DMA_CCR_PSIZE_0
						|  DMA_CCR_PL_1
						|  DMA_CCR_MINC
						|  DMA_CCR_CIRC
						|  DMA_CCR_EN;
}

static void Enable_ADC (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	ADC1->CFGR2   =	ADC_CFGR2_CKMODE_Msk
				 |	ADC_CFGR2_OVSR_Msk
				 |	ADC_CFGR2_OVSS_3
				 |	ADC_CFGR2_OVSE;

	ADC1->CR 	 |= ADC_CR_ADVREGEN
				 |  ADC_CR_ADCAL;
	while(ADC1->CR & ADC_CR_ADCAL);

	ADC->CCR 	 |= ADC_CCR_VREFEN
				 |  ADC_CCR_TSEN;

	ADC1->CHSELR  = ADC_CHSELR_CHSEL8
				 |  ADC_CHSELR_CHSEL9
				 |	ADC_CHSELR_CHSEL17
				 |	ADC_CHSELR_CHSEL18;

	ADC1->CFGR1  |= ADC_CFGR1_AUTOFF
				 |	ADC_CFGR1_DMACFG
				 |  ADC_CFGR1_DMAEN
				 |	ADC_CFGR1_WAIT;

	ADC1->IER	 |= ADC_IER_EOSIE;

	ADC1->CR 	 |= ADC_CR_ADEN;

	NVIC_SetPriority(ADC1_COMP_IRQn, 1);
	NVIC_EnableIRQ(ADC1_COMP_IRQn);
}

static void Measuring_circuits_enable(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

	GPIOB->MODER |= GPIO_MODER_MODE2_Msk;
	GPIOB->MODER &=~GPIO_MODER_MODE2_1;
	GPIOB->BSRR  |= GPIO_BSRR_BS_2;

	Cycle_Delay();
}
static void Measuring_circuits_disable(void)
{
	GPIOB->BSRR |= GPIO_BSRR_BR_2;
	RCC->IOPENR &=~RCC_IOPENR_GPIOBEN;
}

void Driver_ADC_enable(void)
{
	Enable_DMA();
	Enable_ADC();
}

void Run_single_measurement(void)
{
	if	 (adc_state == BUSY){return;}
	else {adc_state =  BUSY;}

	Measuring_circuits_enable();

	ADC1->CR |= ADC_CR_ADSTART;

	while(adc_state == BUSY);
}

void ADC_COMP_IRQHandler(void)
{
	if((ADC1->ISR & ADC_ISR_EOS) == ADC_ISR_EOS)
	{
		adc_raw_data.signal  = adc_raw_data.ina333_output - adc_raw_data.tpr3312_output;
		adc_raw_data.signal -= ADC_INPUT_OFFSET_LEVEL;

		ADC1->ISR |= ADC_ISR_EOS;

		Measuring_circuits_disable();

		adc_state = FREE;
	}

	NVIC_ClearPendingIRQ(ADC1_COMP_IRQn);
}
