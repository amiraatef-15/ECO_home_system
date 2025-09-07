/*
-------------------------------------------------------------------------------------------------------------------------------------------------------------

    name:EEROM_project

	layer:MCAL

	by:Youssef Elswase


-------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define F_CPU 8000000ul
#include "util/delay.h"

#include "STD_Types.h"
#include "BIT_MATH.h"


#include "EEROM_interface.h"
#include "EEROM_config.h"
#include "EEROM_private.h"

void EEROM_VoidSendDataToAddress ( u16 COPY_AddressReg , u8 COPY_Data )
{
	//EEAR = COPY_AddressReg;


		EEARL=(u8)COPY_AddressReg;
		EEARH=(u8)(COPY_AddressReg>>8);


	EEDR = COPY_Data;
	
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);

	while(GET_BIT(EECR,EEWE)==1);
}

u8 EEROM_VoidReadDataFromAddress ( const u16 COPY_AddressReg )
{
	/*EEAR = COPY_AddressReg;*/

		EEARL=(u8)COPY_AddressReg;
		EEARH=(u8)(COPY_AddressReg>>8);

	SET_BIT(EECR,EERE);

	return EEDR;
}



