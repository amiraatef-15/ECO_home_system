/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LDR_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : HAL
 *  SWC    : LDR
 *
 */
#ifndef LDR_CONFIG_H_
#define LDR_CONFIG_H_

/* إعدادات افتراضية (يمكن تعديلها حسب التطبيق) */
#define LDR_VREF        5      // مرجع الجهد (فولت)
#define LDR_ADC_CHANNEL ADC_CHANNEL0 // القناة الافتراضية
#define LDR_RESOLUTION  ADC_RESOLUTION_10_BIT // دقة الـ ADC

#endif