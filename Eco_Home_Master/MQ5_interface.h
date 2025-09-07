#ifndef MQ5_INTERFACE_H
#define MQ5_INTERFACE_H

#define MQ5_CLEAN_AIR_ADC   100   // ADC value in clean air (calibrate as needed)
#define MQ5_MAX_GAS_ADC     900   // ADC value in max gas (calibrate as needed)

void MQ5_vInit(u8 channel);
void MQ5_u8GetGasPercentage(u8* gas_percent);
void MQ5_u8GetAirPurity(u8* air_purity);

#endif