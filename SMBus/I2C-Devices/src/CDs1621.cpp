/*
 * CDs1621.cpp
 *
 *  Created on: 17.07.2022
 *      Author: esy
 */

#include "CDs1621.h"
#include <iostream>
using namespace std;

CDs1621::CDs1621(std::string i2cBus, uint8_t slaveAddress)
: CI2cDevice ( i2cBus, slaveAddress) {
}

void CDs1621::setTL(float threshold) {

	// Variable zum setzen des Bits 8 des LSB des Temperaturewert
	uint8_t mask=0;

	// ganzzahlige Teil abholen
	int16_t entirePart = (int)threshold;

	// Abholung der Nachkommazahl
	float decimal = abs(threshold - (int)threshold);

	// Aufrundung oder Abrundung der Temperatur abhängig vom Nachkommawert
	if(decimal >= 0.75)
	{
		// addiert -1 wenn die Nachkommazahl negativ ist
		if( threshold < 0){
			entirePart = entirePart - 1;
		}
		// addiert 1 wenn die Nachkommazahl positiv ist
		else{
			entirePart = entirePart + 1;
		}
	}
	else if( (decimal >= 0.25) && (decimal < 0.75))
	{
		// maske zu setzen der Bit 8 der MSB der Register
		mask = 0x80;
	}
	else
	{
		// wenn decimal < 0,25 tun nicht
	}

	// Temperaturwert für die Registerdsrstellung vorbereiten und senden
	writeWord( 0xa2, ( entirePart << 8 ) | mask );
}

float CDs1621::getTL() {

	// register lesen
	int16_t registerValue = (int16_t)readWord(0xa2);

	// MSB abholen
	int8_t MSB_part = (registerValue >> 8);

	// LSB abholen
	uint8_t LSB_part =(uint8_t)registerValue;

	// wenn Nachkommazahl vorhanden
	if( LSB_part == 0x80 )
	{
		// Die Nachkommazahl hinzufügen und die Temperatur zurückgeben
		if( registerValue < 0){
			return MSB_part - 0.5;
		}
		else{
			return MSB_part + 0.5;
		}
	}

	//  Temperatur zurückgeben
	return MSB_part;
}

void CDs1621::setTH(float threshold) {

	// Variable zum setzen des Bits 8 des LSB des Temperaturewert
	uint8_t mask=0;

	// ganzzahlige Teil abholen
	int16_t entirePart = (int)threshold;

	// Abholung der Nachkommazahl
	float decimal = abs(threshold - (int)threshold);

	// Aufrundung oder Abrundung der Temperatur abhängig vom Nachkommawert
	if(decimal >= 0.75)
	{
		// addiert -1 wenn die Nachkommazahl negativ ist
		if( threshold < 0){
			entirePart = entirePart - 1;
		}
		// addiert 1 wenn die Nachkommazahl positiv ist
		else{
			entirePart = entirePart + 1;
		}
	}
	else if( (decimal >= 0.25) && (decimal < 0.75))
	{
		// maske zu setzen der Bit 8 der MSB der Register
		mask = 0x80;
	}
	else
	{
		// wenn decimal < 0,25 tun nicht
	}

	// Temperaturwert für die Registerdsrstellung vorbereiten und senden
	writeWord( 0xa1, ( entirePart << 8 ) | mask );
}

float CDs1621::getTH() {

	// register lesen
	int16_t registerValue = readWord(0xa1);

	// MSB abholen
	int8_t MSB_part = (registerValue >> 8);

	// LSB abholen
	uint8_t LSB_part =(uint8_t)registerValue;

	// wenn Nachkommazahl vorhanden
	if( LSB_part == 0x80 )
	{
		// Nachkommazahl hinzufügen und die Temperatur zurückgeben
		if( registerValue < 0){
			return MSB_part - 0.5;
		}
		else{
			return MSB_part + 0.5;
		}
	}

	//  Temperatur zurückgeben
	return MSB_part;
}

void CDs1621::setContinuousConversion(bool state) {

	// configuration register auslesen
	uint8_t configRegister = readByte(0xca);

	// Bit Nummer 1 ( 1SHOT ) des configuration register löschen
	if(state == true)
	{
		configRegister &= 0xfe;
	}
	else
	{
		// Bit Nummer 1 ( 1SHOT ) des configuration register setzen
		configRegister |= 0x01;
	}

	// schreieben in configuration register
	writeByte(0xac,configRegister);
}

bool CDs1621::getContinuousConversion() {

	// prüft ob der 1SHOT-Bit des configuration register gesetzt ist
	if((readByte(0xac) & (0x01)))
	{
		// Continuouse Conversion Mode ist nicht eingestellt.
		return false;
	}

	// Continuouse Conversion Mode ist eingestellt.
	return true;
}

void CDs1621::startConversion() {

	// conversion starten
	sendByte(0xee);
}

void CDs1621::stopConversion() {

	// conversion beenden
	sendByte(0x22);
}

float CDs1621::readTemperature() {

	// register lesen
	uint16_t registerValue = readWord(0xaa);

	// MSB abholen
	int8_t MSB_part = (registerValue >> 8);

	// LSB abholen
	uint8_t LSB_part =(uint8_t)registerValue;

	// Nachkommazahl vorhanden
	if( LSB_part == 0x80 )
	{
		// Die Nachkommazahl hinzufügen und die Temperatur zurückgeben
		if( registerValue < 0){
			return MSB_part - 0.5;
		}
		else{
			return MSB_part + 0.5;
		}
	}

	//  Temperatur zurückgeben
	return MSB_part;
}

float CDs1621::readTemperatureHR() {

	// TEMP_READ berechnen, indem die Temperatur gelesen wird und
	// die Nachkommazahl gelösch wird
	float TEMP_READ = (int8_t)readTemperature();

	// Wert für COUNT_REMAIN auslesen
	float COUNT_REMAIN = readByte(0xa8);

	// Wert für COUNT_PER_C auslesen
	float COUNT_PER_C = readByte(0xa9);

	// Temperature mit der Formel aus dem Dattenblatt berechnen
	return (TEMP_READ -0.25) + ( (COUNT_PER_C - COUNT_REMAIN)  / COUNT_PER_C);
}




