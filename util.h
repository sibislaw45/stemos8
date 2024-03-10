/*
 * util.h
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#ifndef UTIL_H_
#define UTIL_H_

#define UNUSED_PARAM(p) (void)p

#define MAX_CMD_TOKENS 	9

typedef struct {
	char *tokens[MAX_CMD_TOKENS];
	int numTokens;
} tokenizedCommand_t;

void tokenizeCommand(tokenizedCommand_t *t, char *cmdLine);
void memdump(char *mem, int size);

#endif /* UTIL_H_ */
