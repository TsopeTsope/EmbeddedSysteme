/*
 * CKeysToLeds.h
 *
 *  Created on: 26.12.2022
 *      Author: User
 */

#ifndef SRC_CKEYSTOLEDS_H_
#define SRC_CKEYSTOLEDS_H_

class CKeysToLeds {
public:
	void run();
};

extern "C" void runKeysToLeds() {
	CKeysToLeds().run();
}
#endif /* SRC_CKEYSTOLEDS_H_ */
