/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LCD_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : HAL
 *  SWC    : LCD
 *
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_MODE  4

#define LCD_DATA_PORT      DIO_PORTB
/* RS,RW,EN */
#define LCD_CONTROL_PORT   DIO_PORTB

#define LCD_RS             DIO_PIN0
#define LCD_RW             DIO_PIN1
#define LCD_EN             DIO_PIN2

#endif
