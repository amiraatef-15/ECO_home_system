/*
 * soil moisture_config.h
 *
 *  Created on: Apr 4, 2025
 *      Author: Us
 */

#ifndef SOIL_MOISTURE_CONFIG_H_
#define SOIL_MOISTURE_CONFIG_H_

#define SOIL_MOISTURE_ADC_CHANNEL ADC_CHANNEL1

/* Calibration values (adjust based on your sensor) */
#define SOIL_DRY_VALUE     1023    // Value when sensor is in air (completely dry)
#define SOIL_WET_VALUE     200     // Value when sensor is fully submerged in water


#endif /* SOIL_MOISTURE_CONFIG_H_ */
