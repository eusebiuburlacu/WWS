/*
 * ScrIncNumSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRINCNUMSETT_H_
#define SCRINCNUMSETT_H_

#include "ScreenInterface.h"

class ScrIncNumSett : IScreen
{
	ScrIncNumSett();
	~ScrIncNumSett();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};


#endif /* SCRINCNUMSETT_H_ */
