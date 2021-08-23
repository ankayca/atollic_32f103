/*
 * AC_UART.c
 *
 *  Created on: Aug 15, 2021
 *      Author: ahmet
 */
#include "AC_UART.h"

void USART1_Transmitter(unsigned char data)
{
	/*********** STEPS FOLLOWED *************

	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.

		****************************************/


    while((USART1->SR & (1<<6)));	// Wait for TC to SET.. This indicates that the data has been transmitted
    USART1->DR = data;				// load the data into DR register

}

void AC_printstring(char *str)
{
  while(*str)
	{

		USART1_Transmitter(*(str++));

	}
}
/******* STEPS FOLLOWED ********

	1. Enable the UART CLOCK and GPIO CLOCK
	2. Configure the UART PINs for ALternate Functions
	3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	4. Program the M bit in USART_CR1 to define the word length.
	5. Select the desired baud rate using the USART_BRR register.
	6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register

	********************************/
void AC_UARTInit(void)
{
	GPIO_InitTypeDef gpio_init;
	USART_InitTypeDef usart1_init_struct;
	// Clock init for USART and Alternative function
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO ,ENABLE);


    /* Enalbe clock  GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Bit configuration structure for GPIOA PIN9 and PIN10 */

   /* GPIOA PIN9 alternative function Tx */
   gpio_init.GPIO_Pin = GPIO_Pin_9;
   gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
   gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA, &gpio_init);
   /* GPIOA PIN9 alternative function Rx */
   gpio_init.GPIO_Pin = GPIO_Pin_10;
   gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
   gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOA, &gpio_init);





	USART_Cmd(USART1, ENABLE);
	/* Baud rate 9600, 8-bit data, One stop bit
	 * No parity, Do both Rx and Tx, No HW flow control
	 */
	usart1_init_struct.USART_BaudRate = 9600;
	usart1_init_struct.USART_WordLength = USART_WordLength_8b;
	usart1_init_struct.USART_StopBits = USART_StopBits_1;
	usart1_init_struct.USART_Parity = USART_Parity_No ;
	usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* Configure USART1 */
	USART_Init(USART1, &usart1_init_struct);

}
