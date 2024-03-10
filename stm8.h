#ifndef _STM8_H
#define _STM8_H

#define PIN0    (1 << 0)
#define PIN1    (1 << 1)
#define PIN2    (1 << 2)
#define PIN3    (1 << 3)
#define PIN4    (1 << 4)
#define PIN5    (1 << 5)
#define PIN6    (1 << 6)
#define PIN7    (1 << 7)

#define CLK_CKDIVR	*(volatile unsigned char *)0x50C6
#define CLK_PCKENR1 *(volatile unsigned char *)0x0050C7
#define CLK_PCKENR2 *(volatile unsigned char *)0x0050CA

#define PA_ODR *(volatile unsigned char *)0x5000
#define PA_IDR *(volatile unsigned char *)0x5001
#define PA_DDR *(volatile unsigned char *)0x5002
#define PA_CR1 *(volatile unsigned char *)0x5003
#define PA_CR2 *(volatile unsigned char *)0x5004

#define PB_ODR *(volatile unsigned char *)0x5005
#define PB_IDR *(volatile unsigned char *)0x5006
#define PB_DDR *(volatile unsigned char *)0x5007
#define PB_CR1 *(volatile unsigned char *)0x5008
#define PB_CR2 *(volatile unsigned char *)0x5009

#define PC_ODR *(volatile unsigned char *)0x500A
#define PC_IDR *(volatile unsigned char *)0x500B
#define PC_DDR *(volatile unsigned char *)0x500C
#define PC_CR1 *(volatile unsigned char *)0x500D
#define PC_CR2 *(volatile unsigned char *)0x500E

#define PD_ODR *(volatile unsigned char *)0x500F
#define PD_IDR *(volatile unsigned char *)0x5010
#define PD_DDR *(volatile unsigned char *)0x5011
#define PD_CR1 *(volatile unsigned char *)0x5012
#define PD_CR2 *(volatile unsigned char *)0x5013

#define PE_ODR *(volatile unsigned char *)0x5014
#define PE_IDR *(volatile unsigned char *)0x5015
#define PE_DDR *(volatile unsigned char *)0x5016
#define PE_CR1 *(volatile unsigned char *)0x5017
#define PE_CR2 *(volatile unsigned char *)0x5018

#define UART_SR *(volatile unsigned char *)0x5240
#define UART_DR *(volatile unsigned char *)0x5241
#define UART_BRR1 *(volatile unsigned char *)0x5242
#define UART_BRR2 *(volatile unsigned char *)0x5243
#define UART_CR1 *(volatile unsigned char *)0x5244
#define UART_CR2 *(volatile unsigned char *)0x5245
#define UART_CR3 *(volatile unsigned char *)0x5246
#define UART_CR4 *(volatile unsigned char *)0x5247
#define UART_CR5 *(volatile unsigned char *)0x5248
#define UART_CR6 *(volatile unsigned char *)0x5249
#define UART_GTR *(volatile unsigned char *)0x524A
#define UART_PSCR *(volatile unsigned char *)0x524B

#define UART_SR_TXE (1 << 7)
#define UART_SR_TC (1 << 6)
#define UART_SR_RXNE (1 << 5)
#define UART_SR_IDLE (1 << 4)
#define UART_SR_OR (1 << 3)
#define UART_SR_NF (1 << 2)
#define UART_SR_FE (1 << 1)
#define UART_SR_PE (1 << 0)

#define UART_CR1_R8 (1 << 7)
#define UART_CR1_T8 (1 << 6)
#define UART_CR1_UARTD (1 << 5)
#define UART_CR1_M (1 << 4)
#define UART_CR1_WAKE (1 << 3)
#define UART_CR1_PCEN (1 << 2)
#define UART_CR1_PS (1 << 1)
#define UART_CR1_PIEN (1 << 0)

#define UART_CR2_TIEN (1 << 7)
#define UART_CR2_TCIEN (1 << 6)
#define UART_CR2_RIEN (1 << 5)
#define UART_CR2_ILIEN (1 << 4)
#define UART_CR2_TEN (1 << 3)
#define UART_CR2_REN (1 << 2)
#define UART_CR2_RWU (1 << 1)
#define UART_CR2_SBK (1 << 0)

#define UART_CR3_LINEN (1 << 6)
#define UART_CR3_STOP2 (1 << 5)
#define UART_CR3_STOP1 (1 << 4)
#define UART_CR3_CLKEN (1 << 3)
#define UART_CR3_CPOL (1 << 2)
#define UART_CR3_CPHA (1 << 1)
#define UART_CR3_LBCL (1 << 0)

#define TIM2_CR1 *(volatile unsigned char *)0x5300
#define TIM2_IER *(volatile unsigned char *)0x5301
#define TIM2_SR1 *(volatile unsigned char *)0x5302
#define TIM2_PSCR *(volatile unsigned char *)0x530C
#define TIM2_ARRH *(volatile unsigned char *)0x530D
#define TIM2_ARRL *(volatile unsigned char *)0x530E

#define TIM3_CR1 *(volatile unsigned char *)0x5320
#define TIM3_IER *(volatile unsigned char *)0x5321
#define TIM3_SR1 *(volatile unsigned char *)0x5322
#define TIM3_PSCR *(volatile unsigned char *)0x532A
#define TIM3_ARRH *(volatile unsigned char *)0x532B
#define TIM3_ARRL *(volatile unsigned char *)0x532C

#define TIM4_CR1  *(volatile unsigned char *)0x5340
#define TIM4_IER  *(volatile unsigned char *)0x5341
#define TIM4_SR   *(volatile unsigned char *)0x5342
#define TIM4_EGR  *(volatile unsigned char *)0x5343
#define TIM4_CNTR *(volatile unsigned char *)0x5344
#define TIM4_PSCR *(volatile unsigned char *)0x5345
#define TIM4_ARR  *(volatile unsigned char *)0x5346

#define TIM_IER_BIE (1 << 7)
#define TIM_IER_TIE (1 << 6)
#define TIM_IER_COMIE (1 << 5)
#define TIM_IER_CC4IE (1 << 4)
#define TIM_IER_CC3IE (1 << 3)
#define TIM_IER_CC2IE (1 << 2)
#define TIM_IER_CC1IE (1 << 1)
#define TIM_IER_UIE (1 << 0)

#define TIM_CR1_APRE (1 << 7)
#define TIM_CR1_CMSH (1 << 6)
#define TIM_CR1_CMSL (1 << 5)
#define TIM_CR1_DIR (1 << 4)
#define TIM_CR1_OPM (1 << 3)
#define TIM_CR1_URS (1 << 2)
#define TIM_CR1_UDIS (1 << 1)
#define TIM_CR1_CEN (1 << 0)

#define TIM_SR1_BIF (1 << 7)
#define TIM_SR1_TIF (1 << 6)
#define TIM_SR1_COMIF (1 << 5)
#define TIM_SR1_CC4IF (1 << 4)
#define TIM_SR1_CC3IF (1 << 3)
#define TIM_SR1_CC2IF (1 << 2)
#define TIM_SR1_CC1IF (1 << 1)
#define TIM_SR1_UIF (1 << 0)

#define SPI_CR1 *(volatile unsigned char *)0x5200
#define SPI_CR2 *(volatile unsigned char *)0x5201
#define SPI_ICR *(volatile unsigned char *)0x5202
#define SPI_SR *(volatile unsigned char *)0x5203
#define SPI_DR *(volatile unsigned char *)0x5204
#define SPI_CRCPR *(volatile unsigned char *)0x5205
#define SPI_RXCRCR *(volatile unsigned char *)0x5206
#define SPI_TXCRCR *(volatile unsigned char *)0x5207

#define SPI_CR1_LSBFIRST (1 << 7)
#define SPI_CR1_SPE (1 << 6)
#define SPI_CR1_BR(br) ((br) << 3)
#define SPI_CR1_MSTR (1 << 2)
#define SPI_CR1_CPOL (1 << 1)
#define SPI_CR1_CPHA (1 << 0)

#define SPI_CR2_BDM (1 << 7)
#define SPI_CR2_BDOE (1 << 6)
#define SPI_CR2_CRCEN (1 << 5)
#define SPI_CR2_CRCNEXT (1 << 4)
#define SPI_CR2_RXONLY (1 << 2)
#define SPI_CR2_SSM (1 << 1)
#define SPI_CR2_SSI (1 << 0)

#define SPI_ICR_TXIE (1 << 7)
#define SPI_ICR_RXIE (1 << 6)
#define SPI_ICR_ERRIE (1 << 5)
#define SPI_ICR_WKIE (1 << 4)

#define SPI_SR_BSY (1 << 7)
#define SPI_SR_OVR (1 << 6)
#define SPI_SR_MODF (1 << 5)
#define SPI_SR_CRCERR (1 << 4)
#define SPI_SR_WKUP (1 << 3)
#define SPI_SR_TXE (1 << 1)
#define SPI_SR_RxNE (1 << 0)

#define I2C_CR1 *(volatile unsigned char *)0x5210
#define I2C_CR2 *(volatile unsigned char *)0x5211
#define I2C_FREQR *(volatile unsigned char *)0x5212
#define I2C_OARL *(volatile unsigned char *)0x5213
#define I2C_OARH *(volatile unsigned char *)0x5214
#define I2C_DR *(volatile unsigned char *)0x5216
#define I2C_SR1 *(volatile unsigned char *)0x5217
#define I2C_SR2 *(volatile unsigned char *)0x5218
#define I2C_SR3 *(volatile unsigned char *)0x5219
#define I2C_ITR *(volatile unsigned char *)0x521A
#define I2C_CCRL *(volatile unsigned char *)0x521B
#define I2C_CCRH *(volatile unsigned char *)0x521C
#define I2C_TRISER *(volatile unsigned char *)0x521D
#define I2C_PECR *(volatile unsigned char *)0x521E

#define I2C_CR1_NOSTRETCH 	(1 << 7)
#define I2C_CR1_ENGC 	  	(1 << 6)
#define I2C_CR1_PE 		  	(1 << 0)

#define I2C_CR2_SWRST	  	(1 << 7)
#define I2C_CR2_POS		  	(1 << 3)
#define I2C_CR2_ACK		  	(1 << 2)
#define I2C_CR2_STOP	  	(1 << 1)
#define I2C_CR2_START	  	(1 << 0)

#define I2C_SR1_TXE			(1 << 7)
#define I2C_SR1_RXNE		(1 << 6)
#define I2C_SR1_STOPF		(1 << 4)
#define I2C_SR1_ADD10		(1 << 3)
#define I2C_SR1_BTF			(1 << 2)
#define I2C_SR1_ADDR		(1 << 1)
#define I2C_SR1_SB			(1 << 0)

#define I2C_SR2_WUFH		(1 << 5)
#define I2C_SR2_OVR			(1 << 3)
#define I2C_SR2_AF			(1 << 2)
#define I2C_SR2_ARLO		(1 << 1)
#define I2C_SR2_BERR		(1 << 0)

#define I2C_SR3_DUALF		(1 << 7)
#define I2C_SR3_GENCALL		(1 << 4)
#define I2C_SR3_TRA			(1 << 2)
#define I2C_SR3_BUSY		(1 << 1)
#define I2C_SR3_MSL			(1 << 0)

#define I2C_ITR_ITBUFEN		(1 << 2)
#define I2C_ITR_ITEVTEN		(1 << 1)
#define I2C_ITR_ITERREN		(1 << 0)

#define rim() {__asm__("rim\n");}
#define sim() {__asm__("sim\n");}

#define TIM1_OVR_UIF_IRQ 11
#define TIM2_OVR_UIF_IRQ 13
#define TIM3_OVR_UIF_IRQ 15
#define TIM4_OVR_UIF_IRQ 23

#endif
