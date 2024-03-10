/*
 * console.h
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

void init_uart();
int getCommand(char *buf, int bufSize, char *(*completeFn)(char *));

#endif /* CONSOLE_H_ */
