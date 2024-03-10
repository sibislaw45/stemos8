/*
 * cmd.c
 *
 *  Created on: Mar 13, 2024
 *      Author: sibislaw
 */

#include "cmd.h"
#include "util.h"
#include "i2c.h"
#include "spi.h"
#include "stm8.h"
#include "cpuContext.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_SPI_WRITE_BYTES 8

typedef void (*handlingFn_t)(tokenizedCommand_t *, const char *);

typedef struct {
	const char *cmd;
	const char *usage;
	int maxTokens;
	handlingFn_t handlingFn;
} systemCmd_t;

static void handleMemdump(tokenizedCommand_t *t, const char *usage);
static void handleRegdump(tokenizedCommand_t *t, const char *usage);
static void handleMemset(tokenizedCommand_t *t, const char *usage);
static void handleI2CDetect(tokenizedCommand_t *t, const char *usage);
static void handleSpiWrite(tokenizedCommand_t *t, const char *usage);
static void handleI2CWrite(tokenizedCommand_t *t, const char *usage);
static void handleI2CRead(tokenizedCommand_t *t, const char *usage);

systemCmd_t cmdTable[] =
{
		{"md", "memory dump, md <startInHex> [<sizeInHex>]", 3, handleMemdump},
		{"reg", "show registers, no parameters", 1, handleRegdump},
		{"ms", "set byte in memory, ms <addr> <val>", 3, handleMemset},
		{"i2c-detect", "detect i2c devices on bus", 1, handleI2CDetect},
		{"spi-write", "write/read from spi device, spi-write <byte1> <byte2> ... <byte8>", MAX_SPI_WRITE_BYTES+1, handleSpiWrite},
		{"i2c-read", "read from i2c device, i2c-read <dev_addr> <mem_addr>", 3, handleI2CRead},
		{"i2c-write", "write to i2c device, i2c-read <dev_addr> <mem_addr> <val>", 4, handleI2CWrite},
};
uint8_t numOfCmds = sizeof(cmdTable) / sizeof(cmdTable[0]);

const char *autoComplete(char *cmdLine)
{
	for (int i = 0; i < numOfCmds; i++) {
		if (strncmp(cmdTable[i].cmd, cmdLine, strlen(cmdLine)) == 0) {
			return cmdTable[i].cmd;
		}
	}
	return NULL;
}

int checkByteFormat(char *byte)
{
	if (strlen(byte) != 2) {
		return 0;
	}

	if (!isxdigit(byte[0]) || !isxdigit(byte[1])) {
		return 0;
	}

	return 1;
}

static void handleSpiWrite(tokenizedCommand_t *t, const char *usage)
{
	uint8_t bytes[MAX_SPI_WRITE_BYTES];
	int len = t->numTokens - 1;

	if (t->numTokens < 2) {
		printf("No bytes provided!\n");
		printf("usage: %s\n", usage);
		return;
	}

	for (int i = 0; i < len; i++) {
		if (!checkByteFormat(t->tokens[i + 1])) {
			printf("Invalid byte format! Correct is XX!\n");
			return;
		}
		bytes[i] = strtoul(t->tokens[i + 1], NULL, 16);
	}

	spiWrite(bytes, len);

	printf("Received: ");
	for (int i = 0; i < len; i++) {
		printf("%02X ", bytes[i]);
	}
	printf("\n");
}

static void handleI2CRead(tokenizedCommand_t *t, const char *usage)
{
	uint8_t devAddr, value;
	uint16_t memAddr;
	char *endptr;
	int err;

	if (t->numTokens != 3) {
		printf("Usage: %s\n", usage);
		return;
	}

	devAddr = strtoul(t->tokens[1], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("Dev addr argument not a valid number!\n");
		return;
	}

	memAddr = strtoul(t->tokens[2], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("Mem addr argument not a valid number!\n");
		return;
	}

	err = i2cReadMemory(devAddr, memAddr, &value);
	if (err) {
		printf("Read failed for dev %02X mem %04X! Error code %d\n", devAddr, memAddr, err);
		return;
	}
	printf("%04X: %02X\n", memAddr, value);
}

static void handleI2CWrite(tokenizedCommand_t *t, const char *usage)
{
	uint8_t devAddr, value;
	uint16_t memAddr;
	char *endptr;
	int err;

	if (t->numTokens != 4) {
		printf("Usage: %s\n", usage);
		return;
	}

	devAddr = strtoul(t->tokens[1], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("Dev addr argument not a valid number!\n");
		return;
	}

	memAddr = strtoul(t->tokens[2], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("Mem addr argument not a valid number!\n");
		return;
	}

	value = strtoul(t->tokens[3], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("Value addr argument not a valid number!\n");
		return;
	}

	err = i2cWriteMemory(devAddr, memAddr, value);
	if (err) {
		printf("Write failed for dev %02X mem %04X value %02X! code = %d\n", devAddr, memAddr, value, err);
		return;
	}
	printf("%02X -> %04X\n", value, memAddr);
}

static void handleI2CDetect(tokenizedCommand_t *t, const char *usage)
{
	UNUSED_PARAM(t);
	UNUSED_PARAM(usage);

	printf("   ");
	for (int i = 0; i <= 0x0f; i++) {
		printf("  %x", i);
	}
	printf("\n");
	for (uint8_t addrH = 0; addrH <= 0x70; addrH += 0x10) {
		printf("%02X:", addrH);
		for (uint8_t addrL = 0; addrL <= 0xf; addrL++) {
			if (addrL + addrH <= 0x02) {
				printf("   ");
				continue;
			}

			if (addrL + addrH == 0x78) {
				break;
			}

			// user interrupt
			if (UART_SR & UART_SR_RXNE) {
				printf("\n\n INTERRUPTED \n\n");
				UART_DR;
				return;
			}

			if (i2cProbeDevice(addrL + addrH)) {
				printf(" %02X", addrL + addrH);
			} else {
				printf(" --");
			}
		}
		printf("\n");
	}
}

static void handleMemdump(tokenizedCommand_t *t, const char *usage)
{
	uint16_t startAddr;
	uint16_t size = 1;
	char *endptr;

	if (t->numTokens < 2) {
		printf("No parameters!\n");
		printf("Usage:\n%s\n", usage);
		return;
	}

	startAddr = strtoul(t->tokens[1], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("First param invalid number!\n");
		return;
	}

	if (t->numTokens > 2) {
		size = strtoul(t->tokens[2], &endptr, 16);
		if (!endptr || *endptr != '\0') {
			printf("Second param invalid number!\n");
			return;
		}
	}

	printf("MEMDUMP from %04X to %04X\n", startAddr, startAddr + size);
	memdump((char*)startAddr, size);
}

static void handleRegdump(tokenizedCommand_t *t, const char *usage)
{
	UNUSED_PARAM(t);
	UNUSED_PARAM(usage);

	saveCpuContext();
	printCpuContext();
}

static void handleMemset(tokenizedCommand_t *t, const char *usage)
{
	uint16_t addr;
	uint8_t val;
	char *endptr;

	if (t->numTokens < 3) {
		printf("No parameters!\n");
		printf("Usage:\n%s\n", usage);
		return;
	}

	addr = strtoul(t->tokens[1], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("First param invalid number!\n");
		return;
	}

	val = strtoul(t->tokens[2], &endptr, 16);
	if (!endptr || *endptr != '\0') {
		printf("Second param invalid number!\n");
		return;
	}

	*((char*)addr) = val;
}

static void doCmd(tokenizedCommand_t *t)
{
	for (int i = 0; i < numOfCmds; i++) {
		if (strcmp(cmdTable[i].cmd, t->tokens[0]) == 0) {
			if (t->numTokens > cmdTable[i].maxTokens) {
				printf("To many parameters!\n");
				printf("%s\n", cmdTable[i].usage);
				return;
			}

			cmdTable[i].handlingFn(t, cmdTable[i].usage);

			return;
		}
	}

	printf("Invalid command!\n");
	printf("Command list:\n");

	for (int i = 0; i < numOfCmds; i++) {
		printf("%s - %s\n", cmdTable[i].cmd, cmdTable[i].usage);
	}
}

void parseCommand(char *cmdLine)
{
	tokenizedCommand_t tokCmd;

	tokenizeCommand(&tokCmd, cmdLine);
	doCmd(&tokCmd);
}
