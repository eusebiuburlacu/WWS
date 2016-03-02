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

bool RFWrapper::sendImpedance( float *samples, unsigned char numOfValues, ACKCallback callback )
{
	bool result = false;
	if( samples != 0 && callback != 0 )
	{
		registerACKCallback(callback);
		byte *data = (byte *)(void *)samples;
		int dataLen = numOfValues * sizeof(float);
		sendData( dest, (byte)RF_MESSAGE_IMPEDANCE, data, dataLen );
		Serial.println("RFWrapper::sendImpedance");
		result = true;
	}
	else
	{
		Serial.println("RFWrapper::sendImpedance: ERROR: NULL pointer");
	}
	return result;
}

bool RFWrapper::sendPhase( float *samples, unsigned char numOfValues, ACKCallback callback )
{
	bool result = false;
	if( samples != 0 && callback != 0 )
	{
		registerACKCallback(callback);
		byte *data = (byte *)(void *)samples;
		int dataLen = numOfValues * sizeof(float);
		sendData( dest, (byte)RF_MESSAGE_PHASE, data, dataLen );
		Serial.println("RFWrapper::sendPhase");
		result = true;
	}
	else
	{
		Serial.println("RFWrapper::sendPhase: ERROR: NULL pointer");
	}
	return result;
}

bool RFWrapper::sendTemperature( float temperature, ACKCallback callback )
{
	bool result = false;
	if( callback != 0 )
	{
		registerACKCallback(callback);
		byte *data = (byte *)(void *)&temperature;
		int dataLen = sizeof(float);
		sendData( dest, (byte)RF_MESSAGE_TEMPERATURE, data, dataLen );
		Serial.println("RFWrapper::sendTemperature");
		result = true;
	}
	else
	{
		Serial.println("RFWrapper::sendTemperature: ERROR: NULL pointer");
	}

	return result;
}

bool RFWrapper::sendHumidity( unsigned char humidity, ACKCallback callback )
{
	bool result = false;
	
	if( callback != 0 )
	{
		registerACKCallback(callback);
		byte *data = (byte *)(void *)&humidity;
		int dataLen = sizeof(unsigned char);
		sendData( dest, (byte)RF_MESSAGE_HUMIDITY, data, dataLen );
		Serial.println("RFWrapper::sendHumidity");
		result = true;
	}
	else
	{
		Serial.println("RFWrapper::sendHumidity: ERROR: NULL pointer");
	}

	return result;
}

bool RFWrapper::sendBatteryVoltage( float batteryVoltage, ACKCallback callback )
{
	bool result = false;

	if( callback != 0 )
	{
		registerACKCallback(callback);
		byte *data = (byte *)(void *)&batteryVoltage;
		int dataLen = sizeof(float);
		sendData( dest, (byte)RF_MESSAGE_BATTERY, data, dataLen );
		Serial.println("RFWrapper::sendBatteryVoltage");
		result = true;
	}
	else
	{
		Serial.println("RFWrapper::sendBatteryVoltage: ERROR: NULL pointer");
	}

	return result;
}