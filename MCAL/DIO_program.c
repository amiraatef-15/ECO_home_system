/*
 * DIO_program.c
 *
 * Created: 12/19/2024 3:11:29 PM
 *  Author: alaa hassan
 */


#include "../lib/std_typs.h"
#include "../lib/BIT_MATH.h"

#include "DIO_intervace.h"
#include "DIO_private.h"




//void DIO_voidSetPinDirection  ( u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Direction ){

DIO_ErrorStatus DIO_enumSetPinDirection  (u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Direction )
{
 DIO_ErrorStatus loc_enumState =DIO_OK ;
 //make sure that the port id and pin id are in valid rane
 if((copy_u8PORT <= DIO_PORTD) && (copy_u8PIN <= DIO_PIN7)){

	if(copy_u8Direction == DIO_PIN_OUTPUT ){
	switch(copy_u8PORT){
	case DIO_PORTA : SET_BIT(DDRA_REG, copy_u8PIN );break;
	case DIO_PORTB : SET_BIT(DDRB_REG, copy_u8PIN );break;
	case DIO_PORTC : SET_BIT(DDRC_REG, copy_u8PIN );break;
	case DIO_PORTD : SET_BIT(DDRD_REG, copy_u8PIN );break;
	}
	}
	else if(copy_u8Direction == DIO_PIN_INPUT ){

		switch(copy_u8PORT){
	case DIO_PORTA : CLR_BIT(DDRA_REG, copy_u8PIN );break;
	case DIO_PORTB : CLR_BIT(DDRB_REG, copy_u8PIN );break;
	case DIO_PORTC : CLR_BIT(DDRC_REG, copy_u8PIN );break;
	case DIO_PORTD : CLR_BIT(DDRD_REG, copy_u8PIN );break;

	}
}
else {
loc_enumState =DIO_NOK ;
}
}
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}

//void DIO_voidWritePinValue      ( u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value     ){

DIO_ErrorStatus DIO_enumWritePinValue   (u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value )
{
DIO_ErrorStatus loc_enumState =DIO_OK ;
 //make sure that the port id and pin id are in valid rane
 if((copy_u8PORT <= DIO_PORTD) && (copy_u8PIN <= DIO_PIN7))
 {
	if(copy_u8Value == DIO_PIN_OUTPUT )
	{
	switch(copy_u8PORT)
	{
	case DIO_PORTA : SET_BIT(PORTA_REG , copy_u8PIN );break;
	case DIO_PORTB : SET_BIT(PORTB_REG, copy_u8PIN );break;
	case DIO_PORTC : SET_BIT(PORTC_REG, copy_u8PIN );break;
	case DIO_PORTD : SET_BIT(PORTD_REG, copy_u8PIN );break;
	}
	}
	else if(copy_u8Value == DIO_PIN_INPUT ){

		switch(copy_u8PORT){
	case DIO_PORTA : CLR_BIT(PORTA_REG , copy_u8PIN );break;
	case DIO_PORTB : CLR_BIT(PORTB_REG, copy_u8PIN );break;
	case DIO_PORTC : CLR_BIT(PORTC_REG, copy_u8PIN );break;
	case DIO_PORTD : CLR_BIT(PORTD_REG, copy_u8PIN );break;
		}
	}
else {
loc_enumState =DIO_NOK ;
}
	}
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}

//u8 void DIO_voidGetPinValue   ( u8 copy_u8PORT , u8 copy_u8PIN


DIO_ErrorStatus DIO_enumReadPinValue  (u8 copy_u8PORT , u8 copy_u8PIN , u8* copy_ptru8Data ){
DIO_ErrorStatus loc_enumState =DIO_OK ;
 //make sure that the port id and pin id are in valid rane
 if((copy_u8PORT <= DIO_PORTD) && (copy_u8PIN <= DIO_PIN7)){
//u8 loc_u8status=0;
switch(copy_u8PORT){
	case DIO_PORTA : * copy_ptru8Data= GET_BIT(PINA_REG, copy_u8PIN );break;
	case DIO_PORTB : * copy_ptru8Data= GET_BIT(PINB_REG, copy_u8PIN );break;
	case DIO_PORTC : * copy_ptru8Data= GET_BIT(PINC_REG, copy_u8PIN );break;
	case DIO_PORTD : * copy_ptru8Data= GET_BIT(PIND_REG, copy_u8PIN );break;
}
 }
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}
//void DIO_voidTogglePinValue   (u8 copy_u8PORT , u8 copy_u8PIN   ){

DIO_ErrorStatus DIO_enumTogglePinValue  (u8 copy_u8PORT , u8 copy_u8PIN  )
{
DIO_ErrorStatus loc_enumState = DIO_OK ;

	if((copy_u8PORT <= DIO_PORTD) && (copy_u8PIN <= DIO_PIN7))
	{
	switch(copy_u8PORT)
	{
	case DIO_PORTA : TOG_BIT(PORTA_REG , copy_u8PIN );break;
	case DIO_PORTB : TOG_BIT(PORTB_REG, copy_u8PIN );break;
	case DIO_PORTC : TOG_BIT(PORTC_REG, copy_u8PIN );break;
	case DIO_PORTD : TOG_BIT(PORTD_REG, copy_u8PIN );break;
	}

}
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}

DIO_ErrorStatus DIO_enumSetPortDirection  (u8 copy_u8PORT , u8 copy_u8Direction )
{
DIO_ErrorStatus loc_enumState =DIO_OK ;

	if(copy_u8PORT <= DIO_PORTD )
	{
	switch(copy_u8PORT)
	{
	case DIO_PORTA : (DDRA_REG = copy_u8Direction );break;
	case DIO_PORTB : (DDRB_REG = copy_u8Direction );break;
	case DIO_PORTC : (DDRC_REG = copy_u8Direction );break;
	case DIO_PORTD : (DDRD_REG = copy_u8Direction );break;
	default: loc_enumState =DIO_NOK ; break;
	}
}
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}


DIO_ErrorStatus DIO_enumWritePortValue   (u8 copy_u8PORT , u8 portu8Value         )
{
DIO_ErrorStatus loc_enumState =DIO_OK ;

	if((copy_u8PORT <= DIO_PORTD) && ((portu8Value <= 255)|| (portu8Value == DIO_PORT_LOW)||(portu8Value == DIO_PORT_HIGH)))
	{
	switch(copy_u8PORT){
	case DIO_PORTA : PORTA_REG  = portu8Value ;break;
	case DIO_PORTB : PORTB_REG = portu8Value ;break;
	case DIO_PORTC : PORTC_REG = portu8Value ;break;
	case DIO_PORTD : PORTD_REG = portu8Value ;break;
	}
}
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}

DIO_ErrorStatus DIO_enumReadPortValue  (u8 copy_u8PORT , u8 * copy_ptrData )
{
DIO_ErrorStatus loc_enumState =DIO_OK ;

	if((copy_u8PORT <= DIO_PORTD))
	{
 switch(copy_u8PORT)
 {
	case DIO_PORTA : * copy_ptrData= PINA_REG;break;
	case DIO_PORTB : * copy_ptrData=PINA_REG;break;
	case DIO_PORTC : * copy_ptrData= PINA_REG;break;
	case DIO_PORTD : * copy_ptrData= PINA_REG;break;
	default	: loc_enumState =DIO_NOK ;break;
 }
	}
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}
DIO_ErrorStatus DIO_enumTogglePortValue  (u8 copy_u8PORT)
{
DIO_ErrorStatus loc_enumState =DIO_OK ;

if((copy_u8PORT <= DIO_PORTD))
{
switch(copy_u8PORT)
{
	case DIO_PORTA : PORTA_REG  = ~PORTA_REG;break;
	case DIO_PORTB : PORTB_REG = ~PORTB_REG;break;
	case DIO_PORTC : PORTC_REG = ~PORTC_REG;break;
	case DIO_PORTD : PORTD_REG = ~PORTD_REG;break;
}
}
else {
loc_enumState =DIO_NOK ;
}
return loc_enumState ;
}

/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function connected internal pull up
 * Parameters :
      =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
      =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
    =>Copy_u8ConnectPullup --> [DIO_PIN_HIGH , DIO_PIN_LOW ]
 * return : its status
 */
DIO_ErrorStatus DIO_enumConnectPullUp(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8ConnectPullup)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
  {
    switch (Copy_u8PORT)
    {
    /* Connect or disconnect the pull up resistance to the given pin in port A */
    case DIO_PORTA:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD); // It's default is zero
        CLR_BIT(DDRA_REG, Copy_u8PIN);
        SET_BIT(PORTA_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTA_REG, Copy_u8PIN);
      }
      break;
      /* Connect or disconnect the pull up resistance to the given pin in port B */
    case DIO_PORTB:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD);
        CLR_BIT(DDRB_REG, Copy_u8PIN);
        SET_BIT(PORTB_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTB_REG, Copy_u8PIN);
      }
      break;
      /* Connect or disconnect the pull up resistance to the given pin in port C */
    case DIO_PORTC:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD );
        CLR_BIT(DDRC_REG, Copy_u8PIN);
        SET_BIT(PORTC_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTC_REG, Copy_u8PIN);
      }
      break;
      /* Connect or disconnect the pull up resistance to the given pin in port D */
    case DIO_PORTD:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD);
        CLR_BIT(DDRD_REG, Copy_u8PIN);
        SET_BIT(PORTD_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTD_REG, Copy_u8PIN);
      }
      break;
    }
  }

  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}


/*
 * Breif : This Function write value on low nibbles of the Port
 * Parameters :
    =>Copy_u8PORT  --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
    =>Copy_u8value --> to set its low bits on high nibble oh register
 * return : its status
 *
 *Hint1 : Low Nibbles = Least Pins [0:3]
 *Hint2 : This Function also take the first 4 bits from the value (#) => xxxx#### AND put it in low nobbles
 *
 */
DIO_ErrorStatus DIO_vWriteLowNibble(u8 Copy_u8PORT, u8 value)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value &= 0x0F;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      PORTA_REG &= 0xF0; // Set only the high nibble of the port A by the given value
      PORTA_REG |= value;
      break;
    case DIO_PORTB:
      PORTB_REG &= 0xF0; // Set only the high nibble of the port B by the given value
      PORTB_REG |= value;
      break;
    case DIO_PORTC:
      PORTC_REG &= 0xF0; // Set only the high nibble of the port C by the given value
      PORTC_REG |= value;
      break;
    case DIO_PORTD:
      PORTD_REG &= 0xF0; // Set only the high nibble of the port D by the given value
      PORTD_REG |= value;
      break;
    default:
      break;
    }
  }

  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}
/*
DIO_ErrorStatus DIO_vWriteLowNibble(u8 Copy_u8PORT, u8 value)
{
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN0, READ_BIT(value, DIO_PIN0));
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN1, READ_BIT(value, DIO_PIN1));
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN2, READ_BIT(value, DIO_PIN2));
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN3, READ_BIT(value, DIO_PIN3));
}
*/
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function write value on high nibbles of the Port
 * Parameters :
    =>Copy_u8PORT  --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
    =>Copy_u8value --> to set its high bits on high nibble oh register
 * return : its status
 *
 *Hint1 : High Nibbles = Most Pins [4:7]
 *Hint2 : This Function take the first 4 bits from the value (#) => xxxx#### AND put it in high nobbles
 *
 */
DIO_ErrorStatus DIO_vWriteHighNibble(u8 Copy_u8PORT, u8 value)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value <<= 4;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      PORTA_REG &= 0x0F;
      PORTA_REG|= value;
      break;
    case DIO_PORTB:
      PORTB_REG &= 0x0F;
      PORTB_REG |= value;
      break;
    case DIO_PORTC:
      PORTC_REG &= 0x0F;
      PORTC_REG |= value;
      break;
    case DIO_PORTD:
      PORTD_REG &= 0x0F;
      PORTD_REG |= value;
      break;
    default:
      break;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}

/*___________________________________________________________________________________________________________________*/

DIO_ErrorStatus DIO_vSetLowNibbleDir(u8 Copy_u8PORT, u8 value)
{DIO_ErrorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value &= 0x0F;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      DDRA_REG &= 0xF0; // Set only the high nibble of the port A by the given value
      DDRA_REG |= value;
      break;
    case DIO_PORTB:
      DDRB_REG &= 0xF0; // Set only the high nibble of the port B by the given value
      DDRB_REG |= value;
      break;
    case DIO_PORTC:
      DDRC_REG &= 0xF0; // Set only the high nibble of the port C by the given value
      DDRC_REG |= value;
      break;
    case DIO_PORTD:
      DDRD_REG &= 0xF0; // Set only the high nibble of the port D by the given value
      DDRD_REG|= value;
      break;
    default:
      break;
    }
  }

  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}

/*___________________________________________________________________________________________________________________*/

DIO_ErrorStatus DIO_vSetHighNibbleDir(u8 Copy_u8PORT, u8 value)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value <<= 4;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      DDRA_REG &= 0x0F;
      DDRA_REG |= value;
      break;
    case DIO_PORTB:
      DDRB_REG &= 0x0F;
      DDRB_REG |= value;
      break;
    case DIO_PORTC:
      DDRC_REG &= 0x0F;
      DDRC_REG |= value;
      break;
    case DIO_PORTD:
      DDRD_REG &= 0x0F;
      DDRD_REG |= value;
      break;
    default:
      break;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}

//____________________
