/*
 * CLcdTest.h
 *
 *  Created on: Dec 27, 2022
 *      Author: User
 */

#ifndef SRC_CLCDTEST_H_
#define SRC_CLCDTEST_H_

class CLcdTest {
public:
	void run();
};

extern "C" void runLcdTest() {
	CLcdTest().run();
}

#endif /* SRC_CLCDTEST_H_ */
