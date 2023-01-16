/*
 * uartConsole.c
 *
 *  Created on: 03.01.2023
 *      Author: User
 */

#include "usart.h"
#include <stdio.h>
#include <string.h>

int _write(int file, char *ptr, int len)
{
	while(huart2.gState != HAL_UART_STATE_READY)
	{
		//warteschleife
	}
	static char dest[100];

	if(len > 100)
	{
		len = 100;
	}
	memcpy(dest, ptr, len);
	HAL_UART_Transmit_DMA(&huart2, (uint8_t *)dest, len);

	return len;
}

int _read(int file, char *ptr, int len) {

	// Wait for an input character.
	HAL_UART_Receive(&huart2, (uint8_t*)ptr, 1, HAL_MAX_DELAY);

	// Map return to newline which is expected as line termination by caller.
	if (*ptr == '\r') {
		*ptr = '\n';
	}

	// Echo received character, newline (special case) as CR/NL.
	if (*ptr == '\n') {
		_write(1, "\r\n", 2);
	} else {
		_write(1, ptr, 1);
	}
	// One character has been received.
	return 1;
}

