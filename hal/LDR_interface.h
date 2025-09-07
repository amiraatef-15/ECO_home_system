#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

#include "../lib/std_typs.h"
#include "../MCAL/ADC_interface.h"

typedef enum
{
    LDR_OK,
    LDR_NOK
} LDR_ErrorStatus;

typedef struct
{
    u8 Copy_u8Channel;           /* ADC Channel */
    u8 Copy_u8VoltageRefrence;   /* ADC Voltage Reference */
    u8 Copy_u8ADCRes;           /* ADC Resolution */
    u16 Copy_u16RL;             /* Load Resistance */
} LDR_Config_t;

/**
 * @brief Initialize the LDR sensor
 * @param Copy_pstConfig Pointer to LDR configuration structure
 * @return LDR_ErrorStatus
 */
LDR_ErrorStatus LDR_enumInit(LDR_Config_t *Copy_pstConfig);

/**
 * @brief Get the light intensity value
 * @param Copy_pstConfig Pointer to LDR configuration structure
 * @param Copy_pu16LightValue Pointer to store the light intensity value
 * @return LDR_ErrorStatus
 */
LDR_ErrorStatus LDR_enumGetLightIntensity(LDR_Config_t *Copy_pstConfig, u16 *Copy_pu16LightValue);

/**
 * @brief Get the raw ADC value from LDR
 * @param Copy_pstConfig Pointer to LDR configuration structure
 * @param Copy_pu16AnalogSignal Pointer to store the ADC value
 * @return LDR_ErrorStatus
 */
LDR_ErrorStatus LDR_enumGetAnalogSignal(LDR_Config_t *Copy_pstConfig, u16 *Copy_pu16AnalogSignal);

#endif /* LDR_INTERFACE_H_ */ 