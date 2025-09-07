/*
 * CLCD_program.c
 *
 *  Created on: Dec 20, 2024
 *      Author: alaa hassan
 */


/*
 * CLCD.c
 *
 * Created: 12/15/2024 5:48:53 PM
 * Author : alaa hassan
 */




#include <util/delay.h>
#include "../lib/std_typs.h"
#include "../lib/BIT_MATH.h"
#include "../MCAL/DIO_intervace.h"
#include "CLCD_config.h"
#include "CLCD_intreface.h"
#include "CLCD_private.h"
#include "CLCD_extrachar.h"

void CLCD_voidInit(void) {
    /*<<<<<<<<<<<<    8 Bits Mode   >>>>>>>>>>>>>*/
#if CLCD_MODE == 8
    _delay_ms(50);
    DIO_enumSetPortDirection(CLCD_DATA_PORT, DIO_PORT_OUTPUT);
    DIO_enumSetPinDirection(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_OUTPUT);

    CLCD_voidsendCommand(lcd_Home);
    _delay_ms(2);

    CLCD_voidsendCommand(EIGHT_BITS);
    _delay_ms(2);

    CLCD_voidsendCommand(CLCD_DISPLAY_CURSOR);
    _delay_ms(2);

    CLCD_voidClearScreen();
    _delay_ms(2);

    CLCD_voidsendCommand(lcd_EntryMode);
    _delay_ms(2);
#elif CLCD_MODE == 4
    _delay_ms(50);

#if CLCD_DATA_NIBBLE == CLCD_HIGH_NIBBLE
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN4, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN5, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN6, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN7, DIO_PIN_OUTPUT);
#elif CLCD_DATA_NIBBLE == CLCD_LOW_NIBBLE
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN0, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN1, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN2, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_DATA_PORT, DIO_PIN3, DIO_PIN_OUTPUT);
#else
#error "Wrong CLCD_DATA_NIBBLE Config"
#endif

    DIO_enumSetPinDirection(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_OUTPUT);

    CLCD_voidsendCommand(lcd_Home);
    _delay_ms(10);

    CLCD_voidsendCommand(4);
    _delay_ms(2);

    CLCD_voidsendCommand(CLCD_DISPLAY_CURSOR);
    _delay_ms(2);

    CLCD_voidClearScreen();
    _delay_ms(2);

    CLCD_voidsendCommand(lcd_EntryMode);
    _delay_ms(2);
#else
#error "Wrong CLCD_MODE config"
#endif
}

void CLCD_voidsendData(u8 copy_u8D1ata) {
#if CLCD_MODE == 8
    DIO_enumWritePortValue(CLCD_DATA_PORT, copy_u8D1ata);
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_HIGH);
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);
    CLCD_voidSendFallingEdge();
#elif CLCD_MODE == 4
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_HIGH);
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);

#if CLCD_DATA_NIBBLE == CLCD_HIGH_NIBBLE
    DIO_vWriteHighNibble(CLCD_DATA_PORT, (copy_u8D1ata >> 4));
    CLCD_voidSendFallingEdge();
    DIO_vWriteHighNibble(CLCD_DATA_PORT, copy_u8D1ata);
    CLCD_voidSendFallingEdge();
#elif CLCD_DATA_NIBBLE == CLCD_LOW_NIBBLE
    DIO_vWriteLowNibble(CLCD_DATA_PORT, (copy_u8D1ata >> 4));
    CLCD_voidSendFallingEdge();
    DIO_vWriteLowNibble(CLCD_DATA_PORT, copy_u8D1ata);
    CLCD_voidSendFallingEdge();
#else
#error "Wrong CLCD_DATA_NIBBLE config"
#endif
#else
#error "Wrong CLCD_MODE config"
#endif
    _delay_ms(2);
}

void CLCD_voidsendCommand(u8 copy_u8Command) {
#if CLCD_MODE == 8
    DIO_enumWritePortValue(CLCD_DATA_PORT, copy_u8Command);
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_LOW);
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);
    CLCD_voidSendFallingEdge();
#elif CLCD_MODE == 4
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_LOW);
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);

#if CLCD_DATA_NIBBLE == CLCD_HIGH_NIBBLE
    DIO_vWriteHighNibble(CLCD_DATA_PORT, (copy_u8Command >> 4));
    CLCD_voidSendFallingEdge();
    DIO_vWriteHighNibble(CLCD_DATA_PORT, copy_u8Command);
    CLCD_voidSendFallingEdge();
#elif CLCD_DATA_NIBBLE == CLCD_LOW_NIBBLE
    DIO_vWriteLowNibble(CLCD_DATA_PORT, (copy_u8Command >> 4));
    CLCD_voidSendFallingEdge();
    DIO_vWriteLowNibble(CLCD_DATA_PORT, copy_u8Command);
    CLCD_voidSendFallingEdge();
#else
#error "Wrong CLCD_DATA_NIBBLE config"
#endif
#else
#error "Wrong CLCD_MODE config"
#endif
    _delay_ms(2);
}

void CLCD_voidsendString(u8 *copy_u8ptrString) {
    u8 Loc_Iterator = 0;
    while (copy_u8ptrString[Loc_Iterator] != '\0') {
        CLCD_voidsendData(copy_u8ptrString[Loc_Iterator]);
        Loc_Iterator++;
    }
}

static void CLCD_voidSendFallingEdge(void) {
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_enumWritePinValue(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_LOW);
    _delay_ms(1);
}

void CLCD_voidClearScreen(void) {
    CLCD_voidsendCommand(lcd_Clear);
    _delay_ms(10);
}

void CLCD_voidSetPosition(u8 copy_u8Row, u8 copy_u8Col) {
    u8 loc_u8data;
    if ((copy_u8Row > 2) || (copy_u8Row < 1) || (copy_u8Col > 16) || (copy_u8Col < 1)) {
        loc_u8data = lcd_SetCursor;
    } else if (copy_u8Row == CLCD_Row_1) {
        loc_u8data = (lcd_SetCursor) + (copy_u8Col - 1);
    } else if (copy_u8Row == CLCD_Row_2) {
        loc_u8data = (lcd_SetCursor) + 64 + (copy_u8Col - 1);
    }
    CLCD_voidsendCommand(loc_u8data);
    _delay_ms(1);
}

void CLCD_voidSendExtraChar(u8 copy_u8Row, u8 copy_u8Col) {
    u8 loc_u8Iterator = 0;
    CLCD_voidsendCommand(lcd_CGRAM);
    for (loc_u8Iterator = 0; loc_u8Iterator < sizeof(CLCD_u8ExtraChar) / sizeof(CLCD_u8ExtraChar[0]); loc_u8Iterator++) {
        CLCD_voidsendData(CLCD_u8ExtraChar[loc_u8Iterator]);
    }
    CLCD_voidSetPosition(copy_u8Row, copy_u8Col);
    for (loc_u8Iterator = 0; loc_u8Iterator < 8; loc_u8Iterator++) {
        CLCD_voidsendData(loc_u8Iterator);
    }
}

void CLCD_vSendIntNumber(s32 Copy_s32Number) {
    u32 LOC_u32Reverse = 1;
    if (Copy_s32Number == 0) {
        CLCD_voidsendData('0');
    } else {
        if (Copy_s32Number < 0) {
            CLCD_voidsendData('-');
            Copy_s32Number = (-1 * Copy_s32Number);
        }
        while (Copy_s32Number != 0) {
            LOC_u32Reverse = (LOC_u32Reverse * 10) + (Copy_s32Number % 10);
            Copy_s32Number /= 10;
        }
        while (LOC_u32Reverse != 1) {
            CLCD_voidsendData((LOC_u32Reverse % 10) + 48);
            LOC_u32Reverse /= 10;
        }
    }
}

void CLCD_vSendFloatNumber(f64 Copy_f64Number) {
    CLCD_vSendIntNumber((s32)Copy_f64Number);
    if (Copy_f64Number < 0) {
        Copy_f64Number *= -1;
    }
    Copy_f64Number = (f64)Copy_f64Number - (s32)Copy_f64Number;
    Copy_f64Number *= 10000;
    if ((s64)Copy_f64Number != 0) {
        CLCD_voidsendData('.');
        CLCD_vSendIntNumber((s32)Copy_f64Number);
    }
}
