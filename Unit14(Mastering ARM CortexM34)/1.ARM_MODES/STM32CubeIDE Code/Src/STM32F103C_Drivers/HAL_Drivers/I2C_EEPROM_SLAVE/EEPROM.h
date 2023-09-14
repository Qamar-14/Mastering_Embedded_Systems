/*
 *
 * I2C_EEPROM_SLAVE.h
 *
 *
 *	Created on: 8/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */

#ifndef INC_STM32F103x8_I2C_EEPROM_DRIVER_H_
#define INC_STM32F103x8_I2C_EEPROM_DRIVER_H_

#include "I2C_DRIVER/i2c.h"

// E2PROM is an I2C Slave
// Idle Mode : Device is high impedance state and wait for data
// Master Transmitter Mode : the device transmit data to a slave receiver
// Master Receive Mode : the device receives data from a slave transmitter

#define EEPROM_Slave_Address	0x2A  // this value defined by default

void EEPROM_Init(void);
unsigned char EEPROM_Write_NBytes(unsigned int Memory_address , unsigned char *bytes , uint8_t Data_Length);
unsigned char EEPROM_Read_Byte(unsigned int address, unsigned char *dataOut, uint8_t dataLen);


#endif
