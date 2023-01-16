//============================================================================
// Name        : I2C-Devices.cpp
// Author      : Nazer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CDs1621.h"
#include <chrono>
#include <thread>
#include <sys/time.h>
#include <signal.h>

using namespace std;
using namespace std::chrono_literals;

// Deklaration einer Variable für das LED
bool LED;

/**
 * Die Funktion testet die Methode readTemperature(), die die
 *  die Temperatur ausliest
 *
 * @param ds1621 driver
 * */
void testReadTemperature(CDs1621& ds1621){

	// Conversion starten
	ds1621.startConversion();

	// Temperatur auslesen und ausgeben
	cout << "Temperature: " << ds1621.readTemperature()  << " °C" << endl;
}

/**
 * Die Funktion testet die Methode readTemperatureHR(), die die
 *  die Temperatur mit hoher Auflösung ausliest
 *
 * @param ds1621 driver
 * */
void testReadTemperatureHR(CDs1621& ds1621){

	// Conversion starten
	ds1621.startConversion();

	// Temperatur auslesen und ausgeben
	cout <<"Temperature High Resolusion: " << ds1621.readTemperatureHR()
			<< " °C" <<endl;
}

/**
 * Die Funktion testet die Methode getContinuousConversion(),
 * indem Messungen in 1 SHOT und in continuous conversion durchgeführt werden.
 *
 * @param ds1621 driver
 * */
void testReadContinuously(CDs1621& ds1621){

	// Conversion starten
	ds1621.startConversion();

	// 1 SHOT Conversion Mode einstellen
	ds1621.setContinuousConversion(false);

	// test der Methode getContinuousConversion()
	if(!ds1621.getContinuousConversion())
	{
		cout << "1 SHOT Conversion Mode aktiviert !!!" << endl;
	}

	// Temperatur auslesen und ausgeben
	cout <<"Temperature in 1-Shot Conversion: "
			<< ds1621.readTemperature()  << " °C" <<endl;

	// Continuous Conversion Mode einstellen
	ds1621.setContinuousConversion(true);

	// test der Methode getContinuousConversion()
	if(ds1621.getContinuousConversion())
	{
		cout << "Continuous Conversion Mode aktiviert !!!" << endl;
	}

	// Temperatur auslesen und ausgeben
	cout <<"Temperature in Continuous Conversion: "
			<< ds1621.readTemperature()  << " °C" <<endl;

	// meherere Messung durführen
	for(int i = 0; i < 60; i++)
	{
		// Temperatur messen und ausgeben
		cout <<"Temperaturesmessung No " << i + 1 << ":   "
				<< ds1621.readTemperature()  << " °C" <<endl;

		// wartezeit für 1 Sekunde
		this_thread::sleep_for(1s);
	}

}

/**
 * Die Funktion testet die Methode stopConversion(), die die Mesungen stoppt.
 *
 * @param ds1621 driver
 * */
void testStopConversion(CDs1621& ds1621){

	// Conversion starten
	ds1621.startConversion();

	// 1 SHOT Conversion Mode einstellen
	ds1621.setContinuousConversion(false);

	// test der Methode getContinuousConversion()
	if(!ds1621.getContinuousConversion())
	{
		cout << "1 SHOT Conversion Mode aktiviert !!!" << endl;
	}

	// Temperatur auslesen und ausgeben
	cout <<"Temperature in 1-Shot Conversion: "
			<< ds1621.readTemperature() <<endl;

	// Continuous Conversion Mode einstellen
	ds1621.setContinuousConversion(true);

	// test der Methode getContinuousConversion()
	if(ds1621.getContinuousConversion())
	{
		cout << "Continuous Conversion Mode aktiviert !!!" << endl;
	}

	// Temperatur auslesen und ausgeben
	cout <<"Temperature in Continuous Conversion: "
			<< ds1621.readTemperature() <<endl;

	// meherere Messung durführen
	for(int i = 0; i < 60; i++)
	{
		if(i > 29 )
		{
			// Conversion stoppen
			ds1621.stopConversion();
		}

		// Temperatur messen und ausgeben
		cout <<"Temperaturesmessung No " << i + 1 << ":   "
				<< ds1621.readTemperature() << " °C" <<endl;

		// wartezeit für 1 Sekunde
		this_thread::sleep_for(1s);
	}
}

/**
 * Die Funktion testet die Methode getTH() und getTL(),
 * die die Schwelltemperatur einstellen.
 *
 * @param ds1621 driver
 * */
void testThresholds(CDs1621& ds1621){

	// Conversion starten
	ds1621.startConversion();

	// obere Schwelltemperature einstellen
	ds1621.setTH(53.5);

	// test der Methode getTH()
	if(ds1621.getTH() == (53.5))
	{
		cout << "Obere Schwelltemperature ist eingestellt: "
				<< ds1621.getTH()  << " °C" << endl;
	}
	else
	{
		cout << "TH falsch: " << ds1621.getTH() << endl;
	}

	// untere Schwelltemperature einstellen
	ds1621.setTL(33.5);

	// test der Methode getTL()
	if(ds1621.getTL() == (33.5))
	{
		cout << "Untere Schwelltemperature ist eingestellt: "
				<< ds1621.getTL()  << " °C" << endl;
	}
	else
	{
		cout << "TL falsch: " << ds1621.getTL() << endl;
	}

	// wait
	while(true)
	{
		// wartezeit für 1 Sekunde
		this_thread::sleep_for(1s);
	}
}

/**
 * Die Funktion tooggle ein LED
 *
 * @param ds1621 driver
 * */
static void timerSignal(int signum)
{
	// LED togglen
	LED = !LED;

	// wenn das LED eingeschaltet ist
	if(LED == true)
	{
		// Konsolenausgabe
		cout << "LED on!" << endl;
	}
	else
	{
		// Konsolenausgabe
		cout << "LED off!" << endl;
	}

}

/**
 * Die Funktion führt Mesungen aus und soll ein LED ein- bzw. ausschaltet,
 * wenn die Temperatur > 30 bzw. < 29 ist.
 *
 * @param ds1621 driver
 * */
void testBlink(CDs1621& ds1621){

	// Messunngszähler
	int i = 1;
	// Conversion starten
	ds1621.startConversion();

	// timer defineren
	struct itimerval timer1s;

	// Timer Intervall initialisieren
	timer1s.it_interval.tv_sec = 1;
	timer1s.it_interval.tv_usec = 0;
	timer1s.it_value.tv_sec = 1;
	timer1s.it_value.tv_usec = 0;

	// Timer Intervall einstellen
	setitimer(ITIMER_REAL, &timer1s, NULL);
	signal(SIGALRM, timerSignal);

	// Continuous Conversion Mode einstellen
	ds1621.setContinuousConversion(true);
	getitimer(ITIMER_REAL,&timer1s);
	while(true)
	{
		// Prüft ob die Temperatur > 30°C ist
		if(ds1621.readTemperature() > 30 )
		{
			// Timer aktivieren
			setitimer(ITIMER_REAL, &timer1s, NULL);
		}

		// Prüft ob die Temperatur < 29°C ist
		if(ds1621.readTemperature() < 29 )
		{
			// Timer desaktivieren
			setitimer(ITIMER_REAL, NULL, NULL);
		}

		// Ausgabe der Temperatur
		cout << "Temperatur " << i++ << ": "
				<< ds1621.readTemperature() << "°C" << endl;

		// wartezeit für 5 Sekunde
		this_thread::sleep_for(5s);
	}
}

int main() {
	cout << "!!!Embeddded Systems Labor Versuch 5!!!" << endl;

	// Neue Driver erzeugen
	CDs1621 ds1621("/dev/i2c-2", 0x48);

	// Temperatur messen
//	testReadTemperature(ds1621);

	// Temperatur mit hoher Auflösung messen
//	testReadTemperatureHR(ds1621);

	// Temperatur in Continuous Conversion messen
//	testReadContinuously(ds1621);

	// Stop conversion testen
//	testStopConversion(ds1621);

	// Test der Schwelltemperatur
//	testThresholds(ds1621);

	// test der Funktion testBlink
	testBlink(ds1621);

	return 0;
}
