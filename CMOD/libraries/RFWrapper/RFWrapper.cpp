//source code for RF-TX device 
#include "RFWrapper.h"
#include "WProgram.h"

	const int pin_reset = 6;      //chipKIT_CMOD J1-08
	const int pin_cs = 24;        //chipKIT_CMOD J1-01
	const int pin_interrupt = 7;  //chipKIT_CMOD J1-07/INT3
	const int source = 0x6001;
	const word dest = 0x4202;
	//const int dest = 0x6002; for receiving RF 
	
RFWrapper::RFWrapper(): Mrf24j(pin_reset, pin_cs, pin_interrupt)
{
	this->reset();
	this->init(); //here we set also the channel number 12
	this->set_pan(0xcafe); //identical for the RF_TX & RF-RX devices
	
	this->address16_write(source); // for receiving set argument to "dest"
	Serial.println("RFWrapper"); //test if write function went OK	
}

RFWrapper::~RFWrapper()
{
	
}

bool RFWrapper::sendImpedance( float *samples, unsigned char numOfValues )
{
	bool result = false;
	if( samples != 0 )
	{
		byte *data = (byte *)(void *)samples;
		int dataLen = numOfValues * sizeof(float);
		sendData( dest, (byte)RF_MESSAGE_IMPEDANCE, data, dataLen );
		result = true;
	}
	else
	{
		Serial.println("RFWrapper::sendImpedance: ERROR: NULL pointer");
	}
	return result;
}

bool RFWrapper::sendPhase( float *samples, unsigned char numOfValues )
{
	bool result = false;
	return result;
}

bool RFWrapper::sendTemperature( float temperature )
{
	bool result = false;
	return result;
}

bool RFWrapper::sendHumidity( unsigned char humidity )
{
	bool result = false;
	return result;
}

bool RFWrapper::sendBatteryVoltage( float batteryVoltage )
{
	bool result = false;
	return result;
}

void RFWrapper::tx_handler(void) 
{
    if (get_txinfo()->tx_ok) 
	{
        Serial.println("TX went ok, got ack");
    } 
	else 
	{
        Serial.print("TX failed after ");Serial.print(get_txinfo()->retries);Serial.println(" retries\n");
    }
}
void RFWrapper::rx_handler() 
{
    //nothing to receive 
}