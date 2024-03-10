/*
 * util.c
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#include "util.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void tokenizeCommand(tokenizedCommand_t *t, char *cmdLine)
{
	int curToken = 0;
	int inToken = 0;

	for (int i = 0; i < MAX_CMD_TOKENS; i++) {
		t->tokens[i] = NULL;
	}

	for (int i = 0; cmdLine[i] != '\0'; i++) {
		char *c = &cmdLine[i];

		if (inToken) {
			if (isspace(*c)) {
				*c = '\0';
				inToken = 0;
				if (curToken == MAX_CMD_TOKENS) {
					break;
				}
			}
		} else {
			if (isspace(*c)) {
				*c = '\0';
			} else {
				inToken = 1;
				t->tokens[curToken] = c;
				curToken++;
			}
		}
	}

	t->numTokens = curToken;
}

void memdump(char *mem, int size)
{
	char asciiBuf[17];
	char *curAscii = asciiBuf;
	int i;

	memset(asciiBuf, 0, 17);

	printf("%04X: ", mem);
	for (i = 0; i < size; i++) {
		printf("%02X ", *mem);
		*curAscii = isprint(*mem) ? *mem : '.';
		curAscii++;
		mem++;

		if ((i+1) % 16 == 0) {
			printf("| %s |\n", asciiBuf);
			curAscii = asciiBuf;
			memset(asciiBuf, 0, 17);
			printf("%04X: ", mem);
		} else if ((i+1) % 8 == 0) {
			printf("  ");
		}
	}

	while((i) % 16 != 0) {
		printf("   ");
		if ((i) % 8 == 0) {
			printf("  ");
		}
		i++;
	}

	if (asciiBuf[0] != '\0') {
		printf("| %s |\n", asciiBuf);
	}

	printf("\n");
}
