/*
 * CBmp280SpiDriver.h
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#ifndef SRC_CBMP280SPIDRIVER_H_
#define SRC_CBMP280SPIDRIVER_H_
#include "spi.h"
#include "CBmp280LowLevelDriver.h"
#include "CGpioPin.h"

class CBmp280SpiDriver : public CBmp280LowLevelDriver {
public:
	CBmp280SpiDriver(SPI_HandleTypeDef* hspi, CGpioPin* ss);
	virtual ~CBmp280SpiDriver();
	bool readRegisters(uint8_t startAddress, uint8_t* data, uint8_t bytes);
	bool writeRegister(uint8_t address, uint8_t data);

private:
	SPI_HandleTypeDef* m_hspi;
	CGpioPin* m_ss;
};

#endif /* SRC_CBMP280SPIDRIVER_H_ */
