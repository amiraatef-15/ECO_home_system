/*
 * MQ2_private.h
 *
 *  Created on: Mar 7, 2024
 *  Author: alaa hassan
 */

#ifndef HAL_MQ2_PRIVATE_H_
#define HAL_MQ2_PRIVATE_H_

/* Private macros for MQ2 sensor calculations */
#define MQ2_VOLTAGE_RESOLUTION     5.0f    /* ADC voltage resolution */
#define MQ2_MAX_ADC_VALUE         1023    /* Maximum ADC value for 10-bit resolution */
#define MQ2_CALIBRATION_SAMPLE_TIMES 50    /* Number of samples for calibration */
#define MQ2_CALIBRATION_SAMPLE_INTERVAL 500 /* Interval between samples in ms */

/* Private function prototypes */
static u16 MQ2_u16CalculateRS(MQ2_Config_t *Copy_pstConfig, u16 Copy_u16AdcValue);
static u16 MQ2_u16CalculateRatio(u16 Copy_u16Rs, u16 Copy_u16R0);
static MQ2_ErrorStatus MQ2_enumGetCalibrationValue(MQ2_Config_t *Copy_pstConfig, u16 *Copy_pu16R0Value);

#endif /* HAL_MQ2_PRIVATE_H_ */ 