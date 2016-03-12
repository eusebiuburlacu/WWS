/*
 * ScrSweepSettings.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRSWEEPSETTINGS_H_
#define SCRSWEEPSETTINGS_H_

#include "ScreenInterface.h"

class ScrSweepSettings : IScreen
{
	ScrSweepSettings();
	~ScrSweepSettings();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};


#endif /* SCRSWEEPSETTINGS_H_ */
