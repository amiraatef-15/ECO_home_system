/*
 * LED_prog.c
 *
 *  Created on: Dec 21, 2024
 *      Author: alaa hassan
 */



#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"

#include "../MCAL/DIO_intervace.h"

#include "LED_intreface.h"
/*___________________________________________________________________________________________________________________*/

/*
* Breif : This Function initialize the pin which connected to led as output pin
* Parameters :
            => struct has the led port , pin, status
* return : void
*/
void LED_vInit(LED_config LED_Configuration)
{
	DIO_enumSetPinDirection(LED_Configuration.PortName, LED_Configuration.PinNumber, DIO_PIN_OUTPUT);
}

/*___________________________________________________________________________________________________________________*/

/*
* Breif : This Function set high on led pin ( led on )
* Parameters :
            => struct has the led port , pin, status
* return : void
*/
void LED_vTurnOn(LED_config LED_Configuration)
{
  if (LED_Configuration.ActiveState == ACTIVE_HIGH)
  {
	  DIO_enumWritePinValue(LED_Configuration.PortName, LED_Configuration.PinNumber, DIO_PIN_HIGH);
  }
  else if (LED_Configuration.ActiveState == ACTIVE_LOW)
  {
	  DIO_enumWritePinValue(LED_Configuration.PortName, LED_Configuration.PinNumber, DIO_PIN_LOW);
  }
}

/*___________________________________________________________________________________________________________________*/

/*
* Breif : This Function set low on led pin ( led off )
* Parameters :
             => struct has the led port , pin , status
* return : void
*/
void LED_vTurnOff(LED_config LED_Configuration)
{
  if (LED_Configuration.ActiveState == ACTIVE_HIGH)
  {
	  DIO_enumWritePinValue(LED_Configuration.PortName, LED_Configuration.PinNumber, DIO_PIN_LOW);
  }
  else if (LED_Configuration.ActiveState == ACTIVE_LOW)
  {
	  DIO_enumWritePinValue(LED_Configuration.PortName, LED_Configuration.PinNumber, DIO_PIN_HIGH);
  }
}

/*___________________________________________________________________________________________________________________*/

/*
* Breif : This Function toggle led pin
* Parameters :
             => struct has the led port , pin , status
* return : void
*/
void LED_vTog(LED_config LED_Configuration)
{
	DIO_enumTogglePinValue(LED_Configuration.PortName, LED_Configuration.PinNumber);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
