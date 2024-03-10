/*
 * history.c
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#include "history.h"
#include <string.h>

char history[HISTORY_LEN][MAX_CMD_LEN];
unsigned int lastSlot = 0;
unsigned int lastPos = 0;

void historySaveCmd(char *cmd)
{
	if (*cmd != '\0') {
		strcpy(history[lastSlot], cmd);
		lastPos = lastSlot;
		lastSlot = (lastSlot + 1) % HISTORY_LEN;
	}
}

char *historyGetPrevCmd()
{
	char *ret = &history[lastPos][0];

	lastPos = (lastPos - 1) % HISTORY_LEN;
	return ret;
}
