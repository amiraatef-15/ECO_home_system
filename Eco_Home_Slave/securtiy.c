/*
 * securtiy.c
 *
 *  Created on: ٠٨‏/٠٣‏/٢٠٢٥
 *      Author: hp
 */
#include <util/delay.h>
//                                                master
#define F_CPU 8000000UL

/* Include necessary libraries */
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* Include MCU peripheral drivers */
#include "DIO_interface.h"

/* Include HAL drivers */
#include "LCD_interface.h"
#include "KPD_interface.h"
#include"EEROM_interface.h"
#include "USART_interface.h"
#include "LED_interface.h"
#include "secyrtiy.h"
extern u8 BT ;
extern u8 KPD ;
extern u8 code ;
#define TRY 3
extern u8 corsal;

u8 user[16]={0};
u8 pass[4]={0};
u8 x=TRY;
u8 flag =0;
u8 flag1 =0;


void ENTER_USER ()
{
	LCD_vSendString("HELLO");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	LCD_vSendString("Set Setup");
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("creat Name");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 i=0; i<16 ; i++)
	{
		if (code == BT)
				{
					do{
						USART_u8ReceiveData(&corsal);
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = KPD;
					}
				}

				else if (code == KPD)
				{
					do{
						corsal = KPD_u8GetPressed();
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = BT;
					}
				}
		if(corsal == '=')
		{
			for(u8 j=i;j<16;j++)
			{
				EEROM_VoidSendDataToAddress(j,NOTPRESSED);
				user[j]=NOTPRESSED;
			}
			break;
		}
		else if (corsal== ' ')
		{
			LCD_vSendData(' ');
			user[i]=' ';
			EEROM_VoidSendDataToAddress(i,' ');

		}
		else
		{
			LCD_vSendData(corsal);
			user[i]=corsal;
			EEROM_VoidSendDataToAddress(i,corsal);
		}
		corsal = 0xff;
	}
	LCD_vClearScreen();
	corsal = 0xff;

}

void ENTER_PASS ()
{
	LCD_vSendString("creat password");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 i=16 ,j=0; i<20,j<4 ; i++,j++)
	{
		if (code == BT)
		{
			do{
				USART_u8ReceiveData(&corsal);
			}while(corsal == NOTPRESSED);
			if(corsal=='=')
			{
				code = KPD;
			}
		}

		else if (code == KPD)
		{
			do{
				corsal = KPD_u8GetPressed();
			}while(corsal == NOTPRESSED);
			if(corsal=='=')
			{
				code = BT;
			}
		}
		LCD_vSendData(corsal);
		_delay_ms(250);
		LCD_vSetPosition(LCD_ROW_2,j+1);
		LCD_vSendData('*');
		EEROM_VoidSendDataToAddress(i,corsal);
		pass[j]=corsal;
		corsal = 0xff;
	}
	LCD_vClearScreen();
	corsal = 0xff;

}
void TEST_USER ()
{
	LCD_vSendString("Enter name");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 i=0; i<16 ; i++)
	{
		if (code == BT)
				{
					do{
						USART_u8ReceiveData(&corsal);
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = KPD;
					}
				}

				else if (code == KPD)
				{
					do{
						corsal = KPD_u8GetPressed();
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = BT;
					}
				}
		if(corsal == '=')
		{
			for(u8 j=i;j<16;j++)
			{
				user[j]=NOTPRESSED;
			}
			break;
		}
		else if (corsal== '?')
		{
			LCD_vSendData(' ');
			user[i]=' ';
		}
		else
		{
			LCD_vSendData(corsal);
			user[i]=corsal;
		}
		corsal = 0xff;

	}
	_delay_ms(1000);
	LCD_vClearScreen();
	corsal = 0xff;

}
void TEST_PASS ()
{

	LCD_vSendString("Enter password");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 j=0; j<4 ; j++)
	{
		if (code == BT)
				{
					do{
						USART_u8ReceiveData(&corsal);
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = KPD;
					}
				}

				else if (code == KPD)
				{
					do{
						corsal = KPD_u8GetPressed();
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = BT;
					}
				}
		LCD_vSendData(corsal);
		_delay_ms(250);
		LCD_vSetPosition(LCD_ROW_2,j+1);
		LCD_vSendData('*');
		pass[j]=corsal;
		corsal = 0xff;

	}
	LCD_vClearScreen();
	corsal = 0xff;

}
void CHECK_USER ()
{
	LCD_vSendString("name ERROR!");
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("try:");
	LCD_vSendData(x+'0');
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("try name");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 i=0; i<16 ; i++)
	{
		if (code == BT)
				{
					do{
						USART_u8ReceiveData(&corsal);
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = KPD;
					}
				}

				else if (code == KPD)
				{
					do{
						corsal = KPD_u8GetPressed();
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = BT;
					}
				}
		if(corsal == '=')
		{
			for(u8 j=i;j<16;j++)
			{
				user[j]=NOTPRESSED;
			}
			break;
		}
		else if (corsal== '?')
		{
			LCD_vSendData(' ');
			user[i] = ' ';
		}
		else
		{
			LCD_vSendData(corsal);
			user[i] = corsal;
		}
		corsal = 0xff;

	}
	x--;
	LCD_vClearScreen();
	corsal = 0xff;

}
void CHECK_PASS ()
{
	LCD_vSendString("password ERROR!");
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("try:");
	LCD_vSendData(x+'0');
	_delay_ms(500);
	LCD_vClearScreen();
	LCD_vSendString("try password");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 i=0 ; i<4 ; i++)
	{
		if (code == BT)
				{
					do{
						USART_u8ReceiveData(&corsal);
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = KPD;
					}
				}

				else if (code == KPD)
				{
					do{
						corsal = KPD_u8GetPressed();
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = BT;
					}
				}
		LCD_vSendData(corsal);
		_delay_ms(250);
		LCD_vSetPosition(LCD_ROW_2,i+1);
		LCD_vSendData('*');
		pass[i] = corsal;
		corsal = 0xff;

	}
	x--;
	LCD_vClearScreen();
	corsal = 0xff;

}

void CHECK_USER_PASS ()
{
	LCD_vSendString("ERROR!");
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("username ERROR!");
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("try:");
	LCD_vSendData(x+'0');
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("try username");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 i=0; i<16 ; i++)
	{
		if (code == BT)
				{
					do{
						USART_u8ReceiveData(&corsal);
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = KPD;
					}
				}

				else if (code == KPD)
				{
					do{
						corsal = KPD_u8GetPressed();
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = BT;
					}
				}
		if(corsal == '=')
		{
			break;
		}
		else if (corsal== '?')
		{
			LCD_vSendData(' ');
			user[i] = ' ';
		}
		else
		{
			LCD_vSendData(corsal);
			user[i] = corsal;
		}
		corsal = 0xff;

	}
	LCD_vClearScreen();
	LCD_vSendString("password ERROR!");
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("try:");
	LCD_vSendData(x+'0');
	_delay_ms(1000);
	LCD_vClearScreen();
	LCD_vSendString("try password");
	LCD_vSetPosition(LCD_ROW_2,LCD_COL_1);
	for (u8 i=16 ,j=0; i<20,j<4 ; i++,j++)
	{
		if (code == BT)
				{
					do{
						USART_u8ReceiveData(&corsal);
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = KPD;
					}
				}

				else if (code == KPD)
				{
					do{
						corsal = KPD_u8GetPressed();
					}while(corsal == NOTPRESSED);
					if(corsal=='=')
					{
						code = BT;
					}
				}
		LCD_vSendData(corsal);
		_delay_ms(250);
		LCD_vSetPosition(LCD_ROW_2,j+1);
		LCD_vSendData('*');
		pass[j] = corsal;
		corsal = 0xff;

	}
	x--;
	LCD_vClearScreen();
	corsal = 0xff;

}
