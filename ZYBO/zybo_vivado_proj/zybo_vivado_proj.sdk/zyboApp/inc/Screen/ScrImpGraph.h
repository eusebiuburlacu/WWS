/*
 * ScrImpGraph.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#ifndef SCRIMPGRAPH_H_
#define SCRIMPGRAPH_H_

#include "ScreenInterface.h"

class ScrImpGraph : public IScreen
{
public:
	ScrImpGraph();
	~ScrImpGraph();
	virtual void sendIncCmd();
	virtual void sendDecrCmd();
	virtual void sendChScrCmd();
	virtual void sendConfirmCmd();
	virtual void printData();
};



#endif /* SCRIMPGRAPH_H_ */
