#define F_CPU 8000000UL // Define CPU frequency for delay functions

#include <util/delay.h> // Delay functions for timing
#include <avr/interrupt.h> // AVR interrupt handling
#include "STD_TYPES.h" // Standard type definitions (u8, u16, etc.)
#include "BIT_MATH.h" // Bit manipulation macros
#include "DIO_interface.h" // Digital I/O interface
#include "ADC_interface.h" // ADC (Analog to Digital Converter) interface
#include "LCD_interface.h" // LCD display interface
#include "LM35_interface.h" // LM35 temperature sensor interface
#include "LDR_interface.h" // LDR (Light Dependent Resistor) interface
#include "MQ5_interface.h" // MQ5 gas sensor interface
#include "TIMER_interface.h" // Timer interface
#include "USART_interface.h" // USART (serial communication) interface

// UART Command Definitions for controlling devices via serial
#define Out_Light_on    'a'
#define Out_Light_off   'b'
#define IN_Light_on     'C'
#define IN_Light_off    'd'
#define CMD_Fire        'e'
#define CMD_Gas         'f'
#define CMD_COOLING_on  'g'
#define CMD_COOLING_off 'h'

// Time and threshold definitions for automation logic
volatile u8 seconds_counter = 0;
volatile u8 minutes_counter = 45;
volatile u8 hours_counter = 9;
volatile u8 day = 3;
volatile u8 month = 3;

#define TEMP_NORMAL_THRESHOLD    25 // Normal temperature threshold (°C)
#define TEMP_CRITICAL_THRESHOLD  50 // Critical temperature threshold (°C)
#define LIGHT_THRESHOLD         50  // Light level threshold (%)
#define NIGHT_START_HOUR        18  // Night time start (6 PM)
#define NIGHT_END_HOUR          6   // Night time end (6 AM)

u8 gas, purity, temp, LightLevel; // Sensor readings
u8 out_flag =1; // Flag to control outdoor light automation
volatile u8 CMD = 0xff; // Last received UART command
s32 TIME_OUT =10000; // Timeout value (not used in this snippet)

/*----------------- Function Prototypes -----------------*/
// Functions for handling different system events
void vLeaked_Gas_Sys(void);
void vFire_Sys(void);
void vCooling_Sys_On(void);
void vCooling_Sys_Off(void);
void vIn_door_on(void);
void vIn_door_off(void);
void vOut_door_on(void);
void vOut_door_off(void);

/*----------------- Timer2 Overflow ISR -----------------*/
// This ISR is called every timer overflow (e.g., every second)
// It increments the time counters (seconds, minutes, hours, day, month)
void ISR_Timer2_OVF(void) {
    seconds_counter++;
    if(seconds_counter == 60) {
        seconds_counter = 0;
        minutes_counter++;
        if(minutes_counter == 60) {
            minutes_counter = 0;
            hours_counter++;
            if(hours_counter == 24) {
                hours_counter = 0;
                day++;
                if(day == 32) {
                    day = 1;
                    month++;
                    if(month == 13) {
                        month = 1;
                    }
                }
            }
        }
    }
}

// USART Receive Complete Interrupt Service Routine
// Called when a byte is received via UART
ISR (USART_RXC_vect){
    USART_u8ReceiveData(&CMD); // Read received command

    switch (CMD)
    {
       case Out_Light_on:     vOut_door_on();  out_flag=0;  break; // Manual ON, disable auto
       case Out_Light_off:    vOut_door_off(); out_flag=0;  break; // Manual OFF, disable auto
       case IN_Light_on:      vIn_door_on();                break; // Manual indoor ON
       case IN_Light_off:     vIn_door_off();               break; // Manual indoor OFF
       case CMD_Fire:         vFire_Sys();                  break; // Fire emergency
       case CMD_Gas:          vLeaked_Gas_Sys();            break; // Gas leak emergency
       case CMD_COOLING_on:   vCooling_Sys_On();            break; // Manual cooling ON
       case CMD_COOLING_off:  vCooling_Sys_Off();           break; // Manual cooling OFF
       default:               out_flag=1;                   break; // Unknown command, enable auto
    }
}

/*----------------- Main Function -----------------*/
void main(void) {
    // Initialize all peripherals
    ADC_vInit();
    LCD_vInit();
    MQ5_vInit(ADC_CHANNEL2);
    USART_vInit();

    TIMER2_vInit();
    TIMER_u8SetCallBack(ISR_Timer2_OVF, TIMER2_OVF_VECTOR_ID); // Set timer ISR
    sei(); // Enable global interrupts

    // Set pin directions for actuators
    DIO_vSetPinDirection(DIO_PORTC, DIO_PIN2, DIO_PIN_OUTPUT);  // Water pump
    DIO_vSetPinDirection(DIO_PORTC, DIO_PIN3, DIO_PIN_OUTPUT);  // Indoor fan
    DIO_vSetPinDirection(DIO_PORTC, DIO_PIN4, DIO_PIN_OUTPUT);  // Exhaust fan
    DIO_vSetPinDirection(DIO_PORTC, DIO_PIN5, DIO_PIN_OUTPUT);  // Main power
    DIO_vSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_PIN_OUTPUT);  // Outdoor lights
    DIO_vSetPinDirection(DIO_PORTD, DIO_PIN3, DIO_PIN_OUTPUT);  // Gas valve
    DIO_vSetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_OUTPUT);  // Bump valve

    // Sensor configuration structures
    LM35_CONFIG Temp_sensor = {
        .Copy_u8LM35Channel = ADC_CHANNEL0,
        .Copy_u8ADCVoltageReference = 5,
        .Copy_u8ADCResolution = ADC_RESOLUTION_10_BIT
    };
    LDR_Config Light_sensor = {
        .LDR_Channel = ADC_CHANNEL1,
        .LDR_VoltageRef = 5,
        .LDR_Resolution = ADC_RESOLUTION_10_BIT
    };

    DIO_vSetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_HIGH); // Main power ON

    while(1) {
        /* 1. Sensor Reading */
        LM35_u8GetTemp(&Temp_sensor, &temp); // Read temperature
        LDR_u8GetLightLevel(&Light_sensor, &LightLevel); // Read light level
        MQ5_u8GetGasPercentage(&gas); // Read gas level
        MQ5_u8GetAirPurity(&purity); // Read air purity

        /* 2. Automatic Control Logic (if no UART command is received, system works automatically) */
        // Cooling system automatic control
        if (temp <= TEMP_NORMAL_THRESHOLD) {
            vCooling_Sys_Off();
        } else if(temp > TEMP_NORMAL_THRESHOLD && temp < TEMP_CRITICAL_THRESHOLD) {
            vCooling_Sys_On();
        } else {
            vFire_Sys(); // Critical temperature triggers fire system
        }

        // Outdoor light automatic control (only if not overridden by UART)
        if (out_flag==1){
            if (LightLevel < LIGHT_THRESHOLD ||
                (hours_counter >= NIGHT_START_HOUR || hours_counter < NIGHT_END_HOUR)) {
                vOut_door_on();
            } else {
                vOut_door_off();
            }
        } else {
            // Manual override, do nothing
        }

        // Gas and air purity based control (always active)
        if((purity < 100 && purity > 75) || (gas < 50 && gas > 25)) {
            vCooling_Sys_On();
        }
        else if(gas > 50) {
            vLeaked_Gas_Sys();
        }

        /* 3. Display Updates */
        // Display time (HH:MM:SS)
        LCD_vSetPosition(LCD_ROW_1, LCD_COL_1);
        if(hours_counter < 10) LCD_vSendString("0");
        LCD_vSendNumber(hours_counter);
        LCD_vSendString(":");
        if(minutes_counter < 10) LCD_vSendString("0");
        LCD_vSendNumber(minutes_counter);
        LCD_vSendString(":");
        if(seconds_counter < 10) LCD_vSendString("0");
        LCD_vSendNumber(seconds_counter);

        // Display date (DD/MM)
        LCD_vSetPosition(LCD_ROW_1, LCD_COL_11);
        if(day < 10) LCD_vSendString("0");
        LCD_vSendNumber(day);
        LCD_vSendString("/");
        if(month < 10) LCD_vSendString("0");
        LCD_vSendNumber(month);

        // Display temperature
        LCD_vSetPosition(LCD_ROW_2, LCD_COL_1);
        LCD_vSendNumber(temp);
        LCD_vSendString("C");

        // Display light level
        LCD_vSetPosition(LCD_ROW_2, LCD_COL_6);
        LCD_vSendString("L");
        LCD_vSendNumber(LightLevel);
        LCD_vSendString("%");

        // Display air purity
        LCD_vSetPosition(LCD_ROW_2, LCD_COL_12);
        LCD_vSendString("G");
        LCD_vSendNumber(purity);
        LCD_vSendString("%");

        _delay_ms(100); // Main loop delay
    }
}

/*----------------- Emergency and Control System Functions -----------------*/
// Gas leak emergency: close gas valve, start ventilation and exhaust, cut main power, turn off outdoor lights
void vLeaked_Gas_Sys(void) {
    DIO_vSetPinValue(DIO_PORTD, DIO_PIN3, DIO_PIN_HIGH);  // Close gas valve
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN3, DIO_PIN_HIGH);  // Start ventilation
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_HIGH);  // Start exhaust
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_LOW);   // Cut main power
    DIO_vSetPinValue(DIO_PORTD, DIO_PIN2, DIO_PIN_LOW);   // Turn off outdoor lights
}

// Fire emergency: do gas leak actions and start water pump
void vFire_Sys(void) {
    vLeaked_Gas_Sys();
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN2, DIO_PIN_HIGH);  // Start water pump
}

// Turn ON cooling system (indoor fan and exhaust)
void vCooling_Sys_On(void) {
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN3, DIO_PIN_HIGH);  // Start indoor fan
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_HIGH);  // Start exhaust fan
}

// Turn OFF cooling system
void vCooling_Sys_Off(void) {
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN3, DIO_PIN_LOW);   // Stop indoor fan
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);   // Stop exhaust fan
}

// Turn ON indoor light
void vIn_door_on(void) {
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_HIGH);  // Turn on indoor light
}

// Turn OFF indoor light
void vIn_door_off(void) {
    DIO_vSetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_LOW);   // Turn off indoor light
}

// Turn ON outdoor light
void vOut_door_on(void) {
    DIO_vSetPinValue(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);  // Turn on outdoor light
}

// Turn OFF outdoor light
void vOut_door_off(void) {
    DIO_vSetPinValue(DIO_PORTD, DIO_PIN2, DIO_PIN_LOW);   // Turn off outdoor light
}
