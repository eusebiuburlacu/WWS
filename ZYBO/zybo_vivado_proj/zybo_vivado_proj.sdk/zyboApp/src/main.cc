/*****************************************************************************/
/**
* @file main.cc
*
* This is the entry point for WWS application
*
* @note
*
* None.
*
*<pre>
* MODIFICATION HISTORY:
*
*  Who  		Date     Changes
*  --------		---------- ---------------------------------------------------------
*  LucianB 	22/02/2016 Created
*
******************************************************************************/

/***************************** Include Files *********************************/

#include <stddef.h>
#include "xil_printf.h"
#include <xstatus.h>
#include "sleep.h"
#include "OLED/OLED.h"
#include "RF/mrf24j.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

/************************** Object Definitions *****************************/
OledClass OLED;
Mrf24j RF;

/*****************************************************************************/
/**
*
* Main function to call the Spi Polled example.
*
* @param	None
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None
*
******************************************************************************/

using namespace std;

typedef enum
{
	RF_MESSAGE_IMPEDANCE = 1,
	RF_MESSAGE_PHASE,
	RF_MESSAGE_TEMPERATURE,
	RF_MESSAGE_HUMIDITY,
	RF_MESSAGE_BATTERY
} RF_MESSAGE_TYPES;

vector<float> impedanceArray;
vector<float> phaseArray;
float temperature;
unsigned char humidity;
float batteryVoltage;
bool impedanceUpdated = false;

void rxCallback()
{
	int dataLen;
	rx_info_t *RXInfo =  RF.get_rxinfo(dataLen);
	dataLen--;

	int i = 0;

	RF_MESSAGE_TYPES msgType = (RF_MESSAGE_TYPES)RXInfo->rx_data[i++];

	switch( msgType )
	{
		case RF_MESSAGE_IMPEDANCE:
		{
			xil_printf("RF_MESSAGE_IMPEDANCE\n");
			impedanceArray.clear();
			impedanceUpdated = true;
			for(; i < dataLen; i+=4)
			{
				float val;
				uint8_t *valPtr = (uint8_t*)(void *)&val;
				*valPtr++ = RXInfo->rx_data[i];
				*valPtr++ = RXInfo->rx_data[i+1];
				*valPtr++ = RXInfo->rx_data[i+2];
				*valPtr++ = RXInfo->rx_data[i+3];
				impedanceArray.push_back(val);
				char data[5];
				sprintf(data, "%.2f\n", val);
				xil_printf("%s", data);
			}

			break;
		}
		case RF_MESSAGE_PHASE:
		{
			xil_printf("RF_MESSAGE_PHASE\n");
			for(; i < dataLen; i+=4)
			{
				float val;
				uint8_t *valPtr = (uint8_t*)(void *)&val;
				*valPtr++ = RXInfo->rx_data[i];
				*valPtr++ = RXInfo->rx_data[i+1];
				*valPtr++ = RXInfo->rx_data[i+2];
				*valPtr = RXInfo->rx_data[i+3];
				impedanceArray.push_back(val);
				char data[5];
				sprintf(data, "%.2f\n", val);
				xil_printf("%s", data);
			}

			break;
		}
		case RF_MESSAGE_TEMPERATURE:
		{
			xil_printf("RF_MESSAGE_TEMPERATURE\n");
			uint8_t *valPtr = (uint8_t*)(void *)&temperature;
			*valPtr++ = RXInfo->rx_data[1];
			*valPtr++ = RXInfo->rx_data[2];
			*valPtr++ = RXInfo->rx_data[3];
			*valPtr = RXInfo->rx_data[4];
			char data[5];
			sprintf(data, "%.2f\n", temperature);
			xil_printf("%s", data);
			break;
		}
		case RF_MESSAGE_HUMIDITY:
		{
			xil_printf("RF_MESSAGE_HUMIDITY\n");
			humidity = RXInfo->rx_data[1];
			xil_printf("%d\n", humidity);
			break;
		}
		case RF_MESSAGE_BATTERY:
		{
			xil_printf("RF_MESSAGE_BATTERY\n");
			uint8_t *valPtr = (uint8_t*)(void *)&batteryVoltage;
			*valPtr++ = RXInfo->rx_data[1];
			*valPtr++ = RXInfo->rx_data[2];
			*valPtr++ = RXInfo->rx_data[3];
			*valPtr = RXInfo->rx_data[4];
			char data[5];
			sprintf(data, "%.2f\n", batteryVoltage);
			xil_printf("%s", data);
			break;
		}
		default:
		{
			xil_printf("ERROR: Invalid msg type");
			break;
		}
	}
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(void)
{
	xil_printf("Start\n");
	RF.initDrivers();
	xil_printf("initDrivers\n");
	RF.reset();
	xil_printf("reset\n");
	RF.init();
	xil_printf("init\n");
	RF.set_pan(0xcafe);
	xil_printf("set_pan\n");
	RF.registerRXCallback(rxCallback);
	xil_printf("registerRXCallback\n");
	RF.address16_write(0x4202);
	xil_printf("address16_write\n");
	OLED.begin();
	xil_printf("begin\n");

	while(1)

	{
		int irow;
		int ib;
		RF.checkIntFlag();
		//Clear the virtual buffer
		OLED.clearBuffer();
		
		//Chosing Fill pattern 0
		OLED.setFillPattern(OLED.getStdPattern(0));
		//Turn automatic updating off
		OLED.setCharUpdate(0);
		usleep(100000);
		RF.checkIntFlag();
		//Draw a rectangle over wrting then slide the rectagle
		//down slowly displaying all writing
		/*for (irow = 0; irow < OLED.rowMax; irow++)
		{
			OLED.clearBuffer();
			OLED.setCursor(0, 0);
			OLED.putString("PmodOLED");
			OLED.setCursor(0, 1);
			OLED.putString("by Digilent");
			OLED.setCursor(0, 2);
			OLED.putString("Simple Demo");
			
			OLED.moveTo(0, irow);
			OLED.drawFillRect(127,31);
			OLED.moveTo(0, irow);
			OLED.drawLine(127,irow);
			OLED.updateDisplay();
			usleep(100000);
			RF.checkIntFlag();
		}*/

		//draw impedance chart
		OLED.clearBuffer();

		if(impedanceArray.size() != 0 && impedanceUpdated)
		{
			impedanceUpdated = false;
			std::vector<float>::iterator max = std::max_element(impedanceArray.begin(), impedanceArray.end());
			std::vector<float>::iterator min = std::min_element(impedanceArray.begin(), impedanceArray.end());

			//char data[5];
			//OLED.setCursor(0, 0);

			/*sprintf(data, "%.2f", *max);
			OLED.putString(data);
			OLED.setCursor(4, 12);
			sprintf(data, "%.2f", *min);
			OLED.putString(data);
			OLED.updateDisplay();*/
			if( *max > 700 && *min > 700 )
			{
				OLED.setCursor(0, 1);
				OLED.putString("Error impedance");
				OLED.setCursor(0, 3);
				OLED.putString("Check the sensor");
				OLED.updateDisplay();
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
					OLED.updateDisplay();
					usleep(50000);
				}
			}
		}
		
	}
	
	return XST_SUCCESS;
}
