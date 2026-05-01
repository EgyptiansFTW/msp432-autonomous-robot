#include <stdint.h>
#include <stdio.h>
#include "msp.h"

#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/Motor.h"
#include "inc/Ultrasonic.h"
#include "inc/PIR.h"

#define OBSTACLE_THRESHOLD 20

int main(void)
{
    Clock_Init48MHz();
    DisableInterrupts();

    EUSCI_A0_UART_Init_Printf();
    Motor_Init();
    Ultrasonic_Init();
    PIR_Init();

    EnableInterrupts();

    while (1)
    {
        uint32_t distance = Ultrasonic_Read();
        uint8_t motion = PIR_Confirmed();

        printf("Distance: %lu cm | PIR: %u\r\n", distance, motion);

        if (motion)
        {
            Motor_Stop();
            Clock_Delay1ms(1500);
        }
        else if (distance > 0 && distance < OBSTACLE_THRESHOLD)
        {
            Motor_Stop();
            Clock_Delay1ms(200);

            Motor_Right(3000, 3000);
            Clock_Delay1ms(500);

            Motor_Stop();
        }
        else
        {
            Motor_Backward(3000, 3000);
        }

        Clock_Delay1ms(100);
    }
}
