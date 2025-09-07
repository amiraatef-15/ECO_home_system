/*
 * main.c
 *
 *  Created on: ٠١‏/٠٤‏/٢٠٢٥
 *      Author: hp
 */

#include "util/delay.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "USART_interface.h"
#include "EEROM_interface.h"
#include "KPD_interface.h"
#include "LCD_interface.h"
#include "TIMER_interface.h"
#include "secyrtiy.h"

// Global Variables
u8 BT = 0;                // Bluetooth mode flag
u8 KPD = 1;               // Keypad mode flag
u8 code = 1;              // Current input mode (BT or KPD)
extern u8 pass[4];        // Password array (defined elsewhere)
extern u8 x;              // Attempts or state variable (defined elsewhere)
extern u8 flag1;          // Success flag (defined elsewhere)
u8 typuser;               // User type (not used in this code)
u8 corsal = NOTPRESSED;   // Last pressed key/button
u8 LOC = 0;               // Location flag (not used in this code)
u8 LOC1 = 0;              // Password match flag
u8 check = NOTPRESSED;    // Password check result
u8 val = 0;               // Pin value (sensor input)
u8 state = 0;             // Current state (stores last command)

// LED and Buzzer configuration
LED_Type ledg = {LED_PORTD, LED_PIN2, ACTIVE_HIGH}; // Green LED
LED_Type BUZ  = {LED_PORTD, LED_PIN3, ACTIVE_HIGH}; // Buzzer

// Application Initialization
void APP() {
	LCD_vInit();
	KPD_Init();
	DIO_vSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
	DIO_vSetPinDirection(DIO_PORTD, DIO_PIN4, DIO_PIN_OUTPUT);
	TIMER1_vInit();
	DIO_vSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_INPUT);
	USART_vInit();
	LED_vInit(ledg);
	LED_vInit(BUZ);
}

void main() {
	APP();
	LCD_vSendString("HELLO");

	// Select input mode (Bluetooth or Keypad)
	if (code == BT) {
		do {
			USART_u8ReceiveData(&corsal);
		} while (corsal == NOTPRESSED);
		if (corsal == '=') {
			code = KPD;
		}
	} else if (code == KPD) {
		do {
			corsal = KPD_u8GetPressed();
		} while (corsal == NOTPRESSED);
		if (corsal == '=') {
			code = BT;
		}
	}

	LCD_vClearScreen();

	// Store default password in EEPROM
	EEROM_VoidSendDataToAddress(0x00, '1');
	EEROM_VoidSendDataToAddress(0x01, '2');
	EEROM_VoidSendDataToAddress(0x02, '3');
	EEROM_VoidSendDataToAddress(0x03, '4');
	corsal = NOTPRESSED;

	// Test password input
	TEST_PASS();
	do {
		// Check if entered password matches EEPROM
		for (u8 i = 0; i < 4; i++) {
			if (pass[i] == EEROM_VoidReadDataFromAddress(i)) {
				LOC1 = 1;
			}
		}
		if (LOC1 == 1) {
			check = 0; // Password correct
		} else {
			check = 1; // Password incorrect
		}
		if (x == 0) {
			break; // Exit if attempts exhausted
		}

		switch (check) {
		case 0:
			LCD_vSendString("Entered SUCCESSFULLY");
			flag1 = 1;
			_delay_ms(1000);
			LCD_vClearScreen();
			LCD_vSendString("Welcome");
			break;
		case 1:
			CHECK_PASS(); // Handle wrong password
			break;
		}
	} while (flag1 == 0);

	// If attempts exhausted, lock home
	if (x == 0) {
		LCD_vSendString("Home closed .");
		LED_vOn(BUZ);
	}

	// Set timer based on login result
	if (flag1 == 1) {
		TIMER1_vSetCTCB(1.5);
	} else {
		TIMER1_vSetCTCB(2);
	}

	// Read sensor value and control LED
	val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
	if (val == 1) {
		TIMER1_vSetCTCA(1.5);
		LED_vOn(ledg);
	} else {
		TIMER1_vSetCTCA(2);
		LED_vOff(ledg);
	}

	corsal = NOTPRESSED;

	// Wait for command from selected input mode
	if (code == BT) {
		do {
			USART_u8ReceiveData(&corsal);
			val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
			if (val == 1) {
				TIMER1_vSetCTCA(1.5);
				LED_vOn(ledg);
			} else {
				TIMER1_vSetCTCA(2);
				LED_vOff(ledg);
			}
		} while (corsal == NOTPRESSED);
		if (corsal == '=') {
			code = KPD;
			corsal = '1';
		}
	} else if (code == KPD) {
		do {
			corsal = KPD_u8GetPressed();
			val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
			if (val == 1) {
				TIMER1_vSetCTCA(1.5);
				LED_vOn(ledg);
			} else {
				TIMER1_vSetCTCA(2);
				LED_vOff(ledg);
			}
		} while (corsal == NOTPRESSED);
		if (corsal == '=') {
			code = BT;
			corsal = '1';
		}
	}

	// Main control loop
	while (1) {
		state = corsal; // Store last command
		switch (corsal) {
		case '1':
			// Case 1: Control CTCB timer
			do {
				if (state == '1') {
					TIMER1_vSetCTCB(1.5);
				} else if (state == '2') {
					TIMER1_vSetCTCB(2);
				} else if (state == '3') {
					TIMER1_vSetCTCA(1.5);
					LED_vOn(ledg);
				} else if (state == '4') {
					TIMER1_vSetCTCA(2);
					LED_vOff(ledg);
				}
				TIMER1_vSetCTCB(1.5);
				// Wait for next command
				if (code == BT) {
					do {
						USART_u8ReceiveData(&corsal);
						val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
						if (val == 1) {
							TIMER1_vSetCTCA(1.5);
							LED_vOn(ledg);
						} else {
							TIMER1_vSetCTCA(2);
							LED_vOff(ledg);
						}
					} while (corsal == '1');
					if (corsal == '=') {
						code = KPD;
					}
				} else if (code == KPD) {
					do {
						corsal = KPD_u8GetPressed();
						val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
						if (val == 1) {
							TIMER1_vSetCTCA(1.5);
							LED_vOn(ledg);
						} else {
							TIMER1_vSetCTCA(2);
							LED_vOff(ledg);
						}
					} while (corsal == NOTPRESSED);
					if (corsal == '=') {
						code = BT;
					}
				}
			} while (corsal == '1');
			break;
		case '2':
			// Case 2: Control CTCB timer (different value)
			do {
				if (state == '1') {
					TIMER1_vSetCTCB(1.5);
				} else if (state == '2') {
					TIMER1_vSetCTCB(2);
				} else if (state == '3') {
					TIMER1_vSetCTCA(1.5);
					LED_vOn(ledg);
				} else if (state == '4') {
					TIMER1_vSetCTCA(2);
					LED_vOff(ledg);
				}
				TIMER1_vSetCTCB(2);
				// Wait for next command
				if (code == BT) {
					do {
						USART_u8ReceiveData(&corsal);
						val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
						if (val == 1) {
							TIMER1_vSetCTCA(1.5);
							LED_vOn(ledg);
						} else {
							TIMER1_vSetCTCA(2);
							LED_vOff(ledg);
						}
					} while (corsal == '2');
					if (corsal == '=') {
						code = KPD;
					}
				} else if (code == KPD) {
					do {
						corsal = KPD_u8GetPressed();
						val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
						if (val == 1) {
							TIMER1_vSetCTCA(1.5);
							LED_vOn(ledg);
						} else {
							TIMER1_vSetCTCA(2);
							LED_vOff(ledg);
						}
					} while (corsal == NOTPRESSED);
					if (corsal == '=') {
						code = BT;
					}
				}
			} while (corsal == '2' || corsal == '=');
			break;
		case '3':
			// Case 3: Turn on LED and set timer
			do {
				if (state == '1') {
					TIMER1_vSetCTCB(1.5);
				} else if (state == '2') {
					TIMER1_vSetCTCB(2);
				} else if (state == '3') {
					TIMER1_vSetCTCA(1.5);
					LED_vOn(ledg);
				} else if (state == '4') {
					TIMER1_vSetCTCA(2);
					LED_vOff(ledg);
				}
				TIMER1_vSetCTCA(1.5);
				LED_vOn(ledg);
				// Wait for next command
				if (code == BT) {
					do {
						USART_u8ReceiveData(&corsal);
					} while (corsal == '3');
					if (corsal == '=') {
						code = KPD;
					}
				} else if (code == KPD) {
					do {
						corsal = KPD_u8GetPressed();
					} while (corsal == NOTPRESSED);
					if (corsal == '=') {
						code = BT;
					}
				}
			} while (corsal == '3' || corsal == '=');
			break;
		case '4':
			// Case 4: Turn off LED and set timer
			do {
				if (state == '1') {
					TIMER1_vSetCTCB(1.5);
				} else if (state == '2') {
					TIMER1_vSetCTCB(2);
				} else if (state == '3') {
					TIMER1_vSetCTCA(1.5);
					LED_vOn(ledg);
				} else if (state == '4') {
					TIMER1_vSetCTCA(2);
					LED_vOff(ledg);
				}
				TIMER1_vSetCTCA(2);
				LED_vOff(ledg);
				// Wait for next command
				if (code == BT) {
					do {
						USART_u8ReceiveData(&corsal);
					} while (corsal == '4');
					if (corsal == '=') {
						code = KPD;
					}
				} else if (code == KPD) {
					do {
						corsal = KPD_u8GetPressed();
					} while (corsal == NOTPRESSED);
					if (corsal == '=') {
						code = BT;
					}
				}
			} while (corsal == '4' || corsal == '=');
			break;
		default:
			// Default: Wait for valid command (3 or 4)
			if (code == BT) {
				do {
					USART_u8ReceiveData(&corsal);
					val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
					if (val == 1) {
						TIMER1_vSetCTCA(1.5);
						LED_vOn(ledg);
					} else {
						TIMER1_vSetCTCA(2);
						LED_vOff(ledg);
					}
				} while (corsal != '3' || corsal != '4');
				if (corsal == '=') {
					code = KPD;
				}
			} else if (code == KPD) {
				do {
					corsal = KPD_u8GetPressed();
					val = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
					if (val == 1) {
						TIMER1_vSetCTCA(1.5);
						LED_vOn(ledg);
					} else {
						TIMER1_vSetCTCA(2);
						LED_vOff(ledg);
					}
				} while (corsal != '3' || corsal != '4');
				if (corsal == '=') {
					code = BT;
				}
			}
			break;
		}
	}
}












