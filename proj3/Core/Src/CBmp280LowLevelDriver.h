/*
 * CBmp280LowLevelDriver.h
 *
 *  Created on: Jan 11, 2023
 *      Author: Ramses
 */

#ifndef SRC_CBMP280LOWLEVELDRIVER_H_
#define SRC_CBMP280LOWLEVELDRIVER_H_
#include "stm32f4xx_hal.h"

class CBmp280LowLevelDriver {
public:
	virtual bool readRegisters(uint8_t startAddress, uint8_t *data, uint8_t bytes);
	virtual bool writeRegister(uint8_t address, uint8_t data);
};

#endif /* SRC_CBMP280LOWLEVELDRIVER_H_ */
