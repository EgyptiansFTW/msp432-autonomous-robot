/*
 * PIR.c
 *
 *  Created on: May 1, 2026
 *      Author: marka
 */

#include "msp.h"
#include "../inc/PIR.h"

#define PIR_PORT P3
#define PIR_PIN  BIT0

void PIR_Init(void)
{
    PIR_PORT->SEL0 &= ~PIR_PIN;
    PIR_PORT->SEL1 &= ~PIR_PIN;
    PIR_PORT->DIR  &= ~PIR_PIN;
    PIR_PORT->REN  &= ~PIR_PIN;
}

uint8_t PIR_Read(void)
{
    return (PIR_PORT->IN & PIR_PIN) ? 1 : 0;
}

uint8_t PIR_Confirmed(void)
{
    uint8_t count = 0;

    for (int i = 0; i < 5; i++)
    {
        if (PIR_Read())
        {
            count++;
        }

        Clock_Delay1ms(50);
    }

    // require majority HIGH
    return (count >= 3);
}
