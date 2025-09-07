/*
 * DHT11_private.h
 *
 * Created: 03/04/2025 22:37:36
 *  Author: GOHARY 10
 */



#ifndef DHT11_PRIVATE_H_
#define DHT11_PRIVATE_H_

/* Private Macros */
#define DHT11_START_SIGNAL_DURATION 18000  // 18ms
#define DHT11_RESPONSE_SIGNAL_DURATION 20  // 20us
#define DHT11_DATA_BIT_START_DURATION 50   // 50us

/* Private Functions */
static void DHT11_voidSendStartSignal(void);
static u8 DHT11_u8CheckResponse(void);
static u8 DHT11_u8ReadByte(void);

#endif
