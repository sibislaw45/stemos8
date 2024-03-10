/*
 * console.c
 *
 *  Created on: Mar 10, 2024
 *      Author: sibislaw
 */

#include "console.h"
#include "history.h"
#include "stm8.h"
#include <stdio.h>
#include <string.h>

#define SEQ_UP		'A'
#define SEQ_DOWN 	'B'

void init_uart()
{
	UART_BRR1 = 0x0D;
	UART_BRR2 = 0;
	UART_CR2 = UART_CR2_TEN | UART_CR2_REN;
}

int putchar(int c)
{
	if (c == '\n') {
		putchar('\r');
	}
    while(!(UART_SR & UART_SR_TXE)) {
    }
    UART_DR = c;
    return 0;
}

int getchar()
{
	while (!(UART_SR & UART_SR_RXNE)) {
	}
	return UART_DR;
}

void reloadCmd(char *buf, int *pos, char *newCmd)
{
	strcpy(buf, newCmd);
	printf("\x1B[2K");
	printf("\r>%s", buf);
	*pos = strlen(buf);
}

int getCommand(char *buf, int bufSize, char *(*completeFn)(char *))
{
	int bufPos = 0;

	memset(buf, '\0', bufSize);

	while (1) {
		int c = getchar();

		if (c == '\t') {
			char *completion = completeFn(buf);
			if (completion) {
				reloadCmd(buf, &bufPos, completion);
			}
			continue;
		}

		if (c == '\x1B') {
			unsigned char s[2];
			s[0] = getchar();
			s[1] = getchar();

			if (s[0] == '[') {
				if (s[1] == SEQ_UP) {
					char *prevCmd = historyGetPrevCmd();
					reloadCmd(buf, &bufPos, prevCmd);
				} else if (s[1] == SEQ_DOWN) {
				}
			}

			continue;
		}

		if (c == '\r') {
			break;
		} else if (c == '\x08') {
			if (bufPos > 0) {
				putchar('\x08');
				putchar(' ');
				putchar('\x08');
				bufPos--;
				buf[bufPos] = '\0';
			}
		} else {
			if (bufPos < bufSize - 1) {
				buf[bufPos] = c;
				bufPos++;
				putchar(c);
			}
		}
	}
	buf[bufPos] = '\0';
	historySaveCmd(buf);
	return bufPos;
}

