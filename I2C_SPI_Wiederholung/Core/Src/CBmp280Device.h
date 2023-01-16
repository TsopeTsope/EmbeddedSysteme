/*
 * CBmp280Device.h
 *
 *  Created on: Jan 13, 2023
 *      Author: User
 */
#include "CBmp280LowLevelDriver.h"

typedef long unsigned int BMP280_U32_t;
typedef long signed int BMP280_S32_t;
typedef long long signed int BMP280_S64_t;

#ifndef SRC_CBMP280DEVICE_H_
#define SRC_CBMP280DEVICE_H_

class CBmp280Device {
private:
	CBmp280LowLevelDriver* m_driver;
	unsigned short m_dig_T1;
	signed short m_dig_T2;
	signed short m_dig_T3;
	unsigned short m_dig_P1;
	signed short m_dig_P2;
	signed short m_dig_P3;
	signed short m_dig_P4;
	signed short m_dig_P5;
	signed short m_dig_P6;
	signed short m_dig_P7;
	signed short m_dig_P8;
	signed short m_dig_P9;
	BMP280_S32_t m_t_fine;
public:
	enum OperatingMode{
		// x0
		Uninitialized       = 0, // 0b000
		// x1
		UltraLowPower       = 1, // 0b001
		// x2
		LowPower            = 2,
		// x4
		StandardResolution  = 3,
		// x8
		HighResolution      = 4,
		// x16
		UltraHighResolution = 5
	};
	enum StandbyTime{
		STB_0_5    = 0,
		STB_62_5,
		STB_125,
		STB_250,
		STB_500,
		STB_2000,
		STB_1000,
		STB_4000
	};

	CBmp280Device(CBmp280LowLevelDriver* driver);
	float getPressure();
	float getTemperature();
	void getAll(float& pressure, float& temperature);
	void setMode(OperatingMode mode, StandbyTime sbt);
};

#endif /* SRC_CBMP280DEVICE_H_ */
