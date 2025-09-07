/*
 * KPD_prog.c
 *
 *  Created on: Jan 27, 2025
 *      Author: alaa hassan
 */


#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"

#include <util/delay.h>

#include "../MCAL/DIO_intervace.h"

#include "KEPD_interface.h"
#include "KPD_config.h"
#include "KEPD_private.h"

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function initialize the pin which connected to KPD as input pins
 * Parameters : Nothing
 * return : Nothing
 */
void KPD_vInit       (void)
{

  /*                    connect pull up for the pins of the rows                             */

DIO_enumConnectPullUp(KPD_PORT, KPD_R0, DIO_PIN_HIGH);
DIO_enumConnectPullUp(KPD_PORT, KPD_R1, DIO_PIN_HIGH);
DIO_enumConnectPullUp(KPD_PORT, KPD_R2, DIO_PIN_HIGH);
DIO_enumConnectPullUp(KPD_PORT, KPD_R3, DIO_PIN_HIGH);


  DIO_vSetHighNibbleDir(KPD_PORT, 0x0F);
  DIO_vWriteHighNibble (KPD_PORT, 0x0F);
}

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function used to get the pressed button of the kpd
 * Parameters : Nothing
 * return : the pressed button
 */
u8 KPD_u8GetPressed(void)
{
  u8 LOC_u8ReturnData = NOTPRESSED;
  u8 LOC_u8GetPressed;

  /* iterators  */
  u8 LOC_u8Row, LOC_u8Col;

  for (LOC_u8Col = 0 + KPD_COL_INIT; LOC_u8Col <KPD_COL_END + 1; LOC_u8Col++)
  {
	  DIO_enumWritePinValue(KPD_PORT, LOC_u8Col, DIO_PIN_LOW);         // Low on the columns

    for (LOC_u8Row = 0 + KPD_ROW_INIT; LOC_u8Row < KPD_ROW_END + 1; LOC_u8Row++)
    {
    	DIO_enumReadPinValue (KPD_PORT, LOC_u8Row, &LOC_u8GetPressed); // retun the row value
      /*
      if the row is high ....there is no pressed buttons
      if the row is low ....there is pressed button ===>> I will check on this
      */
      if (LOC_u8GetPressed == 0)
      {
        _delay_ms(50);         // delay for bouncing

        DIO_enumReadPinValue(KPD_PORT, LOC_u8Row, &LOC_u8GetPressed); // to make sure that the button is pressed & check again

        if (LOC_u8GetPressed == 0)
        {
          /*
          # Important Note #
                    the button will khnow by the row and the column (ASCII Code)
                    ==> Hint1 : I already defined The ASCII Codes in 2D array at --> "KPD_config.h"
                    ==> Hint2 : if there is no pressed buttons , it will retured NOTPRESSED (0xff) and there is not any button has this ASCII (0xff)
          */

          LOC_u8ReturnData = KPD_u8Buttons[LOC_u8Row - KPD_ROW_INIT][LOC_u8Col - KPD_COL_INIT];
        }
        // stay here if the button is pressed   # we could put delay 200 ms instead of that
        DIO_enumReadPinValue(KPD_PORT, LOC_u8Row, &LOC_u8GetPressed);
        while (DIO_PIN_LOW == LOC_u8GetPressed) /*  This cond for safty instead of (LOC_u8GetPressed == DIO_PIN_LOW) if i foget = */
        {
        	DIO_enumReadPinValue(KPD_PORT, LOC_u8Row, &LOC_u8GetPressed);
        }

        break;
      }
    }

    // return this column’s pin to high
    DIO_enumWritePinValue(KPD_PORT, LOC_u8Col, DIO_PIN_HIGH);
  }

  return LOC_u8ReturnData;
}
