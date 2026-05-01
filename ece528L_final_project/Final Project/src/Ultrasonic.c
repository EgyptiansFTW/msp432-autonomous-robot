/*
 * Ultrasonic.c
 *
 *  Created on: May 1, 2026
 *      Author: marka
 */

#include "../inc/Ultrasonic.h"
#include "msp.h"
#include "../inc/Clock.h"

#define TRIG_PORT P6
#define TRIG_PIN  BIT0

#define ECHO_PORT P6
#define ECHO_PIN  BIT1

void Ultrasonic_Init(void)
{
    // TRIG = output
    TRIG_PORT->SEL0 &= ~TRIG_PIN;
    TRIG_PORT->SEL1 &= ~TRIG_PIN;
    TRIG_PORT->DIR  |= TRIG_PIN;

    // ECHO = input
    ECHO_PORT->SEL0 &= ~ECHO_PIN;
    ECHO_PORT->SEL1 &= ~ECHO_PIN;
    ECHO_PORT->DIR  &= ~ECHO_PIN;
}

uint32_t Ultrasonic_Read(void)
{
    uint32_t time = 0;

    // Ensure trigger is low
    TRIG_PORT->OUT &= ~TRIG_PIN;
    Clock_Delay1us(2);

    // Send 10us pulse
    TRIG_PORT->OUT |= TRIG_PIN;
    Clock_Delay1us(10);
    TRIG_PORT->OUT &= ~TRIG_PIN;

    // Wait for echo to go high
    while ((ECHO_PORT->IN & ECHO_PIN) == 0);

    // Measure high time
    while (ECHO_PORT->IN & ECHO_PIN)
    {
        time++;
        Clock_Delay1us(1);
    }

    // Convert time to distance
    // speed of sound ≈ 343 m/s
    // distance = time * 0.034 / 2
    uint32_t distance = (time * 34) / 2000;

    return distance;
}


