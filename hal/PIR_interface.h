/*
 * PIR_interface.h
 *
 * Created: 04/04/2025 23:15:31
 *  Author: GOHARY 10
 */ 


#ifndef HAL_PIR_INTERFACE_H_
#define HAL_PIR_INTERFACE_H_

#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"

#include "../MCAL/DIO_intervace.h"
#include "PIR_config.h"
#include "PIR_private.h"
/* PIR Connection Modes */
#define PIR_ACTIVE_HIGH 1
#define PIR_ACTIVE_LOW  0

/**
 * @brief Initialize PIR sensor
 */
void PIR_voidInit(void);

/**
 * @brief Read PIR sensor state
 * @return u8: 1 if motion detected, 0 otherwise
 */
u8 PIR_u8Read(void);

/**
 * @brief Read PIR sensor state with debounce
 * @return u8: 1 if motion detected (with debounce), 0 otherwise
 */
u8 PIR_u8ReadDebounced(void);

/**
 * @brief Set callback function for motion detection (for interrupt-based approach)
 * @param Copy_pvNotificationFunc: Pointer to notification function
 */
void PIR_voidSetCallback(void (*Copy_pvNotificationFunc)(void));

#endif
