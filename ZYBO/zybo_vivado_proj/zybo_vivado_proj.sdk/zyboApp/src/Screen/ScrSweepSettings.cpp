/*
 * ScrSweepSettings.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */
#include "Screen/ScrSweepSettings.h"
#include "stdio.h"
#include "RF/mrf24j.h"

extern int arrayIdx;
extern Mrf24j RF;

extern unsigned long measuringFreq;
unsigned long freqSet = 5000;


ScrSweepSettings::ScrSweepSettings()
{

}

ScrSweepSettings::~ScrSweepSettings()
{

}

void ScrSweepSettings::sendIncCmd()
{
	freqSet += 100;
	if(freqSet > 50000)
			freqSet = 0;
}

void ScrSweepSettings::sendDecrCmd()
{
	freqSet -= 100;
	if(freqSet <= 1000)
		freqSet = 50000;
}

void ScrSweepSettings::sendChScrCmd()
{

}

void ScrSweepSettings::sendConfirmCmd()
{
	arrayIdx = -1;
	RF.sendData( 0x2342, 2, freqSet );
}

void ScrSweepSettings::printData()
{
	OLED.setCursor(0, 1);
	char data[20];
	sprintf(data, "%d Hz", freqSet);
	OLED.putString("set frequency");

	if( 0 == arrayIdx )
	{
		OLED.setCursor(3, 3);
		OLED.putString(data);
	}

	OLED.updateDisplay();
}
