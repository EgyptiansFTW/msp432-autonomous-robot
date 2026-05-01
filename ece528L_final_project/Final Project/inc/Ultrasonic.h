/*
 * Ultrasonic.c
 *
 *  Created on: May 1, 2026
 *      Author: marka
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include <stdint.h>

void Ultrasonic_Init(void);
uint32_t Ultrasonic_Read(void); // returns distance in cm

#endif


