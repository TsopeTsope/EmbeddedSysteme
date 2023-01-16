/*
 * CI2cDevice.h
 *
 *  Created on: 17.07.2022
 *      Author: esy
 */

#include <string>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef CI2CDEVICE_H_
#define CI2CDEVICE_H_

class CI2cDevice {
private:
	std::string m_bus;
	uint8_t m_slave_address;
	int m_fd;

public:
	/**
	 * initialisiert der Bus und verbibndet die Slave
	 *
	 * @param i2cBus
	 * @param slaveAddress Adresse der Slave
	 * */
	CI2cDevice(std::string  i2cBus, uint8_t slaveAddress);

	/**
	 * destructor
	 * */
	~CI2cDevice();

	/**
	 * die Methode sendet 1 Byte-Data an der Slave
	 *
	 * @param data daten zu senden
	 * */
	void sendByte(uint8_t data);


	/**
	 * die Methode liest 1 Byte-Data aus der Register aus und gibt es zurück.
	 *
	 * @return 1 Byte-daten
	 * */
	uint8_t receiveByte();


	/**
	 * die Methode sendet 1 Byte-Data an der Slave mit Berücksichtigung des
	 *  Command-Code
	 *
	 * @param commandCode Command-Code zu durchführen
	 * @param data daten zu senden
	 * */
	void writeByte(uint8_t commandCode, uint8_t data);

	/**
	 * die Methode liest 1 Byte-Data aus ein Register mit Berücksichtigung des
	 * Command-Code und gibt der Inhalt zurück.
	 *
	 * @param commandCode Command-Code zu durchführen
	 * @param data daten zu senden
	 * @return ausgelesenen Wert
	 * */
	uint8_t readByte(uint8_t commandCode);

	/**
	 * die Methode sendet 1 Word-Data an der Slave mit Berücksichtigung des
	 *  Command-Code
	 *
	 * @param commandCode Command-Code zu durchführen
	 * @param data daten zu senden
	 * */
	void writeWord(uint8_t commandCode, uint16_t data);

	/**
	 * die Methode liest 1 Word(2 Bytes)-Data aus file mit
	 * Berücksichtigung des Command-Code und gibt der Inhalt zurück.
	 *
	 * @param commandCode Command-Code zu durchführen
	 * @param data daten zu senden
	 * @return ausgelesenen Wert
	 * */
	uint16_t readWord(uint8_t commandCode);
};

#endif /* CI2CDEVICE_H_ */
