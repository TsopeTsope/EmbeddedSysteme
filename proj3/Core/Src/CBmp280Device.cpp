/*
 * CBmp280Device.cpp
 *
 *  Created on: Jan 11, 2023
 *      Author: Ramses
 */

#include "CBmp280Device.h"
typedef long signed int BMP280_S32_t;
typedef long unsigned int BMP280_U32_t;
typedef long long signed int BMP280_S64_t;
BMP280_S32_t t_fine;

CBmp280Device::CBmp280Device(CBmp280LowLevelDriver *driver) {
	m_driver = driver;
}

float CBmp280Device::getPressure() {
	BMP280_S32_t adc_P = 0;
	uint8_t data[3];
	m_driver->readRegisters(0xF7, data, 3);
	adc_P = ((((adc_P|data[2])<<8)|data[1])<<8)|data[0];
	BMP280_S64_t var1, var2, p;
	var1 = ((BMP280_S64_t)t_fine) - 128000;
	var2 = var1 * var1 * (BMP280_S64_t)m_dig_P6;
	var2 = var2 + ((var1*(BMP280_S64_t)m_dig_P5)<<17);
	var2 = var2 + (((BMP280_S64_t)m_dig_P4)<<35);
	var1 = ((var1 * var1 * (BMP280_S64_t)m_dig_P3)>>8) + ((var1 * (BMP280_S64_t)m_dig_P2)<<12);
	var1 = (((((BMP280_S64_t)1)<<47)+var1))*((BMP280_S64_t)m_dig_P1)>>33;
	if (var1 == 0)
	{
	return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((BMP280_S64_t)m_dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((BMP280_S64_t)m_dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((BMP280_S64_t)m_dig_P7)<<4);
	return (BMP280_U32_t)p;
}

float CBmp280Device::getTemperature() {
	BMP280_S32_t adc_T = 0;
	uint8_t data[3];
	m_driver->readRegisters(0xFA, data, 3);
	adc_T = ((((adc_T|data[2])<<8)|data[1])<<8)|data[0];

	// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
	// t_fine carries fine temperature as global value
	BMP280_S32_t var1, var2, T;
	var1 = ((((adc_T>>3) - ((BMP280_S32_t)m_dig_T1<<1))) * ((BMP280_S32_t)m_dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((BMP280_S32_t)m_dig_T1)) * ((adc_T>>4) - ((BMP280_S32_t)m_dig_T1)))
	>> 12) *
	((BMP280_S32_t)m_dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

void CBmp280Device::getAll(float &pressure, float &temperature) {

}

void CBmp280Device::setMode(OperatingMode mode, StandByTime sbt) {
	uint8_t data = 0;
	m_driver->readRegisters(0xF5, &data, 1);
	switch(sbt){
	case SBT_0_5:
		m_driver->writeRegister(0xF5, (0b000<<5)|data);
		break;
	case SBT_1000:
		m_driver->writeRegister(0xF5, (0b101<<5)|data);
		break;
	case SBT_125:
		m_driver->writeRegister(0xF5, (0b010<<5)|data);
		break;
	case SBT_2000:
		m_driver->writeRegister(0xF5, (0b110<<5)|data);
		break;
	case SBT_250:
		m_driver->writeRegister(0xF5, (0b011<<5)|data);
		break;
	case SBT_4000:
		m_driver->writeRegister(0xF5, (0b111<<5)|data);
		break;
	case SBT_500:
		m_driver->writeRegister(0xF5, (0b100<<5)|data);
		break;
	case SBT_62_5:
		m_driver->writeRegister(0xF5, (0b001<<5)|data);
		break;
	default :
		break;
	}

	switch(mode){
	case UltralowPower:
		m_driver->writeRegister(0xF4, 0b00000010);
		break;
	case LowPower:
		m_driver->writeRegister(0xF4, 0b00100110);
		break;
	case StandardResolution:
		m_driver->writeRegister(0xF4, 0b01001011);
		break;
	case HighResolution:
		m_driver->writeRegister(0xF4, 0b01101111);
		break;
	case UltraHighResolution:
		m_driver->writeRegister(0xF4, 0b10010011);
		break;
	case Uninitialised:
		m_driver->writeRegister(0xF4, 0b10110111);
		break;
	default:
		break;
	}
}




