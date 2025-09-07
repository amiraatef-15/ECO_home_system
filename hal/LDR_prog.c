/*
 * LDR_prog.c
 *
 *  Created on: Mar 11, 2024
 *  Author: alaa hassan
 */

#include "LDR_interface.h"
#include "LDR_private.h"
#include "LDR_config.h"

static u16 LDR_u16CalculateResistance(LDR_Config_t *Copy_pstConfig, u16 Copy_u16AdcValue)
{
    float Local_f32Voltage = (float)Copy_u16AdcValue * LDR_VOLTAGE_RESOLUTION / LDR_MAX_ADC_VALUE;
    float Local_f32RL = ((LDR_VOLTAGE_RESOLUTION - Local_f32Voltage) / Local_f32Voltage) * Copy_pstConfig->Copy_u16RL;
    return (u16)Local_f32RL;
}

LDR_ErrorStatus LDR_enumInit(LDR_Config_t *Copy_pstConfig)
{
    LDR_ErrorStatus Local_enumErrorStatus = LDR_NOK;
    
    if (Copy_pstConfig != NULL)
    {
        /* Initialize ADC */
        ADC_vInit();
        
        /* Set default values if not configured */
        if (Copy_pstConfig->Copy_u16RL == 0)
        {
            Copy_pstConfig->Copy_u16RL = LDR_DEFAULT_RL;
        }
        
        Local_enumErrorStatus = LDR_OK;
    }
    
    return Local_enumErrorStatus;
}

LDR_ErrorStatus LDR_enumGetLightIntensity(LDR_Config_t *Copy_pstConfig, u16 *Copy_pu16LightValue)
{
    LDR_ErrorStatus Local_enumErrorStatus = LDR_NOK;
    u16 Local_u16AnalogSignal = 0;
    
    if (Copy_pstConfig != NULL && Copy_pu16LightValue != NULL)
    {
        /* Get raw ADC value */
        Local_enumErrorStatus = LDR_enumGetAnalogSignal(Copy_pstConfig, &Local_u16AnalogSignal);
        
        if (Local_enumErrorStatus == LDR_OK)
        {
            /* Calculate LDR resistance */
            *Copy_pu16LightValue = LDR_u16CalculateResistance(Copy_pstConfig, Local_u16AnalogSignal);
        }
    }
    
    return Local_enumErrorStatus;
}

LDR_ErrorStatus LDR_enumGetAnalogSignal(LDR_Config_t *Copy_pstConfig, u16 *Copy_pu16AnalogSignal)
{
    LDR_ErrorStatus Local_enumErrorStatus = LDR_NOK;
    
    if (Copy_pstConfig != NULL && Copy_pu16AnalogSignal != NULL)
    {
        if (ADC_u8GetResultSync(Copy_pstConfig->Copy_u8Channel, Copy_pu16AnalogSignal) == 0)
        {
            Local_enumErrorStatus = LDR_OK;
        }
    }
    
    return Local_enumErrorStatus;
} 