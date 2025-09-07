/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LED_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  By : Abdallah Saleh
 *  Layer  : HAL (Hardware Abstraction Layer)
 *  SWC    : LED (Software Component for LED control)
 *
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/* Macros for LED ports */
#define LED_PORTA  0
#define LED_PORTB  1
#define LED_PORTC  2
#define LED_PORTD  3

/* Macros for LED pins */
#define LED_PIN0   0
#define LED_PIN1   1
#define LED_PIN2   2
#define LED_PIN3   3
#define LED_PIN4   4
#define LED_PIN5   5
#define LED_PIN6   6
#define LED_PIN7   7

/* Macros for LED active states */
#define ACTIVE_HIGH    1  /* LED is on when the pin is HIGH */
#define ACTIVE_LOW     0  /* LED is on when the pin is LOW */

/* LED_Type structure:
 * Represents the configuration of an LED, including:
 * - Port: The port where the LED is connected (e.g., LED_PORTA).
 * - Pin: The specific pin on the port (e.g., LED_PIN0).
 * - Active_State: Determines if the LED is active HIGH or LOW.
 */
typedef struct {
    u8 Port;           /* Port of the LED */
    u8 Pin;            /* Pin number of the LED */
    u8 Active_State;   /* Active state of the LED (ACTIVE_HIGH or ACTIVE_LOW) */
} LED_Type;

/* 
 * Function: LED_vInit
 * --------------------
 * Initializes the LED by setting the specified pin as output.
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the port, pin, and active state of the LED.
 */
void LED_vInit( LED_Type LED_Configuration );

/* 
 * Function: LED_vOn
 * ------------------
 * Turns the LED on based on its active state.
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the port, pin, and active state of the LED.
 */
void LED_vOn( LED_Type LED_Configuration );

/* 
 * Function: LED_vOff
 * -------------------
 * Turns the LED off based on its active state.
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the port, pin, and active state of the LED.
 */
void LED_vOff( LED_Type LED_Configuration );

/* 
 * Function: LED_vTog
 * -------------------
 * Toggles the LED state (on/off).
 * 
 * Parameters:
 *   - LED_Configuration: A structure containing the port and pin of the LED.
 */
void LED_vTog( LED_Type LED_Configuration );

#endif
