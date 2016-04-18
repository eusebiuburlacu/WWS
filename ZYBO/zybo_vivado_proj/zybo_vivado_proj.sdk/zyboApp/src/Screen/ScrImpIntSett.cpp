/*
 * ScrImpIntSett.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

#include "Screen/ScrImpIntSett.h"
#include "stdio.h"
#include "RF/mrf24j.h"

bool settingActive = false;
extern int arrayIdx;
extern Mrf24j RF;

extern unsigned long measuringFreq;
unsigned long updateInt = 100;

ScrImpIntSett::ScrImpIntSett()
{

}

ScrImpIntSett::~ScrImpIntSett()
{

}

void ScrImpIntSett::sendIncCmd()
{
	updateInt += 100;
	if(updateInt > 5000)
		updateInt = 0;

}

void ScrImpIntSett::sendDecrCmd()
{
	updateInt -= 100;
	if(updateInt <= 0)
		updateInt = 5000;
}

void ScrImpIntSett::sendChScrCmd()
{

}

void ScrImpIntSett::sendConfirmCmd()
{
	arrayIdx = -1;
	RF.sendData( 0x2342, 1, updateInt );
}

void ScrImpIntSett::printData()
{
	OLED.setCursor(0, 1);
	char data[20];
	sprintf(data, "%d ms", updateInt);
	OLED.putString("set update Int");
	if( 0 == arrayIdx )
	{
		OLED.setCursor(3, 3);
		OLED.putString(data);
	}
	OLED.updateDisplay();
}
