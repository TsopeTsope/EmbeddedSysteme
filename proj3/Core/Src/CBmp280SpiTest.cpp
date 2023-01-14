/*
 * CBmp280SpiTest.cpp
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#include "CBmp280SpiTest.h"
#include <sstream>
#include <string>
#include "CLcd1602.h"
#include "iostream"
#include "spi.h"
#include "dma.h"
#include "stm32f4xx_hal.h"
#include "CBmp280SpiDriver.h"
#include "CBmp280I2cDriver.h"

void CBmp280SpiTest::run() {


		CGpioPin rs(GPIOD, 2);
			CGpioPin enable(GPIOC, 9);
			CGpioBus dataBus = CGpioBus().addPin(GPIOA, 1<<11).addPin(GPIOA, 1<<12)
					.addPin(GPIOB, 1<<1).addPin(GPIOB, 1<<2);
			CLcd1602 tempAus(&rs, &enable, &dataBus);
			tempAus.init();

			// LED Board
			CGpioPin boardLED(GPIOA, 5);
			boardLED.setState(true);

			// SPI
			CGpioPin SS(GPIOB, 12);

			// id Register
			uint8_t idReg = 0xd0;
			uint8_t id = 0;

			CBmp280SpiDriver spielem(&hspi2, &SS);

			while(1)
			{
				//SS = 0;
//				HAL_SPI_Transmit(&hspi2, &idReg, 1, HAL_MAX_DELAY);
//				HAL_SPI_Receive(&hspi2, &id, 1, HAL_MAX_DELAY);

				//SS= 1;
				spielem.readRegisters(idReg, &id, 1);
				std::cout << "Id-Register: " << (uint16_t)id << "\r\n";

				// int to char*
				uint16_t id16 = (uint16_t)id;
				std::stringstream strs;
				strs << id16;
				std::string temp_str = strs.str();
				char* char_id = (char*) temp_str.c_str();

				// LCD
				tempAus.setCursor(0, 10);
				tempAus.write(char_id);
				HAL_Delay(10);
			}
}
