/*
 * AC_UART.c
 *
 *  Created on: Aug 15, 2021
 *      Author: ahmet
 */
#include "AC_UART.h"

void USART1_Transmitter(unsigned char data)
{

    while((USART1->SR & (1<<7)) == 0);
    USART1->DR = data;

}

void AC_printstring(char *str)
{
  while(*str)
	{

		USART1_Transmitter(*(str++));

	}
}
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
