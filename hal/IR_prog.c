/*
 * IR_prog.c
 *
 *  Created on: Mar 11, 2024
 *  Author: alaa hassan
 */


#include "../MCAL/DIO_intervace.h"
#include "IR_interface.h"
#include "IR_private.h"
#include "IR_config.h"
#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"


IR_ErrorStatus IR_enumInit(IR_Config_t *Copy_pstConfig)
{
    IR_ErrorStatus Local_enumErrorStatus = IR_NOK;
    
    if (Copy_pstConfig != NULL)
    {
        /* Set pin as input */
        DIO_enumSetPinDirection(Copy_pstConfig->Copy_u8Port, Copy_pstConfig->Copy_u8Pin, DIO_INPUT);
        
        /* Enable internal pull-up resistor */
        DIO_enumConnectPullUp(Copy_pstConfig->Copy_u8Port, Copy_pstConfig->Copy_u8Pin, 1);
        
        Local_enumErrorStatus = IR_OK;
    }
    
    return Local_enumErrorStatus;
}

IR_ErrorStatus IR_enumGetState(IR_Config_t *Copy_pstConfig, u8 *Copy_pu8State)
{
    IR_ErrorStatus Local_enumErrorStatus = IR_NOK;
    u8 Local_u8PinValue;
    
    if (Copy_pstConfig != NULL && Copy_pu8State != NULL)
    {
        /* Read pin value */
        if (DIO_enumReadPinValue(Copy_pstConfig->Copy_u8Port, Copy_pstConfig->Copy_u8Pin, &Local_u8PinValue) == DIO_OK)
        {
            /* Convert to detection state */
            if (Local_u8PinValue == IR_DETECTED)
            {
                *Copy_pu8State = 1;  /* Object detected */
            }
            else
            {
                *Copy_pu8State = 0;  /* No object detected */
            }

            Local_enumErrorStatus = IR_OK;
        }
    }
    
    return Local_enumErrorStatus;
} 
