
#include "RFWrapper.h"
//incluzi libraria rf
#include "WProgram.h"
RFWrapper::RFWrapper()
{
	
}

RFWrapper::~RFWrapper()
{
	
}

bool RFWrapper::sendImpedance( float *samples, unsigned char numOfValues )
{
	for( int i = 0; i < numOfValues; i++)
		Serial.println(samples[i]);
}

bool RFWrapper::sendPhase( float *samples, unsigned char numOfValues )
{
	
}

bool RFWrapper::sendTemperature( float temperature )
{
	
}

bool RFWrapper::sendHumidity( unsigned char humidity )
{
	
}

bool RFWrapper::sendBatteryVoltage( float batteryVoltage )
{
	
}