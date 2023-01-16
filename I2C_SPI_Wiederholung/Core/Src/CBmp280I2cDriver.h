/*
 * CBmp280I2cDriver.h
 *
 *  Created on: Jan 13, 2023
 *      Author: User
 */

#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "CBmp280LowLevelDriver.h"

#ifndef SRC_CBMP280I2CDRIVER_H_
#define SRC_CBMP280I2CDRIVER_H_

class CBmp280I2cDriver : public CBmp280LowLevelDriver {
private:
	I2C_HandleTypeDef* m_hi2c;
	uint8_t m_deviceAdress;
public:
	CBmp280I2cDriver(I2C_HandleTypeDef* hi2c, uint8_t deviceAdress);
	/**
	 * Schreibt einen Wert in ein Register des BMP280.
	 *
	 * @param address Adresse des Registers, in das der Wert
	 * 	geschrieben werden soll
	 * @param data der in das Register zu schreibende Wert
	 * @return true, wenn der Vorgang erfolgreich war
	 */
	bool writeRegister(uint8_t address, uint8_t data);

	/**
	 * Liste die Werte aus einer Folge von Registern in den übergebenen
	 * Puffer. Implementierungen dieser Schnittstelle müssen das Lesen
	 * als Burst-Read (vergl. Datenblatt) implementieren.
	 *
	 * @param startAddress Adresse des als erstes zu lesenden Registers
	 * @param data Zeiger auf den Puffer, in den die gelesenen Daten
	 *  geschrieben werden sollen
	 * @param bytes Anzahl zu lesender Wert (d.h. Register)
	 * @return true, wenn der Vorgang erfolgreich war
	 */
	bool readRegisters(
			uint8_t startAddress, uint8_t* data, uint8_t bytes);
};

#endif /* SRC_CBMP280I2CDRIVER_H_ */
