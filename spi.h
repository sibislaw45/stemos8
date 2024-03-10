/*
 * spi.h
 *
 *  Created on: Mar 13, 2024
 *      Author: sibislaw
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void initSpi();
void spiWrite(uint8_t *bytes, int len);

#endif /* SPI_H_ */
