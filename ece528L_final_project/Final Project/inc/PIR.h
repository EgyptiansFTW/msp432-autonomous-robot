/*
 * PIR.c
 *
 *  Created on: May 1, 2026
 *      Author: marka
 */

#ifndef INC_PIR_H_
#define INC_PIR_H_

#include <stdint.h>

void PIR_Init(void);
uint8_t PIR_Read(void);
uint8_t PIR_Confirmed(void);

#endif

