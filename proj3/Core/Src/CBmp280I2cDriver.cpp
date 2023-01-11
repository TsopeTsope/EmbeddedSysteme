/*
 * CBmp280I2cDriver.cpp
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#include "CBmp280I2cDriver.h"



CBmp280I2cDriver::CBmp280I2cDriver(I2C_HandleTypeDef *hi2c,
		uint8_t deviceAddress) {
}

CBmp280I2cDriver::~CBmp280I2cDriver() {
	// TODO Auto-generated destructor stub
}

bool CBmp280I2cDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {
}

bool CBmp280I2cDriver::writeRegister(uint8_t address, uint8_t data) {
}
