/*
 * CSensorDataDisplay.cpp
 *
 *  Created on: 14.01.2023
 *      Author: User
 */

#include "CSensorDataDisplay.h"
#include "CGpioPin.h"
#include "CBmp280LowLevelDriver.h"
#include "CBmp280Device.h"
#include "spi.h"
#include <iostream>
#include "CLcd1602.h"
#include "CGpioBus.h"
#include "CBmp280SpiDriver.h"
#include "CBmp280I2cDriver.h"
#include <string>
#include <sstream>

void CSensorDataDisplay::run() {
	// LCD
	CGpioPin rs(GPIOD, 2);
	CGpioPin enable(GPIOC, 9);
	CGpioBus dataBus = CGpioBus().addPin(GPIOA, 1<<11).addPin(GPIOA, 1<<12)
					.addPin(GPIOB, 1<<1).addPin(GPIOB, 1<<2);
	CLcd1602 tempAus(&rs, &enable, &dataBus);
	tempAus.init();

	// SPI & I2C
	CGpioPin SS(GPIOB, 12);
	CBmp280SpiDriver spiDriver(&hspi2, &SS);
	CBmp280I2cDriver i2cDriver(&hi2c1, 0x76);
	CBmp280Device device(&i2cDriver);

	// Forced Mode
	device.setMode(device.UltraLowPower, device.STB_1000);
	float temp = 0;
	float press = 0;
	device.getAll(press, temp);
	std::cout << "Temp: " << temp << "        press: " << press << "\r\n";

	// next Time Measurment
	uint64_t nextMeasurmentTime = HAL_GetTick() + 1500;

	while(true)
	{
		if (nextMeasurmentTime <= HAL_GetTick()) {

			// Messung
			device.setMode(device.UltraHighResolution, device.STB_0_5);
			device.getAll(press, temp);
			std::cout << "Temp: " << (uint16_t)temp << "        press: " << (uint16_t)press << "\r\n";

			// pressure... int to char*
			uint16_t pe = (uint16_t)press;
			std::stringstream strs_p;
			strs_p << pe;
			std::string press_str = strs_p.str();
			char* char_press = (char*) press_str.c_str();

			// temperatur... int to char*
			uint16_t te = (uint16_t)temp;
			std::stringstream strs_t;
			strs_t << te;
			std::string temp_str = strs_t.str();
			char* char_temp = (char*) temp_str.c_str();

			// LCD Temperatur
			tempAus.setCursor(0, 1);
			tempAus.write("Temp: ");
			tempAus.write(char_temp);
			HAL_Delay(10);

			// LCD Pressure
			tempAus.setCursor(1, 1);
			tempAus.write("Press: ");
			tempAus.write(char_press);
			HAL_Delay(10);
		}
	}
}
