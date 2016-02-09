/*
*
*
*
*
*
*/

#include "RFInterface.h"
#include "RFWrapper.h"

static RFWrapper m_rfWrapper;

bool sendImpedance( float *samples, unsigned char numOfValues )
{
	m_rfWrapper.sendImpedance( samples, numOfValues );
}

bool sendPhase( float *samples, unsigned char numOfValues )
{
	
}

bool sendTemperature( float temperature )
{
	
}

bool sendHumidity( unsigned char humidity )
{
	
}

bool sendBatteryVoltage( float batteryVoltage )
{
	
}