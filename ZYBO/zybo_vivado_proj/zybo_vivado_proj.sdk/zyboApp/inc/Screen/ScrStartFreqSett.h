/*
 * ScrStartFreqSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRSTARTFREQSETT_H_
#define SCRSTARTFREQSETT_H_

#include "ScreenInterface.h"

class ScrStartFreqSett : public IScreen
{
public:
	ScrStartFreqSett();
	~ScrStartFreqSett();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};



#endif /* SCRSTARTFREQSETT_H_ */
