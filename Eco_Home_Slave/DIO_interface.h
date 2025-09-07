/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DIO_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : MCAL
 *  SWC    : DIO/GPIO
 *
 */ 

 
#include "STD_TYPES.h"
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_



#define DIO_PIN_OUTPUT 1
#define DIO_PIN_INPUT 0

#define DIO_PIN_HIGH 1
#define DIO_PIN_LOW 0

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_PORT_OUTPUT		0xFF
#define DIO_PORT_INPUT		0

#define DIO_PORT_HIGH 		0xFF
#define DIO_PORT_LOW  		0

#define PUD   2
#define  SFIOR   *((volatile u8*)0x50)

/*>>>>>>>>>>>>>>>>>>>>>>>>> "PINS" <<<<<<<<<<<<<<<<<<<<<<<<<<*/
void DIO_vSetPinDirection (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_Direction);
void DIO_vSetPinValue     (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Value);
void DIO_vTOGPinValue     (u8 Copy_u8PORT , u8 Copy_u8PIN );
u8   DIO_u8GetPinValue     (u8 Copy_u8PORT , u8 Copy_u8PIN);
void DIO_vConnectPullup (u8 Copy_u8PORT ,u8 Copy_u8PIN, u8 Copy_u8ConnectPullup);
/*>>>>>>>>>>>>>>>>>>>>>>>>> "PORTS" <<<<<<<<<<<<<<<<<<<<<<<<<<*/
void DIO_vSetPortDirection (u8 Copy_u8PORT , u8 Copy_Direction);
void DIO_vSetPortValue     (u8 Copy_u8PORT , u8 Copy_u8Value);
void DIO_vTOGPortValue     (u8 Copy_u8PORT);
u8 DIO_u8GetPortValue      (u8 Copy_u8PORT);

/*>>>>>>>>>>>>>>>>>>>>>>>>> "HALF_PORT" <<<<<<<<<<<<<<<<<<<<<<<<<<*/
void DIO_voidWriteHighNibbles(u8 Copy_u8PORT,u8 Copy_u8value);
void DIO_voidWriteLowNibbles (u8 Copy_u8PORT,u8 Copy_u8value);

#endif
