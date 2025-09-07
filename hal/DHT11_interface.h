/*
 * DHT11_interface.h
 *
 * Created: 03/04/2025 22:36:39
 *  Author: GOHARY 10
 */


#ifndef DHT11_INTERFACE_H_
#define DHT11_INTERFACE_H_

#include "../lib/std_typs.h"

typedef struct {
	u8 Temperature;
	u8 Humidity;
} DHT11_Data;

/* Function Prototypes */
void DHT11_voidInit(void);
u8 DHT11_u8GetData(DHT11_Data *Copy_pu8Data);

#endif
