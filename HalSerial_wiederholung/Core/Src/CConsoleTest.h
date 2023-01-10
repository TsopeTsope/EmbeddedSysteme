/*
 * CConsoleTest.h
 *
 *  Created on: 02.01.2023
 *      Author: User
 */

#ifndef SRC_CCONSOLETEST_H_
#define SRC_CCONSOLETEST_H_

class CConsoleTest {
public:
	void run();
};

extern "C" void runConsoleTest() {
	CConsoleTest().run();
}

#endif /* SRC_CCONSOLETEST_H_ */
