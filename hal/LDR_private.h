#ifndef LDR_PRIVATE_H_
#define LDR_PRIVATE_H_

/* Default values */
#define LDR_DEFAULT_RL         10000   /* Default load resistance in ohms */
#define LDR_VOLTAGE_RESOLUTION 5.0     /* ADC voltage resolution in volts */
#define LDR_MAX_ADC_VALUE      1023    /* Maximum ADC value for 10-bit resolution */

/* Private function prototypes */
static u16 LDR_u16CalculateResistance(LDR_Config_t *Copy_pstConfig, u16 Copy_u16AdcValue);

#endif /* LDR_PRIVATE_H_ */ 