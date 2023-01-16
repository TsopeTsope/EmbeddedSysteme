/*
 * CBmp280SpiTest.cpp
 *
 *  Created on: Jan 13, 2023
 *      Author: User
 */
#include "CBmp280SpiDriver.h"
#include "CBmp280SpiTest.h"
#include "stm32f4xx_hal.h"
#include "spi.h"
#include <iostream>
#include <sstream>
#include "CLcd1602.h"
#include <string.h>
#include "dma.h"

void CBmp280SpiTest::run() {

	CGpioPin rs(GPIOD, 2);
	CGpioPin enable(GPIOC, 9);
	CGpioBus dataBus = CGpioBus().addPin(GPIOA, 1<<11).addPin(GPIOA, 1<<12)
			.addPin(GPIOB, 1<<1).addPin(GPIOB, 1<<2);
	CLcd1602 tempAus(&rs, &enable, &dataBus);
	tempAus.init();

	// SPI
	CGpioPin SS(GPIOB, 12);

//	// id Register
	uint8_t idReg = 0xd0;
	uint8_t id = 0;

	// Parameter für gleichzeitiges Senden und Empfangen
//	uint8_t out[2] = {0xd0, 0};
//	uint8_t in[2] = {0, 0};

	CBmp280SpiDriver bmp280SpiDriver(&hspi2, &SS);

	while(1)
	{
//		// Einzelaktion
//		SS = 0;
//		HAL_SPI_Transmit(&hspi2, &idReg, 1, HAL_MAX_DELAY);
//		HAL_SPI_Receive(&hspi2, &id, 1, HAL_MAX_DELAY);
//		SS = 1;

		// gleichzeitiges Senden und Empfangen
//		SS = 0;
//		HAL_SPI_TransmitReceive(&hspi2, out, in, 2, HAL_MAX_DELAY);
//		SS = 1;
//		uint16_t in0 = (uint16_t)in[0];
//		uint16_t in1 = (uint16_t)in[1];

		bmp280SpiDriver.readRegisters(idReg, &id, 1);

		// Id Konsolenausgabe
//		std::cout << "Id-Register: " << (uint16_t)in0 <<
//				"   " << (uint16_t)in1 << "\r\n";

		std::cout << "Id-Register: " << (uint16_t)id << "\r\n";

		// int to char*
		uint16_t id16 = (uint16_t)id;
		std::stringstream strs;
		strs << id16;
		std::string temp_str = strs.str();
		char* char_id = (char*) temp_str.c_str();

		// LCD
		tempAus.setCursor(0, 12);
		tempAus.write(char_id);
		HAL_Delay(10);
	}
}
