/*
 * PIR_interface.c
 *
 * Created: 04/04/2025 23:13:38
 *  Author: GOHARY 10
 */
#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"

#include "../MCAL/DIO_intervace.h"
#include "PIR_interface.h"
#include "PIR_config.h"
#include "PIR_private.h"

/* Global variable to store callback function */
static void (*PIR_pvNotificationFunc)(void) = NULL;

/* Global variable for debounce */
static u32 PIR_u32LastDetectionTime = 0;

/**
 * @brief Initialize PIR sensor
 */
void PIR_voidInit(void)
{
    /* Set PIR pin as input */
    DIO_enumSetPinDirection(PIR_PORT, PIR_PIN, DIO_PIN_INPUT);

    /* If active low, enable internal pull-up */
    #if PIR_CONNECTION_MODE == PIR_ACTIVE_LOW
        DIO_enumConnectPullUp(PIR_PORT, PIR_PIN, DIO_PIN_HIGH);
    #endif
}

/**
 * @brief Read PIR sensor state
 * @return u8: 1 if motion detected, 0 otherwise
 */
u8 PIR_u8Read(void)
{
    u8 Local_u8Result = 0;
    u8 Local_u8PinValue;

    DIO_enumReadPinValue(PIR_PORT, PIR_PIN, &Local_u8PinValue);

    #if PIR_CONNECTION_MODE == PIR_ACTIVE_HIGH
        Local_u8Result = Local_u8PinValue;
    #else
        Local_u8Result = !Local_u8PinValue;
    #endif

    return Local_u8Result;
}

/**
 * @brief Read PIR sensor state with debounce
 * @return u8: 1 if motion detected (with debounce), 0 otherwise
 */
u8 PIR_u8ReadDebounced(void)
{
    u8 Local_u8Result = 0;
    u32 Local_u32CurrentTime = 0; // You need to implement a time source (e.g., SysTick)

    if (PIR_u8Read())
    {
        if ((Local_u32CurrentTime - PIR_u32LastDetectionTime) > PIR_DEBOUNCE_MS)
        {
            PIR_u32LastDetectionTime = Local_u32CurrentTime;
            Local_u8Result = 1;
        }
    }

    return Local_u8Result;
}

/**
 * @brief Set callback function for motion detection
 * @param Copy_pvNotificationFunc: Pointer to notification function
 */
void PIR_voidSetCallback(void (*Copy_pvNotificationFunc)(void))
{
    PIR_pvNotificationFunc = Copy_pvNotificationFunc;
}

/* ISR for PIR sensor (if using interrupt) */
void PIR_voidISR(void)
{
    if (PIR_pvNotificationFunc != NULL)
    {
        PIR_pvNotificationFunc();
    }
}
