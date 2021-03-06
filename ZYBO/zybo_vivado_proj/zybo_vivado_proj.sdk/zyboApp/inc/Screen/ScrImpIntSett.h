/*
 * ScrImpIntSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRIMPINTSETT_H_
#define SCRIMPINTSETT_H_

#include "ScreenInterface.h"

class ScrImpIntSett : public IScreen
{
public:
	ScrImpIntSett();
	~ScrImpIntSett();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};

#endif /* SCRIMPINTSETT_H_ */
