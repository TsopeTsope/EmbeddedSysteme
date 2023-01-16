/*
 * CBmp280I2cTest.cpp
 *
 *  Created on: Jan 11, 2023
 *      Author: User
 */

#include "CBmp280I2cDriver.h"
#include "CBmp280I2cTest.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include <iostream>
#include <sstream>
#include "CLcd1602.h"
#include <string.h>
#include "dma.h"
#include "CBmp280Device.h"

void CBmp280I2cTest::run() {
	CGpioPin rs(GPIOD, 2);
	CGpioPin enable(GPIOC, 9);
	CGpioBus dataBus = CGpioBus().addPin(GPIOA, 1<<11).addPin(GPIOA, 1<<12)
			.addPin(GPIOB, 1<<1).addPin(GPIOB, 1<<2);
	CLcd1602 tempAus(&rs, &enable, &dataBus);
	tempAus.init();

	// LED Board
	CGpioPin boardLED(GPIOA, 5);

	// SPI
	CGpioPin SS(GPIOB, 12);

	// id Register
	const uint8_t bmp280Addr = 0b1110110;
	uint8_t idReg = 0xd0;
	uint8_t id = 0;

	// test
	CBmp280I2cDriver Bmp280I2cDriver(&hi2c1, bmp280Addr);


	while(1)
	{
		boardLED = true;

		// Polling
//		HAL_I2C_Master_Seq_Transmit(&hi2c1, bmp280Addr<<1, &idReg, 1, HAL_MAX_DELAY);
//		HAL_I2C_Master_Receive(&hi2c1, bmp280Addr<<1, &id, 1, HAL_MAX_DELAY);

//		// DMA
//		HAL_I2C_Master_Seq_Transmit_DMA(&hi2c1, bmp280Addr<<1, (uint8_t*)&idReg, 1, I2C_FIRST_FRAME);
//		while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){
//		}
//		HAL_I2C_Master_Seq_Receive_DMA(&hi2c1, bmp280Addr<<1, (uint8_t*)&id, 1, I2C_LAST_FRAME);
//		while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){
//		}

		Bmp280I2cDriver.readRegisters(idReg, &id, 1);

//		boardLED = false;

		// Id Konsolenausgabe
		std::cout << "Id-Register: " << (uint16_t)id << "\r\n";

		// int to char*
		uint16_t id16 = (uint16_t)id;
		std::stringstream strs;
		strs << id16;
		std::string temp_str = strs.str();
		char* char_id = (char*) temp_str.c_str();

		// LCD
		tempAus.setCursor(1, 2);
		tempAus.write(char_id);
		HAL_Delay(10);
	}
}

