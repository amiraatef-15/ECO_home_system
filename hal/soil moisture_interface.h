/*
 * soil moisture_interface.h
 *
 *  Created on: Apr 4, 2025
 *      Author: Us
 */

#ifndef SOIL_MOISTURE_INTERFACE_H_
#define SOIL_MOISTURE_INTERFACE_H_
#include "../lib/std_typs.h"


void SoilMoisture_voidInit(void);


u8 SoilMoisture_u8GetRawValue(u16* Copy_pu16Reading);


u8 SoilMoisture_u8GetPercentage(u8* Copy_pu8Percentage);


u8 SoilMoisture_u8IsDry(u8 Copy_u8Threshold, u8* Copy_pu8IsDry);



#endif /* SOIL_MOISTURE_INTERFACE_H_ */
