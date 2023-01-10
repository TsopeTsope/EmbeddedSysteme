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
	if (orig.m_pins != NULL){


		m_pins = new Pin;
		m_pins->mask = orig.m_pins->mask;
		m_pins->next = orig.m_pins->next;
		m_pins->port = orig.m_pins->port;
		Pin *tempOrig = orig.m_pins;
		Pin *temp = m_pins;
		while(tempOrig->next != NULL){
			temp->next = new Pin;
			tempOrig = tempOrig->next;
			temp = temp->next;
			temp->mask = tempOrig->mask;
			temp->port = tempOrig->port;
		}
		temp->next = NULL;
	}

}

CGpioBus& CGpioBus::operator =(const CGpioBus &src) {
	if (src.m_pins !=NULL){
		m_pins = new Pin;
		m_pins->mask = src.m_pins->mask;
		m_pins->port = src.m_pins->port;
		m_pins->next = NULL;
		Pin* tempM_pins = m_pins;
		Pin* tempSrc = src.m_pins;

		while ( tempSrc->next != NULL){
			tempM_pins->next = new Pin;
			tempM_pins = tempM_pins->next;
			tempSrc = tempSrc->next;
			tempM_pins->mask = tempSrc->mask;
			tempM_pins->port = tempSrc->port;
		}
		tempM_pins->next = NULL;
	}
	return *this;
}

CGpioBus::~CGpioBus() {
	// TODO Auto-generated destructor stub
	deleteAll();
}

CGpioBus& CGpioBus::addPin(GPIO_TypeDef *port, uint16_t pinMask) {
	if (m_pins == NULL){
		m_pins = new Pin;
		m_pins->port = port;
		m_pins->mask = pinMask;
		m_pins->next = NULL;
		return *this;
	}
	Pin* tempM_pins = m_pins;
	while (tempM_pins->next != NULL){
		tempM_pins = tempM_pins->next;
	}
	tempM_pins = tempM_pins->next;
	tempM_pins = new Pin;
	tempM_pins->port = port;
	tempM_pins->mask = pinMask;
	tempM_pins->next = NULL;
	return *this;
}

CGpioBus& CGpioBus::write(uint16_t value) {
		uint16_t bitMask = 1;
		Pin* tempM_pins = m_pins;
		while (tempM_pins != NULL){
			if (bitMask & value){
				HAL_GPIO_WritePin(tempM_pins->port, tempM_pins->mask, GPIO_PIN_SET );
			}
			else{
				HAL_GPIO_WritePin(tempM_pins->port, tempM_pins->mask, GPIO_PIN_RESET );
			}
			bitMask=bitMask<<1;
			tempM_pins = tempM_pins->next;
		}
	return *this;
}

void CGpioBus::deleteAll(){
	Pin* tempM_pins = m_pins;
	while(tempM_pins != NULL){
		delete m_pins;
		tempM_pins = tempM_pins->next;
		m_pins = tempM_pins;
	}
}

CGpioBus& CGpioBus::operator =(uint16_t value) {
	return write(value);
}

uint16_t CGpioBus::read() const {
	Pin* tempM_pins = m_pins;
	uint16_t value = 0;
	uint16_t bitMask = 1;
	bool state =false;
	while(tempM_pins != NULL){
		state = HAL_GPIO_ReadPin(tempM_pins->port, tempM_pins->mask);
		if (state){
			value = value | bitMask;
		}
		tempM_pins = tempM_pins->next;
		bitMask = bitMask<<1;
	}
	return value;
}

CGpioBus::operator uint16_t() const {
	return read();
}
