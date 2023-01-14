/*
 * CBmp280I2cDriver.h
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#ifndef SRC_CBMP280I2CDRIVER_H_
#define SRC_CBMP280I2CDRIVER_H_
#include "i2c.h"
#include "CBmp280LowLevelDriver.h"
#include "stm32f4xx_hal.h"

class CBmp280I2cDriver : public CBmp280LowLevelDriver {
public:
	CBmp280I2cDriver(I2C_HandleTypeDef* hi2c, uint8_t deviceAddress);
	virtual ~CBmp280I2cDriver();
	bool readRegisters(uint8_t startAddress, uint8_t* data, uint8_t bytes);
	bool writeRegister(uint8_t address, uint8_t data);
private:
	I2C_HandleTypeDef* m_hi2c;
	uint8_t m_deviceAddress;
};

#endif /* SRC_CBMP280I2CDRIVER_H_ */
