/*
 * CGpioBus.cpp
 *
 *  Created on: Dec 23, 2022
 *      Author: User
 */

#include "CGpioBus.h"

CGpioBus::CGpioBus() {
	m_pins = nullptr;
}

CGpioBus::CGpioBus(const CGpioBus &orig) {


	if (orig.m_pins != nullptr) {
		m_pins = new Pin;
		m_pins->mask = orig.m_pins->mask;
		m_pins->port = orig.m_pins->port;
		m_pins->next = nullptr;

		Pin* ptrTarget = m_pins;
		Pin* ptrOrig = orig.m_pins;
		while(ptrOrig->next != nullptr)
		{
			ptrTarget->next = new Pin;
			ptrTarget = ptrTarget->next;
			ptrOrig = ptrOrig->next;

			ptrTarget->mask = ptrOrig->mask;
			ptrTarget->port = ptrOrig->port;
			ptrTarget->next = nullptr;
		}
	}
}

CGpioBus& CGpioBus::operator =(const CGpioBus &src) {

	deleteAll();

	if (src.m_pins != nullptr) {
		m_pins = new Pin;
		m_pins->mask = src.m_pins->mask;
		m_pins->port = src.m_pins->port;
		m_pins->next = nullptr;

		Pin* ptrTarget = m_pins;
		Pin* ptrSrc = src.m_pins;
		while(ptrSrc->next != nullptr)
		{
			ptrTarget->next = new Pin;
			ptrTarget = ptrTarget->next;
			ptrSrc = ptrSrc->next;

			ptrTarget->mask = ptrSrc->mask;
			ptrTarget->port = ptrSrc->port;
			ptrTarget->next = nullptr;;
		}
	}
	return *this;
}

void CGpioBus::deleteAll() {

	Pin* ptrNextPin = m_pins;
	while(m_pins != 0)
	{
		ptrNextPin = m_pins->next;
		delete m_pins;
		m_pins = ptrNextPin;
	}
}

CGpioBus::~CGpioBus() {
	deleteAll();
}

CGpioBus& CGpioBus::addPin(GPIO_TypeDef *port, uint16_t pinMask) {

	if (m_pins == nullptr) {
		m_pins = new Pin;
		m_pins->mask = pinMask;
		m_pins->port = port;
		m_pins->next = nullptr;
	}
	else
	{
		Pin* nextPin = m_pins;
		while(nextPin->next != nullptr)
		{
			nextPin = nextPin->next;
		}

		if(nextPin->next == nullptr)
		{
			nextPin->next = new Pin;
			nextPin = nextPin->next;
			nextPin->mask = pinMask;
			nextPin->port = port;
			nextPin->next = nullptr;
		}
	}
	return *this;
}

CGpioBus& CGpioBus::write(uint16_t value) {

	if (m_pins != nullptr)
	{
		uint16_t bitMask = 1;
		Pin* pin = m_pins;
		while(pin != 0)
		{
			if( (bitMask & value) )
			HAL_GPIO_WritePin(pin->port, pin->mask, GPIO_PIN_SET );
			else
				HAL_GPIO_WritePin(pin->port, pin->mask, GPIO_PIN_RESET );
			pin = pin->next;
			bitMask = bitMask<<1;;
		}
	}
	return *this;
}

CGpioBus& CGpioBus::operator =(uint16_t value) {
	return write(value);
}

uint16_t CGpioBus::read() const {
	Pin* temp;
	temp = m_pins;
	uint8_t val = 0;
	uint8_t buttMaske = 1;
	bool state;
	while(temp != nullptr)
	{
		state = HAL_GPIO_ReadPin(temp->port, temp->mask);
		if(state)
		{
			val = val | buttMaske;
		}
		temp= temp->next;
		buttMaske = buttMaske << 1;

	}
	return val;
}

CGpioBus::operator uint16_t() const {
	return read();
}

