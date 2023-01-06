/*
 * CPatternGenerator.h
 *
 *  Created on: 25.12.2022
 *      Author: User
 */

#ifndef SRC_CPATTERNGENERATOR_H_
#define SRC_CPATTERNGENERATOR_H_

class CPatternGenerator {
public:
	void run();
};

extern "C" void runPatternGenerator() {
	CPatternGenerator().run();
}

#endif /* SRC_CPATTERNGENERATOR_H_ */


