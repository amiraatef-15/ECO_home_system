/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LCD_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By     : Abdallah Saleh
 *  Layer  : HAL
 *  SWC    : LCD
 *
 *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include "LCD_extrachar.h"
#include "LCD_extrachar.h"


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      LCD_vInit      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_vInit( void )
{



	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if LCD_MODE == 8

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);

	// All Pins as OutPut pins
	DIO_vSetPortDirection   ( LCD_DATA_PORT    , DIO_PORT_OUTPUT );
	DIO_vSetPinDirection  ( LCD_CONTROL_PORT , LCD_RS , DIO_PIN_OUTPUT  );
	DIO_vSetPinDirection  ( LCD_CONTROL_PORT , LCD_RW , DIO_PIN_OUTPUT  );
	DIO_vSetPinDirection  ( LCD_CONTROL_PORT , LCD_EN , DIO_PIN_OUTPUT  );

	/* Return cursor to the first position on the first line  */
	LCD_vSendCommand(lcd_Home);
	_delay_ms(1);

	/*FUNCTION SET Command : 2 lines , 5*8 font size */
	LCD_vSendCommand (EIGHT_BITS); // 8 Bit Mode ==> 0x38
	_delay_ms(1); // wait more than 39 Ms

	/* DISPLAY & Cursor (ON / ON) Control */
	LCD_vSendCommand( lcd_DOn_COff );
	_delay_ms(1);

	/* DISPLAY CLEAR */
	LCD_vClearScreen();

	/* ENTRY MODE  SET*/
	LCD_vSendCommand( lcd_EntryMode );
	_delay_ms(1);


	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#elif LCD_MODE == 4

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);

	// All Pins as OutPut pins
	DIO_vSetPinDirection  ( LCD_DATA_PORT    ,DIO_PIN4, DIO_PIN_OUTPUT   );
	DIO_vSetPinDirection  ( LCD_DATA_PORT    ,DIO_PIN5, DIO_PIN_OUTPUT   );
	DIO_vSetPinDirection  ( LCD_DATA_PORT    ,DIO_PIN6, DIO_PIN_OUTPUT   );
	DIO_vSetPinDirection  ( LCD_DATA_PORT    ,DIO_PIN7, DIO_PIN_OUTPUT   );
	DIO_vSetPinDirection  ( LCD_CONTROL_PORT , LCD_RS , DIO_PIN_OUTPUT  );
	DIO_vSetPinDirection  ( LCD_CONTROL_PORT , LCD_RW , DIO_PIN_OUTPUT  );
	DIO_vSetPinDirection  ( LCD_CONTROL_PORT , LCD_EN , DIO_PIN_OUTPUT  );

	/* Return cursor to the first position on the first line  */
	LCD_vSendCommand(lcd_Home);
	_delay_ms(1);

	/*FUNCTION SET Command : 2 lines , 5*8 font size */
	LCD_vSendCommand( FOUR_BITS ); // 8 Bit Mode ==> 0x38
	_delay_ms(1); // wait more than 39 Ms

	/* DISPLAY & Cursor (ON / ON) Control */
	LCD_vSendCommand( lcd_DOn_COff );
	_delay_ms(1);

	/* DISPLAY CLEAR */
	LCD_vClearScreen();

	/* ENTRY MODE  SET*/
	LCD_vSendCommand( lcd_EntryMode );
	_delay_ms(1);

#endif
}

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>




	void LCD_vSendData    ( u8 Copy_u8Data ){

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if   LCD_MODE == 8

		DIO_vSetPortValue ( LCD_DATA_PORT , Copy_u8Data);
		DIO_vSetPinValue  ( LCD_CONTROL_PORT , LCD_RS , DIO_PIN_HIGH );
		DIO_vSetPinValue  ( LCD_CONTROL_PORT , LCD_RW , DIO_PIN_LOW  );
		LCD_vSendFEdge();

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif   LCD_MODE == 4

		DIO_vSetPinValue  ( LCD_CONTROL_PORT , LCD_RS , DIO_PIN_HIGH );
		DIO_vSetPinValue  ( LCD_CONTROL_PORT , LCD_RW , DIO_PIN_LOW  );
		DIO_voidWriteHighNibbles (LCD_DATA_PORT ,(Copy_u8Data>>4));            // send the most 4 bits of data to high nibbles
		LCD_vSendFEdge();
		DIO_voidWriteHighNibbles (LCD_DATA_PORT ,Copy_u8Data);               // send the least 4 bits of data to high nibbles
		LCD_vSendFEdge();

#endif

		_delay_ms(1);
	}


	void LCD_vSendString  (const u8 * Copy_u8ptrString ){

		u8 LOC_u8Iterator = 0 ;

		while( Copy_u8ptrString[LOC_u8Iterator] != '\0' ){

			LCD_vSendData( Copy_u8ptrString[LOC_u8Iterator] );
			LOC_u8Iterator++ ;

		}

	}
	void LCD_vSendCommand ( u8 Copy_u8Command ){

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if   LCD_MODE == 8

		DIO_vSetPortValue ( LCD_DATA_PORT    , Copy_u8Command);
		DIO_vSetPinValue  ( LCD_CONTROL_PORT , LCD_RS , DIO_PIN_LOW);
		// RW always connect to GND to Write
		DIO_vSetPinValue          (LCD_CONTROL_PORT,LCD_RW , DIO_PIN_LOW);
		LCD_vSendFEdge();

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif   LCD_MODE == 4

		DIO_vSetPinValue  ( LCD_CONTROL_PORT , LCD_RS , DIO_PIN_LOW  );
		DIO_vSetPinValue  ( LCD_CONTROL_PORT , LCD_RW , DIO_PIN_LOW  );
		DIO_voidWriteHighNibbles (LCD_DATA_PORT ,Copy_u8Command>>4);             // send the most 4 bits of data to high nibbles
		LCD_vSendFEdge();
		DIO_voidWriteHighNibbles (LCD_DATA_PORT ,Copy_u8Command);                // send the least 4 bits of data to high nibbles
		LCD_vSendFEdge();

#endif

		_delay_ms(1);

	}

	void LCD_vSendNumber   ( u64 Copy_u64Number    ){

		u64 LOC_u64Reversed = 1 ;

		if( Copy_u64Number == 0 ){ LCD_vSendData('0'); }

		else{

			while( Copy_u64Number != 0 ){

				LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Copy_u64Number % 10 );
				Copy_u64Number /= 10 ;

			}
			while( LOC_u64Reversed != 1 ){

				LCD_vSendData( ( LOC_u64Reversed % 10 ) + 48 );
				LOC_u64Reversed /= 10 ;

			}

		}

	}

	void LCD_vSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col ){

		u8 LOC_u8data ;

		/* In These cases will set at (0,0) ==> if the user enter invalid location */
		if(Copy_u8Row>4||Copy_u8Row<1||Copy_u8Col>20||Copy_u8Col<1)  //check
		{
			LOC_u8data = lcd_Row1 ;   // first location
		}

		else if( Copy_u8Row == LCD_ROW_1 ){

			LOC_u8data = ( ( lcd_Row1 ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

		}

		else if( Copy_u8Row == LCD_ROW_2 ){

			LOC_u8data = ( ( lcd_Row2 )  + ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

		}
		else if( Copy_u8Row == LCD_ROW_3 ){

			LOC_u8data = ( ( lcd_Row3 ) + ( Copy_u8Col - 1 ) );       //Row3 -> 0x90+col-1

		}
		else if( Copy_u8Row == LCD_ROW_4 ){

			LOC_u8data = ( ( lcd_Row4 ) + ( Copy_u8Col - 1 ) );       //Row4 -> 0xd0+col-1

		}

		LCD_vSendCommand ( LOC_u8data );
		_delay_ms(1);

	}

	void LCD_vSendExtraChar( u8 Copy_u8Row , u8 Copy_u8Col ){

		u8 LOC_u8Iterator = 0 ;
		/* 1- Go To CGRAM            */
		LCD_vSendCommand( lcd_CGRAM );  // Make AC refers to the first Place/Address at CGRAM


		/* 2- Draw Character in CGRAM        */
		/* Hint : it will be copied to DDRAM automatically */
		for( LOC_u8Iterator = 0 ; LOC_u8Iterator < sizeof(LCD_u8ExtraChar) / sizeof(LCD_u8ExtraChar[0]) ; LOC_u8Iterator++){

			LCD_vSendData( LCD_u8ExtraChar[LOC_u8Iterator] );

		}


		/* 3- Back (AC) To DDRAM          */
		LCD_vSetPosition(Copy_u8Row,Copy_u8Col);


		/* 4- Send Character Address */
		for( LOC_u8Iterator = 0 ; LOC_u8Iterator < 8 ; LOC_u8Iterator++ ){

			LCD_vSendData( LOC_u8Iterator );

		}

	}

	void LCD_vClearScreen(void)
	{
		LCD_vSendCommand(lcd_Clear);
		_delay_ms(10); //wait more than 1.53 ms
	}

	void LCD_vSendFEdge(void) {
	    DIO_vSetPinValue(LCD_CONTROL_PORT, LCD_EN, DIO_PIN_HIGH);
	    _delay_ms(1);
	    DIO_vSetPinValue(LCD_CONTROL_PORT, LCD_EN, DIO_PIN_LOW);
	    _delay_ms(1);
	}



