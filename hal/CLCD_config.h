/*
 * CLCD_config.h
 *
 * Created: 12/15/2024 5:53:27 PM
 *  Author: alaa hassan
 */


#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define CLCD_MODE            4

#if CLCD_MODE == 4
/*
*Optoins :-
  1- CLCD_HIGH_NIBBLE
  2- CLCD_LOW_NIBBLE
*/
#define CLCD_DATA_NIBBLE CLCD_LOW_NIBBLE

#endif

#define CLCD_DISPLAY_CURSOR lcd_DisplayOn_CursorOn

#define CLCD_DATA_PORT     DIO_PORTB
#define CLCD_CONTROL_PORT  DIO_PORTB


#define CLCD_RS            DIO_PIN5
#define CLCD_RW            DIO_PIN6
#define CLCD_EN            DIO_PIN7



#endif /* CLCD_CONFIG_H_ */
