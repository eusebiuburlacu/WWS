/*
 * ScrImpGraph.h
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */

/*
 * ScrImpCurSett.cpp
 *
 *  Created on: 12.03.2016
 *      Author: Sebi
 */
#include "Screen/ScrImpGraph.h"
#include <vector>;
#include <algorithm>
#include "sleep.h"
using namespace std;

extern bool impedanceUpdated;
extern vector<float> impedanceArray;

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

ScrImpGraph::ScrImpGraph()
{

}

ScrImpGraph::~ScrImpGraph()
{

}

void ScrImpGraph::sendIncCmd()
{

}

void ScrImpGraph::sendDecrCmd()
{

}

void ScrImpGraph::sendChScrCmd()
{

}

void ScrImpGraph::sendConfirmCmd()
{

}

void ScrImpGraph::printData()
{
	if(impedanceArray.size() != 0 && impedanceUpdated)
	{
		impedanceUpdated = false;
		std::vector<float>::iterator max = std::max_element(impedanceArray.begin(), impedanceArray.end());
		std::vector<float>::iterator min = std::min_element(impedanceArray.begin(), impedanceArray.end());

		if( *max > 700 && *min > 700 )
		{
			OLED.setCursor(0, 1);
			OLED.putString("Error impedance");
			OLED.setCursor(0, 3);
			OLED.putString("Check the sensor");
		}
		else
		{
			int step = 128 / (impedanceArray.size() - 1);
			for(int i = 0; i < impedanceArray.size()-1; i++)
			{
				long mappedVal = map((long)impedanceArray[i],(long)*min, (long)*max, 32, 0 );
				OLED.moveTo(i * step, mappedVal );
				mappedVal = map((long)impedanceArray[i+1],(long)*min, (long)*max, 32, 0 );
				OLED.drawLine((i+1)*step, mappedVal);
			}
		}
		OLED.updateDisplay();
	}

	if(impedanceArray.size() == 0)
	{
		OLED.setCursor(0, 1);
		OLED.putString("No impedance");
		OLED.updateDisplay();
	}

}
