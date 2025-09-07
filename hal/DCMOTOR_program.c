/*
 * DCMOTOR_program.c
 *
 *  Created on: Feb 19, 2025
 *      Author: alaa hassan
 */



#include "../MCAL/DIO_intervace.h"
#include "../lib/BIT_MATH.h"
#include "../lib/std_typs.h"

// #include "PORT_INTERFACE.h"

#include "DCMOTOR_INTERFACE.h"

u8 DCMOTOR_uint8Control(DCMOTOR_CONFIG *DcMotor, u8 Copy_uint8State)
{
	u8 Local_uint8ErrorState = OK;

	switch (Copy_uint8State)
	{
	case DCMOTOR_CW:
		DIO_enumWritePinValue(DcMotor->Copy_uint8DcMotorPort, DcMotor->Copy_uint8DcMotorPinA, DIO_PIN_LOW);
		DIO_enumWritePinValue(DcMotor->Copy_uint8DcMotorPort, DcMotor->Copy_uint8DcMotorPinB, DIO_PIN_HIGH);
		break;
	case DCMOTOR_CCW:
		DIO_enumWritePinValue(DcMotor->Copy_uint8DcMotorPort, DcMotor->Copy_uint8DcMotorPinA, DIO_PIN_HIGH);
		DIO_enumWritePinValue(DcMotor->Copy_uint8DcMotorPort, DcMotor->Copy_uint8DcMotorPinB, DIO_PIN_LOW);
		break;
	case DCMOTOR_STOP:
		DIO_enumWritePinValue(DcMotor->Copy_uint8DcMotorPort, DcMotor->Copy_uint8DcMotorPinA, DIO_PIN_LOW);
		DIO_enumWritePinValue(DcMotor->Copy_uint8DcMotorPort, DcMotor->Copy_uint8DcMotorPinB, DIO_PIN_LOW);
		break;
	default:
		Local_uint8ErrorState = NOK;
	}

	return Local_uint8ErrorState;
}

