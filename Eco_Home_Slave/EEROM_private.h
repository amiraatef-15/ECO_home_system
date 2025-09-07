/*
-------------------------------------------------------------------------------------------------------------------------------------------------------------

    name:EEROM_private
	
	layer:MCAL

	by:Youssef Elswase


-------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef _EEROM_PRIVATE_H_
#define _EEROM_PRIVATE_H_
/* EEROM Address */ 

#define EEAR  *((volatile u16 *)0x3F)
#define EEARH *((volatile u8 *)0x3F) 
#define EEARL *((volatile u8 *)0x3E) 

/* EEROM Data */

#define EEDR  *((volatile u8 *)0x3D) 

/* EEROM Control */

#define EECR  *((volatile u8 *)0x3C) 
 
#define EERE  0
#define EEWE  1
#define EEMWE 2
#define EERIE 3




#endif