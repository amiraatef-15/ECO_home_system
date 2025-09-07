/*
 * LCD_intreface.h
 *
 * Created: 12/15/2024 5:54:14 PM
 *  Author: alaa hassan
 */


#ifndef CLCD_INTREFACE_H_
#define CLCD_INTREFACE_H_

/*******/
#if CLCD_MODE == 8
#define EIGHT_BITS       0x38
#elif CLCD_MODE == 4
#define FOUR_BITS    0x28
#endif
/*********/

#define lcd_DisplayOn_CursorOff   0x0c
#define lcd_DisplayOn_CursorOn    0x0e
#define lcd_DisplayOff_CursorOff  0x08
#define lcd_DisplayOn_CursorOn_Blink      0x0f
#define lcd_Clear                 0x01
#define lcd_EntryMode             0x06
#define lcd_Home                  0x02
#define lcd_CGRAM                 0X40
#define lcd_SetCursor             0x80
#define lcd_FunctionReset         0x30
#define lcd_SHIFT_DISPLAY_RIGHT   0x1c      // shift the entire display right cursor follows the display shift
#define lcd_SHIFT_DISPLAY_LEFT    0x18      // shift the entire display left cursor follows the display shift
#define lcd_SHIFT_CURSOR_RIGHT    0x14      // shift the entire display right cursor follows the display shift
#define lcd_SHIFT_CURSOR_LEFT     0x10

/*******************************/

#define CLCD_Row_1 1
#define CLCD_Row_2 2

#define CLCD_col_1 1
#define CLCD_col_2 2
#define CLCD_col_3 3
#define CLCD_col_4 4
#define CLCD_col_5 5
#define CLCD_col_6 6
#define CLCD_col_7 7
#define CLCD_col_8 8
#define CLCD_col_9 9
#define CLCD_col_10 10
#define CLCD_col_11 11
#define CLCD_col_12 12
#define CLCD_col_13 13
#define CLCD_col_14 14
#define CLCD_col_14 14
#define CLCD_col_15 15
#define CLCD_col_16 16

#define CLCD_HIGH_NIBBLE                   0
#define CLCD_LOW_NIBBLE                    1

/**********************************/


void CLCD_voidInit         ( void                                              );
void CLCD_voidsendData      ( u8 copy_u8Data                                   );
void CLCD_voidsendCommand   ( u8 copy_u8Command                                );
void  CLCD_voidClearScreen  (void);
void CLCD_voidsendString     (   u8 * copy_u8ptrString                    );
void CLCD_voidSetPosition( u8 copy_u8Row , u8 copy_u8Col                        );

void CLCD_vSendIntNumber                   (s32 Copy_s32Number                  );
void CLCD_vSendFloatNumber                 (f64 Copy_f64Number                  );

void CLCD_voidShiftDisplayRight            (void                                );
void CLCD_voidShiftDisplayLeft             (void                                );

void CLCD_vSendExtraChar                   (u8 Copy_u8Row, u8 Copy_u8Col        );
#endif /* LCD_INTREFACE_H_ */
