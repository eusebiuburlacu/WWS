/*
 * ScrImpCurSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRIMPCURSETT_H_
#define SCRIMPCURSETT_H_

#include "ScreenInterface.h"

class ScrImpCurSett : public IScreen
{
public:
	ScrImpCurSett();
	~ScrImpCurSett();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};

#endif /* SCRIMPCURSETT_H_ */
