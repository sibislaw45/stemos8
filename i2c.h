/*
 * i2c.h
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#define I2C_ERR_NOT_SPECIFIED	-1
#define I2C_ERR_BUS_NOT_IDLE 	-2
#define I2C_ERR_START_FAILED	-3
#define I2C_ERR_ADDR_NACK 		-4
#define I2C_ERR_ADDR_TIMEOUT	-5
#define I2C_ERR_SEND_TIMEOUT	-6
#define I2C_ERR_READ_TIMEOUT	-7

void i2cInit();
int i2cProbeDevice(uint8_t addr);
int i2cWriteMemory(uint8_t devAddr, uint16_t memAddr, uint8_t value);
int i2cReadMemory(uint8_t devAddr, uint16_t memAddr, uint8_t *value);

#endif /* I2C_H_ */
