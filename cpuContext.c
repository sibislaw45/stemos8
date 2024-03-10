/*
 * cpuContext.c
 *
 *  Created on: Mar 13, 2024
 *      Author: sibislaw
 */

#include "cpuContext.h"
#include <stdio.h>
#include <stdint.h>

static volatile uint8_t Areg;
static volatile uint16_t Xreg;
static volatile uint16_t Yreg;
static volatile uint16_t SPreg;
static volatile uint8_t PCLreg;
static volatile uint8_t PCHreg;
static volatile uint8_t PCEreg;
static volatile uint8_t CCreg;

void saveCpuContext()
{
	__asm
		pushw X
		push CC
		ldw _Xreg, X
		ldw _Yreg, Y

		ldw X, sp
		ldw _SPreg, X

		push CC
		pop _CCreg

		ld _Areg, A

		callf savePC
		savePC:
		pop _PCEreg
		pop _PCHreg
		pop _PCLreg

		pop CC
		popw X
	__endasm;
}

void printCpuContext()
{
	printf("--- REGISTERS:\n");
	printf("A:  %02X    X:  %04X    Y:  %04X\n", Areg, Xreg, Yreg);
	printf("SP: %04X  PC: %02X%02X%02X  CC: %02X\n", SPreg, PCEreg, PCHreg, PCLreg, CCreg);
}

