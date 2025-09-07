/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */ 
 

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "STD_TYPES.h"

#define ADC_DISABLE             0
#define ADC_ENABLE              1

#define INT_DISABLE             0
#define INT_ENABLE              1

#define AREF                    0
#define AVCC                    1
#define INTERNAL_2_56           3


#define RIGHT_ADJUSTMENT        0
#define LEFT_ADJUSTMENT         1

#define ADC_CHANNEL0            0
#define ADC_CHANNEL1            1
#define ADC_CHANNEL2            2
#define ADC_CHANNEL3            3
#define ADC_CHANNEL4            4
#define ADC_CHANNEL5            5
#define ADC_CHANNEL6            6
#define ADC_CHANNEL7            7

#define ADC_SINGLE_CONVERSION   0
#define ADC_FREE_RUNNING        1
#define ADC_ANALOG_COMPARATOR   2
#define ADC_EXTI0               3
#define ADC_TIM0_CTC            4
#define ADC_TIM0_OVF            5
#define ADC_TIM1_CTC_CHANNEL_B  6
#define ADC_TIM1_OVF            7
#define ADC_TIM1_ICU            8

/**
 * @brief Error states for ADC operations
 */

#define OK              0   /* Operation completed successfully */
#define NULL_PTR_ERR    1   /* Null pointer error */
#define BUSY_ERR        2   /* ADC busy with another conversion */
#define TIMEOUT_ERR     3   /* Operation timed out */

/**
 * @brief ADC Prescaler values
 */

#define ADC_PRE_2      0b001   /* Division factor = 2 */
#define ADC_PRE_4      0b010   /* Division factor = 4 */
#define ADC_PRE_8      0b011   /* Division factor = 8 */
#define ADC_PRE_16     0b100   /* Division factor = 16 */
#define ADC_PRE_32     0b101   /* Division factor = 32 */
#define ADC_PRE_64     0b110   /* Division factor = 64 */
#define ADC_PRE_128    0b111   /* Division factor = 128 */

typedef struct 
{
	u8*  Channel ; 
	u16* Result  ;
	u8   Size    ;
	void (*NotificationFunc)(void);
}Chain_t ;


void ADC_vInit               ( void                                                                                 );
u16  ADC_u8GetResultSync        ( u8 Copy_u8Channel , u16* Copy_pu16Result                                         );
u8   ADC_u8StartConversionAsynch( u8 Copy_u8Channel , u16* Copy_pu16Reading , void(*Copy_pvNotificationFunc)(void) );
u8   ADC_u8StartChainAsynch     ( Chain_t * Copy_Chain); //&chaian_t

void ADC_vEnable           (void);
void ADC_vDisable          (void);
void ADC_vInterruptEnable  (void);
void ADC_vInterruptDisable (void);

u8 ADC_u8SetPrescaler (u8 Copy_u8Prescaler);

#endif /* ADC_INTERFACE_H_ */
