/*******************************************************************************
 * File: control.c
 *
 * Description:
 * This file implements the control functions for the smart home system including:
 * - Main control menu
 * - Garage door control
 * - Main door control
 * - Input handling from both Keypad and UART
 *
 * Author: [Your Name]
 * Version: 1.0
 ******************************************************************************/

/* Include necessary headers */
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
#include "control.h"

/* External variables */
extern u8 corsal;        // Input state variable
extern LED_Type ledg;    // Status LED configuration

/*******************************************************************************
 *                      Functions Definitions                                    *
 *******************************************************************************/

/*
 * Function: get_input
 * -----------------------------
 * Monitors and returns input from both Keypad and UART
 *
 * Returns:
 *   u8: The received input character
 *       NOTPRESSED if no input is available
 */
u8 get_input(void) {
    u8 input = NOTPRESSED;
    u8 uart_data;

    while(input == NOTPRESSED) {
        // Check keypad input first
        input = KPD_u8GetPressed();
        if(input != NOTPRESSED) {
            return input;
        }

        // Then check UART input
        if(USART_u8ReceiveData(&uart_data) == OK) {
            return uart_data;
        }

        _delay_ms(50);  // Small delay to prevent CPU hogging
    }
    return input;
}

/*
 * Function: control
 * -----------------------------
 * Main control menu function
 * Displays and handles the main control interface
 */
void control(void) {
    while(1) {
        // Display control menu
        LCD_vClearScreen();
        LCD_vSetPosition(LCD_ROW_1, LCD_COL_6);
        LCD_vSendString("Control Menu");
        LCD_vSetPosition(LCD_ROW_2, LCD_COL_1);
        LCD_vSendString("1:Park  2:Door  0:Exit");

        // Wait for user input
        corsal = get_input();

        // Process user selection
        switch(corsal) {
            case '1':  // Garage control
                park();
                break;
            case '2':  // Door control
                door();
                break;
            case '0':  // Exit to main menu
                return;
        }
        corsal = NOTPRESSED;  // Reset input state
    }
}

/*
 * Function: park
 * -----------------------------
 * Garage door control function
 * Controls the garage door motor and status LED
 */
void park(void) {
    LCD_vClearScreen();
    LCD_vSetPosition(LCD_ROW_1, LCD_COL_6);
    LCD_vSendString("Garage Control");
    LCD_vSetPosition(LCD_ROW_2, LCD_COL_1);
    LCD_vSendString("1:Open 2:Close 0:Back");

    while(1) {
        corsal = get_input();

        switch(corsal) {
            case '1':  // Open garage
                TIMER1_vSetCTCA(1.5);  // Set servo to open position
                LED_vOn(ledg);         // Turn on status LED
                break;

            case '2':  // Close garage
                TIMER1_vSetCTCA(2);    // Set servo to closed position
                LED_vOff(ledg);        // Turn off status LED
                break;

            case '0':  // Return to main menu
                return;
        }
    }
}

/*
 * Function: door
 * -----------------------------
 * Main door control function
 * Controls the main door motor
 */
void door(void) {
    LCD_vClearScreen();
    LCD_vSetPosition(LCD_ROW_1, LCD_COL_6);
    LCD_vSendString("Door Control");
    LCD_vSetPosition(LCD_ROW_2, LCD_COL_1);
    LCD_vSendString("1:Open 2:Close 0:Back");

    while(1) {
        corsal = get_input();

        switch(corsal) {
            case '1':  // Open door
                TIMER1_vSetCTCB(1.5);  // Set servo to open position
                break;

            case '2':  // Close door
                TIMER1_vSetCTCB(2);    // Set servo to closed position
                break;

            case '0':  // Return to main menu
                return;
        }
    }
}
