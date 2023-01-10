/*
 * CPatternGenerator.cpp
 *
 *  Created on: 25.12.2022
 *      Author: User
 */

#include "CPatternGenerator.h"
#include "CGpioBus.h"

void CPatternGenerator::run() {
	CGpioBus ledBus = CGpioBus().addPin(GPIOC, 1 << 0).addPin(GPIOC, 1 << 1).
			addPin(GPIOC, 1 << 2).addPin(GPIOC, 1 << 3).addPin(GPIOC, 1 << 4).
			addPin(GPIOC, 1 << 5).addPin(GPIOC, 1 << 6).addPin(GPIOC, 1 << 7);

	int ledPos = 1;
	int laufRichtung = true;

	while(1)
	{
		ledBus.write(ledPos);
		HAL_Delay(500);
		laufRichtung ? (ledPos = ledPos << 1, ledPos >= 128 ? laufRichtung = false: laufRichtung):(ledPos = ledPos >> 1,ledPos <= 1 ? laufRichtung = true: laufRichtung);
//		if(laufRichtung == true)
//		{
//			ledPos = ledPos << 1;
//			if (ledPos >= 128)
//				laufRichtung = false;
//		}
//		else
//		{
//			ledPos = ledPos >> 1;
//			if (ledPos <= 1)
//			{
//				laufRichtung = true;
//			}
//
//		}
	}
}
