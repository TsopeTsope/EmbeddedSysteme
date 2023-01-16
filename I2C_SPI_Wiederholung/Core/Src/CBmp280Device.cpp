/*
 * CBmp280Device.cpp
 *
 *  Created on: Jan 13, 2023
 *      Author: User
 */

#include "CBmp280Device.h"

CBmp280Device::CBmp280Device(CBmp280LowLevelDriver* driver) {
	m_driver = driver;
	uint8_t adc[24];
	m_driver->readRegisters(0x88, adc, 24);
	m_dig_T1 = (adc[1] << 8) | adc[0];
	m_dig_T2 = (adc[3] << 8) | adc[2];
	m_dig_T3 = (adc[5] << 8) | adc[4];
	m_dig_P1 = (adc[7] << 8) | adc[6];
	m_dig_P2 = (adc[9] << 8) | adc[8];
	m_dig_P3 = (adc[11] << 8) | adc[10];
	m_dig_P4 = (adc[13] << 8) | adc[12];
	m_dig_P5 = (adc[15] << 8) | adc[14];
	m_dig_P6 = (adc[17] << 8) | adc[16];
	m_dig_P7 = (adc[19] << 8) | adc[18];
	m_dig_P8 = (adc[21] << 8) | adc[20];
	m_dig_P9 = (adc[23] << 8) | adc[22];
	m_t_fine = 0;
}

float CBmp280Device::getPressure() {

	getTemperature();

	uint8_t adc[] = {0, 0, 0};
	m_driver->readRegisters(0xf7, adc, 3);
	BMP280_S32_t adc_P = (adc[2] | (adc[1] << 8) | (adc[0] << 16)) >> 4;

	BMP280_S64_t var1, var2, p;
	var1 = ((BMP280_S64_t)m_t_fine) - 128000;
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
	return (float)(((BMP280_U32_t)p)/256/100);
}

float CBmp280Device::getTemperature() {

	uint8_t adc[] = {0, 0, 0};
	m_driver->readRegisters(0xfa, adc, 3);
	BMP280_S32_t adc_T = (adc[2] | (adc[1] << 8) | (adc[0] << 16)) >> 4;

	BMP280_S32_t var1, var2, T;
	var1 = ((((adc_T>>3) - ((BMP280_S32_t)m_dig_T1<<1))) * ((BMP280_S32_t)m_dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((BMP280_S32_t)m_dig_T1)) * ((adc_T>>4) - ((BMP280_S32_t)m_dig_T1)))
			>> 12) *
			((BMP280_S32_t)m_dig_T3)) >> 14;
	m_t_fine = var1 + var2;
	T = (m_t_fine * 5 + 128) >> 8;
	return (float)T/100;
}

void CBmp280Device::getAll(float &pressure, float &temperature) {
	pressure = getPressure();
	temperature = getTemperature();
}

void CBmp280Device::setMode(OperatingMode mode, StandbyTime sbt) {
	uint8_t ctrl_meas;
	// 7,6,5 Bit, Temperatur
	uint8_t osrs_t = mode << 5;
	// 4,3,2 Bit, perssure
	uint8_t osrs_p = mode << 2;
	// 1,0 Bit, Mode
	uint8_t powerMode = 3;
	if(mode == UltraLowPower)
		powerMode = 2;

	// Operating Mode
	ctrl_meas = osrs_t|osrs_p|powerMode;
	m_driver->writeRegister(0xf4, ctrl_meas);

	// Standby Time
	uint8_t config = 0;
	m_driver->readRegisters(0xf5, &config, 1);
	config = (sbt << 5)|(config & 0b00011111);
	m_driver->writeRegister(0xf5, config);
}
