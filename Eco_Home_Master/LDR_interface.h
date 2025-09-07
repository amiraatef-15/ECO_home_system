/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LDR_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : HAL
 *  SWC    : LDR
 *
 */
#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

#include "STD_TYPES.h"
#define ADC_RESOLUTION_10_BIT 0
#define ADC_RESOLUTION_8_BIT  1

typedef enum {
    LDR_OK,
    LDR_NULL_POINTER,
    LDR_INVALID_CHANNEL
} LDR_ErrorStatus;

typedef struct {
    u8 LDR_Channel;      // قناة الـ ADC (مثال: ADC_CHANNEL0)
    u8 LDR_VoltageRef;   // مرجع الجهد (بالفولت)
    u8 LDR_Resolution;   // دقة الـ ADC (10 أو 8 بت)
} LDR_Config;

/**
 * @brief قراءة مستوى الإضاءة من LDR
 * @param Config: مؤشر لتهيئة الـ LDR
 * @param LightLevel: مؤشر لتخزين النتيجة (نسبة من 0 إلى 100%)
 * @return حالة الخطأ (LDR_ErrorStatus)
 */
LDR_ErrorStatus LDR_u8GetLightLevel(LDR_Config *Config, u8 *LightLevel);

#endif
