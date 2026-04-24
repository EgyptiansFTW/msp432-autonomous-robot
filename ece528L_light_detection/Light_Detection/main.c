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

#include <stdint.h>
#include "msp.h"
#include <math.h>

#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/Motor.h"
#include "inc/Timer_A1_Interrupt.h"
#include "inc/OPT3001.h"

// Enable DEBUG_ACTIVE to view the output of the printf statements
#define DEBUG_ACTIVE 1

// Initialize lux threshold. Must be modified based on light intensity
#define LUX_THRESHOLD 5000
#define LUX_MIN 500
#define DUTY_CYCLE_MIN 2000
#define DUTY_CYCLE_MAX 10500
// Declare struct for the light sensor
OPT3001_Result Light;

// Declare global variable to store lux value
static double lux = 0;

// Declare global variable to indicate that lux has been measured by the light sensor
static uint8_t lux_done = 0;

// Set initial duty cycle of the left wheel to 25%
static uint16_t Duty_Cycle_Left = 3750;

// Set initial duty cycle of the right wheel to 25%
static uint16_t Duty_Cycle_Right = 3750;

void Controller_1()
{
    if (lux < LUX_MIN)
    {
        Motor_Stop();
    }
    else if (lux < LUX_THRESHOLD)
    {
        uint16_t Duty_Cycle = DUTY_CYCLE_MIN +
            (uint16_t)(((lux - LUX_MIN) * (DUTY_CYCLE_MAX - DUTY_CYCLE_MIN)) /
            (LUX_THRESHOLD - LUX_MIN));

        Duty_Cycle_Left = Duty_Cycle;
        Duty_Cycle_Right = Duty_Cycle;

        Motor_Forward(Duty_Cycle_Left, Duty_Cycle_Right);
    }
    else
    {
        Duty_Cycle_Left = DUTY_CYCLE_MAX;
        Duty_Cycle_Right = DUTY_CYCLE_MAX;

        Motor_Forward(Duty_Cycle_Left, Duty_Cycle_Right);
    }
}

void Timer_A1_Periodic_Task(void)
{
    Controller_1();
}

void Sample_Light_Sensor()
{
    Light = OPT3001_Read_Light();
    lux = (0.01) * (pow(2, Light.Exponent)) * (Light.Result);
}

int main(void)
{
    // Initialize the 48 MHz Clock
    Clock_Init48MHz();

    // Ensure that interrupts are disabled during initialization
    DisableInterrupts();

    // Initialize the built-in red LED and the RGB LEDs
    LED1_Init();
    LED2_Init();

    // Initialize the chassis board LEDs
    Chassis_Board_LEDs_Init();

    // Initialize EUSCI_A0_UART to use the printf function
    EUSCI_A0_UART_Init_Printf();

    // Initialize Timer A1 with interrupts enabled and an interrupt rate of 1 kHz
    Timer_A1_Interrupt_Init(&Timer_A1_Periodic_Task, TIMER_A1_INT_CCR0_VALUE);

    // Initialize the DC motors
    Motor_Init();

    // Initialize I2C using EUSCI_B1 module
    EUSCI_B1_I2C_Init();
    P8->OUT |= 0x01;
    // Initialize the OPT3001 Ambient Light Sensor
    OPT3001_Init();
    P8->OUT &= ~0x01;

    // Enable the interrupts used by the timer modules and other peripherals
    EnableInterrupts();

    while(1)
    {
        Sample_Light_Sensor();

    #ifdef DEBUG_ACTIVE
        printf("\nLight Sensor Exponent: %d\n", Light.Exponent);
        printf("Light Sensor Mantissa: %d\n", Light.Result);
        printf("Light Sensor Lux: %f\n\n", lux);
        Clock_Delay1ms(100);
    #endif
    }

}

