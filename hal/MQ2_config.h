/*
 * MQ2_config.h
 *
 *  Created on: Mar 7, 2024
 *  Author: alaa hassan
 */

#ifndef HAL_MQ2_CONFIG_H_
#define HAL_MQ2_CONFIG_H_
#include "MQ2_interface.h"
/* Default values for MQ2 sensor */
#define MQ2_DEFAULT_R0     10000   /* Default resistance in clean air (10KΩ) */
#define MQ2_DEFAULT_RL     10000   /* Default load resistance (10KΩ) */

/* MQ2 Sensor Channels */

#define MQ2_CHANNEL_3      ADC_CHANNEL3


/* MQ2 Voltage References */
#define MQ2_VREF_AREF      AREF
#define MQ2_VREF_AVCC      AVCC
#define MQ2_VREF_INTERNAL  INTERNAL_2_56

/* MQ2 Resolution */
#define MQ2_RES_10_BIT     ADC_RES_10_BIT
#define MQ2_RES_8_BIT      ADC_RES_8_BIT

 
#endif /* HAL_MQ2_CONFIG_H_ */ 
