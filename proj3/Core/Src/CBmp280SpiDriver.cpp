/*
 * CBmp280SpiDriver.cpp
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#include "CBmp280SpiDriver.h"
#include "spi.h"

CBmp280SpiDriver::CBmp280SpiDriver(SPI_HandleTypeDef *hspi, CGpioPin *ss) {
	m_hspi = hspi;
	m_ss = ss;
}

CBmp280SpiDriver::~CBmp280SpiDriver() {
	// TODO Auto-generated destructor stub
}

bool CBmp280SpiDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {
	*m_ss = 0;
	if (HAL_SPI_Transmit(m_hspi, &startAddress, 1, HAL_MAX_DELAY)!= HAL_OK){
		return false;
			}
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){}

	if (HAL_SPI_Receive(m_hspi, data, bytes, HAL_MAX_DELAY)!=HAL_OK){
		return false;
		}
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){}
	*m_ss = 1;
		return true;
}

bool CBmp280SpiDriver::writeRegister(uint8_t address, uint8_t data) {
	*m_ss = 0;
	if (HAL_SPI_Transmit(m_hspi, &address, 1, HAL_MAX_DELAY)!= HAL_OK){
		return false;
		}
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){}

	if (HAL_SPI_Transmit(m_hspi, &data, 1, HAL_MAX_DELAY)!= HAL_OK){
		return false;
		}
	while(HAL_SPI_GetState(m_hspi) != HAL_SPI_STATE_READY){}
	*m_ss = 1;
		return true;
}
