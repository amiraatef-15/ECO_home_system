/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LDR_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : HAL
 *  SWC    : LDR
 *
 */
/**
 * @file LDR_Driver.c
 * @brief LDR (Light Dependent Resistor) Sensor Driver
 *
 * The LDR is a variable resistor that changes its resistance based on the intensity of light.
 * It is commonly used in light-sensitive applications such as automatic lighting, 
 * light meters, and security systems.
 *
 * Features:
 * - High resistance in darkness (Mega-ohms)
 * - Low resistance in bright light (Kilo-ohms)
 * - Analog output suitable for ADC readings
 * - No external power required, operates as a passive component
 * - Response time depends on light intensity changes
 *
 * Operating Characteristics:
 * - Resistance decreases as light intensity increases
 * - Works best with a voltage divider circuit for ADC interfacing
 * - Suitable for applications like automatic street lights, 
 *   ambient light sensing, and optical switches.
 */

#include "LDR_interface.h"
#include "LDR_config.h"
#include "ADC_interface.h"

LDR_ErrorStatus LDR_u8GetLightLevel(LDR_Config *Config, u8 *LightLevel) {
    if (Config == NULL || LightLevel == NULL) {
        return LDR_NULL_POINTER;
    }
    
    if (Config->LDR_Channel > ADC_CHANNEL7) {
        return LDR_INVALID_CHANNEL;
    }

    u16 ADC_Result;
    u32 MaxADCValue = (Config->LDR_Resolution == ADC_RESOLUTION_10_BIT) ? 1023 : 255;
    
    // قراءة قيمة الـ ADC
    ADC_u8GetResultSync(Config->LDR_Channel, &ADC_Result);
    
    // تحويل القيمة إلى نسبة مئوية (0% = مظلم, 100% = مضيء)
    *LightLevel = (u8)(((u32)ADC_Result * 100) / MaxADCValue);
    
    return LDR_OK;
}
/*#include "LDR_interface.h"
#include "ADC_interface.h"

int main() {
    ADC_vInit(); // تهيئة الـ ADC أولاً
    
    LDR_Config myLDR = {
        .LDR_Channel = ADC_CHANNEL0,
        .LDR_VoltageRef = 5,
        .LDR_Resolution = ADC_RESOLUTION_10_BIT
    };
    
    u8 LightLevel;
    LDR_ErrorStatus status = LDR_u8GetLightLevel(&myLDR, &LightLevel);
    
    if (status == LDR_OK) {
        // عرض النتيجة على شاشة LCD أو التحكم في إضاءة LED
        if (LightLevel > 50) {
            GPIO_WritePin(PORTA, PIN0, HIGH); // إضاءة عالية
        } else {
            GPIO_WritePin(PORTA, PIN0, LOW); // إضاءة منخفضة
        }
    }
    
    while(1);
}*/
