/*
 * MQ2_prog.c
 *
 *  Created on: Mar 7, 2024
 *  Author: alaa hassan
 */

#include "MQ2_interface.h"
#include "MQ2_private.h"
#include "MQ2_config.h"

#define MQ2_CALIBRATION_SAMPLE_TIMES 50
#define MQ2_CALIBRATION_SAMPLE_INTERVAL 500

static u16 MQ2_u16CalculateRS(MQ2_Config_t *Copy_pstConfig, u16 Copy_u16AdcValue)
{
    float Local_f32Voltage = (float)Copy_u16AdcValue * MQ2_VOLTAGE_RESOLUTION / MQ2_MAX_ADC_VALUE;
    float Local_f32Rs = ((MQ2_VOLTAGE_RESOLUTION - Local_f32Voltage) / Local_f32Voltage) * Copy_pstConfig->Copy_u16RL;
    return (u16)Local_f32Rs;
}

static u16 MQ2_u16CalculateRatio(u16 Copy_u16Rs, u16 Copy_u16R0)
{
    return (u16)((float)Copy_u16Rs / Copy_u16R0);
}

static MQ2_ErrorStatus MQ2_enumGetCalibrationValue(MQ2_Config_t *Copy_pstConfig, u16 *Copy_pu16R0Value)
{
    MQ2_ErrorStatus Local_enumErrorStatus = MQ2_NOK;
    u32 Local_u32Sum = 0;
    u16 Local_u16AnalogValue = 0;
    
    if (Copy_pstConfig != NULL && Copy_pu16R0Value != NULL)
    {
        for (u8 Local_u8Counter = 0; Local_u8Counter < MQ2_CALIBRATION_SAMPLE_TIMES; Local_u8Counter++)
        {
            Local_enumErrorStatus = MQ2_enumGetAnalogSignal(Copy_pstConfig, &Local_u16AnalogValue);
            if (Local_enumErrorStatus == MQ2_OK)
            {
                Local_u32Sum += MQ2_u16CalculateRS(Copy_pstConfig, Local_u16AnalogValue);
            }
            else
            {
                break;
            }
        }
        
        if (Local_enumErrorStatus == MQ2_OK)
        {
            *Copy_pu16R0Value = Local_u32Sum / MQ2_CALIBRATION_SAMPLE_TIMES;
        }
    }
    else
    {
        Local_enumErrorStatus = MQ2_NOK;
    }
    
    return Local_enumErrorStatus;
}

MQ2_ErrorStatus MQ2_enumInit(MQ2_Config_t *Copy_pstConfig)
{
    MQ2_ErrorStatus Local_enumErrorStatus = MQ2_NOK;
    
    if (Copy_pstConfig != NULL)
    {
        /* Initialize ADC */
        ADC_vInit();
        
        /* Set default values if not configured */
        if (Copy_pstConfig->Copy_u16R0 == 0)
        {
            Copy_pstConfig->Copy_u16R0 = MQ2_DEFAULT_R0;
        }
        if (Copy_pstConfig->Copy_u16RL == 0)
        {
            Copy_pstConfig->Copy_u16RL = MQ2_DEFAULT_RL;
        }
        
        Local_enumErrorStatus = MQ2_OK;
    }
    
    return Local_enumErrorStatus;
}

MQ2_ErrorStatus MQ2_enumGetGasConcentration(MQ2_Config_t *Copy_pstConfig, u16 *Copy_pu16GasValue)
{
    MQ2_ErrorStatus Local_enumErrorStatus = MQ2_NOK;
    u16 Local_u16AnalogSignal = 0;
    
    if (Copy_pstConfig != NULL && Copy_pu16GasValue != NULL)
    {
        /* Get raw ADC value */
        Local_enumErrorStatus = MQ2_enumGetAnalogSignal(Copy_pstConfig, &Local_u16AnalogSignal);
        
        if (Local_enumErrorStatus == MQ2_OK)
        {
            /* Calculate sensor resistance */
            u16 Local_u16Rs = MQ2_u16CalculateRS(Copy_pstConfig, Local_u16AnalogSignal);
            
            /* Calculate ratio */
            *Copy_pu16GasValue = MQ2_u16CalculateRatio(Local_u16Rs, Copy_pstConfig->Copy_u16R0);
        }
    }
    
    return Local_enumErrorStatus;
}

MQ2_ErrorStatus MQ2_enumGetAnalogSignal(MQ2_Config_t *Copy_pstConfig, u16 *Copy_pu16AnalogSignal)
{
    MQ2_ErrorStatus Local_enumErrorStatus = MQ2_NOK;
    
    if (Copy_pstConfig != NULL && Copy_pu16AnalogSignal != NULL)
    {
        if (ADC_u8GetResultSync(Copy_pstConfig->Copy_u8Channel, Copy_pu16AnalogSignal) == 0)
        {
            Local_enumErrorStatus = MQ2_OK;
        }
    }
    
    return Local_enumErrorStatus;
}

MQ2_ErrorStatus MQ2_enumCalibrate(MQ2_Config_t *Copy_pstConfig)
{
    MQ2_ErrorStatus Local_enumErrorStatus = MQ2_NOK;
    u16 Local_u16R0Value = 0;
    
    if (Copy_pstConfig != NULL)
    {
        Local_enumErrorStatus = MQ2_enumGetCalibrationValue(Copy_pstConfig, &Local_u16R0Value);
        if (Local_enumErrorStatus == MQ2_OK)
        {
            Copy_pstConfig->Copy_u16R0 = Local_u16R0Value;
        }
    }
    
    return Local_enumErrorStatus;
}
