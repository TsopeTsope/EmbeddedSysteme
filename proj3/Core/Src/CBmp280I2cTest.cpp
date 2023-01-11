/*
 * CBmp280I2cTest.cpp
 *
 *  Created on: Jan 11, 2023
 *      Author: Ramses
 */

#include "CBmp280I2cTest.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include <sstream>
#include <string>

void CBmp280I2cTest::run() {
	const uint16_t bmp280Addr = 0b1110110;
	uint8_t idReg = 0xd0;
	uint8_t id = 0;

	HAL_I2C_Master_Transmit(&hi2c1, bmp280Addr<<1, &idReg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, bmp280Addr<<1, &id, 1, HAL_MAX_DELAY);


	std::stringstream strs;
	strs << id;
	std::string temp_str = strs.str();
	char* char_val = (char*) temp_str.c_str();

	//second method to transform int to string
	//char* char_val = (char*) &id;

	//third method with memcopy, string.h muss be included
//	char arr[sizeof(uint8_t)];
//	memcpy(buffer, &arr, sizeof(int));
//	char* char_val = arr;

	//fourth method using union
//	union {
//	    uint8_t i;
//	    char c[sizeof(int)];
//	} u;
//	u.i = id;
//	const char* char_val = u.c;


	// LCD Anzeige
//	tempAus.setCursor(0, 1);
//	tempAus.write(char_val);
//	tempAus.write("Grad");
//	HAL_Delay(30);
}
