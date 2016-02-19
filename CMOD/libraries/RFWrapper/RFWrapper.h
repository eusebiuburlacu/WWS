/*
*
*
*
*
*
*/

#ifndef RF_WRAPPER_H
#define RF_WRAPPER_H

#include "mrf24j.h"

class RFWrapper: public Mrf24j  // mosteneste libraria rf
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
	void tx_handler(void);
	void rx_handler(void)
	
private: //membri privati, variabile
	

};

#endif