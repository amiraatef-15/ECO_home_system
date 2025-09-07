/*
 * DHT11_program.c
 *
 * Created on: Feb 2, 2025
 * Author:gamila elkomy
 */

#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"

#include "../MCAL/DIO_intervace.h"
#include "DHT11_interface.h"
#include "DHT11_private.h"
#include "DHT11_config.h"
#include <util/delay.h>

void DHT11_voidInit(void) {
    /* Set DHT11 pin as input with pull-up (initially) */
    DIO_enumSetPinDirection(DHT11_PORT, DHT11_PIN, DIO_PIN_INPUT);
    DIO_enumConnectPullUp(DHT11_PORT, DHT11_PIN, DIO_PIN_HIGH);
}

u8 DHT11_u8GetData(DHT11_Data *Copy_pu8Data) {
    u8 Local_u8Response = 0;
    u8 Local_u8Data[5] = {0};
    u8 Local_u8Checksum = 0;
    u8 Local_u8Counter;

    /* Send start signal */
    DHT11_voidSendStartSignal();

    /* Check response */
    Local_u8Response = DHT11_u8CheckResponse();
    if (!Local_u8Response) {
        return 0; // No response from sensor
    }

    /* Read 5 bytes (40 bits) of data */
    for (Local_u8Counter = 0; Local_u8Counter < 5; Local_u8Counter++) {
        Local_u8Data[Local_u8Counter] = DHT11_u8ReadByte();
    }

    /* Verify checksum */
    Local_u8Checksum = Local_u8Data[0] + Local_u8Data[1] + Local_u8Data[2] + Local_u8Data[3];
    if (Local_u8Checksum != Local_u8Data[4]) {
        return 0; // Checksum error
    }

    /* Store data */
    Copy_pu8Data->Humidity = Local_u8Data[0];
    Copy_pu8Data->Temperature = Local_u8Data[2];

    return 1; // Success
}

static void DHT11_voidSendStartSignal(void) {
    /* Set pin as output */
   DIO_enumSetPinDirection(DHT11_PORT, DHT11_PIN, DIO_PIN_OUTPUT);

    /* Pull low for 18ms */
    DIO_enumWritePinValue(DHT11_PORT, DHT11_PIN, DIO_PIN_LOW);
    _delay_us(DHT11_START_SIGNAL_DURATION);

    /* Pull high for 20-40us */
    DIO_enumWritePinValue(DHT11_PORT, DHT11_PIN, DIO_PIN_HIGH);
    _delay_us(DHT11_RESPONSE_SIGNAL_DURATION);

    /* Set pin as input with pull-up */
    DIO_enumSetPinDirection(DHT11_PORT, DHT11_PIN, DIO_PIN_INPUT);
    DIO_enumConnectPullUp(DHT11_PORT, DHT11_PIN, DIO_PIN_HIGH);
}

static u8 DHT11_u8CheckResponse(void) {
    u32 Local_u32TimeOut = 0;
	u32 Local_u8Response;

    /* Wait for DHT11 to pull low (80us) */
    while (DIO_enumReadPinValue(DHT11_PORT, DHT11_PIN, &Local_u8Response) == DIO_PIN_HIGH) {
        Local_u32TimeOut++;
        if (Local_u32TimeOut > DHT11_TIMEOUT) {
            return 0; // Timeout
        }
        _delay_us(1);
    }

    Local_u32TimeOut = 0;


    /* Wait for DHT11 to pull high (80us) */
    while (DIO_enumReadPinValue(DHT11_PORT, DHT11_PIN, &Local_u8Response) == DIO_PIN_LOW) {
        Local_u32TimeOut++;
        if (Local_u32TimeOut > DHT11_TIMEOUT) {
            return 0; // Timeout
        }
        _delay_us(1);
    }

    return 1; // Response received
}

static u8 DHT11_u8ReadByte(void) {
    u8 Local_u8Byte = 0;
    u8 Local_u8Bit;
    u32 Local_u32TimeOut;
	u32 Local_u8Response;

    for (Local_u8Bit = 0; Local_u8Bit < 8; Local_u8Bit++) {
        Local_u32TimeOut = 0;

        /* Wait for start of bit (50us low) */
        while (DIO_enumReadPinValue(DHT11_PORT, DHT11_PIN, &Local_u8Response) == DIO_PIN_LOW) {
            Local_u32TimeOut++;
            if (Local_u32TimeOut > DHT11_TIMEOUT) {
                return 0; // Timeout
            }
            _delay_us(1);
        }

        _delay_us(30); // Wait 30us to determine bit value

        /* Read bit value */
        DIO_enumReadPinValue(DHT11_PORT, DHT11_PIN, &Local_u8Response);
        if (Local_u8Response == DIO_PIN_HIGH) {
            Local_u8Byte |= (1 << (7 - Local_u8Bit));
        }

        /* Wait for bit to finish */
        while (DIO_enumReadPinValue(DHT11_PORT, DHT11_PIN, &Local_u8Response) == DIO_PIN_HIGH) {
            Local_u32TimeOut++;
            if (Local_u32TimeOut > DHT11_TIMEOUT) {
                return 0; // Timeout
            }
            _delay_us(1);
        }
    }

    return Local_u8Byte;
}
