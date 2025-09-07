/*
 * EEPROM_programe.c

 *
 *  Created on: Jan 31, 2025
 *      Author: engineering
 */
#include <avr/io.h>
#include "../Lib/BIT_MATH.h"
#include "../Lib/std_typs.h"
// دالة الكتابة (تدعم بيانات متعددة البايتات)
void EEPROM_write(unsigned short address, const u8 *data, u8 size) {
    for(u8 i = 0; i < size; i++) {
        EEAR = address + i; // تعيين العنوان الحالي
        EEDR = data[i]; // تعيين البيانات
        SET_BIT(EECR, EEMWE); // تمكين الكتابة
        SET_BIT(EECR, EEWE); // بدء الكتابة
        while (GET_BIT(EECR, EEWE)); // انتظار اكتمال الكتابة
    }
}

// دالة القراءة (تدعم بيانات متعددة البايتات)
void EEPROM_read(unsigned short address, u8 *data, u8 size) {
    for(u8 i = 0; i < size; i++) {
        EEAR = address + i; // تعيين العنوان الحالي
        SET_BIT(EECR, EERE); // بدء القراءة
        data[i] = EEDR; // تخزين البيانات المقروءة
    }
}


