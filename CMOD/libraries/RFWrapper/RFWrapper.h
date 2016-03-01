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

typedef enum
{
	RF_MESSAGE_IMPEDANCE = 1,
	RF_MESSAGE_PHASE,
	RF_MESSAGE_TEMPERATURE,
	RF_MESSAGE_HUMIDITY,
	RF_MESSAGE_BATTERY
} RF_MESSAGE_TYPES;


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
	
	void rx_handler(void);
	
private: //membri privati, variabile
	

};

#endif