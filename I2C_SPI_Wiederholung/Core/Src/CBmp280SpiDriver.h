/*
 * CBmp280SpiDriver.h
 *
 *  Created on: Jan 13, 2023
 *      Author: User
 */
#include "CGpioPin.h"
#include "CBmp280LowLevelDriver.h"

#ifndef SRC_CBMP280SPIDRIVER_H_
#define SRC_CBMP280SPIDRIVER_H_

class CBmp280SpiDriver : public CBmp280LowLevelDriver{
private:
	CGpioPin* m_ss;
	SPI_HandleTypeDef* m_hspi;
public:
	CBmp280SpiDriver(SPI_HandleTypeDef* hspi,  CGpioPin* ss);
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

#endif /* SRC_CBMP280SPIDRIVER_H_ */
