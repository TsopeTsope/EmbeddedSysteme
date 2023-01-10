/*
 * CLcd1602.h
 *
 *  Created on: Dec 27, 2022
 *      Author: User
 */

#include "CGpioBus.h"
#include "CGpioPin.h"

#ifndef SRC_CLCD1602_H_
#define SRC_CLCD1602_H_

class CLcd1602 {
private:
	CGpioPin* m_rs;
	CGpioPin* m_enable;
	CGpioBus* m_dataBus;

	void writeNibble(uint8_t rs, uint8_t data);
	void writeByte(uint8_t rs, uint8_t data);
public:
	CLcd1602(CGpioPin* rs, CGpioPin* enable, CGpioBus* data);
	void init();
	void setCursor(int row, int column);
	void write(const char* text);
};

#endif /* SRC_CLCD1602_H_ */
