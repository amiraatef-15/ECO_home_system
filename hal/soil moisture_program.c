/*
 * soil moisture_program.c
 *
 *  Created on: Apr 4, 2025
 *      Author: Us
 */


#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"
#include "../MCAL/ADC_interface.h"
#include "soil moisture_interface.h"
#include "soil moisture_privit.h"
#include "soil moisture_config.h"

void SoilMoisture_voidInit(void)
{
    /* Initialize ADC if not already initialized */
    ADC_vInit();
}

u8 SoilMoisture_u8GetRawValue(u16* Copy_pu16Reading)
{
    u8 Local_u8ErrorState = OK;

    if(Copy_pu16Reading != NULL)
    {
        Local_u8ErrorState = ADC_u8GetResultSync(SOIL_MOISTURE_ADC_CHANNEL, Copy_pu16Reading);
    }
    else
    {
        Local_u8ErrorState = NULL_POINTER;
    }

    return Local_u8ErrorState;
}

u8 SoilMoisture_u8GetPercentage(u8* Copy_pu8Percentage)
{
    u8 Local_u8ErrorState = OK;
    u16 Local_u16RawValue = 0;

    if(Copy_pu8Percentage != NULL)
    {
        Local_u8ErrorState = SoilMoisture_u8GetRawValue(&Local_u16RawValue);

        if(Local_u8ErrorState == OK)
        {
            /* Map the raw value to percentage (inverted because higher value means drier soil) */
            *Copy_pu8Percentage = SoilMoisture_u8MapValue(Local_u16RawValue,
                                                         SOIL_WET_VALUE,
                                                         SOIL_DRY_VALUE);
        }
    }
    else
    {
        Local_u8ErrorState = NULL_POINTER;
    }

    return Local_u8ErrorState;
}

u8 SoilMoisture_u8IsDry(u8 Copy_u8Threshold, u8* Copy_pu8IsDry)
{
    u8 Local_u8ErrorState = OK;
    u8 Local_u8Percentage = 0;

    if(Copy_pu8IsDry != NULL)
    {
        Local_u8ErrorState = SoilMoisture_u8GetPercentage(&Local_u8Percentage);

        if(Local_u8ErrorState == OK)
        {
            *Copy_pu8IsDry = (Local_u8Percentage >= Copy_u8Threshold) ? 1 : 0;
        }
    }
    else
    {
        Local_u8ErrorState = NULL_POINTER;
    }

    return Local_u8ErrorState;
}

static u8 SoilMoisture_u8MapValue(u16 Copy_u16RawValue, u16 Copy_u16Min, u16 Copy_u16Max)
{
    u16 Local_u16MappedValue;

    /* Ensure the raw value is within the expected range */
    if(Copy_u16RawValue <= Copy_u16Min)
    {
        Local_u16MappedValue = 100;  // 100% wet
    }
    else if(Copy_u16RawValue >= Copy_u16Max)
    {
        Local_u16MappedValue = 0;    // 0% wet (100% dry)
    }
    else
    {
        /* Map the value from [min, max] to [100, 0] */
        Local_u16MappedValue = 100 - ((Copy_u16RawValue - Copy_u16Min) * 100) / (Copy_u16Max - Copy_u16Min);
    }

    return (u8)Local_u16MappedValue;
}
