/*
*
*
*
*
*
*/

#ifndef RF_INTERFACE_H
#define RF_INTERFACE_H

/*
*
*/
bool sendImpedance( float *samples, unsigned char numOfValues );

bool sendPhase( float *samples, unsigned char numOfValues );

bool sendTemperature( float temperature );

bool sendHumidity( unsigned char humidity );

bool sendBatteryVoltage( float batteryVoltage );

#endif