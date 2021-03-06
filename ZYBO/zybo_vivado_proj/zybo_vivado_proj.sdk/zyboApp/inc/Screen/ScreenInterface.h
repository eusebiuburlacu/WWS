/*
 * ScreenInterface.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCREENINTERFACE_H_
#define SCREENINTERFACE_H_

#include "OLED/OLED.h"
extern OledClass OLED;
class IScreen
{
public:
	IScreen(){};
	virtual ~IScreen(){};

	virtual void sendIncCmd() = 0;
	virtual void sendDecrCmd() = 0;
	virtual void sendChScrCmd() = 0;
	virtual void sendConfirmCmd() = 0;
	virtual void printData() = 0;
};

#endif /* SCREENINTERFACE_H_ */
