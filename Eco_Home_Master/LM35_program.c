/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LM35_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : HAL
 *  SWC    : LM35
 *
 */
/**
 * @file LM35_Driver.c
 * @brief LM35 Temperature Sensor Driver
 *
 * The LM35 is a precision temperature sensor with an analog output,
 * linearly proportional to the temperature in Celsius.
 *
 * Features:
 * - Linear Output: 10mV/°C
 * - Accuracy: ±0.5°C at 25°C
 * - Operating Voltage: 4V to 30V
 * - Low Power Consumption: ~60 µA
 * - Output Impedance: Low (suitable for direct ADC connection)
 * - No External Calibration Required
 *
 * Operating Range:
 * - Temperature Range: -55°C to +150°C
 * - Suitable for various applications including temperature monitoring,
 *   climate control systems, and industrial automation.
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "ADC_interface.h"

#include "LM35_interface.h"
#include "LM35_private.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function initialize the pin which connected to led as output pin
* Parameters :
            => struct has the LM35 Channel, ADC VoltageReference , ADCResolution
			=> Pointer to TEMP Variable which will return in it 
* return : Error State
*/
u8 LM35_u8GetTemp (LM35_CONFIG * lm35 , u8 * Copy_u8TempValue) 
{
	u8 Local_u8ErrorState = OK ;

	u16 Local_u16ADCResult ;
	u16 Local_u16AnalogValue ; // Voltage Value
	
	u16 Local_u8ADCReference = ( lm35->Copy_u8ADCVoltageReference ) * 1000 ;  // To Convert from ( V --> mV )
	
	
	/* ADC Digital Reading  */
	ADC_u8GetResultSync( lm35->Copy_u8LM35Channel , &Local_u16ADCResult ) ;

	/* Check for ADC Resolution  */
	if ( lm35->Copy_u8ADCResolution == ADC_RESOLUTION_10_BIT )
	{
		Local_u16AnalogValue = (u16) ( ((u32)Local_u16ADCResult * (u32)Local_u8ADCReference ) / 1024UL) ;

	}
	else if ( lm35->Copy_u8ADCResolution == ADC_RESOLUTION_8_BIT )
	{
		Local_u16AnalogValue = (u16) ( ((u32)Local_u16ADCResult * (u32)Local_u8ADCReference ) / 256UL) ;
	}


	/* Convert ( mv --> Temp ) */
	* Copy_u8TempValue = Local_u16AnalogValue / 10 ;

	return Local_u8ErrorState ;
}
/*#include "LM35_interface.h"

int main() {
    u8 temperature;
    LM35_CONFIG my_lm35 = {
        .Copy_u8LM35Channel = ADC_CHANNEL0,   // استخدام القناة 0 في ADC
        .Copy_u8ADCVoltageReference = 5,      // مرجع الجهد 5 فولت (AVCC)
        .Copy_u8ADCResolution = ADC_RESOLUTION_10_BIT // دقة 10 بت
    };
    
    u8 error = LM35_u8GetTemp(&my_lm35, &temperature);
    
    if(error == OK) {
        // استخدام قيمة temperature (مثال: عرضها على شاشة LCD)
    } else {
        // معالجة الخطأ
    }
    
    while(1);
}*/

/*#include "LM35_interface.h"
#include "ADC_interface.h"

void main() {
    ADC_vInit(); // تهيئة ADC حسب إعدادات ADC_config.h
    
    LM35_CONFIG sensor = {
        .Copy_u8LM35Channel = ADC_CHANNEL0,
        .Copy_u8ADCVoltageReference = 5,
        .Copy_u8ADCResolution = ADC_RESOLUTION_10_BIT
    };
    
    u8 temp;
    while(1) {
        u8 error = LM35_u8GetTemp(&sensor, &temp);
        if(error == OK) {
            // عرض الحرارة على شاشة أو استخدامها في منطق التحكم
        }
        _delay_ms(1000); // انتظر ثانية قبل القراءة التالية
    }
}*/
