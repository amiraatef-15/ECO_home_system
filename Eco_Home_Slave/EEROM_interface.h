/*
-------------------------------------------------------------------------------------------------------------------------------------------------------------

    name:EEROM_interface
	
	layer:MCAL

	by:Youssef Elswase


-------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef _EEROM_INTERFACE_H_
#define _EEROM_INTERFACE_H_

void EEROM_VoidSendDataToAddress ( u16 COPY_AddressReg , u8 COPY_Data );

u8 EEROM_VoidReadDataFromAddress ( u16 COPY_AddressReg );




#endif