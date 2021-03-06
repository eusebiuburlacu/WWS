/*
 * ScrTempHumSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRTEMPHUMSETT_H_
#define SCRTEMPHUMSETT_H_

#include "ScreenInterface.h"

class ScrTempHumSett : public IScreen
{
public:
	ScrTempHumSett();
	~ScrTempHumSett();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};

#endif /* SCRTEMPHUMSETT_H_ */
