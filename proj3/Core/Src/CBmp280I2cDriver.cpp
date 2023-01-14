/*
 * CBmp280I2cDriver.cpp
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#include "CBmp280I2cDriver.h"



CBmp280I2cDriver::CBmp280I2cDriver(I2C_HandleTypeDef *hi2c,
		uint8_t deviceAddress) {
	m_hi2c = hi2c;
	m_deviceAddress = deviceAddress;
}

CBmp280I2cDriver::~CBmp280I2cDriver() {
	// TODO Auto-generated destructor stub
}

bool CBmp280I2cDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {
	if (HAL_I2C_Master_Transmit(m_hi2c, m_deviceAddress<<1, &startAddress, 1, HAL_MAX_DELAY)!=HAL_OK){
		return false;
		}
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){}
	if (HAL_I2C_Master_Receive(m_hi2c, m_deviceAddress<<1, data, bytes, HAL_MAX_DELAY)!=HAL_OK){
		return false;
	}
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){}
	return true;
}

bool CBmp280I2cDriver::writeRegister(uint8_t address, uint8_t data) {
	if (HAL_I2C_Master_Transmit(m_hi2c, m_deviceAddress<<1, &address, 1, HAL_MAX_DELAY)!= HAL_OK){
		return false;
	}
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){}
	if (HAL_I2C_Master_Transmit(m_hi2c, m_deviceAddress<<1, &data, 1, HAL_MAX_DELAY)!= HAL_OK){
		return false;
		}
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){}
	return true;
}
