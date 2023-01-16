/*
 * CI2cDevice.cpp
 *
 *  Created on: 17.07.2022
 *      Author: esy
 */

#include "CI2cDevice.h"
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

CI2cDevice::CI2cDevice(std::string i2cBus, uint8_t slaveAddress) {

	// initialisation der Attribute
	m_bus = i2cBus;
	m_slave_address = slaveAddress;

	// datei öffenen und prüfen ob es erfolgreich ist
	m_fd = open (m_bus.c_str(), O_RDWR);
	if(m_fd < 0)
	{
		// Ausgabe der Fehlermeldung und Programm schließen
		printf("Datei öffnen fehlgeschlagen\n");
		exit(1);
	}

	// Adresse der I2cSlave einstellen
	int res = ioctl(m_fd, I2C_SLAVE, m_slave_address);
	if(res < 0)
	{
		// Ausgabe der Fehlermeldung und Programm schließen
		printf("Verbindung nicht erfolgreich\n");
		exit(1);
	}
}

CI2cDevice::~CI2cDevice() {

	// File descriptor Schließen
	if(close(m_fd) < 0 )
	{
		printf("Schließen der File descriptor nicht erfolgreich.\n");
		exit(1);
	}
}

void CI2cDevice::sendByte(uint8_t data) {

	// Schreibt 1 Byte in der File descriptor
	if( write(m_fd, &data, 1) != 1 )
	{
		// wenn der gesendete Datenlänge != 1, programm unterbrechen
		printf("Byte-Transmission nicht erfolgreich\n");
		exit(1);
	}
}

uint8_t CI2cDevice::receiveByte() {

	// Puffer für die gelesenen Wert.
	uint8_t puffer;

	// liest 1 Byte aus der File descriptor und prüft ob es erfolgreich war.
	if( read(m_fd, &puffer, 1) != 1 )
	{
		// Ausgabe der Fehlermeldung
		printf("Byte-Lesevorgang nicht erfolgreich\n");
		return -1;
	}

	// Ausgelesene Wert zurückgeben
	return puffer;
}

void CI2cDevice::writeByte(uint8_t commandCode, uint8_t data) {

	// Puffer für die Schreibdaten.
	uint8_t puffer [2]= {commandCode, data};

	// Schreibt Bytes in der File descriptor
	if( write(m_fd, puffer, 2 ) != 2 )
	{
		// Ausgabe der Fehlermeldung
		printf("Byte-Transmission nicht erfolgreich\n");
	}
}

uint8_t CI2cDevice::readByte(uint8_t commandCode) {

	// Command Code senden und Daten empfangen
	sendByte(commandCode);
	return receiveByte();
}

void CI2cDevice::writeWord(uint8_t commandCode, uint16_t data) {

	// Puffer für die Schreibdaten.
	uint8_t puffer [3] ={0};

	// Command Code hinzufügen
	puffer[0] = commandCode;

	// MSB hinzufügen
	puffer[1] = data >> 8 ;

	//LSB hinzufügen
	puffer[2] = data ;

	// Schreibt Bytes in der File descriptor
	if( write(m_fd, puffer, 3) != 3 )
	{
		// Ausgabe der Fehlermeldung
		printf("Word-Transmission nicht erfolgreich\n");
	}
}

uint16_t CI2cDevice::readWord(uint8_t commandCode) {

	// Puffer für die gelesenen Wert.
	uint8_t puffer[2] ;

	// Command code senden
	sendByte(commandCode);

	// Auslesen von Bytes aus der File descriptor
	if(read(m_fd, puffer,2 ) != 2)
	{
		// Ausgabe der Fehlermeldung
		printf("Word-Lesevorgang nicht erfolgreich\n");
		return -1;
	}

	// MSB von puffer == LSB von data ( data ist die Temperature)
	// LSB von puffer == MSB von data ( data ist die Temperature)
	uint16_t data = (puffer[0] << 8) | puffer[1] ;

	// ausgelesenen Wert
	return data;
}



