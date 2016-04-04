/*
 * ScrImpCurSett.cpp
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */
#include "Screen/ScrImpCurSett.h"
#include <vector>
#include "stdio.h"

extern unsigned long measuringFreq;
extern std::vector<float> impedanceArray;


ScrImpCurSett::ScrImpCurSett()
{

}

ScrImpCurSett::~ScrImpCurSett()
{

}

void ScrImpCurSett::sendIncCmd()
{

}

void ScrImpCurSett::sendDecrCmd()
{

}

void ScrImpCurSett::sendChScrCmd()
{

}

void ScrImpCurSett::sendConfirmCmd()
{

}

void ScrImpCurSett::printData()
{
	if( 0 != impedanceArray.size() )
	{
		OLED.setCursor(0, 0);
		char data[20];
		sprintf(data, "imped: %.2f K", impedanceArray[0]);
		OLED.putString(data);
		OLED.setCursor(0, 2);
		sprintf(data, "freq: %d Hz", measuringFreq);
		OLED.putString(data);
		OLED.updateDisplay();
	}
	else
	{
		OLED.setCursor(0, 0);
		char data[20];
		sprintf(data, "imped: %.2f K", 0.00);
		OLED.putString(data);
		OLED.setCursor(0, 2);
		sprintf(data, "freq: %d Hz", 0);
		OLED.putString(data);
		OLED.updateDisplay();
	}
}
