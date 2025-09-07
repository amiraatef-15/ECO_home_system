/*
 * DIO_intervace.h
 *
 * Created: 12/19/2024 3:06:29 PM
 *  Author: alaa hassan
 */


#ifndef DIO_INTERVACE_H_
#define DIO_INTERVACE_H_

#include "../lib/std_typs.h"

typedef enum
{
	DIO_NOK,
	DIO_OK
}DIO_ErrorStatus;


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


#define HIGH  1
#define LOW 0

#define DIO_HIGH 1
#define DIO_LOW 0

#define DIO_OUTPUT 1
#define DIO_INPUT 0


#define DIO_PORT_OUTPUT 0xFF
#define DIO_PORT_INPUT  0

#define DIO_PORT_HIGH 1
#define DIO_PORT_LOW 0


// Pull UP
#define PUD                 2

//#define PUD 2


void DIO_voidSetPinDirection  ( u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Direction );
void DIO_voidSetPinValue      ( u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value     );
void DIO_voidGetPinValue   ( u8 copy_u8PORT , u8 copy_u8PIN                       );
void DIO_voidTogglePinValue   (u8 copy_u8PORT , u8 copy_u8PIN                       );

//IO PINS

DIO_ErrorStatus DIO_enumSetPinDirection  (u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Direction  );
DIO_ErrorStatus DIO_enumWritePinValue   (u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value       );
DIO_ErrorStatus DIO_enumReadPinValue  (u8 copy_u8PORT , u8 copy_u8PIN , u8 * copy_ptru8Data     );
DIO_ErrorStatus DIO_enumTogglePinValue  (u8 copy_u8PORT , u8 copy_u8PIN                         );


/*Internal Pull UP*/
DIO_ErrorStatus DIO_enumConnectPullUp      (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8ConnectPullup);


//io ports

DIO_ErrorStatus DIO_enumSetPortDirection  (u8 copy_u8PORT , u8 copy_u8Direction   );
DIO_ErrorStatus DIO_enumWritePortValue   (u8 copy_u8PORT , u8 portu8Value         );
DIO_ErrorStatus DIO_enumReadPortValue  (u8 copy_u8PORT , u8* copy_ptrData         );
DIO_ErrorStatus DIO_enumTogglePortValue  (u8 copy_u8PORT);

//io nibbles

DIO_ErrorStatus DIO_vSetLowNibbleDir       (u8 Copy_u8PORT, u8 value);
DIO_ErrorStatus DIO_vSetHighNibbleDir      (u8 Copy_u8PORT, u8 value);
DIO_ErrorStatus DIO_vWriteLowNibble        (u8 Copy_u8PORT, u8 value);
DIO_ErrorStatus DIO_vWriteHighNibble       (u8 Copy_u8PORT, u8 value);




#endif /* DIO_INTERVACE_H_ */
