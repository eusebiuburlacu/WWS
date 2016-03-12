/*
 * ScrIncFrecSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRINCFRECSETT_H_
#define SCRINCFRECSETT_H_

#include "ScreenInterface.h"

class ScrIncFreqSett : IScreen
{
	ScrIncFreqSett();
	~ScrIncFreqSett();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};


#endif /* SCRINCFRECSETT_H_ */
