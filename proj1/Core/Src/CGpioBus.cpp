/*
 * CGpioBus.cpp
 *
 *  Created on: Jan 6, 2023
 *      Author: Ramses
 */

#include "CGpioBus.h"

CGpioBus::CGpioBus() {
	// TODO Auto-generated constructor stub
	m_pins = NULL;

}

CGpioBus::CGpioBus(const CGpioBus &orig) {
	if (orig != NULL){


		m_pins = new Pin;
		m_pins->mask = orig.m_pins->mask;
		m_pins->next = orig.m_pins->next;
		m_pins->port = orig.m_pins->port;
		Pins *tempOrig = orig.m_pins;
		Pins *temp = m_pins;
		while(temp->next != NULL){
			temp->next = new Pin;
			temp->mask = tempOrig->mask;
			temp->port = tempOrig->port;
			tempOrig = tempOrig->next;
			temp = temp->next;

		}
		temp->next = NULL;
	}

}

CGpioBus& CGpioBus::operator =(const CGpioBus &src) {
	if (orig != NULL){
		m_pins = new Pin;
		m_pins->mask = orig.m_pins->mask;
		m_pins->port = orig.m_pins->port;
		Pins *tempOrig = orig.m_pins;
		Pins *temp = m_pins;
		while(temp->next != NULL){
			temp->next = new Pin;
			temp->mask = tempOrig->mask;
			temp->port = tempOrig->port;
			tempOrig = tempOrig->next;
			temp = temp->next;
		}
	}
}

CGpioBus::~CGpioBus() {
	// TODO Auto-generated destructor stub
}

CGpioBus& CGpioBus::addPin(GPIO_TypeDef *port, uint16_t pinMask) {
}

CGpioBus& CGpioBus::write(uint16_t value) {
}

CGpioBus& CGpioBus::operator =(uint16_t value) {
}

uint16_t CGpioBus::read() const {
}
