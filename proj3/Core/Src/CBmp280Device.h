/*
 * CBmp280Device.h
 *
 *  Created on: Jan 11, 2023
 *      Author: Ramses
 */

#ifndef SRC_CBMP280DEVICE_H_
#define SRC_CBMP280DEVICE_H_
#include "CBmp280LowLevelDriver.h"

class CBmp280Device {
public:
	enum OperatingMode{
		HighResolution,
		LowPower,
		StandardResolution,
		UltraHighResolution,
		UltralowPower,
		Uninitialised
	};
	enum StandByTime{
		SBT_0_5,
		SBT_1000,
		SBT_125,
		SBT_2000,
		SBT_250,
		SBT_4000,
		SBT_500,
		SBT_62_5
	};
	CBmp280Device(CBmp280LowLevelDriver* driver);
	float getPressure();
	float getTemperature();
	void getAll(float&pressure, float& temperature);
	void setMode(OperatingMode mode, StandByTime sbt);


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
};

#endif /* SRC_CBMP280DEVICE_H_ */
