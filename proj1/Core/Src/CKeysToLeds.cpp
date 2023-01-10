/*
 * CKeysToLeds.cpp
 *
 *  Created on: 26.12.2022
 *      Author: User
 */

#include "CKeysToLeds.h"
#include "CGpioBus.h"

void CKeysToLeds::run() {

	CGpioBus ledBus = CGpioBus().addPin(GPIOC, 1 << 0).addPin(GPIOC, 1 << 1).
			addPin(GPIOC, 1 << 2).addPin(GPIOC, 1 << 3).addPin(GPIOC, 1 << 4).
			addPin(GPIOC, 1 << 5).addPin(GPIOC, 1 << 6).addPin(GPIOC, 1 << 7);

	CGpioBus buttBus = CGpioBus().addPin(GPIOA, 1 << 4).addPin(GPIOA, 1 << 1).
			addPin(GPIOA, 1 << 0).addPin(GPIOB, 1 << 7).addPin(GPIOA, 1 << 15).
			addPin(GPIOC, 1 << 12).addPin(GPIOC, 1 << 11).addPin(GPIOC, 1 << 10);

	while(true)
	{
		ledBus.write(buttBus.read());
	}
}
