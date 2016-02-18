/*
*
*
*
*
*
*/

#ifndef RF_WRAPPER_H
#define RF_WRAPPER_H

class RFWrapper // mosteneste libraria rf
{
public:
	RFWrapper();
	~RFWrapper();

	/*
	*
	*/
	bool sendImpedance( float *samples, unsigned char numOfValues );

	bool sendPhase( float *samples, unsigned char numOfValues );

	bool sendTemperature( float temperature );

	bool sendHumidity( unsigned char humidity );

	bool sendBatteryVoltage( float batteryVoltage );
	
private: //membri privati, variabile
	

};

#endif