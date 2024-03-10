#include "stm8.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include "util.h"
#include "console.h"
#include "history.h"
#include "i2c.h"
#include "spi.h"
#include "isrdefs.h"
#include "cmd.h"

char userMem[32] = {'A'};

void tim2update() __interrupt(TIM2_OVR_UIF_IRQ)
{
	if (PD_ODR & PIN0) {
		PD_ODR &= ~PIN0;
	} else {
		PD_ODR |= PIN0;
	}
	TIM2_SR1 &= ~TIM_SR1_UIF;
}

void initTim2()
{
	TIM2_PSCR = 0x0d;
	TIM2_ARRH = 0x00;
	TIM2_ARRL = 0x3D;
	TIM2_IER = TIM_IER_UIE;
	TIM2_CR1 = TIM_CR1_CEN;
}

int main()
{
	char cmd[MAX_CMD_LEN];
	int cmdPtr = 0;

	PD_DDR = PIN0 | PIN5; // output
	PD_CR1 = PIN0 | PIN5; // push-pull
	PD_CR2 = PIN0 | PIN5; // 10MHz output speed

	init_uart();
	i2cInit();
	initTim2();
	initSpi();

	rim();

	printf("\n\n");
	printf("STM8S simple os, compiled %s %s\n\n", __DATE__, __TIME__);
	printf("User memory is on address %04X, size %04X\n", &userMem[0], sizeof(userMem));

	while (1) {
		printf(">");
		getCommand(cmd, MAX_CMD_LEN, autoComplete);
		printf("\n");
		parseCommand(cmd);
	}
}
