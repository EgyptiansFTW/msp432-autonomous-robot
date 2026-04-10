/**
 * @file main.c
 *
 * @brief Main source code for the Light_Detection (I2C) program.
 *
 * This file contains the main entry point for the Light_Detection (I2C) program.
 *
 * It establishes communication with the following peripheral using I2C to demonstrate light detection:
 *  - OPT3001 Ambient Light Sensor (TI BP-BASSENSORSMKII BoosterPack)
 *
 * The following Timer_A modules are used in this lab:
 *  - Timer_A0: Used to generate PWM signals that will be used to drive the DC motors
 *  - Timer_A1: Used to generate periodic interrupts at a specified rate (1 kHz)
 *
 * @author
 */

#include "msp.h"
#include <math.h>

int main(void)
{

    while(1)
    {

    }
}
