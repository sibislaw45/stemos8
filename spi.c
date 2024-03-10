/*
 * spi.c
 *
 *  Created on: Mar 13, 2024
 *      Author: sibislaw
 */

#include "spi.h"
#include "stm8.h"
#include <stdio.h>

void initSpi()
{
	SPI_CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
	SPI_CR1 = SPI_CR1_SPE | SPI_CR1_MSTR;

	PC_DDR = PIN4 | PIN5 | PIN6;
	PC_CR1 = PIN4 | PIN5 | PIN6;
	PC_CR2 = PIN4 | PIN5 | PIN6;
	PC_ODR = PIN4;
}

void spiWrite(uint8_t *bytes, int len)
{
	PC_ODR &= ~PIN4;

	for (int i = 0; i < len; i++) {
		SPI_DR = bytes[i];

		while (!(SPI_SR & SPI_SR_TXE)) {
		}

		while (!(SPI_SR & SPI_SR_RxNE)) {
		}

		bytes[i] = SPI_DR;
	}

	PC_ODR |= PIN4;
}
