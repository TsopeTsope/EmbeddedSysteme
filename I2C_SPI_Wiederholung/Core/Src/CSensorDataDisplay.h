/*
 * CSensorDataDisplay.h
 *
 *  Created on: 14.01.2023
 *      Author: User
 */

#ifndef SRC_CSENSORDATADISPLAY_H_
#define SRC_CSENSORDATADISPLAY_H_

class CSensorDataDisplay {
public:
	void run();
};

extern "C" void runSensorDataDisplay(){
	CSensorDataDisplay().run();
}
#endif /* SRC_CSENSORDATADISPLAY_H_ */
