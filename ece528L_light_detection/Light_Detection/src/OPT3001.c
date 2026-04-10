/**
 * @file OPT3001.c
 * @brief Source code for the OPT3001 driver.
 *
 * This file contains the function definitions for the OPT3001 driver.
 *
 * The OPT3001 Ambient Light Sensor from the BP-BASSENSORSMKII Sensor BoosterPack is used.
 *
 * The OPT3001 driver uses the EUSCI_B1_I2C driver to access the registers
 * of the OPT3001 Ambient Light Sensor via I2C.
 *
 * @note This function assumes that the necessary pin configurations for the OPT3001 module have been performed
 *       on the corresponding pins.
 *
 * The OPT3001 Ambient Light Sensor uses the following pinout:
 *  - OPT3001 Pin 1 (VDD)       <-->  MSP432 LaunchPad Pin P4.5 (Device power)
 *  - OPT3001 Pin 2 (ADDR)      <-->  MSP432 LaunchPad GND (To set address 0x44 - Table 1 of datasheet)
 *  - OPT3001 Pin 3 (GND)       <-->  MSP432 LaunchPad GND
 *  - OPT3001 Pin 4 (SCL)       <-->  MSP432 LaunchPad Pin P6.5
 *  - OPT3001 Pin 5 (INT)       <-->  MSP432 LaunchPad Pin P4.2
 *  - OPT3001 Pin 6 (SDA)       <-->  MSP432 LaunchPad Pin P6.4
 *
 * @note Do not use with bumper sensors to avoid any pin conflicts.
 *
 * @note For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @note Refer to the OPT3001 Ambient Light Sensor datasheet for more information regarding the sensor.
 *
 * @author
 *
 */

#include "../inc/OPT3001.h"

// An enumeration that defines constants for various commands that can be sent
// to the OPT3001 Ambient Light Sensor. Each constant represents a specific command
// such as reading the result or configuring the sensor
typedef enum
{
    RESULT            = 0x00,
    CONFIG            = 0x01,
    LOW_LIMIT         = 0x02,
    HIGH_LIMIT        = 0x03,
    MANUFACTURER_ID   = 0x7E,
    DEVICE_ID         = 0x7F,
} OPT3001_Commands;

// A union that combines a bitfield struct with a uint16_t raw_data field.
// This is used to interpret and modify the configuration data for the
// OPT3001 Ambient Light Sensor. Its configuration settings are stored in specific
// bitfields within a 16-bit register
typedef union{
  struct
  {
    uint8_t FaultCount:                 2;
    uint8_t MaskExponent:               1;
    uint8_t Polarity:                   1;
    uint8_t Latch:                      1;
    uint8_t FlagLow:                    1;
    uint8_t FlagHigh:                   1;
    uint8_t ConversionReady:            1;
    uint8_t OverflowFlag:               1;
    uint8_t ModeOfConversionOperation:  2;
    uint8_t ConversionTime:             1;
    uint8_t RangeNumber:                4;
  };
  uint16_t RawData;
} OPT3001_Config;

// Declare a config struct used when reading the configuration register
OPT3001_Config Read_Sensor_Configuration;

/**
 * @brief Writes a single command byte to the OPT3001 light sensor via I2C.
 *
 * @param command The command byte to send to the sensor.
 *
 * @return None
 */
static void OPT3001_Write_Data(OPT3001_Commands command)
{

}

/**
 * @brief Reads data from the OPT3001 light sensor via I2C.
 *
 * @param data Pointer to a uint16_t variable where the sensor data will be stored.
 *
 * @return None
 */
static void OPT3001_Read_Data(uint16_t* data)
{

}

/**
 * @brief Reads a register from the OPT3001 sensor.
 *
 * @param command The command to read the desired register.
 *
 * @return An OPT3001_Result structure containing the data that was read.
 */
OPT3001_Result static OPT3001_Read_Register(OPT3001_Commands command)
{
    OPT3001_Result result;
    OPT3001_Write_Data(command);
    OPT3001_Read_Data(&result.RawData);
    return result;
}

/**
 * @brief This function writes a 16-bit value to a specific register on the OPT3001 sensor via I2C communication.
 *
 * @param register_address The register address to write the data to.
 * @param register_data The 16-bit data to be written to the register.
 *
 * @return None
 */
static void OPT3001_Write_Register(uint8_t register_address, uint16_t register_data)
{

}

/**
 * @brief This function writes an OPT3001_Config struct to the OPT3001 sensor's configuration registers.
 *
 * @param config The OPT3001_Config struct containing configuration data to be written.
 *
 * @return None
 */
static void OPT3001_Write_Configuration(OPT3001_Config config)
{

}

/**
 * @brief This function reads the configuration from the OPT3001 sensor and returns it in an OPT3001_Config struct
 *
 * @param None
 *
 * @return An OPT3001_Config structure containing the sensor's configuration data.
 */
OPT3001_Config static OPT3001_Read_Configuration()
{
    OPT3001_Config config;
    OPT3001_Write_Data(CONFIG);
    OPT3001_Read_Data(&config.RawData);
    return config;
}

void OPT3001_Init()
{

}

OPT3001_Result OPT3001_Read_Light()
{
    // Read the Result Register (offset = 00h)
    // This register contains the most recent light to digital conversion
    return OPT3001_Read_Register(RESULT);
}
