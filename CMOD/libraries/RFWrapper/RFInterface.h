/*
*
*
*
*
*
*/

#ifndef RF_INTERFACE_H
#define RF_INTERFACE_H

#include "WProgram.h"

/*
*
*/

typedef struct {
    uint8_t frame_length;
    uint8_t rx_data[116]; //max data length = (127 aMaxPHYPacketSize - 2 Frame control - 1 sequence number - 2 panid - 2 shortAddr Destination - 2 shortAddr Source - 2 FCS)
    uint8_t lqi;
    uint8_t rssi;
} rx_info;

/**
 * Based on the TXSTAT register, but "better"
 */
typedef struct {
    uint8_t tx_ok:1;
    uint8_t retries:2;
    uint8_t channel_busy:1;
} tx_info;

typedef void(*ACKCallback)(); //this callback is called when a message is successfully sent

typedef void(*RXCallback)(); //who receive a notification with this callback, have to call getRXData to receive the data buffer.

void initRF();

bool sendImpedance( float *samples, unsigned char numOfValues, ACKCallback callback );

bool sendPhase( float *samples, unsigned char numOfValues, ACKCallback callback );

bool sendTemperature( float temperature, ACKCallback callback );

bool sendHumidity( unsigned char humidity, ACKCallback callback );

bool sendBatteryVoltage( float batteryVoltage, ACKCallback callback );

rx_info *getRXData(int &dataLen);

tx_info *getTXData();

bool registerRXCallback(RXCallback callback);

#endif