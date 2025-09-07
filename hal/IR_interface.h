#ifndef IR_INTERFACE_H_
#define IR_INTERFACE_H_

#include "../lib/std_typs.h"
#include "../MCAL/DIO_intervace.h"

typedef enum
{
    IR_OK,
    IR_NOK
} IR_ErrorStatus;

typedef struct
{
    u8 Copy_u8Port;     /* Port number */
    u8 Copy_u8Pin;      /* Pin number */
} IR_Config_t;

/**
 * @brief Initialize the IR sensor
 * @param Copy_pstConfig Pointer to IR configuration structure
 * @return IR_ErrorStatus
 */
IR_ErrorStatus IR_enumInit(IR_Config_t *Copy_pstConfig);

/**
 * @brief Get the IR sensor state (Detected/Not Detected)
 * @param Copy_pstConfig Pointer to IR configuration structure
 * @param Copy_pu8State Pointer to store the sensor state (1: Detected, 0: Not Detected)
 * @return IR_ErrorStatus
 */
IR_ErrorStatus IR_enumGetState(IR_Config_t *Copy_pstConfig, u8 *Copy_pu8State);

#endif /* IR_INTERFACE_H_ */ 