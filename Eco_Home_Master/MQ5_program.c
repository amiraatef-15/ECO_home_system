#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "MQ5_interface.h"

static u8 MQ5_channel = 0;

void MQ5_vInit(u8 channel)
{
    MQ5_channel = channel;
}

void MQ5_u8GetGasPercentage(u8* gas_percent)
{
    u16 adc_value = 0;
    if (gas_percent == 0) return;

    ADC_u8GetResultSync(MQ5_channel, &adc_value);

    // Clamp adc_value between clean air and max gas
    if (adc_value < MQ5_CLEAN_AIR_ADC) adc_value = MQ5_CLEAN_AIR_ADC;
    if (adc_value > MQ5_MAX_GAS_ADC) adc_value = MQ5_MAX_GAS_ADC;

    // Calculate percentage without math library
    // percent = ((adc_value - clean_air) * 100) / (max_gas - clean_air)
    u32 temp = adc_value - MQ5_CLEAN_AIR_ADC;
    temp = temp * 100;
    temp = temp / (MQ5_MAX_GAS_ADC - MQ5_CLEAN_AIR_ADC);

    *gas_percent = (u8)temp;
}

void MQ5_u8GetAirPurity(u8* air_purity)
{
    u8 gas_percent = 0;
    if (air_purity == 0) return;

    MQ5_u8GetGasPercentage(&gas_percent);

    // Air purity is the inverse of gas percentage
    *air_purity = 100 - gas_percent;
}