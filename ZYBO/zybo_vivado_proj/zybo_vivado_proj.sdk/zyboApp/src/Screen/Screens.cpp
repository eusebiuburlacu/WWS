/*
 * Screens.cpp
 *
 *  Created on: 04.04.2016
 *      Author: Sebi
 */
#include "Screen/Screens.h"

vector<IScreen*> getMenuScreens()
{
	vector<IScreen*> screens;
	screens.push_back(new ScrImpGraph());
	//screens.push_back(new ScrMaxMin());
	screens.push_back(new ScrTempHumBat());
	screens.push_back(new ScrImpCurSett());
	screens.push_back(new ScrSettings());

	return screens;
}

vector<IScreen*> getSettingsScreens()
{
	vector<IScreen*> screens;
	screens.push_back(new ScrSweepSettings());
	screens.push_back(new ScrImpIntSett());
	//screens.push_back(new ScrTempHumSett());
	//screens.push_back(new ScrBatIntSett());

	return screens;
}

vector<IScreen*> getSweepScreens()
{
	vector<IScreen*> screens;
	screens.push_back(new ScrStartFreqSett());
	screens.push_back(new ScrIncFreqSett());
	screens.push_back(new ScrIncNumSett());

	return screens;
}



