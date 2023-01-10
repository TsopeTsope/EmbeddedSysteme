/*
 * CUartLoad.h
 *
 *  Created on: Dec 29, 2022
 *      Author: User
 */

#ifndef SRC_CUARTLOAD_H_
#define SRC_CUARTLOAD_H_

class CUartLoad {
public:
	void run();
};

extern "C" void runUartLoad() {
	CUartLoad().run();
}

#endif /* SRC_CUARTLOAD_H_ */
