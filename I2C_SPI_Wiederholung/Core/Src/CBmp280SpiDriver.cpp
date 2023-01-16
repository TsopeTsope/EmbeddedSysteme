/*
 * CBmp280SpiDriver.cpp
 *
 *  Created on: Jan 13, 2023
 *      Author: User
 */

#include "CBmp280SpiDriver.h"
#include "spi.h"
#include "stm32f4xx_hal.h"

CBmp280SpiDriver::CBmp280SpiDriver(SPI_HandleTypeDef* hspi,  CGpioPin* ss) {
	m_ss = ss;
	m_hspi = hspi;
}

bool CBmp280SpiDriver::writeRegister(uint8_t address, uint8_t data) {

	*m_ss = 0;
	if(HAL_SPI_Transmit(m_hspi, &address, 1, HAL_MAX_DELAY) != HAL_OK)
		return false;
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){
	}

	if(HAL_SPI_Transmit(m_hspi, &data, 1, HAL_MAX_DELAY) != HAL_OK)
		return false;
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){
	}
	*m_ss = 1;

	return true;
}

bool CBmp280SpiDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {

	*m_ss = 0;
	if(HAL_SPI_Transmit(m_hspi, &startAddress, 1, HAL_MAX_DELAY) != HAL_OK)
		return false;
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){
	}

	if(HAL_SPI_Receive(m_hspi, data, bytes, HAL_MAX_DELAY) != HAL_OK)
		return false;
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){
	}
	*m_ss = 1;

	return true;
}
