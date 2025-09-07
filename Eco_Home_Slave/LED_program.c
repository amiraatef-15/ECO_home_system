/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LED_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By : Abdallah Saleh
 *  Layer  : HAL (Hardware Abstraction Layer)
 *  SWC    : LED (Software Component for LED control)
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "LED_interface.h"

/* 
 * Function: LED_vInit
 * --------------------
 * Initializes the LED pin as output.
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the LED configuration, 
 *     including port, pin, and active state.
 */
void LED_vInit( LED_Type LED_Configuration )
{
    /* Set the specified pin as output */
    DIO_vSetPinDirection( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_OUTPUT );
}

/* 
 * Function: LED_vOn
 * ------------------
 * Turns the LED on based on its active state (ACTIVE_HIGH or ACTIVE_LOW).
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the LED configuration, 
 *     including port, pin, and active state.
 */
void LED_vOn( LED_Type LED_Configuration )
{
    if( LED_Configuration.Active_State == ACTIVE_HIGH ){
        /* Set pin to HIGH for active high configuration */
        DIO_vSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH );
    } else if( LED_Configuration.Active_State == ACTIVE_LOW ){
        /* Set pin to LOW for active low configuration */
        DIO_vSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW );
    }
}

/* 
 * Function: LED_vOff
 * -------------------
 * Turns the LED off based on its active state (ACTIVE_HIGH or ACTIVE_LOW).
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the LED configuration, 
 *     including port, pin, and active state.
 */
void LED_vOff( LED_Type LED_Configuration )
{
    if( LED_Configuration.Active_State == ACTIVE_HIGH ){
        /* Set pin to LOW for active high configuration */
        DIO_vSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW );
    } else if( LED_Configuration.Active_State == ACTIVE_LOW ){
        /* Set pin to HIGH for active low configuration */
        DIO_vSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH );
    }
}

/* 
 * Function: LED_vTog
 * -------------------
 * Toggles the LED state (on/off).
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the LED configuration, 
 *     including port and pin.
 */
void LED_vTog( LED_Type LED_Configuration )
{
    /* Toggle the current state of the specified pin */
    DIO_vTOGPinValue( LED_Configuration.Port , LED_Configuration.Pin );
}
