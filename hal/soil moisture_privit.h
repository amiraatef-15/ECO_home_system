/*
 * soil moisture_privit.h
 *
 *  Created on: Apr 4, 2025
 *      Author: Us
 */

#ifndef SOIL_MOISTURE_PRIVIT_H_
#define SOIL_MOISTURE_PRIVIT_H_

#define SOIL_MOISTURE_ADC_TIMEOUT 10000

static u8 SoilMoisture_u8MapValue(u16 Copy_u16RawValue, u16 Copy_u16Min, u16 Copy_u16Max);

#define TEMP_THRESHOLD      30
#define MOISTURE_THRESHOLD  30
#define ADC_MAX             1023

#endif /* SOIL_MOISTURE_PRIVIT_H_ */
