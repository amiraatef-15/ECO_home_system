/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DIO_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : MCAL
 *  SWC    : DIO/GPIO
 *
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

/*>>>>>>>>>>>>>>>>>>>>>>>>> "PINS" <<<<<<<<<<<<<<<<<<<<<<<<<<*/
void DIO_vSetPinDirection (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_Direction)
{
	if (Copy_Direction == DIO_PIN_OUTPUT)
	{
		switch (Copy_u8PORT)
		{
		case DIO_PORTA : SET_BIT(DDRA,Copy_u8PIN);break;
		case DIO_PORTB : SET_BIT(DDRB,Copy_u8PIN);break;
		case DIO_PORTC : SET_BIT(DDRC,Copy_u8PIN);break;
		case DIO_PORTD : SET_BIT(DDRD,Copy_u8PIN);break;
		}
	}
	else if (Copy_Direction == DIO_PIN_INPUT)
	{
		switch (Copy_u8PORT)
		{
		case DIO_PORTA : CLR_BIT(DDRA,Copy_u8PIN);break;
		case DIO_PORTB : CLR_BIT(DDRB,Copy_u8PIN);break;
		case DIO_PORTC : CLR_BIT(DDRC,Copy_u8PIN);break;
		case DIO_PORTD : CLR_BIT(DDRD,Copy_u8PIN);break;
		}
	}	
}

void DIO_vSetPinValue (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Value)
{
	if (Copy_u8Value == DIO_PIN_HIGH)
	{
		switch (Copy_u8PORT)
		{
		case DIO_PORTA : SET_BIT(PORTA,Copy_u8PIN);break;
		case DIO_PORTB : SET_BIT(PORTB,Copy_u8PIN);break;
		case DIO_PORTC : SET_BIT(PORTC,Copy_u8PIN);break;
		case DIO_PORTD : SET_BIT(PORTD,Copy_u8PIN);break;
		}
	}
	else if (Copy_u8Value == DIO_PIN_LOW)
	{
		switch (Copy_u8PORT)
		{
		case DIO_PORTA : CLR_BIT(PORTA,Copy_u8PIN);break;
		case DIO_PORTB : CLR_BIT(PORTB,Copy_u8PIN);break;
		case DIO_PORTC : CLR_BIT(PORTC,Copy_u8PIN);break;
		case DIO_PORTD : CLR_BIT(PORTD,Copy_u8PIN);break;
		}
	}	
}

void DIO_vTOGPinValue (u8 Copy_u8PORT , u8 Copy_u8PIN )
{
	switch (Copy_u8PORT)
		{
		case DIO_PORTA : TOG_BIT(PORTA,Copy_u8PIN);break;
		case DIO_PORTB : TOG_BIT(PORTB,Copy_u8PIN);break;
		case DIO_PORTC : TOG_BIT(PORTC,Copy_u8PIN);break;
		case DIO_PORTD : TOG_BIT(PORTD,Copy_u8PIN);break;
		}
}

u8 DIO_vGetPinValue (u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	u8 LOC_u8Sstatues = 0;
	switch (Copy_u8PORT)
		{
		case DIO_PORTA : LOC_u8Sstatues = GET_BIT(PINA,Copy_u8PIN);break;
		case DIO_PORTB : LOC_u8Sstatues = GET_BIT(PINB,Copy_u8PIN);break;
		case DIO_PORTC : LOC_u8Sstatues = GET_BIT(PINC,Copy_u8PIN);break;
		case DIO_PORTD : LOC_u8Sstatues = GET_BIT(PIND,Copy_u8PIN);break;
		}
	return	LOC_u8Sstatues;
}
/*>>>>>>>>>>>>>>>>>>>>>>>>> "PORTS" <<<<<<<<<<<<<<<<<<<<<<<<<<*/
void DIO_vSetPortDirection (u8 Copy_u8PORT , u8 Copy_Direction)
{
    switch (Copy_u8PORT)
		{
		case     DIO_PORTA: DDRA = Copy_Direction; break;
		case     DIO_PORTB: DDRB = Copy_Direction; break;
		case     DIO_PORTC: DDRC = Copy_Direction; break;
		case     DIO_PORTD: DDRD = Copy_Direction; break;
		}
}

void DIO_vSetPortValue (u8 Copy_u8PORT , u8 Copy_u8Value)
{
	 switch (Copy_u8PORT)
		{
		case     DIO_PORTA: PORTA = Copy_u8Value; break;
		case     DIO_PORTB: PORTB = Copy_u8Value; break;
		case     DIO_PORTC: PORTC = Copy_u8Value; break;
		case     DIO_PORTD: PORTD = Copy_u8Value; break;
		}
}

void DIO_vTOGPortValue (u8 Copy_u8PORT)
{
	switch (Copy_u8PORT)
		{
		case     DIO_PORTA: PORTA = ~PORTA; break;
		case     DIO_PORTB: PORTB = ~PORTB; break;
		case     DIO_PORTC: PORTC = ~PORTC; break;
		case     DIO_PORTD: PORTD = ~PORTD; break;
		}
}

u8 DIO_vGetPortValue (u8 Copy_u8PORT)
{
	u8 LOC_u8Sstatues = 0;
	switch (Copy_u8PORT)
		{
		case DIO_PORTA : LOC_u8Sstatues = PINA ;break;
		case DIO_PORTB : LOC_u8Sstatues = PINB ;break;
		case DIO_PORTC : LOC_u8Sstatues = PINC ;break;
		case DIO_PORTD : LOC_u8Sstatues = PIND ;break;
		}
	return	LOC_u8Sstatues;
}

/*>>>>>>>>>>>>>>>>>>>>>>>>> "HALF_PORT" <<<<<<<<<<<<<<<<<<<<<<<<<<*/

void DIO_voidWriteHighNibbles(u8 Copy_u8PORT,u8 Copy_u8value)
{
	Copy_u8value= (Copy_u8value<<4) ;
	switch(Copy_u8PORT)
		{
		case DIO_PORTA:
			PORTA&=0x0f;                   // make sure the high bits = 0000
			PORTA|=Copy_u8value;		  //Set only the high nibble of the port A by the given value
			break ;
		case DIO_PORTB:
			PORTB&=0x0f;                  //Set only the high nibble of the port B by the given value
			PORTB|=Copy_u8value;
			break ;
		case DIO_PORTC :
			PORTC&=0x0f;                 //Set only the high nibble of the port C by the given value
			PORTC|=Copy_u8value;
			break ;
		case DIO_PORTD:
			PORTD&=0x0f;                 //Set only the high nibble of the port D by the given value
			PORTD|=Copy_u8value;
			break ;
		default: break ;
		}
}

void DIO_voidWriteLowNibbles(u8 Copy_u8PORT,u8 Copy_u8value)
{
	Copy_u8value&=0x0f;
	switch(Copy_u8PORT)
		{
		case DIO_PORTA:
			PORTA&=0xf0;                   // make sure the high bits = 0000
			PORTA|=Copy_u8value;		  //Set only the high nibble of the port A by the given value
			break ;
		case DIO_PORTB:
			PORTB&=0xf0;                  //Set only the high nibble of the port B by the given value
			PORTB|=Copy_u8value;
			break ;
		case DIO_PORTC:
			PORTC&=0xf0;                 //Set only the high nibble of the port C by the given value
			PORTC|=Copy_u8value;
			break ;
		case DIO_PORTD:
			PORTD&=0xf0;                 //Set only the high nibble of the port D by the given value
			PORTD|=Copy_u8value;
			break ;
		default: break ;
		}
}


void DIO_vConnectPullup (u8 Copy_u8PORT ,u8 Copy_u8PIN, u8 Copy_u8ConnectPullup){
	switch(Copy_u8PORT)
		{
		/* Connect or disconnect the pull up resistance to the given pin in port A */
		case DIO_PORTA:
			if(Copy_u8ConnectPullup==DIO_PIN_HIGH)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRA,Copy_u8PIN);
				SET_BIT(PORTA,Copy_u8PIN);
			}
			else
			{
				CLR_BIT(PORTA,Copy_u8PIN);
			}
			break;
			/* Connect or disconnect the pull up resistance to the given pin in port B */
		case DIO_PORTB:
			if(Copy_u8ConnectPullup==DIO_PIN_HIGH)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRB,Copy_u8PIN);
				SET_BIT(PORTB,Copy_u8PIN);
			}
			else
			{
				CLR_BIT(PORTB,Copy_u8PIN);
			}
			break;
			/* Connect or disconnect the pull up resistance to the given pin in port C */
		case DIO_PORTC:
			if(Copy_u8ConnectPullup==DIO_PIN_HIGH)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRC,Copy_u8PIN);
				SET_BIT(PORTC,Copy_u8PIN);
			}
			else
			{
				CLR_BIT(PORTC,Copy_u8PIN);
			}
			break;
			/* Connect or disconnect the pull up resistance to the given pin in port D */
		case DIO_PORTD:
			if(Copy_u8ConnectPullup==DIO_PIN_HIGH)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRD,Copy_u8PIN);
				SET_BIT(PORTD,Copy_u8PIN);
			}
			else
			{
				CLR_BIT(PORTD,Copy_u8PIN);
			}
			break;
		}
}
