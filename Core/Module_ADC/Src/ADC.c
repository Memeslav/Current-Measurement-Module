#include "ADC.h"

struct ADC_Data { ADC_State_e state; ADC_Level_t channels[ADC_CHANNELS];} ADC_Data = {0};

static void ADC_Enable(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

		ADC1->CFGR2 	|= ADC_CFGR2_CKMODE_Msk	| ADC_CFGR2_OVSR_Msk 	| ADC_CFGR2_OVSS_3 		| ADC_CFGR2_OVSE;
		ADC->CCR 		|= ADC_CCR_VREFEN 		| ADC_CCR_TSEN;
		ADC1->CR 	 	|= ADC_CR_ADVREGEN		| ADC_CR_ADCAL;
		while(ADC1->CR & ADC_CR_ADCAL);
		ADC1->CHSELR	|= ADC_CHSELR_CHSEL8 	| ADC_CHSELR_CHSEL9 	| ADC_CHSELR_CHSEL17 	| ADC_CHSELR_CHSEL18;
		ADC1->CFGR1 	|= ADC_CFGR1_AUTOFF 	| ADC_CFGR1_DMACFG 		| ADC_CFGR1_DMAEN;
		ADC1->IER 		|= ADC_IER_EOSIE;
		ADC1->CR 		|= ADC_CR_ADEN;
}

static ADC_State_e Get_State 	(void) 					{return ADC_Data.state;}
static ADC_Level_t Get_Channel	(ADC_Channel_e channel)	{return ADC_Data.channels[channel];}
static void Get_All_Channels 	(ADC_Level_t *data) 	{for (int i = 0; i < ADC_CHANNELS; i++)
														 {data[i] = ADC_Data.channels[i];}		}

static void Measure				(void)					{if(ADC_Data.state == Measure_in_Progress) {return;}
														 ADC_Data.state = Measure_in_Progress;
														 ADC1->CR |= ADC_CR_ADSTART;
														 DMA_Waiting_Transmission();
														 ADC_Data.state = Measure_is_Complete;	}

static void Clear				(void)					{ADC_Data.state = Measure_is_Complete;
														 for (int i = 0; i < ADC_CHANNELS; i++)
														 {ADC_Data.channels[i] = 0;}}

void ADC_Init(ADC_t *adc)
{
	ADC_Enable();
	DMA_Enable(&(ADC1->DR), (uint32_t*)ADC_Data.channels, ADC_CHANNELS);

	adc->state 		= &ADC_Data.state;
	adc->channels 	=  ADC_Data.channels;

	adc->measure 			= Measure;
	adc->get_state 			= Get_State;
	adc->get_channel		= Get_Channel;
	adc->get_all_channels	= Get_All_Channels;
	adc->clear				= Clear;
}
