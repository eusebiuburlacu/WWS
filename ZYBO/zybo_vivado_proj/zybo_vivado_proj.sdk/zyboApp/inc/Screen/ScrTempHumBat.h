/*
 * ScrTempHumBat.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRTEMPHUMBAT_H_
#define SCRTEMPHUMBAT_H_

#include "ScreenInterface.h"

class ScrTempHumBat : public IScreen
{
public:
	ScrTempHumBat();
	~ScrTempHumBat();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};

#endif /* SCRTEMPHUMBAT_H_ */
