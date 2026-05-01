# Autonomous Obstacle Avoidance Robot with Motion Detection

ECE 528 – Robotics and Embedded Systems  
Spring 2026

## Project Overview

This project demonstrates a real-time embedded robotic system built on the MSP432 LaunchPad and TI RSLK chassis. The robot autonomously navigates an environment using an HC-SR04 ultrasonic sensor for obstacle detection and an HC-SR501 PIR sensor for motion detection. The control logic is implemented directly on the MSP432 and commands the motors to move forward, turn, or stop based on sensor input.

The design solves the problem of enabling a low-cost mobile embedded platform to react to both static obstacles and dynamic motion events using simple sensors and priority-based control. The project emphasizes practical embedded systems integration, GPIO interfacing, safe signal conditioning, motor control, and real-world testing.

## System Architecture

The system is organized as a sensor-to-controller-to-actuator pipeline:

- **HC-SR04 Ultrasonic Sensor** provides distance measurements for obstacle avoidance.
- **HC-SR501 PIR Sensor** detects motion from nearby warm bodies or moving subjects.
- **MSP432 LaunchPad** reads both sensors, applies control logic, and generates motor commands.
- **Motor Driver / TI RSLK Chassis** executes the commanded movement.

### High-Level Behavior

1. Read ultrasonic distance.
2. Read PIR motion state using software confirmation.
3. Apply priority-based logic:
   - If PIR motion is confirmed, stop the robot.
   - Else if distance is below a threshold, stop and turn.
   - Else continue moving forward.

## Interfaces and Peripherals Used

### Sensors and Connections

| Component | Signal | MSP432 Pin | Direction | Notes |
|---|---|---:|---|---|
| HC-SR04 | TRIG | P6.0 | Output | 10 us trigger pulse |
| HC-SR04 | ECHO | P6.1 | Input | Connected through resistor divider |
| HC-SR501 PIR | OUT | P3.0 | Input | Digital motion signal |

### Power Connections

| Component | Signal | Connection | Notes |
|---|---|---|---|
| HC-SR04 | VCC | 5V | Sensor powered from 5V rail |
| HC-SR04 | GND | GND | Common ground |
| HC-SR501 PIR | VCC | 5V | Stable 5V operation |
| HC-SR501 PIR | GND | GND | Common ground |

### MSP432 Peripherals Used

- **GPIO**
  - Ultrasonic trigger output
  - Ultrasonic echo input
  - PIR digital input
- **UART**
  - Serial debugging and verification output
- **Timers / Delays**
  - Ultrasonic timing and software delays
- **PWM / Motor control**
  - Existing motor driver functions from the TI RSLK kit

### Voltage Divider

The HC-SR04 echo pin outputs a 5V logic signal, while the MSP432 GPIO is a 3.3V device. To safely interface the echo signal, a voltage divider was used:

- **R1 = 1 kOhm**
- **R2 = 2 kOhm**

This reduces the echo signal to approximately 3.3V before it reaches the MSP432 input pin.

## Project Directory Structure

Example project organization:

```text
Final_Project/
├── inc/
│   ├── Motor.h
│   ├── PIR.h
│   └── Ultrasonic.h
├── src/
│   ├── main.c
│   ├── Motor.c
│   ├── PIR.c
│   └── Ultrasonic.c
└── README.md
```

## Verification and Testing

The project was developed using an incremental build-and-test approach so that each subsystem could be verified independently before full integration.

### 1. Motor System Verification
- Confirmed basic movement functions:
  - forward
  - backward
  - left turn
  - right turn
  - stop
- Verified that the robot chassis responded correctly to motor commands.

### 2. Ultrasonic Sensor Testing
- Wired the HC-SR04 and verified trigger/echo behavior.
- Added a resistor divider to safely read the 5V echo output.
- Printed measured distance values over UART to confirm sensor readings.
- Tuned obstacle threshold based on measured distance performance.

### 3. Obstacle Avoidance Integration
- Combined distance readings with motor control logic.
- Verified that the robot stopped and turned when approaching objects.
- Adjusted behavior after changing physical sensor position.

### 4. PIR Sensor Testing
- Wired the HC-SR501 and verified digital motion output.
- Confirmed sensor operation with nearby movement from people and pets.
- Implemented software confirmation (`PIR_Confirmed`) to reduce false triggers.

### 5. Full System Testing
- Combined ultrasonic and PIR behavior into one priority-based loop.
- Verified:
  - normal autonomous movement
  - obstacle avoidance with turning
  - motion-triggered stop behavior
- Observed real-world limitations such as PIR self-triggering from robot movement and ultrasonic blind spots caused by physical placement.

## Project Demonstration (Video Links)

Add your demo links here after uploading videos to GitHub, YouTube, Google Drive, or another hosting platform.

- Demo 1: [Insert link here]
- Demo 2: [Insert link here]

Suggested demo coverage:
- normal forward movement
- obstacle detection and turning
- PIR response to motion from a person or pet

## Limitations

- The ultrasonic sensor has a narrow field of view and may miss objects depending on mounting position.
- Physical space on the robot limits ideal sensor placement.
- The PIR sensor can self-trigger due to robot motion and vibration because it is mounted on a moving platform.
- The current navigation approach is reactive only and does not perform global path planning.

## Conclusion

This project demonstrates a practical embedded robotics implementation using low-cost sensors and microcontroller-based control. The robot successfully integrates distance sensing, motion detection, and motor actuation to produce autonomous, real-time behavior on the MSP432 platform.

The final result is a functional proof of concept showing how multiple sensor inputs can be combined in a simple but effective decision system for autonomous robot navigation.

## Build and Run Notes

- Open the project in Code Composer Studio.
- Verify that all source files are included in the build.
- Flash the MSP432 LaunchPad.
- Open the UART terminal for debug output if needed.
- Place the robot on a clear surface before running tests.

## Authors

- [Your Name]

