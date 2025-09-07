/*
 * PIR_config.h
 *
 * Created: 04/04/2025 23:16:32
 *  Author: GOHARY 10
 */ 


#ifndef HAL_PIR_CONFIG_H_
#define HAL_PIR_CONFIG_H_

/*
 * Options:
 *   PIR_PORT: [DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD]
 *   PIR_PIN:  [DIO_PIN0..DIO_PIN7]
 */
#define PIR_PORT   DIO_PORTD
#define PIR_PIN    DIO_PIN2

/*
 * PIR Connection Mode:
 *   PIR_ACTIVE_HIGH - Sensor outputs HIGH when motion detected
 *   PIR_ACTIVE_LOW  - Sensor outputs LOW when motion detected
 */
#define PIR_CONNECTION_MODE PIR_ACTIVE_HIGH

/*
 * Debounce time in milliseconds
 * (to avoid false triggers)
 */
#define PIR_DEBOUNCE_MS 200

#endif
