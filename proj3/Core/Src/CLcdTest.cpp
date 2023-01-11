/*
 * CLcdTest.cpp
 *
 *  Created on: Dec 27, 2022
 *      Author: User
 */

#include "CLcdTest.h"
#include "CLcd1602.h"
#include "CGpioPin.h"

void CLcdTest::run() {

	CGpioPin rs(GPIOD, 2);
	CGpioPin enable(GPIOC, 9);

	CGpioBus dataBus = CGpioBus().addPin(GPIOA, 1<<11).addPin(GPIOA, 1<<12).addPin(GPIOB, 1<<1).addPin(GPIOB, 1<<2);


	CLcd1602 test(&rs, &enable, &dataBus);
	test.init();

	while(true){
		// Cursor legen und dann schreiben
		test.setCursor(0, 2);
		test.write("Ramses");
		HAL_Delay(700);

		// Cursor legen und dann schreiben
		test.setCursor(0, 9);
		test.write("Kouetsa");
		HAL_Delay(700);

		// Cursor legen und dann schreiben
		test.setCursor(1, 4);
		test.write("758326");
		HAL_Delay(200000);
	}
}
