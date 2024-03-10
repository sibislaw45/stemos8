/*
 * history.h
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#ifndef HISTORY_H_
#define HISTORY_H_

#define MAX_CMD_LEN		32
#define HISTORY_LEN		10

void historySaveCmd(char *cmd);
char *historyGetPrevCmd();

#endif /* HISTORY_H_ */
