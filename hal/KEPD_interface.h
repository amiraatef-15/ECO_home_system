/*
 * KEPD_interface.h
 *
 *  Created on: Jan 27, 2025
 *      Author: alaa hassan
 */

#ifndef HAL_KEPD_INTERFACE_H_
#define HAL_KEPD_INTERFACE_H_

#define NOTPRESSED  0xFF

void KPD_vInit       (void);
u8   KPD_u8GetPressed(void);


#endif /* HAL_KEPD_INTERFACE_H_ */
