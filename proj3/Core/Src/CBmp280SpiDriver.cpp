/*
 * CBmp280SpiDriver.cpp
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#include "CBmp280SpiDriver.h"

CBmp280SpiDriver::CBmp280SpiDriver(SPI_HandleTypeDef *hspi, CGpioPin *ss) {
}

CBmp280SpiDriver::~CBmp280SpiDriver() {
	// TODO Auto-generated destructor stub
}

bool CBmp280SpiDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {
}

bool CBmp280SpiDriver::writeRegister(uint8_t address, uint8_t data) {
}
