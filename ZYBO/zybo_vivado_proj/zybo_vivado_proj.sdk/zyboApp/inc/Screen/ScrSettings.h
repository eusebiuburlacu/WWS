/*
 * ScrSettings.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRSETTINGS_H_
#define SCRSETTINGS_H_

#include "ScreenInterface.h"

class ScrSettings : public IScreen
{
public:
	ScrSettings();
	~ScrSettings();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};



#endif /* SCRSETTINGS_H_ */
