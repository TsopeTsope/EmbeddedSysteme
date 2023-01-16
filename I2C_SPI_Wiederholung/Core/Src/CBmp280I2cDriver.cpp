/*
 * CBmp280I2cDriver.cpp
 *
 *  Created on: Jan 13, 2023
 *      Author: User
 */

#include "CBmp280I2cDriver.h"

CBmp280I2cDriver::CBmp280I2cDriver(I2C_HandleTypeDef *hi2c, uint8_t deviceAdress){
	m_hi2c = hi2c;
	m_deviceAdress = deviceAdress;
}

bool CBmp280I2cDriver::writeRegister(uint8_t address, uint8_t data) {

	if( HAL_I2C_Master_Seq_Transmit_DMA(&hi2c1, m_deviceAdress<<1, (uint8_t*)&address, 1, I2C_FIRST_FRAME) != HAL_OK )
		return false;
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){
	}

	if( HAL_I2C_Master_Seq_Transmit_DMA(&hi2c1, m_deviceAdress<<1, (uint8_t*)&data, 1, I2C_FIRST_FRAME) != HAL_OK )
		return false;
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){
	}
	return true;
}

bool CBmp280I2cDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {

	if( HAL_I2C_Master_Seq_Transmit_DMA(&hi2c1, m_deviceAdress<<1, (uint8_t*)&startAddress, 1, I2C_FIRST_FRAME) != HAL_OK )
		return false;
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){
	}

	if( HAL_I2C_Master_Seq_Receive_DMA(&hi2c1, m_deviceAdress<<1, (uint8_t*)data, bytes, I2C_LAST_FRAME)!= HAL_OK )
		return false;
	while(HAL_I2C_GetState(m_hi2c) != HAL_I2C_STATE_READY){
	}
	return true;
}
