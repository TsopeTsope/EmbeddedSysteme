/*
 * CUartLoad.cpp
 *
 *  Created on: Dec 29, 2022
 *      Author: User
 */

#include "CUartLoad.h"
#include <string>
#include "usart.h"
#include <sstream>

#include <iostream>

void CUartLoad::run() {
	uint32_t nextCheckAt = HAL_GetTick() + 1000;
	uint32_t counter = 0;
	std::string text = "Loops per second: 0\r\n";
	while(true)
	{
		// Pollin
//		HAL_UART_Transmit(&huart2, (uint8_t*) text.c_str(), text.size() , HAL_MAX_DELAY);

		// Interrupt
//		HAL_UART_Transmit_IT(&huart2, (uint8_t*) text.c_str(), text.size());

		// DMA
		HAL_UART_Transmit_DMA(&huart2, (uint8_t*) text.c_str(), text.size());
		counter++;
		if( HAL_GetTick() >= nextCheckAt )
		{
//			std::stringstream temp;
//			temp << "Loops per  : " << counter << "\r\n";
//			text = temp.str();

			text = "Loops per second: " + std::to_string(counter) + "\r\n";
		    counter = 0;
		    nextCheckAt = HAL_GetTick() + 1000;
		}
	}
}
