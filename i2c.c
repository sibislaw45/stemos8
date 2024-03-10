/*
 * i2c.c
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#ifndef I2C_C_
#define I2C_C_

#include "i2c.h"
#include "stm8.h"
#include "isrdefs.h"
#include <stdio.h>

volatile int timeout = 0;

void tim3update() __interrupt(TIM3_OVR_UIF_IRQ)
{
	timeout = 1;
	TIM3_SR1 &= ~TIM_SR1_UIF;
}

static void i2cTimeoutInit()
{
	TIM3_PSCR = 0x0f;
	TIM3_ARRH = 0x00;
	TIM3_ARRL = 0x3D;
	TIM3_IER  = TIM_IER_UIE;
}

static void i2cTimeoutClear()
{
	sim();
	TIM3_CR1 = 0;
	TIM3_SR1 &= ~TIM_SR1_UIF;
	rim();

	timeout = 0;

	TIM3_CR1 = TIM_CR1_OPM | TIM_CR1_CEN;
}

static int i2cTimeout()
{
	return timeout;
}

// PE1 - I2C_SCL
// PE2 - I2C_SDA
void i2cInit()
{
	i2cTimeoutInit();

	PE_ODR |=   PIN1 | PIN2;
	PE_DDR |=   PIN1 | PIN2;
	PE_CR2 |=   PIN1 | PIN2;

	I2C_FREQR	= 2;
	I2C_CCRL	= 10;
	I2C_CCRH	= 0;
	I2C_TRISER	= 3;

	I2C_CR1 |= 0x01;
}

static int i2cWaitForIdleBus()
{
	while ((I2C_SR3 & I2C_SR3_BUSY) && !i2cTimeout()) {
		I2C_CR2 |= I2C_CR2_STOP;
		while ((I2C_CR2 & I2C_CR2_STOP) && !i2cTimeout());
	}
	return i2cTimeout() ? -1 : 0;
}

static int i2cSendStart()
{
	I2C_CR2 |= I2C_CR2_START;
	while (!(I2C_SR1 & I2C_SR1_SB) && !i2cTimeout());
	return i2cTimeout() ? -1 : 0;
}

static int i2cSendStop()
{
	I2C_CR2 |= I2C_CR2_STOP;
	while ((I2C_CR2 & I2C_CR2_STOP) && !i2cTimeout());
	return i2cTimeout() ? -1 : 0;
}

static int i2cSendAddress(uint8_t addr, uint8_t read)
{
	I2C_DR = (addr << 1) | read;
	I2C_SR2 = 0;
	while (!(I2C_SR1 & I2C_SR1_ADDR) && !i2cTimeout()) {
		if (I2C_SR2 & I2C_SR2_AF) {
			return -1;
		}
	}
	I2C_SR3;
	return i2cTimeout() ? -1 : 0;
}

static int i2cStartTransmission(uint8_t addr, uint8_t read)
{
	if (i2cWaitForIdleBus()) 		{ return -1; }
	if (i2cSendStart()) 			{ return -1; }
	if (i2cSendAddress(addr, read)) { return -1; }
	return 0;
}

static int i2cSend(uint8_t byte)
{
	I2C_DR = byte;
	while (!(I2C_SR1 & I2C_SR1_TXE) && !i2cTimeout());
	return i2cTimeout() ? -1 : 0;
}

static int i2cRead(uint8_t *byte)
{
	while (!(I2C_SR1 & I2C_SR1_RXNE) && !i2cTimeout());
	*byte = I2C_DR;
	return i2cTimeout() ? -1 : 0;
}

int i2cWriteMemory(uint8_t devAddr, uint16_t memAddr, uint8_t value)
{
	i2cTimeoutClear();

	if (i2cStartTransmission(devAddr, 0)) 	{ return -1; }
	if (i2cSend((memAddr & 0xFF) >> 8)) 	{ return -1; }
	if (i2cSend(memAddr & 0xFF)) 			{ return -1; }
	if (i2cSend(value)) 					{ return -1; }
	i2cSendStop();

	return 0;
}

int i2cReadMemory(uint8_t devAddr, uint16_t memAddr, uint8_t *value)
{
	i2cTimeoutClear();

	if (i2cStartTransmission(devAddr, 0)) 	{ return -1; }
	if (i2cSend((memAddr & 0xFF) >> 8)) 	{ return -1; }
	if (i2cSend(memAddr & 0xFF)) 			{ return -1; }
	if (i2cSendStart()) 					{ return -1; }
	if (i2cSendAddress(devAddr, 1))			{ return -1; }
	if (i2cRead(value)) 					{ return -1; }
	i2cSendStop();

	return 0;
}

int i2cProbeDevice(uint8_t addr)
{
	i2cTimeoutClear();

	if (i2cStartTransmission(addr, 1)) { return 0; }
	i2cSendStop();

	return 1;
}

#endif /* I2C_C_ */
