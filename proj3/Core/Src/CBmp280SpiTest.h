/*
 * CBmp280SpiTest.h
 *
 *  Created on: 11 janv. 2023
 *      Author: Ramses
 */

#ifndef SRC_CBMP280SPITEST_H_
#define SRC_CBMP280SPITEST_H_

class CBmp280SpiTest {
public:
	void run();
};

extern "C" void runBmp280SpiTest(){
	CBmp280SpiTest().run();
}

#endif /* SRC_CBMP280SPITEST_H_ */
