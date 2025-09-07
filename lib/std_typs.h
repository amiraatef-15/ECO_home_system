/*
 * std_typs.h
 *
 *  Created on: Dec 19, 2024
 *      Author: alaa hassan
 */

#ifndef LIB_STD_TYPS_H_
#define LIB_STD_TYPS_H_

typedef unsigned char          u8;
typedef unsigned short int     u16;
typedef unsigned long int      u32;
typedef unsigned long long int u64;
typedef signed char            s8;
typedef signed short int       s16;
typedef signed long int        s32;
typedef signed long long int   s64;
typedef float                  f32;
typedef double                 f64;

#define NULL                   ((void *)0)

#define ENABLE                 1
#define DISABLE                0


/* Func States  */
#define IDLE                   0
#define BUSY                   1

/* My States  */
#define OK                     0
#define NOK                    1
#define NULL_POINTER           2
#define BUSY_STATE             3
#define TIMEOUT_STATE          4


#endif /* LIB_STD_TYPS_H_ */
