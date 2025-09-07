/*
 * MQ2_interface.h
 *
 *  Created on: Mar 7, 2024
 *  Author: alaa hassan
 */

#ifndef MQ2_INTERFACE_H_
#define MQ2_INTERFACE_H_

#include "../lib/std_typs.h"
#include "../MCAL/ADC_interface.h"

typedef enum
{
    MQ2_NOK,
    MQ2_OK
} MQ2_ErrorStatus;

/* MQ2 Sensor Configuration */
typedef struct
{
    u8 Copy_u8Channel;            /* ADC channel connected to MQ2 sensor */
    u8 Copy_u8VoltageRefrence;    /* Vref = AREF, AVCC, INTERNAL_2_56 */
    u8 Copy_u8ADCRes;            /* ADC_RES_10_BIT or ADC_RES_8_BIT */
    u16 Copy_u16R0;              /* Sensor resistance in clean air */
    u16 Copy_u16RL;              /* Load resistance on the board */
} MQ2_Config_t;

/* Function Prototypes */
MQ2_ErrorStatus MQ2_enumInit(MQ2_Config_t *Copy_pstConfig);
MQ2_ErrorStatus MQ2_enumGetGasConcentration(MQ2_Config_t *Copy_pstConfig, u16 *Copy_pu16GasValue);
MQ2_ErrorStatus MQ2_enumGetAnalogSignal(MQ2_Config_t *Copy_pstConfig, u16 *Copy_pu16AnalogSignal);
MQ2_ErrorStatus MQ2_enumCalibrate(MQ2_Config_t *Copy_pstConfig);

#endif /* MQ2_INTERFACE_H_ */
