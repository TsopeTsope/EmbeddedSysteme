/*
 * CDs1621.h
 *
 *  Created on: 17.07.2022
 *      Author: esy
 */

#include "CI2cDevice.h"

#ifndef CDS1621_H_
#define CDS1621_H_

class CDs1621 : public CI2cDevice {
public:
	CDs1621(std::string  i2cBus, uint8_t slaveAddress);
	void setTL(float threshold);
	float getTL();
	void setTH(float threshold);
	float getTH();
	void setContinuousConversion(bool state);
	bool getContinuousConversion();
	void startConversion();
	void stopConversion();
	float readTemperature();
	float readTemperatureHR();
};

#endif /* CDS1621_H_ */
