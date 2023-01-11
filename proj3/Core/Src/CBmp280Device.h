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
};

#endif /* SRC_CBMP280DEVICE_H_ */
