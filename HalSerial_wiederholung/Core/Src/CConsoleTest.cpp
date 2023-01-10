/*
 * CConsoleTest.cpp
 *
 *  Created on: 02.01.2023
 *      Author: User
 */

#include "CConsoleTest.h"
#include <iostream>
#include "CLcd1602.h"
#include <string>
#include <sstream>
//using namespace std;

void CConsoleTest::run() {
	std::cout << "Hello World!\r\n";

//	std::cout<<"Geben wir ueber 100 Zeichen auf die Console aus und pruefen wir"
//			",ob alle Zeichen auf die Console ausgegeben werden. "
//			"Damit prüfen wir, dass die schwache Funktion _write automatisch "
//			"aufgerufen wird, nachdem 100 Zeichen ausgegeben wurden.\r\n";

//	for (int number = 1; number <= 10; number += 1) {
//	std::cout << "Counter value: " << number << "\r\n";
//	}

	// LCD Konfigureation
	CGpioPin rs(GPIOD, 2);
	CGpioPin enable(GPIOC, 9);
	CGpioBus dataBus = CGpioBus().addPin(GPIOA, 1<<11).addPin(GPIOA, 1<<12)
			.addPin(GPIOB, 1<<1).addPin(GPIOB, 1<<2);
	CLcd1602 tempAus(&rs, &enable, &dataBus);
	tempAus.init();

	// Adc Konfiguration
	ADC_HandleTypeDef ADC_IN16;
	int val = 0;

	while (true) {
		// ADC
		HAL_ADC_Start(&ADC_IN16);
		val = HAL_ADC_GetValue(&ADC_IN16);
		HAL_ADC_Stop(&ADC_IN16);

		// Ausgabe suf die Konsole
		std::cout<< "Interne Temperatur: " << val << "°C" <<"\r\n";

		// Integer to pointer to char
		std::stringstream strs;
		strs << val;
		std::string temp_str = strs.str();
		char* char_val = (char*) temp_str.c_str();

		// LCD Anzeige
		tempAus.setCursor(0, 1);
		tempAus.write(char_val);
		tempAus.write("Grad");
		HAL_Delay(30);

//		int data;
//		std::cout << "Bitte ein Wert eingeben: ";
//		std::cin >> data;
//		std::cout << "\r\n";
//		std::cout << "Ihre Eingabe ist: " << data << "\r\n";
	}
}
