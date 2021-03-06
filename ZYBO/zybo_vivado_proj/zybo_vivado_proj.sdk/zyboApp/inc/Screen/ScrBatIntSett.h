/*
 * ScrBatIntSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRBATINTSETT_H_
#define SCRBATINTSETT_H_

#include "ScreenInterface.h"

class ScrBatIntSett : public IScreen
{
public:
	ScrBatIntSett();
	~ScrBatIntSett();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};

#endif /* SCRBATINTSETT_H_ */
