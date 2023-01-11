/*
 * CLcd1602.cpp
 *
 *  Created on: Dec 27, 2022
 *      Author: User
 */

#include "CLcd1602.h"
#include "tim.h"


CLcd1602::CLcd1602(CGpioPin *rs, CGpioPin *enable, CGpioBus *data) {
	m_rs = rs;
	m_enable = enable;
	m_dataBus = data;
}

void CLcd1602::writeNibble(uint8_t rs, uint8_t data) {
	(*m_rs) = (bool)rs;
	HAL_Delay(1);

	(*m_enable) = true;
	HAL_Delay(1);

	(*m_dataBus).write(data);
	HAL_Delay(1);

	(*m_enable) = false;
}

void CLcd1602::writeByte(uint8_t rs, uint8_t data) {
	writeNibble(rs, (uint8_t) ((data & 0xF0)>>4));
	writeNibble(rs, (uint8_t) (data & 0x0F));
}

void CLcd1602::init() {
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_Delay(15);
	writeNibble(0, 0x3);
	HAL_Delay(5);
	writeNibble(0, 0x3);
	HAL_Delay(1);
	writeNibble(0, 0x3);
	HAL_Delay(1);
	writeNibble(0, 0x2);
	HAL_Delay(1);
	writeByte(0, 0x28);
	HAL_Delay(1);
	writeByte(0, 0x08);
	HAL_Delay(1);
	writeByte(0, 0x01);
	HAL_Delay(1);
	writeByte(0, 0x02);
	HAL_Delay(1);
	writeByte(0, 0x0C);
}

void CLcd1602::setCursor(int row, int column) {
	if( (row < 2) && (row >= 0) && (column < 16) && (column >= 0) )
	{
		uint8_t adress = 0X00;
		if(row == 0)
			adress = 0x80 | column;
		if(row == 1)
			adress = 0xC0 | column;

		writeByte(0, adress);
	}
}

void CLcd1602::write(const char *text) {
	char *ptr = (char *)text;
	while(*ptr)
	{
		writeByte(1, *ptr);
		ptr++;
	}
}
