/*
 * CBmp280I2cTest.h
 *
 *  Created on: Jan 11, 2023
 *      Author: User
 */

#ifndef SRC_CBMP280I2CTEST_H_
#define SRC_CBMP280I2CTEST_H_

class CBmp280I2cTest {
public:
	void run();
};

extern "C" void runBmp280I2cTest(){
	CBmp280I2cTest().run();
}

#endif /* SRC_CBMP280I2CTEST_H_ */
