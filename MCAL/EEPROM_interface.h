/*
 * EEPROM_interface.h
 *
 *  Created on: Jan 31, 2025
 *      Author: engineering
 */

#ifndef MCAL_EEPROM_EEPROM_INTERFACE_H_
#define MCAL_EEPROM_EEPROM_INTERFACE_H_

void EEPROM_write(unsigned short address, const u8 *data, u8 size);
void EEPROM_read(unsigned short address, u8 *data, u8 size);


#endif /* MCAL_EEPROM_EEPROM_INTERFACE_H_ */
