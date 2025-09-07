/*
 * BIT_MATH.h
 *
 *  Created on: Dec 19, 2024
 *      Author: alaa hassan
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define REGISTER_SIZE 8
#define SET_BIT(reg,bit)     reg|=(1<<bit)
#define CLR_BIT(reg,bit)     reg&=(~(1<<bit))
#define TOG_BIT(reg,bit)     reg^=(1<<bit)
#define GET_BIT(reg,bit)     (reg& (1<<bit))>>bit

#define IS_BIT_SET(reg,bit)     (reg& (1<<bit))>>bit
#define IS_BIT_CLR(reg,bit)     !((reg& (1<<bit))>>bit
#define ROR(reg,num)     reg=(reg<<(REGISTER_SIZE-num))|(reg>>(num))
#define ROL(reg,num)     reg=(reg>>(REGISTER_SIZE-num))|(reg<<(num))

#define READ_BIT(REG, BIT)    ((REG >> BIT) & 0x01)

#endif /* LIB_BIT_MATH_H_ */
