#include "Digital_processor.h"

PCB_INFO pcb_info = {0};

static void Supply_voltage_calculation(void)
{
	pcb_info.power_supply_V = INTERNAL_REFERENCE_VOLTAGE * SUPPLY_VOLTAGE_LEVEL;
	pcb_info.power_supply_V /= adc_raw_data.internal_ref;
}

static void INA333_gain_update(void)
{
	pcb_info.ina333_gain = (float)registers.calibration.value / 100;
}
static float From_level_to_mVolt(int level)
{
	return (100000 * ((pcb_info.power_supply_V/ADC_MAXIMAL_LEVEL) * (1.0*level)/pcb_info.ina333_gain));
}
static int From_mVolt_to_level(float mVolt)
{
	return ((mVolt / 100000) * pcb_info.ina333_gain * ADC_MAXIMAL_LEVEL / pcb_info.power_supply_V);
}

static void PCB_info_update(void)
{
	Supply_voltage_calculation();
	Temperature_calculation(&pcb_info.temperature_C);
	INA333_gain_update();
}

static void Impulse_to_archive(void)
{
	IMPULSE buffer = {0};
	Impulse_cut(&buffer);

	PCB_info_update();

	buffer.num_lo  = registers.controls.global_counter_lo;
	buffer.num_hi  = registers.controls.global_counter_hi;
    buffer.max_amp = From_level_to_mVolt(buffer.max_amp);
	buffer.ave_amp = From_level_to_mVolt(buffer.ave_amp);

	uint32_t impulse_num = (uint32_t)(buffer.num_hi << 16)|(buffer.num_lo << 0);

	impulse_archive.impulse[impulse_num % IMPULSE_ARCHIVE_SIZE] = buffer;

    if (++(registers.controls.global_counter_lo) == 0)
       {++(registers.controls.global_counter_hi);}
}

void Load_currents_into_registers(void)
{
	CURRENTS buffer = {0};
	Currents_cut(&buffer);

	PCB_info_update();

	registers.currents.max = From_level_to_mVolt(buffer.max);
	registers.currents.ave = From_level_to_mVolt(buffer.ave);
	registers.currents.min = From_level_to_mVolt(buffer.min);
}

void Update_impulse_settings(void)
{
	PCB_info_update();

	int16_t _trigger = From_mVolt_to_level(registers.settings.trigger_level);

	impulse_settings.hysteresis = From_mVolt_to_level(registers.settings.hysteresis);

	impulse_settings.trigger.upper_limit = _trigger + impulse_settings.hysteresis;
	impulse_settings.trigger.down_limit  = _trigger - impulse_settings.hysteresis;

	impulse_settings.minimal_duration = (uint32_t)(registers.settings.minimal_width_hi << 16) | registers.settings.minimal_width_lo;
}

void Update_data_from_ADC(void)
{
	Run_single_measurement();

	Currents_update();

	if(Impulse_update() == IMPULSE_IS_READY){Impulse_to_archive();}
}
void Digital_processor_enable(void)
{
	Driver_ADC_enable();
	Update_data_from_ADC();
	Update_impulse_settings();
}
