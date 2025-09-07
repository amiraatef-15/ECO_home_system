/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LCD_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : HAL
 *  SWC    : LCD
 *
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "LCD_config.h" // to Select the mode

#if   LCD_MODE == 4
#define FOUR_BITS                     0x28          //4 bits mode initialization
#elif LCD_MODE == 8
#define EIGHT_BITS                    0x38          //8 bits mode initialization (8-bit data, 2-line display, 5 x 7 font )
#endif

#define lcd_DOn_COff                  0x0c          // display on, cursor off, don't blink character 
#define lcd_DOn_COn                   0x0e          // display on, cursor on, don't blink character 
#define lcd_DOff_Cff                  0x08          // turn display off
#define lcd_Clear                     0x01          //replace all characters with ASCII 'space'  
#define lcd_EntryMode                 0x06          // shift cursor from left to right on read/write
#define lcd_Home                      0x02          // return cursor to first position on first line 
#define lcd_CGRAM                     0x40          // the first Place/Address at CGRAM
#define lcd_FunctionReset             0x30          // reset the LCD


#define lcd_Row1                      0x80          // set cursor position
#define lcd_Row2                      0xc0   
#define lcd_Row3                      0x90   
#define lcd_Row4                      0xd0   


#define LCD_ROW_1   1
#define LCD_ROW_2   2
#define LCD_ROW_3   3
#define LCD_ROW_4   4

#define LCD_COL_1   1
#define LCD_COL_2   2
#define LCD_COL_3   3
#define LCD_COL_4   4
#define LCD_COL_5   5
#define LCD_COL_6   6
#define LCD_COL_7   7
#define LCD_COL_8   8
#define LCD_COL_9   9
#define LCD_COL_10  10
#define LCD_COL_11  11
#define LCD_COL_12  12
#define LCD_COL_13  13
#define LCD_COL_14  14
#define LCD_COL_15  15
#define LCD_COL_16  16
#define LCD_COL_17  17
#define LCD_COL_18  18
#define LCD_COL_19  19
#define LCD_COL_20  20

void LCD_vInit                      (void);
void LCD_vSendData                  (u8 Copy_u8Data);
void LCD_vSendCommand               (u8 Copy_u8Commend );
void LCD_vSendString                (const u8 * Copy_u8ptrString);
void LCD_vSendNumber                (u64 Copy_u64Number );
void LCD_vSetPosition               (u8 Copy_u8Row , u8 Copy_u8Col );
void LCD_vSendExtraChar             (u8 Copy_u8Row , u8 Copy_u8Col );
void LCD_vClearScreen               (void );

#endif 
